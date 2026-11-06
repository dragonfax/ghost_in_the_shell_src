/* ObjVars.stage_controller: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_STAGE_CONTROLLER_H
#define OBJVARS_STAGE_CONTROLLER_H

/* stage_controller_spawn (scripts/objkinds.py) */
typedef struct StageControllerVars {
    /* 0x248 */ s16 door_index;
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ s16 timer;
} StageControllerVars;

#endif
