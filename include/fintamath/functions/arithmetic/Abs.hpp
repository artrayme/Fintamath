#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Abs : public IFunctionCRTP<INumber, Abs, INumber> {
public:
  Abs() = default;

  std::string toString() const override {
    return "abs";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Abs;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAbsSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Abs, absExpr);

}
