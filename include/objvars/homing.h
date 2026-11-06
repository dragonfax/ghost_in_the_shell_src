/* ObjVars.homing: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HOMING_H
#define OBJVARS_HOMING_H

/* s03 homing shot (func_800C4E1C) */
typedef struct HomingKindVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ u16 trail_time;   /* frames left dropping a trail */
    /* 0x24E */ u16 steer_time;   /* frames left turning toward the player */
    /* 0x250 */ u16 trail_toggle; /* a trail puff every other frame */
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s32 done;         /* freed at the end of the step */
} HomingKindVars;

#endif
