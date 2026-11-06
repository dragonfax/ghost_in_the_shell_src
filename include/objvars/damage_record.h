/* ObjVars.damage_record: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_DAMAGE_RECORD_H
#define OBJVARS_DAMAGE_RECORD_H

/* damage_record_spawn (scripts/objkinds.py) */
typedef struct DamageRecordVars {
    /* 0x248 */ s16 bob_phase;
    /* 0x24A */ s16 unk_24A;
    /* 0x24C */ s16 saved_yaw;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ u16 steer_level;
    /* 0x252 */ s16 unk_252;
    /* 0x254 */ s16 unused_254; /* only ever set to a constant in the C: never read */
    /* 0x256 */ s16 max_health;
    /* 0x258 */ u16 timer;
    /* 0x25A */ u8 pad_25A[2];
    /* 0x25C */ s32 sound_id;
} DamageRecordVars;

#endif
