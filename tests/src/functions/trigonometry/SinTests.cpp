#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

using namespace fintamath;

const Sin f;

TEST(SinTests, toStringTest) {
  EXPECT_EQ(f.toString(), "sin");
}

TEST(SinTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(SinTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(10))->toString(),
            "-0.54402111088936981340474766185137728168364301291622389157418401261675720964049343");
  EXPECT_EQ(f(Integer(5))->toString(),
            "-0.9589242746631384688931544061559939733524615439646017781316724542351025580865596");

  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.099833416646828152306814198410622026989915388017982259992766861561651744283292428");

  EXPECT_EQ(f(Real("1.123"))->toString(),
            "0.90140343710581305144201223192651962989966379299765630033531049179851968515554771");
  EXPECT_EQ(f(getPi())->toString(),
            "9.3844609550582231725359408128481117450284102701938521105559644622948954930381964*10^-122");
  EXPECT_EQ(f(2 * getPi())->toString(),
            "-6.461329418768921910116446345071881625696223490056820540387704221111928924589791*10^-113");
  EXPECT_EQ(f(getPi() / 2)->toString(),
            "1.0");
  EXPECT_EQ(f(pow(Real(11), -100))->toString(),
            "7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(-pow(Real(11), -100))->toString(),
            "-7.2565715901482001294471610439840355719482218080717617311921652840489155583363378*10^-105");
  EXPECT_EQ(f(pow(Real(11), 100))->toString(),
            "sin(1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");
  EXPECT_EQ(f(-pow(Real(11), 100))->toString(),
            "sin(-1.3780612339822270184118337172089636776264331200038466433146477552154985209552308*10^104)");

  EXPECT_EQ(f(Complex(1, 1))->toString(), "sin(1 + I)");

  EXPECT_EQ(f(Variable("a"))->toString(), "sin(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}

TEST(SinTests, exprTest) {
  EXPECT_EQ(sinExpr(Integer(10))->toString(), "sin(10)");
}

TEST(SinTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_TRUE(f.doArgsMatch({a}));
  EXPECT_FALSE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(SinTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Sin());
  EXPECT_EQ(Sin(), f);
  EXPECT_EQ(f, cast<IMathObject>(Sin()));
  EXPECT_EQ(cast<IMathObject>(Sin()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(SinTests, getTypeTest) {
  EXPECT_EQ(Sin::getTypeStatic(), MathObjectType::Sin);
  EXPECT_EQ(Sin().getType(), MathObjectType::Sin);
}
