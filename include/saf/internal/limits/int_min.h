#pragma once

#if defined(__cplusplus)
#include <limits>
#include <type_traits>

template <typename T> constexpr auto saf_internal_IntMin(T) noexcept -> T {
  static_assert(std::is_integral_v<T>);
  return std::numeric_limits<T>::min();
}

#else

// clang-format off
#define saf_internal_IntMin(integer)                                           \
  _Generic((integer),                                                          \
           int8_t   : INT8_MIN,                                                \
           int16_t  : INT16_MIN,                                               \
           int32_t  : INT32_MIN,                                               \
           int64_t  : INT64_MIN,                                               \
           uint8_t  : 0,                                                       \
           uint16_t : 0,                                                       \
           uint32_t : 0,                                                       \
           uint64_t : 0                                                        \
  )
// clang-format on

#endif
