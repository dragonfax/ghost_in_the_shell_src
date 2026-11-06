/* object_slots: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void aim_marker_draw(s32 kind, SVECTOR *rot, Vec3 *pos, SVECTOR *angles) {
    s32 pitch, yaw, roll;
    s32 *matrix;
    s32 *ray;
    s32 x, y, z;
    s32 rot_x, rot_z;
    s32 dist;
    s32 clamped;
    s32 level;
    s32 handle;
    s32 hi;
    /* the matrix words go through the original's registers (v1, a0, v0): plain locals fold into the asm */
    register s32 word0 asm("$3");
    register s32 word1 asm("$4");
    register s32 word2 asm("$2");

    matrix = scratch_alloc(0x20);
    if (angles == 0) {
        roll = 0;
        pitch = 0;
        yaw = 0;
    } else {
        pitch = angles->vx;
        yaw = angles->vy;
        roll = angles->vz;
    }
    rot_matrix(matrix, yaw, pitch, roll);
    word0 = matrix[0];
    word1 = matrix[1];
    word2 = matrix[2];
    gte_set_ctrl(R11R12, word0);
    gte_set_ctrl(R13R21, word1);
    gte_set_ctrl(R22R23, word2);
    word0 = matrix[3];
    word1 = matrix[4];
    gte_set_ctrl(R31R32, word0);
    gte_set_ctrl(R33, word1);
    scratch_top -= 0x20;
    x = pos->x >> 12;
    y = pos->y >> 12;
    z = pos->z >> 12;
    pos = scratch_alloc(0x20);
    ray = (s32 *)pos; /* ray[0..2]: from (then the hit point), ray[4..6]: to */
    gte_set_ctrl(TRX, x);
    gte_set_ctrl(TRY, y);
    gte_set_ctrl(TRZ, z);
    ray[4] = 0;
    ray[5] = 0x600;
    ray[6] = 0;
    rotate_vector_inverse((VECTOR *)&ray[4], (VECTOR *)&ray[4]);
    ray[0] = x;
    ray[1] = y;
    ray[2] = z;
    rot_x = rot->vx;
    rot_z = rot->vz;
    if (trace_world(kind, 8, ray, &ray[4], ray) != 0) {
        dist = isqrt(length_sq(ray[0] - x, ray[1] - y, ray[2] - z));
        clamped = MAX(MIN(dist, 0x600), 0);
        dist = ((0x600 - clamped) << 12) / 3072;
        x = ray[0];
        y = ray[1];
        z = ray[2];
        handle = pool_spawn_scaled(impact_effect_base, (rot_x << 12) / 168, 0x1000, (rot_z << 12) / 168);
        level = dist >> 5;
        hi = level;
        if (level == 0) {
            hi = 1;
        }
        spark_add(x, y, z, yaw, pitch, roll, handle, (hi << 16) | (level << 8) | level);
    }
    scratch_top -= 0x20;
}

void fn_80107188(void) {

}

/* Sets object_slots_free to 8, then marks all eight object_slots records as free (age -1). */
void object_slots_reset(void) {
    s32 offset;
    s32 age;
    object_slots_free = 8;
    age = -1;
    for (offset = 7 * sizeof(Record); offset >= 0; offset -= sizeof(Record)) {
        *(s16 *)((u8 *)object_slots + offset) = age;
    }
}

/* Claims a free object slot (age < 0): resets its age and counts it; NULL when all 8 are in use. */
Record *object_alloc(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (object_slots[i].age < 0) {
            object_slots[i].age = 0;
            object_slots_free--;
            return &object_slots[i];
        }
    }
    return NULL;
}

void record_free(Record *record) {
    s32 count = object_slots_free;

    record->age = -1;
    object_slots_free = count + 1;
}

s32 object_free_count(void) {
    return object_slots_free;
}

/* out = rotation matrix * (x, y, z) >> 12 */
void rot_mul_vec(s32 x, s32 y, s32 z, s32 *out) {
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_rtirtr();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
}

void pchr_burst_init(PchrBurstFx *fx, s32 *src_hdr) {
    s32 *m = scratch_alloc(0x20);
    PchrBurstSource *src;
    PchrBurstPart *part;
    s32 n;
    s32 *vel;
    s32 a, b, c;
    s32 r0, r1, r2;

    rot_matrix_b(m, -fx->ry, -fx->rx, -fx->rz);
    r0 = m[0];
    r1 = m[1];
    r2 = m[2];
    __asm__ volatile("" : : : "memory");
    gte_set_ctrl(R11R12, r0);
    gte_set_ctrl(R13R21, r1);
    gte_set_ctrl(R22R23, r2);
    r0 = m[3];
    r1 = m[4];
    __asm__ volatile("" : : : "memory");
    gte_set_ctrl(R31R32, r0);
    gte_set_ctrl(R33, r1);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    rot_mul_vec(0, 0x1800, 0, fx->dir);
    src_hdr += 1;
    n = src_hdr[-1];
    src = (PchrBurstSource *)src_hdr;
    part = fx->parts;
    fx->count = n;
    if (n > 0) {
        do {
            part->pos[0] = src->pos[0] << 12;
            part->pos[1] = src->pos[1] << 12;
            part->pos[2] = src->pos[2] << 12;
            a = rand_a_next() * 3 * 8 / 4096 - 0xC;
            b = -(rand_a_next() * 9 * 2) / 4096 - 0x16;
            c = rand_a_next() * 3 * 8 / 4096 - 0xC;
            vel = part->vel;
            gte_set(IR1, a);
            gte_set(IR2, b);
            gte_set(IR3, c);
            gte_rtirtr_sf0();
            gte_stlvnl(vel);
            n--;
            part->a = src->a;
            part->b = src->b;
            part->c = src->c;
            part->r = 0x55;
            part->g = 0xAA;
            part->z = 0;
            src++;
            part++;
        } while (n > 0);
    }
    scratch_top -= 0x20;
}

void obj_recs_init(ObjRecTable *obj, Src80107478 *src) {
    s32 count;
    ObjRec *rec;
    s16 *base;
    s16 *vec;
    s32 v;

    count = *src->count_ptr;
    obj->count = count;
    rec = obj->recs;
    base = src->data;
    vec = base + 2;
    if (count > 0) {
        do {
            rec->unk_00 = 0;
            rec->unk_04 = 0;
            rec->unk_08 = 0;
            rec->pos_x = ((s32) *vec << 12) / 32;
            v = ((s32) vec[1] << 12) / 6;
            if (v > -0x1C000) {
                v = -0x1C000;
            }
            rec->pos_y = v;
            rec->pos_z = ((s32) vec[2] << 12) / 32;
            rec->unk_18[0] = 0;
            rec->unk_18[1] = 0;
            rec->unk_18[2] = 0;
            rec->unk_18[3] = 0;
            rec->unk_18[4] = 0;
            rec->unk_18[5] = 0;
            count--;
            vec += 4;
            rec++;
        } while (count > 0);
    }
}

void rot_up_vector(s16 *rot, s32 *out) {
    s32 *m;
    s32 ry = rot[1], rx = rot[0], rz = rot[2];

    m = (s32 *)scratch_top;
    scratch_top += 0x20;
    rot_matrix(m, ry, rx, rz);
    gte_load_R_v1a0v0(m);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    rot_mul_vec(0, -0x100, 0, out);
    out[1] = (out[1] - 0x100) / 2;
    scratch_top -= 0x20;
}

/* Spawns pchr entry `index` at `pos` with the 8-byte angle block `rot`, plus its effect. */
void object_spawn_at(void *pos, void *rot, s32 index) {
    Pchr *entry;
    PchrSpawn *spawn;
    Vec3 *offset;
    s32 *model;
    s16 *count;
    Pchr *table;
    u32 byte_offset;

    if (object_free_count() != 0) {
        count = &pchr_count;
        if (index >= *count) {
            return;
        }
        byte_offset = (index & 0x7FF) * sizeof(Pchr);
        table = (Pchr *) (count + 2); /* pchr_table follows the count */
        entry = (Pchr *) (byte_offset + (u8 *) table);
        if (entry->bounds_radius != 0 && entry->unk_0C != 0) {
            spawn = (PchrSpawn *) object_alloc();
            spawn->pchr = index;
            spawn->pos = *(SpawnPos *) pos;
            spawn->rot = *(UnalignedVec *) rot;
            spawn->unk_2C = entry->bounds_radius;
            model = entry->unk_0C;
            if (model != 0) {
                pchr_burst_init((PchrBurstFx *) spawn, model);
                offset = scratch_alloc(0x10);
                rot_up_vector(rot, (s32 *) offset);
                spawn_effect(((SpawnPos *) pos)->v[0] + offset->x, ((SpawnPos *) pos)->v[1] + offset->y,
                             ((SpawnPos *) pos)->v[2] + offset->z, 0);
                scratch_top -= 0x10;
            }
        }
    }
}

void record_update(Record *record) {
    RecordBody *rec = (RecordBody *)record;
    RecordEntry *entry;
    s32 count;

    count = rec->count;
    entry = rec->entries;
    if (count > 0) {
        do {
            entry->vel[0] = CLAMP_HI(entry->vel[0] + rec->accel[0], 0x1C000);
            entry->vel[1] = CLAMP_HI(entry->vel[1] + rec->accel[1], 0x1C000);
            entry->vel[2] = CLAMP_HI(entry->vel[2] + rec->accel[2], 0x1C000);
            entry->pos[0] += entry->vel[0];
            entry->pos[1] += entry->vel[1];
            entry->pos[2] += entry->vel[2];
            entry->ang[0] += entry->ang_vel[0];
            entry->ang[1] += entry->ang_vel[1];
            entry->ang[2] += entry->ang_vel[2];
            count--;
            entry++;
        } while (count > 0);
    }
}

void records_step(void) {
    s32 i;
    s16 age;
    Record *r;

    for (i = 0; i < 8; i++) {
        if (object_slots[i].age >= 0) {
            r = &object_slots[i];
            record_update(r);
            age = (u16)object_slots[i].age + 1;
            r->age = age;
            if (age >= 0x28) {
                record_free(r);
            }
        }
    }
}

/* Converts the list to whole units when the counts agree. */
void point_list_to_units(PointListIn *in, PointListOut *out) {
    s32 n = in->count;
    PointIn *src;
    PointOut *dst;

    if (n == out->count) {
        dst = out->points;
        src = in->points;
        if (n > 0) {
            do {
                dst->x = src->x >> 12;
                dst->y = src->y >> 12;
                dst->z = src->z >> 12;
                dst->yaw = src->yaw & 0xFFF;
                dst->pitch = src->pitch & 0xFFF;
                dst->roll = src->roll & 0xFFF;
                n--;
                src++;
                dst++;
            } while (n > 0);
        }
    }
}

void spark_spawn_from_records(void) {
    Record *rec;
    s32 *up;
    s32 i;
    s32 index;
    s32 *poses;
    Pchr *pchr;
    s32 fade;
    s32 red, green, blue;
    s32 colour;
    s32 n;
    SparkList *list;
    Pchr *table;
    s32 ry, rx, rz;
    s32 cell;
    s32 px, py, pz;
    SparkRec *spark;
    u8 *tail;

    rec = object_slots;
    up = scratch_alloc(0x10);
    rot_up_vector(rec->rot, up);
    for (i = 0; i < 8; i++, rec++) {
        if (rec->age >= 0) {
            if (rec->age == 0xC) {
                spawn_effect(rec->x + up[0], rec->y + up[1], rec->z + up[2], 0);
            }
            pchr_lists_build(rec->pchr_slot);
            index = pchr_copy_slot(rec->pchr_slot);
            poses = pchr_poses_build(index);
            cell = index & 0x7FF;
            table = pchr_table;
            pchr = &table[cell];
            pchr->unk_0C = poses;
            if (rec->unk_30 == *poses) {
                pchr->bounds_radius = rec->unk_2C * 2;
                point_list_to_units((PointListIn *)rec, (PointListOut *)poses);
                fade = 0x1000 - ((rec->age << 12) / 56);
                red = (fade * 0xFFF) / 4096 + 0x1000;
                green = (fade / 2) + 0x1000;
                blue = (-fade / 2) + 0x1000;
                red >>= 5;
                green >>= 5;
                blue >>= 5;
                if ((red | green | blue) == 0) {
                    blue = 1;
                }
                colour = (blue << 16) | (green << 8) | red;
                list = &spark_list;
                n = spark_count;
                ry = rec->rot[1];
                rx = rec->rot[0];
                rz = rec->rot[2];
                px = rec->x;
                py = rec->y;
                pz = rec->z;
                if (n < 0xFF) {
                    spark = &list->items[n];
                    n++;
                    spark_count = n;
                    *(s32 *)spark->colour = colour;
                    tail = list->tail[colour >> 24];
                    list->tail[colour >> 24] = &spark->next;
                    *tail = n;
                    spark->next = 0;
                    spark->x = px;
                    spark->y = py;
                    spark->z = pz;
                    spark->unk_12 = index;
                    spark->yaw = ry;
                    spark->pitch = rx;
                    spark->roll = rz;
                }
            }
        }
    }
    scratch_top -= 0x10;
}

void fn_80107C14(void) {

}

void spark_set_effect_base(s32 value) {
    spark_effect_base = value;
}
