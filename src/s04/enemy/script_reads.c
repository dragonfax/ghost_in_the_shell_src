/* script_reads: one of s04's own original source files (scripts/objmap.py); part of src/s04/main.c's unit, included there. */

/* The stage's model and message files: data tables point to them by address. */
const char file_flip_tp0_clt[] = "flip_tp0.clt";
const char file_flip_ch0_clt[] = "flip_ch0.clt";
const char file_flip_tp0_xs3[] = "flip_tp0.xs3";
const char file_flip_ch0_vx1[] = "flip_ch0.vx1";
const char file_flip_ch0_cb4[] = "flip_ch0.cb4";
const char file_mjet_tp0_clt[] = "mjet_tp0.clt";
const char file_mjet_ch0_clt[] = "mjet_ch0.clt";
const char file_mjet_ch0_vx1[] = "mjet_ch0.vx1";
const char file_mjet_tp0_xs3[] = "mjet_tp0.xs3";
const char file_mjet_ch0_cb4[] = "mjet_ch0.cb4";


void script_read_speed(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->speed = *cursor;
}


/* Same code as func_800BC7AC (s01). */
void obj_read_next_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

/* Same code as func_800BC7C8 (s01). */
void obj_read_unk_242(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

void script_jump_if_height(ScriptJumpState *obj) {
    s32 *pos = player_position();
    s16 *op = obj->pc;
    s32 limit, target;

    obj->pc = op + 1;
    limit = *op;
    obj->pc = op + 2;
    target = op[1];
    if (limit >= (s16)((obj->z >> 12) - pos[2])) {
        obj->pc = (s16 *)obj->targets[target];
    }
}
