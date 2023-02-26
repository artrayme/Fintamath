#include "gtest/gtest.h"

#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Acosh f;

TEST(AcoshTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acosh");
}

TEST(AcoshTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcoshTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2))->toString(),
            "1.316957896924816708625046347307968444026981971467516479768472256920460185416444");
  EXPECT_EQ(f(Rational(11, 10))->toString(),
            "0.44356825438511518913291106635249808664900116609997546389342095580766881611303472");
  EXPECT_EQ(f(Rational(23, 13))->toString(),
            "1.1720930632462197632831227513306924192738346732428024686924646851189700836483782");

  EXPECT_EQ(f(Variable("a"))->toString(), "acosh(a)");

  EXPECT_THROW(f(Integer(0)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}