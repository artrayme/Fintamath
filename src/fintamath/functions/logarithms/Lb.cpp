#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

unique_ptr<IMathObject> Lb::call(const ArgumentsRefVector &argsVect) const {
  return lb(convert<Real>(argsVect.front())).toMinimalObject();
}

}
