#include "parser.hpp"
#include <regex>
#include <string>
#include "common.hpp"
#include "action.hpp"

namespace FSGS
{
  Script Parser::parse(std::string script)
  {
    const auto sentences = cleanse(script);
    static OperationCollection scenario;
    Indices labelIndices;
    static std::string nonLabelText = "";
    struct
    {
      bool operator()()
      {
        const auto analyzed = analyze(nonLabelText);
        OperationCollection temp;
        temp.insert(temp.end(), scenario.begin(), scenario.end());
        temp.insert(temp.end(), analyzed.begin(), analyzed.end());
        return temp.empty() ? false : temp.back().action == INLINE_SCRIPT;
      }
    } checkInScript;

    for (auto sentence : sentences)
    {
      if (sentence.empty())
      {
        continue;
      }
      if (sentence[0] == '*')
      {
        // Label line
        if (nonLabelText != "" && !checkInScript())
        {
          const auto analyzed = analyze(nonLabelText);
          scenario.insert(scenario.end(), analyzed.begin(), analyzed.end());
          nonLabelText = "";
        }

        if (!checkInScript())
        {
          std::regex re(R"(^\*(.*?)(\|(.*))?$)");
          std::smatch m;
          if (std::regex_match(sentence, m, re))
          {
            const auto labelName = m[0].str();
            const auto labelAlias = m[1].str();
            labelIndices.insert(std::make_pair(labelName, scenario.size()));
            ParameterCollection pc;
            pc.insert(std::make_pair(labelName, labelName));
            scenario.push_back(Operation{LABEL, pc});
          }
          else
          {
            nonLabelText += sentence + "\r\n";
          }
        }
        else if (checkInScript())
        {
          nonLabelText += sentence + "\r\n";
        }
        else
        {
          nonLabelText += sentence;
        }
      }
    }

    const auto analyzed = analyze(nonLabelText);
    scenario.insert(scenario.end(), analyzed.begin(), analyzed.end());
    filter(scenario, [](const Operation &op)
           { 
    std::regex re(R"(\r\n)");
    return op.action != TEXT || std::regex_replace(get(op.params, "text", std::string("")), re, "") != ""; });

    Indices macroIndices;
    for (int index = 0; index < scenario.size(); index++)
    {
      const auto operation = scenario[index];
      if (operation.action == MACRO)
      {
        macroIndices.insert(std::make_pair(get(operation.params, "name", std::string("")), index));
      }
    }

    return Script{scenario, labelIndices, macroIndices};
  }

  OperationCollection Parser::analyze(std::string script)
  {
    OperationCollection output;
    bool inTag = false;
    bool inText = false;
    bool inParam = false;
    std::string temp = "";
    std::string tagName = "";
    std::string paramName = "";
    ParameterCollection tagParams;
    bool inScript = false;

    for (int i = 0; i < script.length(); i++)
    {
      const char currentCharacter = script[i];
      switch (currentCharacter)
      {
      case '[':
      {
        if (script[i + 1] == '[')
        {
          temp += currentCharacter;
          i++;
          break;
        }
        if (inScript)
        {
          if (script.substr(i + 1, 10) != "endscript")
          {
            temp += currentCharacter;
            break;
          }
          else
          {
            auto params = ParameterCollection();
            params["script"] = temp;
            output.push_back(Operation{INLINE_SCRIPT, params});
            inScript = false;
            inTag = false;
            tagName = "";
            temp = "";
            i += 10;
            break;
          }
        }
        if (!inText)
        {
          if (temp != "")
          {
            auto params = ParameterCollection();
            params["text"] = temp;
            output.push_back(Operation{TEXT, params});
            temp = "";
          }
          inTag = true;
        }
        else
        {
          temp += currentCharacter;
        }
        break;
      }
      case ']':
      {
        if (script[i + 1] == ']')
        {
          temp += currentCharacter;
          i++;
          break;
        }
        if (inTag && !inText)
        {
          if (tagName == "")
          {
            tagName = temp;
            temp = "";
            inParam = true;
          }
          else if (inParam)
          {
            if (paramName != "")
            {
              tagParams[paramName] = temp;
              paramName = "";
              temp = "";
              inParam = false;
            }
            else
            {
              tagParams[temp] = true;
              temp = "";
            }
          }
          if (tagName == "iscript")
          {
            inScript = true;
          }
          output.push_back(Operation{tagName, tagParams});
          tagName = "";
          tagParams = {};
          inTag = false;
        }
        else
        {
          temp += currentCharacter;
        }
        break;
      }
      case '"':
      {
        if (inTag && !inScript)
        {
          inText = !inText;
        }
        else
        {
          temp += currentCharacter;
        }
        break;
      }
      case '*':
      {
        if (inTag && paramName == "" && !inText && !inScript)
        {
          tagParams["inherit_macro_params"] = true;
        }
        else
        {
          temp += currentCharacter;
        }
        break;
      }
      case ' ':
      {
        if (inTag && !inText)
        {
          if (tagName == "")
          {
            tagName = temp;
            temp = "";
            inParam = true;
          }
          else if (inParam)
          {
            if (paramName != "")
            {
              tagParams[paramName] = temp;
              paramName = "";
              temp = "";
            }
            else
            {
              tagParams[temp] = true;
              temp = "";
            }
          }
          else
          {
            temp += currentCharacter;
          }
          break;
        }
      case '=':
      {
        if (inTag && inParam && !inText)
        {
          paramName = temp;
          temp = "";
        }
        else
        {
          temp += currentCharacter;
        }
        break;
      }
      default:
      {
        temp += currentCharacter;
        break;
      }
      }
      }
    }

    if (temp == "")
    {
      return output;
    }
    if (inScript)
    {
      auto params = ParameterCollection();
      params["script"] = temp;
      output.push_back(Operation{INLINE_SCRIPT, params});
    }
    else
    {
      auto params = ParameterCollection();
      params["text"] = temp;
      output.push_back(Operation{INLINE_SCRIPT, params});
      temp = "";
    }

    return output;
  }

  Sentences Parser::cleanse(std::string sentence)
  {
    Sentences output;
    for (std::string line : split(sentence, "\r\n"))
    {
      if (line == "" || line.length() < 1 || line[0] == ';')
      {
        continue;
      }
      std::regex re(R"(^\t*(.*)$)");
      std::smatch m;
      if (std::regex_match(line, m, re))
      {
        auto sentence = m[1].str();
        if (sentence[0] == '@')
        {
          output.push_back('[' + sentence.substr(1) + ']');
          continue;
        }
        output.push_back(sentence);
      }
    }
    return output;
  }
}