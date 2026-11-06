/* grid_hooks: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void grid_camera_reset(void) {
    grid_camera_phase = 0;
}

/* Clears the 0x80 IntPair entries of hook_table (8 bytes each), then sets the used index range. */
void hook_table_clear(void) {
    s32 offset;

    for (offset = 0; offset < 0x400; offset += sizeof(IntPair)) {
        *(s32 *)((u8 *)hook_table + offset) = 0;
        *(s32 *)((u8 *)hook_table + offset + 4) = 0;
    }
    hook_range_lo = 0x7F;
    hook_range_hi = 0;
}

/* Sets pair `index` (< 128) of hook_table and widens the used index range. */
void hook_set(u32 index, s32 a, s32 b) {
    s32 lo;
    s32 hi;

    if (index < 0x80) {
        lo = hook_range_lo;
        hook_table[index].a = a;
        hook_table[index].b = b;
        if ((s32)index < lo) {
            lo = index;
        }
        hi = hook_range_hi;
        hook_range_lo = lo;
        if (hi < (s32)index) {
            hi = index;
        }
        hook_range_hi = hi;
    }
}

/* Calls the function in each hook_table entry from hook_range_lo up to hook_range_hi (inclusive). */
void hook_run_all(void) {
    s32 i;

    for (i = hook_range_lo; i <= hook_range_hi; i++) {
        void (*fn)(void) = (void (*)(void))hook_table[i].a;

        if (fn != NULL) {
            fn();
        }
    }
}

s32 grid_collect_kind(s32 kind, GridEntry **out) {
    s32 zero;
    GridEntry *entry;
    s32 i;
    s32 found;
    s32 unused;

    entry = grid_entries;
    if (entry == NULL) {
        return 0;
    }
    i = 0;
    zero = 0;
    found = 0;
    if (grid_entry_total > zero) {
        do {
            if (entry->kind == kind) {
                *(out++) = entry;
                found++;
            }
            i++;
            entry++;
        } while (i < grid_entry_total);
    }
    return found;
}

/* Copies the pending grid entries flagged with bit 3 into out[]; returns how many. */
s32 grid_collect_flagged(GridEntry **out) {
    s32 frame_pad; /* unused; the original reserves an 8-byte frame */
    GridEntry *entry;
    s32 i;
    s32 count;

    entry = grid_entries;
    if (entry == NULL) {
        return 0;
    }
    count = 0;
    for (i = 0; i < grid_entry_total; i++, entry++) {
        if (entry->flags & 8) {
            *out++ = entry;
            count++;
        }
    }
    return count;
}

/* Starts a grid load from a block whose first halfword is the byte offset of its header. The block is kept
 * in grid_block, the entries in grid_entries and their count in grid_entry_total. */
void grid_load(s32 block) {
    GridHeader *header;
    s32 count;

    grid_block = block;
    grid_entry_total = 0;
    grid_entries = NULL;
    if (block != 0) {
        header = (GridHeader *) (block + *(s16 *) block);
        count = header->count;
        grid_entries = header->entries;
        grid_entry_total = count;
        grid_entries_init_state(header->count, grid_entries); /* a field read: may move above the global stores */
    }
}

s32 grid_count(void) {
    return grid_entry_total;
}

GridEntry *grid_entry(s32 index) {
    return &grid_entries[index];
}

/* Returns grid_block advanced by the s16 at table entry `index` (+2 offset), or 0 when the table is unset. */
s32 grid_block_get(s32 index) {
    s32 base = grid_block;

    if (base != 0) {
        base += ((s16 *) (base + index * 2))[1];
    }
    return base;
}

void grid_entries_init_state(s32 count, GridEntry *entries) {
    s32 i;
    s32 unused;

    i = 0;
    while (i < count) {
        GridEntryState *e = (GridEntryState *)&entries->flags;
        e[i].state2 = (e[i].state2 & 0xFC) | 1;
        e[i].state = (e[i].state & 0xFC) | 1;
        i++;
    }
}

void pending_grid_reset_saved(void) {
    pending_grid_reset(0);
}

void pending_grid_reset_state1(void) {
    pending_grid_reset(1);
}

/* Empties every bucket of the pending grid and the pending list, restores each GridEntry from its saved
 * copy at +0x20 (mode 1 first sets the saved state bits to 1) and files it again. */
void pending_grid_reset(s32 mode) {
    s16 *buckets;
    s32 empty;
    GridEntry *entry;
    s32 i;
    s32 delay;

    empty = -0x8000;
    buckets = grid_buckets;
    for (i = 0x3FF; i >= 0; i--) {
        buckets[i] = empty;
    }
    buckets[0x400] = -0x8000;
    buckets[0x401] = -0x8000;
    entry = grid_entries;
    for (i = 0; i < grid_entry_total; i++, entry++) {
        /* mode: mark the pending copy's state as 1 */
        if (mode != 0) {
            entry->unk_14[0x10] = (entry->unk_14[0x10] & 0xFC) | 1;
        }
        /* commit the pending copy (entry+0x20) into the live half */
        *(GridEntryHalf *)entry = *(GridEntryHalf *)&entry->unk_14[0xC];
        delay = entry->delay;
        if (delay != 0) {
            buckets[delay & 0x7FFF] = i;
            entry->delay = 0;
        }
    }
}

void grid_active_set(s32 value) {
    grid_active_flag = value;
}

s32 grid_active_get(void) {
    return grid_active_flag;
}

void cam_range_set(s32 x, s32 y, s32 z) {
    cam_range_radius = x;
    cam_range_below = y;
    cam_range_above = z;
}

void cam_range_alt_set(s32 x, s32 y, s32 z) {
    cam_range_alt_radius = x;
    cam_range_alt_below = y;
    cam_near_above = z;
}

/* Returns 1 if an active camera (unk_1E set, unk_1C clear) lies within the
 * horizontal radius cam_range_radius of (x, z) and the height window
 * [-cam_range_below, cam_range_above] around y; 0 otherwise.
 * Old-style definition: some callers pass a fourth argument (unused). */
s32 cam_range_check(x, y, z)
    s32 x, y, z;
{
    Camera *cam;
    Camera *camX;
    Camera *prev;
    Camera *last;
    s32 radius = cam_range_radius;
    s32 radiusSq = radius * radius;
    s32 dx, dy, dz, absDx, distXSq, distZSq;
    s32 found;
    s32 dyMin;
    s32 below = cam_range_below;
    s32 above = cam_range_above;

    camX = cameras;
    last = camX + 8;
    gte_set(IR1, 0);
    dyMin = -below;
    found = 1;
    cam = camX;
    do {
        if (cam->user_count != 0 && cam->rec_index == 0) {
            dx = x - camX->pos.vx;
            dz = z - cam->pos.vz;
            gte_set(IR2, dx);
            absDx = dx;
            if (absDx < 0) absDx = -absDx;
            if (absDx <= radius) {
                gte_set(IR3, dz);
                if (ABS(dz) <= radius) {
                    gte_sqr0_b();
                    dy = cam->pos.vy;
                    gte_get(MAC2, distXSq);
                    gte_get(MAC3, distZSq);
                    gte_nop();
                    dy = y - dy;
                    if (distXSq + distZSq <= radiusSq && dy >= dyMin && dy <= above)
                        goto done;
                }
            }
        }
        prev = cam;
        cam++;
        camX++;
    } while (prev != last);
    found = 0;
done:
    return found;
}

/* Same code as cam_range_check (s01). */
s32 cam_range_check_alt(x, y, z)
    s32 x, y, z;
{
    Camera *cam;
    Camera *camX;
    Camera *prev;
    Camera *last;
    s32 radius = cam_range_alt_radius;
    s32 radiusSq = radius * radius;
    s32 dx, dy, dz, absDx, distXSq, distZSq;
    s32 found;
    s32 dyMin;
    s32 below = cam_range_alt_below;
    s32 above = cam_near_above;

    camX = cameras;
    last = camX + 8;
    gte_set(IR1, 0);
    dyMin = -below;
    found = 1;
    cam = camX;
    do {
        if (cam->user_count != 0 && cam->rec_index == 0) {
            dx = x - camX->pos.vx;
            dz = z - cam->pos.vz;
            gte_set(IR2, dx);
            absDx = dx;
            if (absDx < 0) absDx = -absDx;
            if (absDx <= radius) {
                gte_set(IR3, dz);
                if (ABS(dz) <= radius) {
                    gte_sqr0_b();
                    dy = cam->pos.vy;
                    gte_get(MAC2, distXSq);
                    gte_get(MAC3, distZSq);
                    gte_nop();
                    dy = y - dy;
                    if (distXSq + distZSq <= radiusSq && dy >= dyMin && dy <= above)
                        goto done;
                }
            }
        }
        prev = cam;
        cam++;
        camX++;
    } while (prev != last);
    found = 0;
done:
    return found;
}

/* 1 if an active camera of group 0 is within the entry's range (flags 4: wide range, 0x10: half radius). */
s32 grid_entry_near_camera(GridEntry *entry, s32 flags) {
    CameraReach *range = &camera_reach_normal;
    Camera *cam;
    Camera *end;
    s32 x, y;
    register s32 z asm("$3"); /* the original keeps z in v1 */
    s32 radius, below, max_dy, r2;
    s32 dx, dz, dy, sx, sz;
    s32 found;
    s32 min_dy;

    if (flags & 4) {
        range = &camera_reach_wide;
    }
    radius = range->radius;
    below = range->below - 0x180;
    max_dy = range->above - 0x180;
    if (flags & 0x10) {
        radius /= 2;
    }
    radius -= 0x180;
    r2 = radius * radius;
    cam = cameras;
    end = &cameras[8];
    x = entry->x >> 12;
    y = entry->y >> 12;
    z = entry->z >> 12;
    gte_set(IR1, 0);
    min_dy = -below;
    found = 1;
    do {
        if (cam->user_count != 0 && cam->rec_index == 0) {
            dx = x - cam->pos.vx;
            dz = z - cam->pos.vz;
            gte_set(IR2, dx);
            if (ABS(dx) <= radius) {
                gte_set(IR3, dz);
                if (ABS(dz) <= radius) {
                    gte_sqr0_b();
                    dy = cam->pos.vy;
                    gte_get(MAC2, sx);
                    gte_get(MAC3, sz);
                    gte_nop();
                    dy = y - dy;
                    if (r2 >= sx + sz && dy >= min_dy && dy <= max_dy) {
                        goto done;
                    }
                }
            }
        }
    } while (cam++ != end);
    found = 0;
done:
    return found;
}

void grid_camera_step(void) {
    s32 phase = grid_camera_phase;
    Camera *cam;
    Camera *cam_b;
    Camera *end;
    Camera *prev;
    s32 z, j, x, i;
    s16 row;

    grid_camera_phase = (phase + 1) % 4;
    if (phase == 0 && grid_entry_total != 0 && grid_active_flag != 0) {
        cam_b = cameras;
        end = cam_b + 8;
        cam = cam_b;
        do {
            if (cam->user_count != 0 && cam->rec_index == 0) {
                z = cam->pos.vz - 0x1800;
                x = cam_b->pos.vx - 0x1800;
                for (i = 0; i < 7; i++) {
                    row = ((u32)(x + 0x8000) >> 6) & 0x3E0;
                    for (j = 0; j < 7; j++) {
                        grid_bucket_release((((z + 0x8000) & 0xFFFF) >> 11) | row);
                        z += 0x800;
                    }
                    z -= 0x3800;
                    x += 0x800;
                }
            }
            prev = cam;
            cam++;
            cam_b++;
        } while (prev != end);
        grid_bucket_release(0x400);
    }
}

/* Calls the handler of the grid entry's kind (below 0x80) from grid_kind_handlers; 0 when there is none. */
s32 grid_entry_handle(GridEntry *entry) {
    u8 kind = entry->kind;

    if (kind < 0x80) {
        if (grid_kind_handlers[kind].handler != NULL) {
            return grid_kind_handlers[kind].handler(entry);
        }
    }
    return 0;
}

/* Walks one bucket of the grid and moves the entries that are ready to the free list (the bucket after
 * the overflow one). */
void grid_bucket_release(s32 bucket) {
    s16 *link = &grid_buckets[(s16)bucket];
    s32 index = *link;
    GridEntry *entry;
    u8 flags;

    while (index >= 0 && grid_active_flag != 0) {
        entry = &grid_entries[index];
        flags = entry->flags;
        if ((flags & 3) == 1 && grid_entry_near_camera(entry, flags) != 0 &&
            ((entry->flags & 0x10) || grid_entry_handle(entry) != 0)) {
            entry->flags &= 0xFC;
            *link = entry->next;
            entry->next = grid_buckets[0x401];
            grid_buckets[0x401] = index;
        } else {
            link = &entry->next;
        }
        index = *link;
    }
}

/* Moves due entries from the pending list into the grid bucket of their x/z position. */
void grid_pending_step(void) {
    s16 *link;
    u16 index;
    GridEntry *entry;
    s32 state;
    s32 cell;
    s32 x;
    s32 z;

    link = &grid_pending_head;
    for (index = *link; (s16)index >= 0; index = *link) {
        entry = &grid_entries[(s16)index];
        state = entry->flags & 3;
        if (state == 0) {
            if (!(entry->flags & 0x10) || grid_active_flag == 0 || grid_entry_near_camera(entry, entry->flags & 0xEF) == 1
                || grid_entry_handle(entry) == 0) {
                goto next;
            }
            entry->flags &= 0xEF;
        }
        if (state == 3 || entry->delay < 0) {
            /* drop it; this also ends the walk */
            entry->flags |= 3;
            *link = entry->next;
            entry->next = LIST_END;
        } else if (entry->delay > 0) {
            entry->delay--;
        } else if ((entry->flags & 3) == 1 || grid_entry_near_camera(entry, entry->flags) == 0) {
            entry->flags = (entry->flags & 0xFC) | 1;
            if (entry->unk_06 == 0) {
                z = entry->z >> 12;
                x = entry->x >> 12;
                cell = (((z + 0x8000) & 0xFFFF) >> 11) | (((u32)(x + 0x8000) >> 6) & 0x3E0);
            } else {
                cell = 0x400;
            }
            *link = entry->next;
            entry->next = grid_buckets[cell];
            grid_buckets[cell] = index;
            continue;
        }
    next:
        link = &entry->next;
    }
}

void obj_hits_reset_all(void) {
    s16 i;

    for (i = 0; i < 0x60; i++) {
        obj_hit_clear(i);
        obj_hit_flag_set(i, 0);
        obj_hit_set_unk08(i, -1);
        obj_hit_set_unk06(i, 0);
    }
    for (i = 0; i < 8; i++) {
        halfpair_reset(i);
    }
}

/* Clear entry `index` (mod 128) of the table at 0x801396D0. */
void obj_hit_clear(s32 index) {
    ObjHit *hit = &obj_hits[index & 0x7F];

    hit->from = -1;
    hit->damage = 0;
    hit->type = 0;
    hit->unk_0C = 0;
}

void hit_target(s32 slot, s32 mask, s16 from, s16 power, s32 flags)
{
    ObjHit *hit;
    HalfPair *pair;
    s32 lz;
    s16 bit;
    s32 dmg;
    s32 types;

    /* LZCS = mask, through a copy kept in types */
    gte_set_copy(LZCS, types, mask);
    if (types & 0xFF) {
        gte_get(LZCR, lz);
        bit = 31 - lz;
        if (bit < 7) {
            hit = &obj_hits[slot & 0x7F];
            if (hit->flags & mask) {
                return;
            }
            pair = &half_pairs[bit];
            dmg = power;
            if ((pair->b & 1) && (hit->type & mask)) {
                return;
            }
            if (hit->flags & 0x80) {
                dmg = dmg * pair->a / 4096;
            }
            dmg += hit->damage;
            dmg = MAX(MIN(dmg, 0x7FFF), 0);
            hit->from = from;
            hit->damage = dmg;
            hit->type |= types;
            hit->unk_0C |= flags;
        }
    }
}

/* hit_target on object `target` with the 8-bit type mask. */
void hit_target_masked(s16 target, s32 type, s16 from, s16 damage) {
    hit_target(target, type & 0xFF, from, damage, -1);
}

s16 obj_hit_from(s32 i) {
    return obj_hits[i & 0x7F].from;
}

/* The halfword at 0x02 of entry `index` (mod 128) of the table at 0x801396D0. */
s16 obj_hit_damage(s32 index) {
    return obj_hits[index & 0x7F].damage;
}

u8 obj_hit_type(s32 index) {
    return obj_hits[index & 0x7F].type;
}

void obj_hit_flag_set(s32 index, s32 value) {
    obj_hits[index & 0x7F].flags = value;
}

u8 obj_hit_flag_get(s32 index) {
    return obj_hits[index & 0x7F].flags;
}

/* Resets one of the 8 halfword pairs at half_pairs to (0x1000, 0). */
void halfpair_reset(s32 index) {
    HalfPair *pair = &half_pairs[index & 7];

    pair->a = 0x1000;
    pair->b = 0;
}

void pair_set_a(s32 index, s32 value) {
    *(s16 *)&half_pairs[index & 7] = value;
}

s16 pair_get_a(s32 index) {
    return half_pairs[index & 7].a;
}

void pair_set_b(s32 index, s32 value) {
    half_pairs[index & 7].b = value;
}

s16 half_pair_b_get(s32 index) {
    return (&d_801370FE)[index & 7];
}

s32 obj_hit_get_unk0c(s32 i) {
    return obj_hits[i & 0x7F].unk_0C;
}

/* Set the word at 0x08 of entry `index` (mod 128) of the table at 0x801396D0. */
void obj_hit_set_unk08(s32 index, s32 value) {
    obj_hits[index & 0x7F].unk_08 = value;
}

s32 obj_hit_get_unk08(s32 index) {
    return obj_hits[index & 0x7F].unk_08;
}

void obj_hit_set_unk06(s32 index, s32 value) {
    if (value >= 0) {
        value = MAX(MIN(value, 0x1F), 0);
    }
    obj_hits[index & 0x7F].unk_06 = value;
}

s32 obj_hit_get_unk06(s32 index) {
    return obj_hits[index & 0x7F].unk_06;
}
