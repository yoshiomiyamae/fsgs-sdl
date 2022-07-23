#include "parser.hpp"
#include <regex>
#include <string>
#include "common.hpp"

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
        return temp.empty() ? false : temp.back().action == Actions::INLINE_SCRIPT;
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
            scenario.push_back(Operation{Actions::LABEL, pc});
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
    return op.action != Actions::TEXT || std::regex_replace(get(op.params, "text", std::string("")), re, "") != ""; });

    Indices macroIndices;
    for (int index = 0; index < scenario.size(); index++)
    {
      const auto operation = scenario[index];
      if (operation.action == Actions::MACRO)
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

    return OperationCollection{};
  }

  Sentences Parser::cleanse(std::string script)
  {
    return Sentences{};
  }
}