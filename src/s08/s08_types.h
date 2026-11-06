/* s08's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S08_TYPES_H
#define S08_TYPES_H

#include "stage_types.h"

/* from func_800BF110 */
typedef struct ObjAngleRec {
    s16 pos[3];
    s16 ang[3];
} ObjAngleRec;

/* from func_800BF110 */
typedef struct ObjAngleTable {
    s32 unk_00;
    ObjAngleRec rec[1];
} ObjAngleTable;

/* from func_800BF110 */
typedef struct ObjAngleTableSlot {
    ObjAngleTable *table;
    u8 pad_04[0x18];
} ObjAngleTableSlot;

/* from func_800C0DD8 */
typedef struct TurnHoverVars {
    u8 pad_248[0x1C];
    s32 unk_264;
    u8 pad_268[0x12];
    s16 unk_27A;
} TurnHoverVars;

/* from func_800BFCC0 */
typedef struct ScriptBranchCtx {
    u8 pad_00[0x1C];
    /* 0x1C */ s32 *targets;
    /* 0x20 */ s16 *pc;
    u8 pad_24[0x248 - 0x24];
    /* 0x248 */ s16 *expected;
} ScriptBranchCtx;

/* from func_800BDA80 */
typedef struct RollingDoorState {
    s32 active;
    s32 unk4;
    s16 scale;
    s16 value;
} RollingDoorState;

/* from func_800C25A4 */
struct Timer8 {
    s16 timer;
    s16 cnt;
    u16 ang;
    s16 val;
};

/* from func_800C4C98 */
typedef struct PhaseTimer {
    s16 flag;
    u16 tick;
    s16 phase;
} PhaseTimer;

/* from func_800C59E4 */
typedef struct CueState {
    s16 active;
    u16 tick;
    s16 stage;
} CueState;

/* from func_800C41C8 */
typedef struct BlinkState {
    s16 unk_0;
    s16 counter;  /* 0x02: frames in the current phase */
    s16 state;    /* 0x04: 0 random delay, 1 toggling, 2 idle */
    s16 value;    /* 0x06: toggled 0/1 in state 1, random in state 0 */
} BlinkState;

/* from func_800C4080 */
typedef struct BlinkOffset {
    Vec3 pos;
    s32 pad;
} BlinkOffset;

/* from boss_death_update */
typedef struct BossDeathVars {
    u8 pad_00[0x248];
    s32 fx_arg;
    s32 state;
    s32 timer;
} BossDeathVars;

/* from func_800C2688 */
struct LaserCtl {
    s16 flag;
    s16 count;
    s16 state;
};

/* from func_800C005C */
typedef struct BossM8Vars {
    /* 0x248 */ u8 pad_248[6];
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ u8 pad_250[0x14];
    /* 0x264 */ s32 circle_radius;      /* radius of the circling offset */
    /* 0x268 */ u8 pad_268[8];
    /* 0x270 */ s32 unk_270;
    /* 0x274 */ u8 pad_274[6];
    /* 0x27A */ s16 circle_angle;      /* angle of the circling offset */
} BossM8Vars;

/* from func_800C1B2C */
typedef struct ObjLinkValue { s16 *value; } ObjLinkValue;

/* from func_800C3730 */
typedef struct ShotTraceFields {
    /* 0x000 */ u8 pad_000[0x278];
    /* 0x278 */ s16 phase;
    /* 0x27A */ s16 timer;
    /* 0x27C */ s16 alpha;
    /* 0x27E */ u16 wobble;
    /* 0x280 */ s16 base_y;
    /* 0x282 */ u16 angle;
} ShotTraceFields;

/* from func_800C0B8C */
typedef union GteMatrix {
    s16 h[16];
    s32 w[8];
} GteMatrix;

#endif
