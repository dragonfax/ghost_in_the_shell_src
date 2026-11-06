/* ObjVars.walker_mech: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_WALKER_MECH_H
#define OBJVARS_WALKER_MECH_H

/* walker_mech_spawn (scripts/objkinds.py) */
typedef struct WalkerMechVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 spawn_yaw;
    /* 0x252 */ u8 pad_252[4];
    /* 0x256 */ u16 unk_256;
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 last_type;
} WalkerMechVars;

#endif
