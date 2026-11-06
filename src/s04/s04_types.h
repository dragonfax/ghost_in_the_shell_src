/* s04's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S04_TYPES_H
#define S04_TYPES_H

#include "stage_types.h"

/* from func_800BFAB4 */
typedef struct SeqReader {
    u8 pad_00[0x1C];
    u8 **table;
    u8 *cursor;
    u8 pad_24[0x208];
    s16 wanted;
} SeqReader;

/* from func_800C5B18 */
typedef struct BossFxParams {
    s32 x;
    s32 y;
    s32 value;
} BossFxParams;

/* from func_800B7308 */
typedef struct ScriptJumpState {
    u8 pad_00[0x1C];
    /* 0x1C */ s32 *targets;
    /* 0x20 */ s16 *pc;
    u8 pad_24[0x1F8 - 0x24];
    /* 0x1F8 */ s32 z;
} ScriptJumpState;

/* from func_800B7F18 */
typedef struct TraceVec {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} TraceVec;

/* from func_800B74B0 */
typedef struct FlyPairVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 hold_a;
    /* 0x24C */ s16 hold_b;
    /* 0x24E */ s16 timer;
    /* 0x250 */ s32 off_a;
    /* 0x254 */ s32 off_b;
    /* 0x258 */ Object *part_a;
    /* 0x25C */ Object *part_b;
} FlyPairVars;

/* from rocket_boat_rocket_2_draw */
typedef struct RocketBoatRocketParams {
    s16 base;
    s16 unk_02;
    s16 unk_04;
    s16 speed;
} RocketBoatRocketParams;

/* from func_800BBA10 */
typedef struct SpawnVars {
    s16 unk_248;
    s16 unk_24A;
    s32 unk_24C;
    s16 unk_250;
    s16 unk_252;
    s16 unk_254;
    s16 initial_yaw;
    s16 unk_258;
    s16 unk_25A;
    s16 unk_25C;
    u8 pad_25E[2];
    s32 initial_y;
    s16 unk_264;
    u8 pad_266[8];
    s16 unk_26E;
    s16 range;
    s16 unk_272;
    s16 player_left_flag;
    u8 pad_276[2];
    s32 sound_handle;
} SpawnVars;

/* from func_800BBA10 */
typedef struct SpawnPlace {
    u8 pad_00[0x1A];
    s16 unk_1A;
} SpawnPlace;

/* from func_800B7668 */
typedef struct MinePairVars {
    u8 pad_248[2];
    s16 unk_24A;
    s16 unk_24C;
    u16 unk_24E;
    s32 partner_a_offset;
    s32 partner_b_offset;
    Object *partner_a; /* 0x258 */
    Object *partner_b; /* 0x25C */
    u8 pad_260[8];
    u8 spawned; /* 0x268 */
} MinePairVars;

/* from func_800C261C */
typedef struct ObjModelSlots {
    s32 w[3];
} ObjModelSlots;

/* from laser_barrier_boat_draw */
typedef struct LaserBarrierBoatVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 left_state;  /* 1: free the left emitter, 2: freed */
    /* 0x24C */ s16 right_state; /* same for the right emitter */
    /* 0x24E */ s16 beam;        /* beam strength, 0: off */
    /* 0x250 */ u8 pad_250[8];
    /* 0x258 */ Object *left;
    /* 0x25C */ Object *right;
} LaserBarrierBoatVars;

#endif
