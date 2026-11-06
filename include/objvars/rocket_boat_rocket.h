/* ObjVars.rocket_boat_rocket: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_BOAT_ROCKET_H
#define OBJVARS_ROCKET_BOAT_ROCKET_H

/* rocket_boat_rocket_spawn (scripts/objkinds.py) */
typedef struct RocketBoatRocketVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 rocket_type;
    /* 0x24C */ s16 trace_flags;
    /* 0x24E */ s16 draw_countdown;
    /* 0x250 */ s16 spawn_x;
    /* 0x252 */ s16 spawn_y;
    /* 0x254 */ s16 spawn_z;
    /* 0x256 */ s16 random_seed_a;
    /* 0x258 */ s16 random_seed_b;
    /* 0x25A */ u8 pad_25A[2];
    /* 0x25C */ s32 launch_vel_x;
    /* 0x260 */ s32 launch_vel_y;
    /* 0x264 */ s32 launch_vel_z;
} RocketBoatRocketVars;

#endif
