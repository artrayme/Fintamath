#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Log : public IFunctionCRTP<Log, INumber, INumber> {
public:
  Log() = default;

  std::string toString() const override {
    return "log";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
