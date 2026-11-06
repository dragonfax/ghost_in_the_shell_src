/* key_cells: one of s12's own original source files (scripts/objmap.py); part of src/s12/main.c's unit, included there. */

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **get_key_cells(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 grid_flagged_count_get(void) {
    return grid_flagged_count;
}

extern s32 fall_sound_timer;

void sound_pair_reset(void) {
    sound_pair_start();
    fall_sound_timer = 0;
}

extern FlyCam fly_cam;

extern s16 fly_target_pos;
extern s16 D_8012BA06;
extern s16 D_8012BA08;
extern Unaligned8 fly_target_rot;
extern s32 fly_cam_speed;
extern s32 fly_active_flag;
void fly_start(Vec3 *pos, Unaligned8 *src, s32 slot) {
    s32 step_z;
    s32 step_x;
    Vec3 *cam = (Vec3 *) &cam_pos;

    fly_target_pos = slot;
    D_8012BA06 = slot * 2;
    D_8012BA08 = slot;
    *(Unaligned8 *) &fly_target_rot = *src;
    step_z = pos->z - (cam_pos_z >> 12);
    step_x = pos->x - (cam->x >> 12);
    fly_move(atan2(step_z, step_x), 0x480, &step_z, &step_x);
    fly_cam.f4 = 0xFF600000;
    fly_cam.f10 = 0;
    fly_cam.f14 = 0x10000;
    fly_cam.f18 = 0;
    fly_cam_speed = 0;
    step_x += cam->x;
    step_z += cam_pos_z;
    fly_cam.f0 = step_x;
    fly_cam.f8 = step_z;
    fade_level_set(0x1000);
    fly_active_flag = 1;
}

s32 cam_turn_to_angle(s32 target, s32 step) {
    s32 diff;
    s32 turn;

    diff = view_angles_get()[1];
    diff = ((target - diff) << 20) >> 20;
    if (((s16 *)view_matrix_t_get())[4] < 0) {
        diff = -diff;
    }
    if (ABS(diff) < 0x20) {
        return 1;
    }
    if (diff > 0) {
        player_set_input(get_key_config()->action[6], 0);
        diff = MAX(diff - step, 0);
        add_turn(MIN(diff, step));
    } else {
        player_set_input(get_key_config()->action[7], 0);
        turn = diff + step;
        if (turn > 0) {
            turn = 0;
        }
        if (turn < -step) {
            turn = -step;
        }
        add_turn(turn);
    }
    return 0;
}

void func_800CCA24(void) {
}

extern s32 alarm_sound_handle;
extern s32 alarm_armed_flag;

void alarm_arm(void) {
    alarm_sound_handle = 0;
    alarm_armed_flag = 1;
}

extern s32 alarm_sound_handle;
extern s32 alarm_armed_flag;

void alarm_update(void) {
    s32 temp_v0;

    if ((alarm_sound_handle == 0) && (alarm_armed_flag != 0)) {
        temp_v0 = sound_start(SND_PAIR(SND_HOLLOW_WIND_LOOP | SND_HELD | SND_GROUP(2), SND_HOLLOW_WIND_LOOP_ALT | SND_HELD | SND_GROUP(2)), 0x7F, 0, 0);
        alarm_sound_handle = temp_v0;
        sound_set_flag_bit3(temp_v0, 1);
    }
}

extern s32 alarm_sound_handle;
extern s32 alarm_armed_flag;

void alarm_disarm(void) {
    if (alarm_sound_handle != 0) {
        sound_stop(alarm_sound_handle);
        alarm_sound_handle = 0;
    }
    alarm_armed_flag = 0;
}

extern s32 alarm2_sound_handle;

void alarm2_reset(void) {
    alarm2_sound_handle = 0;
}

extern s32 alarm2_sound_handle;

void alarm2_start(void) {
    s32 temp_v0;

    if (alarm2_sound_handle == 0) {
        temp_v0 = sound_start(SND_PAIR(SND_ALARM_LOOP | SND_HELD | SND_GROUP(2), SND_ALARM_LOOP_ALT | SND_HELD | SND_GROUP(2)), 0x7F, 0, 0);
        alarm2_sound_handle = temp_v0;
        sound_set_flag_bit3(temp_v0, 1);
    }
}

extern s32 alarm2_sound_handle;

void alarm2_stop(void) {
    if (alarm2_sound_handle != 0) {
        sound_stop(alarm2_sound_handle);
        alarm2_sound_handle = 0;
    }
}

extern s32 boss_slot_index[3];
/* Returns model_slot_pchr of the stored index boss_slot_index, offset by 0x1F0. */
s32 boss_pchr_get(void) {
    return model_slot_pchr(boss_slot_index[0]) + 0x1F0;
}

void ctrl_set_angle_range(s32 value) {
    s16 *range;
    s32 base;
    s32 *p;
    s32 lo;

    pchr_set_angle_range(boss_pchr_get(), 1, value);
    base = model_slot_pchr(*(s32 *)get_ptr_entry_word2(1));
    p = (s32 *)get_rec_root();
    p = (s32 *)p[2];
    p = (s32 *)p[2];
    p = (s32 *)p[3];
    range = (s16 *)p[5];
    if (value == 0) {
        value = range[2];
    }
    lo = range[0];
    pchr_set_angle_range(base + lo, range[1] - lo + 1, value);
}

extern s32 D_8012B9F0;
extern s32 scene_active_flag;
extern s32 fall_height;
extern s32 area_load_flag;
extern s32 D_80123988[21];
extern s32 D_801239DC[5];
void ctrl_phase2(Object *obj, ObjHandler *handler);
/* Spawns the stage's controller object: list insert, handler setup, globals reset, then the
 * area/sound setup. The placement's halfword at 0x14 picks a row of the area's resource table. */
s32 ctrl_spawn(Placement *record) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    } else {
        list_insert_after((Node *) get_obj_list_b(), (Node *) obj);
        obj->handlers[2].fn = ctrl_phase2;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = NULL;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->vars.ctrl.unused_248 = 0;
        obj->vars.ctrl.unused_24C = 0;
        D_8012B9F0 = 0;
        scene_active_flag = 0;
        fly_active_flag = 0;
        fall_height = 0x40000;
        clamp_set_max_x(0, 1);
        stage_set_offset_x(0x4000);
        boss_slot_index[0] = *((AreaData *)get_area_entry())->rows[(s16)record->health].res->value;
        anim_obj_spawn((s32) D_80123988, (s32) D_801239DC, 0x87, 0x4A, 0);
        interp38b_set_state(2, 0);
        rec_set_pos(1, 0, -0x180, 0);
        ctrl_set_angle_range(0);
        show_line((s32) "#1Warning!  Warning! Multiple fire arms confirmed on the center of the roof.\xA1");
        alarm_arm();
        alarm2_reset();
        area_load_flag = 0;
        return 1;
    }
    return 0;
}

extern s32 scene_active_flag;
void scene_set_pos(Vec3 *pos);
/* Sets up the camera and mover for a fixed scene. */
void scene_cam_setup(void) {
    Vec3 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    Vec3 scene;
    s16 scene_rot[3];
    s32 x;

    mover_offset_set(0x2EE00, -0x36B00, -0x600);
    mover_angles_set(0, 0, 0);
    mover_range_set(0x180, 0x300);
    clamp_set_max_x(0, 0);
    x = 0x2EE00;
    pos->y = -0x35B60;
    pos->x = x;
    pos->z = -0x600;
    rot[0] = 0;
    rot[1] = 0;
    rot[2] = 0;
    player_warp_request((VECTOR *)pos, (UnalignedVec *)rot, -player_angles[0] >> 12);
    set_player_status(get_player_status() | 0x100);
    mover_set((Mover *)get_mover(), 0x200000, 0x800000, 0);
    scratch_top -= 0x18;
    cam_view_pos_set(0x2EE00, -0x343F0, -0xC00);
    fade_level_set(0);
    set_d_801202C8(0);
    scene_active_flag = 1;
    scene.x = x;
    scene.y = -0x343F0;
    scene.z = -0xC00;
    scene_rot[0] = 0;
    scene_rot[1] = 0;
    scene_rot[2] = 0;
    scene_set_pos(&scene);
    scene_set_rot(scene_rot);
    keyframe_table_set_flag(1);
}

void stage_end_camera_rise(void) {
    s16 *angles;
    s32 *offset;
    s32 *move;
    s32 level;
    register s32 clamped asm("$4");
    s32 done;
    s32 height;

    angles = mover_angles_ptr();
    offset = mover_offset_ptr();
    mover_offset_set(offset[0], offset[1] + (fall_height >> 12), offset[2]);
    move = get_flow_move();
    height = fall_height;
    move[0] = 0;
    move[2] = 0;
    height >>= 12;
    move[1] = height << 12;
    cam_look_at_set(offset[0], offset[1], offset[2]);
    if (offset[1] > -0x347D8) {
        level = fade_level_get() + 0x33;
        clamped = 0x1000;
        if (level < 0x1001) {
            clamped = level;
        }
        done = clamped;
        fade_level_set(clamped);
        if (done == 0x1000) {
            mover_angles_set(angles[1], angles[0] - 2, angles[2] - 8);
            cam_view_pos_set(cam_pos >> 12, cam_pos_y >> 12, (cam_pos_z >> 12) - 0x100);
        }
    } else {
        mover_angles_set(angles[1] - 5, angles[0], angles[2]);
    }
}

void stage_end_camera_fall(void) {
    s16 *angles;
    s32 *offset;
    s32 *cam_view;
    s32 *flow;
    s32 z;
    s32 step;
    s32 yaw;
    s32 pitch;
    s32 roll;
    s32 fall;
    s32 mover;

    angles = mover_angles_ptr();
    offset = mover_offset_ptr();
    cam_view = cam_view_pos_get();
    z = offset[2] + 0xC;
    if (z > 0) {
        z = 0;
    }
    if (z >= 0) {
        fall = fall_height - 0x600;
        if (fall < 0) {
            fall = 0;
        }
        fall_height = fall;
    }
    mover_offset_set(offset[0], offset[1] + (fall_height >> 12), z);
    flow = get_flow_move();
    step = fall_height >> 12;
    flow[0] = 0;
    flow[2] = 0;
    flow[1] = step << 12;
    cam_view_pos_set(cam_view[0], cam_view[1] + step, cam_view[2]);
    pitch = angles[1];
    roll = angles[2];
    yaw = angle_approach(angles[0], -0x400, 0x10);
    pitch = angle_approach(pitch, 0, 8);
    roll = angle_approach(roll, 0, 0x20);
    yaw &= 0xFFF;
    if (yaw > 0x800) {
        yaw -= 0x1000;
    }
    pitch &= 0xFFF;
    if (pitch > 0x800) {
        pitch -= 0x1000;
    }
    mover = *get_mover();
    mover = mover * 2 / 3;
    *get_mover() = mover;
    if (fade_level_get() == 0 && yaw == -0x400 && pitch == 0 && fall_height > 0xE000) {
        particle_spawn_near_cam();
        fall_sound_timer += fall_height / 4096;
        if (fall_sound_timer > 0x300) {
            stage_end_fall_sound();
            fall_sound_timer -= 0x300;
        }
    }
    cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
    mover_angles_set(pitch, yaw, roll);
    fade_level_set(fade_level_get() - 0x80);
}

extern s32 fly_cam_z;

void cam_face_target(void) {
    cam_turn_to_angle(atan2(((s32) fly_cam_z >> 0xC) - ((s32) cam_pos_z >> 0xC), (fly_cam.f0 >> 0xC) - ((s32) cam_pos >> 0xC)), 0x10);
}

extern s32 fly_cam_y;
extern s32 fly_cam_vy;
s32 cam_fly_step(void) {
    s32 move_z;
    s32 move_x;
    s32 *view;
    s32 to_y;
    s32 to_x;
    s32 to_z;
    s32 speed;
    s32 v;
    s32 step;
    s32 fade;
    FlyCam *pos;
    s32 *timer;

    pos = &fly_cam;
    speed = fly_cam_speed + 2;
    to_z = (cam_pos_z >> 12) - (fly_cam_z >> 12);
    to_x = (cam_pos >> 12) - (pos->f0 >> 12);
    to_y = (cam_pos_y >> 12) - (fly_cam_y >> 12);
    if (speed > 0x40) {
        speed = 0x40;
    }
    fly_cam_speed = speed;
    fly_move(atan2(to_z, to_x), fly_cam_speed, &move_z, &move_x);
    pos->f0 += move_x;
    fly_cam_z += move_z;
    if (player_y_speed > 0 || to_y > 0) {
        v = fly_cam_speed;
        if (v > 0x30) {
            v = 0x30;
        }
        fly_cam_speed = v;
        timer = &fly_cam_vy;
        step = *timer + 0x1A00;
        if (step > 0x40000) {
            step = 0x40000;
        }
        *timer = step;
        fly_cam_y += step;
        if (player_y_speed == 0 && cam_pos_y < fly_cam_y) {
            fly_cam_y = cam_pos_y;
            *timer = 0;
        }
    }
    view = cam_view_pos_get();
    cam_view_pos_set(view[0] + (move_x / 4 >> 12), view[1] - 8, view[2] + (move_z / 4 >> 12));
    cam_look_at_set(pos->f0 >> 12, pos->f4 >> 12, pos->f8 >> 12);
    if (isqrt(length_sq(to_z, to_x, 0)) < 0x140) {
        sound_pair_reset();
        add_displacement(move_x, 0, move_z);
        fade = fade_level_get() - 0x80;
        if (fade < 0) {
            fade = 0;
        }
        fade_level_set(fade);
    }
    if ((cam_pos_y >> 12) >= -0x257) {
        ctrl_set_angle_range(0x4000);
        if (area_load_flag == 0) {
            area_load_request(0x5A);
            area_load_flag = 1;
        }
    }
    if ((cam_pos_y >> 12) >= -0x3B6) {
        sound_fade_out_start();
    }
    return (cam_pos_y >> 12) >= 0xE00;
}

void cam_chase_step(void) {
    Vec3 *cam = &VEC_80139584;
    s32 step_z;
    s32 step_x;

    /* fly_move's dx output is added to cam->z and its dz output to cam->x. */
    fly_move(atan2((cam->z >> 0xC) - (fly_cam_z >> 0xC), (cam->x >> 0xC) - (fly_cam.f0 >> 0xC)) + 0x400, 0x400, &step_z, &step_x);
    cam_view_pos_set((step_x + cam->x) >> 0xC, (cam_pos_y >> 0xC) - 0x400, (step_z + cam->z) >> 0xC);
    fade_level_set(0x1000);
    player_model_state_set(0);
}

void spark_emit_draw(void);
void scene_mover_draw(void);
void cam_face_target(void);
void cam_chase_step(void);
s32 cam_fly_step(void);
void stage_end_camera_fall(void);
void stage_end_camera_rise(void);
void ctrl_phase2(Object *obj, ObjHandler *handler) {
    s32 *co = obj->vars.words;
    s32 unused[2]; /* the original's 8 spare stack bytes */

    if (co[1 + co[0]] != 0) {
        goto *(void *) co[1 + co[0]];
    }
    co[1 + co[0]] = (s32) &&start;
start:
    if (fly_active_flag != 0) {
        set_stage_flags(get_stage_flags() | 8);
        clamp_set_max_x(0, 0);
        co[0] = (co[0] + 1) & 7;
        co[1 + co[0]] = (s32) &&warn;
        co[9 + co[0]] = 0x67;
warn:
        cam_face_target();
        if (--co[9 + co[0]] >= 0) {
            goto done;
        }
        co[0] = (co[0] - 1) & 7;
        obj->handlers[3].fn = spark_emit_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        cam_chase_step();
        co[0] = (co[0] + 1) & 7;
        co[1 + co[0]] = (s32) &&chase;
        co[9 + co[0]] = 0x1A3;
chase:
        cam_face_target();
        if (cam_fly_step() == 0) {
            if (--co[9 + co[0]] >= 0) {
                goto done;
            }
            co[0] = (co[0] - 1) & 7;
        }
        co[1 + co[0]] = (s32) &&load;
load:
        if (area_load_pending() != 0) {
            goto done;
        }
        sound_pair_stop();
        ctrl_set_angle_range(0);
        set_stage_flags(get_stage_flags() | 8);
        obj->handlers[3].fn = scene_mover_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        scene_cam_setup();
        co[1 + co[0]] = (s32) &&fade;
fade:
        if (fade_level_get() < 0x1000) {
            goto done;
        }
        player_model_state_set(1);
        set_stage_flags(get_stage_flags() & ~8);
        set_d_801202C8(1);
        mission_timer_set(0x708);
        mission_state_set(1);
        mission_timer_active_set(1);
        show_line((s32) "\xA5#1Warning!  Warning! 30 more seconds to safety break.\xA1");
        co[1 + co[0]] = (s32) &&timer;
timer:
        if (mission_timer_get() > 0) {
            if ((pad1_pressed & 0x10) == 0) {
                goto done;
            }
        } else {
            set_player_status(get_player_status() | 0x40);
        }
        co[1 + co[0]] = (s32) &&done;
    }
done:
    if (scene_active_flag != 0) {
        alarm_disarm();
        alarm2_start();
        if (get_stage_end() == 2) {
            stage_end_camera_fall();
        } else {
            stage_end_camera_rise();
        }
    } else {
        alarm_update();
        alarm2_stop();
    }
}

extern s32 fly_cam_y;
void spark_emit_draw(void) {
    SparkRec *rec;
    SparkList *pool;
    s32 angle;
    s32 x;
    s32 y;
    s32 z;
    s16 uv;
    s32 count;
    u8 *tail;

    angle = atan2((cam_pos_z - fly_cam_z) >> 12, (cam_pos - fly_cam.f0) >> 12);
    x = fly_cam.f0 >> 12;
    y = fly_cam_y >> 12;
    z = fly_cam_z >> 12;
    uv = boss_pchr_get();
    pool = &spark_list;
    count = spark_count;
    if (count < 0xFF) {
        rec = &pool->items[count];
        count++;
        spark_count = count;
        *(s32 *)rec->colour = 0;
        tail = spark_list_tail;
        spark_list_tail = &rec->next;
        *tail = count;
        rec->next = 0;
        rec->x = x;
        rec->y = y;
        rec->z = z;
        rec->unk_12 = uv;
        rec->yaw = angle;
        rec->pitch = 0;
        rec->roll = 0;
    }
    aim_marker_draw(2, (SVECTOR *)&fly_target_pos, (Vec3 *)&fly_cam, (SVECTOR *)&fly_target_rot);
}

extern s32 scene_active_flag;
void scene_mover_draw(void) {
    if (scene_active_flag != 0) {
        s32 *pos = scratch_alloc(0x10);
        void *p = scratch_alloc(8);
        Vec3 *vec = scratch_alloc(0xC);

        mover_to_vec3((Vec3 *)get_mover(), vec);
        mover_calc_pos((Mover *)vec, pos);
        mover_set_rot((Mover *)vec, (PlayerObj *)p);
        scratch_top -= 0x24;
    }
}
