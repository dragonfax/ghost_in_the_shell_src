/* camera_follow: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void player_stage_reset(void) {
    player_model_pchr = model_slot_pchr(*(s32 *)get_ptr_entry_word2(1));
    cam_aim_blend = 0x1000;
    d_80120470 = 0xA0;
    cam_distance = 0x400;
    cam_offset_blend = 0;
    cam_offset_speed = 0;
    cam_stick_offset = 0;
    d_80136418 = 0;
    d_80136414 = 0;
    d_80136410 = 0;
    d_80136430 = 0;
    d_8013642C = 0;
    d_80136428 = 0;
    d_80136448 = 0;
    d_80136444 = 0;
    d_80136440 = 0;
    cam_view_state_table = 0;
    cam_view_handler0 = 0;
    cam_follow_blend = 0;
    d_8012049C = 0x120;
    cam_state = player_angles[0];
    d_80136408 = player_angles[1];
    player_roll = player_angles[2];
    set_player_mode_flags(0);
    player_mode_flags_saved = 0;
    player_ceiling_limit_set(0x7FFFF);
    pchr_set_entry_flags(player_model_pchr + 1, 0);
    player_model_enabled = 0;
    player_model_state = 1;
    player_model_on_flag = 0;
    d_8013644C = 0;
    d_80136450 = 0;
    cam_view_pos_set(0, 0, 0);
    cam_look_at_set(0, 0, 0);
    fade_level_set(0x1000);
    d_801364C8 = -1;
    d_801364E4 = -1;
    cam_view_update();
    fn_800DA718(0);
}

/* Sets camera `id` between the old and new view by fade_level: the position is blended linearly;
 * the direction aims at a blend of the old look-at point and a point 0x200 ahead of the new view,
 * with the blend factor eased through a sine. */
void cam_blend_view(s32 id) {
    s32 dx;
    s32 dy;
    s32 dz;
    s32 pitch;
    s32 yaw;
    s32 t;
    s32 x;
    s32 y;
    s32 z;
    s32 roll;

    t = fade_level;
    x = LERP(cam_view_pos_x, cam_dest_x >> 12, t);
    y = LERP(cam_view_pos_y, cam_dest_y >> 12, t);
    z = LERP(cam_view_pos_z, cam_dest_z >> 12, t);
    cam_set_pos(id, x, y, z);
    if (t == 0x1000) {
        roll = cam_blend_roll >> 12;
        yaw = cam_blend_yaw >> 12;
        pitch = cam_blend_pitch >> 12;
    } else {
        t = (s16)rcossin_tbl[t / 4 & 0xFFF];
        angles_to_vector(-cam_blend_yaw >> 12, -cam_blend_pitch >> 12, 0x200, &dx, &dy, &dz);
        dx = (dx >> 12) + (cam_dest_x >> 12);
        dy = (dy >> 12) + (cam_dest_y >> 12);
        dz = (dz >> 12) + (cam_dest_z >> 12);
        dx = LERP(cam_look_at_x, dx, t) - x;
        dy = LERP(cam_look_at_y, dy, t) - y;
        dz = LERP(cam_look_at_z, dz, t) - z;
        vector_to_angles(dx, dy, dz, &yaw, &pitch);
        yaw = -yaw;
        roll = ((cam_blend_roll << 8) >> 20) * t / 0x1000;
    }
    cam_set_rot(id, yaw, pitch, roll);
}

extern s32 player_xyz_y_word __asm__("player_xyz_y");
extern s32 player_xyz_z_word __asm__("player_xyz_z");
/* Points the camera along the player's yaw (blended toward cam_state by cam_follow_blend) and places it behind the
 * player: the offset pulled back and down by the blend, rotated into world space from the player's position. */
void cam_view_source_update(CamViewSource *view) {
    s32 ang[3];
    s32 *words; /* rotation matrix, then a second one at +0x20 */
    VECTOR *block;
    s32 *matrix;
    VECTOR *offset;
    s32 scale;
    s32 turn;
    s32 target;
    s32 base;
    s32 zoom;
    s32 tx, ty, tz;
    s16 rx, ry, rz;

    words = scratch_alloc(0x40);
    block = scratch_alloc(0x20);
    __asm__("" : "=r"(matrix) : "0"(words));
    offset = block + 1;
    turn = (0x1000 - cam_follow_blend) * 2;
    if (turn <= 0x1000) {
        scale = turn;
    } else {
        scale = 0x1000;
    }
    target = cam_state >> 12;
    base = player_angles[0] >> 12;
    turn = (((target - base) << 20) >> 20) * scale;
    ang[0] = turn / 4096 + base;
    rot_matrix(matrix, ang[0], 0, 0);
    rot_matrix(matrix + 8, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
    mul_matrix(matrix + 8, matrix, matrix);
    matrix_to_angles(matrix, &ang[0], &ang[1], &ang[2]);
    zoom = scale * 24;
    rx = -ang[1];
    ry = -ang[0];
    rz = -ang[2];
    view->pitch = rx;
    view->yaw = ry;
    view->roll = rz;
    offset->vx = 0;
    offset->vy = -0x86 - zoom / 4096;
    offset->vz = 0x10 - zoom / 4096;
    rot_load(words);
    tx = player_xyz[0] >> 12;
    ty = player_xyz_y_word >> 12;
    tz = player_xyz_z_word >> 12;
    gte_set_ctrl(TRX, tx);
    gte_set_ctrl(TRY, ty);
    gte_set_ctrl(TRZ, tz);
    rotate_point_inverse(offset, (VECTOR *)view); /* x, y, z */
    scratch_top -= 0x20;
    scratch_top -= 0x40;
}

/* Hit-distance probe from the camera: builds the player-rotation matrix in the
 * scratch block, then traces from a point under the camera to a probe point.
 * Returns the distance between the two trace ends, plus 0x5E. */
s32 cam_probe_distance(s32 probe_z, s32 probe_x) {
    VECTOR *matrix = scratch_alloc(0x20);
    VECTOR *base;
    VECTOR *probe;
    VECTOR *lift;
    register VECTOR *block asm("$2");
    register s32 cam_x asm("$4");
    register s32 cam_y asm("$2");
    register s32 zero asm("$8");
    s32 cam_z, dist;

    rot_matrix(matrix, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
    {
        volatile s32 *m = (volatile s32 *)matrix;
        s32 r0 = m[0], r1 = m[1], r2 = m[2];
        gte_set_ctrl(R11R12, r0);
        gte_set_ctrl(R13R21, r1);
        gte_set_ctrl(R22R23, r2);
        r0 = m[3];
        r1 = m[4];
        gte_set_ctrl(R31R32, r0);
        gte_set_ctrl(R33, r1);
    }
    scratch_top -= 0x20;
    block = (VECTOR *)scratch_top;
    scratch_top += 0x30;
    base = block;
    probe = base + 1;
    cam_x = cam_pos;
    cam_y = cam_pos_y;
    cam_z = cam_pos_z;
    cam_x >>= 12;
    cam_y >>= 12;
    cam_z >>= 12;
    gte_set_TR(cam_x, cam_y, cam_z);
    base->vx = 0;
    base->vy = -0x60;
    base->vz = 0;
    probe->vx = probe_x;
    probe->vy = -0x60;
    probe->vz = probe_z;
    rotate_point_inverse(base, base);
    rotate_point_inverse(probe, probe);
    lift = base + 2;
    lift->vx = 0;
    lift->vy = -0x3A0;
    lift->vz = 0;
    zero = 0;
    gte_set_TR(zero, zero, zero);
    rotate_point_inverse(lift, lift);
    if (probe_x != 0 || probe_z != 0) {
        trace_world(4, 0x40, base, probe, base);
    }
    probe->vx = base->vx + probe[1].vx;
    probe->vy = base->vy + probe[1].vy;
    probe->vz = base->vz + probe[1].vz;
    trace_world(4, 0x3C, base, probe, probe);
    dist = isqrt(length_sq(probe->vx - base->vx, probe->vy - base->vy, probe->vz - base->vz));
    scratch_top -= 0x30;
    return dist + 0x5E;
}

/* length * (a swing of the angle: sine table up to 0x800, its mirror above) / 0x1000 - length. */
s32 sine_swing_offset(s32 length, s32 angle) {
    s32 index;
    s32 product;
    s32 factor;

    index = angle & 0xFFF;
    if (index <= 0x800) {
        product = (length / 2) * (s16)rcossin_tbl[index];
    } else {
        factor = (s16)rcossin_tbl[index];
        factor *= 2;
        product = length * factor;
    }
    return -length + product / 0x1000;
}

/* atan2 of (sqrt(half^2 - sum^2), sum), where sum = a + b and half = b / 2, or b * 2 while sum < 0. */
s32 circle_intersect_angle(s32 a, s32 b) {
    s32 sum = a + b;
    s32 half;

    if (sum < 0) {
        half = b * 2;
    } else {
        half = b / 2;
    }
    return atan2(isqrt((half * half) - (sum * sum)), sum);
}

/* player_xyz's three words read volatile, one symbol each: the original reloads them for every use */
extern volatile s32 player_x_live __asm__("player_xyz");
extern volatile s32 player_y_live __asm__("player_xyz_y");
extern volatile s32 player_z_live __asm__("player_xyz_z");
s32 player_ceiling_probe(void) {
    volatile s32 *from = scratch_alloc(0x20);
    volatile s32 *to = from + 4;
    s32 r = player_y_live >> 12;
    if (player_mode_flags() & 2) {
        if (player_landed == 0 || (u32)((player_ground_id >> 8) - 1) < 0xFF) {
            from[0] = player_x_live >> 12;
            from[1] = player_y_live >> 12;
            from[2] = player_z_live >> 12;
            to[0] = player_x_live >> 12;
            to[1] = (player_y_live >> 12) + 0x400;
            to[2] = player_z_live >> 12;
            trace_world(4, 4, (void *)from, (void *)to, (void *)to);
            r = (r + to[1] * 3) / 4;
            r = r < player_ceiling_limit_get() ? r : player_ceiling_limit_get();
        }
    }
    scratch_top -= 0x20;
    return r;
}

/* Moves `cur` (negative: not set yet, start at `target`) toward `target`: by a fraction of the gap
 * (1/16 at or above 0xE0, else 1/4), with a minimum step, and jumps there when within the minimum. */
s32 value_approach(s32 target, s32 cur) {
    s32 min_step = 8;
    s32 divisor;
    s32 delta;
    s32 step;

    if (cur < 0) {
        cur = target;
    }
    divisor = 16;
    if (target < 0xE0) {
        min_step = 0x30;
        divisor = 4;
    }
    delta = target - cur;
    if (abs(delta) > min_step) {
        step = delta / divisor;
        if (abs(step) > min_step) {
            delta = step;
        } else {
            delta = delta > 0 ? min_step : -min_step;
        }
    }
    return cur + delta;
}

/* Places the camera behind the player: eases the probe distance (cam_distance), builds the view angles
 * from cam_state, puts the eye on a sphere around a pivot above the player, rotates both into the
 * player's frame, pulls the eye in to what trace_world leaves free, smooths that distance in out->dist
 * and blends out's position from the pivot toward the eye. Returns the eye distance. */
s32 cam_place_behind_player(CamViewSource *out) {
    s32 *cam_mtx = scratch_alloc(0x40);
    VECTOR *pivot = scratch_alloc(0x30);
    VECTOR *eye;
    VECTOR *dir;
    s32 ceiling;
    s32 probe;
    s32 mag;
    s32 off_z;
    s32 full;
    s32 swing, base_y;
    s32 amount;
    s32 *player_mtx;
    s32 r0, r1, r2;
    s32 yaw, pitch, roll;
    s32 ang, sum, roll_ang;
    s32 tr_x, tr_z;
    s32 reach;
    s32 radius;
    s32 off_x;
    s32 eased_pitch;
    s32 neg_yaw, neg_pitch, neg_roll;
    register s32 *cam asm("$20") = &cam_state; /* yaw, pitch, roll */
    PlayerObj *player = &player_obj;
    PlayerObj *player_rot = player;

    ceiling = player_ceiling_probe();
    radius = 0x140;
    probe = cam_probe_distance(0, 0);
    eye = pivot + 1;
    dir = pivot + 2;
    amount = probe - cam_distance;
    if (amount < 0) {
        if (player_landed != 0) {
            mag = ABS(amount);
            cam_distance = mag < 0x19 ? cam_distance - mag : cam_distance - 0x18;
        } else {
            cam_distance = cam_distance + amount;
        }
    } else {
        mag = ABS(amount);
        cam_distance = mag < 0x19 ? cam_distance + mag : cam_distance + 0x18;
    }
    ((CamDistance *)&cam_distance)->v = MIN(cam_distance, 0x240) < 0 ? 0 : MIN(cam_distance, 0x240);
    /* ang, reach: set more than once on purpose (sched1 keeps their loads in source order); the
     * y blend at the end reuses them, which puts its values in the original's registers */
    ang = cam[1];
    ang >>= 12;
    reach = d_80120470;
    ang -= reach;
    ang &= 0xFFF;
    roll_ang = cam[2];
    roll_ang >>= 12;
    roll_ang &= 0xFFF;
    yaw = cam[0] >> 12 & 0xFFF;
    roll = roll_ang;
    pitch = ang;
    sum = ang + cam_offset_blend;
    sum = (s32)(sum << 20) >> 20;
    pitch = sum;
    ang = MIN(sum, 0x400) < -0x800 ? -0x800 : MIN(sum, 0x400);
    pitch = ang;
    if (cam_distance < 0x240) {
        amount = cam_distance - 0x120;
        if (amount < 0) {
            amount = 0;
        }
        pitch = ((s32)(pitch << 20) >> 20) * amount / 288;
        cam_offset_speed = ((s32)(cam_offset_speed << 20) >> 20) * amount / 288;
    }
    off_z = radius * cos_table[(yaw + 0x800) & 0xFFF].value / 0x1000 * cos_table[pitch & 0xFFF].value / 0x1000;
    off_x = radius * (s16)rcossin_tbl[(yaw + 0x800) & 0xFFF] / 0x1000 * cos_table[pitch & 0xFFF].value / 0x1000;
    swing = sine_swing_offset(0xD9, pitch);
    base_y = -0xB9;
    if (player->x110 == 0) {
        if (base_y < -probe) {
            base_y = -probe;
        }
        if (swing < -probe) {
            swing = -probe;
        }
    }
    pivot->vx = 0;
    pivot->vy = base_y;
    pivot->vz = 0;
    eye->vx = off_x;
    eye->vy = swing;
    eye->vz = off_z;
    amount = CLAMP_HI(cam_follow_blend * 2, 0x1000);
    full = 0x1000;
    eased_pitch = ((s32)(pitch << 20) >> 20) * (full - amount) / 0x1000;
    pitch = eased_pitch & 0xFFF;
    rot_matrix(cam_mtx, yaw, pitch, roll);
    player_mtx = cam_mtx + 8;
    rot_matrix(player_mtx, -player_rot->rot[1], -player_rot->rot[0], -player_rot->rot[2]);
    mul_matrix(player_mtx, cam_mtx, cam_mtx);
    matrix_to_angles(cam_mtx, &yaw, &pitch, &roll);
    neg_pitch = -pitch;
    neg_yaw = -yaw;
    neg_roll = -roll;
    do { /* loop notes: a scheduling barrier the original's order needs */
    } while (0);
    out->pitch = neg_pitch;
    out->yaw = neg_yaw;
    out->roll = neg_roll;
    gte_set_R012(r0, r1, r2, player_mtx[0], player_mtx[1], player_mtx[2]);
    gte_set_R34(r0, r1, player_mtx[3], player_mtx[4]);
    tr_x = player->x >> 12;
    tr_z = player->z >> 12;
    gte_set_ctrl(TRX, tr_x);
    gte_set_ctrl(TRY, ceiling);
    gte_set_ctrl(TRZ, tr_z);
    rotate_point_inverse(pivot, pivot);
    rotate_point_inverse(eye, eye);
    dir->vx = eye->vx - pivot->vx;
    dir->vy = eye->vy - pivot->vy;
    dir->vz = eye->vz - pivot->vz;
    radius = isqrt(length_sq(dir->vx, dir->vy, dir->vz)) + 0x40;
    VectorNormal(dir, (SVECTOR *)dir);
    eye->vx = pivot->vx + radius * dir->vx / 0x1000;
    eye->vy = pivot->vy + radius * dir->vy / 0x1000;
    eye->vz = pivot->vz + radius * dir->vz / 0x1000;
    if (fade_level_get() == full) {
        trace_world(4, 0x3C, pivot, eye, eye);
    }
    reach = isqrt(length_sq(eye->vx - pivot->vx, eye->vy - pivot->vy, eye->vz - pivot->vz)) - 0x40;
    if (reach < 0) {
        reach = 0;
    }
    radius = reach;
    amount = out->dist = value_approach(radius, out->dist);
    eye->vx = pivot->vx + amount * dir->vx / 0x1000;
    eye->vy = pivot->vy + amount * dir->vy / 0x1000;
    eye->vz = pivot->vz + amount * dir->vz / 0x1000;
    amount = CLAMP_HI(cam_follow_blend * 2, 0x1000);
    amount = 0x1000 - amount;
    out->x = LERP(pivot->vx, eye->vx, amount);
    reach = eye->vy;
    ang = pivot->vy;
    out->y = LERP(ang, reach, amount);
    out->z = LERP(pivot->vz, eye->vz, amount);
    scratch_top -= 0x30;
    scratch_top -= 0x40;
    return radius;
}

/* State machine: cam_view_state_table holds the current state index, followed by one handler
 * address per state (0 = not yet entered). Handlers are labels in this function. */
void cam_view_update(void)
{
    s32 *state_tab;
    s32 mode;
    s32 handler;
    CamViewSource *src;
    CamViewState *cam;
    s32 pad_stack[2]; /* the original frame is 8 bytes larger than the locals need */

    fn_800DA718(1);
    cam_view_source_update(&cam_view_src_model);
    mode = cam_place_behind_player(&cam_view_src_default);
    fn_800DA718(0);
    cam = (CamViewState *)&cam_state;
    if (fade_level_get() < 0x1000) {
        mode = 0x121;
        cam_follow_blend = 0;
        cam_view_state_table = 0;
        cam_view_handler0 = 0;
    }
    state_tab = &cam_view_state_table;

dispatch:
    handler = state_tab[1 + state_tab[0]];
    if (handler != 0) {
        goto *(void *)handler;
    }
store_a:
    state_tab[1 + state_tab[0]] = (s32)&&state_a;
state_a:
    if (!(player_mode_flags() & 9) && mode >= 0xE0) {
        goto end;
    }
state_b:
    state_tab[1 + state_tab[0]] = (s32)&&state_c;
state_c:
    {
        s32 cur = cam_follow_blend;
        s32 step;

        if (cur >= 0x800) {
            cam_follow_blend = cur + 0x100;
        } else {
            step = (mode < 0x70) ? 0x100 : 0xAA;
            cam_follow_blend = cur + step;
        }
    }
    if (cam_follow_blend < 0x1000) {
        goto end;
    }
    state_tab[1 + state_tab[0]] = (s32)&&state_f;
state_f:
    if (player_mode_flags() & 9) {
        goto end;
    }
    if (mode < 0x120) {
        goto end;
    }
    state_tab[1 + state_tab[0]] = (s32)&&state_g;
state_g:
    if (mode < 0xE0) {
        goto state_b;
    }
    {
        s32 cur = cam_follow_blend;

        if (cur < 0x800) {
            cam_follow_blend = cur - 0xAA;
        } else {
            cam_follow_blend = cur - 0x100;
        }
    }
    if (cam_follow_blend <= 0) {
        goto store_a;
    }
end:
    {
        s32 clamped = cam_follow_blend;
        s32 hi;

        if (clamped > 0x1000) {
            clamped = 0x1000;
        }
        hi = cam_follow_blend;
        if (hi > 0x1000) {
            hi = 0x1000;
        }
        if (hi < 0) {
            clamped = 0;
        }
        cam_follow_blend = clamped;
    }
    if (cam_follow_blend >= 0x800 && player_model_state != 0) {
        player_model_enable(1);
        player_model_on_flag = 1;
        src = &cam_view_src_model;
    } else {
        player_model_enable(0);
        player_model_on_flag = 0;
        src = &cam_view_src_default;
    }
    cam->yaw = (s32)src->yaw << 12;
    cam->pitch = (s32)src->pitch << 12;
    cam->roll = (s32)src->roll << 12;
    cam->pos_x = src->x << 12;
    cam->pos_y = src->y << 12;
    player_mode_flags_saved = player_mode_bits;
    cam->pos_z = src->z << 12;
}

void approach_value(s32 *value, s32 target, s32 accel, s32 limit) {
    s32 v;
    s32 mag;
    s32 mag_target;
    s32 neg_limit;

    v = *value;
    if (target > 0) {
        if (v >= 0) {
            if (v < target) {
                v += accel;
            } else if (target < v) {
                v = target / 4;
            }
        } else {
            v += accel * 2;
        }
    } else if (target < 0) {
        if (v > 0) {
            v -= accel * 2;
        } else {
            mag_target = -target;
            do { } while (0);
            mag = -v;
            if (mag < mag_target) {
                mag += accel;
            } else if (mag_target < mag) {
                mag = mag_target / 4;
            }
            mag_target = -mag;
            v = mag_target;
        }
    } else {
        v = 0;
    }
    if (limit < v) {
        v = limit;
    }
    neg_limit = -limit;
    if (neg_limit < v) {
        neg_limit = v;
    }
    *value = neg_limit;
}

/* Angle (12-bit, from atan2 of view-space z and y) toward the last flagged actor within 0xC00 of the
 * player, in view space; 0 if none. */
s32 actor_aim_angle(void) {
    VECTOR *rel;
    s32 *pos;
    s32 *view;
    Object *o;
    s32 px, py, pz;
    s32 angle;
    s32 dx, dy, dz, radius;
    s32 m0, m1, m2;
    s32 range_sq;

    scratch_top += 0x20;
    rel = (VECTOR *)scratch_alloc(0x20);
    pos = player_position();
    px = pos[0];
    py = pos[1];
    pz = pos[2];
    angle = 0;
    range_sq = 0x900000;
    view = view_matrix_t_get();
    gte_set_R012(m0, m1, m2, view[0], view[1], view[2]);
    gte_set_R34(m0, m1, view[3], view[4]);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    o = *(Object **)get_obj_list_actors();
    while (*(s32 *)o != 0) {
        if ((u8)o->unk_17A != 0 && test_bit(o->flags, 5)) {
            radius = isqrt(length_sq(o->width, (s16)o->height / 2, o->unk_1E8[0]));
            dy = (o->y >> 12) - (s16)o->height / 2 - py;
            dz = (o->z >> 12) - pz;
            dx = (o->x >> 12) - px;
            /* range_sq as a variable keeps the compare as slt/beqz (a literal folds to > 0x8FFFFF) */
            if (ABS(dx) - radius < 0xC01 && ABS(dy) - radius < 0xC01 && ABS(dz) - radius < 0xC01
                && length_sq(dx, dy, dz) - radius < range_sq) {
                rel->vx = dx;
                rel->vy = dy;
                rel->vz = dz;
                rotate_point_inverse(rel, rel);
                dz = rel->vz;
                dy = rel->vy;
                if (dz >= 0x80) {
                    angle = atan2(dz, dy) << 20 >> 20;
                }
            }
        }
        o = *(Object **)o;
    }
    scratch_top -= 0x40;
    return angle;
}

void player_aim_settle(void) {
    s32 level;

    if (player_landed != 0 || (get_player_status() & 0x100) || (player_mode_flags() & 4)) {
        cam_aim_blend = CLAMP_HI(cam_aim_blend + 0x100, 0x1000);
        if (abs(cam_offset_speed) < 0x10) {
            cam_offset_speed = 0;
        } else {
            cam_offset_speed = cam_offset_speed * 7 / 8;
        }
    } else {
        level = cam_aim_blend - 0x200;
        if (level < 0) {
            level = 0;
        }
        cam_aim_blend = level;
        if (player_y_speed < 0) {
            cam_offset_speed = CLAMP_HI(cam_offset_speed + 4, 0x40);
        } else {
            cam_offset_speed = MAX(cam_offset_speed - 0xC, -0x200);
        }
    }
}

/* Moves cam_stick_offset by 10 towards the stick direction when it is past 0x118 either way, else back towards 0. */
void stick_offset_step(void) {
    s32 stick;
    s32 a;

    if (get_player_status() & 0x20) {
        stick = 0;
    } else {
        stick = actor_aim_angle();
    }
    if ((u32)(stick + 0x118) >= 0x231) {
        if (stick > 0) {
            cam_stick_offset = cam_stick_offset - 10;
        } else {
            cam_stick_offset = cam_stick_offset + 10;
        }
        cam_stick_offset = MAX(MIN(cam_stick_offset, 0xD0), -0xD0);
        return;
    }
    if (cam_stick_offset < 0) {
        a = abs(cam_stick_offset);
        cam_stick_offset = a < 11 ? cam_stick_offset + a : cam_stick_offset + 10;
    } else {
        a = abs(cam_stick_offset);
        cam_stick_offset = a < 11 ? cam_stick_offset - a : cam_stick_offset - 10;
    }
}

static inline s32 wrap24(s32 from, s32 to) {
    s32 d = (to - from) & 0xFFFFFF;
    if (d > 0x7FFFFF) {
        d += 0xFF000000;
    }
    return d;
}
void cam_follow_update(void) {
    s32 *cam = &cam_state; /* yaw, pitch, roll, their speeds; [0x12] resume state */
    PlayerObj *p = &player_obj;
    s32 *resume;
    s32 spin, speed, angle, dist, step;
    s32 unused[2];

    player_aim_settle();
    stick_offset_step();
    cam_offset_blend = (cam_stick_offset - cam_offset_speed) * cam_aim_blend / 0x1000 + cam_offset_speed;
    resume = &cam[0x12];
    if (resume[1 + resume[0]] != 0) {
        goto *(void *)resume[1 + resume[0]];
    }
    resume[1 + resume[0]] = (s32)&&follow;
follow:
    if (!(get_player_status() & 0x40)) {
        spin = ABS(p->spin_yaw);
        speed = 0x10000;
        if (spin > 0xFFFF) {
            speed = spin;
        }
        approach_value(&cam[3], wrap24(cam[0], p->yaw), speed / 16, speed);
        approach_value(&cam[4], wrap24(cam[1], p->pitch), 0x1800, 0x10000);
        approach_value(&cam[5], wrap24(cam[2], p->roll), 0x1800, 0x10000);
        cam[0] = angle_approach(cam[0] >> 12, p->yaw >> 12, ABS(cam[3] >> 12)) << 12;
        cam[1] = angle_approach(cam[1] >> 12, p->pitch >> 12, 0x1000) << 12;
        cam[2] = angle_approach(cam[2] >> 12, p->roll >> 12, ABS(cam[5] >> 12)) << 12;
        cam_view_update();
        return;
    }
    cam[0] = -cam[12];
    cam[1] = -cam[13];
    cam[2] = -cam[14];
    if (player_model_on_get()) {
        cam[1] = 0xFFC80000;
        cam[7] += 0xFFF80000;
        player_model_enable(0);
        player_model_on_flag = 0;
    }
    resume[1 + resume[0]] = (s32)&&recenter;
recenter:
    angle = (cam[1] << 8) >> 20;
    dist = ABS(-0x380 - angle) / 16;
    if (dist >= 0x41) step = 0x40; else step = dist;
    if ((dist < 0x41 ? dist : 0x40) <= 0) step = 1;
    cam[1] = angle_approach(cam[1] >> 12, -0x380, step) << 12;
    angle = (cam[2] << 8) >> 20;
    dist = ABS(-angle) / 16;
    if (dist >= 0x41) step = 0x40; else step = dist;
    if ((dist < 0x41 ? dist : 0x40) <= 0) step = 1;
    cam[2] = angle_approach(cam[2] >> 12, 0, step) << 12;
    cam[0] += 0x8000;
    cam[7] += 0xC000;
    cam[13] = -cam[1];
    cam[14] = -cam[2];
    cam[12] = -cam[0];
}

void anim_obj_phase2(Object *obj, ObjHandler *handler) {
    s32 timer;
    s16 prev;
    s32 *vec;
    s32 *models;
    s32 *anim;
    void (*callback)(Object *);


    timer = obj->vars.anim_obj.timer;
    prev = obj->vars.anim_obj.timer;
    obj->vars.anim_obj.frame += 1;
    if (timer > 0) {
        obj->vars.anim_obj.timer = prev - 1;
    }
    vec = (s32 *)scratch_alloc(0x10);
    anim = (s32 *)obj->vars.anim_obj.anim_data;
    anim_track_sample(obj->vars.anim_obj.frame, *anim, (TrackKey *)(anim + 1), vec);
    cam_view_pos_set(vec[0], vec[1], vec[2]);
    models = (s32 *)obj->vars.anim_obj.models;
    if (models != NULL) {
        anim_track_sample(obj->vars.anim_obj.frame, *models, (TrackKey *)(models + 1), vec);
        cam_look_at_set(vec[0], vec[1], vec[2]);
    } else {
        cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
    }
    scratch_top -= 0x10;
    if (obj->vars.anim_obj.timer <= 0) {
        fade_level_set(fade_level_get() + obj->vars.enemy.sound_channel[0]);
    }
    callback = (void (*)(Object *))obj->vars.anim_obj.callback;
    if (callback != NULL) {
        callback(obj);
    }
    if (fade_level_get() >= 0x1000) {
        set_d_801202C8(1);
        set_stage_flags(get_stage_flags() & ~0x28);
        obj_free(obj);
    }
}

/* Spawns a handler object: its vars take the four arguments (the sound handle at 0x24C), the handler
 * states are cleared and the third handler runs anim_obj_phase2. Returns 1, or 0 when no object is free. */
s32 anim_obj_spawn(s32 unk_248, s32 sound, s16 unk_252, s16 unk_254, s32 unk_258) {
    Object *obj = obj_new();

    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = anim_obj_phase2;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = NULL;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.anim_obj.anim_data = unk_248;
    obj->vars.snd.sound = sound;
    obj->vars.anim_obj.frame = 0;
    obj->vars.anim_obj.timer = unk_252;
    obj->vars.anim_obj.unk_254 = unk_254;
    obj->vars.anim_obj.callback = unk_258;
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    fade_level_set(0);
    return 1;
}

void fn_80116720(void) {

}
