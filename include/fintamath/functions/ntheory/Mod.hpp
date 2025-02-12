#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Mod : public IOperatorCRTP<INumber, Mod, INumber, INumber> {
public:
  Mod() : IOperatorCRTP(IOperator::Priority::Modulo) {
  }

  std::string toString() const override {
    return "mod";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Mod;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiModSimplify(const INumber &lhs, const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Mod, modExpr);

}
