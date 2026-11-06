/* ObjVars.rocket_drone: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_DRONE_H
#define OBJVARS_ROCKET_DRONE_H

/* rocket_drone_spawn (scripts/objkinds.py) */
typedef struct RocketDroneVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s32 base_y;
    /* 0x250 */ u16 base_yaw;
    /* 0x252 */ u16 rotor_angle;
    /* 0x254 */ u8 pad_254[4];
    /* 0x258 */ u16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ s16 unused_25A; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s32 sound_channel;
} RocketDroneVars;

#endif
