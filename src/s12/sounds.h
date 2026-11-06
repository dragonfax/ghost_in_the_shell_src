/* s12's sound IDs in its stage bank (BC12.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_SPARK_BURST                      0x116C /* BC12 22/12, 0.58 s; named from the code */
#define SND_S12_MECH_MOVE_START              0x1173 /* BC12 23/3, 0.41 s; named from the code */
#define SND_FALL_START                       0x117A /* BC12 23/10, 1.03 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC12 40/4, no tone; named from the code */
#define SND_HOLLOW_WIND_LOOP                 0x1340 /* BC12 52/0, 2.63 s, loops; named from the code */
#define SND_HOLLOW_WIND_LOOP_ALT             0x1341 /* BC12 52/1, 3.94 s, loops; named from the code */
#define SND_ALARM_LOOP                       0x134A /* BC12 52/10, 1.91 s, loops; named from the code */
#define SND_ALARM_LOOP_ALT                   0x134B /* BC12 52/11, 1.74 s, loops; named from the code */
#define SND_PROXIMITY_ALERT_LOOP             0x134C /* BC12 52/12, 1.85 s, loops; named from the code */
#define SND_FALL_LAUNCH                      0x13F1 /* BC12 63/1, 0.77 s; named from the code */
#define SND_LANDING_THUD                     0x13F2 /* BC12 63/2, 0.68 s; named from the code */
#define SND_HELICOPTER                       0x1501 /* BC12 80/1, 1.77 s, loops; heard as "helicopter" */
#define SND_TIMER_LOOP                       0x1590 /* BC12 89/0, 1.88 s, loops; named from the code */

#endif
