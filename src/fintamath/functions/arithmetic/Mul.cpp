#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {
  Mul::Mul() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string Mul::toString() const {
    return "*";
  }

  MathObjectPtr Mul::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return argsVect.at(0).get().to<IArithmetic>() * argsVect.at(1).get().to<IArithmetic>();
  }

  static const bool IS_ADDED = IOperator::addParser<Mul>();
}
