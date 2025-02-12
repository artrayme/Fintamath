#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Equiv : public IOperatorCRTP<Boolean, Equiv, Boolean, Boolean> {
public:
  Equiv() : IOperatorCRTP(IOperator::Priority::Equivalence, true) {
  }

  std::string toString() const override {
    return "<->";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Equiv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Equiv, equivExpr);

}
