/* script_jump_table: one of s02's own original source files (scripts/objmap.py); part of src/s02/main.c's unit, included there. */

/* Same code as func_800BC8AC (s01). */
void script_op_jump_table_if_player_far(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) obj_player_dist_whole(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
