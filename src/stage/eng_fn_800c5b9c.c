/* Shared by s01, s02, s03, s07, s08, s13: obj_sound_clear. */

#include "stage.h"

void obj_sound_clear(Object *obj) {
    obj->vars.snd.sound = 0;
    obj_noop_hook();
}
