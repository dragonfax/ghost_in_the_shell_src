/* stationary_laser: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

void stationary_laser_update(Object *obj, ObjHandler *handler);
void stationary_laser_draw(Object *obj, ObjHandler *handler);
/* Shooting enemy tick: advances the 0x276 counter (capped at 0x1800), steps the
 * four shot slots (timer, shots left, accumulator, aim), and once the shots are
 * spent or walk_state is 1, points handlers[1] and handlers[3] at new fns and
 * clears their state. */
void enemy_shot_slots_update(Object *obj) {
    EnemyShotSlot *slot;
    s32 i;

    if (*(s16 *)&obj->vars.enemy.unk_276 < 0x1800) {
        *(s16 *)&obj->vars.enemy.unk_276 += 0x28;
    }
    slot = (EnemyShotSlot *)&obj->vars.enemy.mode;
    for (i = 0; i < 4; i++, slot++) {
        if (slot->timer > 0) {
            slot->timer--;
        } else if (slot->count != 0) {
            slot->acc += 0x80;
            if ((s16)slot->acc >= 0x1001) {
                slot->count--;
                if (slot->count > 0) {
                    slot->aim = rand_a_next();
                    slot->acc = 0;
                }
            }
        }
    }
    if (*(s16 *)&obj->vars.enemy.unk_260[2] == 0 || *(u8 *)&obj->vars.enemy.walk_state == 1) {
        obj->handlers[1].fn = stationary_laser_update;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[3].fn = stationary_laser_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
    }
}

static inline void spark_emit(s32 x, s32 y, s32 z, s32 val, s32 colour, s32 unk10) {
    register s32 value asm("$7") = val;
    SparkList *list = &spark_list;
    s32 n = spark_count;
    SparkRec *rec;
    u8 *old;

    if (n < 0xFF) {
        rec = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)rec->colour = colour;
        old = list->tail[colour >> 24];
        list->tail[colour >> 24] = &rec->next;
        *old = n;
        rec->next = 0;
        rec->x = x;
        rec->y = y;
        rec->z = z;
        rec->unk_12 = value;
        rec->yaw = 0;
        rec->pitch = 0;
        rec->roll = unk10;
    }
}
void enemy_shooter_emit_draw(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s32 base;
    s32 i;
    EmitterSlot *slot;
    s32 colour;
    s32 scale;
    s32 shifted;
    s32 red, inv, mix, blue, level, top;
    s32 value;

    pos = scratch_alloc(0x10);
    base = get_model_slot_base();
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    slot = (EmitterSlot *)&obj->vars;
    for (i = 0; i < 4; i++, slot++) {
        if (slot->timer <= 0 && slot->enabled != 0) {
            shifted = slot->scale << 16;
            scale = shifted >> 16;
            red = scale * 0xC00;
            inv = 0x1000 - scale;
            if (red < 0) {
                red += 0xFFF;
            }
            mix = (inv << 10) + (scale << 12);
            blue = mix >> 17;
            if (mix < 0) {
                blue = (mix + 0xFFF) >> 17;
            }
            red = red >> 17;
            scale = shifted >> 21;
            if ((red | scale | blue) == 0) {
                blue = 1;
            }
            colour = (blue << 16) | (scale << 8) | red;
            value = pool_spawn_scaled(pchr_blend(base + 0x10, base + 0x11, inv, 0), 0x3000, 0x3000, 0x1000);
            spark_emit(pos[0], pos[1], pos[2], value, colour, slot->colour);
        }
    }
    value = base + 0xF;
    level = (*(u16 *)&obj->vars.enemy_spawn_shooter_obj.unk_276 << 16) >> 21;
    top = level;
    if (level == 0) {
        top = 1;
    }
    colour = (top << 16) | (level << 8) | level;
    spark_emit(pos[0], pos[1], pos[2], value, colour, 0);
    scratch_top -= 0x10;
}

void stationary_laser_update(Object *obj, ObjHandler *handler) {
    StatLaserS07 *v = (StatLaserS07 *)obj;
    register s32 obj_hit asm("$16");
    s32 *from;
    s32 *hit;
    s32 *to;
    s32 world_hit;
    s16 target;
    s32 len;

    v->timer++;
    if (v->timer >= 0xB5) {
        v->off = 1;
    }
    if (v->off == 1) {
        v->power -= 0x44;
        if (v->power < 0) {
            obj_snd2_stop((Object *)v);
            obj_free((Object *)v);
            return;
        }
    } else if (v->power < 0x1000) {
        v->power += 0x44;
    }
    v->power = MAX(MIN(v->power, 0x1000), 0);
    if (v->sound != 0) {
        sound_set_volume(v->sound, sound_volume_of(SND_PAIR(SND_VREEEE | SND_HELD | SND_GROUP(1), SND_STATIONARY_LASER_LOOP | SND_HELD | SND_GROUP(1)), v->power));
    }
    if (v->decay > 0) {
        v->decay -= 0x22;
    }
    from = scratch_alloc(0x30);
    hit = from + 8;
    to = from + 4;
    v->flicker ^= 1;
    from[0] = v->x >> 12;
    from[1] = v->y >> 12;
    from[2] = v->z >> 12;
    to[0] = 0;
    to[1] = 0;
    to[2] = 0xED8;
    rotate_xz_twice(v->yaw, -v->pitch, to, to + 1, to + 2);
    to[0] += from[0];
    to[1] += from[1];
    to[2] += from[2];
    world_hit = trace_world(8, 0x24, from, to, to);
    set_collide_mode(1);
    obj_hit = trace_objects(from, to, 0xC, hit, &target) != 0;
    set_collide_mode(0);
    if ((u8)obj_hit == 1) {
        hit_target_masked(0, 1, atan2(hit[2] - from[2], hit[0] - from[0]), v->owner);
    } else {
        hit = to;
    }
    if (world_hit == 1 || obj_hit == 1) {
        len = isqrt(length_sq(hit[0] - from[0], hit[1] - from[1], hit[2] - from[2]));
        v->hit_len = len / 0xBE;
        v->hit_frac = ((len % 0xBE) << 12) / 0xBE;
    } else {
        v->hit_len = 0x14;
    }
    v->jitter = (rand_a_next() % 16) << 4;
    scratch_top -= 0x30;
}

void stationary_laser_draw(Object *obj, ObjHandler *handler) {
    StationaryLaserVars *lv = (StationaryLaserVars *)obj;
    LaserScratch *sc = scratch_alloc(0x20);
    Vec3 *step = &sc->step;
    s16 *rot = scratch_alloc(8);
    Vec3 *pos = &sc->pos;
    s32 a, tail;
    s32 pitch, hi, base, sprite, size, colour, i, fade;

    base = get_model_slot_base();
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    sprite = base + 0xF;
    size = (s16)lv->end_size >> 5;
    hi = size;
    if (!hi) {
        hi = 1;
    }
    colour = (hi << 16) | (size << 8) | size;
    spark_add(pos->x, pos->y, pos->z, 0, 0, 0, sprite, colour);
    a = lv->start_size;
    size = a + lv->size_add;
    size >>= 5;
    hi = size;
    if (!hi) {
        hi = 1;
    }
    colour = (hi << 16) | (size << 8) | size;
    sprite = base + 8;
    step->x = 0;
    step->y = 0;
    step->z = 0xBE;
    rotate_xz_twice(rot[1], rot[0], &step->x, &step->y, &step->z);
    for (i = 0; i < lv->segments; i++) {
        spark_add(pos->x, pos->y, pos->z, rot[1] + 0x800, -rot[0], rot[2], sprite, colour);
        pos->x += step->x;
        pos->y += step->y;
        pos->z += step->z;
    }
    if (i != 0x14) {
        fade = lv->fade;
        sprite = pool_spawn_scaled(sprite, 0x1000, 0x1000, fade);
        spark_add(pos->x, pos->y, pos->z, rot[1] + 0x800, -rot[0], rot[2], sprite, colour);
        step->x = fade * step->x / 0x1000;
        step->y = fade * step->y / 0x1000;
        step->z = fade * step->z / 0x1000;
        pos->x += step->x;
        pos->y += step->y;
        pos->z += step->z;
        tail = lv->tail_sprite;
        tail += 0xA;
        sprite = base + tail;
        spark_add(pos->x, pos->y, pos->z, rot[1] + 0x800, -rot[0], rot[2], sprite, colour);
        sprite = base + 0xF;
        spark_add(pos->x, pos->y, pos->z, 0, 0, 0, sprite, colour);
    }
    scratch_top -= 0x28;
}

void enemy_shooter_emit_draw(Object *obj, ObjHandler *handler);
/* Spawns a four-slot shooting enemy at pos/angles, copying unk_184 from parent. */
Object *enemy_spawn_shooter(s32 *pos, s16 *angles, Object *parent) {
    Object *obj;
    EnemyShotSlot *slots;
    s32 i;

    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    slots = (EnemyShotSlot *)&obj->vars.enemy.mode;
    list_insert_before((Node *)get_obj_list_actors_tail(), &obj->node);
    obj->x = pos[0];
    obj->y = pos[1];
    obj->z = pos[2];
    obj->pitch = angles[0];
    obj->yaw = angles[1];
    obj->roll = angles[2];
    obj->handlers[1].fn = (void *)enemy_shot_slots_update;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->callback = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[3].fn = enemy_shooter_emit_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    *(u8 *)&obj->vars.enemy.walk_state = 0;
    *(s16 *)&obj->vars.enemy.sound = 0;
    obj->vars.enemy_spawn_shooter_obj.unused_274 = 0;
    for (i = 0; i < 4; i++, slots++) {
        slots->timer = i * 8;
        slots->count = 4;
        slots->acc = 0;
        slots->aim = rand_a_next();
    }
    *(s16 *)&obj->vars.enemy.unk_276 = 0;
    *(s16 *)&obj->vars.enemy.unk_26E = 0;
    obj->damage = parent->damage;
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->vars.enemy_spawn_shooter_obj.unused_268 = 0;
    obj_snd2_loop_start(obj);
    return obj;
}

/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void script_op_jump_if_within_dist(Object *obj) {
    s32 *player = player_position();
    s32 dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    s16 *cursor = obj->script.pc;
    s32 threshold;
    s32 index;

    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold >= dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}
