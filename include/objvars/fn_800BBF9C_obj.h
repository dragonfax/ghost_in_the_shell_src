/* ObjVars.fn_800BBF9C_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_FN_800BBF9C_OBJ_H
#define OBJVARS_FN_800BBF9C_OBJ_H

/* grenade_fuchikoma_spawn (scripts/objkinds.py) */
typedef struct Fn800BBF9CObjVars {
    /* 0x248 */ s16 initial_pitch;
    /* 0x24A */ u16 initial_yaw;
    /* 0x24C */ s16 initial_roll;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ u8 pad_254[6];
    /* 0x25A */ s16 unk_25A;
} Fn800BBF9CObjVars;

#endif
