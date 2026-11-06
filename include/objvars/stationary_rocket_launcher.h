/* ObjVars.stationary_rocket_launcher: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_STATIONARY_ROCKET_LAUNCHER_H
#define OBJVARS_STATIONARY_ROCKET_LAUNCHER_H

/* stationary_rocket_launcher_spawn (scripts/objkinds.py) */
typedef struct StationaryRocketLauncherVars {
    /* 0x248 */ s16 aim_pitch;
    /* 0x24A */ u16 aim_yaw;
    /* 0x24C */ s16 aim_roll;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 target;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 sound_channel;
} StationaryRocketLauncherVars;

#endif
