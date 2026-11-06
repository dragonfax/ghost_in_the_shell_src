/* rec_table: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void rec_table_set_enabled(s32 value) {
    rec_table_enabled = value;
}

s32 rec_table_get_enabled(void) {
    return rec_table_enabled;
}

/* Clears the flag table and the 16 id/state records (id -1). */
void rec_table_reset(void) {
    s8 *flag;
    s32 i;
    s32 off;
    s16 none;

    i = 0x7F;
    flag = &rec_flag_table;
    do {
        *flag = 0;
        i--;
        flag--;
    } while (i >= 0);
    i = 0;
    none = -1;
    off = 0;
    do {
        *(s16 *)((u8 *)d_8012EE14 + off) = none;
        *(s16 *)((u8 *)lock_slot_target + off) = 0;
        off += 0x18;
        i++;
    } while (i < 16);
    lock_spawn_timer = 0;
    rec_table_enabled = 1;
    lock_slot_phase = 0;
}

s32 obj_screen_bounds(s32 id, s32 *out) {
    s32 *m = (s32 *)scratch_top;
    Object *obj = obj_table[id & 0x7F];
    s32 ok;
    s32 r0, r1, r2;
    s32 lo, hi, t;
    s32 h, hs;

    scratch_top += 0x20;
    ok = 0;
    if ((u8)obj->unk_17A != 0 && test_bit(obj->flags, 5)) {
        rot_matrix(m, obj->yaw, -obj->pitch, obj->roll);
        gte_set_R012(r0, r1, r2, m[0], m[1], m[2]);
        gte_set_R34(r0, r1, m[3], m[4]);
        h = (s16)obj->height;
        hs = h << 16;
        gte_set(VXY0, ((-h) / 2) << 16);
        gte_set(VZ0, 0);
        gte_rtv0();
        lo = obj->width;
        hi = (hs >> 16) / 2;
        if (lo < hi) {
            t = hi; hi = lo; lo = t;
        }
        out[3] = (lo << 16) | (hi & 0xFFFF);
        gte_stlvnl(out);
        ok = 1;
        out[0] += obj->x >> 12;
        out[1] += obj->y >> 12;
        out[2] += obj->z >> 12;
    }
    scratch_top -= 0x20;
    return ok;
}

s32 obj_has_flag_200(s32 index) {
    s32 flags;
    s32 result;

    if (rec_table_enabled != 0) {
        flags = obj_table[index & 0x7F]->flags;
        result = flags & 0x200;
    } else {
        result = 0;
    }
    return result;
}

s32 obj_target_score(s32 obj, s32 near) {
    s32 result = -1;
    u8 *rec;
    s32 limit, radius;
    s32 dx, dy, dz;
    s32 *m;
    Camera *cam;

    rec = scratch_alloc(0x20);
    if (obj_screen_bounds(obj, (s32 *)rec) != 0) {
        radius = *(s16 *)(rec + 0xE);
        /* Extra read of radius: without it the compiler gives rec the
           higher register priority and the registers come out swapped. */
        __asm__ volatile("" : : "r"(radius));
        limit = near ? 0x800 : 0xA00;
        dx = *(s32 *)rec - *player_position();
        if (ABS(dx) - radius <= limit) {
            dz = *(s32 *)(rec + 8) - player_position()[2];
            if (ABS(dz) - radius <= limit) {
                dy = *(s32 *)(rec + 4) - player_position()[1];
                if (ABS(dy) - radius <= limit) {
                    if (near) {
                        m = view_matrix_t_get();
                        gte_load_R_a0a1v1(m);
                        gte_set(IR1, dx);
                        gte_set(IR2, dy);
                        gte_set(IR3, dz);
                        gte_nop();
                        gte_nop();
                        gte_rtir_b();
                        gte_get_MAC123(dx, dy, dz);
                        gte_nop();
                        if (dz < 0) goto out;
                        dz += 0x400;
                        if (dz < ABS(dy)) goto out;
                        if (dz < ABS(dx)) goto out;
                        if (cur_cam_index < 0) goto out;
                        cam = &cameras[cur_cam_index];
                        if (!obj_has_flag_200(obj) &&
                            trace_world(4, 8, cam, rec, rec + 0x10) != 0)
                            goto out;
                    }
                    result = length_sq(dx, dy, dz - 0x400);
                }
            }
        }
    }
out:
    scratch_top -= 0x20;
    return result;
}

/* Returns the index of the object (in the actor list) that obj_target_score scores lowest, or -1. */
s32 obj_find_lowest_score(void) {
    Node *head = (Node *) get_obj_list_actors();
    Object *obj;
    Object *best = NULL;
    s32 best_index = -1;
    s32 best_score;
    s32 score;

    for (obj = (Object *) head->next; obj->node.next != NULL; obj = (Object *) obj->node.next) {
        if (obj_lock_counts[obj->index] != 0) {
            continue;
        }
        score = obj_target_score(obj->index, 1);
        if (score < 0) {
            continue;
        }
        if (best == NULL || score < best_score) {
            best = obj;
            best_index = obj->index;
            best_score = score;
        }
    }
    return best_index;
}

void lock_slots_update(void) {
    s32 off;
    s16 *id;
    s32 i;
    s32 free_slot;
    s16 none;
    s32 phase;
    s32 any_flagged;
    s32 step;
    s32 found;
    s32 decay_off;
    s32 new_off;
    s32 raise_off;
    s32 obj;

    phase = lock_slot_phase;
    lock_slot_phase = (phase + 1) % 4;
    free_slot = -1;
    any_flagged = 0;
    i = 0;
    none = -1;
    id = lock_slot_target;
    off = 0;
    for (; i < 16; i++, off += 0x18) {
        if (SLOT_LEVEL(off) < 0) {
            if (free_slot < 0) {
                free_slot = i;
            }
        } else if (*id == 0) {
            /* empty slot: let the level fade out */
            decay_off = off;
            SLOT_LEVEL(decay_off) = SLOT_LEVEL(off) - 0x155 < -1 ? -1 : SLOT_LEVEL(off) - 0x155;
        } else if (obj_screen_bounds(*id, SLOT_BOUNDS(off)) == 0) {
            /* off screen: drop the target */
            obj = *id;
            SLOT_LEVEL(off) = none;
            obj_lock_counts[obj] = 0;
            *id = none;
        } else if (i % 4 == phase && obj_target_score(*id, 0) < 0) {
            /* this frame's recheck failed: drop the target */
            obj = *id;
            SLOT_LEVEL(off) = none;
            obj_lock_counts[obj] = 0;
            *id = none;
        } else {
            step = 0x44;
            if (SLOT_LEVEL(off) < 0x1000) {
                step = 0x155;
            }
            raise_off = off;
            SLOT_LEVEL(raise_off) = SLOT_LEVEL(off) + step > 0x3000 ? 0x3000 : SLOT_LEVEL(off) + step;
            obj = *id;
            obj = obj_table[obj & 0x7F]->flags;
            if (obj & 0x200) {
                any_flagged = 1;
            }
        }
        id += 12;
    }
    if (any_flagged) {
        pursuit_view_hold_add();
    }
    if (meter_is_full() != 0 && free_slot >= 0) {
        if (lock_spawn_timer > 0) {
            lock_spawn_timer--;
            return;
        }
        lock_spawn_timer = 12;
        found = obj_find_lowest_score();
        if (found >= 0) {
            new_off = free_slot * 0x18;
            SLOT_LEVEL(new_off) = 0;
            SLOT_ID(new_off) = found;
            SLOT_FLAG(new_off) = obj_has_flag_200(found);
            obj_screen_bounds(found, SLOT_BOUNDS(new_off));
            obj_lock_counts[found]++;
        }
    }
}

/* Projects a point relative to camera cur_cam_index when it lies within 0x4000 of the camera on each axis.
 * The camera's view matrix is scaled into the scratchpad and loaded into the GTE, then RTPS runs. Returns 1 when
 * the point is in front of the camera (FLAG not negative). */
s32 cam_world_to_screen(WorldPoint *in, ProjectedPoint *out) {
    View *view = views;
    Camera *cam;
    /* volatile: the loads stay in the original's order (the GTE loads are scheduled around the ctc2 pairs) */
    volatile s32 *matrix;
    s32 dx;
    s32 dy;
    s32 dz;
    register s32 flags __asm__("$4");
    s32 depth;
    register s32 rt11_12 __asm__("$3");
    register s32 rt13_21 __asm__("$4");
    register s32 rt22_23 __asm__("$2");
    register s32 rt31_32 __asm__("$3");
    register s32 rt33 __asm__("$4");
    register s32 gte_val __asm__("$7");

    if (cur_cam_index >= 0) {
        cam = &cameras[cur_cam_index];
        dx = in->x - cam->pos.vx;
        if ((u32)(dx + 0x4000) <= 0x7FFF) {
            dy = in->y - cam->pos.vy;
            if ((u32)(dy + 0x4000) <= 0x7FFF) {
                dz = in->z - cam->pos.vz;
                if ((u32)(dz + 0x4000) <= 0x7FFF) {
                    matrix = (s32 *)scratch_top;
                    scratch_top += 0x20;
                    scale_rows(view->rot[0], (s16 *)&view->unk_2C[0xC], (s16 *)matrix);
                    rt11_12 = matrix[0];
                    rt13_21 = matrix[1];
                    rt22_23 = matrix[2];
                    gte_set_ctrl(R11R12, rt11_12);
                    gte_set_ctrl(R13R21, rt13_21);
                    gte_set_ctrl(R22R23, rt22_23);
                    rt31_32 = matrix[3];
                    rt33 = matrix[4];
                    gte_set_ctrl(R31R32, rt31_32);
                    gte_set_ctrl(R33, rt33);
                    scratch_top -= 0x20;
                    /* H and the zero offsets share $7, as the original's `addiu a3,zero,0x80` / `addu a3,zero,zero` do */
                    gte_val = 0x80;
                    gte_set_ctrl(H, gte_val);
                    gte_val = 0;
                    FAKE_OPAQUE(gte_val);
                    gte_set_ctrl(OFX, gte_val);
                    gte_set_ctrl(OFY, gte_val);
                    gte_set_ctrl(TRX, 0);
                    gte_set_ctrl(TRY, 0);
                    gte_set_ctrl(TRZ, 0);
                    gte_set(VXY0, (dy << 16) | (dx & 0xFFFF));
                    gte_set(VZ0, dz);
                    gte_rtps();
                    gte_get_ctrl(FLAG, flags);
                    gte_store(SXY2, out, 0);
                    if (flags >= 0) {
                        gte_get(IR3, depth);
                        /* load delay slot after mfc2 (gte_get doesn't add it) */
                        mips_nop();
                        if (depth < 0x80) {
                            depth = 0x80;
                        }
                        out->depth = depth;
                        out->size = (in->size << 7) / depth;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

static inline void id_push_tagged(s32 tag, s32 x, s32 y, s32 scale, s32 depth, s32 angle)
{
    IdTableRecords *tbl;
    s32 index;
    s32 head;
    IdRecord *rec;

    tbl = (IdTableRecords *)&id_table;
    __asm__ volatile("");
    __asm__ volatile("" : "=r"(tbl) : "0"(tbl));
    index = tbl->count;
    head = tag >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = tbl->id[head];
        tbl->id[head] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = depth;
        rec->field_08 = angle;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = tag;
    }
}
static inline s32 clamp_unit(s32 v)
{
    return CLAMP_HI(v, 0x1000);
}
void rec_marker_draw(ProjectedPoint *pos, s32 dist, s32 lit)
{
    s32 base = track_base + 0xF8;
    s32 size = pos->size;
    s32 x = pos->sx;
    s32 y = pos->sy;
    s32 near;
    s32 value; /* fade, then depth offset, then scale */
    s32 depth_lim;
    s32 tag;

    if (lit == 0) {
        tag = 0x80;
    } else {
        tag = 0x8000;
        if (dist < 0x2800 && id_marker_pushed == 0) {
            if (dist < 0x800) {
                value = (0x800 - dist) / 2;
            } else {
                value = 0;
            }
            tag = 0x408000;
            id_push_tagged(tag, x, y + size + 14, 0x1000, track_base + 0x104, value);
            id_marker_pushed = 1;
            tag = 0x8000;
        }
    }
    near = clamp_unit(dist);
    if (clamp_unit(dist) < 0) near = 0;
    size += (0x1000 - near) * 48 / 4096;
    value = pos->depth - 0x480;
    depth_lim = value;
    if (depth_lim > 0x400) depth_lim = 0x400;
    /* The original keeps this unused clamp: the asm keeps both values live. */
    __asm__ volatile("" : : "r"(depth_lim), "r"(value));
    value = 0x1000;
    id_push_tagged(tag, x + size, y - size, value, base, 0);
    id_push_tagged(tag, x - size, y - size, value, base + 1, 0);
    id_push_tagged(tag, x + size, y + size, value, base + 2, 0);
    id_push_tagged(tag, x - size, y + size, value, base + 3, 0);
}

void rec_table_update(void) {
    s16 *entry;
    s32 off;
    s32 i;
    ProjectedPoint *out;
    s32 flag;

    if (meter_is_full() != 0) {
        i = 0;
        scratch_alloc(0x10);
        out = scratch_alloc(4);
        id_marker_pushed = 0;
        entry = d_8012EE14;
        off = 0;
        do {
            if (entry[0] >= 0 && cam_world_to_screen((WorldPoint *)(rec_table_pos + off), out) != 0) {
                flag = *(s16 *)(rec_table_flag + off);
                if (flag != 0 || entry[0] < 0x2000) {
                    rec_marker_draw(out, entry[0], flag);
                }
            }
            entry += 12;
            off += 0x18;
            i++;
        } while (i < 16);
        scratch_top -= 0x14;
    }
}

void cam_set_mode(s32 value) {
    cam_mode = value;
}

s32 cam_get_mode(void) {
    return cam_mode;
}
