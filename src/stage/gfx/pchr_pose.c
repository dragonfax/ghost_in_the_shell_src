/* pchr_pose: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void light_table_init(void) {
    light_rec_count = 0;
    light_rec_table = *(void **)((u8 *)work_area_ptr + 0x74);
}

/* Clears the spark list: the records-in-use count, every chain tail, and the colour bytes. */
void spark_list_clear(void) {
    s16 *count = &spark_count;
    u8 *list;
    u8 **tail;
    s32 i = 0;

    list = (u8 *) count - 0x181C;
    pchr_count_saved = pchr_count;
    tail = (u8 **) ((u8 *) count - 0x1814);
    *count = 0;
    for (; i < 8; i++) {
        spark_list.head[i] = 0;
        *tail++ = list + i;
    }
}

s32 pchr_copy_slot(s32 value) {
    s16 *countp = &pchr_count_saved;
    s32 n = *countp;
    s32 ret;
    s32 offset;
    u8 *recs;
    PchrSlotEntry *src;

    if (n < 0x600) {
        *countp = n + 1;
        offset = value * sizeof(PchrSlotEntry);
        recs = (u8 *)(countp + 1);
        src = (PchrSlotEntry *)(offset + recs);
        ((PchrSlotEntry *)recs)[n] = *src;
        ret = n;
    } else {
        ret = value;
    }
    return ret;
}

s32 *pchr_poses_build(s32 value) {
    Pchr *entry;
    PchrPoseList *out;
    PchrPoseList *src;
    s32 count;
    s32 i;

    entry = &pchr_table[value & 0x7FF];
    out = (PchrPoseList *)work_area_ptr->packet;
    if (entry->bounds_radius == 0) {
        count = 0;
    } else {
        src = (PchrPoseList *)entry->unk_0C;
        if (src != NULL) {
            count = src->count;
            for (i = 0; i < count; i++) {
                out->pose[i] = src->pose[i];
            }
        } else {
            count = *entry->data;
            for (i = 0; i < count; i++) {
                out->pose[i].pos[2] = 0;
                out->pose[i].pos[1] = 0;
                out->pose[i].pos[0] = 0;
                out->pose[i].rot[2] = 0;
                out->pose[i].rot[1] = 0;
                out->pose[i].rot[0] = 0;
            }
        }
    }
    out->count = count;
    work_area_ptr->packet = (s32 *)((u8 *)out + (count * sizeof(PchrPose) + 4));
    return (s32 *)out;
}

/* Rotates poses first..first+count-1 of a path by the angles rot about pivot: each position is turned
 * around pivot and each pose's own rotation is premultiplied, then converted back to angles. */
void pose_rotate_range(s32 *poses, s32 first, s32 count, void *pivot, void *rot) {
    PosePoint *rec;
    s32 total = poses[0];
    s32 angX;
    s32 angY;
    s32 angZ;
    RotMatrix *mat;
    RotMatrix *ref;
    s16 *vec;
    s32 posZ;

    if (first < total) {
        count += first;
        first = MAX(MIN(first, total - 1), 0);
        count = MAX(MIN(count, total), 0);
        count -= first;
        angY = ((SVECTOR *)rot)->vx;
        angX = ((SVECTOR *)rot)->vy;
        angZ = ((SVECTOR *)rot)->vz;
        if (((angY | angX | angZ) & 0xFFF) != 0) {
            mat = scratch_alloc(2 * sizeof(RotMatrix));
            vec = scratch_alloc(8);
            ref = mat + 1;
            rot_matrix(ref, angX, angY, angZ);
            rec = (PosePoint *)(poses + 1) + first;
            if (count > 0) {
                do {
                    rot_matrix(mat, rec->ang[0], rec->ang[1], rec->ang[2]);
                    rot_load((s32 *)ref);
                    vec[0] = rec->pos[0] - ((SVECTOR *)pivot)->vx;
                    vec[1] = rec->pos[1] - ((SVECTOR *)pivot)->vy;
                    vec[2] = rec->pos[2] - ((SVECTOR *)pivot)->vz;
                    gte_load(VXY0, vec, 0);
                    gte_load(VZ0, vec, 4);
                    gte_rtv0();
                    gte_get_wait(MAC1, angY);
                    gte_get_wait(MAC2, angX);
                    gte_get(MAC3, posZ);
                    rec->pos[0] = ((SVECTOR *)pivot)->vx + (u16)angY;
                    rec->pos[1] = ((SVECTOR *)pivot)->vy + (u16)angX;
                    angZ = posZ;
                    rec->pos[2] = ((SVECTOR *)pivot)->vz + (u16)angZ;
                    /* mat = ref * mat, in place (the hand-scheduled column multiply of mul_matrix) */
                    {
                        register u32 b0 asm("t1");
                        register u32 b1 asm("a0");
                        register u32 b2 asm("v1");
                        register u32 b3 asm("t0");
                        register u32 b4 asm("t0");
                        register u32 hi asm("v0");
                        register s32 m01 asm("t1");
                        register s32 m10 asm("v0");
                        register s32 m12 asm("t0");
                        register s32 m11 asm("t0");

                        b0 = ((u32 *)mat->m)[0];
                        b3 = ((u32 *)mat->m)[3];
                        b1 = ((u32 *)mat->m)[1];
                        gte_set(IR1, b0);
                        hi = b1 >> 16;
                        gte_set(IR2, hi);
                        gte_set(IR3, b3);
                        b0 >>= 16;
                        gte_nop();
                        gte_rtir_b();
                        b2 = ((u32 *)mat->m)[2];
                        b3 >>= 16;
                        b0 |= b2 << 16;
                        gte_store(MAC1, mat, 0);
                        gte_store(MAC3, mat, 12);
                        gte_set(VXY0, b0);
                        gte_set(VZ0, b3);
                        gte_get(MAC2, m01);
                        gte_nop();
                        gte_rtv0_b();
                        b2 >>= 16;
                        b4 = ((u32 *)mat->m)[4];
                        gte_get(MAC1, m10);
                        gte_store(MAC2, mat, 8);
                        gte_set(IR1, b1);
                        gte_set(IR2, b2);
                        gte_set(IR3, b4);
                        gte_get(MAC3, m12);
                        gte_nop();
                        gte_rtir_b();
                        mat->m[0][1] = m10;
                        mat->m[2][1] = m12;
                        gte_store(MAC1, mat, 4);
                        gte_get(MAC2, m11);
                        gte_store(MAC3, mat, 16);
                        mat->m[1][0] = m01;
                        mat->m[1][2] = m11;
                    }
                    matrix_to_angles(mat, &angX, &angY, &angZ);
                    count -= 1;
                    rec->ang[0] = angX & 0xFFF;
                    rec->ang[1] = angY & 0xFFF;
                    rec->ang[2] = angZ & 0xFFF;
                    rec++;
                } while (count > 0);
            }
            scratch_top -= 0x48;
        }
    }
}

void shift_table_add_delta(ShiftTable *tab, s32 first, s32 len, s16 *delta) {
    s32 count = tab->count;
    s32 n;
    s32 dx, dy, dz;
    ShiftEntry *e;

    if (first < count) {
        len += first;
        first = MAX(MIN(first, count - 1), 0);
        len = MAX(MIN(len, count), 0);
        n = len - first;
        dx = delta[0];
        dy = delta[1];
        dz = delta[2];
        if ((dx | dy | dz) != 0) {
            e = &tab->entries[first];
            while (n > 0) {
                n--;
                e->x += dx;
                e->y += dy;
                e->z += dz;
                e++;
            }
        }
    }
}

/* Follows the chain of links to the last entry. */
Pchr *pchr_chain_last(Pchr *p) {
    while (p->link_count > 0) {
        p = &pchr_table[p->link & 0x7FF];
    }
    return p;
}

/* Makes a pchr entry blending entries a and b (weight 0..0x1000 toward a) and returns its index.
 * Returns a or b itself when they are the same, the weight is at an end, the table is full or
 * the two chains' last entries don't share their lists. */
s32 pchr_blend(s32 a, s32 b, s32 weight, s32 flag) {
    Pchr *table;
    s16 *count_ptr;
    Pchr *pa;
    Pchr *pb;
    Pchr *dst;
    s32 count;
    s32 v;
    s32 offset;
    s32 radius_b;

    a &= 0x7FF;
    b &= 0x7FF;
    if (a == b) {
        return a;
    }
    weight = MAX(MIN(weight, 0x1000), 0);
    if (weight == 0) {
        return b;
    }
    if (weight == 0x1000) {
        return a;
    }
    count_ptr = &pchr_count_saved;
    count = *count_ptr;
    if (count < 0x600) {
        offset = a * sizeof(Pchr);
        table = (Pchr *)(count_ptr + 1);
        pa = (Pchr *)(offset + (s32)table);
        pb = &table[b];
        v = pa->bounds_radius;
        radius_b = pb->bounds_radius;
        if (v != 0 && radius_b != 0) {
            v = (s32)pchr_chain_last(pa)->unk_0C;
            if ((v ^ (s32)pchr_chain_last(pb)->unk_0C) >= 0) {
                v = *PCHR_LISTS(pchr_chain_last(pa))->colours;
                if (v == *PCHR_LISTS(pchr_chain_last(pb))->colours) {
                    v = *PCHR_LISTS(pchr_chain_last(pa))->list_04;
                    if (v == *PCHR_LISTS(pchr_chain_last(pb))->list_04) {
                        *count_ptr = count + 1;
                        dst = &table[count];
                        dst->link_count = weight;
                        dst->link = a;
                        dst->unk_06 = b;
                        dst->unk_00 = flag != 0;
                        dst->bounds_radius = MAX(pa->bounds_radius, pb->bounds_radius);
                        dst->unk_1A = pa->unk_1A == pb->unk_1A ? pa->unk_1A : 0;
                        if (weight < 0x800) {
                            pa = pb;
                        }
                        dst->data = pa->data;
                        dst->unk_0C = 0;
                        dst->unk_12 = pa->unk_12;
                        dst->unk_14 = pa->unk_14;
                        dst->far_bias = 0;
                        dst->angle = pa->angle;
                        return count;
                    }
                }
            }
        }
    }
    count = b;
    if (weight > 0x800) {
        count = a;
    }
    return count;
}

s32 pool_spawn_scaled(s32 index, s32 a1, s32 a2, s32 a3) {
    PoolRec *pool;
    PoolRec *src;
    PoolRec *dst;
    s16 *count;
    s32 slot;
    s32 less;
    s32 clamped;
    s32 over;

    index &= 0x7FF;
    a1 = MAX(MIN(a1, 0x7FFF), 0);
    a2 = MAX(MIN(a2, 0x7FFF), 0);
    a3 = MAX(MIN(a3, 0x7FFF), 0);
    count = &pchr_count_saved;
    slot = *count;
    if (slot < 0x600) {
        s32 off = index * sizeof(PoolRec);
        pool = (PoolRec *)(count + 1);
        src = (PoolRec *)((u8 *)pool + off);
        if (src->scale != 0) {
            *count = slot + 1;
            dst = &pool[slot];
            dst->flags = a1 | 0x8000;
            less = a1 < a2;
            dst->index = index;
            dst->unk_02 = a2;
            dst->unk_06 = a3;
            if (less) {
                a1 = a2;
            }
            if (a1 < a3) {
                a1 = a3;
            }
            dst->scale = (src->scale * a1) / 4096;
            dst->unk_08 = src->unk_08;
            dst->unk_0C = 0;
            dst->unk_12 = src->unk_12;
            dst->unk_14 = src->unk_14;
            dst->unk_16 = 0;
            dst->unk_18 = src->unk_18;
            dst->unk_1A = src->unk_1A;
            return slot;
        }
    }
    return index;
}

void *quad_list_build(s32 *out_top, s32 *a, s32 *b, s32 ir0) {
    register s32 *offset_base asm("$12") = a + 1;
    s16 *offset_idx = (s16 *) offset_base;
    s32 group_count = *a;
    s32 total_size = ((group_count + 1) >> 1) * 4 + 4;
    s32 *cur;
    s32 line_n;
    s32 delta;
    s16 *out_offsets;
    s16 *a_idx;
    s16 *b_idx;
    s32 *a_rec;
    s32 *b_rec;
    register s32 *out asm("$8");
    s32 *a_cur;
    s32 *b_cur;
    s32 *out_cur;
    s32 sub_n;
    s32 pt_n;
    s32 i;
    s32 quad_n;
    s32 c_a;
    s32 c_b;
    s32 rows;
    register s32 offset_bytes asm("$2");
    u8 *src_a;
    u8 *src_b;
    u8 *dst;

    while (group_count-- > 0) {
        cur = (s32 *) ((u8 *) offset_base + *offset_idx++ * 4);
        cur++;
        line_n = cur[-1];
        total_size += 4;
        while (line_n-- > 0) {
            delta = *cur * 4 + 4;
            cur = (s32 *) ((u8 *) cur + delta);
            total_size += delta;
            delta = *cur * 0x1C + 4;
            cur = (s32 *) ((u8 *) cur + delta);
            total_size += delta;
        }
    }
    out_top = (s32 *) ((u8 *) out_top - total_size);
    gte_set(IR0, ir0);
    a_idx = (s16 *) (a + 1);
    rows = *a;
    a = (s32 *) a_idx;
    b_idx = (s16 *) (b + 1);
    b = (s32 *) b_idx;
    *out_top = rows;
    out_top++;
    out_offsets = (s16 *) out_top;
    offset_bytes = ((rows + 1) >> 1) * 4;
    out = (s32 *) ((u8 *) out_top + offset_bytes);
    while (rows-- > 0) {
        *out_offsets++ = out - out_top;
        a_rec = (s32 *) ((u8 *) a + *a_idx++ * 4);
        b_rec = (s32 *) ((u8 *) b + *b_idx++ * 4);
        a_rec++;
        sub_n = a_rec[-1];
        b_rec++;
        *out++ = sub_n;
        while (sub_n-- > 0) {
            b_rec++;
            a_rec++;
            pt_n = a_rec[-1];
            *out++ = pt_n;
            while (pt_n-- > 0) {
                b_rec++;
                a_rec++;
                *out++ = a_rec[-1];
            }
            a_rec++;
            a_cur = a_rec;
            b_cur = b_rec + 1;
            quad_n = a_cur[-1];
            out_cur = out + 1;
            *out = quad_n;
            while (quad_n-- > 0) {
                *(Rec800CF0D0 *) out_cur = *(Rec800CF0D0 *) a_cur;
                dst = (u8 *) (out_cur + 3);
                src_a = (u8 *) (a_cur + 3);
                src_b = (u8 *) (b_cur + 3);
                i = 4;
                do {
                    c_a = src_a[0];
                    c_b = src_a[1];
                    gte_set_ctrl(GFC, c_a);
                    gte_set_ctrl(BFC, c_b);
                    c_a = src_b[0];
                    c_b = src_b[1];
                    gte_set(IR2, c_a);
                    gte_set(IR3, c_b);
                    src_a += 2;
                    src_b += 2;
                    gte_intpl_b();
                    gte_get(MAC2, c_a);
                    gte_get(MAC3, c_b);
                    dst[0] = c_a;
                    dst[1] = c_b;
                    dst += 2;
                } while (--i > 0);
                out_cur += 7;
                a_cur += 7;
                b_cur += 7;
            }
            a_rec = a_cur;
            b_rec = b_cur;
            out = out_cur;
        }
    }
    return out_top - 1;
}

/* Interpolates each colour pair in `col` towards the far colours in `src` by `factor` (GTE INTPL) and writes
 * the 8-byte results below `out`, preceded by their count; returns the start of the written block. */
s32 *colour_intpl_list(s32 *out, s32 *src, s32 *col, s32 factor) {
    IntplColour *dst;
    IntplColour *end;
    s32 *far;
    s32 count;
    s32 far_gb;
    s32 far_r;
    s32 half;
    s32 far_b;

    gte_set(IR0, factor);
    far = src + 1;
    count = src[0];
    out = (s32 *)((u8 *)out - (count * 8 + 4));
    dst = (IntplColour *)(out + 1);
    end = dst + count;
    out[0] = count;
    far_gb = src[1];
    far_r = *(s16 *)&src[2];
    col++;
    while (dst != end) {
        factor = col[0]; /* the parameter's register is reused for the IR2/IR3 word */
        gte_load(IR1, col, 4);
        half = far_gb >> 16;
        far_b = (s16)far_gb;
        gte_set_ctrl(RFC, far_r);
        gte_set_ctrl(GFC, half);
        gte_set_ctrl(BFC, far_b);
        half = factor >> 16;
        gte_set(IR2, half);
        gte_set(IR3, factor);
        far += 2;
        col += 2;
        gte_intpl_b();
        far_gb = far[0];
        far_r = *(s16 *)&far[1];
        gte_store(MAC1, dst, 4);
        gte_get(MAC2, half);
        gte_store(MAC3, dst, 0);
        dst++;
        dst[-1].g = half;
    }
    return out;
}

/* Interpolates each colour of `base` towards the matching colour of `far` by `factor` (GTE INTPL) and writes
 * the results below `dst`, preceded by their count (far[0]); returns the start of the written block.
 * The colour pair passes through the scratchpad ($gp): far colour, then base colour. */
s32 *colour_list_intpl(s32 *dst, s32 *far, s32 *base, s32 factor) {
    PackedColour *cur;
    PackedColour *end;
    s32 *next_far;
    s32 *next_base;
    s32 count;
    s32 far_val;  /* far word, then the base red */
    s32 base_val; /* base word, then the far red */
    s32 g, b;

    gte_set(IR0, factor);
    next_far = far + 1;
    count = far[0];
    next_base = base + 1;
    dst = (s32 *)((u8 *)dst - (count * 4 + 4));
    cur = (PackedColour *)(dst + 1);
    dst[0] = count;
    far_val = far[1];
    base_val = base[1];
    end = cur + count;
    ((ColourIntplScratch *)scratch_top)->far.word = far_val;
    ((ColourIntplScratch *)scratch_top)->base.word = base_val;
    /* a goto loop: loop.c would strength-reduce the two byte stores into a second pointer */
    if (cur != end) {
    next:
        base_val = ((ColourIntplScratch *)scratch_top)->far.c.r;
        g = ((ColourIntplScratch *)scratch_top)->far.c.g;
        b = ((ColourIntplScratch *)scratch_top)->far.c.b;
        gte_set_FC(base_val, g, b);
        far_val = ((ColourIntplScratch *)scratch_top)->base.c.r;
        g = ((ColourIntplScratch *)scratch_top)->base.c.g;
        b = ((ColourIntplScratch *)scratch_top)->base.c.b;
        gte_set_IR123(far_val, g, b);
        do { /* loop weight for the register priorities */
            next_far++;
            next_base++;
        } while (0);
        gte_intpl_b();
        far_val = next_far[0];
        base_val = next_base[0];
        ((ColourIntplScratch *)scratch_top)->far.word = far_val;
        ((ColourIntplScratch *)scratch_top)->base.word = base_val;
        gte_store(MAC1, cur, 0);
        gte_get_MAC23(g, b);
        cur->c.g = g;
        cur++;
        cur[-1].c.b = b;
        if (cur != end) {
            goto next;
        }
    }
    return dst;
}

/*
 * Interpolates the pose list `from` towards `to` by t (GTE intpl, IR0 = t) and
 * writes the result to the block that ends at `buf`: the key count, then one
 * PoseKey per key. Each list is a count followed by three words per key
 * (x | y << 16, z | rx << 16, ry | rz << 16). Angles take the short way round.
 * Returns the start of the block.
 * The original is hand-written: the registers are pinned to match it.
 */
s32 *pose_list_intpl(s32 *buf, s32 *from, s32 *to, s32 t)
{
    register s32 *header asm("$14");
    register s32 count asm("$4");
    register s32 size asm("$3");
    register PoseKey *key asm("$9");
    register PoseKey *end asm("$5");
    register s32 *fromKey asm("$13");
    register s32 *toKey asm("$6");
    register s32 fromXY asm("$7");
    register s32 fromZRx asm("$4");
    register s32 fromRyRz asm("$7");
    register s32 toWord asm("$8");
    register s32 toZRx asm("$2");
    register s32 toY asm("$3");
    register s32 fromX asm("$7");
    register s32 fromY asm("$3");
    register s32 fromZ asm("$2");
    register s32 fromAngle asm("$4");
    register s32 toAngle asm("$2");
    register s32 val asm("$2");
    register s32 outY asm("$3");
    register s32 wrapX asm("$12");
    register s32 wrapY asm("$11");
    register s32 wrapZ asm("$10");
    register s32 outRx asm("$8");
    register s32 outRy asm("$3");
    register s32 outRz asm("$2");

    header = buf;
    gte_set(IR0, t);
    fromKey = from + 1;
    count = from[0];
    size = count * sizeof(PoseKey);
    header = (s32 *)((u8 *)header - (size + 4));
    key = (PoseKey *)(header + 1);
    *header = count;
    fromXY = from[1];
    fromZRx = from[2];
    end = (PoseKey *)((u8 *)key + size);
    toKey = to + 1;
    if (key != end) {
    next:
        fromY = fromXY >> 16;
        val = fromXY << 16;
        fromX = val >> 16;
        fromZ = (fromZRx << 16) >> 16;
        gte_set_ctrl(RFC, fromX);
        gte_set_ctrl(GFC, fromY);
        gte_set_ctrl(BFC, fromZ);
        toWord = toKey[0];
        toZRx = toKey[1];
        gte_set(IR1, toWord);
        toY = toWord >> 16;
        gte_set(IR2, toY);
        gte_set(IR3, toZRx);
        fromAngle = fromZRx >> 16;
        toAngle = toZRx >> 16;
        gte_intpl_b();
        toWord = toKey[2];
        fromRyRz = fromKey[2];
        gte_get(MAC2, outY);
        gte_store(MAC1, key, 0);
        gte_store(MAC3, key, 4);
        key->y = outY;
        __asm__ volatile(""); /* keeps the store above the angle math, as in the original */

        wrapX = toAngle - fromAngle - 0x800;
        ANGLE_WRAP_UP(wrapX);
        val = wrapX + fromAngle - 0x1800;
        gte_set_ctrl(RFC, fromAngle);
        gte_set(IR1, val);

        val = toWord & 0xFFFF;
        fromAngle = fromRyRz & 0xFFFF;
        val -= fromAngle;
        wrapY = val - 0x800;
        ANGLE_WRAP_UP(wrapY);
        val = wrapY + fromAngle - 0x1800;
        gte_set_ctrl(GFC, fromAngle);
        gte_set(IR2, val);

        val = toWord >> 16;
        fromAngle = fromRyRz >> 16;
        val -= fromAngle;
        wrapZ = val - 0x800;
        ANGLE_WRAP_UP(wrapZ);
        val = wrapZ + fromAngle - 0x1800;
        gte_set_ctrl(BFC, fromAngle);
        gte_set(IR3, val);

        fromKey += 3;
        toKey += 3;
        gte_intpl_b();
        fromXY = fromKey[0];
        fromZRx = fromKey[1];
        gte_get_MAC123(outRx, outRy, outRz);
        outRx &= 0xFFF;
        outRy &= 0xFFF;
        outRz &= 0xFFF;
        key->ry = outRy;
        key->rx = outRx;
        key++;
        key[-1].rz = outRz;
        if (key != end)
            goto next;
    }
    return header;
}

/*
 * Transforms every vertex of the list at `in` with the GTE (rotation matrix,
 * no translation, sf=1, no clamp) and writes the results to the block that
 * ends at `out`. The block starts with the vertex count.
 * Returns the start of the block.
 */
s32 *vtx_rotate_list(void *out, s32 *in) {
    s32 count;
    s32 *header;
    GteOut *dst;
    GteVtx *src;
    GteOut *end;
    s32 xy;
    s32 z;
    s32 mac2;

    count = in[0];
    header = (s32 *)((u8 *)out - (count * 8 + 4));
    *header = count;
    dst = (GteOut *)((u8 *)header + 4);
    src = (GteVtx *)((u8 *)in + 4);
    end = (GteOut *)((u8 *)dst + count * 8);
    xy = src->xy;
    z = src->z;
    if (dst != end) {
        do {
            gte_set(VXY0, xy);
            gte_set(VZ0, z);
            src++;
            gte_nop();
            gte_rtv0_b();
            xy = src->xy;
            z = src->z;
            gte_store(MAC1, dst, 0);
            gte_get(MAC2, mac2);
            gte_store(MAC3, dst, 4);
            dst++;
            ((s16 *)dst)[-3] = (s16)mac2;
        } while (dst != end);
    }
    return header;
}

s32 *gte_transform_to_end(s32 end, s32 *src) {
    s32 count;
    s32 bytes;
    s32 size;
    s32 *out;
    GteVertexOut *dst;
    GteVertexOut *dstEnd;
    GteVertexIn *in;
    s16 *h;
    s32 xy;
    s32 z;
    s32 m2;
    s32 m3;

    count = src[0];
    bytes = count * 12;
    size = bytes + 4;
    out = (s32 *)(end - size);
    dst = (GteVertexOut *)(out + 1);
    dstEnd = (GteVertexOut *)((u8 *)dst + bytes);
    out[0] = count;
    in = (GteVertexIn *)(src + 1);
    xy = in->xy;
    z = in->z;
    if (dst != dstEnd) {
        h = (s16 *)(out - 1);
        do {
            gte_set(VXY0, xy);
            gte_set(VZ0, z);
            in++;
            gte_nop();
            gte_rtv0_b();
            xy = in->xy;
            z = in->z;
            gte_store(MAC1, dst, 0);
            gte_get(MAC2, m2);
            gte_get(MAC3, m3);
            h += 6;
            dst++;
            h[-1] = m2;
            h[0] = m3;
        } while (dst != dstEnd);
    }
    return out;
}

/* Walks the pchr_table tree from `index` depth first (children by `link`, then the sibling at
 * unk_06 unless bit 0x8000 is set), returning through the computed `resume` address with the
 * $gp stack instead of recursion. Each entry blends its child's lists toward the sibling's by
 * link_count, or (bit 0x8000) rotates the child's vertices with a GTE matrix built from its
 * halfwords. New lists are built at work_area_ptr->unk_80, which is advanced. */
void pchr_lists_build(s32 index) {
    WorkArea *wa;
    void *resume;
    s32 *out;
    Pchr *node;
    Pchr *child;
    Pchr *sibling;
    Pchr *from;
    Pchr *dst;
    Pchr *to;
    s32 *list;
    s32 *target;
    s32 *poses;
    s32 factor;
    s32 other;
    s16 flags;

    wa = work_area_ptr;
    index &= 0x7FF;
    resume = &&done;
    out = (s32 *)wa->list_cursor;
walk:
    node = &pchr_table[index];
    if (node->link_count < 0) {
        goto *resume;
    }
    index = (s16)node->link;
    child = &pchr_table[index];
    if (child->link_count >= 0) {
        scratch_push(node);
        scratch_push(child);
        scratch_push(resume);
        resume = &&after_child;
        goto walk;
    after_child:
        {
            void *saved_resume;
            Pchr *saved_child;
            Pchr *saved_node;

            scratch_pop(saved_resume);
            scratch_pop(saved_child);
            scratch_pop(saved_node);
            resume = saved_resume;
            child = saved_child;
            node = saved_node;
        }
    }
    from = child;
    if (!(node->unk_00 & 0x8000)) {
        index = node->unk_06;
        sibling = &pchr_table[index];
        if (sibling->link_count >= 0) {
            scratch_push(node);
            scratch_push(child);
            scratch_push(sibling);
            scratch_push(resume);
            resume = &&after_sibling;
            goto walk;
        after_sibling:
            {
                void *saved_resume;
                Pchr *saved_sibling;
                Pchr *saved_child;
                Pchr *saved_node;

                scratch_pop(saved_resume);
                scratch_pop(saved_sibling);
                scratch_pop(saved_child);
                scratch_pop(saved_node);
                resume = saved_resume;
                sibling = saved_sibling;
                child = saved_child;
                node = saved_node;
            }
            from = child;
        }
    }
    flags = node->unk_00;
    dst = node;
    if (!(flags & 0x8000)) {
        other = node->unk_1A;
        factor = node->link_count;
        to = sibling;
        if (other != 0) {
            Pchr *copy = &pchr_table[other];

            PCHR_LISTS(node)->colours = PCHR_LISTS(copy)->colours;
            PCHR_LISTS(node)->list_04 = PCHR_LISTS(copy)->list_04;
            PCHR_LISTS(node)->quads = PCHR_LISTS(copy)->quads;
        } else {
            if (flags == 1) {
                list = PCHR_LISTS(child)->quads;
                target = PCHR_LISTS(to)->quads;
                PCHR_LISTS(node)->quads = list;
                if (list != target) {
                    out = quad_list_build(out, list, target, factor);
                    PCHR_LISTS(node)->quads = out;
                }
            }
            list = PCHR_LISTS(from)->colours;
            target = PCHR_LISTS(to)->colours;
            PCHR_LISTS(dst)->colours = list;
            if (list != target) {
                out = colour_intpl_list(out, list, target, factor);
                PCHR_LISTS(dst)->colours = out;
            }
            list = PCHR_LISTS(from)->list_04;
            target = PCHR_LISTS(to)->list_04;
            PCHR_LISTS(dst)->list_04 = list;
            if (list != target) {
                out = colour_list_intpl(out, list, target, factor);
                PCHR_LISTS(dst)->list_04 = out;
            }
        }
        if (PCHR_LISTS(dst)->poses == NULL) {
            list = PCHR_LISTS(from)->poses;
            target = PCHR_LISTS(to)->poses;
            PCHR_LISTS(dst)->poses = list;
            if (list != target) {
                out = pose_list_intpl(out, list, target, factor);
                PCHR_LISTS(dst)->poses = out;
            }
        }
        goto *resume;
    }
    other = node->unk_1A;
    to = child;
    if (other != 0) {
        to = &pchr_table[other];
    }
    other = node->link_count;
    index = node->unk_06;
    gte_set_ctrl(R11R12, flags & 0x7FFF);
    gte_set_ctrl(R13R21, 0);
    gte_set_ctrl(R22R23, other);
    gte_set_ctrl(R31R32, 0);
    gte_set_ctrl(R33, index);
    PCHR_LISTS(node)->list_04 = PCHR_LISTS(to)->list_04;
    out = vtx_rotate_list(out, PCHR_LISTS(to)->colours);
    PCHR_LISTS(node)->colours = out;
    if (PCHR_LISTS(node)->poses == NULL) {
        poses = PCHR_LISTS(child)->poses;
        PCHR_LISTS(node)->poses = poses;
        if (poses != NULL) {
            /* `list` is whatever the last blend left in it (the original passes it unset) */
            out = gte_transform_to_end((s32)out, list);
            PCHR_LISTS(node)->poses = out;
        }
    }
    goto *resume;
done:
    wa->list_cursor = (s32)out;
}

/* Calls pchr_lists_build for the first `count` entries of the table at light_rec_end. */
void gte_run_table(s32 count) {
    s16 *entry = light_rec_end;

    while (count > 0) {
        s32 value = *entry++;
        count--;
        pchr_lists_build(value);
    }
}

/* Loads the light matrix's L11/L13/L31/L33 from the current entry's clamped offset:
   each axis is max(off, lim - off, 0) scaled by 2^17 / size, paired with isqrt(v^2 + 2^24). */
s32 light_matrix_set(void) {
    s32 ofs = cur_view_index * sizeof(ViewLightParams);
    ViewLightParams *rec = (ViewLightParams *)((u8 *)view_light_params + ofs);
    ViewOffset *off = (ViewOffset *)((u8 *)&view_light_params[0].off + ofs);
    ViewVramRect *lim;
    s32 x, y, w, h;
    s32 ox, oy, rest_x, rest_y;
    s32 len_x, len_y;

    ox = off->x;
    lim = (ViewVramRect *)((u8 *)&view_light_params[0].lim + ofs);
    w = rec->w;
    h = rec->h;
    rest_x = lim->w - ox;
    x = ox;
    if (x < rest_x) x = rest_x;
    if (x < 0) x = 0;
    oy = off->y;
    rest_y = lim->h - oy;
    y = oy;
    if (y < rest_y) y = rest_y;
    if (y < 0) y = 0;
    mips_div(x << 17, w);
    mips_mflo(x);
    mips_div(y << 17, h);
    mips_mflo(y);
    len_x = isqrt(x * x + 0x1000000);
    len_y = isqrt(y * y + 0x1000000);
    gte_set_ctrl(L11L12, len_x);
    gte_set_ctrl(L13L21, x);
    gte_set_ctrl(L31L32, len_y);
    gte_set_ctrl(L33, y);
}

extern PchrBank pchr_bank __asm__("pchr_count");
s32 light_records_build(void) {
    s32 *rot;
    s32 t0, t1, t2;
    register s32 n_out asm("$20");
    register s32 prev asm("$19");
    s32 count;
    s16 *out;
    s32 i;
    s32 limit;
    LightRec18 *rec;
    PchrBank *bank;
    register Pchr *table asm("$24");
    s32 first;
    s32 flags, idx;
    s32 radius, depth, z, x, y, zc;
    s32 shift, exp;
    s32 m;
    s16 *sqrt;
    s32 dist, range, bias, link, step, v;
    s32 j;

    light_matrix_set();
    rot = draw_views[cur_view_index].rot;
    gte_set_R012(t0, t1, t2, rot[0], rot[1], rot[2]);
    gte_set_R34(t0, t1, rot[3], rot[4]);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    n_out = 0;
    prev = -1;
    count = 0;
    out = light_rec_end;
    i = light_rec_count - 1;
    limit = pchr_count_saved;
    rec = (LightRec18 *)light_rec_table + i;
    bank = (PchrBank *)&pchr_count;
    first = bank->count;
    table = bank->table;
    for (; i >= 0; i--, rec--) {
        gte_ldv0(rec);
        gte_rtps();
        idx = rec->index;
        flags = idx & 0xB000;
        idx &= 0x7FF;
        radius = table[idx].bounds_radius;
        gte_get(IR0, depth);
        if (radius <= 0) {
            continue;
        }
        gte_get(MAC3, z);
        depth = (depth + 0x7F) & 0x7FE0;
        if (depth >= 0x1000) {
            continue;
        }
        if (z + radius < 0x21) {
            continue;
        }
        gte_get(MAC1, x);
        gte_get(MAC2, y);
        if (z < 0x21) {
            zc = 0x20;
        } else {
            zc = z;
        }
        gte_set(VXY1, radius);
        gte_set(VZ1, zc);
        gte_llv1();
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        radius = -radius;
        gte_get(MAC1, zc);
        gte_get(MAC3, m);
        if (zc < x) {
            continue;
        }
        if (m < y) {
            continue;
        }
        gte_set(VXY1, radius & 0xFFFF);
        z += radius;
        gte_nop();
        gte_llv1_b();
        radius = z < 0x21;
        if (z < 0x800) {
            radius |= 0x10;
        }
        gte_get(MAC1, zc);
        gte_get(MAC3, m);
        if (zc < x) {
            radius |= 1;
        }
        if (m < y) {
            radius |= 1;
        }
        gte_get(VXY0, x);
        gte_get(VZ0, y);
        gte_set(IR1, x);
        x >>= 16;
        gte_set(IR2, x);
        gte_set(IR3, y);
        gte_sqr0();
        rec->depth = depth | radius;
        gte_get(MAC1, x);
        gte_get(MAC2, y);
        gte_get(MAC3, z);
        radius = x + y + z;
        m = ~1;
        if (radius != 0) {
            gte_set(LZCS, radius);
            sqrt = SQRT - 64;
            gte_get(LZCR, zc);
            if (radius < 0) {
                zc = 0;
            }
            shift = 31 - zc;
            zc &= m;
            exp = zc - 24;
            m = radius << exp;
            if (exp < 0) {
                m = (u32)radius >> -exp;
            }
            radius = sqrt[m];
            shift >>= 1;
            radius <<= shift;
            radius = (u32)radius >> 12;
        }
        dist = radius;
        if (dist > 0x7FFF) {
            dist = 0x7FFF;
        }
        flags |= table[idx].unk_12;
        bias = table[idx].angle;
        range = draw_views[cur_view_index].unk_08 * dist;
        range >>= 12;
        do {
        } while (0);
        link = table[idx].unk_1A;
        if (link != 0 && table[idx].far_bias == 0) {
            j = link;
            if (table[j].unk_14 < range) {
                do {
                    step = table[j].far_bias;
                    if (step == 0) {
                        goto next;
                    }
                    j += step;
                } while (table[j].unk_14 < range);
                if (j >= limit) {
                    goto next;
                }
                if (table[j].bounds_radius == 0) {
                    goto next;
                }
                if (*table[j].data != *table[idx].data) {
                    goto search;
                }
                if (*(s32 *)&table[idx].unk_00 < 0) {
                    if (limit >= 0x600) {
                        goto next;
                    }
                    table[limit] = table[j];
                    table[limit].unk_0C = table[idx].unk_0C;
                    table[limit].unk_1A = j;
                    idx = limit;
                    limit = idx + 1;
                    pchr_bank.pad = limit;
                } else {
                    table[idx].unk_1A = j;
                }
            }
        } else {
        search:
            if (table[idx].unk_14 < range) {
                if (table[idx].far_bias == 0) {
                    goto next;
                }
                idx += table[idx].far_bias;
                goto search;
            }
            if (idx >= limit) {
                goto next;
            }
            if (table[idx].bounds_radius == 0) {
                goto next;
            }
        }
        if (flags & 0x800) {
            dist = (flags & 0x7FF) + 1;
        } else {
            v = dist + bias;
            if (v < 0) {
                v = 0;
            }
            v >>= 5;
            if (v >= 0x200) {
                v = 0x1FF;
            }
            dist = 0x208 - v;
        }
        if (idx >= first) {
            *out++ = idx;
            n_out++;
        }
        rec->index = idx | (flags & 0x3000);
        rec->level = dist | (flags & 0x8000);
        rec->next = prev;
        prev = i;
        count++;
    next:;
    }
    light_rec_count = count;
    light_rec_head = prev;
    return n_out;
}

extern DrawList draw_list __asm__("d_8011FFE4");
/* Builds the light environment's draw list (gte_light_setup): for each record from light_rec_head (linked by next)
 * a LightDrawOut block below work_area_ptr->unk_80. A record without rotation, matrix flags or bones keeps the
 * root node with its position; else a node transformed by the view: rotation from the record's angles, light
 * matrix L * R, then 0x1000: the view's second matrix (third row halved), 0x2000: none, else the view's rotation.
 * Mesh parts get their view distances (rtv0tr + sqr0), bone entries one node and part per bone; the keys are
 * insertion-sorted by distance and stored below, zero-terminated. The record loop is goto-built and count sits in
 * s6: a real loop or a free count changes the original's register allocation (reference weights). */
void light_draw_list_build(void) {
    u8 *top;
    LightRecWords *recs;
    LightRecWords *rec;
    LightDrawNode *bnode;
    LightDrawRoot *root;
    LightDrawOut *out;
    LightDepthKey *keys;
    s32 *bones;
    LightDrawNode *node;
    PchrVert *verts;
    PchrPartCursor parts;
    s32 idx, flags, i, j;
    register s32 count asm("$22");
    s32 x, y, z, depth_level;
    s32 rx, ry, rz, dist;
    s32 vz, vxy; /* a mesh vertex's z and xy, then MAC3 and MAC1 */
    s32 mask;
    s16 *rot;
    s32 index;
    s32 bone_count;
    s32 scale_x, scale_y;

    root = scratch_alloc(sizeof(LightDrawRoot));
    root->scale = *(SVECTOR *)&view_light_params[cur_view_index];
    *(s32 *)&root->node.trans.v.vx = 0;
    *(s32 *)&root->node.trans.v.vz = 0;
    scale_x = root->scale.vx;
    root->node.pos.zf.h.depth = 0;
    scale_y = root->scale.vy;
    root->scale.vx = scale_x << 1;
    root->scale.vy = scale_y << 1;
    copy_record20((s32 *)view_light_params[cur_view_index].rot, (s32 *)root->node.rot);
    copy_record20((s32 *)light_sets[light_env_index].light_dir, (s32 *)root->node.light);
    top = (u8 *)work_area_ptr->list_cursor;
    recs = light_rec_table;
    draw_list.end = (s32 *)top;
    idx = light_rec_head;
    if (idx < 0) {
        goto done;
    }
next:
    {
        top -= sizeof(LightDrawOut);
        rec = &recs[idx];
        index = rec->index;
        flags = index & 0x3000;
        index &= 0x7FF;
        ((LightDrawOut *)top)->pchr = &pchr_table[index];
        y = rec->unk_14 & 0xFFFFFF;
        depth_level = rec->depth_level;
        ((LightDrawOut *)top)->level = depth_level >> 16;
        ((LightDrawOut *)top)->unk_04 = y;
        x = rec->xy;
        z = rec->z;
        rx = rec->rot_xy;
        out = (LightDrawOut *)top;
        rz = rec->rot_z;
        ry = rx >> 16;
        if (((rx | ry | rz) & 0xFFF) == 0 && flags == 0 && ((LightDrawOut *)top)->pchr->unk_0C == NULL) {
            node = &root->node;
            node->pos.xy = x;
            node->pos.zf.h.z = z;
            node->pos.zf.h.depth = depth_level & 0x7FFF;
        } else {
            node = scratch_alloc(sizeof(LightDrawNode));
            gte_load_R_split(root->node.rot);
            gte_set_V0(x, z);
            gte_rtv0();
            node->pos.xy = 0;
            node->pos.zf.word = (depth_level | 0x8000) << 16;
            gte_store_MAC13_get_MAC2(node, y);
            node->trans.v.vy = y;
            rot = node->rot;
            FAKE_OPAQUE(rot);
            rot_matrix(rot, rx, ry, rz);
            mul_matrix(root->node.light, rot, node->light);
            if (flags & 0x1000) {
                s32 m20, m21, m22;

                mul_matrix(view_light_params[cur_view_index].rot_b, rot, rot);
                m20 = rot[6];
                m21 = rot[7];
                m22 = rot[8];
                FAKE_OPAQUE(m20);
                FAKE_OPAQUE(m21);
                FAKE_OPAQUE(m22);
                node->rot[6] = m20 >> 1;
                node->rot[7] = m21 >> 1;
                node->rot[8] = m22 >> 1;
            } else if (!(flags & 0x2000)) {
                mul_matrix(root->node.rot, rot, rot);
            }
        }
        bones = out->pchr->unk_0C;
        if (bones == NULL) {
            top -= sizeof(LightDrawPos);
            z = node->pos.zf.word;
            ((LightDrawPos *)top)->zf.word = z;
            if (z < 0) {
                x = node->trans.v.vx;
                y = node->trans.v.vy;
                z = node->trans.v.vz;
                gte_set_TR_r(x, y, z);
                vec_scale_mvmva(node->trans.w, &root->scale.vx, (s16 *)top);
                top -= sizeof(node->rot);
                copy_record20((s32 *)node->light, (s32 *)top);
                top -= sizeof(node->rot);
                scale_rows(node->rot, &root->scale.vx, (s16 *)top);
                z = 0;
                x = 0;
            } else {
                x = node->pos.xy;
                ((LightDrawPos *)top)->xy = x;
                gte_set_ctrl(TRX, 0);
                gte_set_ctrl(TRY, 0);
                gte_set_ctrl(TRZ, 0);
            }
            mask = ~0x10000; /* drops the carry from the x half into y */
            x &= mask;
            gte_load_R_split(node->rot);
            parts.word = out->pchr->data;
            keys = scratch_alloc(32 * sizeof(LightDepthKey));
            parts.word++;
            count = parts.word[-1];
            if (count >= 2) {
                verts = (PchrVert *)(*(s32 **)out->pchr + 1);
                for (i = 0; i < count; i++) {
                    vxy = verts->xy;
                    vz = verts->z;
                    gte_set_V0((vxy + x) & mask, vz + z);
                    verts++;
                    gte_nop();
                    gte_rtv0tr_b();
                    y = *parts.index;
                    gte_sqr0_b();
                    parts.index++;
                    keys[i].key = y & 0xFFFF;
                    gte_get(MAC1, vxy);
                    gte_get(MAC2, y);
                    gte_get(MAC3, vz);
                    keys[i].dist = vxy + y + vz;
                }
            }
        } else {
            keys = scratch_alloc(32 * sizeof(LightDepthKey));
            bnode = scratch_alloc(sizeof(LightDrawNode));
            bones++;
            bone_count = bones[-1];
            parts.word = out->pchr->data;
            parts.word++;
            count = parts.word[-1];
            count = MIN(bone_count, count);
            verts = (PchrVert *)(*(s32 **)out->pchr + 1);
            for (i = 0; i < count; i++) {
                LightDrawPos *bpos;

                top -= sizeof(LightDrawPos);
                bpos = (LightDrawPos *)top;
                bpos->zf.h.depth = node->pos.zf.h.depth;
                rot_matrix(bnode->rot, ((PchrBone *)bones)->rx, ((PchrBone *)bones)->ry, ((PchrBone *)bones)->rz);
                top -= sizeof(node->rot);
                mul_matrix(node->light, bnode->rot, top);
                top -= sizeof(node->rot);
                mul_matrix(node->rot, bnode->rot, bnode->rot);
                scale_rows(bnode->rot, &root->scale.vx, (s16 *)top);
                x = node->trans.v.vx;
                y = node->trans.v.vy;
                z = node->trans.v.vz;
                gte_set_TR_r(x, y, z);
                gte_load_R_split(node->rot);
                gte_ldv0(bones);
                bones += 3;
                gte_rtv0tr_b();
                gte_get(MAC1, x);
                gte_get(MAC2, y);
                gte_get(MAC3, z);
                bnode->trans.v.vx = x;
                bnode->trans.v.vy = y;
                bnode->trans.v.vz = z;
                gte_set_TR_r(x, y, z);
                vec_scale_mvmva(bnode->trans.w, &root->scale.vx, (s16 *)bpos);
                gte_load_R_split(bnode->rot);
                gte_ldv0(verts);
                verts++;
                gte_nop();
                gte_rtv0tr_b();
                y = *parts.index;
                parts.index++;
                gte_sqr0_b();
                x = (u8 *)out - top - (sizeof(LightDrawPos) + 2 * 20); /* this bone's block from the first */
                keys[i].key = (y & 0xFFFF) | (x << 16);
                gte_get(MAC1, x);
                gte_get(MAC2, y);
                gte_get(MAC3, z);
                keys[i].dist = x + y + z;
            }
        }
        for (i = 1; i < count; i++) {
            y = keys[i].key;
            dist = keys[i].dist;
            for (j = i - 1; j >= 0; j--) {
                if (!(dist < keys[j].dist)) {
                    break;
                }
                keys[j + 1].key = keys[j].key;
                keys[j + 1].dist = keys[j].dist;
            }
            keys[j + 1].key = y;
            keys[j + 1].dist = dist;
        }
        i = (u8 *)out - top;
        if (count < 2 && bones == NULL) {
            out->size = i | 0x8000;
        } else {
            out->size = i;
            for (i = 0; i < count; i++) {
                top -= 4;
                *(s32 *)top = keys[i].key;
            }
            top -= 4;
            *(s32 *)top = 0;
        }
        scratch_top = (u8 *)root + sizeof(LightDrawRoot);
        if ((idx = rec->next) >= 0) {
            goto next;
        }
    }
done:
    scratch_top -= sizeof(LightDrawRoot);
    work_area_ptr->list_cursor = (s32)top;
}

/* Copies the records of chain light_env_index within 0x4000 of the current camera to the output list, at most 0x400. */
void spark_list_collect_near(void) {
    SparkArea *area = (SparkArea *)&spark_list;
    s32 n;
    SparkOut *out;
    u32 idx;
    Camera *cam;
    s32 cx, cy, cz;
    SparkRec *s;
    s32 dx, dy, dz, w, colour, rot;

    FAKE_OPAQUE(area);
    n = area->out_count;
    out = &area->out[n];
    idx = area->list.head[light_env_index];
    cam = &cameras[cur_camera_index];
    cx = cam->pos.vx;
    cy = cam->pos.vy;
    cz = cam->pos.vz;
    while (idx != 0) {
        s = &area->list.items[idx - 1];
        idx = s->next;
        dz = s->z - cz;
        if (ABS(dz) < 0x4000) {
            dx = s->x - cx;
            if (ABS(dx) < 0x4000) {
                dy = s->y - cy;
                if (ABS(dy) < 0x4000) {
                    out->x = dx;
                    out->y = dy;
                    out->z = dz;
                    colour = *(s32 *)s->colour;
                    rot = *(s32 *)&s->yaw;
                    w = *(s32 *)&s->roll;
                    out->unk_0C = w;
                    out->colour = colour;
                    out->unk_08 = rot;
                    out->unk_06 = w >> 16;
                    out++;
                    n++;
                    if (n >= 0x400) {
                        break;
                    }
                }
            }
        }
    }
    area->out_count = n;
}

/* Loads the GTE for the current light environment (light_env_index): the depth cue, the light colour matrix and the
 * back colour, then the draw-state calls. ctx is the view's context pointer (ViewDraw.ctx). */
void gte_light_setup(u8 *ctx) {
    s32 *depth_cue;
    LightEnv *env;

    light_rec_end = (s16 *)((u8 *)light_rec_table + light_rec_count * 24);
    gte_set_ctrl(H, 0x80);
    depth_cue = light_envs[light_env_index].depth_cue;
    gte_set_ctrl2(DQA, depth_cue[0], DQB, depth_cue[1]);
    SCRATCH_STACK_ENTER(SCRATCH_STACK_TOP);
    gte_run_table(light_records_build());
    light_draw_list_build();
    d_8011FFE4 = work_area_ptr->list_cursor;
    SCRATCH_STACK_LEAVE();
    env = &light_envs[light_env_index];
    gte_set_ctrl3(LR1LR2, env->color[0], LR3LG1, env->color[1], LG2LG3, env->color[2]);
    gte_set_ctrl2_ab(LB1LB2, env->color[3], LB3, env->color[4]);
    gte_set_ctrl3_bca(RBK, env->back[0], GBK, env->back[1], BBK, env->back[2]);
    packet_free_list_reset();
    light_env_draw(ctx);
    mask_layers_draw();
}

void *model_groups_draw(void *prim, s32 ot, ModelTables *model, s32 flags) {
    /* The original keeps these in fixed registers (v0, a0, v1): user register
     * variables are what stop cse/combine from folding the shifts and copies. */
    register s32 angle asm("$2");
    register s32 gte_arg asm("$4");
    register s32 cos_v asm("$3");
    s32 vz;
    s32 idx;
    s32 *p;
    s32 n;
    s32 cnt;
    s32 *q;
    s32 *list;
    s32 *verts;
    s32 *norms;
    u8 *buf;
    s32 z;

    buf = scratch_alloc(0x1E0);
    vz = flags & 0x7FE0;
    angle = vz;
    vz <<= 5;
    vz >>= 12;
    gte_arg = vz << 6;
    gte_set(VZ1, gte_arg);
    /* cos_table[angle / 4], the signed division rounding spelled out */
    gte_arg = angle;
    idx = angle;
    if (gte_arg < 0) {
        idx = gte_arg + 3;
    }
    cos_v = cos_table[(idx >> 2) & 0xFFF].value;
    angle = 0x1000;
    gte_arg = angle - cos_v;
    gte_set_ctrl(ZSF3, gte_arg);
    p = (s32 *)((flags >> 16) * 4 + (s32)model->groups);
    p += 2;
    n = p[-1];
    verts = model->verts + 1;
    norms = model->norms + 1;
    while (n-- > 0) {
        p++;
        list = p;
        cnt = p[-1];
        p += cnt;
        z = vert_transform_groups(cnt, list, verts, buf, flags & 0x1F);
        p++;
        cnt = p[-1];
        q = p;
        p += cnt * 7;
        if (z >= 0) {
            if ((flags & 0x10) && z < 0x800) {
                prim = prim_build_tris_subdiv(cnt, q, buf - 0xC, norms, prim, ot);
            } else {
                prim = prim_build_tris(cnt, q, buf - 0xC, norms, prim, ot);
            }
            if (d_8011FFE4 - (s32)prim < 0x6000) {
                break;
            }
        }
    }
    scratch_top -= 0x1E0;
    return prim;
}

#ifdef NON_MATCHING
/* Calls model_groups_draw(prim, ot, model, flags) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * C companion of hand-written asm (not compiled): the asm keeps the old $sp in $at and sets up the frame by hand
 * (FINDINGS "$sp in C"). */
void *model_groups_draw_scratch(void *prim, s32 ot, ModelTables *model, s32 flags) {
    void *ret;

    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    ret = model_groups_draw(prim, ot, model, flags);
    SCRATCH_STACK_LEAVE_BELOW();
    return ret;
}
#else
INCLUDE_ASM("../src/stage/asm", model_groups_draw_scratch);
#endif

/* Draws the light environment's records (gte_light_setup): loads the GTE screen state, then for each record
 * (draw_list.end down, light_rec_count of them) the colour, each vertex's translation and matrix, and calls
 * model_groups_draw_scratch per index word. Variables are reused as in the original (GCC 2.7.2 keeps one register per
 * variable): the register choices follow from it. */
void light_env_draw(u8 *base) {
    WorkArea *wa = work_area_ptr;
    DrawScratch *sc;
    s32 *p;     /* the light record, then the view scale, then the index words */
    s32 *m;     /* the scaled view matrix, then the vertex's matrix */
    ViewTail *vt;
    s16 *ofs;
    s32 *src;   /* the light words for copy_record20, then the vertex's matrix in the record */
    s32 *cur;
    s32 count;
    s32 *prev;
    s32 *b;
    s32 lo;
    s32 x, y;
    s32 ox, oy;

    sc = scratch_alloc(0x30);
    gte_set(VXY1, sc);
    p = (s32 *)(light_env_colours + light_env_index * 0x84);
    sc->env[0] = ((SVECTOR *)p)->vx;
    sc->env[1] = ((SVECTOR *)p)->vy;
    y = ((SVECTOR *)p)->vz;
    sc->env[3] = draw_list.unk_00;
    sc->env[2] = y;
    lo = scale_vec[0] * 29 / 4096;
    y = scale_vec[1] * 24 / 4096;
    gte_set_ctrl(ZSF4, (y << 8) | lo);
    vt = &view_tails[cur_view_index];
    y = vt->vram_w;
    x = vt->vram_h;
    /* The view's VRAM size, passed in HI to the hand-written vert_transform_groups (its mfhi), which model_groups_draw_scratch reaches. */
    __asm__ volatile("mthi %0" : : "r"(y | (x << 16)));
    ofs = &view_tails[cur_view_index].ofs_x;
    ox = ofs[0];
    oy = ofs[1];
    gte_set_ctrl(OFX, ox << 16);
    gte_set_ctrl(OFY, oy << 16);
    m = scratch_alloc(0x14);
    b = scratch_alloc(0x14);
    p = (s32 *)scratch_top;
    *(SVECTOR *)p = *(SVECTOR *)((u8 *)&view_tails[cur_view_index] - 0x1C);
    src = (s32 *)(light_env_colours - 0x40 + light_env_index * 0x84);
    ((SVECTOR *)p)->vx *= 2;
    ((SVECTOR *)p)->vy *= 2;
    copy_record20(src, b);
    scale_rows(view_tails[cur_view_index].rot[0], (s16 *)p, (s16 *)m);
    gte_set_ctrl(H, 0x40);
    count = light_rec_count;
    cur = draw_list.end;
    prev = 0;
    if (count > 0) {
        do {
            DrawRec *rec;
            s32 head;
            s32 flags;
            s32 next;
            u8 *prim;
            s32 color;
            s32 idx;
            s32 id;
            s32 *vec;

            cur -= 3;
            rec = (DrawRec *)cur;
            head = rec->head;
            p = (s32 *)((u8 *)rec - (head & 0x7FFF));
            if (head < 0) {
                next = 1;
            } else {
                p--;
                next = *p;
            }
            color = rec->color;
            flags = rec->prim;
            prim = base + ((flags & 0x7FFF) << 2);
            if ((flags & 0x8000) && color != 0) {
                u32 *pkt = wa->packet;
                u32 *q;

                wa->packet = pkt + 4;
                q = pkt + 1;
                pkt[2] = packet_free_list;
                packet_free_list = (s32)pkt;
                pkt[0] = 0;
                pkt[1] = 0;
                addPrim(prim, q);
                addPrim(prim, pkt);
                prim = (u8 *)pkt;
                pkt[3] = color;
                color = 0x848484;
            }
            if (color == 0) {
                color = 0x848484;
            }
            gte_set(RGB, color);
        vertex:
            idx = next >> 16;
            vec = (s32 *)((u8 *)rec - idx);
            src = vec - 2;
            x = vec[-1];
            y = vec[-2];
            id = x >> 16;
            if (x < 0) {
                s32 tz;

                gte_set(VXY2, 0);
                gte_set(VZ2, 0);
                lo = (s16)y;
                y >>= 16;
                tz = (s16)x;
                sc->trans[0] = lo;
                sc->trans[1] = y;
                sc->trans[2] = tz;
                gte_set_ctrl(TRX, lo);
                gte_set_ctrl(TRY, y);
                gte_set_ctrl(TRZ, tz);
                m = src;
            } else {
                gte_set(VXY2, y);
                gte_set(VZ2, x);
                gte_set_ctrl(TRX, 0);
                gte_set_ctrl(TRY, 0);
                gte_set_ctrl(TRZ, 0);
                m = (s32 *)scratch_top;
                sc->trans[0] = 0;
                sc->trans[1] = 0;
                sc->trans[2] = 0;
            }
            if (m != prev) {
                s32 r0, r1, r2;

                prev = m;
                m -= 10;
                r1 = m[0];
                r0 = m[1];
                r2 = m[2];
                sc->rot[0] = r1;
                sc->rot[1] = r0;
                sc->rot[2] = r2;
                gte_set_R012(r1, r0, r2, r1, r0, r2);
                r1 = m[3];
                r0 = ((DrawMatrix *)m)->m[2][2];
                sc->rot[3] = r1;
                sc->rot33 = r0;
                gte_set_R34(r1, r0, r1, r0);
                m += 5;
                r0 = m[0];
                r1 = m[1];
                r2 = m[2];
                gte_set_L012(r0, r1, r2, r0, r1, r2);
                r0 = m[3];
                r1 = m[4];
                gte_set_L34(r0, r1, r0, r1);
            }
        draw:
            wa->packet = (void *)model_groups_draw_scratch(wa->packet, prim, rec->arg, (next << 16) | (id & 0x7FFF));
            if (head < 0) {
                goto done;
            }
            p--;
            next = *p;
            if (next == 0) {
                goto done;
            }
            if (idx == next >> 16) {
                goto draw;
            }
            goto vertex;
        done:
            cur = p;
        } while (--count > 0);
    }
    scratch_top -= 0x58;
    gte_set_ctrl(H, 0x80);
}

/* hand-written: loop bound in $at, a value spilled to LO (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Transforms a model's vertex groups to screen space into buf (one 12-byte ScreenVert per vertex) and returns the
   nearest vertex z (0 if negative), or -1 when every vertex is off-screen (only when flags & 1 asks for the clip
   test). C companion of hand-written asm (not compiled): keeps the vertex base in LO (mtlo), the view size in HI
   (mthi, set by light_env_draw) and the vertex offset in the GTE's VXY2/VZ2, and software-pipelines RTPS (each
   result is stored one vertex late); written here without the pipelining. */
typedef struct ScreenVert {
    s16 x, y, z;      /* MAC1..MAC3 of the transform */
    u8 pad;
    u8 clip;          /* 1 below, 2 above, 4 right, 8 left of the view, 0x10 near (z < 0x21) */
    union {
        u32 sxy;      /* SXY2: screen x (low half), y (high half) */
        struct { s16 sxy_x, sxy_y; };
    };
} ScreenVert;

s32 vert_transform_groups(s32 count, s16 *groups, u8 *verts, ScreenVert *buf, s32 flags) {
    s32 min_z = 0x7FFF;
    s32 all_clip = -(flags & 1);   /* AND of every vertex's clip bits; stays 0 when not clip-testing */
    s16 *end = groups + count * 2;
    s32 hi;
    s32 off_xy, off_z;

    gte_get(VXY2, off_xy);
    gte_get(VZ2, off_z);
    off_xy &= 0xFFFEFFFF;
    mips_mfhi(hi);   /* view size: low half width, high half height */
    for (; groups != end; groups += 2) {
        /* groups[0] = first vertex, groups[1] = vertex count */
        s32 *v = (s32 *)(verts + groups[0] * 8);
        s32 *vend = (s32 *)((u8 *)v + groups[1] * 8);

        for (; v != vend; v += 2, buf++) {
            s32 xy = (v[0] + off_xy) & 0xFFFEFFFF;
            s32 z = ((s16 *)v)[2] + off_z;
            u32 sxy;
            s32 clip;

            gte_set(VXY0, xy);
            gte_set(VZ0, z);
            gte_rtps();
            gte_get(MAC1, buf->x);
            gte_get(MAC2, buf->y);
            gte_get(MAC3, buf->z);
            gte_get(SXY2, buf->sxy);
            buf->pad = 0;
            buf->clip = 0;
            if (flags == 0) {
                continue;
            }
            if (buf->z < min_z) {
                min_z = buf->z;
            }
            if (flags & 1) {
                sxy = buf->sxy;
                clip = (buf->z < 0x21) << 4;
                if ((hi >> 16) < (s32)(sxy >> 16)) {
                    clip |= ((sxy >> 16) >> 15) + 1;            /* y: 1 below, 2 above */
                }
                if ((u32)(hi & 0xFFFF) < (sxy & 0xFFFF)) {
                    clip |= (((sxy & 0xFFFF) >> 15) + 1) << 2;  /* x: 4 right, 8 left */
                }
                buf->clip = clip;
                all_clip &= clip;
            }
        }
    }
    if (min_z < 0) {
        min_z = 0;
    }
    if (all_clip != 0) {
        min_z = -1;
    }
    return min_z;
}
#else
INCLUDE_ASM("../src/stage/asm", vert_transform_groups);
#endif

/* GTE gouraud triangles/quads into the OT. Hand-written in the original: the OT link lives in $at. */
#ifdef NON_MATCHING
/* Builds textured, lit polygons from a model's face records (0x1C bytes each) into prim, links each into the
   ordering-table slot ot, and returns the new prim pointer. Faces whose vertices are all past the same screen edge
   (clip bits ANDed) or that face away (NCLIP <= 0) are skipped. The colour is NCDS of the face's normal (or DPCL of
   the vertex colour when record flag bit 0 is set); a fourth vertex index makes a quad. C companion of hand-written
   asm (not compiled): holds the OT link in $at through the loop (lwl/swl $at, sll $at) and the slot pointer in LO. */
typedef struct LitPrim {
    u32 tag;          /* OT link in the low 24 bits, length in the top byte (8 tri, 0xA quad) */
    u32 word4;        /* record word 1 */
    u32 rgb;          /* lit colour (RGB2); top byte = code 0x24/0x2C, +2 when semi-transparent */
    u32 sxy0;
    u16 uv0, tpage;   /* record word 3 low half; record word 0 low half (+ average z when not flagged) */
    u32 sxy1;
    u16 uv1, clut;    /* record word 3 high half; record word 0 high half & 0x7FFF */
    u32 sxy2;
    u16 uv2, pad;     /* record word 4 low half */
    u32 sxy3;         /* quad only */
    u16 uv3;          /* record word 4 high half */
} LitPrim;

u8 *prim_build_tris(s32 count, u8 *recs, u8 *buf, u8 *norms, u8 *prim, u32 *ot) {
    u8 *end = recs + count * 0x1C;
    u32 head = *ot;   /* the OT link, carried in $at */
    u32 rgbc;

    /* code byte 0x24 goes into the GTE's RGBC so NCDS/DPCL results come out as polygon colours */
    gte_get(RGB, rgbc);
    gte_set(RGB, (rgbc & 0xFFFFFF) | 0x24000000);
    for (; recs != end; recs += 0x1C) {
        s32 w2 = ((s32 *)recs)[2];
        s32 vi3 = w2 >> 24;                     /* fourth vertex index (0: triangle) */
        ScreenVert *v0 = (ScreenVert *)(buf + ((w2 & 0xFF) << 2));
        ScreenVert *v1 = (ScreenVert *)(buf + ((w2 >> 6) & 0x3FC));
        ScreenVert *v2 = (ScreenVert *)(buf + ((w2 >> 14) & 0x3FC));
        ScreenVert *v3 = 0;
        s32 outside = v0->clip & v1->clip & v2->clip;
        s32 w0, area, z_add, rec_flags;
        LitPrim *p;

        if (vi3 != 0) {
            v3 = (ScreenVert *)(buf + (vi3 << 2));
            outside &= v3->clip;
        }
        gte_load(SXY0, &v0->sxy, 0);
        gte_load(SXY2, &v2->sxy, 0);
        gte_load(SXY1, &v1->sxy, 0);
        if (outside != 0) {
            continue;
        }
        gte_nclip();
        gte_get(MAC0, area);
        if (area <= 0) {
            continue;                           /* back-facing */
        }
        w0 = ((s32 *)recs)[0];
        z_add = 0;
        if (((w0 >> 16) & 0x60) == 0) {         /* neither flag: add the average z to the tpage word */
            gte_get(SZ3, z_add);
            w0 += z_add;
            z_add = 0x840;                      /* far colour for the depth cue */
        }
        p = (LitPrim *)prim;
        p->tpage = w0;
        p->clut = (w0 >> 16) & 0x7FFF;
        gte_set_ctrl(RFC, z_add);
        gte_set_ctrl(GFC, z_add);
        gte_set_ctrl(BFC, z_add);
        rec_flags = ((s16 *)recs)[0x14 / 2];
        if (rec_flags & 1) {
            /* per-vertex colour: DPCL of the colour the GTE's IR holds (loaded from the pointer in VXY1) */
            gte_dpcl();
        } else {
            u32 c = *(u32 *)(norms + (rec_flags & 0x7FFC));

            gte_set_V0((c - (c & 0xFF00)) << 8, c & 0xFF00);
            gte_ncds();
        }
        p->word4 = ((u32 *)recs)[1];
        p->uv0 = ((u32 *)recs)[3];
        p->uv1 = ((u32 *)recs)[3] >> 16;
        p->uv2 = ((u32 *)recs)[4];
        p->tag = head >> 8;                     /* swl: link to the previous slot head */
        head = (u32)p << 8;
        gte_get(RGB2, p->rgb);
        gte_get(SXY0, p->sxy0);
        gte_get(SXY1, p->sxy1);
        gte_get(SXY2, p->sxy2);
        if (v3 != 0) {
            p->tag |= 0x0A000000;
            p->rgb = (p->rgb & 0xFFFFFF) | ((w0 < 0 ? 0x2E : 0x2C) << 24);
            p->sxy3 = v3->sxy;
            p->uv3 = ((u32 *)recs)[4] >> 16;
            prim += 0x2C;
        } else {
            p->tag |= 0x08000000;
            p->rgb = (p->rgb & 0xFFFFFF) | ((w0 < 0 ? 0x26 : 0x24) << 24);   /* bit 1: semi-transparent */
            prim += 0x24;
        }
    }
    *ot = head >> 8;                            /* swl $at, 2(ot) */
    return prim;
}
#else
INCLUDE_ASM("../src/stage/asm", prim_build_tris);
#endif

/* hand-written: branches into prim_subdiv_tri (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Like prim_build_tris but for faces near the camera (flag 0x10): builds lit, textured polygons from the 0x1C-byte face
   records, subdividing them (prim_subdiv_tri) when they cross the screen edge or are large, so the PS1's affine texture
   mapping and 1024-pixel limit don't distort them. Stops early when the primitive buffer is within 0x6000 bytes of
   its end (d_8011FFE4) and returns the new prim pointer. C companion of hand-written asm (not compiled): its loop
   is shared with prim_subdiv_tri (it jumps to .L490 for "next face" and falls into it with $ra set to the entry
   fn_800D1D6C by hand); the state below lives in registers $s0-$s7, $t9, $at, $gp (a private stack of 0x38-byte
   frames in the scratchpad) and $a1 across both functions. It also saves and restores the GTE rotation/translation
   it clobbers (OP needs the matrix diagonal). */
typedef struct SubdivCtx {
    ScreenVert *va, *vb, *vc;   /* $s0, $s2, $s1: the three corners of the piece being built */
    ScreenVert *quad_vert;      /* $s5: the fourth vertex while the first triangle is built, else 0 */
    s32 depth_size;             /* $s3: low half = subdivision depth left, then size limits in bytes 2 and 3 */
    u32 clip_or;                /* $s6: OR of the corners' clip bits (0: all inside) */
    u32 colour_word;            /* $s4: record word 0 + average z (tpage/clut) */
    s32 rec_flags;              /* $s7: record flags (sign: per-vertex colour) */
    u8 *prim;                   /* $t9 */
    u8 *rec;                    /* $a1 */
    u32 ot_link;                /* $at */
} SubdivCtx;

void prim_subdiv_tri(SubdivCtx *c);

/* POLY_FT3/GT3 head as the asm writes it (a PsyQ-style primitive) */
typedef struct FlatTri {
    u32 tag;
    u32 rgb;          /* RGB2 with the code in the top byte */
    u32 sxy0;
    u16 uv0, clut;
    u32 sxy1;
    u16 uv1, tpage;
    u32 sxy2;
    u16 uv2, pad;
} FlatTri;
s32 facing_triple_product(ScreenVert *a, ScreenVert *b, ScreenVert *c);   /* (b x a) . c of the 3D vertices (x, y, z) */
s32 gte_average_z(void);                                                   /* SZ3 of the last NCLIP'd face */
void subdivide_edges_and_recurse(SubdivCtx *c);                            /* inline in the asm */

u8 *prim_build_tris_subdiv(s32 count, u8 *recs, u8 *buf, u8 *norms, u8 *prim, u32 *ot) {
    SubdivCtx c;
    u8 *end = recs + count * 0x1C;
    u32 rgbc;

    c.prim = prim;
    c.ot_link = *ot;
    gte_set_ctrl(RFC, 0x840);
    gte_set_ctrl(GFC, 0x840);
    gte_set_ctrl(BFC, 0x840);
    gte_get(RGB, rgbc);
    gte_set(RGB, (rgbc & 0xFFFFFF) | 0x24000000);
    for (c.rec = recs; c.rec != end; c.rec += 0x1C) {
        s32 w2 = ((s32 *)c.rec)[2];
        s32 vi3 = w2 >> 24;
        u32 and_clip;
        s32 area;

        c.va = (ScreenVert *)(buf + ((w2 & 0xFF) << 2));
        c.vc = (ScreenVert *)(buf + ((w2 >> 6) & 0x3FC));
        c.vb = (ScreenVert *)(buf + ((w2 >> 14) & 0x3FC));
        c.quad_vert = 0;
        c.clip_or = c.va->clip | c.vc->clip | c.vb->clip;
        and_clip = c.va->clip & c.vc->clip & c.vb->clip;
        if (vi3 != 0) {
            c.quad_vert = (ScreenVert *)(buf + (vi3 << 2));
            and_clip &= c.quad_vert->clip;
            c.clip_or |= c.quad_vert->clip;
        }
        if (and_clip == 0) {
            c.clip_or &= 0x1F;
            if (c.clip_or != 0) {
                /* partly off-screen: the screen coordinates are unusable, so the facing comes from the
                   triple product (vc x va) . vb of the 3D corners (OP, then MVMVA, after scaling the
                   vectors down by LZCS so they fit 16 bits), skipped when >= 0 */
                area = -facing_triple_product(c.va, c.vc, c.vb);
            } else {
                gte_load(SXY0, &c.va->sxy, 0);
                gte_load(SXY2, &c.vb->sxy, 0);
                gte_load(SXY1, &c.vc->sxy, 0);
                gte_nclip();
                gte_get(MAC0, area);
            }
            if (area > 0) {
                c.rec_flags = ((s16 *)c.rec)[0x14 / 2];
                /* colour: DPCL of the vertex colours (flag bit 0) or NCDS of the normal in norms, giving
                   RGB2 for a flat triangle, or three vertex colours (rec_flags < 0, from the colour words at
                   rec + 0x16 / 0x18 / 0x1A) for Gouraud; colour_word = record word 0 + the lit-colour z. */
                c.colour_word = ((u32 *)c.rec)[0] + gte_average_z();
                /* depth 3, with x/y size limits derived from LZCR of the face size (shifted into bytes 2, 3) */
                c.depth_size = 3;
                prim_subdiv_tri(&c);
                if (c.quad_vert != 0) {
                    /* second half of a quad: the same, with corners (vc, vb, quad_vert), entered through
                       fn_800D1D6C: the asm resets $ra by hand and jumps to prim_subdiv_tri */
                    c.va = c.vc;
                    c.vc = c.vb;
                    c.vb = c.quad_vert;
                    c.quad_vert = 0;
                    prim_subdiv_tri(&c);
                }
            }
        }
        if (d_8011FFE4 - (s32)c.prim < 0x6000) {
            break;                              /* output buffer nearly full */
        }
    }
    *ot = c.ot_link >> 8;                       /* swl $at, 2(ot) */
    return c.prim;
}
#else
INCLUDE_ASM("../src/stage/asm", prim_build_tris_subdiv);
#endif

/* hand-written: subroutine branching back into prim_build_tris_subdiv (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Emits or splits one lit triangle (corners va, vb, vc in c). If the corners are all past one edge (clip_or set)
   it returns without output. If the subdivision depth is used up, or every edge is within the size limits in x
   and y, it writes the primitive (a flat-lit 7-word triangle, or a Gouraud 9-word one when rec_flags < 0) and
   advances c->prim. Otherwise it builds the three edge midpoints (screen x/y, colour and uv averaged, RTPS on the
   midpoint when clipping), and calls itself on the three corner triangles and the middle one with depth - 1.
   C companion of hand-written asm (not compiled): a subroutine with its own calling convention (state in
   $s0-$s7/$t9/$at, the recursion frames on a private stack in $gp), entered from prim_build_tris_subdiv both by a call and by
   a jump back from fn_800D1D6C with $ra set by hand. */
void prim_subdiv_tri(SubdivCtx *c) {
    s32 limit_x = (c->depth_size >> 16) & 0xFF;
    s32 limit_y = c->depth_size >> 24;
    s32 small;
    FlatTri *ft;

    if ((c->depth_size & 0xFFFF) > 0) {
        if (c->clip_or != 0 && (c->va->clip & c->vb->clip & c->vc->clip) != 0) {
            return;
        }
        /* all three edges within the size limits in x (halfwords at +8) and y (+0xA): emit as is */
        small = abs(c->va->sxy_x - c->vb->sxy_x) <= limit_x && abs(c->vb->sxy_x - c->vc->sxy_x) <= limit_x &&
                abs(c->va->sxy_x - c->vc->sxy_x) <= limit_x && abs(c->va->sxy_y - c->vb->sxy_y) <= limit_y &&
                abs(c->vb->sxy_y - c->vc->sxy_y) <= limit_y && abs(c->va->sxy_y - c->vc->sxy_y) <= limit_y;
        if (!small) {
            /* Split: the edge midpoints go on the $gp stack (position, colour and uv averaged, and an RTPS
               of the midpoint with its clip bits recomputed when clip_or is set); then the three corner
               triangles and the middle one are drawn with depth_size - 1 by calling this function on the
               corners in turn (the asm sets $s0..$s2 for each from the stack frame and jals). */
            c->depth_size--;
            subdivide_edges_and_recurse(c);
            c->depth_size++;
            return;
        }
    }
    ft = (FlatTri *)c->prim;
    ft->sxy0 = c->va->sxy;
    ft->uv0 = *(u16 *)&c->va->x;              /* the frame's copies keep u, v in the x, y halves */
    ft->clut = c->colour_word;
    ft->tag = c->ot_link >> 8;                  /* swl $at, 2(prim) */
    c->ot_link = (u32)c->prim << 8;             /* sll $at, $t9, 8 */
    ft->sxy1 = c->vb->sxy;
    ft->uv1 = *(u16 *)&c->vb->x;
    ft->sxy2 = c->vc->sxy;
    ft->uv2 = *(u16 *)&c->vc->x;
    if (c->rec_flags >= 0) {
        ft->tag |= 7 << 24;                     /* POLY_FT3: flat colour in RGB2 */
        gte_get(RGB2, ft->rgb);
        ft->tpage = (c->colour_word >> 16) & 0x7FFF;
        if ((s32)c->colour_word < 0) {
            ft->rgb = (ft->rgb & 0xFFFFFF) | (0x26 << 24);   /* semi-transparent */
        }
        c->prim += 0x20;
    } else {
        ft->tag |= 9 << 24;                     /* POLY_GT3: a colour per corner */
        ft->rgb = ((c->colour_word < 0x80000000u) ? 0x34 : 0x36) << 24;
        /* the three corner colours from the frame's copies (+0x4 each) are stored with the uv words */
        c->prim += 0x28;
    }
}
#else
INCLUDE_ASM("../src/stage/asm", prim_subdiv_tri);
#endif

void texel_row_scale(u16 *src, s16 *dst, s32 count, s32 scale) {
    s32 texel, b, g, r;

    while (count > 0) {
        texel = *src;
        b = texel & 0x1F;
        g = (texel >> 5) & 0x1F;
        r = (texel >> 10) & 0x1F;
        texel &= 0x8000;
        b = b * scale / 4096;
        g = g * scale / 4096;
        r = r * scale / 4096;
        *dst = texel | (r << 10) | (g << 5) | b;
        count--;
        src++;
        dst++;
    }
}

/* Uploads two images to the frame buffer: 4x32 words from vram_image_a at (0x60, 0x140), then a 32x1 row
 * converted by texel_row_scale from vram_image_b at (0x60, 0x160). */
void vram_load_images(void) {
    Rect rect;
    Rect *r = &rect;

    r->x = 0x60;
    r->y = 0x140;
    r->w = 4;
    r->h = 0x20;
    svc_load_image(r, vram_image_a);
    svc_draw_sync(0);
    r->y = 0x160;
    r->x = 0x60;
    r->w = 0x20;
    r->h = 1;
    texel_row_scale(vram_image_b, arena_top(), 0x20, 0x380);
    svc_load_image(r, arena_top());
    svc_draw_sync(0);
}

void ring32_reset(void) {
    ring32_index = 0;
}

void ring32_step(void) {
    ring32_index = (ring32_index - 1) & 0x1F;
}

void packet_free_list_reset(void) {
    packet_free_list = 0;
}

/* Copies each polygon of the primitive list prim..end (3 or 4 vertices; word 1,
 * or word 2 when word 1 has 0x80, holds the flags) into a black flat F3/F4 at
 * out, links it into ot, and writes the screen bounding box {x, y, w, h} to
 * bounds. Returns the next free byte after the new primitives. */
void *prim_flat_black_build(PrimWord *prim, PrimWord *end, u8 *ot, PolyFlat *out, s16 *bounds) {
    s32 minx, maxx, miny, maxy;
    s16 *src, *dst;
    s32 n, stride;

    if (prim == end) {
        return out;
    }
    miny = 0x7FFF;
    minx = 0x7FFF;
    maxy = -0x8000;
    maxx = -0x8000;
    do {
        s32 flags = prim[1].hi;
        src = (s16 *)&prim[2];
        n = prim[0].hi;
        if (n >= 3) {
            if (flags & 0x80) {
                flags = prim[2].hi;
                src = (s16 *)&prim[3];
            }
            n = 4;
            if (flags & 8) {
                out->len = 5;
                out->code = 0x28;
            } else {
                n = 3;
                out->len = 4;
                out->code = 0x20;
            }
            dst = out->xy[0];
            stride = 8;
            out->r = 0;
            out->g = 0;
            out->b = 0;
            if (flags & 0x10) {
                stride = 0xC;
            }
            while (n > 0) {
                s32 x = src[0];
                s32 y = src[1];
                s32 v;
                v = x;
                if (minx < x) {
                    v = minx;
                }
                minx = v;
                v = x;
                if (x < maxx) {
                    v = maxx;
                }
                maxx = v;
                v = y;
                if (miny < y) {
                    v = miny;
                }
                miny = v;
                v = y;
                if (y < maxy) {
                    v = maxy;
                }
                maxy = v;
                n--;
                src = (s16 *)((u8 *)src + stride);
                dst[0] = x;
                dst[1] = y;
                dst += 2;
            }
            addPrim(ot, out);
            out = (PolyFlat *)dst;
        }
        {
            /* next primitive: the 24-bit tag link, read unaligned */
            u32 link;
            ot_link_load(link, prim);
            prim = (PrimWord *)((link >> 8) | 0x80000000);
        }
    } while (prim != end);
    bounds[0] = minx;
    bounds[1] = miny;
    bounds[2] = maxx - minx + 1;
    bounds[3] = maxy - miny + 1;
    return out;
}

/* Draws rect as a fade-in curtain: a solid textured quad down to the alpha-scaled edge (alpha 0..128), a
 * gradient quad fading to black over the next third of the height, then a texture-window reset. Returns the
 * next free primitive. */
void *prim_fade_curtain(void *ot, void *prim, Rect *rect, s32 alpha)
{
    PolyFT4 *ft4;
    PolyGT4 *gt4;
    DrTwin *twin;
    s32 fade;
    s32 top;
    s32 scaled;
    u16 tpage;

    alpha &= 0xFF;
    alpha = MAX(MIN(alpha, 128), 0);
    if (alpha == 0) {
        return prim;
    }
    fade = (s16)(rect->h / 3);
    scaled = (rect->h + fade) * alpha;
    tpage = (2 << 7) | (1 << 5) | ((mask_buf_rect.y >> 4) & 0x10) | ((mask_buf_rect.x & 0x3FF) >> 6) | ((mask_buf_rect.y & 0x200) << 2);
    top = scaled / 128 - fade;
    if (top >= 0) {
        ft4 = prim;
        prim = ft4 + 1;
        ft4->len = 9;
        ft4->code = 0x2E;
        ft4->tpage = tpage;
        ft4->b0 = 0x80;
        ft4->g0 = 0x80;
        ft4->r0 = 0x80;
        ft4->x0 = rect->x;
        ft4->y0 = rect->y;
        ft4->x1 = rect->x + rect->w;
        ft4->y1 = rect->y;
        ft4->x2 = rect->x;
        ft4->y2 = rect->y + top;
        ft4->x3 = rect->x + rect->w;
        ft4->y3 = rect->y + top;
        ft4->u0 = 0;
        ft4->v0 = 0;
        ft4->u1 = rect->w;
        ft4->v1 = 0;
        ft4->u2 = 0;
        ft4->v2 = top;
        ft4->u3 = rect->w;
        ft4->v3 = top;
        addPrim(ot, ft4);
        if (alpha == 128) {
            goto twin;
        }
    }
    fade += top;
    if (top < 0) {
        top = 0;
    }
    if (rect->h < fade) {
        fade = rect->h;
    }
    gt4 = prim;
    prim = gt4 + 1;
    gt4->len = 0xC;
    gt4->code = 0x3E;
    gt4->b1 = 0x80;
    gt4->g1 = 0x80;
    gt4->r1 = 0x80;
    gt4->b0 = 0x80;
    gt4->g0 = 0x80;
    gt4->r0 = 0x80;
    gt4->b3 = 0;
    gt4->g3 = 0;
    gt4->r3 = 0;
    gt4->b2 = 0;
    gt4->g2 = 0;
    gt4->r2 = 0;
    gt4->tpage = tpage;
    gt4->x0 = rect->x;
    gt4->y0 = rect->y + top;
    gt4->x1 = rect->x + rect->w;
    gt4->y1 = rect->y + top;
    gt4->x2 = rect->x;
    fade -= top;
    gt4->y2 = rect->y + top + fade;
    gt4->x3 = rect->x + rect->w;
    gt4->y3 = rect->y + top + fade;
    gt4->u0 = 0;
    gt4->v0 = top;
    gt4->u1 = rect->w;
    gt4->v1 = top;
    gt4->u2 = 0;
    gt4->v2 = top + fade;
    gt4->u3 = rect->w;
    gt4->v3 = top + fade;
    addPrim(ot, gt4);
twin:
    twin = prim;
    prim = twin + 1;
    twin->len = 2;
    twin->code[0] = 0xE2000000;
    twin->code[1] = 0;
    addPrim(ot, twin);
    return prim;
}

/* Draws a full-rect fade quad (POLY_GT4 shaded by 0x80 minus the shade byte of shade_word) between
 * mask-bit and texture-window mode packets; returns the next free primitive byte. */
void *prim_fade_quad_shade(u32 *ot, u8 *prim, FadeRect *rect, s32 shade_word)
{
    s32 shade;
    s32 level;
    PrimGp0Cmd *mask_off;
    PrimGp0Cmd *tex_window;
    PrimGp0Cmd *mask_on;
    FadeQuad *poly;
    s32 clamped;
    s32 tex_v;

    shade = (shade_word >> 8) & 0xFF;
    level = shade;
    if (shade > 0x80) {
        level = 0x80;
    }
    clamped = shade;
    if (shade > 0x80) {
        clamped = 0x80;
    }
    if (clamped < 0) {
        level = 0;
    }
    shade = 0x80 - level;
    if (shade != 0) {
        mask_off = (PrimGp0Cmd *)prim;
        prim += sizeof(PrimGp0Cmd);
        mask_off->len = 2;
        mask_off->code = 0xE6000000;
        mask_off->pad = 0;
        addPrim(ot, mask_off);

        poly = (FadeQuad *)prim;
        prim += sizeof(FadeQuad);
        tex_v = ring32_index;
        poly->len = 0xC;
        poly->code = 0x3E;
        poly->tpage = 0xB1;
        poly->clut = 0x5806;
        poly->r0 = poly->g0 = poly->b0 = shade;
        poly->r1 = poly->g1 = poly->b1 = shade;
        poly->r2 = poly->g2 = poly->b2 = shade;
        poly->r3 = poly->g3 = poly->b3 = shade;
        poly->x0 = rect->x;
        poly->y0 = rect->y;
        poly->x1 = rect->x + rect->w;
        poly->y1 = rect->y;
        poly->x2 = rect->x;
        poly->y2 = rect->y + rect->h;
        poly->x3 = rect->x + rect->w;
        poly->y3 = rect->y + rect->h;
        poly->u0 = 0;
        poly->v0 = tex_v;
        poly->u1 = rect->w;
        poly->v1 = tex_v;
        poly->u2 = 0;
        poly->v2 = tex_v + (u8)rect->h;
        poly->u3 = rect->w;
        poly->v3 = tex_v + (u8)rect->h;
        addPrim(ot, poly);

        tex_window = (PrimGp0Cmd *)prim;
        prim += sizeof(PrimGp0Cmd);
        tex_window->len = 2;
        tex_window->code = 0xE204239F;
        tex_window->pad = 0;
        addPrim(ot, tex_window);

        mask_on = (PrimGp0Cmd *)prim;
        prim += sizeof(PrimGp0Cmd);
        mask_on->len = 2;
        mask_on->code = 0xE6000002;
        mask_on->pad = 0;
        addPrim(ot, mask_on);
    }
    return prim;
}

u8 *fade_rect_prims(u32 *ot, u8 *prim, Rect *rect, s32 alpha) {
    PrimGp0Cmd *mask_off;
    PrimGp0Cmd *mask_on;
    PrimGp0Cmd *tex_window;
    PolyFT4 *ft4;
    PolyGT4 *gt4;
    s32 fade;
    s32 top;
    s32 scaled;
    s32 v_top;
    s32 v_mid;
    u8 v_bottom;
    u16 tpage;

    alpha &= 0xFF;
    alpha = MAX(MIN(alpha, 128), 0);
    if (alpha == 128) {
        return prim;
    }
    mask_off = (PrimGp0Cmd *)prim;
    prim += sizeof(PrimGp0Cmd);
    mask_off->len = 2;
    mask_off->code = 0xE6000000;
    mask_off->pad = 0;
    addPrim(ot, mask_off);

    fade = (s16)(rect->h / 3);
    scaled = (rect->h + fade) * alpha;
    tpage = (2 << 7) | (1 << 5) | ((mask_buf_rect.y >> 4) & 0x10) | ((mask_buf_rect.x & 0x3FF) >> 6) | ((mask_buf_rect.y & 0x200) << 2);
    top = scaled / 128;
    top -= fade;
    fade += top;
    if (top < 0) {
        top = 0;
    }
    do { /* setUV4: refs in the block count double for register priority */
            if (rect->h < fade) {
                fade = rect->h;
            }
            v_top = rect->h / 16;
            v_mid = rect->h * 15 / 16 - (rect->h * 14 / 16 * (rect->h - fade)) / (rect->h - top);
    } while (0);
    if (rect->h != fade) {
        ft4 = (PolyFT4 *)prim;
        prim += sizeof(PolyFT4);
        ft4->len = 9;
        ft4->code = 0x2E;
        ft4->b0 = 0x80;
        ft4->g0 = 0x80;
        ft4->r0 = 0x80;
        ft4->tpage = tpage;
        ft4->x0 = rect->x;
        ft4->y0 = rect->y + fade;
        ft4->x1 = rect->x + rect->w;
        ft4->y1 = rect->y + fade;
        ft4->x2 = rect->x;
        ft4->y2 = rect->y + rect->h;
        ft4->x3 = rect->x + rect->w;
        ft4->y3 = rect->y + rect->h;
        do { /* setUV4: refs in the block count double for register priority */
            ft4->u0 = rect->w / 16;
            ft4->v0 = v_mid;
            ft4->u1 = rect->w / 16 + rect->w * 14 / 16;
            ft4->v1 = v_mid;
            ft4->u2 = rect->w / 16;
            ft4->v2 = rect->h * 15 / 16;
            ft4->u3 = rect->w / 16 + rect->w * 14 / 16;
            ft4->v3 = rect->h * 15 / 16;
        } while (0);
        addPrim(ot, ft4);
        if (alpha == 0) {
            goto tail;
        }
    }
    gt4 = (PolyGT4 *)prim;
    prim += sizeof(PolyGT4);
    gt4->len = 0xC;
    gt4->code = 0x3E;
    gt4->b1 = 0;
    gt4->g1 = 0;
    gt4->r1 = 0;
    gt4->b0 = 0;
    gt4->g0 = 0;
    gt4->r0 = 0;
    gt4->b3 = 0x80;
    gt4->g3 = 0x80;
    gt4->r3 = 0x80;
    gt4->b2 = 0x80;
    gt4->g2 = 0x80;
    gt4->r2 = 0x80;
    gt4->tpage = tpage;
    gt4->x0 = rect->x;
    gt4->y0 = rect->y + top;
    gt4->x1 = rect->x + rect->w;
    gt4->y1 = rect->y + top;
    gt4->x2 = rect->x;
    gt4->y2 = rect->y + fade;
    gt4->x3 = rect->x + rect->w;
    gt4->y3 = rect->y + fade;
    do { /* setUV4: refs in the block count double for register priority */
        gt4->u0 = rect->w / 16;
        gt4->v0 = v_top;
        gt4->u1 = rect->w / 16 + rect->w * 14 / 16;
        gt4->v1 = v_top;
        gt4->u2 = rect->w / 16;
        v_bottom = v_mid;
        gt4->v2 = v_bottom;
        gt4->u3 = rect->w / 16 + rect->w * 14 / 16;
        gt4->v3 = v_bottom;
    } while (0);
    addPrim(ot, gt4);
tail:
    mask_on = (PrimGp0Cmd *)prim;
    prim += sizeof(PrimGp0Cmd);
    mask_on->len = 2;
    mask_on->code = 0xE6000002;
    mask_on->pad = 0;
    addPrim(ot, mask_on);
    tex_window = (PrimGp0Cmd *)prim;
    prim += sizeof(PrimGp0Cmd);
    tex_window->len = 2;
    tex_window->code = 0xE2000000;
    tex_window->pad = 0;
    addPrim(ot, tex_window);
    return prim;
}

/* For each layer of packet_free_list with primitives: builds a 3-entry OT, gets the layer's bounds from
 * prim_flat_black_build, clips them to the current view and, if anything is left, copies that part of the
 * screen to the mask buffer (the RECT at mask_buf_rect), blacks it out, draws the layer into the buffer with
 * the three fade passes and restores the view's draw area; the sub-OT is spliced in front of the layer. */
void mask_layers_draw(void)
{
    MaskLayer *layer;
    WorkArea *work;
    u32 cmd_e4, cmd_e5;
    s32 buf_x, buf_y;
    s32 packed_x, packed_y; /* FAKE: dead after combine, each keeps an 8-byte spill slot (the original's 0x78 frame) */
    s32 buf_ofs_y, buf_ofs_x;
    s32 dst_x;
    register s32 dst_y asm("$23"); /* FAKE: the original's global-alloc order (s6 dst_x, s7 dst_y, fp buf_x) */
    Rect rect;
    Rect *bounds;

    layer = (MaskLayer *)packet_free_list;
    work = work_area_ptr;
    if (layer == NULL) {
        return;
    }
    cmd_e4 = 0;
    cmd_e5 = 0;
    bounds = &rect;
    buf_x = (s16)mask_buf_rect.x;
    buf_y = (s16)mask_buf_rect.y;
    dst_y = (u16)buf_y;
    dst_x = (s16)buf_x;
    /* The high halves vanish under the 0x7FF masks; combine deletes packed_x/packed_y but reload still gives
     * each a stack slot, numbered between buf_y's and buf_ofs_y's (FINDINGS: "Stack frame from s16 temporaries"). */
    packed_x = dst_x << 16;
    packed_y = dst_y << 16;
    buf_ofs_y = ((packed_y | dst_y) & 0x7FF) << 11;
    buf_ofs_x = (packed_x | dst_x) & 0x7FF;

    do {
        u32 link;
        PrimWord *first;
        u32 *ot;
        u32 *saved;
        u32 *p;
        u32 *end;
        u32 next;

        ot_link_load(link, layer);
        first = (PrimWord *)((link >> 8) | 0x80000000);
        if (first != (PrimWord *)&layer->end) {
            ViewTail *clip_view;
            ViewTail *src_view;
            ViewTail *env_view;
            PrimGp0Cmd *mask;
            PrimVramCopy *copy;
            PrimBgRect *fill;
            PrimDrawAreas *areas;
            PrimDrawAreas *env;
            register u32 ofs_word asm("$4"); /* FAKE: local-alloc gives the original's a0/v1 the other way round */
            s32 lo, hi, lim_w, lim_h;
            s32 visible;
            Rect *r;
            u32 term;

            ot = work->packet;
            saved = ot;
            work->packet = ot + 3;
            term = 0xFFFFFF;
            p = ot;
            end = ot + 2;
            next = (u32)(ot + 1) & term;
            do {
                *p++ = next;
                next += 4;
            } while (end != p);
            *p = term;
            work->packet = prim_flat_black_build(first, (PrimWord *)&layer->end, (u8 *)ot, work->packet,
                                                 (s16 *)bounds);
            r = bounds;

            lo = rect.x;
            hi = lo + rect.w;
            clip_view = &view_tails[cur_view_index];
            lim_w = clip_view->vram_w;
            lim_h = clip_view->vram_h;
            lo = MAX(CLAMP_HI(lo, lim_w), 0);
            hi = MAX(CLAMP_HI(hi, lim_w), 0);
            rect.x = lo;
            rect.w = hi - lo;
            lo = rect.y;
            hi = lo + rect.h;
            lo = MAX(CLAMP_HI(lo, lim_h), 0);
            hi = MAX(CLAMP_HI(hi, lim_h), 0);
            r->y = lo;
            r->h = hi - lo;
            visible = r->w > 0 && r->h > 0;
            if (!visible) {
                work->packet = saved;
            } else {
                mask = work->packet;
                work->packet = mask + 1;
                mask->len = 2;
                mask->code = 0xE6000000;
                mask->pad = 0;
                addPrim(ot, mask);

                copy = work->packet;
                work->packet = copy + 1;
                copy->len = 5;
                copy->flush = 1;
                copy->cmd = 0x80000000;
                src_view = &view_tails[cur_view_index];
                copy->src_x = src_view->vram_x + (work->draw_x + rect.x);
                copy->src_y = src_view->vram_y + (work->draw_y + rect.y);
                copy->dst_x = dst_x;
                copy->dst_y = dst_y;
                copy->w = rect.w;
                copy->h = rect.h;
                addPrim(ot, copy);

                fill = work->packet;
                work->packet = fill + 1;
                fill->len = 3;
                fill->code = 0x60;
                fill->r = 0;
                fill->g = 0;
                fill->b = 0;
                fill->x = rect.x;
                fill->y = rect.y;
                fill->w = rect.w;
                fill->h = rect.h;
                addPrim(layer, fill);

                /* Draw area = the buffer at the clipped size, offset so the layer lands at the buffer. */
                cmd_e5 = 0xE5000000;
                cmd_e4 = 0xE4000000;
                areas = work->packet;
                work->packet = areas + 1;
                areas->len = 3;
                areas->e3 = (((dst_y & 0x3FF) << 10) | (dst_x & 0x3FF)) | 0xE3000000;
                areas->e4 = ((((buf_y + rect.h - 1) & 0x3FF) << 10) | ((buf_x + rect.w - 1) & 0x3FF)) | cmd_e4;
                ofs_word = buf_ofs_y | (buf_ofs_x | cmd_e5);
                areas->e5 = ofs_word;
                areas->e5 = (((buf_y - rect.y) & 0x7FF) << 11) | (((buf_x - rect.x) & 0x7FF) | cmd_e5);
                addPrim(layer, areas);

                work->packet = fade_rect_prims(ot + 1, work->packet, &rect, layer->fade);
                work->packet = prim_fade_quad_shade(ot + 1, work->packet, (FadeRect *)&rect, layer->fade);
                env = prim_fade_curtain(&layer->end, work->packet, &rect, layer->fade);

                /* Restore the view's draw area and offset. */
                work->packet = env + 1;
                env->len = 3;
                env_view = &view_tails[cur_view_index];
                env->e3 = ((((work->draw_y + env_view->vram_y) & 0x3FF) << 10)
                           | ((work->draw_x + env_view->vram_x) & 0x3FF)) | 0xE3000000;
                env->e4 = ((((work->draw_y + env_view->vram_y + env_view->vram_h - 1) & 0x3FF) << 10)
                           | ((work->draw_x + env_view->vram_x + env_view->vram_w - 1) & 0x3FF)) | cmd_e4;
                env->e5 = (((work->draw_y + env_view->vram_y) & 0x7FF) << 11)
                          | (((work->draw_x + env_view->vram_x) & 0x7FF) | cmd_e5);
                addPrim(&layer->end, env);
                addPrims(layer, ot, ot + 2);
            }
        }
        layer = layer->next;
    } while (layer != NULL);
}

/* Resets the 24 SceneModel entries (their first word), the 512 PointSlot entries, and the three counters. */
void rec_tables_reset(void) {
    s32 off;
    s32 i;
    PointSlot *rec;

    for (off = 0x2E0; off >= 0; off -= 0x20) {
        *(s32 *)((u8 *)scene_models + off) = 0;
    }
    scene_model_count = 0;
    point_base = 0;
    point_search_radius = 0x2000;
    rec = point_slots;
    for (i = 0; i < 0x200; i++, rec++) {
        rec->flags = i;
        rec->unk_0C = 0;
        rec->unk_08 = 0;
        rec->unk_0A = 0;
        rec->z = 0;
        rec->y = 0;
        rec->x = 0;
        rec->colour = 0;
        *(u16 *)rec->unk_0E = 0;
    }
}

/* Set the position of entry `index` and mark it (flag 0x8000). */
void rec_set_pos(s32 index, s32 x, s32 y, s32 z) {
    PointSlot *rec = &point_slots[index];

    rec->x = x;
    rec->y = y;
    rec->z = z;
    rec->flags |= 0x8000;
}

void point_set_extra(s32 index, s32 a, s32 b, s32 c) {
    PointSlot *rec = &point_slots[index];

    rec->unk_0A = a;
    rec->unk_08 = b;
    rec->unk_0C = c;
    rec->flags |= 0x8000;
}

/* Sets the colour of entry `index` (components scaled down by 32; never black) and marks it (flag 0x8000). */
void rec_set_rgb(s32 index, s32 r, s32 g, s32 b) {
    PointSlot *rec = &point_slots[index];
    s32 blue = b >> 5;
    s32 red = r >> 5;
    s32 green = g >> 5;

    if ((red | green | blue) == 0) {
        blue = 1;
    }
    rec->colour = (blue << 16) | (green << 8) | red;
    rec->flags |= 0x8000;
}

/* Sets the low 15 bits of the flags of record `index` to `value`, keeping the mark (flag 0x8000). */
void rec_set_flags(s32 index, s32 value) {
    s32 mark = *(s16 *)&point_slots[index].flags & 0x8000;

    point_slots[index].flags = (value & 0x7FFF) | mark;
}

s32 rec_get_flags(s32 index) {
    return point_slots[index].flags & 0x7FF;
}

/* Bits 12-13 of the flags of record `index`. */
s32 fn_800D33A4(s32 index) {
    s32 flags = *(s16 *)&point_slots[index].flags;

    return flags & 0x3000;
}

void point_set_base(s32 value) {
    point_base = value;
}

/* Sets point_search_radius (clamped to 0..0x7FFF), point_search_below and point_search_above. */
void point_search_set(s32 value, s32 b, s32 c) {
    value = MAX(MIN(value, 0x7FFF), 0);
    point_search_radius = value;
    point_search_below = b;
    point_search_above = c;
}

/* Swaps the bytes of every halfword of a block: a count, then count * 8 halfwords. */
u16 *block_byteswap16(u16 *block) {
    s16 *p;
    s32 count;
    u16 head = *block;

    count = ((head & 0xFF) << 8) | (head >> 8);
    *block = count;
    count *= 8;
    p = (s16 *)block + 1;
    if (count > 0) {
        do {
            s32 v = *p;
            count -= 1;
            *p = ((v & 0xFF) << 8) | ((v & 0xFF00) >> 8);
            p++;
        } while (count > 0);
    }
    return block;
}

/* Converts a big-endian list of records (count, then 16 bytes each) to 8 bytes each (words 0, 1, 2, 5)
 * after the count at dst. Returns the size of the result in bytes. */
s32 records_be_to_le(u16 *src, s32 *dst) {
    Half8 *in = (Half8 *)(src + 1);
    Half4 *out = (Half4 *)(dst + 1);
    s32 count = ((*src & 0xFF) << 8) | (*src >> 8);
    s32 size = count * 8 + 4;

    *dst = count;
    while (count > 0) {
        s32 a, b, c, d;

        count--;
        b = in->w[1];
        c = in->w[2];
        d = in->w[5];
        a = in->w[0];
        out->w[0] = SWAP16S(a);
        out->w[1] = SWAP16S(b);
        out->w[2] = SWAP16S(c);
        out->w[3] = SWAP16S(d);
        in++;
        out++;
    }
    return size;
}

static inline s32 rec_key(SortRecord *r) {
    return (r->x + 0x8000) >> 9;
}
static inline s32 rec_gt(SortRecord *a, SortRecord *b) {
    s32 ka = a->flags & 0x4000;
    s32 kb = b->flags & 0x4000;
    s32 ga, gb, za, zb;
    if (kb < ka) return 1;
    if (ka < kb) return 0;
    ga = rec_key(a);
    gb = rec_key(b);
    if (gb < ga) return 1;
    if (ga < gb) return 0;
    za = a->z;
    zb = b->z;
    if (zb < za) return 1;
    return !(za < zb);
}
static inline s32 count_run(SortRecord *p, s32 left, s32 key) {
    s32 cnt = 0;
    while (!(p->flags & 0x4000)) {
        if (left <= 0 || rec_key(p) != key) break;
        cnt++;
        p++;
        left--;
    }
    return cnt;
}
void *sort_records_by_band(void *list, s16 *marks) {
    SortInput *input;
    u16 *remap = (u16 *)heap_get_top();
    SortResult *res;
    SortRecord *recs;
    s32 n, i, j, k;
    SortRecord *tmp;
    s32 next;

    for (i = 0x1FF; i >= 0; i--) {
        remap[i] = i;
    }
    if (marks) {
        while ((i = *marks++) != 0) {
            remap[i] = i | 0x4000;
        }
    }
    i = 0;
    input = list;
    n = input->count;
    recs = input->recs;
    for (; i < n; i++) {
        recs[i].flags = remap[(s16)recs[i].flags];
    }

    tmp = scratch_alloc(8);
    for (k = 1; k <= n / 9; k = k * 3 + 1)
        ;
    /* Shell sort, gap sequence 1, 4, 13, ...; next gap = hi(k * 0x55555556) = k / 3 */
    for (; k > 0; k = next) {
        div3_hi(next, k);
        for (i = k; i < n; i++) {
            *tmp = recs[i];
            for (j = i - k; j >= 0; j -= k) {
                if (rec_gt(tmp, &recs[j])) break;
                recs[j + k] = recs[j];
            }
            recs[j + k] = *tmp;
        }
    }
    scratch_top -= 8;

    res = (SortResult *)heap_get_top();
    res->input = input;
    res->num_groups = 0;
    res->first_key = 0;
    i = 0;
    if (!(recs[0].flags & 0x4000) && i < n) {
        s32 groups = 0;
        s32 next = rec_key(&recs[0]);
        res->first_key = next;
        do {
            s32 cnt = count_run(&recs[i], n - i, next++);
            res->groups[groups].start = i;
            res->groups[groups].len = cnt;
            groups++;
            i += cnt;
            if (recs[i].flags & 0x4000) break;
        } while (i < n);
        res->num_groups = groups;
    }
    res->groups[res->num_groups].start = i;
    res->groups[res->num_groups].len = n - i;
    heap_set_top((s32)&res->groups[res->num_groups + 1]);
    for (; i < n; i++) {
        { s32 mask = ~0x4000; recs[i].flags &= mask; }
    }
    return res;
}

/* Adds a record (when value is not 0 and there is room); returns its index. */
s32 scene_model_add(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 value) {
    s32 index;

    if (value != 0) {
        index = scene_model_count;
        if (index < 0x18) {
            scene_model_count = index + 1;
            scene_models[index].handle = value;
            scene_models[index].scale[0] = 0x1000;
            scene_models[index].scale[1] = 0x1000;
            scene_models[index].scale[2] = 0x1000;
            scene_models[index].layer = arg1;
            scene_models[index].offset_x = arg2;
            scene_models[index].offset_y = arg3;
            scene_models[index].offset_z = arg4;
            scene_models[index].unk_1E = arg0;
            scene_models[index].flag = 1;
            return index;
        }
    }
}

void model_set_scale(s32 i, s32 a, s32 b, s32 c) {
    scene_models[i].scale[0] = a;
    scene_models[i].scale[1] = b;
    scene_models[i].scale[2] = c;
}

void scene_model_set_flag(s32 index, s32 value) {
    if (index >= 0 && scene_model_count - 1 >= index) {
        scene_models[index].flag = value;
    }
}

s32 scene_model_get_flag(s32 id) {
    if (id < 0) {
        return 0;
    }
    if (scene_model_count - 1 < id) {
        return 0;
    }
    return scene_models[id].flag;
}

/* Collects the scene models' points within point_search_radius of the camera (XZ distance, Y between -point_search_below and
 * point_search_above) into the 0x18-byte records at light_rec_table, appending after the light_rec_count already there. Each
 * model's points sit in rows 512 wide along X, each sorted by Z, plus an extra run at rows[num_rows] that is
 * checked point by point; the rows near the camera are binary-searched for the Z window the circle leaves. */
void scene_models_project(void) {
    s32 *rot;
    Camera *cam;
    Camera *cams; /* the table base in its own register (scheduling) */
    OutRec18 *out;
    s32 cam_x, cam_y, cam_z;
    s32 layer;
    s32 floor_y, ceil_y, rr, i;

    rot = cam_rotations[cur_view_index].rot;
    gte_set_ctrl3(R11R12, rot[0], R13R21, rot[1], R22R23, rot[2]);
    gte_set_ctrl2_ab(R31R32, rot[3], R33, rot[4]);

    out = (OutRec18 *)light_rec_table + light_rec_count;
    ceil_y = point_search_above;
    cams = cameras;
    cam = &cams[cur_camera_index];
    floor_y = -point_search_below;
    cam_x = cam->pos.vx;
    cam_y = cam->pos.vy;
    cam_z = cam->pos.vz;
    layer = light_env_index;
    rr = point_search_radius * point_search_radius;
    /* IR1 = 0, so SQR gives MAC2 = x * x, MAC3 = z * z (the zero goes through a register) */
    gte_set_r(IR1, 0);

    for (i = 0; i < scene_model_count; i++) {
        SceneModel *rec = &scene_models[i];
        ModelRowsHdr *model, *hdr;
        u8 *verts;
        s32 dx, dy, dz;
        s32 flag_base;
        s32 n;
        ModelVert8 *v;
        PointSlot *p;
        s32 x, y, z, f, m2v, m3v;

        if (rec->flag == 0 || layer != rec->layer) {
            continue;
        }
        model = (ModelRowsHdr *)rec->handle;
        verts = model->verts;
        if (verts == 0) {
            continue;
        }
        dx = cam_x * (0x1000 - rec->scale[0]) / 0x1000 + rec->offset_x - cam_x;
        dy = cam_y * (0x1000 - rec->scale[1]) / 0x1000 + rec->offset_y - cam_y;
        dz = cam_z * (0x1000 - rec->scale[2]) / 0x1000 + rec->offset_z - cam_z;
        if (ABS(dx) > point_search_radius + 0x7FFF) {
            continue;
        }
        if (ABS(dz) > point_search_radius + 0x7FFF) {
            continue;
        }
        if (dy < floor_y - 0x7FFF || ceil_y + 0x7FFF < dy) {
            continue;
        }
        hdr = model;
        flag_base = point_base + rec->unk_1E;

        n = hdr->rows[hdr->num_rows].count;
        if (n > 0) {
            v = (ModelVert8 *)(verts + (hdr->rows[hdr->num_rows].start * 8 + 4));

            for (; n > 0; n--, v++) {
                f = v->idx;
                p = &point_slots[f];
                y = v->y + p->y + dy;

                if (y < floor_y || ceil_y < y) {
                    continue;
                }
                x = v->x + p->x + dx;
                if (ABS(x) > point_search_radius) {
                    continue;
                }
                z = v->z + p->z + dz;
                gte_set(IR2, x);
                gte_set(IR3, z);
                gte_sqr0();
                f = (s16)p->flags & ~0x8000;
                gte_get(MAC2, m2v);
                gte_get_wait(MAC3, m3v);
                if (rr < m2v + m3v) {
                    continue;
                }
                out->x = x;
                out->y = y;
                out->z = z;
                out->flags = f + flag_base;
                out->unk_08[0] = p->unk_0A;
                out->unk_08[1] = p->unk_08;
                out->unk_08[2] = p->unk_0C;
                out->colour = p->colour;
                out++;
            }
        }

        {
            s32 mx = -dx;
            s32 left = mx - 0x1FF;
            s32 right = mx + 0x1FF;
            s32 first = hdr->first_row;
            s32 lo, hi, last, top;

            lo = (left - point_search_radius + 0x8000) >> 9;
            hi = (right + point_search_radius + 0x8000) >> 9;
            last = first + hdr->num_rows - 1;
            if (hi < first || last < lo) {
                continue;
            }
            lo = (lo <= first) ? first : lo;
            top = (hi <= last) ? hi : last;
            last = (top <= first) ? first : top;
            lo -= first;
            hi = last; /* two statements: more refs for hi, which global-alloc then ranks above out */
            hi -= first;
            for (; lo <= hi; lo++) {
                s32 d, lz, shift, e, reach, lim, a, b;
                u32 idx;
                s16 *table;
                n = hdr->rows[lo].count;

                if (n <= 0) {
                    continue;
                }
                /* reach: the camera's row, then the squared radius left at this row, then its root */
                reach = (mx + 0x8000) >> 9;
                d = lo + first - reach;
                if (d < 0) {
                    d = reach - (lo + first);
                }
                d <<= 9;
                reach = rr - d * d;
                idx = ~1;
                if (reach <= 0) {
                    continue;
                }
                gte_set(LZCS, reach);
                table = SQRT - 64;
                gte_get(LZCR, lz);
                shift = 31 - lz;
                lz &= idx;
                e = lz - 24;
                idx = reach << e;
                if (e < 0) {
                    idx = (u32)reach >> -e;
                }
                shift >>= 1;
                reach = (u32)(table[idx] << shift) >> 12;
                v = (ModelVert8 *)(hdr->verts + (hdr->rows[lo].start * 8 + 4));
                lim = -dz - reach;
                a = 0;
                b = n - 1;
                while (a < b) {
                    s32 mid = (a + b) >> 1;

                    if (v[mid].z < lim) {
                        a = mid + 1;
                    } else {
                        b = mid;
                    }
                }
                if (a > 0) {
                    a--;
                }
                n -= a;
                v += a;
                for (; n > 0; n--, v++) {
                    z = ((ModelVertWords *)v)->z_idx;
                    x = ((ModelVertWords *)v)->xy;
                    f = z >> 16;
                    z = (s16)z + dz;
                    if (reach < z) {
                        break;
                    }
                    y = (x >> 16) + dy;
                    x += dx;
                    out->y = y;
                    if (y < floor_y || ceil_y < y) {
                        continue;
                    }
                    gte_set(IR2, x);
                    gte_set(IR3, z);
                    out->x = x;
                    out->z = z;
                    gte_sqr0_b();
                    p = &point_slots[f];
                    gte_get(MAC2, m2v);
                    gte_get_wait(MAC3, m3v);
                    *(s32 *)&out->unk_08[0] = 0;
                    out->unk_08[2] = 0;
                    if (rr < m2v + m3v) {
                        continue;
                    }
                    f = (s16)p->flags;
                    out->colour = 0;
                    if (f & 0x8000) {
                        out->unk_08[0] = p->unk_0A;
                        out->unk_08[1] = p->unk_08;
                        out->unk_08[2] = p->unk_0C;
                        f &= ~0x8000;
                        out->colour = p->colour;
                    }
                    out->flags = f + flag_base;
                    out++;
                }
            }
        }
    }
    light_rec_count = (u32)((u8 *)out - (u8 *)light_rec_table) / sizeof(OutRec18);
}

#ifdef NON_MATCHING
/* Calls scene_models_project() on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * C companion of hand-written asm (not compiled): the asm keeps the old $sp in $at and sets up the frame by hand
 * (FINDINGS "$sp in C"). */
void scene_models_project_scratch(void) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    scene_models_project();
    SCRATCH_STACK_LEAVE_BELOW();
}
#else
INCLUDE_ASM("../src/stage/asm", scene_models_project_scratch);
#endif

void cyl_init(void) {
    d_8011FFF8 = 0;
    cyl_scale = 0x6000;
    cyl_table_build();
    cyl_tex_table = 0;
    vec3_x = 0;
    vec3_y = 0;
    vec3_z = 0;
    vec3_pad = 0;
}

void set_vec3(s16 a, s16 b, s16 c) {
    vec3_x = a;
    vec3_y = b;
    vec3_z = c;
    vec3_pad = 0;
}

s16 *get_vec3_ptr(void) {
    return &vec3_x;
}

void fn_800D425C(s32 value) {
    d_8011FFF8 = value;
}
