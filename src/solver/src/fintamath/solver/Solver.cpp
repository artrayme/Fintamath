#include "fintamath/solver/Solver.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/terms/constants/MathConstant.hpp"
#include "fintamath/math_objects/relations/functions/ElementaryFunction.hpp"
#include "fintamath/math_objects/relations/operators/ArithmeticOperator.hpp"

using namespace fintamath;

static void elemReset(const std::shared_ptr<ArithmeticExpression::Elem> &elem, const Rational &val);

Rational Solver::solve(ArithmeticExpression &expr) {
  if (expr.getRootModifiable()->right->right == nullptr && expr.getRootModifiable()->right->left == nullptr) {
    return Rational(toRational(expr.getRootModifiable()->right).toString(precision));
  }
  solveRec(expr.getRootModifiable()->right);
  return *std::dynamic_pointer_cast<Rational>(expr.getRootModifiable()->right->info);
}

int64_t Solver::getPrecision() const {
  return precision;
}

void Solver::setPrecision(int64_t precision_) {
  precision = precision_ <= 0 ? 1 : precision_;
}

Rational Solver::toRational(const std::shared_ptr<ArithmeticExpression::Elem> &elem) const {
  if (elem->info == nullptr) {
    throw std::invalid_argument("Solver invalid input");
  }

  if (elem->info->getTypeName() == "Constant") {
    return MathConstant(elem->info->toString()).toRational(getNewPrecision());
  }

  try {
    return *std::dynamic_pointer_cast<Rational>(elem->info);
  } catch (const std::invalid_argument &) {
    throw std::invalid_argument("Solver invalid input");
  }
}

void Solver::solveRec(const std::shared_ptr<ArithmeticExpression::Elem> &elem) {
  if (elem->info == nullptr) {
    throw std::invalid_argument("Solver invalid input");
  }

  if (elem->right != nullptr) {
    if (elem->right->info == nullptr) {
      throw std::invalid_argument("Solver invalid input");
    }
    if (elem->right->info->getTypeName() == "Operator" || elem->right->info->getTypeName() == "Function") {
      solveRec(elem->right);
    }
  }

  if (elem->left != nullptr) {
    if (elem->left->info == nullptr) {
      throw std::invalid_argument("Solver invalid input");
    }
    if (elem->left->info->getTypeName() == "Operator" || elem->left->info->getTypeName() == "Function") {
      solveRec(elem->left);
    }
  }

  if (elem->info->getTypeName() == "Operator") {
    ArithmeticOperator oper(elem->info->toString());
    Rational val(oper.solve(toRational(elem->right), toRational(elem->left), getNewPrecision())
                     .toString(getNewRoundPrecision()));
    elemReset(elem, val);
    return;
  }

  if (elem->info->getTypeName() == "Function") {
    ElementaryFunction func(elem->info->toString());
    Rational val;
    if (types::isBinaryFunction(func.toString())) {
      val = Rational(func.solve(toRational(elem->right), toRational(elem->left), getNewPrecision())
                         .toString(getNewRoundPrecision()));
    } else {
      val = Rational(func.solve(toRational(elem->right), getNewPrecision()).toString(getNewRoundPrecision()));
    }
    elemReset(elem, val);
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

static void elemReset(const std::shared_ptr<ArithmeticExpression::Elem> &elem, const Rational &val) {
  elem->info = std::make_shared<Rational>(val);
  elem->right.reset();
  elem->left.reset();
}