/* ObjVars.rocket_boat_spawn_side_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_BOAT_SPAWN_SIDE_OBJ_H
#define OBJVARS_ROCKET_BOAT_SPAWN_SIDE_OBJ_H

/* rocket_boat_spawn_side (scripts/objkinds.py) */
typedef struct RocketBoatSpawnSideObjVars {
    /* 0x248 */ s16 side;
    /* 0x24A */ u16 frame_counter;
    /* 0x24C */ s16 aim_yaw;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 gun_mount_z;
    /* 0x254 */ s32 gun_mount_x;
    /* 0x258 */ s32 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s32 turn_rate;
    /* 0x260 */ s32 sound_handle;
    /* 0x264 */ s32 unk_264;
    /* 0x268 */ s32 unk_268;
} RocketBoatSpawnSideObjVars;

#endif
