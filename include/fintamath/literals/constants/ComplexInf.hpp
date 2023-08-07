#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class ComplexInf : public IConstantCRTP<INumber, ComplexInf> {
public:
  std::string toString() const override {
    return "ComplexInf";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::ComplexInf);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}