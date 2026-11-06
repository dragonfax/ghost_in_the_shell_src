/* ObjVars.bomb_mech_m7_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BOMB_MECH_M7_BOSS_H
#define OBJVARS_BOMB_MECH_M7_BOSS_H

/* bomb_mech_m7_boss_spawn (scripts/objkinds.py) */
typedef struct BombMechM7BossVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 max_health;
    /* 0x254 */ s32 sound_handle_a;
    /* 0x258 */ s32 sound_handle_b;
    /* 0x25C */ s16 turn_speed;
    /* 0x25E */ s16 unused_25E; /* only ever set to a constant in the C: never read */
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ u8 pad_264[2];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 unk_268;
} BombMechM7BossVars;

#endif
