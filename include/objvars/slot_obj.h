/* ObjVars.slot_obj: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SLOT_OBJ_H
#define OBJVARS_SLOT_OBJ_H

/* slot_obj_init (scripts/objkinds.py) */
typedef struct SlotObjVars {
    /* 0x248 */ s16 slot;
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 timer;
} SlotObjVars;

#endif
