#include <gtest/gtest.h>

#include "fintamath/core/IMathObject.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestMathObject : public IMathObjectCRTP<TestMathObject> {};

}

TEST(IMathObjectTests, toStringTest) {
  EXPECT_EQ(TestMathObject().toString(), typeid(TestMathObject).name());
}

TEST(IMathObjectTests, cloneTest) {
  std::unique_ptr<IMathObject> m1 = std::make_unique<Integer>();
  std::unique_ptr<IMathObject> m2 = std::make_unique<Integer>(1);
  std::unique_ptr<IMathObject> m3 = m1->clone();
  std::unique_ptr<IMathObject> m4 = Integer(1).clone();

  EXPECT_EQ(*m3, *m1);
  EXPECT_EQ(*m4, *m2);

  EXPECT_NE(*m3, *m2);
  EXPECT_NE(*m4, *m1);

  EXPECT_NE(m3, m1);
  EXPECT_NE(m4, m2);
}

TEST(IMathObjectTests, equalsTest) {
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

  Integer m4;
  EXPECT_TRUE(m4 == m4);
}

TEST(IMathObjectTests, nequalsTest) {
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

  Integer m4;
  EXPECT_FALSE(m4 != m4);
}

TEST(IMathObjectTests, outputTest) {
  std::unique_ptr<IMathObject> m1 = std::make_unique<Integer>(123);
  std::stringstream out;
  out << *m1;
  EXPECT_EQ(out.str(), "123");
}

TEST(IMathObjectTests, getTypeTest) {
  EXPECT_EQ(IMathObject::getTypeStatic(), MathObjectType::IMathObject);
}
