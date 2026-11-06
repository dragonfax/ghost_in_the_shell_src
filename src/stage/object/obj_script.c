/* obj_script: one of the original source files (scripts/objmap.py); s04, s09. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

s32 vec3_dist(Vec3 *a, Vec3 *b) {
    return SquareRoot0(length_sq(a->x - b->x, a->y - b->y, a->z - b->z));
}

/* Distance from the player to the object's placement position, in whole units (pos_distance). */
s32 obj_player_dist(Object *obj) {
    void *target = player_position();
    Placement *placement = obj->placement;
    Vec3 *pos = scratch_alloc(0x10);
    s32 dist;

    pos->x = placement->x >> 12;
    pos->y = placement->y >> 12;
    pos->z = placement->z >> 12;
    dist = vec3_dist(target, pos);
    scratch_top -= 0x10;
    return dist;
}

void obj_script_set_sound(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.snd.sound = *cursor;
}

#if STAGE == 4
/* Reads the next halfword of the object's script cursor (unk_1C.unk_04) into vars.h.unk_24A. */
void obj_script_read_u16(Object *obj) {
    u16 *cursor;

    cursor = (u16 *)obj->script.pc;
    obj->script.pc = cursor + 1;
    obj->vars.h.unk_24A = *cursor;
}
#elif STAGE == 9
u16 obj_script_read_u16(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;
    u16 value;

    obj->script.pc = cursor + 1;
    value = *cursor;
    obj->vars.h.unk_248 = value;
    return value;
}
#else
INCLUDE_ASM(STAGE_ASM, obj_script_read_u16);
#endif

void obj_script_set_fly_mode(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void obj_script_jump_if_within(Object *obj) {
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

void obj_script_jump_if_beyond(Object *obj) {
    s32 *player;
    s16 dist;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 half_h;
    s16 *cursor;
    s32 range;
    s32 index;

    player = player_position();
    dx = player[0] - (obj->x >> 12);
    half_h = (s16)obj->height / 2;
    dy = player[1] - ((obj->y >> 12) - half_h);
    dz = player[2] - (obj->z >> 12);
    dist = isqrt(length_sq(dx, dy, dz));
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    range = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (range < dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

#if STAGE == 9
void script_op_read_u16(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.heavy_mobile_suit.aim_yaw = *cursor;
}
#endif

void obj_script_set_258(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.h.unk_258 = *cursor;
}

#if STAGE == 4
void obj_script_set_selector(Object *obj) {
    obj->vars.h.unk_25A = obj_read_u16(obj);
}
#endif
