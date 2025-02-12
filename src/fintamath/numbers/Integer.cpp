#include "fintamath/numbers/Integer.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"

namespace fintamath {

Integer::Integer() = default;

Integer::Integer(const Integer &rhs) = default;

Integer::Integer(Integer &&rhs) noexcept = default;

Integer &Integer::operator=(const Integer &rhs) = default;

Integer &Integer::operator=(Integer &&rhs) noexcept = default;

Integer::~Integer() = default;

Integer::Integer(Backend inBackend) : backend(std::move(inBackend)) {
}

Integer::Integer(std::string str) {
  if (str.empty()) {
    throw InvalidInputException(str);
  }

  // Remove leading zeros
  {
    size_t i = 0;
    if (str.front() == '-') {
      i++;
    }

    str.erase(i, str.find_first_not_of('0'));
    if (str.empty()) {
      str = "0";
    }
  }

  try {
    backend.assign(str);
  }
  catch (const std::runtime_error &) {
    throw InvalidInputException(str);
  }
}

Integer::Integer(int64_t val) : backend(val) {
}

std::string Integer::toString() const {
  return backend.str();
}

int Integer::sign() const {
  return backend.sign();
}

const Integer::Backend &Integer::getBackend() const {
  return backend;
}

bool Integer::equals(const Integer &rhs) const {
  return backend == rhs.backend;
}

std::strong_ordering Integer::compare(const Integer &rhs) const {
  return backend.compare(rhs.backend) <=> 0;
}

Integer &Integer::add(const Integer &rhs) {
  backend += rhs.backend;
  return *this;
}

Integer &Integer::substract(const Integer &rhs) {
  backend -= rhs.backend;
  return *this;
}

Integer &Integer::multiply(const Integer &rhs) {
  backend *= rhs.backend;
  return *this;
}

Integer &Integer::divide(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  backend /= rhs.backend;
  return *this;
}

Integer &Integer::mod(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedBinaryOperatorException("mod", toString(), rhs.toString());
  }

  backend %= rhs.backend;
  return *this;
}

Integer &Integer::bitAnd(const Integer &rhs) {
  backend &= rhs.backend;
  return *this;
}

Integer &Integer::bitOr(const Integer &rhs) {
  backend |= rhs.backend;
  return *this;
}

Integer &Integer::bitXor(const Integer &rhs) {
  backend ^= rhs.backend;
  return *this;
}

Integer &Integer::bitLeftShift(const Integer &rhs) {
  try {
    backend <<= int64_t(rhs.backend);
    return *this;
  }
  catch (...) {
    throw UndefinedBinaryOperatorException("<<", toString(), rhs.toString());
  }
}

Integer &Integer::bitRightShift(const Integer &rhs) {
  try {
    backend >>= int64_t(rhs.backend);
    return *this;
  }
  catch (...) {
    throw UndefinedBinaryOperatorException(">>", toString(), rhs.toString());
  }
}

Integer &Integer::bitNot() {
  backend = ~backend;
  return *this;
}

Integer &Integer::negate() {
  backend = -backend;
  return *this;
}

Integer &Integer::increase() {
  ++backend;
  return *this;
}

Integer &Integer::decrease() {
  --backend;
  return *this;
}

} // namespace fintamath
