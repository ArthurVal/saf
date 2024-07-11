#include "gtest/gtest.h"

#include <cstdint>
#include <limits>
#include <type_traits>

namespace saf {
template <typename T> struct TestIntegers : public testing::Test {
  static_assert(std::is_integral_v<T>);

  static constexpr auto IsUnsigned() noexcept -> bool {
    return std::is_unsigned_v<T>;
  }

  static constexpr auto IsSigned() noexcept -> bool {
    return std::is_signed_v<T>;
  }

  template <typename U> static constexpr auto Cast(U val) -> T {
    return static_cast<T>(val);
  }

  static constexpr auto GetMaxValue() noexcept -> T {
    return std::numeric_limits<T>::max();
  }

  static constexpr auto GetMinValue() noexcept -> T {
    return std::numeric_limits<T>::min();
  }
};

using AllInts =
    ::testing::Types<std::int8_t, std::int16_t, std::int32_t, std::int64_t,
                     std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t>;

} // namespace saf
