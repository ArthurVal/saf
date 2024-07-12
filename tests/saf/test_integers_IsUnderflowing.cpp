#include "IntegersFixture.hpp"

#include "saf/integers.h"

namespace {

template <typename T> using TestSafUnderflows = saf::TestIntegers<T>;
TYPED_TEST_SUITE(TestSafUnderflows, saf::AllInts);

TYPED_TEST(TestSafUnderflows, Addition) {
  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(0)},
           std::array{TestFixture::Cast(TestFixture::GetMinValue() + 1),
                      TestFixture::Cast(-1)},
           std::array{TestFixture::GetMinValue(), TestFixture::GetMaxValue()},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Add, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Add, a, b); }, rhs,
        lhs);
  }

  if constexpr (TestFixture::IsSigned()) {
    // Addition with unsigned can never underflows
    for (auto [lhs, rhs] : std::array{
             std::array{TestFixture::GetMinValue(), TestFixture::Cast(-1)},
             std::array{TestFixture::GetMinValue(), TestFixture::GetMinValue()},
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
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(0)},
           std::array{TestFixture::Cast(TestFixture::GetMinValue() + 1),
                      TestFixture::Cast(1)},
           std::array{TestFixture::GetMaxValue(), TestFixture::GetMaxValue()},
           std::array{TestFixture::GetMinValue(), TestFixture::GetMinValue()},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Sub, a, b); }, lhs,
        rhs);
  }

  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(1)},
           std::array{TestFixture::GetMinValue(), TestFixture::GetMaxValue()},
       }) {
    EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Sub, a, b); },
                 lhs, rhs);
  }
}

TYPED_TEST(TestSafUnderflows, Multiplication) {
  for (auto [lhs, rhs] : std::array{
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(0)},
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(1)},
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(-1)},
           std::array{TestFixture::GetMinValue(), TestFixture::Cast(-2)},
       }) {
    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Mul, a, b); }, lhs,
        rhs);

    EXPECT_PRED2(
        [](auto a, auto b) { return not saf_IsUnderflowing(Mul, a, b); }, rhs,
        lhs);
  }
  if constexpr (TestFixture::IsSigned()) {
    // Unsigned multiplication cannot underflows
    for (auto [lhs, rhs] : std::array{
             std::array{TestFixture::GetMaxValue(), TestFixture::Cast(-2)},
             std::array{TestFixture::GetMinValue(), TestFixture::Cast(2)},
         }) {
      EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Mul, a, b); },
                   lhs, rhs);

      EXPECT_PRED2([](auto a, auto b) { return saf_IsUnderflowing(Mul, a, b); },
                   rhs, lhs);
    }
  }
}

} // namespace
