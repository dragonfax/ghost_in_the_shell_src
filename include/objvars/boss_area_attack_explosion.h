/* ObjVars.boss_area_attack_explosion: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BOSS_AREA_ATTACK_EXPLOSION_H
#define OBJVARS_BOSS_AREA_ATTACK_EXPLOSION_H

/* boss_area_attack_explosion_spawn (scripts/objkinds.py) */
typedef struct BossAreaAttackExplosionVars {
    /* 0x248 */ s16 model_base;
    /* 0x24A */ u16 kind;
    /* 0x24C */ s16 colour;
    /* 0x24E */ s16 age;
    /* 0x250 */ s32 size;
    /* 0x254 */ s32 grow_speed;
    /* 0x258 */ s32 grow_accel;
    /* 0x25C */ s16 unk_25C;
} BossAreaAttackExplosionVars;

#endif
