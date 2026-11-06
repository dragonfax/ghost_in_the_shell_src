/* ObjVars.dmech: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_DMECH_H
#define OBJVARS_DMECH_H

/* s10 M10 dual mech (func_800C35A0); a pair kind */
typedef struct DmechVars {
    /* 0x248 */ s16 side;
    /* 0x24A */ s16 part;    /* 0 or 0x100; part bounds use part + 1 */
    /* 0x24C */ s16 unused_24C; /* only ever set to a constant in the C: never read */
    /* 0x24E */ s16 unused_24E; /* only ever set to a constant in the C: never read */
    /* 0x250 */ u8 pad_250[2];
    /* 0x252 */ s16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s32 unused_254; /* only ever set to a constant in the C: never read */
    /* 0x258 */ s32 unused_258; /* only ever set to a constant in the C: never read */
    /* 0x25C */ struct Object *partner;
    /* 0x260 */ struct Object *child;
    /* 0x264 */ s32 sound;
    /* 0x268 */ s16 unused_268; /* only ever set to a constant in the C: never read */
    /* 0x26A */ s16 timer;
} DmechVars;

#endif
