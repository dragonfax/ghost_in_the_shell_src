/* ObjVars.at_pos: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_AT_POS_H
#define OBJVARS_AT_POS_H

/* obj_spawn_at_pos (scripts/objkinds.py) */
typedef struct AtPosVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 unk_24A;
} AtPosVars;

#endif
