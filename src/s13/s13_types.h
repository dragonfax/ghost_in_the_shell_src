/* s13's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S13_TYPES_H
#define S13_TYPES_H

#include "stage_types.h"

/* from func_800BCF58 */
typedef struct AngleBlendEntry {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 pad_04;
    /* 0x08 */ s32 z;
    /* 0x0C */ u8 pad_0C[4];
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ s16 count; /* sparks func_800BD060 emits */
    /* 0x1A */ s16 step; /* their spacing along x or z (axis) */
    /* 0x1C */ u16 width;
    /* 0x1E */ s16 limit;
    /* 0x20 */ s16 back;
    /* 0x22 */ s16 axis;
} AngleBlendEntry;

/* from func_800B8084 */
typedef struct StateSource {
    u8 unk_00[0x12];
    s16 state;
} StateSource;

/* from func_800B90E4 */
typedef struct {
    u8 unk_00[0x1C];
    s16 **jumps; /* 0x1C: the script's jump table */
    s16 *pc;     /* 0x20 */
    u8 unk_24[2];
    s16 unk_26;
} ObjDataView;

/* from func_800BE394 */
typedef struct Rec800BE394 {
    s16 x0;
    s16 y0;
    s16 z;
    s16 unk_6;
    s16 x1;
    s16 y1;
    u16 scale; /* 0x1000 = 1.0 in 4.12 fixed point */
    s16 unk_E;
    s16 unk_10;
    s16 unk_12;
    s32 unk_14;
    s32 unk_18;
} Rec800BE394;

/* from func_800BBE90 */
typedef struct FadeRgbState {
    u8 pad_00[0x18];
    s32 level;
    u8 pad_1C[0x10];
    s8 r;
    s8 g;
    s8 b;
    s8 a;
} FadeRgbState;

/* from func_800BCACC */
typedef struct StatusView {
    u8 pad_248[6];
    s16 unk_24E;
    u16 unk_250;
    s16 unk_252;
    u8 pad_254[2];
    u8 unk_256;
} StatusView;

/* from func_800BB0EC */
typedef struct FadeColour {
    /* 0x00 */ u8 pad_00[0x18];
    /* 0x18 */ s32 timer;
    /* 0x1C */ u8 pad_1C[0x10];
    /* 0x2C */ u8 colour[4];
} FadeColour;

/* from func_800BE2BC */
typedef struct DrawReqEntry {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
} DrawReqEntry;

/* from func_800BD9B8; s13 slot_enemy_limits record (12 bytes): enemy cap and timer, then a coordinate span (each span ends where the next starts) */
typedef struct ClampRange {
    s16 low;
    s16 high;
    s32 span_min;
    s32 span_max;
} ClampRange;

/* from func_800BBD28 */
typedef struct SpotRec {
    s32 x;          /* 0x00 */
    s32 y;          /* 0x04 */
    s32 z;          /* 0x08 */
    u8 pad_0C[0xC];
    s32 dist;       /* 0x18 */
    s32 unk_1C;     /* 0x1C */
    u8 pad_20[0xC];
    s8 scale_a;     /* 0x2C */
    s8 scale_b;     /* 0x2D */
    s8 scale_c;     /* 0x2E */
    s8 flag;        /* 0x2F */
} SpotRec;

/* from func_800BE3C8 */
typedef struct EffectObj {
    u8 unk_00[2];
    u16 base;     /* 0x02 */
    s16 active;   /* 0x04: -1 once finished */
    u8 unk_06[4];
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    CoItem co;    /* 0x14 */
} EffectObj;

/* from func_800B7E90 */
typedef struct GuardVars {
    u8 pad_248[0x1C];
    u32 flags;      /* 0x264 */
    u8 pad_268[2];
    u8 hold;        /* 0x26A */
    u8 can_blink;   /* 0x26B */
} GuardVars;

/* from func_800B7E90 */
typedef struct AiTimers {
    u8 pad_00[0x12];
    s16 target_id;   /* 0x12, compared with the owner's next_state */
    s16 mode;        /* 0x14, -2 resets to -1 */
    u8 pad_16[2];
    u16 timer;       /* 0x18 */
    s16 subtimer;    /* 0x1A */
} AiTimers;

/* from func_800BE608 */
typedef struct IdRequest {
    s32 unk_00;
    s16 flag_04;
    s16 unk_06;
    s16 field_08;
    s16 field_0A;
    s16 field_0C;
    s16 field_0E;
    s16 field_10;
    s16 field_12;
} IdRequest;

/* from func_800B922C */
typedef struct BlinkObject {
    /* 0x000 */ u8 pad_000[0x18E];
    /* 0x18E */ s16 next_state;
    /* 0x190 */ u8 pad_190[0x24E - 0x190];
    /* 0x24E */ s16 hold;
    /* 0x250 */ u8 pad_250;
    /* 0x251 */ u8 blink_on_end;
    /* 0x252 */ u8 pad_252[0x264 - 0x252];
    /* 0x264 */ s32 timer;
} BlinkObject;

/* from func_800B922C */
typedef struct BlinkLink {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ s16 flag;
} BlinkLink;

/* from func_800BD3D8 */
typedef struct { u16 value; s16 pad[5]; } Rec8011016E;

/* from func_800B80F4 */
typedef struct SwingPlacement {
    u8 pad_00[0x14];
    s16 angle;
} SwingPlacement;

#endif
