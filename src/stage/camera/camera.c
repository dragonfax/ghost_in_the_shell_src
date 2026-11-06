/* camera: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void target_select(s32 value) {
    value = NOT_NEGATIVE(value < 6 ? value : 5);
    target_requested = value;
    target_switch_timer = 30;
}

s32 target_get_index(void) {
    return target_current;
}

void cam_set_offset(s32 x, s32 y) {
    cam_offset_x = x + 0xB4;
    cam_offset_y = y + 6;
}

void cam_set_target(s32 x, s32 y, s32 z) {
    cam_target_x = x;
    cam_target_y = y;
    cam_target_z = z;
}

void pursuit_view_hold_add(void) {
    pursuit_hold_timer += 2;
}

/* Point camera `camera` along the direction (dx, dy, dz). */
void cam_set_dir(s32 camera, s32 dx, s32 dy, s32 dz) {
    s32 yaw;
    s32 pitch;
    s32 neg_yaw;

    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    neg_yaw = -yaw;
    yaw = neg_yaw;
    cam_set_rot(camera, neg_yaw, pitch, 0);
}

void cam_init(void) {
    view_setup(5, 2, 2);
    cam_set_pos(2, 0, -0x15E, -0x28A);
    cam_set_dir(2, 0, 0x15E, 0x28A);
    cam_mode = 1;
    cam_offset_x = 0xB4;
    cam_offset_y = 6;
    pursuit_view_w = 0x40;
    pursuit_view_h = 0x40;
    pursuit_blend = 0;
    pursuit_spin_angle = 0;
    pursue_msg_timer = 0x12C;
    target_requested = 0;
    target_current = 0;
    pursuit_hold_timer = 0;
    target_switch_timer = 0;
    cam_set_target(0, 0, 0);
    cam_path_clear();
}

void pursuit_view_update(void) {
    s32 sin_off;

    if (pursuit_hold_timer > 0) {
        pursuit_hold_timer--;
    } else {
        if (pursue_msg_timer < 0x960) {
            pursue_msg_timer++;
        }
        if (pursue_msg_timer == 0x960) {
            pursue_msg_timer = 0x12C;
        }
    }
    if (pursuit_hold_timer >= 0x78) {
        pursuit_hold_timer = 0x78;
        pursue_msg_timer = 0;
    }
    if (meter_is_full() && meter_get_mode() == 0 && cam_mode != 0 && target_current != 0 &&
        target_current == target_requested && (target_current == 5 || (u32)(pursue_msg_timer - 0x12C) < 0x12C)) {
        pursuit_blend = CLAMP_HI(pursuit_blend + 0x200, 0x1000);
        pursuit_spin_angle = (pursuit_spin_angle + 0x44) & 0xFFF;
        if (target_current != 5 && pursue_msg_timer == 0x12C) {
            static const char pursue_msg[] = "Pursue the target.\xA1";
            show_line((s32)pursue_msg);
            pursue_msg_timer++;
        }
    } else {
        pursuit_blend = MAX(pursuit_blend - 0x200, 0);
        pursuit_spin_angle = 0;
    }
    if (target_current != target_requested && pursuit_blend == 0) {
        if (--target_switch_timer <= 0) {
            target_current = target_requested;
        }
    }
    if (untimed_part()) {
        view_set_on(5, 0);
        {
            register s32 five asm("$3") = 5;
            if (target_current == five) {
                view_set_on(5, pursuit_blend > 0);
            }
        }
        view_set_size(5, pursuit_view_w, pursuit_view_h);
        view_set_pivot(5, 0x20, 0x26);
        fn_800C94D8(5, 0, 0);
        sin_off = pursuit_view_h * (s16)rcossin_tbl[(pursuit_blend / 4) & 0xFFF] >> 12;
        set_view_offset(5, cam_offset_x, cam_offset_y);
        view_set_clip_size(5, pursuit_view_w, sin_off);
    }
}

/* Pushes a 0x14-byte IdRecord after id_table: position (x, y) relative to the
 * view origin, scale 0x1000, colour, and an angle from pursuit_blend. The record
 * is linked into the bucket given by the packed level's top byte. */
void id_table_push_view(s32 x, s32 y, s32 color, s32 level) {
    IdTable *tbl;
    IdRecord *rec;
    s32 scale;
    s32 level_hi;
    s32 angle;
    s32 packed;
    s32 index;
    s32 slot;
    s32 off;
    s32 dx;
    s32 px;
    s32 py;
    s32 diff;
    s32 dy;

    level >>= 5;
    level_hi = level;
    if (level == 0) {
        level_hi = 1;
    }
    scale = 0x1000;
    packed = (level_hi << 16) | (level << 8) | level;
    dx = cam_offset_x - view_screen_offsets[0].value;
    dy = cam_offset_y - view_screen_offsets[0].offset_y;
    diff = scale - pursuit_blend;
    if (diff < 0) {
        diff += 3;
    }
    angle = diff >> 2;
    px = dx + x;
    py = dy + y;
    __asm__("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;
    slot = packed >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        do {
        } while (0);
        off = index * 0x14 + 0x24;
        rec = (IdRecord *)((u8 *)tbl + off);
        rec->prev_id = tbl->id[slot];
        tbl->id[slot] = index;
        rec->field_00 = px;
        rec->field_02 = py;
        rec->field_04 = scale;
        rec->field_0E = color;
        rec->field_08 = 0;
        rec->field_0A = angle;
        rec->field_0C = 0;
        rec->field_10 = packed;
    }
}

static inline void spark_add_chain2(s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n;
    SparkRec *s;
    u8 *tail;
    s32 off;
    s32 pitch;

    FAKE_OPAQUE(list);
    n = SPARK_COUNT;
    pitch = rx;
    if (n < 0xFF) {
        off = (s32)&((SparkList *)0)->items[n];
        s = (SparkRec *)(off + (s32)list);
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[2];
        list->tail[2] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = 0;
        s->y = 0;
        s->z = 0;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = pitch;
        s->roll = rz;
    }
}
void target_marker_draw(void) {
    s32 ang[3];
    s32 t0, t1, t2;
    s32 dx, dy, dz;
    s32 *mtx;
    s32 *mtx2;
    s32 base;
    s32 *view;
    register s32 *cam asm("$4");
    s32 offset;

    if (pursuit_blend != 0 && target_current != 0) {
        base = ((s32 *)get_ptr_entry_word2(5))[2];
        if (target_current == 5) {
            view = view_matrix_t_get();
            cam = &cam_target_x;
            gte_set_R012(t0, t1, t2, view[0], view[1], view[2]);
            gte_set_R34(t0, t1, view[3], view[4]);
            dx = *cam - (player_xyz[0] >> 12);
            dy = cam_target_y - (player_xyz[1] >> 12);
            dz = cam_target_z - (player_xyz[2] >> 12);
            gte_set(IR1, dx);
            gte_set(IR2, dy);
            gte_set(IR3, dz);
            gte_rtir();
            gte_get(MAC1, dx);
            gte_get(MAC2, dy);
            gte_get(MAC3, dz);
            vector_to_angles(dx, dy, dz, &ang[0], &ang[1]);
            mtx = scratch_alloc(0x40);
            rot_matrix(mtx, ang[0], -ang[1], 0);
            mtx2 = mtx + 8;
            rot_matrix(mtx2, 0, -0x400, 0);
            mul_matrix(mtx, mtx2, mtx);
            matrix_to_angles(mtx, &ang[0], &ang[1], &ang[2]);
            scratch_top -= 0x40;
            spark_add_chain2(0, 0x400, 0, spark_model_base + 0x2A, 0x2555555);
            spark_add_chain2(ang[0], ang[1], ang[2], spark_model_base + 0x2B, 0x2606060);
            id_table_push_view(0, 0, base + 0x17, 0x1FFF);
        } else {
            offset = 0xF;
            id_table_push_view(0, 0, target_current + (base + offset), 0x1FFF);
        }
        if (target_current != 5 && pursuit_spin_angle >= 0x800) {
            id_table_push_view(0, 0x16, base + 0x18, 0x1000);
        }
    }
}

/* Closest point to p on the segment a..b (a clamped projection), stored in *out; returns the distance from p
 * to it. Vectors are s32 triples. */
s32 seg_closest_point(s32 *p, s32 *a, s32 *b, s32 *out) {
    VECTOR *dir = scratch_alloc(0x10);
    s32 cx = a[0];
    s32 cy = a[1];
    s32 cz = a[2];
    s32 dx = b[0];
    s32 dy = b[1];
    s32 dz = b[2];
    s32 px = p[0];
    s32 py = p[1];
    s32 pz = p[2];
    s32 len;
    s32 t;

    dx -= cx;
    dy -= cy;
    dz -= cz;
    if (dx != 0 || dy != 0 || dz != 0) {
        len = isqrt(length_sq(dx, dy, dz));
        dir->vx = dx;
        dir->vy = dy;
        dir->vz = dz;
        VectorNormal(dir, (SVECTOR *)dir);
        t = ((px - cx) * dir->vx + (py - cy) * dir->vy + (pz - cz) * dir->vz) / len;
        if (t >= 0x1000) {
            cx += dx;
            cy += dy;
            cz += dz;
        } else if (t > 0) {
            cx += (dx * t) / 0x1000;
            cy += (dy * t) / 0x1000;
            cz += (dz * t) / 0x1000;
        }
    }
    scratch_top -= 0x10;
    out[0] = cx;
    out[1] = cy;
    out[2] = cz;
    return isqrt(length_sq(px - cx, py - cy, pz - cz));
}

/* Finds the segment of the polyline `points` (count points) closest to `pos`; copies the closest point on it
 * to `out` and returns the segment's index. A single point is copied and 0 returned. */
s32 path_nearest_segment(s32 count, PathPoint *points, Vec3 *pos, PathPoint *out) {
    PathPoint *next;
    s32 i;
    PathPoint *closest;
    register s32 *point asm("$4");
    register PathPoint *seg asm("$5");
    s32 best_index;
    s32 best;
    s32 dist;

    if (count == 1) {
        *out = *points;
        return 0;
    }
    closest = scratch_alloc(0x10);
    point = (s32 *)pos;
    seg = points;
    best = seg_closest_point(point, (s32 *)seg, (s32 *)(next = seg + 1), (s32 *)closest);
    *out = *closest;
    best_index = 0;
    for (i = 1; i < count - 1; i++) {
        seg = next;
        point = (s32 *)pos;
        dist = seg_closest_point(point, (s32 *)seg, (s32 *)(next = seg + 1), (s32 *)closest);
        if (dist < best) {
            best_index = i;
            *out = *closest;
            best = dist;
        }
    }
    scratch_top -= 0x10;
    return best_index;
}

void cam_path_sample(s32 count, s32 pts, Vec3 *pos, Vec3 *out, s32 dist) {
    s32 prev;
    s32 idx;
    s32 n;
    s32 seg;
    PathPoint *q;
    s32 x, y, z;
    s32 off;
    PathPoint *cur;

    if (count == 1) {
        *(PathPoint *)out = ((PathPoint *)pts)[0];
        return;
    }
    prev = cam_path_last_seg;
    idx = prev - 1;
    if (idx < 0) {
        idx = 0;
    }
    n = 6;
    if (count - idx < 7) {
        n = count - idx;
    }
    idx += path_nearest_segment(n, &((PathPoint *)pts)[idx], pos, (PathPoint *)out);
    cam_path_last_seg = idx;
    dist -= isqrt(length_sq(pos->x - out->x, pos->y - out->y, pos->z - out->z));
    if (dist <= 0) {
        x = out->x;
        y = out->y;
        z = out->z;
    } else {
        off = idx << 4;
        cur = (PathPoint *)(off + pts);
        dist += isqrt(length_sq(out->x - cur->x, out->y - cur->y, out->z - cur->z));
        while (idx < count - 1) {
            FAKE_OPAQUE(cur);
            seg = isqrt(length_sq(cur[1].x - cur->x, cur[1].y - cur->y, cur[1].z - cur->z));
            if (seg >= dist) {
                break;
            }
            dist -= seg;
            idx++;
            cur++;
        }
        if (idx == count - 1) {
            idx = count - 2;
            dist += seg;
        }
        dist = (dist << 12) / seg;
        q = &((PathPoint *)pts)[idx];
        x = q->x;
        y = q->y;
        z = q->z;
        x += (q[1].x - x) * dist / 4096;
        y += (q[1].y - y) * dist / 4096;
        z += (q[1].z - z) * dist / 4096;
    }
    if (prev < 0) {
        cam_path_smooth.x = x;
        cam_path_smooth_y = y;
        cam_path_smooth_z = z;
    } else {
        cam_path_smooth.x += (x - cam_path_smooth.x) / 8;
        cam_path_smooth_y += (y - cam_path_smooth_y) / 8;
        cam_path_smooth_z += (z - cam_path_smooth_z) / 8;
    }
    *(PathPoint *)out = cam_path_smooth;
}

void cam_path_clear(void) {
    cam_path_last_seg = -1;
    cam_path_start = -1;
}

void cam_path_set(s32 a, s32 b) {
    cam_path_last_seg = -1;
    cam_path_start = a;
    cam_path_end = b;
}

void cam_path_update(void) {
    CamPathSample *rec;

    if (cam_path_start >= 0) {
        rec = scratch_alloc(sizeof(CamPathSample));
        rec->pos.x = VEC_80139584.x >> 12;
        rec->pos.y = VEC_80139584.y >> 12;
        rec->pos.z = VEC_80139584.z >> 12;
        cam_path_sample(cam_path_start, cam_path_end, &rec->pos, &rec->out, 0x600);
        cam_set_target(rec->out.x, rec->out.y, rec->out.z);
        scratch_top -= sizeof(CamPathSample);
    }
}

void fn_80106E70(void) {

}

void impact_effect_base_set(s32 value) {
    impact_effect_base = value;
}

/* Transforms the vector at in by the GTE rotation matrix and translation into out, and returns out (same code as transform_point). */
VECTOR *rotate_vector_inverse(VECTOR *in, VECTOR *out) {
    gte_load(IR1, in, 0);
    gte_load(IR2, in, 4);
    gte_load(IR3, in, 8);
    gte_rtirtr();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
    return out;
}
