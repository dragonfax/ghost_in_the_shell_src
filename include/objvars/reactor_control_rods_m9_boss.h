/* ObjVars.reactor_control_rods_m9_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_REACTOR_CONTROL_RODS_M9_BOSS_H
#define OBJVARS_REACTOR_CONTROL_RODS_M9_BOSS_H

/* reactor_control_rods_m9_boss_spawn (scripts/objkinds.py) */
typedef struct ReactorControlRodsM9BossVars {
    /* 0x248 */ s16 burst_timer;
    /* 0x24A */ s16 fire_timer;
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s32 engine_speed;
    /* 0x254 */ s32 engine_accel;
    /* 0x258 */ s32 engine_speed_max;
    /* 0x25C */ s32 fly_speed_max;
    /* 0x260 */ s32 fly_speed;
    /* 0x264 */ s32 fly_accel;
    /* 0x268 */ s32 unk_268;
    /* 0x26C */ s32 unk_26C;
    /* 0x270 */ u16 base_pitch;
} ReactorControlRodsM9BossVars;

#endif
