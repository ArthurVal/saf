#include "IntegersFixture.hpp"

#include "saf/integers.h"

namespace {

template <typename T> using TestSafUnderflows = saf::TestIntegers<T>;
TYPED_TEST_SUITE(TestSafUnderflows, saf::AllInts);

TYPED_TEST(TestSafUnderflows, Addition) {
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMinValue(), this->Cast(0)},
           std::array{this->Cast(this->GetMinValue() + 1), this->Cast(-1)},
           std::array{this->GetMinValue(), this->GetMaxValue()},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Add, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Add, a, b); }, rhs,
        lhs);
  }

  if constexpr (this->IsSigned()) {
    // Addition with unsigned can never underflows
    for (auto [lhs, rhs] : std::array{
             std::array{this->GetMinValue(), this->Cast(-1)},
             std::array{this->GetMinValue(), this->GetMinValue()},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Add, a, b); },
                   lhs, rhs);

      EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Add, a, b); },
                   rhs, lhs);
    }
  }
}

TYPED_TEST(TestSafUnderflows, Subsctraction) {
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMinValue(), this->Cast(0)},
           std::array{this->Cast(this->GetMinValue() + 1), this->Cast(1)},
           std::array{this->GetMaxValue(), this->GetMaxValue()},
           std::array{this->GetMinValue(), this->GetMinValue()},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Sub, a, b); }, lhs,
        rhs);
  }

  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMinValue(), this->Cast(1)},
           std::array{this->GetMinValue(), this->GetMaxValue()},
       }) {
    EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Sub, a, b); },
                 lhs, rhs);
  }
}

TYPED_TEST(TestSafUnderflows, Multiplication) {
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMinValue(), this->Cast(0)},
           std::array{this->GetMinValue(), this->Cast(1)},
           std::array{this->GetMinValue(), this->Cast(-1)},
           std::array{this->GetMinValue(), this->Cast(-2)},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Mul, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Mul, a, b); }, rhs,
        lhs);
  }
  if constexpr (this->IsSigned()) {
    // Unsigned multiplication cannot underflows
    for (auto [lhs, rhs] : std::array{
             std::array{this->GetMaxValue(), this->Cast(-2)},
             std::array{this->GetMinValue(), this->Cast(2)},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Mul, a, b); },
                   lhs, rhs);

      EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Mul, a, b); },
                   rhs, lhs);
    }
  }
}

} // namespace
