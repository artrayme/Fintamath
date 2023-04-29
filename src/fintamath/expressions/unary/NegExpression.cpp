#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/INegatableExpression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(NEG, inChild) {
}

ArgumentPtr NegExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();

  auto simplExpr = cast<NegExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (const auto expr = cast<NegExpression>(simplExpr->child)) {
    return expr->child;
  }

  return simpl;
}

ArgumentPtr NegExpression::postSimplify() const {
  auto simpl = IUnaryExpression::postSimplify();

  auto simplExpr = cast<NegExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (auto expr = cast<INegatableExpression>(simplExpr->child)) {
    return expr->negate();
  }

  return simpl;
}

}
