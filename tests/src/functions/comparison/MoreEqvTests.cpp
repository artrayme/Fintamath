#include "gtest/gtest.h"

#include "fintamath/functions/comparison/MoreEqv.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const MoreEqv f;

TEST(MoreEqvTests, toStringTest) {
  EXPECT_EQ(f.toString(), ">=");
}

TEST(MoreEqvTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(MoreEqvTests, getOperatorPriorityTest) {
  EXPECT_EQ(f.getOperatorPriority(), IOperator::Priority::Comparison);
}

TEST(MoreEqvTests, isAssociativeTest) {
  EXPECT_TRUE(f.isAssociative());
}

TEST(MoreEqvTests, callTest) {
  EXPECT_EQ(f(Integer(5), Integer(3))->toString(), "True");
  EXPECT_EQ(f(Integer(3), Integer(5))->toString(), "False");
  EXPECT_EQ(f(Integer(3), Integer(3))->toString(), "True");
  EXPECT_EQ(f(Integer(3), Rational(3, 1))->toString(), "True");
  EXPECT_EQ(f(Rational(5, 2), Integer(2))->toString(), "True");

  EXPECT_EQ(f(Complex(1, 1), Complex(1, 1))->toString(), "1 + I >= 1 + I");
  EXPECT_EQ(f(Complex(1, 1), Complex(1, 2))->toString(), "1 + I >= 1 + 2 I");
  EXPECT_EQ(f(Complex(1, 1), Complex(2, 1))->toString(), "1 + I >= 2 + I");
  EXPECT_EQ(f(Complex(1, 1), Complex(2, 2))->toString(), "1 + I >= 2 + 2 I");

  EXPECT_EQ(f(Integer(3), Variable("a"))->toString(), "a - 3 <= 0");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "True");

  EXPECT_THROW(f(Integer(1)), InvalidInputFunctionException);
  EXPECT_THROW(f(Rational(2, 3)), InvalidInputFunctionException);
  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(MoreEqvTests, exprTest) {
  EXPECT_EQ(moreEqvExpr(Integer(10), Integer(10))->toString(), "10 >= 10");
}

TEST(MoreEqvTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(MoreEqvTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, MoreEqv());
  EXPECT_EQ(MoreEqv(), f);
  EXPECT_EQ(f, cast<IMathObject>(MoreEqv()));
  EXPECT_EQ(cast<IMathObject>(MoreEqv()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(MoreEqvTests, getTypeTest) {
  EXPECT_EQ(MoreEqv::getTypeStatic(), MathObjectType::MoreEqv);
  EXPECT_EQ(MoreEqv().getType(), MathObjectType::MoreEqv);
}
