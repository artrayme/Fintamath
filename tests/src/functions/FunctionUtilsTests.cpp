#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/IFunction.hpp"

#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(FunctionUtilsTests, makeExpressionPtrsTest) {
  ArgumentPtr one = std::make_unique<Integer>(1);
  ArgumentPtr two = std::make_unique<Integer>(2);
  auto expr1 = makeExpr(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_FALSE(is<INumber>(expr1));

  ArgumentPtr var = std::make_unique<Variable>("a");
  ArgumentPtr expr2 = makeExpr(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));

  EXPECT_THROW(makeExpr(Mul(), ArgumentPtrVector{var})->toString(), InvalidInputException);
  EXPECT_THROW(makeExpr(Mul(), ArgumentPtrVector{})->toString(), InvalidInputException);
  EXPECT_THROW(makeExpr(Pow(), ArgumentPtrVector{var})->toString(), InvalidInputException);
  EXPECT_THROW(makeExpr(Pow(), ArgumentPtrVector{})->toString(), InvalidInputException);
}

TEST(FunctionUtilsTests, makeExpressionRefsTest) {
  Integer one = 1;
  Integer two = 2;
  auto expr1 = makeExpr(Add(), {one, two});
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_FALSE(is<INumber>(expr1));

  Variable var("a");
  auto expr2 = makeExpr(Cos(), {var});
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));

  EXPECT_THROW(makeExpr(Mul(), ArgumentRefVector{var})->toString(), InvalidInputException);
  EXPECT_THROW(makeExpr(Mul(), ArgumentRefVector{})->toString(), InvalidInputException);
  EXPECT_THROW(makeExpr(Pow(), ArgumentRefVector{var})->toString(), InvalidInputException);
  EXPECT_THROW(makeExpr(Pow(), ArgumentRefVector{})->toString(), InvalidInputException);
}

TEST(FunctionUtilsTests, makeExpressionAnyArgsRefTest) {
  auto expr1 = makeExpr(Add(), Integer(1), Integer(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  auto var = Variable("a");
  auto expr2 = makeExpr(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}

TEST(FunctionUtilsTests, makeExpressionAnyArgsPtrTest) {
  auto expr1 = makeExpr(Add(), std::make_shared<Integer>(1), std::make_shared<Integer>(2));
  EXPECT_EQ(expr1->toString(), "1 + 2");
  EXPECT_TRUE(is<IExpression>(expr1));
  EXPECT_FALSE(is<Expression>(expr1));

  auto var = std::make_shared<Variable>("a");
  auto expr2 = makeExpr(Cos(), var);
  EXPECT_EQ(expr2->toString(), "cos(a)");
  EXPECT_TRUE(is<IExpression>(expr2));
  EXPECT_FALSE(is<Expression>(expr2));
}
