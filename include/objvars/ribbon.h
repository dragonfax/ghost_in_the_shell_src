/* ObjVars.ribbon: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_RIBBON_H
#define OBJVARS_RIBBON_H

/* s10 two-ring ribbon drawn as quads, then a spark at its head (func_800C4978) */
typedef struct RibbonVars {
    /* 0x248 */ s16 unk_248;      /* + 0xEE: the spark's unk_12 */
    /* 0x24A */ u8 pad_24A[4];
    /* 0x24E */ s16 spark_colour;      /* sets the spark colour */
    /* 0x250 */ u8 pad_250[4];
    /* 0x254 */ struct RibbonRing *ring_a;
    /* 0x258 */ struct RibbonRing *ring_b;
} RibbonVars;

#endif
