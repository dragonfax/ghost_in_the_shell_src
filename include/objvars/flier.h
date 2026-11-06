/* ObjVars.flier: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FLIER_H
#define OBJVARS_FLIER_H

/* s06 func_800B95A8: flier that follows a flow and hugs the floor */
typedef struct FlierKindVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ s16 range;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ s16 chase_timer;  /* > 0: chases the player, -1 a step */
    /* 0x252 */ u16 rotor;        /* -0x40 a step */
    /* 0x254 */ u8 pad_254[2];
    /* 0x256 */ s16 grounded;     /* 1: a floor probe touched */
    /* 0x258 */ s32 pitch;
    /* 0x25C */ u8 pad_25C[8];
    /* 0x264 */ s32 unk_264;
    /* 0x268 */ u8 pad_268[8];
    /* 0x270 */ s32 floor_y[2];   /* ahead, behind */
    /* 0x278 */ s32 floor_slope;
    /* 0x27C */ u8 pad_27C[4];
    /* 0x280 */ Flow flow;
} FlierKindVars;

#endif
