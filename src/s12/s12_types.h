/* s12's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S12_TYPES_H
#define S12_TYPES_H

#include "stage_types.h"

/* from func_800C610C */
typedef struct ParticleSlot {
    /* 0x00 */ u8 unk_00[0x3E];
    /* 0x3E */ s16 active;
    /* 0x40 */ u8 unk_40[0x4];
} ParticleSlot;

/* from func_800C6610 */
typedef struct ShotPoolEntry {
    /* 0x00 */ u8 unk_00[0x1C];
    /* 0x1C */ s16 active;
    /* 0x1E */ u8 unk_1E[0x6];
} ShotPoolEntry;

/* from func_800C6FC8 */
typedef struct SparkSource {
    /* 0x00 */ Object *owner;
    /* 0x04 */ VECTOR pos;
    /* 0x14 */ s16 vel[3];
    /* 0x1A */ s16 pad_1A;
    /* 0x1C */ s16 rot_y;
    /* 0x1E */ s16 rot_x;
    /* 0x20 */ s16 rot_z;
    /* 0x22 */ s16 active; /* active */
    /* 0x24 */ s16 timer;
    /* 0x26 */ s16 pad_26;
} SparkSource;

/* from func_800C7798, func_800C7694: the two entries at fx_entries (result != 0: active) */
typedef struct FxEntry {
    /* 0x00 */ Object *owner;
    /* 0x04 */ s16 *cursor;
    /* 0x08 */ s32 pos_x;
    /* 0x0C */ s32 pos_y;
    /* 0x10 */ s32 pos_z;
    /* 0x14 */ u8 unk_14[0x4];
    /* 0x18 */ s16 rand_18;
    /* 0x1A */ s16 rand_1A;
    /* 0x1C */ s16 rand_1C;
    /* 0x1E */ u8 unk_1E[0x2];
    /* 0x20 */ s32 remaining;
    /* 0x24 */ s32 scroll;
    /* 0x28 */ s32 index;
    /* 0x2C */ s16 speed;
    /* 0x2E */ s16 rand_2E;
    /* 0x30 */ u16 out0;
    /* 0x32 */ u16 out1;
    /* 0x34 */ s16 out4;
    /* 0x36 */ s16 result;
    /* 0x38 */ u16 out2;
    /* 0x3A */ u16 out3;
} FxEntry;

/* from func_800C8004 */
typedef struct FxSlot {
    /* 0x00 */ struct Object *owner;
    /* 0x04 */ u8 pad_04[0x10];
    /* 0x14 */ SVECTOR jitter[4]; /* random offsets, re-rolled every frame by func_800C7F08 */
    /* 0x34 */ s16 level;         /* += level_step each frame, clamped to 0..0x3FFF */
    /* 0x36 */ s16 level_step;
    /* 0x38 */ s16 active;
    /* 0x3A */ s16 unk_3A; /* nonzero: model part 11, else 9 */
    /* 0x3C */ s16 seed;
    /* 0x3E */ u8 pad_3E[0x2];
} FxSlot;

/* from func_800C9BC8 */
typedef struct SoundSlotEntry {
    /* 0x00 */ Object *owner; /* its asset table gives the spark's model slot (sound_slot_draw) */
    /* 0x04 */ Vec3 pos;
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ s32 timer; /* counts up to 0x31 (sound_slot_tick) */
    /* 0x18 */ s16 active;
    /* 0x1A */ u8 unk_1A[0x2];
} SoundSlotEntry;

/* from func_800C7024 */
typedef struct ShotSweep {
    u8 pad_00[4];
    VECTOR from;
    s16 off[3];
    u8 pad_1A[8];
    s16 unk_22;
} ShotSweep;

/* from func_800C66D0 */
typedef struct HitboxBounds {
    s32 w[4];
} HitboxBounds;

/* from func_800C66D0 */
typedef struct Hitbox {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ HitboxBounds box;
    /* 0x14 */ s16 size[3];
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ u16 flags;
} Hitbox;

/* from func_800CBAE0 */
typedef struct CamTrackState {
    /* 0x00 */ u8 unk_00[4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 enabled;  /* func_800CB930 does nothing while 0 */
    /* 0x0E */ s16 angle2;
    /* 0x10 */ s16 angle1;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u8 unk_14[2];
    /* 0x16 */ s16 pos_history_index;   /* func_800C983C's index */
    /* 0x18 */ s16 mode;     /* 0 for D_80131E68, 1 for D_80131E84 */
    /* 0x1A */ u8 unk_1A[2];
} CamTrackState;

/* from func_800C9BA0 */
typedef struct SoundSlotTimer {
    u8 unk_00[0x14];
    s32 timer;
    s16 unk_18;
} SoundSlotTimer;

/* from func_800C1578 */
typedef struct HalfStream {
    u8 unk_00[0x20];
    u8 *cursor;
    u8 unk_24[0x276 - 0x24];
    u16 value;
} HalfStream;

/* from func_800C2028 */
typedef struct ScriptCtx {
    u8 unk_00[0x20];
    s16 *cursor; /* 0x20: read pointer, advanced one s16 per call */
    u8 unk_24[0x24C];
    s32 value; /* 0x270 */
} ScriptCtx;

/* from func_800CA8A8 */
typedef struct PosRecord16 {
    Vec3 pos;
    s32 unk_0C;
} PosRecord16;

/* from func_800C1AB4 */
typedef struct {
    u8 pad[0x20];
    u8 *cursor;
} CursorObj20;

/* from func_800C0290 */
struct ProximityFlag {
    u8 armed;
    u8 active;
    u8 unk_02;
    u8 unk_03;
    s16 level;
    s16 step;
};

/* from func_800C1C6C */
typedef struct BytecodeCursor {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ s16 *pc;
} BytecodeCursor;

/* from func_800C84B4 */
typedef struct FxSlotSpawn {
    /* 0x00 */ s32 owner;
    /* 0x04 */ u8 unk_04[0x30];
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
} FxSlotSpawn;

/* from func_800C90A8 */
typedef struct Quad4 { s32 a, b, c, d; } Quad4;

/* from func_800C9F74 */
typedef struct SoundSlot {
    /* 0x00 */ s32 id;
    /* 0x04 */ SoundPos pos;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s16 active;
} SoundSlot;

/* from func_800C666C */
typedef struct ShotHitState {
    /* 0x00 */ u8 unk_00[0x1C];
    /* 0x1C */ s16 active;
    /* 0x1E */ s16 hit;
    /* 0x20 */ u16 flags;
    /* 0x22 */ u8 unk_22[2];
} ShotHitState;

/* from func_800C89A4; func_800C8F4C runs one setup on cur and stores it in slots[index] */
typedef struct PosHistorySlot {
    /* 0x00 */ Quad unk_00;
    /* 0x10 */ Quad pos;
} PosHistorySlot;

typedef struct PosHistoryEntry {
    /* 0x000 */ s32 obj;
    /* 0x004 */ s32 mode;      /* 0: keyframe_slot_emit_spark, else func_800C4CDC */
    /* 0x008 */ u8 world_pos[0x10];
    /* 0x018 */ Quad cur;
    /* 0x028 */ PosHistorySlot slots[64];
    /* 0x828 */ u8 pool_model_ids[8];
    /* 0x830 */ s16 count;
    /* 0x832 */ s16 index;
    /* 0x834 */ s16 active;
    /* 0x836 */ s16 result;
    /* 0x838 */ s16 unk_838;
    /* 0x83A */ s16 rnd;
} PosHistoryEntry;

/* from func_800C5498 */
typedef struct FadeEffect {
    /* 0x00 */ s32 pad_00;
    /* 0x04 */ s32 pos;
    /* 0x08 */ u8 pad_08[0x10];
    /* 0x18 */ s32 timer;
    /* 0x1C */ s32 limit;
    /* 0x20 */ u8 pad_20[0xC];
    /* 0x2C */ u8 colour[4];
} FadeEffect;

/* from func_800C5498 */
typedef struct ObjectMode {
    u8 pad[0x250];
    s32 mode;
} ObjectMode;

/* from func_800C6560 */
typedef struct ShotMover {
    /* 0x00 */ s32 pad0;
    /* 0x04 */ s32 x;
    /* 0x08 */ s32 y;
    /* 0x0C */ s32 z;
    /* 0x10 */ s32 pad10;
    /* 0x14 */ s16 vx;
    /* 0x16 */ s16 vy;
    /* 0x18 */ s16 vz;
    /* 0x1A */ s16 pad1A;
    /* 0x1C */ s16 active;
} ShotMover;

/* from func_800C6058 */
typedef struct ParticleSlotFields {
    s32 pos_x;      /* 0x00 */
    s32 pos_y;      /* 0x04 */
    s32 pos_z;      /* 0x08 */
    u8 unk_0C[4];   /* 0x0C */
    s32 vel_x;      /* 0x10 */
    s32 vel_y;      /* 0x14 */
    s32 vel_z;      /* 0x18 */
    u8 unk_1C[4];   /* 0x1C */
    s16 accel_x;    /* 0x20 */
    s16 accel_y;    /* 0x22 */
    s16 accel_z;    /* 0x24 */
    u8 unk_26[2];   /* 0x26 */
    s32 keyframe_time;     /* 0x28 */
    u8 unk_2C[4];   /* 0x2C */
    s16 *cursor;    /* 0x30 */
    u16 chan_a_start;     /* 0x34 */
    u16 chan_a_end;     /* 0x36 */
    u16 chan_b_start;     /* 0x38 */
    u16 chan_b_end;     /* 0x3A */
    u16 blend_factor;     /* 0x3C */
    s16 result;     /* 0x3E */
    u8 unk_40[2];   /* 0x40 */
    u16 flags;      /* 0x42 */
} ParticleSlotFields; /* 0x44, like ParticleSlot */

/* from func_800C748C */
typedef struct SparkSourceFields {
    /* 0x00 */ s32 owner;
    /* 0x04 */ s32 pos_x;
    /* 0x08 */ s32 pos_y;
    /* 0x0C */ s32 pos_z;
    /* 0x10 */ u8 unk_10[0x4];
    /* 0x14 */ s16 dir_x;
    /* 0x16 */ s16 dir_y;
    /* 0x18 */ s16 dir_z;
    /* 0x1A */ u8 unk_1A[0x2];
    /* 0x1C */ s16 yaw;
    /* 0x1E */ s16 pitch;
    /* 0x20 */ s16 roll;
    /* 0x22 */ s16 active;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ u8 unk_26[0x2];
} SparkSourceFields;

/* from func_800CA584 */
typedef struct RecS12Burst {
    /* 0x00 */ s32 owner;
    /* 0x04 */ Quad4S12 lo;
    /* 0x14 */ Quad4S12 pos;    /* world position, fixed point */
    /* 0x24 */ s32 speed;
    /* 0x28 */ s32 vel_y;
    /* 0x2C */ s16 angle;
    /* 0x2E */ s16 active;
    /* 0x30 */ s16 frame_count;
} RecS12Burst; /* the 0x40 records at D_80130A68 */

/* from func_800CC7F0 */
typedef struct { s32 f0, f4, f8, fc, f10, f14, f18; } FlyCam;

/* from func_800C8590 */
typedef struct {
    s32 unk_00[2];  /* 0x00 */
    u16 pos;        /* 0x08 */
    u16 vel;        /* 0x0A */
    s16 active;     /* 0x0C */
    s16 base;       /* 0x0E */
    s16 scale;      /* 0x10 */
    s16 vals[3];    /* 0x12 */
} ScrollSeg;

/* from func_800CB7FC */
typedef struct FxTrack {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ u16 level;
    /* 0x0A */ u16 rate;
    /* 0x0C */ s16 active;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 phase;
    /* 0x16 */ s16 handle;
    /* 0x18 */ s16 unk_18;
} FxTrack;

/* from func_800C6168 */
typedef struct GlowParticle {
    /* 0x00 */ s32 x, y, z;
    /* 0x0C */ u8 unk_0C[0x20];
    /* 0x2C */ s16 base;
    /* 0x2E */ u8 unk_2E[6];
    /* 0x34 */ s16 offset_a;
    /* 0x36 */ s16 offset_b;
    /* 0x38 */ u16 from;
    /* 0x3A */ u16 to;
    /* 0x3C */ s16 blend; /* 0x1000 = all `to` */
    /* 0x3E */ u8 unk_3E[4];
    /* 0x42 */ u16 colour;
} GlowParticle;

/* from func_800BCB3C */
typedef struct TimerTail {
    u8 pad_000[0x1B7];
    u8 unk_1B7;
    u8 pad_1B8[0x26A - 0x1B8];
    u16 wander_timer;
    u8 pad_26C[0x270 - 0x26C];
    s16 unk_270;
    s16 wander_count;
    union {
        s32 word;
        s16 half[2];
    } unk_274;   /* word at 0x274; half[1] is 0x276 */
} TimerTail;

/* from func_800CB930 */
typedef struct FxOffset {
    s16 x;
    s16 y;
    s16 z;
    s16 unk_06;
} FxOffset;

/* from func_800CAF04 */
typedef struct TurnVars {
    /* 0x248 */ Mover mover;
    /* 0x254 */ u8 unk_254[6];
    /* 0x25A */ s16 turn_a;
    /* 0x25C */ s16 turn_b;
    /* 0x25E */ u16 turn_c;
    /* 0x260 */ s16 yaw_offset;
    /* 0x262 */ s16 pitch_offset;
    /* 0x264 */ u16 phase;
} TurnVars;

/* from func_800C72F8 */
typedef struct SparkPose {
    /* 0x00 */ struct { u8 pad[0x1A0]; s32 *table; } *owner;
    /* 0x04 */ s32 x, y, z;
    /* 0x10 */ u8 pad_10[0xC];
    /* 0x1C */ s16 ry, rx, rz;
} SparkPose;

/* from func_800BC50C */
typedef struct TimerTailFields {
    u8 pad_000[0x268];
    s16 unk_268;
    u16 unk_26A;
    s16 unk_26C;
    s16 unk_26E;
    s16 unk_270;
    s16 unk_272;
    s16 unk_274;
    s16 unk_276;
    s16 sound_handle;
} TimerTailFields;

/* from func_800C8A00 */
typedef struct BlendVec {
    s16 x, z, y, pad;
} BlendVec;

/* from func_800C8A00 */
typedef struct BlendSrc {
    u8 pad0[0x14];
    s16 den;
    s16 num;
    s16 index_a;
    s16 index_b;
} BlendSrc;

/* from func_800C8A00 */
typedef struct BlendDst {
    BlendSrc *src;
    s32 unk_04;
    s32 base[3];
    s32 unk_14;
    s32 result[3];
} BlendDst;

/* from func_800C06EC */
typedef struct ProxCell {
    u8 pad_00[4];
    u16 unk_04;
    u16 unk_06;
    s16 x_offset;
    s16 z_offset;
    u8 pad_0C[4];
    s16 flag_offset;
} ProxCell;

/* from func_800C06EC */
typedef struct ProxBlock {
    u8 pad_00[0x1C];
    s32 x;
    s32 y;
    s32 z;
} ProxBlock;

/* from func_800C2CC4 */
typedef struct TrailPos { s32 x, y, z, pad; } TrailPos;

#endif
