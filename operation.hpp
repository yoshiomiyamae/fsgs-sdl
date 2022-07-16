#pragma once
#include <vector>
#include "action.hpp"
#include "parameter.hpp"

namespace FSGS
{
  struct Operation
  {
    Actions action;
    ParameterCollection params;
  };
  using OperationCollection = std::vector<Operation>;
}