/* Shared by s09, s10: enemy_steer_obstacle..obj_fire_offset (5 functions). */

#include "stage.h"

void enemy_steer_obstacle(Object *obj) {
    s32 delay = 4;
    s32 turn_step = 0xC;
    ObjHandler *h = &obj->handlers[1];
    s32 *from;
    s32 *to;
    s32 *hit;
    register s32 hits asm("$19");
    s32 shifted;
    s32 angle;
    s32 i;
    register s32 mode asm("$3");
    s32 speed;
    s32 flags;

    obj->speed += obj->speed_accel;
    flags = obj->ground_flags;
    speed = MAX(CLAMP_HI(obj->speed, obj->vars.enemy.unk_250), 0);
    obj->speed = speed;
    if (flags & 0x3C) {
        mode = 3;
    } else {
        mode = 0;
        if (h->timer == 0) {
            from = scratch_alloc(0x30);
            to = from + 4;
            hit = from + 8;
            from[0] = obj->x >> 12;
            from[1] = obj->y >> 12;
            from[2] = obj->z >> 12;
            hits = 0;
            from[1] -= 0x69;
            angle = obj->yaw - 0x40;
            for (i = 0; i < 2; i++) {
                to[2] = 0x100;
                to[0] = 0;
                to[1] = 0;
                rotate_xz_twice(angle, 0, &to[0], &to[1], &to[2]);
                to[0] += from[0];
                to[1] += from[1];
                to[2] += from[2];
                shifted = hits << 1;
                hits = trace_world(8, 0x64, from, to, hit) != 0 ? shifted | 1 : shifted;
                angle += 0x80;
            }
            scratch_top -= 0x30;
            mode = hits;
            h->timer = delay;
        }
    }
    switch (mode) {
    case 0:
        if (h->turn_timer == 0) {
            obj_yaw_turn(obj);
            break;
        }
        obj->yaw += obj->unk_226[0];
        break;
    case 1:
        if (h->turn_timer == 0) {
            obj->unk_226[0] = -0xC;
        }
        break;
    case 2:
        if (h->turn_timer == 0) {
            obj->unk_226[0] = turn_step;
        }
        break;
    case 3:
        if (h->turn_timer == 0) {
            h->turn_timer = 0x1E;
        }
        obj->yaw += obj->unk_226[0];
        break;
    }
    fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);
    if (h->turn_timer > 0) {
        h->turn_timer--;
    }
    if (h->timer > 0) {
        h->timer--;
    }
}

s32 player_near_placement(Object *obj) {
    s32 *pos = player_position();
    u8 *base = (u8 *)obj->placement;

    if (isqrt(length_sq(pos[0] - (*(s32 *)(base + 0x28) >> 12), pos[1] - (*(s32 *)(base + 0x2C) >> 12),
                        pos[2] - (*(s32 *)(base + 0x30) >> 12))) < 0x961 &&
        (player_position()[1] >= (obj->y >> 12) - 0x200 || player_landed != 1)) {
        return 1;
    }
    return 0;
}

void enemy_steer_obstacle(Object *obj);
static inline s32 aimed_at(s32 yaw0, s32 yaw1, s32 pitch0, s32 pitch1) {
    if (ANG_ABS_DIFF(yaw0, yaw1) < 0x60 && ANG_ABS_DIFF(pitch0, pitch1) < 0x155) {
        return 1;
    }
    return 0;
}
/* Patrol state machine: 0 wanders around the placement (a new random heading every 120 frames) until the
 * player comes near, 1 turns toward the player and goes to 3 once aimed and in view, 2 walks back home.
 * unk_250 is the speed, slower the more the object turned this step. */
void obj_patrol_update(Object *obj) {
    s32 old_yaw = obj->yaw;
    PlacedTarget *place;
    s32 range;
    s32 px;
    s32 offset_x;
    s32 yaw;
    s32 pitch;
    s32 ahead;
    s32 view_yaw;
    s32 view_pitch;
    s32 new_yaw;
    s32 turn;

    enemy_steer_obstacle(obj);
    new_yaw = obj->yaw;
    turn = ang_abs_diff(old_yaw, new_yaw);
    obj->vars.enemy.unk_250 = (0x10 - turn) * 0x280 + 0x2800;

    switch (obj->unk_242) {
    case 0:
        if (player_near_placement(obj)) {
            if (player_dist_to_obj_point(obj, 0) < 0x781) {
                obj->unk_242 = 1;
            }
        }
        if ((s16)--obj->vars.h.unk_258 > 0) {
            return;
        }
        obj->vars.h.unk_258 = 0x78;
        place = (PlacedTarget *)obj->placement;
        range = 0x12C0;
        offset_x = rand_a_next() * range / 0x1000 - 0x960;
        px = place->x + offset_x;
        {
            register s32 offset_z asm("$3") = rand_a_next() * range / 0x1000 - 0x960;

            obj->vars.h.unk_254 = atan2((place->z + offset_z - obj->z) >> 12, (px - obj->x) >> 12);
        }
        break;
    case 1:
        {
            s32 *pos = player_position();

            obj->vars.h.unk_254 = atan2(pos[2] - (obj->z >> 12), pos[0] - (obj->x >> 12));
        }
        if (player_near_placement(obj)) {
            if (player_dist_to_obj_point(obj, 0) < 0x781) {
                s32 cur_yaw;
                s32 cur_pitch;

                cur_yaw = obj->yaw;
                cur_pitch = obj->pitch;

                angles_to_player(obj->x >> 12, (obj->y >> 12) - (s16)obj->height / 2, obj->z >> 12, &yaw, &pitch);
                if (aimed_at(cur_yaw, yaw, cur_pitch, pitch)) {
                    point_to_view_angles(obj->x >> 12, obj->y >> 12, obj->z >> 12, &yaw, &pitch);
                    view_yaw = yaw;
                    view_pitch = pitch;
                    if (view_yaw > 0x800) {
                        view_yaw = 0x1000 - view_yaw;
                    }
                    if (view_pitch > 0x800) {
                        view_pitch = 0x1000 - view_pitch;
                    }
                    ahead = view_yaw < 0x400 && view_pitch < 0x400;
                    if (ahead) {
                        obj->unk_242 = 3;
                    }
                }
                return;
            }
        }
        obj->unk_242 = 2;
        break;
    case 2: {
        PlacedTarget *home = (PlacedTarget *)obj->placement;

        obj->vars.h.unk_254 = atan2((home->z - obj->z) >> 12, (home->x - obj->x) >> 12);
        home = (PlacedTarget *)obj->placement;
        if (isqrt(length_sq((obj->x - home->x) >> 12, (obj->y - home->y) >> 12,
                            (obj->z - home->z) >> 12)) < 0x200) {
            obj->unk_242 = 0;
            return;
        }
        if (player_dist_to_obj_point(obj, 1) < 0x961) {
            if (player_dist_to_obj_point(obj, 0) < 0x781) {
                obj->unk_242 = 1;
            }
        }
        break;
    }
    }
}

void obj_pitch_toward_player(Object *obj, s32 step) {
    s32 yaw;
    s32 pitch;
    s32 angle;
    s16 *field;
    s32 lo = 0;

    angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &yaw, &pitch);
    pitch = angle_approach(obj->vars.h.unk_248, pitch, step);
    field = &obj->vars.h.unk_248;
    angle = pitch & 0xFFF;
    if (angle >= 0x800) {
        if (angle < 0xF4C) {
            angle = 0xF4C;
        }
    } else if (angle > lo) {
        angle = lo;
    }
    *field = angle;
}

/* Builds two rotations in scratch (a 0x20-byte vector pair and an 8-byte angle record) from the object's
 * angles and the argument, then passes the result to shot_spawn_obj. */
void obj_fire_offset(Object *obj, s32 arg) {
    Vec3 *vec = scratch_alloc(0x20);
    SVECTOR *ang = scratch_alloc(8);
    Vec3 *offs = (Vec3 *)((u8 *)vec + 0x10);

    ang->vx = -obj->vars.h.unk_248;
    ang->vy = obj->yaw;
    ang->vz = 0;
    vec->x = 0;
    vec->y = -0x90;
    vec->z = 0x6E;
    rotate_xz_twice(ang->vy, -obj->pitch, &vec->x, &vec->y, &vec->z);
    offs->x = arg;
    offs->y = 0;
    offs->z = 0x96;
    rotate_xz_twice(ang->vy, ang->vx, &offs->x, &offs->y, &offs->z);
    offs->x = (obj->x >> 12) + vec->x + offs->x;
    offs->y = (obj->y >> 12) + vec->y + offs->y;
    offs->z = (obj->z >> 12) + vec->z + offs->z;
    shot_spawn_obj((s32 *)offs, (u16 *)ang, 1, ((s32)obj->damage << 16) | 1);
    scratch_top -= 0x28;
}
