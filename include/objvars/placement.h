/* ObjVars.placement: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PLACEMENT_H
#define OBJVARS_PLACEMENT_H

/* obj_spawn_placement (scripts/objkinds.py) */
typedef struct PlacementVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ u8 pad_24C[6];
    /* 0x252 */ s16 flag_offset;
} PlacementVars;

#endif
