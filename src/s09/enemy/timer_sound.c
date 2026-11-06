/* timer_sound: one of s09's own original source files (scripts/objmap.py); part of src/s09/main.c's unit, included there. */

void obj_play_sound_here(Object *obj) {
    s32 pos[3];
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    sound_play_at_units(0x3530, 0x60, 0x3C, pos);
}

#if STAGE == 9
/* Once the timer field unk_F8 has run out, copies the 0x248 halfword into next_state. */
void obj_timer_next_state(Object *obj) {
    obj_link_script_run();
    if (obj->script_flag == 0) {
        obj->next_state = (u16)obj->vars.h.unk_248;
    }
}
#else
/* S04: the same with the 0x24A halfword. */
void obj_timer_next_state(Object *obj) {
    obj_link_script_run();
    if (obj->script_flag == 0) {
        obj->next_state = obj->vars.h.unk_24A;
    }
}
#endif
