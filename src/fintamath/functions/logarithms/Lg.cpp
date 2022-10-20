#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/numbers/NumericFunctions.hpp"

namespace fintamath {
  std::string Lg::toString() const {
    return "lg";
  }

  MathObjectPtr Lg::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    constexpr int64_t defaultPrecision = 45;
    return lg(help::convertMathObject(argsVect.at(0), Rational())->to<Rational>(), defaultPrecision).simplify();
  }

  static const bool isAdded = IFunction::addParser<Lg>();
}
