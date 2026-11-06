/* hit_reaction: one of the original source files (scripts/objmap.py); s01, s06, s07, s12. */

#include "stage.h"

void obj_set_hit_reaction(Object *obj, s32 flag) {
    s32 flags = obj->flags;

    obj->unk_17A = flag;
    if (flag != 0) {
        flags |= 0x4;
    } else {
        flags &= -5;
    }
    obj->flags = flags;
}
