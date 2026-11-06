/* script_jump_ops: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

s32 player_horiz_dist(s32 *pos);
void script_op_jump_if_player_close(Object *obj) {
    s32 pos[3];
    s32 *pos_ptr;
    s32 *player;
    s16 *script;
    s32 cmd;
    s32 dist;
    s32 dy;

    pos_ptr = pos;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    script = obj->script.pc;
    obj->script.pc = script + 1;
    cmd = *script;
    if (obj->health > 0) {
        player = player_position();
        dist = player_horiz_dist(pos_ptr);
        dy = player[1] - pos[1];
        if (dist < 0x320 && (u32) dy < 0x64) {
            obj->script.pc = ((s16 **)obj->script.data)[cmd];
        }
    }
}

/* Script step: read the next s16 op; when the object's flag (unk_1B7) is set, the op
 * indexes the type's table (unk_1C.data) and the stream jumps to that entry. */
void script_op_jump_if_flag_1b7(Object *obj) {
    s32 op = obj_read_s16(obj);

    if (*(u8 *)&obj->unk_1B7 != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}



void script_set_enemy_var(Object *obj) {
    obj->vars.enemy.unk_25C = obj_read_u16(obj);
}
