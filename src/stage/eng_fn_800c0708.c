/* Shared by s06, s07, s09: obj_finish_step. */

#include "stage.h"

void obj_finish_step(Object *obj, ObjHandler *handler) {
    if (handler->result == -2) {
        obj_sound_held_stop(obj);
        obj_muzzle_effect(obj);
        handler->queued_entry = -1;
        handler->result = 0x3C;
    }
}
