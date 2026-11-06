/* ObjVars.keyholder_fuchikoma: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_KEYHOLDER_FUCHIKOMA_H
#define OBJVARS_KEYHOLDER_FUCHIKOMA_H

/* keyholder_fuchikoma_spawn (scripts/objkinds.py) */
typedef struct KeyholderFuchikomaVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s16 target_yaw;
    /* 0x24E */ u8 pad_24E[10];
    /* 0x258 */ u16 sound_timer;
    /* 0x25A */ s16 script_state;
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ s16 unk_25E;
} KeyholderFuchikomaVars;

#endif
