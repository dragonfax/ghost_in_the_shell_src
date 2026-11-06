/* s11's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S11_TYPES_H
#define S11_TYPES_H

#include "stage_types.h"

/* from func_800BEF50 */
typedef struct PlacedRectState {
    u8 active;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 level;
    s16 fade_rate;
} PlacedRectState;

/* from func_800C4EC8 */
typedef struct TrailObj {
    u8 pad_000[0x1F0];
    s32 x;                 /* 0x1F0 */
    s32 y;                 /* 0x1F4 */
    s32 z;                 /* 0x1F8 */
    u8 pad_1FC[0x58];
    s16 index;             /* 0x254: ring slot to write next */
    u8 pad_256[6];
    TrailEntry entries[4]; /* 0x25C */
} TrailObj;

/* from func_800C3030 */
typedef struct PosHistRing {
    u8 pad_000[0x25E];
    PosHist ring[5];
} PosHistRing;

/* from func_800C713C */
typedef struct { u8 pad[0x250]; s16 a; s16 pad2; s16 b; } SteerSpawnObject;

/* from func_800BF954 */
typedef struct DirState {
    u8 pad_000[0x252];
    s16 unk_252;
} DirState;

/* from func_800C10CC */
typedef struct TrailObjPose {
    u8 pad_000[0x1F0];
    s32 x;                 /* 0x1F0 */
    s32 y;                 /* 0x1F4 */
    s32 z;                 /* 0x1F8 */
    u8 pad_1FC[0x24];
    u16 unk_220;
    s16 pitch;
    u16 unk_224;
    u8 pad_226[0x26];
    u16 yaw;
} TrailObjPose;

/* from func_800BFD68 */
typedef struct RoutePoint {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} RoutePoint;

/* from func_800C1614 */
typedef struct DamageRecord {
    s16 unk_18;
    s16 unk_1A;
    u8 kind;
    u8 sub;
    s16 unk_1E;
    s32 x, y, z;
    s16 amount;
    s16 code;
    s16 zero[4];
} DamageRecord;

/* from func_800C376C */
typedef struct SparkShot {
    /* 0x248 */ s16 id;
    /* 0x24A */ s16 pad_24A;
    /* 0x24C */ u16 yaw_base;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s16 phase_step;
    /* 0x252 */ s16 phase;
    /* 0x254 */ u16 life;
    /* 0x256 */ u8 pad_256[2];
    /* 0x258 */ s32 done;
    /* 0x25C */ s16 scale;
    /* 0x25E */ s16 sounded;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ Object *owner;
} SparkShot;

/* from func_800C3460 */
typedef struct PulseTrail {
    u8 pad_000[0x25E];
    SVECTOR trail[5];
} PulseTrail;

/* from func_800C53C0 */
typedef struct { s16 x, y, z, pad; } PosSample;

/* from func_800C84C4 */
typedef struct CamZone {
    BoundsBox box;
    s32 lights;
} CamZone;

/* from func_800B8B3C */
typedef struct CeilingBomberMat {
    s32 w[8];
} CeilingBomberMat;

/* from func_800C4BA0 */
typedef struct TrailObjectVars {
    /* 0x248 */ s16 model;
    /* 0x24A */ u8 pad_24A[6];
    /* 0x250 */ s32 flag;
    /* 0x254 */ s16 start;
    /* 0x256 */ u8 pad_256[2];
    /* 0x258 */ s16 t0;
    /* 0x25A */ s16 t1;
} TrailObjectVars;

/* from func_800C4BA0 */
typedef struct TrailObject {
    u8 pad_000[0x25C];
    struct { s16 x, y, z, pad; } pts[4];
} TrailObject;

/* the last record's unk_10/unk_12 are also the first word of D_8011A6EC (-1), which follows */
typedef struct PlacedRectDefs {
    PlacedRectDef rects[4];
    s32 asset_rest[2]; /* the rest of D_8011A6EC */
} PlacedRectDefs;

#endif
