/* lock_on: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s16 locked_target(s32 index) {
    s32 k;
    s32 remaining = index;

    if (lock_target_count == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (lock_target_count - 1 < index) {
        return 0;
    }
    for (k = 0; k < 6; k++) {
        if (lock_slots[k].id >= 0) {
            if (remaining-- <= 0) {
                return lock_slots[k].flag_index;
            }
        }
    }
    return 0;
}

/* Writes obj's aim point to sel->pos (a solid part's position when it has a hit part, else half its
   height above its position, rotated by its angles) and its vertical extent (min, max of unk_1E4 and half the height) to unk_0C/radius; returns 0 when
   the object has no hit reaction. */
s32 lock_target_sphere(s32 obj_index, SelRecord *sel) {
    s32 *out = (s32 *)sel; /* out[3]: unk_0C (low half) and radius (high half) in one word store */
    s32 *mat = scratch_alloc(0x20);
    Object *obj = obj_table[obj_index & 0x7F];
    register s32 result asm("$5");
    s32 part;
    s32 flags;
    s32 lo;
    s32 hi;

    result = 0;
    if ((u8)obj->unk_17A != 0 && ((u32)(flags = obj->flags) >> 5) & 1) { /* s32 copy: keeps the lh */
        part = obj_hit_get_unk06(obj->index);
        if (part >= 0) {
            result = solid_part_pos(obj->solid_id, part, out);
        } else {
            rot_matrix(mat, obj->yaw, -obj->pitch, obj->roll);
            {
                register s32 r0 asm("$3") = mat[0];
                register s32 r1 asm("$4") = mat[1];
                register s32 r2 asm("$2") = mat[2];
                gte_set_ctrl(R11R12, r0);
                gte_set_ctrl(R13R21, r1);
                gte_set_ctrl(R22R23, r2);
            }
            {
                register s32 r3 asm("$3") = mat[3];
                register s32 r4 asm("$4") = mat[4];
                gte_set_ctrl(R31R32, r3);
                gte_set_ctrl(R33, r4);
            }
            gte_set(VXY0, (-(s16)obj->height / 2) << 16);
            gte_set(VZ0, 0);
            gte_rtv0();
            gte_store(MAC1, out, 0);
            gte_store(MAC2, out, 4);
            gte_store(MAC3, out, 8);
            result = 1;
            out[0] += obj->x >> 12;
            out[1] += obj->y >> 12;
            out[2] += obj->z >> 12;
        }
        hi = obj->width;
        lo = (s16)obj->height / 2;
        if (hi < lo) {
            s32 swap = lo;
            lo = hi;
            hi = swap;
        }
        out[3] = (hi << 16) | (lo & 0xFFFF);
    }
    scratch_top -= 0x20;
    return result;
}

s32 lock_target_distance(s32 index) {
    s32 dist = -1;
    SelRecord *sel = scratch_alloc(0x10);
    s32 radius;
    s32 dx, dy, dz;
    s32 *view;
    register s32 m0 asm("$4");
    register s32 m1 asm("$5");
    s32 m2;

    if (lock_target_sphere(index, sel)) {
        radius = sel->radius;
        dx = sel->pos[0] - player_position()[0];
        if (ABS(dx) - radius < 0x801) {
            dz = sel->pos[2] - player_position()[2];
            if (ABS(dz) - radius < 0x801) {
                dy = sel->pos[1] - player_position()[1];
                if (ABS(dy) - radius < 0x801) {
                    view = view_matrix_t_get();
                    m0 = view[0];
                    m1 = view[1];
                    m2 = view[2];
                    gte_set_ctrl(R11R12, m0);
                    gte_set_ctrl(R13R21, m1);
                    gte_set_ctrl(R22R23, m2);
                    m0 = view[3];
                    m1 = view[4];
                    gte_set_ctrl(R31R32, m0);
                    gte_set_ctrl(R33, m1);
                    gte_set(IR1, dx);
                    gte_set(IR2, dy);
                    gte_set(IR3, dz);
                    gte_rtir();
                    gte_get(MAC1, dx);
                    gte_get(MAC2, dy);
                    gte_get(MAC3, dz);
                    gte_nop();
                    if (dz >= 0) {
                        dz += 0x400;
                        if (ABS(dy) <= dz) {
                            if (ABS(dx) <= dz) {
                                dist = length_sq(dx, dy, dz - 0x400);
                            }
                        }
                    }
                }
            }
        }
    }
    scratch_top -= 0x10;
    return dist;
}

s32 lock_find_target(void) {
    Object *obj;
    Object *cand;
    Object *best;
    s32 best_dist;
    s32 best_index;
    s32 dist;
    s32 pos[3];

    obj = *(Object **)get_obj_list_actors();
    best = NULL;
    best_index = -1;
    while (*(s32 *)obj != 0) {
        if (obj->health >= lock_flag_counts[obj->index] * 0x90) {
            dist = lock_target_distance(obj->index);
            if (dist >= 0 && (best == NULL || dist < best_dist)) {
                cand = obj;
                best = cand;
                best_index = cand->index;
                best_dist = dist;
            }
        }
        obj = *(Object **)obj;
    }
    if (best_index != -1) {
        pos[0] = cand->x;
        pos[1] = cand->y;
        pos[2] = cand->z;
        sound_play_at(SND_THREE_BEEPS | SND_VOICE_FLAG, 0x7F, 0x3C, pos);
        sound_start(SND_LOCK_ON_BEEP | SND_VOICE_FLAG, 0x40, 0, 0);
    }
    return best_index;
}

void lock_update(void) {
    s32 free_slot;
    s32 i;
    s32 target;

    if (lock_mode == 0) {
        return;
    }
    free_slot = -1;
    for (i = 0; i < 6; i++) {
        if (lock_slots[i].id < 0) {
            if (free_slot < 0) {
                free_slot = i;
            }
        } else {
            lock_slots[i].id += 0x199;
            lock_slots[i].id = MAX(MIN(lock_slots[i].id, 0x1000), 0);
            if (lock_target_distance(lock_slots[i].flag_index) < 0) {
                lock_flag_counts[lock_slots[i].flag_index] = 0;
                lock_slots[i].id = -1;
                lock_target_count--;
            }
        }
    }
    if (lock_cooldown_timer > 0) {
        lock_cooldown_timer--;
    } else if (lock_target_count < 6 && free_slot >= 0) {
        target = lock_find_target();
        if (target >= 0) {
            lock_slots[free_slot].flag_index = target;
            lock_target_count++;
            lock_slots[free_slot].id = 0;
            lock_flag_counts[target]++;
            lock_cooldown_timer = 10;
        }
    }
}

s32 world_to_screen(s32 *pos, s16 *sxy) {
    Camera *cam;
    s32 dx, dy, dz;
    s32 *m;
    s32 flag, t0, t1, t2;
    register s32 k __asm__("$8");
    View *v = views;

    if (cur_cam_index >= 0) {
        cam = &cameras[cur_cam_index];
        dx = pos[0] - cam->pos.vx;
        if ((u32)(dx + 0x4000) <= 0x7FFF) {
            dy = pos[1] - cam->pos.vy;
            if ((u32)(dy + 0x4000) <= 0x7FFF) {
                dz = pos[2] - cam->pos.vz;
                if ((u32)(dz + 0x4000) <= 0x7FFF) {
                    m = scratch_alloc(0x20);
                    scale_rows((s16 *)&v->unk_2C[0x34], (s16 *)&v->unk_2C[0xC], (s16 *)m);
                    gte_set_R012(t0, t1, t2, m[0], m[1], m[2]);
                    gte_set_R34(t0, t1, m[3], m[4]);
                    scratch_top -= 0x20;
                    k = 0x80;
                    gte_set_ctrl(H, k);
                    k = 0;
                    gte_set_ctrl(OFX, k);
                    gte_set_ctrl(OFY, k);
                    gte_set_ctrl(TRX, 0);
                    gte_set_ctrl(TRY, 0);
                    gte_set_ctrl(TRZ, 0);
                    gte_set(VXY0, (dy << 16) | (dx & 0xFFFF));
                    gte_set(VZ0, dz);
                    gte_rtps();
                    gte_get_ctrl(FLAG, flag);
                    gte_store(SXY2, sxy, 0);
                    if (flag >= 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void lock_draw_markers(void) {
    SelRecord *sel;
    s16 *pos;
    Slot14 *slot;
    s32 i;

    if (lock_mode != 0 && meter_is_full() != 0) {
        sel = scratch_alloc(0x10);
        pos = scratch_alloc(4);
        i = 0;
        slot = lock_slots;
        for (; i < 6; slot++, i++) {
            if (slot->id >= 0 && lock_target_sphere(lock_slots[i].flag_index, sel) &&
                world_to_screen(sel->pos, pos)) {
                s32 depth = slot->id * 6 / 0x1000;
                s32 frame = lock_frame_base + 1;
                id_table_add(pos[0], pos[1], 0x1000, depth + frame, 0, 0, 0);
            }
        }
        scratch_top -= 0x14;
    }
}
