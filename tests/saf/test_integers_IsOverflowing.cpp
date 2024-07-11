#include "IntegersFixture.hpp"

#include "saf/integers.h"

namespace {

template <typename T> using TestSafOverflows = saf::TestIntegers<T>;
TYPED_TEST_SUITE(TestSafOverflows, saf::AllInts);

TYPED_TEST(TestSafOverflows, Addition) {
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMaxValue(), this->Cast(0)},
           std::array{this->Cast(this->GetMaxValue() - 1), this->Cast(1)},
           std::array{this->GetMinValue(), this->GetMaxValue()},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Add, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Add, a, b); }, rhs,
        lhs);
  }

  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMaxValue(), this->Cast(1)},
           std::array{this->GetMaxValue(), this->GetMaxValue()},
       }) {
    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Add, a, b); },
                 lhs, rhs);

    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Add, a, b); },
                 rhs, lhs);
  }
}

TYPED_TEST(TestSafOverflows, Subsctraction) {
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMaxValue(), this->Cast(0)},
           std::array{this->Cast(this->GetMaxValue() - 1), this->Cast(-1)},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Sub, a, b); }, lhs,
        rhs);
  }

  if constexpr (this->IsSigned()) {
    // Unsigned substraction can never Overflows

    for (auto [lhs, rhs] : std::array{
             std::array{this->GetMaxValue(), this->Cast(-1)},
             std::array{this->GetMaxValue(), this->GetMinValue()},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Sub, a, b); },
                   lhs, rhs);
    }
  }
}

TYPED_TEST(TestSafOverflows, Multiplication) {
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMaxValue(), this->Cast(0)},
           std::array{this->GetMaxValue(), this->Cast(1)},
           std::array{this->Cast(this->GetMaxValue() / this->Cast(2)),
                      this->Cast(2)},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Mul, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Mul, a, b); }, rhs,
        lhs);
  }

  // Only positive values for unsigned case
  for (auto [lhs, rhs] : std::array{
           std::array{this->GetMaxValue(), this->GetMaxValue()},
           std::array{this->GetMaxValue(), this->Cast(2)},
       }) {
    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                 lhs, rhs);

    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                 rhs, lhs);
  }

  if constexpr (this->IsSigned()) {
    for (auto [lhs, rhs] : std::array{
             std::array{this->GetMinValue(), this->GetMinValue()},
             std::array{this->GetMinValue(), this->Cast(-2)},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                   lhs, rhs);

      EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                   rhs, lhs);
    }
  }
}

} // namespace
