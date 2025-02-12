#include "gtest/gtest.h"

#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestDerivative : public IComparableCRTP<TestDerivative> {
public:
  std::string toString() const override {
    return "testderivative";
  }

  static MathObjectType getTypeStatic() {
    return size_t(MathObjectType::IComparable) + 11;
  }

protected:
  std::strong_ordering compare(const TestDerivative & /* rhs */) const override {
    return 0 <=> 1;
  }

  TestDerivative &add(const TestDerivative & /* rhs */) override {
    return *this;
  }

  TestDerivative &substract(const TestDerivative & /* rhs */) override {
    return *this;
  }

  TestDerivative &multiply(const TestDerivative & /* rhs */) override {
    return *this;
  }

  TestDerivative &divide(const TestDerivative & /* rhs */) override {
    return *this;
  }

  TestDerivative &negate() override {
    return *this;
  }
};

}

const Derivative f;

TEST(DerivativeTests, toStringTest) {
  EXPECT_EQ(f.toString(), "derivative");
}

TEST(DerivativeTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(DerivativeTests, callTest) {
  EXPECT_EQ(f(Integer(5), Variable("a"))->toString(), "0");
  EXPECT_EQ(f(Variable("a"), Variable("a"))->toString(), "1");
  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "0");
  EXPECT_EQ(f(Expression("a+a"), Variable("a"))->toString(), "2");

  EXPECT_EQ(f(TestDerivative(), Variable("a"))->toString(), "derivative(testderivative, a)");

  EXPECT_THROW(f(Integer(5), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Variable("a"), Expression("a+a")), InvalidInputException);

  EXPECT_THROW(f(), InvalidInputException);
  EXPECT_THROW(f(Integer(1)), InvalidInputException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputException);
}

TEST(DerivativeTests, exprTest) {
  EXPECT_EQ(derivativeExpr(Variable("a"), Variable("a"))->toString(), "derivative(a, a)");
}

TEST(DerivativeTests, doArgsMatchTest) {
  Integer a;
  Variable b("b");

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, b}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(DerivativeTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Derivative());
  EXPECT_EQ(Derivative(), f);
  EXPECT_EQ(f, cast<IMathObject>(Derivative()));
  EXPECT_EQ(cast<IMathObject>(Derivative()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(DerivativeTests, getTypeTest) {
  EXPECT_EQ(Derivative::getTypeStatic(), MathObjectType::Derivative);
  EXPECT_EQ(Derivative().getType(), MathObjectType::Derivative);
}
