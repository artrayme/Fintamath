#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/expressions/interfaces/IInvertable.hpp"

namespace fintamath {

class PowExpression : public IBinaryExpressionCRTP<PowExpression>, public IInvertable {
public:
  explicit PowExpression(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild);

  // ArgumentPtr polynomSimplify();

  // ArgumentPtr sumSimplify();

  // ArgumentPtr mulSimplify();

  // ArgumentPtr getValue();

  // ArgumentPtr getPow();

  ArgumentPtr invert() const override;

protected:
  ArgumentPtr postSimplify() const override;

private:
  // static ArgumentPtr sumPolynomSimplify(const SumExpression &sumExpr, Integer pow);

  // static Integer generateNextNumber(Integer n);

  // static Integer generateFirstNum(const Integer &countOfOne);

  // static vector<Integer> generateSplit(Integer bitNumber, const Integer &variableCount);
};
}