#include "gtest/gtest.h"

#include "fintamath/functions/arithmetic/Sign.hpp"

#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

const Sign f;

TEST(SignTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sign");
}

TEST(SignTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SignTests, callTest) {
  EXPECT_EQ(f(Integer(-10))->toString(), "-1");
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(), "1");

  EXPECT_EQ(f(Rational(-10, 3))->toString(), "-1");
  EXPECT_EQ(f(Rational(10, 3))->toString(), "1");
  
  EXPECT_EQ(f(Real("-1.23"))->toString(), "-1");
  EXPECT_EQ(f(Real(0))->toString(), "1");
  EXPECT_EQ(f(Real("1.23"))->toString(), "1");
  
  EXPECT_EQ(f(Complex(2, 0))->toString(), "1");
  EXPECT_EQ(f(Complex(0, 2))->toString(), "I");
  EXPECT_EQ(f(Complex(2, 2))->toString(), "((1 + I) sqrt(2))/2");
  EXPECT_EQ(f(Complex(3, 2))->toString(), "((3 + 2 I) sqrt(13))/13");
  EXPECT_EQ(f(Complex(2, 3))->toString(), "((2 + 3 I) sqrt(13))/13");
  EXPECT_EQ(f(Complex(-2, 0))->toString(), "-1");
  EXPECT_EQ(f(Complex(0, -2))->toString(), "-I");
  EXPECT_EQ(f(Complex(2, -2))->toString(), "((1 - I) sqrt(2))/2");
  EXPECT_EQ(f(Complex(-3, 2))->toString(), "-((3 - 2 I) sqrt(13))/13");
  EXPECT_EQ(f(Complex(2, -3))->toString(), "((2 - 3 I) sqrt(13))/13");
  EXPECT_EQ(f(Complex(-2, -3))->toString(), "-((2 + 3 I) sqrt(13))/13");

  EXPECT_EQ(f(Variable("a"))->toString(), "sign(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SignTests, exprTest) {
  EXPECT_EQ(signExpr(Integer(10))->toString(), "sign(10)");
}

TEST(SignTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SignTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sign());
  EXPECT_EQ(Sign(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sign()));
  EXPECT_EQ(cast<IMathObject>(Sign()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SignTests, getTypeTest) {
  EXPECT_EQ(Sign::getTypeStatic(), MathObjectType::Sign);
  EXPECT_EQ(Sign().getType(), MathObjectType::Sign);
}
