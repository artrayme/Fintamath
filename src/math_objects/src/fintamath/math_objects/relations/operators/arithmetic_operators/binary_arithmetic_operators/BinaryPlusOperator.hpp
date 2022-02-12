#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperator.hpp"

namespace fintamath {
  class BinaryPlusOperator : public BinaryArithmeticOperator {
  public:
    Set operator()(const Set &set, int64_t precision = 0) const override;

    NodePtr operator()(const Integer &lhs, const Integer &rhs) const;
    NodePtr operator()(const Rational &lhs, const Rational &rhs) const;
    NodePtr operator()(const Integer &lhs, const Rational &rhs) const;
    NodePtr operator()(const Rational &lhs, const Integer &rhs) const;

    std::string toString() const override;
  };
}