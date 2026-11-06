/* ObjVars.projectile: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PROJECTILE_H
#define OBJVARS_PROJECTILE_H

/* obj_spawn_projectile, projectile_spawn (scripts/objkinds.py) */
typedef struct ProjectileVars {
    /* 0x248 */ s32 done;
    /* 0x24C */ s32 sound;
    /* 0x250 */ u16 countdown;
    /* 0x252 */ u16 toggle;
} ProjectileVars;

#endif
