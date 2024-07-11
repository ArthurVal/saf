#pragma once

#if defined(__cplusplus)
#include <limits>
#include <type_traits>

template <typename T> constexpr auto saf_internal_IntMax(T) noexcept -> T {
  static_assert(std::is_integral_v<T>);
  return std::numeric_limits<T>::max();
}

#else

// clang-format off
#define saf_internal_IntMax(integer)                                           \
  _Generic((integer),                                                          \
           int8_t   : INT8_MAX,                                                \
           int16_t  : INT16_MAX,                                               \
           int32_t  : INT32_MAX,                                               \
           int64_t  : INT64_MAX,                                               \
           uint8_t  : UINT8_MAX,                                               \
           uint16_t : UINT16_MAX,                                              \
           uint32_t : UINT32_MAX,                                              \
           uint64_t : UINT64_MAX                                               \
  )
// clang-format on

#endif
