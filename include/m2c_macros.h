/* Macros m2c emits with --valid-syntax (scripts/autodecomp.py drafts). Not for finished code. */
#ifndef M2C_MACROS_H
#define M2C_MACROS_H
#include "common.h"
#define M2C_UNK s32
#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_CARRY 0
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY(dst, src, size) memcpy((dst), (src), (size))
#define M2C_LWL(expr) (expr)
#define M2C_LWR(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#endif
