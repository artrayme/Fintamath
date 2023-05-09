#pragma once

#include <map>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class IExpression;

std::string putInBrackets(const std::string &str);

std::string putInSpaces(const std::string &str);

std::string functionToString(const IFunction &func, const ArgumentsPtrVector &args);

std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values);

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs);

bool hasVariables(const std::shared_ptr<const IExpression> &expr);

bool hasVariable(const std::shared_ptr<const IExpression> &expr, const Variable &var);

extern std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const ArgumentsRefVector &args);

extern ArgumentPtr makeFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

extern std::shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, const ArgumentsPtrVector &args);

template <typename... Args, typename = std::enable_if_t<(std::is_base_of_v<IMathObject, Args> && ...)>>
std::unique_ptr<IMathObject> makeFunctionExpression(const IFunction &func, const Args &...args) {
  return makeFunctionExpression(func, ArgumentsRefVector{args...});
}

template <typename T, typename = std::enable_if_t<(std::is_convertible_v<T, ArgumentPtr>)>>
ArgumentPtr toArgumentPtr(T &arg) {
  if constexpr (std::is_copy_constructible_v<T>) {
    return arg;
  }
  else {
    return std::move(arg);
  }
}

template <typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, ArgumentPtr> && ...)>>
ArgumentPtr makeFunctionExpression(const IFunction &func, Args &&...args) {
  return makeFunctionExpression(func, ArgumentsPtrVector{toArgumentPtr(args)...});
}

template <typename... Args, typename = std::enable_if_t<(std::is_convertible_v<Args, ArgumentPtr> && ...)>>
std::shared_ptr<IExpression> makeRawFunctionExpression(const IFunction &func, Args &&...args) {
  return makeRawFunctionExpression(func, ArgumentsPtrVector{toArgumentPtr(args)...});
}

}
