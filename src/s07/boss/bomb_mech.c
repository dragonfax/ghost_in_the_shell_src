/* bomb_mech: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

/* Script op: reads a halfword from the cursor, advances it, sets vy to the value << 12. */
void script_op_set_vy(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vy = *cursor << 12;
}

/* Reads a code from the object's script cursor (ObjLink unk_04) and, while vy is not negative, replaces
 * the cursor with the entry for that code in the table at data. */
void script_op_jump_if_vy_nonneg(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 code;

    obj->script.pc = cursor + 1;
    code = *cursor;
    if (obj->vy >= 0) {
        obj->script.pc = ((s16 **)obj->script.data)[code];
    }
}



void script_value_queue_push(ValueScript *script) {
    s16 value = *script->pc++;

    value_queue[value_queue_index++] = value;
    value_queue_index = MAX(MIN(value_queue_index, 0xF), 0);
}



void value_queue_pop(RingLookup *obj) {
    s32 raw = value_queue_index - 1;
    s32 idx;
    s32 in_range;

    value_queue_index = raw;
    idx = raw;
    in_range = idx < 16;
    if (!in_range) {
        idx = 15;
    }
    FAKE_OPAQUE(in_range);
    if (in_range == 0) {
        raw = 15;
    }
    if (raw < 0) {
        idx = 0;
    }
    value_queue_index = idx;
    obj->value = obj->table[value_queue[idx]];
}


void fly_spawn(void *owner, s32 *pos, s32 angle, s32 speed, s32 unk28, s32 unk34);
void heli_fire_bombs(Object *obj) {
    s16 src[3];
    s32 pos[2];
    s32 z;
    s32 dist;
    s32 dy;
    s32 yaw;
    s32 speed;
    s32 step1;
    s32 step2;

    src[1] = -0x12C;
    src[0] = 0;
    src[2] = 0;
    obj_point_to_world(obj, src, &pos[0], &pos[1], &z);
    dist = player_horiz_dist(&pos[0]);
    yaw = obj->yaw;
    yaw += obj->vars.heli.part3_yaw;
    dy = pos[1];
    yaw &= 0xFFF;
    dy -= player_position()[1];
    speed = 0x18;
    if (dy < 0) {
        dist = MAX(MIN(dist, 0xAF0), 0x320);
    } else {
        dist = MAX(MIN(dist, 0xAF0), 0xC8);
    }
    step1 = (((speed * speed * dy) << 12) / dist) + (dist << 11);
    step1 = step1 / speed;
    dist = dist / 2;
    step1 = -step1;
    dist = MAX(MIN(dist, 0xAF0), 0x320);
    step2 = (((speed * speed * dy) << 12) / dist) + (dist << 11);
    step2 = -(step2 / speed);
    fly_spawn(obj, &pos[0], yaw, speed << 12, step1, 0);
    fly_spawn(obj, &pos[0], yaw + 0x800, speed << 12, step2, 0);
    sound_play_at_units(SND_HELICOPTER_BOMB_LAUNCH | SND_GROUP(2), 0x64, 0x3C, &pos[0]);
    obj->vars.heli.part3_yaw += 0x200;
}

void fly_spawn(void *owner, s32 *pos, s32 angle, s32 speed, s32 unk28, s32 unk34);
void fly_emitter_update(Object *obj) {
    s16 src[3];
    s32 pos[2];
    s32 z;
    s16 *script;
    s16 kind;
    s32 dist;
    s32 yaw;
    s32 step;
    s32 i;
    s32 scale;
    s32 speed;
    s32 angle;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    kind = *script;
    src[1] = -0x12C;
    src[0] = 0;
    src[2] = 0;
    obj_point_to_world(obj, src, &pos[0], &pos[1], &z);
    dist = player_horiz_dist(&pos[0]);
    yaw = obj->yaw;
    dist = MAX(MIN(dist, 0xAF0), 0x320);
    if (kind == 0) {
        dist = 0x320;
        yaw += 0x200;
    }
    if (kind == 2) {
        dist = 0x708;
    }
    scale = 0x240;
    speed = 0x18;
    step = (((pos[1] * scale) << 12) / dist) + (dist << 11);
    step = step / speed;
    i = 0;
    angle = yaw;
    step = -step;
    for (; i < 8; i++) {
        fly_spawn(obj, &pos[0], angle, speed << 12, step, i);
        angle += 0x200;
    }
    sound_play_at_units(SND_HELICOPTER_BOMB_LAUNCH | SND_GROUP(2), 0x64, 0x3C, &pos[0]);
}

void timer_reverse(void);

void script_timer_reverse(void) {
    timer_reverse();
}

s32 is_timer_done(s32 mode);
void script_jump_table_cond(ScriptJumpTable *self) {
    s16 *cur = self->cursor;
    s32 idx;

    self->cursor = cur + 1;
    idx = *cur;
    if (is_timer_done(1) != 0) {
        self->cursor = (s16 *) self->table[idx];
    }
}

void timer_arm(Object *obj, volatile s32 *pos, void *p);
void marker_add(s32 owner, s32 *vec, u16 *dims);
void obj_point_to_world(Object *obj, s16 *src, s32 *x, s32 *y, s32 *z);
/* Per-frame update: while the object is in its first phase, jitter its
 * screen position around the centre; vars.jitter.timer gates the jitter. */
void obj_jitter_update(Object *obj) {
    u16 pos[3];
    s32 vec[3];
    s16 rot[3];
    s32 offsets[3];
    s32 vx;
    s32 vy;
    s32 vz;
    s32 rnd;
    s32 rnd2;
    s32 base;
    s32 base2;

    if (is_timer_done(0) == 0) {
        offsets[0] = -0x1B;
        offsets[1] = 0x2E;
        offsets[2] = 0x72;
        timer_arm(obj, offsets, (void *) (model_slot_pchr(*(s32 *) obj->asset) + 0x104));
        return;
    }
    rot[0] = -0x1C;
    rot[1] = -0x98;
    rot[2] = 0xB4;
    obj_point_to_world(obj, rot, &vx, &vy, &vz);
    vec[0] = vx;
    vec[1] = vy;
    vec[2] = vz;
    pos[0] = obj->pitch;
    pos[1] = obj->yaw;
    pos[2] = obj->roll;
    rot_turn_toward(vec, (s16 *) pos, 0x140, 0x60);
    if (obj->vars.jitter.timer < 8) {
        rnd = rand_a_next();
        base = pos[0] - 0x10;
        if (rnd < 0) {
            rnd += 0x1F;
        }
        pos[0] = base + (rnd >> 5);
        rnd2 = rand_a_next();
        base2 = pos[1] - 0x40;
        if (rnd2 < 0) {
            rnd2 += 0xF;
        }
        pos[1] = base2 + (rnd2 >> 4);
    } else {
        obj->vars.jitter.timer = 0;
    }
    obj->vars.jitter.timer++;
    marker_add((s32) obj, vec, pos);
    sound_play_at_units(0x30C7, 0x46, 0x36, vec);
}

void spark_entry_spawn(Object *obj, s32 *pos, s16 yaw, s16 pitch, s32 extra);
void obj_point_to_world(Object *obj, s16 *src, s32 *x, s32 *y, s32 *z);
void obj_spawn_muzzle_flash(Object *obj) {
    u16 rot[3];
    s32 base[3];
    s16 offset[3];
    s32 out[3];

    offset[0] = 0x19;
    offset[1] = -0xB0;
    offset[2] = 0xFB;
    obj_point_to_world(obj, offset, &out[0], &out[1], &out[2]);
    base[0] = out[0];
    base[1] = out[1];
    base[2] = out[2];
    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    rot_turn_toward(base, rot, 0x100, 0x40);
    spark_entry_spawn(obj, base, (s16) rot[1], (s16) rot[0], 0x30);
}

void obj_nop(void) {
}

/* Reads an (index, value) pair of u16s from the cursor at unk_1C.unk_04, advances it by 4 bytes,
   and stores the value at vars.enemy.unk_266[index]. */
void script_store_enemy_halfword(Object *obj) {
    s16 *cursor;
    s32 index;
    u16 value;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    obj->script.pc = cursor + 2;
    value = *(u16 *)(cursor + 1);
    (&obj->vars.bomb_mech_m7_boss.unk_266)[index] = value;
}

/* Script op: reads a loop index and a 16-bit count from the script cursor,
 * stores the count in ctx->loop_counts[index]. The rand call's result is unused. */
void script_loop_set_count(ScriptLoopCtx *ctx) {
    u16 *operands;
    s32 index;

    index = *ctx->cursor++;
    rand_a_next();
    operands = (u16 *)ctx->cursor;
    ctx->cursor = (s16 *)(operands + 2);
    ctx->loop_counts[index] = operands[1];
}

void script_loop_next(ScriptLoopCtx *ctx) {
    s32 op;
    u16 count;

    op = *ctx->cursor++;
    count = ctx->loop_counts[op] - 1;
    ctx->loop_counts[op] = count;
    if ((s16)count <= 0) {
        ctx->cursor += 1;
    } else {
        op = *ctx->cursor++;
        ctx->cursor = (s16 *)ctx->table[op];
    }
}

void model_part_spawn_list(s32 unk_a0, s32 unk_a1);
void script_spawn_model_parts(s32 unk_a0) {
    model_part_spawn_list(unk_a0, 0x104);
}

void model_part_clear_active(void);
void script_clear_model_parts(void) {
    model_part_clear_active();
}

void keyframe_table_set_flag(s32 arg0);

void mode_keyframe_enable(void) {
    keyframe_table_set_flag(1);
}


void mode_reset(void) {
    keyframe_table_set_flag(0);
}


void keytrack_start_free(Object *obj, s32 *pos);
void obj_keytrack_start(Object *obj) {
    s32 pos[3];

    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    keytrack_start_free(obj, pos);
}

/*
 * Reads two halfword operands from the object's script cursor (unk_1C.unk_04)
 * and, while the object is alive (health > 0), fires hit_target_masked with an
 * angle from the object's position (in whole units, >> 12) to the player.
 */
void script_shoot_at_player(Object *obj) {
    s32 pos[3];
    s32 *player;
    s16 *cursor;
    s32 type;
    s32 from;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    player = player_position();

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    type = cursor[0];
    obj->script.pc = cursor + 2;
    from = cursor[1];

    if (obj->health > 0) {
        hit_target_masked(0, type & 0xFF, atan2(pos[2] - player[2], pos[0] - player[0]), from);
    }
}

void fly_set_active(s32 arg0);

void debris_set_active(s32 arg0);

void obj_enable(void) {
    fly_set_active(1);
    debris_set_active(1);
}

void obj_disable(void) {
    fly_set_active(0);
    debris_set_active(0);
}

/* Stores a random halfword at 0x262, the upper half of vars.words[6]. */
void obj_roll_set(Object *obj) {
    s16 *half = (s16 *)&obj->vars.bomb_mech_m7_boss.unk_260;

    half[1] = rand_a_next();
}

/* Reads a (threshold, index) halfword pair from the object's script stream and advances it by 4 bytes.
 * If the threshold is at least the random halfword at 0x262 (stored by obj_roll_set), the stream
 * jumps to the entry the index selects in the object's table at unk_1C.data. */
void script_branch_if_roll(Object *obj) {
    s16 *stream = obj->script.pc;
    s32 roll = ((s16 *)&obj->vars.bomb_mech_m7_boss.unk_260)[1];
    s32 threshold;
    s32 index;

    obj->script.pc = stream + 1;
    threshold = stream[0];
    obj->script.pc = stream + 2;
    index = stream[1];
    if (threshold >= roll) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_branch_if_repeat(ScriptRepeatCtx *obj) {
    s32 unused[2];
    s32 id = *obj->pc++;
    s16 saved = id;
    s32 target = *obj->pc++;
    if (obj->last == id) {
        obj->pc = (s16 *)obj->table[target];
    }
    obj->last = saved;
}

void ramp_timer_start(Object *owner);
void obj_start_positional_sound(Object *obj) {
    s32 temp_v0;

    ramp_timer_start(obj);
    temp_v0 = sound_start(0x50D4, 0x7F, 0, 0);
    if (temp_v0 != 0) {
        sound_attach(temp_v0, &obj->x, NULL);
    }
}

s32 ramp_timer_is_active(void);
void obj_ramp_dispatch(Object *obj) {
    s16 *pc;
    s32 op;

    pc = obj->script.pc;
    obj->script.pc = pc + 1;
    op = *pc;
    if (ramp_timer_is_active() == 0) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

/* Passes the object's position to sound_set_pos through a scratch vector. */
s32 obj_sound_follow_a(Object *obj, s32 arg) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    sound_set_pos(arg, pos);
    scratch_top -= 0x10;
    return 0;
}

/* If the object has no sound handle yet (words[3] at 0x254), starts sound 0xB0C5B0C6 at volume 0x7F, stores the handle, sets it on sound_set_flag_bit2 and attaches obj_sound_follow_a to the object as its update. */
void obj_sound_start_a(Object *obj) {
    s32 handle;

    if (obj->vars.bomb_mech_m7_boss.sound_handle_a == 0) {
        handle = sound_start(0xB0C5B0C6, 0x7F, 0, 0);
        obj->vars.bomb_mech_m7_boss.sound_handle_a = handle;
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach(obj->vars.bomb_mech_m7_boss.sound_handle_a, obj, (void (*)())obj_sound_follow_a);
        }
    }
}


void obj_stop_held_sound(Object *obj) {
    if (obj->vars.words[3] != 0) {
        sound_stop(obj->vars.words[3]);
        obj->vars.words[3] = 0;
    }
}


/* Passes the object's position to sound_set_pos through a scratch vector. */
s32 obj_sound_follow_b(Object *obj, s32 arg) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    sound_set_pos(arg, pos);
    scratch_top -= 0x10;
    return 0;
}

/* If the object has no sound handle yet (words[4] at 0x258), starts sound 0xB0D0B0D1 at volume 0x7F, stores the handle, sets it on sound_set_flag_bit2 and attaches obj_sound_follow_b to the object as its update. */
void obj_sound_start_b(Object *obj) {
    s32 handle;

    if (obj->vars.bomb_mech_m7_boss.sound_handle_b == 0) {
        handle = sound_start(0xB0D0B0D1, 0x7F, 0, 0);
        obj->vars.bomb_mech_m7_boss.sound_handle_b = handle;
        if (handle != 0) {
            sound_set_flag_bit2(handle, 1);
            sound_attach(obj->vars.bomb_mech_m7_boss.sound_handle_b, obj, (void (*)())obj_sound_follow_b);
        }
    }
}

/* Stops the sound handle at 0x258 if one is playing. */
void obj_sound_stop_b(Object *obj) {
    if (obj->vars.bomb_mech_m7_boss.sound_handle_b != 0) {
        sound_stop(obj->vars.bomb_mech_m7_boss.sound_handle_b);
        obj->vars.bomb_mech_m7_boss.sound_handle_b = 0;
    }
}

/* Reads one u16 from the cursor at unk_1C.unk_04 into the target yaw and advances the cursor by 2 bytes. */
void script_set_target_yaw(Object *obj) {
    u16 *cursor;

    cursor = (u16 *)obj->script.pc;
    obj->script.pc = (s16 *)(cursor + 1);
    obj->vars.enemy.target_yaw = *cursor;
}

void script_branch_if_flag(Object *obj) {
    s16 *cursor;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->vars.enemy.target_yaw == 1) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Reads the next u16 from the cursor kept in the link at 0x20 into walk_state, then advances it. */
void script_read_walk_state(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = (s16 *)(cursor + 1);
    obj->vars.enemy.walk_state = *cursor;
}

/* Reads one opcode from the object's script cursor (unk_1C.unk_04). If the
   player is more than 0x190 units below the object, the cursor jumps to the
   entry of the type's table (unk_1C.data) selected by the opcode. */
void script_jump_if_player_below(Object *obj) {
    s16 *cursor;
    s32 opcode;
    s32 *player_pos;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    opcode = *cursor;
    player_pos = player_position();
    if (player_pos[1] < ((obj->y >> 12) - 0x190)) {
        obj->script.pc = ((s16 **)obj->script.data)[opcode];
    }
}

void bomb_mech_m7_boss_phase0_systems(void);

void bomb_mech_m7_boss_phase0(void) {
    obj_link_script_run();
    bomb_mech_m7_boss_phase0_systems();
}

void bomb_mech_m7_boss_update_systems(void);
void bomb_mech_m7_boss_update(Object *obj, ObjHandler *handler) {
    s32 dx = 0;
    s32 dz = 0;
    s32 x;
    s32 z;
    s32 outside;
    s32 old_yaw;
    s32 new_yaw;
    s16 angle;

    x = obj->x >> 12;
    outside = x < area_bounds_x0;
    z = obj->z >> 12;
    if (area_bounds_x1 < x) {
        outside = 1;
    }
    if (z < area_bounds_z0) {
        outside = 1;
    }
    if (area_bounds_z1 < z) {
        outside = 1;
    }
    if (outside == 0 && obj->unk_242 == 0) {
        obj_turn_toward_player(obj, obj->vars.bomb_mech_m7_boss.turn_speed);
    } else {
        old_yaw = obj->yaw;
        angle = atan2(area_center_z - (obj->z >> 12), area_center_x - (obj->x >> 12));
        obj->target_yaw = angle;
        obj->yaw = angle_approach(obj->yaw, obj_angle_wobble(obj, angle), obj->vars.bomb_mech_m7_boss.turn_speed);
        obj->unk_242 = -1;
        new_yaw = obj->yaw;
        obj->turn = new_yaw - old_yaw;
    }
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vz = dx;
    obj->vx = dz;
    obj_script_step(obj, handler);
    bomb_mech_m7_boss_update_systems();
}


/* Average of the values whose bit is set in mask (8 values). */
s32 obj_hit_mask_avg(s32 mask, s16 *values) {
    s32 sum;
    s32 count;
    s32 i;

    sum = 0;
    count = 0;
    i = 0;
    do {
        if ((mask >> i) & 1) {
            count++;
            sum += *values;
        }
        i++;
        values++;
    } while (i < 8);
    if (count != 0) {
        sum = sum / count;
    }
    return sum;
}


extern s16 hit_mask_weights[];
void bomb_mech_m7_boss_stop(void);
void obj_set_hit_reaction(Object *obj, s32 flag);
void enemy_take_damage(Object *obj, s16 *rec) {
    s32 power;
    s32 damage;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    power = (s16) obj_hit_damage(obj->index);
    if (obj->hit_cooldown != 0) {
        obj->hit_cooldown += 0xFF;
    }
    if (power > 0) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        damage = power * obj_hit_mask_avg(obj_hit_type(obj->index) & 0xFF, hit_mask_weights);
        power = damage >> 12;
        if (damage < 0) {
            power = (damage + 0xFFF) >> 12;
        }
        obj->health -= power;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    if (obj->health <= 0) {
        rec[9] = 1;
        add_score(obj->score);
        add_kill_count(1);
        obj_set_hit_reaction(obj, 0);
        meter_set_mode(0);
        set_d_801202C8(0);
        bomb_mech_m7_boss_stop();
        return;
    }
    if (test_bit(obj->flags, 5)) {
        obj_block_lerp(obj, 0);
    }
}

/* Calls the object's per-frame callback (unk_170) after two setup calls.
 * unused[] reproduces the original's 0x38-byte stack frame; rec is unused (bomb_mech_m7_boss_phase2 passes it). */
void obj_call_frame_callback(Object *obj, s16 *rec) {
    void (*callback)(Object *);
    s32 unused[5];

    callback = (void (*)(Object *))obj->callback;
    ((void (*)(Object *, s32))obj_stop_held_sound)(obj, 0);
    ((void (*)(Object *, s32))obj_sound_stop_b)(obj, 0);
    if (callback != NULL) {
        callback(obj);
    }
}

void bomb_mech_m7_boss_phase2_systems(void);
void bomb_mech_m7_boss_phase2(Object *obj, s16 *rec) {
    s16 state = rec[9];

    if (state == 0) {
        enemy_take_damage(obj, rec);
    }
    if (rec[9] != 0 && (u8)obj->unk_1B7 != 0) {
        obj_call_frame_callback(obj, rec);
    }
    bomb_mech_m7_boss_phase2_systems();
    meter_set(obj->health, obj->vars.bomb_mech_m7_boss.max_health);
}

extern s32 pchr_pose_table_alt[];
void bomb_mech_m7_boss_frame(void);

void bomb_mech_m7_boss_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR dir;
    s32 value;
    s32 pitch;
    s32 colour;
    s32 *seq;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;

        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    pchr_lists_build(value);
    value = pchr_copy_slot(value);
    seq = pchr_poses_build(value);
    pchr_pose_table_alt[(value & 0x7FF) * 7] = (s32)seq;
    obj->vars.bomb_mech_m7_boss.unk_248 = (s32)seq;
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    spark_add(pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, value, colour);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    dir.vx = obj->width;
    dir.vy = obj->height;
    dir.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &dir, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    bomb_mech_m7_boss_frame();
}

extern void bomb_mech_m7_boss_phase0(void);
extern void bomb_mech_m7_boss_update(Object *obj, ObjHandler *handler);
extern void bomb_mech_m7_boss_phase2(Object *obj, s16 *rec);
extern void bomb_mech_m7_boss_draw(Object *obj, ObjHandler *handler);
extern void boss_proximity_hook(void);
extern void bomb_mech_m7_boss_start(s32 arg0);
extern s16 *bomb_mech_m7_boss_data[];
extern s32 bomb_mech_m7_boss_asset[];
extern ScriptCallEntry D_8011D7F0[];
extern StateEntry D_8011DEA8[];
extern SoundVolume D_8011D554[];
extern s16 *D_8011DD68[];
extern struct Rec8011DEA4 { s16 *value; } D_8011DEA4;
extern void obj_explode_and_free(Object *obj);
/* Spawns the bomb mech boss from a placement. Returns 1 if an object was made. */
s32 bomb_mech_m7_boss_spawn(Placement *place) {
    Object *obj;
    s16 *init_value;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *)&place->unk_00[2] = -1;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) bomb_mech_m7_boss_phase0;
    obj->handlers[1].fn = bomb_mech_m7_boss_update;
    obj->handlers[2].fn = (void (*)(Object *, ObjHandler *)) bomb_mech_m7_boss_phase2;
    obj->handlers[3].fn = bomb_mech_m7_boss_draw;
    obj->callback = (s32) &obj_explode_and_free;
    obj->asset = bomb_mech_m7_boss_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_8011D7F0;
    obj->state_table = D_8011DEA8;
    obj->sounds = D_8011D554;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->unk_1C6 = 0;
    init_value = D_8011DEA4.value;
    obj->script.data = D_8011DD68;
    obj->script.unk_0A = 0;
    obj->script.pc = init_value;
    script_start((Script *) obj, bomb_mech_m7_boss_data[0], (s32) bomb_mech_m7_boss_data);
    obj_init_from_place(obj, place, 0x27);
    obj_set_part_bounds(obj, 1, 0x1000);
    area_set_bounds(-0xA58, 0x9F8, -0x3E78, -0x2498);
    obj->unk_1B7 = 0;
    bomb_mech_m7_boss_start((s32) obj);
    proximity_hook_set((s32) boss_proximity_hook);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, -1);
    obj->vars.bomb_mech_m7_boss.max_health = obj->health;
    obj->vars.bomb_mech_m7_boss.unused_25E = 0;
    *(s16 *)&obj->vars.enemy.unk_260[0] = 0;
    obj->vars.bomb_mech_m7_boss.unk_266 = 0;
    *(s16 *)&obj->vars.bomb_mech_m7_boss.unk_268 = 0;
    obj->vars.bomb_mech_m7_boss.unk_248 = 0;
    *(s16 *)&obj->vars.enemy.unk_260[4] = -1;
    obj->vars.bomb_mech_m7_boss.sound_handle_a = 0;
    obj->vars.bomb_mech_m7_boss.sound_handle_b = 0;
    obj->vars.enemy.target_yaw = 0;
    obj->vars.enemy.walk_state = 0;
    obj->handlers[2].state = 0;
    meter_set(obj->health, obj->vars.bomb_mech_m7_boss.max_health);
    meter_set_mode(1);
    obj_actors_clear_index();
    obj_hit_clear(obj->index);
    obj->score = (s16) place->unk_16;
    grid_active_set(0);
    obj_hit_flag_set(obj->index, 0x80);
    value_queue_index = 0;
    area_load_request(0x3C);
    return 1;
}

void bomb_mech_m7_boss_stop(void);
s32 obj_spawn_replacement(Object *src, s32 arg1);
void obj_explode_and_free(Object *obj) {
    s32 pos[3];
    s32 index;

    meter_set_mode(0);
    set_d_801202C8(0);
    bomb_mech_m7_boss_stop();
    index = obj->type.unk_0E;
    obj_spawn_replacement(obj, index + model_slot_pchr(*(s32 *)obj->asset));
    obj_free(obj);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    sound_play_at_units(0x30C330C4, 0x7F, 0x3C, pos);
}
