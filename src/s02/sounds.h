/* s02's sound IDs in its stage bank (BC02.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_MECH_FOOTSTEP                    0x1020 /* BC02 2/0, 0.84 s; named from the code */
#define SND_TUNNEL_MECH_STEP                 0x1021 /* BC02 2/1, 0.62 s; named from the code */
#define SND_MECH_DESTROY_EXPLOSION           0x1023 /* BC02 2/3, 1.74 s; named from the code */
#define SND_LASER_BEAM_LOOP                  0x1025 /* BC02 2/5, 1.74 s, loops; named from the code */
#define SND_LASER_IMPACT_LOOP                0x1026 /* BC02 2/6, 1.6 s, loops; named from the code */
#define SND_MECH_CANNON_FIRE                 0x1027 /* BC02 2/7, 1.64 s; named from the code */
#define SND_MECH_FIRE_LOOP                   0x1030 /* BC02 3/0, 1.7 s, loops; named from the code */
#define SND_TUNNEL_MECH_SHOT_IMPACT          0x1034 /* BC02 3/4, 0.54 s; named from the code */
#define SND_TUNNEL_MECH_FIRE                 0x1035 /* BC02 3/5, 1.21 s; named from the code */
#define SND_WARNING_ALARM_LOOP               0x1201 /* BC02 32/1, 2.74 s, loops; named from the code */
#define SND_NIGHT_VISION_OFF                 0x1203 /* BC02 32/3, 0.25 s; named from the code */
#define SND_NIGHT_VISION_ON                  0x1204 /* BC02 32/4, 0.19 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC02 40/4, no tone; named from the code */
#define SND_STAGE_ENEMY_FIRE                 0x1490 /* BC02 73/0, 0.77 s; named from the code */
#define SND_ROCKET_DRONE_LOOP                0x1492 /* BC02 73/2, 1.65 s, loops; named from the code */
#define SND_ENEMY_BEAM_LOOP                  0x1560 /* BC02 86/0, 1.51 s, loops; named from the code */
#define SND_ENEMY_BEAM_FIRE_LOOP             0x1561 /* BC02 86/1, 1.73 s, loops; named from the code */

#endif
