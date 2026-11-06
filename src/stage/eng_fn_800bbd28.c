/* Shared by s10, s12: loop_sound_fade_in..obj_destroy_loop_sound (2 functions). */

#include "stage.h"

void loop_sound_fade_in(void) {
    if (stage_ready_get() != 0) {
        loop_sound_fade_handle = interp1c_add((s32)d_8011B7AC, timer_tail_data.words[0]);
        interp1c_set_state(loop_sound_fade_handle, 1);
    }
}

#if STAGE == 10
void obj_destroy_loop_sound(Object *obj) {
    /* the high halfword of the loop sound handle (0x272) */
    u16 *handle_hi = &((u16 *) &obj->vars.enemy.sound)[1];

    if (*handle_hi != 0) {
        sound_stop(*handle_hi);
        *handle_hi = 0;
    }
}
#elif STAGE == 12
void obj_destroy_loop_sound(Object *obj) {
    /* the halfword sound handle at 0x278 (shares the turn view's yaw_offset slot) */
    u16 *handle = (u16 *) &obj->vars.turn.yaw_offset;

    if (*handle != 0) {
        sound_stop(*handle);
        *handle = 0;
    }
}
#else
INCLUDE_ASM(STAGE_ASM, obj_destroy_loop_sound);
#endif
