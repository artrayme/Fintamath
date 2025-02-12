#include <gtest/gtest.h>

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

#include "fintamath/functions/other/Factorial.hpp"

using namespace fintamath;

const Factorial f;

namespace {

class TestUnaryExpression : public IUnaryExpressionCRTP<TestUnaryExpression> {
public:
  explicit TestUnaryExpression(ArgumentPtr inRhsChild)
      : IUnaryExpressionCRTP(f, std::move(inRhsChild)) {
  }

  static MathObjectType getTypeStatic() {
    return MathObjectBoundTypes::get().at(IUnaryExpression::getTypeStatic()) - 1;
  }
};

}

TEST(IUnaryExpressionTests, toStringTest) {
  TestUnaryExpression expr(std::make_shared<Integer>(1));
  EXPECT_EQ(expr.toString(), "1!");
}

TEST(IUnaryExpressionTests, getFunctionTest) {
  TestUnaryExpression expr(std::make_shared<Integer>(1));
  EXPECT_EQ(*expr.getFunction(), f);
}

TEST(IUnaryExpressionTests, getChildren) {
  TestUnaryExpression expr(std::make_shared<Integer>(1));
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().front(), Integer(1));
}

TEST(IUnaryExpressionTests, setChildren) {
  TestUnaryExpression expr(std::make_shared<Integer>(1));

  expr.setChildren({std::make_shared<Integer>(0)});
  EXPECT_EQ(expr.getChildren().size(), 1);
  EXPECT_EQ(*expr.getChildren().front(), Integer(0));

  EXPECT_THROW(expr.setChildren({}), InvalidInputFunctionException);
  EXPECT_THROW(expr.setChildren({std::make_shared<Integer>(1), std::make_shared<Integer>(1)}),
               InvalidInputFunctionException);
}

TEST(IUnaryExpressionTests, toMinimalObjectTest) {
  TestUnaryExpression expr1(Integer(4).clone());
  EXPECT_EQ(expr1.toMinimalObject()->toString(), "24");

  TestUnaryExpression expr2(Variable("a").clone());
  EXPECT_EQ(expr2.toMinimalObject()->toString(), "a!");

  TestUnaryExpression expr3(TestUnaryExpression(Variable("a").clone()).clone());
  EXPECT_EQ(expr3.toMinimalObject()->toString(), "(a!)!");
}

TEST(IUnaryExpressionTests, getTypeTest) {
  EXPECT_EQ(IUnaryExpression::getTypeStatic(), MathObjectType::IUnaryExpression);
}
