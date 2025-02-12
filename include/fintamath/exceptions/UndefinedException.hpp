#pragma once

#include <string>
#include <vector>

#include "fintamath/exceptions/Exception.hpp"

namespace fintamath {

class UndefinedException : public Exception {
public:
  UndefinedException() = default;

  explicit UndefinedException(const std::string &input) {
    content += ": " + input;
  }

  const char *what() const noexcept override {
    return content.c_str();
  }

protected:
  std::string content = "Undefined";
};

class UndefinedFunctionException : public UndefinedException {
public:
  explicit UndefinedFunctionException(const std::string &func, const std::vector<std::string> &argsVect) {
    content += ": " + func + "(";

    if (!argsVect.empty()) {
      for (const auto &arg : argsVect) {
        content += arg + ',';
      }

      content.pop_back();
    }

    content += ")";
  }

  const char *what() const noexcept override {
    return content.c_str();
  }
};

class UndefinedBinaryOperatorException : public UndefinedException {
public:
  explicit UndefinedBinaryOperatorException(const std::string &oper, const std::string &lhs, const std::string &rhs) {
    content += ": (" + lhs + ")" + oper + "(" + rhs + ")";
  }
};

class UndefinedUnaryOperatorException : public UndefinedException {
public:
  enum class Type {
    Prefix,
    Postfix,
  };

public:
  explicit UndefinedUnaryOperatorException(const std::string &oper, const std::string &rhs, Type type) {
    switch (type) {
      case Type::Prefix:
        content += ": " + oper + "(" + rhs + ")";
        break;
      case Type::Postfix:
        content += ": (" + rhs + ")" + oper;
        break;
    }
  }
};

}
