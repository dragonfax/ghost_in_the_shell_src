/* script_bounds_ops: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

/* Advances the s32 at 0x20 (unk_1C.unk_04) by 2. */
void script_op_skip_halfword(Object *obj) {
    obj->script.pc++;
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_op_jump_if_player_within(Object *obj) {
    s32 *player;
    s32 dist;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 half;
    s16 *cursor;
    s32 threshold;
    s32 index;

    player = player_position();
    half = (s16) obj->height / 2;
    dx = player[0] - (obj->x >> 12);
    dy = player[1] - ((obj->y >> 12) - half);
    dz = player[2] - (obj->z >> 12);
    dist = (s16) isqrt(length_sq(dx, dy, dz));

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < dist) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is at least
 * `threshold` from the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_op_jump_if_player_beyond(Object *obj) {
    s32 *player;
    s32 dist;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 half;
    s16 *cursor;
    s32 threshold;
    s32 index;

    player = player_position();
    half = (s16) obj->height / 2;
    dx = player[0] - (obj->x >> 12);
    dy = player[1] - ((obj->y >> 12) - half);
    dz = player[2] - (obj->z >> 12);
    dist = (s16) isqrt(length_sq(dx, dy, dz));

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (dist < threshold) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}

extern s32 area_bounds_x0;
extern s32 area_bounds_x1;
extern s32 area_bounds_z0;
extern s32 area_bounds_z1;
extern s32 area_center_x;
extern s32 area_center_z;
void area_set_bounds(s32 x0, s32 x1, s32 y0, s32 y1) {
    area_bounds_x0 = x0;
    area_bounds_x1 = x1;
    area_bounds_z0 = y0;
    area_bounds_z1 = y1;
    area_center_x = (x0 + x1) / 2;
    area_center_z = (y0 + y1) / 2;
}

void script_op_jump_if_outside_bounds(Object *obj) {
    s16 *stream;
    s32 out_of_range;
    s32 idx;
    s32 pos[3];

    /* the link's cursor is a byte address into a halfword stream: read one halfword, advance 2 bytes */
    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    idx = stream[0];
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    out_of_range = pos[0] < area_bounds_x0;
    if (area_bounds_x1 < pos[0]) {
        out_of_range = 1;
    }
    if (pos[2] < area_bounds_z0) {
        out_of_range = 1;
    }
    if (area_bounds_z1 < pos[2]) {
        out_of_range = 1;
    }
    if (out_of_range) {
        obj->script.pc = ((s16 **)obj->script.data)[idx];
    }
}
