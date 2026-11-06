/* s02's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S02_TYPES_H
#define S02_TYPES_H

#include "stage_types.h"

/* from func_800C5310 */
typedef struct RangeBox {
    s32 min_x, max_x;
    s32 min_y, max_y;
    s32 min_z, max_z;
} RangeBox;

/* from func_800BF524 */
typedef struct BlinkObj {
    u8 pad_000[0x268];
    s16 timer;
    u16 count;
} BlinkObj;

/* from func_800C1704 */
typedef struct TrailSample {
    MatrixRow row[4];
} TrailSample;

/* from func_800C0440 */
typedef struct TunnelMechObj {
    u8 pad_000[0x18E];
    s16 next_index;
    u8 pad_190[0x1A0 - 0x190];
    s32 *asset;
    u8 pad_1A4[0x1F0 - 0x1A4];
    s32 x;
    s32 y;
    u8 pad_1F8[0x250 - 0x1F8];
    s16 index;
    s16 frame;
    u8 pad_254[0x272 - 0x254];
    s16 mode;
} TunnelMechObj;

/* from func_800C10DC */
typedef struct TunnelMechState {
    /* 0x00 */ s16 timer;
    /* 0x02 */ s16 counter;
    /* 0x04 */ s16 sweep;        /* 0x1000 per turn, wraps */
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 sound_on;     /* 1: sound_handle plays */
    /* 0x0A */ u8 pad_0A[2];
    /* 0x0C */ s32 sound_handle; /* looping sound */
    /* 0x10 */ s16 sound2_on;    /* 1: sound2_handle plays */
    /* 0x12 */ u8 pad_12[2];
    /* 0x14 */ s32 sound2_handle;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s16 unk_1C;
} TunnelMechState;

#endif
