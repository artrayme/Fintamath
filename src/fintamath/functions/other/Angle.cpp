#include "fintamath/functions/other/Angle.hpp"

#include "fintamath/functions/other/Rad.hpp"

namespace fintamath {

unique_ptr<IMathObject> Angle::call(const ArgumentsRefVector &argsVect) const {
  static const Rad RAD;
  return RAD(argsVect.front().get());
}

}
