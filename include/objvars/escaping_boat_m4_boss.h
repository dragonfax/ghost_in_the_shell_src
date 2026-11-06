/* ObjVars.escaping_boat_m4_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ESCAPING_BOAT_M4_BOSS_H
#define OBJVARS_ESCAPING_BOAT_M4_BOSS_H

/* escaping_boat_m4_boss_spawn (scripts/objkinds.py) */
typedef struct EscapingBoatM4BossVars {
    /* 0x248 */ s16 timer;
    /* 0x24A */ u16 frame_counter;
    /* 0x24C */ s16 yaw;
    /* 0x24E */ s16 state;
    /* 0x250 */ s32 target_z;
    /* 0x254 */ s32 target_x;
    /* 0x258 */ s32 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s32 turn_rate;
    /* 0x260 */ s16 unused_260; /* only ever set to a constant in the C: never read */
    /* 0x262 */ s16 unused_262; /* only ever set to a constant in the C: never read */
    /* 0x264 */ s32 sound_handle;
    /* 0x268 */ s32 part_slot;
    /* 0x26C */ s32 heading;
} EscapingBoatM4BossVars;

#endif
