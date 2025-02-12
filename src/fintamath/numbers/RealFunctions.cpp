#include "fintamath/numbers/RealFunctions.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

const Real &getMaxPreciseValue() {
  static const Real maxPreciseValue = pow(10, FINTAMATH_PRECISION) - 1;
  return maxPreciseValue;
}

Integer floor(const Real &rhs) {
  if (abs(rhs) > getMaxPreciseValue()) {
    throw UndefinedFunctionException("floor", {rhs.toString()});
  }

  Real::Backend res = boost::multiprecision::floor(rhs.getBackend());
  return res.convert_to<Integer::Backend>();
}

Integer ceil(const Real &rhs) {
  if (abs(rhs) > getMaxPreciseValue()) {
    throw UndefinedFunctionException("ceil", {rhs.toString()});
  }

  Real::Backend res = boost::multiprecision::ceil(rhs.getBackend());
  return res.convert_to<Integer::Backend>();
}

Real abs(const Real &rhs) {
  return rhs < 0 ? -rhs : rhs;
}

Real sqrt(const Real &rhs) {
  if (rhs < 0) {
    throw UndefinedFunctionException("sqrt", {rhs.toString()});
  }

  return {sqrt(rhs.getBackend())};
}

Real pow(const Real &lhs, const Real &rhs) {
  if (lhs == 0 && rhs == 0) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }

  try {
    return {pow(lhs.getBackend(), rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedBinaryOperatorException("^", lhs.toString(), rhs.toString());
  }
}

Real exp(const Real &rhs) {
  return {exp(rhs.getBackend())};
}

Real log(const Real &lhs, const Real &rhs) {
  try {
    return ln(rhs) / ln(lhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("log", {lhs.toString(), rhs.toString()});
  }
}

Real ln(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("ln", {rhs.toString()});
  }

  return {log(rhs.getBackend())};
}

Real lb(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lb", {rhs.toString()});
  }

  return {log2(rhs.getBackend())};
}

Real lg(const Real &rhs) {
  if (rhs <= 0) {
    throw UndefinedFunctionException("lg", {rhs.toString()});
  }

  return {log10(rhs.getBackend())};
}

Real sin(const Real &rhs) {
  static const Real zeroValue = 0;

  Real::Backend res = sin(rhs.getBackend());

  if (res == zeroValue && abs(rhs) > getMaxPreciseValue()) {
    throw UndefinedFunctionException("sin", {rhs.toString()});
  }

  return res;
}

Real cos(const Real &rhs) {
  static const Real zeroValue = 1;

  Real::Backend res = cos(rhs.getBackend());

  if (res == zeroValue && abs(rhs) > getMaxPreciseValue()) {
    throw UndefinedFunctionException("cos", {rhs.toString()});
  }

  return res;
}

Real tan(const Real &rhs) {
  static const Real zeroValue = 0;

  Real::Backend res = tan(rhs.getBackend());

  if (res == zeroValue && abs(rhs) > getMaxPreciseValue()) {
    throw UndefinedFunctionException("tan", {rhs.toString()});
  }

  return res;
}

Real cot(const Real &rhs) {
  try {
    return 1 / tan(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("cot", {rhs.toString()});
  }
}

Real sec(const Real &rhs) {
  try {
    return 1 / cos(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("sec", {rhs.toString()});
  }
}

Real csc(const Real &rhs) {
  try {
    return 1 / sin(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("csc", {rhs.toString()});
  }
}

Real asin(const Real &rhs) {
  try {
    return {asin(rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asin", {rhs.toString()});
  }
}

Real acos(const Real &rhs) {
  try {
    return {acos(rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acos", {rhs.toString()});
  }
}

Real atan(const Real &rhs) {
  return {atan(rhs.getBackend())};
}

Real acot(const Real &rhs) {
  try {
    return atan(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acot", {rhs.toString()});
  }
}

Real asec(const Real &rhs) {
  try {
    return acos(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asec", {rhs.toString()});
  }
}

Real acsc(const Real &rhs) {
  try {
    return asin(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acsc", {rhs.toString()});
  }
}

Real sinh(const Real &rhs) {
  try {
    return {sinh(rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("sinh", {rhs.toString()});
  }
}

Real cosh(const Real &rhs) {
  try {
    return {cosh(rhs.getBackend())};
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("cosh", {rhs.toString()});
  }
}

Real tanh(const Real &rhs) {
  return {tanh(rhs.getBackend())};
}

Real coth(const Real &rhs) {
  try {
    return 1 / tanh(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("coth", {rhs.toString()});
  }
}

Real sech(const Real &rhs) {
  return 1 / cosh(rhs);
}

Real csch(const Real &rhs) {
  try {
    return 1 / sinh(rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("csch", {rhs.toString()});
  }
}

Real asinh(const Real &rhs) {
  return boost::math::asinh(rhs.getBackend());
}

Real acosh(const Real &rhs) {
  try {
    return boost::math::acosh(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("acosh", {rhs.toString()});
  }
}

Real atanh(const Real &rhs) {
  try {
    return boost::math::atanh(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("atanh", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
    throw UndefinedFunctionException("atanh", {rhs.toString()});
  }
}

Real acoth(const Real &rhs) {
  try {
    return atanh(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acoth", {rhs.toString()});
  }
}

Real asech(const Real &rhs) {
  try {
    return acosh(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("asech", {rhs.toString()});
  }
}

Real acsch(const Real &rhs) {
  try {
    return asinh(1 / rhs);
  }
  catch (const UndefinedException &) {
    throw UndefinedFunctionException("acsch", {rhs.toString()});
  }
}

Real tgamma(const Real &rhs) {
  try {
    return boost::math::tgamma(rhs.getBackend());
  }
  catch (const std::domain_error &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
  catch (const std::overflow_error &) {
    throw UndefinedFunctionException("tgamma", {rhs.toString()});
  }
}

const Real &getE() {
  using boost::multiprecision::default_ops::get_constant_e;
  static const Real e = Real::Backend(get_constant_e<Real::Backend::backend_type>());
  return e;
}

const Real &getPi() {
  using boost::multiprecision::default_ops::get_constant_pi;
  static const Real pi = Real::Backend(get_constant_pi<Real::Backend::backend_type>());
  return pi;
}

}
