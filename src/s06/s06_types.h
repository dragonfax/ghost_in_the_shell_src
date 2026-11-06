/* s06's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S06_TYPES_H
#define S06_TYPES_H

#include "stage_types.h"

/* from func_800C8814 */
typedef struct FxTableEntry {
    /* 0x00 */ s32 pos[3];
    /* 0x0C */ u8 unk_0C[0x18 - 0x0C];
    /* 0x18 */ void *ptr;
    /* 0x1C */ u8 unk_1C[0x24 - 0x1C];
    /* 0x24 */ s32 pool_index; /* pool index, offset by 0x1E0 for pool_spawn_scaled */
} FxTableEntry;

/* from func_800C8C64 */
typedef struct KeyframeTrack {
    /* 0x00 */ u8 unk_00[0x3A];
    /* 0x3A */ s16 active;
    /* 0x3C */ u8 unk_3C[0x40 - 0x3C];
} KeyframeTrack;

/* from func_800CA4A8 */
typedef struct AttachEntry {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ u8 ray_pos[0x20];
    /* 0x24 */ u8 ray_rot[8];
    /* 0x2C */ s32 ray_dist; /* func_800CA1EC's result (func_800CA500) */
    /* 0x30 */ s32 level;
    /* 0x34 */ s32 fade_rate; /* added to unk_30 each frame (attach_entry_update) */
    /* 0x38 */ s32 range; /* eased toward the player's horizontal distance */
    /* 0x3C */ s16 active;
    /* 0x3E */ s16 flicker; /* rand_a_next() each frame */
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ u8 pad_42[2];
} AttachEntry;

/* from move_box_step */
typedef struct ShotTarget {
    u8 unk_00[0x24C];
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
} ShotTarget;

/* from func_800C3FF4 */
typedef struct AimPoint {
    s32 w[4];
} AimPoint;

/* from func_800C3FF4 */
typedef struct AimSoundBuf {
    Vec3 out;
    s32 pad;
    AimPoint src;
    AimPoint dst;
} AimSoundBuf;

/* from func_800C201C */
typedef struct EulerAngles {
    s16 pitch, yaw, roll;
} EulerAngles;

/* from func_800C453C */
typedef struct StateHistory {
    u16 state;
    u16 zero;
    u8 pad[2];
    u16 prev_state;
} StateHistory;

/* from func_800BD1F8 */
typedef struct ObjSoundBytes {
    u8 unk_000[0x270];
    u8 sound_0; /* 0x270 */
    u8 sound_1; /* 0x271 */
} ObjSoundBytes;

/* from func_800C875C */
typedef struct SoundHandles {
    s32 unk_00[7];
    s32 sound_a; /* 0x1C */
    s32 sound_b; /* 0x20 */
} SoundHandles;

/* from func_800C87B8 */
typedef struct FxPointEntry {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ u8 unk_0C[4];
    /* 0x10 */ s32 age;
    /* 0x14 */ s32 phase;
    /* 0x18 */ void *ptr; /* NULL once the point test fails: the slot is free */
} FxPointEntry;

/* from func_800C7B38 */
typedef struct ScriptBounds {
    u8 pad_00[0x186];
    s16 unk_186;
} ScriptBounds;

/* from func_800C7B38 */
typedef struct ScriptVm {
    u8 pad_00[0x1C];
    s32 *jump_table;             /* 0x1C */
    u8 *pc;                      /* 0x20 */
    u8 pad_24[0x248 - 0x24];
    ScriptBounds *bounds;        /* 0x248 */
} ScriptVm;

/* from func_800C455C */
typedef struct WalkState { s16 *tab; s32 count; s32 mag; s32 next_state; } WalkState;

/* from func_800C455C */
typedef struct EnemyWalkObj {
    u8 pad_000[0x1F0];
    s32 x, y, z;
    u8 pad_1FC[0x210 - 0x1FC];
    s32 vy;
    u8 pad_214[0x21C - 0x214];
    s32 accel;
    u8 pad_220[0x248 - 0x220];
    s32 pos;
    u8 pad_24C[0x22];
    s16 frame;  /* index into the D_8011E9AC record's table */
    s16 step;
} EnemyWalkObj;

/* from func_800C752C */
typedef struct ShotHalves {
    /* 0x27C */ s16 unk_27C;
    /* 0x27E */ s16 state;
    /* 0x280 */ s16 shots_left;
} ShotHalves;

/* from func_800C8AB4 */
typedef struct FxPosition {
    s32 w[4];
} FxPosition;

/* from func_800C8AB4 */
typedef struct FxEmitter {
    FxPosition pos;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 owner;
} FxEmitter;

/* from func_800CA2D8 */
typedef struct ObjAttach {
    Object *obj;          /* 0x00 */
    s32 pos[3];           /* 0x04 */
    u8 unk_10[4];         /* 0x10 */
    s16 rot[3];           /* 0x14 */
    u8 unk_1A[2];         /* 0x1A */
    u8 unk_1C[8];         /* 0x1C, copied to unk_24 */
    u8 unk_24[2];         /* 0x24 */
    u16 angle_sum;        /* 0x26 */
    u8 unk_28[4];         /* 0x28 */
} ObjAttach;

/* from func_800C8BC0 */
typedef struct KeyframeTrackFields {
    s32 pos[3];          /* 0x00 */
    u8 pad_0C[4];
    s32 vel[3];          /* 0x10 */
    u8 pad_1C[4];
    s16 accel[3];        /* 0x20 */
    u8 pad_26[2];
    s32 tick;            /* 0x28 */
    s16 kind;            /* 0x2C */
    u8 pad_2E[2];
    Keyframe *cursor;    /* 0x30 */
    s16 from;            /* 0x34 */
    s16 to;              /* 0x36 */
    s16 value;           /* 0x38 */
    s16 result;          /* 0x3A */
    s16 lifetime;        /* 0x3C */
    u16 rate;            /* 0x3E */
} KeyframeTrackFields;

/* from func_800C227C */
typedef struct PackedWord {
    s32 w;
} __attribute__((packed)) PackedWord;

/* from func_800C97DC */
typedef struct PosRef {
    u8 pad_000[0x220];
    u16 yaw;
    u16 pitch;
    u16 roll;
    u8 pad_226[0x26];
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    u8 pad_258[6];
    s16 unk_25E;
} PosRef;

/* from func_800C522C */
typedef struct { s16 id; s16 mul; s16 y; s16 pad; } Rec8011EB0C;

/* from func_800CB018 */
typedef struct HitPos16 {
    s32 x, y, z, w;
} HitPos16;

/* from func_800C5F64 */
typedef struct EnemyPartObj {
    /* 0x000 */ u8 pad_000[0x1A0 - 0];
    /* 0x1A0 */ s32 *asset;
    /* 0x1A4 */ u8 pad_1A4[0x1F0 - 0x1A4];
    /* 0x1F0 */ s32 pos[3];
    /* 0x1FC */ u8 pad_1FC[0x25C - 0x1FC];
    /* 0x25C */ u16 rot[3];
    /* 0x262 */ u8 pad_262[0x280 - 0x262];
    /* 0x280 */ s16 state;
    /* 0x282 */ s16 anim;
} EnemyPartObj;

/* from func_800C3AB0 */
typedef struct MechModeVars {
    u8 pad_000[0x26A];
    s16 mode;     /* 0x26A */
    s16 pad_26C[3];
    s16 prev_act; /* 0x272 */
    s16 timer;    /* 0x274 */
} MechModeVars;

/* from func_800B7690 */
typedef struct MineSpawn {
    s32 px;
    s32 py;
    s32 pz;
    s32 speed;
    s16 pitch;
    s16 yaw;
    u16 roll;
    u16 rnd;
    s32 unused[2];
} MineSpawn;

/* from func_800CA63C */
typedef struct AttachView {
    Object *obj;
    s32 x, y, z;
    u8 pad_10[0x14];
    s16 rx, ry;
    u8 pad_28[4];
    s32 dist;
    s32 unk_30;
    u8 pad_34[0xA];
    s16 unk_3E;
} AttachView;

/* from func_800C62B0 */
typedef struct SwingArmVars {
    /* 0x248 */ Object *parent;
    /* 0x24C */ s32 pivot[3];
    /* 0x258 */ s32 pad_258;
    /* 0x25C */ s16 pad_25C;
    /* 0x25E */ s16 angle;
    /* 0x260 */ s32 pad_260;
    /* 0x264 */ SVECTOR arm0;
    /* 0x26C */ SVECTOR arm1;
    /* 0x274 */ SVECTOR arm2;
    /* 0x27C */ u16 timer;
    /* 0x27E */ s16 kind;
    /* 0x280 */ s16 mode;
} SwingArmVars;

/* from func_800B84C4 */
typedef struct CrashVars {
    u8 pad_248[8];
    s16 roll_target;  /* 0x250 */
    s16 heading;      /* 0x252 */
    s16 timer;        /* 0x254 */
    s16 ground_flags; /* 0x256 */
    u8 pad_258[0x18];
    s32 ground_left;  /* 0x270 */
    s32 ground_right; /* 0x274 */
    s32 ground_diff;  /* 0x278 */
    s32 yaw_rate;     /* 0x27C */
} CrashVars;

/* from func_800C71B4 */
typedef struct SparkEmitVars {
    /* 0x248 */ Object *parent;
    /* 0x24C */ s32 base_x, base_y, base_z;
    /* 0x258 */ u8 pad_258[6];
    /* 0x25E */ s16 spark_rot;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ s16 off3[3];
    /* 0x26A */ u8 pad_26A[2];
    /* 0x26C */ s16 off2[3];
    /* 0x272 */ u8 pad_272[2];
    /* 0x274 */ s16 off1[3];
    /* 0x27A */ u8 pad_27A[2];
    /* 0x27C */ u16 pose_x;
    /* 0x27E */ u8 pad_27E[2];
    /* 0x280 */ s16 mode;
    /* 0x282 */ s16 model_offset;
} SparkEmitVars;

#endif
