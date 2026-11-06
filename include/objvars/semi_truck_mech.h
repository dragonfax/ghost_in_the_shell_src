/* ObjVars.semi_truck_mech: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SEMI_TRUCK_MECH_H
#define OBJVARS_SEMI_TRUCK_MECH_H

/* semi_truck_mech_spawn (scripts/objkinds.py) */
typedef struct SemiTruckMechVars {
    /* 0x248 */ s32 spawn_x;
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s32 loop_sound_handle;
    /* 0x258 */ s32 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s32 part_obj_third;
    /* 0x260 */ s32 part_obj_second;
    /* 0x264 */ s32 part_obj_first;
    /* 0x268 */ s16 unk_268;
    /* 0x26A */ s16 state;
    /* 0x26C */ u8 pad_26C[8];
    /* 0x274 */ s16 unused_274; /* only ever set to a constant in the C: never read */
    /* 0x276 */ s16 unk_276;
} SemiTruckMechVars;

#endif
