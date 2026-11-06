/* s09's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S09_TYPES_H
#define S09_TYPES_H

#include "stage_types.h"

/* from func_800B9D84 */
typedef struct EdgeSlot800B9D84 {
    s32 value;
    s32 other;
} EdgeSlot800B9D84;

/* from func_800B9D84 */
typedef struct PosShift {
    Vec3 before; /* 0x00; padded to 0x10 */
    s32 pad;
    Vec3 after;  /* 0x10 */
} PosShift;

/* from func_800C5858 */
typedef struct RingEffectPoint {
    s32 x, y, z, unk_0C;
} RingEffectPoint;

/* from func_800C5B48 */
typedef struct DeathPiece {
    s32 a, b, c, d;
} DeathPiece;

/* from func_800C5944 */
typedef struct EffectOffset {
    s32 x, y, z, pad;
} EffectOffset;

/* from func_800B8F0C */
typedef struct ObjSetupVars {
    s16 blend_weight;
    u16 unk_24A;
    s16 second_spark_offset_x;
    u16 second_spark_offset_z;
    u8 unk_250[6];
    u8 weight_mode;
    u8 first_spark_model_offset;
    u8 second_spark_model_offset;
    u8 unk_259;
} ObjSetupVars;

/* from func_800B8A40 */
typedef struct TuneVars {
    s16 unk_00;     /* 0x248 */
    s16 unk_02;     /* 0x24A */
    s16 unk_04;     /* 0x24C */
    s16 unk_06;     /* 0x24E */
    s16 unk_08;     /* 0x250 */
    s16 unk_0A;     /* 0x252 */
    s16 unk_0C;     /* 0x254 */
    u8 unk_0E;      /* 0x256 */
    u8 unk_0F;      /* 0x257 */
    u8 unk_10;      /* 0x258 */
    u8 pad_11[3];   /* 0x259 */
    s16 unk_14;     /* 0x25C */
    s16 unk_16;     /* 0x25E */
} TuneVars;

/* from func_800B91FC */
typedef struct ShooterVarsView {
    s16 mode;       /* 0x248: set to 0x1000 */
    s16 unk_24A;
    s16 unk_24C;    /* -0x300 */
    s16 unk_24E;
    s16 unk_250;    /* -0x180 */
    s16 unk_252;    /* -0x180 */
    s16 unk_254;
    u8 unk_256;     /* 1 */
    u8 unk_257;     /* 0xC */
    u8 unk_258;     /* 0xE */
    u8 pad_259[3];
    s16 unk_25C;    /* 1 */
    s16 unk_25E;    /* 0x30 */
} ShooterVarsView;

/* from func_800BA784 */
typedef struct ScriptReader {
    u8 pad_00[0x1C];
    u8 **op_table;
    u8 *pc;
    u8 pad_24[0x262 - 0x24];
    s16 jump_enabled;
} ScriptReader;

/* from func_800C7C38 */
typedef struct { s32 x, y, z; } Pos3;

/* from func_800C8064 */
typedef struct { s32 w[3]; } Words3_8011CDB8;

/* from func_800B7EEC */
typedef struct ElevatorVars {
    s16 timer;
    s16 ready;
    u8 unk_4[0xD];
    u8 started; /* set once the player stands in the car and looks past the limit (func_800B8CB0) */
    u8 pad_12[2];
    s16 rec;
    s16 rec_off;
} ElevatorVars;

/* from func_800C7E70 */
typedef struct SparkMount {
    s16 x, y, z;
    u16 ry;
    u16 rx;
} SparkMount;

/* from func_800C94C8 */
typedef struct SparkTrailVars {
    /* 0x248 */ s16 base;
    /* 0x24A */ s16 step;
    /* 0x24C */ u8 pad_24C[6];
    /* 0x252 */ s16 colour;
    /* 0x254 */ s16 tx, ty, tz;
    /* 0x25A */ s16 advance;
} SparkTrailVars;

/* from func_800C673C */
typedef struct PylonAsset {
    s32 words[3];
} PylonAsset;

/* from func_800C673C */
typedef struct PylonLinkWord { s16 *v; } PylonLinkWord;

/* from func_800C673C */
typedef struct PylonCount { s32 n; } PylonCount;

/* from func_800B769C */
typedef struct EnemySpawn {
    u8 pad_00[8];
    s32 x;       /* 0x08 */
    s32 y;       /* 0x0C */
    s32 z;       /* 0x10 */
    s16 kind;    /* 0x14 */
    u16 unk_16;  /* 0x16 */
} EnemySpawn;

/* from func_800C7218 */
typedef struct HomingVars {
    s16 pad_248[2];
    s16 anchor[3];          /* 0x24C */
    u8 pad_252[0x264 - 0x252];
    s16 target[3];          /* 0x264 */
    u8 pad_26A[2];
    s16 target_pitch;       /* 0x26C */
} HomingVars;

#endif
