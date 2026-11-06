/* ObjVars.slots: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SLOTS_H
#define OBJVARS_SLOTS_H

/* two shot slots with a fading muzzle spark each (shot_slots_update, shot_muzzle_spark_spawn) */
typedef struct SlotsVars {
    /* 0x248 */ s32 rot[5];      /* rotation matrix words for the GTE */
    /* 0x25C */ u8 pad_25C[0x20];
    /* 0x27C */ s16 timer[2];    /* > 0: the slot's spark is drawn */
    /* 0x280 */ u8 pad_280[4];
    /* 0x284 */ u8 was_hit;      /* set to 1 when hit (fuchikoma_b_draw) */
    /* 0x285 */ u8 pad_285;
    /* 0x286 */ u8 fade;         /* nonzero: the spark is blended by 0x80 - fade */
    /* 0x287 */ u8 unk_287;
} SlotsVars;

#endif
