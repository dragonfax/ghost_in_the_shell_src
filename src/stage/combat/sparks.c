/* sparks: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void sparks_reset(void) {
    s32 off;

    for (off = 7 * sizeof(Spark); off >= 0; off -= sizeof(Spark)) {
        *(s16 *)((u8 *)spark_pool + off) = 0;
    }
    spark_free_count = 8;
    trail_ring_reset();
}

/* Takes a free spark from spark_pool (marks it active, one fewer free); NULL when none is free. */
void *spark_alloc(void) {
    s32 i;

    if (spark_free_count == 0) {
        return NULL;
    }
    for (i = 0; i < 8; i++) {
        if (spark_pool[i].active == 0) {
            spark_pool[i].active = 1;
            spark_free_count--;
            return &spark_pool[i];
        }
    }
    return NULL;
}

void spark_free(s16 *p) {
    s32 count = spark_free_count;

    *p = 0;
    spark_free_count = count + 1;
}

/* Moves a spark by its velocity. */
void spark_move(Spark *spark) {
    spark->x += spark->vx;
    spark->y += spark->vy;
    spark->z += spark->vz;
}

/* Moves a spark by its velocity and traces the step: returns 1 when it hit an object or the world, or lived past
 * 0x78 steps (spawning the effect at the hit point); a hit on an object with bit 0x100 set also hurts it. */
s32 spark_move_trace(Spark *spark) {
    register s32 collided asm("$19");
    TraceScratch *trace;
    s16 target;

    collided = 0;
    trace = scratch_alloc(sizeof(TraceScratch));

    trace->from.x = spark->prev[0] >> 12;
    trace->from.y = spark->prev[1] >> 12;
    trace->from.z = spark->prev[2] >> 12;
    spark->x += spark->vx;
    spark->y += spark->vy;
    spark->z += spark->vz;
    trace->to.x = spark->x >> 12;
    trace->to.y = spark->y >> 12;
    trace->to.z = spark->z >> 12;
    spark->prev[0] = spark->x;
    spark->prev[1] = spark->y;
    spark->prev[2] = spark->z;

    set_collide_mode(2);
    if (trace_objects(trace, &trace->to, 0x10, &trace->hit, &target) != 0) {
        if ((u16)target & 0x100) {
            hit_target(target, 2, spark->yaw, 0x90, 1 << trace->unk_2C);
            add_mission_count(1);
        }
        collided = 1;
    } else if (trace_world(4, 0x10, trace, &trace->to, &trace->hit) != 0 || spark->age >= 0x79) {
        collided = 1;
    }
    set_collide_mode(0);
    if (collided) {
        spawn_effect(trace->hit.x, trace->hit.y, trace->hit.z, 2);
    }
    scratch_top -= sizeof(TraceScratch);
    return collided;
}

void spark_steer_to_target(Spark *spark) {
    Object *target;
    s32 *aim;
    s32 yaw;
    s32 pitch;
    s32 dx, dy, dz;
    s32 part;

    aim = (s32 *)scratch_alloc(0x10);
    if (spark->target != 0) {
        target = obj_table[spark->target & 0x7F];
        if ((u8)target->unk_17A != 0 && test_bit(target->flags, 5)) {
            part = obj_hit_get_unk06(target->index);
            if (part >= 0) {
                if (solid_part_pos(target->solid_id, part, aim) == 0) {
                    goto clear;
                }
            } else {
                s32 height, top;

                aim[0] = target->x >> 12;
                height = (s16)target->height;
                top = target->y >> 12;
                aim[1] = top - height / 2;
                aim[2] = target->z >> 12;
            }
            dx = aim[0] - (spark->x >> 12);
            dy = aim[1] - (spark->y >> 12);
            dz = aim[2] - (spark->z >> 12);
            vector_to_angles(dx, dy, dz, &yaw, &pitch);
            if (isqrt(length_sq(dx, dy, dz)) < spark->speed * 8) {
                spark->yaw = angle_approach(spark->yaw, yaw, spark->speed * 30);
                spark->pitch = angle_approach(spark->pitch, -pitch, spark->speed * 24);
            } else {
                spark->yaw = angle_approach(spark->yaw, yaw, spark->speed * 10);
                spark->pitch = angle_approach(spark->pitch, -pitch, spark->speed * 8);
            }
            goto done;
        }
    clear:
        spark->target = 0;
    }
done:
    scratch_top -= 0x10;
}

/* Steps the 8 sparks: ages them, leaves a trail, bends their velocity by the wind and checks for hits. */
void sparks_step(void) {
    s32 i;
    Spark *spark = spark_pool;
    s32 *wind;

    for (i = 0; i < 8; i++, spark++) {
        if (spark->active == 0) {
            continue;
        }
        spark->age += 1;
        if (!(spark->age & 1)) {
            trail_ring_push(spark->x >> 12, spark->y >> 12, spark->z >> 12);
        }
        if (spark->age >= 0xB) {
            spark->speed = CLAMP_HI(spark->speed + 2, 0x30);
        }
        if ((u32)(spark->age - 0xA) < 0x6F && !(spark->age & 1)) {
            spark_steer_to_target(spark);
        }
        angles_to_vector(spark->yaw, spark->pitch, spark->speed, &spark->vx, &spark->vy, &spark->vz);
        wind = get_flow_move();
        spark->vx += wind[0] / 2;
        spark->vy += wind[1] / 2;
        spark->vz += wind[2] / 2;
        if (spark->age & 3) {
            spark_move(spark);
        } else if (spark_move_trace(spark) == 1 || cam_range_check_alt(spark->x >> 12, spark->y >> 12, spark->z >> 12) == 0) {
            spark_free((s16 *)spark);
        }
    }
    trail_ring_age();
}

/* Turns each live spark into two effect records (one with the yaw/pitch, one without). */
void sparks_emit_effects(void) {
    Spark *sp = spark_pool;
    s32 i = 0;

    do {
        if (sp->active != 0) {
            s32 value = spark_effect_base + 0xD;
            spark_add_head(&spark_list, sp->x >> 12, sp->y >> 12, sp->z >> 12, sp->yaw, sp->pitch, 0, value, 0);
            value = spark_effect_base + 0xE;
            spark_add_head(&spark_list, sp->x >> 12, sp->y >> 12, sp->z >> 12, 0, 0, 0, value, 0);
        }
        i++;
        sp++;
    } while (i < 8);
    trail_sparks_emit();
}

void launch_missile(s32 *origin, Bytes8 *aim, s16 flags) {
    Missile *m;
    s32 handle;
    s32 x;

    m = spark_alloc();
    if (m != NULL) {
        x = origin[0] << 12;
        m->pos[0] = x;
        m->origin[0] = x;
        x = origin[1] << 12;
        m->pos[1] = x;
        m->origin[1] = x;
        x = origin[2] << 12;
        m->pos[2] = x;
        m->origin[2] = x;
        *(Bytes8 *)&m->aim = *aim;
        m->flags = flags;
        m->age = 0;
        m->speed = 0x18;
        handle = sound_start(SND_ROCKET_LAUNCH | SND_GROUP(1), 0x40, 0, 0);
        sound_attach(handle, m->pos, NULL);
        sound_set_flag_bit2(handle, 1);
    }
}

void trail_ring_reset(void) {
    trail_ring_tail = 0;
    trail_ring_head = 0;
    trail_ring_count = 0;
}
