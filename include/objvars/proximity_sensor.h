/* ObjVars.proximity_sensor: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_PROXIMITY_SENSOR_H
#define OBJVARS_PROXIMITY_SENSOR_H

/* proximity_sensor_spawn (scripts/objkinds.py) */
typedef struct ProximitySensorVars {
    /* 0x248 */ s16 zone;
    /* 0x24A */ s16 lane;
    /* 0x24C */ s16 sound_id;
} ProximitySensorVars;

#endif
