/* s03's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S03_TYPES_H
#define S03_TYPES_H

#include "stage_types.h"

/* from func_800B8C4C */
typedef struct DrawRequest {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} DrawRequest;

/* from func_800B7F90 */
typedef struct SlotObj {
    s32 unk_00;
    u8 flags_04;
} SlotObj;

/* from func_800C0958 */
typedef struct { s16 a, b, c, d; } ShotAim;

/* from func_800C3D08 */
typedef struct Words3 {
    s32 w[3];
} Words3;

/* from func_800C2764 */
typedef struct MuzzleAim {
    Vec3 off;
    s32 yaw;
    s32 pitch;
} MuzzleAim;

#endif
