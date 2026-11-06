/* reactor_control_rods: one of s09's own original source files (scripts/objmap.py); part of src/s09/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **get_flagged_grid_list(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 func_800C4838(void) {
    return grid_flagged_count;
}

char str_bos9_tp0_clt[16] = "bos9_tp0.clt";

char str_bos9_ch0_vx1[16] = "bos9_ch0.vx1";

char str_bos9_tp1_xs3[16] = "bos9_tp1.xs3";

char str_bos9_tp0_xs3[16] = "bos9_tp0.xs3";

char str_bos9_ch0cb4[16] = "bos9_ch0.cb4";

extern s32 reactor_boss_active_flag;
extern s32 boss_done_flag;
extern s32 control_rods_left;
extern RecTemplate mission_end_fx[];
void obj_fire_tick(Object *obj);
void obj_engine_sound_update(Object *obj);
void obj_shoot_callback(Object *obj);
void obj_burst_tick(Object *obj);
void obj_fly_to_camera(Object *obj);
/* Mission 9 reactor boss, phase 0: runs the control-rod state machine on next_state, then the shared tail. */
void reactor_control_rods_m9_boss_phase0(Object *obj) {
    s32 *rec;
    RecTemplate *tmpl;
    s32 flag;

    obj_link_script_run();
    switch (obj->next_state) {
    case 0:
        if (reactor_boss_active_flag != 1) {
            obj_engine_sound_update(obj);
            obj_fly_to_camera(obj);
            return;
        }
        obj->next_state = 1;
        break;
    case 1:
        if (control_rods_left >= 5 && mission_timer_get() >= 0x4B0) {
            break;
        }
        /* 0x254, 0x258, 0x25C are stored as whole words here */
        obj->vars.reactor_control_rods_m9_boss.engine_accel = 0x2000;
        obj->vars.reactor_control_rods_m9_boss.fly_speed_max = 0xA000;
        obj->vars.reactor_control_rods_m9_boss.engine_speed_max = 0xAA000;
        obj->next_state = 2;
        break;
    case 2:
        obj_fire_tick(obj);
        if (control_rods_left < 3) {
            obj->next_state = 3;
        }
        break;
    case 3:
        obj_burst_tick(obj);
        obj_fire_tick(obj);
        if (get_enemies_left() > 0) {
            break;
        }
        obj->vars.reactor_control_rods_m9_boss.engine_accel = -0x1000;
        reactor_boss_active_flag = 0;
        boss_done_flag = 1;
        pursue_flag_set(0);
        mission_timer_active_set(0);
        warning_ack_set(0);
        set_d_801202C8(0);
        set_mission_active(0);
        obj->next_state = 4;
        break;
    case 4:
        if (control_rods_left != 0) {
            break;
        }
        obj->vars.reactor_control_rods_m9_boss.fly_speed_max = 0;
        sound_stop(obj->vars.snd2.sound[0]);
        sound_stop(obj->vars.snd2.sound[1]);
        obj->vars.snd2.sound[0] = 0;
        obj->vars.snd2.sound[1] = 0;
        set_stage_end(2);
        break;
    case 5:
        rec = scratch_alloc(0x10);
        rec[0] = 0;
        rec[1] = 0;
        rec[2] = -0x60;
        sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x7F, 0x3F, 0x3C);
        sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x7F, 0xC0, 0x3C);
        tmpl = mission_end_fx;
        fx_spawn_template(rec, tmpl, 0);
        fx_spawn_template(rec, tmpl + 1, obj_shoot_callback);
        scratch_top -= 0x10;
        obj->next_state = 6;
        break;
    case 6:
        break;
    }

    flag = reactor_boss_active_flag;
    if (flag == 1 && mission_timer_get() <= 0 && control_rods_left > 0) {
        pursue_flag_set(0);
        mission_timer_active_set(0);
        warning_ack_set(0);
        reactor_boss_active_flag = 0;
        boss_done_flag = flag;
        obj->next_state = 5;
    }

    obj_engine_sound_update(obj);
    obj_fly_to_camera(obj);
}

extern s32 reactor_boss_active_flag;
/* Sets the mode flag reactor_boss_active_flag and programs the engine's parameters through the fn_800BF3xx setters. */
void stage_engine_init(void) {
    reactor_boss_active_flag = 1;
    warning_ack_set(0);
    eng_set_mode(4);
    set_enemies_left(8);
    pursue_flag_set(1);
    mission_timer_set(0xE10);
    mission_state_set(2);
    mission_timer_active_set(1);
}

s32 obj_spawn_at(Node *list, s32 *pos, u16 *rot, s32 mode, s32 arg4);
/* Countdown (vars.h.unk_248, steps) to the next burst: when it runs out, an effect is thrown from a random
 * point above the camera and the countdown is reset to 4..15. */
void obj_burst_tick(Object *obj) {
    Vec3 *from;
    Vec3 *to;
    SVECTOR *rot;
    s32 vx, vy, vz;
    s32 yaw;

    if (--obj->vars.reactor_control_rods_m9_boss.burst_timer <= 0) {
        from = scratch_alloc(0x10);
        to = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        vx = 0;
        vy = 0;
        vz = 0;
        yaw = rand_a_next();
        angles_to_vector(yaw, 0, rand_a_next() * 0x8C8 / 0x1000 + 0x738, &vx, &vy, &vz);
        to->x = vx >> 12;
        to->y = vy >> 12;
        to->z = (vz >> 12) - 0x60;
        from->x = to->x;
        from->y = to->y - 0x400;
        from->z = to->z;
        trace_world(8, 0xC, from, to, to);
        rot->vx = -0x400;
        rot->vy = 0;
        rot->vz = 0;
        obj_spawn_at(&obj->node, (s32 *)to, (u16 *)rot, 0, model_slot_pchr(*(s32 *)obj->asset));
        to->y = cam_pos_y >> 12;
        sound_play_at_units(SND_BURST_IMPACT | SND_GROUP(2), 0x7F, 0x3C, to);
        obj->vars.reactor_control_rods_m9_boss.burst_timer = rand_a_next() * 12 / 0x1000 + 4;
        scratch_top -= 8;
        scratch_top -= 0x10;
        scratch_top -= 0x10;
    }
}

s32 energy_mote_spawn(Object *head, s32 *pos, s16 *rot, s32 mode, s32 arg4);
void obj_fire_tick(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 angle;

    obj->vars.reactor_control_rods_m9_boss.fire_timer--;
    if (obj->vars.reactor_control_rods_m9_boss.fire_timer <= 0) {
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        angle = atan2((cam_pos_z >> 12) + 0x60, cam_pos >> 12);
        angle += rand_a_next() / 2;
        angle -= 0x400;
        fly_move(angle, rand_a_next() / 4 + 0xB38, pos + 2, pos);
        pos[0] >>= 12;
        pos[1] = -(rand_a_next() / 2 + 0x80);
        pos[2] = (pos[2] >> 12) - 0x60;
        rot[0] = 0;
        rot[1] = 0;
        rot[2] = 0;
        energy_mote_spawn(obj, pos, rot, 0, model_slot_pchr(*(s32 *)obj->asset));
        obj->vars.reactor_control_rods_m9_boss.fire_timer = rand_a_next() * 6 / 4096 + 2;
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
}

/* Accelerates words[2] by words[3] up to words[4] (never below 0), adds it to words[1],
   and sets the loop sound's pitch and volume from how far words[2] was above 0x10000. */
void obj_engine_sound_update(Object *obj) {
    s32 speed;
    s32 level;
    s32 limit;

    level = (obj->vars.reactor_control_rods_m9_boss.engine_speed - 0x10000) >> 12;
    speed = obj->vars.reactor_control_rods_m9_boss.engine_speed + obj->vars.reactor_control_rods_m9_boss.engine_accel;
    limit = obj->vars.reactor_control_rods_m9_boss.engine_speed_max;
    speed = MAX(MIN(speed, limit), 0);
    obj->vars.reactor_control_rods_m9_boss.engine_speed = speed;
    obj->vars.reactor_control_rods_m9_boss.unk_24C += speed;
    if (level < 0) {
        level = 0;
    }
    sound_set_pitch(obj->vars.reactor_control_rods_m9_boss.unk_268, obj->vars.reactor_control_rods_m9_boss.base_pitch + level * 640 / 154);
    sound_set_volume(obj->vars.reactor_control_rods_m9_boss.unk_26C, sound_volume_of(SND_PAIR(SND_REACTOR_HUM_LOOP | SND_HELD | SND_GROUP(2), SND_BOSS_ENGINE_LOOP | SND_HELD | SND_GROUP(2)), level / 154));
}

s32 arc_spawn(Node *src, void *unused, SVECTOR *rot, u32 side, s32 value, s32 sound);
/* Flying enemy near the camera: inside 0x739 units it fires the two effects at it and drops its climb speed
 * (vars.words[6]), then moves along the bearing to the camera at that speed. words[5] caps the speed, words[7]
 * accelerates it. */
void obj_fly_to_camera(Object *obj) {
    struct { s32 dz, dx; } d; /* offset to the camera (a struct keeps its loads below the speed store) */
    s32 cap, speed;
    Vec3 *pos;
    SVECTOR *rot;

    d.dz = -0x60 - (cam_pos_z >> 12);
    d.dx = -(cam_pos >> 12);
    if (isqrt(length_sq(d.dx, 0, d.dz)) < 0x739) {
        pos = (Vec3 *)scratch_top;
        scratch_top += 0x10;
        rot = (SVECTOR *)scratch_top;
        scratch_top += 8;
        pos->x = 0;
        pos->y = 0;
        pos->z = 0;
        rot->vx = 0;
        rot->vy = atan2(-d.dz, -d.dx);
        rot->vz = 0;
        arc_spawn(&obj->node, pos, rot, 0, model_slot_pchr(*(s32 *)obj->asset), 1);
        arc_spawn(&obj->node, pos, rot, 1, model_slot_pchr(*(s32 *)obj->asset), 0);
        obj->vars.reactor_control_rods_m9_boss.fly_speed = -0x30000;
        if (get_enemies_left() > 0) {
            hit_target_masked(0, 0x10, rot->vy, 0x14);
        }
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
    cap = obj->vars.reactor_control_rods_m9_boss.fly_speed_max;
    speed = obj->vars.reactor_control_rods_m9_boss.fly_speed + obj->vars.reactor_control_rods_m9_boss.fly_accel;
    obj->vars.reactor_control_rods_m9_boss.fly_speed = speed;
    speed = MAX(CLAMP_HI(speed, cap), -0x30000);
    obj->vars.reactor_control_rods_m9_boss.fly_speed = speed;
    fly_move(atan2(d.dz, d.dx), obj->vars.reactor_control_rods_m9_boss.fly_speed >> 12, &d.dz, &d.dx);
    add_displacement(d.dx, 0, d.dz);
}

void obj_shoot_at_target(Vec3 *from, s32 dist);
/* Passes the object's word at 0x18 (fixed point, 12 fraction bits) to obj_shoot_at_target as an integer. */
void obj_shoot_callback(Object *obj) {
    obj_shoot_at_target((Vec3 *)obj, *(s32 *)&obj->type.unk_0C >> 12);
}

/* Aims from `from` at the point player_position_copy gives, steps `dist` along that line and damages what it hits there. */
void obj_shoot_at_target(Vec3 *from, s32 dist) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 yaw, pitch;
    s32 dx, dy, dz;
    s16 target;

    dx = 0;
    dy = 0;
    dz = 0;
    pitch = 0;
    yaw = 0;
    target = 0;

    player_position_copy((VECTOR *)pos);
    dx = pos->x - from->x;
    dy = pos->y - from->y;
    dz = pos->z - from->z;
    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    angles_to_vector(yaw, -pitch, dist, &dx, &dy, &dz);
    pos->x = from->x + (dx >> 12);
    pos->y = from->y + (dy >> 12);
    pos->z = from->z + (dz >> 12);
    set_collide_mode(1);
    if (trace_objects(from, pos, 8, pos, &target) == 1) {
        hit_target_masked(target, 0x10, yaw, 0x7FFF);
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
}

/* Stops the object's two sound handles. */
void obj_stop_sound_pair(Object *obj) {
    sound_stop(obj->vars.snd2.sound[0]);
    sound_stop(obj->vars.snd2.sound[1]);
}

void obj_spark_burst(Object *obj, s32 angle);
void obj_spark_add_fixed(Object *obj, s32 arg);
/* 0x24C holds a 4096-per-unit value; the whole units feed both callees.
   The name "sound" comes from the snd view and is unconfirmed. */
void reactor_control_rods_m9_boss_draw(Object *obj) {
    obj_spark_burst(obj, (obj->vars.snd.sound >> 12) / 4);
    obj_spark_add_fixed(obj, -(obj->vars.snd.sound >> 12));
}

void obj_spark_emit(Object *obj, s32 angle);
/* Adds a spark record at a fixed scratch position, then runs obj_spark_emit for three angles 0x555 apart. */
void obj_spark_burst(Object *obj, s32 angle) {
    s32 *pos = scratch_alloc(0x10);
    s32 frame;
    s32 x, y, z;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    frame = model_slot_pchr(*(s32 *)obj->asset) + 0x30;
    pos[1] = -0x7E0;
    z = -0x60;
    pos[0] = 0;
    pos[2] = z;
    x = pos[0];
    y = pos[1];
    n = SPARK_COUNT;
    list = &spark_list;
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
        s->unk_12 = frame;
        s->yaw = angle;
        s->pitch = 0;
        s->roll = 0;
    }
    obj_spark_emit(obj, angle);
    obj_spark_emit(obj, angle + 0x555);
    obj_spark_emit(obj, angle + 0xAAA);
    scratch_top -= 0x10;
}

/* Emits one spark at the object's point, aimed along the given yaw, with the asset's value. */
void obj_spark_emit(Object *obj, s32 yaw) {
    s32 x, y, z;
    s32 value;

    value = model_slot_pchr(*(s32 *)obj->asset) + 0x31;
    x = 0;
    y = 0;
    z = 0;
    angles_to_vector(yaw, 0, 0x2A0, &x, &y, &z);
    x >>= 12;
    y = (y >> 12) - 0x4E0;
    z = (z >> 12) - 0x60;
    spark_add(x, y, z, yaw, 0, 0, value, 0);
}

void obj_spark_add_fixed(Object *obj, s32 arg) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 value;
    s32 n, x, y, z;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    value = model_slot_pchr(*(s32 *)obj->asset) + 0x32;
    pos->y = 0x120;
    pos->x = 0;
    z = -0x60;
    pos->z = z;
    n = SPARK_COUNT;
    x = pos->x;
    y = pos->y;
    list = &spark_list;
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
        s->yaw = arg;
        s->pitch = 0;
        s->roll = 0;
    }
    scratch_top -= 0x10;
}

void obj_start_ring_effects(s32 arg0);
void obj_start_aimed_effects(Object *obj);
extern u8 reactor_boss_asset[];
extern s16 *reactor_boss_script_data[];
extern ScriptCallEntry reactor_boss_table[2];
extern s16 *reactor_boss_script_start;
/* Spawns the mission 9 reactor control-rod boss: handlers, model, random timers, globals reset, effects and its two sounds. */
s32 reactor_control_rods_m9_boss_spawn(void) {
    Object *obj;
    s32 *pos;
    s32 *words;
    s32 handle;
    s32 result;
    ScriptCallEntry *tbl;

    result = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) reactor_control_rods_m9_boss_phase0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) reactor_control_rods_m9_boss_draw;
        obj->destructor = obj_stop_sound_pair;
        obj->asset = reactor_boss_asset;
        tbl = reactor_boss_table;
        do { } while (0);
        obj->handlers[0].unk_11 = 0;
        do { } while (0);
        obj->handlers[0].state = 0;
        do { } while (0);
        obj->handlers[1].fn = NULL;
        do { } while (0);
        obj->handlers[1].unk_11 = 0;
        do { } while (0);
        obj->handlers[1].state = 0;
        do { } while (0);
        obj->handlers[2].fn = NULL;
        do { } while (0);
        obj->handlers[2].unk_11 = 0;
        do { } while (0);
        obj->handlers[2].state = 0;
        do { } while (0);
        obj->handlers[3].unk_11 = 0;
        do { } while (0);
        obj->handlers[3].state = 0;
        do { } while (0);
        obj->callback = 0;
        do { } while (0);
        obj->call_table = tbl;
        obj->script.data = reactor_boss_script_data;
        obj->script.pc = reactor_boss_script_start;
        obj->script.unk_0A = 0;
        obj->x = 0;
        obj->y = 0;
        obj->z = -0x60000;
        obj->next_state = 0;
        obj->vars.reactor_control_rods_m9_boss.burst_timer = ((s32) (rand_a_next() * 0xC) / 4096) + 4;
        obj->vars.reactor_control_rods_m9_boss.fire_timer = ((s32) (rand_a_next() * 6) / 4096) + 2;
        words = (s32 *) &obj->vars;
        words[2] = 0x10000;
        words[4] = 0x10000;
        words[1] = 0;
        words[3] = 0;
        words[5] = 0;
        words[6] = 0;
        words[7] = 0x1000;
        reactor_boss_active_flag = 0;
        boss_done_flag = 0;
        control_rods_left = 0;
        obj_start_ring_effects((s32) obj);
        obj_start_aimed_effects(obj);
        handle = sound_start(SND_PAIR(SND_BOSS_SPAWN_LOOP | SND_HELD | SND_GROUP(2), SND_BOSS_SPAWN_LOOP_ALT | SND_HELD | SND_GROUP(2)), 0x7F, 0, 0);
        obj->vars.snd2.sound[0] = handle;
        pos = &obj->x;
        *(s16 *) &obj->vars.enemy.sound = sound_get_pitch(handle);
        sound_attach(obj->vars.snd2.sound[0], pos, NULL);
        sound_set_flag_bit2(obj->vars.snd2.sound[0], 1);
        handle = sound_start(SND_PAIR(SND_REACTOR_HUM_LOOP | SND_HELD | SND_GROUP(2), SND_BOSS_ENGINE_LOOP | SND_HELD | SND_GROUP(2)), 0, 0, 0);
        obj->vars.snd2.sound[1] = handle;
        sound_attach(handle, pos, NULL);
        sound_set_flag_bit2(obj->vars.snd2.sound[1], 1);
        show_line((s32) "#2Destroy all controlsticks, and stop them now.\xA1");
        result = 1;
    }
    return result;
}

extern RingEffectPoint ring_effect_points[];
s32 pylon_spawn_child(Object *parent, Vec3 *pos, s16 *rot, s32 index);
void obj_start_ring_effects(s32 arg0) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    s32 i = 0;

    do {
        pos->x = (ring_effect_points[i].x << 12) >> 12;
        pos->y = (ring_effect_points[i].y << 12) >> 12;
        pos->z = (ring_effect_points[i].z << 12) >> 12;
        rot[0] = 0;
        rot[1] = i << 9;
        rot[2] = 0;
        pylon_spawn_child((Object *)arg0, pos, rot, i);
        i++;
    } while (i < 8);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

extern EffectOffset aimed_effect_points[8];
s32 obj_spawn_part(Object *parent, Vec3 *pos, SVECTOR *rot, s32 kind);
/* Starts the eight effects of the table around the object, each aimed from its point. */
void obj_start_aimed_effects(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 i;
    s32 yaw;
    s32 pitch;
    s32 dx, dy, dz;

    for (i = 0; i < 8; i++) {
        pos->x = (aimed_effect_points[i].x << 12) >> 12;
        yaw = 0;
        pitch = 0;
        dx = 0;
        dy = 0;
        dz = 0;
        pos->y = (aimed_effect_points[i].y << 12) >> 12;
        pos->z = (aimed_effect_points[i].z << 12) >> 12;
        vector_to_angles(pos->x, 0x1000, pos->z + 0x60, &yaw, &pitch);
        angles_to_vector(yaw, -pitch, 0x390, &dx, &dy, &dz);
        pos->x += dx >> 12;
        pos->y += dy >> 12;
        pos->z += dz >> 12;
        rot->vx = pitch;
        rot->vy = yaw;
        rot->vz = 0;
        obj_spawn_part(obj, pos, rot, i);
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 reactor_control_rods_m9_boss_update(void) {
    return reactor_control_rods_m9_boss_spawn();
}

void pylon_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Reads the next 16-bit opcode from the object's stream (unk_1C.unk_04). When health is
   zero or below, the stream jumps to the target stored in the type's table at unk_1C.data. */
void obj_stream_read_op(Object *obj) {
    s16 *stream;
    s32 op;
    s16 **table;

    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    op = *stream;
    if (obj->health <= 0) {
        table = (s16 **)obj->script.data;
        obj->script.pc = table[op];
    }
}

extern DeathPiece enemy_death_points[6];
void enemy_death_piece(Object *obj, DeathPiece *from, DeathPiece *to, s32 i);
void enemy_kill(Object *obj) {
    DeathPiece *from = scratch_alloc(0x10);
    DeathPiece *to = scratch_alloc(0x10);
    s32 i;
    s32 fl;

    for (i = 0; i < 6;) {
        *from = enemy_death_points[i % 6];
        *to = enemy_death_points[(i + 1) % 6];
        enemy_death_piece(obj, from, to, i);
        i++;
    }
    obj->unk_17A = 0;
    fl = obj->flags;
    obj->flags = fl & ~4;
    add_score(obj->score);
    add_kill_count(1);
    obj->score = 0;
    set_enemies_left(get_enemies_left() - 1);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

void enemy_death_piece(Object *obj, DeathPiece *from, DeathPiece *to, s32 i) {
    s32 *delta;
    s16 *rot;
    s32 yaw;
    s32 pitch;
    s32 rot_pitch;
    s32 rot_yaw;
    s32 jitter;
    s32 spread;

    // delta: first from-to offset, then the midpoint of from and to
    delta = scratch_alloc(0x10);
    rot = scratch_alloc(0x8);

    pitch = obj->pitch;
    yaw = obj->yaw;
    rotate_xz_twice(yaw, -pitch, &from->a, &from->b, &from->c);
    rotate_xz_twice(yaw, -pitch, &to->a, &to->b, &to->c);

    delta[0] = to->a - from->a;
    delta[1] = to->b - from->b;
    delta[2] = to->c - from->c;
    vector_to_angles(delta[0], delta[1], delta[2], &yaw, &pitch);

    rot_pitch = pitch;
    rot_yaw = yaw;
    rot[2] = 0;
    rot[0] = rot_pitch;
    rot[1] = rot_yaw - 0x400;

    delta[0] = (obj->x >> 12) + ((to->a + from->a) / 2);
    delta[1] = (obj->y >> 12) + ((to->b + from->b) / 2);
    delta[2] = (obj->z >> 12) + ((to->c + from->c) / 2);

    obj_spawn(obj, delta, rot, 0, model_slot_pchr(*(s32 *)obj->asset));

    if (!(i & 1)) {
        from->a += obj->x >> 12;
        spread = obj->y;
        jitter = rand_a_next() * 0x174;
        spread >>= 12;
        if (jitter < 0) {
            jitter += 0xFFF;
        }
        from->b += spread - (jitter >> 12);
        from->c += obj->z >> 12;
        spawn_effect(from->a, from->b, from->c, 0x80007F00);
    }

    scratch_top -= 0x8;
    scratch_top -= 0x10;
}

void pylon_update(Object *obj, ObjHandler *handler) {
    s16 state;
    s32 flags; /* s32 read keeps the original lh (a s16 read compiles to lhu) */

    obj->vz = 0;
    obj->vx = 0;
    if (obj->script_flag != 0) {
        state = obj->next_state;
        if (state == handler->state) {
            switch (state) {
            case 0:
            case 2:
            case 4:
            case 6:
                break;
            case 1:
                obj->next_state = 2;
                break;
            case 3:
                obj->next_state = 4;
                break;
            case 5:
                obj->next_state = 6;
                flags = obj->flags;
                obj->flags = flags & 0xFFDF;
                break;
            default:
                obj->next_state = 0;
                break;
            }
        }
    }
    obj_script_step(obj, handler);
}

extern s32 control_rods_left;
void enemy_sound_start(Object *obj) {
    s32 handle;

    if (obj->vars.pylon_spawn_child_obj.unused_250 == 0) {
        handle = sound_start(SND_PAIR(SND_ENEMY_IDLE_LOOP | SND_HELD | SND_GROUP(1), SND_ENEMY_IDLE_LOOP_ALT | SND_HELD | SND_GROUP(1)), 0x7F, 0, 0);
        obj->vars.pylon_spawn_child_obj.unused_250 = handle;
        sound_attach(handle, &obj->x, NULL);
        sound_set_flag_bit2(obj->vars.pylon_spawn_child_obj.unused_250, 1);
        control_rods_left -= 1;
    }
}

/* When the object holds a sound handle at 0x250, stops it and plays sound 0x3106 at its position. */
void enemy_sound_stop_cue(Object *obj) {
    s32 handle = obj->vars.pylon_spawn_child_obj.unused_250;
    Vec3 *pos;

    if (handle != 0) {
        pos = scratch_alloc(0x10);
        sound_stop(handle);
        obj->vars.pylon_spawn_child_obj.unused_250 = 0;
        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        sound_play_at_units(SND_ENEMY_SHUTDOWN | SND_GROUP(1), 0x7F, 0x3C, pos);
        scratch_top -= 0x10;
    }
}

void pylon_phase2(Object *obj) {
    s32 damage;
    u8 cooldown;
    s32 flags;

    damage = (s16) obj_hit_damage(obj->index);
    if (obj->hit < 0) {
        obj->hit = 0;
    }
    cooldown = obj->hit_cooldown;
    if (cooldown != 0) {
        /* count down one step; 0xFF wraps the u8 */
        obj->hit_cooldown = cooldown + 0xFF;
    }
    if ((reactor_boss_active_flag == 1) && (damage > 0) && (obj->next_state == 0)) {
        if (obj->hit == 0) {
            obj->hit = 1;
        }
        obj->health -= damage;
        obj->hit_from = obj_hit_from(obj->index);
        obj->hit_type = obj_hit_type(obj->index);
        if (obj->hit_cooldown == 0) {
            obj->hit_cooldown = obj->hit_cooldown_max;
        }
    }
    obj_hit_clear(obj->index);
    flags = obj->flags;
    if ((((u32) flags) >> 5) & 1) {
        obj_block_lerp(obj, 0);
    }
}

/* Stops the sound handle at 0x250. */
void enemy_sound_stop(Object *obj) {
    sound_stop(obj->vars.pylon_spawn_child_obj.unused_250);
}

void obj_size_from_type(Object *obj);
void obj_spark_above(Object *obj);
void obj_spark_add_frame(Object *obj);
void pylon_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 value = obj_type_range_value(obj, 0);
    s32 colour;
    u16 roll;
    s32 pitch;

    if (obj->hit <= 0) {
        colour = 0;
    } else {
        colour = 0x60C0FF;
        pitch = 0;
    }
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    roll = obj->roll;
    rot->vz = roll;
    spark_add_u(pos->x, pos->y, pos->z, rot->vy, rot->vx, roll, value, colour);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    obj_size_from_type(obj);
    obj_spark_above(obj);
    obj_spark_add_frame(obj);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/*
 * Maps the object's type-link range (unk_0C..unk_0E) through the current
 * position: a single point when both ends match, otherwise a blend of the
 * two ends by a weight derived from unk_08 and unk_0A.
 * The args[] array is a dead store to the stack that the original keeps;
 * dropping it changes the frame.
 */
s32 obj_type_range_value(Object *obj, s32 arg1) {
    s32 base = arg1 + model_slot_pchr(*(s32 *)obj->asset);
    s16 first = obj->type.unk_0C;
    s32 args[4];

    if (first != obj->type.unk_0E) {
        args[0] = first + base;
        args[1] = obj->type.unk_0E + base;
        args[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        args[3] = 0x1000 - args[2];
        return pchr_blend(args[0], args[1], args[2], 1);
    }
    return first + base;
}

extern s32 obj_size_table[];
void obj_size_from_type(Object *obj) {
    s16 result;
    s32 *tbl;
    s32 *entry_b;
    s32 idx_a;
    s32 idx_b;
    s32 frac;
    s32 mixed;
    s32 hi;

    idx_a = obj->type.unk_0C - 8;
    idx_b = obj->type.unk_0E - 8;
    if (idx_a == idx_b) {
        tbl = obj_size_table;
        entry_b = (s32 *)((idx_b * 4) + (u8 *)tbl);
        obj->vars.pylon_spawn_child_obj.unk_24A = (s16) ((s32) *entry_b / 2);
        obj->vars.pylon_spawn_child_obj.unk_24C = (s16) ((*entry_b << 0xC) / 528);
        if (idx_b == 0) {
            result = 0xAAA;
            goto store;
        }
    } else {
        frac = (s32) ((obj->type.unk_0A + 1) << 0xC) / (s16) obj->type.blend_duration;
        hi = obj_size_table[idx_a];
        hi = hi * frac;
        mixed = hi + (obj_size_table[idx_b] * (0x1000 - frac));
        hi = mixed >> 0xC;
        obj->vars.pylon_spawn_child_obj.unk_24A = (s16) ((s32) (hi + ((u32) mixed >> 0x1F)) >> 1);
        result = (hi << 0xC) / 528;
store:
        obj->vars.pylon_spawn_child_obj.unk_24C = result;
    }
}

/* Adds a spark above the object, coloured from its unk_24C, with the sound-table value added to its id. */
void obj_spark_above(Object *obj) {
    Vec3 *pos = (Vec3 *)scratch_top;
    s32 c;
    s32 v;
    s32 z;
    s32 value;

    scratch_top += 0x10;
    scratch_top += 8;
    value = model_slot_pchr(*(s32 *)obj->asset) + obj->vars.pylon_spawn_child_obj.child_index;
    c = ((u16)obj->vars.pylon_spawn_child_obj.unk_24C << 16) >> 21;
    v = c;
    if (c == 0) {
        v = 1;
    }
    pos->x = obj->x >> 12;
    pos->y = (obj->y >> 12) + 0x60;
    z = obj->z >> 12;
    pos->z = z;
    spark_add(pos->x, pos->y, z, 0, 0, 0, value, (v << 16) | (c << 8) | c);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void obj_spark_add_frame(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 frame;
    s32 level, blue, colour;
    s32 x, y, z, n, off, ty;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    frame = model_slot_pchr(*(s32 *)obj->asset) + 0xE;
    level = (s16)obj->vars.pylon_spawn_child_obj.unk_24C >> 5;
    blue = level;
    if (blue == 0) {
        blue = 1;
    }
    pos->x = obj->x >> 12;
    ty = obj->y >> 12;
    off = obj->vars.pylon_spawn_child_obj.unk_24A - 0x30;
    pos->y = ty - off;
    x = pos->x;
    colour = blue << 16 | level << 8 | level;
    z = obj->z >> 12;
    y = ((volatile s32 *)pos)[1];
    pos->z = z;
    n = SPARK_COUNT;
    list = &spark_list;
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
        s->unk_12 = frame;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
    scratch_top -= 0x10;
}

extern PylonAsset pylon_asset;
extern ScriptCallEntry pylon_call_table[];
extern StateEntry pylon_state_table[];
extern s16 *pylon_script_data[];
extern PylonLinkWord pylon_link_word;
extern s16 *pylon_data[];
void obj_init_pose(Object *obj, s32 *pos, u16 *rot, s32 flags);
/* Spawns one pylon of the ring around parent; returns 1 if made. */
s32 pylon_spawn_child(Object *parent, Vec3 *pos, s16 *rot, s32 index) {
    Object *obj;
    s32 made = 0;
    s16 *link_word;

    obj = obj_new();
    if (obj != NULL) {
        made = 1;
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = (void *)pylon_phase0;
        obj->handlers[1].fn = pylon_update;
        obj->handlers[2].fn = (void *)pylon_phase2;
        obj->handlers[3].fn = (void *)pylon_draw;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = (s32)enemy_sound_stop;
        obj->kind = parent->kind;
        pylon_asset = *(PylonAsset *)parent->asset;
        obj->asset = &pylon_asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = pylon_call_table;
        obj->state_table = pylon_state_table;
        obj->unk_1C6 = 0;
        link_word = pylon_link_word.v;
        obj->script.data = pylon_script_data;
        obj->script.unk_0A = 0;
        obj->script.pc = link_word;
        script_start((Script *)obj, pylon_data[0], (s32)pylon_data);
        obj_init_pose(obj, (s32 *)pos, (u16 *)rot, 0x225);
        obj_set_part_bounds(obj, 8, 0x1000);
        obj->vars.pylon_spawn_child_obj.unk_24A = 0x108;
        obj->vars.pylon_spawn_child_obj.child_index = index;
        obj->vars.pylon_spawn_child_obj.unk_24C = 0xAAA;
        obj->vars.pylon_spawn_child_obj.unused_250 = 0;
        control_rods_left = ((PylonCount *)&control_rods_left)->n + 1;
    }
    return made;
}

/* Resets an object's state and sets its pose. pos holds x/y/z as integers (stored <<12); rot holds pitch/yaw/roll. */
void obj_init_pose(Object *obj, s32 *pos, u16 *rot, s32 flags) {
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0x80);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj_set_flags(obj, flags);
    obj->health = 0x7D0;
    obj->score = 0x7D0;
    obj->damage = 0;
    obj->unk_17B = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    obj->placement = NULL;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

void obj_launch_update(Object *obj, ObjHandler *h) {
    s32 pitch = (s16)obj->pitch;
    s32 vy = obj->vy;
    s32 vx = obj->vx;
    s32 vz = obj->vz;
    s16 cnt;

    obj->x += vx;
    obj->y += vy;
    obj->z += vz;
    pitch += 0x1C;
    obj->vy = vy;
    obj->pitch = pitch;
    cnt = obj->vars.obj.frame_count + 1;
    obj->vars.obj.frame_count = cnt;
    if (cnt >= 0x18) {
        obj_free(obj);
    }
}

void obj_spark_list_add(Object *obj);
/* Calls obj_spark_list_add unless the object's 16-bit state at 0x24C is in a
   valid range: 12..17 and divisible by 3, or 18 and up and even. */
void obj_spark_check(Object *obj, ObjHandler *handler) {
    u16 raw;
    s32 state;

    raw = obj->vars.obj.frame_count;
    state = (s16) raw;
    if (state >= 0xC) {
        if (state < 0x12) {
            if (state != (state / 3) * 3) {
                obj_spark_list_add(obj);
            }
        } else if (state & 1) {
            obj_spark_list_add(obj);
        }
    } else {
        obj_spark_list_add(obj);
    }
}

void obj_spark_list_add(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;
    s32 level = obj->vars.obj.unk_248 + 0xD;
    s32 pitch;
    s32 x, y, z;
    u16 roll;
    s32 a, b;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    list = &spark_list;
    a = rot[0];
    b = rot[1];
    x = pos->x;
    y = pos->y;
    z = pos->z;
    n = SPARK_COUNT;
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
        s->unk_12 = level;
        s->yaw = b;
        s->pitch = a;
        s->roll = roll;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void obj_launch(Object *obj, s32 unused);
s32 obj_spawn(s32 ctx, s32 *pos, u16 *rot, s32 mode, s32 flags) {
    Object *obj;
    s32 spawned = 0;

    if (mode >= 0) {
        if (mode <= 0) {
            obj = obj_new();
            if (obj != NULL) {
                list_insert_after((Node *) get_obj_list_actors(), &obj->node);
                obj_hit_clear(obj->index);
                obj_hit_flag_set(obj->index, 0);
                obj->x = pos[0] << 12;
                obj->y = pos[1] << 12;
                obj->z = pos[2] << 12;
                obj->pitch = rot[0];
                obj->yaw = rot[1];
                obj->roll = rot[2];
                obj->vars.obj.unk_248 = flags;
                obj->vars.obj.mode = mode;
                if (mode == 0) {
                    obj_launch(obj, ctx);
                }
                spawned = 1;
            }
        }
    }
    return spawned;
}

void obj_launch_update(Object *obj, ObjHandler *h);
void obj_spark_check(Object *obj, ObjHandler *handler);
/* Resets the object's handlers and state, then sets its speed and velocity from its yaw and pitch
 * (angles_to_vector with length 0x14). */
void obj_launch(Object *obj, s32 unused) {
    s32 vel[3];
    s32 vx;
    s32 vy;
    s32 vz;

    scratch_alloc(0x10);
    vel[0] = 0;
    vel[1] = 0;
    vel[2] = 0;
    obj->handlers[1].fn = obj_launch_update;
    obj->handlers[3].fn = obj_spark_check;
    obj->speed = 0x14;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.obj.frame_count = 0;
    obj->damage = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x14, &vel[0], &vel[1], &vel[2]);
    vx = vel[0];
    vy = vel[1];
    vz = vel[2];
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    scratch_top -= 0x10;
}

void obj_part_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

Object *boss_laser_spawn(Node *list, Vec3 *pos, SVECTOR *rot, s32 kind, s32 param);
/* Once (while vars.words[6] is 0): turns a (0, 0, 0x138) offset by the object's angles, adds its position and stores boss_laser_spawn's result. */
void obj_boss_laser_init(Object *obj) {
    Vec3 *pos;
    SVECTOR *rot;

    if (obj->vars.words[6] == 0) {
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        pos->x = 0;
        pos->y = 0;
        pos->z = 0x138;
        rot->vx = obj->pitch;
        rot->vy = obj->yaw;
        rot->vz = obj->roll;
        rotate_xz_twice(rot->vy, -rot->vx, &pos->x, &pos->y, &pos->z);
        pos->x = pos->x + (obj->x >> 12);
        pos->y = pos->y + (obj->y >> 12);
        pos->z = pos->z + (obj->z >> 12);
        obj->vars.words[6] = (s32)boss_laser_spawn(&obj->node, pos, rot, 0, model_slot_pchr(*(s32 *)obj->asset));
        scratch_top -= 0x8;
        scratch_top -= 0x10;
    }
}

/* Reads the next halfword of the object's script cursor (0x20). When vars.words[6] (0x260) is
 * nonzero, the halfword indexes the object's table (0x1C) and the cursor jumps to that entry. */
void obj_script_jump_linked(Object *obj) {
    s16 *cursor;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->vars.words[6] != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

extern s32 reactor_boss_active_flag;
/* Reads the next halfword of the object's script cursor (0x20). When reactor_boss_active_flag is 1, the halfword
 * indexes the object's table (0x1C) and the cursor jumps to that entry. */
void obj_script_jump_on_flag(Object *obj) {
    s16 *cursor;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    if (reactor_boss_active_flag == 1) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Reads the cursor's (threshold, index) pair; when the player's horizontal distance from the object's
 * aim point is more than `threshold`, the cursor jumps to table entry `index`. */
void obj_script_jump_far(Object *obj) {
    VECTOR *delta = scratch_alloc(0x10);
    s16 *cursor;
    s32 threshold;
    s32 index;
    s32 dist;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = ((s16 *)cursor)[0];
    obj->script.pc = cursor + 2;
    index = ((s16 *)cursor)[1];
    player_position_copy(delta);
    delta->vz -= (s16)obj->vars.part.offset_z;
    delta->vx -= obj->vars.h.unk_24C;
    dist = isqrt(length_sq(delta->vx, 0, delta->vz));
    if (threshold < dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
    scratch_top -= 0x10;
}

/* Reads the cursor's (threshold, index) pair; when the player's horizontal distance from the object's
 * aim point is at most `threshold`, the cursor jumps to table entry `index`. */
void obj_script_jump_near(Object *obj) {
    VECTOR *delta = scratch_alloc(0x10);
    s16 *cursor;
    s32 threshold;
    s32 index;
    s32 dist;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = ((s16 *)cursor)[0];
    obj->script.pc = cursor + 2;
    index = ((s16 *)cursor)[1];
    player_position_copy(delta);
    delta->vz -= (s16)obj->vars.part.offset_z;
    delta->vx -= obj->vars.h.unk_24C;
    dist = isqrt(length_sq(delta->vx, 0, delta->vz));
    if (threshold >= dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
    scratch_top -= 0x10;
}

void limb_solve_joint(Object *obj);
void obj_move_sound_update(Object *obj, ObjHandler *handler) {
    s32 cellX;
    s32 cellY;
    s32 cellZ;

    cellX = obj->x >> 12;
    cellY = obj->y >> 12;
    cellZ = obj->z >> 12;
    obj_script_step(obj, handler);
    if (cellX != (obj->x >> 12) || cellY != (obj->y >> 12) || cellZ != (obj->z >> 12)) {
        if (obj->vars.enemy.sound == 0) {
            obj->vars.enemy.sound = sound_start(SND_PAIR(SND_ENEMY_MOVE_LOOP | SND_HELD | SND_GROUP(2), SND_OBJECT_MOVE_LOOP | SND_HELD | SND_GROUP(2)), 0x7F, 0, 0);
            sound_attach(obj->vars.enemy.sound, &obj->x, NULL);
            sound_set_flag_bit2(obj->vars.enemy.sound, 1);
        }
    } else if (obj->vars.enemy.sound != 0) {
        sound_stop(obj->vars.enemy.sound);
        obj->vars.enemy.sound = 0;
    }
    limb_solve_joint(obj);
}

static inline HomingVars *homing_vars(Object *obj) {
    return (HomingVars *)&obj->vars;
}
void homing_move(Object *obj) {
    s32 yaw = 0;
    s32 pitch = 0;
    s32 *vec;
    s32 dist;
    s32 speed;

    vec = scratch_alloc(0x10);
    vec[0] = homing_vars(obj)->target[0] - homing_vars(obj)->anchor[0];
    vec[1] = homing_vars(obj)->target[1] - homing_vars(obj)->anchor[1];
    vec[2] = homing_vars(obj)->target[2] - homing_vars(obj)->anchor[2];
    dist = isqrt(length_sq(vec[0], vec[1], vec[2])) << 12;

    speed = obj->speed;
    if (ABS(dist - speed) <= 0x8000) {
        obj->speed = dist;
    } else {
        /* hard registers: the step stays in v0 and the new speed in v1 */
        register s32 step asm("$2") = dist - speed;
        register s32 new_speed asm("$3");
        if (step < 0) {
            step = -0x8000;
        } else {
            step = 0x8000;
        }
        new_speed = speed + step;
        obj->speed = new_speed;
    }

    vector_to_angles(vec[0], vec[1], vec[2], &yaw, &pitch);
    obj->unk_226[3] = angle_approach(obj->unk_226[3], yaw, 3);
    obj->unk_226[4] = angle_approach(obj->unk_226[4], pitch, 2);
    angles_to_vector(obj->unk_226[3], -obj->unk_226[4], obj->speed >> 12,
                     &vec[0], &vec[1], &vec[2]);

    obj->x = vec[0] + (homing_vars(obj)->anchor[0] << 12);
    obj->y = vec[1] + (homing_vars(obj)->anchor[1] << 12);
    obj->z = vec[2] + (homing_vars(obj)->anchor[2] << 12);
    obj->yaw = obj->unk_226[3];
    obj->pitch = angle_approach(obj->pitch, homing_vars(obj)->target_pitch, 2);

    scratch_top -= 0x10;
}

/* Flying object: speed scales with player distance, orbit kept above a floor height. */
void homing_steer_player(Object *obj) {
    VECTOR *player = (VECTOR *)scratch_alloc(0x10);
    VECTOR *delta = (VECTOR *)scratch_alloc(0x10);
    s32 yaw, pitch;
    s32 vx, vy, vz;
    s32 dist;
    s32 cur;
    s32 diff;
    s32 radius;
    s32 speed_scale;
    s32 y;
    s32 speed;

    player_position_copy(player);
    delta->vx = player->vx - obj->vars.h.unk_24C;
    delta->vy = player->vy - (s16)obj->vars.part.offset_y;
    delta->vz = player->vz - (s16)obj->vars.part.offset_z;
    dist = MIN(isqrt(length_sq(delta->vx, delta->vy, delta->vz)), 0xA80);
    vx = 0;
    vy = 0;
    vz = 0;
    yaw = 0;
    pitch = 0;
    cur = obj->speed;
    speed_scale = 0x669;
    FAKE_OPAQUE(speed_scale);
    radius = 0x390;
    dist = (dist * speed_scale) / 0xA80;
    speed = dist;
    if (speed < 0xE4) {
        speed = 0xE4;
    }
    dist = speed << 12;
    diff = dist - cur;
    if (diff >= 0 ? diff <= 0x8000 : cur - dist <= 0x8000) {
        obj->speed = dist;
    } else {
        diff = cur + (dist - cur < 0 ? -0x8000 : 0x8000);
        obj->speed = diff;
    }
    vector_to_angles(delta->vx, delta->vy, delta->vz, &yaw, &pitch);
    obj->unk_226[3] = angle_approach(obj->unk_226[3], yaw, 3);
    obj->unk_226[4] = angle_approach(obj->unk_226[4], pitch, 2);
    angles_to_vector(obj->unk_226[3], -obj->unk_226[4], obj->speed >> 12, &vx, &vy, &vz);
    delta->vx = vx >> 12;
    delta->vy = vy >> 12;
    delta->vz = vz >> 12;
    dist = isqrt(length_sq(delta->vx, 0, delta->vz));
    if (dist < radius / 4) {
        fly_move(obj->unk_226[3], radius / 4, &vz, &vx);
        delta->vx = vx >> 12;
        delta->vz = vz >> 12;
    }
    y = delta->vy;
    if (y < (s32)((u32)radius >> 1)) {
        y = (u32)radius >> 1;
    }
    delta->vy = y;
    obj->x = (delta->vx + obj->vars.h.unk_24C) << 12;
    obj->y = (delta->vy + (s16)obj->vars.part.offset_y) << 12;
    obj->z = (delta->vz + (s16)obj->vars.part.offset_z) << 12;
    delta->vx = player->vx - (obj->x >> 12);
    delta->vy = player->vy - (obj->y >> 12);
    delta->vz = player->vz - (obj->z >> 12);
    vector_to_angles(delta->vx, delta->vy, delta->vz, &yaw, &pitch);
    obj->yaw = obj->unk_226[3];
    obj->pitch = angle_approach(obj->pitch, pitch, 2);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

/* Two-segment limb IK: places the joint between root and obj->pos, segment length 912 each half-span, then aims both segments. */
void limb_solve_joint(Object *obj) {
    s32 angle[2];
    VECTOR v;
    s32 midX, midY, midZ;
    s32 rootY, rootZ;
    s32 len;
    s32 jointX, jointY, jointZ;

    midX = (obj->vars.limb.root[0] + (obj->x >> 12)) / 2;
    rootY = obj->vars.limb.root[1];
    rootZ = obj->vars.limb.root[2];
    midY = (rootY + (obj->y >> 12)) / 2;
    v.vx = midX - obj->vars.limb.root[0];
    v.vy = midY - obj->vars.limb.root[1];
    midZ = (rootZ + (obj->z >> 12)) / 2;
    v.vz = midZ - obj->vars.limb.root[2];
    angle[0] = 0;
    angle[1] = 0;
    /* joint offset from the midpoint: sqrt(912^2 - |half span|^2) */
    len = isqrt(0xCB100 - length_sq(v.vx, v.vy, v.vz));
    vector_to_angles(v.vx, v.vy, v.vz, &angle[0], &angle[1]);
    angles_to_vector(angle[0], -(angle[1] + 0x400), len, &v.vx, &v.vy, &v.vz);
    jointX = (v.vx >> 12) + midX;
    v.vx = jointX;
    obj->vars.limb.joint[0] = jointX;
    jointY = (v.vy >> 12) + midY;
    v.vy = jointY;
    obj->vars.limb.joint[1] = jointY;
    jointZ = (v.vz >> 12) + midZ;
    v.vz = jointZ;
    obj->vars.limb.joint[2] = jointZ;
    vector_to_angles(jointX - obj->vars.limb.root[0], jointY - obj->vars.limb.root[1], jointZ - obj->vars.limb.root[2], &angle[0], &angle[1]);
    obj->vars.limb.upper_yaw = angle[0];
    obj->vars.limb.upper_pitch = angle[1];
    vector_to_angles((obj->x >> 12) - v.vx, (obj->y >> 12) - v.vy, (obj->z >> 12) - v.vz, &angle[0], &angle[1]);
    obj->vars.limb.lower_yaw = angle[0];
    obj->vars.limb.lower_pitch = angle[1];
}

extern s32 boss_done_flag;
/* When reactor_boss_active_flag is 0, runs obj_hit_clear on the object's index; when boss_done_flag is 1, zeroes the health and
   unk_188 (the passed-to-add_score-on-death word). Then runs obj_state_run on the object. */
void obj_hit_handler(Object *obj, ObjHandler *handler) {
    if (reactor_boss_active_flag == 0) {
        obj_hit_clear(obj->index);
    }
    if (boss_done_flag == 1) {
        obj->health = 0;
        obj->score = 0;
    }
    obj_state_run(obj, handler);
}

void obj_effect_at_offset(Object *obj);
void spawn_effect_dir(Pos3 *origin, s16 *angles, s32 scale);
s32 burst_update(Object *obj) {
    register Pos3 *origin asm("$4");
    register s16 *angles asm("$5");
    s32 alive = 1;

    if (obj->vars.burst.timer == 0) {
        obj->unk_17A = 0;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        if (obj->vars.burst.child != NULL) {
            pair_release_child(obj->vars.burst.child);
            obj->vars.burst.child = NULL;
        }
        if (boss_done_flag == 0) {
            msg_show_slot(6, 0x78);
            mission_timer_set(mission_timer_get() + 0x4B0);
        }
        obj_effect_at_offset(obj);
    } else if (obj->vars.burst.timer < 7 && !(obj->vars.burst.timer & 1)) {
        origin = (Pos3 *) scratch_top;
        origin->x = obj->vars.burst.first_pos[0];
        origin->y = obj->vars.burst.first_pos[1];
        origin->z = obj->vars.burst.first_pos[2];
        scratch_top += 0x10;
        angles = (s16 *) scratch_top;
        scratch_top += 8;
        angles[0] = obj->vars.burst.first_pitch;
        angles[1] = obj->vars.burst.first_yaw;
        angles[2] = 0;
        spawn_effect_dir(origin, angles, ((4 - obj->vars.burst.timer / 2) << 12) / 3);
        scratch_top -= 8;
        scratch_top -= 0x10;
    } else if (obj->vars.burst.timer < 15 && !(obj->vars.burst.timer & 1)) {
        origin = (Pos3 *) scratch_top;
        origin->x = obj->vars.burst.second_pos[0];
        origin->y = obj->vars.burst.second_pos[1];
        origin->z = obj->vars.burst.second_pos[2];
        scratch_top += 0x10;
        angles = (s16 *) scratch_top;
        scratch_top += 8;
        angles[0] = obj->vars.burst.second_pitch;
        angles[1] = obj->vars.burst.second_yaw;
        angles[2] = 0;
        spawn_effect_dir(origin, angles, ((4 - (obj->vars.burst.timer - 6) / 2) << 12) / 3);
        scratch_top -= 8;
        scratch_top -= 0x10;
    } else if (obj->vars.burst.timer >= 16) {
        obj_free(obj);
        alive = 0;
    }
    obj->vars.burst.timer++;
    return alive;
}

/* Spawns an effect at the object's position, offset by a vector (0, -0xF, 0x96) turned by the object's yaw and
 * negated pitch. */
void obj_effect_at_offset(Object *obj) {
    Vec3 *offset = scratch_alloc(0x10);

    offset->y = -0xF;
    offset->x = 0;
    offset->z = 0x96;
    rotate_xz_twice(obj->yaw, -obj->pitch, &offset->x, &offset->y, &offset->z);
    offset->x += obj->x >> 12;
    offset->y += obj->y >> 12;
    offset->z += obj->z >> 12;
    spawn_effect(offset->x, offset->y, offset->z, 0x80007F00);
    scratch_top -= 0x10;
}

void spawn_effect_dir(Pos3 *origin, s16 *angles, s32 scale) {
    Pos3 v;
    s32 x, y, z;

    v.x = 0;
    v.y = 0;
    v.z = (scale * 0x390) >> 12;
    rotate_xz_twice(angles[1], -angles[0], &v.x, &v.y, &v.z);
    x = v.x + origin->x;
    y = v.y + origin->y;
    z = v.z + origin->z;
    v.x = x;
    v.y = y;
    v.z = z;
    spawn_effect(x, y, z, 0x80000000);
}

void obj_destructor_stop_sound(Object *obj) {
    sound_stop(obj->vars.enemy.sound);
}

void obj_mount_sparks(Object *obj, s32 colour);
void obj_hit_spark(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 value = model_slot_pchr(*(s32 *)obj->asset) + 0x11;
    s32 colour;
    u16 roll;
    s32 pitch;

    if (obj->hit <= 0) {
        colour = 0;
    } else {
        colour = 0x60C0FF;
        pitch = 0;
    }
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    roll = obj->roll;
    rot->vz = roll;
    spark_add_u(pos->x, pos->y, pos->z, rot->vy, rot->vx, roll, value, colour);
    obj_mount_sparks(obj, colour);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Emits two sparks from the object's two mounts, both with the asset's value + 0x10. */
void obj_mount_sparks(Object *obj, s32 colour) {
    SparkMount *mounts = (SparkMount *)&obj->vars.words[1];
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    s32 value;

    value = model_slot_pchr(*(s32 *)obj->asset) + 0x10;
    pos[0] = mounts[0].x;
    pos[1] = mounts[0].y;
    pos[2] = mounts[0].z;
    rot[0] = -mounts[0].rx;
    rot[1] = mounts[0].ry;
    rot[2] = 0;
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], 0, value, colour);

    pos[0] = mounts[1].x;
    pos[1] = mounts[1].y;
    pos[2] = mounts[1].z;
    rot[0] = -mounts[1].rx;
    rot[1] = mounts[1].ry;
    rot[2] = 0;
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], 0, value, colour);

    scratch_top -= 8;
    scratch_top -= 0x10;
}

void obj_move_sound_update(Object *obj, ObjHandler *handler);
void obj_hit_spark(Object *obj);
s32 burst_update(Object *obj);
void obj_init_pose_b(Object *obj, s32 *pos, u16 *rot, s32 flags);
extern Words3_8011CDB8 part_asset_buf;
extern s16 *part_scripts[];
extern s32 part_kind_params[][4];
extern s16 *D_8011CEA8[];
extern s16 *D_8011CEC0;
extern ScriptCallEntry D_8011CEC4[];
extern StateEntry D_8011CEF4[];
s32 obj_spawn_part(Object *parent, Vec3 *pos, SVECTOR *rot, s32 kind) {
    Object *obj;
    s32 ret = 0;
    Words3_8011CDB8 *copy;
    s32 *d;
    s32 dx, dy, dz;

    obj = obj_new();
    if (obj != NULL) {
    d = scratch_alloc(0x10);
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) obj_part_phase0;
    obj->handlers[1].fn = obj_move_sound_update;
    obj->handlers[2].fn = obj_hit_handler;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) obj_hit_spark;
    obj->callback = (s32) burst_update;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->destructor = obj_destructor_stop_sound;
    obj->kind = parent->kind;
    copy = &part_asset_buf;
    *copy = *(Words3_8011CDB8 *) parent->asset;
    obj->asset = copy;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_8011CEC4;
    obj->state_table = D_8011CEF4;
    *(volatile s16 *) &obj->unk_1C6 = 0;
    obj->script.data = D_8011CEA8;
    obj->script.unk_0A = 0;
    obj->script.pc = D_8011CEC0;
    script_start((Script *) obj, part_scripts[0], (s32) part_scripts);
    obj_init_pose_b(obj, (s32 *) pos, (u16 *) rot, 0x25);
    obj_set_part_bounds(obj, 0x11, 0x800);
    obj->vars.h.unk_248 = kind;
    obj->vars.h.unk_24A = 0;
    obj->vars.h.unk_24C = part_kind_params[kind][0];
    obj->vars.part.offset_y = part_kind_params[kind][1];
    obj->vars.part.offset_z = part_kind_params[kind][2];
    limb_solve_joint(obj);
    obj->vars.words[6] = 0;
    ((s16 *) &obj->vars)[0xE] = pos->x;
    obj->vars.enemy.unk_266 = pos->y;
    ((s16 *) &obj->vars)[0x10] = pos->z;
    obj->vars.enemy.walk_state = rot->vx;
    obj->vars.enemy.target_yaw = rot->vy;
    obj->vars.words[0xA] = 0;
    obj->unk_226[4] = rot->vx;
    obj->unk_226[3] = rot->vy;
    d[0] = (obj->x >> 12) - obj->vars.h.unk_24C;
    d[1] = (obj->y >> 12) - (s16) obj->vars.part.offset_y;
    d[2] = (obj->z >> 12) - (s16) obj->vars.part.offset_z;
    obj->speed = isqrt(length_sq(d[0], d[1], d[2])) << 12;
    scratch_top -= 0x10;
    ret = 1;
    }
    return ret;
}

void obj_init_pose_b(Object *obj, s32 *pos, u16 *rot, s32 flags) {
    u16 roll;

    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0x80);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj_set_flags(obj, flags);
    obj->health = 0x4B0;
    obj->score = 0x3E8;
    obj->damage = 0;
    obj->unk_17B = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    roll = rot[2];
    obj->placement = NULL;
    obj->roll = roll;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

void obj_clear_child(Object *obj) {
    if (obj != NULL) {
        obj->vars.boss_laser.sound_channel = 0; /* 0x260 */
    }
}

s32 obj_follow_parent(Object *self);
s32 obj_hit_trace(Object *obj, TraceHit *out);
/* Laser beam: aims along the parent's yaw/pitch; fades in (unk_25E) for 16 frames, then traces hits and widens (unk_25C) with its sound until frame 0xD0, then narrows and frees itself at 0 or when the parent is gone. */
void boss_laser_update(Object *obj, ObjHandler *handler) {
    TraceHit *hit = scratch_alloc(0x10);
    s32 x = 0, y = 0, z = 0;
    s32 done;
    s16 age;

    obj_follow_parent(obj);
    angles_to_vector(obj->yaw, -obj->pitch, 0x2000, &x, &y, &z);
    obj->vx = x;
    obj->vy = y;
    obj->vz = z;
    done = 0;
    age = obj->vars.shot.age;
    if (age <= 0x10) {
        obj->vars.boss_laser.spark_life += 0x100;
        obj->vars.boss_laser.spark_life = MAX(MIN(obj->vars.boss_laser.spark_life, 0x1000), 0);
    } else if (age >= 0x11 && age < 0xD1) {
        if (obj_hit_trace(obj, hit) == 1) {
            obj->vars.boss_laser.hit_x = hit->w[0];
            obj->vars.boss_laser.hit_y = hit->w[1];
            obj->vars.boss_laser.hit_z = hit->w[2];
        }
        obj->vars.boss_laser.beam_width += 0x80;
        obj->vars.boss_laser.beam_width = MAX(MIN(obj->vars.boss_laser.beam_width, 0x1000), 0);
        obj->vars.boss_laser.spark_life = 0;
        if (obj->vars.boss_laser.sound_channel == 0) {
            obj->vars.boss_laser.sound_channel = sound_start(SND_PAIR(SND_WHIRR | SND_HELD | SND_GROUP(1), SND_BOSS_LASER_WHIRR_LOOP | SND_HELD | SND_GROUP(1)), 0x7F, 0, 0);
            sound_attach(obj->vars.boss_laser.sound_channel, &obj->x, NULL);
            sound_set_flag_bit2(obj->vars.boss_laser.sound_channel, 1);
        }
    } else if (age > 0xD0) {
        if (obj_hit_trace(obj, hit) == 1) {
            obj->vars.boss_laser.hit_x = hit->w[0];
            obj->vars.boss_laser.hit_y = hit->w[1];
            obj->vars.boss_laser.hit_z = hit->w[2];
        }
        obj->vars.boss_laser.beam_width -= 0x100;
        obj->vars.boss_laser.beam_width = MAX(MIN(obj->vars.boss_laser.beam_width, 0x1000), 0);
        if (obj->vars.boss_laser.beam_width == 0) {
            done = 1;
        }
    }
    obj->vars.shot.age++;
    scratch_top -= 0x10;
    if (done == 1 || obj->vars.boss_laser.parent == 0) {
        if (obj->vars.boss_laser.parent != 0) {
            obj_clear_child((Object *)obj->vars.boss_laser.parent);
        }
        obj_free(obj);
    }
}

/* Copies the attitude from the parent object (vars.enemy.unk_250), then offsets self's
 * position from the parent's by a vector (z = 0x138) rotated by the parent's yaw/pitch.
 * Returns 1 if a parent exists. */
s32 obj_follow_parent(Object *self) {
    Object *parent;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 result;

    parent = (Object *)self->vars.boss_laser.parent;
    result = 0;
    if (parent != NULL) {
        self->pitch = parent->pitch;
        dx = 0;
        dy = 0;
        self->yaw = parent->yaw;
        dz = 0x138;
        self->roll = parent->roll;
        rotate_xz_twice(self->yaw, -self->pitch, &dx, &dy, &dz);
        result = 1;
        self->x = parent->x + (dx << 12);
        self->y = parent->y + (dy << 12);
        self->z = parent->z + (dz << 12);
    }
    return result;
}

void ray_extend_end(Vec3 *from, Vec3 *to);
/* Traces a line from the object's position to position + velocity; on an object hit damages it (when
 * get_enemies_left allows) and calls ray_extend_end (1 returned), on a world hit stores the hit record in out. */
s32 obj_hit_trace(Object *obj, TraceHit *out) {
    s32 result = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to;
    TraceHit *hit;
    s16 target;
    s32 world;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to = scratch_alloc(0x10);
    to->x = (obj->x + obj->vx) >> 12;
    to->y = (obj->y + obj->vy) >> 12;
    hit = scratch_alloc(0x10);
    target = 0;
    to->z = (obj->z + obj->vz) >> 12;
    set_collide_mode(1);
    world = trace_world(8, obj->vars.boss_laser.unk_24C, from, to, hit);
    if (trace_objects(from, hit, obj->vars.boss_laser.unk_24C, out, &target) == 1) {
        if (get_enemies_left() > 0) {
            hit_target_masked(target, 8, obj->yaw, obj->damage);
        }
        ray_extend_end(from, (Vec3 *)out);
        result = 1;
    } else if (world == 1) {
        *out = *hit;
        result = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}

/* Moves `to` toward/along the direction from `from` to `to`: the offset is re-aimed
 * at the same yaw and reversed pitch, its length is the distance plus 0x50, and the
 * scaled offset (>> 12) is added to `from` to give the new `to`. */
void ray_extend_end(Vec3 *from, Vec3 *to) {
    s32 yaw;
    s32 pitch;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 len;

    dx = to->x - from->x;
    dy = to->y - from->y;
    dz = to->z - from->z;
    len = isqrt(length_sq(dx, dy, dz)) + 0x50;
    yaw = 0;
    pitch = 0;
    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    angles_to_vector(yaw, -pitch, len, &dx, &dy, &dz);
    to->x = from->x + (dx >> 12);
    to->y = from->y + (dy >> 12);
    to->z = from->z + (dz >> 12);
}


void obj_sound_stop_260(Object *obj) {
    sound_stop(obj->vars.words[6]); /* 0x260 */
}


void boss_laser_spark_draw(Object *obj);

void boss_laser_beam_draw(Object *obj);

void boss_laser_draw(Object *obj) {
    boss_laser_spark_draw(obj);
    boss_laser_beam_draw(obj);
}

/* Puffs a fading spark at the object's position, sized by its remaining life. */
void boss_laser_spark_draw(Object *obj) {
    s32 life = obj->vars.boss_laser.spark_life;
    s32 z, y, x;
    s32 scale, size, q, r, colour, n, zero;
    SparkList *list;
    SparkRec *rec;
    u8 *tail;

    if (life > 0) {
        scale = (0x1000 - life) * 2;
        x = obj->x >> 12;
        z = obj->z >> 12;
        y = obj->y >> 12;
        size = pool_spawn_scaled(obj->vars.boss_laser.unk_248 + 0x1D, scale, scale, scale);
        q = life / 3 >> 5;
        r = life >> 5;
        zero = (q | r) == 0;
        colour = (zero << 16) | (r << 8) | q;
        list = &spark_list;
        n = SPARK_COUNT;
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
            /* the loop doubles y's and z's register priority: x in $s4 */
            do {
                rec->y = y;
                rec->z = z;
            } while (0);
            rec->unk_12 = size;
            rec->yaw = 0;
            rec->pitch = 0;
            rec->roll = 0;
        }
    }
}

/* Object vars (from 0x248) of the spark-beam effect: a line of sparks from the object to a target point. */
typedef struct SparkBeamVars {
    /* 0x248 */ s16 model;      /* base model slot of the spark records */
    /* 0x24A */ u8 pad_24A[10];
    /* 0x254 */ s16 tx, ty, tz; /* target point, whole units */
    /* 0x25A */ s16 flip;       /* toggles each unpaused frame: alternate end model */
    /* 0x25C */ u16 count;      /* strength; also picks the colour */
} SparkBeamVars;

#define V ((SparkBeamVars *)&obj->vars)

void boss_laser_beam_draw(Object *obj) {
    s32 colour;
    s32 value;
    s32 yaw, pitch;
    s32 sx, sy, sz;
    s32 x, y, z;
    register s32 base asm("$3");
    register s32 tx asm("$4");
    register s32 ty asm("$5");
    register s32 tz asm("$6");
    s32 dist;
    s32 low, high, empty;
    s32 step_len;
    s16 count = V->count;

    if (count <= 0) {
        return;
    }
    colour = count;
    base = V->model;
    tx = V->tx;
    ty = V->ty;
    tz = V->tz;
    sx = 0;
    sy = 0;
    sz = 0;
    base += 0x1D;
    value = base;
    x = tx - (obj->x >> 12);
    y = ty - (obj->y >> 12);
    z = tz - (obj->z >> 12);
    pitch = obj->pitch;
    yaw = obj->yaw;
    dist = isqrt(length_sq(x, y, z));
    vector_to_angles(x, y, z, &yaw, &pitch);
    low = colour / 3 >> 5;
    high = count >> 5;
    empty = (low | high) == 0;
    colour = empty << 16 | (high << 8) | low;
    step_len = 0xC0;
    x = obj->x;
    y = obj->y;
    z = obj->z;
    spark_add(x >> 12, y >> 12, z >> 12, 0, 0, 0, value, colour);
    value = V->model + 0x19;
    angles_to_vector(yaw, -pitch, step_len, &sx, &sy, &sz);
    while (dist >= step_len) {
        spark_add(x >> 12, y >> 12, z >> 12, yaw, -pitch, 0, value, colour);
        dist -= step_len;
        x += sx;
        y += sy;
        z += sz;
    }
    if (dist > 0) {
        value = pool_spawn_scaled(value, 0x1000, 0x1000, (dist << 12) / step_len);
        spark_add(x >> 12, y >> 12, z >> 12, yaw, -pitch, 0, value, colour);
    }
    {
        register s32 end_model asm("$2") = V->flip + 0x1B;

        value = V->model + end_model;
    }
    spark_add(V->tx, V->ty, V->tz, yaw, -pitch, 0, value, colour);
    if (is_paused() == 0) {
        V->flip ^= 1;
    }
}
#undef V

/* Spawns an object at pos/rot (fixed-point, 12-bit shifted) and links it into list.
 * kind 0 also runs boss_laser_init on it. Returns NULL unless kind <= 0 and the spawn succeeded. */
void boss_laser_init(Object *obj, s32 unk_250);
Object *boss_laser_spawn(Node *list, Vec3 *pos, SVECTOR *rot, s32 kind, s32 param) {
    Object *obj;

    obj = NULL;
    if (kind >= 0) {
        if (kind <= 0) {
            obj = obj_new();
            if (obj != NULL) {
                list_insert_after(list, &obj->node);
                obj_hit_clear(obj->index);
                obj_hit_flag_set(obj->index, 0);
                obj->x = pos->x << 12;
                obj->y = pos->y << 12;
                obj->z = pos->z << 12;
                obj->pitch = rot->vx;
                obj->yaw = rot->vy;
                obj->roll = rot->vz;
                obj->vars.boss_laser.unk_248 = param;
                obj->vars.boss_laser.kind = kind;
                if (kind == 0) {
                    boss_laser_init(obj, (s32) list);
                }
            }
        }
    }
    return obj;
}

void boss_laser_update(Object *obj, ObjHandler *handler);
/* Sets up a shooting enemy: two of its four handlers, the destructor, and the cleared state. */
void boss_laser_init(Object *obj, s32 unk_250) {
    obj->handlers[1].fn = boss_laser_update;
    obj->handlers[3].fn = (void *)boss_laser_draw;
    obj->destructor = obj_sound_stop_260;
    obj->damage = 6;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.boss_laser.unk_24C = 0xC;
    obj->vars.boss_laser.unused_24E = 0;
    obj->vars.boss_laser.parent = unk_250;
    obj->vars.boss_laser.hit_x = 0;
    obj->vars.boss_laser.hit_y = 0;
    obj->vars.boss_laser.hit_z = 0;
    obj->vars.boss_laser.unused_25A = 0;
    obj->vars.boss_laser.beam_width = 0;
    obj->vars.boss_laser.spark_life = 0;
    obj->vars.boss_laser.sound_channel = 0; /* 0x260 */
}


void pair_release_child(Object *obj) {
    if (obj != NULL) {
        obj->vars.enemy.unk_250 = 0;
    }
}


extern s32 boss_done_flag;
extern FxRecordParams fade_fx_params;
s32 obj_trace_shot(Object *obj, s32 *to);
/* Ramps unk_252 (0..0x1000) up while unk_250 < 0x19 and boss_done_flag is 0, down otherwise; frees the object once it
 * reaches 0. When cam_range_check says the spot is blocked: at the top of the ramp spawns the effect at its position
 * and then at its unk_254..258 point, once. */
void obj_fade_update(Object *obj) {
    s32 *pos;

    if (obj->vars.at.fade_timer < 0x19 && boss_done_flag == 0) {
        obj->vars.at.fade_level += 0x200;
        obj->vars.at.fade_level = MAX(MIN(obj->vars.at.fade_level, 0x1000), 0);
    } else {
        obj->vars.at.fade_level -= 0x100;
        obj->vars.at.fade_level = MAX(MIN(obj->vars.at.fade_level, 0x1000), 0);
        obj->vars.at.unused_25A = 0;
        if (obj->vars.at.fade_level == 0) {
            obj_free(obj);
        }
    }
    if (cam_range_check(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 1) {
        pos = scratch_alloc(0x10);
        obj_trace_shot(obj, pos);
        if (obj->vars.at.unk_25C == 0 && obj->vars.at.fade_level == 0x1000) {
            pos[0] = obj->x >> 12;
            pos[1] = obj->y >> 12;
            pos[2] = obj->z >> 12;
            fx_rec34_spawn_cb(pos, &fade_fx_params, 0);
            pos[0] = obj->vars.at.origin_x;
            pos[1] = obj->vars.at.origin_y;
            pos[2] = obj->vars.at.origin_z;
            fx_rec34_spawn_cb(pos, &fade_fx_params, 0);
            obj->vars.at.unk_25C = 1;
        }
        scratch_top -= 0x10;
    }
    obj->vars.at.fade_timer++;
}

/* Traces from the object along its velocity with collision on; hits the target when engines are running. Returns 1 on a hit. */
s32 obj_trace_shot(Object *obj, s32 *to) {
    Vec3 *from;
    Vec3 *vel;
    s32 hit_result;
    s32 z;
    s16 target[1];

    from = (Vec3 *)scratch_top;
    from->x = obj->x >> 12;
    hit_result = 0;
    from->y = obj->y >> 12;
    z = obj->z;
    scratch_top += 0x10;
    target[0] = 0;
    from->z = z >> 12;
    vel = (Vec3 *)scratch_top;
    scratch_top += 0x10;
    vel->x = obj->vars.at.origin_x;
    vel->y = obj->vars.at.origin_y;
    vel->z = obj->vars.at.origin_z;
    set_collide_mode(1);
    if (trace_objects(from, vel, obj->vars.at.unk_24E, to, target) == 1) {
        if (get_enemies_left() > 0) {
            hit_target_masked(target[0], 8, obj->yaw, obj->damage);
        }
        hit_result = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return hit_result;
}

void tracer_trail_draw(Object *obj);

void tracer_draw(Object *obj) {
    tracer_trail_draw(obj);
}

void tracer_trail_draw(Object *obj) {
    s32 dir[3];
    s32 x, y, z;
    s32 dist;
    s32 base;
    s32 step;
    s32 colour, level;
    u16 raw;
    s32 hi;
    s32 yaw, pitch;
    s32 seg, zero, tx, ty, tz, dx, dy, dz;

    if (((SparkTrailVars *)&obj->vars)->colour > 0 && cam_range_check(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 1) {
        step = ((SparkTrailVars *)&obj->vars)->step;
        base = ((SparkTrailVars *)&obj->vars)->base + 0x28;
        raw = ((SparkTrailVars *)&obj->vars)->colour;
        tx = ((SparkTrailVars *)&obj->vars)->tx;
        ty = ((SparkTrailVars *)&obj->vars)->ty;
        tz = ((SparkTrailVars *)&obj->vars)->tz;
        seg = 0x180;
        dir[0] = 0;
        dir[1] = 0;
        dir[2] = 0;
        hi = raw << 16;
        pitch = -obj->pitch;
        yaw = obj->yaw;
        dx = tx - (obj->x >> 12);
        dy = ty - (obj->y >> 12);
        dz = tz - (obj->z >> 12);
        dist = isqrt(length_sq(dx, dy, dz));
        x = obj->x;
        y = obj->y;
        z = obj->z;
        level = hi >> 21;
        zero = level == 0;
        colour = (zero << 16) | (level << 8) | level;
        angles_to_vector(yaw, pitch, 0x180, &dir[0], &dir[1], &dir[2]);
        if (dist >= seg) {
            do {
                spark_add(x >> 12, y >> 12, z >> 12, 0, 0, 0, base + step, colour);
                dist -= seg;
                x += dir[0];
                y += dir[1];
                step = (step + 1) % 6;
                z += dir[2];
            } while (dist >= seg);
        }
        if (dist > 0) {
            base = pool_spawn_scaled(base + step, 0x1000, (dist << 12) / seg, 0x1000);
            spark_add(x >> 12, y >> 12, z >> 12, 0, 0, 0, base, colour);
        }
        if (is_paused() == 0 && ((SparkTrailVars *)&obj->vars)->advance == 1) {
            ((SparkTrailVars *)&obj->vars)->step = (((SparkTrailVars *)&obj->vars)->step + 1) % 6;
        }
    }
}

void tracer_init(Object *obj, Node *list);
/* Spawns an object at pos (integer units, shifted to 12-bit fixed point) and rot
 * (pitch, yaw, roll). Only mode 0 is spawned; arg4 goes into vars.h.unk_248.
 * Returns 1 if an object was created. */
s32 obj_spawn_at(Node *list, s32 *pos, u16 *rot, s32 mode, s32 arg4) {
    Object *obj;
    s32 spawned = 0;

    if (mode >= 0) {
        if (mode <= 0) {
            obj = obj_new();
            if (obj != NULL) {
                list_insert_after(list, &obj->node);
                obj_hit_clear(obj->index);
                obj_hit_flag_set(obj->index, 0);
                obj->x = pos[0] << 12;
                obj->y = pos[1] << 12;
                obj->z = pos[2] << 12;
                obj->pitch = rot[0];
                obj->yaw = rot[1];
                obj->roll = rot[2];
                obj->vars.at.unk_248 = arg4;
                obj->vars.at.unused_24A = 0;
                obj->vars.at.unk_24C = mode;
                if (mode == 0) {
                    tracer_init(obj, list);
                }
                spawned = 1;
            }
        }
    }
    return spawned;
}

void obj_muzzle_trace(Object *obj, void *hit);
/* Spawns a tracer: sets its fade and draw handlers, aims it along yaw/pitch and traces the muzzle hit point. */
void tracer_init(Object *obj, Node *list) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 dx = 0;
    s32 dy = 0;
    s32 dz = 0;
    s32 yaw = obj->yaw;
    s32 pitch = obj->pitch;

    obj->handlers[1].fn = (void *)obj_fade_update;
    obj->handlers[3].fn = (void *)tracer_draw;
    obj->damage = 10;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    angles_to_vector(yaw, -pitch, 0x1000, &dx, &dy, &dz);
    obj->vars.at.unk_24E = 12;
    obj->vars.at.fade_timer = 0;
    obj->vars.at.fade_level = 0;
    obj->vx = dx;
    obj->vy = dy;
    obj->vz = dz;
    obj_muzzle_trace(obj, pos);
    obj->vars.at.origin_x = pos->x;
    obj->vars.at.origin_y = pos->y;
    obj->vars.at.origin_z = pos->z;
    obj->vars.at.unused_25A = 1;
    obj->vars.at.unk_25C = 0;
    scratch_top -= 0x10;
}

/* Traces a line from the object's position to the position plus its velocity, then 0x20 units along its facing. */
void obj_muzzle_trace(Object *obj, void *hit) {
    s32 *start = scratch_alloc(0x10);
    s32 *end = scratch_alloc(0x10);
    s32 off[3];

    off[0] = 0;
    off[1] = 0;
    off[2] = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x20, &off[0], &off[1], &off[2]);
    start[0] = (obj->x + off[0]) >> 12;
    start[1] = (obj->y + off[1]) >> 12;
    start[2] = (obj->z + off[2]) >> 12;
    end[0] = (obj->x + obj->vx) >> 12;
    end[1] = (obj->y + obj->vy) >> 12;
    end[2] = (obj->z + obj->vz) >> 12;
    trace_world(8, obj->vars.at.unk_24E, start, end, hit);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

s32 is_energy_mote_near(Object *obj);
void energy_mote_discharge(Object *obj);
void energy_mote_update(Object *obj) {
    switch (obj->vars.energy_mote.state) {
    case 0:
        obj->vars.energy_mote.shade += 0x80;
        obj->vars.energy_mote.shade = MAX(MIN(obj->vars.energy_mote.shade, 0x800), 0);
        if (obj->vars.energy_mote.shade >= 0x800) {
            obj->vars.energy_mote.state = 1;
        }
        break;
    case 2:
        obj->vars.energy_mote.shade += 0x200;
        obj->vars.energy_mote.shade = MAX(MIN(obj->vars.energy_mote.shade, 0x1000), 0);
        obj->vars.energy_mote.scale += 0x400;
        obj->vars.energy_mote.scale = MAX(MIN(obj->vars.energy_mote.scale, 0x2000), 0);
        if (obj->vars.energy_mote.shade >= 0x1000) {
            obj->vars.energy_mote.state = 3;
        }
        break;
    case 3:
        obj->vars.energy_mote.shade -= 0x100;
        obj->vars.energy_mote.shade = MAX(MIN(obj->vars.energy_mote.shade, 0x1000), 0);
        obj->vars.energy_mote.scale -= 0x100;
        obj->vars.energy_mote.scale = MAX(MIN(obj->vars.energy_mote.scale, 0x2000), 0);
        if (obj->vars.energy_mote.shade <= 0) {
            obj->vars.energy_mote.state = 4;
            obj_free(obj);
        }
        break;
    case 1:
    case 4:
        break;
    }
    if (obj->vars.energy_mote.state < 2) {
        obj->x += obj->vx;
        obj->y += obj->vy;
        obj->z += obj->vz;
        if (is_energy_mote_near(obj) == 1) {
            energy_mote_discharge(obj);
            obj->vars.energy_mote.state = 2;
        }
    }
}

s32 is_energy_mote_near(Object *obj) {
    return isqrt(length_sq(obj->x >> 12, 0, (obj->z >> 12) + 0x60)) < 0x739;
}

s32 arc_spawn(Node *src, void *unused, SVECTOR *rot, u32 side, s32 value, s32 sound);
void energy_mote_discharge(Object *obj) {
    Vec3 *pos = (Vec3 *)scratch_top;
    s16 *rot;
    s32 r;

    scratch_top += 0x10;
    pos->z = (obj->z >> 12) + 0x60;
    pos->x = obj->x >> 12;
    rot = (s16 *)scratch_top;
    rot[0] = 0;
    scratch_top += 8;
    rot[1] = atan2(pos->z, pos->x);
    rot[2] = 0;
    pos->x = 0;
    pos->y = 0;
    pos->z = 0;
    r = rand_a_next();
    arc_spawn(&obj->node, pos, (SVECTOR *)rot, 0, obj->vars.energy_mote.unk_248, r < 0x200);
    arc_spawn(&obj->node, pos, (SVECTOR *)rot, 1, obj->vars.energy_mote.unk_248, 0);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Queue the mote as one spark when it is on screen; its colour fades with unk_24E. */
void energy_mote_draw(Object *obj) {
    s32 shade; /* the fade level, then (reused) the packed spark colour */
    s32 scale;
    s16 value;
    s32 x, y, z;
    s32 level;
    s32 green;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    if (cam_range_check(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 1) {
        shade = obj->vars.energy_mote.shade;
        scale = (obj->vars.energy_mote.scale * 2457) >> 12;
        x = obj->x >> 12;
        y = obj->y >> 12;
        z = obj->z >> 12;
        value = pool_spawn_scaled(obj->vars.energy_mote.unk_248 + 0x1D, scale, scale, scale);
        level = shade * 2 / 3;
        level >>= 5;
        green = shade >> 5;
        if ((level | green) == 0) {
            green = 1;
        }
        shade = (green << 16) | (level << 8) | level;
        list = &spark_list;
        n = spark_count;
        if (n < 0xFF) {
            s = &list->items[n];
            n++;
            spark_count = n;
            *(s32 *)s->colour = shade;
            tail = list->tail[shade >> 24];
            list->tail[shade >> 24] = &s->next;
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
}

void energy_mote_draw(Object *obj);
void energy_mote_home(Object *obj);
s32 energy_mote_spawn(Object *head, s32 *pos, s16 *rot, s32 mode, s32 arg4) {
    Object *obj;
    s32 ok;
    u16 roll;

    ok = 0;
    if (mode >= 0) {
        if (mode <= 0) {
            obj = obj_new();
            if (obj != NULL) {
                list_insert_after(&head->node, &obj->node);
                obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) energy_mote_update;
                obj->handlers[0].fn = NULL;
                obj->handlers[0].unk_11 = 0;
                obj->handlers[0].state = 0;
                obj->handlers[1].unk_11 = 0;
                obj->handlers[1].state = 0;
                obj->handlers[2].fn = NULL;
                obj->handlers[2].unk_11 = 0;
                obj->handlers[2].state = 0;
                obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) energy_mote_draw;
                obj->handlers[3].unk_11 = 0;
                obj->handlers[3].state = 0;
                obj->callback = 0;
                obj_hit_clear(obj->index);
                obj_hit_flag_set(obj->index, 0);
                obj->x = pos[0] << 12;
                obj->y = pos[1] << 12;
                obj->z = pos[2] << 12;
                ok = 1;
                obj->pitch = rot[0];
                obj->yaw = rot[1];
                roll = rot[2];
                obj->vars.energy_mote.unk_248 = arg4;
                obj->vars.energy_mote.mode = mode;
                obj->vars.energy_mote.state = 0;
                obj->vars.energy_mote.shade = 0;
                obj->vars.energy_mote.scale = 0x1000;
                obj->roll = roll;
                energy_mote_home(obj);
            }
        }
    }
    return ok;
}

void energy_mote_home(Object *obj) {
    s32 dx;
    s32 dz;

    dx = 0;
    dz = 0;
    fly_move(atan2(-0x60 - (obj->z >> 12), -(obj->x >> 12)), 0xA, &dx, &dz);
    obj->vy = 0;
    obj->vx = dz;
    obj->vz = dx;
}

void arc_set_heading(Object *obj);
void arc_update(Object *obj) {
    s16 t;
    s32 cur;
    s16 r;
    cur = obj->unk_226[3];
    obj->unk_226[3] = cur + obj->vars.arc.turn_speed;
    arc_set_heading(obj);
    t = obj->vars.arc.life - 0x80;
    obj->vars.arc.life = t;
    r = NOT_NEGATIVE(MIN(t, 0x1000));
    obj->vars.arc.life = r;
    if (r <= 0) {
        obj_free(obj);
    }
}

void arc_set_heading(Object *obj) {
    s32 pos[4];
    s32 angle;
    s32 base;
    s32 dz;
    s32 dx;
    s16 yaw;

    angle = obj->unk_226[3];
    pos[0] = 0;
    pos[1] = 0;
    fly_move(angle, 0x738, &pos[0], &pos[1]);
    /* opaque copy: the original keeps angle -> base -> yaw as two moves */
    __asm__("" : "=r"(base) : "0"(angle));
    yaw = base;
    dz = pos[0];
    dx = pos[1];
    obj->z = dz - 0x60000;
    obj->x = dx;
    if (obj->vars.trace.aim_yaw != 0) {
        yaw = angle + 0x800;
    }
    obj->yaw = yaw;
}

void arc_draw(Object *obj, ObjHandler *handler) {
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    s32 colour, len, v, a, b, size, step;

    if (cam_range_check(x, y, z) == 1) {
        v = obj->vars.arc.life;
        len = 0x954;
        step = 0x300;
        size = obj->vars.h.unk_248 + 0x38;
        a = v * 2 / 3;
        b = v >> 5;
        a >>= 5;
        if ((a | b) == 0) {
            b = 1;
        }
        colour = (b << 16) | (a << 8) | a;
        FAKE_OPAQUE(colour);
        do {
            spark_add(x, y, z, (u16)obj->yaw, 0, 0, size, colour);
            len -= step;
            y -= step;
        } while (len >= step);
        if (len > 0) {
            size = pool_spawn_scaled(size, 0x1000, (len << 12) / step, 0x1000);
            spark_add(x, y, z, (u16)obj->yaw, 0, 0, size, colour);
        }
    }
}

void arc_draw(Object *obj, ObjHandler *handler);
void arc_set_heading(Object *obj);
/* Spawns a side-`side` object (0 or 1) next to `src`; plays a sound if `sound` is 1. */
s32 arc_spawn(Node *src, void *unused, SVECTOR *rot, u32 side, s32 value, s32 sound) {
    Object *obj;
    s32 *pos;
    s32 ok = 0;

    if (side < 2) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after(src, (Node *)obj);
            obj->handlers[1].fn = (ObjHandlerFn)arc_update;
            obj->handlers[0].fn = NULL;
            obj->handlers[0].unk_11 = 0;
            obj->handlers[0].state = 0;
            obj->handlers[1].unk_11 = 0;
            obj->handlers[1].state = 0;
            obj->handlers[2].fn = NULL;
            obj->handlers[2].unk_11 = 0;
            obj->handlers[2].state = 0;
            obj->handlers[3].fn = arc_draw;
            obj->handlers[3].unk_11 = 0;
            obj->handlers[3].state = 0;
            obj->callback = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->unk_226[3] = rot->vy;
            arc_set_heading(obj);
            obj->vars.h.unk_248 = value;
            obj->vars.h.unk_24A = side;
            obj->vars.arc.life = 0x1000;
            *(s16 *)&obj->vars.arc.turn_speed = side == 0 ? 4 : -4;
            if (sound == 1) {
                pos = scratch_alloc(0x10);
                pos[0] = obj->x >> 12;
                pos[1] = cam_pos_y >> 12;
                pos[2] = obj->z >> 12;
                sound_play_at_units(0xB10BB10C, 0x7F, 0x3C, pos);
                scratch_top -= 0x10;
            }
            ok = 1;
        }
    }
    return ok;
}
