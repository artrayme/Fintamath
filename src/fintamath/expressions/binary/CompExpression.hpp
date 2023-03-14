#pragma once

#include "fintamath/expressions/binary/IBinaryExpression.hpp"

namespace fintamath {

class CompExpression : public IBinaryExpressionCRTP<CompExpression> {
public:
  CompExpression(const IOperator &oper, const shared_ptr<IMathObject> &lhsChild,
                 const shared_ptr<IMathObject> &rhsChild);

  shared_ptr<IMathObject> solve() const;

  // string solve(uint8_t precision) const;

protected:
  shared_ptr<IMathObject> postSimplify() const override;

  // vector<unique_ptr<IMathObject>> solvePowEquation(const Variable &x) const;

  // vector<unique_ptr<IMathObject>> solveQuadraticEquation(const unique_ptr<IMathObject> &v) const;

  // static bool sortFunc(const unique_ptr<IMathObject> &lhs, const unique_ptr<IMathObject> &rhs);

  // static vector<unique_ptr<IMathObject>> sortResult(vector<unique_ptr<IMathObject>> &result);

  // bool detectOneVariable(Variable &v) const;
};

}