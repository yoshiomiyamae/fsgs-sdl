#pragma once
#include <vector>
#include "action.hpp"
#include "parameter.hpp"
#include <string>

namespace FSGS
{
  struct Operation
  {
    std::string action;
    ParameterCollection params;
  };
  using OperationCollection = std::vector<Operation>;
}