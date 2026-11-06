/* giant_robot_fx: one of the original source files (scripts/objmap.py); s01, s06, s07, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void model_part_transform(s32 arg0, s32 idx, void *vec) {
    s16 *rec;
    s16 *m;
    s16 ang[3];
    s32 trans[3];
    s32 x, y, z;

    if (arg0 != 0) {
        rec = (s16 *)((u8 *)arg0 + (idx * 12 + 4));
        m = (s16 *)scratch_alloc(0x20);
        trans[0] = rec[0];
        trans[1] = rec[1];
        trans[2] = rec[2];
        TransMatrix(m, trans);
        ang[0] = rec[4];
        ang[1] = rec[3];
        ang[2] = rec[5];
        rot_matrix(m, ang[1], ang[0], ang[2]);
        SetRotMatrix(m);
        SetTransMatrix(m);
        gte_ldv0(vec);
        gte_rtv0tr();
        gte_get(MAC1, x);
        gte_get(MAC2, y);
        gte_get(MAC3, z);
        scratch_top -= 0x20;
        ((SVECTOR *)vec)->vx = x;
        ((SVECTOR *)vec)->vy = y;
        ((SVECTOR *)vec)->vz = z;
    }
}

/* Horizontal (x/z) distance from the player to pos. */
s32 player_horiz_dist(s32 *pos) {
    s32 *player = player_position();

    return SquareRoot0(length_sq(player[0] - pos[0], 0, player[2] - pos[2]));
}

#if STAGE == 12
/* Squared horizontal (x, z) distance from pos to the player; y is left out. */
s32 player_dist_sq_xz(Vec3 *pos) {
    Vec3 *player = (Vec3 *)player_position();

    return length_sq(player->x - pos->x, 0, player->z - pos->z);
}
#endif

/* Distance from the player to pos. */
void player_distance(s32 *pos) {
    s32 *player = player_position();

    SquareRoot0(length_sq(player[0] - pos[0], player[1] - pos[1], player[2] - pos[2]));
}

/* Squared distance from the player to pos; the result is discarded. */
s32 player_dist_sq(s32 *pos) {
    s32 *player = player_position();

    return length_sq(player[0] - pos[0], player[1] - pos[1], player[2] - pos[2]);
}

/* Rotates the vector src (three halfwords) by the object's yaw and pitch into x, y, z, then adds the
 * object's position (whole units) to each. */
void obj_point_to_world(Object *obj, s16 *src, s32 *x, s32 *y, s32 *z) {
    *x = src[0];
    *y = src[1];
    *z = src[2];
    rotate_xz_twice(obj->yaw, obj->pitch, x, y, z);
    *x = (obj->x >> 12) + *x;
    *y = (obj->y >> 12) + *y;
    *z = (obj->z >> 12) + *z;
}

void rot_turn_toward(s32 *target, s16 *rot, s32 pitch_step, s32 yaw_step) {
    VECTOR *pos = scratch_alloc(16);
    s32 yaw;
    s32 pitch;
    s32 tx, ty, tz;

    player_position_copy(pos);
    tx = target[0];
    ty = target[1];
    tz = target[2];
    tx = pos->vx - tx;
    ty = ty - pos->vy;
    tz = pos->vz - tz;
    vector_to_angles(tx, ty, tz, &yaw, &pitch);
    rot[1] = angle_approach(rot[1], yaw, pitch_step);
    rot[0] = angle_approach(rot[0], pitch, yaw_step);
    rot[2] = 0;
    scratch_top -= 16;
}

/* Result discarded. */
s32 get_angle_to_player(s32 *pos) {
    s32 *player = player_position();

    return atan2(player[2] - pos[2], player[0] - pos[0]);
}

#if STAGE == 6 || STAGE == 12
/* The angle from the player to the given position, in the XZ plane. */
s32 player_angle_to(Vec3 *pos) {
    Vec3 *player;

    player = (Vec3 *)player_position();
    return atan2(pos->z - player->z, pos->x - player->x);
}
#endif

#if STAGE == 12
/* Walks a table of 6-halfword records. A record starts with a signed id
 * (-1 ends the table). Records are skipped while id < *remaining. On a hit,
 * copies four fields out and writes a 12-bit fixed-point ratio of *remaining
 * over the record id. */
s32 particle_keyframe_next(s16 **cursor, s32 *remaining, u16 *out0, u16 *out1, u16 *out2, u16 *out3, s16 *out4) {
    s16 *rec;

    rec = *cursor;
    if (rec[0] == -1) {
        return 0;
    }
    if (rec[0] < *remaining) {
        rec += 3; /* 6 bytes: one record */
        *cursor = rec;
        *remaining = 0;
        if (rec[0] == -1) {
            return 0;
        }
    }

    *out0 = rec[1];
    *out1 = rec[4];
    *out2 = rec[2];
    *out3 = rec[5];
    *out4 = (s16)((*remaining << 12) / rec[0]);
    *remaining += 1;
    return 1;
}
#endif

#if STAGE != 12
/* Steps through a keyframe list: gives the current and next values and how far (0x1000 = all the way)
 * `*tick` is between them. Returns 0 at the end of the list. */
s32 keyframe_step(Keyframe **cursor, s32 *tick, u16 *from, u16 *to, s16 *t) {
    Keyframe *key;
    s16 time;

    key = *cursor;
    time = key->time;
    if (time == -1) {
        return 0;
    }
    if (time < *tick) {
        key++;
        *cursor = key;
        *tick = 0;
        if (key->time == -1) {
            return 0;
        }
    }
    *from = key[0].value;
    *to = key[1].value;
    *t = (*tick << 12) / key->time;
    *tick += 1;
    return 1;
}
#endif

void tick_reset(s32 *arg0) {
    *arg0 = 0;
}

#if STAGE == 1 || STAGE == 7
s32 cam_point_in_zone(s32 id, s32 x, s32 y, s32 z, s32 radius, s32 down, s32 up) {
    Camera *cam = cameras;
    Camera *end = &cameras[8];
    s32 dx, dz, dy, sx, sz;
    s32 r2 = radius * radius;

    gte_set(IR1, 0);
    do {
        if (cam->user_count != 0 && cam->rec_index == id) {
            dx = x - cam->pos.vx;
            dz = z - cam->pos.vz;
            gte_set(IR2, dx);
            if (ABS(dx) <= radius) {
                gte_set(IR3, dz);
                if (ABS(dz) <= radius) {
                    gte_sqr0_b();
                    dy = cam->pos.vy;
                    gte_get(MAC2, sx);
                    gte_get(MAC3, sz);
                    gte_nop();
                    dy = y - dy;
                    if (r2 >= sx + sz && dy >= -down && dy <= up) {
                        return 1;
                    }
                }
            }
        }
    } while (cam++ != end);
    return 0;
}
#endif

#if STAGE == 1
s32 trace_shot_segment(VECTOR *from, VECTOR *to, VECTOR *hit, s32 flags, s32 type, s32 damage);

/* Runs trace_shot_segment from `from` to `to` and keeps its result and hit point in giant_robot_aim_result..giant_robot_aim_z. */
void giant_robot_aim_trace(VECTOR *from, VECTOR *to, s32 a) {
    s32 hit[3];

    giant_robot_aim_result = trace_shot_segment(from, to, (VECTOR *)hit, a, 0, 0);
    giant_robot_aim_x = hit[0];
    giant_robot_aim_y = hit[1];
    giant_robot_aim_z = hit[2];
}

/* Runs trace_shot_segment when the segment a-b, widened by 0x80 on each side, covers the point (giant_robot_aim_x, giant_robot_aim_z). */
s32 giant_robot_aim_test(VECTOR *from, VECTOR *to, VECTOR *hit, s32 arg3, s32 arg4, s32 arg5) {
    s32 min_x;
    s32 min_z;
    s32 max_x;
    s32 max_z;
    s32 bx;
    s32 bz;

    if (giant_robot_aim_result != 0) {
        min_x = from->vx;
        bx = to->vx;
        if (bx < min_x) {
            min_x = bx;
        }
        min_z = from->vz;
        bz = to->vz;
        if (bz < min_z) {
            min_z = bz;
        }
        max_x = from->vx;
        if (max_x < bx) {
            max_x = bx;
        }
        max_z = from->vz;
        if (max_z < bz) {
            max_z = bz;
        }
        min_x -= 0x80;
        max_x += 0x80;
        min_z -= 0x80;
        max_z += 0x80;
        if (giant_robot_aim_x >= min_x) {
            if (max_x >= giant_robot_aim_x && giant_robot_aim_z >= min_z && max_z >= giant_robot_aim_z) {
                return trace_shot_segment(from, to, hit, arg3, arg4, arg5);
            }
            return 0;
        }
    }
    return 0;
}
#endif

/* Queues a kind-3 request with the caller's three arguments. */
void req_queue_push_vec(s32 a, s32 b, s32 c) {
    req_queue_push(a, b, c, 3);
}
