/* ObjVars.spin_laser: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPIN_LASER_H
#define OBJVARS_SPIN_LASER_H

/* s12 laser ball with a spin-up (func_800BCC5C) */
typedef struct SpinLaserVars {
    /* 0x248 */ s32 target[3];  /* moves there while moving is set */
    /* 0x254 */ u8 pad_254[0x14];
    /* 0x268 */ u16 phase;      /* bobbing phase, +0x20 a step */
    /* 0x26A */ u16 timer;
    /* 0x26C */ s16 frozen;     /* nonzero: no update */
    /* 0x26E */ s16 spin;       /* 0: aims at the player, 0x1000: fires */
    /* 0x270 */ s16 spin_step;  /* added to spin; negated at 0x1400 */
    /* 0x272 */ s16 pad_272;
    /* 0x274 */ s16 moving;
    /* 0x276 */ s16 fired;
    /* 0x278 */ u16 sound;
} SpinLaserVars;

#endif
