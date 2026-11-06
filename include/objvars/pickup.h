/* ObjVars.pickup: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PICKUP_H
#define OBJVARS_PICKUP_H

/* pickup_spawn (scripts/objkinds.py) */
typedef struct PickupVars {
    /* 0x248 */ s16 age;
    /* 0x24A */ s16 variant_index;
    /* 0x24C */ s16 floor_y;
    /* 0x24E */ s16 angle_y;
    /* 0x250 */ s16 angle_x;
    /* 0x252 */ s16 angle_z;
    /* 0x254 */ u16 brightness;
    /* 0x256 */ u8 pad_256[2];
    /* 0x258 */ s32 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s32 unk_25C;
} PickupVars;

#endif
