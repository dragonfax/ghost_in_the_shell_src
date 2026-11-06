/* ObjVars.dreadnought_m11_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_DREADNOUGHT_M11_BOSS_H
#define OBJVARS_DREADNOUGHT_M11_BOSS_H

/* dreadnought_m11_boss_spawn (scripts/objkinds.py) */
typedef struct DreadnoughtM11BossVars {
    /* 0x248 */ s16 max_health;
    /* 0x24A */ u16 frame_toggle;
    /* 0x24C */ s16 body_yaw;
    /* 0x24E */ s16 speed_step_timer;
    /* 0x250 */ s16 target_speed;
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s16 turn_around;
    /* 0x256 */ u16 prev_turn_around;
    /* 0x258 */ u16 muzzle_fx_pending;
    /* 0x25A */ s16 burst_timer;
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ s16 unk_25E;
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 unk_268;
} DreadnoughtM11BossVars;

#endif
