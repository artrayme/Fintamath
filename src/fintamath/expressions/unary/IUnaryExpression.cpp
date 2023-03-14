#include "fintamath/expressions/unary/IUnaryExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

// void IUnaryExpression::setPrecision(uint8_t precision) {
//   if (const auto expr = cast<IExpression>(child)) {
//     expr->setPrecision(precision);
//     return;
//   }

//   if (const auto constant = cast<IConstant>(child)) {
//     child = (*constant)();
//   }

//   if (is<INumber>(child)) {
//     child = make_shared<Real>(convert<Real>(*child).precise(precision));
//   }
// }

string IUnaryExpression::toString() const {
  if (!func) {
    return {};
  }

  if (const auto oper = cast<IOperator>(func)) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixToString();
    default:
      return prefixToString();
    }
  }

  return functionToString();
}

string IUnaryExpression::postfixToString() const {
  string result = child->toString();

  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (IOperator::Priority priority = exprOper->getOperatorPriority();
          priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + func->toString();
      }
    }
  }

  if (const auto comp = cast<IComparable>(child); comp && *comp < ZERO) {
    return putInBrackets(result) + func->toString();
  }

  return result + func->toString();
}

string IUnaryExpression::prefixToString() const {
  string result = func->toString();

  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (IOperator::Priority priority = exprOper->getOperatorPriority();
          priority == IOperator::Priority::PrefixUnary || priority == IOperator::Priority::Multiplication ||
          priority == IOperator::Priority::Exponentiation) {
        return result + child->toString();
      }

      return result + putInBrackets(child->toString());
    }
  }

  return result + child->toString();
}

string IUnaryExpression::functionToString() const {
  return func->toString() + "(" + child->toString() + ")";
}

// void IUnaryExpression::simplifyValue(bool isPrecise) {
//   IExpression::simplifyChild(child);
// }

shared_ptr<IFunction> IUnaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IUnaryExpression::getChildren() const {
  return {child};
}

ArgumentPtr IUnaryExpression::simplify() const {
  if (auto res = preSimplify()) {
    simplifyChild(res);
    return res;
  }

  auto simpl = cast<IUnaryExpression>(clone());
  simplifyChild(simpl->child);

  if (func->isNonExressionEvaluatable() && func->doArgsMatch({*simpl->child})) {
    return (*func)(*simpl->child);
  }

  if (auto res = simpl->preSimplify()) { // TODO: try to remove this
    return res;
  }

  if (auto res = simpl->postSimplify()) {
    return res;
  }

  return simpl;
}

ArgumentPtr IUnaryExpression::preSimplify() const {
  return {};
}

ArgumentPtr IUnaryExpression::postSimplify() const {
  return {};
}

}