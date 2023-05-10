#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

NotExpression::NotExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(Not(), inChild) {
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForSimplify() const {
  static const NotExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NotExpression::simplifyNestedNot, //
  };
  return simplifyFunctions;
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForPreSimplify() const {
  static const NotExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NotExpression::callNotFunction, //
  };
  return simplifyFunctions;
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForPostSimplify() const {
  static const NotExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NotExpression::simplifyLogicNegatable, //
  };
  return simplifyFunctions;
}

ArgumentPtr NotExpression::callNotFunction(const ArgumentPtr &rhs) {
  if (ArgumentPtr res = callFunction(Not(), {rhs})) {
    return res;
  }

  return {};
}

ArgumentPtr NotExpression::simplifyLogicNegatable(const ArgumentPtr &rhs) {
  if (auto expr = cast<ILogicNegatableExpression>(rhs)) {
    return expr->logicNegate();
  }

  return {};
}

ArgumentPtr NotExpression::simplifyNestedNot(const ArgumentPtr &rhs) {
  if (const auto expr = cast<NotExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

}
