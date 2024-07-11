#pragma once

#if defined(__cplusplus)

#include <cassert>
#include <type_traits>

template <typename T, typename U>
constexpr auto saf_internal_SameType(T, U) noexcept -> bool {
  return std::is_same_v<std::decay_t<T>, std::decay_t<U>>;
}

template <typename T, typename U>
constexpr auto saf_internal_StaticAssertSameType(T &&, U &&) noexcept -> void {
  static_assert(std::is_same_v<std::decay_t<T>, std::decay_t<U>>,
                "Both operands must be of the same type");
}

#else

#include <assert.h>

#define saf_internal_SameType(lhs, rhs)                                        \
  _Generic((rhs), __typeof(lhs) : 1, default : 0)

#define saf_internal_StaticAssertSameType(lhs, rhs)                            \
  sizeof(struct {                                                              \
    static_assert(saf_internal_SameType(lhs, rhs),                             \
                  "Both operands must be of the same type");                   \
    int dummy;                                                                 \
  })

#endif
