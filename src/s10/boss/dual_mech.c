/* dual_mech: one of s10's own original source files (scripts/objmap.py); part of src/s10/main.c's unit, included there. */

void func_800C11D8(void) {
    aobj_set_flag(get_rec_id(0) + 0x87, 0);
    aobj_set_flag(get_rec_id(0) + 0x88, 0);
}

extern s32 elevator_cam_slot;
extern s32 elevator_inside_flag;
extern s32 elevator_nudge_phase;
extern PathPoint warp_cam_path[8];
void state_machine_phase2(Object *obj, ObjHandler *handler);
void state_machine_draw(void);
/* Create the object for this state machine: link it into the object list,
   install its two phase handlers and reset the globals. */
s32 state_machine_spawn(void) {
    Object *obj;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_b(), (Node *) obj);
    obj->handlers[2].fn = (ObjHandlerFn) state_machine_phase2;
    obj->handlers[3].fn = (ObjHandlerFn) state_machine_draw;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = NULL;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->vars.state_machine.unused_248 = 0;
    obj->vars.state_machine.unused_24C = 0;
    elevator_cam_slot = 0;
    elevator_inside_flag = 0;
    elevator_nudge_phase = -1;
    cam_zone_setup();
    cam_path_set(8, (s32) warp_cam_path);
    target_select(5);
    return 1;
}

extern s32 warp_pos_x;
extern s32 warp_pos_y;
extern s32 warp_pos_z;
extern s32 warp_from_origin_x;
extern s32 warp_from_origin_y;
extern s32 warp_from_origin_z;
extern s32 warp_to_origin_x;
extern s32 warp_to_origin_y;
extern s32 warp_to_origin_z;
/* Warps the player to a point: the position in warp_pos_x..F0 (4096ths), moved from
   the warp_from_origin_x origin to the warp_to_origin_x one, with no rotation. */
void player_warp_to_point(void) {
    VECTOR pos;
    s16 rot[4];
    s32 x, y, z;

    rot[0] = 0;
    rot[1] = 0;
    rot[2] = 0;
    x = warp_pos_x >> 12;
    y = warp_pos_y >> 12;
    z = warp_pos_z >> 12;
    do { } while (0); /* scheduling barrier: shifts stay ahead of the sums */
    x = x - warp_from_origin_x + warp_to_origin_x;
    pos.vx = x;
    y = y - warp_from_origin_y + warp_to_origin_y;
    pos.vy = y;
    z = z - warp_from_origin_z + warp_to_origin_z;
    pos.vz = z;
    player_warp_request(&pos, (UnalignedVec *)rot, 0);
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


extern s32 stage_end_zone_min_x, stage_end_zone_max_x, stage_end_zone_min_y, stage_end_zone_max_y, stage_end_zone_min_z, stage_end_zone_max_z;
extern s32 door_trigger_min_x, door_trigger_max_x, door_trigger_min_y, door_trigger_max_y, door_trigger_min_z, door_trigger_max_z;
extern PathPoint door_cam_path[10];
s16 door_get_scale(u32 index);
void door_set_active(u32 index, s8 value);
void player_warp_to_point(void);
s32 player_turn_to_yaw(s32 target_yaw);
void state_machine_phase2(Object *obj, ObjHandler *handler) {
    CoItem *co;
    s32 x, y, z;
    s32 inside;
    s32 unused[2];

    cam_zone_fade_step();
    co = (CoItem *) &obj->vars;
    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    co->resume[co->level] = &&check_zone;
check_zone:
    x = cam_pos >> 12;
    y = cam_pos_y >> 12;
    z = cam_pos_z >> 12;
    if (x < door_trigger_min_x || door_trigger_max_x < x || y < door_trigger_min_y || door_trigger_max_y < y || z < door_trigger_min_z ||
        door_trigger_max_z < z) {
        inside = 0;
    } else {
        inside = 1;
    }
    if (inside) {
        set_stage_flags(get_stage_flags() | 8);
        target_select(0);
        elevator_cam_slot = -1;
        co->resume[co->level] = &&s1;
s1:
        co->level = (co->level + 1) & 7;
        co->resume[co->level] = &&s2;
        co->count[co->level] = 0x4F;
s2:
        if (player_turn_to_yaw(0x800) == 0) {
            if (--co->count[co->level] >= 0) {
                goto done;
            }
            co->level = (co->level - 1) & 7;
        }
        co->resume[co->level] = &&s3;
s3:
        co->level = (co->level + 1) & 7;
        co->resume[co->level] = &&s4;
        co->count[co->level] = 0xF;
s4:
        if (--co->count[co->level] >= 0) {
            goto done;
        }
        co->level = (co->level - 1) & 7;
        door_set_active(0, 0);
        door_set_active(1, 0);
        co->resume[co->level] = &&s5;
s5:
        if (((s32(*)(s32))door_get_scale)(0) < 0x1000) {
            goto done;
        }
        co->resume[co->level] = &&s6;
s6:
        co->level = (co->level + 1) & 7;
        co->resume[co->level] = &&s7;
        co->count[co->level] = 0x1F;
s7:
        if (--co->count[co->level] >= 0) {
            goto done;
        }
        co->level = (co->level - 1) & 7;
        set_draw_enabled(0);
        show_line((s32) "#2Accessed!  Elevatorstarting.\xa1");
        elevator_nudge_phase = 0;
        sound_start(SND_PAIR(SND_ELEVATOR_START | SND_GROUP(1), SND_ELEVATOR_START_ALT | SND_GROUP(1)), 0x60, 0, 0);
        co->resume[co->level] = &&s8;
s8:
        co->level = (co->level + 1) & 7;
        co->resume[co->level] = &&s9;
        co->count[co->level] = 0x77;
s9:
        set_view_nudge(0, elevator_nudge_phase);
        if (--co->count[co->level] >= 0) {
            goto done;
        }
        elevator_nudge_phase = -1;
        co->level = (co->level - 1) & 7;
        player_warp_to_point();
        co->resume[co->level] = &&s10;
s10:
        co->level = (co->level + 1) & 7;
        co->resume[co->level] = &&s11;
        co->count[co->level] = 0x1F;
s11:
        if (--co->count[co->level] >= 0) {
            goto done;
        }
        co->level = (co->level - 1) & 7;
        set_draw_enabled(1);
        door_set_active(1, 1);
        show_line((s32) "Arrived at target  floor 69.\xa1");
        co->resume[co->level] = &&s12;
s12:
        if (((s32(*)(s32))door_get_scale)(1) > 0) {
            goto done;
        }
        set_stage_flags(get_stage_flags() & ~8);
        elevator_cam_slot = 1;
        cam_path_set(10, (s32) door_cam_path);
        target_select(5);
        co->resume[co->level] = &&s13;
s13:
        if (((s32(*)(s32))door_get_scale)(1) < 0x1000) {
            goto done;
        }
        door_set_active(1, 0);
        aobj_set_flag(get_rec_id(0) + 0x88, 1);
        co->resume[co->level] = &&done;
    }
done:
    if (elevator_inside_flag == 0) {
        x = cam_pos >> 12;
        y = cam_pos_y >> 12;
        z = cam_pos_z >> 12;
        if (x < stage_end_zone_min_x || stage_end_zone_max_x < x || y < stage_end_zone_min_y || stage_end_zone_max_y < y || z < stage_end_zone_min_z ||
            stage_end_zone_max_z < z) {
            inside = 0;
        } else {
            inside = 1;
        }
        elevator_inside_flag = inside;
        if (inside) {
            set_stage_end(2);
        }
    }
}

/* The boss's model files: data tables point to them by address. */
const char file_bosa_tp1_clt[] = "bosa_tp1.clt";
const char file_bosa_ch0_clt[] = "bosa_ch0.clt";
const char file_bosa_ch3_vx1[] = "bosa_ch3.vx1";
const char file_bosa_ch2_vx1[] = "bosa_ch2.vx1";
const char file_bosa_ch1_vx1[] = "bosa_ch1.vx1";
const char file_bosa_ch0_vx1[] = "bosa_ch0.vx1";
const char file_bosa_tp1_xs3[] = "bosa_tp1.xs3";
const char file_bosa_tp0_xs3[] = "bosa_tp0.xs3";
const char file_bosa_ch3_cb4[] = "bosa_ch3.cb4";
const char file_bosa_ch2_cb4[] = "bosa_ch2.cb4";
const char file_bosa_ch1_cb4[] = "bosa_ch1.cb4";
const char file_bosa_ch0_cb4[] = "bosa_ch0.cb4";

extern s32 elevator_nudge_phase;
extern s32 elevator_cam_slot;
extern s32 state_machine_req_table[];
void state_machine_draw(void) {
    s32 *entry;

    cam_path_update();
    if (elevator_nudge_phase >= 0) {
        elevator_nudge_phase ^= 1;
    }
    if (elevator_cam_slot >= 0) {
        entry = &state_machine_req_table[elevator_cam_slot * 4];
        req_queue_push(entry[0], entry[1], entry[2], 4);
    }
}

s32 obj_get_health(Object *obj);
extern s32 stream_last_s16;
extern s32 d_80119E84;
/* Teardown for an object with two sound handles (words[0], words[1]). While
 * either is set, sum their values and pass the total to meter_set; otherwise
 * clear the global and free the object. */
void sound_pair_teardown(Object *obj) {
    s32 sound_a;
    s32 sound_b;
    s32 total;

    sound_a = obj->vars.arrival_warning.sound_a;
    if ((sound_a != 0) || (obj->vars.arrival_warning.sound_b != 0)) {
        total = 0;
        if (sound_a != 0) {
            total = obj_get_health((Object *)sound_a);
        }
        sound_b = obj->vars.arrival_warning.sound_b;
        if (sound_b != 0) {
            total += obj_get_health((Object *)sound_b);
        }
        meter_set(total, 0x5DC0);
        meter_set_mode(stream_last_s16);
        return;
    }
    meter_set_mode(0);
    warning_ack_set(0);
    set_d_801202C8(0);
    d_80119E84 = 0;
    obj_free(obj);
}

extern ModelSlotHead arrival_warning_asset;
void arrival_warning_sounds_start(Object *obj);
s32 arrival_warning_spawn(void) {
    Object *obj;
    s32 result = 0;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        obj->handlers[2].fn = sound_pair_teardown;
        obj->asset = &arrival_warning_asset;
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
        obj->callback = 0;
        stream_last_s16 = 0;
        d_80119E84 = 1;
        meter_set(0x5DC0, 0x5DC0);
        meter_set_mode(0);
        show_line((s32) "Arrived at target  floor 97.\xa1|2");
        show_line((s32) "#1Warning!  Warning! Moving object confirmed in the area.\xa1");
        msg_show_slot(1, 0xB4);
        warning_ack_set(1);
        arrival_warning_sounds_start(obj);
        result = 1;
    }
    return result;
}

Object * dual_mech_spawn(Object *parent, Vec3 *pos, SVECTOR *rot, s32 side);
/* Spawns the two M10 dual mechs (dual_mech_spawn) at offsets mirrored in x; the first goes to
 * vars.snd.unk_248, the second to the sound handle. */
void arrival_warning_sounds_start(Object *obj) {
    Vec3 *from = scratch_alloc(0x10);
    SVECTOR *to = scratch_alloc(8);

    from->x = 0xCC0;
    from->y = -0x20;
    from->z = -0x3C0;
    to->vx = 0;
    to->vy = 0xC00;
    to->vz = 0;
    obj->vars.arrival_warning.sound_a = (s32)dual_mech_spawn(obj, from, to, 0);
    from->x = -0xCC0;
    from->y = -0x20;
    from->z = -0x3C0;
    to->vx = 0;
    to->vy = 0x400;
    to->vz = 0;
    obj->vars.snd.sound = (s32)dual_mech_spawn(obj, from, to, 1);
    scratch_top -= 8;
    scratch_top -= 0x10;
}

void slot_records_clear_all(void);

void arrival_warning_start(void) {
    spawn_slots_reset();
    slot_records_clear_all();
    arrival_warning_spawn();
}

/* Clears one of the object's two sound handles: snd.unk_248 for which == 0, snd.sound for which == 1. */
void sound_pair_clear(Object *obj, s32 which) {
    switch (which) {
    case 0:
        obj->vars.snd.unk_248 = 0;
        return;
    case 1:
        obj->vars.snd.sound = 0;
        return;
    }
}

/* Counts the sound handles that are set: snd.unk_248 (nonzero) and snd.sound (nonzero). */
s32 sound_pair_count(Object *obj) {
    s32 count = obj->vars.snd.unk_248 != 0;

    if (obj->vars.snd.sound != 0) {
        count += 1;
    }
    return count;
}

void dual_mech_m10_boss_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

s32 spark_or_shot_spawn(Object *owner, Vec3 *pos, SVECTOR *rot, s32 mode, s32 arg4);
void spark_init(Object *obj, Object *owner);
void shot_init(Object *obj, Object *owner);
/* Rotates an offset by the object's angles, moves it to the object's position, hands position, angles (pitch lowered by 0x200) and the asset's model_slot_pchr value to spark_or_shot_spawn after playing sound 0x312D there. */
void muzzle_effect_spawn(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *ang = scratch_alloc(8);

    pos->x = -0x39;
    pos->y = -0xF2;
    pos->z = -0xC;
    ang->vx = obj->pitch;
    ang->vy = obj->yaw;
    ang->vz = obj->roll;
    rotate_xz_twice(ang->vy, -ang->vx, &pos->x, &pos->y, &pos->z);
    pos->x += obj->x >> 12;
    pos->y += obj->y >> 12;
    pos->z += obj->z >> 12;
    ang->vx -= 0x200;
    sound_play_at_units(SND_GUN_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    spark_or_shot_spawn(obj, pos, ang, 0, model_slot_pchr(*(s32 *)obj->asset));
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Spawns an effect at the object's muzzle: the offset vector between two rotated points gives the angles. */
void rocket_fire(Object *obj) {
    s32 ax, ay, az;
    s32 bx, by, bz;
    s32 yaw, pitch;
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);

    ax = -0x52;
    ay = -0xA8;
    az = 0xE3;
    bx = -0x53;
    by = -0x9C;
    bz = 0x99;
    yaw = 0;
    pitch = 0;
    rotate_xz_twice(obj->yaw, -obj->pitch, &ax, &ay, &az);
    rotate_xz_twice(obj->yaw, -obj->pitch, &bx, &by, &bz);
    vector_to_angles(ax - bx, ay - by, az - bz, &yaw, &pitch);
    rot->vz = 0;
    rot->vx = pitch;
    rot->vy = yaw;
    pos->x = (obj->x >> 12) + ax;
    pos->y = (obj->y >> 12) + ay;
    pos->z = (obj->z >> 12) + az;
    sound_play_at_units(SND_ROCKET_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    rocket_spawn(obj, pos, rot, 0, model_slot_pchr(*(s32 *)obj->asset));
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 projectile_spawn(s32 arg0, s32 *pos, u16 *rot, s32 arg3, s32 arg4);
/* Plays an effect at the object's muzzle: the offsets in the object's frame give the position, and the
 * direction from the second offset to the first gives the rotation. */
void laser_fire(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 ax, ay, az;
    s32 bx, by, bz;
    s32 yaw, pitch;

    ax = 0x4D;
    ay = -0xAC;
    az = 0xB9;
    bx = 0x4D;
    by = -0xA6;
    bz = 0x96;
    yaw = 0;
    pitch = 0;
    rotate_xz_twice(obj->yaw, -obj->pitch, &ax, &ay, &az);
    rotate_xz_twice(obj->yaw, -obj->pitch, &bx, &by, &bz);
    vector_to_angles(ax - bx, ay - by, az - bz, &yaw, &pitch);
    rot->vz = 0;
    rot->vx = pitch;
    rot->vy = yaw;
    pos->x = (obj->x >> 12) + ax;
    pos->y = (obj->y >> 12) + ay;
    pos->z = (obj->z >> 12) + az;
    sound_play_at_units(SND_PROJECTILE_FIRE_ALT | SND_GROUP(1), 0x7F, 0x3C, pos);
    projectile_spawn((s32)obj, (s32 *)pos, (u16 *)rot, 0, model_slot_pchr(*(s32 *)obj->asset));
    scratch_top -= 8;
    scratch_top -= 0x10;
}

s32 obj_debris_spawn(Object *parent, Vec3 *pos, SVECTOR *rot, s32 kind, s32 value);
/* Plays an effect at the object's muzzle: the offsets in the object's frame give the position, and the
 * direction from the second offset to the first gives the rotation. */
void muzzle_debris_spawn(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);
    s32 ax, ay, az;
    s32 bx, by, bz;
    s32 yaw, pitch;

    ax = -0x54;
    ay = -0x82;
    az = 0xA6;
    bx = -0x54;
    by = -0x84;
    bz = 0x9E;
    yaw = obj->yaw;
    pitch = obj->pitch;
    rotate_xz_twice(yaw, -pitch, &ax, &ay, &az);
    rotate_xz_twice(yaw, -pitch, &bx, &by, &bz);
    vector_to_angles(ax - bx, ay - by, az - bz, &yaw, &pitch);
    rot->vz = 0;
    rot->vx = pitch;
    rot->vy = yaw;
    pos->x = (obj->x >> 12) + ax;
    pos->y = (obj->y >> 12) + ay;
    pos->z = (obj->z >> 12) + az;
    sound_play_at_units(SND_PROJECTILE_FIRE | SND_GROUP(1), 0x7F, 0x3C, pos);
    obj_debris_spawn(obj, pos, rot, 0, model_slot_pchr(*(s32 *)obj->asset));
    scratch_top -= 8;
    scratch_top -= 0x10;
}

/* Reads the halfword at the stream pointer (unk_1C.unk_04) into vars.h, then advances the pointer by 2 bytes. */
void obj_cmd_read_u16(Object *obj) {
    u16 *stream;

    stream = (u16 *)obj->script.pc;
    obj->script.pc = (s16 *)(stream + 1);
    obj->vars.dual_mech.aim_mode = *stream;
}

/*
 * Reads a (key, index) pair from the stream and jumps to table[index] when the
 * key matches: key >= 0 matches selector == key, key < 0 matches selector != ~key.
 */
void cmd_branch_if_selector(CmdStream *s) {
    u8 *cur;
    s32 key;
    s32 index;

    cur = s->cursor;
    s->cursor = cur + 2;
    key = *(s16 *)cur;
    s->cursor = cur + 4;
    index = *(s16 *)(cur + 2);
    if (key >= 0) {
        if (s->selector != key) {
            return;
        }
    } else if (s->selector == ~key) {
        return;
    }
    s->cursor = (u8 *)s->table[index];
}

s32 obj_trace_angle(Object *obj, s32 angle);
void obj_aim_at_player_mode(Object *obj) {
    VECTOR *player = scratch_alloc(0x10);
    s32 *pos = scratch_alloc(0x10);
    s32 dz;
    s32 dx;
    s32 ang;
    s32 ang4;
    s32 base;
    s32 h;

    dx = 0;
    dz = 0;
    player_position_copy(player);
    dz = player->vz - (obj->z >> 12);
    dx = player->vx - (obj->x >> 12);
    base = atan2(dz, dx);
    switch (obj->vars.dual_mech.aim_mode) {
    case 0:
        obj->unk_226[3] = obj_trace_angle(obj, base) == 1 ? base + 0x800 : base;
        break;
    case 1:
        base += 0x800;
        obj->unk_226[3] = obj_trace_angle(obj, base) == 1 ? base + 0x800 : base;
        break;
    case 2:
        ang = base;
        if (rand_a_next() < 0x200) {
            obj->vars.dual_mech.unk_24E ^= 1;
        }
        if (obj->vars.dual_mech.unk_24E == 0) {
            base += 0x200;
        } else {
            base -= 0x200;
        }
        if (obj_trace_angle(obj, base) == 1) {
            obj->unk_226[3] = ang * 2 - base;
        } else {
            obj->unk_226[3] = base;
            obj->vars.dual_mech.unk_24E ^= 1;
        }
        break;
    case 3:
        if (rand_a_next() < 0x200) {
            obj->vars.dual_mech.unk_24E ^= 1;
        }
        if (obj->vars.dual_mech.unk_24E == 0) {
            base += 0xA00;
        } else {
            base += 0x600;
        }
        if (obj_trace_angle(obj, base) == 1) {
            obj->unk_226[3] = base + 0x800;
        } else {
            obj->unk_226[3] = base;
            obj->vars.dual_mech.unk_24E ^= 1;
        }
        break;
    case 4:
        ang4 = base;
        if (rand_a_next() < 0x400) {
            obj->vars.dual_mech.unk_24E ^= 1;
        }
        if (obj->vars.dual_mech.unk_24E == 0) {
            base += 0xAAA;
        } else {
            base += 0x556;
        }
        fly_move(base, 0x660, &dz, &dx);
        dz = player->vz + ((-obj->z + dz) >> 12);
        dx = player->vx + ((-obj->x + dx) >> 12);
        base = atan2(dz, dx);
        if (obj_trace_angle(obj, base) == 1) {
            obj->unk_226[3] = ang4 * 2 - base;
            obj->vars.dual_mech.unk_24E ^= 1;
        } else {
            obj->unk_226[3] = base;
        }
        break;
    case 5:
        if (rand_a_next() < 0x200) {
            obj->vars.dual_mech.unk_24E ^= 1;
        }
        if (obj->vars.dual_mech.unk_24E == 0) {
            base += 0x199;
        } else {
            base -= 0x199;
        }
        fly_move(base, 0x660, &dz, &dx);
        dz = player->vz + ((-obj->z + dz) >> 12);
        dx = player->vx + ((-obj->x + dx) >> 12);
        base = atan2(dz, dx);
        if (obj_trace_angle(obj, base) == 1) {
            obj->unk_226[3] = base + 0x800;
            obj->vars.dual_mech.unk_24E ^= 1;
        } else {
            obj->unk_226[3] = base;
        }
        break;
    }
    pos[0] = obj->x >> 12;
    h = (s16)obj->height;
    pos[1] = (obj->y >> 12) - h / 2;
    pos[2] = obj->z >> 12;
    sound_play_at_units(0x31223123, 0x7F, 0x3C, pos);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
}

void cmd_read_u16(CmdReader *reader) {
    u8 *p;

    p = reader->cursor;
    reader->cursor = p + 2;
    reader->value = *(u16 *)p;
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


/* Reads a (kind, index) pair from the object's script cursor (unk_1C.unk_04). When the Object at 0x25C
   is set and its sound_pair_count count equals kind, the cursor jumps to the table entry at index. */
void script_jump_if_partner_kind(Object *obj) {
    s16 *cursor = obj->script.pc;
    Object *other = (Object *) obj->vars.dual_mech.partner; /* 0x25C */
    s32 kind;
    s32 index;

    obj->script.pc = cursor + 1;
    kind = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (other != NULL && sound_pair_count(other) == kind) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: jump to targets[*pc] while the player's y (cam_pos is his position) is below obj's threshold. */
void script_jump_if_below_height(ScriptBranchHeight *obj) {
    s16 *pc = obj->pc;
    s32 threshold = obj->deadline;
    s32 index;
    s32 diff;

    obj->pc = pc + 1;
    diff = ((VECTOR *)&cam_pos)->vy - threshold;
    index = *pc;
    if (diff < 0) {
        obj->pc = (s16 *)obj->targets[index];
    }
}

void script_jump_if_outside_radius(Object *obj) {
    s16 *stream;
    s32 radius;
    s32 index;
    s32 dx;
    s32 dz;

    /* Reads a (radius, index) pair from the object's script cursor, then
       picks the next cursor from the type's table when the object is
       outside the radius of the camera (XZ distance in 4096ths). */
    stream = obj->script.pc;
    obj->script.pc = stream + 1;
    radius = stream[0];
    obj->script.pc = stream + 2;
    index = stream[1];
    dx = obj->x;
    dx = (VEC_80139584.x - dx) >> 12;
    dz = (VEC_80139584.z - obj->z) >> 12;

    if (isqrt(length_sq(dx, 0, dz)) >= radius) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void door_state_set(u32 index, s8 value);
void obj_flag_set(Object *obj) {
    s32 index;

    switch (obj->vars.dual_mech.unk_248) {
    case 0:
        index = 0;
        break;
    case 1:
        index = 1;
        break;
    default:
        return;
    }
    door_state_set(index, 1);
}

void obj_flag_clear(Object *obj) {
    u32 index;

    switch (obj->vars.dual_mech.unk_248) {
    case 0:
        index = 0;
        break;
    case 1:
        index = 1;
        break;
    default:
        return;
    }
    door_state_set(index, 0);
}

/* Reads a halfword from the object's data cursor (+0x20), advances the cursor by 2, and stores the value at +0x250. */
void obj_script_read_u16_var(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.h.unk_250 = *cursor;
}

/* Reads one signed halfword from the stream's cursor into stream_last_s16 and advances the cursor by 2. */
void stream_read_s16(ByteStream *stream) {
    u8 *cursor = stream->pos;

    stream->pos = cursor + 2;
    stream_last_s16 = *(s16 *)cursor;
}

s32 obj_trace_angle(Object *obj, s32 angle) {
    Vec3 *from = scratch_alloc(0x10);
    Vec3 *to = scratch_alloc(0x10);
    s32 dx = 0, dy = 0, dz = 0;
    s32 e4 = obj->width << 16;
    s32 flags;
    s32 height;
    s32 hit;

    if (obj->width > obj->unk_1E8[0]) {
        flags = e4 >> 16;
    } else {
        flags = obj->unk_1E8[0];
    }
    angles_to_vector(angle, 0, 0x660, &dx, &dy, &dz);
    from->x = obj->x >> 12;
    height = (s16)obj->height;
    from->y = (obj->y >> 12) - height / 2;
    from->z = obj->z >> 12;
    to->x = from->x + (dx >> 12);
    to->y = from->y + (dy >> 12);
    to->z = from->z + (dz >> 12);
    hit = trace_world(2, flags, from, to, to);
    scratch_top -= 0x10;
    scratch_top -= 0x10;
    return hit;
}

void fly_steer(Object *obj);
void obj_snapshot_update(Object *obj);
void obj_shadow_spawn(Object *obj);
void dual_mech_m10_boss_update(Object *obj, ObjHandler *handler) {
    s16 state;

    if (obj->script_flag != 0) {
        state = obj->next_state;
        if (state == handler->state) {
            switch (state) {
            case 1:
                obj->next_state = 2;
                break;
            case 4:
                obj->next_state = 5;
                break;
            case 7:
            case 9:
                obj->next_state = 8;
                break;
            case 11:
            case 13:
                obj->next_state = 0xC;
                break;
            case 16:
            case 18:
                obj->next_state = 0x11;
                break;
            case 0:
            case 2:
            case 5:
            case 8:
            case 12:
            case 17:
                break;
            default:
                obj->next_state = 0;
                break;
            }
        }
    }
    obj_script_step(obj, handler);
    fly_steer(obj);
    obj_snapshot_update(obj);
    obj_shadow_spawn(obj);
}

void func_800C2D5C(Object *obj) {
    obj->speed_accel = 0x3000;
}

/* Turns the object toward the target player_position_copy returns (yaw only), and sets 0x234 to -0x3000. */
void obj_turn_to_target(Object *obj) {
    Vec3 *target = scratch_alloc(0x10);
    s32 yaw = 0;
    s32 pitch = 0;

    player_position_copy((VECTOR *)target);
    vector_to_angles(target->x - (obj->x >> 12), target->y - (obj->y >> 12), target->z - (obj->z >> 12), &yaw, &pitch);
    obj->yaw = angle_approach(obj->yaw, yaw, 0x80);
    obj->speed_accel = -0x3000;
    scratch_top -= 0x10;
}

void fly_steer(Object *obj) {
    s32 dx;
    s32 dz;
    s32 speed;
    s32 err;
    s32 turn;

    dz = 0;
    dx = 0;
    speed = obj->speed + obj->speed_accel;
    err = (obj->y >> 12) - obj->vars.fly.target_y;
    if (ABS(err) >= 2) {
        if (err >= 0) {
            obj->vars.fly.climb_step = -0x800;
        } else {
            obj->vars.fly.climb_step = 0x800;
        }
    } else if (obj->vars.fly.climb != 0) {
        obj->vars.fly.climb_step = obj->vars.fly.climb >= 0 ? -0x800 : 0x800;
    } else {
        obj->vars.fly.climb_step = 0;
    }
    turn = obj->vars.fly.climb + obj->vars.fly.climb_step;
    turn = MAX(MIN(turn, 0x8000), -0x8000);
    obj->vars.fly.climb = turn;
    speed = MAX(MIN(speed, 0x30000), 0);
    obj->speed = speed;
    fly_move(obj->unk_226[3], speed >> 12, &dx, &dz);
    obj->vy = turn;
    obj->vx = dz;
    obj->vz = dx;
    obj->vars.fly.phase += 0x2A;
}

void obj_snapshot_update(Object *obj) {
    obj_snapshot_save(obj, (ObjSnapshot *)obj->rot_angles);
    player_step_move_scratch(obj->rot_angles);
    obj_snapshot_restore(obj, (ObjSnapshot *)obj->rot_angles);
}

extern u8 shadow_tint_rgb[];
/* Every 32 ticks: spawn a rec34 effect at the object, tinted darker the higher it is. */
void obj_shadow_spawn(Object *obj) {
    s32 *pos;
    s8 shade;

    if (!(obj->vars.dual_mech.frame_counter & 0x1F)) {
        pos = (s32 *)scratch_top;
        scratch_top += 0x10;
        shade = -((obj->y >> 12) * 40 / 256);
        pos[0] = obj->x >> 12;
        pos[1] = 0;
        pos[2] = obj->z >> 12;
        shadow_tint_rgb[0] = shade;
        shadow_tint_rgb[1] = shade;
        shadow_tint_rgb[2] = shade;
        fx_rec34_spawn(pos, (FxRecordParams *)(shadow_tint_rgb - 1));
        scratch_top -= 0x10;
    }
    obj->vars.dual_mech.frame_counter++;
}

extern s32 stream_last_s16;
/* Runs one step of an object's handler. While stream_last_s16 is zero, the object's index is first passed to obj_hit_clear. */
void dual_mech_m10_boss_phase2(Object *obj, ObjHandler *handler) {
    if (stream_last_s16 == 0) {
        obj_hit_clear(obj->index);
    }
    obj_state_run_b(obj, handler);
}

/* Per-frame object update. Returns 1 while the object stays idle (no reaction),
 * 0 once the reaction branch ran: it then releases the partner object and turns
 * toward its type's angle plus the asset's model_slot_pchr value. */
s32 pair_update(Object *obj) {
    s32 idle;
    s32 hit;
    Object *child;
    s32 yaw;

    idle = 1;
    obj->unk_17A = 0;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->vars.dual_mech.unk_250 = 0;
    child = obj->vars.pair.child;
    if (child != NULL) {
        pair_release_child(child);
        obj->vars.pair.child = NULL;
    }
    hit = 0;
    if (obj->unk_1B7 != 0 || obj->vars.pair.timer >= 0xB5) {
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->next_state = 0x14;
        child = obj->vars.pair.partner;
        if (child != NULL) {
            hit = sound_pair_count(child) == 1;
            sound_pair_clear(obj->vars.pair.partner, obj->vars.pair.side);
            obj->vars.pair.partner = NULL;
        }
        yaw = obj->type.unk_0E;
        idle = 0;
        enemy_spawn_copy(obj, yaw + model_slot_pchr(*(s32 *)obj->asset), hit);
    }
    obj->vars.pair.timer += 1;
    return idle;
}

void obj_stop_sound_handle(Object *obj) {
    sound_stop(obj->vars.dual_mech.sound_handle); /* 0x264 */
}

s32 obj_turn_update(Object *obj, s32 base);
/* Draws the M10 dual mech: its model (obj_turn_update's pose) as a spark record, tinted while hit, then
 * its aim marker (aim_marker_draw); a hit flag is set to -1 once drawn. */
void dual_mech_m10_boss_draw(Object *obj) {
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
    model = obj_turn_update(obj, obj->vars.dmech.part);
    if (obj->hit <= 0) {
        colour = 0;
    } else {
        colour = 0x60C0FF;
        /* keeps the branch: combine's nonzero bits then fold the chain index (colour >> 24) to 0 */
        __asm__("");
    }
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    roll = obj->roll;
    rot[2] = roll;
    spark_add_u(pos[0], pos[1], pos[2], rot[1], rot[0], roll, model, colour);
    scratch_top -= 8;
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
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

s32 obj_turn_blend(Object *obj, s32 base);
s32 obj_pose_frame_blend(Object *obj, s32 base);
s32 obj_turn_update(Object *obj, s32 base) {
    s16 state = obj->next_state;

    if (state < 4) {
        if (state > 0) {
            return obj_turn_blend(obj, base);
        }
    }
    return obj_pose_frame_blend(obj, base);
}

/* Same code as obj_pose_range_blend (s04): the pose frame between the type's start and end, blended by its step. */
s32 obj_pose_frame_blend(Object *obj, s32 base) {
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

extern s32 turn_frame_offsets[];
/* Blends the two table entries straddling the object's yaw delta. */
s32 obj_turn_blend(Object *obj, s32 base) {
    s32 idx_lo;
    s32 delta;
    s32 lo_angle;
    s32 hi_angle;
    s32 idx_hi;
    s32 segments[4];

    delta = (obj->unk_226[3] - obj->yaw) & 0xFFF;
    lo_angle = delta;
    if (delta < 0) {
        lo_angle = delta + 0x3FF;
    }
    idx_lo = lo_angle >> 10;
    hi_angle = (delta + 0x3FF) & 0xFFF;
    if (hi_angle < 0) {
        hi_angle += 0x3FF;
    }
    idx_hi = hi_angle >> 10;
    if (idx_lo == idx_hi) {
        obj_pose_frame_blend(obj, base + turn_frame_offsets[idx_lo]);
        return;
    }
    segments[0] = obj_pose_frame_blend(obj, base + turn_frame_offsets[idx_lo]);
    segments[1] = obj_pose_frame_blend(obj, base + turn_frame_offsets[idx_hi]);
    segments[2] = 0x1000 - ((delta - (idx_lo << 10)) << 2);
    segments[3] = 0x1000 - segments[2];
    return pchr_blend(segments[0], segments[1], segments[2], 0);
}

extern ModelSlotHead dual_mech_asset_head;
extern s16 *dual_mech_script_ids[];
extern s16 *D_8011CDD4[109];
extern ScriptCallEntry dual_mech_table_a[17];
extern StateEntry dual_mech_table_b[24];
extern s16 *dual_mech_m10_boss_data[];
void dual_mech_m10_boss_draw(Object *obj);
Object *obj_spawn_after(Node *pos, s32 mode, s32 param);
void obj_place_at(Object *obj, s32 *pos, u16 *rot, s32 flags);
/* Spawns one of the two M10 dual mechs (side 0 or 1) under its parent. */
Object *dual_mech_spawn(Object *parent, Vec3 *pos, SVECTOR *rot, s32 side) {
    Object *obj;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_actors(), &obj->node);
        obj->handlers[0].fn = dual_mech_m10_boss_phase0;
        obj->handlers[1].fn = dual_mech_m10_boss_update;
        obj->handlers[2].fn = dual_mech_m10_boss_phase2;
        obj->handlers[3].fn = dual_mech_m10_boss_draw;
        obj->callback = (s32)pair_update;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->destructor = obj_stop_sound_handle;
        obj->kind = parent->kind;
        dual_mech_asset_head = *(ModelSlotHead *)parent->asset;
        obj->asset = &dual_mech_asset_head;
        obj->hit_cooldown_max = 0x30;
        obj->call_table = dual_mech_table_a;
        obj->state_table = dual_mech_table_b;
        obj->unk_1C6 = 0;
        obj->script.pc = dual_mech_script_ids[side];
        obj->script.data = D_8011CDD4;
        obj->script.unk_0A = 0;
        obj->vars.dmech.side = side;
        obj->vars.dmech.unused_24C = 3;
        obj->vars.dmech.unused_24E = 0;
        obj->vars.dual_mech.unk_250 = pos->y;
        obj->vars.dmech.unused_252 = 0;
        obj->vars.dmech.unused_254 = 0;
        obj->vars.dmech.unused_258 = 0;
        obj->vars.dmech.partner = parent;
        obj->vars.dmech.unused_268 = 0;
        obj->vars.dmech.timer = 0;
        if (side == 0) {
            obj->vars.dmech.part = 0;
            obj->vars.dmech.child = NULL;
            obj_hit_set_unk06(obj->index, 0x16);
        } else {
            obj->vars.dmech.part = 0x100;
            obj->vars.dmech.child = obj_spawn_after(&obj->node, 0, model_slot_pchr(*(s32 *)obj->asset));
            obj_hit_set_unk06(obj->index, 0x11);
        }
        obj_hit_flag_set(obj->index, 0x80);
        script_start((Script *)obj, (s16 *)dual_mech_m10_boss_data[0], (s32)dual_mech_m10_boss_data);
        obj_place_at(obj, (s32 *)pos, (u16 *)rot, 0x425);
        obj_set_part_bounds(obj, obj->vars.dmech.part + 1, 0x1000);
        obj->vars.dmech.sound = sound_start(SND_PAIR(SND_DUAL_MECH_LOOP | SND_HELD, SND_DUAL_MECH_LOOP_ALT | SND_HELD), 0x7F, 0, 0);
        sound_attach(obj->vars.dmech.sound, &obj->x, NULL);
        sound_set_flag_bit2(obj->vars.dmech.sound, 1);
    }
    return obj;
}

/* Sets up an object from a position (fixed point, shifted to 20.12) and pitch/yaw/roll. */
void obj_place_at(Object *obj, s32 *pos, u16 *rot, s32 flags) {
    obj_hit_clear(obj->index);
    obj->flags = flags;
    if (flags & 4) {
        obj->unk_17A = 1;
    }
    obj_set_flags(obj, flags);
    obj->health = 0x2EE0;
    obj->score = 0x2EE0;
    obj->damage = 0;
    obj->unk_17B = 0;
    obj->x = pos[0] << 12;
    obj->y = pos[1] << 12;
    obj->z = pos[2] << 12;
    obj->pitch = rot[0];
    obj->yaw = rot[1];
    obj->roll = rot[2];
    obj->unk_226[3] = 0;
    obj->placement = NULL;
    if (flags & 0x20) {
        obj->solid_id = solid_alloc();
    }
}

s32 obj_get_health(Object *obj) {
    return obj->health;
}

extern u8 slot_records[];
void slot_records_clear(void) {
    s32 offset;

    offset = 0x20C;
    do {
        *(s32 *)(slot_records + offset) = 0;
        offset -= 0x20C;
    } while (offset >= 0);
}

/* Originally C, kept as asm: we can't reproduce it with the compilers we have. It is a short slot-claim loop (the
 * first free of two records in D_801253C4) and our C matches every instruction but one: the original starts the
 * counter as a copy of the zeroed return value (`addu a2,v1,zero`), where cc1 2.7.2 -O2 always writes a plain
 * zero (its second cse pass folds the copy). The draft matches byte for byte with -fno-rerun-cse-after-loop, but
 * the rest of this file needs that pass, so the original was likely built with other settings for this code.
 * FINDINGS "A copy of a known zero"; draft: agent_logs/sessions/c392c_func_800C392C_v22.c. */
#ifdef NON_MATCHING
/* Claims the first free of the two records of D_801253C4 (first word 0): marks it used, clears two more words and
 * returns it, or NULL when both are taken. C companion of an asm function whose C matches byte for byte only with
 * -fno-rerun-cse-after-loop (draft v22, agent_logs/sessions/c392c_func_800C392C_v22.c); the original starts the
 * counter as a copy of the zeroed return value, which has no C form. Not compiled. */
typedef struct Slot801253C4 {
    s32 w[0x83];
} Slot801253C4;
extern Slot801253C4 D_801253C4[];

s32 *ribbon_slot_claim(void) {
    Slot801253C4 *slot = NULL;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (D_801253C4[i].w[0] == 0) {
            slot = &D_801253C4[i];
            slot->w[0] = 1;
            slot->w[1] = 0;
            slot->w[2] = 0;
            break;
        }
    }
    return (s32 *)slot;
}
#else
INCLUDE_ASM("../src/s10/asm", ribbon_slot_claim);
#endif
