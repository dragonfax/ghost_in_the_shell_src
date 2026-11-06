/* ObjVars.tunnel_mech_laser: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TUNNEL_MECH_LASER_H
#define OBJVARS_TUNNEL_MECH_LASER_H

/* tunnel_mech_laser_spawn (scripts/objkinds.py) */
typedef struct TunnelMechLaserVars {
    /* 0x248 */ u8 pad_248[4];
    /* 0x24C */ s16 intensity;
    /* 0x24E */ s16 toggle;
    /* 0x250 */ s16 model_base;
    /* 0x252 */ u16 unused_252; /* only ever set to a constant in the C: never read */
    /* 0x254 */ s16 timer;
    /* 0x256 */ s16 segment_count;
    /* 0x258 */ s16 tail_scale;
    /* 0x25A */ s16 unk_25A;
    /* 0x25C */ s16 wave_phase;
    /* 0x25E */ u8 pad_25E[8];
    /* 0x266 */ s16 unused_266; /* only ever set to a constant in the C: never read */
} TunnelMechLaserVars;

#endif
