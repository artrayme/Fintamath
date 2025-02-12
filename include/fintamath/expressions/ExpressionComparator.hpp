#pragma once

#include "fintamath/functions/FunctionArguments.hpp"

namespace fintamath {

struct ComparatorOptions {
  bool constantGreaterThanVariable = false;
  bool comparableOrderInversed = false;
};

std::strong_ordering compare(ArgumentPtr lhs, ArgumentPtr rhs, ComparatorOptions options = {});

}
