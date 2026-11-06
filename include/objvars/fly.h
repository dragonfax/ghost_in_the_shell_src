/* ObjVars.fly: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FLY_H
#define OBJVARS_FLY_H

/* s10 kinds that fly toward a height (func_800C2E0C) */
typedef struct FlyVars {
    /* 0x248 */ u8 pad_248[8];
    /* 0x250 */ s16 target_y;
    /* 0x252 */ u16 phase;
    /* 0x254 */ s32 climb_step;
    /* 0x258 */ s32 climb;     /* stored as vy */
} FlyVars;

#endif
