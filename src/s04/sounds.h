/* s04's sound IDs in its stage bank (BC04.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_BOAT_ENGINE_LOOP                 0x1060 /* BC04 6/0, 1.99 s, loops; named from the code */
#define SND_ROCKET_MOTOR_LOOP                0x1061 /* BC04 6/1, 1.63 s, loops; named from the code */
#define SND_ROCKET_BOAT_LAUNCH               0x1062 /* BC04 6/2, 1.36 s; named from the code */
#define SND_WATER_PLOP                       0x1063 /* BC04 6/3, 1.11 s; heard as "water plop" */
#define SND_ROCKET_HIT_TARGET                0x1064 /* BC04 6/4, 0.45 s; named from the code */
#define SND_ROCKET_EXPLOSION                 0x1065 /* BC04 6/5, 1.62 s; named from the code */
#define SND_ROCKET_WALL_IMPACT               0x1066 /* BC04 6/6, 2.13 s; named from the code */
#define SND_S04_ROCKET_FIRE                  0x1067 /* BC04 6/7, 0.37 s; named from the code */
#define SND_MORTAR_WHISTLE                   0x106F /* BC04 6/15, 1.72 s; named from the code */
#define SND_STAGE_AMBIENCE_LOOP              0x1240 /* BC04 36/0, 1.67 s, loops; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC04 40/4, no tone; named from the code */
#define SND_JETSKI_ENGINE_LOOP               0x1462 /* BC04 70/2, 1.52 s, loops; named from the code */
#define SND_COMPUTER_GARBLE                  0x1470 /* BC04 71/0, 1.62 s; heard as "computer garble" */
#define SND_MECH_ENGINE_LOOP                 0x1531 /* BC04 83/1, 1.85 s, loops; named from the code */
#define SND_MECH_GUN_FIRE                    0x1534 /* BC04 83/4, 1.36 s; named from the code */
#define SND_S04_PROJECTILE_FIRE              0x1540 /* BC04 84/0, 0.85 s; named from the code */
#define SND_FIGHTER_JET_LOOP                 0x1541 /* BC04 84/1, 1.65 s, loops; named from the code */

#endif
