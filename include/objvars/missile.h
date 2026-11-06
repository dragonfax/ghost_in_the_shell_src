/* ObjVars.missile: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_MISSILE_H
#define OBJVARS_MISSILE_H

/* s11 homing missile (func_800C8058) */
typedef struct MissileVars {
    /* 0x248 */ u8 pad_248[2];
    /* 0x24A */ u16 steer_time;  /* frames left steering at the player */
    /* 0x24C */ s32 done;        /* hit something: freed this frame */
    /* 0x250 */ u16 trail;       /* toggles; smoke on every other frame */
} MissileVars;

#endif
