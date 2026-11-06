/* ObjVars.part: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PART_H
#define OBJVARS_PART_H

/* s06 parts of a larger enemy: hits on the part go to the parent's body (func_800C64BC) */
typedef struct PartVars {
    /* 0x248 */ struct Object *parent;
    /* 0x24C */ u16 parent_yaw;      /* the parent's yaw at the last step (func_800C7BAC) */
    /* 0x24E */ u16 offset_y;
    /* 0x250 */ u16 offset_z;
    /* 0x252 */ u8 pad_252[2];
    /* 0x254 */ s32 unk_254;
    /* 0x258 */ s32 unk_258;         /* of the parent: subtracted from z >> 12 (func_800C3730) */
    /* 0x25C */ struct Object *body; /* of the parent: takes the damage */
    /* 0x260 */ struct Object *mirror; /* of the parent: copies the part's hit and health (func_800C5920) */
    /* 0x264 */ s16 part_slots[2];   /* of the body: one per part, indexed by the part's parent_yaw;
                                      * cleared when the part is freed (s03 func_800C3C08) */
    /* 0x268 */ s16 unk_268;         /* of the parent: < 0 skips func_800C4F34 */
    /* 0x26A */ u8 pad_26A[2];
    /* 0x26C */ u8 pad_26C[0xA];
    /* 0x276 */ s16 unk_276;         /* of the parent: cap of unk_268 */
    /* 0x278 */ s16 unk_278;
    /* 0x27A */ s16 unused_27A; /* only ever set to a constant in the C: never read */
    /* 0x27C */ s16 unk_27C;
    /* 0x27E */ s16 kind;            /* 0, 1: no damage; 3: skips func_800C4F34 */
    /* 0x280 */ s16 unk_280;
    /* 0x282 */ s16 unk_282;
    /* 0x284 */ u8 turn_rate;          /* s12 func_800C2788: turn rate toward the target */
    /* 0x285 */ u8 move_mode;          /* s12 func_800C2788: movement mode (0, 2, other) */
    /* 0x286 */ s16 unused_286; /* only ever set to a constant in the C: never read */
} PartVars;

#endif
