#include "fintamath/expressions/binary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOperatorException.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

DerivativeExpression::DerivativeExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(Derivative(), inLhsChild, inRhsChild) {
}

DerivativeExpression::SimplifyFunctionsVector DerivativeExpression::getFunctionsForPostSimplify() const {
  static const DerivativeExpression::SimplifyFunctionsVector simplifyFunctions = {
      &DerivativeExpression::derivativeSimplify, //
  };
  return simplifyFunctions;
}

ArgumentPtr DerivativeExpression::derivativeSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  // TODO: remove this and implement derivative with rhs !is Variable
  if (!is<Variable>(rhs)) {
    throw InvalidInputFunctionException(Derivative().toString(), {lhs->toString(), rhs->toString()});
  }

  ArgumentPtr res;

  if (is<INumber>(lhs) || is<IConstant>(lhs)) {
    res = ZERO.clone();
  }
  else if (is<Variable>(lhs) && *lhs == *rhs) {
    res = ONE.clone();
  }

  return res;
}

}