/* ObjVars.cam_path_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CAM_PATH_OBJ_H
#define OBJVARS_CAM_PATH_OBJ_H

/* cam_path_obj_spawn (scripts/objkinds.py) */
typedef struct CamPathObjVars {
    /* 0x248 */ s32 unused_248; /* only ever set to a constant in the C: never read */
} CamPathObjVars;

#endif
