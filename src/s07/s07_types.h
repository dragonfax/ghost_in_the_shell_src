/* s07's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S07_TYPES_H
#define S07_TYPES_H

#include "stage_types.h"

/* s07's 0x20 records at D_80126710 (func_800C5D30 walks them, func_800C5CE0 steps one) */
typedef struct SfxEmitter {
    /* 0x00 */ Object *owner;
    /* 0x04 */ Vec3 pos;
    /* 0x10 */ u8 pad_10[4];
    /* 0x14 */ s32 tick;
    /* 0x18 */ Keyframe *keyframes;
    /* 0x1C */ u16 from;
    /* 0x1E */ u16 to;
    /* 0x20 */ s16 blend;
    /* 0x22 */ s16 active;
    /* 0x24 */ u16 level;
    /* 0x26 */ u8 pad_26[2];
} SfxEmitter;

/* s07's fliers (0x20 of them at D_80126010; func_800C62C8 moves one) */
typedef struct FlyEntry {
    /* 0x00 */ void *owner; /* passed to func_800C6134 */
    /* 0x04 */ s32 prev_pos_x; /* unk_04..unk_10: the previous unk_14..unk_20 */
    /* 0x08 */ s32 prev_pos_y;
    /* 0x0C */ s32 prev_pos_z;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 pos_x;
    /* 0x18 */ s32 pos_y;
    /* 0x1C */ s32 pos_z;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 speed;
    /* 0x28 */ s32 vel_y;
    /* 0x2C */ s16 angle;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ s16 active; /* nonzero: active */
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ u8 pad_36[2];
} FlyEntry;

/* from func_800C6A30 */
typedef struct SparkEntry {
    /* 0x00 */ s32 object;
    /* 0x04 */ s32 a[3];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 b[3];
    /* 0x20 */ u8 pad_20[0x10];
    /* 0x30 */ struct SegTarget *target;
    /* 0x34 */ s16 key_from;  /* model blend for the spark (s07 func_800C6BF0) */
    /* 0x36 */ s16 key_to;
    /* 0x38 */ s16 key_t;
    /* 0x3A */ s16 active;
} SparkEntry;

/* from func_800C71A8 */
typedef struct KeyframeEntry {
    /* 0x00 */ u8 unk_00[0x2A];
    /* 0x2A */ s16 active;
    /* 0x2C */ u8 unk_2C[0x34 - 0x2C];
} KeyframeEntry;

/* from func_800C7AD0 */
typedef struct PackedBytes8 {
    u8 bytes[8];
} __attribute__((packed)) PackedBytes8;

/* from func_800C7870 */
typedef struct ModelPart {
    /* 0x00 */ Object *owner;
    /* 0x04 */ s32 pos[3];
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ PackedBytes8 rot;
    /* 0x1C */ s16 active;
    /* 0x1E */ s16 model_offset;
    /* 0x20 */ s16 part;
    /* 0x22 */ s16 level_ramp[2];
    /* 0x26 */ u16 shade;
    /* 0x28 */ s16 scale;
    /* 0x2A */ u8 pad_2A[2];
} ModelPart;

/* from func_800C6A8C */
typedef struct SegPair {
    s32 a[3];          /* 0x00 */
    s32 unk_0C;
    s32 b[3];          /* 0x10 */
} SegPair;

/* from func_800C715C */
typedef struct KeyframeInterp {
    u8 unk_00[0x1C];
    s32 tick;           /* 0x1C */
    Keyframe *cursor;   /* 0x20 */
    u16 from;           /* 0x24 */
    u16 to;             /* 0x26 */
    s16 t;              /* 0x28 */
    u8 unk_2A[0x30 - 0x2A];
    s16 unk_30;         /* 0x30 */
} KeyframeInterp;

/* from func_800C46F4 */
typedef struct ScriptRepeatCtx {
    u8 pad_00[0x1C];
    s32 *table;
    s16 *pc;
    u8 pad_24[0x264 - 0x24];
    s16 last;
} ScriptRepeatCtx;

/* from func_800C8A88 */
typedef struct DebrisEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 active;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} DebrisEntry;

/* from func_800C4434 */
typedef struct ScriptLoopCtx {
    u8 pad_00[0x1C];
    s32 *table;      /* 0x1C */
    s16 *cursor;     /* 0x20 */
    u8 pad_24[0x242];
    u16 loop_counts[1]; /* 0x266, indexed by op */
} ScriptLoopCtx;

/* from func_800C40F0 */
typedef struct ScriptJumpTable {
    /* 0x00 */ u8 unk_00[0x1C];
    /* 0x1C */ s32 *table;
    /* 0x20 */ s16 *cursor;
} ScriptJumpTable;

/* from func_800C6978 */
typedef struct SparkState {
    u8 unk_00[4];
    Vec4Words pos;
    Vec4Words prev;
    s32 speed;
    s32 tick;
    s16 yaw;
    s16 pitch;
    Keyframe *cursor;
    u16 from;
    u16 to;
    s16 t;
    s16 result;
} SparkState;

/* from func_800C684C */
typedef struct PositionedObj {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ s32 x;
    /* 0x18 */ s32 y;
    /* 0x1C */ s32 z;
    /* 0x20 */ u8 pad_20[0x12];
    /* 0x32 */ s16 active;
} PositionedObj;

/* from func_800C8744 */
typedef struct DebrisMotion {
    s32 unk_00;
    s32 unk_04;
    s32 x;
    s32 dx;
    s32 y;
    s32 vy;
    s32 ay;
    s32 z;
    s32 vz;
    s32 az;
} DebrisMotion;

/* from func_800C8348 */
typedef struct KeyTrack {
    Object *owner;          /* 0x00 */
    Keyframe *cursor;       /* 0x04 */
    s32 pos_x;             /* 0x08 */
    s32 pos_y;             /* 0x0C */
    s32 pos_z;             /* 0x10 */
    u8 pad_14[0x0C];
    s32 tick;               /* 0x20 */
    s32 scale;              /* 0x24 */
    s32 unk_28;             /* 0x28 */
    s16 unk_2C;             /* 0x2C */
    u8 pad_2E[2];
    u16 from;               /* 0x30 */
    u16 to;                 /* 0x32 */
    s16 t;                  /* 0x34 */
    s16 done;               /* 0x36 */
} KeyTrack;

/* from func_800B8514 */
typedef struct EnemyShotSlot {
    s16 timer;  /* 0x00 */
    s16 count;  /* 0x02 */
    u16 acc;    /* 0x04 */
    s16 aim;    /* 0x06 */
} EnemyShotSlot;

/* from func_800C6518 */
typedef struct SparkEmitter {
    /* 0x00 */ struct { u8 pad[0x1A0]; s32 *table; } *owner;
    /* 0x04 */ u8 pad_04[0x0C];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 x, y, z;
    /* 0x20 */ u8 pad_20[0xE];
    /* 0x2E */ u16 timer;
} SparkEmitter;

/* from func_800C8CA0 */
typedef struct KeyMover {
    u8 pad_00[4];
    s32 pos_x;              /* 0x04 */
    s32 pos_y;              /* 0x08 */
    s32 pos_z;              /* 0x0C */
    u8 pad_10[4];
    s16 rot_a;              /* 0x14 */
    s16 rot_b;              /* 0x16 */
    u8 pad_18[4];
    s32 tick;               /* 0x1C */
    s16 active;             /* 0x20 */
    s16 state;              /* 0x22 */
    Keyframe *cursor;       /* 0x24 */
    u16 from;               /* 0x28 */
    u16 to;                 /* 0x2A */
    s16 t;                  /* 0x2C */
} KeyMover;

/* from func_800C885C */
typedef struct DebrisParams {
    /* 0x00 */ SparkOwner *owner;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 angle;
    /* 0x14 */ u8 pad[8];
    /* 0x1C */ s32 speed;
} DebrisParams;

/* from func_800CA0CC */
typedef struct ClampTable {
    s32 w[8];
} ClampTable;

/* from func_800CA0CC */
typedef struct SpawnArgs {
    u8 pad_00[0x16];
    s16 unk_16;
} SpawnArgs;

/* from stationary_laser_draw */
typedef struct StationaryLaserVars {
    /* 0x000 */ u8 pad_000[0x26D];
    /* 0x26D */ u8 segments;
    /* 0x26E */ u8 pad_26E[2];
    /* 0x270 */ s16 start_size;
    /* 0x272 */ s16 fade;
    /* 0x274 */ s16 tail_sprite;
    /* 0x276 */ u16 end_size;
    /* 0x278 */ s16 size_add;
} StationaryLaserVars;

/* from stationary_laser_draw */
typedef struct LaserScratch {
    Vec3 step;
    s32 pad;
    Vec3 pos;
} LaserScratch;

/* from stationary_laser_update */
typedef struct StatLaserS07 {
    u8 pad_000[0x184];
    /* 0x184 */ s16 owner;
    u8 pad_186[0x1F0 - 0x186];
    /* 0x1F0 */ s32 x, y, z;
    u8 pad_1FC[0x220 - 0x1FC];
    /* 0x220 */ s16 yaw, pitch;
    u8 pad_224[0x268 - 0x224];
    /* 0x268 */ s32 sound;
    /* 0x26C */ u8 off;
    /* 0x26D */ u8 hit_len;
    /* 0x26E */ u16 timer;
    /* 0x270 */ s16 power;
    /* 0x272 */ s16 hit_frac;
    /* 0x274 */ u16 flicker;
    /* 0x276 */ s16 decay;
    /* 0x278 */ s16 jitter;
} StatLaserS07;

/* from func_800C6DE0 */
typedef struct SegEntryFull {
    /* 0x00 */ Object *obj;
    /* 0x04 */ s32 a[3];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 b[3];
    /* 0x20 */ u8 pad_20[4];
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 tick;
    /* 0x2C */ s16 yaw;
    /* 0x2E */ s16 pitch;
    /* 0x30 */ Keyframe *cursor;
    /* 0x34 */ u16 from;
    /* 0x36 */ u16 to;
    /* 0x38 */ s16 t;
    /* 0x3A */ s16 active;
} SegEntryFull;

/* from func_800C7204 */
typedef struct PartPoint { u8 b[8]; } PartPoint;

/* from func_800C7204 */
typedef struct KeyframeSpark {
    /* 0x00 */ Object *owner;
    /* 0x04 */ s32 pos[3];
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ PartPoint box;
    /* 0x1C */ u8 pad1C[8];
    /* 0x24 */ s16 key_from;
    /* 0x26 */ s16 key_to;
    /* 0x28 */ s16 key_t;
    /* 0x2A */ u8 pad2A[4];
    /* 0x2E */ s16 sel;
    /* 0x30 */ s16 yaw;
} KeyframeSpark;

/* from func_800B8650 */
typedef struct EmitterSlot {
    s16 timer;
    s16 enabled;
    u16 scale;
    s16 colour;
} EmitterSlot;

#endif
