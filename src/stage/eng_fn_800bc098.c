/* Shared by s01, s03, s05, s07, s10: script_jump_if_not_below_speed..script_jump_if_facing_player_in_radius (3 functions). */

#include "stage.h"

/* Script op: if the op is not below obj->speed, jump to the table entry given by the next word. */
void script_jump_if_not_below_speed(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op >= obj->speed) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Reads a (radius, index) pair from the object's script stream. If the player is at least `radius` away from
 * the target, the stream's cursor becomes entry `index` of the object's table (unk_1C.data). */
void script_jump_if_beyond_radius(Object *obj) {
    s16 radius;
    s16 index;
    s32 *player;
    PlacedTarget *target;
    s32 dist;

    radius = obj_read_s16(obj);
    index = obj_read_s16(obj);
    player = player_position();
    target = (PlacedTarget *) obj->placement;
    dist = isqrt(length_sq(player[0] - (target->x >> 12), player[1] - (target->y >> 12),
                           player[2] - (target->z >> 12)));
    if (dist >= radius) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op (radius, range, near, far): when the player is within `radius`, jumps the script cursor to table
 * entry `near` if the object faces the player (yaw within `range`, pitch within 0x155), else to `far`. */
void script_jump_if_facing_player_in_radius(Object *obj) {
    s32 *player;
    s32 dist;
    s16 *cursor;
    s32 radius;
    s32 range;
    s32 near_index;
    s32 far_index;
    ObjLink *link;
    s32 obj_yaw;
    s32 obj_pitch;
    s32 yaw;
    s32 pitch;
    s32 facing;
    s32 to_yaw;
    s32 to_pitch;

    player = player_position();
    dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    radius = cursor[0];
    obj->script.pc = cursor + 2;
    range = cursor[1];
    obj->script.pc = cursor + 3;
    near_index = cursor[2];
    obj->script.pc = cursor + 4;
    far_index = cursor[3];
    link = &obj->script;
    if (radius < dist) {
        return;
    }
    obj_yaw = obj->yaw;
    obj_pitch = obj->pitch;
    angles_to_player(obj->x >> 12, (obj->y >> 12) - (s16) obj->height / 2, obj->z >> 12, &yaw, &pitch);
    to_yaw = yaw;
    to_pitch = pitch;
    if (ANG_ABS_DIFF(obj_yaw, to_yaw) < range && ANG_ABS_DIFF(obj_pitch, to_pitch) < 0x155) {
        facing = 1;
    } else {
        facing = 0;
    }
    if (facing) {
        link->pc = ((s16 **)link->data)[near_index];
    } else {
        link->pc = ((s16 **)link->data)[far_index];
    }
}
