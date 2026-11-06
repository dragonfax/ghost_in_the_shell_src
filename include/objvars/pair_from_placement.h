/* ObjVars.pair_from_placement: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PAIR_FROM_PLACEMENT_H
#define OBJVARS_PAIR_FROM_PLACEMENT_H

/* obj_spawn_pair_from_placement (scripts/objkinds.py) */
typedef struct PairFromPlacementVars {
    /* 0x248 */ s16 rect_index;
    /* 0x24A */ u16 sub_index;
} PairFromPlacementVars;

#endif
