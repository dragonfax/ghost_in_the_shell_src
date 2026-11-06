/* ObjVars.timer_tail: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TIMER_TAIL_H
#define OBJVARS_TIMER_TAIL_H

/* timer_tail_spawn (scripts/objkinds.py) */
typedef struct TimerTailVars {
    /* 0x248 */ s32 wander_target_x;
    /* 0x24C */ s32 wander_target_y;
    /* 0x250 */ s32 wander_target_z;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 home_x;
    /* 0x25C */ s32 home_y;
    /* 0x260 */ s32 home_z;
    /* 0x264 */ u8 pad_264[16];
    /* 0x274 */ s16 unk_274;
} TimerTailVars;

#endif
