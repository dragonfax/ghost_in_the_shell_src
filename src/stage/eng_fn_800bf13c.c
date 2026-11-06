/* Shared by s06, s07, s09: obj_angle_to_player..obj_retarget (8 functions). */

#include "stage.h"

s32 obj_angle_to_player(Object *obj) {
    s32 *pos = player_position();
    s32 x = obj->x >> 12;
    s32 z = obj->z >> 12;
    return atan2(pos[2] - z, pos[0] - x);
}

/* Distance from the object's position to its target point (vars.words[4..6], 4.12 fixed point). */
s32 obj_dist_to_target(Object *obj) {
    s32 x = obj->x;
    s32 dx = (obj->vars.words[4] - x) >> 12;
    s32 y = obj->y;
    s32 dy = (obj->vars.words[5] - y) >> 12;
    s32 z = obj->z;
    s32 dz = (obj->vars.words[6] - z) >> 12;

    return isqrt(length_sq(dx, dy, dz));
}

/* Picks a random target point near the placement's centre: x and z are
   offset by up to +-0x7D0 whole units, y is copied. The centre words sit
   past the end of Placement (0x28..0x30). */
void obj_pick_random_target(Object *obj) {
    s32 *centre = (s32 *)obj->placement;
    s32 base_x = centre[10];
    s32 base_y = centre[11];
    s32 base_z = centre[12];
    s32 range = 0xFA0;

    obj->vars.tank.target_x = base_x + ((rand_a_next() * range) / 4096 - 0x7D0) * 4096;
    obj->vars.tank.target_y = base_y;
    obj->vars.tank.target_z = base_z + ((rand_a_next() * range) / 4096 - 0x7D0) * 4096;
}

/* Distance from the object (in 1/4096 units) to the player, in the same units. */
s32 obj_player_distance(Object *obj) {
    s32 *player = player_position();

    return isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
}

static inline s32 player_in_view(s32 yaw, s32 pitch, s32 to_yaw, s32 to_pitch, s32 yaw_tol) {
    if (ABS(angle_diff(yaw, to_yaw)) < yaw_tol
        && ABS(angle_diff(pitch, to_pitch)) < 0x2AA) {
        return 1;
    }
    return 0;
}
void script_jump_if_near_player_in_view(Object *obj) {
    ObjLink *link;
    s16 *cursor;
    s32 threshold;
    s32 yaw_tol;
    s32 index;
    s32 obj_yaw;
    s32 obj_pitch;
    s32 yaw_to_player;
    s32 pitch_to_player;
    s32 out_yaw;
    s32 out_pitch;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    yaw_tol = cursor[1];
    obj->script.pc = cursor + 3;
    index = cursor[2];

    link = &obj->script;
    if (threshold < obj_player_distance(obj)) {
        return;
    }

    obj_yaw = (s16) obj->vars.h.unk_252;
    obj_pitch = obj->pitch;
    angles_to_player((s32) obj->x >> 12,
                     ((s32) obj->y >> 12) - ((s16) obj->height / 2),
                     (s32) obj->z >> 12,
                     &out_yaw, &out_pitch);
    yaw_to_player = out_yaw;
    pitch_to_player = out_pitch;

    if (player_in_view(obj_yaw, obj_pitch, yaw_to_player, pitch_to_player, yaw_tol)) {
        link->pc = ((s16 **)link->data)[index];
    }
}

void script_jump_if_player_in_view(Object *obj) {
    ObjLink *link = &obj->script;
    s16 *cursor = link->pc;
    s32 yaw = (s16)obj->vars.h.unk_252;
    s32 pitch = obj->pitch;
    s32 tol;
    s32 target;
    s32 want_yaw;
    s32 want_pitch;
    s32 player_yaw;
    s32 player_pitch;
    s32 in_view;

    link->pc = cursor + 1;
    tol = *cursor;
    link->pc = cursor + 2;
    target = cursor[1];
    angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &want_yaw, &want_pitch);
    player_yaw = want_yaw;
    player_pitch = want_pitch;
    if (ABS(angle_diff(yaw, player_yaw)) < tol && ABS(angle_diff(pitch, player_pitch)) < 0x2AA) {
        in_view = 1;
    } else {
        in_view = 0;
    }
    if (in_view) {
        link->pc = ((s16 **)link->data)[target];
    }
}

void script_read_s32(Object *obj) {
    s16 *p = obj->script.pc;
    s32 lo, hi;
    obj->script.pc = p + 1;
    lo = p[0];
    obj->script.pc = p + 2;
    hi = p[1] << 16;
    obj->vars.script.value = (lo & 0xFFFF) | hi;
}

void obj_retarget(Object *obj) {
    obj_pick_random_target(obj);
}
