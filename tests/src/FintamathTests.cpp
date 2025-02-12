#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionFunctions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(FintamathTests, fintamathTests) {
  Expression expr;
  Variable x("x");
  Variable y("y");

  //-------------------------------------------------------------------------------------//

  expr = add(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "a + b + E + Pi");

  expr = mul(e(), pi(), Variable("a"), Variable("b"));
  EXPECT_EQ(expr.toString(), "E Pi a b");

  expr = pow(Variable("a"), Variable("b")) * Variable("c");
  EXPECT_EQ(expr.toString(), "a^b c");

  expr = x * x * x * y + 10 * x;
  EXPECT_EQ(expr.toString(), "x^3 y + 10 x");

  expr = x + 10 * x / 10 + (sqrt(x) * 2);
  EXPECT_EQ(expr.toString(), "2 x + 2 sqrt(x)");

  expr = eqv(x * x + y * y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^3 = 0");

  expr = eqv(x * x + y * y, x * y);
  EXPECT_EQ(expr.toString(), "x^2 - x y + y^2 = 0");

  expr = eqv(x / x - y / y, x / y);
  EXPECT_EQ(expr.toString(), "x = 0");

  expr = Expression("(4x^4 + 1 + 3x^3 + 2x) / (x^2 + x + 2)");
  EXPECT_EQ(expr.toString(), "4 x^2 - x - 7 + (11 x + 15)/(x^2 + x + 2)");

  expr = log(2, 256) + ln(pow(e(), 2));
  EXPECT_EQ(expr.toString(), "10");

  expr = sqrt(Expression(8));
  EXPECT_EQ(expr.toString(), "2 sqrt(2)");

  expr = pow(Expression("244706656946119777797996531655819747089832578"), Rational(1, 4));
  EXPECT_EQ(expr.toString(), "sqrt(11) root(2022369065670411386760301914510907000742418, 4)");

  expr = sin(asin(Variable(x))) + cos(acos(Integer(1)));
  EXPECT_EQ(expr.toString(), "x + 1");

  expr = pow(sin(x), 2) + pow(cos(x), 2) + tan(x) * cot(x);
  EXPECT_EQ(expr.toString(), "2");

  expr = sin(Expression("-3Pi/2")) + cos(Expression("Pi/4"));
  EXPECT_EQ(expr.toString(), "sqrt(2)/2 + 1");

  expr = sin(Expression("123")).approximate();
  EXPECT_EQ(expr.toString(), "-0.45990349068959125129243571529323181080858060738104258092774286802995864335938568");

  expr = cos(Expression("-256")).approximate();
  EXPECT_EQ(expr.toString(), "-0.03979075993115770952448155799687436467725547418710853642067732094296726801190103");

  expr = Expression("~a & b | ~c -> a <-> b !<-> c");
  EXPECT_EQ(expr.toString(), "(a & b & ~c) | (~a & ~b & ~c) | (~a & c) | (~b & c)");

  //-------------------------------------------------------------------------------------//

  expr = solve(eqv(pow(x, 2) - 10, 39));
  EXPECT_EQ(expr.toString(), "x = -7 | x = 7");

  expr = solve(Expression("-4x^2 + 28x - 49 = 0"));
  EXPECT_EQ(expr.toString(), "x = 7/2");

  expr = solve(Expression("x^2 + 4x + 5 = 0"));
  EXPECT_EQ(expr.toString(), "x = -2 - I | x = -2 + I");

  expr = solve(Expression("3x^2 + 11x + 15 = 0"));
  EXPECT_EQ(expr.toString(), "x = -(I sqrt(59))/6 - 11/6 | x = (I sqrt(59))/6 - 11/6");

  expr = solve(Expression("-3x^2 + 28x - 49 = 0")).approximate(2);
  EXPECT_EQ(expr.toString(), "x = 2.3 | x = 7");
}
