/* s07's sound IDs in its stage bank (BC07.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_OBJECT_EXPLOSION                 0x10C4 /* BC07 12/4, 0.26 s; named from the code */
#define SND_DOOR_OPEN                        0x10C8 /* BC07 12/8, 0.88 s; heard as "door open" */
#define SND_DOOR_CLOSE                       0x10C9 /* BC07 12/9, 0.32 s; heard as "door close" */
#define SND_ZRRRT                            0x10CA /* BC07 12/10, 0.85 s; heard as "zrrrt" */
#define SND_HELICOPTER_BOMB_LAUNCH           0x10D3 /* BC07 13/3, 0.97 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC07 40/4, no tone; named from the code */
#define SND_HOLLOW_WIND                      0x12A2 /* BC07 42/2, 2.98 s, loops; heard as "hollow wind" */
#define SND_HOLLOW_WIND_LOOP                 0x12A3 /* BC07 42/3, 5.31 s, loops; named from the code */
#define SND_FALL_LAUNCH                      0x13F1 /* BC07 63/1, 0.77 s; named from the code */
#define SND_LANDING_THUD                     0x13F2 /* BC07 63/2, 0.68 s; named from the code */
#define SND_SHOT_FIRE_ALT_B                  0x1410 /* BC07 65/0, 0.06 s; named from the code */
#define SND_MECH_STEP                        0x1411 /* BC07 65/1, 0.48 s; named from the code */
#define SND_S07_ENEMY_FIRE                   0x1430 /* BC07 67/0, 1.04 s; named from the code */
#define SND_MACHINE_GUN_FIRE                 0x1440 /* BC07 68/0, 1.55 s, loops; heard as "machine gun fire" */
#define SND_MUZZLE_FIRE                      0x1441 /* BC07 68/1, 0.8 s; named from the code */
#define SND_TRAIN_LOOP                       0x1442 /* BC07 68/2, 2.07 s, loops; named from the code */
#define SND_TRAIN_LOOP_ALT                   0x1443 /* BC07 68/3, 2.24 s, loops; named from the code */
#define SND_VREEEE                           0x14B0 /* BC07 75/0, 1.7 s, loops; heard as "vreeee" */
#define SND_STATIONARY_ROCKET_LAUNCH         0x14B1 /* BC07 75/1, 0.83 s; named from the code */
#define SND_STATIONARY_LASER_LOOP            0x14B3 /* BC07 75/3, 1.59 s, loops; named from the code */
#define SND_HELICOPTER_ROTOR_LOOP            0x1510 /* BC07 81/0, 1.63 s, loops; named from the code */

#endif
