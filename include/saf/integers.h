#pragma once

/* NOTE:
 * Do not include those in 'extern C' since it declares template functions in
 * order to replace _Generic() macros for the c++ based unittests
 */
#include "internal/assert.h"
#include "internal/limits/int_max.h"
#include "internal/limits/int_min.h"

/*****************************************************************************/
/*                               IsOverflowing                               */
/*****************************************************************************/
#define saf_IsOverflowing_AddImpl(lhs, rhs)                                    \
  (((rhs) > 0) && ((lhs) > (saf_internal_IntMax(lhs) - (rhs))))

#define saf_IsOverflowing_Add(lhs, rhs)                                        \
  (saf_internal_StaticAssertSameType(lhs, rhs),                                \
   saf_IsOverflowing_AddImpl(lhs, rhs))

#define saf_IsOverflowing_SubImpl(lhs, rhs)                                    \
  (((rhs) < 0) && ((lhs) > (saf_internal_IntMax(lhs) + (rhs))))

#define saf_IsOverflowing_Sub(lhs, rhs)                                        \
  (saf_internal_StaticAssertSameType(lhs, rhs),                                \
   saf_IsOverflowing_SubImpl(lhs, rhs))

#define saf_IsOverflowing_MulImpl(lhs, rhs)                                    \
  (((((lhs) > 0) && ((rhs) > 0)) &&                                            \
    ((lhs) > (saf_internal_IntMax(lhs) / (rhs)))) ||                           \
   ((((lhs) < 0) && ((rhs) < 0)) &&                                            \
    ((lhs) < (saf_internal_IntMax(lhs) / (rhs)))) ||                           \
   (false))

#define saf_IsOverflowing_Mul(lhs, rhs)                                        \
  (saf_internal_StaticAssertSameType(lhs, rhs),                                \
   saf_IsOverflowing_MulImpl(lhs, rhs))

#define saf_IsOverflowing(Op, lhs, rhs) saf_IsOverflowing_##Op(lhs, rhs)

/*****************************************************************************/
/*                              IsUnderflowing                               */
/*****************************************************************************/
#define saf_IsUnderflowing_AddImpl(lhs, rhs)                                   \
  (((rhs) < 0) && ((lhs) < (saf_internal_IntMin(lhs) - (rhs))))

#define saf_IsUnderflowing_Add(lhs, rhs)                                       \
  (saf_internal_StaticAssertSameType(lhs, rhs),                                \
   saf_IsUnderflowing_AddImpl(lhs, rhs))

#define saf_IsUnderflowing_SubImpl(lhs, rhs)                                   \
  (((rhs) > 0) && ((lhs) < (saf_internal_IntMin(lhs) + (rhs))))

#define saf_IsUnderflowing_Sub(lhs, rhs)                                       \
  (saf_internal_StaticAssertSameType(lhs, rhs),                                \
   saf_IsUnderflowing_SubImpl(lhs, rhs))

#define saf_IsUnderflowing_MulImpl(lhs, rhs)                                   \
  (((((lhs) > 0) && ((rhs) < 0)) &&                                            \
    ((lhs) > (saf_internal_IntMin(lhs) / (rhs)))) ||                           \
   ((((lhs) < 0) && ((rhs) > 0)) &&                                            \
    ((lhs) < (saf_internal_IntMin(lhs) / (rhs)))) ||                           \
   (false))

#define saf_IsUnderflowing_Mul(lhs, rhs)                                       \
  (saf_internal_StaticAssertSameType(lhs, rhs),                                \
   saf_IsUnderflowing_MulImpl(lhs, rhs))

#define saf_IsUnderflowing(Op, lhs, rhs) saf_IsUnderflowing_##Op(lhs, rhs)
