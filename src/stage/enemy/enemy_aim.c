/* enemy_aim: one of the original source files (scripts/objmap.py); s01, s02, s03, s04, s05, s06, s07, s08, s09, s10, s11, s12. */

#include "stage.h"

void vec3_rotate(s32 yaw, s32 pitch, s32 roll, s32 *px, s32 *py, s32 *pz) {
    s32 x;
    s32 y;
    s32 z;
    s32 idx;
    s32 tmp;
    s32 cos_v;
    s32 sin_v;

    x = *px;
    y = *py;
    z = *pz;

    idx = roll & 0xFFF;
    if (idx != 0) {
        cos_v = cos_table[idx].value;
        sin_v = (s16)rcossin_tbl[idx];
        tmp = x;
        x = ((cos_v * tmp) - (sin_v * y)) >> 12;
        y = ((sin_v * tmp) + (cos_v * y)) >> 12;
    }
    idx = pitch & 0xFFF;
    if (idx != 0) {
        cos_v = cos_table[idx].value;
        sin_v = (s16)rcossin_tbl[idx];
        tmp = y;
        y = ((cos_v * tmp) - (sin_v * z)) >> 12;
        z = ((sin_v * tmp) + (cos_v * z)) >> 12;
    }
    idx = yaw & 0xFFF;
    if (idx != 0) {
        cos_v = cos_table[idx].value;
        sin_v = (s16)rcossin_tbl[idx];
        tmp = z;
        z = ((cos_v * tmp) - (sin_v * x)) >> 12;
        x = ((sin_v * tmp) + (cos_v * x)) >> 12;
    }
    *px = x;
    *py = y;
    *pz = z;
}

/* Combines the base rotation with a turn of -rot->vy about y (m = R(base) * Ry(-rot.vy), on the scratchpad)
 * and writes the resulting angles back into rot. */
void rot_compose_base_yaw(SVECTOR *base, SVECTOR *rot) {
    RotMatrix *m = scratch_alloc(0x40);
    RotMatrix *yaw_m = m + 1; /* Ry(-rot.vy) */
    s32 yaw;
    s32 pitch;
    s32 roll;
    s32 sc;

    yaw = rot->vy;
    pitch = rot->vx;
    roll = rot->vz;
    rot_matrix(m, base->vy, base->vx, base->vz);
    sc = rcossin_tbl[-rot->vy & 0xFFF];
    yaw_m->m[0][1] = 0;
    yaw_m->m[1][0] = 0;
    yaw_m->m[1][1] = 0x1000;
    yaw_m->m[1][2] = 0;
    yaw_m->m[2][1] = 0;
    {
        s16 cos = (u32)sc >> 16;
        s16 neg_sin = -sc;

        yaw_m->m[0][0] = cos;
        yaw_m->m[0][2] = sc;
        yaw_m->m[2][0] = neg_sin;
        yaw_m->m[2][2] = cos;
    }
    mul_matrix(m, yaw_m, m);
    matrix_to_angles(m, &yaw, &pitch, &roll);
    scratch_top -= 0x40;
    rot->vy = yaw;
    rot->vx = pitch;
    rot->vz = roll;
}

/* Moves unk_214 and unk_21C one step (0x1000) towards the targets, and zeroes them when the flags are set. */
void obj_step_axes_toward(Object *obj, s32 target_a, s32 target_b) {
    if (obj->accel_z < target_b) {
        obj->accel_z += 0x1000;
    }
    if (target_b < obj->accel_z) {
        obj->accel_z -= 0x1000;
    }
    if (obj->accel_x < target_a) {
        obj->accel_x += 0x1000;
    }
    if (target_a < obj->accel_x) {
        obj->accel_x -= 0x1000;
    }
    if (obj->blocked_z != 0) {
        obj->accel_z = 0;
    }
    if (obj->blocked_x != 0) {
        obj->accel_x = 0;
    }
}

/* Sets the object's falling speed (vy) toward height `target` (whole units). */
void obj_set_fall_speed(Object *obj, s32 speed, s32 target) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 x = obj->vx;
    s32 step = speed << 12;

    pos->y = step;
    pos->x = x;
    pos->z = obj->vz;
    if ((obj->y >> 12) == target) {
        obj->vy = 0;
    } else if (!(target < (obj->y >> 12)) && !obj_probe_hit(obj, pos, 1)) {
        obj->vy = step;
    } else {
        obj->vy = -step;
    }
    scratch_top -= 0x10;
}

void obj_aim_and_turn(Object *obj, void *aim_slot, s16 aim_step, s16 yaw_step) {
    s32 old_yaw = obj->yaw;
    s16 target;
    s16 new_yaw;
    s32 turn;
    s32 z;

    switch (obj->unk_242) {
    case 0:
        z = obj->z;
        target = atan2((cam_pos_z - z) >> 12, (cam_pos - obj->x) >> 12);
        break;
    case 1:
        target = atan2((obj->placement->z >> 12) - (obj->z >> 12), (obj->placement->x >> 12) - (obj->x >> 12));
        break;
    default:
        return;
    }
    *(s16 *)aim_slot = angle_approach(*(s16 *)aim_slot, target, aim_step);
    new_yaw = angle_approach(obj->yaw, obj_angle_wobble(obj, target), yaw_step);
    turn = new_yaw;
    obj->yaw = new_yaw;
    turn -= old_yaw;
    obj->turn = turn;
}

/* Eases obj->pitch back to 0 while speed is 0, else steps it toward -limit or +limit. */
void obj_ease_pitch(Object *obj, s16 step, s16 limit) {
    s32 p1, p2, p3, p4;

    if (obj->speed == 0) {
        p1 = obj->pitch;
        if (p1 > 0) {
            obj->pitch = p1 - step;
        }
        p2 = obj->pitch;
        if (p2 < 0) {
            obj->pitch = p2 - -step;
        }
    }
    if (obj->speed < 0) {
        p3 = obj->pitch;
        if (-limit < p3) {
            obj->pitch = p3 - step;
        }
    }
    if (obj->speed > 0) {
        p4 = obj->pitch;
        if (p4 < limit) {
            s16 cur = p4; /* an s16 operand keeps `p4 + step` in this order */
            obj->pitch = cur + step;
        }
    }
}

/* Leans the object (roll) into a yaw change toward *prevYaw, eases it back
 * otherwise, clamps it within +-limit and records the current yaw in *prevYawSlot.
 * "- -step" (not "+ step") keeps roll as the first addu operand. */
void obj_lean_into_turn(Object *obj, void *prevYawSlot, s16 step, s16 limit)
{
    s16 *prevYaw = prevYawSlot; /* callers keep it in various vars slots */
    s32 roll; /* lean while turning */
    s32 easeRoll; /* lean while easing back to level */

    if (obj->yaw == *prevYaw || obj->speed == 0) {
        easeRoll = obj->roll;
        if (easeRoll > 0) {
            obj->roll = easeRoll - step;
        }
        easeRoll = obj->roll;
        if (easeRoll < 0) {
            obj->roll = easeRoll - -step;
        }
    } else {
        if (*prevYaw < obj->yaw) {
            roll = obj->roll;
            if (roll < limit) {
                obj->roll = roll - -step;
            }
        }
        if (obj->yaw < *prevYaw) {
            roll = obj->roll;
            if (-limit < roll) {
                obj->roll = roll - step;
            }
        }
    }
    if (obj->roll > limit) {
        obj->roll = limit - 1;
    }
    if (obj->roll < -limit) {
        obj->roll = 1 - limit;
    }
    *prevYaw = obj->yaw;
}

/* Nonzero when the player (cam_pos/8C: its x and z) is within `range` of the heading `center` as seen
 * from the object and the object's slope from point_to_view_angles is outside 0x400..0xC00. */
s32 obj_player_in_arc(Object *obj, s32 center, s32 range) {
    s32 slope, unused;
    s32 yaw;
    s32 result = 0;
    s32 z;

    z = obj->z;
    yaw = atan2((cam_pos_z - z) >> 12, (cam_pos - obj->x) >> 12);
    point_to_view_angles(obj->x >> 12, obj->y >> 12, obj->z >> 12, &slope, &unused);
    if (center + range > (s16)yaw) {
        if ((s16)yaw > center - range) {
            if (slope >= 0x400 && slope <= 0xC00) {
            } else {
                result = 1;
            }
        }
    }
    return result;
}

/* Traces from the object up to its position plus `dir` (whole units); true if the trace hit. */
s32 obj_probe_hit(Object *obj, Vec3 *dir, s32 flags) {
    TraceScratch *trace = scratch_alloc(0x30);
    s32 hit;

    trace->from.x = obj->x >> 12;
    trace->from.y = (obj->y >> 12) + (s16)obj->height;
    trace->from.z = obj->z >> 12;
    trace->to.x = trace->from.x + (dir->x >> 12);
    trace->to.y = trace->from.y + (dir->y >> 12);
    trace->to.z = trace->from.z + (dir->z >> 12);
    hit = trace_world(8, flags, &trace->from, &trace->to, &trace->hit);

    scratch_top -= 0x30;
    return hit != 0;
}

/* Adds a spark record at (x, y + y_offset, z), with the rotation words and value/colour. */
void spark_add_y_offset(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour, s32 y_offset) {
    spark_add(x, y + y_offset, z, ry, rx, rz, value, colour);
}
