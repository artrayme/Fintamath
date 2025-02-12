#include "fintamath/functions/calculus/Max.hpp"

#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Max::call(const ArgumentRefVector &argsVect) const {
  std::reference_wrapper<const IComparable> res = cast<IComparable>(argsVect.front().get());

  for (auto i : std::views::iota(1U, argsVect.size())) {
    std::reference_wrapper<const IComparable> arg = cast<IComparable>(argsVect[i].get());

    if (is<Complex>(arg)) {
      return {};
    }

    if (res < arg) {
      res = arg;
    }
  }

  return res.get().clone();
}

}
