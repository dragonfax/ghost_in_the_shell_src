/* ObjVars.helicopter2: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HELICOPTER2_H
#define OBJVARS_HELICOPTER2_H

/* helicopter2_spawn (scripts/objkinds.py) */
typedef struct Helicopter2Vars {
    /* 0x248 */ s16 draw_toggle;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ u16 yaw;
    /* 0x252 */ u16 rotor_angle;
    /* 0x254 */ s16 unk_254;
    /* 0x256 */ u16 unk_256;
    /* 0x258 */ s32 prev_yaw;
    /* 0x25C */ s16 unused_25C; /* only ever set to a constant in the C: never read */
    /* 0x25E */ s16 timer;
} Helicopter2Vars;

#endif
