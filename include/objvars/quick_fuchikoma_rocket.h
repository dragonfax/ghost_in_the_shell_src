/* ObjVars.quick_fuchikoma_rocket: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_QUICK_FUCHIKOMA_ROCKET_H
#define OBJVARS_QUICK_FUCHIKOMA_ROCKET_H

/* quick_fuchikoma_rocket_spawn (scripts/objkinds.py) */
typedef struct QuickFuchikomaRocketVars {
    /* 0x248 */ s32 muzzle_flash_pending;
    /* 0x24C */ s32 spawn_x;
    /* 0x250 */ s32 spawn_y;
    /* 0x254 */ s32 spawn_z;
    /* 0x258 */ u8 pad_258[4];
    /* 0x25C */ s32 dir_x;
    /* 0x260 */ s32 dir_y;
    /* 0x264 */ s32 dir_z;
    /* 0x268 */ u8 pad_268[4];
    /* 0x26C */ s32 target_x;
    /* 0x270 */ s32 target_y;
    /* 0x274 */ s32 target_z;
    /* 0x278 */ u8 pad_278[4];
    /* 0x27C */ s32 flight_timer;
} QuickFuchikomaRocketVars;

#endif
