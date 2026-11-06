/* ObjVars.timed_effect: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TIMED_EFFECT_H
#define OBJVARS_TIMED_EFFECT_H

/* timed_effect_spawn (scripts/objkinds.py) */
typedef struct TimedEffectVars {
    /* 0x248 */ s16 progress;
    /* 0x24A */ u16 level;
    /* 0x24C */ u8 pad_24C[2];
    /* 0x24E */ u16 phase;
    /* 0x250 */ u16 rise_step;
    /* 0x252 */ u16 fall_step;
    /* 0x254 */ s32 sound_handle;
} TimedEffectVars;

#endif
