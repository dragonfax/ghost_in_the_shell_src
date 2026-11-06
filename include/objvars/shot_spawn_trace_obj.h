/* ObjVars.shot_spawn_trace_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SHOT_SPAWN_TRACE_OBJ_H
#define OBJVARS_SHOT_SPAWN_TRACE_OBJ_H

/* shot_spawn_trace (scripts/objkinds.py) */
typedef struct ShotSpawnTraceObjVars {
    /* 0x248 */ s32 kind;
    /* 0x24C */ s32 age;
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
} ShotSpawnTraceObjVars;

#endif
