#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/polynomial/AndExpression.hpp"
#include "fintamath/expressions/unary/NotExpression.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

const Or OR;

OrExpression::OrExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(OR, children) {
}

std::string OrExpression::toString() const {
  return binaryOperatorToString(OR, children);
}

std::unique_ptr<IMathObject> OrExpression::simplify(bool /*isPrecise*/) const {
  // std::unique_ptr<IMathObject> result = children.front()->clone();
  // for (size_t i = 1; i < children.size(); i++) {
  //   const auto &lhsPtr = result;
  //   const auto &rhsPtr = children[i];
  //   const auto &lhs = *lhsPtr;
  //   const auto &rhs = *rhsPtr;

  //   if (const auto *lhsBool = cast<Boolean>(&lhs)) {
  //     if (*lhsBool == true) {
  //       result = std::make_unique<Boolean>(true);
  //     } else {
  //       *result = *rhsPtr;
  //     }
  //     continue;
  //   }

  //   if (const auto *rhsBool = cast<Boolean>(&rhs)) {
  //     if (*rhsBool == true) {
  //       result = std::make_unique<Boolean>(true);
  //     } else {
  //       *result = *lhsPtr;
  //     }
  //     continue;
  //   }

  //   if (lhs == notL(rhs)) {
  //     result = std::make_unique<Boolean>(true);
  //   }
  // }

  // return result;

  return std::make_unique<OrExpression>(*this);
}

std::shared_ptr<IMathObject> OrExpression::postSimplify(size_t lhsChildNum, size_t rhsChildNum) const {
  const std::shared_ptr<IMathObject> &lhsChild = children[lhsChildNum];
  const std::shared_ptr<IMathObject> &rhsChild = children[rhsChildNum];

  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? std::make_shared<Boolean>(true) : rhsChild;
  }
  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? std::make_shared<Boolean>(true) : lhsChild;
  }

  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  if (const auto lhsNot = cast<NotExpression>(lhsChild); lhsNot && *lhsNot->getChildren().front() == *rhsChild) {
    return std::make_shared<Boolean>(true);
  }
  if (const auto rhsNot = cast<NotExpression>(rhsChild); rhsNot && *rhsNot->getChildren().front() == *lhsChild) {
    return std::make_shared<Boolean>(true);
  }

  return {};
}

void OrExpression::logicNegate() {
  ArgumentsPtrVector negChildren;

  for (const auto &child : children) {
    negChildren.emplace_back(Expression::makeRawFunctionExpression(Not(), {child}));
  }

  children = {std::make_shared<AndExpression>(negChildren)};
}

}
