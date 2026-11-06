/* s09, s10: obj_sound_handle_stop's copy of eng_fn_800bab20.c (the same helper in another original file; scripts/objtree.py unshare). */

#include "stage.h"

void obj_script_jump_if_key(Object *obj) {
    s16 *cursor;
    s32 key;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    key = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (key == obj->unk_242) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
