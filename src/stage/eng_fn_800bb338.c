/* Shared by s01, s03, s10: rocket_fuchikoma_phase0..rocket_fuchikoma_turn (2 functions). */

#include "stage.h"

/* Identical to keyholder_fuchikoma_phase0 (a copy at another address). */
void rocket_fuchikoma_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

void rocket_fuchikoma_turn(Object *obj) {
    obj->yaw = angle_approach(obj->yaw, obj->vars.enemy.sound_channel[0], 0xA);
}
