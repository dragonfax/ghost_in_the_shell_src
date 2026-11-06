/* Shared by s05, s07, s09, s10: obj_yaw_turn. */

#include "stage.h"

/* Turns the yaw toward vars.h.unk_254 by up to 0x10 per step. */
void obj_yaw_turn(Object *obj) {
    obj->yaw = angle_approach(obj->yaw, obj->vars.h.unk_254, 0x10);
}
