#include "fintamath/functions/trigonometry/Asec.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asec::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs == Integer(-1)) {
    return Pi().toMinimalObject();
  }

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  if (rhs == Integer(1)) {
    return Integer(0).clone();
  }

  return multiAsecSimplify(rhs);
}

std::unique_ptr<IMathObject> Asec::multiAsecSimplify(const INumber &rhs) {
  static const auto multiAsec = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &)> outMultiAsec;

    outMultiAsec.add<Integer>([](const Integer &inRhs) {
      return multiAsecSimplify(Real(inRhs));
    });

    outMultiAsec.add<Rational>([](const Rational &inRhs) {
      return multiAsecSimplify(Real(inRhs));
    });

    outMultiAsec.add<Real>([](const Real &inRhs) {
      return asec(inRhs).clone();
    });

    return outMultiAsec;
  }();

  return multiAsec(rhs);
}

}
