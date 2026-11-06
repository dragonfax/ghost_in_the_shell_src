/* shots_fx: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void countdown_trace(Countdown *cd, s32 steps, s32 *pos, s32 *vel) {
    s32 dx = vel[0];
    register s32 dz asm("$18");
    register s32 dx_step asm("$9") = dx * steps;
    s32 dy;
    TraceSegment *seg;
    Vec3 *start;
    Vec3 *end;
    s32 fx, fy, fz;
    s16 hit;

    dy = vel[1];
    dz = vel[2];
    seg = scratch_alloc(sizeof(TraceSegment));
    start = &seg->start;
    end = &seg->end;
    fx = pos[0];
    fy = pos[1];
    fz = pos[2];

    start->x = fx >> 12;
    start->y = fy >> 12;
    start->z = fz >> 12;
    cd->count = steps;
    end->x = (fx + dx_step) >> 12;
    end->y = (fy + dy * steps) >> 12;
    end->z = (fz + dz * steps) >> 12;
    hit = trace_world(8, 8, start, end, cd);
    cd->latched = hit;
    if (hit != 0) {
        dx = __builtin_abs(dx);
        dy = __builtin_abs(dy);
        dz = __builtin_abs(dz);
        cd->count = 0;
        if (dx >= dy && dx >= dz) {
            if (dx > 0) {
                s32 d = cd->value.w[0] - start->x;
                if (d < 0) {
                    d = start->x - cd->value.w[0];
                }
                cd->count = ((d << 12) + dx - 1) / dx;
            }
        } else if (dy >= dx && dy >= dz) {
            if (dy > 0) {
                s32 d = cd->value.w[1] - start->y;
                if (d < 0) {
                    d = start->y - cd->value.w[1];
                }
                cd->count = ((d << 12) + dy - 1) / dy;
            }
        } else if (dz > 0) {
            s32 d = cd->value.w[2] - start->z;
            if (d < 0) {
                d = start->z - cd->value.w[2];
            }
            cd->count = ((d << 12) + dz - 1) / dz;
        }
    }
    scratch_top -= sizeof(TraceSegment);
}

s32 countdown_tick(Countdown *cd, s32 restart, s32 *pos, s32 *vel, Quad *out)
{
    cd->count--;
    if ((s16)cd->count > 0) {
        return 0;
    }
    if (cd->latched != 0) {
        *out = cd->value;
        return 1;
    }
    if (restart > 0) {
        countdown_trace(cd, restart, pos, vel);
    }
    return 0;
}

static inline void spark_lerp(s32 *pos, s32 scale, s32 x, s32 y, s32 z, s32 value, s32 colour) {
    s32 ox, oy, oz;

    __asm__("" : "=r"(scale) : "0"(scale));
    gte_load(IR1, pos, 0);
    gte_load(IR2, pos, 4);
    gte_load(IR3, pos, 8);
    gte_set(IR0, scale);
    gte_set(MAC1, x);
    gte_set(MAC2, y);
    gte_set(MAC3, z);
    gte_gpl12();
    gte_get(IR1, ox);
    gte_get(IR2, oy);
    gte_get(IR3, oz);
    spark_add(ox, oy, oz, 0, 0, 0, value, colour);
}
static inline void spark_lerp_head(s32 *pos, s32 scale, s32 x, s32 y, s32 z, s32 value) {
    s32 ox, oy, oz;

    __asm__("" : "=r"(scale) : "0"(scale));
    gte_load(IR1, pos, 0);
    gte_load(IR2, pos, 4);
    gte_load(IR3, pos, 8);
    gte_set(IR0, scale);
    gte_set(MAC1, x);
    gte_set(MAC2, y);
    gte_set(MAC3, z);
    gte_gpl12();
    gte_get(IR1, ox);
    gte_get(IR2, oy);
    gte_get(IR3, oz);
    spark_add_head(&spark_list, ox, oy, oz, 0, 0, 0, value, 0);
}
static inline void spark_add_head_roll(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, u16 rz, s32 value, s32 colour) {
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
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
void trace_shot_spark_draw(Object *obj) {
    s32 base;
    s32 model;
    s32 *pos;
    s32 x, y, z;
    s32 level, red, rem, colour;
    s32 pitch;
    s32 yaw;

    base = get_model_slot_base();
    pos = scratch_alloc(0x10);
    pos[0] = obj->vars.words[7];
    pos[1] = obj->vars.words[8];
    pos[2] = obj->vars.words[9];
    if (obj->vars.h.unk_24C == 1) {
        x = obj->x;
        y = obj->y;
        z = obj->z;
        x >>= 12;
        y >>= 12;
        z >>= 12;
        pitch = -obj->pitch;
        model = base + 0x15;
        {
            /* v1, so the yaw load doesn't reuse the pitch temp's v0 */
            register s32 raw_yaw asm("$3") = obj->yaw;
            yaw = raw_yaw + 0x800;
        }
        spark_add_head_roll(&spark_list, x, y, z, yaw, pitch, obj->roll, model, 0);
        spark_lerp_head(pos, 0x266, x, y, z, base + 0x16);
    }
    if ((s16)obj->vars.h.unk_24E > 0) {
        x = obj->vars.words[2];
        y = obj->vars.words[3];
        z = obj->vars.words[4];
        level = rand_b_next();
        rem = level % 0x800;
        level = 0x1000 - rem;
        level >>= 5;
        red = level;
        if (red == 0) {
            red = 1;
        }
        colour = (red << 16) | (level << 8) | level;
        spark_add(x, y, z, 0, 0, 0, base + 1, colour);
        spark_lerp(pos, 0xB33, x, y, z, base + 3, colour);
        if (rand_b_next() % 3 == 0) {
            spark_lerp(pos, 0x1333, x, y, z, base + 4, colour);
            spark_lerp(pos, 0x333, x, y, z, base + 5, colour);
        }
        obj->vars.h.unk_24E--;
    }
    if (obj->vars.words[0] != 0 && obj->vars.h.unk_24C == 0) {
        obj_free(obj);
    }
    scratch_top -= 0x10;
}

/* trace_shot_init shot, per-frame: trace the step, hit objects, spawn the impact effect. */
void trace_shot_phase1(Object *obj)
{
    register s32 hit asm("$17"); /* the original keeps hit (then the model) in s1 */
    TraceShotSeg *seg;
    s32 kind;
    s32 step;
    s32 life;
    s32 surface;
    Quad *to;
    s16 target;

    if (obj->vars.trace_shot.done != 1) {
        if (obj_hit_damage(obj->index) > 0) {
            obj->vars.trace_shot.done = 1;
        } else {
            obj->vars.trace_shot.start[0] += obj->vars.trace_shot.offset[0];
            obj->vars.trace_shot.start[1] += obj->vars.trace_shot.offset[1];
            obj->vars.trace_shot.start[2] += obj->vars.trace_shot.offset[2];
            seg = scratch_alloc(sizeof(TraceShotSeg));
            seg->from.w[0] = obj->x >> 12;
            seg->from.w[1] = obj->y >> 12;
            seg->from.w[2] = obj->z >> 12;
            to = &seg->to;
            to->w[0] = (obj->x + obj->vx) >> 12;
            to->w[1] = (obj->y + obj->vy) >> 12;
            to->w[2] = (obj->z + obj->vz) >> 12;
            if (obj->vars.trace_shot.mode == 0) {
                obj->vars.trace_shot.done = 1;
                hit = countdown_tick(&obj->vars.trace_shot.trace, 0, &obj->x, &obj->vx, to);
            } else {
                obj->z += obj->vz;
                obj->x += obj->vx;
                obj->y += obj->vy;
                hit = countdown_tick(&obj->vars.trace_shot.trace, 6, &obj->x, &obj->vx, to);
            }
            if (hit != 0) {
                surface = (surface_of(seg->to.w[3]) & 0x300) >> 8;
            }
            set_collide_mode(1);
            if (trace_objects(seg, &seg->to, 8, &seg->to, &target) != 0) {
                hit = 1;
                surface = 0;
                hit_target_masked(target, 1, atan2(seg->to.w[2] - seg->from.w[2], seg->to.w[0] - seg->from.w[0]), obj->damage);
            }
            set_collide_mode(0);
            if (hit != 0) {
                sound_play_at_units(SND_PROJECTILE_IMPACT | SND_GROUP(2), 0x60, 0x3C, seg);
                hit = 0x48;
                if (surface == 1) {
                    kind = 5;
                    life = 0xF;
                } else {
                    step = rand_a_next() * 3 / 4096 * 4;
                    hit = step + 0x30;
                    FAKE_USE(step);
                    kind = 4;
                    life = 0x3C;
                }
                effect_spawn_at((Vec3 *)&seg->to, hit + get_model_slot_base(), kind, life);
                obj->vars.trace_shot.done = 1;
            } else if (cam_range_check(seg->from.w[0], seg->from.w[1], seg->from.w[2]) == 0) {
                obj->vars.trace_shot.done = 1;
            }
            scratch_top -= sizeof(TraceShotSeg);
        }
    }
    if (obj->vars.trace_shot.done != 0 && obj->vars.trace_shot.mode == 1) {
        obj_free(obj);
    }
}

static inline void vec_from_angles(Vec3 *v, s32 yaw, s32 pitch, s32 len) {
    angles_to_vector(yaw, pitch, len, &v->x, &v->y, &v->z);
}
void trace_shot_init(Object *obj, s32 *pos, u16 *rot, u32 arg, s32 *offset) {
    Vec3 *vel;
    u32 mode;
    u32 high;

    obj->handlers[1].fn = (void *)trace_shot_phase1;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void *)trace_shot_spark_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    mode = arg & 0xFFFF;
    if (mode == 0) {
        obj->speed = 1200;
    } else {
        obj->speed = 40;
    }
    high = arg >> 16;
    obj->vars.trace_shot.done = 0;
    obj->vars.trace_shot.unused_24E = 1;
    obj->vars.trace_shot.mode = mode;
    if (high == 0) {
        high = 5;
    }
    vel = scratch_alloc(0x10);
    obj->damage = high;
    obj->vars.trace_shot.start[0] = pos[0];
    obj->vars.trace_shot.start[1] = pos[1];
    obj->vars.trace_shot.start[2] = pos[2];
    vel->x = 0;
    vel->y = 0;
    vel->z = 0;
    vec_from_angles(vel, obj->yaw, obj->pitch, obj->speed);
    if (offset != NULL) {
        vel->x += offset[0] << 12;
        vel->y += offset[1] << 12;
        vel->z += offset[2] << 12;
        obj->vars.trace_shot.offset[0] = offset[0];
        obj->vars.trace_shot.offset[1] = offset[1];
        obj->vars.trace_shot.offset[2] = offset[2];
    } else {
        obj->vars.trace_shot.offset[0] = 0;
        obj->vars.trace_shot.offset[1] = 0;
        obj->vars.trace_shot.offset[2] = 0;
    }
    obj->vars.trace_shot.dir[0] = 0;
    obj->vars.trace_shot.dir[1] = 0;
    obj->vars.trace_shot.dir[2] = 100;
    rotate_xz_twice((s16)rot[1], (s16)rot[0], &obj->vars.trace_shot.dir[0], &obj->vars.trace_shot.dir[1], &obj->vars.trace_shot.dir[2]);
    obj->vx = vel->x;
    obj->vy = vel->y;
    obj->vz = vel->z;
    scratch_top -= 0x10;
    if (obj->vars.trace_shot.mode == 0) {
        countdown_trace(&obj->vars.trace_shot.trace, 1, &obj->x, &obj->vx);
    } else {
        countdown_trace(&obj->vars.trace_shot.trace, 6, &obj->x, &obj->vx);
    }
}

/* rotate_xz_twice on a Vec3 in place. */
void vec3_rotate_xz_twice(s32 angle2, s32 angle1, Vec3 *v) {
    rotate_xz_twice(angle2, angle1, &v->x, &v->y, &v->z);
}

/* Traces a shot from `from` to `to`: 0 flew on, 1 left the world (object freed), 2 hit (impact effect, freed). */
s32 shot_path_trace(Object *obj, Vec3 *from, Vec3 *to, s32 flags) {
    s32 result = 0;
    Vec3 *hit = scratch_alloc(0x10);
    s16 target;

    if (cam_range_check(to->x, to->y, to->z) == 0) {
        obj_free(obj);
        result = 1;
    } else if (trace_world(8, flags, from, to, hit) == 1) {
        result = 2;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, flags, hit, &target)) {
            result = 2;
            hit_target_masked(target, 1, atan2(hit->z - from->z, hit->x - from->x), obj->damage);
        }
        set_collide_mode(0);
    }
    if (result == 2) {
        if (GUN_VARS(obj)->hit_effect_index != -1) {
            spawn_effect(hit->x, hit->y, hit->z, gun_hit_effect_table[GUN_VARS(obj)->hit_effect_index][0]);
        } else {
            impact_spawn((s32 *)hit, 0x400, 0x100, 0x1770);
            sound_play_at_units(SND_BULLET_IMPACT | SND_GROUP(2), 0x40, 0x3C, hit);
        }
        obj_free(obj);
    }
    scratch_top -= 0x10;
    return result;
}

/* Turns the object toward the player's position (aimed at its own mid-height)
 * by at most its turn steps, then sets its velocity along the new angles. */
void gun_shot_turn_to_player(Object *obj) {
    s32 yaw;
    s32 pitch;
    s32 x = obj->x;
    register s32 y asm("$17") = obj->y;
    s32 z = obj->z;
    s32 *player;
    s32 height;
    s32 dx;

    x >>= 12;
    player = player_position();
    dx = player[0] - x;
    height = (s16)obj->height;
    vector_to_angles(dx, player[1] - ((y >> 12) - height / 2),
                     player[2] - (z >> 12), &yaw, &pitch);
    obj->yaw = angle_approach(obj->yaw, yaw, (u16)obj->vars.enemy.target_yaw);
    obj->pitch = angle_approach(obj->pitch, pitch, (u16)obj->vars.enemy.walk_state);
    angles_to_vector(obj->yaw, -obj->pitch, obj->speed >> 12, &obj->vx, &obj->vy, &obj->vz);
}

void gun_shot_update(Object *obj) {
    TrailOffset *t = &trail_offsets[((GunShotVars *)&obj->vars)->kind];
    s32 base_y = get_model_slot_base();
    ShotScratch *sc = scratch_alloc(0x30);
    Vec3 *pos = &sc->from;
    Vec3 *to = &sc->to;
    Vec3 *v = &sc->offs;
    s32 nx, ny, nz;
    u8 count;
    s32 ph;

    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    if (obj_hit_damage(obj->index) > 0) {
        spawn_effect(pos->x >> 12, pos->y >> 12, pos->z >> 12, t->unk_0C[1]);
        obj_free(obj);
        scratch_top -= 0x30;
        return;
    }
    if (((GunShotVars *)&obj->vars)->age > ((GunShotVars *)&obj->vars)->turn_start_age && ((GunShotVars *)&obj->vars)->turn_angle < 0x1000) {
        ((GunShotVars *)&obj->vars)->turn_angle += ((GunShotVars *)&obj->vars)->turn_step;
    }
    if (((GunShotVars *)&obj->vars)->smoke_limit <= ((GunShotVars *)&obj->vars)->age && ((GunShotVars *)&obj->vars)->age % ((GunShotVars *)&obj->vars)->smoke_period == 0) {
        v->x = 0;
        v->y = 0;
        v->z = t->unk_0C[0];
        vec3_rotate_xz_twice(obj->yaw, -obj->pitch, v);
        v->x = (pos->x >> 12) + v->x;
        v->y = (pos->y >> 12) + v->y;
        v->z = (pos->z >> 12) + v->z;
        effect_spawn_at(v, base_y + t->unk_06, 8, ((GunShotVars *)&obj->vars)->smoke_arg);
    }
    ph = ((GunShotVars *)&obj->vars)->phase;
    if (ph != 1) {
        if (ph < 2) {
            if (ph == 0) {
                if (((GunShotVars *)&obj->vars)->age >= ((GunShotVars *)&obj->vars)->launch_age) {
                    ((GunShotVars *)&obj->vars)->phase++;
                }
            }
        }
    } else {
        if (((GunShotVars *)&obj->vars)->age < ((GunShotVars *)&obj->vars)->homing_end_age) {
            if (obj->speed < ((GunShotVars *)&obj->vars)->max_speed) {
                obj->speed += obj->speed_accel;
            }
            gun_shot_turn_to_player(obj);
        } else {
            angles_to_vector(obj->yaw, -obj->pitch, obj->speed >> 12, &obj->vx, &obj->vy, &obj->vz);
            ((GunShotVars *)&obj->vars)->phase++;
        }
    }
    nx = pos->x;
    ny = pos->y;
    nz = pos->z;
    nx += obj->vx;
    ny += obj->vy;
    nz += obj->vz;
    if (((GunShotVars *)&obj->vars)->has_target == 1) {
        nx += ((GunShotVars *)&obj->vars)->target[0] << 12;
        ny += ((GunShotVars *)&obj->vars)->target[1] << 12;
        nz += ((GunShotVars *)&obj->vars)->target[2] << 12;
    }
    obj->x = nx;
    obj->y = ny;
    obj->z = nz;
    count = --((GunShotVars *)&obj->vars)->trace_count;
    if (count == 0) {
        pos->x = ((GunShotVars *)&obj->vars)->x;
        pos->y = ((GunShotVars *)&obj->vars)->y;
        pos->z = ((GunShotVars *)&obj->vars)->z;
        to->x = nx >> 12;
        to->y = ny >> 12;
        to->z = nz >> 12;
        shot_path_trace(obj, pos, to, t->unk_0C[2]);
        ((GunShotVars *)&obj->vars)->x = to->x;
        ((GunShotVars *)&obj->vars)->y = to->y;
        ((GunShotVars *)&obj->vars)->z = to->z;
        ((GunShotVars *)&obj->vars)->trace_count = 4;
    }
    ((GunShotVars *)&obj->vars)->age++;
    asm("");
    scratch_top -= 0x30;
}

static inline TrailVars *trail_vars(Object *obj) {
    return (TrailVars *)&obj->vars;
}
s32 rocket_trail_draw(Object *obj) {
    TrailOffset *t = &trail_offsets[trail_vars(obj)->kind];
    s32 base_y = get_model_slot_base();
    Vec3 *v = scratch_alloc(0x10);
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    s32 pitch = obj->pitch;
    s32 npitch = -pitch;
    s32 yaw = obj->yaw;
    s32 roll = obj->roll;
    s32 yaw_back = yaw + 0x800;
    s32 col;
    s32 a;
    s32 b;

    spark_add(x, y, z, yaw_back, pitch, roll, base_y + t->y0, 0);
    if (trail_vars(obj)->amount > trail_vars(obj)->limit_a) {
        col = trail_vars(obj)->scale;
        a = col >> 5;
        b = a;
        if (!a) {
            b = 1;
        }
        col = (b << 16) | (a << 8) | a;
        v->x = 0;
        v->y = 0;
        v->z = t->z;
        vec3_rotate_xz_twice(yaw, npitch, v);
        v->x += x;
        v->y += y;
        v->z += z;
        spark_add(v->x, v->y, v->z, yaw_back, pitch, roll, base_y + t->y1, col);
    }
    if (trail_vars(obj)->amount > trail_vars(obj)->limit_b) {
        v->x = 0;
        v->y = 0;
        v->z = t->z2;
        vec3_rotate_xz_twice(yaw, npitch, v);
        v->x += x;
        v->y += y;
        v->z += z;
        spark_add(v->x, v->y, v->z, 0, 0, 0, base_y + t->y2, 0);
    }
    scratch_top -= 0x10;
}

/* Moves the gun object by its velocity, counting down the byte at GunVars.unk_27F. When the count reaches 0 it
 * reloads the count with 2 and works out the step's position: the position at (x, y, z) is converted to
 * 4.12 fixed point, the pair shot_path_trace gets (from = the stored position, to = the new one) and the result is
 * stored back. Its scratch pair lives on the $gp scratch stack. */
void laser_bullet_update(Object *obj, ObjHandler *handler) {
    GunVars *gun = (GunVars *)&obj->vars;
    Vec3 *from = scratch_alloc(0x20);
    Vec3 *to = (Vec3 *)&((s32 *)from)[4];
    s32 new_x, new_y, new_z, gun_z;
    u8 count;

    new_x = obj->x;
    new_y = obj->y;
    new_z = obj->z;
    new_x += obj->vx;
    new_y += obj->vy;
    new_z += obj->vz;
    count = gun->trace_countdown - 1;
    obj->x = new_x;
    obj->y = new_y;
    gun->trace_countdown = count;
    obj->z = new_z;
    if (count == 0) {
        from->x = gun->x;
        from->y = gun->y;
        gun_z = gun->z;
        to->x = new_x >> 12;
        to->y = new_y >> 12;
        to->z = new_z >> 12;
        from->z = gun_z;
        shot_path_trace(obj, from, to, 0xC);
        gun->x = to->x;
        gun->y = to->y;
        gun_z = to->z;
        gun->trace_countdown = 2;
        gun->z = gun_z;
    }
    scratch_top -= 0x20;
}

void laser_bullet_draw(Object *obj) {
    s32 pitch = obj->pitch;
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    s32 yaw = obj->yaw;
    s32 roll = obj->roll;
    s32 value = get_model_slot_base() + 9;
    s32 ry = yaw + 0x800;
    s32 n = spark_count;
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
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = pitch;
        s->roll = roll;
    }
}

void gun_shot_setup(Object *obj, GunSetup *setup, s32 *target) {
    obj->handlers[1].fn = (void *)gun_shot_update;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = (void *)rocket_trail_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->speed = setup->speed;
    obj->speed_accel = setup->speed_delta;
    GUN_VARS(obj)->unk_248 = setup->unk_04;
    GUN_VARS(obj)->unk_266 = setup->unk_10;
    GUN_VARS(obj)->unk_268 = setup->unk_12 + setup->unk_10;
    GUN_VARS(obj)->unk_26A = setup->unk_14;
    GUN_VARS(obj)->unk_26C = setup->unk_16;
    GUN_VARS(obj)->unk_272 = setup->unk_1A;
    GUN_VARS(obj)->unk_274 = setup->unk_1C;
    GUN_VARS(obj)->unk_276 = setup->unk_18;
    obj->damage = setup->damage;
    GUN_VARS(obj)->unk_26E = setup->unk_1E;
    GUN_VARS(obj)->unk_270 = setup->unk_20;
    GUN_VARS(obj)->unk_278 = setup->unk_22;
    GUN_VARS(obj)->unk_27A = 0;
    GUN_VARS(obj)->hit_effect_index = setup->hit_effect_index;
    GUN_VARS(obj)->trace_countdown = 4;
    GUN_VARS(obj)->x = obj->x >> 12;
    GUN_VARS(obj)->y = obj->y >> 12;
    GUN_VARS(obj)->z = obj->z >> 12;
    angles_to_vector(obj->yaw, -obj->pitch, obj->speed >> 12, &obj->vx, &obj->vy, &obj->vz);
    if (target == NULL) {
        GUN_VARS(obj)->has_target = 0;
    } else {
        GUN_VARS(obj)->has_target = 1;
        GUN_VARS(obj)->target[0] = target[0];
        GUN_VARS(obj)->target[1] = target[1];
        GUN_VARS(obj)->target[2] = target[2];
    }
    GUN_VARS(obj)->unk_27D = 0;
    GUN_VARS(obj)->unk_264 = 0;
}

void laser_bullet_init(Object *obj, u32 arg1, Vec3 *offset) {
    Vec3 *vec;
    u32 high;

    get_model_slot_base();
    vec = scratch_alloc(0x10);
    obj->handlers[1].fn = laser_bullet_update;
    obj->handlers[3].fn = laser_bullet_draw;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    angles_to_vector(obj->yaw, -obj->pitch, arg1 & 0xFFFF, &vec->x, &vec->y, &vec->z);
    if (offset != NULL) {
        vec->x += offset->x << 12;
        vec->y += offset->y << 12;
        vec->z += offset->z << 12;
    }
    /* vars words 1-3 get the object's position in whole units (x, y, z) */
    obj->vars.words[1] = obj->x >> 12;
    obj->vars.words[2] = obj->y >> 12;
    obj->vars.words[3] = obj->z >> 12;
    ((u8 *)&obj->vars.enemy.shot_timer)[3] = 2;
    obj->vx = vec->x;
    obj->vy = vec->y;
    high = arg1 >> 16;
    obj->vz = vec->z;
    ((s8 *)&obj->vars.enemy.shot_timer)[0] = -1;
    if (high == 0) {
        high = 0xF;
    }
    obj->damage = high;
    scratch_top -= 0x10;
}

/* Spawns an object of the given kind at pos (whole units) with rot (pitch = -rot[0], yaw = rot[1], roll = rot[2]). Returns 1 when set up. */
s32 shot_spawn_obj(s32 *pos, u16 *rot, s32 kind, s32 arg) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    switch (kind) {
    case 2:
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = -rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        if (arg == 0) {
            obj_free(obj);
            return 0;
        }
        gun_shot_setup(obj, (GunSetup *)arg, NULL); /* kind 2: arg is the setup record */
        return 1;
    case 3:
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = -rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        laser_bullet_init(obj, arg, 0);
        return 1;
    case 1:
        trace_shot_init(obj, pos, rot, arg, 0);
        return 1;
    }
    return 1;
}

s32 shot_spawn_target(s32 *pos, u16 *rot, s32 *target, s32 mode, s32 arg4) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), &obj->node);
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    switch (mode) {
    case 2:
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = -rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        if (arg4 == 0) {
            obj_free(obj);
            return 0;
        }
        gun_shot_setup(obj, (GunSetup *)arg4, target);
        return 1;
    case 3:
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = -rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        laser_bullet_init(obj, arg4, (Vec3 *)target);
        return 1;
    case 1:
        trace_shot_init(obj, pos, rot, arg4, target);
        return 1;
    }
    return 1;
}

/* Spawns an actor at pos (x, y, z words) running handlers impact_update and impact_draw, with three
 * parameters in its vars; returns 0 when the pool is full. */
s32 impact_spawn(s32 *pos, u16 arg_250, u16 arg_252, s16 arg_24C) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    obj->handlers[1].fn = (void *)impact_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = (void *)impact_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->x = pos[0];
    obj->y = pos[1];
    obj->z = pos[2];
    obj->vars.impact.progress = 0;
    obj->vars.impact.level = 0;
    obj->vars.impact.phase = 0;
    obj->vars.impact.max_scale = arg_24C;
    obj->vars.impact.rise_step = arg_250;
    obj->vars.impact.fall_step = arg_252;
    return 1;
}

/* Object phase in vars.h: 0 ramps progress up by unk_250 and moves to phase 1 past 0x1000; 1 ramps by
 * unk_252 and frees the object past 0x1000. unk_24A follows progress (inverted in phase 1). */
void impact_update(Object *obj) {
    s16 phase;

    phase = obj->vars.impact.phase;
    switch (phase) {
    case 0: {
        s16 progress;

        progress = (u16) obj->vars.impact.progress + obj->vars.impact.rise_step;
        obj->vars.impact.progress = progress;
        obj->vars.impact.level = (u16) progress;
        if (obj->vars.impact.progress >= 0x1001) {
            obj->vars.impact.progress = 0;
            obj->vars.impact.phase += 1;
            return;
        }
        return;
    }
    case 1: {
        u16 progress;

        progress = obj->vars.impact.progress + obj->vars.impact.fall_step;
        obj->vars.impact.progress = progress;
        obj->vars.impact.level = 0x1000 - progress;
        if ((s16) obj->vars.impact.progress >= 0x1001) {
            obj_free(obj);
        }
        break;
    }
    }
}

/* Spawns a pool entry sized from the object's scale (halfword 0x24A x 0x24C), then adds a spark
 * at the object's position with a colour built from 0x24A's top bits. */
void impact_draw(Object *obj) {
    s32 product;
    s32 scale;
    s32 level;
    s32 channel;
    s32 colour;
    s32 pool_index;

    pool_index = get_model_slot_base() + 0xF;
    product = obj->vars.impact.level * (s16)obj->vars.impact.max_scale;
    if (product < 0) {
        product += 0xFFF;
    }
    scale = product >> 12;
    pool_index = pool_spawn_scaled(pool_index, scale, scale, scale);

    level = obj->vars.impact.level >> 5;
    channel = level ? level : 1;
    colour = (channel << 16) | (level << 8) | level;
    spark_add(obj->x, obj->y, obj->z, 0, 0, 0, pool_index, colour);
}

/* Timer in the words view: words[5] advances by words[4]; at 0x1000 the object frees, otherwise
 * words[6] advances by words[7]. */
void spark_life_update(Object *obj) {
    s32 elapsed;

    elapsed = obj->vars.spark.life_progress + obj->vars.spark.life_step;
    obj->vars.spark.life_progress = elapsed;
    if (elapsed >= 0x1000) {
        obj_free(obj);
        return;
    }
    obj->vars.spark.brightness += obj->vars.spark.brightness_step;
}

/* Blend between two of `count` consecutive entries from `first` at position t (20.12 over the whole
 * range; `loop` wraps the last entry around to the first). */
s32 frame_range_blend(s32 first, s32 count, s32 t, s32 loop) {
    s32 pos;
    s32 a;
    s32 b;

    if (loop) {
        pos = count * t;
    } else {
        pos = (count - 1) * t;
    }
    a = pos >> 12;
    b = a + 1;
    if (b >= count) {
        /* FAKE? a do-while(0) (a macro in the original?) is needed for the frac recomputation */
        do {
            b = 0;
        } while (0);
    }
    return pchr_blend(a + first, b + first, 0x1000 - (pos & 0xFFF), 0);
}

/* Adds a spark record at the object's position, its colour from the object's fade value. */
void spark_draw(Object *obj) {
    s32 frame;
    s32 value;
    s32 level;
    s32 raw;
    s32 blue;
    s32 n;
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    u8 **bucket;
    s32 a, b;
    s32 x, y, z;

    frame = obj->vars.spark.frame;
    if (frame & 0x8000) {
        value = (obj->vars.spark.range_end - obj->vars.spark.range_start) * obj->vars.spark.life_progress / 0x1000 + obj->vars.spark.range_start;
        frame &= 0x7FFF;
    } else {
        frame = frame_range_blend(frame + obj->vars.spark.range_start, obj->vars.spark.range_end - obj->vars.spark.range_start + 1, obj->vars.spark.life_progress, 0);
        value = obj->vars.spark.scale;
    }
    if (value != 0x1000) {
        frame = pool_spawn_scaled(frame, value, value, value);
    }
    raw = obj->vars.spark.brightness;
    level = NOT_NEGATIVE(raw < 0x1001 ? raw : 0x1000);
    level >>= 5;
    blue = level;
    if (level == 0) {
        blue = 1;
    }
    raw = (blue << 16) | (level << 8) | level;
    list = &spark_list;
    n = spark_count;
    a = obj->vars.spark.unk_24A;
    b = obj->vars.spark.unk_248;
    x = obj->x;
    y = obj->y;
    z = obj->z;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = raw;
        bucket = (u8 **)((u8 *)list + (raw >> 24) * 4);
        tail = bucket[2];
        bucket[2] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = frame;
        s->yaw = a;
        s->pitch = b;
        s->roll = 0;
    }
}

/* Spawns an object at `pos`, links it before the node get_obj_list_actors_tail returns, sets its two handlers and
 * copies the parameters into its vars. Returns 1 when an object was made, 0 when the pool is full. */
s32 spark_spawn(Vec3 *pos, SpawnStats *stats, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    Object *obj;
    SpawnHead *head;
    u16 stats_04;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) spark_life_update;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) spark_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->x = pos->x;
    obj->y = pos->y;
    obj->z = pos->z;
    head = (SpawnHead *) &obj->vars;
    head->unk_00 = stats->unk_00;
    head->unk_02 = stats->unk_02;
    stats_04 = stats->unk_04;
    obj->vars.spark.range_start = arg3;
    obj->vars.spark.range_end = arg4;
    obj->vars.spark.life_step = arg5;
    obj->vars.spark.life_progress = 0;
    obj->vars.spark.brightness = arg6;
    obj->vars.spark.brightness_step = arg7;
    obj->vars.spark.frame = arg2;
    obj->vars.spark.scale = arg8;
    head->unk_04 = stats_04;
    return 1;
}

void spark_pair_spawn(Vec3 *pos, s32 index, s32 arg) {
    SpawnStats *stats = scratch_alloc(8);
    s32 base;

    stats->unk_00 = 0;
    stats->unk_02 = 0;
    stats->unk_04 = 0;
    base = get_model_slot_base();
    spark_spawn(pos, stats, base + 0x803E, (index * 3 << 9) / 0x1000, (index * 9 << 9) / 0x1000, 0xCC, 0x1800,
                -0x133, 0);
    *(s16 *)&stats->unk_00 = -0x400;
    stats->unk_02 = 0;
    stats->unk_04 = 0;
    base = get_model_slot_base();
    spark_spawn(pos, stats, base + 0x4E, 0, 1, 0x200, 0x1000, -0x155, arg);
    scratch_top -= 8;
}

void fn_8010CBD0(void) {

}

void fn_8010CBD8(void) {

}

void fn_8010CBE0(void) {

}

/* Fill a 32-entry CLUT with a grey ramp (STP bit set). */
void clut_fill_grey_ramp(u16 *clut) {
    s32 i;

    for (i = 0; i < 32; i++) {
        *clut++ = (i << 10) | (i << 5) | i | 0x8000;
    }
}

/* Fills a 32 entry 16 bit palette with 0 except for `count` white entries (with greyer entries around
 * them) starting `first` entries from its end. Nothing else is set when they don't fit. */
void palette_highlight_fill(u16 *p, s32 first, s32 count) {
    u16 *pal = p;
    s32 i;
    s32 end;

    i = 0x1F;
    do {
        *p++ = 0;
    } while (--i >= 0);
    if (count > 0 && first + count < 0x20) {
        p = (u16 *)((u8 *)pal - (first * 2 - 0x40));
        p[1] = first >= 2 ? 0x9CE7 : 0xFFFF;
        p[0] = first > 0 ? 0xBDEF : 0xFFFF;
        p--;
        i = count;
        if (i > 0) {
            do {
                *p-- = 0xFFFF;
            } while (--i > 0);
        }
        end = first + count;
        if (end < 0x1F) {
            *p-- = 0xBDEF;
        }
        if (end < 0x1E) {
            *p = 0x9CE7;
        }
    }
}

/* Clears a FxEffect record; a NULL record is ignored. */
void fx_rec30_clear(FxEffect *rec) {
    if (rec != NULL) {
        rec->progress = 0;
        rec->progress_step = 0;
        rec->size = 0;
        rec->size_speed = 0;
        rec->size_accel = 0;
        rec->used = 0;
        rec->callback = 0;
        rec->intensity = 0;
        rec->color_r = 0;
        rec->color_g = 0;
        rec->color_b = 0;
        rec->unk_2A = 0;
    }
}

/* Run fx_rec30_clear on each of the 16 entries at 0x80131E2C. */
void fx_rec30_clear_all(void) {
    FxEffect *rec = fx_rec30_pool;
    s32 i;

    for (i = 0; i < 16; i++, rec++) {
        fx_rec30_clear(rec);
    }
}

/* Returns the first of the 16 FxEffect records at fx_rec30_pool whose byte 0x2F is clear, or NULL if all are in use. */
FxEffect *fx_rec30_alloc(void) {
    FxEffect *rec = fx_rec30_pool;
    s32 i;
    for (i = 0; i < 16; i++, rec++) {
        if (rec->used == 0) {
            return rec;
        }
    }
    return NULL;
}

s32 fx_colour_level(s32 kind) {
    s32 result = 0x80;

    switch (kind & 0xFF) {
    case 0:
        result = 0x80;
        break;
    case 1:
        result = 0x40;
        break;
    case 2:
        result = 0x20;
        break;
    case 3:
        result = 0;
        break;
    }
    return result;
}

s32 probe_clip_to_column(Probe *probe)
{
    s32 x0 = probe->x0;
    s32 x1 = probe->x1;
    s32 y0 = probe->y0;
    s32 col = probe->half_extent;
    s32 y1 = probe->y1;
    s32 flags = 0;

    if (col > 0) {
        flags = col < x0;
        if (col < x1) {
            flags |= 2;
        }
    } else {
        if (x0 < col) {
            flags = 1;
        }
        if (x1 < col) {
            flags |= 2;
        }
    }
    if (flags == 3) {
        return 0;
    }
    if (flags == 0) {
        return 1;
    }
    if (flags == 1) {
        y0 += (((y1 - y0) << 12) / (x1 - x0)) * (col - x0) >> 12;
        x0 = col;
    }
    if (flags == 2) {
        y1 += (((y0 - y1) << 12) / (x0 - x1)) * (col - x1) >> 12;
        x1 = col;
    }
    y0 = NOT_NEGATIVE(MIN(y0, 0x40));
    y1 = MAX(MIN(y1, 0x40), 1);
    probe->x0 = x0;
    probe->x1 = x1;
    probe->y0 = y0;
    probe->y1 = y1;
    return 1;
}

/* Tests probe, then tests it again with unk_10 negated; true when both pass. */
s32 probe_test_both_sides(Probe *probe) {
    if (probe_clip_to_column(probe) == 0) {
        return 0;
    }
    probe->half_extent = -probe->half_extent;
    if (probe_clip_to_column(probe) == 0) {
        return 0;
    }
    return 1;
}

void sprite_draw_rect(SpriteRec *sprite, s32 dx, s32 dy, Probe *probes) {
    u8 *ot;
    PrimBuf *buf;
    WinPolyFT4 *prim;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 min_x;
    s32 max_x;
    s32 min_y;
    s32 max_y;
    s32 half_w;
    s32 half_h;
    Probe *second;

    second = probes + 1;
    x0 = sprite->xy;
    buf = sprite->buf;
    ot = sprite->ot;
    half_w = sprite->half_w;
    half_h = sprite->half_h;
    y0 = x0 >> 16;
    x0 <<= 16;
    x0 >>= 16;
    x1 = x0 + dx;
    min_x = x0;
    if (x1 < x0) {
        min_x = x1;
    }
    y1 = y0 + dy;
    min_y = y0;
    if (y1 < y0) {
        min_y = y1;
    }
    max_x = x0;
    if (x0 < x1) {
        max_x = x1;
    }
    max_y = y0;
    if (y0 < y1) {
        max_y = y1;
    }
    if (half_w < min_x || half_h < min_y || max_x < -half_w || max_y < -half_h) {
        return;
    }
    probes[0].x0 = x0;
    probes[0].x1 = x1;
    probes[0].y0 = 0;
    probes[0].y1 = 0x40;
    probes[0].half_extent = half_w;
    probes[1].x0 = y0;
    probes[1].x1 = y1;
    probes[1].y0 = 0;
    probes[1].y1 = 0x40;
    probes[1].half_extent = half_h;
    if (probe_test_both_sides(&probes[0]) && probe_test_both_sides(second)) {
        prim = (WinPolyFT4 *)buf->top;
        buf->top = (u8 *)(prim + 1);
        prim->rgbc.word = sprite->color;
        prim->len = 10;
        prim->tex_window = 0xE2042318;
        prim->rgbc.c.code = 0x2E;
        prim->x2 = prim->x0 = probes[0].x0;
        prim->x3 = prim->x1 = probes[0].x1;
        prim->y1 = prim->y0 = probes[1].x0;
        prim->y3 = prim->y2 = probes[1].x1;
        prim->u2 = prim->u0 = probes[0].y0;
        prim->u3 = prim->u1 = probes[0].y1 - 1;
        prim->v1 = prim->v0 = probes[1].y0;
        prim->v3 = prim->v2 = probes[1].y1 - 1;
        prim->tpage = fx_tpage;
        prim->clut = fx_clut_word;
        addPrim(ot, prim);
    }
}

/* Builds a LoadImage packet for rect (like PsyQ SetDrawLoad). */
void prim_vram_load_packet(u8 *packet, s16 *rect)
{
    DrawLoadPacket *load = (DrawLoadPacket *)packet;
    RectWords *area = (RectWords *)rect;
    s32 size;
    s32 xy;
    s32 words;
    s32 len;
    u32 code;

    code = 0xA0000000;
    size = area->wh;
    do {
    } while (0);
    len = size >> 16;
    size <<= 16;
    size >>= 16;
    size = size * len;
    size += 1;
    words = size / 2;
    load->code = code;
    len = words + 4;
    code = 0x01000000;
    if (words > 12) {
        len = 0;
    }
    load->len = len;
    xy = area->xy;
    size = area->wh;
    load->xy = xy;
    load->wh = size;
    *(u32 *)(packet + (len << 2)) = code;
}

void fx_palette_init(void) {
    ScreenRect r;
    s32 i, sq, n;
    u16 *p;
    r.x = 0x100; r.y = 0xDA; r.w = 0x20; r.h = 1;
    clut_fill_grey_ramp(fx_grey_clut_buf);
    for (i = 0, p = fx_palette_table; i < 0x20; i++) {
        sq = i * i - 0x10;
        n = i;
        if (sq <= 0) {
            sq = 0;
        } else {
            sq = SquareRoot0(sq);
        }
        n -= sq;
        if (n == 0) n = 1;
        palette_highlight_fill(p, sq, n);
        p += 0x20;
    }
    fx_tables_init();
}

void fx_init_rects(void) {
    fx_tpage = 0xB0;
    fx_clut_word = 0x3690;
    fx_vram_rect_a = 0x100;
    d_80131E1E = 0xDA;
    d_80131E20 = 0x10;
    d_80131E22 = 1;
    fx_vram_rect_b = 0x110;
    d_80131E26 = 0xDA;
    d_80131E28 = 0x10;
    d_80131E2A = 1;
    fn_8010DFEC();
}

void fx_reset_pools(void) {
    fx_rec30_clear_all();
    fn_8010DFF4();
}

/* Steps each in-use FxEffect (unk_10 += unk_12, unk_1C += unk_20, unk_1C floored at the value at unk_24).
 * While unk_10 is below 0x1000 the record's callback runs; otherwise, or once the callback clears
 * `used`, the record is released with fx_rec30_clear. */
void fx_pool_step(void) {
    FxEffect *rec;
    s16 next;
    s32 sum;
    s32 i;

    rec = fx_rec30_pool;
    i = 0;
    do {
        if (rec->used != 0) {
            sum = rec->progress = rec->progress + rec->progress_step;
            next = sum;
            rec->intensity = next;
            if (next < 0x1000) {
                rec->size += rec->size_speed;
                rec->size_speed += rec->size_accel;
                if (rec->size_speed < *(s32 *) rec->size_speed_min) {
                    rec->size_speed = *(s32 *) rec->size_speed_min;
                }
                if (rec->callback != NULL) {
                    rec->callback(rec);
                    if (rec->used == 0) {
                        fx_rec30_clear(rec);
                    }
                }
            } else {
                fx_rec30_clear(rec);
            }
        }
        i += 1;
        rec += 1;
    } while (i < 0x10);
    fx_rec34_step_all();
}

static inline u32 *fx_ot_entry(View *vw, s32 z) {
    s32 k = z;

    if (k < 0) {
        k = 0;
    }
    k >>= 5;
    if (k >= 0x200) {
        k = 0x1FF;
    }
    return &((FxOtBuffer *)vw->ot)->ot[0x1FF - k];
}

static inline s32 fx_in_range(s32 dx, s32 dy, s32 dz) {
    if ((u32)(dx + 0x4000) > 0x7FFF) {
        return 0;
    }
    if ((u32)(dy + 0x4000) > 0x7FFF) {
        return 0;
    }
    return (u32)(dz + 0x4000) <= 0x7FFF;
}

static inline void fx_emit_clut_packets(SpriteRec *prim, u32 *src) {
    PrimBuf *work = prim->buf;
    u32 *ot = (u32 *)prim->ot;
    u8 *pk;
    u32 *dst;
    s32 j;

    pk = work->top;
    work->top = pk + 0x44;
    prim_vram_load_packet(pk, &fx_vram_rect_a);
    dst = (u32 *)(pk + 0x10);
    j = 0;
    do {
        j++;
        *dst++ = *src++;
    } while (j < 8);
    addPrim(ot, pk);
    pk = work->top;
    work->top = pk + 0x44;
    prim_vram_load_packet(pk, &fx_vram_rect_b);
    dst = (u32 *)(pk + 0x10);
    j = 0;
    do {
        j++;
        *dst++ = *src++;
    } while (j < 8);
    addPrim(ot, pk);
}

/* Draws the glows of fx_rec30_pool against cameras[cur_cam_index]: each record in use and within 0x4000 of the
 * camera is projected (rtps), sized and placed in the view's OT by depth (type 3: the nearest slot), its colour
 * faded by unk_28 (dpcs), then drawn as four quarter sprites with two CLUT packets (type 2: the CLUT row from
 * progress / 0x80, others fx_grey_clut_buf). Ends with fx_draw_pool. */
void fx_glow_pool_draw(void) {
    s32 i;
    FxEffect *rec;
    Camera *cam;
    View *vw = views;
    s32 *rot;
    s32 gfc; /* never set: the original reads GFC into bfc and restores GFC from this */

    if (cur_cam_index >= 0) {
        cam = &cameras[cur_cam_index];
        rec = fx_rec30_pool;
        rot = scratch_alloc(0x20);
        for (i = 0; i < 16; i++, rec++) {
            /* dx is reused for the screen position, dz for the sprite size, flag for the clamped depth */
            s32 dx, dz, dy, inside, flag, z, inten, px, py, row, ox, oy;
            s32 rfc, bfc, ofx, ofy, frame;
            SpriteRec *prim;
            u32 *col;

            if (rec->used == 0) {
                continue;
            }
            dx = ((VECTOR *)rec->pos)->vx - cam->pos.vx;
            dy = ((VECTOR *)rec->pos)->vy - cam->pos.vy;
            dz = ((VECTOR *)rec->pos)->vz - cam->pos.vz;
            if (!fx_in_range(dx, dy, dz)) {
                continue;
            }
            /* inside: the camera is within the glow's radius (size >> 12) */
            inside = rec->size;
            if (inside < 0) {
                inside += 0xFFF;
            }
            inside >>= 12;
            inside = inside * inside;
            inside = length_sq(dx, dy, dz) < inside;
            scale_rows(vw->rot[0], (s16 *)&vw->unk_2C[0xC], (s16 *)rot);
            {
                /* one load and one ctc2 per word, through v1, a0, v0 as in the original */
                register s32 w0 asm("$3");
                register s32 w1 asm("$4");
                register s32 w2 asm("$2");

                w0 = rot[0];
                w1 = rot[1];
                w2 = rot[2];
                gte_set_ctrl(R11R12, w0);
                gte_set_ctrl(R13R21, w1);
                gte_set_ctrl(R22R23, w2);
                w0 = rot[3];
                w1 = rot[4];
                gte_set_ctrl(R31R32, w0);
                gte_set_ctrl(R33, w1);
            }
            ofx = ((s16 *)vw->screen_offset)[0];
            ofy = ((s16 *)vw->screen_offset)[1];
            gte_set_ctrl(OFX, ofx << 16);
            gte_set_ctrl(OFY, ofy << 16);
            gte_set_ctrl(H, 0x80);
            gte_set_ctrl(TRX, 0);
            gte_set_ctrl(TRY, 0);
            gte_set_ctrl(TRZ, 0);
            ox = vw->vram_w;
            oy = vw->vram_h;
            gte_set(VXY0, (dx & 0xFFFF) | (dy << 16));
            gte_set(VZ0, dz);
            gte_rtps();
            gte_nop();
            gte_get_ctrl(FLAG, flag);
            gte_nop();
            if (flag < 0 && !inside) {
                continue;
            }
            gte_get(MAC3, z);
            gte_get(SXY2, dx);
            if (z <= 0x40 && !inside) {
                continue;
            }
            flag = ABS(z);
            if (flag < 0x40) {
                flag = 0x40;
            }
            dz = ((rec->size >> 12) << 7) / flag;
            z -= dz;
            if (z < 0) {
                z = 0;
            }
            prim = scratch_alloc(sizeof(SpriteRec));
            prim->xy = dx;
            prim->half_w = ox;
            prim->half_h = oy;
            if (rec->used == 3) {
                prim->ot = (u8 *)&((FxOtBuffer *)vw->ot)->ot[0x1FF];
            } else {
                prim->ot = (u8 *)fx_ot_entry(vw, z);
            }
            prim->buf = (PrimBuf *)work_area_ptr;
            prim->color = *(s32 *)&rec->color_r;
            inten = rec->intensity;
            col = &prim->color;
            inten = MAX(MIN(inten, 0xFFF), 0);
            gte_get_ctrl(RFC, rfc);
            gte_get_ctrl(GFC, bfc);
            gte_get_ctrl(BFC, bfc);
            gte_set_ctrl(RFC, 0);
            gte_set_ctrl(GFC, 0);
            gte_set_ctrl(BFC, 0);
            gte_load(RGB, col, 0);
            gte_set(IR0, inten);
            gte_dpcs();
            gte_store(RGB2, col, 0);
            gte_set_ctrl(RFC, rfc);
            gte_set_ctrl(GFC, gfc);
            gte_set_ctrl(BFC, bfc);
            row = rec->progress;
            px = (dz * *(s16 *)&vw->unk_2C[0x14]) / 0x1000;
            py = (dz * *(s16 *)&vw->unk_2C[0x16]) / 0x1000;
            if (rec->used == 2) {
                if ((u32)row < 0x1000) {
                    Probe *probes;

                    probes = (Probe *)scratch_top;
                    frame = row;
                    scratch_top += 0x28;
                    frame /= 0x80;
                    sprite_draw_rect(prim, px, py, probes);
                    sprite_draw_rect(prim, -px, py, probes);
                    sprite_draw_rect(prim, px, -py, probes);
                    sprite_draw_rect(prim, -px, -py, probes);
                    fx_emit_clut_packets(prim, (u32 *)&fx_palette_table[frame * 0x20]);
                    scratch_top -= 0x28;
                }
            } else {
                Probe *probes;

                probes = (Probe *)scratch_top;
                scratch_top += 0x28;
                sprite_draw_rect(prim, px, py, probes);
                sprite_draw_rect(prim, -px, py, probes);
                sprite_draw_rect(prim, px, -py, probes);
                sprite_draw_rect(prim, -px, -py, probes);
                fx_emit_clut_packets(prim, (u32 *)fx_grey_clut_buf);
                scratch_top -= 0x28;
            }
            scratch_top -= sizeof(SpriteRec);
        }
        scratch_top -= 0x20;
        fx_draw_pool();
    }
}

void fx_spawn_style(s32 *pos, s32 style) {
    FxEffect *rec;
    FxParams fx;
    u32 bits;

    rec = fx_rec30_alloc();
    if (rec != NULL) {
        bits = style;
        if ((s32)bits >= 0) {
            if (bits >= 24) {
                bits = 23;
            }
            bits = fx_style_table[bits];
        }
        fx.used = ((bits >> 18) & 3) + 1;
        fx.progress_step = (bits & 0xF) << 5;
        fx.size_speed = ((bits >> 8) & 0xF) << 16;
        fx.size_accel = (((bits >> 4) & 0xF) * 0xFFFFF) << 10;
        fx.col[0] = (bits >> 16) & 3;
        fx.col[1] = (bits >> 14) & 3;
        fx.size = 0;
        fx.progress = 0;
        fx.unk_14 = 0;
        fx.col[2] = (bits >> 12) & 3;
        rec->color_r = fx_colour_level(rec->color_r);
        rec->color_g = fx_colour_level(rec->color_g);
        rec->color_b = fx_colour_level(rec->color_b);
        *(s32 *)&rec->pos[0] = pos[0];
        *(s32 *)&rec->pos[4] = pos[1];
        *(s32 *)&rec->pos[8] = pos[2];
        rec->used = fx.used;
        rec->progress = fx.progress;
        rec->progress_step = fx.progress_step;
        rec->size = fx.size;
        rec->size_speed = fx.size_speed;
        rec->size_accel = fx.size_accel;
        rec->color_r = fx.col[0];
        rec->color_g = fx.col[1];
        rec->color_b = fx.col[2];
        *(s32 *)rec->size_speed_min = fx.unk_14;
        rec->callback = 0;
    }
}

/* Takes a free FxEffect and fills it: the position (3 words) from pos, the rest from tmpl, and the callback.
 * Returns 1, or 0 when all records are in use. */
s32 fx_spawn_template(s32 *pos, RecTemplate *tmpl, void (*callback)()) {
    FxEffect *rec = fx_rec30_alloc();
    s32 *words;
    s32 tmpl_14;

    if (rec == NULL) {
        return 0;
    }
    words = (s32 *)rec;
    words[0] = pos[0];
    words[1] = pos[1];
    words[2] = pos[2];
    rec->used = tmpl->used;
    rec->progress = tmpl->progress;
    rec->progress_step = tmpl->progress_step;
    rec->size = tmpl->size;
    rec->size_speed = tmpl->size_speed;
    rec->size_accel = tmpl->size_accel;
    rec->color_r = tmpl->color_r;
    rec->color_g = tmpl->color_g;
    rec->color_b = tmpl->color_b;
    tmpl_14 = tmpl->unk_14;
    rec->callback = callback;
    *(s32 *)rec->size_speed_min = tmpl_14;
    return 1;
}

s16 *fx_mask_row_build(s16 *out, s32 shift, s32 level)
{
    s32 step = 0x40 >> shift;
    s32 idx;
    s32 outer;
    s32 x, y, bit, mask;

    idx = (level < 32 ? level : 31);
    if ((level < 32 ? level : 31) < 0) {
        idx = 0;
    }
    level = d_8011E510[32 - idx];
    level = level * level / 3;
    outer = step + 0x40;
    outer = outer * outer;
    for (y = step; y <= 0x40; y += step) {
        x = step;
        bit = 0;
        mask = 0;
        for (; x <= 0x40; x += step, bit++) {
            s32 d = x * x + y * y;
            if (d < level || d > outer) {
                mask |= 1 << bit;
            }
        }
        *out++ = mask;
    }
    return out;
}

/* Calls fx_mask_row_build 32 times, each call taking the pointer the previous one returned. */
void fx_table_build(void *buf, s32 index) {
    void *cursor;
    s32 i;

    cursor = buf;
    i = 0;
    do {
        cursor = fx_mask_row_build(cursor, index, i);
        i += 1;
    } while (i < 0x20);
}

void fx_tables_init(void) {
    d_8012040C = 0xB0;
    d_80120410 = 0x3690;
    fx_vram_rect_c = 0x100;
    d_80132FEE = 0xDA;
    d_80132FF0 = 0x10;
    d_80132FF2 = 1;
    fx_vram_rect_d = 0x110;
    d_80132FF6 = 0xDA;
    d_80132FF8 = 0x10;
    d_80132FFA = 1;
    fx_table_build(&d_80132FFC, 0);
    fx_table_build(&d_8013303C, 1);
    fx_table_build(&d_801330BC, 2);
    fx_table_build(&d_801331BC, 3);
    fx_table_build(&d_801333BC, 4);
}

/* Resets a FxRecord record to its idle state (unk_33 starts at 0x2E). */
void fx_rec34_reset(FxRecord *rec) {
    rec->phase = 0;
    rec->phase_speed = 0;
    rec->radius_motion[0] = 0;
    rec->radius_motion[1] = 0;
    rec->radius_motion[2] = 0;
    rec->radius_motion[3] = 0;
    rec->color_r = 0;
    rec->color_g = 0;
    rec->color_b = 0;
    rec->unk_33 = 0x2E;
    rec->active = 0;
}

void fx_rec34_reset_all(void) {
    FxRecord *rec = fx_rec34_pool;
    s32 i = 0;

    do {
        fx_rec34_reset(rec);
        i++;
        rec++;
    } while (i < 32);
}

/* Returns the first of the 32 FxRecord records at fx_rec34_pool whose unk_16 is zero, or NULL if none is. */
FxRecord *fx_rec34_alloc(void) {
    FxRecord *rec = fx_rec34_pool;
    s32 i;
    for (i = 0; i < 32; i++, rec++) {
        if (rec->active == 0) {
            return rec;
        }
    }
    return NULL;
}

void fn_8010DFEC(void) {

}

void fn_8010DFF4(void) {
    fx_rec34_reset_all();
}

void clut_fill_gradient(u16 *clut, s32 count) {
    u16 *p;
    u16 *q;
    s32 width;
    s32 clamped;
    s32 i;
    s32 g;

    p = clut;
    q = p;
    width = count;
    if (count >= 0x20) {
        width = 0x1F;
    }
    clamped = count;
    if (count >= 0x20) {
        clamped = 0x1F;
    }
    if (clamped < 0) {
        width = 0;
    }
    count = width;
    for (i = 0x1F; i >= 0; i--) {
        *p++ = 0;
    }
    q++;
    *q = 0xA108;
    q++;
    *q = 0xBDEF;
    q++;
    for (i = count - 2; i > 0; i--) {
        g = i * 0x1F / count;
        *q++ = (g << 10) | (g << 5) | g | 0x8000;
    }
}

/* Far colour (RFC/GFC/BFC, GTE control 21-23) from three globals; the loads go into the registers the original uses. */
void fx_restore_bk_colour(void) {
    register s32 green asm("$2") = fx_saved_bk_green;
    register s32 blue asm("$3") = fx_saved_bk_blue;
    register s32 red asm("$4") = fx_saved_bk_red;
    gte_set_ctrl(RFC, red);
    gte_set_ctrl(GFC, green);
    gte_set_ctrl(BFC, blue);
}

void fx_save_bk_colour(s32 arg) {
    s32 a, b, c;

    gte_get_ctrl(RFC, a);
    gte_get_ctrl(GFC, b);
    gte_get_ctrl(BFC, c);
    gte_set_ctrl(RFC, 0);
    gte_set_ctrl(GFC, 0);
    gte_set_ctrl(BFC, 0);
    fx_saved_bk_red = a;
    fx_saved_bk_green = arg;
    fx_saved_bk_blue = c;
}

/* One step of a FxRecord: angle unk_10 advances by unk_12 (unk_14 is it, at least 0x800), the position word
 * unk_18[0] by unk_18[1], which accelerates by unk_18[2] up to a limit of unk_18[3]; unk_2C is a per-step
 * callback. The record is released when it stops (unk_16 == 0) or the angle reaches 0x1000. */
void fx_rec34_step(FxRecord *rec) {
    void (*step)(FxRecord *);
    s32 limit;
    s32 speed;
    u16 angle;

    if (rec->active != 0) {
        rec->phase += rec->phase_speed;
        angle = rec->phase;
        if (rec->phase < 0x800) {
            angle = 0x800;
        }
        rec->clamped_phase = angle;
        rec->radius_motion[0] += rec->radius_motion[1];
        limit = rec->radius_motion[3];
        speed = rec->radius_motion[1] + rec->radius_motion[2];
        rec->radius_motion[1] = speed;
        if (speed < limit) {
            rec->radius_motion[1] = limit;
        }
        step = (void (*)(FxRecord *)) rec->step_fn;
        if ((step != NULL && (step(rec), rec->active == 0)) || rec->phase >= 0x1000) {
            fx_rec34_reset(rec);
        }
    }
}

/* Loads (x, y) into V0 and z into VZ0, runs RTPS and returns max(MAC3, 0x80). The nop is the load
 * delay slot after mfc2, which the original has and gte_get doesn't add. */
s32 gte_depth_clamped(s32 x, s32 y, s32 z) {
    gte_set(VXY0, (x & 0xFFFF) | (y << 16));
    gte_set(VZ0, z);
    gte_rtps();
    gte_get(MAC3, z);
    mips_nop();
    if (z < 0x80) {
        return 0x80;
    }
    return z;
}

/* Adds a draw-mode primitive (tag length 2, texture page word 0xE2042318) from the work area's packet buffer
 * in front of OT entry ot. */
void prim_add_draw_mode(WorkArea *work, u32 *ot) {
    u8 *prim = work->packet;

    work->packet = prim + 0xC;
    prim[3] = 2;
    ((u32 *)prim)[1] = 0xE2042318;
    ((u32 *)prim)[2] = 0;
    addPrim(ot, prim);
}

s32 prim_depth_cue(s32 *colour, s32 ir0) {
    s32 out;
    gte_load(RGB, colour, 0);
    gte_set(IR0, ir0);
    gte_dpcs();
    gte_get(RGB2, out);
    return out;
}

/* Projects one row of the glow grid (up to 17 vertices): height scr->y, depth scr->z + j * extent_z / 4096,
 * x from scr->x across extent_x in steps of step / 4096. Texture u = i / 64 (0x3F at the last vertex),
 * v = j / 64 clamped to 0..0x3F. The product for the next vertex is computed while rtps runs. */
static inline void glow_project_row(GlowVert *row, FxGlowScratch *scr, s32 j, s32 step) {
    s32 i, offset, flag, z, y, x, extent, v;

    z = scr->z;
    y = scr->y;
    x = scr->x;
    z += j * scr->extent_z / 4096;
    extent = scr->extent_x;
    v = j / 64;
    v = MAX(MIN(v, 0x3F), 0);
    offset = 0;
    i = 0;
    do {
        gte_set(VXY0, ((x + offset) & 0xFFFF) | (y << 16));
        gte_set(VZ0, z);
        gte_nop();
        gte_nop();
        offset = i + step;
        mips_mult(extent, offset);
        gte_rtps_b();
        mips_mflo(offset);
        offset >>= 12;
        gte_get_ctrl_wait(FLAG, flag);
        row->clipped = (flag & GTE_FLAG_ERRORS) != 0;
        gte_stsxy(row);
        row->u = i / 64;
        i += step;
        row->v = v;
        row++;
    } while (i <= 0x1000);
    row--;
    row->u = 0x3F;
}

/* Draws one quarter of a glow sprite for fx_glow_draw: a grid of 2^(level-1) x 2^(level-1) textured quads
 * from scr's centre out to (extent_x, extent_z), two rows of projected vertices at a time. A cell is skipped
 * when its bit in the row's mask is set or one of its corners failed to project. */
void fx_glow_grid_draw(FxGlowScratch *scr, s32 extent_x, s32 extent_z, s16 *masks) {
    GlowVert *prev = scratch_alloc(sizeof(GlowVert) * 17);
    GlowVert *cur = scratch_alloc(sizeof(GlowVert) * 17);
    GlowVert *swap;
    GlowVert *near;
    GlowVert *far;
    PolyFT4 *quad;
    WorkArea *work;
    u32 *ot;
    s32 level, step, cells, j;
    u32 skip;

    scr->extent_x = extent_x;
    scr->extent_z = extent_z;
    level = scr->level;
    step = 1 << (13 - level);
    glow_project_row(prev, scr, 0, step);

    for (j = step; j <= 0x1000; j += step) {
        glow_project_row(cur, scr, j, step);

        near = prev;
        far = cur;
        skip = (u16)*masks++;
        cells = 1 << (level - 1);
        work = scr->work;
        ot = scr->ot;
        for (; cells > 0; cells--, far++, near++, skip >>= 1) {
            if ((skip & 1) == 0
                && (near[0].clipped | near[1].clipped | far[0].clipped | far[1].clipped) == 0) {
                quad = work->packet;
                work->packet = quad + 1;
                quad->len = 9;
                /* word and halfword copies: colour + code, x/y pairs, u/v pairs */
                *(s32 *)&quad->r0 = scr->colour;
                *(s32 *)&quad->x0 = near[0].sxy;
                *(s32 *)&quad->x1 = near[1].sxy;
                *(u16 *)&quad->u0 = *(u16 *)&near[0].u;
                *(u16 *)&quad->u1 = *(u16 *)&near[1].u;
                *(s32 *)&quad->x2 = far[0].sxy;
                *(s32 *)&quad->x3 = far[1].sxy;
                *(u16 *)&quad->u2 = *(u16 *)&far[0].u;
                *(u16 *)&quad->u3 = *(u16 *)&far[1].u;
                quad->tpage = d_8012040C;
                quad->clut = d_80120410;
                addPrim(ot, quad);
            }
        }
        swap = prev;
        prev = cur;
        cur = swap;
    }
    scratch_top -= sizeof(GlowVert) * 17 * 2;
}

s16 *fx_glow_table_entry(s32 shift, s32 value) {
    s16 *base;
    value = NOT_NEGATIVE(value < 32 ? value : 31);
    base = fx_glow_tables[shift];
    return base + (value << shift);
}

/* Draws one FxRecord as a glow: skipped when out of range of the camera or culled; the level of detail
 * comes from the nearest of eight points around the record (radius unk_18[0] >> 12) against the
 * D_8011E564 thresholds, then four quarter sprites (fx_glow_grid_draw), a draw mode and two CLUT packets. */
void fx_glow_draw(FxRecord *rec, View *vw, Camera *cam) {
    u16 clut[32];
    s32 dx, dy, dz;
    s32 r, t;
    s32 nearest, near_z, v;
    s32 depth;
    s32 n;
    s32 *p;
    s32 colour;
    s16 *size;
    FxGlowScratch *scr;
    WorkArea *work;
    u32 *ot;
    u8 *prim;
    s32 *src;
    s32 *dst;
    s32 i;

    if (rec->active == 0) {
        return;
    }
    dx = rec->pos[0] - cam->pos.vx;
    dy = rec->pos[1] - cam->pos.vy;
    dz = rec->pos[2] - cam->pos.vz;
    if ((u32)(dx + 0x4000) > 0x7FFF || (u32)(dy + 0x4000) > 0x7FFF || (u32)(dz + 0x4000) > 0x7FFF) {
        return;
    }
    r = rec->radius_motion[0] / 4096;
    nearest = 0x7FFFFFFF;
    v = gte_depth_clamped(dx + r, dy, dz);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) goto near;
    v = gte_depth_clamped(dx - r, dy, dz);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) goto near;
    v = gte_depth_clamped(dx, dy, dz + r);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) goto near;
    v = gte_depth_clamped(dx, dy, dz - r);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) goto near;
    t = r * 2 / 3;
    v = gte_depth_clamped(dx + t, dy, dz + t);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) goto near;
    v = gte_depth_clamped(dx - t, dy, dz + t);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) goto near;
    v = gte_depth_clamped(dx + t, dy, dz - t);
    if (v < nearest) nearest = v;
    if (nearest <= 0x40) {
near:
        near_z = 0x40;
    } else {
        v = gte_depth_clamped(dx - t, dy, dz - t);
        if (v < nearest) nearest = v;
        near_z = nearest;
        if (near_z <= 0x40) {
            near_z = 0x40;
        }
    }
    n = 4;
    p = fx_depth_thresholds;
    do {
        if (*p++ >= near_z) {
            nearest = n;
            goto done;
        }
    } while (--n > 0);
    nearest = 1;
done:
    colour = prim_depth_cue((s32 *)&rec->color_r, rec->clamped_phase);
    if (colour == 0x2E000000) {
        return;
    }
    depth = gte_depth_clamped(dx, dy, dz);
    if (depth < rec->radius_motion[0] / 4096) {
        return;
    }
    scr = scratch_alloc(sizeof(FxGlowScratch));
    scr->x = dx;
    scr->y = dy;
    scr->z = dz;
    scr->level = nearest;
    scr->colour = colour;
    scr->work = work_area_ptr;
    if (rec->depth_sorted == 0) {
        scr->ot = &((FxOtBuffer *)vw->ot)->front;
    } else {
        scr->ot = fx_ot_entry(vw, depth);
    }
    size = fx_glow_table_entry(nearest, (0x1000 - rec->phase) / 128);
    fx_glow_grid_draw(scr, r, r, size);
    fx_glow_grid_draw(scr, -r, r, size);
    fx_glow_grid_draw(scr, r, -r, size);
    fx_glow_grid_draw(scr, -r, -r, size);
    prim_add_draw_mode(scr->work, scr->ot);
    work = scr->work;
    ot = scr->ot;
    clut_fill_gradient(clut, (0x1000 - rec->phase) / 128);
    prim = work->packet;
    work->packet = prim + 0x44;
    prim_vram_load_packet(prim, &fx_vram_rect_c);
    src = (s32 *)clut;
    dst = (s32 *)(prim + 0x10);
    i = 0;
    do {
        i++;
        *dst++ = *src++;
    } while (i < 8);
    addPrim(ot, prim);
    prim = work->packet;
    work->packet = prim + 0x44;
    prim_vram_load_packet(prim, &fx_vram_rect_d);
    dst = (s32 *)(prim + 0x10);
    i = 0;
    do {
        i++;
        *dst++ = *src++;
    } while (i < 8);
    addPrim(ot, prim);
    scratch_top -= sizeof(FxGlowScratch);
}

/* Runs fx_rec34_step on all 32 entries of fx_rec34_pool. */
void fx_rec34_step_all(void) {
    FxRecord *entry;
    s32 i;

    entry = fx_rec34_pool;
    i = 0;
    do {
        fx_rec34_step(entry);
        i++;
        entry++;
    } while (i < 0x20);
}

void fx_draw_pool(void) {
    s32 *mtx;
    FxRecord *rec;
    Camera *cam;
    View *vw = views;
    s32 i;
    s32 ofs_x, ofs_y;
    /* The asm leaves the sixth matrix word in $a0, which is the colour argument below. */
    register s32 bk_colour asm("$4");

    if (cur_cam_index >= 0) {
        mtx = scratch_alloc(0x20);
        scale_rows((s16 *)&vw->unk_2C[0x34], (s16 *)&vw->unk_2C[0xC], (s16 *)mtx);
        gte_load_R_v1a0v0_out(bk_colour, mtx);
        ofs_x = view_screen_offsets[0].value;
        ofs_y = view_screen_offsets[0].offset_y;
        gte_set_ctrl(OFX, ofs_x << 16);
        gte_set_ctrl(OFY, ofs_y << 16);
        gte_set_ctrl(H, 0x80);
        gte_set_ctrl(TRX, 0);
        gte_set_ctrl(TRY, 0);
        gte_set_ctrl(TRZ, 0);
        scratch_top -= 0x20;
        rec = fx_rec34_pool;
        cam = &cameras[cur_cam_index];
        fx_save_bk_colour(bk_colour);
        for (i = 0; i < 0x20; i++) {
            fx_glow_draw(rec, vw, cam);
            rec++;
        }
        fx_restore_bk_colour();
    }
}

/* Sets up record `rec` from a position and a parameter block; unk_14 is unk_10 raised to at least 0x800. */
void fx_rec34_init(FxRecord *rec, s32 *pos, FxRecordParams *params, s32 arg) {
    s16 v;

    rec->pos[0] = pos[0];
    rec->pos[1] = pos[1];
    rec->pos[2] = pos[2];
    rec->active = 1;
    rec->depth_sorted = params->b0;
    v = params->h4;
    rec->phase = v;
    rec->clamped_phase = v < 0x800 ? 0x800 : v;
    rec->phase_speed = params->h6;
    rec->radius_motion[0] = params->w[0];
    rec->radius_motion[1] = params->w[1];
    rec->radius_motion[2] = params->w[2];
    rec->radius_motion[3] = params->w[3];
    rec->color_r = params->b1;
    rec->color_g = params->b2;
    rec->color_b = params->b3;
    rec->step_fn = arg;
}

/* Sets up a free FxRecord (fx_rec34_alloc) at pos from params. */
void fx_rec34_spawn(s32 *pos, FxRecordParams *params) {
    FxRecord *rec;

    rec = fx_rec34_alloc();
    if (rec != NULL) {
        fx_rec34_init(rec, pos, params, 0);
    }
}

void fx_rec34_spawn_cb(s32 *pos, FxRecordParams *params, s32 arg) {
    FxRecord *rec;

    rec = fx_rec34_alloc();
    if (rec != NULL) {
        fx_rec34_init(rec, pos, params, arg);
    }
}
