/* object_system: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void ptr_table_init(void) {
    void **p;
    s32 i;

    p = ptr_table;
    i = 0x400;
    ptr_table_len = 0;
    ptr_table_mark = 0;
    do {
        *p = NULL;
        i--;
        p++;
    } while (i > 0);
}

void ptr_table_save_mark(void) {
    ptr_table_mark = ptr_table_len;
}

/* Sets ptr_table_len to ptr_table_mark and clears the ptr_table slots from there to the end (0x400). */
void ptr_table_restore_mark(void) {
    s32 count;
    void **slot;

    count = ptr_table_mark;
    slot = &ptr_table[count];
    ptr_table_len = count;
    count = 0x400 - count;
    while (count > 0) {
        *slot = NULL;
        slot++;
        count--;
    }
}

s32 ptr_table_count(void) {
    return ptr_table_len;
}

/* Appends 128 pointers to ptr_table from a table of 128 halfword offsets (in halfwords from the
 * table's start); a zero offset leaves its slot unchanged. */
void ptr_table_append(u16 *table) {
    if (ptr_table_len + 128 < 0x400) {
        u16 *offset = table;
        void **out = &ptr_table[ptr_table_len];
        s32 i;

        for (i = 128; i > 0; i--, offset++, out++) {
            s32 bytes = *offset * 2;
            if (bytes != 0) {
                *out = (u8 *)table + bytes;
            }
        }
        ptr_table_len += 128;
    }
}

/* Shrinks ptr_table_len past trailing zero entries of d_80137118. */
void ptr_table_trim(void) {
    s32 count;
    s32 *entry;

    count = ptr_table_len;
    entry = &d_80137118[count];
    while (count > 0 && *entry == 0) {
        count--;
        entry--;
    }
    ptr_table_len = count;
}

// Fills the 16-bit extents of a model part, then sets both ends to the larger one.
void model_part_extents_max(s32 obj, s32 part_arg, void *extents) {
    s16 *span = extents;
    s32 second;
    s32 first;
    s16 larger;

    model_part_extents(obj, part_arg, span);
    second = span[2];
    first = span[0];
    if (second < first) {
        second = first;
    }
    larger = second;
    span[0] = larger;
    span[2] = larger;
}

/* Extents of a model's 32 parts. node_tree_blend fills a 6-halfword box per part ([0..2] and [3..5] are the
 * two corners, x y z); this keeps the largest |x sum| and |x difference| (out[0]), the y span (out[1]) and
 * the same for z (out[2]). */
void model_part_extents(s32 obj, s32 part_arg, s16 *out) {
    s16 *box = scratch_alloc(0xC);
    s32 ext_x = 0;
    s32 span_y = 0;
    s32 ext_z = 0;
    s32 hi = -0x7FFF;
    s32 lo = 0x7FFF;
    s32 i;
    s32 v;
    s32 x0, x1, y0, y1, z0, z1;

    for (i = 0x1F; i >= 0; i--) {
        if (node_tree_blend(obj, i, part_arg, box) == 1) {
            z1 = box[5];
            z0 = box[2];
            x1 = box[3];
            y1 = box[4];
            x0 = box[0];
            y0 = box[1];
            v = ABS(z1 + z0);
            if (ext_z < v) {
                ext_z = v;
            }
            v = ABS(x1 + x0);
            if (ext_x < v) {
                ext_x = v;
            }
            ext_z = MAX(ABS(z1 - z0), ext_z);
            ext_x = MAX(ABS(x1 - x0), ext_x);
            v = y1 + y0;
            if (hi < v) {
                hi = v;
            }
            v = y1 - y0;
            if (v < lo) {
                lo = v;
            }
            span_y = hi - lo;
        }
    }
    scratch_top -= 0xC;
    out[0] = ext_x;
    out[1] = span_y;
    out[2] = ext_z;
}

/* Adds a solid from two 16-bit point pairs if the table has room.
 * Returns the new solid's id (index + 0x400), or -1 when full. */
s32 solid_add(s16 *p0, s16 *p1, s32 unused_a, void *unused_b) {
    s32 index;
    s32 solid_id;
    SolidCoords *slot;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    index = solid_slot_next;
    solid_id = -1;
    if (0x100 - index > 0) {
        solid_id = index + 0x400;
        x0 = p0[0];
        y0 = p1[0];
        solid_slot_next = index + 1;
        slot = &solid_slots[index];
        x1 = p0[1];
        y1 = p1[1];
        slot->v[0] = x0;
        slot->v[1] = x1;
        slot->v[2] = y0;
        slot->v[3] = y1;
    }
    return solid_id;
}

/* Max over a binary tree of NodePairs (node_pair_table). Leaves (node < 0x400) are
 * entries of ptr_table: GTE general-purpose interpolation of scale with the
 * entry's second halfword. The first call's a1 is still scale, so it emits no move.
 * The nop is the load delay after mfc2 at the join, which gte_get doesn't add. */
s32 node_tree_max_scaled(s32 node, s32 scale) {
    s32 best;

    if (node - 0x400 >= 0) {
        NodePair *pair = &node_pair_table[node];
        s32 left = node_tree_max_scaled(pair->left, scale);
        s32 right = node_tree_max_scaled(pair->right, scale);

        best = left;
        if (left < right) {
            best = right;
        }
    } else {
        s32 value = 0;
        s16 *entry = ptr_table[node];

        if (entry != NULL) {
            s32 ir1 = entry[1];

            gte_set(IR0, scale);
            gte_set(IR1, ir1);
            gte_gpf12();
            gte_get(MAC1, value);
        }
        mips_nop_use(value);
        best = value;
    }
    return best;
}

void solid_system_reset(void) {
    solid_grid_parity = 0;
    solid_count = -1;
    collide_mode = 0;
    solid_pool_clear();
    solid_slot_next = 0;
}

/* Re-centres the solid grid on a position and clears the 32 cell counts of each axis (if any solids were added). */
void solid_grid_reset(s32 *pos) {
    s32 *cell_x;
    s32 *cell_y;
    s32 *cell_z;
    s32 n;

    grid_origin_x = (0x2000 - (pos[0] >> 12)) & ~0x1FF;
    grid_origin_y = (0x2000 - (pos[1] >> 12)) & ~0x1FF;
    grid_origin_z = (0x2000 - (pos[2] >> 12)) & ~0x1FF;
    if (solid_count != 0) {
        cell_x = &solid_cells_x;
        cell_y = &solid_cells_y;
        cell_z = &solid_cells_z;
        n = 0x20;
        do {
            *cell_x = 0;
            cell_x++;
            *cell_y = 0;
            cell_y++;
            *cell_z = 0;
            cell_z++;
            n -= 1;
        } while (n > 0);
        solid_count = 0;
    }
    solid_grid_parity ^= 1;
}

void set_collide_mode(s16 value) {
    collide_mode = value;
}

/* Calls solid_setup(index, shape, a, b) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * The original is hand-written asm: the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void solid_setup_scratch(u32 index, SolidShape *shape, s32 a, s32 b) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    solid_setup(index, shape, a, b);
    SCRATCH_STACK_LEAVE_BELOW();
}

/* Sets up solid `index` from `shape`: every one of its 32 boxes starts as the shape's size (box_b zero),
 * and the bit for the new solid (solid_count) is set in the grid cells its extent covers on each axis.
 * The solid is then appended to solid_index. */
void solid_setup(u32 index, SolidShape *shape, s32 a, s32 b) {
    Solid *solid;
    SVECTOR *box;
    SVECTOR *box_b;
    s16 *p;
    s16 *q;
    s32 sx;
    s32 sy;
    s32 sz;
    s32 radius;
    /* the register numbers matter: the allocator picks the wrong ones otherwise */
    register s32 mask asm("$9");
    register s32 one asm("$3");
    s32 count;
    s32 i;
    s32 c;
    u32 lo;
    u32 hi;
    u32 *cell;

    count = solid_count;
    if (count < 0x20 && index < 0x20) {
        solid = &solids[index];
        box = solid->box;
        box_b = solid->box_b;
        radius = node_tree_max_scaled(a, b);
        one = 1;
        mask = one << count;
        i = 0x20;
        sx = shape->size[0];
        sy = shape->size[1];
        sz = shape->size[2];
        q = &solid->box_b[0].vz;
        p = &solid->box[0].vz;
        solid->owner = (s32 *)shape;
        solid->node_root = a;
        solid->radius = radius;
        solid->unk_006 = b;
        solid->unk_20C = 1;
        do {
            i--;
            box->vx = sx;
            p[-1] = sy;
            p[0] = sz;
            p += 4;
            box += 1;
            box_b->vx = 0;
            q[-1] = 0;
            q[0] = 0;
            q += 4;
            box_b += 1;
        } while (i > 0);
        /* each axis: mark the grid cells from (position - radius) to (position + radius) */
        __asm__("" : "=r"(cell) : "0"(&solid_cells_x));
        c = (shape->pos[0] >> 12) + grid_origin_x;
        if (c < 0x4000) {
            lo = ((c - radius) >> 9) & 0x1F;
            hi = ((c + radius) >> 9) & 0x1F;
            if (hi >= lo) {
                cell = &cell[lo];
                hi++;
                while (lo != hi) {
                    lo++;
                    *cell |= mask;
                    cell++;
                }
            }
        }
        __asm__("" : "=r"(cell) : "0"(&solid_cells_y));
        c = (shape->pos[1] >> 12) + grid_origin_y;
        if (c < 0x4000) {
            lo = ((c - radius) >> 9) & 0x1F;
            hi = ((c + radius) >> 9) & 0x1F;
            if (hi >= lo) {
                cell = &cell[lo];
                hi++;
                while (lo != hi) {
                    lo++;
                    *cell |= mask;
                    cell++;
                }
            }
        }
        __asm__("" : "=r"(cell) : "0"(&solid_cells_z));
        c = (shape->pos[2] >> 12) + grid_origin_z;
        if (c < 0x4000) {
            lo = ((c - radius) >> 9) & 0x1F;
            hi = ((c + radius) >> 9) & 0x1F;
            if (hi >= lo) {
                cell = &cell[lo];
                hi++;
                while (lo != hi) {
                    lo++;
                    *cell |= mask;
                    cell++;
                }
            }
        }
        ((u8 *)&solid_index)[count] = index;
        solid_count = count + 1;
    }
}

/* Set sub-box `box` of solid `index` and mark the solid changed. */
void solid_set_box(u32 index, u32 box, SVECTOR *v) {
    Solid *solid;
    SVECTOR *dst;

    if (index < 32 && box < 32) {
        solid = &solids[index];
        dst = &solid->box[box];
        dst->vx = v->vx;
        dst->vy = v->vy;
        dst->vz = v->vz;
        solid->unk_20C = 0;
    }
}

/* Sets box j of solid i (both < 32). */
void solid_set_box_b(u32 i, u32 j, SVECTOR *src) {
    if (i < 32 && j < 32) {
        SVECTOR *box = &solids[i].box_b[j];
        box->vx = src->vx;
        box->vy = src->vy;
        box->vz = src->vz;
    }
}

void solid_set_unk214(u32 i, s32 value) {
    if (i < 32) {
        solids[i].part_enable_mask = value;
    }
}

static inline void rotate_svectors_from(SVECTOR *src, SVECTOR *dst, s32 count) {
    SVECTOR *end;
    s32 xy, z, mac2;

    gte_load(VXY0, src, 0);
    gte_load(VZ0, src, 4);
    src++;
    end = dst + count - 1;
    gte_rtv0_b();
    while (dst != end) {
        xy = *(s32 *)&src->vx;
        z = *(s32 *)&src->vz;
        src++;
        gte_store(MAC1, dst, 0);
        gte_get(MAC2, mac2);
        gte_set(VZ0, z);
        gte_set(VXY0, xy);
        gte_store(MAC3, dst, 4);
        dst->vy = mac2;
        gte_rtv0_b();
        dst++;
    }
    gte_store(MAC1, dst, 0);
    gte_get(MAC2, mac2);
    gte_store(MAC3, dst, 4);
    dst->vy = mac2;
}
/* Sets the collider box once (state 0 -> 1): turns the half-size box (dim) by the angles and stores its
 * axis-aligned half-extent and turned centre in size/offset (Collider 0x04 is laid out as a MovingBox),
 * or their changes in size_delta/offset_delta when the box was already set. */
void collider_box(Collider *c) {
    s32 *rot;
    SVECTOR *v;
    SVECTOR *center;
    register SVECTOR *corner asm("$18");
    s32 x, y, z, t;
    s32 yaw, pitch, roll;
    s32 ox, oy;
    register s32 oz asm("$7");
    register MovingBox *box asm("$17");
    MovingBox *delta;

    if (c->state == 0) {
        pitch = c->angle[0];
        yaw = c->angle[1];
        roll = c->angle[2];
        do { /* scheduling barrier: the angle loads stay first */
        } while (0);
        rot = scratch_alloc(0x48);
        v = (SVECTOR *)(rot + 8);
        center = v + 1;
        corner = v + 2;
        box = (MovingBox *)c->size;
        delta = box;
        x = c->dim[0];
        y = c->dim[1] / 2;
        z = c->dim[2];
        v[0].vx = x;
        v[0].vy = y;
        v[0].vz = z;
        center->vx = 0;
        center->vy = -y;
        center->vz = 0;
        corner[0].vx = -x;
        corner[0].vy = y;
        corner[0].vz = z;
        corner[1].vx = x;
        corner[1].vy = -y;
        corner[1].vz = z;
        corner[2].vx = x;
        corner[2].vy = y;
        corner[2].vz = -z;
        rot_matrix(rot, yaw, pitch, roll);
        rot_load(rot);
        rotate_svectors_from(v, v, 5);
        x = v[0].vx;
        y = v[0].vy;
        z = v[0].vz;
        x = ABS(x); t = ABS(corner[0].vx); if (x < t) x = t;
        y = ABS(y); t = ABS(corner[0].vy); if (y < t) y = t;
        z = ABS(z); t = ABS(corner[0].vz); if (z < t) z = t;
        t = ABS(corner[1].vx); if (x < t) x = t;
        t = ABS(corner[1].vy); if (y < t) y = t;
        t = ABS(corner[1].vz); if (z < t) z = t;
        t = ABS(corner[2].vx); if (x < t) x = t;
        t = ABS(corner[2].vy); if (y < t) y = t;
        t = ABS(corner[2].vz); if (z < t) z = t;
        if (box->size[0] == 0) {
            ox = center->vx;
            oy = center->vy;
            oz = center->vz;
            box->size[0] = x;
            box->size[1] = y;
            box->size[2] = z;
        } else {
            ox = center->vx;
            oy = center->vy;
            oz = center->vz;
            delta->size_delta[0] = x - box->size[0];
            delta->size_delta[1] = y - box->size[1];
            delta->size_delta[2] = z - box->size[2];
            delta->offset_delta[0] = ox - box->offset[0];
            delta->offset_delta[1] = oy - box->offset[1];
            delta->offset_delta[2] = oz - box->offset[2];
        }
        box->offset[0] = ox;
        box->offset[1] = oy;
        box->offset[2] = oz;
        do {
        } while (0);
        scratch_top -= 0x48;
        c->state = 1;
    }
}

/* push_out_of_solids_xz, discarding the side hit. */
void collide_solids_xz(Collider *coll) {
    s16 wall_hit = 0;

    push_out_of_solids_xz(coll, &wall_hit);
}

void push_out_of_solids_xz(Collider *coll, s16 *wall_hit) {
    s32 y;
    s32 i;
    u32 bit;
    s32 lower;
    s32 cells;
    s32 dx;
    s32 dz;
    s32 parts;
    s32 part_bit;
    s32 rest_bits;
    s16 *ext;
    s32 x, z;
    s32 dy;
    Solid *solid;
    Collider *other;
    MovingBox *part;
    MovingBox *box;
    s32 half;
    s32 touching;
    s32 part_hit;
    s32 was_in_x;
    s32 was_in_z;
    s32 grow_x, grow_z;
    s32 other_x, other_px, other_pz;
    s32 cur_x, cur_z;

    if (solid_count > 0) {
        ext = scratch_alloc(8);
        i = solid_count - 1;
        bit = 1 << i;
        lower = solid_masks[i];
        box = (MovingBox *)coll->size;
        collider_box(coll);
        x = (coll->sub[0] >> 12) + coll->offset[0] + coll->pos[0];
        y = (coll->sub[1] >> 12) + coll->offset[1];
        z = (coll->sub[2] >> 12) + coll->offset[2] + coll->pos[2];
        ext[0] = coll->size[0] + coll->size_delta[0];
        ext[1] = coll->size[1] + coll->size_delta[1];
        ext[2] = coll->size[2] + coll->size_delta[2];
        cells = (&solid_cells_x)[((u32)(x + grid_origin_x) >> 9) & 0x1F]
              & (&solid_cells_y)[((u32)(y + grid_origin_y) >> 9) & 0x1F]
              & (&solid_cells_z)[((u32)(z + grid_origin_z) >> 9) & 0x1F];
        do {
            if (cells & bit) {
                solid = &solids[((u8 *)&solid_index)[i]];
                other = (Collider *)solid->owner;
                if (other != NULL && !(((u8 *)&other->x0)[1] & (u16)collide_mode)) {
                    half = solid->radius - 1;
                    touching = 1;
                    if (!BOX_OVERLAP(x, other->sub[0] >> 12, half + ext[0], y, other->sub[1] >> 12, half + ext[1], z, other->sub[2] >> 12, half + ext[2])) {
                        touching = 0;
                    }
                    if (touching == 1) {
                        part = (MovingBox *)solid->parts;
                        rest_bits = -1;
                        part_bit = 1;
                        parts = solid_parts_update_scratch(solid, 0);
                        dx = x - (other->sub[0] >> 12);
                        dy = y - (other->sub[1] >> 12);
                        dz = z - (other->sub[2] >> 12);
                        collider_box(other);
                        if (parts != 0) {
                            do {
                                if (parts & part_bit) {
                                    part_hit = 1;
                                    if (!BOX_OVERLAP(dx, part->offset[0], part->size[0] + part->size_delta[0] + ext[0] - 1, dy, part->offset[1], part->size[1] + part->size_delta[1] + ext[1] - 1, dz, part->offset[2], part->size[2] + part->size_delta[2] + ext[2] - 1)) {
                                        part_hit = 0;
                                    }
                                    if (part_hit == 1) {
                                        grow_z = part->size_delta[2] + box->size_delta[2];
                                        grow_x = part->size_delta[0] + box->size_delta[0];
                                        other_pz = (other->sub[2] >> 12) + part->offset[2];
                                        other_x = other->sub[0] >> 12;
                                        other_px = other_x + part->offset[0];
                                        if ((coll->sub[2] >> 12) + box->offset[2] - other_pz < 0) {
                                            grow_z = -grow_z;
                                        }
                                        cur_x = (coll->sub[0] >> 12) + box->offset[0];
                                        if (cur_x - other_px < 0) {
                                            grow_x = -grow_x;
                                        }
                                        was_in_x = 1;
                                        if (!BOX_OVERLAP(cur_x - box->offset_delta[0] + (other->pos[0] + part->offset_delta[0] + grow_x) - other_x, part->offset[0],
                                                       part->size[0] + part->size_delta[0] + ext[0] - 1, dy, part->offset[1], part->size[1] + part->size_delta[1] + ext[1] - 1, dz, part->offset[2], part->size[2] + part->size_delta[2] + ext[2] - 1)) {
                                            was_in_x = 0;
                                        }
                                        if (!was_in_x) {
                                            s32 reach, motion, pen, push;

                                            reach = part->size[0] + part->size_delta[0];
                                            reach += ext[0];
                                            motion = (coll->pos[0] + box->offset_delta[0]) - (other->pos[0] + part->offset_delta[0] + grow_x);
                                            pen = reach - ABS(x - other_px);
                                            if (pen < 0) {
                                                pen = 0;
                                            }
                                            push = pen;
                                            if (motion < 0) {
                                                push = -push;
                                            }
                                            if (ABS(motion) < ABS(push)) {
                                                push = motion;
                                            }
                                            coll->pos[0] -= push;
                                            coll->contact |= 1;
                                            *wall_hit = other->x0;
                                            x -= push;
                                        }
                                        cur_z = (coll->sub[2] >> 12) + box->offset[2] - box->offset_delta[2] + (other->pos[2] + part->offset_delta[2] + grow_z) - (other->sub[2] >> 12);
                                        was_in_z = 1;
                                        if (!BOX_OVERLAP(dx, part->offset[0], part->size[0] + part->size_delta[0] + ext[0] - 1, dy, part->offset[1], part->size[1] + part->size_delta[1] + ext[1] - 1, cur_z, part->offset[2], part->size[2] + part->size_delta[2] + ext[2] - 1)) {
                                            was_in_z = 0;
                                        }
                                        if (!was_in_z) {
                                            s32 reach, motion, pen, push;

                                            motion = (coll->pos[2] + box->offset_delta[2]) - (other->pos[2] + part->offset_delta[2] + grow_z);
                                            reach = part->size[2] + part->size_delta[2];
                                            reach += ext[2];
                                            pen = reach - ABS(z - other_pz);
                                            if (pen < 0) {
                                                pen = 0;
                                            }
                                            push = pen;
                                            if (motion < 0) {
                                                push = -push;
                                            }
                                            if (ABS(motion) < ABS(push)) {
                                                push = motion;
                                            }
                                            coll->pos[2] -= push;
                                            coll->contact |= 4;
                                            *wall_hit = other->x0;
                                            z -= push;
                                        }
                                    }
                                }
                                part++;
                                rest_bits <<= 1;
                                part_bit <<= 1;
                            } while (parts & rest_bits);
                        }
                    }
                }
            }
            lower &= bit - 1;
            bit >>= 1;
        } while ((cells & lower) && i-- > 0);
        scratch_top -= 8;
    }
}

void collide_solids_y(Collider *coll) {
    s16 side = 0;

    push_out_of_solids_y(coll, &side);
}

static inline s32 solid_y_push(MovingBox *part, Collider *coll, Collider *other, s32 y, s16 *ext, s32 *push) {
    s32 mode = 0;
    s32 h = part->size[1] + part->size_delta[1];
    s32 ext_y = ext[1];
    s32 top = part->offset[1] - h;
    s32 d = top - ((y - (other->sub[1] >> 12)) + coll->pos[1] + ext_y);
    register s32 under asm("$4");

    if (d >= 0) {
        d = top;
        mode = 1;
    } else {
        under = -d;
        d += (h + ext_y) * 2;
        if (d <= 0) {
            d = -d;
            mode = -1;
        } else if (d - under >= 0) {
            d = under;
        }
    }
    *push = d;
    return mode;
}
void push_out_of_solids_y(Collider *coll, s16 *side) {
    s32 y;
    s32 i;
    u32 bit;
    s32 cells;
    s32 parts;
    s32 part_bit;
    s32 rest_bits;
    s16 *ext;
    s32 x, z;
    Solid *solid;
    Collider *other;
    MovingBox *part;
    MovingBox *box;
    s32 half;
    s32 touching;
    s32 part_hit;
    s32 grow_x, grow_z;
    s32 other_x, other_z, other_px, other_pz;
    s32 mode;
    s32 dx, dz;
    s32 push;

    if (solid_count > 0) {
        ext = scratch_alloc(8);
        i = solid_count - 1;
        bit = 1 << i;
        box = (MovingBox *)coll->size;
        collider_box(coll);
        x = (coll->sub[0] >> 12) + coll->offset[0];
        y = (coll->sub[1] >> 12) + coll->offset[1];
        z = (coll->sub[2] >> 12) + coll->offset[2];
        ext[0] = coll->size[0] + coll->size_delta[0];
        ext[1] = coll->size[1] + coll->size_delta[1];
        ext[2] = coll->size[2] + coll->size_delta[2];
        cells = (&solid_cells_z)[((u32)(z + grid_origin_z) >> 9) & 0x1F]
              & (&solid_cells_x)[((u32)(x + grid_origin_x) >> 9) & 0x1F];
        do {
            if (cells & bit) {
                solid = &solids[((u8 *)&solid_index)[i]];
                other = (Collider *)solid->owner;
                if (other != NULL && !(((u8 *)&other->x0)[1] & (u16)collide_mode)) {
                    collider_box(other);
                    touching = 1;
                    z = (coll->sub[2] >> 12) + box->offset[2] + other->pos[2];
                    x = (coll->sub[0] >> 12) + box->offset[0] + other->pos[0];
                    if (solid->owner != NULL) {
                        half = solid->radius - 1;
                        if (!(in_range(z, ((Collider *)solid->owner)->sub[2] >> 12, half + ext[2])
                              && in_range(x, ((Collider *)solid->owner)->sub[0] >> 12, half + ext[0]))) {
                            touching = 0;
                        }
                    }
                    if (touching == 1) {
                        part = (MovingBox *)solid->parts;
                        parts = solid_parts_update_scratch(solid, 0);
                        rest_bits = -1;
                        part_bit = 1;
                        if (parts != 0) {
                            do {
                                if (parts & part_bit) {
                                    grow_z = part->size_delta[2] + box->size_delta[2];
                                    grow_x = part->size_delta[0] + box->size_delta[0];
                                    other_z = other->sub[2] >> 12;
                                    other_pz = other_z + part->offset[2];
                                    other_x = other->sub[0] >> 12;
                                    other_px = other_x + part->offset[0];
                                    if ((coll->sub[2] >> 12) + box->offset[2] - other_pz < 0) {
                                        grow_z = -grow_z;
                                    }
                                    if ((coll->sub[0] >> 12) + box->offset[0] - other_px < 0) {
                                        grow_x = -grow_x;
                                    }
                                    part_hit = 1;
                                    dz = z - box->offset_delta[2] + part->offset_delta[2] + grow_z - other_z;
                                    dx = x - box->offset_delta[0] + part->offset_delta[0] + grow_x - other_x;
                                    if (!(in_range(dz, part->offset[2], part->size[2] + part->size_delta[2] + ext[2] - 1)
                                          && in_range(dx, part->offset[0], part->size[0] + part->size_delta[0] + ext[0] - 1))) {
                                        part_hit = 0;
                                    }
                                    if (part_hit == 1) {
                                        push = 0;
                                        mode = solid_y_push(part, coll, other, y, ext, &push);
                                        switch (mode) {
                                        case 0: {
                                            s32 motion = (coll->pos[1] + box->offset_delta[1] + box->size_delta[1])
                                                       - (other->pos[1] + part->offset_delta[1] - part->size_delta[1]);
                                            if (motion < 0) {
                                                push = -push;
                                                coll->contact |= 2;
                                                *side = other->x0;
                                            }
                                            if (ABS(motion) < ABS(push)) {
                                                push = motion;
                                            }
                                            coll->pos[1] -= push;
                                            break;
                                        }
                                        case 1:
                                            if (coll->pos[1] >= 0) {
                                                push = part->offset[1] + (other->sub[1] >> 12) - y - (part->size[1] + part->size_delta[1] + ext[1]);
                                                if (!(part->offset_delta[1] - part->size_delta[1] + other->pos[1] < push)) {
                                                    coll->pos[1] = push;
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                                part++;
                                rest_bits <<= 1;
                                part_bit <<= 1;
                            } while (parts & rest_bits);
                        }
                    }
                }
            }
            cells &= bit - 1;
            bit >>= 1;
        } while (cells && i-- > 0);
        scratch_top -= 8;
    }
}

/* collide_objects with a cleared result word. */
void collide_objects_discard(Collider *coll, s32 *pos) {
    u16 side;

    side = 0;
    collide_objects(coll, pos, &side);
}

static inline s32 y_side(s32 ext, s32 centre, s32 reach, s32 sub_y, s32 y, s32 *gap) {
    s32 dir = 0;
    s32 top = centre - reach;
    s32 d;
    s32 below;

    sub_y >>= 12;
    d = top - (y - sub_y + ext);

    if (d >= 0) {
        d = top;
        dir = 1;
    } else {
        below = -d;
        ext = (reach + ext) * 2;
        d += ext;
        if (d <= 0) {
            d = -d;
            dir = -1;
        } else if (d - below >= 0) {
            d = below;
        }
    }
    *gap = d;
    return dir;
}
s32 collide_objects(Collider *coll, s32 *pos, u16 *side) {
    s32 x, y, z;
    s32 best;
    s32 best_id;
    s32 i;
    u32 bit;
    s32 cells;
    s16 *ext;
    MovingBox *box;
    Solid *solid;
    Collider *other;
    MovingBox *part;
    s32 parts;
    s32 part_bit;
    s32 rest_bits;
    s32 half;
    s32 touching;
    s32 part_hit;
    s32 dist;

    best = 0x7FFFF;
    x = pos[0];
    y = pos[1];
    z = pos[2];
    coll->contact_type_mask = 0;
    best_id = 0;
    coll->contact_id = 0;
    if (solid_count > 0) {
        ext = scratch_alloc(8);
        i = solid_count - 1;
        bit = 1 << i;
        box = (MovingBox *)coll->size;
        collider_box(coll);
        x += coll->offset[0];
        y += coll->offset[1];
        z += coll->offset[2];
        ext[0] = coll->size[0] + coll->size_delta[0];
        ext[1] = coll->size[1] + coll->size_delta[1];
        ext[2] = coll->size[2] + coll->size_delta[2];
        cells = (&solid_cells_z)[((u32)(z + grid_origin_z) >> 9) & 0x1F]
              & (&solid_cells_x)[((u32)(x + grid_origin_x) >> 9) & 0x1F];
        do {
            if (cells & bit) {
                solid = &solids[((u8 *)&solid_index)[i]];
                other = (Collider *)solid->owner;
                if (other != NULL && !(((u8 *)&other->x0)[1] & (u16)collide_mode)) {
                    half = solid->radius - 1;
                    touching = 1;
                    if (!(in_range(z, other->sub[2] >> 12, half + ext[2]) && in_range(x, other->sub[0] >> 12, half + ext[0]))) {
                        touching = 0;
                    }
                    if (touching == 1) {
                        part = (MovingBox *)solid->parts;
                        parts = solid_parts_update_scratch(solid, 0);
                        rest_bits = -1;
                        part_bit = 1;
                        collider_box(other);
                        if (parts != 0) {
                            do {
                                if (parts & part_bit) {
                                    s32 dz = z - (other->sub[2] >> 12);
                                    s32 dx = x - (other->sub[0] >> 12);

                                    part_hit = 1;
                                    if (!(in_range(dz, part->offset[2], part->size[2] + part->size_delta[2] + ext[2] - 1)
                                          && in_range(dx, part->offset[0], part->size[0] + part->size_delta[0] + ext[0] - 1))) {
                                        part_hit = 0;
                                    }
                                    if (part_hit == 1) {
                                        dist = 0;
                                        switch (y_side(ext[1], part->offset[1], part->size[1] + part->size_delta[1], other->sub[1], y, &dist)) {
                                        case 0:
                                            coll->contact_type_mask |= ((u8 *)&other->x0)[1];
                                            coll->contact |= CONTACT_20;
                                            *side = other->x0;
                                            break;
                                        case 1:
                                            dist += other->sub[1] >> 12;
                                            if (dist < best) {
                                                best = dist;
                                                best_id = other->x0;
                                            }
                                            break;
                                        default:
                                            if (dist == 0) {
                                                coll->contact |= CONTACT_CEILING | 2;
                                            }
                                            break;
                                        }
                                    }
                                }
                                part++;
                                rest_bits <<= 1;
                                part_bit <<= 1;
                            } while (parts & rest_bits);
                        }
                    }
                }
            }
            cells &= bit - 1;
            bit >>= 1;
        } while (cells && i-- > 0);
        y -= box->offset[1];
        scratch_top -= 8;
    }
    if (y >= best - (coll->dim[1] / 2 + coll->offset[1])) {
        y = best - (coll->dim[1] / 2 + coll->offset[1]);
        coll->contact |= CONTACT_FLOOR | 2;
    }
    *(s32 *)coll->unk_50 = best;
    coll->contact_id = best_id;
    return y;
}

/* Finds the first solid (highest index first) in pos's grid cell whose box holds pos and
 * whose parts pass solid_contains_point; records the contact in c. */
void collide_solid_point(Collider *c, s32 *pos) {
    s16 *box;
    s32 i;
    u32 bit;
    s32 cells;
    s32 half;
    s32 x, y, z;
    s32 hit;
    Solid *solid;
    Collider *other;

    c->contact_type_mask = 0;
    c->contact_id = 0;
    if (solid_count > 0) {
        box = scratch_alloc(8);
        i = solid_count - 1;
        bit = 1 << i;
        cells = *(s32 *)((u8 *)&solid_cells_x + (((u32)(pos[0] + grid_origin_x) >> 7) & 0x7C)) &
                *(s32 *)((u8 *)&solid_cells_y + (((u32)(pos[1] + grid_origin_y) >> 7) & 0x7C)) &
                *(s32 *)((u8 *)&solid_cells_z + (((u32)(pos[2] + grid_origin_z) >> 7) & 0x7C));
        box[0] = 0;
        box[1] = 0;
        box[2] = 0;
        do {
            if (cells & bit) {
                solid = &solids[((u8 *)&solid_index)[i]];
                other = (Collider *)solid->owner;
                if (other != NULL && !(((u8 *)&other->x0)[1] & (u16)collide_mode)) {
                    x = pos[0];
                    y = pos[1];
                    z = pos[2];
                    half = solid->radius - 1;
                    hit = 1;
                    if (!BOX_OVERLAP(x, other->sub[0] >> 12, half + box[0],
                                     y, other->sub[1] >> 12, half + box[1],
                                     z, other->sub[2] >> 12, half + box[2])) {
                        hit = 0;
                    }
                    if (hit == 1 && (s32)solid_contains_point(solid, pos) == hit) {
                        c->contact |= 5;
                        c->contact_type_mask = ((u8 *)&other->x0)[1];
                        c->contact_id = other->x0;
                        return;
                    }
                }
            }
            cells &= bit - 1;
            bit >>= 1;
        } while (cells != 0 && i-- > 0);
        scratch_top -= 8;
    }
}

/* Calls collide_solid_point(c, pos) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * The original is hand-written asm: the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void collide_solid_point_scratch(Collider *c, s32 *pos) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    collide_solid_point(c, pos);
    SCRATCH_STACK_LEAVE_BELOW();
}

static inline s32 span_hit(s32 r, s32 d) {
    return (u32)(d + r) <= (u32)(r * 2);
}
/* Moving box `c` against the solids in its grid cells; returns the first hit solid's state, else 0. */
s16 collide_solid_cells(Collider *c, s32 *pos) {
    s32 x, y, z;
    s32 mask;
    s32 i;
    u32 bit;
    s16 *sz;

    if (solid_count > 0) {
        i = solid_count - 1;
        bit = 1 << i;
        x = pos[0];
        y = pos[1];
        z = pos[2];
        mask = *(s32 *)((u8 *)&solid_cells_x + (((u32)(x + grid_origin_x) >> 7) & 0x7C)) &
               *(s32 *)((u8 *)&solid_cells_y + (((u32)(y + grid_origin_y) >> 7) & 0x7C)) &
               *(s32 *)((u8 *)&solid_cells_z + (((u32)(z + grid_origin_z) >> 7) & 0x7C));
        collider_box(c);
        sz = c->size;
        x += c->offset[0];
        y += c->offset[1];
        z += c->offset[2];
        do {
            if (mask & bit) {
                Solid *solid = &solids[((u8 *)&solid_index)[i]];
                s32 *owner = solid->owner;
                if (owner != 0) {
                    u8 flags = ((SolidOwner *)owner)->head.b.flags;
                    if (!(flags & (u16)collide_mode)) {
                        if ((flags & c->contact_type_mask) != flags) {
                            s16 *box = scratch_alloc(8);
                            s32 hit = 1;
                            s16 bz;
                            box[0] = sz[0] + sz[9];
                            box[1] = sz[1] + sz[10];
                            bz = sz[2] + sz[11];
                            box[2] = bz;
                            if (solid->owner != 0) {
                                s32 *o = solid->owner;
                                s32 h = solid->radius - 1;
                                if (!(span_hit(h + box[0], x - (o[7] >> 12)) &&
                                      span_hit(h + box[1], -(o[8] >> 12) + y) &&
                                      span_hit(h + bz, z - (o[9] >> 12)))) {
                                    hit = 0;
                                }
                            }
                            if (hit == 1) {
                                SolidPartHit *part = (SolidPartHit *)solid->parts;
                                s32 ox = x - (owner[7] >> 12);
                                s32 oy = y - (owner[8] >> 12);
                                s32 oz = z - (owner[9] >> 12);
                                s32 parts = solid_parts_update_scratch(solid, 0);
                                s32 rest = -1;
                                s32 pbit = 1;
                                if (parts != 0) {
                                    do {
                                        if (parts & pbit) {
                                            s16 *q = &part->off[2]; /* walks with part: q[-2..0] = off, q[4..6] = size_delta */
                                            s32 ok;
                                            ok = 1;
                                            if (!(span_hit(part->size[0] + q[4] + box[0] - 1, ox - q[-2]) &&
                                                 span_hit(q[-4] + q[5] + box[1] - 1, oy - q[-1]) &&
                                                 span_hit(q[-3] + q[6] + box[2] - 1, oz - q[0]))) {
                                                ok = 0;
                                            }
                                            if (ok == 1) {
                                                return ((SolidOwner *)owner)->head.id;
                                            }
                                        }
                                        part++;
                                        rest <<= 1;
                                        pbit <<= 1;
                                    } while (parts & rest);
                                }
                                scratch_top -= 8;
                            } else {
                                scratch_top -= 8;
                            }
                        }
                    }
                }
            }
            mask &= bit - 1;
            bit >>= 1;
            if (mask == 0) {
                break;
            }
            if (i-- <= 0) {
                break;
            }
        } while (1);

    }
    return 0;
}

static inline s32 axis_in(s32 r, s32 a, s32 b) {
    s32 d = a - b + r;

    r <<= 1;
    return (u32)d <= (u32)r;
}
static inline void rotate_svectors_n(SVECTOR *src, SVECTOR *dst, s32 count) {
    SVECTOR *end;
    s32 xy, z, mac2;

    gte_load(VXY0, src, 0);
    gte_load(VZ0, src, 4);
    src++;
    end = dst + count - 1;
    gte_rtv0();
    while (dst != end) {
        xy = *(s32 *)&src->vx;
        z = *(s32 *)&src->vz;
        src++;
        gte_store(MAC1, dst, 0);
        gte_get(MAC2, mac2);
        gte_set(VZ0, z);
        gte_set(VXY0, xy);
        gte_store(MAC3, dst, 4);
        dst->vy = mac2;
        gte_rtv0_b();
        dst++;
    }
    gte_store(MAC1, dst, 0);
    gte_get(MAC2, mac2);
    gte_store(MAC3, dst, 4);
    dst->vy = mac2;
}
/* 1 when pos lies inside one of solid's part boxes (in that part's rotated frame), else 0. */
s32 solid_contains_point(Solid *solid, s32 *pos) {
    s32 *rot;
    SVECTOR *local;
    s16 *blend;
    s32 *owner;
    s32 done;
    s32 i;
    s32 x_ok, y_ok;
    s32 result;

    result = 0;
    done = 0;
    rot = scratch_alloc(0x34);
    local = (SVECTOR *)(rot + 8);
    blend = (s16 *)(local + 1);
    owner = solid->owner;
    if (owner != NULL) {
        i = 0;
        if (solid->radius != 0) {
            i = 0; /* no effect; makes i's start a copy of result (lw from its slot) */
        }
        for (; i < 32; i++) {
            if (node_tree_blend(solid->node_root, i, solid->unk_006, blend) != 1) {
                continue;
            }
            if (done == 0 || solid->unk_20C == 0) {
                rot_matrix_b(rot, -solid->box[i].vz, -solid->box[i].vx, -solid->box[i].vy);
                rot_load(rot);
                local->vx = pos[0] - (owner[7] >> 12);
                local->vy = pos[1] - (owner[8] >> 12);
                local->vz = pos[2] - (owner[9] >> 12);
                rotate_svectors_n(local, local, 1);
                done = 1;
            }
            x_ok = axis_in(blend[0] - 1, local->vx, blend[3]);
            if (x_ok == 1) {
                y_ok = axis_in(blend[1] - 1, local->vy, blend[4]);
                if (y_ok == x_ok && axis_in(blend[2] - 1, local->vz, blend[5]) == y_ok) {
                    result = 1;
                    break;
                }
            }
        }
    }
    scratch_top -= 0x34;
    return result;
}

void solid_pool_clear(void) {
    Solid *solid = solids;
    s32 i;

    solid_active_count = 0;
    for (i = 32; i > 0; i--) {
        solid->state = 0;
        solid++;
    }
}

s32 solid_alloc(void) {
    Solid *s;
    s32 count = solid_active_count;
    s32 idx = -1;
    s32 i;

    s = solids;
    if (count < 0x20) {
        for (idx = 0; idx < 0x20; s++, idx++) {
            if (s->state == 0) {
                SVECTOR *a = s->box;
                SVECTOR *b = s->box_b;
                SolidPart12 *c = (SolidPart12 *)s->parts;
                s->node_root = -1;
                s->radius = 0;
                s->unk_006 = 0;
                s->owner = NULL;
                s->unk_20E = 0;
                s->unk_20C = 1;
                s->part_mask = 0;
                s->part_enable_mask = -1;
                i = 0x20;
                do {
                    i--;
                    a->vx = 0; a->vy = 0; a->vz = 0; a++;
                    b->vx = 0; b->vy = 0; b->vz = 0; b++;
                    c->v[0] = 0; c->v[1] = 0; c->v[2] = 0; c->v[3] = 0;
                    c->v[4] = 0; c->v[5] = 0; c->v[6] = 0; c->v[7] = 0;
                    c->v[8] = 0; c->v[9] = 0; c->v[10] = 0; c->v[11] = 0;
                    c++;
                } while (i > 0);
                s->state = 1;
                solid_active_count++;
                break;
            }
        }
    }
    return idx;
}

/* Deactivate solid `index`. */
void solid_free(u32 index) {
    Solid *solid;

    if (index < 32) {
        solid = &solids[index];
        if (solid->state == 1) {
            solid->state = 0;
            solid_active_count--;
        }
    }
}

/* Reset all 32 solids. */
void solid_reset_all(void) {
    Solid *solid = solids;
    s32 i;

    for (i = 32; i > 0; i--, solid++) {
        solid_parts_move(solid);
    }
    solid_slot_next = 0;
}

void solid_parts_move(Solid *solid) {
    s32 state = solid->state;
    s32 flag = (s16)solid->unk_20E;
    u32 mask = solid->part_mask;
    SolidPartMotion *part = (SolidPartMotion *)solid->parts;
    u32 bit;
    s32 x, y, z;

    if ((state & flag) == 1) {
        bit = 1;
        while (mask != 0) {
            if (mask & bit) {
                x = part->pos[0];
                y = part->pos[1];
                z = part->pos[2];
                x += part->vel[0];
                y += part->vel[1];
                z += part->vel[2];
                part->pos[0] = x;
                part->pos[1] = y;
                part->pos[2] = z;
                part->unk_0C[0] = 0;
                part->unk_0C[1] = 0;
                part->unk_0C[2] = 0;
                part->vel[0] = 0;
                part->vel[1] = 0;
                part->vel[2] = 0;
            }
            part++;
            mask >>= 1;
        }
        solid->unk_20E = 0;
    }
}

/* Scales the 2-vector pair for `bit` of record `idx` (following parent links
 * via rec[0]) by `scale` with GPF; writes 6 shorts to out. Returns 1 on success. */
s32 rec_bit_pair_scale(s32 idx, u32 bit, s32 scale, s16 *out) {
    s16 *rec = ptr_table[idx];
    s32 ret = 0;
    s16 *p;
    s32 mask;
    s32 bit_mask;
    s32 i = 0; /* dead store, needed for the match */
    u32 m;
    s32 a, b, c, d, e, f;

    if (rec != NULL && bit < 0x20) {
        mask = *(s32 *)(rec + 2);
        bit_mask = 1 << bit;
        if (mask & bit_mask) {
            if (rec[0] == 0) {
                rec += 4;
                m = 1;
                for (i = 0; i < (s32)bit; i++) {
                    if (mask & m) rec += 6;
                    m <<= 1;
                }
                a = rec[0];
                b = rec[1];
                c = rec[2];
                if (a != 0 && b != 0 && c != 0) {
                    gte_set(IR0, scale);
                    gte_set(IR1, a);
                    gte_set(IR2, b);
                    gte_set(IR3, c);
                    d = rec[3];
                    gte_nop();
                    gte_gpf12_b();
                    e = rec[4];
                    f = rec[5];
                    gte_get(MAC1, a);
                    gte_set(IR1, d);
                    gte_set(IR2, e);
                    gte_set(IR3, f);
                    gte_get(MAC2, b);
                    gte_get(MAC3, c);
                    gte_gpf12_b();
                    out[0] = a;
                    out[1] = b;
                    out[2] = c;
                    gte_get(MAC1, d);
                    gte_get(MAC2, e);
                    gte_get(MAC3, f);
                    ret = 1;
                    out[3] = d;
                    out[4] = e;
                    out[5] = f;
                }
                return ret;
            }
            p = rec + 4;
            m = 1;
            for (i = 0; i < (s32)bit; i++) {
                if (mask & m) p += 4;
                m <<= 1;
            }
            ret = rec_bit_pair_scale(idx + rec[0], bit, scale, out);
            if (ret == 1) {
                s32 x, y, z;
                x = p[0];
                y = p[1];
                z = p[2];
                gte_set(IR0, scale);
                gte_set(IR1, x);
                gte_set(IR2, y);
                gte_set(IR3, z);
                gte_gpf12();
                gte_get(MAC1, x);
                gte_get(MAC2, y);
                gte_get(MAC3, z);
                out[3] = x;
                out[4] = y;
                out[5] = z;
            }
        }
    }
    return ret;
}

/* Copies src's part records that part_mask marks in use into dst.
 * A goto loop: a C loop lets GCC's loop pass add pointers per word. */
void solid_copy(Solid *dst, Solid *src) {
    SolidPartWords *from = (SolidPartWords *)src->parts;
    u32 mask = src->part_mask;
    SolidPartWords *to = (SolidPartWords *)dst->parts;
    u32 bit = 1;

    dst->unk_20E = src->unk_20E;
    dst->part_mask = mask;
    dst->part_enable_mask = src->part_enable_mask;
    if (mask == 0) {
        return;
    }
next:
    if (mask & bit) {
        s32 w0 = from->w[0], w1 = from->w[1], w2 = from->w[2];
        s32 w3 = from->w[3], w4 = from->w[4], w5 = from->w[5];
        to->w[0] = w0; to->w[1] = w1; to->w[2] = w2;
        to->w[3] = w3; to->w[4] = w4; to->w[5] = w5;
    }
    to++;
    mask >>= 1;
    from++;
    if (mask != 0) {
        goto next;
    }
}

/*
 * Walks the node tree at node_pair_table. A leaf (index < 0x400) is handled by
 * rec_bit_pair_scale. An inner node evaluates both children into scratch, then blends
 * each child's two vectors with the node's left/right weights through the GTE
 * (gpf0/gpl0, 12-bit fixed point) into out[0..5].
 */
s32 node_tree_blend(s32 node_index, s32 arg1, s32 arg2, s16 *out) {
    NodePair *node;
    s16 *left_out;
    s16 *right_out;
    s32 ok = 0;
    s32 left_ok;
    s32 rx, ry, rz;
    s32 w_left, w_right;
    s32 vx, vy, vz;
    /* FLAG reads are discarded: the original's cfc2 writes $zero */
    register s32 gte_flag asm("$0");

    if (node_index >= 0x400) {
        left_out = (s16 *)scratch_top;
        scratch_top += 0x18;
        node = &node_pair_table[node_index];
        right_out = left_out + 6;
        left_ok = node_tree_blend(node->left, arg1, arg2, left_out);
        if (left_ok == 1 && node_tree_blend(node->right, arg1, arg2, right_out) == left_ok) {
            w_left = node->left_weight;
            w_right = node->right_weight;
            vx = left_out[0]; vy = left_out[1]; vz = left_out[2];
            gte_set(IR0, w_left);
            gte_set(IR1, vx);
            gte_set(IR2, vy);
            gte_set(IR3, vz);
            gte_gpf0();
            vx = right_out[0]; vy = right_out[1]; vz = right_out[2];
            gte_get_ctrl(FLAG, gte_flag);
            gte_set(IR0, w_right);
            gte_set(IR1, vx);
            gte_set(IR2, vy);
            gte_set(IR3, vz);
            gte_gpl0();
            gte_get(MAC1, rx);
            gte_get(MAC2, ry);
            gte_get(MAC3, rz);
            rx >>= 12;
            ry >>= 12;
            rz >>= 12;
            out[0] = rx;
            out[1] = ry;
            out[2] = rz;
            vx = left_out[3]; vy = left_out[4]; vz = left_out[5];
            gte_set(IR0, w_left);
            gte_set(IR1, vx);
            gte_set(IR2, vy);
            gte_set(IR3, vz);
            gte_gpf0();
            vx = right_out[3]; vy = right_out[4]; vz = right_out[5];
            gte_get_ctrl(FLAG, gte_flag);
            gte_set(IR0, w_right);
            gte_set(IR1, vx);
            gte_set(IR2, vy);
            gte_set(IR3, vz);
            gte_gpl0();
            gte_get(MAC1, rx);
            gte_get(MAC2, ry);
            gte_get(MAC3, rz);
            rx >>= 12;
            ry >>= 12;
            rz >>= 12;
            ok = 1;
            out[3] = rx;
            out[4] = ry;
            out[5] = rz;
        }
        scratch_top -= 0x18;
    } else {
        ok = rec_bit_pair_scale(node_index, arg1, arg2, out);
    }
    return ok;
}

/* Returns word +4 of the entry in ptr_table[index], or 0 if the slot is empty. */
s32 ptr_table_get_word1(s32 index) {
    s32 *entry = ptr_table[index];
    s32 value = 0;

    if (entry != NULL) {
        value = entry[1];
    }
    return value;
}

s32 node_tree_eval(s32 node) {
    NodePair *pair;
    s32 left;
    s32 result;

    if (node >= 0x400) {
        pair = &node_pair_table[node];
        left = node_tree_eval(pair->left);
        result = left & node_tree_eval(pair->right);
    } else {
        result = ptr_table_get_word1(node);
    }
    return result;
}

/* Calls solid_parts_update(solid, parent) on the scratchpad stack and returns its result: the old $sp is saved
 * there and restored after. The original is hand-written asm: the asm keeps the old $sp in $at
 * and sets up the frame by hand (FINDINGS "$sp in C"). */
s32 solid_parts_update_scratch(Solid *solid, s32 *parent) {
    s32 result;
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    result = solid_parts_update(solid, parent);
    SCRATCH_STACK_LEAVE_BELOW();
    return result;
}

static inline void rotate_svectors(SVECTOR *dst, SVECTOR *src, s32 count) {
    SVECTOR *end;
    s32 xy, z, mac2;

    gte_load(VXY0, src, 0);
    gte_load(VZ0, src, 4);
    src++;
    end = dst + count - 1;
    gte_rtv0_b();
    while (dst != end) {
        xy = *(s32 *)&src->vx;
        z = *(s32 *)&src->vz;
        src++;
        gte_store(MAC1, dst, 0);
        gte_get(MAC2, mac2);
        gte_set(VZ0, z);
        gte_set(VXY0, xy);
        gte_store(MAC3, dst, 4);
        dst->vy = mac2;
        gte_rtv0_b();
        dst++;
    }
    gte_store(MAC1, dst, 0);
    gte_get(MAC2, mac2);
    gte_store(MAC3, dst, 4);
    dst->vy = mac2;
}
/* Updates the solid's parts once per frame: for each part in node_tree_eval's mask, rotates its blended box
 * (center and half-size from node_tree_blend, by box[i] angles and the parent matrix) and stores the box's
 * axis-aligned extent, center and their changes in the MovingBox records at unk_218.
 * Returns the parts in use and enabled (part_mask & unk_214). */
s32 solid_parts_update(Solid *solid, s32 *parent) {
    s32 *rot;
    SVECTOR *verts;
    s16 *blend;
    SVECTOR *center;
    SVECTOR *corner;
    register SVECTOR *v asm("$18");
    u32 mask;
    s32 i;
    s32 done;
    MovingBox *part;
    SVECTOR *angle;
    s32 x, y, z, t;

    if (solid->state == 1 && (s16)solid->unk_20E == 0) {
        rot = scratch_alloc(0x54);
        verts = (SVECTOR *)(rot + 8);
        blend = (s16 *)(verts + 5);
        i = 0;
        done = 0;
        part = (MovingBox *)solid->parts;
        mask = node_tree_eval(solid->node_root);
        solid->part_mask = mask;
        for (; mask != 0; mask >>= 1, i++, part++) {
            SVECTOR *ofs;

            if (!(mask & 1)) {
                continue;
            }
            if (node_tree_blend(solid->node_root, i, solid->unk_006, blend) != 1) {
                continue;
            }
            v = verts;
            center = v + 1;
            corner = v + 2;
            ofs = &solid->box_b[i];
            if (done == 0 || solid->unk_20C == 0) {
                angle = &solid->box[i];
                rot_matrix(rot, angle->vy, angle->vx, angle->vz);
                if (parent) {
                    mul_matrix(parent, rot, rot);
                }
                rot_load(rot);
                done = 1;
            }
            x = blend[3];
            y = blend[4];
            z = blend[5];
            x += ofs->vx;
            y += ofs->vy;
            z += ofs->vz;
            center->vx = x;
            center->vz = z;
            center->vy = y;
            x = blend[0];
            y = blend[1];
            z = blend[2];
            v[0].vx = x;
            v[0].vy = y;
            v[0].vz = z;
            corner[0].vx = -x;
            corner[0].vy = y;
            corner[0].vz = z;
            corner[1].vx = x;
            corner[1].vy = -y;
            corner[1].vz = z;
            corner[2].vx = x;
            corner[2].vy = y;
            corner[2].vz = -z;
            rotate_svectors(verts, verts, 5);
            x = ABS(v[0].vx); t = ABS(corner[0].vx); if (x < t) x = t;
            y = ABS(v[0].vy); t = ABS(corner[0].vy); if (y < t) y = t;
            z = ABS(v[0].vz); t = ABS(corner[0].vz); if (z < t) z = t;
            t = ABS(corner[1].vx); if (x < t) x = t;
            t = ABS(corner[1].vy); if (y < t) y = t;
            t = ABS(corner[1].vz); if (z < t) z = t;
            t = ABS(corner[2].vx); if (x < t) x = t;
            t = ABS(corner[2].vy); if (y < t) y = t;
            t = ABS(corner[2].vz); if (z < t) z = t;
            if (part->size[0] == 0) {
                part->size[0] = x;
                part->size[1] = y;
                part->size[2] = z;
            } else {
                part->offset_delta[0] = center->vx - part->offset[0];
                part->offset_delta[1] = center->vy - part->offset[1];
                part->offset_delta[2] = center->vz - part->offset[2];
                part->size_delta[0] = x - part->size[0];
                part->size_delta[1] = y - part->size[1];
                part->size_delta[2] = z - part->size[2];
            }
            part->offset[0] = center->vx;
            part->offset[1] = center->vy;
            part->offset[2] = center->vz;
        }
        solid->unk_20E = 1;
        scratch_top -= 0x54;
    }
    return solid->part_mask & solid->part_enable_mask;
}

s32 clip_outcode(s16 *rect, s32 x, s32 y)
{
    s32 code;
    s32 lo, hi;

    lo = rect[0];
    hi = rect[2];
    lo = lo - x;
    hi = x - hi;
    code = lo > 0;
    if (hi > 0) {
        code |= 2;
    }
    lo = rect[1];
    hi = rect[3];
    lo = lo - y;
    hi = y - hi;
    if (lo > 0) {
        code |= 4;
    }
    if (hi > 0) {
        code |= 8;
    }
    return code;
}

/* (w - y0) * (x - x0) / (y - y0) + x0, the product taken in the GTE (gpf 0), with the divide done in
 * the CPU; the nop after mfc2 is its load delay slot. */
s32 segment_x_at_y(s32 x, s32 y, s32 x0, s32 y0, s32 w) {
    s32 mac1;
    x = x - x0;
    gte_set(IR0, w - y0);
    gte_set(IR1, x);
    y = y - y0;
    gte_nop();
    gte_gpf0_b();
    gte_get(MAC1, mac1);
    mips_nop(); /* mfc2 load delay */
    return mac1 / y + x0;
}

/* (w - x0) * (y - y0) / (x - x0) + y0: segment_x_at_y with the axes swapped. */
s32 segment_y_at_x(s32 x, s32 y, s32 x0, s32 y0, s32 w) {
    s32 mac1;
    y = y - y0;
    gte_set(IR0, w - x0);
    gte_set(IR1, y);
    x = x - x0;
    gte_nop();
    gte_gpf0_b();
    gte_get(MAC1, mac1);
    mips_nop(); /* mfc2 load delay */
    return mac1 / x + y0;
}

/* Cohen-Sutherland clip of a segment (x0,y0)-(x1,y1) to a rect (left,top,right,bottom).
   Returns 1 if the segment is entirely inside after clipping, else 0. */
s32 clip_segment_rect(s16 *rect, s16 *seg) {
    s32 result = 0;
    s32 x0, y0, x1, y1;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    s32 c0;
    s32 c1;
    s32 code;
    s32 v;

    left = rect[0];
    top = rect[1];
    right = rect[2];
    bottom = rect[3];
    x0 = seg[0];
    y0 = seg[1];
    x1 = seg[2];
    y1 = seg[3];
    c0 = clip_outcode(rect, x0, y0);
    c1 = clip_outcode(rect, x1, y1);
    while (!(c0 & c1) && (c0 || c1)) {
        code = c0 | c1;
        if (code & 1) {
            v = segment_y_at_x(x0, y0, x1, y1, left);
            if (c0 & 1) {
                y0 = v;
                x0 = left;
            } else {
                y1 = v;
                x1 = left;
            }
        } else if (code & 2) {
            v = segment_y_at_x(x0, y0, x1, y1, right);
            if (c0 & 2) {
                y0 = v;
                x0 = right;
            } else {
                y1 = v;
                x1 = right;
            }
        } else if (code & 4) {
            v = segment_x_at_y(x0, y0, x1, y1, top);
            if (c0 & 4) {
                x0 = v;
                y0 = top;
            } else {
                x1 = v;
                y1 = top;
            }
        } else if (code & 8) {
            v = segment_x_at_y(x0, y0, x1, y1, bottom);
            if (c0 & 8) {
                x0 = v;
                y0 = bottom;
            } else {
                x1 = v;
                y1 = bottom;
            }
        }
        c0 = clip_outcode(rect, x0, y0);
        c1 = clip_outcode(rect, x1, y1);
    }
    if (c0 == 0 && c1 == 0) {
        result = 1;
    }
    return result;
}

/* Clips the segment pos -> pos + dir (or 0 -> pos) against box's rectangle. */
s32 box_segment_hit_xz(s16 *box, s16 *pos, s16 *dir) {
    s16 *seg = scratch_alloc(0x10);
    s16 *rect = seg + 4;
    s32 z = pos[2];
    s32 x = pos[0];
    s32 cz, cx;
    s32 hit;

    if (dir == NULL) {
        seg[0] = 0;
        seg[1] = 0;
        seg[2] = z;
        seg[3] = x;
    } else {
        cz = dir[2];
        cx = dir[0];
        seg[2] = cz + z;
        seg[0] = cz;
        seg[1] = cx;
        seg[3] = cx + x;
    }
    z = box[2];
    x = box[0];
    cz = box[5];
    cx = box[3];
    rect[0] = cz - z;
    rect[1] = cx - x;
    rect[2] = cz + z;
    rect[3] = cx + x;
    hit = clip_segment_rect(rect, seg);
    scratch_top -= 0x10;
    return hit;
}

s32 box_segment_hit_yz(s16 *box, s16 *p, s16 *q) {
    s16 *seg;
    s16 *rect;
    s32 w, h;
    s32 x, y;
    s32 ret;

    seg = scratch_alloc(0x10);
    w = p[1];
    h = p[2];
    rect = seg + 4;
    if (q == NULL) {
        seg[0] = 0;
        seg[1] = 0;
        seg[2] = w;
        seg[3] = h;
    } else {
        x = q[1];
        y = q[2];
        seg[2] = x + w;
        seg[0] = x;
        seg[1] = y;
        seg[3] = y + h;
    }
    w = box[1];
    h = box[2];
    x = box[4];
    y = box[5];
    rect[0] = x - w;
    rect[1] = y - h;
    rect[2] = x + w;
    rect[3] = y + h;
    ret = clip_segment_rect(rect, seg);
    scratch_top -= 0x10;
    return ret;
}

/* Builds four axis vectors (+-r on x and y) and rotates each in place by the matrix. */
s32 axis_vectors_rotate(s32 r, s32 *w, Vec8 *v) {
    Vec8Words *p;
    Vec8 *end;
    s32 mac2;
    s32 a, b;
    register s32 c0 asm("$3");
    register s32 c1 asm("$4");
    register s32 c2 asm("$2");
    s16 nr = -r;

    v[0].vx = r;
    v[0].vy = 0;
    v[0].vz = 0;
    v[1].vx = nr;
    v[1].vy = 0;
    v[1].vz = 0;
    v[2].vx = 0;
    v[2].vy = r;
    v[2].vz = 0;
    v[3].vx = 0;
    v[3].vy = -r;
    v[3].vz = 0;
    c0 = w[0];
    c1 = w[1];
    c2 = w[2];
    gte_set_ctrl(R11R12, c0);
    gte_set_ctrl(R13R21, c1);
    gte_set_ctrl(R22R23, c2);
    c0 = w[3];
    c1 = w[4];
    gte_set_ctrl(R31R32, c0);
    gte_set_ctrl(R33, c1);
    p = (Vec8Words *)v;
    __asm__("" : "=r"(p) : "0"(p));
    gte_ldv0(p);
    p = (Vec8Words *)(v + 1);
    end = v + 3;
    gte_rtv0_b();
    while (v != end) {
        a = p->xy;
        b = p->z;
        p++;
        gte_store(MAC1, v, 0);
        gte_get(MAC2, mac2);
        gte_set(VZ0, b);
        gte_set(VXY0, a);
        gte_store(MAC3, v, 4);
        v->vy = mac2;
        gte_rtv0_b();
        v++;
    }
    gte_store(MAC1, v, 0);
    gte_get(MAC2, mac2);
    gte_store(MAC3, v, 4);
    *(volatile s16 *)&v->vy = mac2;
}

static inline void sweep_set_light(s32 *m) {
    register s32 c0 asm("$3");
    register s32 c1 asm("$4");
    register s32 c2 asm("$2");

    c0 = m[0];
    c1 = m[1];
    c2 = m[2];
    gte_set_ctrl(L11L12, c0);
    gte_set_ctrl(L13L21, c1);
    gte_set_ctrl(L22L23, c2);
    c0 = m[3];
    c1 = m[4];
    gte_set_ctrl(L31L32, c0);
    gte_set_ctrl(L33, c1);
}
static inline void sweep_rotate(SVECTOR *v) {
    register SVECTOR *p asm("$2") = v;
    s32 vy;

    __asm__("" : "=r"(p) : "0"(p));
    __asm__("" : "=r"(v) : "0"(v));
    gte_ldv0(p);
    gte_rtv0();
    gte_store(MAC1, v, 0);
    gte_get(MAC2, vy);
    gte_store(MAC3, v, 4);
    v->vy = vy;
}
s32 trace_solids_masked(s32 *pos, s32 *target, s32 radius, s32 *out, u16 *out_id, u32 mask) {
    s32 yaw, pitch;
    s32 result = 0;
    SweepScratch *s;
    SVECTOR *rel;
    SVECTOR *dir;
    SVECTOR *ext;
    Vec8 *axes;
    SVECTOR *wrel;
    SVECTOR *seg;
    MovingBox *box;
    s32 i;
    Solid *solid;
    Collider *owner;
    s32 x, y, z; /* x is reused as the part's hit flag */
    s32 r;
    MovingBox *part;
    s32 n;
    s32 parts;
    s32 rest;
    s32 hit_part;
    s32 nz, nx;
    s32 inside;
    s32 top;
    s32 turn_yaw, turn_pitch;
    s32 mac1, mac2, mac3;
    const SolidPartWords *src;

    if (solid_count > 0) {
        s = scratch_alloc(sizeof(SweepScratch));
        s->ext.vx = radius;
        s->ext.vy = radius;
        s->ext.vz = radius;
        s->dir.vx = s->seg.vx = target[0] - pos[0];
        yaw = 0;
        pitch = 0;
        s->dir.vy = s->seg.vy = target[1] - pos[1];
        s->dir.vz = s->seg.vz = target[2] - pos[2];
        vector_to_angles(s->dir.vx, s->dir.vy, s->dir.vz, &yaw, &pitch);
        rot_matrix(s->m_world, yaw, pitch, 0);
        axes = s->axes;
        axis_vectors_rotate(radius, s->m_world, axes);
        vector_to_angles(s->dir.vx, s->dir.vy, s->dir.vz, &yaw, &pitch);
        turn_yaw = yaw;
        turn_pitch = pitch;
        rot_matrix_b(s->m_local, -turn_yaw, turn_pitch - 0x400, 0);
        rot_matrix(s->m_world, turn_yaw, 0x400 - turn_pitch, 0);
        rel = &s->rel;
        dir = &s->dir;
        ext = &s->ext;
        wrel = &s->wrel;
        seg = &s->seg;
        box = &s->box;
        gte_load_R(s->m_local);
        sweep_rotate(dir);
        sweep_set_light(s->m_local);
        gte_load_LC(s->m_world);
        *(VECTOR *)out = *(VECTOR *)target;
        for (i = solid_count - 1; i >= 0; i--) {
            solid = &solids[((u8 *)&solid_index)[i]];
            if (solid->state != 1) {
                continue;
            }
            owner = (Collider *)solid->owner;
            if (owner == NULL || (((u8 *)&owner->x0)[1] & (u16)collide_mode)) {
                continue;
            }
            x = owner->sub[0] >> 12;
            y = owner->sub[1] >> 12;
            z = owner->sub[2] >> 12;
            rel->vx = wrel->vx = x - pos[0];
            rel->vy = wrel->vy = y - pos[1];
            rel->vz = wrel->vz = z - pos[2];
            gte_ldv0(rel);
            r = solid->radius;
            gte_nop();
            gte_llv0_b();
            gte_get(MAC1, x);
            gte_get_wait(MAC2, y);
            gte_get(MAC3, z);
            if (y - r >= dir->vy || y + r <= 0) {
                continue;
            }
            if ((u32)(z + r + radius) > (u32)((r + radius) * 2)
                || (u32)(x + r + radius) > (u32)((r + radius) * 2)) {
                continue;
            }
            part = (MovingBox *)solid->parts;
            rest = -1;
            n = 0;
            hit_part = -1;
            solid_parts_update_scratch(solid, 0);
            solid_copy(&solid_backup, solid);
            {
                SolidPartWords *p = (SolidPartWords *)part;
                u32 bit;

                r = solid->part_mask;
                bit = 1;
                if (r != 0) {
                clear:
                    if (r & bit) {
                        p->w[0] = 0;
                        p->w[1] = 0;
                        p->w[2] = 0;
                        p->w[3] = 0;
                        p->w[4] = 0;
                        p->w[5] = 0;
                    }
                    r = (u32)r >> 1;
                    p++;
                    if (r != 0) {
                        goto clear;
                    }
                }
            }
            solid->unk_20E = 0;
            parts = solid_parts_update_scratch(solid, s) & mask;
            if (parts & rest) {
                nx = -x;
                nz = -z;
                do {
                    if (parts & (u32)(1 << n)) {
                        inside = 1;
                        if (!in_range(nz, part->offset[2], part->size[2] + part->size_delta[2] + ext->vz - 1)
                            || !in_range(nx, part->offset[0], part->size[0] + part->size_delta[0] + ext->vx - 1)) {
                            inside = 0;
                        }
                        if (inside == 1) {
                            top = y + part->offset[1];
                            if (top - part->size[1] <= dir->vy && top + part->size[1] >= 0) {
                                src = (const SolidPartWords *)solid_backup.parts;
                                src += n;
                                ((SolidPartWords *)box)->w[0] = src->w[0];
                                ((SolidPartWords *)box)->w[1] = src->w[1];
                                ((SolidPartWords *)box)->w[2] = src->w[2];
                                ((SolidPartWords *)box)->w[3] = src->w[3];
                                ((SolidPartWords *)box)->w[4] = src->w[4];
                                ((SolidPartWords *)box)->w[5] = src->w[5];
                                do { /* a loop note: keeps x = 0 below the stores (FINDINGS "sched2's hazard tie-break") */
                                } while (0);
                                x = 0;
                                box->offset[0] += wrel->vx;
                                box->offset[1] += wrel->vy;
                                box->offset[2] += wrel->vz;
                                if ((box_segment_hit_xz((s16 *)box, (s16 *)seg, NULL) == 1
                                     && box_segment_hit_yz((s16 *)box, (s16 *)seg, NULL) == 1)
                                    || ((box_segment_hit_xz((s16 *)box, (s16 *)seg, (s16 *)&axes[0]) == 1
                                         || box_segment_hit_xz((s16 *)box, (s16 *)seg, (s16 *)&axes[1]) == 1)
                                        && (box_segment_hit_yz((s16 *)box, (s16 *)seg, (s16 *)&axes[2]) == 1
                                            || box_segment_hit_yz((s16 *)box, (s16 *)seg, (s16 *)&axes[3]) == 1))) {
                                    x = 1;
                                }
                                if (x == 1) {
                                    dir->vy = MAX(top - part->size[1], 0);
                                    hit_part = n;
                                }
                            }
                        }
                    }
                    part++;
                    n++;
                } while (parts & (rest <<= 1));
            }
            solid_copy(solid, &solid_backup);
            if (hit_part >= 0) {
                dir->vx = 0;
                dir->vz = 0;
                gte_ldv0(dir);
                out[3] = hit_part;
                gte_lcv0_b();
                *out_id = owner->x0;
                result = 1;
                gte_get(MAC1, mac1);
                gte_get(MAC2, mac2);
                gte_get(MAC3, mac3);
                mac1 += pos[0];
                mac2 += pos[1];
                mac3 += pos[2];
                out[0] = mac1;
                out[1] = mac2;
                out[2] = mac3;
            }
        }
        scratch_top -= sizeof(SweepScratch);
    }
    return result;
}

/* Forwards the five arguments to trace_solids_masked with -1 as the sixth; 1 when it hit an object (its id in *target). */
s32 trace_objects(void *from, void *hit, s32 flags, void *to, s16 *target) {
    return trace_solids_masked(from, hit, flags, to, target, -1);
}

void obj_clear_block54(void *sub) {
    volatile s32 *p = sub;
    s32 i;
    s32 k;
    register s32 n asm("a1");

    for (i = 5; i > 0; i--) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p += 4;
    }
    __asm__("" : "=r"(n) : "0"(3));
    k = n & 0x15;
    __asm__("" :: "r"(n));
    for (; k > 0; k--) {
        *p++ = 0;
    }
    ((ClearBlock54 *)sub)->flags = 0;
}

void collider_begin(Collider *coll) {
    s32 w;
    s32 dx, dy, dz;
    s32 h, d;

    if (coll->state == 1) {
        w = coll->size[0];
        if (w != 0) {
            dx = coll->size_delta[0];
            dy = coll->size_delta[1];
            dz = coll->size_delta[2];
            coll->offset_delta[0] = 0;
            coll->offset_delta[1] = 0;
            coll->offset_delta[2] = 0;
            coll->size_delta[0] = 0;
            coll->size_delta[1] = 0;
            coll->size_delta[2] = 0;
            coll->size[0] = w + dx;
            h = coll->size[1];
            d = coll->size[2];
            coll->size[1] = h + dy;
            coll->size[2] = d + dz;
        }
        coll->contact = 0;
        coll->state = 0;
    }
}

s32 solid_part_mask(u32 index) {
    s32 result = 0;
    if (index < 32) {
        result = solid_parts_update_scratch(&solids[index], 0);
    }
    return result;
}

/* Writes part `part_index` of solid `solid_index` (its position in 20.12 world units) to out[0..2]
 * when the solid reports that part as present. Returns 1 when out was written. */
s32 solid_part_pos(u32 solid_index, u32 part_index, s32 *out) {
    Solid *solid;
    SolidFrame *frame;
    SolidPart *part;
    s32 parts;
    s32 found;
    s32 bit;

    found = 0;
    if (solid_index < 0x20 && part_index < 0x20) {
        solid = &solids[solid_index];
        frame = *(SolidFrame **) ((u8 *) solid + 8);
        part = (SolidPart *) ((u8 *) solid + 0x218 + part_index * 0x18);
        parts = solid_parts_update_scratch(solid, 0);
        if (frame != NULL) {
            bit = 1 << part_index;
            if (parts & bit) {
                if (part->active != 0) {
                    found = 1;
                    out[0] = (frame->pos[0] >> 12) + part->off[0];
                    out[1] = (frame->pos[1] >> 12) + part->off[1];
                    out[2] = (frame->pos[2] >> 12) + part->off[2];
                }
            }
        }
    }
    return found;
}

/*
 * Looks up one part of a solid. Returns 1 and copies the part's three s16
 * values to out when the solid is in use, the part's bit is set in the mask
 * from solid_parts_update_scratch, and the part's first s16 is nonzero. Otherwise returns 0.
 */
s32 solid_part_offset(u32 solid_idx, u32 part_idx, s16 *out) {
    s32 found = 0;

    if (solid_idx < 0x20 && part_idx < 0x20) {
        Solid *solid = &solids[solid_idx];
        s32 *in_use = solid->owner;
        s16 *part = (s16 *)&((SolidPart *)solid->parts)[part_idx];
        s32 mask = solid_parts_update_scratch(solid, 0);

        if (in_use != 0) {
            s32 bit = 1 << part_idx;
            if (mask & bit) {
                s32 x = part[0];
                if (x != 0) {
                    s32 y = part[1];
                    s32 z = part[2];
                    found = 1;
                    out[0] = x;
                    out[1] = y;
                    out[2] = z;
                }
            }
        }
    }
    return found;
}

s32 solid_part_box(u32 solid, u32 part, s32 *pos_out, s16 *box_out) {
    s32 hit = 0;
    Solid *s;
    SolidPartBox *p;
    s32 *owner;
    s32 parts, mask;
    s32 w, h, d;

    if (solid < 0x20 && part < 0x20) {
        s = &solids[solid];
        owner = s->owner;
        p = (SolidPartBox *)(s->parts + part * 0x18);
        parts = solid_parts_update_scratch(s, 0);
        if (owner != 0 && (parts & (mask = 1 << part))) {
            w = p->size[0];
            if (w != 0) {
                hit = 1;
                h = p->size[1];
                d = p->size[2];
                pos_out[0] = (owner[7] >> 12) + p->off[0];
                pos_out[1] = (owner[8] >> 12) + p->off[1];
                pos_out[2] = (owner[9] >> 12) + p->off[2];
                box_out[0] = w;
                box_out[1] = h;
                box_out[2] = d;
            }
        }
    }
    return hit;
}

/* Clears the four bytes at +8 (phase_slot), last to first; returns obj. */
Object *obj_clear_phase_slots(Object *obj) {
    s32 count = 3;
    u8 *p = (u8 *)obj + 3;
    do {
        p[8] = 0;
        count--;
        p--;
    } while (count >= 0);
    return obj;
}

/* Points phase slot `phase` at a handler record inside the object (as a word index). */
void obj_set_handler(Object *obj, s32 phase, ObjHandler *handler) {
    obj->phase_slot[phase] = (u32)((u8 *)handler - (u8 *)obj) >> 2;
}

/* Links node after pos (pos -> node -> the old successor) and returns node. */
Node *list_insert_after(Node *pos, Node *node) {
    Node *next = pos->next;

    pos->next = node;
    node->prev = pos;
    node->next = next;
    next->prev = node;
    return node;
}

Node *list_insert_before(Node *pos, Node *node) {
    Node *prev = pos->prev;

    pos->prev = node;
    node->next = pos;
    node->prev = prev;
    prev->next = node;
    return node;
}

Node *list_remove(Node *node) {
    Node *prev = node->prev;
    Node *next = node->next;

    prev->next = next;
    next->prev = prev;
    return node;
}

/* An empty list between two sentinel nodes. */
void list_init(Node *head, Node *tail) {
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
}

/* Runs phase `phase` for every object in the list headed by *head (the sentinel is skipped): each
 * object's handler for the phase runs when its function word is negative, then actor_hook runs if the
 * object is still the cursor. obj_list_cursor tracks the node so that obj_free can step it back. */
void obj_list_run(Node **head, s32 phase) {
    Node *first;
    Node *node;
    ObjHandler *handler;
    s32 slot;

    first = *head;
    obj_list_cursor = first;
    if (first->next != NULL) {
        do {
            node = obj_list_cursor;
            slot = ((Object *)node)->phase_slot[phase];
            if (slot != 0) {
                handler = (ObjHandler *)((u8 *)node + slot * 4);
                if ((s32)handler->fn < 0) {
                    handler->fn((Object *)node, handler);
                }
                if (node == obj_list_cursor && actor_hook != NULL) {
                    ((void (*)(Node *, ObjHandler *))actor_hook)(node, handler);
                }
            }
            obj_list_cursor = obj_list_cursor->next;
        } while (obj_list_cursor->next != NULL);
    }
    obj_list_cursor = NULL;
}

void hit_ext_flag_set(s32 value) {
    hit_ext_flag = value;
}

s32 hit_ext_flag_get(void) {
    return hit_ext_flag;
}

void obj_system_init(void) {
    obj_hits_reset_all();
    obj_pool_init();
    grid_active_set(1);
    obj_new();
    pair_set_a(2, 0x400);
    hit_ext_flag = 0;
}

void placement_list_pop(ListRecord *rec) {
    s32 first = rec->first;
    s32 second = rec->second;

    *(ListBlock *)rec = *(ListBlock *)((u8 *)rec + 0x20);
    rec->first = first;
    rec->second = second;
}

/* Keeps placement's whole-unit position from obj and stores obj's pitch, yaw, roll in the low 12 bits. */
void placement_snap_to_obj(Placement *placement, Object *obj)
{
    s32 x = obj->x;
    s32 y = obj->y;
    s32 z = obj->z;
    s32 pitch, yaw, roll;

    placement->x = ((x >> 12) << 12) + (placement->x & 0xFFF);
    placement->y = ((y >> 12) << 12) + (placement->y & 0xFFF);
    placement->z = ((z >> 12) << 12) + (placement->z & 0xFFF);
    pitch = obj->pitch;
    placement->x = ((placement->x >> 12) << 12) + (pitch & 0xFFF);
    yaw = obj->yaw;
    placement->y = ((placement->y >> 12) << 12) + (yaw & 0xFFF);
    roll = obj->roll;
    placement->unk_06 = 0;
    placement->z = ((placement->z >> 12) << 12) + (roll & 0xFFF);
}

/* Sets an object's hit-reaction flags (unk_1CA is the low byte of `mode`) and clears its sub-record at
 * 0x2C: mode bit 7 turns on bit 6, bit 6 bit 5, and without bit 4 bits 4-8 are cleared. */
void obj_set_hit_mode(Object *obj, s32 mode) {
    s16 *part;
    s32 flags;

    obj->hit_mode = mode;
    flags = (s16)mode;
    part = obj->rot_angles;
    if (flags & 0x10) {
        if (flags & 0x80) {
            flags |= 0x40;
        }
        if (flags & 0x40) {
            flags |= 0x20;
        }
    } else {
        flags &= ~0x1F0;
    }
    *(s32 *)(part + 8) = flags;
    part[0] = 0;
    part[1] = 0;
    part[2] = 0;
    part[4] = 0;
    part[5] = 0;
    part[6] = 0;
    player_refresh_state_scratch(part, flags);
}

void obj_set_flags(Object *obj, s32 flags) {
    s16 mask;

    mask = (flags & 0x10) == 0 ? 0x10 : 0;
    obj->flags = flags;
    if (flags & 0x80) {
        mask |= 8;
    } else {
        mask |= 2;
    }
    if (flags & 8) {
        mask |= 0x100;
    }
    if (flags & 0x400) {
        mask |= 0x200;
    }
    if (hit_ext_flag == 1) {
        mask |= 0x200;
    }
    obj_set_hit_mode(obj, mask);
}

void obj_init_from_place(Object *obj, Placement *place, s32 flags) {
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, -1);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj->health = place->health;
    obj->score = place->unk_16;
    obj->damage = place->unk_18;
    obj->unk_17B = place->unk_1A;
    obj->x = (place->x >> 12) << 12;
    obj->y = (place->y >> 12) << 12;
    obj->z = (place->z >> 12) << 12;
    obj->accel_y = 0x1000;
    obj->yaw = place->y & 0xFFF;
    obj->pitch = place->x & 0xFFF;
    obj->roll = place->z & 0xFFF;
    obj_set_flags(obj, flags);
    obj->placement = place;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

/* Sets the object's extents from a model part's box (model_part_extents_max) and its bounding radius. */
void obj_set_part_bounds(Object *obj, s32 part, s32 part_arg) {
    u16 ext[3];
    s32 unused[2];
    u16 depth;
    s32 span;
    s32 y;
    s16 y_copy;
    s16 span_copy;

    model_part_extents_max(part + ((s32 *)obj->asset)[1], part_arg, ext);
    obj->unk_190 = part_arg;
    obj->width = ext[0];
    obj->height = ext[1];
    obj->unk_1E8[0] = depth = ext[2];
    y = (s16)obj->height;
    span = (s16)depth;
    y_copy = y;
    if (span < obj->width) {
        span = obj->width;
    }
    span_copy = span;
    obj->extents[0] = span_copy;
    obj->extents[1] = y_copy;
    obj->extents[2] = span_copy;
    obj->bound_radius = isqrt(length_sq(span, y, span));
}

void obj_aim_step_at_player(Object *obj, s32 turn, s32 yaw_step, s32 pitch_step, s32 speed) {
    s32 yaw;
    s32 pitch;
    s32 vx;
    s32 vy;
    s32 vz;
    s32 *target;
    s32 height;

    target = player_position();
    height = (s16)obj->height;
    obj->target_yaw += turn;
    vector_to_angles(target[0] - (obj->x >> 12), target[1] - (obj->y >> 12) - height / 2,
                     target[2] - (obj->z >> 12), &yaw, &pitch);
    yaw = angle_approach(obj->yaw, yaw, yaw_step);
    pitch = angle_approach(obj->pitch, pitch, pitch_step);
    obj->pitch = pitch;
    obj->yaw = yaw;
    angles_to_vector(yaw, -pitch, speed, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
}

/* Adds the object's wobble (obj->unk_246, for unk_244 steps) to an angle; when it has run out and the
 * object is active, starts a new random wobble that lasts 0x80 steps. */
s16 obj_angle_wobble(Object *obj, s32 angle) {
    s32 count = obj->wobble_count;
    s32 result = angle;
    s32 active;

    if (count != 0) {
        result++; /* permuter: these two give the register allocation of the original */
        result--;
        obj->wobble_count = count - 1;
        result = angle + obj->wobble_offset;
    } else {
        active = obj->blocked_x;
        if (active == 0) {
            active = obj->blocked_z;
        }
        if (active != 0) {
            obj->wobble_count = 0x80;
            obj->wobble_offset = (rand_a_next() >> 1) - 0x400;
        }
    }
    return result;
}

/* Turns obj's yaw by at most `step` toward the player, or, while unk_242 counts down, toward its
 * target object (unk_FC; the direction is kept in unk_240 and only updated beyond 0x800 units).
 * unk_23E gets the yaw change. */
void obj_turn_toward_player(Object *obj, s32 step) {
    s32 *player;
    Placement *target;
    s32 dx;
    s32 dz;
    s32 angle;
    u16 old_yaw;
    s16 yaw;
    s32 turn;

    old_yaw = obj->yaw;
    if (obj->unk_242 == 0) {
        player = player_position();
        angle = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
    } else {
        target = obj->placement;
        dx = (target->x >> 12) - (obj->x >> 12);
        dz = (target->z >> 12) - (obj->z >> 12);
        if (length_sq(dx, 0, dz) > 0x400000) {
            obj->target_yaw = atan2(dz, dx);
        }
        angle = obj->target_yaw;
        obj->unk_242--;
    }
    yaw = angle_approach(obj->yaw, obj_angle_wobble(obj, (s16)angle), (s16)step);
    turn = yaw;
    turn -= old_yaw;
    obj->yaw = yaw;
    obj->turn = turn;
}

s32 obj_keyframe_value(Object *obj, s32 offset) {
    s32 from;
    s32 to;
    s32 steps;
    s32 index;
    s32 slot;
    register s32 base asm("$3");

    from = obj->type.unk_0C;
    to = obj->type.unk_0E;
    slot = model_slot_pchr(*(s32 *)obj->asset);
    base = slot;
    if (from == to) {
        return to + slot + offset;
    }
    offset += base;
    from += offset;
    to += offset;
    steps = obj->type.blend_duration;
    index = obj->type.unk_0A + 1;
    if (index == steps) {
        return from;
    }
    if (index != 0) {
        return pchr_blend(from, to, (index << 12) / steps, 0);
    }
    return to;
}

static inline void spark_add_list_rot(SparkList *list, s32 ry, s32 rx, s32 rz, s32 x, s32 y, s32 z, s32 value, s32 colour) {
    s32 n = spark_count;
    SparkRec *s;
    SparkList *head;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        head = list;
        __asm__("" : "=r"(head) : "0"(list));
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = head->tail[0];
        head->tail[0] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
void obj_draw_spark(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot;
    SVECTOR *dir;
    s32 value;
    s32 colour;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    rot = scratch_alloc(0x10);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    dir = (SVECTOR *)(rot + 4);
    dir->vx = obj->width;
    dir->vy = obj->height;
    dir->vz = obj->unk_1E8[0];
    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;

        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    spark_add_list_rot(&spark_list, rot[1], rot[0], rot[2], pos[0], pos[1], pos[2], value, colour);
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    aim_marker_draw(2, dir, (Vec3 *)pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}

/* Header of the asset a block object points to. */
typedef struct BlockAsset {
    s32 unk_00;
    s32 unk_04; /* added to the height base */
} BlockAsset;

/* Copies the object's rotation into its block (pitch negated), picks the
 * block's height between the type's two levels (offset by base plus the
 * asset's offset), adding a blended solid when they differ, then fills
 * and submits the block. */
void obj_block_lerp(Object *obj, s32 base) {
    s16 *from;
    s16 *frac;
    s16 start;
    s16 end;
    s16 res;
    s32 lo;
    s32 hi;
    s32 weight;
    s32 steps;
    u8 *block;
    s32 pitch;
    u16 yaw;
    u16 roll;
    BlockAsset *asset;
    s32 spare[2];

    asset = obj->asset;
    yaw = obj->yaw;
    roll = obj->roll;
    base += asset->unk_04;
    pitch = obj->pitch;
    *(u16 *)&obj->unk_A4[0x2E] = yaw;
    *(u16 *)&obj->unk_A4[0x30] = roll;
    *(s16 *)&obj->unk_A4[0x2C] = -pitch;
    lo = obj->type.unk_0C;
    start = lo + base;
    hi = obj->type.unk_0E;
    end = hi + base;
    block = obj->unk_A4;
    if (start == end || obj->type.blend_duration == (steps = obj->type.unk_0A + 1)) {
        do {
            res = start;
        } while (0);
    } else if (steps == 0) {
        res = end;
    } else {
        weight = (steps << 12) / obj->type.blend_duration;
        from = scratch_alloc(4);
        frac = scratch_alloc(4);
        frac[0] = weight;
        frac[1] = 0x1000 - weight;
        from[0] = start;
        from[1] = end;
        res = ((SolidAddFn)solid_add)(from, frac);
        scratch_top -= 8;
    }
    block[1] = 1;
    block[0] = obj->index;
    obj_block_fill(obj, block);
    solid_setup_scratch(obj->solid_id, block, res, obj->unk_190);
    fn_800FB460(obj, block);
}

/* Per-step hit handling: counts the hit cooldown down, applies this step's damage and records the hit. */
void obj_hit_update(Object *obj) {
    s16 damage;
    u8 cooldown;

    damage = obj_hit_damage(obj->index);
    cooldown = obj->hit_cooldown;
    if (cooldown != 0) {
        obj->hit_cooldown = cooldown + 0xFF;
    }
    if (damage > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->health -= damage;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
}

void obj_hit_handle(Object *obj, ObjHandler *handler) {
    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj_hit_update(obj);
    if (obj->health <= 0) {
        add_score(obj->score);
        if (obj->score != 0) {
            add_kill_count(1);
        }
        obj->score = 0;
        handler->state = 1;
        handler->request_flags = 8;
        return;
    }
    if (test_bit(obj->flags, 5)) {
        obj_block_lerp(obj, 0);
    }
}

/* Releases obj's placement and frees obj when the check passes; otherwise hands obj to obj_hit_handle. */
void obj_release_check(Object *obj, ObjHandler *handler) {
    Placement *placement;
    s32 use_alt;
    s32 flag_bits;
    s32 release;
    s32 x;
    s32 y;
    s32 z;

    use_alt = 0;
    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    /* placement byte 4, bit 2: selects the alternate check */
    if (obj->placement != NULL) {
        flag_bits = obj->placement->unk_00[4] & 4;
        use_alt = flag_bits != 0;
    }
    if (use_alt != 0) {
        release = cam_range_check_alt(x, y, z, obj->placement) == 0;
    } else {
        release = cam_range_check(x, y, z, obj->placement) == 0;
    }
    if (release != 0) {
        placement = obj->placement;
        placement_snap_to_obj(placement, obj);
        ((s16 *)placement->unk_00)[1] = 0;
        /* byte 4: clear bits 0-1, then set bit 1 (freed) */
        placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
        obj_free(obj);
        return;
    }
    obj_hit_handle(obj, handler);
}

/* Frees obj when it is outside the area cam_range_check_alt accepts (whole-unit position), otherwise obj_hit_handle. */
void obj_area_update(Object *obj, ObjHandler *handler) {
    Placement *place;

    if (cam_range_check_alt(obj->x >> 0xC, obj->y >> 0xC, obj->z >> 0xC) == 0) {
        place = obj->placement;
        *(s16 *)&place->unk_00[2] = -1;
        place->unk_00[4] |= 3;
        obj_free(obj);
    } else {
        obj_hit_handle(obj, handler);
    }
}

/* Runs the object's hook at 0x170 (if set) with the object as its argument; returns its result, else 0. */
s32 obj_call_hook(Object *obj) {
    s32 (*hook)(Object *) = (s32 (*)(Object *))obj->callback;
    s32 result = 0;
    if (hook != NULL) {
        result = hook(obj);
    }
    return result;
}

void obj_hook_or_free(Object *obj) {
    if (obj_call_hook(obj) == 0) {
        obj_free(obj);
    }
}

/* Runs the handler for each state in turn until the handler clears its flag (unk_10). */
void obj_run_states(Object *obj, ObjHandler *handler, ObjHandlerFn *table) {
    ObjHandlerFn fn;
    s32 state;

    do {
        state = handler->state;
        handler->request_flags = 0;
        fn = table[state];
        if (fn) {
            fn(obj, handler);
        }
    } while (handler->request_flags != 0);
}

void obj_run_states_default(Object *obj, ObjHandler *handler) {
    ObjHandlerFn fn;
    s32 state;

    do {
        state = handler->state;
        handler->request_flags = 0;
        fn = obj_state_handlers[state];
        if (fn) {
            fn(obj, handler);
        }
    } while (handler->request_flags != 0);
}

/* Runs the state's handler until one leaves unk_10 clear (a handler sets it to re-run the step). */
void obj_state_run(Object *obj, ObjHandler *handler) {
    void (*step)(Object *, ObjHandler *);

    do {
        handler->request_flags = 0;
        step = obj_state_steps[handler->state];
        if (step != NULL) {
            step(obj, handler);
        }
    } while (handler->request_flags != 0);
}

/* Runs the state's handler until one leaves unk_10 clear (a handler sets it to re-run the step). */
void obj_state_run_b(Object *obj, ObjHandler *handler) {
    void (*step)(Object *, ObjHandler *);

    do {
        handler->request_flags = 0;
        step = obj_state_steps_b[handler->state];
        if (step != NULL) {
            step(obj, handler);
        }
    } while (handler->request_flags != 0);
}

/* Steps a handler's coroutine script: applies a pending state change (unk_10 bit 8: at once; bit 1:
 * after unk_16 more calls), then runs the resume address of each queued entry of obj->state_table (8 bytes
 * each) until none is queued. */
void obj_script_step(Object *obj, ObjHandler *handler) {
    s32 changed;
    s32 left;
    s32 delay;
    s32 entry;
    StateEntry *entries, *e;
    s16 next;     /* s16: the copy keeps its own register and 8 bytes of frame */
    s32 unused[2];

restart:
    if (handler->request_flags & 8) {
        changed = 1;
    } else if (handler->request_flags & 1) {
        delay = handler->state_delay;
        delay--;
        if (delay >= 0) {
            changed = 0;
            handler->state_delay = delay;
        } else {
            changed = 1;
            obj->next_state = handler->pending_state;
        }
    } else {
        changed = obj->next_state != handler->state;
    }
    if (changed) {
        handler->state = obj->next_state;
        handler->queued_entry = -1;
        handler->request_flags = 0;
        handler->result = -2;
        obj_request_state(obj, handler, -1, -1);
        handler->next_entry = obj->next_state;
        obj_start_state_script(obj, handler, obj->next_state);
    } else if ((left = handler->result) >= 0) {
        if (--left == -1) {
            if (handler->queued_entry >= 0) {
                next = handler->queued_entry;
                handler->next_entry = next;
                handler->queued_entry = -1;
                handler->result = -1;
                goto run;
            }
        }
        handler->result = left;
        handler->next_entry = handler->entry_index;
    } else if (handler->next_entry < 0) {
        handler->next_entry = handler->entry_index;
    }
run:
    while (handler->next_entry >= 0) {
        entries = obj->state_table;
        entry = handler->next_entry;
        e = &entries[entry]; /* a pointer, not entries[entry].code: table + offset order */
        handler->resume = e->code;
        handler->entry_index = entry;
        handler->next_entry = -1;
        if (handler->resume != 0) {
            ((ObjHandlerFn)handler->resume)(obj, handler);
        }
        if ((handler->request_flags & 8) && handler->state_delay <= 0) {
            goto restart;
        }
    }
}

/* Asks an object to change to state `next`: dir 0 switches at once (handler mode 8), otherwise the
 * handler turns towards it in direction dir (mode 1 positive, 0 negative). */
void obj_request_state(Object *obj, ObjHandler *handler, s16 next, s16 dir) {
    if (obj->next_state != next) {
        handler->state_delay = dir;
        if (dir == 0) {
            handler->request_flags = 8;
            obj->next_state = next;
            return;
        }
        if (dir > 0) {
            handler->request_flags = 1;
            handler->pending_state = next;
        } else {
            handler->request_flags = 0;
            handler->pending_state = next;
        }
    }
}

void obj_start_state_script(Object *obj, ObjHandler *handler, s32 slot) {
    StateEntry *entry = obj->state_table + (s16)slot;

    if (entry != NULL && entry->index != -1) {
        if (entry->flag != 0) {
            script_start((Script *)obj, (s16 *)((s32 *)obj->type.data)[entry->index], (s32)obj->type.data);
            return;
        }
        script_jump((Script *)obj, (s16 *)((s32 *)obj->type.data)[entry->index], (s32)obj->type.data);
    }
}

/* Runs the script of obj->unk_1C: built-in opcodes -1..-13 (wait, counted and random jumps, state test,
   speed, next state, yaw changes, a jump on camera distance); an opcode >= 0 calls entry `op` of obj->call_table.
   K&R so the pass-through callers (handlers that call it with no arguments) still compile. */
void obj_link_script_run(obj, handler)
    Object *obj;
    ObjHandler *handler;
{
    s16 op;
    s32 slot;
    ScriptCallEntry *entry;
    ObjLink *link = &obj->script;

    if (link->unk_0C == OBJLINK_SCRIPT_WAIT) {
        if (link->unk_0E-- <= 0) {
            link->unk_0C = 0;
        } else {
            return;
        }
    }
    for (;;) {
        if (link->unk_0C == OBJLINK_SCRIPT_WAIT) {
            return;
        }
        op = *(link)->pc++;
        slot = op;
        switch (op) {
        case -1: {
            s32 n = *(link)->pc++;
            link->unk_0E = n - 1;
            if (n > 0) {
                link->unk_0C = OBJLINK_SCRIPT_WAIT;
                return;
            }
            break;
        }
        case -2:
            if (--link->unk_0A <= 0) {
                (link)->pc++;
                break;
            }
            /* fallthrough */
        case -3: {
            s32 target = *(link)->pc++;
            OBJLINK_JUMP(link, target);
            break;
        }
        case -4: {
            s32 chance = rand_a_next();
            s32 limit = *(link)->pc++;
            if (chance < limit) {
                s32 target = *(link)->pc++;
                OBJLINK_JUMP(link, target);
            } else {
                (link)->pc++;
            }
            break;
        }
        case -5:
            link->unk_0A = *(u16 *)(link)->pc++;
            break;
        case -6: {
            s32 r = rand_a_next();
            s32 mod = *(link)->pc++;
            s32 base = *(link)->pc++;
            link->unk_0A = r % mod + base;
            break;
        }
        case -7: {
            s32 state = *(link)->pc++;
            s32 target = *(link)->pc++;
            if (state >= 0 ? obj->next_state == state : obj->next_state != ~state) {
                OBJLINK_JUMP(link, target);
            }
            break;
        }
        case -8:
            obj->speed = *obj->script.pc++;
            break;
        case -9:
            obj->next_state = *(u16 *)obj->script.pc++;
            break;
        case -10: {
            s32 v = *obj->script.pc++;
            obj->unk_242 = v;
            if (v != 0) {
                s32 r;
                obj->target_yaw = rand_a_next();
                r = rand_a_next();
                obj->unk_242 = (r >> 4) / 2 + 0x80;
            }
            break;
        }
        case -11: {
            s32 dist = isqrt(length_sq((cam_pos >> 12) - (obj->x >> 12), (cam_pos_y >> 12) - (obj->y >> 12),
                                       (cam_pos_z >> 12) - (obj->z >> 12)));
            s32 range = *obj->script.pc++;
            s32 target = *obj->script.pc++;
            if (!(range < (s16)dist)) {
                OBJLINK_JUMP(&obj->script, target);
            }
            break;
        }
        case -12: {
            s32 r = rand_a_next();
            s32 step = *(link)->pc++;
            s32 yaw = obj->yaw;
            obj->yaw = (yaw + (step + r)) & 0xFFF;
            break;
        }
        case -13: {
            s32 span = *(link)->pc++;
            s32 turn = rand_a_next() % (span * 2) - span;
            s32 yaw = obj->yaw;
            obj->yaw = (yaw + turn) & 0xFFF;
            break;
        }
        case 0:
            break;
        default:
            if (slot < 0) {
                return;
            }
            entry = obj->call_table + slot;
            if (entry->fn != 0) {
                entry->fn(obj, handler);
            }
            break;
        }
    }
}

/* Clears every actor's index-keyed entry in the actor list: for each actor,
 * hit_target_masked is called with the actor's index and the field at 0x188 is zeroed. */
void obj_actors_clear_index(void) {
    Object *obj;

    obj = (Object *) *get_obj_list_actors();
    if (obj->node.next != NULL) {
        do {
            hit_target_masked(obj->index, 4, -1, 0x7FFF);
            obj->score = 0;
            obj = (Object *) obj->node.next;
        } while (obj->node.next != NULL);
    }
}

/* Clears an ObjLink record (16 bytes). */
void obj_link_clear(ObjLink *link) {
    link->data = NULL;
    link->pc = 0;
    link->blend_duration = 0;
    link->unk_0A = 0;
    link->unk_0C = 0;
    link->unk_0E = 0;
}

void obj_handler_clear(ObjHandler *handler) {
    handler->fn = NULL;
    handler->resume = 0;
    handler->entry_index = 0;
    handler->next_entry = -1;
    handler->queued_entry = -1;
    handler->request_flags = 0;
    handler->pending_state = -1;
    handler->unk_11 = 1;
    *(u8 *)&handler->fn = 0; /* the word, then its first byte again */
    handler->state = -1;
    handler->result = 0;
    handler->state_delay = 0;
    handler->turn_timer = 0;
    handler->timer = 0;
}

/* Puts an object's fields back to their initial state. */
void obj_reset(Object *obj) {
    s32 *p;
    s32 i;

    obj->hit_from = -1;
    obj->unk_1C6 = -1;
    obj->unk_17A = 0;
    obj->damage = 0;
    obj->health = 0;
    obj->score = 0;
    obj->flags = 0;
    obj->placement = NULL;
    obj->call_table = NULL;
    obj->state_table = NULL;
    obj->sounds = NULL;
    obj->unk_1A4 = 0;
    obj->unk_1A8 = 0;
    obj->hit = 0;
    obj->unk_1AE = 0;
    obj->blocked_z = 0;
    obj->blocked_x = 0;
    obj->blocked_y = 0;
    obj->unk_1B7 = 0;
    obj->unk_1C9 = 0;
    obj->hit_mode = 0;
    obj->unk_1B0 = 0;
    obj->unk_1B2 = 0;
    obj->unk_1B8 = 0;
    obj->unk_1BC = 0;
    obj->unk_1C0 = 0;
    obj->unk_1CB = 0;
    obj->unk_1DC = 0;
    obj->unk_1E0 = 0;
    obj->unk_1D0 = 0;
    obj->unk_1CC = 0;
    obj->hit_cooldown = 0;
    obj->hit_cooldown_max = 0;
    obj->width = 0;
    obj->height = 0;
    obj->unk_1E8[0] = 0;
    obj->unk_1E8[2] = 0;
    obj->unk_1E8[3] = 0;
    obj->unk_1E8[1] = 0;
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;
    obj->scale[0] = 0x1400;
    obj->scale[1] = 0x1400;
    obj->scale[2] = 0x1400;
    obj->vx = 0;
    obj->vy = 0;
    obj->vz = 0;
    obj->accel_x = 0;
    obj->accel_y = 0;
    obj->accel_z = 0;
    obj->yaw = 0;
    obj->pitch = 0;
    obj->roll = 0;
    obj->unk_226[0] = 0;
    obj->unk_226[1] = 0;
    obj->unk_226[2] = 0;
    obj->unk_226[3] = 0;
    obj->unk_226[4] = 0;
    obj->speed = 0;
    obj->speed_accel = 0;
    obj->move_delta[0] = 0;
    obj->move_delta[1] = 0;
    obj->move_delta[2] = 0;
    obj->turn = 0;
    obj->unk_17B = 0;
    obj->next_state = 0;
    obj->target_yaw = 0;
    obj->unk_242 = 0;
    obj->wobble_count = 0;
    obj->wobble_offset = 0;
    obj->serial = 0;
    obj->kind = 0;
    obj->unk_180 = 0;
    obj_handler_clear(&obj->handlers[0]);
    obj_handler_clear(&obj->handlers[1]);
    obj_handler_clear(&obj->handlers[2]);
    obj_handler_clear(&obj->handlers[3]);
    obj->callback = 0;
    obj->destructor = NULL;
    obj_link_clear(&obj->script);
    obj_link_clear(&obj->type);
    obj_clear_block54(obj->unk_A4);
    i = 15;
    p = &obj->vars.words[15];
    obj->solid_id = 0xFF;
    obj->free = 0;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
    obj->rot_angles[0] = 0;
    obj->rot_angles[1] = 0;
    obj->rot_angles[2] = 0;
    obj->unk_34[0] = 0;
    obj->unk_34[1] = 0;
    obj->unk_34[2] = 0;
    obj->ground_flags = 0;
    obj->unk_3C = 0;
    obj->extents[0] = 0;
    obj->extents[1] = 0;
    obj->extents[2] = 0;
    obj->unk_4C[0] = 0;
    obj->unk_4C[1] = 0;
    obj->unk_4C[2] = 0;
    obj->home_pos[0] = 0;
    obj->home_pos[1] = 0;
    obj->home_pos[2] = 0;
    obj->unk_6C[0] = 0;
    obj->unk_6C[1] = 0;
    obj->unk_6C[2] = 0;
    obj->unk_7C[0] = 0;
    obj->unk_7C[1] = 0;
    obj->unk_7C[2] = 0;
    obj->unk_84[0] = 0;
    obj->unk_84[1] = 0;
    obj->unk_84[2] = 0;
    obj->unk_94[0] = 0;
    obj->unk_94[1] = 0;
    obj->unk_94[2] = 0;
    obj->unk_190 = 0;
    obj->asset = NULL;
    obj->hit_type = 0;
    obj->script_flag = 0;
}

void obj_pool_init(void) {
    Object *obj = obj_pool;
    s16 i = 0;

    list_init(&obj_free_head, &obj_free_tail);
    list_init(&obj_list_actors, &obj_list_actors_tail);
    list_init(&obj_list_b, &obj_list_b_tail);
    list_init(&obj_list_c, &obj_list_c_tail);
    obj_free_count = OBJ_POOL_SIZE;
    do {
        obj_table[i] = obj;
        obj_set_handler(obj, 0, &obj->handlers[0]);
        obj_set_handler(obj, 1, &obj->handlers[1]);
        obj_set_handler(obj, 2, &obj->handlers[2]);
        obj_set_handler(obj, 3, &obj->handlers[3]);
        obj_reset(obj);
        obj->index = i;
        obj->rocket_marker = 0;
        list_insert_before(&obj_free_tail, &obj->node);
        obj++;
        i++;
    } while (i < OBJ_POOL_SIZE);
    obj_serial = 0;
    obj_pending_count = 0;
    obj_pending = NULL;
}

s32 *get_obj_list_actors(void) {
    return &obj_list_actors;
}

s32 *get_obj_list_actors_tail(void) {
    return &obj_list_actors_tail;
}

s32 *get_obj_list_b(void) {
    return &obj_list_b;
}

s32 *get_obj_list_b_tail(void) {
    return &obj_list_b_tail;
}

s32 *get_obj_list_c(void) {
    return &obj_list_c;
}

s32 *get_obj_list_c_tail(void) {
    return &obj_list_c_tail;
}

s16 get_obj_free_count(void) {
    return obj_free_count;
}

Object *obj_new(void) {
    Object *obj = NULL;

    if (obj_free_count > 0) {
        obj = (Object *)obj_free_head.next;
        while (obj->free == 1) {
            obj_flush_one();
        }
        list_remove(&obj->node);
        obj_free_count--;
        obj->serial = obj_serial++;
        obj->rocket_marker = 0;
        obj->unk_17A = 0;
    }
    return obj;
}

/* Walks the circular Node list headed by `head` and returns the first
   Object whose unk_17E equals `key`, or NULL. */
Object *obj_find_by_id(Node *head, s16 key) {
    Node *node;
    Object *obj;

    node = head->next;
    if (head != node) {
        do {
            obj = (Object *)node;
            if (node == NULL) {
                return NULL;
            }
            if (obj->kind == key) {
                return obj;
            }
            node = node->next;
        } while (head != node);
    }
    return NULL;
}

/* Finds the first object in a circular list (sentinel `list`) whose
 * unk_17C equals `kind` and whose unk_17E equals `id`. Returns NULL when
 * `id` is 0 or nothing matches. */
Object *obj_find_by_kind_id(Node *list, s32 id, s32 kind) {
    Node *node;
    Object *obj;
    s16 id16;
    s16 kind16;

    id16 = (s16) id;
    if (id16 != 0) {
        node = list->next;
        kind16 = (s16) kind;
        if (list != node) {
            do {
                if (node == NULL) {
                    return NULL;
                }
                obj = (Object *) node;
                if (obj->serial == kind16) {
                    if (obj->kind == id16) {
                        return obj;
                    }
                }
                node = node->next;
            } while (list != node);
        }
    }
    return NULL;
}

/* Sets the value at 0x180 of the object at (x, y); returns -1 when there is none. */
s32 obj_set_unk180_at(Node *list, s16 x, s16 y, s32 value) {
    Object *obj = obj_find_by_kind_id(list, x, y);

    if (obj == NULL) {
        return -1;
    }
    obj->unk_180 = value;
    return 0;
}

s32 obj_set_unk180_by_id(Node *head, s16 key, s32 value) {
    Object *cur;
    s32 result = -1;

    if (key != 0) {
        cur = obj_find_by_id(head, key);
        while (head != (Node *)cur) {
            if (cur == NULL) break;
            cur->unk_180 = value;
            cur = obj_find_by_id(&cur->node, key);
            result = 0;
        }
    }
    return result;
}

void obj_free(Object *obj) {
    s32 unused; /* the original reserves a stack slot for an unused local */

    if (obj == NULL) {
        printf("Free Work NULL Pointer\n");
        return;
    }
    if (obj->destructor != NULL) {
        obj->destructor(obj);
    }
    if (&obj->node == obj_list_cursor) {
        obj_list_cursor = obj->node.prev;
    }
    obj->serial = 0;
    obj->kind = 0;
    obj->unk_17A = 0;
    obj->free = 1;
    solid_free(obj->solid_id);
    list_remove(&obj->node);
    list_insert_before(&obj_free_tail, &obj->node);
    obj_free_count++;
    if (obj_pending_count == 0) {
        obj_pending = obj;
    }
    obj_pending_count++;
}

void obj_flush_one(void) {
    if (obj_pending_count > 0) {
        obj_reset(obj_pending);
        obj_pending_count--;
        obj_pending = (Object *)obj_pending->node.next;
    }
}

void sound_play_spatial(s32 x, s32 y, s32 z, s32 id, s32 volume) {
    s32 pos[3];
    s32 level;

    if (id & 0x8000) {
        return;
    }
    volume = MAX(volume <= 0x2000 ? volume : 0x2000, 0);
    level = sound_volume_of(id, volume);
    level = MAX(level <= 0x7F ? level : 0x7F, 0);
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    sound_play_at(id, level, 0x3C, pos);
}

void obj_play_sound(Object *obj, s32 a, s32 b) {
    s32 x = obj->x;
    s32 y = obj->y;
    s32 z = obj->z;

    sound_play_spatial(x, y, z, a, b);
}

/* Passes the object's position and a percentage (in 4096ths of 1/100) on. */
void obj_sound_at_volume(Object *obj, s32 a1, s32 percent) {
    s32 x = obj->x;
    s32 y = obj->y;
    s32 z = obj->z;

    sound_play_spatial(x, y, z, a1, (percent << 12) / 100);
}

/* Runs the negative opcodes (-6..-1) of a script stream. pc is the operand
   cursor, op the current opcode word. Each opcode consumes its operand(s); the
   loop ends at the first non-negative word and returns the operand cursor. */
s16 *script_run_neg_ops(Script *script, s16 *pc, s16 *op) {
    ObjLink *link = &((Object *)script)->type;

    while (*op < 0) {
        switch ((s16)((u16)*op + 6)) {
        case 5: {
            /* jump into the per-type table: the word at *pc selects a stream pointer */
            u16 *target = ((u16 **)link->data)[*pc];
            u16 value;
            pc = (s16 *)target;
            value = *target;
            pc++;
            *op = value;
            ((Object *)script)->script_flag = -1;
            continue;
        }
        case 4:
            if (((Object *)script)->sounds != NULL) {
                /* integer arithmetic: as a pointer index, cc1 adds the operands the other way round */
                SoundVolume *entry = (SoundVolume *)(*pc * sizeof(SoundVolume) + (u32)((Object *)script)->sounds);
                obj_play_sound((Object *)script, entry->sound, entry->volume);
            }
            break;
        case 3:
            {
                s32 speed = *pc;
                ((Object *)script)->speed = speed;
                fly_move(((Object *)script)->yaw, speed, &((Object *)script)->vz, &((Object *)script)->vx);
            }
            break;
        case 2:
            ((Object *)script)->vy = -(*pc << 12);
            ((Object *)script)->unk_1B7 = 0;
            break;
        case 1: {
            s32 r = rand_a_next();
            ((Object *)script)->vy = -((*pc << 12) + (r << 2));
            ((Object *)script)->unk_1B7 = 0;
            break;
        }
        case 0:
            ((Object *)script)->script_flag = *pc;
            break;
        default:
            break;
        }
        /* shared tail: skip the operand, then fetch the next word */
        pc++;
        *op = *pc;
        pc++;
    }
    return pc;
}

void script_advance(Script *script, ScriptState *st) {
    s16 *pc;
    u16 op;

    pc = st->pc;
    op = *pc++;
    pc = script_run_neg_ops(script, pc, (s16 *)&op);
    st->a = op;
    st->b = op;
    st->c = st->d;
    st->d = *pc++;
    st->pc = pc;
}

void script_start(Script *script, s16 *pc, s32 value) {
    ScriptState *st = &script->state;
    u16 op;
    s16 *next;

    op = *pc++;
    st->unk_00 = value;
    next = script_run_neg_ops(script, pc, (s16 *)&op);
    st->a = op;
    st->b = op;
    st->c = *next;
    st->d = *next;
    pc = next + 1;
    st->pc = pc;
}

void stream_reader_init(StreamReader *reader, s16 *stream, s32 base) {
    s16 head;

    /* Wrap a negative head value up to non-negative in steps of 2. */
    head = *stream;
    while (head < 0) {
        *stream = head + 2;
        head = head + 2;
    }
    reader->first[0] = *stream;
    reader->first[1] = *stream;
    stream++;
    reader->second[0] = *stream;
    reader->second[1] = *stream;
    stream++;
    reader->base = base;
    reader->cursor = stream;
}

/* Starts `ctx` at `pc`; a negative first word is an opcode run at once by script_run_neg_ops. */
void script_jump(Script *script, s16 *pc, s32 arg) {
    s16 op;

    if (arg != 0) {
        script->state.unk_00 = arg;
    }
    if (*pc < 0) {
        op = *pc;
        pc = script_run_neg_ops(script, pc + 1, &op) - 1;
    }
    script->state.pc = pc;
}

/* Points the cursor at the first entry at or after `entry` whose first halfword is not negative and
 * sets its value unless `value` is 0. */
void entry_cursor_seek(EntryCursor *cursor, s16 *entry, s32 value) {
    if (*entry < 0) {
        do {
            entry += 2;
        } while (*entry < 0);
    }
    cursor->entry = entry;
    if (value != 0) {
        cursor->value = value;
    }
}

s32 anim_seq_step(AnimSequence *seq) {
    u16 v;
    u16 *p;
    u16 **table;
    s32 indirect;
    u16 nextv;

    seq->count--;
    indirect = 0;
    if ((s16)seq->count < 0) {
        table = seq->table;
        p = seq->cur;
        v = *p;
        if ((s16)*p++ < 0) {
            indirect = 1;
            do {
                p = table[(s16)*p];
                v = *p;
            } while ((s16)*p++ < 0);
        }
        if (v == 0) {
            do {
                v = *p;
                p += 2;
            } while (v == 0);
        }
        seq->value = v;
        seq->count = v;
        seq->prev = seq->next;
        nextv = *p++;
        seq->cur = p;
        seq->next = nextv;
    }
    return indirect;
}

void actors_phase0(void) {
    obj_list_run((Node **)&obj_list_actors, 0);
}

/* Per-step hook of an actor: ticks its script, applies the velocity (clamped by `scale`) and either
 * moves the angles/position or runs the collision update. */
void actor_hook_fn(Object *obj) {
    s32 flags;
    s32 lo;
    s32 v;
    ScriptState *st;
    void *p;

    if (obj->free != 1) {
        flags = obj->flags;
        st = &((Script *)obj)->state;
        if ((flags & 1) && st != NULL) {
            obj->script_flag = 0;
            st->b--;
            if ((s16)st->b < 0) {
                script_advance((Script *)obj, st);
            }
        }
        if (test_bit(flags, 1) | test_bit(flags, 8)) {
            obj->vx += obj->accel_x;
            if (!test_bit(obj->flags, 4)) {
                obj->vy += obj->accel_y;
            }
            lo = obj->vx;
            obj->vz += obj->accel_z;
            if (obj->scale[0] < lo) {
                lo = obj->scale[0];
            }
            v = obj->vx;
            if (v < lo) {
                v = lo;
            }
            lo = obj->vy;
            obj->vx = v;
            if (obj->scale[1] < lo) {
                lo = obj->scale[1];
            }
            v = obj->vy;
            if (v < lo) {
                v = lo;
            }
            lo = obj->vz;
            obj->vy = v;
            if (obj->scale[2] < lo) {
                lo = obj->scale[2];
            }
            v = obj->vz;
            if (v < lo) {
                v = lo;
            }
            obj->vz = v;
            if (!test_bit(obj->flags, 8)) {
                p = (u8 *)obj + 0x2C;
                obj_snapshot_save(obj, p);
                player_step_move_scratch(p);
                obj_snapshot_restore(obj, p);
                if ((u8)obj->blocked_y != 0) {
                    obj->vy = 0;
                }
            } else {
                obj->move_delta[0] += (obj->vx + (obj->x & 0xFFF)) >> 12;
                obj->x += obj->vx;
                obj->move_delta[1] += (obj->vy + (obj->y & 0xFFF)) >> 12;
                obj->move_delta[2] += (obj->vz + (obj->z & 0xFFF)) >> 12;
                obj->y += obj->vy;
                obj->z += obj->vz;
            }
        }
        if (test_bit(flags, 5)) {
            collider_begin((Collider *)obj->unk_A4);
        }
    }
}

void actors_phase1(void) {
    actor_hook = &actor_hook_fn;
    obj_list_run((Node **)&obj_list_actors, 1);
    actor_hook = NULL;
}

void actors_phase2(void) {
    obj_list_run((Node **)&obj_list_actors, 2);
}

void actors_draw(void) {
    obj_list_run((Node **)&obj_list_actors, 3);
}

void list_b_phase0(void) {
    obj_list_run((Node **)&obj_list_b, 0);
}

void list_b_phase1(void) {
    obj_list_run((Node **)&obj_list_b, 1);
}

void list_b_phase2(void) {
    obj_list_run((Node **)&obj_list_b, 2);
}

void list_b_draw(void) {
    obj_list_run((Node **)&obj_list_b, 3);
}

void list_c_phase0(void) {
    obj_list_run((Node **)&obj_list_c, 0);
}

void list_c_phase1(void) {
    obj_list_run((Node **)&obj_list_c, 1);
}

void list_c_phase2(void) {
    obj_list_run((Node **)&obj_list_c, 2);
}

void list_c_draw(void) {
    obj_list_run((Node **)&obj_list_c, 3);
}

/* Adds the packed halfword pair at +0x1EC to the pair at +0x1E4 (and clears it),
   and folds the high half of +0x1E8 into its low half. */
void obj_apply_step(Object *obj) {
    s32 pos = *(s32 *)&obj->width;
    s32 delta = *(s32 *)&obj->unk_1E8[2];
    s32 pair = *(s32 *)&obj->unk_1E8[0];
    s32 lo_sum;
    s16 hi_sum, pair_sum;
    *(s32 *)&obj->unk_1E8[2] = 0;
    obj->unk_1E8[1] = 0;
    lo_sum = pos + delta;
    pos >>= 16;
    delta >>= 16;
    hi_sum = pos + delta;
    pos = pair >> 16;
    pair_sum = pos + pair;
    obj->width = lo_sum;
    obj->height = hi_sum;
    obj->unk_1E8[0] = pair_sum;
}

/* End of frame for every object of a list: clears its per-frame turn and
   applies the packed step at +0x1EC (see obj_apply_step). The goto keeps the
   original unrotated loop. */
void obj_list_end_step(s32 *list)
{
    Object *obj;
    s32 pos, delta, pair, lo_sum;
    s16 hi_sum, pair_sum;

    obj = (Object *)*list;
loop:
    if (obj->node.next != 0) {
        pos = *(s32 *)&obj->width;
        delta = *(s32 *)&obj->unk_1E8[2];
        pair = *(s32 *)&obj->unk_1E8[0];
        *(s32 *)&obj->move_delta[0] = 0;
        *(s32 *)&obj->move_delta[2] = 0;
        *(s32 *)&obj->unk_1E8[2] = 0;
        obj->unk_1E8[1] = 0;
        lo_sum = pos + delta;
        pos >>= 16;
        delta >>= 16;
        hi_sum = pos + delta;
        pos = pair >> 16;
        pair_sum = pos + pair;
        obj->width = lo_sum;
        obj->height = hi_sum;
        obj->unk_1E8[0] = pair_sum;
        obj = (Object *)obj->node.next;
        goto loop;
    }
}

void objects_end_step(void) {
    obj_list_end_step(get_obj_list_actors());
    obj_list_end_step(get_obj_list_b());
    solid_reset_all();
}

void obj_block_fill(void *src, void *dst) {
    s32 a, b, c;

    a = (*(s32 *)((u8 *)(src) + (0x1F0)));
    b = (*(s32 *)((u8 *)(src) + (0x1F4)));
    c = (*(s32 *)((u8 *)(src) + (0x1F8)));
    (*(s32 *)((u8 *)(dst) + (0x1C))) = a;
    (*(s32 *)((u8 *)(dst) + (0x20))) = b;
    (*(s32 *)((u8 *)(dst) + (0x24))) = c;
    a = (*(s32 *)((u8 *)(src) + (0x1E4)));
    b = (*(s32 *)((u8 *)(src) + (0x1E8)));
    c = (*(s32 *)((u8 *)(src) + (0x1EC)));
    (*(s32 *)((u8 *)(dst) + (0x34))) = a;
    (*(s16 *)((u8 *)(dst) + (0x38))) = b;
    (*(s32 *)((u8 *)(dst) + (0x44))) = c;
    (*(s16 *)((u8 *)(dst) + (0x48))) = b >> 16;
    a = (*(s32 *)((u8 *)(src) + (0x238)));
    b = (*(s16 *)((u8 *)(src) + (0x23C)));
    (*(s32 *)((u8 *)(dst) + (0x3C))) = a;
    (*(s16 *)((u8 *)(dst) + (0x40))) = b;
    a = (*(s32 *)((u8 *)(src) + (0x220)));
    b = (*(s16 *)((u8 *)(src) + (0x224)));
    (*(s16 *)((u8 *)(dst) + (0x2E))) = a;
    (*(s16 *)((u8 *)(dst) + (0x2C))) = -(a >> 16);
    (*(s16 *)((u8 *)(dst) + (0x30))) = b;
}

void fn_800FB460(Object *obj, u8 *block) {

}
