#pragma once

#include "fintamath/expressions/IExpression.hpp"

namespace fintamath {

class IPolynomExpression : virtual public IExpression {
public:
  shared_ptr<IFunction> getFunction() const final;

  ArgumentsPtrVector getChildren() const final;

  // void setPrecision(uint8_t precision) final;

  ArgumentsPtrVector getVariables() const final;

  ArgumentsPtrVector getPolynom() const;

  virtual void addElement(const shared_ptr<IMathObject> &element) = 0;

protected:
  virtual shared_ptr<IMathObject> preSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  virtual shared_ptr<IMathObject> postSimplify(size_t lhsChildNum, size_t rhsChildNum) const;

  shared_ptr<IMathObject> simplify() final;

protected:
  // static void sortVector(ArgumentsPtrVector &vector, map<IOperator::Priority, ArgumentsPtrVector> &priorityMap,
  //                        ArgumentsPtrVector &functionVector, ArgumentsPtrVector &variableVector);

  // static void pushPolynomToPolynom(const ArgumentsPtrVector &from, ArgumentsPtrVector &to);

protected:
  shared_ptr<IFunction> func;

  ArgumentsPtrVector children;

private:
  void preSimplifyRec();

  void postSimplifyRec();
};

template <typename Derived>
class IPolynomExpressionCRTP : virtual public IExpressionCRTP<Derived>, virtual public IPolynomExpression {
public:
  explicit IPolynomExpressionCRTP(const IFunction &func, const ArgumentsPtrVector &children) {
    this->func = cast<IFunction>(func.clone());

    for (const auto &child : children) {
      addElement(child);
    }
  }

  void addElement(const shared_ptr<IMathObject> &element) final {
    shared_ptr<IMathObject> elem = element;
    compressChild(elem);

    ArgumentsPtrVector elemPolynom;

    if (auto expr = cast<Derived>(elem)) {
      elemPolynom = expr->children;
    }

    if (!elemPolynom.empty()) {
      for (auto &child : elemPolynom) {
        children.emplace_back(child);
      }
    }
    else {
      children.emplace_back(elem);
    }
  }
};

}
