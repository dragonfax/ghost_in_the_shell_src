/* ObjVars.burst_enemy: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BURST_ENEMY_H
#define OBJVARS_BURST_ENEMY_H

/* s06 burst enemy (enemy_burst_update) */
typedef struct BurstEnemyVars {
    /* 0x248 */ u8 pad_248;
    /* 0x249 */ u8 shots_left;   /* shots in the burst, counted down; 0 starts the pause */
    /* 0x24A */ u8 fire_gap;     /* frames since the last shot; a shot at 4 */
    /* 0x24B */ u8 pause_timer;  /* frames of the pause, then re-arms */
    /* 0x24C */ u8 pad_24C[0x1C];
    /* 0x268 */ s32 player_distance;     /* >= 0x801 stops the loop sound */
    /* 0x26C */ u8 pad_26C[0x10];
    /* 0x27C */ u8 sound;        /* loop sound handle, 0 when none */
} BurstEnemyVars;

#endif
