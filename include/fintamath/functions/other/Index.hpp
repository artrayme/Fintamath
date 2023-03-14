#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Index : public IOperatorCRTP<IComparable, Index, IComparable, IComparable> {
public:
  Index() : IOperatorCRTP(IOperator::Priority::Exponentiation, false, false) {
  }

  string toString() const override {
    return "_";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
