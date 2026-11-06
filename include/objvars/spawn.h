/* ObjVars.spawn: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SPAWN_H
#define OBJVARS_SPAWN_H

/* enemies placed by func_800B769C (s09) */
typedef struct SpawnKindVars {
    /* 0x248 */ u8 pad_248[0x11];
    /* 0x259 */ u8 unk_259;
    /* 0x25A */ u8 unk_25A;
} SpawnKindVars;

#endif
