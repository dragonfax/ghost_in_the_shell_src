/* ObjVars.supermech_m12_boss: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SUPERMECH_M12_BOSS_H
#define OBJVARS_SUPERMECH_M12_BOSS_H

/* supermech_m12_boss_spawn (scripts/objkinds.py) */
typedef struct SupermechM12BossVars {
    /* 0x248 */ u8 pad_248[12];
    /* 0x254 */ s16 shot_counter;
    /* 0x256 */ u8 pad_256[2];
    /* 0x258 */ s16 max_health;
    /* 0x25A */ s16 unused_25A; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s16 unused_25C; /* only ever set to a constant in the C: never read */
    /* 0x25E */ s16 unused_25E; /* only ever set to a constant in the C: never read */
    /* 0x260 */ u8 pad_260[6];
    /* 0x266 */ s16 unused_266; /* only ever set to a constant in the C: never read */
} SupermechM12BossVars;

#endif
