#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/powers/Pow.hpp"

using namespace fintamath;

TEST(PowExpressionTests, getTypeTest) {
  EXPECT_EQ(powExpr(Integer(0), Integer(0))->getType(), MathObjectType::PowExpression);
}
