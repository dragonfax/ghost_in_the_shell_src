/* ObjVars.tunnel_mech_laser_strike: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TUNNEL_MECH_LASER_STRIKE_H
#define OBJVARS_TUNNEL_MECH_LASER_STRIKE_H

/* tunnel_mech_laser_strike_spawn (scripts/objkinds.py) */
typedef struct TunnelMechLaserStrikeVars {
    /* 0x248 */ s16 base_model;
    /* 0x24A */ s16 model;
    /* 0x24C */ s16 progress;
    /* 0x24E */ u16 flip;
    /* 0x250 */ s16 intensity;
} TunnelMechLaserStrikeVars;

#endif
