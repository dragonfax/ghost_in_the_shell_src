/* ObjVars.tmech: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TMECH_H
#define OBJVARS_TMECH_H

/* s02 tunnel mech boss (func_800C10DC) */
typedef struct TmechVars {
    /* 0x248 */ s16 unused_248[7]; /* only ever set to a constant in the C: never read */
    /* 0x256 */ s16 path_len;    /* entries of tunnel_mech_path before -1 */
    /* 0x258 */ s16 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25A */ u8 pad_25A[4];
    /* 0x25E */ s16 unused_25E[6]; /* only ever set to a constant in the C: never read */
    /* 0x26A */ s16 unused_26A; /* only ever set to a constant in the C: never read */
    /* 0x26C */ s16 unused_26C; /* only ever set to a constant in the C: never read */
    /* 0x26E */ s16 unused_26E; /* only ever set to a constant in the C: never read */
    /* 0x270 */ u16 health_max;
    /* 0x272 */ s16 unused_272[6]; /* only ever set to a constant in the C: never read */
} TmechVars;

#endif
