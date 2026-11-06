/* ObjVars.dual_mech: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_DUAL_MECH_H
#define OBJVARS_DUAL_MECH_H

/* dual_mech_spawn (scripts/objkinds.py) */
typedef struct DualMechVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u8 pad_24A[2];
    /* 0x24C */ s16 aim_mode;
    /* 0x24E */ s16 unk_24E;
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ u8 pad_252[10];
    /* 0x25C */ s32 partner;
    /* 0x260 */ u8 pad_260[4];
    /* 0x264 */ s32 sound_handle;
    /* 0x268 */ s16 frame_counter;
} DualMechVars;

#endif
