/* s05's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S05_TYPES_H
#define S05_TYPES_H

#include "stage_types.h"

/* from func_800C0348 */
typedef struct SpawnOffset {
    s32 unk_00;
    s16 x;
    s16 y;
    s16 z;
} SpawnOffset;

/* from func_800C0000 */
typedef struct StreamObj {
    u8 pad_00[0x20];
    u8 *cursor;        /* 0x20: read position, advanced by one halfword */
    u8 pad_24[0x256 - 0x24];
    u16 value;         /* 0x256: last halfword read */
    u16 unk_258;       /* 0x258: cleared */
} StreamObj;

/* from func_800C00B4 */
typedef struct {
    u8 unk_00[0x20];
    s16 *cursor;
    u8 unk_24[0x156];
    s8 flag_17A;
} ScriptMeterCtx;

/* from func_800BE510 */
typedef struct SlotRec {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 pos_x;
    /* 0x0C */ s32 pos_y;
    /* 0x10 */ s32 pos_z;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} SlotRec;

/* from spark_emit_pose */
typedef struct BonePose {
    /* 0x00 */ u8 pad_00[0x1C];
    /* 0x1C */ s16 x, y, z;
    /* 0x22 */ s16 ry, rx, rz;
} BonePose;

/* A patched script parameter and the code address it selects; lists end with a 0xFFFF param (S05 enemy type tables). */
typedef struct ScriptParamEntry {
    u16 param;
    u16 unk_02;
    u32 target;
} ScriptParamEntry;

#endif
