/* mover: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void mover_reset(void) {
    mover_offset_set(0, 0, 0);
    mover_angles_set(0, 0, 0);
    mover_range_set(0x200, 0x800);
}

/* Stores two values (negatives cut to 0) in ascending order. */
void mover_range_set(s32 a, s32 b) {
    s32 lo = NOT_NEGATIVE(a);
    s32 hi;

    a = lo;
    hi = NOT_NEGATIVE(b);
    b = hi;
    if (b < a) {
        a = b;
        b = lo;
    }
    mover_min_dist = a;
    mover_max_dist = b;
}

void mover_offset_set(s32 x, s32 y, s32 z) {
    mover_offset_x = x;
    mover_offset_y = y;
    mover_offset_z = z;
}

s32 *mover_offset_ptr(void) {
    return &mover_offset_x;
}

void mover_angles_set(s32 a, s32 b, s32 c) {
    mover_angle_b = b;
    mover_angle_a = a;
    mover_angle_c = c;
    rot_matrix_b(mover_rot_matrix, a, b, c);
    transpose_matrix(mover_rot_matrix, mover_rot_matrix_inv);
}

s16 *mover_angles_ptr(void) {
    return &mover_angle_b;
}

/* Rotates the vector at src by the current GTE rotation matrix (4.12 fixed point).
 * The integer and fractional parts are rotated separately so the result keeps full precision. */
s32 *rotate_vector_precise(s32 *src, s32 *dst) {
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

void mover_set(Mover *mover, s32 distance, s32 yaw, s32 pitch) {
    s32 nearest;
    s32 farthest;
    s32 result;

    farthest = mover_max_dist << 12;
    if (farthest < distance) {
        distance = farthest;
    }
    nearest = mover_min_dist << 12;
    result = nearest;
    if (nearest < distance) {
        result = distance;
    }
    pitch = (pitch << 8) >> 8;
    mover->yaw = (yaw << 8) >> 8;
    mover->distance = result;
    pitch = MAX(MIN(pitch, 0x400000), -0x400000);
    mover->pitch = pitch;
}

/* Moves the mover by the deltas: each one is added to the mover's current distance, yaw and pitch. */
void mover_move(Mover *m, s32 add_distance, s32 add_yaw, s32 add_pitch) {
    mover_set(m, add_distance + m->distance, add_yaw + m->yaw, add_pitch + m->pitch);
}

void mover_apply(Mover *mover, PlayerObj *p) {
    u32 x = p->pos[0];
    u32 y = p->pos[1];
    u32 z = p->pos[2];

    mover_calc_pos(mover, p->pos);
    mover_set_rot(mover, p);
    p->y_max = 0x7FFF;
    p->y_min = -0x7FFF;
    p->flags = 0;
    p->x_max = 0;
    p->unk_60 = 0;
    p->ground = 0;
    p->x_min = 0;
    p->unk_70 = 0;
    p->unk_74 = 0;
    p->delta[0] = (p->pos[0] - x) >> 12;
    p->delta[1] = (p->pos[1] - y) >> 12;
    p->delta[2] = (p->pos[2] - z) >> 12;
}

/* Turns the mover's yaw/pitch/distance (20.12) into a world-space position in pos,
 * rotates it by the inverse mover rotation and adds the mover offset. */
void mover_calc_pos(Mover *mover, s32 *pos) {
    Vec3 v;
    s32 x, y, z;
    s16 *rot_inv;
    s32 distance = mover->distance;
    s32 yaw = mover->yaw;
    s32 pitch = mover->pitch;

    angles_to_vector(yaw >> 12, pitch >> 12, distance >> 12, &v.x, &v.y, &v.z);
    /* The copies into x, y, z and the matrix address come before the stores: the original's schedule. */
    x = v.x;
    y = v.y;
    z = v.z;
    rot_inv = mover_rot_matrix_inv;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    /* Loads the inverse rotation matrix into the GTE control registers (RT11..RT33). */
    gte_load_R_v1a0v0(rot_inv);
    rotate_vector_precise(pos, pos);
    pos[0] += mover_offset_x << 12;
    pos[1] += mover_offset_y << 12;
    FAKE_OPAQUE(pos);
    pos[2] += mover_offset_z << 12;
}

/* Builds the mover's rotation matrix from its yaw and pitch, and writes the three
   resulting angles to p->rot. The angles are read back as u16 (the original loads them with lhu). */
void mover_set_rot(Mover *mover, PlayerObj *p) {
    RotMatrix *mtx = scratch_alloc(0x20);
    s32 angles[3];

    rot_matrix(mtx, ((s32) mover->yaw >> 0xC) + 0x800, -((s32) mover->pitch >> 0xC), 0);
    mul_matrix(mover_rot_matrix_inv, mtx, mtx);
    transpose_matrix(mtx, mtx);
    rot_matrix_to_angles(mtx, &angles[0], &angles[1], &angles[2]);
    p->rot[0] = *(u16 *) &angles[1];
    p->rot[1] = *(u16 *) &angles[0];
    p->rot[2] = *(u16 *) &angles[2];
    scratch_top -= 0x20;
}

/* Copies a Vec3 with y as a 24-bit angle (biased by half a turn, then wrapped) and z negated. */
void mover_to_vec3(Vec3 *src, Vec3 *dst) {
    dst->x = src->x;
    dst->y = ((src->y + 0x800000) << 8) >> 8;
    dst->z = -src->z;
}

