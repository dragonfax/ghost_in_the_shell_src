/* s01's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S01_TYPES_H
#define S01_TYPES_H

#include "stage_types.h"

/* A spark burst source: 0x38-byte records (40 at spark_burst_table in S01, walked by rec_list_run). owner is the object
 * whose asset table gives the model slot; the burst spawns a spark at pos and, for mode 0, a second at pos2. */
typedef struct SparkBurst {
    /* 0x00 */ Object *owner;
    /* 0x04 */ Vec3 pos;
    /* 0x10 */ u8 pad_10[4];
    /* 0x14 */ Vec3 pos2;
    /* 0x20 */ u8 pad_20[4];
    /* 0x24 */ s16 rot_x;
    /* 0x26 */ s16 rot_y;
    /* 0x28 */ s16 rot_z;
    /* 0x2A */ u8 pad_2A[2];
    /* 0x2C */ s32 size;
    /* 0x30 */ s32 strength;
    /* 0x34 */ s32 mode;
} SparkBurst;

/* The collision move records of move_box_step. */
typedef struct MoveIn {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ VECTOR pos;
    /* 0x14 */ u8 hit_pos[0x10];
    /* 0x24 */ Bytes8 angles;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 unk_34[0xC];
    /* 0x40 */ s32 unk_40;
} MoveIn;

typedef struct MoveOut {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ VECTOR pos;
    /* 0x14 */ VECTOR prev;
    /* 0x24 */ Bytes8 angles;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 ok;
} MoveOut;

typedef struct MoveBox {
    VECTOR a, b, c;
} MoveBox;

/* from sway_update */
typedef struct SwayState {
    /* 0x00 */ Object *owner;
    /* 0x04 */ u8 unk_04[0x28];
    /* 0x2C */ s32 level;
    /* 0x30 */ s32 sway;
    /* 0x34 */ s32 active;
    /* 0x38 */ s32 level_step;
    /* 0x3C */ s32 sway_step;
    /* 0x40 */ s32 pitch;
} SwayState;

/* The owner sound_emitter_update (an S01 sound callback, see SoundOwner) follows: pitch read as s16. */
typedef struct SoundEmitter {
    /* 0x00 */ Object *target; /* the object the sound follows */
    /* 0x04 */ u8 unk_04[0x1C];
    /* 0x20 */ s16 pitch;
    /* 0x22 */ u8 unk_22[2];
    /* 0x24 */ s32 volume;
} SoundEmitter;

/* Scratch block of the SoundPair callbacks: the segment and the point on it nearest the listener. */
typedef struct SegmentWork {
    Segment32 seg;
    Vec3 near;
    s32 pad_2C;
} SegmentWork;

/* from sway_start */
typedef struct SegVec {
    Vec3 a;
    s32 pad_0C;
} SegVec;

/* from move_box_sweep */
typedef struct MoveScratch {
    MoveBox box;
    VECTOR rot[2];
} MoveScratch;

#endif
