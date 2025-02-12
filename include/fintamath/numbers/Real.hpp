#pragma once

#include <boost/multiprecision/cpp_dec_float.hpp>

#include "fintamath/core/CoreConstants.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

class Real : public INumberCRTP<Real> {
public:
  using Backend = boost::multiprecision::cpp_dec_float_100;

public:
  Real();

  Real(const Real &rhs);

  Real(Real &&rhs) noexcept;

  Real &operator=(const Real &rhs);

  Real &operator=(Real &&rhs) noexcept;

  ~Real() override;

  Real(Backend inBackend);

  explicit Real(std::string str);

  Real(const Rational &val);

  Real(const Integer &val);

  Real(double val);

  std::string toString() const override;

  std::string toString(uint8_t precision) const;

  bool isPrecise() const override;

  uint8_t getPrecision() const;

  void setPrecision(uint8_t precision);

  int sign() const;

  const Backend &getBackend() const;

  static MathObjectType getTypeStatic() {
    return MathObjectType::Real;
  }

protected:
  bool equals(const Real &rhs) const override;

  bool equalsAbstract(const IMathObject &rhs) const override;

  std::strong_ordering compare(const Real &rhs) const override;

  std::strong_ordering compareAbstract(const IComparable &rhs) const override;

  Real &add(const Real &rhs) override;

  Real &substract(const Real &rhs) override;

  Real &multiply(const Real &rhs) override;

  std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const override;

  Real &divide(const Real &rhs) override;

  Real &negate() override;

private:
  bool isValid() const;

private:
  Backend backend;

  uint8_t precision = FINTAMATH_PRECISION;

  bool isNegative = false;
};

}
