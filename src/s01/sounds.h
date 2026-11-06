/* s01's sound IDs in its stage bank (BC01.VAB); made by scripts/sound_c.py. */
#ifndef STAGE_SOUNDS_H
#define STAGE_SOUNDS_H

#include "sound.h"

#define SND_SHOT_FIRE                        0x1006 /* BC01 0/6, 0.76 s; named from the code */
#define SND_SCREECH_LOOP                     0x100D /* BC01 0/13, 1.75 s, loops; named from the code */
#define SND_SCREECH_ALT_LOOP                 0x100E /* BC01 0/14, 1.74 s, loops; named from the code */
#define SND_SCREECH                          0x100F /* BC01 0/15, 1.58 s, loops; heard as "screech" */
#define SND_PURSUE_AMBIENCE_LOOP             0x11E0 /* BC01 30/0, 4.41 s, loops; named from the code */
#define SND_SEAGULL                          0x11E2 /* BC01 30/2, 0.5 s; heard as "seagull" */
#define SND_EXIT_DOOR_LOOP                   0x11E3 /* BC01 30/3, 1.73 s, loops; named from the code */
#define SND_KEY_CODE_ACQUIRED                0x11E4 /* BC01 30/4, 0.27 s; named from the code */
#define SND_ALL_KEY_CODES_ACQUIRED           0x11E5 /* BC01 30/5, 0.58 s; named from the code */
#define SND_COLLISION_IMPACT                 0x1284 /* BC01 40/4, no tone; named from the code */
#define SND_ENEMY_BURST_FIRE                 0x1420 /* BC01 66/0, 1.03 s; named from the code */
#define SND_HELICOPTER                       0x1501 /* BC01 80/1, 1.77 s, loops; heard as "helicopter" */

#endif
