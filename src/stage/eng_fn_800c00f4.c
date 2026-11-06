/* Shared by s06, s07, s09: obj_turn_sound_update. */

#include "stage.h"

void obj_turn_sound_update(Object *obj) {
    obj_sound_held_stop(obj);
    if (((ObjTail *) obj)->unk_284 == 0) {
        obj_yaw_step(obj);
        obj_sound2_start(obj);
    }
    obj_avoid_walls(obj);
}
