/* ObjVars.tank: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TANK_H
#define OBJVARS_TANK_H

/* tank_spawn (scripts/objkinds.py) */
typedef struct TankVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ u16 unk_250;
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 target_x;
    /* 0x25C */ s32 target_y;
    /* 0x260 */ s32 target_z;
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ s32 prev_x;
    /* 0x26C */ s32 prev_y;
    /* 0x270 */ s32 prev_z;
    /* 0x274 */ u8 pad_274[4];
    /* 0x278 */ s32 max_sink_speed;
    /* 0x27C */ s32 unk_27C;
    /* 0x280 */ u8 pad_280[2];
    /* 0x282 */ s16 sink_timer;
    /* 0x284 */ s32 unk_284;
} TankVars;

#endif
