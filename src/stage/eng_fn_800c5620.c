/* Shared by s01, s02, s03, s07, s08, s11, s13: fade_red_update (1 function); not yet decompiled. */

#include "stage.h"

void fade_red_update(FadeRedState *f) {
    s32 q;
    s32 v;
    q = f->timer / 6144;
    q = 0x1000 - q;
    v = q * 0xFF;
    f->colour[0] = v / 0x1000;
    f->colour[1] = 0;
    f->colour[2] = 0;
    if (f->timer <= 0 || f->limit > 0) {
        f->flag = 0;
        fade_red_obj->state = 4;
    }
}
