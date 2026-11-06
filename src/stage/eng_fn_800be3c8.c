/* Shared by s09, s10: obj_sound_handle_stop..troi_phase0 (2 functions). */

#include "stage.h"

/* Stops the sound handle byte at 0x25A if one is set. */
void obj_sound_handle_stop(Object *obj) {
    u8 *sound = (u8 *)obj + 0x25A;

    if (*sound != 0) {
        sound_stop(*sound);
        *sound = 0;
    }
}

void troi_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}
