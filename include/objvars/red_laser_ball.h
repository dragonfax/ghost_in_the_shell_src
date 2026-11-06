/* ObjVars.red_laser_ball: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_RED_LASER_BALL_H
#define OBJVARS_RED_LASER_BALL_H

/* red_laser_ball_spawn (scripts/objkinds.py) */
typedef struct RedLaserBallVars {
    /* 0x248 */ s32 target_x;
    /* 0x24C */ s32 target_y;
    /* 0x250 */ s32 target_z;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 spawn_x;
    /* 0x25C */ s32 spawn_y;
    /* 0x260 */ s32 spawn_z;
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ u8 unk_268;
    /* 0x269 */ u8 pad_269[9];
    /* 0x272 */ u16 sound;
} RedLaserBallVars;

#endif
