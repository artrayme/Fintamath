#pragma once

#include <cstdint>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/expressions/interfaces/ILogicNegatable.hpp"
#include "fintamath/expressions/polynomial/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression>, public ILogicNegatable {
public:
  explicit AndExpression(const ArgumentsPtrVector &children);

  string toString() const override;

  void logicNegate() override;

protected:
  shared_ptr<IMathObject> postSimplify(size_t lhsChildNum, size_t rhsChildNum) const override;
};

}