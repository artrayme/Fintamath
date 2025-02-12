#pragma once

#include <stdexcept>

namespace fintamath {

class Exception : public std::exception {
public:
  const char *what() const noexcept override {
    return "Something went wrong...";
  }
};

}
