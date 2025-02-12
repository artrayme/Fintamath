#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/functions/powers/Root.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqrt::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = argsVect.front().get();
  static const Integer rhs = 2;

  return Root()(lhs, rhs);
}

}
