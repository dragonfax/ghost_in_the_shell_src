/* ObjVars.at_point: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_AT_POINT_H
#define OBJVARS_AT_POINT_H

/* obj_spawn_at_point (scripts/objkinds.py) */
typedef struct AtPointVars {
    /* 0x248 */ s32 progress;
    /* 0x24C */ s32 base_pool_id;
    /* 0x250 */ s32 pool_id;
    /* 0x254 */ s32 flicker_toggle;
} AtPointVars;

#endif
