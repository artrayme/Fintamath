#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Cos f;

TEST(CosTests, toStringTest) {
  EXPECT_EQ(f.toString(), "cos");
}

TEST(CosTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(CosTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(),
            "-0.83907152907645245225886394782406483451993016513316854683595373104879258686627077");
  EXPECT_EQ(f(Integer(5))->toString(),
            "0.2836621854632262644666391715135573083344225922522159449303590665861514567673827");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.99500416527802576609556198780387029483857622541508403595935274468526591021824047");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "0.43298018843109500232420037773924183842996270566187693920912130535865346742072348");
  EXPECT_EQ(f(getPi() / 2)->toString(),
            "5.4692230477529111586267970406424055872514205135096926055277982231147447746519098*10^-121");
  EXPECT_EQ(f(getPi())->toString(),
            "-1.0");
  EXPECT_EQ(f(2 * getPi())->toString(),
            "1.0");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "1.0");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "1.0");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "cos(1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "cos(-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "cos(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "cos(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(CosTests, exprTest) {
  EXPECT_EQ(cosExpr(Integer(10))->toString(), "cos(10)");
}

TEST(CosTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(CosTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Cos());
  EXPECT_EQ(Cos(), f);
  EXPECT_EQ(f, cast<IMathObject>(Cos()));
  EXPECT_EQ(cast<IMathObject>(Cos()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(CosTests, getTypeTest) {
  EXPECT_EQ(Cos::getTypeStatic(), MathObjectType::Cos);
  EXPECT_EQ(Cos().getType(), MathObjectType::Cos);
}
