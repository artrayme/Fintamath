#include "calculator/Solver.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "single_entities/operators/Function.hpp"
#include "single_entities/operators/Operator.hpp"
#include "single_entities/terms/literals/Constant.hpp"
#include "single_entities/terms/literals/Variable.hpp"

using namespace std;

void rootReset(const shared_ptr<Expression::Elem> &root, const Rational &inFrac);

Rational Solver::solve(Expression &Expression) {
  if (Expression.root->right->right == nullptr && Expression.root->right->left == nullptr) {
    return Rational(toFrac(Expression.root->right).toString());
  }
  solveRec(Expression.root->right);
  return *dynamic_pointer_cast<Rational>(Expression.root->right->info);
}

void Solver::solveEquals(const vector<string> &vectIOfTokens, const Rational &inFrac) {
  if (vectIOfTokens.size() < 2) {
    throw invalid_argument("Parser invalid input");
  }
  if (!(isType::isVariable(*(vectIOfTokens.end() - 1)))) {
    throw invalid_argument("Parser invalid input");
  }

  for (size_t i = 1; i < vectIOfTokens.size(); ++i) {
    if (vectIOfTokens[i] == "=" && !isType::isVariable(vectIOfTokens[i + 1])) {
      throw invalid_argument("Parser invalid input");
    }

    if (isType::isVariable(vectIOfTokens[i])) {
      if (!(vectIOfTokens[i - 1] == "=")) {
        throw invalid_argument("Parser invalid input");
      }
      if (isType::isConstant(vectIOfTokens[i]) || isType::isFunction(vectIOfTokens[i])) {
        throw invalid_argument("Solver invalid input");
      }

      size_t j = 0;
      for (; j < this->params.size(); ++j) {
        if (this->params[j].name == vectIOfTokens[i]) {
          this->params[j].value = inFrac;
          break;
        }
      }

      if (j == this->params.size()) {
        Param par;
        par.name = vectIOfTokens[i];
        par.value = inFrac;
        this->params.push_back(par);
      }
    }
  }
}

int64_t Solver::getPrecision() const {
  return precision;
}

void Solver::setPrecision(int64_t precision) {
  this->precision = precision;
}

Rational Solver::toFrac(const shared_ptr<Expression::Elem> &root) const {
  if (root->info == nullptr) {
    throw invalid_argument("Parser invalid input");
  }

  if (root->info->getTypeName() == "Constant") {
    return Constant(root->info->toString()).toRational(getNewPrecision());
  }

  if (root->info->getTypeName() == "Variable") {
    string str = root->info->toString();
    auto iter = find_if(this->params.begin(), this->params.end(), [str](const Param &p) { return p.name == str; });
    if (iter == this->params.end()) {
      throw invalid_argument("Solver invalid input");
    }
    return iter->value;
  }

  try {
    return *dynamic_pointer_cast<Rational>(root->info);
  } catch (const invalid_argument &) {
    throw invalid_argument("Solver invalid input");
  }
}

void Solver::solveRec(shared_ptr<Expression::Elem> &root) {
  if (root->info == nullptr) {
    throw invalid_argument("Parser invalid input");
  }
  if (root->right != nullptr) {
    if (root->right->info == nullptr) {
      throw invalid_argument("Parser invalid input");
    }
    if (root->right->info->getTypeName() == "Operator" || root->right->info->getTypeName() == "Function") {
      solveRec(root->right);
    }
  }
  if (root->left != nullptr) {
    if (root->left->info == nullptr) {
      throw invalid_argument("Parser invalid input");
    }
    if (root->left->info->getTypeName() == "Operator" || root->left->info->getTypeName() == "Function") {
      solveRec(root->left);
    }
  }
  if (root->info->getTypeName() == "Operator") {
    Operator oper(root->info->toString());
    Rational frac(
        oper.solve(toFrac(root->right), toFrac(root->left), getNewPrecision()).toString(getNewRoundPrecision()));
    rootReset(root, frac);
    return;
  }
  if (root->info->getTypeName() == "Function") {
    Function func(root->info->toString());
    Rational frac;
    if (isType::isBinaryFunction(func.toString())) {
      frac = Rational(
          func.solve(toFrac(root->right), toFrac(root->left), getNewPrecision()).toString(getNewRoundPrecision()));
    } else {
      frac = Rational(func.solve(toFrac(root->right), getNewPrecision()).toString(getNewRoundPrecision()));
    }
    rootReset(root, frac);
    return;
  }
}

int64_t Solver::getNewPrecision() const {
  const int64_t PRECISION_INCREASER = 9;
  return precision + PRECISION_INCREASER;
}

int64_t Solver::getNewRoundPrecision() const {
  return getNewPrecision() - 1;
}

inline void rootReset(const shared_ptr<Expression::Elem> &root, const Rational &inFrac) {
  root->info = make_shared<Rational>(inFrac);
  root->right.reset();
  root->left.reset();
}
