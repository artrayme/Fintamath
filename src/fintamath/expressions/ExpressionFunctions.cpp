#include "fintamath/expressions/ExpressionFunctions.hpp"

#include "fintamath/expressions/binary/CompExpression.hpp"
#include "fintamath/functions/arithmetic/Abs.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/hyperbolic/Acosh.hpp"
#include "fintamath/functions/hyperbolic/Acoth.hpp"
#include "fintamath/functions/hyperbolic/Asinh.hpp"
#include "fintamath/functions/hyperbolic/Atanh.hpp"
#include "fintamath/functions/hyperbolic/Cosh.hpp"
#include "fintamath/functions/hyperbolic/Coth.hpp"
#include "fintamath/functions/hyperbolic/Sinh.hpp"
#include "fintamath/functions/hyperbolic/Tanh.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"
#include "fintamath/functions/ntheory/Mod.hpp"
#include "fintamath/functions/other/Factorial.hpp"
#include "fintamath/functions/powers/Exp.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"
#include "fintamath/functions/trigonometry/Acos.hpp"
#include "fintamath/functions/trigonometry/Acot.hpp"
#include "fintamath/functions/trigonometry/Asin.hpp"
#include "fintamath/functions/trigonometry/Atan.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Cot.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/functions/trigonometry/Tan.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Pi.hpp"

namespace fintamath {

Expression sub(const Expression &lhs, const Expression &rhs) {
  return lhs - rhs;
}

Expression div(const Expression &lhs, const Expression &rhs) {
  return lhs / rhs;
}

Expression mod(const Expression &lhs, const Expression &rhs) {
  return Expression(modExpr(lhs, rhs));
}

Expression neg(const Expression &rhs) {
  return -rhs;
}

Expression eqv(const Expression &lhs, const Expression &rhs) {
  return Expression(eqvExpr(lhs, rhs));
}

Expression neqv(const Expression &lhs, const Expression &rhs) {
  return Expression(neqvExpr(lhs, rhs));
}

Expression less(const Expression &lhs, const Expression &rhs) {
  return Expression(lessExpr(lhs, rhs));
}

Expression more(const Expression &lhs, const Expression &rhs) {
  return Expression(moreExpr(lhs, rhs));
}

Expression lessEqv(const Expression &lhs, const Expression &rhs) {
  return Expression(lessEqvExpr(lhs, rhs));
}

Expression moreEqv(const Expression &lhs, const Expression &rhs) {
  return Expression(moreEqvExpr(lhs, rhs));
}

Expression floor(const Expression &rhs) {
  return Expression(floorExpr(rhs));
}

Expression ceil(const Expression &rhs) {
  return Expression(ceilExpr(rhs));
}

Expression abs(const Expression &rhs) {
  return Expression(absExpr(rhs));
}

Expression factorial(const Expression &rhs) {
  return Expression(factorialExpr(rhs));
}

Expression sqrt(const Expression &rhs) {
  return Expression(sqrtExpr(rhs));
}

Expression pow(const Expression &lhs, const Expression &rhs) {
  return Expression(powExpr(lhs, rhs));
}

Expression exp(const Expression &rhs) {
  return Expression(expExpr(rhs));
}

Expression log(const Expression &lhs, const Expression &rhs) {
  return Expression(logExpr(lhs, rhs));
}

Expression ln(const Expression &rhs) {
  return Expression(lnExpr(rhs));
}

Expression lb(const Expression &rhs) {
  return Expression(lbExpr(rhs));
}

Expression lg(const Expression &rhs) {
  return Expression(lgExpr(rhs));
}

Expression sin(const Expression &rhs) {
  return Expression(sinExpr(rhs));
}

Expression cos(const Expression &rhs) {
  return Expression(cosExpr(rhs));
}

Expression tan(const Expression &rhs) {
  return Expression(tanExpr(rhs));
}

Expression cot(const Expression &rhs) {
  return Expression(cotExpr(rhs));
}

Expression asin(const Expression &rhs) {
  return Expression(asinExpr(rhs));
}

Expression acos(const Expression &rhs) {
  return Expression(acosExpr(rhs));
}

Expression atan(const Expression &rhs) {
  return Expression(atanExpr(rhs));
}

Expression acot(const Expression &rhs) {
  return Expression(acotExpr(rhs));
}

Expression sinh(const Expression &rhs) {
  return Expression(sinhExpr(rhs));
}

Expression cosh(const Expression &rhs) {
  return Expression(coshExpr(rhs));
}

Expression tanh(const Expression &rhs) {
  return Expression(tanhExpr(rhs));
}

Expression coth(const Expression &rhs) {
  return Expression(cothExpr(rhs));
}

Expression asinh(const Expression &rhs) {
  return Expression(asinhExpr(rhs));
}

Expression acosh(const Expression &rhs) {
  return Expression(acoshExpr(rhs));
}

Expression atanh(const Expression &rhs) {
  return Expression(atanhExpr(rhs));
}

Expression acoth(const Expression &rhs) {
  return Expression(acothExpr(rhs));
}

Expression derivative(const Expression &lhs, const Expression &rhs) {
  return Expression(derivativeExpr(lhs, rhs));
}

Expression notL(const Expression &rhs) {
  return Expression(notExpr(rhs));
}

Expression andL(const Expression &lhs, const Expression &rhs) {
  return Expression(andExpr(lhs, rhs));
}

Expression orL(const Expression &lhs, const Expression &rhs) {
  return Expression(orExpr(lhs, rhs));
}

Expression e() {
  return E();
}

Expression pi() {
  return Pi();
}

Expression inf() {
  return Inf();
}

Expression negInf() {
  return NegInf();
}

Expression complexInf() {
  return ComplexInf();
}

}
