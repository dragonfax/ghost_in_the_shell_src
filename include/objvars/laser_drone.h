/* ObjVars.laser_drone: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_LASER_DRONE_H
#define OBJVARS_LASER_DRONE_H

/* laser_drone_spawn (scripts/objkinds.py) */
typedef struct LaserDroneVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 base_y;
    /* 0x250 */ s16 heading_angle;
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ s32 prev_yaw;
    /* 0x25C */ s16 hit_timer;
    /* 0x25E */ s16 unk_25E;
} LaserDroneVars;

#endif
