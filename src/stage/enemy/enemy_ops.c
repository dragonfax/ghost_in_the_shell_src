/* enemy_ops: one of the original source files (scripts/objmap.py); s01, s02, s03, s04, s05, s06, s07, s08, s09, s12. */

#include "stage.h"

/* Script op: reads a target speed and moves obj->speed one step towards it. */
void obj_speed_approach(Object *obj) {
    s16 target;

    target = obj_read_s16(obj);
    if (obj->speed == target) {
        obj->speed = target;
    }
    if (obj->speed < target) {
        obj->speed += 1;
    }
    if (target < obj->speed) {
        obj->speed -= 1;
    }
}

void obj_set_next_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

void script_set_turn_mode(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void obj_jump_if_player_near(Object *obj) {
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
