/* ObjVars.copy: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_COPY_H
#define OBJVARS_COPY_H

/* obj_spawn_copy (scripts/objkinds.py) */
typedef struct CopyVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unused_250; /* only ever set to a constant in the C: never read */
} CopyVars;

#endif
