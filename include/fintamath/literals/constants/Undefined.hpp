#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Undefined : public IConstantCRTP<INumber, Undefined> {
public:
  std::string toString() const override {
    return "Undefined";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Undefined;
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
