#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class And : public IOperatorCRTP<Boolean, And, Boolean, Boolean> {
public:
  And() : IOperatorCRTP(IOperator::Priority::Conjunction, true) {
  }

  std::string toString() const override {
    return "&";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::And;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(And, andExpr);

}
