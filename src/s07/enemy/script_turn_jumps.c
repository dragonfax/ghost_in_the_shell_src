/* script_turn_jumps: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

void script_turn_to_player_jump(Object *obj) {
    s16 *cursor;
    s32 raw;
    s32 index;
    s16 step;
    s32 *player;
    s32 target;
    s32 yaw;
    s32 diff;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    raw = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    step = ABS(raw);
    player = player_position();
    target = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    yaw = obj->yaw;
    yaw &= 0xFFF;
    if (yaw >= 0x800) {
        yaw -= 0x1000;
    }
    diff = angle_approach(yaw, target, step) - yaw;
    diff &= 0xFFF;
    if (diff >= 0x800) {
        diff -= 0x1000;
    }
    if (ABS(diff) < step) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: if the op equals obj->unk_F8, jump to the table entry given by the next word. */
void script_case_match(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op == obj->script_flag) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}
