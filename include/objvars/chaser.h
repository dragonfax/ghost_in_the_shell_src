/* ObjVars.chaser: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_CHASER_H
#define OBJVARS_CHASER_H

/* s12 kinds that chase the player and can be hurt (func_800C204C, func_800C2A98; func_800C21C8
 * tests and clears damage) */
typedef struct ChaserVars {
    /* 0x248 */ u8 pad_248[0x14];
    /* 0x25C */ s32 target_x;
    /* 0x260 */ s32 target_yaw;
    /* 0x264 */ s32 target_z;
    /* 0x268 */ s32 target_dist;
    /* 0x26C */ u8 pad_26C[0xE];
    /* 0x27A */ s16 damage_scale; /* times the hit strength, 4.12 */
    /* 0x27C */ u8 pad_27C[9];
    /* 0x285 */ u8 mode;          /* the last script op; cleared when it dies */
    /* 0x286 */ u16 damage;       /* added up per hit */
} ChaserVars;

#endif
