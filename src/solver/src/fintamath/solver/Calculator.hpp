#pragma once

#include "fintamath/solver/Solver.hpp"

namespace fintamath {
  class Calculator {
  public:
    std::string calculate(const std::string &strExpr);

    int64_t getPrecision() const;
    void setPrecision(int64_t precision);

  private:
    Solver solver;

    void toShortForm(std::string &strVal) const;
  };
}