#include <gtest/gtest.h>

#include "fintamath/core/IMathObject.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(MathObjectTests, cloneTest) {
  std::unique_ptr<IMathObject> m1 = std::make_unique<Integer>();
  std::unique_ptr<IMathObject> m2 = std::make_unique<Integer>(1);
  std::unique_ptr<IMathObject> m3 = m1->clone();

  EXPECT_EQ(*m3, *m1);

  EXPECT_NE(*m3, *m2);

  EXPECT_NE(m3, m1);
}

TEST(MathObjectTests, equalsTest) {
  std::unique_ptr<IMathObject> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IMathObject> m2 = std::make_unique<Rational>(1);
  std::unique_ptr<IMathObject> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_TRUE(*m1 == *m1);
  EXPECT_TRUE(*m2 == *m2);
  EXPECT_TRUE(*m1 == *m2);
  EXPECT_TRUE(*m2 == *m1);

  EXPECT_FALSE(*m1 == *m3);
  EXPECT_FALSE(*m2 == *m3);
  EXPECT_FALSE(*m3 == *m1);
  EXPECT_FALSE(*m3 == *m2);

  EXPECT_FALSE(*m1 == Variable("a"));
  EXPECT_FALSE(Variable("a") == *m1);

  EXPECT_TRUE(Integer() == 0);
  EXPECT_TRUE(0 == Integer());

  EXPECT_FALSE(Integer() == 1);
  EXPECT_FALSE(1 == Integer());
}

TEST(MathObjectTests, nequalsTest) {
  std::unique_ptr<IMathObject> m1 = std::make_unique<Integer>(1);
  std::unique_ptr<IMathObject> m2 = std::make_unique<Rational>(1);
  std::unique_ptr<IMathObject> m3 = std::make_unique<Rational>(1, 2);

  EXPECT_FALSE(*m1 != *m1);
  EXPECT_FALSE(*m2 != *m2);
  EXPECT_FALSE(*m1 != *m2);
  EXPECT_FALSE(*m2 != *m1);

  EXPECT_TRUE(*m1 != *m3);
  EXPECT_TRUE(*m2 != *m3);
  EXPECT_TRUE(*m3 != *m1);
  EXPECT_TRUE(*m3 != *m2);

  EXPECT_TRUE(*m1 != Variable("a"));
  EXPECT_TRUE(Variable("a") != *m1);

  EXPECT_FALSE(Integer() != 0);
  EXPECT_FALSE(0 != Integer());

  EXPECT_TRUE(Integer() != 1);
  EXPECT_TRUE(1 != Integer());
}

TEST(MathObjectTests, outputTest) {
  std::unique_ptr<IMathObject> m1 = std::make_unique<Integer>(123);
  std::stringstream out;
  out << *m1;
  EXPECT_EQ(out.str(), "123");
}
