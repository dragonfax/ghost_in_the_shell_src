/* ObjVars.with_matrix: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_WITH_MATRIX_H
#define OBJVARS_WITH_MATRIX_H

/* obj_spawn_with_matrix (scripts/objkinds.py) */
typedef struct WithMatrixVars {
    /* 0x248 */ u8 pad_248[52];
    /* 0x27C */ s16 glow_power;
    /* 0x27E */ u8 pad_27E[4];
    /* 0x282 */ s16 unused_282; /* only ever set to a constant in the C: never read */
} WithMatrixVars;

#endif
