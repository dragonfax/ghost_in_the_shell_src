/* ObjVars.limb: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_LIMB_H
#define OBJVARS_LIMB_H

/* s09 two-segment limb (func_800C7724) */
typedef struct LimbVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s16 root[3];
    /* 0x252 */ s16 upper_yaw;
    /* 0x254 */ s16 upper_pitch;
    /* 0x256 */ s16 joint[3];
    /* 0x25C */ s16 lower_yaw;
    /* 0x25E */ s16 lower_pitch;
} LimbVars;

#endif
