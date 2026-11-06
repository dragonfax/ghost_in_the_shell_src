/* aim_helpers: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

/* Rotates the vector at src by the current GTE rotation matrix (4.12 fixed point).
 * The integer and fractional parts are rotated separately so the result keeps full precision. */
s32 *rot_vec_by_matrix(s32 *src, s32 *dst) {
    s32 rot_frac_x, rot_frac_y, rot_frac_z;
    s32 x = src[0];
    s32 y = src[1];
    s32 z = src[2];

    gte_set(IR1, x & 0xFFF);
    gte_set(IR2, y & 0xFFF);
    gte_set(IR3, z & 0xFFF);
    gte_rtir_sf0();
    x >>= 12;
    y >>= 12;
    z >>= 12;
    gte_get(MAC1, rot_frac_x);
    gte_get(MAC2, rot_frac_y);
    gte_get(MAC3, rot_frac_z);
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_rtir_sf0();
    rot_frac_x >>= 12;
    rot_frac_y >>= 12;
    rot_frac_z >>= 12;
    gte_get(MAC1, x);
    gte_get(MAC2, y);
    gte_get(MAC3, z);

    dst[0] = x + rot_frac_x;
    dst[1] = y + rot_frac_y;
    dst[2] = z + rot_frac_z;
    return dst;
}

void obj_vec_to_world_gte(Object *obj, s32 *vec) {
    s32 *m = (s32 *)scratch_top;
    s32 a, b, c;

    scratch_top += 0x20;
    rot_matrix(m, obj->yaw, -obj->pitch, obj->roll);
    gte_load_R012(m, a, b, c);
    gte_load_R34(m, a, b);
    rot_vec_by_matrix(vec, vec);
    scratch_top -= 0x20;
    vec[0] += obj->x >> 12;
    vec[1] += obj->y >> 12;
    vec[2] += obj->z >> 12;
}

void rot_compose_angles(s32 x, s32 y, s32 z, SVECTOR *rot) {
    RotMatrix *a;
    RotMatrix *b;
    s32 pitch, yaw, roll;

    a = scratch_alloc(0x40);
    b = (RotMatrix *)((u8 *)a + 0x20);
    rot_matrix(b, x, y, z);
    rot_matrix_b(a, rot->vy, rot->vx, rot->vz);
    mul_matrix(b, a, a);
    rot_matrix_to_angles(a, &pitch, &yaw, &roll);
    rot->vx = *(u16 *)&yaw;
    rot->vy = *(u16 *)&pitch;
    rot->vz = *(u16 *)&roll;
    scratch_top -= 0x40;
}

/* Fly/climb script op: aims x and z from the yaw (or from the object's position for mode 3),
 * clamps them to the arena and stores the results. The mode byte goes to 0x284, the last byte
 * of chaser's pad_27C (no named field there yet). */
s32 obj_set_move_mode(Object *obj, s32 mode) {
    s32 x;
    s32 z;
    s32 lim;
    u16 yaw;

    yaw = view_angles_get()[1];
    obj->vars.chaser.pad_27C[8] = mode;
    switch (mode) {
    case 3:
        x = obj->x >> 12;
        z = obj->z >> 12;
        if (is_outside_bounds(x, z) != 0) {
            obj->vars.chaser.pad_27C[8] = 4;
            x = (-0x2EE00);
            z = 0;
        }
        break;
    case 4:
        x = (-0x2EE00);
        z = 0;
        break;
    case 0:
        fly_move((s16)yaw, 0x800, &z, &x);
        x >>= 12;
        z >>= 12;
        break;
    case 1:
        fly_move((s16)yaw + 0x800, 0x800, &x, &z);
        x >>= 12;
        z >>= 12;
        break;
    }
    x = (-0x2F9B8) > MIN(x, (-0x2E248)) ? (-0x2F9B8) : MIN(x, (-0x2E248));
    z = MAX(MIN(z, 0xBB8), -0xBB8);
    obj->vars.fly.climb_step = z;
    obj->vars.snd.sound = x;
}

s32 obj_aim_at_target(Object *obj, s32 mode) {
    s32 obj_z = obj->z >> 12;
    s32 obj_x = obj->x >> 12;
    s32 *player = player_position();
    s32 dz;
    s32 dx;

    switch (mode) {
    case 3:
        dz = obj_z - player[2];
        dx = obj_x - player[0];
        break;
    case 0:
    case 1:
    case 4:
        /* Fixed target point stored in the object's vars. */
        dz = obj->vars.supermech.target_z - obj_z;
        dx = obj->vars.supermech.target_x - obj_x;
        if (length_sq(dz, dx, 0) <= 0x9C3F) {
            ((u8 *)obj->vars.words)[0x3C] = 2; /* unnamed byte flag */
        }
        break;
    case 2:
    default:
        dz = player[2] - obj_z;
        dx = player[0] - obj_x;
        break;
    }
    return atan2(dz, dx);
}

void obj_turn_toward_target(Object *obj, s32 mode, s32 step) {
    s32 old = obj->yaw;
    s32 raw = angle_approach(obj->yaw, (s16)obj_aim_at_target(obj, mode), step);
    s32 diff = (s16)raw - old;
    obj->yaw = raw;
    FAKE_OPAQUE(diff);
    obj->turn = diff;
}

extern s32 bounds_x_min;
extern s32 bounds_x_max;
extern s32 bounds_z_min;
extern s32 bounds_z_max;

void bounds_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    bounds_x_min = arg0;
    bounds_z_min = arg2;
    bounds_x_max = arg1;
    bounds_z_max = arg3;
}

extern s32 bounds_x_min;
extern s32 bounds_x_max;
extern s32 bounds_z_min;
extern s32 bounds_z_max;

s32 is_outside_bounds(s32 arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = arg0 < bounds_x_min;
    if (arg1 < bounds_z_min) {
        var_v1 = 1;
    }
    if (bounds_x_max < arg0) {
        var_v1 = 1;
    }
    if (bounds_z_max < arg1) {
        var_v1 = 1;
    }
    return var_v1;
}
