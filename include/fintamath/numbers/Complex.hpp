#pragma once

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Complex : public INumberCRTP<Complex> {
public:
  Complex() = default;

  Complex(const Complex &rhs);

  Complex(Complex &&rhs) noexcept = default;

  Complex &operator=(const Complex &rhs);

  Complex &operator=(Complex &&rhs) noexcept = default;

  ~Complex() override = default;

  explicit Complex(const std::string &str);

  explicit Complex(const INumber &inReal, const INumber &inImag);

  explicit Complex(int64_t inReal, int64_t inImag);

  Complex(const Integer &rhs);

  Complex(const Rational &rhs);

  Complex(const Real &rhs);

  Complex(int64_t rhs);

  std::string toString() const override;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  bool isPrecise() const override;

  bool isComplex() const override;

  const INumber &real() const;

  const INumber &imag() const;

  static MathObjectType getTypeStatic() {
    return MathObjectType::Complex;
  }

protected:
  bool equals(const Complex &rhs) const override;

  std::strong_ordering compare(const Complex &rhs) const override;

  Complex &add(const Complex &rhs) override;

  Complex &substract(const Complex &rhs) override;

  Complex &multiply(const Complex &rhs) override;

  Complex &divide(const Complex &rhs) override;

  Complex &negate() override;

private:
  std::unique_ptr<INumber> re = std::make_unique<Integer>(0);
  std::unique_ptr<INumber> im = std::make_unique<Integer>(0);
};

}
