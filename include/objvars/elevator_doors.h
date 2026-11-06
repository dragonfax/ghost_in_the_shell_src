/* ObjVars.elevator_doors: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ELEVATOR_DOORS_H
#define OBJVARS_ELEVATOR_DOORS_H

/* elevator_doors_spawn (scripts/objkinds.py) */
typedef struct ElevatorDoorsVars {
    /* 0x248 */ s16 door_index;
    /* 0x24A */ u16 part_index;
    /* 0x24C */ s16 shape_row;
    /* 0x24E */ s16 grid_entry;
} ElevatorDoorsVars;

#endif
