/* scene_intro: one of s07's own original source files (scripts/objmap.py); part of src/s07/main.c's unit, included there. */

void scene_intro_setup(void) {
    Vec3 *pos;
    SVECTOR *rot;

    set_d_801202C8(0);
    set_stage_flags(get_stage_flags() | 0x28);
    cam_view_pos_set(0x34C, -0xEE8, 0x1C02);
    cam_look_at_set(VEC_80139584.x >> 12, VEC_80139584.y >> 12, VEC_80139584.z >> 12);
    fade_level_set(0);
    pos = scratch_alloc(0x10);
    pos->x = VEC_80139584.x >> 12;
    rot = scratch_alloc(8);
    pos->y = VEC_80139584.y >> 12;
    pos->z = (VEC_80139584.z >> 12) + 0x640;
    rot->vx = 0;
    rot->vy = 0;
    rot->vz = 0;
    player_warp_request((VECTOR *)pos, (UnalignedVec *)rot, 0);
    scratch_top -= 0x18;
}

void fade_in_step(void) {
    s32 val;
    s32 next;
    s32 clamped;

    val = fade_level_get();
    if (val != 0x1000) {
        cam_look_at_set(cam_pos >> 12, cam_pos_y >> 12, cam_pos_z >> 12);
        player_set_input(get_key_config()->action[4], 0);
        next = val + 0x22;
        clamped = 0x1000;
        if (next < 0x1001) {
            clamped = next;
        }
        val = clamped;
        fade_level_set(val);
        if (val == 0x1000) {
            set_d_801202C8(1);
            set_stage_flags(get_stage_flags() & ~0x28);
        }
    }
}

extern s32 area_capture_final_flag;
extern s32 area_capture_complete_flag;
extern s32 area_capture_count;
extern s32 *area_target_ptr;
extern s32 area_ambient_sound;
extern s32 clamp_table[8];
extern ClampTable area_clamp_table_set;
extern s32 D_8011E0D0;
extern s32 area_capture_state[5];
extern SoundPos area_sound_slots[4]; /* positioned ambient sounds (unk_0C the sound pair), ended by -1 */
void area_capture_update(Object *obj, ObjHandler *handler);
void req_push_pos(void);
s32 scene_spawn(void *arg0) {
    GridEntry *grid;
    SoundPos *slot;
    Object *obj;

    area_capture_final_flag = 0;
    area_capture_complete_flag = 0;
    area_capture_count = 0;
    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    {
        list_insert_after((Node *)get_obj_list_b(), &obj->node);
        obj->handlers[2].fn = area_capture_update;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = (void (*)(Object *, ObjHandler *))req_push_pos;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        area_target_ptr = NULL;
        grid_collect_kind(((SpawnArgs *)arg0)->unk_16, (GridEntry **)&area_target_ptr);
        grid = (GridEntry *)area_target_ptr;
        if (grid != NULL) {
            *(ClampTable *)clamp_table = area_clamp_table_set;
            D_8011E0D0 = 1;
            area_capture_state[0] = 1;
            clamp_table_set((s32)clamp_table - 4);
            grid->flags = (grid->flags & 0xFC) | 2;
        }
        scene_intro_setup();
        slot = area_sound_slots;
        if (area_sound_slots[0].sound_id != -1) {
            do {
                sound_attach(sound_start(slot->sound_id, 0x28, 0, 0), slot, NULL);
                slot++;
            } while (slot->sound_id != -1);
        }
        area_ambient_sound = sound_start(SND_PAIR(SND_HOLLOW_WIND | SND_HELD | SND_GROUP(2), SND_HOLLOW_WIND_LOOP | SND_HELD | SND_GROUP(2)), 0x7F, 0, 0);
        target_select(4);
        show_line((s32) "Pursue the target.\xA1");
        set_area_warnings(1);
        return 1;
    }
    return 0;
}

extern s32 *area_target_ptr;
/* Converts the three 20.12 fixed-point values at area_target_ptr[2..4] to integers (truncating toward zero). */
void vec3_fixed_to_int(s32 *out) {
    s32 *src = area_target_ptr;

    out[0] = src[2] / 4096;
    out[1] = src[3] / 4096;
    out[2] = src[4] / 4096;
}

GridEntry **get_grid_areas(void);
s32 grid_flagged_count_read(void);
void pursue_flag_set(s32 arg0);
/* Area-capture mission: sets the ambient volume from the player's depth,
 * counts captured areas and announces progress / the final target. */
void area_capture_update(Object *obj, ObjHandler *handler) {
    s32 depth;
    s32 volume;
    s32 captured;
    s32 total;
    s32 i;
    GridEntry **areas;
    s32 *pos;
    s32 line;

    depth = -player_position()[1];
    depth -= 0x400;
    depth = MAX(depth <= 0x800 ? depth : 0x800, 0);
    volume = depth / 24;
    volume = MAX(volume <= 0x7F ? volume : 0x7F, 8);
    sound_set_volume(area_ambient_sound, volume);
    if (area_capture_complete_flag != 0) {
        return;
    }
    captured = 0;
    fade_in_step();
    areas = get_grid_areas();
    total = grid_flagged_count_read() - 1;
    for (i = 0; i < total; i++) {
        if ((areas[i]->flags & 3) == 3) {
            captured++;
        }
    }
    if (area_capture_count < captured) {
        area_capture_count = captured;
        if (captured == total) {
            area_capture_final_flag = 1;
            show_line((s32)"#2Target destroyed!\xA1|2");
            show_line((s32)"#1All areas under control.\xA1|2");
            show_line((s32)"#1Warning!  Warning!\xA1|2Response in centralarea, destroy immediately.\xA1");
            msg_show_slot(1, -1);
            pos = scratch_alloc(0x10);
            vec3_fixed_to_int(pos);
            cam_set_target(pos[0], 0, pos[2]);
            scratch_top -= 0x10;
            target_select(5);
        } else {
            msg_show_slot(0xB, 0xB4);
            show_line((s32)"#2Target destroyed!\xA1|2");
            show_line((s32)"#2Current area under control.\xA1|2");
            switch (area_capture_count) {
            case 1:
                line = (s32)"3 more areas to bring under control.\xA1";
                break;
            case 2:
                line = (s32)"2 more areas to bring under control.\xA1";
                break;
            default:
                line = (s32)"1 more area to bring under control.\xA1";
                break;
            }
            show_line(line);
        }
    }
    eng_set_mode(1);
    pursue_flag_set(total - area_capture_count);
    set_enemies_left(total - area_capture_count);
    if (area_capture_final_flag != 0) {
        if ((((GridEntry *)area_target_ptr)->flags & 3) == 0) {
            area_capture_complete_flag = 1;
            pursue_flag_set(0);
            warning_ack_set(0);
            target_select(0);
            ((GridEntry *)area_target_ptr)->flags &= 0xF7;
        } else if (cam_find_box() == 0) {
            ((GridEntry *)area_target_ptr)->flags = (((GridEntry *)area_target_ptr)->flags & 0xFC) | 1;
            area_capture_state[0] = 0;
        }
    }
}

/* File names referenced by address from the table at msgs_file_names; they follow this function's strings. */
const char msgs_spr_so3_name[] = "msgs_spr.so3";
const char msgs_spr_grc_name[] = "msgs_spr.grc";
const char msgs_spr_clt_name[] = "msgs_spr.clt";

extern s32 area_capture_final_flag;
extern s32 area_capture_complete_flag;
void req_push_pos(void) {
    s32 *pos;

    if (area_capture_final_flag != 0) {
        pos = (s32 *)scratch_top;
        if (area_capture_complete_flag == 0) {
            scratch_top += 0x10;
            vec3_fixed_to_int(pos);
            req_queue_push(pos[0], pos[1], pos[2], 0);
            scratch_top -= 0x10;
        }
    }
}
