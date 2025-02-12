#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Neg.hpp"

#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Neg f;

TEST(NegTests, toStringTest) {
  EXPECT_EQ(f.toString(), "-");
}

TEST(NegTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(NegTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::PrefixUnary);
}

TEST(NegTests, isAssociativeTest) {
  EXPECT_FALSE(f.isAssociative());
}

TEST(NegTests, callTest) {
  EXPECT_EQ(f(Integer(3))->toString(), "-3");
  EXPECT_EQ(f(Rational(5, 2))->toString(), "-5/2");
  EXPECT_EQ(f(Rational(-5, 2))->toString(), "5/2");

  EXPECT_EQ(f(Variable("a"))->toString(), "-a");

  EXPECT_THROW(f(Integer(1), Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(NegTests, exprTest) {
  EXPECT_EQ(negExpr(Integer(10))->toString(), "-10");
}

TEST(NegTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(NegTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Neg());
  EXPECT_EQ(Neg(), f);
  EXPECT_EQ(f, cast<IMathObject>(Neg()));
  EXPECT_EQ(cast<IMathObject>(Neg()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(NegTests, getTypeTest) {
  EXPECT_EQ(Neg::getTypeStatic(), MathObjectType::Neg);
  EXPECT_EQ(Neg().getType(), MathObjectType::Neg);
}
