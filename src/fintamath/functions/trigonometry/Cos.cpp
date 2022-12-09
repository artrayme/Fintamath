#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {
  std::string Cos::toString() const {
    return "cos";
  }

  std::string Cos::getClassName() const {
    return "Cos";
  }

  MathObjectPtr Cos::call(const std::vector<std::reference_wrapper<const IMathObject>> &argsVect) const {
    return cos(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
  }
}
