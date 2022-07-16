#pragma once
#include "operation.hpp"
#include "index.hpp"

namespace FSGS
{
  struct Script
  {
    OperationCollection scenario;
    Indices labelIndices;
    Indices macroIndices;
  };
}