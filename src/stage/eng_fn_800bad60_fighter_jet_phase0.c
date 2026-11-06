/* s05: fighter_jet_phase0's copy of eng_fn_800bad60.c (the same helper in another original file; scripts/objtree.py unshare). */

#include "stage.h"

void fighter_jet_stop_sound(Object *obj) {
    sound_stop(obj->vars.words[5]); /* 0x25C */
}
