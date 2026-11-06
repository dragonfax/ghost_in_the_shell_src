/* boss_systems: one of s01's own original source files (scripts/objmap.py); part of src/s01/main.c's unit, included there. */

extern s32 loop_state_pos_x;
extern s32 loop_state_pos_y;
extern s32 loop_state_pos_z;
extern s16 loop_state_noisy;
extern s16 loop_state_spark_id;
/* Spawns a spark at part 0x15 of loop_state's owner, its shade from the state's noisy level. */
void loop_state_spark_emit(void) {
    s16 part[3];
    s32 x;
    s32 y;
    s32 z;
    Object *owner;
    s32 level;
    s32 shade;
    s32 hi;
    s32 size;
    s32 value;

    if (loop_state_active != 0) {
        owner = loop_state.owner;
        part[0] = loop_state_pos_x;
        part[1] = loop_state_pos_y;
        part[2] = loop_state_pos_z;
        model_part_transform(owner->vars.eshot.model, 0x15, part);
        obj_point_to_world(owner, part, &x, &y, &z);
        level = loop_state_noisy;
        level <<= 5;
        level = NOT_NEGATIVE(level < 0x2000 ? level : 0x1FFF);
        shade = level >> 5;
        hi = shade;
        if (hi == 0) {
            hi = 1;
        }
        /* the original reuses owner's variable for the colour (a second set keeps
           the scheduler from hoisting level's rounding copy above the ors) */
        owner = (Object *)((hi << 16) | (shade << 8) | shade);
        level /= 4;
        size = level * loop_state_scale;
        if (size < 0) {
            size += 0xFFF;
        }
        size >>= 12;
        value = pool_spawn_scaled(loop_state_spark_id, size, size, size);
        spark_add(x, y, z, 0, 0, 0, value, (s32)owner);
        size = (loop_state_scale << 12) / 4096;
        pool_spawn_scaled(loop_state_spark_id, size, size, size);
    }
}

/* Starts the loop_state state for `owner` at `pos` unless it is already active. Only the `owner` store and
 * the call go through `state` (the original keeps the address in a register for those two). */
void loop_state_start(Object *owner, Vec3 *pos, s32 unk_1C) {
    LoopState *state = &loop_state;

    if (loop_state.active != 1) {
        loop_state.step = 1;
        loop_state.level = 0;
        loop_state.active = 1;
        loop_state.pos.x = pos->x;
        loop_state.pos.y = pos->y;
        loop_state.pos.z = pos->z;
        state->owner = owner;
        loop_state.noisy = 0;
        loop_state.unk_1C = unk_1C;
        loop_state.sound = 0;
        loop_state_sound_start(state);
    }
}

void state_stop(void) {
    loop_state.step = -6;
    shot_fire_sound_stop();
}

/* Resets the state record to its idle values and stops its sound. */
void loop_state_stop(void) {
    loop_state.owner = NULL;
    loop_state.level = 0;
    loop_state.step = 0;
    loop_state.scale = 0x1000;
    loop_state.active = 0;
    shot_fire_sound_stop();
}

/* Resets the state record like loop_state_stop, but forgets the sound handle instead of stopping it. */
void loop_state_init(void) {
    loop_state.owner = NULL;
    loop_state.level = 0;
    loop_state.step = 0;
    loop_state.scale = 0x1000;
    loop_state.active = 0;
    loop_state.sound = 0;
}

void cam_get_pos(Vec3 *out) {
    if (views[0].camera >= 0) {
        VECTOR *pos = &cameras[views[0].camera].pos;
        out->x = pos->vx;
        out->y = pos->vy;
        out->z = pos->vz;
    }
}

/* Angle from obj's (x, z) to target, both in 12-bit fixed point (atan2 of the z and x offsets). */
s32 obj_angle_to(Object *obj, VECTOR *target) {
    return atan2(target->vz - (obj->z >> 12), target->vx - (obj->x >> 12));
}

s32 obj_turn_to_cam_done(Object *obj, s32 step) {
    VECTOR cam;
    s32 target;
    s32 yaw;
    s32 diff;

    step = ABS(step);
    cam_get_pos((Vec3 *)&cam);
    target = obj_angle_to(obj, &cam);
    yaw = obj->yaw;
    yaw &= 0xFFF;
    if (yaw >= 0x800) {
        yaw -= 0x1000;
    }
    diff = angle_approach(yaw, target, step) - yaw;
    diff &= 0xFFF;
    if (diff >= 0x800) {
        diff -= 0x1000;
    }
    return ABS(diff) < step;
}


/* Call pchr_set_angle_range with first + base and the count of first..last. */
void pchr_set_angle_span(s32 first, s32 last, s32 unused, s32 base) {
    pchr_set_angle_range(first + base, last - first + 1, unused);
}


extern s32 obj_target_index;

void obj_set_target(s32 arg0) {
    obj_target_index = arg0;
}

/* Runs the entries of obj_target_pchr_table through pchr_set_angle_span, sign-flipped by the result of obj_turn_to_cam_done. */
void obj_target_pchr_update(Object *obj) {
    s16 *entry;
    s32 base;
    s32 span;

    if (obj_target_index >= 0) {
        entry = obj_target_pchr_table;
        span = 0xFA;
        base = model_slot_pchr(*(s32 *) obj->asset);
        if (obj_turn_to_cam_done(obj, obj_target_index) != 0) {
            span = -0xFA;
        }
        while (entry[0] >= 0) {
            pchr_set_angle_span(entry[0], entry[1], span, base);
            entry += 4;
        }
    }
}

void obj_clear_target(void) {
    obj_set_target(-1);
}

/* Moves a playing sound to its emitter's target: position, pitch and volume. */
s32 sound_emitter_update(SoundEmitter *emitter, s32 handle) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = emitter->target->x;
    pos->y = emitter->target->y;
    pos->z = emitter->target->z;
    sound_set_pos(handle, pos);
    sound_set_pitch(handle, emitter->pitch);
    sound_set_volume(handle, (s16)sound_volume_of(0x900B900C, emitter->volume));
    scratch_top -= 0x10;
    return 0;
}

/* Starts the owner's looping sound once, attached to it, at pitch 0xC00. */
void sound_emitter_start(SoundOwner *owner) {
    if (owner->sound == 0) {
        owner->sound = sound_start(SOUND_LOOP_800C3A98, 0x7F, 0, 0);
        if (owner->sound != 0) {
            owner->pitch = 0xC00;
            owner->volume = 0;
            sound_attach(owner->sound, owner, (void (*)())sound_emitter_update);
            sound_set_pitch(owner->sound, owner->pitch);
            sound_set_volume(owner->sound, sound_volume_of(SOUND_LOOP_800C3A98, owner->volume));
        }
    }
}

extern s32 sound_loop_handle;

void sound_stop_global(void) {
    if (sound_loop_handle != 0) {
        sound_stop(sound_loop_handle);
        sound_loop_handle = 0;
    }
}

/* Sound callback: sets the sound's position to the point nearest the listener on the segment, and its volume. */
s32 sound_pair_update0(SoundPair *owner, s32 handle) {
    SegmentWork *w = scratch_alloc(sizeof(SegmentWork));
    s32 volume;

    w->seg = owner->seg;
    sound_closest_point(&w->seg.a, &w->seg.b, &w->near);
    w->near.x <<= 12;
    w->near.y <<= 12;
    w->near.z <<= 12;
    sound_set_pos(handle, &w->near);
    scratch_top -= sizeof(SegmentWork);
    volume = owner->volume;
    volume = MAX(MIN(volume, 0xFFF), 0);
    sound_set_volume(handle, sound_volume_of(SND_PAIR(SND_SCREECH_LOOP | SND_HELD, SND_SCREECH_ALT_LOOP | SND_HELD), volume));
    return 0;
}

/* Sound callback: sets the sound's position to the point nearest the listener on the segment, and its volume. */
s32 sound_pair_update1(SoundPair *owner, s32 handle) {
    SegmentWork *w = scratch_alloc(sizeof(SegmentWork));
    s32 volume;

    w->seg = owner->seg;
    sound_closest_point(&w->seg.a, &w->seg.b, &w->near);
    w->near.x <<= 12;
    w->near.y <<= 12;
    w->near.z <<= 12;
    sound_set_pos(handle, &w->near);
    scratch_top -= sizeof(SegmentWork);
    volume = owner->volume;
    volume = MAX(MIN(volume, 0xFFF), 0);
    sound_set_volume(handle, sound_volume_of(0x900F9005, volume));
    return 0;
}

/* Starts both looping sounds of the owner if they are not playing yet (volume 0 at first). */
void sound_pair_start_loops(SoundPair *owner) {
    s32 handle;

    if (owner->sound[0] == 0) {
        handle = sound_start(SND_PAIR(SND_SCREECH_LOOP | SND_HELD, SND_SCREECH_ALT_LOOP | SND_HELD), 0x7F, 0, 0);
        owner->sound[0] = handle;
        if (handle != 0) {
            sound_attach(handle, owner, (void (*)())sound_pair_update0);
            sound_set_volume(owner->sound[0], 0);
        }
    }
    if (owner->sound[1] == 0) {
        handle = sound_start(0x900F9005, 0x7F, 0, 0);
        owner->sound[1] = handle;
        if (handle != 0) {
            sound_attach(handle, owner, (void (*)())sound_pair_update1);
            sound_set_volume(owner->sound[1], 0);
        }
    }
}

/* Stops both looping sounds of the owner and clears their handles. */
void func_800C3E60(SoundPair *owner) {
    s32 handle;

    handle = owner->sound[0];
    if (handle != 0) {
        sound_stop(handle);
        owner->sound[0] = 0;
    }
    handle = owner->sound[1];
    if (handle != 0) {
        sound_stop(handle);
        owner->sound[1] = 0;
    }
}

s32 move_box_step(MoveIn *in, MoveOut *out, MoveBox *box) {
    s32 big;

    out->ok = 1;
    out->pos = in->pos;
    out->angles = in->angles;
    out->unk_30 = in->unk_2C;
    out->unk_2C = in->unk_40;
    out->unk_00 = in->unk_00;
    box->c = box->b;
    box->a.vx += in->pos.vx;
    box->a.vy += in->pos.vy;
    box->a.vz += in->pos.vz;
    box->b.vx += in->pos.vx;
    box->b.vy += in->pos.vy;
    box->b.vz += in->pos.vz;
    out->prev = in->pos;
    in->pos.vx += box->c.vx * 2;
    in->pos.vy += box->c.vy * 2;
    in->pos.vz += box->c.vz * 2;
    big = in->unk_30 >= 0x1000;
    if (giant_robot_aim_test(&box->a, &box->b, &box->c, 0x30, 8, -big & 0x18) != 0) {
        out->ok = 0;
    }
    return out->ok;
}

extern s32 move_box_hit_state;
void move_box_sweep(MoveIn *in) {
    MoveOut *out;
    MoveScratch *s;
    s32 i;

    s = scratch_alloc(0x50);
    s->rot[0].vx = 0;
    s->rot[0].vy = 0;
    s->rot[0].vz = -0x60;
    rotate_xz_twice(((s16 *)in->angles.b)[1], ((s16 *)in->angles.b)[0], &s->rot[0].vx, &s->rot[0].vy, &s->rot[0].vz);
    s->rot[1].vx = 0;
    s->rot[1].vy = 0;
    s->rot[1].vz = 0x60;
    rotate_xz_twice(((s16 *)in->angles.b)[1], ((s16 *)in->angles.b)[0], &s->rot[1].vx, &s->rot[1].vy, &s->rot[1].vz);

    s->box.a = s->rot[0];
    s->box.b = s->rot[1];
    s->box.b.vx = s->box.b.vx * 0x50;
    s->box.b.vy = s->box.b.vy * 0x50;
    s->box.b.vz = s->box.b.vz * 0x50;
    s->box.a.vx += in->pos.vx;
    s->box.a.vy += in->pos.vy;
    out = (MoveOut *)spark_burst_table;
    s->box.a.vz += in->pos.vz;
    s->box.b.vx += in->pos.vx;
    s->box.b.vy += in->pos.vy;
    s->box.b.vz += in->pos.vz;
    giant_robot_aim_trace(&s->box.a, &s->box.b, 0x30);

    i = 0;
    do {
        s->box.a = s->rot[0];
        s->box.b = s->rot[1];
        if (move_box_step(in, out, &s->box) == 0) {
            *(VECTOR *)in->hit_pos = s->box.c;
            break;
        }
        do {
            i++;
            out++;
        } while (0);
    } while (i < 40);

    if (i != 0) {
        move_box_hit_state = 2;
    }
    if (i == 40) {
        out[-1].ok = 0;
        *(VECTOR *)in->hit_pos = s->box.b;
    }
    scratch_top -= 0x50;
}

void sound_pair_run_copy(void) {
    SoundPair copy;

    copy = sway_state;
    if (copy.call_flag == 1) {
        move_box_sweep((MoveIn *)&copy);
    }
}

s32 spark_burst_emit(SparkBurst *burst) {
    register s32 pchr asm("$7");
    s32 has_second = 0;
    s32 tier;
    register s32 chain asm("$2");
    register s32 radius asm("$5");
    s32 colour;
    s32 spawn;
    s32 size_x3;
    register s32 strength asm("$3");
    register s32 scale asm("$5");
    register s32 size asm("$6");

    pchr = model_slot_pchr(*(s32 *)burst->owner->asset);
    if (burst->mode == 0) {
        pchr += 0xA2;
        has_second = 1;
    } else if (burst->mode == 1) {
        pchr += 0xA0;
    } else {
        pchr += 0xA1;
    }

    tier = burst->size >> 5;
    chain = tier;
    if (tier == 0) {
        chain = 1;
    }
    colour = (chain << 16) | (tier << 8) | tier;
    strength = burst->strength;
    radius = strength << 11;
    chain = radius;
    if (radius < 0) {
        chain = radius + 0xFFF;
    }
    radius = chain >> 12;
    spawn = pool_spawn_scaled(pchr, radius, radius, 0x1000);
    spark_add(burst->pos.x, burst->pos.y, burst->pos.z, burst->rot_y, burst->rot_x, burst->rot_z, spawn, colour);

    if (has_second) {
        pchr = model_slot_pchr(*(s32 *)burst->owner->asset) + 0xB8;
        size = burst->size;
        size_x3 = size * 3;
        tier = (s32)(size_x3 + ((u32)size_x3 >> 31)) >> 6;
        chain = tier;
        if (tier == 0) {
            chain = 1;
        }
        colour = (chain << 16) | (tier << 8) | tier;
        scale = 0xC00;
        FAKE_OPAQUE(scale);
        radius = size * scale;
        chain = radius;
        if (radius < 0) {
            chain = radius + 0xFFF;
        }
        radius = chain >> 12;
        spawn = pool_spawn_scaled(pchr, radius, radius, radius);
        spark_add(burst->pos2.x, burst->pos2.y, burst->pos2.z, 0, 0, 0, spawn, colour);
    }
    return burst->mode;
}

/* Runs spark_burst_emit on each record until one returns 0. */
void rec_list_run(void) {
    SparkBurst *burst = spark_burst_table;
    s32 i;

    for (i = 0; i < 40; i++, burst++) {
        if (spark_burst_emit(burst) == 0) {
            break;
        }
    }
}

void rec_list_update(void) {
    if (sway_flag == 1) {
        rec_list_run();
    }
}

void sound_pair_set_pose(s16 *src, s16 *rot) {
    SoundPair *snd = &sway_state;
    if (sway_flag != 0) {
        obj_point_to_world((Object *)snd->owner, src, &snd->seg.a.x, &snd->seg.a.y, &snd->seg.a.z);
        sway_aim = *(AimPacket *)rot;
    }
}

/* Steps the sway_state effect: eases its level and sway, sets the pitch and plays it, or stops it at the end. */
void sway_update(void) {
    SwayState *st = (SwayState *)&sway_state;
    s16 pos[3];
    s16 rot[3];
    s32 t;
    s32 r;
    u32 bias;

    if (sway_flag != 0) {
        switch (sway_phase) {
        case 0:
            if (sway_level >= 0x2000) {
                sway_rate = -0x100;
                sway_phase = 1;
            }
            break;
        case 1:
            if (sway_level <= 0x1000) {
                sway_level = 0x1000;
                sway_rate = 0;
                sway_phase = 2;
            }
            break;
        case 2:
            break;
        }
        st->level += st->level_step;
        st->sway += st->sway_step;
        if (st->level < 0 || st->sway < 0) {
            st->active = 0;
            func_800C3E60((SoundPair *)st);
            return;
        }
        t = st->level;
        t = NOT_NEGATIVE(t < 0x2001 ? t : 0x2000);
        st->level = t;
        t = st->sway;
        t = NOT_NEGATIVE(t < 0x1001 ? t : 0x1000);
        st->sway = t;
        bias = 0x400;
        t = t - bias + rand_a_next() / 8;
        r = NOT_NEGATIVE(t < 0x2000 ? t : 0x1FFF);
        st->pitch = r;
        pos[0] = 0;
        pos[1] = -0xD1;
        pos[2] = -0x9F;
        t = (rot[0] = 0);
        rot[1] = st->owner->yaw;
        rot[2] = t;
        sound_pair_set_pose(pos, rot);
    }
}

extern s32 sway_flag;

void sway_disable(void) {
    sway_flag = 0;
}

void sway_start(Object *obj, s16 *src, AimPacket *aim) {
    SoundPair *pb = &sway_state;
    pb->owner = (s32) obj;
    obj_point_to_world((Object *) pb->owner, src, &pb->seg.a.x, &pb->seg.a.y, &pb->seg.a.z);
    sway_pos = *(SegVec *) &pb->seg.a;
    *(AimPacket *) &sway_aim = *aim;
    sway_flag = 1;
    sway_rate = 0x200;
    sway_level = 0;
    D_80121AE8 = 0;
    D_80121AF4 = 0xAA;
    sway_phase = 0;
    sound_stop_global();
    D_80121B00 = 0;
    D_80121B04 = 0;
    sound_pair_start_loops(pb);
}

/* Sets three parameters of the sway_rate block to their defaults. */
void sway_reset_params(void) {
    sway_rate = -0x40;
    D_80121AF4 = -0x80;
    sway_phase = 2;
}

/* Clears the flag sway_flag and stops the sounds of the record at sway_state. */
void sway_stop(void) {
    sway_flag = 0;
    func_800C3E60(&sway_state);
}

/* Steps the record's keyframes (keyframe_step) and sets unk_20 to half the key time, offset unless the
 * current key is 0xB0 or 0xB3. */
void rec_keyframe_step(KeyframeSlot *rec) {
    rec->active = keyframe_step(&rec->keys, &rec->tick, &rec->key_from, &rec->key_to, &rec->key_t);
    if ((s16)rec->key_from == 0xB0 || (s16)rec->key_from == 0xB3) {
        rec->unk_20 = (s16)rec->key_t / 2;
    } else {
        rec->unk_20 = (s16)rec->key_t / 2 + 0x800;
    }
}

void keyframe_update_all(void) {
    KeyframeSlot *rec = keyframe_slots;
    s32 i;

    for (i = 0; i < 16; i++, rec++) {
        if (rec->active != 0) {
            rec_keyframe_step(rec);
        }
    }
}

void keyframe_hook_noop(void *slot) {
}

void keyframe_hook_run_all(void) {
    s32 i;
    KeyframeSlot *slot = keyframe_slots;

    for (i = 0; i < 16; i++, slot++) {
        if (slot->active != 0) {
            keyframe_hook_noop(slot);
        }
    }
}

/* Spawns a spark at the slot's start point on its owner: its model blends the owner's models
 * key_from -> key_to by key_t, its colour comes from unk_20. */
void keyframe_slot_emit_spark(KeyframeSlot *rec) {
    Vec3 pos;
    s32 slot_a, slot_b;
    s32 lo, hi;
    s32 colour;
    register s32 model asm("$7");
    register Object *owner asm("$3"); /* the owner and its yaw share v1 */
    register s32 owner_yaw asm("$3");
    SparkList *list;
    s32 n, x, y, z, yaw;
    SparkRec *s;
    u8 *tail;

    obj_point_to_world(rec->owner, (s16 *)rec->start, &pos.x, &pos.y, &pos.z);
    slot_b = model_slot_pchr(*(s32 *)((Object *)rec->owner)->asset);
    slot_a = slot_b + (s16)rec->key_from;
    slot_b += (s16)rec->key_to;
    lo = (s16)rec->unk_20 >> 5;
    hi = (s16)rec->unk_20 >> 4;
    if ((lo | hi) == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (lo << 8) | lo;
    model = pool_spawn_scaled(pchr_blend(slot_a, slot_b, 0x1000 - (s16)rec->key_t, 0), 0x1000, 0x1000, 0x800);
    list = &spark_list;
    n = SPARK_COUNT;
    x = pos.x;
    y = pos.y;
    z = pos.z;
    owner = rec->owner;
    owner_yaw = owner->yaw;
    yaw = owner_yaw + 0x800;
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
        s->yaw = yaw;
        s->pitch = 0;
        s->roll = 0;
    }
}

/* Run keyframe_slot_emit_spark on every active entry. */
void keyframe_run_all(void) {
    KeyframeSlot *rec = keyframe_slots;
    s32 i;

    for (i = 0; i < 16; i++, rec++) {
        if (rec->active != 0) {
            keyframe_slot_emit_spark(rec);
        }
    }
}

KeyframeSlot *keyframe_slot_alloc(void) {
    s32 i;
    KeyframeSlot *slot = keyframe_slots;

    for (i = 0; i < 0x10; i++, slot++) {
        if (slot->active == 0) {
            return slot;
        }
    }
    return NULL;
}

/* Takes a free keyframe record for owner, starting at the three halfwords `start` along `keys`, and steps it once. */
void keyframe_start(void *owner, u16 *start, struct Keyframe *keys) {
    KeyframeSlot *rec = keyframe_slot_alloc();

    if (rec != NULL) {
        tick_reset(&rec->tick);
        rec->owner = owner;
        rec->start[0] = start[0];
        rec->start[1] = start[1];
        rec->start[2] = start[2];
        rec->keys = keys;
        rec->active = keyframe_step(&rec->keys, &rec->tick, &rec->key_from, &rec->key_to, &rec->key_t);
        rec->unk_10 = 0;
    }
}

/* Deactivate all 16 entries of the table at 0x80120FB8 (see keyframe_run_all). */
void keyframe_clear_all(void) {
    KeyframeSlot *rec = keyframe_slots;
    s32 i;

    for (i = 15; i >= 0; i--, rec++) {
        rec->active = 0;
    }
}

void keyframe_reset(void) {
    keyframe_clear_all();
}

extern Keyframe giant_robot_sound_keys_start[3];
extern Keyframe giant_robot_sound_keys_end[5];
void giant_robot_sound_update(void) {
    s16 start[3];
    SoundOwner *owner = &sound_loop;
    s32 sum, last;
    s32 jitter;

    if (sound_loop_level < 0 || sound_loop_intensity < 0) {
        return;
    }
    if (giant_robot_on_flag != 0) {
        start[1] = -0xD1;
        start[2] = -0x9F;
        start[0] = 0;
        if (++giant_robot_tick == 8) {
            keyframe_start((void *)owner->object, (u16 *)start, giant_robot_sound_keys_start);
        }
        if (giant_robot_tick == 0x10) {
            keyframe_start((void *)owner->object, (u16 *)start, giant_robot_sound_keys_end);
            giant_robot_tick = 0;
        }
    }
    sum = owner->unk_04 + owner->unk_08;
    owner->unk_04 = CLAMP_IN_REG(sum, 0, 0xC00, "$2");
    jitter = rand_a_next();
    sum = owner->unk_04 - 0x80;
    sum += jitter / 16;
    owner->unk_0C = CLAMP_IN_REG(sum, 0, 0xC00, "$4");
    sum = owner->unk_10 + owner->unk_14;
    owner->unk_10 = CLAMP_IN_REG(sum, 0, 0x800, "$2");
    owner->pitch += 0x24;
    last = owner->volume + 0x80;
    owner->volume = CLAMP_IN_REG(last, 0, 0x1000, "$4");
    FAKE_USE(last);
}

extern s32 giant_robot_level;
/* Emits a spark at a point on sound_loop's object, scaled by sound_loop_intensity * giant_robot_level and shaded by giant_robot_level. */
void giant_robot_spark_draw(void) {
    Vec3 pos;
    SoundOwner *owner = &sound_loop;
    s32 shade;
    s32 hi;
    s32 scale;
    s32 value;
    s32 colour;

    if (sound_loop_level > 0 && sound_loop_intensity > 0) {
        s16 offset[3];

        offset[1] = -0xD1;
        offset[2] = -0x9F;
        offset[0] = 0;
        obj_point_to_world((Object *)owner->object, offset, &pos.x, &pos.y, &pos.z);
        value = model_slot_pchr(*(s32 *)((Object *)owner->object)->asset) + 0xB8;
        shade = giant_robot_level >> 5;
        hi = shade;
        if (shade == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (shade << 8) | shade;
        scale = sound_loop_intensity * giant_robot_level;
        scale /= 0x1000;
        value = pool_spawn_scaled(value, scale, scale, scale);
        spark_add(pos.x, pos.y, pos.z, 0, 0, 0, value, colour);
    }
}

/* Sets the defaults of the words at sound_loop + 0x04..0x24 (the record sound_emitter_start takes), then calls
 * sound_emitter_start on it. */
void sound_loop_start(void) {
    sound_loop_slot_a = 0x1F;
    sound_loop_slot_b = 0x15;
    sound_loop_level = 0;
    sound_loop_intensity = 0;
    sound_loop_pitch = 0xC00;
    sound_loop_volume = 0;
    sound_emitter_start(&sound_loop);
}

/* Marks two slots unset, then stops the sound held in sound_loop_handle. */
void sound_loop_stop(void) {
    sound_loop_slot_a = SLOT_UNSET;
    sound_loop_slot_b = SLOT_UNSET;
    sound_stop_global();
}

/* Stores `value` in sound_loop and clears the state words that follow it. */
void sound_loop_reset(s32 value) {
    sound_loop.object = value;
    sound_loop_slot_a = 0;
    sound_loop_level = 0;
    sound_loop_intensity = 0;
    sound_loop_slot_b = 0;
    giant_robot_tick = 0;
    sound_loop_handle = 0;
    giant_robot_on_flag = 0;
}

/* Clears four state words, then stops the sound held in sound_loop_handle. */
void sound_loop_clear(void) {
    sound_loop_slot_a = 0;
    sound_loop_level = 0;
    sound_loop_intensity = 0;
    sound_loop_slot_b = 0;
    sound_stop_global();
}


/* Sets the flag at giant_robot_on_flag. */
void flag_set(void) {
    giant_robot_on_flag = 1;
}


extern s32 giant_robot_on_flag;

void flag_clear(void) {
    giant_robot_on_flag = 0;
}

/* Steps the record's keyframes (keyframe_step) and moves unk_24 up or down by 0x100 by the current key. */
void keyframe_ramp_step(KeyframeRamp *rec) {
    rec->active = keyframe_step(&rec->keys, &rec->tick, &rec->key_from, &rec->key_to, &rec->key_t);
    if ((s16)rec->key_from == 0xA3) {
        rec->unk_24 += 0x100;
    } else {
        rec->unk_24 -= 0x100;
    }
}

/* Runs keyframe_ramp_step on each active record. */
void keyframe_ramp_update_all(void) {
    KeyframeRamp *rec = keyframe_ramp_recs;
    s32 i = 0;

    do {
        if (rec->active != 0) {
            keyframe_ramp_step(rec);
        }
        i++;
        rec++;
    } while (i < 4);
}

/* keyframe_slot_emit_spark for a ramp: colour from unk_24, spark value 0x1000. */
void keyframe_ramp_emit_spark(KeyframeRamp *rec) {
    Vec3 pos;
    s32 slot_a, slot_b;
    s32 lo, hi;
    s32 colour;
    register s32 model asm("$7");
    register Object *owner asm("$3"); /* the owner and its yaw share v1 */
    register s32 owner_yaw asm("$3");
    SparkList *list;
    s32 n, x, y, z, yaw;
    SparkRec *s;
    u8 *tail;

    obj_point_to_world(rec->owner, (s16 *)rec->start, &pos.x, &pos.y, &pos.z);
    slot_b = model_slot_pchr(*(s32 *)((Object *)rec->owner)->asset);
    slot_a = slot_b + (s16)rec->key_from;
    slot_b += (s16)rec->key_to;
    lo = (s16)rec->unk_24 >> 5;
    hi = lo;
    if (lo == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (lo << 8) | lo;
    model = pool_spawn_scaled(pchr_blend(slot_a, slot_b, 0x1000 - (s16)rec->key_t, 0), 0x1000, 0x1000, 0x1000);
    list = &spark_list;
    n = SPARK_COUNT;
    x = pos.x;
    y = pos.y;
    z = pos.z;
    owner = rec->owner;
    owner_yaw = owner->yaw;
    yaw = owner_yaw + 0x800;
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
        s->yaw = yaw;
        s->pitch = 0;
        s->roll = 0;
    }
}

/* Updates the 4 active entries of keyframe_ramp_recs. */
void keyframe_ramp_run_all(void) {
    KeyframeRamp *entry;
    s32 i;

    entry = keyframe_ramp_recs;
    i = 0;
    do {
        if (entry->active != 0) {
            keyframe_ramp_emit_spark(entry);
        }
        i++;
        entry++;
    } while (i < 4);
}

KeyframeRamp *keyframe_ramp_alloc(void) {
    s32 i;
    KeyframeRamp *slot = keyframe_ramp_recs;

    for (i = 0; i < 4; i++, slot++) {
        if (slot->active == 0) {
            return slot;
        }
    }
    return NULL;
}

/* Wrapper: calls keyframe_ramp_alloc. */
void keyframe_ramp_alloc_wrapper(void) {
    s32 unused[2];
    keyframe_ramp_alloc();
}

void keyframe_ramp_clear_all(void) {
    KeyframeRamp *rec = keyframe_ramp_recs;
    s32 i = 3;

    do {
        rec->active = 0;
        i--;
        rec++;
    } while (i >= 0);
}

void keyframe_ramp_reset(void) {
    keyframe_ramp_clear_all();
}
