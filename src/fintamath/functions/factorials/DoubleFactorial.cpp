#include "fintamath/functions/factorials/DoubleFactorial.hpp"

#include "fintamath/exceptions/UndefinedUnaryOpearatorException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

MathObjectPtr DoubleFactorial::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = argsVect.at(0).get();

  if (!rhs.is<Integer>()) {
    throw UndefinedUnaryOpearatorException("!!", rhs.toString(), UndefinedUnaryOpearatorException::Type::Postfix);
  }

  return doubleFactorial(rhs.to<Integer>()).simplify();
}

}
