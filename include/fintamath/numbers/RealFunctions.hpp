#pragma once

#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Integer floor(const Real &rhs);

Integer ceil(const Real &rhs);

Real abs(const Real &rhs);

Real sqrt(const Real &rhs);

Real pow(const Real &lhs, const Real &rhs);

Real exp(const Real &rhs);

Real log(const Real &lhs, const Real &rhs);

Real ln(const Real &rhs);

Real lb(const Real &rhs);

Real lg(const Real &rhs);

Real sin(const Real &rhs);

Real cos(const Real &rhs);

Real tan(const Real &rhs);

Real cot(const Real &rhs);

Real sec(const Real &rhs);

Real csc(const Real &rhs);

Real asin(const Real &rhs);

Real acos(const Real &rhs);

Real atan(const Real &rhs);

Real acot(const Real &rhs);

Real asec(const Real &rhs);

Real acsc(const Real &rhs);

Real sinh(const Real &rhs);

Real cosh(const Real &rhs);

Real tanh(const Real &rhs);

Real coth(const Real &rhs);

Real sech(const Real &rhs);

Real csch(const Real &rhs);

Real asinh(const Real &rhs);

Real acosh(const Real &rhs);

Real atanh(const Real &rhs);

Real acoth(const Real &rhs);

Real asech(const Real &rhs);

Real acsch(const Real &rhs);

Real tgamma(const Real &rhs);

const Real &getE();

const Real &getPi();

}
