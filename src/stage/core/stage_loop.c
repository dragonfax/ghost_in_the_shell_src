/* stage_loop: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void sound_stage_stop(void) {
    sound_poll_load();
    sound_timer_stop();
    sound_stop_list();
}

void pause_cooldown_tick(void) {
    if (pause_cooldown > 0) {
        pause_cooldown -= 1;
    }
}

s32 pause_ready(void) {
    return pause_cooldown < 1;
}

void pause_apply(void) {
    if (area_sound_requested != 0) {
        pause_cooldown = 0xC;
        if ((sound_is_paused() == 0) || (get_stage_end() == 4) || (get_stage_end() == 1)) {
            sound_set_fade_rate(0);
            sound_set_master_volume(0);
            sound_poll_load();
        } else {
            sound_load_finish();
            sound_set_fade_rate(area_fade_rate);
            sound_set_master_volume(0x1000);
        }
    }
    sound_toggle_pause();
}

void fade_set_frames(s32 value) {
    value += 0x5A;
    sound_fade_start((value + 0xFFF) / value);
}

/* Returns 1 when part_is_done succeeds and sound_is_fading returns 0, else 0. */
s32 stage_exit_ready(void) {
    s32 result = 0;

    if (part_is_done() != 0) {
        result = sound_is_fading() == 0;
    }
    return result;
}

/* Show one or two lines of text (and a line number) on a blank screen: for 3 frames, or with `wait` until
 * Start is pressed. */
void show_message(s32 wait, char *line1, char *line2, s32 line) {
    s32 frames;
    s32 pressed;

    svc_draw_sync(0);
    text_color_set(0, 0, 0);
    frames = 0;
    input_reset();
    set_vblank_count(0);
    pad_log_enable();
    wait_vblank_count(1);
    for (;;) {
        frame_begin();
        input_next();
        debug_set_cursor(1, 1);
        if (line1 != NULL) {
            debug_print_str(line1);
        }
        debug_set_cursor(2, 3);
        if (line2 != NULL) {
            debug_print_str(line2);
        }
        if (line != 0) {
            debug_printf(" (LINE:%d )", line);
        }
        frame_present();
        text_flip();
        pressed = pad1_pressed;
        if (wait != 0 && frames >= 3 && (pressed & PAD_START)) {
            break;
        }
        frames++;
        if (frames >= 3 && wait == 0) {
            break;
        }
    }
    svc_draw_sync(0);
    wait_vblank_count(1);
    pad_log_disable();
    input_reset();
}

/* Initialize the engine's subsystems, once. */
void engine_init(void) {
    s32 w;
    s32 h;

    if (engine_initialized == 0) {
        engine_initialized = 1;
        font_init();
        ot_depth_set(5);
        w = stage_screen_size()->w;
        h = stage_screen_size()->h;
        tile_row_draw(0, 0, w, h);
        screen_area_set(2, 12, w - 8, h - 24);
        video_mode_set(svc_video_mode());
        cam_reset();
        cam_view_reset();
        scale_vec_set(stage_screen_w * 0x1100 / 320 * video_scale() / 4096, 0x1000, 0x1000);
        vsync_init();
        cyl_init();
        rec_tables_reset();
        stage_tables_reset();
        interp_reset_all();
        part_reset_all();
        fn_800FB528();
        fn_80107188();
        query_tables_clear();
        fn_80116720();
        pair_table_init();
        fn_8010CBD0();
        lock_frame_base_clear();
        engine_palette_setup();
        fn_80107C14();
        proximity_hook_clear();
        fx_init_rects();
        particle_base_init();
    }
}

void bg_load_request(s32 a, s32 b) {
    bg_load_pending = 0;
    bg_load_name = a;
    bg_load_file = b;
}

s32 bg_load_start(void) {
    void *buf;

    debug_name_set((u8 *)bg_load_name);
    bg_load_size = file_sector_size(bg_load_file);
    if (bg_load_size > 0) {
        buf = (void *)heap2_alloc(bg_load_size);
        bg_buffer = (u32)buf; /* addresses are compared as numbers */
        if (file_read_bg_retry(bg_load_file, buf) <= 0) {
            return 0;
        }
        printf("[job ]:%s%s:$%X(%d)\n", bg_load_name, bg_load_file, bg_buffer, bg_load_size);
        bg_load_pending = 1;
    }
    debug_name_set(NULL);
    return 1;
}

/* One step of loading a stage's background data: returns 0 while it is not done (or failed), 1 when done. */
s32 bg_load_step(void) {
    s32 over;

    if (bg_load_pending != 0) {
        if (bg_buffer < heap_get_top()) {
            over = heap_get_top() - bg_buffer;
            printf("Memory Over! HEAP:%X BG:%X (%d)\n", heap_get_top(), bg_buffer, over);
            return 0;
        }
        while (file_io_poll() == 0) {
            heap2_free(bg_load_size);
            if (bg_load_start() == 0) {
                return 0;
            }
        }
        bg_load_pending = 0;
        mem_copy_blocks((void *)bg_buffer, arena_top(), bg_load_size);
        heap2_free(bg_load_size);
        set_name_table_ptr((s32)arena_alloc(bg_load_size));
        return 1;
    }
    debug_name_set((u8 *)bg_load_name);
    bg_load_size = file_seek_retry(bg_load_file);
    if (bg_load_size > 0) {
        if (file_read_retry(bg_load_file, arena_top()) <= 0) {
            return 0;
        }
        set_name_table_ptr((s32)arena_alloc(bg_load_size));
    }
    debug_name_set(NULL);
    return 1;
}

s32 load_stage_data(void) {
    ResourceRoot *rec;
    s32 *entry;

    rec = get_rec_root();
    entry = get_area_entry();
    bg_load_request(entry[0], entry[4]);
    if (stage_saved_flag != 0) {
        stage_counts_restore();
        scratch_restore();
        ptr_table_restore_mark();
        img_upload_pair();
        tex_upload_reset();
        img_upload_clear();
        stage_image_load();
        heap_set_top(stage_heap_mark);
    } else {
        arena_reset();
        set_name_table_ptr(0);
        set_name_table_ptr((s32)arena_alloc(handle_load(d_800A0000, (s32)arena_top())));
        if (bg_load_start() == 0) {
            return 0;
        }
        pchr_table_reset();
        scratch_reset();
        ptr_table_init();
        img_upload_pair();
        tex_upload_reset();
        img_upload_clear();
        stage_image_load();
        fx_palette_init();
        vram_load_images();
        if (scan_items_run(-1, rec->items) == 0) {
            return 0;
        }
        debug_name_set(NULL);
        set_name_table_ptr(0);
        arena_reset();
        stage_counts_save();
        scratch_save();
        ptr_table_save_mark();
        stage_heap_mark = heap_get_top();
        stage_saved_flag = 1;
    }
    return 1;
}

s32 load_stage_part(void) {
    s32 *part = get_area_entry();

    arena_reset();
    set_name_table_ptr(0);
    if (bg_load_step() != 0) {
        bg_load_request(part[0], part[5]);
        if (bg_load_start() != 0) {
            return named_entry_run(get_area_entry());
        }
        return 0;
    }
    return 0;
}

s32 setup_stage(void) {
    StageSetupBlock *res;
    SetupEntry *ent;
    SVECTOR *vec;
    s32 offset;
    s32 arg;

    res = get_stage_setup_block();
    ent = (SetupEntry *) get_area_entry();

    stage_setup_pair_load(1);
    model_slot_upload_clut();
    debug_name_set(ent->name);
    stage_setup_pair_load(0);
    if (stage_setup_load() == 0) {
        return 0;
    }

    if (ent->key != NULL) {
        void *rec = record_data_get(ent->key);
        if (rec == NULL) {
            return 0;
        }
        grid_load((s32) rec);
    }

    debug_name_set(NULL);
    set_name_table_ptr(0);
    arena_reset();

    offset = *(s32 *) &res->unk_00[0x70];
    arg = offset;
    if (offset > 0) {
        arg = (s32) res->unk_00 + ((offset << 8) >> 8);
    }
    set_data_base(arg);

    if (bg_load_step() == 0) {
        return 0;
    }

    stage_setup_pair_load(1);
    if (scan_record_run((u8 *) ent) == 0) {
        return 0;
    }

    set_name_table_ptr(0);
    arena_reset();

    vec = (SVECTOR *) ((u8 *) get_stage_record(0) + 0xC);
    cam_range_alt_set(vec->vx, vec->vy, vec->vz);
    cam_range_set(ent->pos[0], ent->pos[1], ent->pos[2]);
    hook_set(0x40, d_8011E460, d_8011E464);
    return 1;
}

void group_start_fade(s32 arg) {
    s32 area;

    area = get_area();
    if (area == ((area / 3) * 3)) {
        fade_set_frames(arg);
    }
}

/* Stage start: resets every subsystem and sets up view 0 as the full screen. */
void area_reinit(void) {
    s32 view;
    s16 *size;

    step_abort = 1;
    pal_accum = 0;
    counters_reset();
    mission_start();
    input_reset();
    rand_init();
    cam_view_reset_all();
    sound_stage_init();
    end_ramp_reset();
    solid_system_reset();
    fn_8011285C();
    mover_reset();
    player_spawn();
    anim_clock_reset();
    part_timer_start();
    part_fade_swap((s32)group_start_fade);
    place_view();
    pause_state_set(pause_state_get());
    debug_switches_apply();
    if (timed_part() == 0) {
        view_set_on(0, 1);
        view_set_parent(0, -1);
        view_set_camera(0, 0);
        view_set_colour(0, 0, 0, 0, 0x80);
        view_set_colour_b(0, 0, 0, 0, 0);
        view_set_colour_c(0, 0, 0, 0, 0);
        set_view_offset(0, 0, 0);
        size = &stage_screen_w;
        FAKE_OPAQUE(size);
        view_set_size(0, size[0], size[1]);
        view = 0;
        if (player_mode != 0) {
            view_set_pivot(0, size[0] / 2, size[1] / 2 - 0x10);
        } else {
            view_set_pivot(0, size[0] / 2, size[1] / 2);
        }
        fn_800C94D8(view, 0, 0);
        view_set_clip_size(view, stage_screen_w, stage_screen_h);
        cam_offset_set(0, 0, 0);
        cam_fade_set(0x1000);
    }
    pause_block_reset();
    track_reset_all();
    ring32_reset();
    sparks_reset();
    grenade_pool_init();
    fade_pool_init();
    object_slots_reset();
    fx_reset_pools();
    particle_pool_reset();
    lock_reset();
    round_reset();
    obj_system_init();
    pending_grid_reset_state1();
    hook_run_all();
    grid_camera_reset();
    fn_8010CBE0();
    interp_start_all();
    area_load_init();
    stage_ready_set(0);
}

void fn_800E5A14(void) {
    stage_begin();
}

void world_update(void) {
    s32 frozen;

    frozen = get_stage_flags() & 4;
    end_ramp_step();
    if (animation_on() != 0) {
        mission_clock_step();
    }
    player_warp();
    solid_grid_reset(player_xyz);
    grid_camera_step();
    if (frozen == 0) {
        player_frame_update();
        if (animation_on() != 0) {
            list_b_phase0();
            list_b_phase1();
        }
        list_b_phase2();
        if (!(get_stage_flags() & 0x20) && (animation_on() != 0)) {
            actors_phase0();
            actors_phase1();
        }
        actors_phase2();
        list_c_phase0();
        list_c_phase1();
        list_c_phase2();
        sparks_step();
        grenades_update();
        fx_pool_step();
        fades_step();
        records_step();
        particle_list_update();
        lock_update();
    }
    grid_pending_step();
    status_update();
    if (frozen == 0) {
        player_read_input();
        player_update();
    }
    area_load_step();
    sound_frame_update();
    if (frozen == 0) {
        place_view();
        if (animation_on() != 0) {
            if (timed_part() != 0) {
                part_timer_step();
            }
            clock_step();
            interp_step_all();
        }
        track_step_all();
        ring32_step();
    }
    objects_end_step();
}

void pause_changed(void) {
    pause_apply();
}

/* One fixed-rate step of the stage: debug camera, pause menu, or the world. */
void stage_step(void) {
    s32 pressed = pad1.pressed;
    s32 held = pad1.held;

    pause_cooldown_tick();
    if (debug_cam_on() != 0) {
        debug_cam_control();
        if (pressed & PAD_R2) {
            debug_cam_set(debug_cam_on() ^ 1);
        }
        world_update();
        return;
    }
    if (is_paused() != 0) {
        if (is_pause_blocked() == 0) {
            if (pause_menu_busy() == 0 && pause_menu() != 0) {
                pause_state_set(pause_state_get());
                toggle_paused();
                pause_changed();
            }
            if (dev_mode() != 0) {
                debug_menu_input();
                if (debug_check_b() == 0 || debug_check_a() == 0) {
                    if (pressed & PAD_R2) {
                        debug_cam_set(debug_cam_on() ^ 1);
                    }
                    if (pressed & PAD_TRIANGLE) {
                        debug_freeze();
                    }
                }
            }
        }
    } else {
        debug_cursor_reset();
        world_update();
        if (!(debug_check_b() != 0 && debug_check_a() != 0 && get_area() % 3 == 0)) {
            if (timed_part() != 0 && (held & PAD_SELECT)) {
                world_update();
                world_update();
                world_update();
            }
        }
    }
    if (debug_check_b() != 0 && debug_check_a() != 0 && get_area() % 3 == 0) {
        return;
    }
    if (!(player_controls_enabled() != 0 && meter_is_full() != 0 && get_stage_end() == 0) && dev_mode() == 0) {
        return;
    }
    if (is_pause_blocked() == 0 && (pressed & PAD_START) && pause_ready() != 0 &&
        (pause_menu_busy() != 0 || is_paused() == 0)) {
        pause_state_set(pause_state_get());
        toggle_paused();
        pause_changed();
    }
}

void stage_draw_frame(void)
{
    WorkArea *work;
    s32 paused_here;
    u8 *packet;

    work = work_area_ptr;
    text_color_set(0, 0, 0);
    spark_list_clear();
    id_table_init();
    sound_update();
    interp_sample_all((s32)work, 0);
    track_text_draw();
    if (timed_part() != 0) {
        part_view_apply();
    }
    view_update_all();
    if (timed_part() != 0) {
        part_draw();
    }
    paused_here = 0;
    player_sparks_update();
    if (is_paused() == 0 && (get_stage_flags() & 4)) {
        paused_here = 1;
        toggle_paused();
    }
    if (!(get_stage_flags() & 0x40)) {
        lock_draw_markers();
    }
    stage_reset();
    list_b_draw();
    if (!(get_stage_flags() & 0x40)) {
        actors_draw();
        list_c_draw();
        sparks_emit_effects();
        grenade_sparks_emit();
        fx_glow_pool_draw();
        fade_spawn_sparks();
        spark_spawn_from_records();
        particle_sparks_draw();
    }
    if (paused_here != 0) {
        toggle_paused();
    }
    if (pause_menu_busy() == 0) {
        if (get_area() % 3 != 0) {
            pause_menu_draw();
        }
    }
    view_draw_sorted((u8 *)work->ot + 8);
    packet = work->packet;
    work->packet = packet + 0x40;
    svc_set_draw_env(packet, &work->draw_x);
    addPrim((u8 *)work->ot + 0xC, packet);
    end_ramp_apply();
}

void end_ramp_reset(void) {
    end_ramp = 0;
    end_ramp_rate = 0;
}

/* Ramp end_ramp up to 0x1000 once the end flag is set; at the top set stage flag 1. */
void end_ramp_step(void) {
    s32 next;
    s32 ramp;

    if ((end_ramp_rate == 0) && (get_stage_flags() & 2)) {
        end_ramp_rate = 0x44;
        fade_set_frames(0x3C);
    }
    next = end_ramp + end_ramp_rate;
    ramp = 0x1000;
    if (next < 0x1001) {
        ramp = next;
    }
    end_ramp = ramp;
    if ((ramp == 0x1000) && (sound_is_fading() == 0)) {
        set_stage_flags(get_stage_flags() | 1);
    }
}

void end_ramp_apply(void) {
    if (end_ramp_rate != 0) {
        cam_offset_set(0, 0, 0);
        cam_fade_set(0x1000 - end_ramp);
    }
}

/* Debug camera: the d-pad pans it (faster with L1 and at higher debug_cam_speed levels). */
void debug_cam_control(void) {
    s32 held = pad1.held;
    s32 pressed = pad1_pressed;
    s32 step_x;
    s32 step_y;

    if (debug_cam_on() != 0) {
        step_y = 2;
        step_x = debug_cam_speed(); /* a speed level */
        if (step_x >= 4) {
            step_y = 4;
        }
        step_x = step_x >= 2 ? 4 : 2;
        if (held & PAD_L1) {
            step_x *= 3;
            step_y *= 3;
        }
        if (held & PAD_RIGHT) {
            debug_cam_pan(step_x, 0);
        }
        if (held & PAD_LEFT) {
            debug_cam_pan(-step_x, 0);
        }
        if (held & PAD_DOWN) {
            debug_cam_pan(0, step_y);
        }
        if (held & PAD_UP) {
            debug_cam_pan(0, -step_y);
        }
        if (pressed & PAD_L2) {
            debug_cam_speed_next();
        }
    }
}

s32 animation_on(void) {
    return dbg_animation;
}

s32 debug_info_on(void) {
    return debug_info_flag;
}

s32 timed_part(void) {
    u8 first_of_group;
    s32 result;

    result = 0;
    if (part_slots_in_use() != 0) {
        first_of_group = get_area() % 3 == 0;
        result = first_of_group;
    }
    return result;
}

s32 pause_menu_busy(void) {
    return debug_menu_enabled;
}
