#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Log f;

TEST(LogTests, toStringTest) {
  EXPECT_EQ(f.toString(), "log");
}

TEST(LogTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(LogTests, callTest) {
  EXPECT_EQ(f(Integer(10), Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(0), Integer(10))->toString(), "0");

  EXPECT_EQ(f(Integer(10), Integer(10))->toString(), "1");
  EXPECT_EQ(f(Integer(10), Rational(1, 10))->toString(), "-1");
  EXPECT_EQ(f(Rational(1, 10), Integer(10))->toString(), "-1");
  EXPECT_EQ(f(Rational(1, 10), Rational(1, 10))->toString(), "1");

  EXPECT_EQ(f(Integer(11), Integer(11))->toString(), "1");
  EXPECT_EQ(f(Integer(11), Rational(1, 11))->toString(), "-1");
  EXPECT_EQ(f(Rational(1, 11), Integer(11))->toString(), "-1");
  EXPECT_EQ(f(Rational(1, 11), Rational(1, 11))->toString(), "1");

  EXPECT_EQ(f(Integer(10), Integer("10000000000000000000000000000000000000000000000000000000000"))->toString(), "58");
  EXPECT_EQ(f(Integer("10000000000000000000000000000000000000000000000000000000000"), Integer(10))->toString(), "1/58");

  EXPECT_EQ(f(Integer(121), Integer(11))->toString(), "1/2");
  EXPECT_EQ(f(Rational(1, 11), Integer(121))->toString(), "-2");
  EXPECT_EQ(f(Rational(1, 121), Integer(11))->toString(), "-1/2");
  EXPECT_EQ(f(Integer(121), Rational(1, 11))->toString(), "-1/2");
  EXPECT_EQ(f(Integer(11), Rational(1, 121))->toString(), "-2");

  EXPECT_EQ(f(Rational(7, 9), Rational(40353607, 387420489))->toString(), "9");
  EXPECT_EQ(f(Rational(40353607, 387420489), Rational(7, 9))->toString(), "1/9");
  EXPECT_EQ(f(Rational(387420489, 40353607), Rational(7, 9))->toString(), "-1/9");

  EXPECT_EQ(f(Integer(2), Integer(10))->toString(),
            "3.3219280948873623478703194294893901758648313930245806120547563958159347766086252");
  EXPECT_EQ(f(Integer(2), Integer(3))->toString(),
            "1.5849625007211561814537389439478165087598144076924810604557526545410982277943586");
  EXPECT_EQ(f(Integer(10), Real(121))->toString(),
            "2.0827853703164500815003999424860484834134043809329061891930780373595060644664987");
  EXPECT_EQ(f(Real(121), Integer(10))->toString(),
            "0.4801262838945637487030558225096301948381401591993519366116255938360392246042024");
  EXPECT_EQ(f(1 / Real(121), Integer(10))->toString(),
            "-0.4801262838945637487030558225096301948381401591993519366116255938360392246042024");
  EXPECT_EQ(f(Integer(10), 1 / Real(121))->toString(),
            "-2.0827853703164500815003999424860484834134043809329061891930780373595060644664987");

  EXPECT_EQ(f(Complex(1, 1), Complex(1, 1))->toString(), "1");
  EXPECT_EQ(f(Complex(1, 1), Complex(1, 2))->toString(), "log(1 + I, 1 + 2 I)");
  EXPECT_EQ(f(Complex(1, 1), Integer(1))->toString(), "0");

  EXPECT_EQ(f(Integer(10), Integer(0))->toString(), "-Inf");
  EXPECT_EQ(f(Rational(1, 10), Integer(0))->toString(), "Inf");
  EXPECT_EQ(f(Integer(1), Integer(10))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1), Complex(1, 1))->toString(), "ComplexInf");
  EXPECT_EQ(f(Integer(1), Integer(1))->toString(), "Undefined");
  EXPECT_EQ(f(Integer(0), Integer(0))->toString(), "Undefined");

  EXPECT_EQ(f(Integer(-10), Integer(10))->toString(), "log(-10, 10)");
  EXPECT_EQ(f(Integer(10), Integer(-10))->toString(), "log(10, -10)");
  EXPECT_EQ(f(Real("-10.2"), Integer(-10))->toString(), "log(-10.2, -10)");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "log(a, b)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LogTests, exprTest) {
  EXPECT_EQ(logExpr(Integer(10), Integer(10))->toString(), "log(10, 10)");
}

TEST(LogTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(LogTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Log());
  EXPECT_EQ(Log(), f);
  EXPECT_EQ(f, cast<IMathObject>(Log()));
  EXPECT_EQ(cast<IMathObject>(Log()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(LogTests, getTypeTest) {
  EXPECT_EQ(Log::getTypeStatic(), MathObjectType::Log);
  EXPECT_EQ(Log().getType(), MathObjectType::Log);
}
