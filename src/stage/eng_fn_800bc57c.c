/* Shared by s04, s05: fighter_jet_phase0..obj_fly_velocity (2 functions). */

#include "stage.h"

void fighter_jet_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void obj_fly_velocity(Object *obj) {
    s32 dx = 0;
    s32 dz = 0;
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vx = dz;
    obj->vz = dx;
}
