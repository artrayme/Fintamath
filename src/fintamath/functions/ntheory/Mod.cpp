#include "fintamath/functions/ntheory/Mod.hpp"

#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Mod::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  if (rhs == Integer(0)) {
    return Undefined().clone();
  }

  return multiModSimplify(lhs, rhs);
}

std::unique_ptr<IMathObject> Mod::multiModSimplify(const INumber &lhs, const INumber &rhs) {
  // TODO: implement non-integer modulo

  static const auto multiMod = [] {
    static MultiMethod<std::unique_ptr<IMathObject>(const INumber &, const INumber &)> outMultiMod;

    outMultiMod.add<Integer, Integer>([](const Integer &inLhs, const Integer &inRhs) {
      Integer mod = inLhs % inRhs;

      if (mod != 0 && inLhs.sign() != inRhs.sign()) {
        mod += inRhs;
      }

      return std::move(mod).clone();
    });

    return outMultiMod;
  }();

  return multiMod(lhs, rhs);
}

}
