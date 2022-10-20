#include "fintamath/functions/factorials/DoubleFactorial.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  DoubleFactorial::DoubleFactorial() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string DoubleFactorial::toString() const {
    return "!!";
  }

  MathObjectPtr DoubleFactorial::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return std::make_unique<Integer>(doubleFactorial(argsVect.at(0).get().to<Integer>()));
  }

  static const bool isAdded = IOperator::addParser<DoubleFactorial>();
}
