/* ObjVars.rocket_boat: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ROCKET_BOAT_H
#define OBJVARS_ROCKET_BOAT_H

/* rocket_boat_spawn (scripts/objkinds.py) */
typedef struct RocketBoatVars {
    /* 0x248 */ s16 asset;
    /* 0x24A */ u16 mode;
    /* 0x24C */ s16 trace_flags;
    /* 0x24E */ u16 angle;
    /* 0x250 */ u16 fall_counter;
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s32 dir_x;
    /* 0x258 */ s32 dir_y;
    /* 0x25C */ s32 dir_z;
} RocketBoatVars;

#endif
