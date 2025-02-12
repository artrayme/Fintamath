#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

IBinaryExpression::IBinaryExpression(const IFunction &inFunc, ArgumentPtr lhs, ArgumentPtr rhs)
    : func(cast<IFunction>(inFunc.clone())),
      lhsChild(std::move(lhs)),
      rhsChild(std::move(rhs)) {
}

std::string IBinaryExpression::toString() const {
  if (auto oper = cast<IOperator>(func)) {
    return binaryOperatorToString(*oper, lhsChild, rhsChild);
  }

  return functionToString(*func, {lhsChild, rhsChild});
}

const std::shared_ptr<IFunction> &IBinaryExpression::getFunction() const {
  return func;
}

const ArgumentPtrVector &IBinaryExpression::getChildren() const {
  childrenCached.front() = lhsChild;
  childrenCached.back() = rhsChild;
  return childrenCached;
}

ArgumentPtr IBinaryExpression::preSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  preSimplifyChild(simpl->lhsChild);
  preSimplifyChild(simpl->rhsChild);
  return simpl->simplifyRec(false);
}

ArgumentPtr IBinaryExpression::postSimplify() const {
  auto simpl = cast<IBinaryExpression>(clone());
  postSimplifyChild(simpl->lhsChild);
  postSimplifyChild(simpl->rhsChild);
  return simpl->simplifyRec(true);
}

ArgumentPtr IBinaryExpression::simplifyRec(bool isPostSimplify) const {
  if (ArgumentPtr res = simplifyUndefined(*func, lhsChild, rhsChild)) {
    return res;
  }

  if (ArgumentPtr res = callFunction(*func, {lhsChild, rhsChild})) {
    return res;
  }

  ArgumentPtr res = isPostSimplify ? useSimplifyFunctions(getFunctionsForPostSimplify(),
                                                          *func,
                                                          lhsChild,
                                                          rhsChild)
                                   : useSimplifyFunctions(getFunctionsForPreSimplify(),
                                                          *func,
                                                          lhsChild,
                                                          rhsChild);

  if (res && *res != *this) {
    if (isPostSimplify) {
      postSimplifyChild(res);
    }
    else {
      preSimplifyChild(res);
    }

    return res;
  }

  return clone();
}

IBinaryExpression::SimplifyFunctionVector IBinaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IBinaryExpression::SimplifyFunctionVector IBinaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

void IBinaryExpression::setChildren(const ArgumentPtrVector &childVect) {
  if (childVect.size() != 2) {
    throw InvalidInputFunctionException(toString(), argumentVectorToStringVector(childVect));
  }

  lhsChild = childVect[0];
  rhsChild = childVect[1];
}

}
