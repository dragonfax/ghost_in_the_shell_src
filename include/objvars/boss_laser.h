/* ObjVars.boss_laser: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BOSS_LASER_H
#define OBJVARS_BOSS_LASER_H

/* boss_laser_spawn (scripts/objkinds.py) */
typedef struct BossLaserVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 kind;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ s32 parent;
    /* 0x254 */ s16 hit_x;
    /* 0x256 */ u16 hit_y;
    /* 0x258 */ u16 hit_z;
    /* 0x25A */ s16 unused_25A; /* only ever set to a constant in the C: never read */
    /* 0x25C */ s16 beam_width;
    /* 0x25E */ s16 spark_life;
    /* 0x260 */ s32 sound_channel;
} BossLaserVars;

#endif
