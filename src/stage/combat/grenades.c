/* grenades: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void trail_ring_push(s32 x, s32 y, s32 z) {
    RingEntry *entry;
    s16 *pos;
    s32 head;

    x >>= 4;
    y >>= 4;
    z >>= 4;
    if (trail_ring_count != RING_SIZE) {
        trail_ring_count += 1;
        head = trail_ring_head;
        entry = &trail_ring[head % RING_SIZE];
        pos = (s16 *) entry->pos;
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
        entry->age = 0;
        trail_ring_head = (head + 1) % RING_SIZE;
    }
}

/* Ages every entry in use by one; an entry that reaches 0x28 is retired (only the oldest can be). */
void trail_ring_age(void) {
    s32 next;
    s32 index;
    s32 left;
    RingEntry *entry;
    u16 age;

    left = trail_ring_count;
    index = trail_ring_tail % RING_SIZE;
    if (left > 0) {
        do {
            entry = &trail_ring[index % RING_SIZE];
            age = entry->age + 1;
            entry->age = age;
            if ((s16)age >= 0x28) {
                trail_ring_count -= 1;
                trail_ring_tail = (trail_ring_tail + 1) % RING_SIZE;
                next = index + 1;
            }
            next = index + 1;
            left -= 1;
            index = next % RING_SIZE;
        } while (left > 0);
    }
}

static inline void spark_add_at(s16 *pos, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    s32 x = pos[0] << 4, y = pos[1] << 4, z = pos[2] << 4;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
}
/* Emits a spark at each trail ring point, fading with its age. */
void trail_sparks_emit(void) {
    s32 left;
    RingEntry *entry;
    s32 index;
    s16 *pos;
    s32 age;
    s32 level;
    s32 red;
    s32 value;
    s32 colour;
    s32 age_shade;

    left = trail_ring_count;
    index = trail_ring_tail % RING_SIZE;
    if (left > 0) {
        do {
            entry = &trail_ring[index % RING_SIZE];
            age = (s16)entry->age;
            age_shade = age / 4 + 0x20;
            level = 0x1000 - (age << 12) / 80;
            level >>= 5;
            value = spark_effect_base + age_shade;
            red = level;
            if (level == 0) {
                red = 1;
            }
            do {
                colour = (red << 16) | (level << 8) | level;
            } while (0);
            pos = (s16 *)entry->pos;
            spark_add_at(pos, value, colour);
            left -= 1;
            index = (index + 1) % RING_SIZE;
        } while (left > 0);
    }
}

void proximity_hook_clear(void) {
    proximity_hook_fn = 0;
}

void grenade_spark_set_base(s32 value) {
    grenade_effect_base = value;
}

s32 grenades_in_air(void) {
    return 1 - grenade_slots_free;
}

/* Set proximity_hook_fn and return its old value. */
s32 proximity_hook_set(s32 value) {
    s32 old;

    old = proximity_hook_fn;
    proximity_hook_fn = value;
    return old;
}

void grenade_pool_init(void) {
    s32 i;

    for (i = 0; i <= 0; i++) {
        grenade_pool[i].active = 0;
    }
    grenade_slots_free = 1;
    proximity_hook_fn = 0;
}

void *grenade_alloc(void) {
    s32 n = 0;
    s32 off;
    u8 *base;
    s32 cnt;

    if (grenade_slots_free != 0) {
        goto search;
    }
    return NULL;
claim:
    base = (u8 *)grenade_pool;
    cnt = grenade_slots_free;
    *(s16 *)((u8 *)grenade_pool + off) = 1;
    grenade_slots_free = cnt - 1;
    return base + off;
search:
    off = 0;
    do {
        if (*(s16 *)((u8 *)grenade_pool + off) == 0) {
            n++;
            goto claim;
        }
        n++;
        off += 0x30;
    } while (n <= 0);
    return NULL;
}

/* Clears *value and counts the call in grenade_slots_free. */
void grenade_free(s16 *value) {
    s32 count;

    count = grenade_slots_free;
    *value = 0;
    grenade_slots_free = count + 1;
}

/* Adds the vector get_flow_move gives (in 1/4096 units) to a position. */
void pos_drift_wind(s32 *pos) {
    s32 x = pos[0];
    s32 y = pos[1];
    s32 z = pos[2];
    s32 *delta = get_flow_move();
    s32 dx = delta[0];
    s32 dy = delta[1];
    s32 dz = delta[2];

    pos[0] = x + (dx >> 12);
    pos[1] = y + (dy >> 12);
    pos[2] = z + (dz >> 12);
}

/* Visits each actor near the query point (within range on each axis and in radius) and, when the
 * hook proximity_hook_fn is set, calls it last. Each actor near enough gets hit_target_masked with its bearing. */
void blast_hit_actors(ProximityQuery *q) {
    s32 r;
    s32 r2;
    s32 qx;
    s32 qy;
    s32 qz;
    Object *obj;
    s32 dx;
    s32 dy;
    s32 dz;

    pos_drift_wind((s32 *) q);
    r = q->range >> 12;
    qx = q->x;
    qy = q->y;
    qz = q->z;
    obj = (Object *) *get_obj_list_actors();
    r2 = r * r;
    if (obj->node.next != 0) {
        do {
            dx = (obj->x >> 12) - qx;
            dy = (obj->y >> 12) - qy;
            dz = (obj->z >> 12) - qz;
            if (ABS(dx) <= r && ABS(dy) <= r && ABS(dz) <= r) {
                if (length_sq(dx, dy, dz) < r2) {
                    hit_target_masked(obj->index, 4, (s16) atan2(dz, dx), 100);
                }
            }
            obj = (Object *)obj->node.next;
        } while (obj->node.next != 0);
    }
    if (proximity_hook_fn != 0) {
        ((void (*)(s32 *)) proximity_hook_fn)((s32 *) q);
    }
}

/* Moves a grenade by its velocity and tests the step (whole units, from the old to the new position) against
 * objects and the world; on a hit or after 0x14 frames it bursts into effects. Returns 1 when it ended. */
s32 grenade_step(GrenadeMover *r) {
    GrenadeStep *step = scratch_alloc(0); /* the 0x20 bytes are taken below, after the first store */
    u16 target;
    s32 done = 0;
    s32 *pos;

    step->from.x = r->pos[0] >> 12;
    step->from.y = r->pos[1] >> 12;
    step->from.z = r->pos[2] >> 12;
    r->pos[0] += r->vel[0];
    r->pos[1] += r->vel[1];
    r->pos[2] += r->vel[2];
    step->to.x = r->pos[0] >> 12;
    scratch_top += 0x20;
    step->to.y = r->pos[1] >> 12;
    step->to.z = r->pos[2] >> 12;
    set_collide_mode(2);
    if (trace_objects(step, &step->to, 0x10, &step->to, (s16 *)&target)) {
        if (target & 0x100) {
            hit_target_masked(target, 4, r->yaw, 0x1F4);
            add_mission_count(1);
        }
        done = 1;
    } else if (trace_world(4, 0x10, step, &step->to, &step->to)) {
        done = 1;
    }
    set_collide_mode(0);
    if ((s16)r->age > 0x14) {
        done = 1;
    }
    if (done) {
        sound_attach(sound_start(SND_PAIR(SND_LARGE_EXPLOSION | SND_GROUP(1), SND_MEDIUM_EXPLOSION | SND_GROUP(1)), 0x7F, 0, 0), &r->pos[0], NULL);
        pos = (s32 *)&step->to;
        fx_spawn_template(pos, &grenade_burst_templates[0], pos_drift_wind);
        fx_spawn_template(pos, &grenade_burst_templates[1], blast_hit_actors);
        fx_spawn_template(pos, &grenade_burst_templates[2], pos_drift_wind);
    }
    scratch_top -= 0x20;
    return done;
}

void grenades_update(void) {
    GrenadeMover *r = grenade_pool;
    s32 i = 0;
    s32 *delta;

    do {
        if (r->active != 0) {
            r->age += 1;
            angles_to_vector(r->yaw, r->pitch, r->speed, &r->vel[0], &r->vel[1], &r->vel[2]);
            delta = get_flow_move();
            r->vel[0] += delta[0];
            r->vel[1] += delta[1];
            r->vel[2] += delta[2];
            if (grenade_step(r) == 1 || cam_range_check_alt(r->pos[0] >> 12, r->pos[1] >> 12, r->pos[2] >> 12) == 0) {
                grenade_free(&r->active);
            }
        }
        i++;
        r++;
    } while (i <= 0);
}

/* Adds a spark (no rotation, colour 0) at each active grenade's position
 * (spark_add_head written out: the model value is allocated first). */
void grenade_sparks_emit(void) {
    GrenadeMover *mover = grenade_pool;
    s32 i = 0;

    do {
        if (mover->active != 0) {
            s32 value = pool_spawn_scaled(grenade_effect_base + 0xF, 0x800, 0x800, 0x800);
            s32 n = spark_count;
            s32 x = mover->pos[0] >> 12;
            s32 y = mover->pos[1] >> 12;
            s32 z = mover->pos[2] >> 12;
            SparkList *list = &spark_list;
            SparkRec *s;
            u8 *tail;

            if (n < 0xFF) {
                s = &list->items[n];
                n++;
                spark_count = n;
                *(s32 *)s->colour = 0;
                tail = spark_list_tail;
                spark_list_tail = &s->next;
                *tail = n;
                s->next = 0;
                s->x = x;
                s->y = y;
                s->z = z;
                /* the nested loops raise value's register priority */
                do {
                    do {
                        s->unk_12 = value;
                    } while (0);
                } while (0);
                s->yaw = 0;
                s->pitch = 0;
                s->roll = 0;
            }
        }
        i++;
        mover++;
    } while (i <= 0);
}

/* Starts a grenade from pos (whole units) with the aim in aim: takes a free mover record (grenade_alloc) and
 * sets it up with a speed of 0x28. */
void launch_grenade(Vec3 *pos, AimPacket *aim) {
    GrenadeMover *shot = (GrenadeMover *) grenade_alloc();

    if (shot != NULL) {
        shot->pos[0] = pos->x << 12;
        shot->pos[1] = pos->y << 12;
        shot->pos[2] = pos->z << 12;
        *(AimPacket *) &shot->pitch = *aim;
        shot->age = 0;
        shot->speed = 0x28;
        sound_start(SND_GRENADE_LAUNCH | SND_GROUP(1), 0x64, 0, 0);
    }
}

void fn_801090F8(void) {

}
