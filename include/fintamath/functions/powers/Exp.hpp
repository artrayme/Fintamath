#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Exp : public IFunctionCRTP<INumber, Exp, INumber> {
public:
  Exp() = default;

  std::string toString() const override {
    return "exp";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Exp;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Exp, expExpr);

}
