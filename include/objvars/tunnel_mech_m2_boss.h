/* ObjVars.tunnel_mech_m2_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TUNNEL_MECH_M2_BOSS_H
#define OBJVARS_TUNNEL_MECH_M2_BOSS_H

/* tunnel_mech_m2_boss_spawn (scripts/objkinds.py) */
typedef struct TunnelMechM2BossVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 fire_side;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s16 prev_state;
    /* 0x252 */ u16 angle;
    /* 0x254 */ s16 path_blend;
    /* 0x256 */ s16 path_count;
    /* 0x258 */ s16 path_index;
    /* 0x25A */ s16 unused_25A; /* only ever set to a constant in the C: never read */
    /* 0x25C */ u8 pad_25C[2];
    /* 0x25E */ s16 timer;
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 unk_268;
    /* 0x269 */ u8 pad_269[7];
    /* 0x270 */ s16 health_meter_max;
    /* 0x272 */ s16 sound;
    /* 0x274 */ s16 unk_274;
} TunnelMechM2BossVars;

#endif
