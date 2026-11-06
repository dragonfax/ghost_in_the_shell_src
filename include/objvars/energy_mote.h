/* ObjVars.energy_mote: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_ENERGY_MOTE_H
#define OBJVARS_ENERGY_MOTE_H

/* energy_mote_spawn (scripts/objkinds.py) */
typedef struct EnergyMoteVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 mode;
    /* 0x24C */ s16 state;
    /* 0x24E */ s16 shade;
    /* 0x250 */ s16 scale;
} EnergyMoteVars;

#endif
