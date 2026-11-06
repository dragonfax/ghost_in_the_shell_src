/* stage: one of s04's own original source files (scripts/objmap.py); part of src/s04/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **func_800BE8F8(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 func_800BE908(void) {
    return grid_flagged_count;
}

void stage_intro_setup(void) {
    Vec3 *pos;
    SVECTOR *rot;

    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(-0x258, -0x258, -0x4844);
    cam_look_at_set(VEC_80139584.x >> 12, VEC_80139584.y >> 12, VEC_80139584.z >> 12);
    fade_level_set(0);
    pos = scratch_alloc(0x10);
    pos->x = VEC_80139584.x >> 12;
    rot = scratch_alloc(8);
    pos->y = (VEC_80139584.y >> 12) - 0xE00;
    pos->z = VEC_80139584.z >> 12;
    rot->vx = 0;
    rot->vy = 0;
    rot->vz = 0;
    player_warp_request((VECTOR *)pos, (UnalignedVec *)rot, 0);
    scratch_top -= 0x18;
}

void cam_fly_in_step(void) {
    s32 *dst;
    s32 progress;
    s32 *src;
    s32 advanced;
    s32 clamped;

    /* the three src[] terms are the source vector / 8192, rounded toward zero */
    progress = fade_level_get();
    if (progress != 0x1000) {
        dst = cam_view_pos_get();
        src = get_flow_move();
        dst[0] += (s32)(src[0] + ((u32)src[0] >> 31)) >> 13;
        src = get_flow_move();
        dst[1] += (s32)(src[1] + ((u32)src[1] >> 31)) >> 13;
        src = get_flow_move();
        dst[2] += (s32)(src[2] + ((u32)src[2] >> 31)) >> 13;
        cam_view_pos_set(dst[0], dst[1], dst[2]);
        cam_look_at_set(VEC_80139584.x >> 12, VEC_80139584.y >> 12, VEC_80139584.z >> 12);
        advanced = progress + 0x28;
        clamped = 0x1000;
        if (advanced < 0x1001) {
            clamped = advanced;
        }
        progress = clamped;
        fade_level_set(progress);
        if (progress == 0x1000) {
            set_d_801202C8(1);
            set_stage_flags(get_stage_flags() & ~0x28);
        }
    }
}

extern u8 span_table[];
extern s32 D_80119DA4[];
extern LightData stage_data_base;
extern s32 effect_spawn_phase;
extern s32 sound_ramp_level;
extern s32 sound_interval_timer;
/* Stage setup: flow limit, the three counters at 0x80122474 cleared, then the
   start sound and its volume. */
void stage_start(void) {
    s32 handle;

    if (stage_ready_get() != 0) {
        span_table_build((s32)span_table, D_80119DA4);
    }
    set_flow_max(0x20);
    set_player_status(get_player_status() | 7);
    effect_spawn_phase = 0;
    sound_ramp_level = 0;
    sound_interval_timer = 0;
    stage_intro_setup();
    handle = sound_start(SND_STAGE_AMBIENCE_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    sound_set_volume(handle, sound_volume_of(SND_STAGE_AMBIENCE_LOOP | SND_HELD | SND_GROUP(2), 0xCCC));
    hit_ext_flag_set(1);
    set_data_base((s32)&stage_data_base);
}

char str_ctl4_tp0_clt[16] RODATA = "ctl4_tp0.clt";

char str_ctl4_tp0_xs3[16] RODATA = "ctl4_tp0.xs3";

char str_ctl4_ch0_vx1[16] RODATA = "ctl4_ch0.vx1";

void sound_driver_update(void);
void player_spark_add(void);
/* Spawns the stage's sound-driver object (handlers: sound_driver_update, player_spark_add) and shows the
 * landing line. */
s32 sound_driver_spawn(void) {
    Object *obj;
    s32 ok;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_b(), (Node *)obj);
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = (ObjHandlerFn)sound_driver_update;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (ObjHandlerFn)player_spark_add;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        show_line((s32)"Landing completed, will pursue.\xA1");
        ok = 1;
    } else {
        ok = 0;
    }
    return ok;
}

/* Boss model files a data table (escaping_boat_boss_palettes) points to by address; they follow this function's string. */
const char file_bos4_tp1_clt[] = "bos4_tp1.clt";
const char file_bos4_ch0_clt[] = "bos4_ch0.clt";
const char file_bos4_ch0_vx1[] = "bos4_ch0.vx1";
const char file_bos4_tp1_xs3[] = "bos4_tp1.xs3";
const char file_bos4_tp0_xs3[] = "bos4_tp0.xs3";
const char file_bos4_ch0_cb4[] = "bos4_ch0.cb4";

extern s32 sound_ramp_level;
s32 speedboat_wake_spawn(Vec3 *pos, SVECTOR *rot, s32 arg2, s32 arg3, s32 arg4);
/* Builds a Vec3 at the player's x/z (from cam_pos/8C) and an SVECTOR with vy 0x800, then calls speedboat_wake_spawn. */
void player_effect_spawn(void) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 *words;

    pos->x = 0;
    pos->y = 0;
    pos->z = -0x180;
    if (sound_ramp_level > 0) {
        pos->z = 0x100;
    }
    /* Adding through an s32 view keeps the stores in the original's order against the global loads. */
    words = (s32 *)pos;
    words[0] += cam_pos >> 12;
    words[2] += cam_pos_z >> 12;
    rot->vx = 0;
    rot->vy = 0x800;
    rot->vz = 0;
    speedboat_wake_spawn(pos, rot, get_model_slot_base() + 0x50, 8, 0xAA);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void cam_fly_in_step(void);
/* Per-frame sound driver: steps the 8-phase counter at 0x80122474 (calling player_effect_spawn when it wraps
 * to 0), ramps the level at 0x80122478 up by 0x200 to 0x1000 (or zeroes it while player_landed is set,
 * starting sound 0x5242 when it was 0), and counts down 0x8012247C, starting sound 0x5241 and drawing
 * a new interval of 45 or 60 each time it goes negative. */
void sound_driver_update(void) {
    cam_fly_in_step();
    effect_spawn_phase = (effect_spawn_phase + 1) % 8;
    if (effect_spawn_phase == 0) {
        player_effect_spawn();
    }
    if (player_landed != 0) {
        sound_ramp_level = 0;
    } else {
        s32 level = sound_ramp_level + 0x200;
        s32 next;
        if (sound_ramp_level == 0) {
            s32 handle = sound_start(0x5242, 0x7F, 0, 0);
            sound_set_volume(handle, sound_volume_of(0x5242, 0x1000));
            level = sound_ramp_level + 0x200;
        }
        next = 0x1000;
        if (level < 0x1001) {
            next = level;
        }
        sound_ramp_level = next;
    }
    sound_interval_timer -= 1;
    if (sound_interval_timer < 0) {
        s32 handle = sound_start(0x5241, 0x7F, 0, 0);
        sound_set_volume(handle, sound_volume_of(0x5241, 0xE66));
        sound_interval_timer = (rand_a_next() % 2) * 0xF + 0x2D;
    }
}

extern ModelSlotHead spark_model_index;
void player_spark_add(void) {
    s32 t1 = model_slot_pchr(spark_model_index.words[0]);
    s32 colour = ((0x1000 - sound_ramp_level) >> 5) | 0x808000;
    s32 x = cam_pos >> 12;
    s32 z = cam_pos_z >> 12;

    spark_add(x, 0, z, 0x800, 0, 0, t1, colour);
}

/* Advances the object's 16-bit counter (0x24E) by its step (0x24C); frees the object once the counter
 * reaches 0x1000 (as signed). */
void speedboat_wake_update(Object *obj) {
    u16 counter;

    counter = obj->vars.speedboat_wake.phase + obj->vars.speedboat_wake.phase_step;
    obj->vars.speedboat_wake.phase = counter;
    if ((s16)counter >= 0x1000) {
        obj_free(obj);
    }
}

/* Adds a spark record at the object's position with its (pitch negated) rotation. */
void speedboat_wake_draw(Object *obj) {
    s32 *pos = (s32 *)scratch_top;
    s16 *rot;
    s32 base;
    s32 pitch;

    base = obj->vars.speedboat_wake.base + (((s16)obj->vars.speedboat_wake.phase * obj->vars.speedboat_wake.amplitude) >> 12);
    scratch_top += 0x10;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot = (s16 *)scratch_top;
    scratch_top += 8;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    base = pool_spawn_scaled(base, 0x2000, 0x2000, 0x2000);
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], base, 0);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 speedboat_wake_spawn(Vec3 *pos, SVECTOR *rot, s32 arg2, s32 arg3, s32 arg4) {
    Object *obj;
    s32 result;
    s16 roll;

    result = 0;
    obj = obj_new();
    if (obj != NULL) {
        result = 1;
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = speedboat_wake_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = speedboat_wake_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        roll = rot->vz;
        obj->vars.speedboat_wake.base = arg2;
        obj->vars.speedboat_wake.amplitude = arg3;
        obj->vars.speedboat_wake.phase_step = arg4;
        obj->vars.speedboat_wake.phase = 0;
        obj->roll = roll;
    }
    return result;
}

extern s32 boss_active_flag;
extern s32 boss_meter_flag;
extern s32 boss_retreat_flag;
extern s32 rocket_boat_count;
void escaping_boat_m4_boss_phase0(Object *obj, ObjHandler *handler) {
    /* phase is signed (lh); the h view declares it u16 */
    switch (obj->vars.escaping_boat_m4_boss.state) {
    case 0:
        obj->vars.escaping_boat_m4_boss.timer = 180;
        obj->vars.escaping_boat_m4_boss.state = 1;
        /* fallthrough */
    case 1:
        obj->vars.escaping_boat_m4_boss.timer--;
        if (obj->vars.escaping_boat_m4_boss.timer > 0) {
            break;
        }
        mission_timer_set(3600);
        mission_state_set(2);
        mission_timer_active_set(1);
        warning_ack_set(0);
        boss_active_flag = 1;
        obj->vars.escaping_boat_m4_boss.state = 2;
        break;
    case 2:
        if (mission_timer_get() >= 0x709 && rocket_boat_count >= 2) {
            break;
        }
        obj->vars.escaping_boat_m4_boss.timer = 180;
        /* halfword at 0x260: no named field in ObjVars */
        *(s16 *)&obj->vars.enemy.unk_260[0] = 0;
        obj->unk_226[3] = 0;
        obj->vars.escaping_boat_m4_boss.state = 3;
        break;
    case 3:
        obj->vars.escaping_boat_m4_boss.timer--;
        if (obj->vars.escaping_boat_m4_boss.timer > 0) {
            break;
        }
        meter_set(obj->health, 12000);
        meter_set_mode(1);
        boss_meter_flag = 1;
        obj->vars.escaping_boat_m4_boss.state = 4;
        break;
    case 4:
        if (mission_timer_get() > 0) {
            break;
        }
        obj->vars.escaping_boat_m4_boss.timer = 300;
        obj->unk_17A = 0;
        obj->unk_226[3] = 0;
        meter_set_mode(0);
        mission_timer_active_set(0);
        warning_ack_set(0);
        boss_retreat_flag = 1;
        boss_active_flag = 0;
        boss_meter_flag = 0;
        obj->vars.escaping_boat_m4_boss.state = 5;
        break;
    case 5:
        obj->vars.escaping_boat_m4_boss.timer--;
        if (obj->vars.escaping_boat_m4_boss.timer > 0) {
            break;
        }
        set_stage_end(3);
        obj->vars.escaping_boat_m4_boss.state = 6;
        break;
    case 6:
        break;
    }
    if (boss_retreat_flag == 0) {
        obj_link_script_run(obj, handler);
    }
}
void rocket_boat_fire_aimed(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 *dir;
    VECTOR *target;
    s32 off_x, off_y, off_z;
    s32 vec_x, vec_y, vec_z;
    s32 yaw1, pitch1;
    s32 yaw2, pitch2;
    s32 speed;
    s32 pitch_rot, yaw_a, yaw_b;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    dir = scratch_alloc(0x10);
    target = scratch_alloc(0x10);

    off_z = 0xC9;
    vec_y = -0x1B2;
    yaw1 = 0;
    pitch1 = 0;
    yaw2 = 0;
    pitch2 = 0;
    off_x = 0;
    off_y = 0;
    vec_x = 0;
    vec_z = -0x51;

    rotate_xz_twice(obj->vars.escaping_boat_m4_boss.yaw, 0, &off_x, &off_y, &off_z);
    pos[0] = vec_x + off_x;
    pos[1] = vec_y + off_y;
    pos[2] = vec_z + off_z;
    rotate_xz_twice(obj->yaw, -obj->pitch, pos, &pos[1], &pos[2]);
    rotate_xz_twice(obj->yaw, -obj->pitch, &vec_x, &vec_y, &vec_z);

    vector_to_angles(pos[0] - vec_x, pos[1] - vec_y, pos[2] - vec_z, &yaw1, &pitch1);

    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;

    player_position_copy(target);
    vec_x = target->vx - pos[0];
    vec_y = target->vy - pos[1];
    vec_z = target->vz - pos[2];
    vector_to_angles(vec_x, vec_y, vec_z, &yaw2, &pitch2);

    pitch_rot = angle_approach(pitch1, pitch2, 0x80);
    yaw_a = yaw1;
    yaw_b = yaw2;
    rot[0] = pitch_rot;
    rot[1] = angle_approach(yaw_a, yaw_b, 0x80);
    rot[2] = 0;
    speed = get_flow_max();

    angles_to_vector(obj->vars.enemy.walk_state, 0, speed, dir, &dir[1], &dir[2]);
    rocket_boat_rocket_spawn((s32)obj, pos, rot, 0, model_slot_pchr(*(s32 *)obj->asset), dir);

    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
}

extern s16 muzzle_offset_x_table[];
extern s16 muzzle_offset_y_table[];
extern s16 muzzle_offset_z_table[];
extern u16 muzzle_yaw_table[];
s32 obj_spawn_shot(Object *parent, s32 *pos, u16 *rot, s32 type, s32 slot, s32 *vel);
void rocket_boat_launch(Object *obj, Object *parent);
void escaping_boss_mortar_init(Object *obj, Object *parent);
void escaping_boss_rocket_init(Object *obj, Object *parent);
void obj_script_muzzle_shot(Object *obj) {
    s32 *pos;
    s16 *ang;
    s32 *dir;
    s16 *script;
    s32 index;

    script = obj->script.pc;
    obj->script.pc = script + 1;
    index = script[0] * 4;

    pos = scratch_alloc(0x10);
    ang = scratch_alloc(8);
    dir = scratch_alloc(0x10);

    pos[0] = (muzzle_offset_x_table[index] * 0x333) >> 10;
    pos[1] = (muzzle_offset_y_table[index] * 0x333) >> 10;
    pos[2] = (muzzle_offset_z_table[index] * 0x333) >> 10;

    ang[0] = obj->pitch;
    ang[1] = obj->yaw;
    ang[2] = obj->roll;

    rotate_xz_twice(ang[1], -ang[0], pos, pos + 1, pos + 2);

    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;

    ang[0] -= 0x333;
    ang[1] += muzzle_yaw_table[index];

    angles_to_vector(obj->vars.enemy.walk_state, 0, get_flow_max(), dir, dir + 1, dir + 2);
    sound_play_at_units(SND_ENEMY_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    obj_spawn_shot(obj, pos, ang, 0, model_slot_pchr(*(s32 *)obj->asset), dir);
    scratch_top -= 0x10;
    scratch_top -= 0x8;
    scratch_top -= 0x10;
}

extern s16 effect_offset_table[][4];
s32 rocket_boat_spawn(Object *parent, s32 *pos, SVECTOR *rot, s32 mode, s32 asset, s32 *dir);
/* Reads a table index from the script, places an effect at that offset (scaled by 819/1024) rotated by the
 * object's angles, and passes it with a direction vector to rocket_boat_spawn. */
void obj_spawn_effect_offset(Object *obj) {
    s32 *pos;
    SVECTOR *rot;
    s32 *dir;
    s32 idx;
    s32 v;
    s32 asset;

    pos = (s32 *)scratch_top;
    idx = obj_read_s16(obj);
    scratch_top += 0x10;
    rot = (SVECTOR *)scratch_top;
    v = effect_offset_table[idx][0];
    scratch_top += 8;
    pos[0] = (v * 819) >> 10;
    v = effect_offset_table[idx][1];
    dir = (s32 *)scratch_top;
    pos[1] = (v * 819) >> 10;
    v = effect_offset_table[idx][2];
    scratch_top += 0x10;
    pos[2] = (v * 819) >> 10;
    rot->vx = obj->pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    rotate_xz_twice(rot->vy, -rot->vx, pos, pos + 1, pos + 2);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;
    angles_to_vector((s16)obj->vars.escaping_boat_m4_boss.heading, 0, get_flow_max(), dir, dir + 1, dir + 2);
    sound_play_at_units(SND_ROCKET_BOAT_LAUNCH | SND_GROUP(1), 0x7F, 0x3C, pos);
    idx &= 1;
    asset = model_slot_pchr(*(s32 *)obj->asset);
    rocket_boat_spawn(obj, pos, rot, idx, asset, dir);
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void script_read_param(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 value;

    obj->script.pc = cursor + 1;
    value = *cursor;
    obj->unk_226[3] = value & 0xFFF; /* 0x22C */
}

void seq_branch_on_match(SeqReader *reader) {
    u8 *cmd;
    s32 id;
    s32 arg;

    cmd = reader->cursor;
    reader->cursor = cmd + 2;
    id = *(s16 *) cmd;
    reader->cursor = cmd + 4;
    arg = *(s16 *) (cmd + 2);
    if (reader->wanted == (id & 0xFFF)) {
        reader->cursor = reader->table[arg];
    }
}

extern u16 stream_last_u16;
extern u16 D_8011A294;
extern u16 D_8011A2C6;
/* Reads the u16 at the stream cursor (arg+0x20), advances the cursor by 2 bytes,
   and stores the value in three globals. */
void cursor_read_u16_globals(u8 **stream) {
    u8 *cursor;
    u16 value;

    cursor = stream[8];
    stream[8] = cursor + 2;
    value = *(u16 *)cursor;
    stream_last_u16 = value;
    D_8011A294 = value;
    D_8011A2C6 = value;
}

extern s32 boss_meter_flag;
/* Reads the next halfword of the object's script cursor (0x20). When D_8011C9D0 is 1, the halfword
 * indexes the object's table (0x1C) and the cursor jumps to that entry. */
void obj_cursor_read_jump(Object *obj) {
    s16 *cursor;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    if (boss_meter_flag == 1) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Takes the halfword at the cursor and advances the cursor by one halfword. */
void cursor_read_u16(ReadCursor *r) {
    u8 *cur = r->cursor;

    r->cursor = cur + 2;
    r->value = *(u16 *)cur;
}

void escaping_boat_m4_boss_move(Object *obj);
void escaping_boat_m4_boss_face_camera(Object *obj);
void escaping_boat_m4_boss_spawn_hull_fx(Object *obj);
void escaping_boat_m4_boss_update(Object *obj, ObjHandler *handler) {
    obj->vz = 0;
    obj->vx = 0;
    escaping_boat_m4_boss_move(obj);
    if (obj->script_flag != 0 && obj->next_state == handler->state) {
        switch (obj->next_state) {
        case 0:
        case 2:
            break;
        case 1:
            obj->next_state = 2;
            break;
        default:
            obj->next_state = 0;
            break;
        }
    }
    obj_script_step(obj, handler);
    escaping_boat_m4_boss_face_camera(obj);
    obj->vars.escaping_boat_m4_boss.frame_counter++;
    if ((obj->vars.escaping_boat_m4_boss.frame_counter & 7) == 0) {
        escaping_boat_m4_boss_spawn_hull_fx(obj);
    }
    meter_set(obj->health, 0x2EE0);
}

void escaping_boat_m4_boss_throttle(Object *obj);
void escaping_boat_m4_boss_steer(Object *obj);
extern s32 boss_active_flag;
void escaping_boat_m4_boss_move(Object *obj) {
    s32 angle;
    u16 phase;
    s32 step;

    obj->vars.bob.current.speed = get_flow_max();
    flow_sample(&obj->vars.bob.current, (s32)obj->width, &obj->x, &obj->vx, &obj->turn);
    obj->yaw = (u16)(obj->yaw + obj->turn);
    escaping_boat_m4_boss_throttle(obj);
    limit_move(&obj->x, &obj->vx);
    step = obj->vz;
    obj->vars.escaping_boat_m4_boss.target_z = obj->vars.escaping_boat_m4_boss.target_z + step;
    if (obj->vars.bob.timer != 0 && boss_active_flag == 1) {
        phase = obj->vars.bob.phase + 0x10;
        angle = *(s16 *)&rcossin_tbl[phase & 0xFFF];
        obj->vars.bob.phase = phase;
        if (angle < 0) {
            angle += 0x1F;
        }
        obj->unk_226[3] = (s16)((u32)angle >> 5);
    }
    escaping_boat_m4_boss_steer(obj);
    limit_move(&obj->x, &obj->vx);
}

extern s32 boss_retreat_flag;
void escaping_boat_m4_boss_throttle(Object *self) {
    u8 *obj = (u8 *)self;
    s32 speed = *(s32 *)(obj + 0x258);
    s32 d = ((cam_pos_z - *(s32 *)(obj + 0x250)) >> 12) + *(s16 *)(obj + 0x260);

    s32 angle = *(s16 *)(obj + 0x26C);

    if (boss_retreat_flag == 0) {
        if (ABS(d) <= 0x100) {
            if (speed > 0) {
                speed -= 0x400;
                speed = MAX(MIN(speed, 0x14000), 0);
            } else if (speed < 0) {
                speed += 0x400;
                speed = MAX(MIN(speed, 0), -0x14000);
            }
        } else {
            if (d > 0) speed += 0x400;
            if (d < 0) speed -= 0x400;
            speed = MAX(MIN(speed, 0x14000), -0x14000);
        }
    } else {
        speed += 0x1000;
        speed = MAX(MIN(speed, 0x20000), -0x20000);
    }
    *(s32 *)(obj + 0x258) = speed;
    fly_strafe(angle, speed >> 12, (s32 *)(obj + 0x210), (s32 *)(obj + 0x208));
}

/* vars.words[2], [3]: target offsets; [5]: turn rate; s16 at 0x26C: bearing offset. Steers a turn rate toward the bearing to a target and moves the object by the resulting step. */
void escaping_boat_m4_boss_steer(Object *obj) {
    Vec3 *step = scratch_alloc(0x10);
    s32 dz, dx, ang, diff, rate;

    s32 base_210 = obj->vz;
    dz = obj->z - (obj->vars.escaping_boat_m4_boss.target_z - base_210);
    dx = obj->x - obj->vars.escaping_boat_m4_boss.target_x;
    ang = (atan2(dz >> 12, dx >> 12) - *(s16 *)&obj->vars.escaping_boat_m4_boss.heading) & 0xFFF;
    rate = obj->vars.escaping_boat_m4_boss.turn_rate;
    diff = (ang - obj->unk_226[3]) & 0xFFF;
    if ((u32)(diff - 5) >= 0xFF8) {
        if (rate > 0) {
            rate -= 0x200;
            rate = MAX(MIN(rate, 0x8000), 0);
        } else if (rate < 0) {
            rate += 0x200;
            rate = MAX(MIN(rate, 0), -0x8000);
        }
    } else {
        if (diff >= 0x800) {
            rate += 0x200;
        } else {
            rate -= 0x200;
        }
        rate = MAX(MIN(rate, 0x8000), -0x8000);
    }
    obj->vars.escaping_boat_m4_boss.turn_rate = rate;
    angles_to_vector(ang + (rate >> 12), 0, 0x900, &step->x, &step->y, &step->z);
    scratch_top -= 0x10;
    obj->vz += step->z - dz;
    obj->vx += step->x - dx;
}

void escaping_boat_m4_boss_face_camera(Object *obj) {
    Vec3 *vec = scratch_alloc(0x10);
    s32 dx, dz;

    vec->y = -0x1B2;
    vec->z = -0x51;
    vec->x = 0;
    rotate_xz_twice(obj->yaw, -obj->pitch, &vec->x, &vec->y, &vec->z);
    dz = obj->z;
    vec->z = ((VEC_80139584.z - dz) >> 12) - vec->z;
    dx = obj->x;
    vec->x = ((VEC_80139584.x - dx) >> 12) - vec->x;
    obj->vars.escaping_boat_m4_boss.yaw = angle_approach(obj->vars.escaping_boat_m4_boss.yaw, atan2(vec->z, vec->x), 0x10);
    scratch_top -= 0x10;
}

void obj_spawn_at_local_point(Object *obj, Vec3 *pos);
/* Calls obj_spawn_at_local_point three times with a scratch vector holding the three offsets. */
void escaping_boat_m4_boss_spawn_hull_fx(Object *obj) {
    Vec3 *v = scratch_alloc(0x10);

    v->x = 0;
    v->y = 0;
    v->z = 0x3D9;
    obj_spawn_at_local_point(obj, v);
    v->x = 0x249;
    v->y = 0;
    v->z = -0x20;
    obj_spawn_at_local_point(obj, v);
    v->x = -0x24A;
    v->y = 0;
    v->z = -0x20;
    obj_spawn_at_local_point(obj, v);
    scratch_top -= 0x10;
}

s32 rocket_boat_wake_spawn(Vec3 *pos, SVECTOR *rot, s32 arg2, s32 arg3, s32 arg4);
/* Rotates a position by the object's angles, adds the object's position, then calls rocket_boat_wake_spawn with the
 * angles in scratch. */
void obj_spawn_at_local_point(Object *obj, Vec3 *pos) {
    SVECTOR *ang = scratch_alloc(8);

    ang->vx = obj->pitch;
    ang->vy = obj->yaw;
    ang->vz = obj->roll;
    rotate_xz_twice(ang->vy, -ang->vx, &pos->x, &pos->y, &pos->z);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->z += obj->z >> 12;
    ang->vy += 0x800;
    rocket_boat_wake_spawn(pos, ang, get_model_slot_base() + 0x50, 8, 0xAA);
    scratch_top -= 8;
}

extern s32 boss_meter_flag;
extern s32 boss_retreat_flag;
void escaping_boat_m4_boss_phase2(Object *obj, ObjHandler *handler) {
    if (boss_meter_flag == 0) {
        obj_hit_clear(obj->index);
    }
    if (boss_retreat_flag == 0) {
        obj_state_run(obj, handler);
    }
}

extern s32 d_80119E84;
s32 escaping_boat_m4_boss_destroy(Object *obj) {
    s32 type_offset;
    s32 asset_id;

    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->next_state = 4;
    meter_set_mode(0);
    mission_timer_active_set(0);
    warning_ack_set(0);
    set_mission_active(0);
    set_d_801202C8(0);
    type_offset = obj->type.unk_0E;
    asset_id = *(s32 *)obj->asset;
    d_80119E84 = 0;
    enemy_spawn_copy(obj, type_offset + model_slot_pchr(asset_id), 1);
    obj_free(obj);
    return 0;
}

/* Same code as func_800C31C4 (s10). */
void escaping_boat_m4_boss_stop_sound(Object *obj) {
    sound_stop(obj->vars.escaping_boat_m4_boss.sound_handle); /* 0x264 */
}

s32 obj_pose_blend_index(Object *obj, s32 base);
s32 escaping_boat_m4_boss_attach_part(Object *obj, s32 arg);
void escaping_boat_m4_boss_draw_hull_fx(Object *obj);
void escaping_boat_m4_boss_draw(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s16 *aim;
    s16 *rot;
    s32 model;
    s32 colour;
    s32 pitch;
    u16 roll;

    pos = scratch_alloc(0x10);
    aim = scratch_alloc(8);
    rot = scratch_alloc(8);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    model = obj_pose_blend_index(obj, 0);
    if (obj->hit <= 0) {
        colour = 0;
    } else {
        colour = 0x60C0FF;
        /* keeps the branch: without it GCC merges the arms and can't fold colour >> 24 (the spark tail index) to 0 */
        __asm__("");
    }
    model = escaping_boat_m4_boss_attach_part(obj, model);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    spark_add_u(pos[0], pos[1], pos[2], rot[1], rot[0], roll, model, colour);
    escaping_boat_m4_boss_draw_hull_fx(obj);
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    scratch_top -= 8;
    aim[0] = obj->width;
    aim[1] = obj->height;
    aim[2] = obj->unk_1E8[0];
    aim_marker_draw(2, (SVECTOR *)aim, (Vec3 *)pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}


/* Same code as obj_pose_range_blend (s04). */
s32 obj_pose_blend_index(Object *obj, s32 base) {
    s32 blend[4]; /* start, end, weight, 0x1000 - weight */

    base += model_slot_pchr(*(s32 *)obj->asset);
    if (obj->type.unk_0C != obj->type.unk_0E) {
        blend[0] = obj->type.unk_0C + base;
        blend[1] = obj->type.unk_0E + base;
        blend[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        blend[3] = 0x1000 - blend[2];
        return pchr_blend(blend[0], blend[1], blend[2], 0);
    }
    return obj->type.unk_0C + base;
}

extern Rec8013C970 seq_slots[];
s32 escaping_boat_m4_boss_attach_part(Object *obj, s32 arg) {
    s32 result = -1;
    s16 *rot;
    s16 *rot2;
    s32 *first;
    s32 yaw;

    if (arg >= 0) {
        rot = scratch_alloc(8);
        rot2 = scratch_alloc(8);
        pchr_lists_build(arg);
        result = pchr_copy_slot(arg);
        first = pchr_poses_build(result);
        seq_slots[result & 0x7FF].first = first;
        rot[1] = -0x1B2;
        rot[0] = 0;
        rot[2] = -0x51;
        rot2[0] = 0;
        yaw = obj->yaw;
        rot2[1] = (u16) obj->vars.escaping_boat_m4_boss.yaw - yaw;
        rot2[2] = 0;
        pose_rotate_range(first, 2, 1, rot, rot2);
        scratch_top -= 8;
        scratch_top -= 8;
    }
    return result;
}

void obj_exhaust_emit(Object *obj, Vec3 *pos);
/* Calls obj_exhaust_emit three times with a scratch vector holding the three offsets. */
void escaping_boat_m4_boss_draw_hull_fx(Object *obj) {
    Vec3 *v = scratch_alloc(0x10);

    v->x = 0;
    v->y = 0;
    v->z = 0x4CC;
    obj_exhaust_emit(obj, v);
    v->x = 0x249;
    v->y = 0;
    v->z = 0x5F;
    obj_exhaust_emit(obj, v);
    v->x = -0x24A;
    v->y = 0;
    v->z = 0x5F;
    obj_exhaust_emit(obj, v);
    scratch_top -= 0x10;
}

static inline void spark_add_head2(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
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
void obj_exhaust_emit(Object *obj, Vec3 *pos) {
    s16 *rot;
    s32 base;
    s32 phase;
    s16 step;
    s32 index;
    s32 value;
    s32 roll;
    s32 pitch;
    s32 frame_pad[2]; /* the original's stack frame is 8 bytes larger; keeps the saved registers at the same offsets */

    rot = scratch_alloc(8);
    base = model_slot_pchr(*(s32 *)obj->asset);
    phase = (s16)obj->vars.escaping_boat_m4_boss.frame_counter;
    if (phase < 0) {
        phase += 3;
    }
    step = phase >> 2;
    index = (s16)(step % 3);
    index += 0x1D;
    value = base + index;

    rotate_xz_twice(obj->yaw, -obj->pitch, (s32 *)pos, &pos->y, &pos->z);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->z += obj->z >> 12;

    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    spark_add_head2(&spark_list, pos->x, pos->y, pos->z, rot[1] + 0x80, rot[0], roll - 0x100, value, 0);
    spark_add_head2(&spark_list, pos->x, pos->y, pos->z, rot[1] - 0x80, rot[0], rot[2] + 0x100, value, 0);
    scratch_top -= 8;
}

extern u8 escaping_boat_m4_boss_asset[];
extern ScriptCallEntry D_8011A370[];
extern StateEntry D_8011A408[];
extern s16 *escaping_boat_m4_boss_type_data[];
extern s16 *escaping_boat_m4_boss_script_start;
extern s16 *escaping_boat_m4_boss_data[];
void escaping_boat_m4_boss_draw(Object *obj, ObjHandler *handler);
void escaping_boat_m4_boss_set_target(Object *obj);
void escaping_boat_m4_boss_spawn_side_fx(Object *obj);
void obj_set_bounds_from_asset(Object *obj, s32 offset, s32 arg);
s32 escaping_boat_m4_boss_spawn(Placement *place) {
    Object *obj;
    s32 ret;
    s32 sound;
    s32 kind;
    void *type_data;

    ret = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = escaping_boat_m4_boss_phase0;
        obj->handlers[1].fn = escaping_boat_m4_boss_update;
        obj->handlers[2].fn = escaping_boat_m4_boss_phase2;
        obj->handlers[3].fn = escaping_boat_m4_boss_draw;
        obj->callback = (s32) escaping_boat_m4_boss_destroy;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->destructor = escaping_boat_m4_boss_stop_sound;
        kind = place->unk_04[1];
        obj->asset = escaping_boat_m4_boss_asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = D_8011A370;
        obj->state_table = D_8011A408;
        type_data = escaping_boat_m4_boss_type_data;
        obj->unk_1C6 = 0;
        do { } while (0);
        obj->kind = kind;
        obj->script.data = type_data;
        obj->script.unk_0A = 0;
        obj->script.pc = escaping_boat_m4_boss_script_start;
        script_start((Script *) obj, escaping_boat_m4_boss_data[0], (s32) escaping_boat_m4_boss_data);
        obj_init_from_place(obj, place, 0x27);
        obj_set_bounds_from_asset(obj, 0, 0xCCC);
        obj->health = 0x2EE0;
        obj->score = 0x3A98;
        obj->damage = 0;
        obj->unk_226[3] = 0;
        obj_hit_set_unk06(obj->index, 0);
        obj_hit_flag_set(obj->index, 0x80);
        obj->vars.escaping_boat_m4_boss.timer = 0;
        obj->vars.escaping_boat_m4_boss.frame_counter = 0;
        obj->vars.escaping_boat_m4_boss.yaw = 0;
        obj->vars.escaping_boat_m4_boss.state = 0;
        obj->vars.escaping_boat_m4_boss.unused_260 = 0xA00;
        obj->vars.escaping_boat_m4_boss.unused_262 = 0;
        rec_reset((PartSlot *) &obj->vars.escaping_boat_m4_boss.part_slot);
        escaping_boat_m4_boss_set_target(obj);
        show_line((s32) "#1Warning!  Warning! Unknown code sensedand approaching!\xA1");
        msg_show_slot(1, -1);
        warning_ack_set(1);
        area_load_request(0x5A);
        obj_actors_clear_index();
        obj_hit_clear(obj->index);
        obj->score = 0x3A98;
        grid_active_set(0);
        boss_active_flag = 0;
        boss_meter_flag = 0;
        d_80119E84 = 1;
        boss_retreat_flag = 0;
        rocket_boat_count = 0;
        sound = sound_start(SND_BOAT_ENGINE_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
        obj->vars.escaping_boat_m4_boss.sound_handle = sound;
        sound_attach(sound, &obj->x, NULL);
        sound_set_flag_bit2(obj->vars.escaping_boat_m4_boss.sound_handle, 1);
        escaping_boat_m4_boss_spawn_side_fx(obj);
        ret = 1;
    }
    return ret;
}

void obj_set_bounds_from_asset(Object *obj, s32 offset, s32 arg) {
    SVECTOR *v = scratch_alloc(8);
    s32 span;
    s32 vy;
    s16 w;

    model_part_extents(offset + ((s32 *)obj->asset)[1], arg, (s16 *)v);
    obj->unk_190 = arg;
    obj->width = v->vx;
    obj->height = v->vy;
    obj->unk_1E8[0] = v->vz;
    span = v->vz;
    vy = v->vy;
    if (span < v->vx) {
        span = v->vx;
    }
    w = span;
    obj->extents[0] = w;
    obj->extents[1] = vy;
    obj->extents[2] = w;
    obj->bound_radius = isqrt(length_sq(span, vy, span));
    scratch_top -= 8;
}

void escaping_boat_m4_boss_set_target(Object *obj) {
    s32 *offset;
    s32 yaw;
    s32 base_yaw;

    offset = scratch_alloc(0x10);
    offset[2] = -0x900;
    offset[0] = 0;
    offset[1] = 0;
    base_yaw = obj->unk_226[3];
    yaw = obj->vars.enemy.walk_state + base_yaw;
    rotate_xz_twice(yaw, 0, &offset[0], &offset[1], &offset[2]);
    obj->vars.escaping_boat_m4_boss.target_z = (offset[2] << 12) + obj->z;
    obj->vars.escaping_boat_m4_boss.target_x = (offset[0] << 12) + obj->x;
    obj->vars.escaping_boat_m4_boss.unused_258 = 0xFFFEC000;
    obj->vars.escaping_boat_m4_boss.turn_rate = 0;
    scratch_top -= 0x10;
}

void obj_spawn_at_local_side(Object *obj, s32 *pos, u16 *rot, s32 side);
/* Spawns two effects at +/-0x200 yaw offsets from the object's facing. */
void escaping_boat_m4_boss_spawn_side_fx(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    u16 *rot = scratch_alloc(8);

    rot[0] = obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    angles_to_vector(0x200, 0, 0x700, pos, &pos[1], &pos[2]);
    pos[0] >>= 12;
    pos[2] = (pos[2] >> 12) - 0x900;
    pos[1] >>= 12;
    obj_spawn_at_local_side(obj, pos, rot, 0);
    angles_to_vector(-0x200, 0, 0x700, pos, &pos[1], &pos[2]);
    pos[0] >>= 12;
    pos[2] = (pos[2] >> 12) - 0x900;
    pos[1] >>= 12;
    obj_spawn_at_local_side(obj, pos, rot, 1);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 rocket_boat_spawn_side(Object *parent, s32 *pos, u16 *rot, s32 side);
void obj_spawn_at_local_side(Object *obj, s32 *pos, u16 *rot, s32 side) {
    rotate_xz_twice(obj->yaw, 0, &pos[0], &pos[1], &pos[2]);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;
    rocket_boat_spawn_side(obj, pos, rot, side);
}

void stage_spawn_slots_reset(void) {
    spawn_slots_reset();
}

/* While boss_retreat_flag is set, clears the object's unk_17A and sets its unk_226[3] to +0x200 or -0x200 by the sign of the object's vars.h.unk_248; with boss_retreat_flag clear, only obj_link_script_run runs. */
void rocket_boat_phase0(Object *obj) {
    s16 value;

    if (boss_retreat_flag == 0) {
        obj_link_script_run();
        return;
    }
    value = -0x200;
    obj->unk_17A = 0;
    if (obj->vars.rocket_boat_spawn_side_obj.side == 0) {
        value = 0x200;
    }
    obj->unk_226[3] = value;
}

s32 rocket_boat_rocket_spawn(s32 unused, s32 *pos, s16 *rot, u32 index, s32 speed, s32 *vec);
void rocket_boat_fire_drift(Object *obj) {
    s32 rel_x, rel_y, rel_z;
    s32 off_x, off_y, off_z;
    s32 yaw1, pitch1, yaw2, pitch2;
    s32 pitch_turn, yaw_a, yaw_b;
    s32 *pos;
    s16 *turn;
    s32 *vel;
    VECTOR *player;

    pos = scratch_alloc(0x10);
    turn = scratch_alloc(8);
    vel = scratch_alloc(0x10);
    player = scratch_alloc(0x10);

    rel_z = 0x52;
    off_y = -0x109;
    yaw1 = 0;
    pitch1 = 0;
    yaw2 = 0;
    pitch2 = 0;
    rel_x = 0;
    rel_y = 0;
    off_x = 0;
    off_z = -0x20;

    rotate_xz_twice(obj->vars.rocket_boat_spawn_side_obj.aim_yaw, 0, &rel_x, &rel_y, &rel_z);
    pos[0] = off_x + rel_x;
    pos[1] = off_y + rel_y;
    pos[2] = off_z + rel_z;

    rotate_xz_twice(obj->yaw, -obj->pitch, &pos[0], &pos[1], &pos[2]);
    rotate_xz_twice(obj->yaw, -obj->pitch, &off_x, &off_y, &off_z);
    vector_to_angles(pos[0] - off_x, pos[1] - off_y, pos[2] - off_z, &yaw1, &pitch1);

    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;
    player_position_copy(player);

    off_x = player->vx - pos[0];
    off_y = player->vy - pos[1];
    off_z = player->vz - pos[2];
    vector_to_angles(off_x, off_y, off_z, &yaw2, &pitch2);

    pitch_turn = angle_approach(pitch1, pitch2, 0x80);
    yaw_a = yaw1;
    yaw_b = yaw2;
    turn[0] = pitch_turn;
    turn[1] = angle_approach(yaw_a, yaw_b, 0x80);
    turn[2] = 0;

    angles_to_vector(obj->vars.drift.current.angle, 0, get_flow_max(), vel, &vel[1], &vel[2]);
    rocket_boat_rocket_spawn((s32)obj, pos, turn, 1, model_slot_pchr(*(s32 *)obj->asset), vel);

    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 rocket_boat_shot_spawn(Object *obj, Vec3 *pos, SVECTOR *rot, s32 kind, Vec3 *dir);
/* Spawns a shot (rocket_boat_shot_spawn) from a point 0x1F4 ahead of the object, aimed at the camera: the rotation
 * follows the camera direction (yaw offset by 0x800), the shot direction comes from the object's 0x268 angle. */
void rocket_boat_fire(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    Vec3 *dir = scratch_alloc(0x10);
    s32 yaw = 0;
    s32 pitch = 0;

    pos->y = -0xD1;
    pos->x = 0;
    pos->z = -0x1F4;
    rotate_xz_twice(obj->yaw, -obj->pitch, &pos->x, &pos->y, &pos->z);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->z += obj->z >> 12;
    vector_to_angles((VEC_80139584.x >> 12) - pos->x, (VEC_80139584.y >> 12) - pos->y,
                     (VEC_80139584.z >> 12) - pos->z, &yaw, &pitch);
    rot->vx = angle_approach(obj->pitch, pitch, 0x200);
    rot->vy = angle_approach(obj->yaw + 0x800, yaw, 0x80);
    rot->vz = 0;
    angles_to_vector(*(s16 *)&obj->vars.enemy.unk_268, 0, get_flow_max(), &dir->x, &dir->y, &dir->z);
    sound_play_at_units(SND_PROJECTILE_FIRE_ALT | SND_GROUP(1), 0x7F, 0x3C, pos);
    rocket_boat_shot_spawn(obj, pos, rot, model_slot_pchr(*(s32 *)obj->asset), dir);
    scratch_top -= 0x10;
    scratch_top -= 0x8;
    scratch_top -= 0x10;
}

s32 rocket_boat_shell_spawn(Object *obj, Vec3 *pos, SVECTOR *ang, s32 kind, Vec3 *dir);
/* When the object is near the camera (xz distance, squared, within 0x1000000): puts a position in front of
 * it (offset rotated by its angles), plays a sound there and calls rocket_boat_shell_spawn with the position, angles
 * and the aim direction. */
void rocket_boat_fire_near(Object *obj) {
    Vec3 *pos;
    SVECTOR *ang;
    Vec3 *dir;

    s32 x = obj->x;

    if (length_sq((VEC_80139584.x - x) >> 12, 0, (VEC_80139584.z - obj->z) >> 12) <= 0x1000000) {
        pos = scratch_alloc(0x10);
        ang = scratch_alloc(8);
        dir = scratch_alloc(0x10);
        pos->y = -0x102;
        pos->x = 0;
        pos->z = -0x9B;
        ang->vx = obj->pitch;
        ang->vy = obj->yaw;
        ang->vz = obj->roll;
        rotate_xz_twice(ang->vy, -ang->vx, &pos->x, &pos->y, &pos->z);
        pos->x += obj->x >> 12;
        pos->y += obj->y >> 12;
        pos->z += obj->z >> 12;
        ang->vx -= 0x400;
        angles_to_vector(*(s16 *)&obj->vars.enemy.unk_268, 0, get_flow_max(), &dir->x, &dir->y, &dir->z);
        sound_play_at_units(SND_WHISTLE | SND_GROUP(2), 0x7F, 0x3C, pos);
        rocket_boat_shell_spawn(obj, pos, ang, model_slot_pchr(*(s32 *)obj->asset), dir);
        scratch_top -= 0x10;
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
}

/* Same code as script_read_param (s04). */
void obj_script_set_angle(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 value;

    obj->script.pc = cursor + 1;
    value = *cursor;
    obj->unk_226[3] = value & 0xFFF; /* 0x22C */
}

/* Same code as seq_branch_on_match (s04). */
void script_jump_if_wanted_matches(SeqReader *reader) {
    u8 *cmd;
    s32 id;
    s32 arg;

    cmd = reader->cursor;
    reader->cursor = cmd + 2;
    id = *(s16 *) cmd;
    reader->cursor = cmd + 4;
    arg = *(s16 *) (cmd + 2);
    if (reader->wanted == (id & 0xFFF)) {
        reader->cursor = reader->table[arg];
    }
}

extern u16 script_mode0_reg0;
extern u16 script_mode0_reg1;
extern u16 script_mode0_reg2;
extern u16 script_mode1_reg0;
extern u16 script_mode1_reg1;
extern u16 script_mode1_ch2;

/* Reads the next halfword of the object's script and stores it in the three channel
   registers of the current mode (0 or 1). */
void obj_script_read_value(Object *obj) {
    u16 *script = (u16 *)obj->script.pc;
    s16 mode;
    u16 value;

    obj->script.pc = script + 1;
    mode = obj->vars.h.unk_248;
    value = *script;
    switch (mode) {
    case 0:
        script_mode0_reg0 = value;
        script_mode0_reg1 = value;
        script_mode0_reg2 = value;
        return;
    case 1:
        script_mode1_reg0 = value;
        script_mode1_reg1 = value;
        script_mode1_ch2 = value;
        return;
    }
}


extern s32 boss_active_flag;
/* Reads the next halfword of the object's script cursor (0x20). When D_8011C9D0 is 1, the halfword
 * indexes the object's table (0x1C) and the cursor jumps to that entry. */
void script_jump_if_mission_flag(Object *obj) {
    s16 *cursor;
    s32 index;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    index = *cursor;
    if (boss_active_flag == 1) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void rocket_boat_move(Object *obj);
void rocket_boat_spawn_effects(Object *obj);
void rocket_boat_aim_at_target(Object *obj);
void rocket_boat_update(Object *obj, ObjHandler *handler) {
    obj->vz = 0;
    obj->vx = 0;
    rocket_boat_move(obj);
    if (obj->script_flag != 0) {
        if (obj->next_state == handler->state) {
            switch (obj->next_state) {
            case 0:
            case 2:
                break;
            case 1:
                obj->next_state = 2;
                break;
            default:
                obj->next_state = 0;
                break;
            }
        }
    }
    obj_script_step(obj, handler);
    rocket_boat_aim_at_target(obj);
    obj->vars.rocket_boat_spawn_side_obj.frame_counter++;
    if (!(obj->vars.rocket_boat_spawn_side_obj.frame_counter & 7)) {
        rocket_boat_spawn_effects(obj);
    }
    if (d_80119E84 == 0) {
        obj->health = 0;
    }
}

void rocket_boat_throttle(Object *obj);
void rocket_boat_steer_to_target(Object *obj);
void rocket_boat_move(Object *obj) {
    s32 *pos;
    s32 *move;
    s32 delta;

    obj->vars.drift.current.speed = get_flow_max();
    pos = &obj->x;
    move = &obj->vx;
    flow_sample(&obj->vars.drift.current, obj->width, pos, move, &obj->turn);
    obj->yaw += obj->turn;
    rocket_boat_throttle(obj);
    limit_move(pos, move);
    delta = obj->vz;
    obj->vars.drift.unk_250 = obj->vars.drift.unk_250 + delta;
    rocket_boat_steer_to_target(obj);
    limit_move(pos, move);
}

void rocket_boat_throttle(Object *obj) {
    s32 diff;
    s32 v;
    s32 ang;
    u8 *o = (u8 *)obj;

    diff = (cam_pos_z - *(s32 *)(o + 0x250)) >> 12;
    v = *(s32 *)(o + 0x258);
    ang = *(s16 *)(o + 0x268);
    if (boss_retreat_flag == 0) {
        if (ABS(diff) <= 0x100) {
            if (v > 0) {
                v -= 0x400;
                v = MAX(MIN(v, 0x14000), 0);
            } else if (v < 0) {
                v += 0x400;
                v = MAX(MIN(v, 0), -0x14000);
            }
        } else {
            if (diff > 0) {
                v += 0x400;
            }
            if (diff < 0) {
                v -= 0x400;
            }
            v = MAX(MIN(v, 0x14000), -0x14000);
        }
    } else {
        v += 0x1000;
        v = MAX(MIN(v, 0x20000), -0x20000);
    }
    *(s32 *)(o + 0x258) = v;
    fly_strafe(ang, v >> 12, (s32 *)(o + 0x210), (s32 *)(o + 0x208));
}

/* vars.words[2], [3]: target offsets; [5]: turn rate; s16 at 0x268: bearing offset. Steers a turn rate toward the bearing to a target and moves the object by the resulting step. */
void rocket_boat_steer_to_target(Object *obj) {
    Vec3 *step = scratch_alloc(0x10);
    s32 dz, dx, ang, diff, rate;

    s32 base_210 = obj->vz;
    dz = obj->z - (obj->vars.rocket_boat_spawn_side_obj.gun_mount_z - base_210);
    dx = obj->x - obj->vars.rocket_boat_spawn_side_obj.gun_mount_x;
    ang = (atan2(dz >> 12, dx >> 12) - *(s16 *)&obj->vars.rocket_boat_spawn_side_obj.unk_268) & 0xFFF;
    rate = obj->vars.rocket_boat_spawn_side_obj.turn_rate;
    diff = (ang - obj->unk_226[3]) & 0xFFF;
    if ((u32)(diff - 5) >= 0xFF8) {
        if (rate > 0) {
            rate -= 0x400;
            rate = MAX(MIN(rate, 0x8000), 0);
        } else if (rate < 0) {
            rate += 0x400;
            rate = MAX(MIN(rate, 0), -0x8000);
        }
    } else {
        if (diff >= 0x800) {
            rate += 0x400;
        } else {
            rate -= 0x400;
        }
        rate = MAX(MIN(rate, 0x8000), -0x8000);
    }
    obj->vars.rocket_boat_spawn_side_obj.turn_rate = rate;
    angles_to_vector(ang + (rate >> 12), 0, 0x700, &step->x, &step->y, &step->z);
    scratch_top -= 0x10;
    obj->vz += step->z - dz;
    obj->vx += step->x - dx;
}

void rocket_boat_aim_at_target(Object *obj) {
    Vec3 *vec = scratch_alloc(0x10);
    s32 dx, dz;

    vec->y = -0x109;
    vec->z = -0x20;
    vec->x = 0;
    rotate_xz_twice(obj->yaw, -obj->pitch, &vec->x, &vec->y, &vec->z);
    dz = obj->z;
    vec->z = ((VEC_80139584.z - dz) >> 12) - vec->z;
    dx = obj->x;
    vec->x = ((VEC_80139584.x - dx) >> 12) - vec->x;
    obj->vars.rocket_boat_spawn_side_obj.aim_yaw = angle_approach(obj->vars.rocket_boat_spawn_side_obj.aim_yaw, atan2(vec->z, vec->x), 0x10);
    scratch_top -= 0x10;
}

void obj_spawn_effect_local(Object *obj, Vec3 *pos);
void rocket_boat_spawn_effects(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = 0x7B;
    pos->y = 0;
    pos->z = -0xA0;
    obj_spawn_effect_local(obj, pos);
    pos->x = -0x7C;
    pos->y = 0;
    pos->z = -0xA0;
    obj_spawn_effect_local(obj, pos);
    scratch_top -= 0x10;
}

/* Rotates a position by the object's angles, adds the object's position, then calls rocket_boat_wake_spawn with the
 * angles in scratch. */
void obj_spawn_effect_local(Object *obj, Vec3 *pos) {
    SVECTOR *ang = scratch_alloc(8);

    ang->vx = obj->pitch;
    ang->vy = obj->yaw;
    ang->vz = obj->roll;
    rotate_xz_twice(ang->vy, -ang->vx, &pos->x, &pos->y, &pos->z);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->z += obj->z >> 12;
    ang->vy += 0x800;
    rocket_boat_wake_spawn(pos, ang, get_model_slot_base() + 0x50, 8, 0xAA);
    scratch_top -= 8;
}

/* Same code as escaping_boat_m4_boss_phase2 (s04). */
void rocket_boat_phase2(Object *obj, ObjHandler *handler) {
    if (boss_active_flag == 0) {
        obj_hit_clear(obj->index);
    }
    if (boss_retreat_flag == 0) {
        obj_state_run(obj, handler);
    }
}

extern s32 rocket_boat_count;
s32 rocket_boat_on_destroy(Object *obj) {
    s32 type_offset;

    obj->unk_17A = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[1].unk_11 = 0;
    obj->next_state = 4;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].state = 0;
    if (d_80119E84 == 1) {
        msg_show_slot(2, 0x78);
        mission_timer_set(mission_timer_get() + 0x708);
    }
    type_offset = obj->type.unk_0E;
    enemy_spawn_copy(obj, type_offset + model_slot_pchr(*(s32 *)obj->asset), 0);
    rocket_boat_count -= 1;
    obj_free(obj);
    return 0;
}


void obj_sound_stop_260(Object *obj) {
    sound_stop(obj->vars.words[6]); /* 0x260 */
}


s32 func_800C2208(Object *obj, s32 base);
s32 rocket_boat_pose_copy(Object *obj, s32 arg);
void rocket_boat_fire_fx(Object *obj);
/* Same code as escaping_boat_m4_boss_draw (s04). */
void rocket_boat_draw(Object *obj, ObjHandler *handler) {
    s32 *pos;
    s16 *aim;
    s16 *rot;
    s32 model;
    s32 colour;
    s32 pitch;
    u16 roll;

    pos = scratch_alloc(0x10);
    aim = scratch_alloc(8);
    rot = scratch_alloc(8);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    model = func_800C2208(obj, 0);
    if (obj->hit <= 0) {
        colour = 0;
    } else {
        colour = 0x60C0FF;
        /* keeps the branch: without it GCC merges the arms and can't fold colour >> 24 (the spark tail index) to 0 */
        __asm__("");
    }
    model = rocket_boat_pose_copy(obj, model);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    spark_add_u(pos[0], pos[1], pos[2], rot[1], rot[0], roll, model, colour);
    rocket_boat_fire_fx(obj);
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    scratch_top -= 8;
    aim[0] = obj->width;
    aim[1] = obj->height;
    aim[2] = obj->unk_1E8[0];
    aim_marker_draw(2, (SVECTOR *)aim, (Vec3 *)pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Same code as obj_pose_range_blend (s04). */
s32 func_800C2208(Object *obj, s32 base) {
    s32 blend[4]; /* start, end, weight, 0x1000 - weight */

    base += model_slot_pchr(*(s32 *)obj->asset);
    if (obj->type.unk_0C != obj->type.unk_0E) {
        blend[0] = obj->type.unk_0C + base;
        blend[1] = obj->type.unk_0E + base;
        blend[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        blend[3] = 0x1000 - blend[2];
        return pchr_blend(blend[0], blend[1], blend[2], 0);
    }
    return obj->type.unk_0C + base;
}

s32 rocket_boat_pose_copy(Object *obj, s32 arg) {
    s32 result = -1;
    s16 *rot;
    s16 *rot2;
    s32 *first;
    s32 yaw;

    if (arg >= 0) {
        rot = scratch_alloc(8);
        rot2 = scratch_alloc(8);
        pchr_lists_build(arg);
        result = pchr_copy_slot(arg);
        first = pchr_poses_build(result);
        seq_slots[result & 0x7FF].first = first;
        rot[1] = -0x109;
        rot[0] = 0;
        rot[2] = -0x20;
        rot2[0] = 0;
        yaw = obj->yaw;
        rot2[1] = (u16) obj->vars.rocket_boat_spawn_side_obj.aim_yaw - yaw;
        rot2[2] = 0;
        pose_rotate_range(first, 1, 1, rot, rot2);
        scratch_top -= 8;
        scratch_top -= 8;
    }
    return result;
}

void rocket_boat_spark_emit(Object *obj, Vec3 *pos, s16 *rot);
/* Plays two effects on the object: each takes a position (a Vec3 with a z of 0x5F) and a three-value s16 rotation
 * (x 0 or 0x7B, the second and third fixed), in the scratchpad, and calls rocket_boat_spark_emit for each. */
void rocket_boat_fire_fx(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);

    pos->x = -0x7C;
    pos->y = 0;
    pos->z = 0x5F;
    rot[1] = 0x80;
    rot[0] = 0;
    rot[2] = -0x100;
    rocket_boat_spark_emit(obj, pos, rot);
    pos->x = 0x7B;
    pos->y = 0;
    pos->z = 0x5F;
    rot[1] = -0x80;
    rot[0] = 0;
    rot[2] = 0x100;
    rocket_boat_spark_emit(obj, pos, rot);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void rocket_boat_spark_emit(Object *obj, Vec3 *pos_v, s16 *rot) {
    s32 *pos = (s32 *)pos_v;
    s32 base;
    s32 phase;
    s16 step;
    s32 index;
    s32 value;
    s32 pitch;
    s32 yaw;
    s32 roll;

    base = model_slot_pchr(*(s32 *)obj->asset);
    phase = (s16)obj->vars.rocket_boat_spawn_side_obj.frame_counter;
    if (phase < 0) {
        phase += 3;
    }
    step = phase >> 2;
    index = (s16)(step % 3);
    index += 0x1D;
    value = base + index;

    rotate_xz_twice(obj->yaw, -obj->pitch, pos, pos + 1, pos + 2);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    pos[2] += obj->z >> 12;

    pitch = obj->pitch;
    rot[0] += pitch;
    yaw = obj->yaw;
    rot[1] += yaw;
    roll = obj->roll;
    rot[2] += roll;

    spark_add_head2(&spark_list, pos[0], pos[1], pos[2], (s16)rot[1], -(s16)rot[0], (s16)rot[2], value, 0);
}

extern ObjModelSlots rocket_boat_asset_slots;
extern ScriptCallEntry rocket_boat_side_call_table[8];
extern StateEntry rocket_boat_side_state_table[5];
extern s16 *rocket_boat_side_anim_table[];
extern s16 *rocket_boat_script_data[82];
extern s16 *rocket_boat_data[];
void rocket_boat_draw(Object *obj, ObjHandler *handler);
void rocket_boat_gun_mount_update(Object *obj);
void obj_init_placement(Object *obj, s32 *pos, u16 *rot, s32 flags);
s32 rocket_boat_spawn_side(Object *parent, s32 *pos, u16 *rot, s32 side) {
    Object *obj;
    s32 ok;
    ObjModelSlots *asset;
    s16 *anim;
    s16 turn;

    ok = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) rocket_boat_phase0;
        obj->handlers[1].fn = rocket_boat_update;
        obj->handlers[2].fn = rocket_boat_phase2;
        obj->handlers[3].fn = rocket_boat_draw;
        obj->callback = (s32) rocket_boat_on_destroy;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->destructor = obj_sound_stop_260;
        obj->kind = parent->kind;
        asset = &rocket_boat_asset_slots;
        *asset = *(ObjModelSlots *) parent->asset;
        obj->asset = asset;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = rocket_boat_side_call_table;
        obj->state_table = rocket_boat_side_state_table;
        obj->unk_1C6 = 0;
        anim = rocket_boat_side_anim_table[side];
        obj->script.data = rocket_boat_script_data;
        obj->script.unk_0A = 0;
        obj->script.pc = anim;
        script_start((Script *) obj, (s16 *) rocket_boat_data[0], (s32) rocket_boat_data);
        obj_init_placement(obj, pos, rot, 0x27);
        obj_set_part_bounds(obj, 0x30, 0xCCC);
        turn = -0x200;
        if (side == 0) {
            turn = 0x200;
        }
        obj->unk_226[3] = turn;
        obj_hit_set_unk06(obj->index, 0);
        obj_hit_flag_set(obj->index, 0x80);
        obj->vars.rocket_boat_spawn_side_obj.side = side;
        obj->vars.rocket_boat_spawn_side_obj.frame_counter = 0;
        obj->vars.rocket_boat_spawn_side_obj.aim_yaw = 0;
        rec_reset((PartSlot *) &obj->vars.rocket_boat_spawn_side_obj.unk_264);
        rocket_boat_gun_mount_update(obj);
        obj->vars.rocket_boat_spawn_side_obj.sound_handle = sound_start(SND_BOAT_ENGINE_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
        sound_attach(obj->vars.rocket_boat_spawn_side_obj.sound_handle, &obj->x, NULL);
        sound_set_flag_bit2(obj->vars.rocket_boat_spawn_side_obj.sound_handle, 1);
        ok = 1;
        rocket_boat_count++;
    }
    return ok;
}

void obj_init_placement(Object *obj, s32 *pos, u16 *rot, s32 flags) {
    obj_hit_clear(obj->index);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj_set_flags(obj, flags);
    obj->health = 0xFA0;
    obj->score = 0xFA0;
    obj->damage = 0;
    obj->unk_17B = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    obj->accel_y = 0x1000;
    obj->placement = NULL;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

void rocket_boat_gun_mount_update(Object *obj) {
    s32 *offset;
    s32 yaw;
    s32 base_yaw;

    offset = scratch_alloc(0x10);
    offset[2] = -0x700;
    offset[0] = 0;
    offset[1] = 0;
    base_yaw = obj->unk_226[3];
    yaw = GUN_VARS(obj)->unk_268 + base_yaw;
    rotate_xz_twice(yaw, 0, &offset[0], &offset[1], &offset[2]);
    obj->vars.rocket_boat_spawn_side_obj.gun_mount_z = (offset[2] << 12) + obj->z;
    obj->vars.rocket_boat_spawn_side_obj.gun_mount_x = (offset[0] << 12) + obj->x;
    obj->vars.rocket_boat_spawn_side_obj.unused_258 = 0xFFFEC000;
    obj->vars.rocket_boat_spawn_side_obj.turn_rate = 0;
    scratch_top -= 0x10;
}

s32 rocket_boat_trace_hit(Object *obj);
/* Per-frame motion update: applies gravity to vy (a sound plays when it turns
 * non-negative), moves the object by its velocity plus the parent offsets, and
 * stores the yaw/pitch of the remaining step. */
void rocket_boat_mortar_update(Object *obj) {
    s32 yaw;
    s32 pitch;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 vy;
    s32 sign;

    step_x = obj->vx;
    vy = obj->vy;
    step_z = obj->vz;
    yaw = 0;
    pitch = 0;
    sign = (u32)vy >> 31;
    vy += 0x1000;
    obj->vy = vy;
    if (sign == 1 && vy >= 0) {
        obj->vars.chaser.target_yaw = sound_start(SND_MORTAR_WHISTLE | SND_GROUP(2), 0x7F, 0, 0);
        sound_attach(obj->vars.chaser.target_yaw, &obj->x, NULL);
        sound_set_flag_bit2(obj->vars.chaser.target_yaw, 1);
        sound_set_flag_bit3(obj->vars.chaser.target_yaw, 1);
    }
    step_x += obj->vars.fly.climb_step;
    step_y = vy + obj->vars.fly.climb;
    step_z += obj->vars.chaser.target_x;
    if (rocket_boat_trace_hit(obj) == 1) {
        obj->hit = 1;
    }
    obj->x += step_x;
    obj->y += step_y;
    obj->z += step_z;
    step_x -= obj->vars.fly.climb_step;
    step_y -= obj->vars.fly.climb;
    step_z -= obj->vars.chaser.target_x;
    vector_to_angles(step_x >> 12, step_y >> 12, step_z >> 12, &yaw, &pitch);
    obj->yaw = *(u16 *)&yaw;
    obj->pitch = *(u16 *)&pitch;
    obj->vars.rocket_boat_shell.unk_24E = rand_a_next();
    obj->vars.rocket_boat_shell.unk_250 = rand_a_next();
}

s32 rocket_boat_spark_spawn(Object *obj, Vec3 *pos, s32 arg);
/* Traces the object's step from its position to position + velocity (whole units); when the trace hits an
 * object plays a sound and spawns an impact, when it hits the world plays a sound and calls rocket_boat_spark_spawn.
 * Returns 1 on any hit. */
s32 rocket_boat_trace_hit(Object *obj) {
    s32 result = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    Vec3 *obj_hit = scratch_alloc(0x10);
    Vec3 *world_hit = scratch_alloc(0x10);
    s16 target;
    s32 hit;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to->x = (obj->x + obj->vx) >> 12;
    to->y = (obj->y + obj->vy) >> 12;
    to->z = (obj->z + obj->vz) >> 12;
    target = 0;
    set_collide_mode(1);
    hit = trace_world(8, obj->vars.rocket_boat_shell.unk_24A, from, to, world_hit);
    if (trace_objects(from, world_hit, obj->vars.rocket_boat_shell.unk_24A, obj_hit, &target) == 1) {
        hit_target_masked(target, 2, obj->yaw, obj->damage);
        result = 1;
        sound_play_at_units(SND_SMALL_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, obj_hit);
        spawn_effect(obj_hit->x, obj_hit->y, obj_hit->z, 0x80000000);
    } else if (hit == 1) {
        sound_play_at_units(SND_ROCKET_WALL_IMPACT | SND_GROUP(2), 0x7F, 0x3C, world_hit);
        rocket_boat_spark_spawn(obj, world_hit, obj->vars.rocket_boat_shell.unk_248);
        result = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return result;
}

extern s32 d_80119E84;

void projectile_impact_phase2(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(x, y, z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(x, y, z, 0x80000000);
        } else {
            return;
        }
    }
    obj_free(obj);
}


void rocket_boat_shell_stop_sound(Object *obj) {
    s32 sound = obj->vars.rocket_boat_shell.sound_handle; /* 0x260 */

    if (sound != 0) {
        sound_stop(sound);
    }
}

void rocket_boat_spark_add_at(Object *obj, Vec3 *pos, s16 *rot, s32 value, s32 colour);
void rocket_boat_mortar_draw(Object *obj) {
    Vec3 *pos = (Vec3 *)scratch_top;
    SVECTOR *rot;
    s32 n;
    s32 frame;
    s32 x, y, z;
    s32 rx, ry, neg;
    u16 rz;
    SparkRec *s;
    SparkList *list;
    u8 *tail;
    s32 step, mid, colour;

    frame = obj->vars.rocket_boat_shell.unk_248 + 0x48;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    scratch_top += 0x10;
    rot = (SVECTOR *)scratch_top;
    scratch_top += 8;
    neg = obj->pitch;
    neg = -neg;
    rot->vx = neg;
    rot->vy = obj->yaw;
    rz = obj->roll;
    rot->vz = rz;
    rx = rot->vx;
    ry = rot->vy;
    x = pos->x;
    y = pos->y;
    z = pos->z;
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
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
    if (obj->vars.rocket_boat_shell.timer > 0) {
        s16 e = obj->vars.rocket_boat_shell.unk_24E;
        s16 ph = e % 0x800;
        step = 0x1000 - ph;
        step >>= 5;
        mid = step;
        if (step == 0) {
            mid = 1;
        }
        pos->z = -0x1D;
        colour = (mid << 16) | (step << 8) | step;
        pos->x = 0;
        pos->y = 0;
        rocket_boat_spark_add_at(obj, pos, (s16 *)rot, obj->vars.rocket_boat_shell.unk_248 + 0xB, colour);
        pos->x = 0;
        pos->y = 0;
        pos->z = -0x57;
        rocket_boat_spark_add_at(obj, pos, (s16 *)rot, obj->vars.rocket_boat_shell.unk_248 + 0xA, colour);
        if (obj->vars.rocket_boat_shell.unk_250 % 3 == 0) {
            pos->x = 0;
            pos->y = 0;
            pos->z = -0x44;
            rocket_boat_spark_add_at(obj, pos, (s16 *)rot, obj->vars.rocket_boat_shell.unk_248 + 0xB, colour);
            pos->x = 0;
            pos->y = 0;
            pos->z = -0x84;
            rocket_boat_spark_add_at(obj, pos, (s16 *)rot, obj->vars.rocket_boat_shell.unk_248 + 0xA, colour);
        }
        if (is_paused() == 0) {
            obj->vars.rocket_boat_shell.timer--;
        }
    }
    scratch_top -= 0x8;
    scratch_top -= 0x10;
}

/* Rotates the position by the angles, adds the object's position (fixed point, >> 12) and adds a spark
 * record with zero rotation. The position words are read before the local copy is written (matching). */
void rocket_boat_spark_add_at(Object *obj, Vec3 *pos, s16 *rot, s32 value, s32 colour) {
    Vec3 p;
    s32 x = pos->x;
    s32 y = pos->y;
    s32 z = pos->z;

    p.x = x;
    p.y = y;
    p.z = z;
    rotate_xz_twice(rot[1], rot[0], &p.x, &p.y, &p.z);
    p.x += obj->x >> 12;
    p.y += obj->y >> 12;
    p.z += obj->z >> 12;
    spark_add(p.x, p.y, p.z, 0, 0, 0, value, colour);
}

void rocket_boat_mortar_update(Object *obj);
void rocket_boat_mortar_draw(Object *obj);
void rocket_boat_shell_drift(Object *obj);
void shell_spawn_effect(Object *obj);
s32 rocket_boat_shell_spawn(Object *obj, Vec3 *pos, SVECTOR *ang, s32 kind, Vec3 *dir) {
    s32 vx;
    s32 vy;
    s32 vz;
    Object *shell;
    s32 result;

    result = 0;
    shell = obj_new();
    if (shell != NULL) {
        vx = 0;
        vy = 0;
        vz = 0;
        list_insert_after((Node *) get_obj_list_actors(), &shell->node);
        shell->handlers[1].fn = (void (*)(Object *, ObjHandler *)) rocket_boat_mortar_update;
        shell->handlers[2].fn = (void (*)(Object *, ObjHandler *)) projectile_impact_phase2;
        shell->handlers[3].fn = (void (*)(Object *, ObjHandler *)) rocket_boat_mortar_draw;
        shell->handlers[0].fn = NULL;
        shell->handlers[0].unk_11 = 0;
        shell->handlers[0].state = 0;
        shell->handlers[1].unk_11 = 0;
        shell->handlers[1].state = 0;
        shell->handlers[2].unk_11 = 0;
        shell->handlers[2].state = 0;
        shell->handlers[3].unk_11 = 0;
        shell->handlers[3].state = 0;
        shell->callback = 0;
        shell->destructor = rocket_boat_shell_stop_sound;
        shell->hit = 0;
        obj_hit_clear((s32) shell->index);
        obj_hit_flag_set((s32) shell->index, 0);
        shell->x = pos->x << 12;
        shell->y = pos->y << 12;
        shell->z = pos->z << 12;
        shell->pitch = ang->vx;
        result = 1;
        shell->yaw = ang->vy;
        shell->roll = ang->vz;
        shell->flags = 0x80;
        shell->vars.h.unk_24A = 0x18;
        shell->vars.h.unk_248 = kind;
        shell->vars.h.unk_24C = 2;
        shell->vars.h.unk_24E = 0;
        shell->vars.h.unk_250 = 0;
        shell->vars.words[3] = dir->x;
        shell->vars.words[4] = dir->y;
        shell->vars.words[5] = dir->z;
        shell->damage = 0xE;
        shell->vars.words[6] = 0;
        shell->speed = 0x30;
        angles_to_vector(ang->vy, -ang->vx, 0x30, &vx, &vy, &vz);
        shell->vx = vx;
        shell->vy = vy;
        shell->vz = vz;
        rocket_boat_shell_drift(shell);
        shell_spawn_effect(shell);
    }
    return result;
}

/* Aim a falling object at the camera: count the frames until it lands
 * (speed grows by 0x1000 a frame) and add the per-frame x/z step. */
void rocket_boat_shell_drift(Object *obj)
{
    s32 frames = 0;
    s32 vy = obj->vy;
    s32 height = obj->y + ((player_height / 2) << 12);
    s32 speed;
    s32 dz, dx;

    if (vy >= 0) {
        speed = vy;
    } else {
        speed = -vy;
    }
    while (height <= 0) {
        speed += 0x1000;
        height += speed;
        frames++;
    }
    if (obj->vy >= 0) {
        frames += obj->vy / 0x800;
    } else {
        frames += -obj->vy / 0x800;
    }
    do {
    } while (0);
    dz = obj->z;
    dz = (cam_pos_z - dz) / frames;
    do {
        dx = (cam_pos - obj->x) / frames;
    } while (0);
    obj->vz += dz;
    obj->vx += dx;
}

/* Passes the object's position (whole units) and its halfword at 0x248 + 0x43 to effect_spawn_at. */
void shell_spawn_effect(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    effect_spawn_at(pos, obj->vars.rocket_boat_shell.unk_248 + 0x43, 3, 0x19);
    scratch_top -= 0x10;
}

/* Steps the rocket along its velocity, traces the step against the world and objects, and hits the
 * target or plays the world impact. Sets obj->hit when it hit something. */
void rocket_boat_rocket_update(Object *obj) {
    s16 target[1] = { 0 };
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    Vec3 *obj_hit = scratch_alloc(0x10);
    Vec3 *world_hit = scratch_alloc(0x10);
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 hit;
    s32 roll;

    step_x = obj->vx + obj->vars.snd.sound;
    step_y = obj->vy + obj->vars.rocket_boat_shot.extra_vy;
    step_z = obj->vz + obj->vars.fly.climb_step;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to->x = (obj->x + step_x) >> 12;
    to->y = (obj->y + step_y) >> 12;
    to->z = (obj->z + step_z) >> 12;
    set_collide_mode(1);
    hit = trace_world(8, obj->vars.trace.aim_yaw, from, to, world_hit);
    if (trace_objects(from, world_hit, obj->vars.trace.aim_yaw, obj_hit, target) == 1) {
        hit_target_masked(target[0], 2, obj->yaw, obj->damage);
        spawn_effect(obj_hit->x, obj_hit->y, obj_hit->z, 0x80007F00);
        obj->hit = 1;
    } else if (hit == 1) {
        sound_play_at_units(SND_ROCKET_WALL_IMPACT | SND_GROUP(2), 0x7F, 0x3C, world_hit);
        rocket_boat_spark_spawn(obj, world_hit, obj->vars.rocket_boat_shot.frame_base);
        obj->hit = 1;
    }
    set_collide_mode(0);
    roll = obj->roll;
    roll += 0xAA;
    obj->x += step_x;
    obj->y += step_y;
    obj->z += step_z;
    obj->roll = roll;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}


void rocket_hit_phase2(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(x, y, z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(x, y, z, 0x80000000);
        } else {
            return;
        }
    }
    obj_free(obj);
}


/* Adds a spark record at the object's position and orientation, then runs spark_add_at_obj_offset. */
void spark_add_at_obj_offset(Object *obj);

void s04_rocket_boat_rocket_draw(Object *obj) {
    Vec3 *pos = (Vec3 *)scratch_top;
    SVECTOR *rot;
    s32 n;
    s32 frame;
    s32 x, y, z;
    s32 rx, ry, neg;
    u16 rz;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    frame = obj->vars.rocket_boat_shot.frame_base + 0x40;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    scratch_top += 0x10;
    rot = (SVECTOR *)scratch_top;
    scratch_top += 8;
    neg = obj->pitch;
    neg = -neg;
    rot->vx = neg;
    rot->vy = obj->yaw;
    rz = obj->roll;
    rot->vz = rz;
    rx = rot->vx;
    ry = rot->vy;
    x = pos->x;
    y = pos->y;
    z = pos->z;
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
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
    spark_add_at_obj_offset(obj);
    scratch_top -= 0x8;
    scratch_top -= 0x10;
}

/* Adds a spark record at the object's position, offset by (0, 0, -0x24) rotated by its yaw/pitch. */
void spark_add_at_obj_offset(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s32 word;
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 n;
    s32 x, y, z;

    word = obj->vars.rocket_boat_shot.frame_base + 0x42;
    pos[2] = -0x24;
    pos[0] = 0;
    pos[1] = 0;
    rotate_xz_twice(obj->yaw, -obj->pitch, &pos[0], &pos[1], &pos[2]);
    pos[0] += obj->x >> 12;
    pos[1] += obj->y >> 12;
    z = pos[2] + (obj->z >> 12);
    pos[2] = z;
    list = &spark_list;
    n = SPARK_COUNT;
    x = pos[0];
    y = pos[1];
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
        s->unk_12 = word;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
    scratch_top -= 0x10;
}

void rocket_boat_rocket_update(Object *obj);
void s04_rocket_boat_rocket_draw(Object *obj);
void shot_spawn_effect(Object *obj);
s32 rocket_boat_shot_spawn(Object *obj, Vec3 *pos, SVECTOR *rot, s32 kind, Vec3 *dir) {
    s32 result;
    Object *shot;

    result = 0;
    shot = obj_new();
    if (shot != NULL) {
        s32 vx = 0;
        s32 vy = 0;
        s32 vz = 0;

        list_insert_after((Node *) get_obj_list_actors(), &shot->node);
        shot->handlers[1].fn = rocket_boat_rocket_update;
        shot->handlers[2].fn = (void (*)(Object *, ObjHandler *)) rocket_hit_phase2;
        shot->handlers[0].fn = NULL;
        shot->handlers[0].unk_11 = 0;
        shot->handlers[0].state = 0;
        shot->handlers[1].unk_11 = 0;
        shot->handlers[1].state = 0;
        shot->handlers[2].unk_11 = 0;
        shot->handlers[2].state = 0;
        shot->handlers[3].fn = s04_rocket_boat_rocket_draw;
        shot->handlers[3].unk_11 = 0;
        shot->handlers[3].state = 0;
        shot->callback = 0;
        shot->hit = 0;
        obj_hit_clear(shot->index);
        obj_hit_flag_set(shot->index, 0);
        shot->x = pos->x << 12;
        shot->y = pos->y << 12;
        shot->z = pos->z << 12;
        shot->pitch = rot->vx;
        shot->yaw = rot->vy;
        shot->roll = rot->vz;
        shot->flags = 0x80;
        result = 1;
        shot->vars.h.unk_248 = kind;
        shot->vars.h.unk_24A = 0x18;
        shot->vars.words[1] = dir->x;
        shot->vars.words[2] = dir->y;
        shot->vars.words[3] = dir->z;
        shot->damage = 0xC;
        shot->speed = 0x14;
        angles_to_vector(rot->vy, -rot->vx, 0x14, &vx, &vy, &vz);
        shot->vx = vx;
        shot->vy = vy;
        shot->vz = vz;
        shot_spawn_effect(shot);
    }
    return result;
}

/* Passes the object's position (whole units) and its halfword at 0x248 + 0x43 to effect_spawn_at. */
void shot_spawn_effect(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    effect_spawn_at(pos, obj->vars.rocket_boat_shot.frame_base + 0x43, 3, 0x19);
    scratch_top -= 0x10;
}

s32 escaping_boss_sweep_hit(Object *obj);
void rocket_boat_fragment_spawn(Object *obj, s32 *base, s32 unused, s32 spread);
void rocket_boat_fly_update(Object *obj, ObjHandler *handler) {
    s32 yaw;
    s32 pitch;
    s32 vx;
    s32 vy;
    s32 vz;
    s32 *pos;
    s16 *rot;
    s32 *vel;

    yaw = 0;
    pitch = 0;
    vx = obj->vx;
    vz = obj->vz;
    vy = obj->vy + 0x1000;
    vx += obj->vars.fly.climb;
    obj->vy = vy;
    vy += obj->vars.chaser.target_x;
    vz += obj->vars.chaser.target_yaw;
    if (escaping_boss_sweep_hit(obj) == 1) {
        obj->hit = 1;
    }
    obj->x += vx;
    obj->y += vy;
    obj->z += vz;
    vx -= obj->vars.fly.climb;
    vy -= obj->vars.chaser.target_x;
    vz -= obj->vars.chaser.target_yaw;
    vector_to_angles(vx >> 12, vy >> 12, vz >> 12, &yaw, &pitch);
    obj->yaw = *(u16 *)&yaw;
    obj->pitch = *(u16 *)&pitch;
    *(s16 *)&obj->vars.pair.pad_252[0] = rand_a_next();
    *(s16 *)&obj->vars.pair.pad_252[2] = rand_a_next();
    if (obj->vy >= 0 && obj->hit == 0) {
        pos = scratch_alloc(0x10);
        rot = scratch_alloc(8);
        vel = scratch_alloc(0x10);
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        vel[0] = obj->vars.fly.climb;
        vel[1] = obj->vars.chaser.target_x;
        vel[2] = obj->vars.chaser.target_yaw;
        sound_play_at_units(SND_S04_ROCKET_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
        obj_spawn_shot(obj, pos, rot, 1, obj->vars.pair.side, vel);
        obj_spawn_shot(obj, pos, rot, 2, obj->vars.pair.side, vel);
        obj_spawn_shot(obj, pos, rot, 3, obj->vars.pair.side, vel);
        rocket_boat_fragment_spawn(obj, pos, (s32)rot, 0);
        rocket_boat_fragment_spawn(obj, pos, (s32)rot, 1);
        rocket_boat_fragment_spawn(obj, pos, (s32)rot, 2);
        scratch_top -= 0x10;
        scratch_top -= 8;
        scratch_top -= 0x10;
        obj->hit = 1;
    }
}

void vec3_rotate_xyz(s32 angle_x, s32 angle_y, s32 angle_z, s32 *x, s32 *y, s32 *z);
void rocket_boat_fragment_spawn(Object *obj, s32 *base, s32 unused, s32 spread) {
    s32 *pos;
    s16 *rot;
    s32 *vel;
    s32 step;
    s32 vx;
    s32 vy;
    s32 vz;
    s32 yaw;
    s32 pitch;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(8);
    vel = scratch_alloc(0x10);
    vx = 0;
    vy = 0;
    vz = 0;
    yaw = 0;
    pitch = 0;
    step = (spread << 12) / 3;
    angles_to_vector(0x400, 0x400 - step, 0x18, &vx, &vy, &vz);
    rotate_xz_twice(obj->yaw, -obj->pitch, &vx, &vy, &vz);
    pos[0] = base[0] + (vx >> 12);
    pos[1] = base[1] + (vy >> 12);
    pos[2] = base[2] + (vz >> 12);
    angles_to_vector(-0xAA, 0, 0x18, &vx, &vy, &vz);
    vx >>= 12;
    vy >>= 12;
    vz >>= 12;
    vec3_rotate_xyz(0, 0, 0x155 - step, &vx, &vy, &vz);
    rotate_xz_twice(obj->yaw, -obj->pitch, &vx, &vy, &vz);
    vector_to_angles(vx, vy, vz, &yaw, &pitch);
    {
        s32 rot_pitch = pitch;
        s32 rot_yaw = yaw;
        rot[2] = 0;
        rot[0] = rot_pitch;
        rot[1] = rot_yaw;
    }
    vel[0] = obj->vars.fly.climb;
    vel[1] = obj->vars.chaser.target_x;
    vel[2] = obj->vars.chaser.target_yaw;
    obj_spawn_shot(obj, pos, rot, 4, obj->vars.pair.side, vel);
    scratch_top -= 0x10;
    scratch_top -= 0x8;
    scratch_top -= 0x10;
}

static inline void rotate_pair(s32 angle, s32 *pa, s32 *pb) {
    s32 idx;

    if ((idx = angle & 0xFFF) != 0) {
        s32 c = cos_table[idx].value;
        s32 s = (s16)rcossin_tbl[idx];
        s32 a = *pa;
        s32 b = *pb;
        *pa = (c * a - s * b) >> 12;
        *pb = (s * a + c * b) >> 12;
    }
}
/* Rotates the vector (x, y, z) in place by three angles:
   angle_z in the x/y plane, then angle_y in y/z, then angle_x in z/x. */
void vec3_rotate_xyz(s32 angle_x, s32 angle_y, s32 angle_z, s32 *x, s32 *y, s32 *z) {
    rotate_pair(angle_z, x, y);
    rotate_pair(angle_y, y, z);
    rotate_pair(angle_x, z, x);
}

/* Gravity added to the falling speed each step (1.0 in 4.12 fixed point). */
/* The mortar shell: moves by its velocity plus the per-step offset in vars.words[4..6] (the offset is
 * not kept in the velocity), traces the step against the world, and turns to face its velocity. */
void escaping_boss_mortar_update(Object *obj, ObjHandler *handler) {
    s32 *from = scratch_alloc(0x10);
    s32 vx = obj->vx;
    s32 vz = obj->vz;
    s32 vy = obj->vy + 0x1000;
    s32 *to;
    s32 yaw = 0;
    s32 pitch = 0;
    s32 ax = obj->vars.words[4];
    s32 ay = obj->vars.words[5];
    s32 az = obj->vars.shot.vel_z;
    Vec3 *hit;

    to = scratch_alloc(0x10);
    obj->vy = vy;
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    hit = scratch_alloc(0x10);
    from[2] = obj->z >> 12;
    vx += ax;
    to[0] = (obj->x + vx) >> 12;
    vy += ay;
    to[1] = (obj->y + vy) >> 12;
    vz += az;
    to[2] = (obj->z + vz) >> 12;
    if (trace_world(8, obj->vars.trace.trace_flags, from, to, hit) == 1) {
        effect_spawn_at(hit, get_model_slot_base() + 0x40, 8, 6);
        obj->hit = 1;
    }
    obj->x += vx;
    obj->y += vy;
    obj->z += vz;
    vx -= obj->vars.words[4];
    vy -= obj->vars.words[5];
    vz -= obj->vars.shot.vel_z;
    /* The angles come back as s32 but are kept as the low halfwords. */
    vector_to_angles(vx >> 12, vy >> 12, vz >> 12, &yaw, &pitch);
    obj->yaw = *(u16 *)&yaw;
    obj->pitch = *(u16 *)&pitch;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

void escaping_boss_rocket_update(Object *obj, ObjHandler *handler) {
    s32 yaw;
    s32 pitch;
    s32 vx;
    s32 vy;
    s32 vz;
    s32 *drift;
    s32 *pos;
    s32 speed;
    s32 sum;

    vx = 0;
    vy = 0;
    vz = 0;
    do {
    } while (0);
    if ((s16)obj->vars.h.unk_24E >= 8) {
        obj->vars.h.unk_250 += 0x80;
        obj->vars.h.unk_250 = MAX(MIN((s16)obj->vars.h.unk_250, 0x1000), 0);
    }
    if ((s16)obj->vars.h.unk_24E >= 0x10 && (s16)((s16)obj->vars.h.unk_24E % 6) == 0) {
        pos = (s32 *)scratch_top;
        scratch_top += 0x10;
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = -0x84;
        rotate_xz_twice(obj->yaw, -obj->pitch, &pos[0], &pos[1], &pos[2]);
        pos[0] += obj->x >> 12;
        pos[1] += obj->y >> 12;
        pos[2] += obj->z >> 12;
        effect_spawn_at((Vec3 *)pos, get_model_slot_base() + 0x68, 8, 0xA);
        scratch_top -= 0x10;
    }
    sum = obj->speed + obj->speed_accel;
    speed = MAX(MIN(sum, 0x20000), 0);
    obj->speed = speed;
    if ((u16)(obj->vars.h.unk_24E - 0x30) < 0x60) {
        yaw = 0;
        pitch = 0;
        pos = (s32 *)scratch_top;
        scratch_top += 0x10;
        player_position_copy((VECTOR *)pos);
        vector_to_angles(pos[0] - (obj->x >> 12), pos[1] - (obj->y >> 12), pos[2] - (obj->z >> 12), &yaw, &pitch);
        obj->yaw = angle_approach(obj->yaw, yaw, 0x14);
        obj->pitch = angle_approach(obj->pitch, pitch, 0x14);
        scratch_top -= 0x10;
    }
    angles_to_vector(obj->yaw, -obj->pitch, obj->speed >> 12, &vx, &vy, &vz);
    drift = &obj->vars.words[4];
    vx += *drift++;
    vy += *drift++;
    vz += *drift;
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    if (escaping_boss_sweep_hit(obj) == 1) {
        obj->hit = 1;
    }
    obj->x += vx;
    obj->y += vy;
    obj->z += vz;
    obj->vars.h.unk_24E++;
}

/* Sweeps the object from its position along its velocity (0x208..0x210): a hit on an object spawns an effect
 * there; a hit on the world makes a sound and an effect at the hit point. 1 when anything was hit. */
s32 escaping_boss_sweep_hit(Object *obj) {
    s32 hit_something = 0;
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    Vec3 *obj_hit = scratch_alloc(0x10);
    Vec3 *world_hit = scratch_alloc(0x10);
    s16 target;
    s32 world;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to->x = (obj->x + obj->vx) >> 12;
    to->y = (obj->y + obj->vy) >> 12;
    target = 0;
    to->z = (obj->z + obj->vz) >> 12;
    set_collide_mode(1);
    world = trace_world(8, obj->vars.shot.trace_flags, from, to, world_hit);
    if (trace_objects(from, world_hit, obj->vars.shot.trace_flags, obj_hit, &target) == 1) {
        hit_target_masked(target, 2, obj->yaw, obj->damage);
        hit_something = 1;
        spawn_effect(obj_hit->x, obj_hit->y, obj_hit->z, 0x80007F00);
    } else if (world == 1) {
        if ((s16)obj->vars.h.unk_24A == 0) {
            sound_play_at_units(SND_ROCKET_WALL_IMPACT | SND_GROUP(2), 0x7F, 0x3C, world_hit);
            rocket_boat_spark_spawn(obj, world_hit, obj->vars.h.unk_248);
        } else {
            effect_spawn_at(world_hit, get_model_slot_base() + 0x40, 8, 6);
        }
        hit_something = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return hit_something;
}


void obj_terrain_hit_expire(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(x, y, z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(x, y, z, 0x80000000);
        } else {
            return;
        }
    }
    obj_free(obj);
}


/* Same code as func_800C31C4 (s10). */
void escaping_boss_rocket_destroy(Object *obj) {
    sound_stop(obj->vars.shot.sound_handle); /* 0x264 */
}

void rocket_boat_flare_draw(Object *obj) {
    Vec3 *spark_pos;
    s16 *spark_rot;
    u16 roll;
    s32 pitch;
    s32 base;
    s32 red;
    s32 brightness;
    s32 colour;

    base = obj->vars.h.unk_248;
    spark_pos = scratch_alloc(0x10);
    spark_pos->x = obj->x >> 12;
    spark_pos->y = obj->y >> 12;
    spark_pos->z = obj->z >> 12;
    spark_rot = scratch_alloc(8);
    pitch = obj->pitch;
    spark_rot[0] = -pitch;
    spark_rot[1] = obj->yaw;
    roll = obj->roll;
    spark_rot[2] = roll;

    spark_add_u(spark_pos->x, spark_pos->y, spark_pos->z, spark_rot[1], spark_rot[0], roll, base + 0x18, 0);

    if ((s16)obj->vars.h.unk_24E > 0) {
        brightness = 0x1000 - (s16)((s16)obj->vars.h.unk_252 % 0x800);
        brightness = brightness >> 5;
        red = brightness;
        if (brightness == 0) {
            red = 1;
        }
        colour = (red << 16) | (brightness << 8) | brightness;
        spark_pos->z = -0x3A;
        spark_pos->x = 0;
        spark_pos->y = 0;
        escaping_boss_spark_at_offset(obj, spark_pos, spark_rot, base + 0xB, colour);
        spark_pos->x = 0;
        spark_pos->y = 0;
        spark_pos->z = -0x74;
        escaping_boss_spark_at_offset(obj, spark_pos, spark_rot, base + 0xA, colour);
        if (obj->vars.h.unk_254 % 3 == 0) {
            spark_pos->x = 0;
            spark_pos->y = 0;
            spark_pos->z = -0x60;
            escaping_boss_spark_at_offset(obj, spark_pos, spark_rot, base + 0xB, colour);
            spark_pos->x = 0;
            spark_pos->y = 0;
            spark_pos->z = -0xA0;
            escaping_boss_spark_at_offset(obj, spark_pos, spark_rot, base + 0xA, colour);
        }
        if (!is_paused()) {
            obj->vars.h.unk_24E = (u16)(obj->vars.h.unk_24E - 1);
        }
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void escaping_boss_mortar_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;
    s32 level = obj->vars.h.unk_248 + 0x19;
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

static inline void rocket_spark_head(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
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
void escaping_boss_rocket_draw(Object *obj) {
    s32 *pos;
    s16 *rot;
    s32 pitch;
    s32 roll;
    s32 value;
    s32 colour;
    s32 size;
    s32 shade;

    pos = scratch_alloc(0x10);
    value = obj->vars.h.unk_248 + 0x1A;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    rot = (s16 *)scratch_top;
    scratch_top += 8;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = (u16)obj->roll;
    rot[2] = roll;
    rocket_spark_head(&spark_list, pos[0], pos[1], pos[2], rot[1], rot[0], roll, value, 0);

    if ((s16)obj->vars.h.unk_24E >= 8) {
        value = get_model_slot_base() + 0x72;
        shade = (s16)obj->vars.h.unk_250 >> 5;
        size = shade;
        if (shade == 0) {
            size = 1;
        }
        colour = (size << 16) | (shade << 8) | shade;
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = -0x60;
        rotate_xz_twice(obj->yaw, -obj->pitch, pos, pos + 1, pos + 2);
        pos[0] += obj->x >> 12;
        pos[1] += obj->y >> 12;
        pos[2] += obj->z >> 12;
        spark_add(pos[0], pos[1], pos[2], rot[1] + 0x800, -rot[0], rot[2], value, colour);
    }

    if ((s16)obj->vars.h.unk_24E >= 12) {
        value = get_model_slot_base() + 0x73;
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = -0x3C;
        rotate_xz_twice(obj->yaw, -obj->pitch, pos, pos + 1, pos + 2);
        pos[0] += obj->x >> 12;
        pos[1] += obj->y >> 12;
        pos[2] += obj->z >> 12;
        rocket_spark_head(&spark_list, pos[0], pos[1], pos[2], 0, 0, 0, value, 0);
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Rotates the position by the angles, adds the object's position (fixed point, >> 12) and adds a spark
 * record with zero rotation. The position words are read before the local copy is written (matching). */
void escaping_boss_spark_at_offset(Object *obj, Vec3 *pos, s16 *rot, s32 value, s32 colour) {
    Vec3 p;
    s32 x = pos->x;
    s32 y = pos->y;
    s32 z = pos->z;

    p.x = x;
    p.y = y;
    p.z = z;
    rotate_xz_twice(rot[1], rot[0], &p.x, &p.y, &p.z);
    p.x += obj->x >> 12;
    p.y += obj->y >> 12;
    p.z += obj->z >> 12;
    spark_add(p.x, p.y, p.z, 0, 0, 0, value, colour);
}

// Spawns an object of the given type (0..4) under parent, copying in the
// position, angles, slot and velocity, then runs the type's init routine.
// Returns 1 if an object was spawned, 0 otherwise.
s32 obj_spawn_shot(Object *parent, s32 *pos, u16 *rot, s32 type, s32 slot, s32 *vel) {
    Object *obj;
    register s32 spawned asm("$18");

    spawned = 0;

    if (type < 5U) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after((Node *)get_obj_list_actors(), &obj->node);
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos[0] << 12;
            obj->y = pos[1] << 12;
            obj->z = pos[2] << 12;
            obj->pitch = rot[0];
            obj->yaw = rot[1];
            obj->roll = rot[2];
            obj->vars.h.unk_248 = slot;
            obj->vars.h.unk_24A = type;
            obj->vars.words[4] = vel[0];
            obj->vars.words[5] = vel[1];
            obj->vars.shot.vel_z = vel[2];
            obj->vars.shot.sound_handle = 0;
            switch (type) {
            case 0:
                rocket_boat_launch(obj, parent);
                spawned = 1;
                break;
            case 1:
            case 2:
            case 3:
                escaping_boss_mortar_init(obj, parent);
                spawned = 1;
                break;
            case 4:
                escaping_boss_rocket_init(obj, parent);
                spawned = 1;
                break;
            default:
                spawned = 1;
                break;
            }
        }
    }
    return spawned;
}

void rocket_boat_fly_update(Object *obj, ObjHandler *handler);
void rocket_boat_flare_draw(Object *obj);
/* Sets up the object (handlers, flags, speed 0x28), gives it a velocity along its yaw/pitch, and passes its
 * position (whole units) to effect_spawn_at through a scratch vector. */
void rocket_boat_launch(Object *obj, Object *parent) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 vx;
    s32 vy;
    s32 vz;

    vx = 0;
    vy = 0;
    vz = 0;
    obj->handlers[1].fn = rocket_boat_fly_update;
    obj->handlers[2].fn = (void *)obj_terrain_hit_expire;
    obj->handlers[3].fn = (void *)rocket_boat_flare_draw;
    obj->flags = 0x80;
    obj->vars.shot.trace_flags = 0x26;
    obj->vars.h.unk_24E = 2;
    obj->damage = 0xA;
    obj->speed = 0x28;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.h.unk_250 = 0;
    obj->vars.h.unk_252 = 0;
    obj->vars.h.unk_254 = 0;
    angles_to_vector(obj->yaw, -obj->pitch, 0x28, &vx, &vy, &vz);
    obj->vx = vx;
    obj->vy = vy;
    obj->vz = vz;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    effect_spawn_at(pos, obj->vars.h.unk_248 + 0x43, 3, 0x19);
    scratch_top -= 0x10;
}

void escaping_boss_mortar_update(Object *obj, ObjHandler *handler);
/* Sets up a child that rides on a parent object: three behaviour handlers
   (all idle), a 0x26 timer, the roll from the count at 0x24A, and its
   offset from the parent, rotated by the object's yaw and pitch. */
void escaping_boss_mortar_init(Object *obj, Object *parent) {
    s32 dx = 0;
    s32 dy = 0;
    s32 dz = 0;
    s16 roll;

    obj->handlers[1].fn = escaping_boss_mortar_update;
    obj->handlers[2].fn = obj_terrain_hit_expire;
    obj->handlers[3].fn = (void *)escaping_boss_mortar_draw;
    obj->vars.shot.trace_flags = 0x26;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.h.unk_24E = 0;
    obj->vars.h.unk_250 = 0;
    obj->vars.h.unk_252 = 0;
    obj->vars.h.unk_254 = 0;
    roll = ((*(s16 *)&obj->vars.h.unk_24A - 1) << 0xC) / 3;
    obj->roll = roll;
    angles_to_vector(0x400, 0x400 - roll, 8, &dx, &dy, &dz);
    rotate_xz_twice(obj->yaw, -obj->pitch, &dx, &dy, &dz);
    obj->vx = parent->vx + dx;
    obj->vy = parent->vy + dy;
    obj->vz = parent->vz + dz;
}

void escaping_boss_rocket_update(Object *obj, ObjHandler *handler);
void escaping_boss_rocket_draw(Object *obj);
void escaping_boss_rocket_init(Object *obj, Object *parent) {
    s32 handle;

    obj->handlers[1].fn = escaping_boss_rocket_update;
    obj->handlers[2].fn = (void *)obj_terrain_hit_expire;
    obj->handlers[3].fn = escaping_boss_rocket_draw;
    obj->destructor = escaping_boss_rocket_destroy;
    obj->flags = 0x80;
    obj->vars.shot.trace_flags = 0xC;
    obj->damage = 6;
    obj->speed = 0x8000;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.h.unk_24E = 0;
    obj->vars.h.unk_250 = 0;
    obj->vars.h.unk_252 = 0;
    obj->vars.h.unk_254 = 0;
    obj->speed_accel = 0x999;
    handle = sound_start(SND_ROCKET_ENGINE_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0);
    /* the sound handle lives at 0x264 (vars.words[7]); the sound follows the object's position */
    obj->vars.shot.sound_handle = handle;
    sound_attach(handle, &obj->x, NULL);
    sound_set_flag_bit2(obj->vars.shot.sound_handle, 1);
}

void escaping_boss_fx_burst(void *target);
/* Rocket step: falls, traces its move against the world and objects; hits a target or bursts on a wall. */
void rocket_boat_hit_update(Object *obj) {
    s32 *from = scratch_alloc(0x10);
    s32 *to = scratch_alloc(0x10);
    s32 *hit = scratch_alloc(0x10);
    s32 *world_hit = scratch_alloc(0x10);
    s32 dx;
    s32 dy;
    s32 dz;
    s32 wall;
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;
    s32 pitch;
    s16 target;

    dx = obj->vx;
    dz = obj->vz;
    dy = obj->vy + 0x1000;
    target = 0;
    vel_x = obj->vars.rocket_boat.dir_x;
    vel_y = obj->vars.rocket_boat.dir_y;
    vel_z = obj->vars.rocket_boat.dir_z;
    obj->vy = dy;
    from[0] = obj->x >> 12;
    from[1] = obj->y >> 12;
    from[2] = obj->z >> 12;
    dx += vel_x;
    to[0] = (obj->x + dx) >> 12;
    dy += vel_y;
    to[1] = (obj->y + dy) >> 12;
    dz += vel_z;
    to[2] = (obj->z + dz) >> 12;
    set_collide_mode(1);
    wall = trace_world(8, obj->vars.rocket_boat.trace_flags, from, to, world_hit);
    if (trace_objects(from, world_hit, obj->vars.rocket_boat.trace_flags, hit, &target) == 1) {
        hit_target_masked(target, 2, obj->yaw, obj->damage);
        sound_play_at_units(SND_ROCKET_HIT_TARGET | SND_GROUP(2), 0x7F, 0x3C, hit);
        sound_play_at_units(SND_ROCKET_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, hit);
        spawn_effect(hit[0], hit[1], hit[2], 0x80000000);
        obj->hit = 1;
    } else if (wall == 1) {
        s32 *pos = scratch_alloc(0x10);
        SVECTOR *rot = scratch_alloc(8);
        s32 *dir = scratch_alloc(0x10);

        escaping_boss_fx_burst(obj);
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot->vx = 0;
        rot->vy = 0;
        rot->vz = 0;
        dir[0] = obj->vars.rocket_boat.dir_x;
        dir[1] = obj->vars.rocket_boat.dir_y;
        dir[2] = obj->vars.rocket_boat.dir_z;
        sound_play_at_units(SND_WATER_PLOP | SND_GROUP(1), 0x7F, 0x3C, pos);
        rocket_boat_spawn(obj, pos, rot, 2, obj->vars.rocket_boat.asset, dir);
        scratch_top -= 0x10;
        scratch_top -= 8;
        scratch_top -= 0x10;
        obj->hit = 1;
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    pitch = obj->pitch;
    pitch -= 0xC;
    obj->x += dx;
    obj->y += dy;
    obj->z += dz;
    obj->pitch = pitch;
}

void rocket_boat_fall_update(Object *obj, ObjHandler *handler) {
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *hit = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    s16 target = 0;
    u16 old;
    u16 next;
    u16 counter;
    Vec3 *flash;
    s32 vx = obj->vx;
    s32 vy = obj->vy;
    s32 vz = obj->vz;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    hit->x = (obj->x + vx) >> 12;
    hit->y = (obj->y + vy) >> 12;
    hit->z = (obj->z + vz) >> 12;
    set_collide_mode(1);
    if (trace_objects(from, hit, obj->vars.rocket_boat.trace_flags, to, &target) == 1) {
        hit_target_masked(target, 2, obj->yaw, obj->damage);
        sound_play_at_units(SND_ROCKET_HIT_TARGET | SND_GROUP(2), 0x7F, 0x3C, to);
        sound_play_at_units(SND_ROCKET_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, to);
        spawn_effect(to->x, to->y, to->z, 0x80000000);
        sound_play_at_units(SND_ROCKET_WALL_IMPACT | SND_GROUP(2), 0x7F, 0x3C, to);
        rocket_boat_spark_spawn(obj, to, obj->vars.rocket_boat.asset);
        obj->hit = 1;
    }
    set_collide_mode(0);

    old = obj->vars.rocket_boat.angle;
    next = old + 0x2A;
    obj->vars.rocket_boat.angle = next;
    if ((s16)next >= 0x2001) {
        obj->vars.rocket_boat.angle = old - 0xFD6;
    }

    counter = obj->vars.rocket_boat.fall_counter + 1;
    obj->vars.rocket_boat.fall_counter = counter;
    if ((s16)counter >= 0x200) {
        flash = scratch_alloc(0x10);
        flash->x = obj->x >> 12;
        flash->y = obj->y >> 12;
        flash->z = obj->z >> 12;
        sound_play_at_units(SND_ROCKET_EXPLOSION | SND_GROUP(1), 0x7F, 0x3C, flash);
        spawn_effect(flash->x, flash->y, flash->z, 0x80000000);
        sound_play_at_units(SND_ROCKET_WALL_IMPACT | SND_GROUP(2), 0x7F, 0x3C, flash);
        rocket_boat_spark_spawn(obj, flash, obj->vars.rocket_boat.asset);
        scratch_top -= 0x10;
        obj->hit = 1;
    }
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

void escaping_boss_fx_at_offset(Object *obj, BossFxParams *pos);
void escaping_boss_fx_burst(void *target) {
    BossFxParams *rec = scratch_alloc(0x10);

    rec->x = 0;
    rec->y = 0;
    rec->value = 0x21;
    escaping_boss_fx_at_offset(target, rec);
    rec->x = 0;
    rec->y = 0;
    rec->value = -0xC;
    escaping_boss_fx_at_offset(target, rec);
    rec->x = 0;
    rec->y = 0;
    rec->value = -0x38;
    escaping_boss_fx_at_offset(target, rec);
    rec->x = 0;
    rec->y = 0;
    rec->value = -0x65;
    escaping_boss_fx_at_offset(target, rec);
    rec->x = 0;
    rec->y = 0;
    rec->value = -0x93;
    escaping_boss_fx_at_offset(target, rec);
    scratch_top -= 0x10;
}

/* Rotates the 3-vector at pos by the object's yaw, adds its position (>>12), then hands pos to effect_spawn_at. */
void escaping_boss_fx_at_offset(Object *obj, BossFxParams *pos) {
    rotate_xz_twice(obj->yaw, 0, &pos->x, &pos->y, &pos->value);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->value += obj->z >> 12;
    effect_spawn_at((Vec3 *)pos, get_model_slot_base() + 0x40, 8, 6);
}

s32 rocket_boat_spark_spawn(Object *obj, Vec3 *pos, s32 arg);
/* Frees the object; when it is on a valid cell, not hit, and visible (or d_80119E84 is 0) it first spawns
 * an effect and, if its unk_24A is 2, plays a sound and calls rocket_boat_spark_spawn. */
void rocket_boat_hit_phase2(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    if (obj->hit != 1 && cam_range_check(pos->x, pos->y, pos->z) != 0) {
        if (d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0) {
            spawn_effect(pos->x, pos->y, pos->z, 0x80000000);
            if ((s16)obj->vars.rocket_boat.mode == 2) {
                sound_play_at_units(SND_ROCKET_WALL_IMPACT | SND_GROUP(2), 0x7F, 0x3C, pos);
                rocket_boat_spark_spawn(obj, pos, obj->vars.rocket_boat.asset);
            }
        } else {
            scratch_top -= 0x10;
            return;
        }
    }
    obj_free(obj);
    scratch_top -= 0x10;
}

void rocket_boat_trail_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot;
    s32 n;
    SparkRec *s;
    SparkList *list;
    u8 *tail;
    s32 level = obj->vars.rocket_boat.asset + 0x10;
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

s32 obj_pose_blend_by_angle(Object *obj);
void spark_add_tinted(Object *obj, Vec3 *pos);
/* Adds a spark record at the object's position with its (pitch negated) rotation, valued by
 * obj_pose_blend_by_angle (negative: nothing), then runs spark_add_tinted. */
void rocket_boat_fall_draw(Object *obj, ObjHandler *handler) {
    s32 value = obj_pose_blend_by_angle(obj);
    s32 *pos;
    s16 *rot;
    s32 rx, ry;
    SparkList *list;
    SparkRec *s;
    u8 *tail;
    s32 n;
    u16 roll;
    s32 x, y, z, pitch;

    if (value >= 0) {
        pos = scratch_alloc(0x10);
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        rot = scratch_alloc(8);
        pitch = obj->pitch;
        rot[0] = -pitch;
        rot[1] = obj->yaw;
        roll = obj->roll;
        rot[2] = roll;
        list = &spark_list;
        n = SPARK_COUNT;
        rx = rot[0];
        ry = rot[1];
        x = pos[0];
        y = pos[1];
        z = pos[2];
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
            s->pitch = rx;
            s->roll = roll;
        }
        spark_add_tinted(obj, (Vec3 *)pos);
        scratch_top -= 8;
        scratch_top -= 0x10;
    }
}

s32 obj_pose_blend_by_angle(Object *obj) {
    s32 t[4];
    s32 ret = -1;

    if ((s16)obj->vars.rocket_boat.angle >= 0x1000) {
        t[0] = obj->vars.rocket_boat.asset + 0x12;
        t[1] = obj->vars.rocket_boat.asset + 0x13;
        t[2] = ((s16)rcossin_tbl[obj->vars.rocket_boat.angle & 0xFFF] + 0x1000) / 2;
        t[3] = 0x1000 - t[2];
        ret = pchr_blend(t[0], t[1], t[2], 1);
    }
    return ret;
}

/* Adds a spark at pos, its value blended from keys unk_248+0x15/+0x14 by unk_24E, brightness by the inverse weight. */
void spark_add_tinted(Object *obj, Vec3 *pos) {
    s32 t[4];
    s16 value;
    s32 color;
    s32 n;
    s32 level;
    s32 g;
    SparkRec *s;
    SparkList *list;
    s32 x, y, z;
    u8 *tail;

    t[0] = obj->vars.rocket_boat.asset + 0x15;
    t[1] = obj->vars.rocket_boat.asset + 0x14;
    t[2] = ((s16)obj->vars.rocket_boat.angle * 2) & 0xFFF;
    t[3] = 0x1000 - t[2];
    value = pchr_blend(t[0], t[1], t[2], 0);
    level = t[3];
    level >>= 5;
    g = level;
    if (g == 0) {
        g = 1;
    }
    color = (g << 16) | (level << 8) | level;
    list = &spark_list;
    n = spark_count;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = color;
        tail = list->tail[color >> 24];
        list->tail[color >> 24] = &s->next;
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

void rocket_boat_launch_init(Object *obj, Object *parent);
void rocket_boat_fall_init(Object *obj, Object *parent);
/* Spawns a rocket boat object in the actor list at pos (world units), with the given angles,
   asset and direction vector; mode 0/1 starts it launching, mode 2 falling.
   Returns 1 when spawned, 0 for a bad mode or no free object. */
s32 rocket_boat_spawn(Object *parent, s32 *pos, SVECTOR *rot, s32 mode, s32 asset, s32 *dir) {
    Object *obj;
    s16 roll;
    s32 result = 0;

    if ((u32)mode < 3) {
        obj = obj_new();
        if (obj != NULL) {
            list_insert_after((Node *)get_obj_list_actors(), &obj->node);
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos[0] << 12;
            obj->y = pos[1] << 12;
            obj->z = pos[2] << 12;
            obj->pitch = rot->vx;
            obj->yaw = rot->vy;
            roll = rot->vz;
            obj->vars.rocket_boat.asset = asset;
            obj->vars.rocket_boat.mode = mode;
            obj->roll = roll;
            obj->vars.rocket_boat.dir_x = dir[0];
            obj->vars.rocket_boat.dir_y = dir[1];
            obj->vars.rocket_boat.dir_z = dir[2];
            switch (mode) {
            case 0:
            case 1:
                rocket_boat_launch_init(obj, parent);
                break;
            case 2:
                rocket_boat_fall_init(obj, parent);
                break;
            }
            result = 1;
        }
    }
    return result;
}

void rocket_boat_hit_update(Object *obj);
/* Resets the object's handlers and speed, then sets its velocity from its yaw and pitch
   (the 0x24A mode picks a yaw offset of -0x400 or +0x400; any other value leaves the velocity at 0). */
void rocket_boat_launch_init(Object *obj, Object *parent) {
    s32 vec[3];
    s32 yaw;
    s32 x;
    s32 y;
    s32 z;
    s32 mode;

    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;
    mode = *(s16 *)&obj->vars.rocket_boat.mode;
    obj->handlers[1].fn = rocket_boat_hit_update;
    obj->handlers[2].fn = (void *)rocket_boat_hit_phase2;
    obj->handlers[3].fn = (void *)rocket_boat_trail_draw;
    obj->flags = 0x80;
    obj->vars.rocket_boat.trace_flags = 0x16;
    obj->damage = 0x10;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.rocket_boat.angle = 0;
    obj->vars.rocket_boat.fall_counter = 0;
    obj->speed = 8;
    switch (mode) {
    case 0:
        yaw = obj->yaw - 0x400;
        angles_to_vector(yaw, -obj->pitch, 8, &vec[0], &vec[1], &vec[2]);
        break;
    case 1:
        yaw = obj->yaw + 0x400;
        angles_to_vector(yaw, -obj->pitch, 8, &vec[0], &vec[1], &vec[2]);
        break;
    }
    x = vec[0];
    y = vec[1];
    z = vec[2];
    obj->vx = x;
    obj->vy = y;
    obj->vz = z;
}

void rocket_boat_fall_update(Object *obj, ObjHandler *handler);
void rocket_boat_fall_draw(Object *obj, ObjHandler *handler);
/* Sets up an object with three behaviour handlers (the first slot is cleared, the others are
   set), a fall speed of 0x3E000 and the cleared speed and vy fields. */
void rocket_boat_fall_init(Object *obj, Object *parent) {
    obj->handlers[1].fn = rocket_boat_fall_update;
    obj->handlers[2].fn = (void *)rocket_boat_hit_phase2;
    obj->handlers[3].fn = rocket_boat_fall_draw;
    obj->flags = 0x80;
    obj->vars.rocket_boat.trace_flags = 0x16;
    obj->vars.rocket_boat.angle = 0xC00;
    obj->handlers[0].fn = 0;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = 0;
    obj->vars.rocket_boat.fall_counter = 0;
    obj->damage = 0xA;
    obj->speed = 0;
    obj->vx = 0;
    obj->vy = 0x3E000;
    obj->vz = 0;
}

void rocket_boat_rocket_2_update(Object *obj) {
    s16 target[1] = { 0 };
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    Vec3 *obj_hit = scratch_alloc(0x10);
    Vec3 *world_hit = scratch_alloc(0x10);
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 hit;
    s32 effect;
    s32 offset;

    step_x = obj->vx + obj->vars.chaser.target_x;
    step_y = obj->vy + obj->vars.chaser.target_yaw;
    step_z = obj->vz + obj->vars.chaser.target_z;

    from->x = obj->x >> 12;
    from->y = obj->y >> 12;
    from->z = obj->z >> 12;
    to->x = (obj->x + step_x) >> 12;
    to->y = (obj->y + step_y) >> 12;
    to->z = (obj->z + step_z) >> 12;
    set_collide_mode(1);
    hit = trace_world(8, obj->vars.rocket_boat_rocket.trace_flags, from, to, world_hit);
    if (trace_objects(from, world_hit, obj->vars.rocket_boat_rocket.trace_flags, obj_hit, target) == 1) {
        effect = get_model_slot_base();
        offset = (rand_a_next() % 3) * 4 + 0x30;
        effect += offset;
        hit_target_masked(target[0], 1, obj->yaw, obj->damage);
        effect_spawn_at(obj_hit, effect, 4, 0x40);
        obj->hit = 1;
    } else if (hit == 1) {
        effect_spawn_at(world_hit, get_model_slot_base() + 0x40, 8, 6);
        obj->hit = 1;
    }
    set_collide_mode(0);
    obj->x += step_x;
    obj->y += step_y;
    obj->z += step_z;
    obj->vars.rocket_boat_rocket.random_seed_a = rand_a_next();
    obj->vars.rocket_boat_rocket.random_seed_b = rand_a_next();
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

void rocket_boat_rocket_2_phase2(Object *obj) {
    s32 x;
    s32 y;
    s32 z;

    x = obj->x >> 12;
    y = obj->y >> 12;
    z = obj->z >> 12;
    if (obj->hit == 1 || d_80119E84 == 0 || (obj_hit_damage(obj->index) << 16) > 0 || cam_range_check(x, y, z) == 0) {
        obj_free(obj);
    }
}

extern RocketBoatRocketParams rocket_boat_rocket_params[];
void rocket_boat_emit_spark(Object *obj, s32 *offset, s16 *rot, s32 value, s32 colour);
static inline void spark_add_head_u(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, u16 rz, s32 value, s32 colour) {
    s32 n = SPARK_COUNT;
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
void rocket_boat_rocket_2_draw(Object *obj) {
    s32 *pos;
    SVECTOR *rot;
    s32 p;
    u16 roll;
    s32 value;
    s32 step;
    s32 shade;
    s32 colour;
    s32 level;

    value = obj->vars.rocket_boat_rocket.unk_248 + rocket_boat_rocket_params[obj->vars.rocket_boat_rocket.rocket_type].base;
    pos = (s32 *)scratch_top;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    scratch_top += 0x10;
    rot = scratch_alloc(8);
    p = obj->pitch;
    rot->vx = -p;
    rot->vy = obj->yaw;
    roll = obj->roll;
    rot->vz = roll;
    spark_add_head_u(&spark_list, pos[0], pos[1], pos[2], rot->vy, rot->vx, roll, value, 0);
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], 0, 0, 0, value + 1, 0);
    if (obj->vars.rocket_boat_rocket.draw_countdown > 0) {
        level = (s16)(obj->vars.rocket_boat_rocket.random_seed_a % 0x800);
        step = 0x1000 - level;
        step >>= 5;
        shade = step ? step : 1;
        colour = (shade << 16) | (step << 8) | step;
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = 0;
        rocket_boat_emit_spark(obj, pos, (s16 *)rot, value + 3, colour);
        pos[0] = 0;
        pos[1] = 0;
        pos[2] = 0x48;
        rocket_boat_emit_spark(obj, pos, (s16 *)rot, value + 2, colour);
        if (obj->vars.rocket_boat_rocket.random_seed_b % 3 == 0) {
            pos[0] = 0;
            pos[1] = 0;
            pos[2] = 0x30;
            rocket_boat_emit_spark(obj, pos, (s16 *)rot, value + 3, colour);
            pos[0] = 0;
            pos[1] = 0;
            pos[2] = 0x80;
            rocket_boat_emit_spark(obj, pos, (s16 *)rot, value + 2, colour);
        }
        obj->vars.rocket_boat_rocket.draw_countdown--;
    }
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void rocket_boat_emit_spark(Object *obj, s32 *offset, s16 *rot, s32 value, s32 colour) {
    s32 v[3];
    s32 x = offset[0];
    s32 y = offset[1];
    s32 z = offset[2];

    v[0] = x;
    v[1] = y;
    v[2] = z;
    if (obj->vars.rocket_boat_rocket.rocket_type == 1) {
        v[0] = x >> 1;
        v[1] = y >> 1;
        v[2] = z >> 1;
    }
    rotate_xz_twice(rot[1], rot[0], &v[0], &v[1], &v[2]);
    v[0] += obj->vars.rocket_boat_rocket.spawn_x;
    v[1] += obj->vars.rocket_boat_rocket.spawn_y;
    v[2] += (s16)obj->vars.rocket_boat_rocket.spawn_z;
    spark_add(v[0], v[1], v[2], 0, 0, 0, value, colour);
}

void rocket_boat_rocket_2_update(Object *obj);
void rocket_boat_rocket_2_phase2(Object *obj);
void rocket_boat_rocket_2_draw(Object *obj);
s32 rocket_boat_rocket_spawn(s32 unused, s32 *pos, s16 *rot, u32 index, s32 speed, s32 *vec) {
    s32 vx;
    s32 vy;
    s32 vz;
    Object *obj;
    RocketBoatRocketParams *entry;
    s32 sound;
    s32 result;

    result = 0;
    if (index < 2) {
        obj = obj_new();
        if (obj != NULL) {
            entry = &rocket_boat_rocket_params[index];
            vx = 0;
            vy = 0;
            vz = 0;
            list_insert_after((Node *) get_obj_list_actors(), &obj->node);
            obj->handlers[1].fn = rocket_boat_rocket_2_update;
            obj->handlers[2].fn = rocket_boat_rocket_2_phase2;
            obj->handlers[0].fn = NULL;
            obj->handlers[0].unk_11 = 0;
            obj->handlers[0].state = 0;
            obj->handlers[1].unk_11 = 0;
            obj->handlers[1].state = 0;
            obj->handlers[2].unk_11 = 0;
            obj->handlers[2].state = 0;
            obj->handlers[3].fn = rocket_boat_rocket_2_draw;
            obj->handlers[3].unk_11 = 0;
            obj->handlers[3].state = 0;
            obj->callback = 0;
            obj->hit = 0;
            obj_hit_clear(obj->index);
            obj_hit_flag_set(obj->index, 0);
            obj->x = pos[0] << 12;
            obj->y = pos[1] << 12;
            obj->z = pos[2] << 12;
            obj->pitch = rot[0];
            obj->yaw = rot[1];
            obj->roll = rot[2];
            obj->flags = 0x80;
            obj->vars.rocket_boat_rocket.unk_248 = speed;
            obj->vars.rocket_boat_rocket.rocket_type = index;
            obj->vars.rocket_boat_rocket.trace_flags = entry->unk_02;
            obj->vars.rocket_boat_rocket.spawn_x = pos[0];
            obj->vars.rocket_boat_rocket.spawn_y = pos[1];
            obj->vars.enemy.sound_channel[0] = pos[2];
            obj->vars.rocket_boat_rocket.draw_countdown = 2;
            obj->vars.rocket_boat_rocket.launch_vel_x = vec[0];
            obj->vars.rocket_boat_rocket.launch_vel_y = vec[1];
            obj->vars.rocket_boat_rocket.launch_vel_z = vec[2];
            result = 1;
            obj->damage = entry->unk_04;
            obj->speed = entry->speed;
            angles_to_vector(rot[1], -rot[0], entry->speed, &vx, &vy, &vz);
            obj->vx = vx;
            obj->vy = vy;
            obj->vz = vz;
            sound = sound_start(SND_ROCKET_MOTOR_LOOP | SND_HELD | SND_GROUP(2), 0x7F, 0, 0xA);
            sound_attach(sound, &obj->x, 0);
            sound_set_flag_bit2(sound, 1);
        }
    }
    return result;
}

void rocket_boat_spark_update(Object *obj) {
    u16 frames;

    frames = obj->vars.rocket_boat_spark.frame_count + 1;
    obj->vars.rocket_boat_spark.frame_count = frames;
    if ((s16) frames >= 0x30) {
        obj_free(obj);
    }
}

s32 obj_pose_blend_offset(Object *obj, s32 offset);
/* Adds a spark at the object's position, coloured by how far unk_248 is past 0x24. */
void rocket_boat_spark_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 value;
    s32 color;
    s32 n;
    s32 level;
    SparkRec *s;
    SparkList *list;
    s32 x, y, z;
    u8 *tail;

    scratch_alloc(8);
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    value = obj_pose_blend_offset(obj, 0);
    level = (s16)obj->vars.rocket_boat_spark.frame_count;
    color = 0;
    if (level >= 0x25) {
        s32 g;

        level = ((0x30 - level) << 12) / 12;
        level >>= 5;
        g = level;

        if (g == 0) {
            g = 1;
        }
        color = (g << 16) | (level << 8) | level;
    }
    list = &spark_list;
    n = spark_count;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = color;
        tail = list->tail[color >> 24];
        list->tail[color >> 24] = &s->next;
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
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Interpolates between the two key values (plus offset) by the type's frame/length weight. */
s32 obj_pose_blend_offset(Object *obj, s32 offset) {
    s32 keys[4];
    s32 base;
    s32 value;

    base = offset + obj->vars.rocket_boat_spark.frame_base;
    if (obj->type.unk_0C == obj->type.unk_0E) {
        value = obj->type.unk_0C + base;
    } else {
        keys[0] = obj->type.unk_0C + base;
        keys[1] = obj->type.unk_0E + base;
        keys[2] = ((obj->type.unk_0A + 1) << 12) / obj->type.blend_duration;
        keys[3] = 0x1000 - keys[2];
        value = pchr_blend(keys[0], keys[1], keys[2], 1);
    }
    return value;
}

extern s16 *spark_script_ptr[2];
void obj_init_at(Object *obj, Vec3 *pos, s32 flags);
/* Spawns an object into the actor list with its handlers set up; returns 1 if it was created. */
s32 rocket_boat_spark_spawn(Object *unused, Vec3 *pos, s32 arg2) {
    Object *obj;
    s32 result = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[1].fn = rocket_boat_spark_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = rocket_boat_spark_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->kind = 0;
        script_start((Script *) obj, spark_script_ptr[0], (s32) spark_script_ptr);
        obj_init_at(obj, pos, 1);
        obj->vars.rocket_boat_spark.frame_base = arg2;
        obj->vars.rocket_boat_spark.frame_count = 0;
        effect_spawn_at(pos, arg2 + 0x50, 9, 0xC);
        result = 1;
    }
    return result;
}

void obj_apply_flags(Object *obj, s32 flags);
void obj_init_at(Object *obj, Vec3 *pos, s32 flags) {
    s32 z;

    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj->health = 0;
    obj->score = 0;
    obj->damage = 0;
    obj->unk_17B = 0;
    obj->x = pos->x << 12;
    obj->y = pos->y << 12;
    z = pos->z;
    obj->placement = NULL;
    obj->z = z << 12;
    obj_apply_flags(obj, 0x18);
}

void obj_apply_flags(Object *obj, s32 flags) {
    ObjSnapshot *snap;

    snap = (ObjSnapshot *)&obj->rot_angles;
    obj_snapshot_save(obj, snap);
    if (flags & 0x10) {
        if (flags & 0x80) {
            flags |= 0x40;
        }
        if (flags & 0x40) {
            flags |= 0x20;
        }
    } else {
        flags &= ~0x1F0;
    }
    snap->unk_10 = flags;
    player_refresh_state_scratch(snap);
    obj_snapshot_restore(obj, snap);
}

/* Advances the object's 16-bit counter (0x24E) by its step (0x24C); frees the object once the counter
 * reaches 0x1000 (as signed). */
void rocket_boat_wake_update(Object *obj) {
    u16 counter;

    counter = obj->vars.rocket_boat_wake.phase + obj->vars.rocket_boat_wake.phase_step;
    obj->vars.rocket_boat_wake.phase = counter;
    if ((s16)counter >= 0x1000) {
        obj_free(obj);
    }
}

/* Adds a spark record at the object's position with its (pitch negated) rotation. The colour
 * argument is pool_spawn_scaled of an s16 at 0x248 plus the product of the s16s at 0x24A and 0x24E (>> 12). */
void rocket_boat_wake_draw(Object *obj) {
    s32 *pos = (s32 *)scratch_top;
    s16 *rot;
    s32 base;
    s32 pitch;

    base = obj->vars.rocket_boat_wake.unk_248 + (((s16)obj->vars.rocket_boat_wake.phase * obj->vars.rocket_boat_wake.amplitude) >> 12);
    scratch_top += 0x10;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot = (s16 *)scratch_top;
    scratch_top += 8;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    base = pool_spawn_scaled(base, 0x1666, 0x1666, 0x1666);
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], base, 0);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Same code as speedboat_wake_spawn (s04). */
s32 rocket_boat_wake_spawn(Vec3 *pos, SVECTOR *rot, s32 arg2, s32 arg3, s32 arg4) {
    Object *obj;
    s32 result;
    s16 roll;

    result = 0;
    obj = obj_new();
    if (obj != NULL) {
        result = 1;
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = rocket_boat_wake_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = rocket_boat_wake_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot->vx;
        obj->yaw = rot->vy;
        roll = rot->vz;
        obj->vars.rocket_boat_wake.unk_248 = arg2;
        obj->vars.rocket_boat_wake.amplitude = arg3;
        obj->vars.rocket_boat_wake.phase_step = arg4;
        obj->vars.rocket_boat_wake.phase = 0;
        obj->roll = roll;
    }
    return result;
}
