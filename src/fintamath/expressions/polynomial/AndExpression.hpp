#pragma once

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/expressions/IPolynomExpression.hpp"

namespace fintamath {

class AndExpression : public IPolynomExpressionCRTP<AndExpression>, public ILogicNegatableExpression {
public:
  explicit AndExpression(const ArgumentsPtrVector &inChildren);

  ArgumentPtr logicNegate() const override;

protected:
  ArgumentPtr postSimplifyChildren(size_t lhsChildNum, size_t rhsChildNum) const override;

  SimplifyFunctionsVector getFunctionsForSimplify() const override;

  bool isComparableOrderInversed() const override;

  bool isUnaryOperatorsOrderInversed() const override;

private:
  static ArgumentPtr simplifyEqual(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyNot(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyOr(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  static ArgumentPtr simplifyBooleans(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

private:
  static const SimplifyFunctionsVector simplifyFunctions;
};

}