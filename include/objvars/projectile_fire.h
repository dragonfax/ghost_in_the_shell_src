/* ObjVars.projectile_fire: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PROJECTILE_FIRE_H
#define OBJVARS_PROJECTILE_FIRE_H

/* projectile_fire_spawn (scripts/objkinds.py) */
typedef struct ProjectileFireVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 pad_24C[4];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ u8 pad_254[20];
    /* 0x268 */ s32 unused_268; /* only ever set to a constant in the C: never read */
} ProjectileFireVars;

#endif
