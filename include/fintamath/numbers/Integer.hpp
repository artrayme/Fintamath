#pragma once

#include <memory>

#include "fintamath/core/IIntegral.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class IntegerImpl;

class Integer : public INumberCRTP<Integer>, public IIntegralCRTP<Integer>, public IIncrementalCRTP<Integer> {
public:
  Integer();

  Integer(const Integer &rhs);

  Integer(Integer &&rhs) noexcept;

  Integer &operator=(const Integer &rhs);

  Integer &operator=(Integer &&rhs) noexcept;

  ~Integer() override;

  Integer(const IntegerImpl &inImpl);

  explicit Integer(std::string str);

  Integer(int64_t val);

  std::string toString() const override;

  int sign() const;

  operator long long() const;

  const std::unique_ptr<IntegerImpl> &getImpl() const;

protected:
  bool equals(const Integer &rhs) const override;

  bool less(const Integer &rhs) const override;

  bool more(const Integer &rhs) const override;

  Integer &add(const Integer &rhs) override;

  Integer &substract(const Integer &rhs) override;

  Integer &multiply(const Integer &rhs) override;

  Integer &divide(const Integer &rhs) override;

  Integer &mod(const Integer &rhs) override;

  Integer &bitAnd(const Integer &rhs) override;

  Integer &bitOr(const Integer &rhs) override;

  Integer &bitXor(const Integer &rhs) override;

  Integer &bitLeftShift(const Integer &rhs) override;

  Integer &bitRightShift(const Integer &rhs) override;

  Integer &bitNot() override;

  Integer &negate() override;

  Integer &increase() override;

  Integer &decrease() override;

private:
  std::unique_ptr<IntegerImpl> impl;
};

}
