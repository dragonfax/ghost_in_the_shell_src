/* ObjVars.typed: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TYPED_H
#define OBJVARS_TYPED_H

/* obj_spawn_typed (scripts/objkinds.py) */
typedef struct TypedVars {
    /* 0x248 */ s16 kind;
    /* 0x24A */ s16 seek_timer;
    /* 0x24C */ s32 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u16 unused_250; /* only ever set to a constant in the C: never read */
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
} TypedVars;

#endif
