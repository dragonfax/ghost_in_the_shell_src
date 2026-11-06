/* ObjVars.homing_energy_pulse: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_HOMING_ENERGY_PULSE_H
#define OBJVARS_HOMING_ENERGY_PULSE_H

/* homing_energy_pulse_spawn (scripts/objkinds.py) */
typedef struct HomingEnergyPulseVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ u16 unused_24A; /* only ever set to a constant in the C: never read */
    /* 0x24C */ s16 life_timer;
    /* 0x24E */ u8 pad_24E[2];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ s16 trail_index;
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ s16 unk_258;
    /* 0x25A */ s16 unk_25A;
    /* 0x25C */ s16 unk_25C;
} HomingEnergyPulseVars;

#endif
