/* tunnel_mech: one of s02's own original source files (scripts/objmap.py); part of src/s02/main.c's unit, included there. */

void fx_shoot_at_player(void *origin, s32 len) {
    s32 *from = origin;
    VECTOR *aim_pos = scratch_alloc(0x10);
    s32 dx = 0, dy = 0, dz = 0;
    s32 pitch = 0, yaw = 0;
    s16 target = 0;

    player_position_copy(aim_pos);
    dx = aim_pos->vx - from[0];
    dy = aim_pos->vy - from[1];
    dz = aim_pos->vz - from[2];
    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    angles_to_vector(yaw, -pitch, len, &dx, &dy, &dz);
    aim_pos->vx = from[0] + (dx >> 12);
    aim_pos->vy = from[1] + (dy >> 12);
    aim_pos->vz = from[2] + (dz >> 12);
    set_collide_mode(1);
    if (trace_objects(origin, aim_pos, 8, aim_pos, &target) == 1) {
        hit_target_masked(target, 4, (s16)yaw, 10);
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
}


/* Runs func_800B7B44 with the word at 0x18 (12 fraction bits dropped) while the halfword at 0x28 is below 0x999. */
void burst_fx_update(Object *obj) {
    if (obj->script.unk_0C < 0x999) {
        fx_shoot_at_player(obj, *(s32 *)&obj->type.unk_0C >> 12);
    }
}

/* Draw handler: two sparks at the object, faded by vars.h.unk_24E. The first uses model unk_24A
 * scaled by 0x2000 - fade; the second uses model unk_24C, larger and brighter on the step where
 * unk_248 == unk_24C - 0x10. */
void burst_shot_draw(Object *obj) {
    s32 second_model;
    Object *self = obj; /* a second copy: the original keeps it in its own register */
    s32 pos[3];
    s16 rot[3];
    s32 model, size, level, hi, colour, pitch;
    s32 full, dim;

    dim = 0xC00;
    model = obj->vars.burst_shot.model;
    second_model = obj->vars.burst_shot.second_model;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    size = 0x2000 - obj->vars.burst_shot.unk_24E;
    model = pool_spawn_scaled(model, size, size, size);
    full = 0x1000;
    level = full - obj->vars.burst_shot.unk_24E;
    level >>= 5;
    hi = level;
    if (hi == 0) {
        hi = 1;
    }
    colour = (hi << 16) | (level << 8) | level;
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], model, colour);
    if (obj->vars.burst_shot.unk_248 == obj->vars.burst_shot.second_model - 0x10) {
        level = full - obj->vars.burst_shot.unk_24E;
        level >>= 5;
        hi = level;
        if (hi == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (level << 8) | level;
        second_model = pool_spawn_scaled(second_model, 0x999, 0x999, 0x999);
    } else {
        level = dim - self->vars.burst_shot.unk_24E;
        level >>= 5;
        hi = level;
        if (hi == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (level << 8) | level;
        second_model = pool_spawn_scaled(second_model, 0x999, 0xC00, 0x1000);
    }
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], second_model, colour);
}

void burst_shot_update(Object *obj) {
    s32 from[4];
    s32 hit[4];
    s32 to[4];
    s32 unused_stack[4]; /* keeps the frame layout; the original has this space */
    s16 target;
    s32 angle;
    s32 offset;

    if (is_stage_ending(obj) == 0) {
        obj->vars.burst_shot.toggle ^= 1;
        if (obj->vars.burst_shot.toggle == 0) {
            obj->vars.burst_shot.model = obj->vars.burst_shot.unk_248 + (rand_a_next() % 5);
            offset = (rand_a_next() % 2) + 0x10;
            obj->vars.burst_shot.second_model = obj->vars.burst_shot.unk_248 + offset;
        }
        from[0] = obj->x >> 12;
        from[1] = obj->y >> 12;
        from[2] = obj->z >> 12;
        hit[0] = (obj->x + obj->vx) >> 12;
        hit[1] = (obj->y + obj->vy) >> 12;
        hit[2] = (obj->z + obj->vz) >> 12;
        set_collide_mode(1);
        if (trace_objects(from, hit, 0x10, to, &target) != 0) {
            angle = atan2(to[2] - from[2], to[0] - from[0]);
            hit_target_masked(target, 1, angle, 0xA);
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
        if (obj->vars.burst_shot.unk_24E >= 0x1001) {
            obj_free(obj);
        }
    } else {
        obj_free(obj);
    }
    obj->vars.burst_shot.unk_24E += 0x20;
}

extern void burst_shot_update();
void burst_shot_draw(Object *obj);
s32 burst_shot_spawn(s32 *pos, s16 yaw, s32 arg) {
    Object *obj;
    s32 ret;
    s32 z;
    s32 spd;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_before((Node *)get_obj_list_actors_tail(), &obj->node);
        obj_set_flags(obj, 0x80);
        obj_hit_clear(obj->index);
        obj_hit_flag_set(obj->index, 0);
        obj->handlers[1].fn = burst_shot_update;
        obj->handlers[3].fn = burst_shot_draw;
        obj->speed = 0x28;
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->damage = 0xA;
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        spd = obj->speed;
        z = pos[2] << 12;
        obj->yaw = yaw;
        obj->pitch = 0;
        obj->roll = 0;
        obj->vars.burst_shot.unk_248 = arg;
        obj->vars.burst_shot.model = arg;
        obj->vars.burst_shot.second_model = arg;
        obj->vars.burst_shot.unk_24E = 0;
        obj->vars.burst_shot.toggle = 0;
        obj->vars.burst_shot.unused_252 = 0;
        obj->z = z;
        angles_to_vector(obj->yaw, obj->pitch, spd, &obj->vx, &obj->vy, &obj->vz);
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 is_stage_ending(Object *obj);
void countdown_update(Object *obj) {
    u16 counter;
    /* written but never read: volatile keeps the stores in the original */
    volatile s32 pos[3];

    if (is_stage_ending(obj) == 0) {
        counter = obj->vars.timed_burst.countdown;
        obj->vars.timed_burst.countdown = counter - 1;
        if ((s16)counter >= 0) {
            return;
        }
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
    }
    obj_free(obj);
}

extern RecTemplate burst_fx_template;
extern RecTemplate D_80116FE8;
/* Spawns an object at the position pos (world units, 12 fraction bits added on store) facing yaw.
   tag goes to vars.h.unk_24A. Unless skip_probes is set, it runs burst_shot_spawn facing yaw and the opposite yaw.
   Returns 0 when no object slot is free. */
s32 spawn_timed_burst(s32 *pos, s16 yaw, s32 tag, s32 skip_probes) {
    Object *obj;
    s32 opposite_yaw;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *)get_obj_list_actors_tail(), &obj->node);
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = countdown_update;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = NULL;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->yaw = yaw;
    obj->pitch = 0;
    obj->roll = 0;
    obj->vars.timed_burst.countdown = 0xE;
    obj->vars.timed_burst.tag = tag;
    fx_spawn_template(pos, &burst_fx_template, burst_fx_update);
    fx_spawn_template(pos, &D_80116FE8, NULL);
    if (skip_probes == 0) {
        burst_shot_spawn(pos, obj->yaw, tag);
        opposite_yaw = obj->yaw;
        burst_shot_spawn(pos, (s16)(opposite_yaw + 0x800), tag);
    }
    return 1;
}

void spark_emitter_sparks_draw(Object *obj) {
    s32 base = obj->vars.snd.sound + 0x190;
    s32 value = get_model_slot_base() + 0xE;
    Vec3 pos;
    struct { s16 x; u16 y, z; } rot;
    s32 pitch;
    s32 yaw, roll;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.x = -pitch;
    yaw = (u16)obj->yaw;
    rot.y = yaw;
    roll = (u16)obj->roll;
    rot.z = roll;
    spark_add(pos.x, pos.y, pos.z, yaw, -rot.x, roll, base, 0);
    spark_add(pos.x, pos.y, pos.z, 0, 0, 0, value, 0);
}

void spark_emitter_trace_update(Object *obj) {
    s32 from[3];
    s32 to[3];
    s32 hit[8];
    s32 origin[3];
    s32 angles[2];
    s16 target;
    s32 *player;
    s32 tag;
    s32 base;
    s32 sound;
    s32 back_yaw;
    s16 pitch;
    s32 yaw;
    s32 speed;

    player = player_position();
    base = obj->vars.snd.sound;
    origin[0] = obj->x >> 12;
    origin[1] = obj->y >> 12;
    tag = base + 0x195;
    origin[2] = obj->z >> 12;
    if (is_stage_ending((Object *)base) != 0 ||
        (vector_to_angles(0, 0x15E, player[2] - origin[2], &angles[0], &angles[1]),
         pitch = angle_approach(obj->pitch, -angles[1], 8),
         yaw = obj->yaw, speed = obj->speed, obj->pitch = pitch,
         angles_to_vector(yaw, pitch, speed, &obj->vx, &obj->vy, &obj->vz),
         from[0] = obj->x >> 12,
         from[1] = obj->y >> 12,
         from[2] = obj->z >> 12,
         to[0] = (obj->x + obj->vx) >> 12,
         to[1] = (obj->y + obj->vy) >> 12,
         to[2] = (obj->z + obj->vz) >> 12,
         ((obj_hit_damage(obj->index) << 16) > 0))) {
        spawn_effect(origin[0], origin[1], origin[2], 0x80000000);
        obj->vars.spark_emitter.unused_248 = 1;
    } else if (trace_world(8, 0x10, from, to, hit) != 0) {
        sound_play_at_units(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x60, 0x3C, hit);
        sound_play_at_units(0x30323033, 0x60, 0x3C, hit);
        spawn_timed_burst(hit, obj->yaw, tag, 0);
        back_yaw = obj->yaw;
        spawn_timed_burst(hit, back_yaw + 0x800, tag, 0);
        obj->vars.spark_emitter.unused_248 = 1;
    } else {
        set_collide_mode(1);
        if (trace_objects(from, to, 0x10, hit, &target) != 0) {
            hit_target_masked(target, 1, atan2(hit[2] - from[2], hit[0] - from[0]), 0xA);
            sound_play_at_units(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x60, 0x3C, hit);
            fx_spawn_template(hit, &burst_fx_template, burst_fx_update);
            fx_spawn_template(hit, &D_80116FE8, NULL);
            obj->vars.spark_emitter.unused_248 = 1;
        }
        set_collide_mode(0);
        obj->z += obj->vz;
        obj->x += obj->vx;
        obj->y += obj->vy;
        if (obj->vars.spark_emitter.timer-- > 0) {
            obj->vars.spark_emitter.toggle ^= 1;
            if (obj->vars.spark_emitter.toggle == 0) {
                sound = obj->vars.snd.sound;
                from[0] = obj->x >> 12;
                from[1] = obj->y >> 12;
                from[2] = obj->z >> 12;
                effect_spawn_at((Vec3 *)from, sound + 0x191, 3, 0x10);
            }
        }
    }
    if (obj->vars.spark_emitter.unused_248 != 0) {
        obj_free(obj);
    }
    if (obj->speed < 0x32) {
        obj->speed++;
    }
}

void spark_emitter_trace_update(Object *obj);
s32 spark_emitter_spawn(Object *parent, s32 *pos) {
    Object *obj;
    s32 frame_pad[4]; /* unused; the original's stack frame is 16 bytes larger */

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_before((Node *) get_obj_list_actors_tail(), &obj->node);
    obj_set_flags(obj, 0x80);
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->handlers[1].fn = spark_emitter_trace_update;
    obj->handlers[3].fn = spark_emitter_sparks_draw;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = NULL;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->speed = 0;
    obj->damage = 0xA;
    obj->x = pos[0] << 0xC;
    obj->y = pos[1] << 0xC;
    obj->z = pos[2] << 0xC;
    obj->yaw = 0;
    obj->pitch = 0;
    obj->roll = 0;
    obj->vars.spark_emitter.unused_248 = 0;
    obj->vars.spark_emitter.model_slot = model_slot_pchr(*(s32 *) parent->asset);
    obj->vars.spark_emitter.timer = 0x14;
    obj->vars.spark_emitter.toggle = 0;
    return 1;
}


void script_read_speed(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->speed = *cursor;
}


/* Script op: always reads the next u16 from the script stream; the first
 * time vars.h.unk_248 is 0, it becomes next_state and the flag is set. */
void script_op_set_next_state(Object *obj) {
    u16 value = obj_read_u16(obj);

    if (obj->vars.tunnel_mech_m2_boss.unk_248 == 0) {
        obj->next_state = value;
        obj->vars.tunnel_mech_m2_boss.unk_248 = 1;
    }
}

/* Same code as func_800BC7C8 (s01). */
void script_read_u16_field(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Distance from pos to obj's position, in 4096ths, after the 0x2D0000 y offset. */
s32 obj_distance(Vec3 *pos, Object *obj) {
    s32 dx, dy, dz, pos_y;

    /* Assignments are split so GCC keeps the object loads in source order. */
    dx = obj->x;
    dx = (pos->x - dx) >> 12;
    pos_y = pos->y + 0x2D0000;
    dy = obj->y;
    dy = (pos_y - dy) >> 12;
    dz = (pos->z - obj->z) >> 12;

    return SquareRoot0(length_sq(dx, dy, dz));
}

void script_branch_if_within(Object *obj) {
    s16 *cursor;
    s16 limit;
    s32 key;
    s32 index;

    limit = obj_distance(&VEC_80139584, obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    key = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (key >= limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script branch: reads two halfwords after the counter. When the first one
 * is below the object's distance to the camera, the counter jumps to the
 * per-type table entry given by the second. */
void script_branch_if_far(Object *obj) {
    s16 *script;
    s16 dist;
    s32 threshold;
    s32 table_index;

    dist = obj_distance(&VEC_80139584, obj);
    script = obj->script.pc;
    obj->script.pc = script + 1;
    threshold = script[0];
    obj->script.pc = script + 2;
    table_index = script[1];
    if (threshold < dist) {
        obj->script.pc = ((s16 **)obj->script.data)[table_index];
    }
}

/* Advances the object's script read pointer by one halfword. The opcode
 * is then used as an index into the per-type table, but only while the
 * object's z position (scaled >> 12) is at or above -0xF9F. */
void script_jump_if_above_z(Object *obj) {
    s16 *script;
    s32 opcode;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    opcode = script[0];
    if ((obj->z >> 12) >= -0xF9F) {
        obj->script.pc = ((s16 **)obj->script.data)[opcode];
    }
}

/*
 * Script opcode fetch. The script counter lives in obj->unk_1C.unk_04 and
 * advances 2 bytes per opcode. When obj->z >> 12 is below -0x1F40, the
 * opcode is a jump: the counter is reloaded from the per-type table
 * (obj->unk_1C.data) at index opcode.
 */
void script_jump_if_below_z(Object *obj) {
    s16 *pc;
    s32 op;

    pc = obj->script.pc;
    obj->script.pc = pc + 1;
    op = *pc;
    if ((obj->z >> 12) < -0x1F40) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

void tunnel_mech_m2_boss_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void obj_state_step(Object *obj) {
    s16 next_state;
    s16 counter;

    next_state = obj->next_state;
    if (next_state != obj->vars.tunnel_mech_m2_boss.prev_state) {
        if (next_state != 4) {
            obj->vars.tunnel_mech_m2_boss.angle += 0xAA;
        } else {
            obj->vars.tunnel_mech_m2_boss.angle += 0x200;
        }
        if ((s16) obj->vars.tunnel_mech_m2_boss.angle >= 0x1001) {
            obj->vars.tunnel_mech_m2_boss.angle = obj->vars.tunnel_mech_m2_boss.angle & 0xFFF;
            obj->vars.tunnel_mech_m2_boss.prev_state = obj->next_state;
        }
    } else {
        obj->vars.tunnel_mech_m2_boss.angle = 0;
        obj->vars.tunnel_mech_m2_boss.unk_248 = 0;
    }
    counter = obj->vars.tunnel_mech_m2_boss.path_blend + 0x333;
    obj->vars.tunnel_mech_m2_boss.path_blend = counter;
    if (counter >= 0x1001) {
        obj->vars.tunnel_mech_m2_boss.path_blend = counter & 0xFFF;
        obj->vars.tunnel_mech_m2_boss.path_index = (obj->vars.tunnel_mech_m2_boss.path_index + 1) % obj->vars.tunnel_mech_m2_boss.path_count;
    }
}

extern s16 tunnel_mech_sound_on;
extern s32 tunnel_mech_sound_handle;
extern s16 tunnel_mech_sound2_on;
extern s32 tunnel_mech_sound2_handle;
extern s16 tunnel_mech_sweep_timer;
void tunnel_mech_fire_side(Object *obj, s16 *angles, s16 flag);
/* Aims the object's pitch (0x262) at the player and sweeps it. Keeps a looping sound
 * handle (tunnel_mech_sound_on/28) and a sweep angle (tunnel_mech_sweep_timer, 0x1000 per turn) that wraps.
 * The halfword timer at 0x264 counts down; when it runs out it re-arms to 0x78. */
void tunnel_mech_aim_update(Object *obj) {
    s32 *player;
    s32 y;
    s32 dx;
    s32 dy;
    s32 dz;
    s16 *sweep;
    s16 *sweep_wrap;
    s32 pitch;
    s32 aim_pos[3];
    s16 steer[3];
    s32 aim_angles[2];
    u16 timer;

    player = player_position();
    aim_pos[0] = obj->x >> 12;
    y = obj->y >> 12;
    aim_pos[1] = y;
    aim_pos[2] = obj->z >> 12;
    aim_pos[1] = y - 0x2D0;
    steer[0] = 0;
    steer[1] = 0;
    steer[2] = 0;
    if (tunnel_mech_sound2_on == 1) {
        sound_stop(tunnel_mech_sound2_handle);
        tunnel_mech_sound2_handle = 0;
        tunnel_mech_sound2_on = 0;
    }
    timer = *(u16 *)&obj->vars.enemy.unk_260[4];
    if ((u32)(timer - 1) < 0x77U) {
        if (tunnel_mech_sound_on == 0) {
            tunnel_mech_sound_handle = sound_start(SND_MEDIUM_GUNFIRE | SND_HELD | SND_GROUP(1), 0x40, 0, 0);
            sound_attach(tunnel_mech_sound_handle, &obj->x, NULL);
            tunnel_mech_sound_on = 1;
        }
        dz = (player[2] - aim_pos[2]) + 0x7D0;
        dx = player[0] - aim_pos[0];
        dy = player[1] - aim_pos[1];
        vector_to_angles(dx, dy, dz, &aim_angles[0], &aim_angles[1]);
        *(s16 *)&obj->vars.enemy.unk_260[2] = angle_approach(*(s16 *)&obj->vars.enemy.unk_260[2], -aim_angles[1], 8);
        steer[0] = *(s16 *)&obj->vars.enemy.unk_260[2];
        sweep = &tunnel_mech_sweep_timer;
        if (*sweep >= 0x1001) {
            tunnel_mech_fire_side(obj, steer, 1);
            *sweep = 0;
        } else {
            tunnel_mech_fire_side(obj, steer, 0);
        }
    } else {
        vector_to_angles(player[0] - aim_pos[0], player[1] - aim_pos[1], 0x100, &aim_angles[0], &aim_angles[1]);
        pitch = aim_angles[1];
        *(u16 *)&obj->vars.enemy.unk_260[4] = 0x78;
        *(s16 *)&obj->vars.enemy.unk_260[2] = -pitch;
    }
    *(u16 *)&obj->vars.enemy.unk_260[4] = *(u16 *)&obj->vars.enemy.unk_260[4] - 1;
    sweep_wrap = &tunnel_mech_sweep_timer;
    *sweep_wrap = (u16) *sweep_wrap + 0x400;
}

extern s16 tunnel_mech_sound_on;
extern s32 tunnel_mech_sound_handle;
extern s16 tunnel_mech_sound2_on;
extern s32 tunnel_mech_sound2_handle;
void func_800C13AC(void);
void tunnel_mech_stop_sounds(Object *obj) {
    if (obj->vars.tunnel_mech_m2_boss.unk_266 == 0) {
        func_800C13AC();
    }
    if (tunnel_mech_sound_on == 1) {
        sound_stop(tunnel_mech_sound_handle);
        tunnel_mech_sound_handle = 0;
        tunnel_mech_sound_on = 0;
    }
    if (tunnel_mech_sound2_on == 1) {
        sound_stop(tunnel_mech_sound2_handle);
        tunnel_mech_sound2_handle = 0;
        tunnel_mech_sound2_on = 0;
    }
}

void tunnel_mech_fire_effect(Object *obj);
void tunnel_mech_fire_cycle(BlinkObj *obj) {
    u16 count;

    if (obj->timer < 0) {
        count = obj->count - 1;
        obj->count = count;
        if ((s16)count < 0) {
            obj->count = 3;
        }
        obj->timer = 0x1E;
        tunnel_mech_fire_effect((Object *)obj);
    }
    obj->timer = (s16)((u16)obj->timer - 1);
    if (tunnel_mech_sound2_on == 1) {
        sound_stop(tunnel_mech_sound2_handle);
        tunnel_mech_sound2_handle = 0;
        tunnel_mech_sound2_on = 0;
    }
}

void tunnel_mech_fire_shot(Object *obj, s32 mode);
void tunnel_mech_fire_update(Object *obj) {
    s32 angle;
    s32 cam_x;
    s32 cam_y;
    s32 obj_x;
    s32 obj_y;

    cam_x = cam_pos >> 12;
    cam_y = cam_pos_y >> 12;
    obj_x = obj->x >> 12;
    obj_y = (obj->y >> 12) - 0x2D0;

    if (tunnel_mech_sound_on == 1) {
        sound_stop(tunnel_mech_sound_handle);
        tunnel_mech_sound_handle = 0;
        tunnel_mech_sound_on = 0;
    }
    if (tunnel_mech_sound2_on == 0) {
        tunnel_mech_sound2_handle = sound_start(0xB030B031, 0x40, 0, 0);
        sound_attach(tunnel_mech_sound2_handle, &obj->x, NULL);
        tunnel_mech_sound2_on = 1;
    }

    angle = atan2(obj_x - cam_x, obj_y - cam_y);
    if (obj->vars.enemy.walk_state >= 0x1001) {
        if ((u16)(angle - 0x200) >= 0xC01) {
            tunnel_mech_fire_shot(obj, 2);
            tunnel_mech_fire_shot(obj, 1);
        } else if ((u16)(angle - 0x201) < 0x3FF) {
            tunnel_mech_fire_shot(obj, 4);
            tunnel_mech_fire_shot(obj, 2);
        } else if ((u16)(angle - 0x601) < 0x3FF) {
            tunnel_mech_fire_shot(obj, 4);
            tunnel_mech_fire_shot(obj, 3);
        } else {
            tunnel_mech_fire_shot(obj, 3);
            tunnel_mech_fire_shot(obj, 1);
        }
        obj->vars.enemy.walk_state = 0;
    }
    obj->vars.enemy.walk_state += 0x200;
    *(u16 *)&obj->vars.enemy.unk_26E += 0x20;
}

extern s16 tunnel_mech_fired_flag;
void tunnel_mech_effect_at_player(Object *obj);
/* Fires the object's effect when its z is within 0x2BC (in 4096ths) of
 * cam_pos_z, once the timer at 0x276 has passed 0x1000. The timer restarts
 * at 0 when it fires, and grows by 0x1000 on every call. */
void tunnel_mech_fire_when_near(Object *obj) {
    s32 pos[3];
    s32 cam_z;
    s32 obj_z;

    cam_z = (s32) cam_pos_z >> 12;
    obj_z = obj->z >> 12;
    if (ABS(cam_z - obj_z) < 0x2BC) {
        if (*(s16 *) obj->vars.enemy.unk_276 >= 0x1001) {
            tunnel_mech_effect_at_player(obj);
            *(s16 *) obj->vars.enemy.unk_276 = 0;
            pos[0] = obj->x >> 12;
            pos[1] = obj->y >> 12;
            pos[2] = obj->z >> 12;
            sound_play_at_units(SND_TUNNEL_MECH_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
            tunnel_mech_fired_flag = 1;
        }
    }
    *(s16 *) obj->vars.enemy.unk_276 = (s16) (*(u16 *) obj->vars.enemy.unk_276 + 0x1000);
}

extern s16 tunnel_mech_step_counter;
void tunnel_mech_step_timer_update(Object *obj) {
    s32 pos[4];
    s32 slot;

    slot = obj->solid_id;
    if (obj->next_state == 3 && obj->vars.tunnel_mech_m2_boss.prev_state != obj->next_state) {
        s16 *counter;

        if (solid_part_box(slot, 0, pos, 0) == 0) {
            return;
        }
        counter = &tunnel_mech_step_counter;
        if (*counter >= 0x1001) {
            sound_play_at_units(SND_TUNNEL_MECH_STEP | SND_GROUP(2), 0x60, 0x3C, pos);
            *counter = 0;
        }
    }
    if (obj->vars.tunnel_mech_m2_boss.prev_state == 3) {
        if (obj->next_state == 3) {
            tunnel_mech_step_counter = 0x1001;
        } else {
            s16 *counter;

            if (solid_part_box(slot, 0, pos, 0) == 0) {
                return;
            }
            counter = &tunnel_mech_step_counter;
            if (*counter >= 0x1001) {
                sound_play_at_units(SND_TUNNEL_MECH_STEP | SND_GROUP(2), 0x60, 0x3C, pos);
                *counter = 0;
            }
            if (obj->vars.tunnel_mech_m2_boss.prev_state == obj->next_state) {
                tunnel_mech_step_counter = 0x1001;
            }
        }
    } else if (obj->vars.tunnel_mech_m2_boss.prev_state == obj->next_state) {
        tunnel_mech_step_counter = 0x1001;
    }
    {
        s16 *counter;

        counter = &tunnel_mech_step_counter;
        *counter = (u16)*counter + 0xAA;
    }
}

extern s16 tunnel_mech_state;
void tunnel_mech_footstep_sound(Object *obj) {
    s32 pos[4];
    u32 solid;
    s16 *timer;

    timer = &tunnel_mech_state;
    solid = obj->solid_id;
    if (*timer >= 0x1001) {
        if (solid_part_box(solid, 0xD, pos, 0) == 0) {
            return;
        }
        if (ABS(pos[1]) != 0x1A4) {
            if (solid_part_box(solid, 0xE, pos, 0) == 0) {
                return;
            }
            if (ABS(pos[1]) != 0x62C) {
                if (solid_part_box(solid, 0x14, pos, 0) == 0) {
                    return;
                }
                if (ABS(pos[1]) != 0x62C) {
                    if (solid_part_box(solid, 0x13, pos, 0) == 0) {
                        return;
                    }
                    if (ABS(pos[1]) != 0x1A4) {
                        goto add;
                    }
                }
            }
        }
        sound_play_at_units(SND_MECH_FOOTSTEP | SND_GROUP(2), 0x60, 0x3C, pos);
        do {
            *timer = 0;
        } while (0);
    }
add:
    {
        s16 *counter = &tunnel_mech_state;
        *counter = (u16)*counter + 0xAA;
    }
}

void enemy_shot_pick_mode(Object *obj) {
    s32 *player;
    Vec3 pos;
    s32 r;
    s32 dx;

    if (*(s16 *)&obj->vars.enemy.shot_timer != 0) {
        if (cam_pos_y >= obj->y) {
            *(s16 *)obj->vars.enemy.unk_260 = 1;
        } else {
            *(s16 *)obj->vars.enemy.unk_260 = 2;
        }
        player = player_position();
        pos.x = obj->x >> 12;
        pos.y = obj->y >> 12;
        pos.z = obj->z >> 12;
        dx = player[0] - pos.x;
        if ((dx < 0 ? pos.x - player[0] : dx) < 100) {
            *(s16 *)obj->vars.enemy.unk_260 = 0;
        }
        if (rand_a_next() % 6 == 1) {
            *(s16 *)obj->vars.enemy.unk_260 = 2;
        } else if (rand_a_next() % 6 == 1) {
            *(s16 *)obj->vars.enemy.unk_260 = 1;
        } else {
            r = rand_a_next();
            if (r == (r / 3) * 3) {
                *(s16 *)obj->vars.enemy.unk_260 = 0;
            }
        }
        *(s16 *)&obj->vars.enemy.shot_timer = 0;
    }
}

char str_mfir_tp0_clt[16] RODATA = "mfir_tp0.clt";

char str_mfir_ch0_clt[16] RODATA = "mfir_ch0.clt";

char str_mfir_tp0_xs3[16] RODATA = "mfir_tp0.xs3";

char str_mfir_ch0_vx1[16] RODATA = "mfir_ch0.vx1";

char str_mfir_ch0cb4[16] RODATA = "mfir_ch0.cb4";

char str_sel1_tp0_clt[16] RODATA = "sel1_tp0.clt";

char str_sel1_ch0_clt[16] RODATA = "sel1_ch0.clt";

char str_sel1_tp0_xs3[16] RODATA = "sel1_tp0.xs3";

char str_sel1_ch0_vx1[16] RODATA = "sel1_ch0.vx1";

char str_sel1_ch0cb4[16] RODATA = "sel1_ch0.cb4";

char str_hou2_tp0_clt[16] RODATA = "hou2_tp0.clt";

char str_hou2_ch0_clt[16] RODATA = "hou2_ch0.clt";

char str_hou2_tp0_xs3[16] RODATA = "hou2_tp0.xs3";

char str_hou2_ch0_vx1[16] RODATA = "hou2_ch0.vx1";

char str_hou2_ch0cb4[16] RODATA = "hou2_ch0.cb4";

char str_kira_tp0_clt[16] RODATA = "kira_tp0.clt";

char str_kira_ch0_clt[16] RODATA = "kira_ch0.clt";

char str_kira_tp0_xs3[16] RODATA = "kira_tp0.xs3";

char str_kira_ch0_vx1[16] RODATA = "kira_ch0.vx1";

char str_kira_ch0cb4[16] RODATA = "kira_ch0.cb4";

char str_jira_tp0_clt[16] RODATA = "jira_tp0.clt";

char str_jira_ch0_clt[16] RODATA = "jira_ch0.clt";

char str_jira_tp0_xs3[16] RODATA = "jira_tp0.xs3";

char str_jira_ch0_vx1[16] RODATA = "jira_ch0.vx1";

char str_jira_ch0cb4[16] RODATA = "jira_ch0.cb4";

char str_bos2_tp1_clt[16] RODATA = "bos2_tp1.clt";

char str_bos2_tp0_clt[16] RODATA = "bos2_tp0.clt";

char str_bos2_ch3_clt[16] RODATA = "bos2_ch3.clt";

char str_bos2_ch2_clt[16] RODATA = "bos2_ch2.clt";

char str_bos2_ch1_clt[16] RODATA = "bos2_ch1.clt";

char str_bos2_ch0_clt[16] RODATA = "bos2_ch0.clt";

char str_bos2_tp1_xs3[16] RODATA = "bos2_tp1.xs3";

char str_bos2_tp0_xs3[16] RODATA = "bos2_tp0.xs3";

char str_bos2_ch3_vx1[16] RODATA = "bos2_ch3.vx1";

char str_bos2_ch2_vx1[16] RODATA = "bos2_ch2.vx1";

char str_bos2_ch1_vx1[16] RODATA = "bos2_ch1.vx1";

char str_bos2_ch0_vx1[16] RODATA = "bos2_ch0.vx1";

char str_bos2_ch3cb4[16] RODATA = "bos2_ch3.cb4";

char str_bos2_ch2cb4[16] RODATA = "bos2_ch2.cb4";

char str_bos2_ch1cb4[16] RODATA = "bos2_ch1.cb4";

char str_bos2_ch0cb4[16] RODATA = "bos2_ch0.cb4";

void tunnel_mech_state_update(Object *obj) {
    s32 state;
    s32 state_hi;
    s32 playing;

    if (*(s16 *)&obj->vars.enemy.unk_276[4] > 0x1000) {
        obj->vars.tunnel_mech_m2_boss.timer--;
        switch (obj->next_state) {
        case 0:
        case 1:
        case 2:
            enemy_shot_pick_mode(obj);
            break;
        case 3:
            *(s16 *)obj->vars.enemy.unk_260 = 3;
            break;
        case 4:
            *(s16 *)obj->vars.enemy.unk_260 = 4;
            break;
        }
        *(s16 *)&obj->vars.enemy.unk_276[4] = 0x1001;
    } else {
        *(s16 *)obj->vars.enemy.unk_260 = 4;
    }

    if (*(s16 *)&obj->vars.enemy.unk_276[2] <= 0x1000) {
        *(s16 *)obj->vars.enemy.unk_260 = 4;
        *(s16 *)&obj->vars.enemy.unk_276[2] += 0x15;
    }

    switch (*(s16 *)obj->vars.enemy.unk_260) {
    case 0:
        if (obj->vars.tunnel_mech_m2_boss.unk_266 == 0) {
            tunnel_mech_aim_update(obj);
        }
        break;
    case 1:
        if (obj->vars.tunnel_mech_m2_boss.unk_266 == 0) {
            tunnel_mech_fire_cycle((BlinkObj *)obj);
        }
        break;
    case 2:
        tunnel_mech_stop_sounds(obj);
        break;
    case 3:
        tunnel_mech_fire_update(obj);
        break;
    case 4:
        break;
    }

    if (obj->vars.tunnel_mech_m2_boss.timer < 0) {
        obj->vars.tunnel_mech_m2_boss.timer = 0xF0;
        obj->vars.enemy.target_yaw = 3;
        do { } while (0);
        playing = tunnel_mech_sound_on;
        *(s16 *)&obj->vars.enemy.unk_260[2] = 0;
        *(s16 *)&obj->vars.enemy.unk_260[4] = 0;
        *(s16 *)&obj->vars.tunnel_mech_m2_boss.unk_268 = 0;
        obj->vars.enemy.walk_state = 0;
        if (playing == 1) {
            sound_stop(tunnel_mech_sound_handle);
            tunnel_mech_sound_handle = 0;
            tunnel_mech_sound_on = 0;
        }
        if (tunnel_mech_sound2_on == 1) {
            sound_stop(tunnel_mech_sound2_handle);
            tunnel_mech_sound2_handle = 0;
            tunnel_mech_sound2_on = 0;
        }
        *(s16 *)&obj->vars.enemy.unk_276[4] = 0;
        *(s16 *)&obj->vars.enemy.shot_timer = 1;
    }

    tunnel_mech_fire_when_near(obj);
    state = obj->next_state;
    state_hi = state << 16; /* the original re-sign-extends state for the second test */
    if (state == 1 || (state = state_hi >> 16) == 2) {
        tunnel_mech_footstep_sound(obj);
    }
    tunnel_mech_step_timer_update(obj);
    *(s16 *)&obj->vars.enemy.unk_276[4] += 0x20;
}

void tunnel_mech_state_update(Object *obj);
/* Steps a flying object: while its state is 1 or 2, fly_move turns its speed
   along its yaw into the (unk_210, unk_208) pair; then it clears vy and, unless
   the state is 4, calls tunnel_mech_state_update. */
void tunnel_mech_m2_boss_update(Object *obj) {
    s32 dz;
    s32 dx;

    dx = 0;
    dz = 0;
    collider_begin((Collider *) obj->unk_A4);
    obj_state_step(obj);
    if ((u16) obj->next_state - 1 < 2U) {
        fly_move(obj->yaw, obj->speed, &dx, &dz);
    }
    obj->vx = dz;
    obj->vy = 0;
    obj->vz = dx;
    if (obj->next_state != 4) {
        tunnel_mech_state_update(obj);
    }
}

s32 tunnel_mech_aim_joints(TunnelMechObj *obj) {
    s32 joints[3];
    s32 yaw;
    s32 pitch;
    s32 cam_x;
    s32 cam_y;
    s32 x;
    s32 y;
    s32 sin_part;
    s32 cos_part;
    s32 angle;
    s32 base;
    s32 result;

    sin_part = 0;
    cos_part = 0;
    cam_x = cam_pos >> 12;
    cam_y = cam_pos_y >> 12;
    x = obj->x >> 12;
    y = (obj->y >> 12) - 0x2D0;
    base = model_slot_pchr(*obj->asset) + 0x101;
    joints[0] = base;
    joints[1] = base;
    joints[2] = base;
    vector_to_angles(x - cam_x, y - cam_y, 0x100, &yaw, &pitch);
    if (cam_y < y) {
        sin_part = *(s16 *)&rcossin_tbl[pitch & 0xFFF];
        joints[1] = model_slot_pchr(*obj->asset) + 0xAF;
        joints[1] = pchr_blend(joints[1], joints[0], sin_part, 0);
    } else if (y < cam_y) {
        sin_part = *(s16 *)&rcossin_tbl[-pitch & 0xFFF];
        joints[1] = model_slot_pchr(*obj->asset) + 0x8F;
        joints[1] = pchr_blend(joints[1], joints[0], sin_part, 0);
        sin_part = -sin_part;
    }
    if (x < cam_x) {
        cos_part = cos_table[(yaw + 0x400) & 0xFFF].value;
        joints[2] = model_slot_pchr(*obj->asset) + 0xEF;
        joints[2] = pchr_blend(joints[2], joints[0], cos_part, 0);
    } else if (cam_x < x) {
        cos_part = cos_table[(-yaw + 0x400) & 0xFFF].value;
        joints[2] = model_slot_pchr(*obj->asset) + 0xCF;
        joints[2] = pchr_blend(joints[2], joints[0], cos_part, 0);
        cos_part = -cos_part;
    }
    angle = atan2(sin_part, cos_part);
    if (cam_y < y) {
        if (cam_x < x) {
            result = pchr_blend(joints[1], joints[2], (angle - 0xC00) * 4, 0);
        } else {
            result = pchr_blend(joints[1], joints[2], 0x1000 - angle * 4, 0);
        }
    } else if (cam_x < x) {
        angle -= 0x800;
        result = pchr_blend(joints[1], joints[2], 0x1000 - angle * 4, 0);
    } else {
        result = pchr_blend(joints[1], joints[2], (angle - 0x400) * 4, 0);
    }
    return result;
}

extern s16 tunnel_mech_path[];
s32 tunnel_mech_path_a(Object *obj) {
    s32 pos[2];

    pos[0] = tunnel_mech_path[obj->vars.tunnel_mech_m2_boss.path_index];
    pos[1] = tunnel_mech_path[(obj->vars.tunnel_mech_m2_boss.path_index + 1) % obj->vars.tunnel_mech_m2_boss.path_count];
    pos[0] += model_slot_pchr(*(s32 *)obj->asset);
    pos[1] += model_slot_pchr(*(s32 *)obj->asset);
    return pchr_blend(pos[0], pos[1], 0x1000 - (s16)obj->vars.tunnel_mech_m2_boss.path_blend, 0);
}

extern s16 tunnel_mech_path_b_table[];
/* Same code as tunnel_mech_path_a (s02). */
s32 tunnel_mech_path_b(Object *obj) {
    s32 pos[2];

    pos[0] = tunnel_mech_path_b_table[obj->vars.tunnel_mech_m2_boss.path_index];
    pos[1] = tunnel_mech_path_b_table[(obj->vars.tunnel_mech_m2_boss.path_index + 1) % obj->vars.tunnel_mech_m2_boss.path_count];
    pos[0] += model_slot_pchr(*(s32 *)obj->asset);
    pos[1] += model_slot_pchr(*(s32 *)obj->asset);
    return pchr_blend(pos[0], pos[1], 0x1000 - (s16)obj->vars.tunnel_mech_m2_boss.path_blend, 0);
}

extern s16 tunnel_mech_path_c_table[];
s32 tunnel_mech_path_c(Object *obj) {
    s32 pos[2];
    s32 result;

    pos[0] = tunnel_mech_path_c_table[obj->vars.tunnel_mech_m2_boss.path_index];
    pos[1] = tunnel_mech_path_c_table[(obj->vars.tunnel_mech_m2_boss.path_index + 1) % obj->vars.tunnel_mech_m2_boss.path_count];
    pos[0] += model_slot_pchr(*(s32 *)obj->asset);
    pos[1] += model_slot_pchr(*(s32 *)obj->asset);
    result = pchr_blend(pos[0], pos[1], 0x1000 - (s16)obj->vars.tunnel_mech_m2_boss.path_blend, 0);
    if (obj->vars.tunnel_mech_m2_boss.path_index + 1 == obj->vars.tunnel_mech_m2_boss.path_count && obj->next_state == 4) {
        ((s16 *)&obj->vars.tunnel_mech_m2_boss.unused_25A)[0xC] = -1; /* offset 0x272 */
    }
    return result;
}

s32 tunnel_mech_aim_joints(TunnelMechObj *obj);
s32 tunnel_mech_pose_lerp(TunnelMechObj *obj) {
    s32 t[7];
    s32 ret = -1;

    t[2] = model_slot_pchr(*obj->asset) + 0x101;
    t[3] = tunnel_mech_path_a((Object *)obj);
    t[4] = tunnel_mech_path_b((Object *)obj);
    t[5] = tunnel_mech_aim_joints(obj);
    t[6] = tunnel_mech_path_c((Object *)obj);
    t[0] = t[obj->index + 2];
    t[1] = t[obj->next_index + 2];
    if (obj->mode == ret) {
        ret = model_slot_pchr(*obj->asset) + 0x150;
    } else {
        ret = pchr_blend(t[0], t[1], 0x1000 - obj->frame, 0);
    }
    return ret;
}

static inline void tunnel_spark_add(SparkList *list, s32 ry, s32 rx, s32 rz, s32 x, s32 y, s32 z, s32 value, s32 colour) {
    s32 n = spark_count;
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
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}
void tunnel_mech_m2_boss_draw(Object *obj, ObjHandler *handler) {
    s32 pos[3];
    s16 rot[3];
    SVECTOR dir;
    s32 value;
    s32 colour;
    s32 pitch;
    Object *self;

    /* the original reads obj in $a0 until the call and keeps a copy in $s0 for after it */
    self = obj;
    FAKE_OPAQUE(self);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    value = tunnel_mech_pose_lerp((TunnelMechObj *)obj);
    {
        /* the original's registers for the y offset (load in $v1, result in $t4) */
        register s32 py asm("$3") = pos[1];
        register s32 y asm("$12") = py - 0x2D0;

        tunnel_spark_add(&spark_list, rot[1], rot[0], rot[2], pos[0], y, pos[2], value, colour);
    }
    pos[0] = self->x;
    pos[1] = self->y;
    pos[2] = self->z;
    dir.vx = self->width;
    dir.vy = self->height;
    dir.vz = self->unk_1E8[0];
    aim_marker_draw(2, &dir, (Vec3 *)pos, 0);
    if (self->hit != 0) {
        self->hit = -1;
    }
}

/* the original passes only the first two arguments to solid_add */
s32 tunnel_mech_view_angle(Object *obj) {
    s32 heights[3];
    s16 pos[2];
    s16 frac[2];
    s32 yaw;
    s32 pitch;
    s32 camX, camY, objX, objY;
    s32 sinv = 0;
    s32 cosv = 0;
    s32 base;
    s32 angle;

    camX = cam_pos >> 12;
    objX = obj->x >> 12;
    camY = cam_pos_y >> 12;
    objY = obj->y >> 12;
    base = ((s32 *)obj->asset)[1] + 0x101;
    frac[0] = 0;
    frac[1] = 0x1000;
    heights[0] = base;
    heights[1] = base;
    heights[2] = base;
    pos[0] = base;
    pos[1] = base;
    vector_to_angles(objX - camX, objY - camY, 0x100, &yaw, &pitch);
    if (camY < objY) {
        sinv = *(s16 *)&rcossin_tbl[pitch & 0xFFF];
        frac[1] = sinv;
        frac[0] = 0x1000 - sinv;
        pos[1] = ((s32 *)obj->asset)[1] + 0xAF;
        heights[1] = ((s32 (*)(s16 *, s16 *))solid_add)(pos, frac);
    } else if (objY < camY) {
        sinv = *(s16 *)&rcossin_tbl[-pitch & 0xFFF];
        frac[1] = sinv;
        frac[0] = 0x1000 - sinv;
        sinv = -sinv;
        pos[1] = ((s32 *)obj->asset)[1] + 0x8F;
        heights[1] = ((s32 (*)(s16 *, s16 *))solid_add)(pos, frac);
    }
    if (objX < camX) {
        cosv = cos_table[(yaw + 0x400) & 0xFFF].value;
        frac[1] = cosv;
        frac[0] = 0x1000 - cosv;
        pos[1] = ((s32 *)obj->asset)[1] + 0xEF;
        heights[2] = ((s32 (*)(s16 *, s16 *))solid_add)(pos, frac);
    } else if (camX < objX) {
        cosv = cos_table[(-yaw + 0x400) & 0xFFF].value;
        frac[1] = cosv;
        frac[0] = 0x1000 - cosv;
        cosv = -cosv;
        pos[1] = ((s32 *)obj->asset)[1] + 0xCF;
        heights[2] = ((s32 (*)(s16 *, s16 *))solid_add)(pos, frac);
    }
    angle = atan2(sinv, cosv);
    pos[0] = heights[1];
    pos[1] = heights[2];
    if (camY < objY) {
        if (camX < objX) {
            angle -= 0xC00;
            frac[0] = angle * 4;
            frac[1] = 0x1000 - frac[0];
        } else {
            frac[0] = 0x1000 - angle * 4;
            frac[1] = 0x1000 - frac[0];
        }
    } else if (camX < objX) {
        angle -= 0x800;
        frac[0] = 0x1000 - angle * 4;
        frac[1] = 0x1000 - frac[0];
    } else {
        angle -= 0x400;
        frac[0] = angle * 4;
        frac[1] = 0x1000 - frac[0];
    }
    return ((s32 (*)(s16 *, s16 *))solid_add)(pos, frac);
}

s32 tunnel_mech_add_solid_a(Object *obj) {
    u16 pos[2];
    u16 rect[2];
    u16 first;
    u16 second;

    first = tunnel_mech_path[(s16)obj->vars.h.unk_258];
    pos[0] = first;
    second = tunnel_mech_path[((s16)obj->vars.h.unk_258 + 1) % (s16)obj->vars.h.unk_256];
    pos[1] = second;
    pos[0] = first + ((s32 *)obj->asset)[1];
    pos[1] = second + ((s32 *)obj->asset)[1];
    rect[0] = obj->vars.h.unk_254;
    rect[1] = 0x1000 - obj->vars.h.unk_254;
    /* the original sets only the first two arguments */
    return ((s32 (*)(s16 *, s16 *))solid_add)((s16 *)pos, (s16 *)rect);
}

/* Same code as tunnel_mech_add_solid_a (s02). */
s32 tunnel_mech_add_solid_b(Object *obj) {
    u16 pos[2];
    u16 rect[2];
    u16 first;
    u16 second;

    first = tunnel_mech_path_b_table[(s16)obj->vars.h.unk_258];
    pos[0] = first;
    second = tunnel_mech_path_b_table[((s16)obj->vars.h.unk_258 + 1) % (s16)obj->vars.h.unk_256];
    pos[1] = second;
    pos[0] = first + ((s32 *)obj->asset)[1];
    pos[1] = second + ((s32 *)obj->asset)[1];
    rect[0] = obj->vars.h.unk_254;
    rect[1] = 0x1000 - obj->vars.h.unk_254;
    /* the original sets only the first two arguments */
    return ((s32 (*)(s16 *, s16 *))solid_add)((s16 *)pos, (s16 *)rect);
}

s32 tunnel_mech_view_angle(Object *obj);
void tunnel_mech_submit_model(Object *obj) {
    s16 pts[8];
    s32 slots[5];
    s32 lookup;
    s32 pitch;
    u8 *block;

    /* slots: asset word 1 + 0x101, then four helper results */
    slots[0] = ((s32 *)obj->asset)[1] + 0x101;
    slots[1] = tunnel_mech_add_solid_a(obj);
    slots[2] = tunnel_mech_add_solid_b(obj);
    slots[3] = tunnel_mech_view_angle(obj);
    slots[4] = tunnel_mech_view_angle(obj);

    if (obj->next_state != (s16)obj->vars.h.unk_250) {
        pts[5] = obj->vars.fly.phase;
        pts[4] = 0x1000 - obj->vars.fly.phase;
        pts[0] = (s16)slots[(s16)obj->vars.h.unk_250];
        pts[1] = (s16)slots[obj->next_state];
        /* the original sets only the first two arguments */
        lookup = ((s32 (*)(s16 *, s16 *))solid_add)(pts, &pts[4]);
    } else {
        lookup = (u16)slots[obj->next_state];
    }

    /* unk_A4 block: pitch/yaw/roll copies at +0x2C/+0x2E/+0x30 (0xD0/0xD2/0xD4) */
    block = obj->unk_A4;
    block[1] = 1;
    pitch = obj->pitch;
    *(s16 *)(block + 0x2C) = -pitch;
    *(u16 *)(block + 0x2E) = obj->yaw;
    *(u16 *)(block + 0x30) = obj->roll;
    block[0] = obj->index;
    obj_block_fill(obj, block);
    solid_setup_scratch(obj->solid_id, block, (s16)lookup, 0x1000);
    fn_800FB460(obj, block);
}

void tunnel_mech_submit_model(Object *obj);
void tunnel_mech_damage_update(Object *obj, ObjHandler *h) {
    s32 flags;

    if (obj->hit < 0) {
        obj->hit = 0;
    }
    obj_hit_update(obj);
    if (obj->health <= 0) {
        h->state = 1;
        h->request_flags = 8;
        return;
    }
    flags = obj->flags;
    if (((u32)flags >> 5) & 1) {
        tunnel_mech_submit_model(obj);
    }
}

s32 obj_run_stored_update(Object *obj) {
    s32 result;
    s32 points;
    s32 (*update)(Object *);

    points = obj->score;
    update = (s32 (*)(Object *))obj->callback;
    result = 0;
    if (points != 0) {
        add_score(points);
        obj->score = 0;
        add_kill_count(1);
    }
    if (update != NULL) {
        result = update(obj);
    }
    return result;
}

extern void (*obj_state_step_table[])(Object *obj, ObjHandler *handler);
/* Runs the state handler until it stops asking for a rerun (unk_10), then
   shows the object's health on the meter. */
void obj_state_run_health_meter(Object *obj, ObjHandler *handler) {
    void (*step)(Object *, ObjHandler *);
    Object *self = obj;

rerun:
    handler->request_flags = 0;
    step = obj_state_step_table[handler->state];
    if (step != NULL) {
        step(obj, handler);
    }
    if (handler->request_flags != 0) {
        goto rerun;
    }
    meter_set(obj->health, self->vars.tunnel_mech_m2_boss.health_meter_max);
}

void obj_state_run_health_meter(Object *obj, ObjHandler *handler);
void tunnel_mech_shot_arm(void);
void tunnel_mech_m2_boss_phase2(Object *obj, ObjHandler *handler) {
    obj->y -= 0x2D0000;
    obj_state_run_health_meter(obj, handler);
    obj->y += 0x2D0000;
    tunnel_mech_shot_arm();
}

extern s32 stage_end_flag;
void obj_become_spark(Object *obj);
/* Kills the tunnel mech: stops its sounds, sets the next state and throws explosions around it; once its sound is gone (-1), turns it into a spark. */
s32 tunnel_mech_destroy(Object *obj) {
    s32 dx;
    s32 dy;
    s32 lift;
    s32 pitch;
    s32 pos[3];
    s16 rot[4];

    dx = rand_a_next() % 512;
    dy = rand_a_next() % 256;
    rand_a_next();
    if (tunnel_mech_sound_on == 1) {
        sound_stop(tunnel_mech_sound_handle);
        tunnel_mech_sound_handle = 0;
        tunnel_mech_sound_on = 0;
    }
    if (tunnel_mech_sound2_on == 1) {
        sound_stop(tunnel_mech_sound2_handle);
        tunnel_mech_sound2_handle = 0;
        tunnel_mech_sound2_on = 0;
    }
    stage_end_flag = 1;
    meter_set_mode(0);
    set_d_801202C8(0);
    obj->next_state = 4;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    obj->vars.tunnel_mech_m2_boss.unk_266 = 2;
    meter_set_mode(0);
    if (obj->vars.tunnel_mech_m2_boss.unk_274 == 0) {
        spawn_effect(pos[0] + dx, pos[1] - dy, pos[2], 0x80007F01);
        spawn_effect(pos[0] - dx, pos[1] - dy, pos[2], 0x80000002);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
        obj->vars.tunnel_mech_m2_boss.path_index = 0;
        obj->vars.tunnel_mech_m2_boss.angle = 0;
        obj->vars.tunnel_mech_m2_boss.unk_274 = -1;
    }
    lift = 0x200;
    if (rand_a_next() % 5 == 0) {
        if ((s16)obj->vars.tunnel_mech_m2_boss.fire_side == 0) {
            spawn_effect(pos[0] + dx, pos[1] - (dy - lift), pos[2], 0x80007F00);
        } else {
            spawn_effect(pos[0] - dx, pos[1] - (dy - lift), pos[2], 0x80000000);
        }
    }
    if (obj->vars.tunnel_mech_m2_boss.sound == -1) {
        sound_play_at_units(SND_MECH_DESTROY_EXPLOSION | SND_GROUP(1), 0x60, 0x3C, pos);
        obj_become_spark(obj);
        return 0;
    }
}

void tunnel_mech_m2_boss_draw(Object *obj, ObjHandler *handler);
extern u8 tunnel_mech_asset[];
extern s16 *tunnel_mech_script[];
extern s16 *D_80117310;
extern ScriptCallEntry D_80117314[];
s32 tunnel_mech_m2_boss_spawn(Placement *place) {
    Object *obj;
    s16 *script_pc;
    s32 script_arg;
    u8 place_byte5;
    u16 health;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), &obj->node);
    script_arg = 0;
    script_pc = NULL;
    obj->handlers[0].fn = (void *)tunnel_mech_m2_boss_phase0;
    obj->handlers[1].fn = (void *)tunnel_mech_m2_boss_update;
    obj->handlers[2].fn = tunnel_mech_m2_boss_phase2;
    obj->handlers[3].fn = tunnel_mech_m2_boss_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32)tunnel_mech_destroy;
    place_byte5 = place->unk_04[1];
    obj->asset = tunnel_mech_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 0;
    obj->call_table = D_80117314;
    obj->kind = place_byte5;
    script_start((Script *)obj, script_pc, script_arg);
    obj->script.data = tunnel_mech_script;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80117310;
    obj_init_from_place(obj, place, 0x134);
    obj->speed = 0;
    obj_set_part_bounds(obj, 0x101, 0x1000);
    obj_hit_set_unk08(obj->index, 1);
    obj_hit_set_unk06(obj->index, 0);
    obj->vars.tmech.path_len = 0;
    obj->vars.tmech.unused_248[0] = 0;
    obj->vars.tmech.unused_248[1] = 0;
    obj->vars.tmech.unused_248[2] = 0;
    obj->vars.tmech.unused_248[3] = 0;
    obj->vars.tmech.unused_248[4] = 0;
    obj->vars.tmech.unused_248[5] = 0;
    obj->vars.tmech.unused_248[6] = 0;
    obj->vars.tmech.unused_258 = 0;
    while (tunnel_mech_path[obj->vars.tmech.path_len] != -1) {
        obj->vars.tmech.path_len++;
    }
    health = obj->health;
    obj->vars.tmech.unused_25E[0] = 0;
    obj->vars.tmech.unused_25E[1] = 0;
    obj->vars.tmech.unused_25E[2] = 0;
    obj->vars.tmech.unused_25E[3] = 0;
    obj->vars.tmech.unused_25E[4] = 0;
    obj->vars.tmech.unused_25E[5] = 0;
    obj->vars.tmech.unused_26A = 3;
    obj->vars.tmech.unused_26C = 0;
    obj->vars.tmech.unused_26E = 0;
    obj->vars.tmech.unused_272[0] = 0;
    obj->vars.tmech.unused_272[1] = 0;
    obj->vars.tmech.unused_272[2] = 0;
    obj->vars.tmech.unused_272[3] = 0;
    obj->vars.tmech.unused_272[4] = 0;
    obj->vars.tmech.unused_272[5] = 0;
    (*(TunnelMechState *)&tunnel_mech_state).sound_on = 0;
    (*(TunnelMechState *)&tunnel_mech_state).sound_handle = 0;
    (*(TunnelMechState *)&tunnel_mech_state).sound2_on = 0;
    (*(TunnelMechState *)&tunnel_mech_state).sound2_handle = 0;
    (*(TunnelMechState *)&tunnel_mech_state).unk_18 = 0;
    (*(TunnelMechState *)&tunnel_mech_state).unk_1C = 0;
    obj->vars.tmech.health_max = health;
    (*(TunnelMechState *)&tunnel_mech_state).timer = 0;
    (*(TunnelMechState *)&tunnel_mech_state).counter = 0;
    (*(TunnelMechState *)&tunnel_mech_state).sweep = 0;
    (*(TunnelMechState *)&tunnel_mech_state).unk_06 = 0;
    obj_hit_flag_set(obj->index, 0x80);
    meter_set(obj->health, (s16)obj->vars.tmech.health_max);
    meter_set_mode(1);
    msg_show_slot(1, 0xB4);
    warning_ack_set(1);
    tunnel_mech_shot_arm();
    return 1;
}

/* Shows the approaching-giant-object warning line, then starts sound 0xD201 at volume 0x7F. */
void show_giant_warning(void) {
    show_line((s32)"#1Warning!  Warning! A giant object approaching.\xA1");
    sound_start(SND_WARNING_ALARM_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
}

void func_800C13AC(void) {
    tunnel_mech_laser_spawn();
}

s32 tunnel_mech_shot_spawn(s32 *pos, u16 *angles, s32 c);

/* Fires a tunnel mech shot from its solid part's box, alternating sides 0x8C either way of the centre. */
void tunnel_mech_fire_side(Object *obj, s16 *angles, s16 flag) {
    s32 pos[3];
    s32 unused[2];
    s32 y;
    s32 z;

    if (solid_part_box(obj->solid_id, 0, pos, NULL)) {
        obj->vars.tunnel_mech_m2_boss.fire_side ^= 1;
        if (obj->vars.tunnel_mech_m2_boss.fire_side == 0) {
            pos[0] += 0x8C;
            z = pos[2];
        } else {
            pos[0] -= 0x8C;
            z = pos[2];
        }
        pos[2] = z + 0x14A;
        y = pos[1] + 0x28;
        /* keeps the argument setup below the stores (the loop note pins the store) */
        do { } while (0);
        pos[1] = y;
        tunnel_mech_shot_spawn(pos, (u16 *)angles, flag);
    }
}

s32 spark_emitter_spawn(Object *parent, s32 *pos);
void tunnel_mech_fire_effect(Object *obj) {
    s32 pos[5];

    if (solid_part_box(obj->solid_id, 0, pos, 0)) {
        s32 x = pos[0] + 0x46;
        pos[0] = x - obj->vars.enemy.target_yaw * 0x2D;
        pos[1] += 0x5A;
        pos[2] += 0xFA;
        sound_play_at_units(SND_MECH_CANNON_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
        spark_emitter_spawn(obj, pos);
    }
}

s32 tunnel_mech_shot_launch(Vec3 *pos, s16 *rot, s32 index);
void tunnel_mech_fire_shot(Object *obj, s32 mode) {
    Vec3 pos;
    s16 rot[3];
    s32 bias;
    s32 index;
    u16 speed;
    s32 p, x, y, z;

    bias = 0;
    index = model_slot_pchr(*(s32 *)obj->asset);
    if (solid_part_box(obj->solid_id, mode, &pos.x, 0) != 0) {
        x = pos.x;
        y = pos.y;
        z = pos.z;
        pos.x = x;
        pos.y = y;
        pos.z = z + 0x1C2;
        p = obj->pitch;
        rot[0] = -p;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        if (mode == 2 || mode == 4) {
            bias = 0x800;
        }
        if (mode == 1 || mode == 4) {
            speed = -((u16 *)&obj->vars)[19];
        } else {
            speed = ((u16 *)&obj->vars)[19];
        }
        rot[2] = speed + bias;
        tunnel_mech_shot_launch(&pos, rot, index);
    }
}

void obj_spawn_at_pos(s32 index, s32 *pos);
/* Nudge the player's position word down by 0x64, then pass it with the
   index held in the object's asset to obj_spawn_at_pos. */
void tunnel_mech_effect_at_player(Object *obj) {
    s32 *pos;

    pos = player_position();
    pos[2] -= 0x64;
    obj_spawn_at_pos(model_slot_pchr(*(s32 *)obj->asset), pos);
}

extern s32 stage_end_flag;

/* Callers pass the object; it is not used. */
s32 is_stage_ending(Object *obj) {
    return stage_end_flag;
}

extern TrailSample laser_trail_ring[16];
extern s32 trail_head;
extern s32 trail_count;
void trail_clear(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 4; j++) {
            laser_trail_ring[i].row[j].w[0] = 0;
            laser_trail_ring[i].row[j].w[1] = 0;
            laser_trail_ring[i].row[j].w[2] = 0;
        }
    }
    trail_head = 0;
    trail_count = 0;
}

void trail_push(MatrixRow *src) {
    s32 i;

    if (trail_head >= 0x10) {
        for (i = 0; i < 15; i++) {
            laser_trail_ring[i + 1] = laser_trail_ring[i];
        }
    }
    for (i = 0; i < 4; i++) {
        laser_trail_ring[trail_head].row[i] = src[i];
    }
    trail_head = (trail_head + 1) % 16;
    if (trail_count < 0x10) {
        trail_count++;
    }
}
