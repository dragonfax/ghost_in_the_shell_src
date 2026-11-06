/* ObjVars.laser: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_LASER_H
#define OBJVARS_LASER_H

/* s10 red laser ball (red_laser_ball_update) */
typedef struct LaserVars {
    /* 0x248 */ s32 target[3];  /* moves there while moving is set */
    /* 0x254 */ s32 unused_254; /* no use in the C */
    /* 0x258 */ s32 home[3];
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ u16 phase;      /* bobbing phase, +0x20 a step */
    /* 0x26A */ s16 timer;
    /* 0x26C */ s16 frozen;     /* nonzero: no update */
    /* 0x26E */ s16 moving;
    /* 0x270 */ s16 fired;
    /* 0x272 */ u16 sound;
} LaserVars;

#endif
