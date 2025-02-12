#pragma once

#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

namespace fintamath {

class HyperbExpression : public IUnaryExpressionCRTP<HyperbExpression, true> {
public:
  explicit HyperbExpression(const IFunction &inFunc, ArgumentPtr inChild);

  static MathObjectType getTypeStatic() {
    return MathObjectType::HyperbExpression;
  }

protected:
  SimplifyFunctionVector getFunctionsForPreSimplify() const override;

  SimplifyFunctionVector getFunctionsForPostSimplify() const override;

private:
  static ArgumentPtr oppositeFunctionsSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr expandSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr negSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr tanhSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr cothSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr sechSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static ArgumentPtr cschSimplify(const IFunction &func, const ArgumentPtr &rhs);

  static std::shared_ptr<IFunction> getOppositeFunction(const IFunction &function);
};

}