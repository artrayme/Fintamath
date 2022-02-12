#pragma once

#include <string>

#include "fintamath/math_objects/relations/Relation.hpp"

namespace fintamath {
  class RelationParser final {
  public:
    RelationParser() = delete;

    static RelationPtr parse(const std::string_view &str);
  };
}