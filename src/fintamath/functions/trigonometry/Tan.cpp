#include "fintamath/functions/trigonometry/Tan.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Tan::call(const ArgumentsVector &argsVect) const {
  return tan(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
