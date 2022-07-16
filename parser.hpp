#pragma once
#include <string>
#include "script.hpp"
#include "operation.hpp"

namespace FSGS
{
  using Sentences = std::vector<std::string>;

  class Parser final
  {
  public:
    Parser() = delete;
    ~Parser() = delete;
    static Script parse(std::string script);

  private:
    static OperationCollection analyze(std::string script);
    static Sentences cleanse(std::string script);
  };
}