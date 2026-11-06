/* stage: one of s09's own original source files (scripts/objmap.py); part of src/s09/main.c's unit, included there. */

/* The stage's model and message files: data tables point to them by address. */
const char file_gt3_mobj_cb4[] = "gt3_mobj.cb4";

/* The player's model block (engine loader step 1) gives a {first, last} s16 pair at its word 5. */
void player_set_angle_range(s32 value) {
    s32 first;
    s16 *range;

    first = model_slot_pchr(*(s32 *)get_ptr_entry_word2(1));
    range = (s16 *)((s32 *)get_rec_root()->items[1].entry->model_block)[5];
    pchr_set_angle_range(first + range[0], range[1] - range[0] + 1, value);
}

void stage_view_reset(void) {
    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0xAF0, -0x258, -0x1770);
    cam_look_at_set((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
    fade_level_set(0);
    player_set_angle_range(0);
}

void stage_fade_step(Object *obj) {
    s32 pos;
    s32 next;
    s32 clamped;

    pos = fade_level_get();
    if (pos != 0x1000) {
        cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
        player_set_input(get_key_config()->action[4], 0);
        next = pos + 0x22;
        clamped = 0x1000;
        if (next < 0x1001) {
            clamped = next;
        }
        pos = clamped;
        fade_level_set(pos);
        if (pos == 0x1000) {
            player_set_angle_range(-0x800);
            set_d_801202C8(1);
            set_stage_flags(get_stage_flags() & ~0x28);
        }
    }
}

/* Runs stage_fade_step; if fade_level_get returns 0x1000, clears handlers[2]'s fn, unk_11 and state. */
void stage_ctrl_phase2(Object *obj, ObjHandler *handler) {
    stage_fade_step(obj);
    if (fade_level_get() == 0x1000) {
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
    }
}

extern s32 stage_ctrl_index;
extern s32 stage_ctrl_entries[];
void stage_ctrl_draw(Object *obj, ObjHandler *handler) {
    cam_path_update();
    if (!(stage_ctrl_index & 0x8000)) {
        s32 *entry = &stage_ctrl_entries[stage_ctrl_index * 4];
        req_queue_push(entry[0], entry[1], entry[2], 4);
    }
}

extern PathPoint stage_ctrl_cam_path[];
void stage_ctrl_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_b(), &obj->node);
        obj->handlers[2].fn = stage_ctrl_phase2;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = stage_ctrl_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        stage_ctrl_index = 0;
        stage_view_reset();
        cam_path_set(6, (s32)stage_ctrl_cam_path);
        target_select(5);
    }
}

extern s32 stage_ctrl_index;
/* Packs a counter in the low 15 bits of stage_ctrl_index: a non-zero argument increments it, capped at 2;
   zero sets bit 15 (0x8000) instead. */
void stage_ctrl_advance(s32 arg0) {
    s32 count;
    s32 next;

    if (arg0 != 0) {
        count = stage_ctrl_index & 0x7FFF;
        next = count + 1;
        stage_ctrl_index = count;
        if (next >= 3) {
            next = 2;
        }
        stage_ctrl_index = next;
        return;
    }
    stage_ctrl_index |= 0x8000;
}

extern s32 elevator_ride_flag;
extern s32 elevator_done_flag;
extern s32 spark_model_index_base;
void stage_ctrl_spawn(void);
void stage_ctrl_init(void) {
    s32 *p = &elevator_ride_flag;
    *p = 0;
    elevator_done_flag = 0;
    spark_model_index_base = point_base;
    clamp_table_set((s32) ((char *) p - 0x10));
    stage_ctrl_spawn();
}

extern void (*enemy_kind_init_fns[])(Object *obj);
extern void (*enemy_kind_phase0_fns[])(Object *obj, ObjHandler *handler);
extern void (*enemy_kind_phase1_fns[])(Object *obj, ObjHandler *handler);
extern void (*enemy_kind_phase2_fns[])(Object *obj, ObjHandler *handler);
extern void (*enemy_kind_phase3_fns[])(Object *obj, ObjHandler *handler);
extern s32 door_model_base[];
s32 enemy_spawn_record(EnemySpawn *spawn) {
    Object *obj;
    s32 kind;
    u16 ext[3];
    s32 unused[2];
    s32 z;
    u16 depth;
    s32 span;
    s32 y;
    s16 y_copy;
    s16 span_copy;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    kind = spawn->kind;
    obj->damage = spawn->unk_16;
    obj->handlers[0].fn = enemy_kind_phase0_fns[kind * 4];
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = enemy_kind_phase1_fns[kind * 4];
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = enemy_kind_phase2_fns[kind * 4];
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = enemy_kind_phase3_fns[kind * 4];
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = spawn->x;
    obj->y = spawn->y;
    z = spawn->z;
    obj->vars.spawn.unk_25A = 1;
    obj->vars.spawn.unk_259 = 0;
    obj->vars.enemy.sound_channel[0] = -1;
    obj->vars.enemy_spawn_record_obj.unused_25C = -1;
    obj->z = z;
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, -1);
    obj->solid_id = solid_alloc();
    obj->flags = 0x130;
    obj_set_flags(obj, 0x130);
    model_part_extents_max(door_model_base[0] + 2, 0x1000, ext);
    obj->unk_190 = 0x1000;
    obj->unk_17A = 0;
    obj->width = ext[0];
    obj->height = ext[1];
    obj->unk_1E8[0] = depth = ext[2];
    y = (s16)obj->height;
    span = (s16)depth;
    y_copy = y;
    if (span < obj->width) {
        span = obj->width;
    }
    span_copy = span;
    obj->extents[0] = span_copy;
    obj->extents[1] = y_copy;
    obj->extents[2] = span_copy;
    obj->bound_radius = isqrt(length_sq(span, y, span));
    if (enemy_kind_init_fns[kind] != NULL) {
        enemy_kind_init_fns[kind](obj);
    }
    return 1;
}


void fn_800B789C(Object *obj) {
    ObjSum *sum_obj = (ObjSum *) obj;
    s32 sum = sum_obj->total + sum_obj->step;
    s32 clamped;
    s32 result;

    sum_obj->total = sum;
    clamped = (s16) sum;
    if (clamped >= 0x1001) {
        clamped = 0x1000;
    }
    if (clamped >= 0) {
        clamped = (s16) sum;
        if (clamped >= 0x1001) {
            clamped = 0x1000;
        }
        result = clamped;
    } else {
        result = 0;
    }
    sum_obj->total = result;
}


extern s32 door_model_base[];
void rising_door_phase2(Object *obj) {
    u8 *block;
    s16 step;

    block = obj->unk_A4;
    if ((obj->vars.h.unk_254 >= 0) && (obj->vars.h.unk_248 != 0)) {
        obj_hit_damage(obj->index);
        step = door_model_base[0] + 2;
        obj->unk_A4[1] = 4;
        obj->unk_A4[0] = obj->index;
        obj_block_fill(obj, block);
        ((Collider *)obj->unk_A4)->sub[0] += (s16)obj->vars.h.unk_250 << 12;
        ((Collider *)obj->unk_A4)->sub[2] += (s16)obj->vars.h.unk_252 << 12;
        ((Collider *)obj->unk_A4)->angle[1] = obj->vars.h.unk_254;
        ((Collider *)obj->unk_A4)->sub[1] += 0x180000;
        solid_setup_scratch(obj->solid_id, block, step, obj->unk_190);
        fn_800FB460(obj, block);
        obj_hit_clear(obj->index);
    }
}

extern s32 view_nudge_toggle;
/* Two effect records at the door's position and at the offset (unk_24C, unk_24E), their values blended by
 * pchr_blend between the bases unk_257/unk_258; unk_259 toggles view_nudge_toggle every frame. */
void rising_door_draw(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s32 base;
    s32 weight;
    s32 lo;
    s32 hi;
    s32 colour = 0;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    base = spark_model_index_base;
    if (((ObjSetupVars *)&obj->vars)->weight_mode == 1) {
        weight = *(s16 *)&rcossin_tbl[(((ObjSetupVars *)&obj->vars)->blend_weight / 4) & 0xFFF];
    } else {
        weight = ((ObjSetupVars *)&obj->vars)->blend_weight;
    }
    lo = base + ((ObjSetupVars *)&obj->vars)->first_spark_model_offset;
    hi = base + ((ObjSetupVars *)&obj->vars)->second_spark_model_offset;
    lo = pchr_blend(lo + 1, lo, weight, 1);
    hi = pchr_blend(hi + 1, hi, weight, 1);
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, lo, colour);
    pos[0] += ((ObjSetupVars *)&obj->vars)->second_spark_offset_x;
    pos[2] += (s16)((ObjSetupVars *)&obj->vars)->second_spark_offset_z;
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, hi, colour);
    if (((ObjSetupVars *)&obj->vars)->unk_259 != 0) {
        view_nudge_toggle ^= 1;
    }
    scratch_top -= 0x10;
}


s32 player_turn_to_yaw(s32 target_yaw) {
    s32 diff;
    s32 turn;

    diff = view_angles_get()[1];
    diff = (s32)(target_yaw - diff) << 20 >> 20;
    if (((s16 *)view_matrix_t_get())[4] < 0) {
        diff = -diff;
    }
    if (ABS(diff) < 0x20) {
        return 1;
    }
    if (diff > 0) {
        player_set_input(get_key_config()->action[6], 0);
        diff = MAX(diff - 0x18, 0);
        FAKE_OPAQUE(diff);
        turn = MIN(diff, 0x18);
    } else {
        player_set_input(get_key_config()->action[7], 0);
        turn = diff + 0x18;
        if (turn > 0) {
            turn = 0;
        }
        if (turn < -0x18) {
            turn = -0x18;
        }
    }
    add_turn(turn);
    return 0;
}


/* 1 when the halfword at +8 of the block view_matrix_t_get returns is >= 0xC00. */
s32 view_is_past_limit(void) {
    return *(s16 *)((u8 *)view_matrix_t_get() + 8) >= 0xC00;
}

extern s32 marker_ref_x;
extern s32 marker_ref_y;
extern s32 marker_ref_z;
extern VECTOR marker_points[];
/* Places an object's marker point: a table VECTOR picked by obj->unk_184, offset by the
   object's position (in 4096ths) and the caller's offsets, then player_warp_request turns it. */
void obj_place_marker(Object *obj, s32 off_x, s32 off_z) {
    VECTOR pos;
    s16 rot[4];
    s32 dx, dy, dz, base;

    view_angles_get();
    base = marker_ref_x / 0x1000;
    dx = base - ((obj->x / 0x1000) + off_x);
    base = marker_ref_y / 0x1000 - 0x180;
    dy = base - (obj->y / 0x1000);
    dz = (marker_ref_z / 0x1000) - ((obj->z / 0x1000) + off_z);

    pos = marker_points[obj->damage];
    pos.vx += off_x;
    pos.vy += 0x180;
    pos.vz += off_z;
    pos.vx += dx;
    pos.vy += dy;
    pos.vz += dz;

    rot[1] = 0;
    rot[2] = 0;
    rot[0] = 0;
    player_warp_request(&pos, (UnalignedVec *)rot, 0);
}

extern s32 d_80118190;
extern s32 screen_fade_amount;


void fade_reset(void) {
    d_80118190 = 0;
    screen_fade_amount = 0;
}


extern s32 view_nudge_toggle;
extern char elevator_start_msg[]; /* a pool of the elevator's message lines */
extern PathPoint elevator_cam_path_final[];
s32 player_turn_to_yaw(s32 target_yaw);
void elevator_start_update(Object *obj) {
    Coroutine *co = (Coroutine *)&d_80118190;
    s32 unused[2]; /* the 8 extra bytes of frame in the original */

    if (co->resume[co->level] != 0) {
        goto *(void *)co->resume[co->level];
    }
    stage_ctrl_advance(0);
    set_stage_flags(get_stage_flags() | 8);
    target_select(0);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = (u32)&&wait_intro;
    co->count[co->level] = 0x4F;
wait_intro:
    if (player_turn_to_yaw(0) == 0) {
        if (--co->count[co->level] >= 0) {
            return;
        }
        co->level = (co->level - 1) & 7;
    }
    if (((ElevatorVars *)&obj->vars)->ready != 0x80) {
        sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
    }
    ((ElevatorVars *)&obj->vars)->ready = 0x80;
    if (((ElevatorVars *)&obj->vars)->rec != -1) {
        if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
            aobj_set_flag(get_rec_id(((ElevatorVars *)&obj->vars)->rec) + ((ElevatorVars *)&obj->vars)->rec_off, 1);
        }
    }
    co->resume[co->level] = (u32)&&wait_timer;
wait_timer:
    if (((ElevatorVars *)&obj->vars)->timer < 0x1000) {
        return;
    }
    set_draw_enabled(0);
    show_line((s32)elevator_start_msg);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = (u32)&&shake_wait;
    co->count[co->level] = 0x1D;
shake_wait:
    if (--co->count[co->level] >= 0) {
        return;
    }
    view_nudge_toggle = 0;
    co->level = (co->level - 1) & 7;
    sound_start(SND_PAIR(SND_QUAKE_RUMBLE | SND_GROUP(1), SND_QUAKE_RUMBLE_ALT | SND_GROUP(1)), 0x60, 0, 0);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = (u32)&&shake;
    co->count[co->level] = 0x77;
shake:
    set_view_nudge(0, view_nudge_toggle);
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = (u32)&&end_wait;
    co->count[co->level] = 0x1D;
end_wait:
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    obj_place_marker(obj, -0x180, -0x150);
    set_stage_flags(get_stage_flags() & ~8);
    stage_ctrl_advance(1);
    cam_path_set(4, (s32)elevator_cam_path_final);
    target_select(5);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = (u32)&&final_wait;
    co->count[co->level] = 0xE;
final_wait:
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    set_draw_enabled(1);
    obj_free(obj);
}

extern PathPoint elevator_cam_path_pos[2];
void elevator_start_pos_update(Object *obj) {
    CoItem *co = (CoItem *)&d_80118190;
    s32 unused[2];

    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    stage_ctrl_advance(0);
    set_stage_flags(get_stage_flags() | 8);
    target_select(0);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_pos;
    co->count[co->level] = 0x4F;
wait_pos:
    if (player_turn_to_yaw(0xC00) == 0) {
        if (--co->count[co->level] >= 0) {
            return;
        }
        co->level = (co->level - 1) & 7;
    }
    if (obj->vars.trace.aim_yaw != 0x80) {
        sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
    }
    obj->vars.trace.aim_yaw = 0x80;
    if (obj->vars.enemy.unk_25C != -1) {
        if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
            aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + (&obj->vars.enemy.unk_25C)[1], 1);
        }
    }
    co->resume[co->level] = &&wait_rise;
wait_rise:
    if (obj->vars.h.unk_248 < 0x1000) {
        return;
    }
    set_draw_enabled(0);
    show_line((s32)elevator_start_msg);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_a;
    co->count[co->level] = 0x1D;
wait_a:
    if (--co->count[co->level] >= 0) {
        return;
    }
    view_nudge_toggle = 0;
    co->level = (co->level - 1) & 7;
    sound_start(SND_PAIR(SND_QUAKE_RUMBLE | SND_GROUP(1), SND_QUAKE_RUMBLE_ALT | SND_GROUP(1)), 0x60, 0, 0);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_b;
    co->count[co->level] = 0x77;
wait_b:
    set_view_nudge(0, view_nudge_toggle);
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (((co->level - 1) & 7) + 1) & 7;
    co->resume[co->level] = &&wait_c;
    co->count[co->level] = 0x1D;
wait_c:
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    obj_place_marker(obj, -0x150, -0x180);
    set_stage_flags(get_stage_flags() & ~8);
    stage_ctrl_advance(1);
    cam_path_set(2, (s32)elevator_cam_path_pos);
    target_select(5);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_d;
    co->count[co->level] = 0xE;
wait_d:
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    set_draw_enabled(1);
    obj_free(obj);
}

extern s32 view_nudge_toggle;
extern char elevator_start_msg[]; /* a pool of the elevator's message lines */
s32 player_turn_to_yaw(s32 target_yaw);
void stage_clear_scene(Object *obj) {
    CoItem *co = (CoItem *)&d_80118190;
    s32 unused[2];

    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    stage_ctrl_advance(0);
    set_stage_flags(get_stage_flags() | 8);
    target_select(0);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_move;
    co->count[co->level] = 0x4F;
wait_move:
    if (player_turn_to_yaw(0x400) == 0) {
        if (--co->count[co->level] >= 0) {
            return;
        }
        co->level = (co->level - 1) & 7;
    }
    if ((s16)obj->vars.h.unk_24A != 0x80) {
        sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
    }
    obj->vars.h.unk_24A = 0x80;
    if (obj->vars.enemy.unk_25C != -1) {
        if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
            aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 1);
        }
    }
    co->resume[co->level] = &&wait_fade;
wait_fade:
    if (obj->vars.h.unk_248 < 0x1000) {
        return;
    }
    set_draw_enabled(0);
    show_line((s32)elevator_start_msg);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_line;
    co->count[co->level] = 0x1D;
wait_line:
    if (--co->count[co->level] >= 0) {
        return;
    }
    view_nudge_toggle = 0;
    co->level = (co->level - 1) & 7;
    sound_start(SND_PAIR(SND_QUAKE_RUMBLE | SND_GROUP(1), SND_QUAKE_RUMBLE_ALT | SND_GROUP(1)), 0x60, 0, 0);
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = &&wait_nudge;
    co->count[co->level] = 0x77;
wait_nudge:
    set_view_nudge(0, view_nudge_toggle);
    if (--co->count[co->level] >= 0) {
        return;
    }
    co->level = (co->level - 1) & 7;
    set_stage_end(2);
    co->resume[co->level] = &&last;
last:
    set_view_nudge(0, view_nudge_toggle);
}

void elevator_phase0(Object *obj, ObjHandler *handler);
void tune_obj_init(Object *obj) {
    TuneVars *v = (TuneVars *)&obj->vars;

    v->unk_00 = 0x1000;
    v->unk_0F = 0x34;
    v->unk_10 = 0x36;
    v->unk_0E = 1;
    v->unk_04 = -0x300;
    v->unk_02 = 0;
    v->unk_06 = 0;
    v->unk_14 = 0;
    v->unk_16 = 0x30;
    if (obj->damage >= 0) {
        obj->handlers[0].fn = elevator_phase0;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
    }
}

/* Switch toggled by the player's position: while armed (0x25A), plays sound
 * 0x32E4 on each change and sets (away) or clears (near) the linked flag. */
void player_switch_update(Object *obj) {
    s32 *pos;
    register s32 biased_x asm("$4");
    s32 player_x;
    s32 dist_x;
    s32 player_z;
    s32 v;

    if (*(u8 *)&obj->vars.h.unk_25A != 0) {
        pos = player_position();
        v = obj->x;
        biased_x = v;
        player_x = pos[0] + 0x180;
        if (v < 0) {
            biased_x = v + 0xFFF;
        }
        {
            register s32 obj_x asm("$5") = biased_x >> 12;
            dist_x = player_x - obj_x;
            if (dist_x < 0) {
                dist_x = obj_x - player_x;
            }
        }
        v = obj->z;
        player_z = pos[2] + 0x120;
        if (v < 0) {
            v += 0xFFF;
        }
        if ((u32)(player_z - (v >> 12) + 0x57F) < 0x77F && dist_x < 0x300) {
            if (obj->vars.trace.aim_yaw != -0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
            }
            obj->vars.trace.aim_yaw = -0x80;
            if (obj->vars.enemy.unk_25C != -1) {
                if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
                    aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 0);
                }
            }
        } else {
            if (obj->vars.trace.aim_yaw != 0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
            }
            obj->vars.trace.aim_yaw = 0x80;
            if (obj->vars.enemy.unk_25C != -1) {
                if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
                    aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 1);
                }
            }
            *(u8 *)&obj->vars.h.unk_25A = 0;
        }
    }
}

void elevator_phase0(Object *obj, ObjHandler *handler) {
    s32 *player;
    s32 px;
    s32 pz;
    s32 dx;
    s32 dz;

    if (((ElevatorVars *)&obj->vars)->started == 0) {
        player = player_position();
        px = player[0] + 0x180;
        dx = px - obj->x / 4096;
        if (dx < 0) {
            dx = obj->x / 4096 - px;
        }
        pz = player[2] + 0x120;
        dz = pz - obj->z / 4096;
        if ((u32)(dz + 0x57F) < 0x27F && dx < 0x300 && view_is_past_limit() != 0) {
            fade_reset();
            ((ElevatorVars *)&obj->vars)->started = 1;
            return;
        }
        if ((u32)(dz + 0x57F) < 0xA7F && dx < 0x300) {
            if (((ElevatorVars *)&obj->vars)->ready != -0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
            }
            ((ElevatorVars *)&obj->vars)->ready = -0x80;
            if (((ElevatorVars *)&obj->vars)->rec != -1) {
                if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
                    aobj_set_flag(get_rec_id(((ElevatorVars *)&obj->vars)->rec) + ((ElevatorVars *)&obj->vars)->rec_off, 0);
                }
            }
        } else {
            if (((ElevatorVars *)&obj->vars)->ready != 0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
            }
            ((ElevatorVars *)&obj->vars)->ready = 0x80;
            if (((ElevatorVars *)&obj->vars)->rec != -1) {
                if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
                    aobj_set_flag(get_rec_id(((ElevatorVars *)&obj->vars)->rec) + ((ElevatorVars *)&obj->vars)->rec_off, 1);
                }
            }
        }
    } else {
        elevator_start_update(obj);
    }
}

void rising_door_vars_init(Object *obj) {
    ObjSetupVars *vars = (ObjSetupVars *)&obj->vars;

    vars->blend_weight = 0x1000;
    vars->first_spark_model_offset = 0x3C;
    vars->second_spark_model_offset = 0x3E;
    vars->unk_24A = 0;
    vars->weight_mode = 0;
    vars->second_spark_offset_x = 0;
    vars->second_spark_offset_z = 0x300;
}

void rising_door_phase0(Object *obj) {
    s32 *player;
    s32 px;
    s32 pz;
    s32 dx;
    s32 dz;

    player = player_position();
    px = player[0] - 0x120;
    dx = ABS(px - obj->x / 0x1000);
    pz = player[2] - 0x180;
    dz = ABS(pz - obj->z / 0x1000);
    if (dx < 0x800 && dz < 0x5DC) {
        if (obj->vars.trace.aim_yaw != -0x80) {
            sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
        }
        obj->vars.trace.aim_yaw = -0x80;
        if (obj->vars.enemy.unk_25C != -1) {
            if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 0);
            }
        }
    }
}

void rising_door_sense_vars_init(Object *obj) {
    ObjSetupVars *vars = (ObjSetupVars *)&obj->vars;

    vars->blend_weight = 0x1000;
    vars->first_spark_model_offset = 0x38;
    vars->second_spark_model_offset = 0x3A;
    vars->unk_24A = 0;
    vars->weight_mode = 0;
    vars->second_spark_offset_x = 0;
    vars->second_spark_offset_z = 0x300;
}

void rising_door_sense_phase0(Object *obj) {
    s32 *pos = player_position();
    s32 x = obj->x;
    s32 px = pos[0] + 0x120;
    s32 dx = ABS(px - x / 0x1000);
    s32 z = obj->z;
    s32 pz = pos[2] - 0x180;
    s32 dz = ABS(pz - z / 0x1000);

    if (dx < 0x800 && dz < 0x5DC) {
        if (obj->vars.trace.aim_yaw != -0x80) {
            sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
        }
        obj->vars.trace.aim_yaw = -0x80;
        if (obj->vars.enemy.unk_25C != -1) {
            if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 0);
            }
        }
    }
}

/* Resets the shooting-enemy state in the object's vars block to its starting values. */
void shooter_vars_reset(Object *obj) {
    ShooterVarsView *v = (ShooterVarsView *)&obj->vars;

    v->mode = 0x1000;
    v->unk_257 = 0xC;
    v->unk_258 = 0xE;
    v->unk_256 = 1;
    v->unk_24C = -0x300;
    v->unk_250 = -0x180;
    v->unk_252 = -0x180;
    v->unk_25C = 1;
    v->unk_24A = 0;
    v->unk_24E = 0;
    v->unk_254 = 0;
    v->unk_25E = 0x30;
}

void enemy_vars_init_raw(Object *obj) {
    u8 *p = (u8 *)obj;

    *(s16 *)(p + 0x248) = 0x1000;
    *(u8 *)(p + 0x257) = 0xDE;
    *(u8 *)(p + 0x258) = 0xDC;
    *(u8 *)(p + 0x256) = 1;
    *(s16 *)(p + 0x24E) = 0x300;
    *(s16 *)(p + 0x250) = 0x180;
    *(s16 *)(p + 0x252) = 0x180;
    *(s16 *)(p + 0x254) = 0x400;
    *(s16 *)(p + 0x25E) = 0x31;
    *(s16 *)(p + 0x24A) = 0;
    *(s16 *)(p + 0x24C) = 0;
    *(s16 *)(p + 0x25C) = 1;
}

void trace_enemy_update(Object *obj) {
    s32 *player;
    s32 px;
    s32 pz;
    s32 dx;
    s32 dz;
    s32 ahead;

    if (obj->vars.spawn.unk_259 == 0) {
        player = player_position();
        px = player[0] - 0x120;
        dx = px - obj->x / 0x1000;
        pz = player[2] - 0x180;
        dz = pz - obj->z / 0x1000;
        if (dz < 0) {
            dz = obj->z / 0x1000 - pz;
        }
        if ((u32)(dx - 0x301) < 0x27F && dz < 0x300 && view_is_past_limit()) {
            fade_reset();
            obj->vars.spawn.unk_259 = 1;
            return;
        }
        ahead = dx + 0x4FF;
        if ((u32)ahead < 0xA7F && dz < 0x300) {
            if (obj->vars.trace.aim_yaw != -0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
            }
            obj->vars.trace.aim_yaw = -0x80;
            if (obj->vars.enemy.unk_25C != -1) {
                if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                    aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 0);
                }
            }
        } else {
            if (obj->vars.trace.aim_yaw != 0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
            }
            obj->vars.trace.aim_yaw = 0x80;
            if (obj->vars.enemy.unk_25C != -1) {
                if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                    aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 1);
                }
            }
        }
    } else {
        elevator_start_pos_update(obj);
    }
}

/* Resets the halfword view of an object's vars. 0x256..0x258 are stored as bytes. */
void enemy_vars_reset_bytes(Object *obj) {
    obj->vars.h.unk_248 = 0x1000;
    *((u8 *)&obj->vars.h.unk_256 + 1) = 0xCA;
    *(u8 *)&obj->vars.h.unk_258 = 0xC8;
    *(u8 *)&obj->vars.h.unk_256 = 1;
    obj->vars.h.unk_24E = 0x300;
    obj->vars.h.unk_250 = 0x180;
    obj->vars.h.unk_252 = 0x180;
    obj->vars.h.unk_254 = 0x400;
    obj->vars.enemy.unk_25C = 2;
    obj->vars.h.unk_24A = 0;
    obj->vars.h.unk_24C = 0;
    obj->vars.enemy.unk_25E = 0x31;
}

void rising_door_sense_check(Object *obj) {
    s32 *pos;
    s32 px;
    s32 pz;
    s32 dx;
    s32 dz;

    if (*(u8 *)&obj->vars.h.unk_25A == 0) {
        return;
    }

    pos = player_position();
    px = pos[0] - 0x120;
    dx = px - obj->x / 0x1000;
    pz = pos[2] - 0x180;
    dz = ABS(pz - obj->z / 0x1000);

    if ((u32)(dx + 0x1FF) < 0x77F && dz < 0x300) {
        if (obj->vars.trace.aim_yaw != -0x80) {
            sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
        }
        obj->vars.trace.aim_yaw = -0x80;
        if (obj->vars.enemy.unk_25C != -1) {
            if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 0);
            }
        }
    } else {
        if (obj->vars.trace.aim_yaw != 0x80) {
            sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
        }
        obj->vars.trace.aim_yaw = 0x80;
        if (obj->vars.enemy.unk_25C != -1) {
            if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 1);
            }
        }
        *(u8 *)&obj->vars.h.unk_25A = 0;
    }
}

/* Resets an object's halfword/byte state to its initial values.
 * Bytes at 0x256-0x258 have no union view here, so they are written by offset. */
void enemy_vars_reset_offsets(Object *obj) {
    obj->vars.h.unk_248 = 0x1000;
    ((u8 *)&obj->vars.h.unk_256)[1] = 0xC2;
    ((u8 *)&obj->vars.h.unk_258)[0] = 0xC4;
    ((u8 *)&obj->vars.h.unk_256)[0] = 1;
    obj->vars.h.unk_24E = 0x300;
    *(s16 *)&obj->vars.h.unk_250 = -0x180;
    obj->vars.h.unk_252 = 0x180;
    obj->vars.h.unk_254 = 0x400;
    obj->vars.enemy.unk_25C = 2;
    obj->vars.h.unk_24A = 0;
    obj->vars.h.unk_24C = 0;
    obj->vars.enemy.unk_25E = 0x31;
}

void tune_vars_reset(Object *obj) {
    TuneVars *v = (TuneVars *)&obj->vars;

    v->unk_00 = 0x1000;
    v->unk_0F = 0x48;
    v->unk_10 = 0x46;
    v->unk_0E = 1;
    v->unk_06 = 0x300;
    v->unk_08 = 0x204;
    v->unk_0A = 0x180;
    v->unk_0C = 0x400;
    v->unk_14 = 2;
    v->unk_02 = 0;
    v->unk_04 = 0;
    v->unk_16 = 0x32;
}

void rising_door_sense_gated(Object *obj) {
    s32 *pos = player_position();
    s32 px = pos[0] - 0x120;
    s32 dx = px - obj->x / 0x1000;
    s32 pz = pos[2] - 0x180;
    s32 dz = ABS(pz - obj->z / 0x1000);

    if (elevator_done_flag != 0) {
        if (dx < -0x100) {
            if (obj->vars.trace.aim_yaw != 0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
            }
            obj->vars.trace.aim_yaw = 0x80;
            if (obj->vars.enemy.unk_25C != -1) {
                if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                    aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 1);
                }
            }
            elevator_ride_flag = 0;
        }
    } else if ((u32)(dx + 0x2FF) < 0xAFF && dz < 0x300) {
        if (obj->vars.trace.aim_yaw != -0x80) {
            sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
        }
        obj->vars.trace.aim_yaw = -0x80;
        if (obj->vars.enemy.unk_25C != -1) {
            if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 0);
            }
        }
    } else {
        if (obj->vars.trace.aim_yaw != 0x80) {
            sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, NULL);
        }
        obj->vars.trace.aim_yaw = 0x80;
        if (obj->vars.enemy.unk_25C != -1) {
            if (cam_range_check(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000) != 0) {
                aobj_set_flag(get_rec_id(obj->vars.enemy.unk_25C) + obj->vars.enemy.unk_25E, 1);
            }
        }
    }
}

/* Init of the s09 ride kind (func_800B9C10): clears its state and hit record, sets its extents from the model. */
void s09_diagonal_elevator_init(Object *obj) {
    u16 ext[3];
    s32 unused[2];
    u16 depth;
    s32 span;
    s32 y;
    s16 y_copy;
    s16 span_copy;

    obj->vars.ride.enabled = 1;
    obj->vars.ride.moving = 0;
    obj->vars.ride.unused_24A = 1;
    obj->vars.ride.sound = 0;
    obj->vars.ride.sound2 = 0;
    obj->yaw = 0;
    obj->pitch = 0;
    obj->roll = 0;
    obj_hit_clear(obj->index);
    obj_hit_flag_set(obj->index, 0);
    obj_hit_set_unk08(obj->index, -1);
    obj_hit_set_unk06(obj->index, -1);
    obj->flags = 0x130;
    obj_set_flags(obj, 0x130);
    model_part_extents_max(door_model_base[0] + 1, 0x1000, ext);
    obj->unk_190 = 0x1000;
    obj->unk_17A = 0;
    obj->width = ext[0];
    obj->height = ext[1];
    obj->unk_1E8[0] = depth = ext[2];
    y = (s16)obj->height;
    span = (s16)depth;
    y_copy = y;
    if (span < obj->width) {
        span = obj->width;
    }
    span_copy = span;
    obj->extents[0] = span_copy;
    obj->extents[1] = y_copy;
    obj->extents[2] = span_copy;
    obj->bound_radius = isqrt(length_sq(span, y, span));
    set_player_status(get_player_status() | 0x200);
}

extern s32 player_xyz_y;
extern s32 player_xyz_z;
extern char elevator_start_msg[]; /* a pool of the elevator's message lines */
void s09_diagonal_elevator_phase0(Object *self) {
    s32 new_x;

    if (self->vars.ride.enabled != 0) {
        if (self->vars.ride.moving == 0) {
            s32 px = player_xyz[0] >> 12;
            s32 py = player_xyz_y >> 12;
            s32 pz = player_xyz_z >> 12;

            if ((u32)(px - 0x960) < 0x2D9 &&
                (u32)(pz + 0x28F) < 0x51F &&
                py == -0x6600) {
                sound_start(SND_ELEVATOR_ENGAGE | SND_GROUP(1), 0x7F, 0, 0);
                self->vars.ride.sound = sound_start(SND_PAIR(SND_ELEVATOR_MOVE_LOOP | SND_HELD | SND_GROUP(1), SND_ELEVATOR_MOVE_ALT_LOOP | SND_HELD | SND_GROUP(1)), 0x40, 0xF, 0);
                self->vars.ride.sound2 = sound_start(SND_ELEVATOR_RIDE_LOOP | SND_HELD | SND_GROUP(1), 0x40, 0x78, 0);
                self->vars.ride.moving = 1;
                elevator_ride_flag = 1;
                show_line((s32)elevator_start_msg);
            }
        } else if (self->x / 4096 < -0x5277) {
            sound_start(SND_ELEVATOR_ENGAGE | SND_GROUP(1), 0x7F, 0, 0);
            sound_stop(self->vars.ride.sound);
            sound_stop(self->vars.ride.sound2);
            new_x = 0xFAD88000;
            self->y = 0xFB981000;
            self->vars.ride.moving = 0;
            self->vars.ride.enabled = 0;
            self->x = new_x;
            elevator_done_flag = 1;
        }
    }
}

extern EdgeSlot800B9D84 elevator_edges[4];
/* Moves a box around the object's position: saves the position before and after a shift and the difference. */
void s09_diagonal_elevator_update(Object *obj) {
    PosShift *p = scratch_alloc(0x20);

    collider_begin((Collider *)obj->unk_A4);
    p->before.x = obj->x >> 12;
    p->before.y = obj->y >> 12;
    p->before.z = obj->z >> 12;
    if (*(u8 *)&obj->vars && player_landed) {
        obj->x += -0xA000;
        obj->y += 0x3552;
    }
    p->after.x = obj->x >> 12;
    p->after.y = obj->y >> 12;
    p->after.z = obj->z >> 12;
    obj->move_delta[0] = p->after.x - p->before.x;
    obj->move_delta[1] = p->after.y - p->before.y;
    obj->move_delta[2] = p->after.z - p->before.z;
    elevator_edges[0].value = p->before.x - 0x19C;
    elevator_edges[2].value = p->before.x + 0x1C;
    elevator_edges[1].value = p->before.z - 0x10F;
    elevator_edges[3].value = p->before.z + 0x40F;
    scratch_top -= 0x20;
}

extern s32 door_model_base[];
void diagonal_elevator_phase2(Object *obj) {
    u8 *block;
    s16 frame;

    block = obj->unk_A4;
    obj_hit_damage(obj->index);
    frame = door_model_base[0] + 1;
    block[1] = 4;
    block[0] = obj->index;
    obj_block_fill(obj, block);
    *(s32 *)&block[0x20] += 0x300000;
    solid_setup_scratch(obj->solid_id, block, frame, obj->unk_190);
    fn_800FB460(obj, block);
    obj_hit_clear(obj->index);
}

static inline void diag_elevator_spark_push(Vec3 *pos, s32 id) {
    SparkList *list = &spark_list;
    SparkRec *s;
    u8 *tail;
    s32 x = pos->x;
    s32 y = pos->y;
    s32 z = pos->z;
    s32 n = SPARK_COUNT;

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
        s->unk_12 = id;
        s->yaw = 0;
        s->pitch = 0;
        s->roll = 0;
    }
}
void diagonal_elevator_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 id = spark_model_index_base + 0xF0;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    diag_elevator_spark_push(pos, id++);
    pos->z += 0x300;
    diag_elevator_spark_push(pos, id++);
    pos->z -= 0x300;
    pos->x -= 0x180;
    diag_elevator_spark_push(pos, id++);
    pos->z += 0x300;
    diag_elevator_spark_push(pos, id);
    scratch_top -= 0x10;
}

void diagonal_elevator_trigger(Object *obj) {
    s32 *player;
    s32 px;
    s32 pz;
    s32 dx;
    s32 dz;

    if (((ElevatorVars *)&obj->vars)->started == 0) {
        player = player_position();
        px = player[0] + 0x120;
        dx = px - obj->x / 4096;
        pz = player[2] - 0x180;
        dz = pz - obj->z / 4096;
        if (dz < 0) {
            dz = obj->z / 4096 - pz;
        }
        if ((u32)(dx + 0x57F) < 0x27F && dz < 0x300 && view_is_past_limit() != 0) {
            fade_reset();
            ((ElevatorVars *)&obj->vars)->started = 1;
            return;
        }
        if ((u32)(dx + 0x57F) < 0xA7F && dz < 0x300) {
            if (((ElevatorVars *)&obj->vars)->ready != -0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
            }
            ((ElevatorVars *)&obj->vars)->ready = -0x80;
            if (((ElevatorVars *)&obj->vars)->rec != -1) {
                if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
                    aobj_set_flag(get_rec_id(((ElevatorVars *)&obj->vars)->rec) + ((ElevatorVars *)&obj->vars)->rec_off, 0);
                }
            }
        } else {
            if (((ElevatorVars *)&obj->vars)->ready != 0x80) {
                sound_attach(sound_start(SND_SWITCH_TOGGLE | SND_GROUP(1), 0x40, 0, 0), &obj->x, 0);
            }
            ((ElevatorVars *)&obj->vars)->ready = 0x80;
            if (((ElevatorVars *)&obj->vars)->rec != -1) {
                if (cam_range_check(obj->x / 4096, obj->y / 4096, obj->z / 4096) != 0) {
                    aobj_set_flag(get_rec_id(((ElevatorVars *)&obj->vars)->rec) + ((ElevatorVars *)&obj->vars)->rec_off, 1);
                }
            }
        }
    } else {
        stage_clear_scene(obj);
    }
}
