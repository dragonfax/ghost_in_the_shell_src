/* math: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"
#include "gte.h"

void rand_reset(Rand *rand) {
    s32 i;

    rand->index = 0;
    for (i = 0; i < RAND_SIZE; i++) {
        rand->values[i] = rand_seed_table[i];
    }
}

void rand_init_states(void) {
    rand_reset(&rand_a);
    rand_reset(&rand_b);
}

/* rand_step (below) with the held buttons' bits 12-15 (pad1.held >> 8, as 0xF0) added to every value. Its own
 * inline: one helper shared with rand_b_next compiles both differently (the original had two). */
static inline s32 rand_a_step(Rand *r, s32 buttons) {
    s32 i;
    s32 value;

    i = (r->index + 1) & (RAND_SIZE - 1);
    r->index = i;
    value = ((r->values[(i - 24) & (RAND_SIZE - 1)] ^ r->values[(i - 55) & (RAND_SIZE - 1)]) + buttons
             + rand_seed_table[i]) & 0xFFF;
    r->values[i] = value;
    return value;
}

s32 rand_a_next(void) {
    return rand_a_step(&rand_a, (pad1.held >> 8) & 0xF0);
}

/* One lagged-Fibonacci step: values[i] = (values[i-24] ^ values[i-55]) + seed[i], 12 bits. */
static inline s32 rand_step(Rand *r) {
    s32 i;
    s32 value;

    i = (r->index + 1) & (RAND_SIZE - 1);
    r->index = i;
    value = ((r->values[(i - 24) & (RAND_SIZE - 1)] ^ r->values[(i - 55) & (RAND_SIZE - 1)]) + rand_seed_table[i]) & 0xFFF;
    r->values[i] = value;
    return value;
}

s32 rand_b_next(void) {
    return rand_step(&rand_b);
}

s32 atan2(s32 x, s32 y) {
    s32 ax, ay, angle, q;
    s16 *table;

    ax = abs(x);
    ay = abs(y);
    if (ax == ay) {
        if (ay == 0) {
            return 0;
        }
        angle = 0x200;
    } else if (ay < ax) {
        mips_div(ay << 10, ax);
        __asm__("" : "=r"(table) : "0"(atan_table));
        mips_mflo(q);
        angle = table[q];
    } else {
        mips_div(ax << 10, ay);
        __asm__("" : "=r"(table) : "0"(atan_table));
        angle = 0x400;
        mips_mflo(q);
        angle -= table[q];
    }
    if (y < 0) {
        angle = 0x1000 - angle;
    }
    if (x < 0) {
        angle = 0x800 - angle;
    }
    return angle & 0xFFF;
}

/* Yaw and pitch (atan2 units) of the vector (x, y, z). */
/* isqrt is inlined here in the original. */
void vector_to_angles(s32 x, s32 y, s32 z, s32 *yaw, s32 *pitch) {
    s32 n;
    s32 sq;
    s32 lz;
    s32 e;
    u32 idx;
    s32 shift;
    s16 *table;

    gte_set(IR1, 0);
    gte_set(IR2, x);
    gte_set(IR3, z);
    gte_sqr0();
    *yaw = atan2(z, x);
    gte_get(MAC2, n);
    gte_get(MAC3, sq);
    gte_nop();
    n += sq;
    idx = ~1;
    if (n != 0) {
        gte_set(LZCS, n);
        table = SQRT - 64;
        gte_get(LZCR, lz);
        if (n < 0) {
            lz = 0;
        }
        shift = 31 - lz;
        lz &= idx;
        e = lz - 24;
        idx = n << e;
        if (e < 0) {
            idx = (u32)n >> -e;
        }
        n = table[idx];
        shift >>= 1;
        n <<= shift;
        n = (u32)n >> 12;
    }
    *pitch = atan2(n, y);
}

s32 length_sq(s32 x, s32 y, s32 z) {
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_sqr0();
    gte_get_MAC123(x, y, z);
    return x + y + z;
}

/* Turns `from` towards `to` by at most `step`, the short way round. */
s32 angle_approach(s32 from, s32 to, s32 step) {
    s32 diff;

    from = (from << 20) >> 20;
    diff = ((to - from) << 20) >> 20;
    if (diff >= 0) {
        if (step < diff) {
            diff = step;
        }
    } else if (diff == -0x800) {
        if (from > 0) {
            diff = -step;
        } else {
            diff = step;
        }
    } else if (step < -diff) {
        diff = -step;
    }
    return (diff + from) & 0xFFF;
}

/* Moves `speed` units along `angle`: *dx = speed * sin, *dz = speed * cos (12-bit fixed point). */
void fly_move(s32 angle, s32 speed, s32 *dx, s32 *dz) {
    s32 sc = rcossin_tbl[angle & 0xFFF];

    gte_set(IR0, speed);
    gte_set(IR1, sc >> 16);
    gte_set(IR2, sc);
    gte_gpf0();
    gte_store(MAC1, dx, 0);
    gte_store(MAC2, dz, 0);
}

void fly_strafe(s32 angle, s32 speed, s32 *x, s32 *z) {
    s32 sc;
    s32 dx, dz;
    s32 x0, z0;

    if (speed != 0) {
        sc = rcossin_tbl[angle & 0xFFF];
        gte_set(IR0, speed);
        gte_set(IR1, sc >> 16);
        gte_set(IR2, sc);
        gte_gpf0();
        x0 = *x;
        z0 = *z;
        gte_get(MAC1, dx);
        gte_get(MAC2, dz);
        *x = x0 + dx;
        *z = z0 + dz;
    }
}

void angles_to_vector(s32 yaw, s32 pitch, s32 len, s32 *x, s32 *y, s32 *z) {
    fly_move(pitch, len, z, y);
    *y = -*y;
    fly_move(yaw, *z >> 12, z, x);
}

/* Turns (x, z) by angle1 about Y, then (that x, a) by angle2. */
void rotate_xz_twice(s32 angle2, s32 angle1, s32 *a, s32 *x, s32 *z) {
    s32 sc = rcossin_tbl[angle1 & 0xFFF];
    s32 t;

    gte_set_rot_y(sc);
    gte_load(IR1, x, 0);
    gte_set(IR2, 0);
    gte_load(IR3, z, 0);
    angle2 &= 0xFFF;
    gte_nop();
    gte_rtir_b();
    sc = rcossin_tbl[angle2];
    gte_get(MAC3, t);
    gte_set_rot_y(sc);
    gte_set(IR1, t);
    gte_set(IR2, 0);
    gte_load(IR3, a, 0);
    gte_store(MAC1, x, 0);
    gte_nop();
    gte_rtir_b();
    gte_store(MAC1, z, 0);
    gte_store(MAC3, a, 0);
}

/* VectorNormal, after scaling large vectors down so the GTE's squares don't overflow. */
void vector_normal_scaled(VECTOR *v, SVECTOR *out) {
    s32 x = v->vx;
    s32 y = v->vy;
    s32 z = v->vz;
    s32 max, ay, az;
    s32 shift;

    max = abs(x);
    ay = abs(y);
    if (max < ay) {
        max = ay;
    }
    az = abs(z);
    if (max < az) {
        max = az;
    }
    gte_set(LZCS, max);
    gte_nop();
    gte_nop();
    gte_get(LZCR, shift);
    shift = 18 - shift;
    if (shift > 0) {
        v->vx = x >> shift;
        v->vy = y >> shift;
        v->vz = z >> shift;
    }
    VectorNormal(v, out);
}

void tex_tint_gradient(s32 width, s32 height, u8 *tint, u16 *src, u16 *dst)
{
    s32 y;
    s32 x;
    s32 half;
    s32 stepR, stepG, stepB;

    stepR = tint[0] >> 3;
    stepG = tint[1] >> 3;
    stepB = tint[2] >> 3;

    half = height / 2;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++, dst++) {
            s32 c = src[x];
            if (c == 0) {
                *dst = 0;
            } else {
                s32 r = c & 0x1F;
                s32 g = (c >> 5) & 0x1F;
                s32 b = (c >> 10) & 0x1F;

                r = (y * stepR + r * (height - y) + half) / height & 0x1F;
                g = (y * stepG + g * (height - y) + half) / height & 0x1F;
                b = (y * stepB + b * (height - y) + half) / height & 0x1F;
                c = (c & 0x8000) | r | (g << 5) | (b << 10);
                if (c == 0) {
                    c = 0x400;
                }
                *dst = c;
            }
        }
    }
}

/* Sets the semi-transparency bit on every non-black colour. */
void clut_set_stp(s32 n, u16 *clut) {
    for (; n > 0; n--, clut++) {
        if (*clut != 0) {
            *clut |= 0x8000;
        }
    }
}

/* Builds one CLUT row: the first half of dst gets src[i] (0 where the mask
 * bit is set, and 0xC210 for any other non-zero colour); the second half,
 * dst[count..], keeps src[i] before that replacement. */
void clut_make_pair(s32 count, u16 *src, u16 *dst, u8 *mask) {
    u16 *out = dst;
    u8 *m;
    u8 *end;
    u16 color;

    if (count > 0) {
        m = mask;
        end = (u8 *) (count + (s32) mask); /* count + mask, not mask + count: the operand order is the original's */
        do {
            color = *src;
            src += 1;
            if (mask != NULL && (*m & 1)) {
                color = 0;
            }
            dst[count] = color;
            if (color != 0) {
                color = 0xC210;
            }
            *out = color;
            dst += 1;
            m += 1;
            out += 1;
        } while ((s32) m < (s32) end); /* a signed compare (slt) */
    }
}

/* Packs pairs of 8-bit pixels (low nibbles) into 4-bit pixels, sampling every 2^shift pixels. */
void pack_4bpp(s32 stride, s32 w, s32 h, s32 shift, u8 *src, u8 *dst) {
    s32 y;
    s32 x;
    s32 low_nibble;

    for (y = h; y > 0; y -= 1 << shift) {
        for (x = w; x > 0; x -= 2 << shift) {
            low_nibble = src[0] & 0xF;
            *dst++ = ((src[1 << shift] & 0xF) << 4) | low_nibble;
            src += 2 << shift;
        }
        src += (stride << shift) - w;
    }
}

/* Integer square root from the GTE's leading-zero count and a table (PsyQ SquareRoot0's method). */
s32 isqrt(s32 n) {
    s32 lz;
    s32 e;
    u32 idx = ~1; /* first the even mask for lz, then the table index (one register) */
    s32 shift;
    s16 *table;

    if (n != 0) {
        gte_set(LZCS, n);
        table = SQRT - 64;
        gte_get(LZCR, lz);
        if (n < 0) {
            lz = 0;
        }
        shift = 31 - lz;
        lz &= idx;
        e = lz - 24;
        idx = n << e;
        if (e < 0) {
            idx = (u32)n >> -e;
        }
        n = table[idx];
        shift >>= 1;
        n <<= shift;
        n = (u32)n >> 12;
    }
    return n;
}

void *transpose_matrix(void *src_, void *dst)
{
    s32 a, b, c, d;
    s16 *src = src_;
    s16 *out = dst;
    a = *(s32 *)&src[0];
    b = *(s32 *)&src[2];
    *(s32 *)&out[2] = a;
    *(s32 *)&out[0] = b;
    c = *(s32 *)&src[4];
    d = *(s32 *)&src[6];
    out[0] = a;
    *(s32 *)&out[6] = c;
    *(s32 *)&out[4] = d;
    out[6] = b;
    a = src[8];
    out[4] = c;
    out[2] = d;
    out[8] = a;
    return out;
}

/* Three rows of an s16 vector (x, y, z) each, scaled by one per-row factor through the GTE:
 * IR0 = scale factor, IR1..IR3 = the vector, GPF (sf = 12) multiplies the vector by IR0.
 * The register pins keep the original's allocation (v0 scale, v1/a3/t0 components). */
void scale_rows(s16 *in, s16 *scale, s16 *out) {
    s32 row_count = 3;
    register s16 *in_ptr asm("$4") = in;
    register s16 *scale_ptr asm("$5") = scale;
    register s16 *out_ptr asm("$6") = out;
    register s32 factor asm("$2");
    register s32 in_x asm("$3");
    register s32 in_y asm("$7");
    register s32 in_z asm("$8");
    register s32 res_x asm("$3");
    register s32 res_y asm("$7");
    register s32 res_z asm("$8");

    do {
        factor = scale_ptr[0];
        do { } while (0);
        in_x = in_ptr[0];
        in_y = in_ptr[1];
        in_z = in_ptr[2];
        gte_set(IR0, factor);
        gte_set(IR1, in_x);
        gte_set(IR2, in_y);
        gte_set(IR3, in_z);
        scale_ptr++;
        in_ptr += 3;
        gte_gpf12_b();
        gte_get(IR1, res_x);
        gte_get(IR2, res_y);
        gte_get(IR3, res_z);
        out_ptr[0] = res_x;
        out_ptr[1] = res_y;
        out_ptr[2] = res_z;
        out_ptr += 3;
    } while (--row_count > 0);
}

void vector_double_even(Vec3 *in, Vec3 *out) {
    s32 mask = 0xFFFEFFFE;
    s32 x = in->x;
    s32 y = in->y;
    s32 z = in->z;

    x = (x << 1) & mask;
    y = (y << 1) & mask;
    z = (z << 1) & mask;
    out->x = x;
    out->y = y;
    out->z = z;
}

void copy_record20(s32 *src, s32 *dst) {
    s32 a = src[0];
    s32 b = src[1];
    s32 c = src[2];
    dst[0] = a;
    dst[1] = b;
    dst[2] = c;
    a = src[3];
    b = src[4];
    dst[3] = a;
    dst[4] = b;
    __asm__ volatile("");
}

/* out = a * b for 3x3 fixed-point (4.12) MATRIX rotations: a goes into the GTE rotation matrix, then each
 * column of b (read as packed halfword words) is rotated and stored as the matching column of out.
 * The original is hand-scheduled assembly: the register variables reproduce its register choices. */
/* Old-style definition: callers pass a fourth argument, so mul_matrix stays unprototyped (stage_decls.h). */
void mul_matrix(a, b_mat, out_mat)
    void *a;
    void *b_mat;
    void *out_mat;
{
    u32 *b = b_mat;
    s16 *out = out_mat;
    /* a's rows (loaded by the asm below) */
    register u32 r0 asm("a3");
    register u32 r1 asm("v1");
    register u32 r2 asm("v0");
    /* b's halfword pairs; b0 then holds column 1 (b[1].x | b[2].x << 16) */
    register u32 b0 asm("t0");
    register u32 b1 asm("a0");
    register u32 b2 asm("v1");
    register u32 b3 asm("a3");
    register u32 b4 asm("a3");
    register u32 hi asm("v0");
    /* products read back for halfword stores */
    register s32 m01 asm("t0");
    register s32 m10 asm("v0");
    register s32 m12 asm("a3");
    register s32 m11 asm("a3");

    gte_load_R_via(r0, r1, r2, a);

    b0 = b[0];
    b3 = b[3];
    b1 = b[1];
    gte_set(IR1, b0);
    hi = b1 >> 16;
    gte_set(IR2, hi);
    gte_set(IR3, b3);
    b0 >>= 16;
    gte_nop();
    gte_rtir_b();
    b2 = b[2];
    b3 >>= 16;
    b0 |= b2 << 16;
    gte_store(MAC1, out, 0);
    gte_store(MAC3, out, 12);
    gte_set(VXY0, b0);
    gte_set(VZ0, b3);
    gte_get(MAC2, m01);
    gte_nop();
    gte_rtv0_b();
    b2 >>= 16;
    b4 = b[4];
    gte_get(MAC1, m10);
    gte_store(MAC2, out, 8);
    gte_set(IR1, b1);
    gte_set(IR2, b2);
    gte_set(IR3, b4);
    gte_get(MAC3, m12);
    gte_nop();
    gte_rtir_b();
    out[1] = m10;
    out[7] = m12;
    gte_store(MAC1, out, 4);
    gte_get(MAC2, m11);
    gte_store(MAC3, out, 16);
    out[3] = m01;
    out[5] = m11;
}

/* Builds a rotation matrix from three angles (rotations about X, Y and Z multiplied onto a start of
 * diag(1, -1, -1)), then negates its last six entries. */
void rot_matrix_from_angles(RotMatrix *out, s32 ay, s32 ax, s32 az) {
    RotMatrix *step = scratch_alloc(sizeof(RotMatrix));
    s32 angle;

    angle = ax & 0xFFF;
    out->m[0][0] = 0x1000;
    out->m[0][1] = 0;
    out->m[0][2] = 0;
    out->m[1][0] = 0;
    out->m[1][1] = -0x1000;
    out->m[1][2] = 0;
    out->m[2][0] = 0;
    out->m[2][1] = 0;
    out->m[2][2] = -0x1000;
    if (angle != 0) {
        u32 sc = rcossin_tbl[-angle & 0xFFF];
        step->m[0][0] = 0x1000;
        step->m[0][1] = 0;
        step->m[0][2] = 0;
        step->m[1][0] = 0;
        step->m[2][0] = 0;
        step->m[1][1] = sc >> 16;
        step->m[1][2] = -sc;
        step->m[2][1] = sc;
        step->m[2][2] = sc >> 16;
        mul_matrix(step, out, out);
    }
    angle = ay & 0xFFF;
    if (angle != 0) {
        u32 sc = rcossin_tbl[-angle & 0xFFF];
        step->m[0][1] = 0;
        step->m[1][0] = 0;
        step->m[1][1] = 0x1000;
        step->m[1][2] = 0;
        step->m[2][1] = 0;
        /* s16, so sched1 computes them before the stores */
        {
            s16 cos = sc >> 16;
            s16 neg_sin = -sc;

            step->m[0][0] = cos;
            step->m[0][2] = sc;
            step->m[2][0] = neg_sin;
            step->m[2][2] = cos;
        }
        mul_matrix(step, out, out);
    }
    angle = az & 0xFFF;
    if (angle != 0) {
        u32 sc = rcossin_tbl[-angle & 0xFFF];
        step->m[0][2] = 0;
        step->m[1][2] = 0;
        step->m[2][0] = 0;
        step->m[2][1] = 0;
        step->m[2][2] = 0x1000;
        step->m[0][0] = sc >> 16;
        step->m[0][1] = -sc;
        step->m[1][0] = sc;
        step->m[1][1] = sc >> 16;
        mul_matrix(step, out, out);
    }
    scratch_top -= sizeof(RotMatrix);
    out->m[1][0] = -out->m[1][0];
    out->m[1][1] = -out->m[1][1];
    out->m[1][2] = -out->m[1][2];
    out->m[2][0] = -out->m[2][0];
    out->m[2][1] = -out->m[2][1];
    out->m[2][2] = -out->m[2][2];
}

/* m = Ry(yaw) * Rx(pitch) * Rz(roll), 4.12 fixed point */
void rot_matrix(void *m, s32 yaw, s32 pitch, s32 roll) {
    RotMatrix *rot = m;
    RotMatrix *tmp = scratch_alloc(sizeof(RotMatrix));
    s32 *table;
    s32 one;
    s32 sc;
    s32 angle;

    yaw &= 0xFFF;
    angle = pitch & 0xFFF;
    one = 0x1000;
    sc = rcossin_tbl[yaw];
    table = rcossin_tbl;
    rot->m[0][1] = 0;
    rot->m[1][0] = 0;
    rot->m[1][1] = one;
    rot->m[1][2] = 0;
    rot->m[2][1] = 0;
    {
        /* s16, so sched1 doesn't move them next to their stores */
        s16 cos = (u32)sc >> 16;
        s16 neg_sin = -sc;

        rot->m[0][0] = cos;
        rot->m[0][2] = sc;
        rot->m[2][0] = neg_sin;
        rot->m[2][2] = cos;
    }
    if (angle != 0) {
        s32 sc = table[angle];
        tmp->m[0][0] = one;
        tmp->m[0][1] = 0;
        tmp->m[0][2] = 0;
        tmp->m[1][0] = 0;
        tmp->m[2][0] = 0;
        tmp->m[1][1] = (u32)sc >> 16;
        tmp->m[1][2] = -sc;
        tmp->m[2][1] = sc;
        tmp->m[2][2] = (u32)sc >> 16;
        mul_matrix(m, tmp, m);
    }
    angle = roll & 0xFFF;
    if (angle != 0) {
        s32 sc = table[angle];
        tmp->m[0][2] = 0;
        tmp->m[1][2] = 0;
        tmp->m[2][0] = 0;
        tmp->m[2][1] = 0;
        tmp->m[2][2] = one;
        tmp->m[0][0] = (u32)sc >> 16;
        tmp->m[0][1] = -sc;
        tmp->m[1][0] = sc;
        tmp->m[1][1] = (u32)sc >> 16;
        mul_matrix(m, tmp, m);
    }
    scratch_top -= sizeof(RotMatrix);
}

/* m = Rz(roll) * Rx(pitch) * Ry(yaw): rot_matrix's products the other way round */
void rot_matrix_b(void *m, s32 yaw, s32 pitch, s32 roll) {
    RotMatrix *rot = m;
    RotMatrix *tmp = scratch_alloc(sizeof(RotMatrix));
    s32 *table;
    s32 one;
    s32 sc;
    s32 angle;

    yaw &= 0xFFF;
    angle = pitch & 0xFFF;
    one = 0x1000;
    sc = rcossin_tbl[yaw];
    table = rcossin_tbl;
    rot->m[0][1] = 0;
    rot->m[1][0] = 0;
    rot->m[1][1] = one;
    rot->m[1][2] = 0;
    rot->m[2][1] = 0;
    {
        /* s16, so sched1 doesn't move them next to their stores */
        s16 cos = (u32)sc >> 16;
        s16 neg_sin = -sc;

        rot->m[0][0] = cos;
        rot->m[0][2] = sc;
        rot->m[2][0] = neg_sin;
        rot->m[2][2] = cos;
    }
    if (angle != 0) {
        s32 sc = table[angle];
        tmp->m[0][0] = one;
        tmp->m[0][1] = 0;
        tmp->m[0][2] = 0;
        tmp->m[1][0] = 0;
        tmp->m[2][0] = 0;
        tmp->m[1][1] = (u32)sc >> 16;
        tmp->m[1][2] = -sc;
        tmp->m[2][1] = sc;
        tmp->m[2][2] = (u32)sc >> 16;
        mul_matrix(tmp, m, m);
    }
    angle = roll & 0xFFF;
    if (angle != 0) {
        s32 sc = table[angle];
        tmp->m[0][2] = 0;
        tmp->m[1][2] = 0;
        tmp->m[2][0] = 0;
        tmp->m[2][1] = 0;
        tmp->m[2][2] = one;
        tmp->m[0][0] = (u32)sc >> 16;
        tmp->m[0][1] = -sc;
        tmp->m[1][0] = sc;
        tmp->m[1][1] = (u32)sc >> 16;
        mul_matrix(tmp, m, m);
    }
    scratch_top -= sizeof(RotMatrix);
}

void point_calc_projection(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    if (arg0 < arg1) {
        *arg3 = (s32) (((s32) (arg1 * arg0) / (s32) (arg0 - arg1)) << 8) / arg2;
        *arg4 = ((s32) (arg1 << 0xC) / (s32) (arg1 - arg0)) << 0xC;
        return;
    }
    *arg3 = 0;
    *arg4 = 0;
}

static inline void rot3x3_copy(RotMatrix *dst, RotMatrix *src) {
    s32 a, b, c;

    rot_matrix_copy012(dst, src, a, b, c);
    rot_matrix_copy34(dst, src, a, b);
}
/* Splits a rotation matrix into three angles without transposing it: a rotation about Z is undone (into a
 * scratch matrix), then one about X, and each angle is read from the matrix that is left. The 3x3 part
 * is copied with inline asm (3 words, then 2), which also keeps reorg from filling the first delay slot. */
void matrix_to_angles(void *m, void *a, void *b, void *c) {
    RotMatrix *src = m;
    s32 *out_a = a;
    s32 *out_b = b;
    s32 *out_c = c;
    RotMatrix *acc = scratch_alloc(0x20);
    RotMatrix *step = scratch_alloc(0x20);
    s32 angle;
    u32 sc;

    rot3x3_copy(acc, src);
    *out_c = atan2(acc->m[1][1], acc->m[1][0]);
    sc = rcossin_tbl[-*out_c & 0xFFF];
    step->m[0][2] = 0;
    step->m[1][2] = 0;
    step->m[2][0] = 0;
    step->m[2][1] = 0;
    step->m[2][2] = 0x1000;
    step->m[0][0] = sc >> 16;
    step->m[0][1] = -sc;
    step->m[1][0] = sc;
    step->m[1][1] = sc >> 16;
    mul_matrix(acc, step, acc, sc >> 16);
    angle = atan2(acc->m[1][1], acc->m[1][2]);
    *out_b = -angle;
    sc = rcossin_tbl[angle & 0xFFF];
    step->m[0][0] = 0x1000;
    step->m[0][1] = 0;
    step->m[0][2] = 0;
    step->m[1][0] = 0;
    step->m[2][0] = 0;
    step->m[1][1] = sc >> 16;
    step->m[1][2] = -sc;
    step->m[2][1] = sc;
    step->m[2][2] = sc >> 16;
    mul_matrix(acc, step, acc, sc >> 16);
    *out_a = -atan2(acc->m[2][2], acc->m[2][0]);
    scratch_top -= 0x40;
}

/* Splits a rotation matrix into three angles: undoes a rotation about Z, then one about X, and reads each angle
 * from the matrix that is left. */
void rot_matrix_to_angles(RotMatrix *src, s32 *out_a, s32 *out_b, s32 *out_c) {
    RotMatrix *acc = scratch_alloc(0x20);
    RotMatrix *step = scratch_alloc(0x20);
    u32 sc;

    transpose_matrix(src, acc);
    *out_c = -atan2(acc->m[1][1], acc->m[1][0]);
    sc = rcossin_tbl[*out_c & 0xFFF];
    step->m[0][2] = 0;
    step->m[1][2] = 0;
    step->m[2][0] = 0;
    step->m[2][1] = 0;
    step->m[2][2] = 0x1000;
    step->m[0][0] = sc >> 16;
    step->m[0][1] = -sc;
    step->m[1][0] = sc;
    step->m[1][1] = sc >> 16;
    mul_matrix(acc, step, acc, sc >> 16);
    *out_b = atan2(acc->m[1][1], acc->m[1][2]);
    sc = rcossin_tbl[*out_b & 0xFFF];
    step->m[0][0] = 0x1000;
    step->m[0][1] = 0;
    step->m[0][2] = 0;
    step->m[1][0] = 0;
    step->m[2][0] = 0;
    step->m[1][1] = sc >> 16;
    step->m[1][2] = -sc;
    step->m[2][1] = sc;
    step->m[2][2] = sc >> 16;
    mul_matrix(acc, step, acc, sc >> 16);
    *out_a = atan2(acc->m[2][2], acc->m[2][0]);
    scratch_top -= 0x40;
}

/* Scales the vector at `vec` by the per-axis factors `scale` (s16 x, y, z, 1.12 fixed point: a diagonal GTE
 * rotation matrix, then mvmva) and stores the result as a word and two s16 at `out`.
 * Hand-written in the original: returns scale[2] (v0 is left holding it). */
s32 vec_scale_mvmva(s32 *vec, s16 *scale, s16 *out) {
    u32 xy = *(u32 *)scale; /* later reused for MAC2 */
    s32 sz = scale[2];
    u32 sy = xy >> 16;      /* later reused for MAC3 */
    s32 sx = xy & 0xFFFF;

    gte_set_ctrl(R11R12, sx);
    gte_set_ctrl(R22R23, sy);
    gte_set_ctrl(R33, sz);
    gte_set_ctrl(R13R21, 0);
    gte_set_ctrl(R31R32, 0);
    gte_load(VXY0, vec, 0);
    gte_load(VZ0, vec, 4);
    gte_rtv0();
    gte_store(MAC1, out, 0);
    gte_get(MAC2, xy);
    gte_get(MAC3, sy);
    out[1] = xy;
    out[2] = sy;
    return sz;
}
