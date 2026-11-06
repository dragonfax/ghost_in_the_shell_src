/* ObjVars.enemy: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENEMY_H
#define OBJVARS_ENEMY_H

/* shooting enemies (func_800B8E08, func_800B915C, snd_move) */
typedef struct EnemyVars {
    /* 0x248 */ s32 mode;
    /* 0x24C */ u8 unk_24C[4];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ s16 sound_channel[2]; /* > 0: playing */
    /* 0x258 */ s32 unk_258;
    /* 0x25C */ s16 unk_25C;
    /* 0x25E */ s16 unk_25E;
    /* 0x260 */ u8 unk_260[6];
    /* 0x266 */ s16 unk_266;
    /* 0x268 */ u8 unk_268;
    /* 0x269 */ u8 unk_269;
    /* 0x26A */ s16 target_yaw;  /* func_800B9D6C, func_800B9F78 */
    /* 0x26C */ s16 walk_state;  /* > 0 heading back, < 0 returning, 0 free (func_800B9F78) */
    /* 0x26E */ u8 unk_26E[2];
    /* 0x270 */ s32 sound;       /* loop sound handle; SOUND_PENDING: start at the next shot */
    /* 0x274 */ s16 unk_274;
    /* 0x276 */ u8 unk_276[6];
    /* 0x27C */ s32 shot_timer;
    /* 0x280 */ s32 shots_left;
    /* 0x284 */ u8 pad_284[2];
    /* 0x286 */ u8 throttle;      /* 0..0x80, fuchikoma_chase_update */
    /* 0x287 */ u8 brake;      /* 0..0x80: scales the speed limit down (fuchikoma_chase_update) */
} EnemyVars;

#endif
