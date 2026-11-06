/* stage: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

extern s32 bomb_mech_m7_boss_active;

void debris_spawn_tick(void);

void fly_emit_tick(void);
void bomb_mech_m7_boss_spawn_entry(void);
void bomb_mech_m7_boss_phase0_systems(void) {
    if (bomb_mech_m7_boss_active != 0) {
        bomb_mech_m7_boss_spawn_entry();
        fly_emit_tick();
        debris_spawn_tick();
    }
}

extern s32 bomb_mech_m7_boss_active;

void fly_update(void);

void spark_update(void);

void ramp_timer_update(void);

void keyframe_table_run(void);

void model_part_run(void);

void cam_shake_run(void);

void debris_update_all(void);

void keymover_update_all(void);

void bomb_mech_m7_boss_update_systems(void) {
    if (bomb_mech_m7_boss_active != 0) {
        fly_update();
        loop_state_update();
        keymover_update_all();
        spark_update();
        ramp_timer_update();
        keyframe_table_run();
        model_part_run();
        cam_shake_run();
        debris_update_all();
    }
}

extern s32 bomb_mech_m7_boss_active;

void fly_check_hits(void);

void spark_hit_test_all(void);

void shots_check_hits(void);

void shots_trace(void);

void bomb_mech_m7_boss_phase2_systems(void) {
    if (bomb_mech_m7_boss_active != 0) {
        fly_check_hits();
        shots_trace();
        spark_hit_test_all();
        shots_check_hits();
    }
}

extern s32 bomb_mech_m7_boss_active;

void spark_emitters_update(void);

void seg_table_run(void);

void bomb_mech_spark_update(void);

void keyframe_entries_update(void);

void model_part_draw_run(void);

void keytrack_update_all(void);

void debris_draw_all(void);
void timer_sparks_emit(void);
void shot_draw_all(void);

void bomb_mech_m7_boss_frame(void) {
    if (bomb_mech_m7_boss_active != 0) {
        spark_emitters_update();
        timer_sparks_emit();
        shot_draw_all();
        seg_table_run();
        bomb_mech_spark_update();
        keyframe_entries_update();
        model_part_draw_run();
        keytrack_update_all();
        debris_draw_all();
    }
}

extern s32 bomb_mech_m7_boss_active;

void ramp_timer_stop(void);

void keytrack_reset_all(void);

void boss_state_reset(void);

void fly_setup(s32 arg0);
void spark_table_clear(void);
void model_part_clear(void);

void fly_shutdown(void);
void keyframe_table_clear(void);

void keyframe_table_reset(s32 next);

void debris_init(s32 value);

void shot_pool_clear(void);

void bomb_mech_m7_boss_start(s32 arg0) {
    fly_shutdown();
    boss_state_reset();
    shot_pool_clear();
    spark_table_clear();
    ramp_timer_stop();
    keyframe_table_reset(arg0);
    model_part_clear();
    keytrack_reset_all();
    fly_setup(arg0);
    debris_init(arg0);
    bomb_mech_m7_boss_active = 1;
}

extern s32 bomb_mech_m7_boss_active;

void bomb_mech_m7_boss_stop(void);
void func_800C6F34(void);
void ramp_timer_reset(void);
void model_part_reset(void);
void fly_stop(void);
void func_800C93BC(void);
void timer_reset(void);

void debris_stop(void);
void fly_init(void);
void keytrack_deactivate_first(void);

void bomb_mech_m7_boss_stop(void) {
    if (bomb_mech_m7_boss_active != 0) {
        fly_init();
        timer_reset();
        func_800C93BC();
        func_800C6F34();
        ramp_timer_reset();
        keyframe_table_clear();
        model_part_reset();
        keytrack_deactivate_first();
        fly_stop();
        debris_stop();
        bomb_mech_m7_boss_active = 0;
    }
}

void obj_set_hit_reaction(Object *obj, s32 flag) {
    s32 flags = obj->flags;

    obj->unk_17A = flag;
    if (flag != 0) {
        flags |= 0x4;
    } else {
        flags &= -5;
    }
    obj->flags = flags;
}

void boss_proximity_stub(void);
void boss_proximity_hook(void) {
    boss_proximity_stub();
}

void sfx_emitter_step(SfxEmitter *e) {
    e->active = keyframe_step(&e->keyframes, &e->tick, &e->from, &e->to, &e->blend);
    e->level -= 0x80;
}

extern SfxEmitter sfx_emitters[0x20];
void sfx_emitter_step(SfxEmitter *entry);
void sfx_emitters_update(void) {
    SfxEmitter *entry = sfx_emitters;
    s32 i = 0;
    do {
        if (entry->active == 1) {
            sfx_emitter_step(entry);
        }
        i += 1;
        entry += 1;
    } while (i < 0x20);
}

/* Hits the player when they come within the emitter's blended range. */
void sfx_emitter_hit_player(SfxEmitter *e) {
    s32 dist;
    s32 range;
    s32 *pp;
    s16 blend;

    dist = player_dist_sq(&e->pos.x);
    blend = e->blend;
    range = blend * 0x90 + (0x1000 - blend) * 0xC;
    range /= 0x1000;
    range *= 4;
    range *= range;
    if (dist < range) {
        pp = player_position();
        hit_target_masked(0, 4, atan2(e->pos.z - pp[2], e->pos.x - pp[0]), 0xE);
    }
}

/* Same code as sfx_emitters_update (s07). */
void sfx_emitters_hit_check(void) {
    SfxEmitter *entry = sfx_emitters;
    s32 i = 0;
    do {
        if (entry->active == 1) {
            sfx_emitter_hit_player(entry);
        }
        i += 1;
        entry += 1;
    } while (i < 0x20);
}

static inline s32 beam_colour(s32 blue, s32 green, s32 red) {
    red >>= 5;
    blue >>= 5;
    green >>= 5;
    if ((blue | green | red) == 0) {
        red = 1;
    }
    return (red << 16) | (green << 8) | blue;
}
/* Spawns a spark at the emitter's position (model blended between the owner's key_from and
 * key_to slots, colour from its level unk_24), then queues that position. */
void sfx_emitter_spawn_spark(SfxEmitter *e) {
    s32 slot_b;
    s32 slot_a;
    s32 level;
    s32 scaled;
    s32 colour;
    register s32 model asm("$7");
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 n;
    s32 x, y, z;

    slot_b = model_slot_pchr(*(s32 *)e->owner->asset);
    slot_a = slot_b + (s16)e->from;
    slot_b += (s16)e->to;
    level = (s16)e->level;
    scaled = level * 3;
    colour = beam_colour(scaled / 4, level, scaled / 4);
    model = pool_spawn_scaled(pchr_blend(slot_a, slot_b, 0x1000 - e->blend, 0), 0x4000, 0x4000, 0x4000);
    list = &spark_list;
    n = spark_count;
    x = e->pos.x;
    y = e->pos.y;
    z = e->pos.z;
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
        s->unk_12 = model;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
    req_queue_push_vec(e->pos.x, e->pos.y, e->pos.z);
}

/* Same code as sfx_emitters_update (s07). */
void sfx_emitters_spawn_sparks(void) {
    SfxEmitter *entry = sfx_emitters;
    s32 i = 0;
    do {
        if (entry->active == 1) {
            sfx_emitter_spawn_spark(entry);
        }
        i += 1;
        entry += 1;
    } while (i < 0x20);
}

extern s32 D_80125970;
/* Clears the type link's unk_0A (halfword at 0x16) while D_80125970 is 1. */
void func_800C6088(Object *obj) {
    if (D_80125970 == 1) {
        obj->type.unk_0A = 0;
    }
}

SfxEmitter *sfx_emitter_alloc(void) {
    SfxEmitter *rec;
    s32 i;

    rec = sfx_emitters;
    for (i = 0; i < 0x20; i++) {
        if (rec->active == 0) {
            return rec;
        }
        rec++;
    }
    return NULL;
}

/* Shifts words 1..3 of src by 12 into a scratch vector and passes it to sound_set_pos. */
s32 sfx_emitter_set_pos(s32 *src, s32 index) {
    Vec3 *scaled = scratch_alloc(0x10);

    scaled->x = src[1] << 12;
    scaled->y = src[2] << 12;
    scaled->z = src[3] << 12;
    sound_set_pos(index, scaled);
    scratch_top -= 0x10;
    return 0;
}

extern Keyframe sfx_keyframes[];
extern FxRecordParams sfx_emitter_params;
void tick_reset(s32 *arg0);
/* Takes a free sfx_emitters entry, stores owner id and 3 words from src, sets up its keyframe
   cursor and the 0x1FFF limit, then runs fx_rec34_spawn_cb on a copy of words 1..4.
   Starts a sound with a callback on the entry when flags' low 2 bits are clear. */
void sfx_emitter_spawn(s32 id, s32 *src, s32 flags) {
    SfxEmitter *rec;
    s32 *rec_words;
    Quad pos;
    s32 handle;

    rec = sfx_emitter_alloc();
    if (rec != NULL) {
        rec_words = (s32 *)rec;
        rec_words[0] = id;
        tick_reset(&rec->tick);
        rec_words[1] = src[0];
        rec_words[2] = src[1];
        rec_words[3] = src[2];
        rec->keyframes = sfx_keyframes;
        rec->active = keyframe_step(&rec->keyframes, &rec->tick, &rec->from, &rec->to, &rec->blend);
        rec->level = 0x1FFF;
        pos = *(Quad *)&rec_words[1];
        fx_rec34_spawn_cb(pos.w, &sfx_emitter_params, (s32)func_800C6088);
        if ((flags & 3) == 0) {
            handle = sound_start(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x50, 0, 0);
            if (handle != 0) {
                sound_attach(handle, rec, (void (*)())sfx_emitter_set_pos);
            }
        }
    }
}

/* Clears the halfword at 0x22 of one sfx_emitters entry (looped by sfx_emitters_clear_all). */
void sfx_emitter_clear(SfxEmitter *entry) {
    entry->active = 0;
}

void sfx_emitters_clear_all(void) {
    SfxEmitter *entry;
    s32 i;

    entry = sfx_emitters;
    i = 0;
    do {
        sfx_emitter_clear(entry);
        i += 1;
        entry += 1;
    } while (i < 0x20);
}

void sfx_emitters_reset(void) {
    sfx_emitters_clear_all();
}

/* One flying step: move along the heading, keep the old position, drift, and roll a new random angle. */
void fly_step(FlyEntry *fly) {
    s32 dx;
    s32 dz;

    fly_move(fly->angle, fly->speed, &dx, &dz);
    /* save the position from unk_14..unk_20 into unk_04..unk_10 */
    *(Quad *)&fly->prev_pos_x = *(Quad *)&fly->pos_x;
    fly->pos_x += dz;
    fly->pos_z += dx;
    fly->pos_y += fly->vel_y;
    fly->vel_y += 0x1000;
    fly->unk_30 = rand_a_next();
}

extern FlyEntry fly_pool[0x20];
void fly_step(FlyEntry *entry);
void sfx_emitters_update(void);
void fly_update(void) {
    FlyEntry *entry = fly_pool;
    s32 i = 0;
    do {
        if (entry->active != 0) {
            fly_step(entry);
        }
        i += 1;
        entry += 1;
    } while (i < 0x20);
    sfx_emitters_update();
}

void sfx_emitter_spawn(s32 id, s32 *src, s32 flags);
void fly_hit_test(FlyEntry *src, s32 *out) {
    s32 *vec;
    s32 scratch[4]; /* unused: the original reserves this stack space (frame 0x38) */

    out[0] = src->pos_x >> 12;
    out[1] = src->pos_y >> 12;
    out[2] = src->pos_z >> 12;
    vec = out + 8;
    out[4] = src->prev_pos_x >> 12;
    out[5] = src->prev_pos_y >> 12;
    out[6] = src->prev_pos_z >> 12;
    if (trace_hit_damage(out, out + 4, vec, 0x20, 1, 0xE) != 0) {
        src->active = 0;
        if (out[9] >= -0x80) {
            sfx_emitter_spawn((s32)src->owner, vec, src->unk_34);
        }
    }
}

void fly_check_hits(void) {
    FlyEntry *entry = fly_pool;
    void *buf = scratch_alloc(0x30);
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (entry->active != 0) {
            fly_hit_test(entry, buf);
        }
        entry++;
    }
    scratch_top -= 0x30;
    sfx_emitters_hit_check();
}

void spark_emitter_update(SparkEmitter *e) {
    s32 base = model_slot_pchr(*e->owner->table) + 0x100;
    s32 x, y, z;
    s32 unused[2];

    if (!is_paused()) {
        e->timer++;
    }
    base += e->timer & 1;
    x = e->x >> 12;
    y = e->y >> 12;
    z = e->z >> 12;
    base = pool_spawn_scaled(base + 2, 0x2000, 0x2000, 0x2000);
    spark_add_head(&spark_list, x, y, z, 0, 0, 0, base, 0);
    req_queue_push_vec(x, y, z);
}

void sfx_emitters_spawn_sparks(void);
/* Same code as fly_update (s07). */
void spark_emitters_update(void) {
    FlyEntry *entry = fly_pool;
    s32 i = 0;
    do {
        if (entry->active != 0) {
            spark_emitter_update((SparkEmitter *)entry);
        }
        i += 1;
        entry += 1;
    } while (i < 0x20);
    sfx_emitters_spawn_sparks();
}

FlyEntry *fly_alloc(void) {
    FlyEntry *rec = fly_pool;
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (rec->active == 0) {
            return rec;
        }
        rec++;
    }
    return NULL;
}

s32 busy_wait(void) {
    s32 count = 0x1F;
    do {
        count--;
    } while (count >= 0);
    return count;
}

/* Spawns a fly entry at pos (whole units, stored as 20.12 fixed point). */
void fly_spawn(void *owner, s32 *pos, s32 angle, s32 speed, s32 unk28, s32 unk34) {
    FlyEntry *entry = fly_alloc();
    s32 z;
    s32 x;

    if (entry != NULL) {
        entry->owner = owner;
        entry->pos_x = pos[0] << 12;
        entry->pos_y = pos[1] << 12;
        x = entry->pos_x;
        z = pos[2];
        entry->vel_y = unk28;
        entry->angle = angle;
        entry->unk_2E = 0;
        entry->unk_34 = unk34;
        entry->prev_pos_x = x + 0x1000;
        do {
            entry->speed = speed >> 12;
        } while (0);
        entry->active = 1;
        entry->pos_z = z << 12;
        entry->prev_pos_y = entry->pos_y + 0x1000;
        entry->prev_pos_z = entry->pos_z + 0x1000;
    }
}

/* Clears the halfword at 0x32 of one fly_pool entry (looped by fly_shutdown). */
void fly_deactivate(FlyEntry *entry) {
    entry->active = 0;
}

void fly_init(void) {
    FlyEntry *entry;
    s32 i;

    entry = fly_pool;
    for (i = 0; i < 0x20; i++) {
        fly_deactivate(entry);
        entry++;
    }
    sfx_emitters_reset();
    D_80125970 = 1;
}

void obj_deactivate_near(PositionedObj *obj, s32 *target, s32 range, s32 max_sq) {
    s32 dx, dy, dz;

    dx = (obj->x >> 12) - target[0];
    dy = (obj->y >> 12) - target[1];
    dz = (obj->z >> 12) - target[2];
    if (range >= ABS(dx)) {
        if (range >= ABS(dy)) {
            if (range >= ABS(dz)) {
                if (length_sq(dx, dy, dz) < max_sq) {
                    obj->active = 0;
                }
            }
        }
    }
}

/* Empty function. The unused volatile array only reproduces the original's
   0x10-byte stack frame (addiu sp,-0x10 / addiu sp,0x10). */
void boss_proximity_stub(void) {
    volatile s32 pad[4];
}

void fly_shutdown(void) {
    FlyEntry *entry;
    s32 i;

    entry = fly_pool;
    i = 0;
    do {
        fly_deactivate(entry);
        i += 1;
        entry += 1;
    } while (i < 0x20);
    sfx_emitters_clear_all();
    D_80125970 = 0;
}

/* Moves a spark along a direction from its yaw/pitch, saving the previous position. */
void spark_step(SparkState *self) {
    s32 dx;
    s32 dy;
    s32 dz;

    angles_to_vector(self->yaw, self->pitch, self->speed, &dx, &dy, &dz);
    self->prev = self->pos;
    self->pos.x += dx;
    self->pos.y += dy;
    self->pos.z += dz;
    self->result = keyframe_step(&self->cursor, &self->tick, &self->from, &self->to, &self->t);
}

extern SparkEntry spark_table[];
void spark_update(void) {
    SparkEntry *entry = spark_table;
    s32 i;

    for (i = 0; i < 0x10; i++, entry++) {
        if (entry->active != 0) {
            spark_step((SparkState *)entry); /* the same records, SparkState's view */
        }
    }
}

/* Convert the actor's segment to integer space. If player_dist_sq reports it
 * within range, call hit_target_masked with the segment's heading (atan2 of the
 * b-minus-a deltas), then clear the actor's unk_3A unless its target kind is
 * 0x108. */
void spark_hit_test(SparkEntry *actor, SegPair *seg) {
    seg->a[0] = actor->a[0] >> 12;
    seg->a[1] = actor->a[1] >> 12;
    seg->a[2] = actor->a[2] >> 12;
    seg->b[0] = actor->b[0] >> 12;
    seg->b[1] = actor->b[1] >> 12;
    seg->b[2] = actor->b[2] >> 12;
    if (player_dist_sq(seg->a) <= 0xFFFF) {
        hit_target_masked(0, 0x10, atan2(seg->b[2] - seg->a[2], seg->b[0] - seg->a[0]), 0x10);
        if (actor->target->kind != 0x108) {
            actor->active = 0;
        }
    }
}

void spark_hit_test_all(void) {
    void *buf = scratch_alloc(0x30);
    SparkEntry *entry = spark_table;
    s32 i;

    for (i = 0; i < 0x10; i++) {
        if (entry->active != 0) {
            spark_hit_test(entry, buf);
        }
        entry++;
    }
    scratch_top -= 0x30;
}

/* Spawns a spark at the entry's start point a: its model blends the owner's models key_from -> key_to by
 * key_t, its colour comes from the target's kind. */
void spark_entry_emit(SparkEntry *entry) {
    s32 slot_a, slot_b;
    s32 x, y;
    s32 z;
    register s32 raw_x asm("$3"); /* the original loads x/y into v1/v0 */
    register s32 raw_y asm("$2");
    s32 shade, bright, colour;
    SparkList *list;
    SparkRec *rec;
    s32 n;
    u8 *tail;

    slot_b = model_slot_pchr(*(s32 *)((Object *)entry->object)->asset);
    slot_a = slot_b + entry->key_from;
    slot_b += entry->key_to;
    shade = ((0x10C - entry->target->kind) << 10) + 0x800;
    shade >>= 5;
    bright = shade;
    if (shade == 0) {
        bright = 1;
    }
    colour = (bright << 16) | (shade << 8) | shade;
    shade = pool_spawn_scaled(pchr_blend(slot_a, slot_b, 0x1000 - entry->key_t, 0), 0x3000, 0x3000, 0x3000);
    list = &spark_list;
    n = SPARK_COUNT;
    raw_x = entry->a[0];
    raw_y = entry->a[1];
    x = raw_x >> 12;
    y = raw_y >> 12;
    z = entry->a[2] >> 12;

    if (n < 0xFF) {
        rec = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)rec->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &rec->next;
        *tail = n;
        rec->next = 0;
        rec->x = x;
        rec->y = y;
        rec->z = z;
        rec->unk_12 = shade;
        rec->yaw = 0;
        rec->pitch = 0;
        rec->roll = 0;
    }
    req_queue_push_vec(x, y, z);
}

/* Same code as spark_update (s07). */
void seg_table_run(void) {
    SparkEntry *entry = spark_table;
    s32 i;

    for (i = 0; i < 0x10; i++, entry++) {
        if (entry->active != 0) {
            spark_entry_emit(entry);
        }
    }
}

/* Returns the first of the 16 records whose unk_3A is 0 (free slot), or NULL. */
SparkEntry *seg_entry_alloc(void) {
    SparkEntry *rec = spark_table;
    s32 i;

    for (i = 0; i < 16; i++, rec++) {
        if (rec->active == 0) {
            return rec;
        }
    }
    return 0;
}

extern Keyframe spark_keyframe_path[7];
void spark_entry_spawn(Object *obj, s32 *pos, s16 yaw, s16 pitch, s32 extra) {
    SegEntryFull *rec = (SegEntryFull *) seg_entry_alloc();

    if (rec != NULL) {
        rec->obj = obj;
        rec->a[0] = pos[0] << 12;
        rec->a[1] = pos[1] << 12;
        rec->a[2] = pos[2] << 12;
        rec->b[0] = rec->a[0] + 0x1000;
        rec->unk_24 = extra;
        rec->yaw = yaw;
        rec->pitch = pitch;
        rec->b[1] = rec->a[1] + 0x1000;
        rec->b[2] = rec->a[2] + 0x1000;
        tick_reset(&rec->tick);
        rec->cursor = spark_keyframe_path;
        rec->active = keyframe_step(&rec->cursor, &rec->tick, &rec->from, &rec->to, &rec->t);
    }
}

/* Clears the halfword at 0x3A of one spark_table entry (looped by spark_table_clear). */
void spark_entry_deactivate(SparkEntry *entry) {
    entry->active = 0;
}

void spark_table_clear(void) {
    SparkEntry *entry;
    s32 i;

    entry = spark_table;
    for (i = 0; i < 0x10; i++) {
        spark_entry_deactivate(entry);
        entry++;
    }
}

void func_800C6F34(void) {
    spark_table_clear();
}

extern s32 ramp_timer_flag;
extern s32 ramp_value;

void ramp_timer_update(void) {
    s32 temp_v0;

    if (ramp_timer_flag != 0) {
        temp_v0 = ramp_value + 0x40;
        ramp_value = temp_v0;
        if (temp_v0 >= 0x1001) {
            ramp_timer_flag = 0;
        }
    }
}

extern Object *ramp_owner;
/* Spawns a spark at a point on part 5 of the object held in ramp_owner, scaled and shaded by the
 * fade value ramp_value. */
void bomb_mech_spark_update(void) {
    Object **owner = &ramp_owner;
    s16 offset[3];
    s32 pos[3];
    s32 shade;
    s32 dark;
    s32 colour;

    if (ramp_timer_flag != 0) {
        s32 value;

        value = model_slot_pchr(*(s32 *)(*owner)->asset);
        value += 0x104;
        offset[0] = 0x1D;
        offset[1] = 9;
        offset[2] = 0xBA;
        model_part_transform((*owner)->vars.words[0], 5, offset);
        obj_point_to_world(*owner, offset, &pos[0], &pos[1], &pos[2]);
        shade = ramp_value >> 5;
        dark = 0;
        if (shade == 0) {
            dark = 1;
            FAKE_OPAQUE(dark);
        }
        colour = (dark << 16) | shade;
        value = pool_spawn_scaled(value, (0x1000 - ramp_value) * 4, (0x1000 - ramp_value) * 4,
                                  (0x1000 - ramp_value) * 4);
        spark_add(pos[0], pos[1], pos[2], 0, 0, 0, value, colour);
    }
}

extern s32 ramp_timer_flag;
extern s32 ramp_value;

/* Starts the ramp timer for `owner` (bomb_mech_spark_update sparks on it). */
void ramp_timer_start(Object *owner) {
    ramp_timer_flag = 1;
    ramp_owner = owner;
    ramp_value = 0;
}

extern s32 ramp_timer_flag;

void ramp_timer_reset(void) {
    ramp_timer_flag = 0;
}

extern s32 ramp_timer_flag;

void ramp_timer_stop(void) {
    ramp_timer_flag = 0;
}

extern s32 ramp_timer_flag;

s32 ramp_timer_is_active(void) {
    return ramp_timer_flag;
}

void keyframe_entry_step(KeyframeEntry *entry) {
    KeyframeInterp *e = (KeyframeInterp *)entry;

    entry->active = keyframe_step(&e->cursor, &e->tick, &e->from, &e->to, &e->t);
    e->unk_30 = rand_a_next();
}

void keyframe_entry_step(KeyframeEntry *entry);
extern KeyframeEntry keyframe_entries[];
void keyframe_table_run(void) {
    KeyframeEntry *entry = keyframe_entries;
    s32 i;

    for (i = 0; i < 0x10; i++, entry++) {
        if (entry->active != 0) {
            keyframe_entry_step(entry);
        }
    }
}

static inline void spark_add_head_a2(s32 val, s32 x, s32 y, s32 z, s32 ry, s32 colour) {
    register s32 value asm("$6") = val;
    SparkList *list = &spark_list;
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
        s->pitch = 0;
        s->roll = 0;
    }
}
void keyframe_entry_emit_spark(KeyframeEntry *entry) {
    KeyframeSpark *rec = (KeyframeSpark *)entry;
    PartPoint box;
    s32 from, to, value;
    s32 colour = 0xFFFFFF;
    s32 kf, kt;

    from = model_slot_pchr(*(s32 *)rec->owner->asset);
    to = from;
    kf = rec->key_from;
    kt = rec->key_to;
    box = rec->box;
    from += kf;
    model_part_transform(rec->owner->vars.snd.unk_248, rec->sel, &box);
    to += kt;
    obj_point_to_world(rec->owner, (s16 *)&box, &rec->pos[0], &rec->pos[1], &rec->pos[2]);
    value = pool_spawn_scaled(pchr_blend(from, to, 0x1000 - rec->key_t, 0), 0x4000, 0x4000, 0x4000);
    spark_add_head_a2(value, rec->pos[0], rec->pos[1], rec->pos[2], rec->yaw, colour);
}

/* Same code as keyframe_table_run (s07). */
void keyframe_entries_update(void) {
    KeyframeEntry *entry = keyframe_entries;
    s32 i;

    for (i = 0; i < 0x10; i++, entry++) {
        if (entry->active != 0) {
            keyframe_entry_emit_spark(entry);
        }
    }
}

/* Returns the first of the 16 entries whose unk_2A is 0, or NULL if all are in use. */
KeyframeEntry *keyframe_entry_alloc(void) {
    KeyframeEntry *entry = keyframe_entries;
    s32 i;

    for (i = 0; i < 0x10; i++, entry++) {
        if (entry->active == 0) {
            return entry;
        }
    }
    return NULL;
}

extern Keyframe keyframe_table_alt[];
extern Keyframe keyframe_table_default[];
void tick_reset(s32 *arg0);
/* Allocates a record and fills it from the 3 u16 values at `vec`.
 * Field offsets not yet in stage.h: 0x00 id, 0x14/0x16/0x18 vec, 0x1C tick,
 * 0x20 table cursor, 0x24/0x26 from/to, 0x28 t, 0x2A result, 0x2E slot.
 */
void keyframe_entry_spawn(s32 id, u16 *vec, s32 slot, s32 use_alt_table) {
    u8 *rec;

    rec = (u8 *)keyframe_entry_alloc();
    if (rec != NULL) {
        *(s32 *)(rec + 0x00) = id;
        *(s16 *)(rec + 0x2E) = slot;
        tick_reset((s32 *)(rec + 0x1C));
        *(u16 *)(rec + 0x14) = vec[0];
        *(u16 *)(rec + 0x16) = vec[1];
        *(u16 *)(rec + 0x18) = vec[2];
        if (use_alt_table != 0) {
            *(Keyframe **)(rec + 0x20) = keyframe_table_alt;
        } else {
            *(Keyframe **)(rec + 0x20) = keyframe_table_default;
        }
        *(s16 *)(rec + 0x2A) = keyframe_step((Keyframe **)(rec + 0x20), (s32 *)(rec + 0x1C),
                                           (u16 *)(rec + 0x24), (u16 *)(rec + 0x26), (s16 *)(rec + 0x28));
    }
}

extern s32 keyframe_spawn_enabled;
extern s32 model_part_slots[];
extern s32 keyframe_spawn_timer;
extern s32 keyframe_spawn_index;
extern s32 keyframe_spawn_owner;
void bomb_mech_m7_boss_spawn_entry(void) {
    u16 vec[3];
    s32 handle;

    if (keyframe_spawn_enabled != 0) {
        keyframe_spawn_timer = keyframe_spawn_timer + rand_a_next() + 0x200;
        if (keyframe_spawn_timer > 0x2000) {
            vec[0] = rand_a_next() / 8 - 0x100;
            vec[1] = rand_a_next() / 16 - 0x80;
            vec[2] = rand_a_next() / 8 - 0x100;
            vec[0] -= 0xB9;
            vec[1] += 0x99;
            vec[2] += 0;
            keyframe_entry_spawn(keyframe_spawn_owner, vec, model_part_slots[keyframe_spawn_index], keyframe_spawn_timer & 1);
            handle = sound_start(SND_ZRRRT | SND_GROUP(2), 0x3C, 0, 0);
            if (handle != 0) {
                sound_attach(handle, (void *)(keyframe_spawn_owner + 0x1F0), NULL);
            }
            keyframe_spawn_index++;
            if (model_part_slots[keyframe_spawn_index] == -1) {
                keyframe_spawn_index = 0;
            }
            keyframe_spawn_timer = 0;
        }
    }
}

void keyframe_entry_reset(Object *obj, s32 next) {
    obj->node.next = (Node *)next;
    obj->script.unk_0E = 0;
}

extern s32 keyframe_spawn_timer;
extern s32 keyframe_spawn_index;
extern s32 keyframe_spawn_owner;
extern s32 keyframe_spawn_enabled;
void keyframe_table_reset(s32 next) {
    KeyframeEntry *entry;
    s32 i;

    entry = keyframe_entries;
    for (i = 0; i < 0x10; i++) {
        keyframe_entry_reset((Object *)entry, next);
        entry++;
    }
    keyframe_spawn_timer = 0;
    keyframe_spawn_index = 0;
    keyframe_spawn_owner = next;
    keyframe_spawn_enabled = 0;
}

/* Clears the halfword at 0x2A of one keyframe_entries entry (looped by keyframe_table_clear). */
void keyframe_entry_clear(KeyframeEntry *entry) {
    entry->active = 0;
}

extern s32 keyframe_spawn_timer;
extern s32 keyframe_spawn_index;
extern s32 keyframe_spawn_enabled;
void keyframe_table_clear(void) {
    KeyframeEntry *entry;
    s32 i;

    entry = &keyframe_entries[0];
    for (i = 0; i < 0x10; i++) {
        keyframe_entry_clear(entry);
        entry++;
    }
    keyframe_spawn_timer = 0;
    keyframe_spawn_index = 0;
    keyframe_spawn_enabled = 0;
}

extern s32 keyframe_spawn_enabled;

void keyframe_table_set_flag(s32 arg0) {
    keyframe_spawn_enabled = arg0;
}

void model_part_update(ModelPart *part) {
    s32 level;
    s16 sum;
    s32 jitter;
    s32 base;

    sum = part->level_ramp[0] += part->level_ramp[1];
    if (sum < 0) {
        part->active = 0;
        return;
    }
    level = sum;
    level = MAX(MIN(level, 0x400), 0);
    part->level_ramp[0] = level;
    jitter = rand_a_next();
    base = level - 0x100;
    level = base + jitter / 8;
    level = MAX(MIN(level, 0x500), 0);
    part->shade = level;
    part->scale += 0x60;
    level = part->scale;
    level = MAX(MIN(level, 0x2000), 0);
    part->scale = level;
}

void model_part_update(ModelPart *part);
extern ModelPart model_part_pool[];
void model_part_run(void) {
    ModelPart *entry = model_part_pool;
    s32 i;

    for (i = 0; i < 4; i++, entry++) {
        if (entry->active != 0) {
            model_part_update(entry);
        }
    }
}

void model_part_draw(ModelPart *rec) {
    PackedBytes8 rot;
    s32 shade = (s16)rec->shade >> 5;
    s32 flag = shade;
    s32 colour;
    s32 model;

    if (shade == 0) {
        flag = 1;
    }
    colour = (flag << 16) | (shade << 8) | shade;
    model = rec->model_offset;
    model += model_slot_pchr(*(s32 *)rec->owner->asset);
    model = pool_spawn_scaled(model, rec->scale, rec->scale, rec->scale);
    rot = rec->rot;
    model_part_transform(rec->owner->vars.words[0], rec->part, &rot);
    obj_point_to_world(rec->owner, (s16 *)&rot, &rec->pos[0], &rec->pos[1], &rec->pos[2]);
    spark_add(rec->pos[0], rec->pos[1], rec->pos[2], 0, 0, 0, model, colour);
}

/* Same code as model_part_run (s07). */
void model_part_draw_run(void) {
    ModelPart *entry = model_part_pool;
    s32 i;

    for (i = 0; i < 4; i++, entry++) {
        if (entry->active != 0) {
            model_part_draw(entry);
        }
    }
}

ModelPart *model_part_alloc(void) {
    ModelPart *entry = model_part_pool;
    s32 i;

    for (i = 0; i < 4; i++, entry++) {
        if (entry->active == 0) {
            return entry;
        }
    }
    return NULL;
}

void model_part_spawn(s32 owner, PackedBytes8 *src, s32 arg2, s32 arg3) {
    ModelPart *entry;
    PackedBytes8 *dst;

    entry = model_part_alloc();
    if (entry != NULL) {
        entry->owner = (Object *)owner;
        dst = &entry->rot;
        *dst = *src;
        entry->active = 1;
        entry->model_offset = arg2;
        entry->part = arg3;
        entry->level_ramp[0] = 0;
        entry->level_ramp[1] = 0x18;
        entry->scale = 0x1000;
    }
}

extern s32 model_part_slots[];
void model_part_spawn_list(s32 owner, s32 arg1) {
    s16 params[3];
    s32 *slot;

    slot = model_part_slots;
    if (*slot != -1) {
        do {
            params[0] = -0xB9;
            params[1] = 0x99;
            params[2] = 0;
            model_part_spawn(owner, (PackedBytes8 *)params, arg1, *slot);
            slot++;
        } while (*slot != -1);
    }
}

void func_800C7C14(Object *obj) {
    *(s16 *)&obj->script = 0;
}

void model_part_clear_active(void) {
    ModelPart *entry = model_part_pool;
    s32 i;

    for (i = 0; i < 4; i++, entry++) {
        if (entry->active != 0) {
            func_800C7C14((Object *)entry);
        }
    }
}

/* Same code as func_800C7C14 (s07). */
void model_part_entry_clear(Object *obj) {
    *(s16 *)&obj->script = 0;
}

void model_part_clear(void) {
    ModelPart *rec;
    s32 i;

    rec = model_part_pool;
    for (i = 0; i < 4; i++) {
        model_part_entry_clear((Object *)rec);
        rec++;
    }
}

void model_part_reset(void) {
    model_part_clear();
}

extern s16 cam_shake_nudges[];
void cam_shake_step(KeyTrackSlot *r) {
    s32 running;
    s32 nudge;
    s16 *view;

    running = keyframe_step(&r->cursor, &r->tick, &r->from, &r->to, &r->t);
    r->active = running;
    if (r->life <= 0) {
        r->active = 0;
    }
    if (r->active != 0) {
        r->size += 0x200;
        r->life = (u16)r->life - 0x40;
        r->unk_2E = rand_a_next();
        r->unk_18 = rand_a_next() + 0xFFF;
        r->unk_1A = rand_a_next() + 0xFFF;
        r->unk_1C = rand_a_next() + 0xFFF;
        if (r->key_index >= 0) {
            nudge = cam_shake_nudges[r->key_index];
            if (nudge < 0) {
                r->key_index = -1;
                nudge = 0;
            }
            view = (s16 *)get_view_nudge();
            set_view_nudge(view[0], view[1] + nudge);
        }
    }
}

extern KeyTrackSlot keytrack_slots[];
void cam_shake_step(KeyTrackSlot *rec);
void cam_shake_run(void) {
    KeyTrackSlot *rec = keytrack_slots;
    s32 i = 0;
    do {
        if (rec->active != 0) {
            cam_shake_step(rec);
        }
        i++;
        rec++;
    } while (i <= 0);
}

extern s32 player_xyz_y;
void shot_hit_test(KeyTrackSlot *rec) {
    s32 a;
    s32 t;
    s32 lo;
    s32 hi;
    s32 d;
    s32 *p;

    if ((player_xyz_y >> 12) < -0x10) {
        rec->key_index = -1;
        return;
    }
    a = rec->size;
    a <<= 12;
    a /= 0x1000;
    t = rec->t;
    t = MAX(MIN(t, 0x1000), 0);
    lo = (0x1000 - t) * 0xC0 + t * 0x480;
    lo /= 0x1000;
    lo *= a;
    lo /= 0x1000;
    hi = a * 0x480;
    hi /= 0x1000;
    d = player_horiz_dist(&rec->pos_x);
    if (lo < d && d < hi) {
        p = player_position();
        hit_target_masked(0, 4, atan2(rec->pos_z - p[2], rec->pos_x - p[0]), 0x18);
    }
}

/* Same code as cam_shake_run (s07). */
void shots_check_hits(void) {
    KeyTrackSlot *rec = keytrack_slots;
    s32 i = 0;
    do {
        if (rec->active != 0) {
            shot_hit_test(rec);
        }
        i++;
        rec++;
    } while (i <= 0);
}


extern SVECTOR fade_target_color;
#define BLEND_TARGET fade_target_color

/* Blends `from` toward the stage's target vector by weight/4096, then scales
 * each component of `v` by the result (in 4096ths). Returns v. */
SVECTOR *color_blend_scale(SVECTOR *v, s32 weight, SVECTOR *from)
{
    s32 inv = 0x1000 - weight;
    s32 x = from->vx * inv + BLEND_TARGET.vx * weight;
    s32 y = from->vy * inv + BLEND_TARGET.vy * weight;
    s32 z = from->vz * inv + BLEND_TARGET.vz * weight;

    x /= 4096;
    y /= 4096;
    z /= 4096;
    x *= v->vx;
    y *= v->vy;
    z *= v->vz;
    x /= 4096;
    y /= 4096;
    z /= 4096;
    v->vx = x;
    v->vy = y;
    v->vz = z;
    return v;
}


void keytrack_slot_emit_spark(KeyTrackSlot *slot) {
    SVECTOR scale;
    s32 base;
    s32 pos_a;
    s32 pos_b;
    s32 t;
    s32 r, g, b;
    s32 colour;
    s32 value;
    s32 size;

    base = model_slot_pchr(*(s32 *)slot->owner->asset);
    pos_a = base;
    pos_b = base;
    pos_a += (s16)slot->from;
    pos_b += (s16)slot->to;
    scale.vx = 0x1000;
    scale.vy = 0x1000;
    scale.vz = 0x1000;
    t = slot->life;
    t = MAX(MIN(t, 0xFFF), 0);
    color_blend_scale(&scale, 0x1000 - t, (SVECTOR *)&slot->unk_18);
    b = scale.vz >> 5;
    g = scale.vy >> 5;
    r = scale.vx >> 5;
    if ((r | g | b) == 0) {
        b = 1;
    }
    colour = (b << 16) | (g << 8) | r;
    value = pchr_blend(pos_a, pos_b, 0x1000 - slot->t, 0);
    size = slot->size;
    size <<= 12;
    size /= 0x1000;
    value = pool_spawn_scaled(value, size, size, size);
    spark_add(slot->pos_x, slot->pos_y, slot->pos_z, slot->unk_2E, 0, 0, value, colour);
    if (slot->key_index >= 0) {
        slot->key_index++;
    }
}

/* Same code as cam_shake_run (s07). */
void keytrack_update_all(void) {
    KeyTrackSlot *rec = keytrack_slots;
    s32 i = 0;
    do {
        if (rec->active != 0) {
            keytrack_slot_emit_spark(rec);
        }
        i++;
        rec++;
    } while (i <= 0);
}

extern Keyframe keyframe_list[];
/* Starts a keyframe track in a record: owner, position (>> 12) and cursor into the
 * keyframe_list keyframe list, first step via keyframe_step, default scale and a -1/0 flag from the player's height. */
void keytrack_start(KeyTrackSlot *rec, Object *obj, s32 *pos) {
    KeyTrack *track = (KeyTrack *)rec;

    track->owner = obj;
    tick_reset(&track->tick);
    track->pos_x = pos[0] >> 12;
    track->pos_y = pos[1] >> 12;
    track->pos_z = pos[2] >> 12;
    track->cursor = keyframe_list;
    track->done = keyframe_step(&track->cursor, &track->tick, &track->from, &track->to, &track->t);
    track->scale = 0x800;
    track->unk_2C = 0x1000;
    if ((player_xyz[1] >> 12) < -0x10) {
        track->unk_28 = -1;
    } else {
        track->unk_28 = 0;
    }
    sound_play(0x50CC, 0x7F, 0xC0, 0x3C);
}

/* Calls keytrack_start for the first record of keytrack_slots whose unk_36 is 0.
   The loop only gets one pass: i is 1 after the first check, so it stops. */
void keytrack_start_free(Object *obj, s32 *pos) {
    KeyTrackSlot *rec;
    s32 i;

    rec = keytrack_slots;
    i = 0;
    do {
        i += 1;
        if (rec->active == 0) {
            keytrack_start(rec, obj, pos);
            return;
        }
        rec += 1;
    } while (i <= 0);
}

void keytrack_reset(KeyTrackSlot *entry) {
    entry->active = 0;
}

void keytrack_reset_all(void) {
    KeyTrackSlot *entry = keytrack_slots;
    s32 i = 0;
    do {
        keytrack_reset(entry);
        i++;
        entry++;
    } while (i <= 0);
}


void keytrack_slot_deactivate(KeyTrackSlot *entry) {
    entry->active = 0;
}


void keytrack_deactivate_first(void) {
    KeyTrackSlot *entry = keytrack_slots;
    s32 i = 0;
    do {
        keytrack_slot_deactivate(entry);
        i++;
        entry++;
    } while (i <= 0);
}

void func_800C8520(void) {
}

void func_800C8528(void) {
}

extern s32 fx_stop_flag;
void fx_record_update(FxRecord *rec) {
    s32 v;
    s32 shade;

    rec->radius_motion[0] -= 0x20000;
    if (rec->radius_motion[0] <= 0 || fx_stop_flag == 1) {
        rec->active = 0;
    }
    v = rec->phase * 3;
    if (v < 0) {
        v += 3;
    }
    v >>= 2;
    shade = v + 0x400;
    shade /= 32;
    rec->color_r = shade;
    rec->color_g = shade;
    rec->color_b = shade;
}

extern FxRecordParams fly_spark_params;
void fx_record_update(FxRecord *rec);
void fly_emit_at(Object *obj) {
    s32 pos[3];

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    fx_rec34_spawn_cb(pos, &fly_spark_params, (s32) fx_record_update);
}

extern s32 fly_active;
extern s32 fly_emit_timer;
extern s32 fx_owner_obj;
extern s32 get_angle_to_player(s32 *pos);
void fly_emit_tick(void) {
    s32 pos[3];
    s32 dx;
    s32 dz;
    s32 angle;
    s32 rnd;
    Object *obj;

    if (fly_active != 1) {
        return;
    }
    fly_emit_timer--;
    if (fly_emit_timer < 0) {
        fly_emit_at((Object *)fx_owner_obj);
        fly_emit_timer = 0xE;
    }
    obj = (Object *)fx_owner_obj;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    angle = get_angle_to_player(pos) + 0x800;
    rnd = rand_a_next();
    if (rnd < 0) {
        rnd += 0xFF;
    }
    fly_move(angle, (rnd >> 8) + 8, &dx, &dz);
    add_displacement(dz, 0, dx);
}

extern s32 fly_active;
extern s32 fly_emit_timer;

void fly_set_active(s32 arg0) {
    fly_active = arg0;
    if (arg0 == 0) {
        fly_emit_timer = 0;
    }
}

extern s32 fly_active;
extern s32 fx_stop_flag;
extern s32 fly_emit_timer;
extern s32 fx_owner_obj;

void fly_setup(s32 arg0) {
    fx_owner_obj = arg0;
    fly_active = 0;
    fx_stop_flag = 0;
    fly_emit_timer = 0;
}

extern s32 fly_active;
extern s32 fx_stop_flag;
extern s32 fly_emit_timer;

void fly_stop(void) {
    fly_active = 0;
    fx_stop_flag = 1;
    fly_emit_timer = 0;
}

void debris_step(DebrisMotion *m) {
    s32 x;
    if (m->z <= 0x31FFFF) {
        m->unk_04 = 0;
    }
    m->x += m->dx;
    m->y += m->vy / 0x1000;
    x = m->x;
    m->z += m->vz;
    m->vz += m->az;
    m->vy += m->ay;
    x = MAX(MIN(x, 0x1FFF), 0);
    m->x = x;
    x = m->y;
    x &= 0xFFF;
    m->y = x;
}

extern Debris debris_table[];
void debris_update_all(void) {
    Debris *entry = debris_table;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            debris_step((DebrisMotion *)entry);
        }
    }
}

void debris_draw(Debris *entry) {
    s32 model;
    s32 s;
    s32 colour;
    s32 hi;
    s32 pos[3];

    model = model_slot_pchr(*((DebrisParams *)entry)->owner->asset) + 0x114;
    s = ((DebrisParams *)entry)->size;

    s >>= 5;
    hi = s;
    if (hi == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (s << 8) | s;
    fly_move(((DebrisParams *)entry)->angle, ((DebrisParams *)entry)->speed / 0x1000, &pos[2], &pos[0]);
    pos[1] = -0x20;
    pos[0] >>= 12;
    pos[2] >>= 12;
    pos[0] += ((DebrisParams *)entry)->owner->x >> 12;
    pos[1] = (((DebrisParams *)entry)->owner->y >> 12) - 0x20;
    pos[2] += ((DebrisParams *)entry)->owner->z >> 12;
    model = pool_spawn_scaled(model, 0x1000, 0x1000, 0x1000);
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, model, colour);
}

/* Same code as debris_update_all (s07). */
void debris_draw_all(void) {
    Debris *entry = debris_table;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        if (entry->active != 0) {
            debris_draw(entry);
        }
    }
}

/* First free entry (unk_04 == 0) in the 0x30-entry table, or NULL if full. */
Debris *debris_find_free(void) {
    Debris *entry;
    s32 i;

    entry = debris_table;
    for (i = 0; i < 0x30; i++) {
        if (entry->active == 0) {
            return entry;
        }
        entry++;
    }
    return NULL;
}

/* Claims the first free entry and fills it in; does nothing if the table is full. */
void debris_spawn(s32 arg0, s32 arg1) {
    DebrisEntry *entry;

    entry = (DebrisEntry *)debris_find_free();
    if (entry != NULL) {
        entry->active = 1;
        entry->unk_0C = 0x55;
        entry->unk_18 = 0x800;
        entry->unk_1C = 0xC00000;
        entry->unk_20 = 0xFFFF0000;
        entry->unk_00 = arg0;
        entry->unk_08 = 0;
        entry->unk_10 = arg1;
        entry->unk_14 = 0;
        entry->unk_24 = -0x2000;
    }
}

void debris_entry_clear(Object *obj) {
    obj->node.prev = NULL;
}

extern s32 debris_active;
extern s32 debris_stopped;
extern s32 debris_spawn_timer;
extern s32 debris_angle;
/* Resets all 0x30 entries of the table, then stores value in fx_owner_obj and clears the 4 state words. */
void debris_init(s32 value) {
    Debris *entry = debris_table;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        debris_entry_clear((Object *)entry);
    }
    fx_owner_obj = value;
    debris_active = 0;
    debris_stopped = 0;
    debris_spawn_timer = 0;
    debris_angle = 0;
}

extern s32 debris_active;
extern s32 debris_spawn_timer;

void debris_set_active(s32 arg0) {
    debris_active = arg0;
    if (arg0 == 0) {
        debris_spawn_timer = 0;
    }
}

extern s32 debris_active;
extern s32 debris_spawn_timer;
extern s32 debris_angle;
extern s32 fx_owner_obj;

void debris_spawn_tick(void) {
    s32 temp_v0;

    if (debris_active == 1) {
        temp_v0 = debris_spawn_timer - 1;
        debris_spawn_timer = temp_v0;
        if (temp_v0 < 0) {
            debris_spawn(fx_owner_obj, debris_angle);
            debris_spawn_timer = 0;
            debris_angle += 0x300;
        }
    }
}

/* Same code as debris_entry_clear (s07). */
void debris_entry_stop(Object *obj) {
    obj->node.prev = NULL;
}

void debris_stop(void) {
    Debris *entry = debris_table;
    s32 i;

    for (i = 0; i < 0x30; i++, entry++) {
        debris_entry_stop((Object *)entry);
    }
    debris_active = 0;
    debris_stopped = 1;
    debris_spawn_timer = 0;
    debris_angle = 0;
}

/* state 0: start a rotated offset from the rest pose and check the new position with cam_point_in_zone;
 * state 1..2: step the keyframe path and clear `active` when it finishes. */
void keymover_update(KeyMover *m) {
    s32 x;
    s32 y;
    s32 z;

    switch (m->state) {
    case 0:
        x = 0;
        y = 0;
        z = 0x38;
        rotate_xz_twice(m->rot_b, m->rot_a, &x, &y, &z);
        x += m->pos_x;
        y += m->pos_y;
        z += m->pos_z;
        if (cam_point_in_zone(0, x, y, z, 0x3A98, 0x1770, 0x1770) == 0) {
            m->active = 0;
        }
        m->pos_x = x;
        m->pos_y = y;
        m->pos_z = z;
        break;
    case 1:
    case 2:
        if (keyframe_step(&m->cursor, &m->tick, &m->from, &m->to, &m->t) == 0) {
            m->active = 0;
        }
        break;
    }
}

extern Shot shot_table[32];
void keymover_update_all(void) {
    Shot *shot;
    s32 i;

    shot = shot_table;
    for (i = 0; i < 0x20; i++, shot++) {
        if (shot->active != 0) {
            keymover_update((KeyMover *)shot);
        }
    }
}
