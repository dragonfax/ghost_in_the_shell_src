/* ObjVars.laser_barrier_boat: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_LASER_BARRIER_BOAT_H
#define OBJVARS_LASER_BARRIER_BOAT_H

/* laser_barrier_boat_spawn, laser_barrier_boat_spawn_placed (scripts/objkinds.py) */
typedef struct LaserBarrierBoatKindVars {
    /* 0x248 */ s16 unused_248; /* only ever set to a constant in the C: never read */
    /* 0x24A */ u16 state;
    /* 0x24C */ s32 unk_24C;
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s32 unused_254; /* only ever set to a constant in the C: never read */
    /* 0x258 */ s32 left_barrier;
    /* 0x25C */ s32 right_barrier;
    /* 0x260 */ s32 unk_260;
    /* 0x264 */ u8 pad_264[4];
    /* 0x268 */ u8 unused_268; /* only ever set to a constant in the C: never read */
} LaserBarrierBoatKindVars;

#endif
