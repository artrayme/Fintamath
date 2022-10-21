#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {
  Div::Div() : IOperatorCRTP(IOperator::Priority::Multiplication) {
  }

  std::string Div::toString() const {
    return "/";
  }

  MathObjectPtr Div::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return argsVect.at(0).get().to<IArithmetic>() / argsVect.at(1).get().to<IArithmetic>();
  }

  static const bool IS_ADDED = IOperator::addParser<Div>();
}
