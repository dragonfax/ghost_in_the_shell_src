/* stage_controller: one of s03's own original source files (scripts/objmap.py); part of src/s03/main.c's unit, included there. */

extern s32 bomb_armed_flag;

void time_bomb_clear_armed(void) {
    bomb_armed_flag = 0;
}

extern u8 door_box_table[][4];
extern u8 rect_x0_table[];
extern u8 rect_y0_table[];
extern u8 rect_x1_table[];
extern u8 rect_y1_table[];
/* Returns 1 if the point (pos[2], pos[4]) lies inside any active rect in the
 * table for the entries listed at door_box_table[idx]. */
s32 rect_table_contains(s32 *pos, s32 idx) {
    u8 *slot;
    u8 *end;
    s32 x;
    s32 y;
    s32 off;
    s32 i;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;

    u8 *base = door_box_table[0];
    idx *= 4;
    slot = idx + base;
    end = slot + 3;
    x = pos[2] >> 12;
    y = pos[4] >> 12;
    do {
        i = slot[0];
        if (i >= 0) {
            off = i << 5;
            x0 = *(s32 *)(rect_x0_table + off);
            y0 = *(s32 *)(rect_y0_table + off);
            x1 = *(s32 *)(rect_x1_table + off);
            y1 = *(s32 *)(rect_y1_table + off);
            if (x0 < x && x < x1 && y0 < y && y < y1) {
                return 1;
            }
        }
        slot++;
    } while ((s32)slot < (s32)end);
    return 0;
}

void slot_mark_in_area(s32 arg0) {
    GridEntry **table;
    s32 count;
    s32 i;
    SlotObj *obj;

    table = slot_list_get();
    count = slot_list_count();
    for (i = 0; i < count; i++) {
        obj = (SlotObj *)table[i];
        if (rect_table_contains((s32 *)obj, arg0) != 0) {
            obj->flags_04 = (obj->flags_04 & 0xFC) | 1;
        }
    }
}

s32 slot_list_count(void);

void slot_mark_all(void) {
    GridEntry **list = slot_list_get();
    s32 count = slot_list_count();
    s32 i;

    for (i = 0; i < count; i++) {
        FlagRecord04 *rec = (FlagRecord04 *)list[i];
        rec->flags = (rec->flags & 0xFC) | 2;
    }
}


void stage_player_start(void) {
    Vec3 *pos;
    SVECTOR *rot;

    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0x1717, -0x4B0, -0xFD);
    cam_look_at_set(VEC_80139584.x >> 12, VEC_80139584.y >> 12, VEC_80139584.z >> 12);
    fade_level_set(0);
    pos = scratch_alloc(0x10);
    pos->x = VEC_80139584.x >> 12;
    rot = scratch_alloc(8);
    pos->y = VEC_80139584.y >> 12;
    pos->z = (VEC_80139584.z >> 12) - 0x320;
    rot->vx = 0;
    rot->vy = 0;
    rot->vz = 0;
    player_warp_request((VECTOR *)pos, (UnalignedVec *)rot, 0);
    scratch_top -= 0x18;
}

/* Advances the progress value by 0x2D per call, capped at 0x1000. Once it
 * reaches the cap, clears the flags used by the completed state. */
void stage_fade_in_step(void) {
    s32 progress;
    s32 full;
    s32 advanced;
    s32 clamped;

    progress = fade_level_get();
    full = 0x1000;
    if (progress != full) {
        mission_timer_set(0xE10);
        player_set_input(get_key_config()->action[4], 0);
        cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
        advanced = progress + 0x2D;
        clamped = 0x1000;
        if (advanced < 0x1001) {
            clamped = advanced;
        }
        progress = clamped;
        fade_level_set(progress);
        if (progress == full) {
            set_d_801202C8(1);
            set_stage_flags(get_stage_flags() & ~0x28);
        }
    }
}

extern s32 D_801176E8;
extern s32 mission_active_flag;
extern s32 bomb_exploded_flag;
extern s32 door_sound_idx;
extern s32 door_sound_handle;
void slot_mark_in_area(s32 arg);
/* Runs the setup calls, then resets the five state words bomb_armed_flag..door_sound_handle (two set to 1, one to 0, two to -1). */
void stage_state_reset(void) {
    clamp_table_set((s32)&D_801176E8);
    slot_mark_all();
    slot_mark_in_area(0);
    bomb_armed_flag = 1;
    mission_active_flag = 1;
    bomb_exploded_flag = 0;
    door_sound_idx = -1;
    door_sound_handle = -1;
    hit_ext_flag_set(1);
}

void sound_channel_fade_step(Object *obj, ObjHandler *handler);
void stage_controller_phase2(Object *arg, ObjHandler *handler);
void stage_controller_draw(Object *obj);
extern GridEntry *bomb_grid_entry;
extern s16 D_801208A8[];
extern SoundSegmentList stage_sound_owner_a;
extern SoundSegmentList stage_sound_owner_b;
s32 stage_controller_spawn(Placement *placement) {
    Object *obj;
    s16 *ptr;
    s32 count;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_b(), &obj->node);
    /* four behaviour slots; each gets its function, then fn/state cleared */
    obj->handlers[1].fn = sound_channel_fade_step;
    obj->handlers[2].fn = stage_controller_phase2;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))stage_controller_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    mission_timer_set(0xE10);
    obj->vars.stage_controller.unk_24A = 0;
    obj->vars.stage_controller.door_index = 0;
    obj->vars.stage_controller.timer = 0;
    count = 2;
    ptr = &D_801208A8[0];
    do {
        *ptr = 0;
        count--;
        ptr--;
    } while (count >= 0);
    eng_set_mode(2);
    pursue_flag_set(1);
    mission_state_set(0);
    mission_timer_active_set(1);
    bomb_grid_entry = NULL;
    grid_collect_kind((s16)placement->unk_16, &bomb_grid_entry);
    if (bomb_grid_entry != NULL) {
        bomb_grid_entry->flags = (bomb_grid_entry->flags & 0xFC) | 2;
    }
    stage_player_start();
    sound_start_attached(0xD222, 0x30, &stage_sound_owner_a);
    sound_set_note(sound_start_attached(0xD222, 0x40, &stage_sound_owner_b), 0x40);
    target_select(2);
    set_area_warnings(1);
    return 1;
}

u8 door_box_table[4][4] = {
    0x01, 0x02, 0x03, 0x00, 0x05, 0xFF, 0xFF, 0x04, 0x07, 0xFF, 0xFF, 0x06,
    0x08, 0xFF, 0xFF, 0xFF,
};

extern s16 door_open_level[];
extern s16 door_open_step[];
extern DrawRequest door_point_table[];
extern VECTOR door_sound_pos;
void door_access_sound_start(s32 idx) {
    s32 handle;
    DrawRequest *rec;
    DrawRequest *table;
    s16 level = door_open_level[idx];

    if (level == 0 && door_open_step[idx] < 0) {
        return;
    }
    if (level == 0x1000 && door_open_step[idx] > 0) {
        return;
    }
    if (door_sound_handle != -1) {
        return;
    }
    door_sound_idx = idx;
    table = door_point_table;
    rec = table + idx;
    door_sound_pos.vx = rec->a;
    door_sound_pos.vy = rec->b;
    door_sound_pos.vz = rec->c;
    door_sound_pos.vx <<= 12;
    door_sound_pos.vy <<= 12;
    door_sound_pos.vz <<= 12;
    handle = sound_start(SND_DOOR_MOVE_LOOP | SND_HELD | SND_GROUP(1), 0x7F, 0, 0);
    sound_attach(handle, &door_sound_pos, NULL);
    door_sound_handle = handle;
    if (door_open_step[idx] < 0) {
        show_line((s32)"Accessed!  Enteringarea.\xA1");
    }
}

extern s16 door_open_level[];
/* Stops the sound held in door_sound_handle when handle index `idx` is the one
   in door_sound_idx and its table entry is 0 or 0x1000 (idle). */
void sound_stop_if_idle(s32 idx) {
    s16 flags;

    flags = door_open_level[idx];
    if ((flags == 0 || flags == 0x1000) && door_sound_idx == idx) {
        sound_stop(door_sound_handle);
        door_sound_handle = -1;
        door_sound_idx = -1;
    }
}

extern s16 door_open_step[];
void sound_channel_fade_step(Object *obj, ObjHandler *handler) {
    s32 i;

    for (i = 0; i < 3; i++) {
        door_open_level[i] += door_open_step[i];
        door_open_level[i] = MAX(MIN(door_open_level[i], 0x1000), 0);
        sound_stop_if_idle(i);
    }
}

extern FxRecordParams bomb_burst_params;
extern RecTemplate bomb_burst_templates[];
void area_load_start(void);
void stage_controller_phase2(Object *arg, ObjHandler *handler) {
    register Object *obj asm("$21") = arg; /* the original keeps obj in $s5 */
    s32 pos[3];
    s32 unused[2];
    s32 i;
    s32 id;
    s32 box;
    GridEntry **list;
    s32 *entry;
    s32 total;
    s32 count;
    s32 removed;
    s32 left;
    s32 *player;
    DrawRequest *rec;

    stage_fade_in_step();
    if (bomb_exploded_flag != 0) {
        hit_target_masked(0, 1, 0, 0xC8);
    }
    id = get_rec_id(0);
    for (i = 0; i < 3; i++) {
        if (door_open_level[i] == 0x1000) {
            aobj_set_flag(id + 0xB0 + i, 1);
        } else {
            aobj_set_flag(id + 0xB0 + i, 0);
        }
    }
    for (i = 0; i < 9; i++) {
        clamp_set_max_x(i, 0);
    }
    for (i = 0; i < 3; i++) {
        box = door_box_table[obj->vars.stage_controller.door_index][i];
        if (box >= 0) {
            clamp_set_max_x(box, 1);
        }
    }
    if (obj->vars.stage_controller.unk_24A != 0) {
        box = door_box_table[obj->vars.stage_controller.door_index][3];
        if (box >= 0) {
            clamp_set_max_x(box, 1);
            if (door_open_level[obj->vars.stage_controller.door_index] == 0) {
                clamp_set_max_x(door_box_table[obj->vars.stage_controller.door_index + 1][0], 1);
                target_select(2);
            }
        }
        box = cam_find_box();
        if (box == door_box_table[obj->vars.stage_controller.door_index][3]) {
            door_open_step[obj->vars.stage_controller.door_index] = -0x40;
            door_access_sound_start(obj->vars.stage_controller.door_index);
        }
        if (box == door_box_table[obj->vars.stage_controller.door_index + 1][0]) {
            door_open_step[obj->vars.stage_controller.door_index] = 0x40;
            door_access_sound_start(obj->vars.stage_controller.door_index);
            obj->vars.stage_controller.door_index++;
            obj->vars.stage_controller.unk_24A = 0;
            slot_mark_in_area(obj->vars.stage_controller.door_index);
            if (obj->vars.stage_controller.door_index == 3) {
                warning_ack_set(0);
                area_load_start();
                target_select(0);
            }
        }
    }
    i = 0;
    list = slot_list_get();
    count = slot_list_count();
    removed = 0;
    total = count;
    if (count > 0) {
        do {
            entry = (s32 *)list[i];
            if (rect_table_contains(entry, obj->vars.stage_controller.door_index) == 0) {
                count--;
            } else if ((((GridEntry *)entry)->flags & 3) == 3) {
                removed++;
            }
            i++;
        } while (i < total);
    }
    left = count - removed;
    set_enemies_left(left);
    pursue_flag_set(left);
    if (obj->vars.stage_controller.unk_24A != 0) {
        if (obj->vars.stage_controller.timer > 0) {
            if (--obj->vars.stage_controller.timer == 0) {
                msg_show_slot(4, 0xF0);
            }
        }
    }
    if (obj->vars.stage_controller.unk_24A == 0 && count == removed) {
        if (obj->vars.stage_controller.door_index < 2) {
            show_line((s32)"#2All bombs in this  area have been removed.\xA1|3");
            show_line((s32)"Proceed to the nextarea.\xA1");
            msg_show_slot(3, 0x78);
            mission_timer_set(mission_timer_get() + 0xE10);
            obj->vars.stage_controller.timer = 0x78;
        } else if (obj->vars.stage_controller.door_index == 2) {
            show_line((s32)"#2All bombs have beenremoved.\xA1|2");
            show_line((s32)"#1Warning! Warning!  Moving object acknowledged.\xA1");
            mission_timer_active_set(0);
            pursue_flag_set(0);
            msg_show_slot(1, -1);
            bomb_grid_entry->flags = (bomb_grid_entry->flags & 0xFC) | 1;
            mission_active_flag = 0;
        }
        rec = &door_point_table[obj->vars.stage_controller.door_index];
        cam_set_target(rec->a, rec->b, rec->c);
        target_select(5);
        obj->vars.stage_controller.unk_24A = 1;
    }
    if (mission_active_flag != 0) {
        if (mission_timer_get() == 0) {
            if (bomb_armed_flag != 0) {
                player = player_position();
                angles_to_vector(view_angles_get()[1], 0x71, 0x400, &pos[0], &pos[1], &pos[2]);
                pos[0] = pos[0] / 4096 + player[0];
                pos[1] = pos[1] / 4096 + player[1];
                pos[2] = pos[2] / 4096 + player[2];
                fx_rec34_spawn_cb(pos, &bomb_burst_params, 0);
                fx_spawn_template(pos, &bomb_burst_templates[0], 0);
                fx_spawn_template(pos, &bomb_burst_templates[1], 0);
                bomb_armed_flag = 0;
            }
            sound_start(SND_BOMB_EXPLOSION | SND_GROUP(1), 0x7F, 0, 0);
            mission_active_flag = 0;
            bomb_exploded_flag = 1;
        }
        if (mission_active_flag != 0) {
            return;
        }
    }
    if (meter_get_mode() != 0) {
        mission_timer_set(0);
    }
}

/* file names the data tables reference by address */
const char file_mth1_tp0_clt[] = "mth1_tp0.clt";
const char file_mth1_ch0_clt[] = "mth1_ch0.clt";
const char file_mth1_tp0_xs3[] = "mth1_tp0.xs3";
const char file_mth1_ch0_vx1[] = "mth1_ch0.vx1";
const char file_mth1_ch0_cb4[] = "mth1_ch0.cb4";
const char file_mbaz_tp0_clt[] = "mbaz_tp0.clt";
const char file_mbaz_ch0_clt[] = "mbaz_ch0.clt";
const char file_mbaz_tp0_xs3[] = "mbaz_tp0.xs3";
const char file_mbaz_ch0_vx1[] = "mbaz_ch0.vx1";
const char file_mbaz_ch0_cb4[] = "mbaz_ch0.cb4";
const char file_hou2_tp0_clt[] = "hou2_tp0.clt";
const char file_hou2_ch0_clt[] = "hou2_ch0.clt";
const char file_hou2_tp0_xs3[] = "hou2_tp0.xs3";
const char file_hou2_ch0_vx1[] = "hou2_ch0.vx1";
const char file_hou2_ch0_cb4[] = "hou2_ch0.cb4";
const char file_fap2_tp1_clt[] = "fap2_tp1.clt";
const char file_fap2_tp0_clt[] = "fap2_tp0.clt";
const char file_fap2_ch0_clt[] = "fap2_ch0.clt";
const char file_fap2_tp1_xs3[] = "fap2_tp1.xs3";
const char file_fap2_tp0_xs3[] = "fap2_tp0.xs3";
const char file_fap2_ch0_vx1[] = "fap2_ch0.vx1";
const char file_fap2_ch0_cb4[] = "fap2_ch0.cb4";
const char file_bomb_tp0_clt[] = "bomb_tp0.clt";
const char file_bomb_ch0_clt[] = "bomb_ch0.clt";
const char file_bomb_tp0_xs3[] = "bomb_tp0.xs3";
const char file_bomb_ch0_vx1[] = "bomb_ch0.vx1";
const char file_bomb_ch0_cb4[] = "bomb_ch0.cb4";
const char file_part_ch0_cb4[] = "part_ch0.cb4";
const char file_bos3_tp1_clt[] = "bos3_tp1.clt";
const char file_bos3_ch1_clt[] = "bos3_ch1.clt";
const char file_bos3_tp0_clt[] = "bos3_tp0.clt";
const char file_bos3_ch0_clt[] = "bos3_ch0.clt";
const char file_bos3_tp1_xs3[] = "bos3_tp1.xs3";
const char file_bos3_tp0_xs3[] = "bos3_tp0.xs3";
const char file_bos3_ch1_vx1[] = "bos3_ch1.vx1";
const char file_bos3_ch0_vx1[] = "bos3_ch0.vx1";
const char file_bos3_ch1_cb4[] = "bos3_ch1.cb4";
const char file_bos3_ch0_cb4[] = "bos3_ch0.cb4";

extern DrawRequest door_point_table[];
void stage_controller_draw(Object *obj) {
    DrawRequest *rec;

    if (obj->vars.stage_controller.unk_24A != 0) {
        rec = &door_point_table[obj->vars.stage_controller.door_index];
        if (rec->d != -1) {
            req_queue_push(rec->a, rec->b, rec->c, 4);
        }
    }
}
