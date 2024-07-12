#include "IntegersFixture.hpp"

#include "saf/integers.h"

namespace {

template <typename T> using TestSafOverflows = saf::TestIntegers<T>;
TYPED_TEST_SUITE(TestSafOverflows, saf::AllInts);

TYPED_TEST(TestSafOverflows, Addition) {
  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMaxValue(), TestFixture::Cast(0)},
           std::array{TestFixture::Cast(TestFixture::GetMaxValue() - 1),
                      TestFixture::Cast(1)},
           std::array{TestFixture::GetMinValue(), TestFixture::GetMaxValue()},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Add, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Add, a, b); }, rhs,
        lhs);
  }

  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMaxValue(), TestFixture::Cast(1)},
           std::array{TestFixture::GetMaxValue(), TestFixture::GetMaxValue()},
       }) {
    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Add, a, b); },
                 lhs, rhs);

    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Add, a, b); },
                 rhs, lhs);
  }
}

TYPED_TEST(TestSafOverflows, Subsctraction) {
  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMaxValue(), TestFixture::Cast(0)},
           std::array{TestFixture::Cast(TestFixture::GetMaxValue() - 1),
                      TestFixture::Cast(-1)},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsOverflowing(Sub, a, b); }, lhs,
        rhs);
  }

  if constexpr (TestFixture::IsSigned()) {
    // Unsigned substraction can never Overflows

    for (auto [lhs, rhs] : std::array{
             std::array{TestFixture::GetMaxValue(), TestFixture::Cast(-1)},
             std::array{TestFixture::GetMaxValue(), TestFixture::GetMinValue()},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Sub, a, b); },
                   lhs, rhs);
    }
  }
}

TYPED_TEST(TestSafOverflows, Multiplication) {
  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMaxValue(), TestFixture::Cast(0)},
           std::array{TestFixture::GetMaxValue(), TestFixture::Cast(1)},
           std::array{TestFixture::Cast(TestFixture::GetMaxValue() /
                                        TestFixture::Cast(2)),
                      TestFixture::Cast(2)},
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
           std::array{TestFixture::GetMaxValue(), TestFixture::GetMaxValue()},
           std::array{TestFixture::GetMaxValue(), TestFixture::Cast(2)},
       }) {
    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                 lhs, rhs);

    EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                 rhs, lhs);
  }

  if constexpr (TestFixture::IsSigned()) {
    for (auto [lhs, rhs] : std::array{
             std::array{TestFixture::GetMinValue(), TestFixture::GetMinValue()},
             std::array{TestFixture::GetMinValue(), TestFixture::Cast(-2)},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                   lhs, rhs);

      EXPECT_PRED2([](auto a, auto b) { return saf_IsOverflowing(Mul, a, b); },
                   rhs, lhs);
    }
  }
}

} // namespace
