/* ObjVars.tunnel_mech_shot: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TUNNEL_MECH_SHOT_H
#define OBJVARS_TUNNEL_MECH_SHOT_H

/* tunnel_mech_shot_spawn (scripts/objkinds.py) */
typedef struct TunnelMechShotVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 pad_24C[2];
    /* 0x24E */ s16 timer;
    /* 0x250 */ s32 origin_x;
    /* 0x254 */ s32 origin_y;
    /* 0x258 */ s32 origin_z;
    /* 0x25C */ s16 unk_25C;
} TunnelMechShotVars;

#endif
