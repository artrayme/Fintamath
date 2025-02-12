#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Sinh f;

TEST(SinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sinh");
}

TEST(SinhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(5))->toString(),
            "74.203210577788758977009471996064565599619409004425816980661269789669690649221486");
  EXPECT_EQ(f(Integer(-5))->toString(),
            "-74.203210577788758977009471996064565599619409004425816980661269789669690649221486");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.10016675001984402582372938352190502351492091687855888336830298619259400070170297");

  EXPECT_EQ(f(Real("0.5"))->toString(),
            "0.52109530549374736162242562641149155910592898261148052794609357645280225089023359");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "sinh(1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "sinh(-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sinh(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sinh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SinhTests, exprTest) {
  EXPECT_EQ(sinhExpr(Integer(10))->toString(), "sinh(10)");
}

TEST(SinhTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SinhTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sinh());
  EXPECT_EQ(Sinh(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sinh()));
  EXPECT_EQ(cast<IMathObject>(Sinh()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SinhTests, getTypeTest) {
  EXPECT_EQ(Sinh::getTypeStatic(), MathObjectType::Sinh);
  EXPECT_EQ(Sinh().getType(), MathObjectType::Sinh);
}
