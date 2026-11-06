/* stage_main: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void stage_main(void) {
    Pchr *pchr;
    s32 left;
    s32 num;

    debug_nop_a();
    printf("Start:No.%d\n", svc_get_exec_code());
    svc_0();
    ptr_entry_clear_targets();
    run_restore();
again:
    if (get_area() % 3 == 0 && get_run_flag_27() == 0) {
        /* next area within the same group of three */
        num = get_area();
        set_area(num / 3 * 3 + (num % 3 + 1) % 3);
    }
    engine_initialized = 0;
    scratch_top = (u8 *) 0x1F800000;
    heap_reset();
    rand_nop();
    pause_reset();
    stage_data_clear();
    arena_init((u8 *) 0x80040000, (s32) &work_area_size);
    if (sound_initialized == 0) {
        sound_reset_fade();
        sound_initialized = 1;
    }
    if (load_stage_data() == 0 || load_stage_part() == 0) {
        goto fail;
    }
    engine_init();
    if (debug_check_b() == 0 || debug_check_a() == 0) {
        show_message(0, "NOW FILE LOADING...", 0, 0);
    }
    if (setup_stage() == 0) {
        goto fail;
    }
    print_load_stats();
    pchr = pchr_table;
    num = 0;
    for (left = pchr_count - 1; left >= 0; left--, pchr++) {
        if (pchr->bounds_radius != 0) {
            num++;
        }
    }
    printf("PchrTop:%d(%d)\n", pchr_count, num);
    printf("PsprTop:%d\n", pspr_top);
    if (debug_check_b() != 0 && debug_check_a() != 0) {
        frame_begin();
    }
    debug_menu_init();
    stage_ready_set(1);
    do {
        pad_log_disable();
        svc_draw_sync(0);
        area_reinit();
        set_vblank_count(0);
        pad_log_enable();
        wait_vblank_count(1);
        do {
            debug_nop_b();
            counters_reset();
            count_draw();
            frame_begin();
            for (frames_pending = pad_log_count(); frames_pending >= 5; frames_pending--) {
                pad_log_pop();
            }
            left = frames_pending;
            if (left > 0) {
                do {
                    if (svc_video_mode() != 0) {
                        pal_accum += 0x2C0;
                    }
                    if (pal_accum >= 0x1000) {
                        pal_accum -= 0x1000;
                        input_repeat();
                        left++;
                    } else {
                        input_next();
                    }
                    if (wants_exit() != 0) {
                        goto done;
                    }
                    step_abort = 0;
                    stage_step();
                    if (step_abort != 0) {
                        break;
                    }
                    left--;
                } while (left > 0);
            }
            stage_draw_frame();
            if (is_pause_blocked() == 0) {
                debug_overlay_draw();
            }
            frame_present();
            if (is_pause_blocked() == 0) {
                text_flip();
            }
            screenshot_update();
        } while (get_stage_end() != 1);
        stage_begin();
    } while (get_area() % 3 != 2);
    __asm__ volatile(""); /* keeps the loop exit jump from being threaded to done */
    goto done;
fail:
    engine_init();
    show_message(1, "[FILE NOT FOUND]", (char *) get_file_name(), 0);
done:
    svc_draw_sync(0);
    vsync_shutdown();
    svc_wait_frames(0);
    svc_set_disp_mask(0);
    sound_stage_stop();
    {
        static const s32 clear_rect[2] = {0, 0x00D80400};
        svc_clear_image((void *) clear_rect, 0, 0, 0);
    }
    svc_draw_sync(0);
    if (stage_continue() != 0) {
        goto again;
    }
    record_run_result();
    printf("Term\n");
    sound_reset_state();
    choose_next_exec();
    stage_exit();
}

/* Called after an attempt; its result tells the stage main loop whether to go on (see FINDINGS "Stage main"). */
s32 stage_continue(void) {
    s32 first_part;
    s32 area;

    if (get_stage_end() == 1) {
        area = get_area();
        set_area(area / 3 * 3);
    }
    first_part = get_area() % 3 == 0;
    area = get_area();
    area_next_part();
    if (first_part) {
        return 1;
    }
    if (debug_check_b() != 0) {
        if (get_stage_end() != 2) {
            return 0;
        }
        return area < get_area();
    }
    if (get_stage_end() != 2 || area >= get_area()) {
        fn_800E5A14();
    }
    return 1;
}

/* Move to the next part of the current mission (wrapping to its first part), skipping parts without an
 * area entry. */
void area_next_part(void) {
    s32 current;
    s32 mission;
    s32 part;

    do {
        current = get_area();
        part = current % 3; /* before mission: keeps the original's copy of the quotient */
        mission = current / 3;
        set_area(mission * 3 + (part + 1) % 3);
    } while (get_area_entry() == NULL);
}

s32 wants_exit(void) {
    s32 pressed = pad1_pressed;
    s32 held = pad1.held;
    s32 exit = 0;

    if (get_area() % 3 == 0) {
        if (debug_check_b() && debug_check_a()) {
            s32 start = pressed & PAD_START;
            exit = start != 0;
            if (stage_exit_ready()) {
                exit = 1;
            }
        }
    } else if (player_mode && dev_mode() && (held & PAD_SELECT) && get_stage_end() == 0) {
        if (pressed & PAD_R2) {
            set_stage_end(2);
        } else if (pressed & PAD_L2) {
            set_stage_end(3);
        }
    }
    if (dev_mode() && (pressed & PAD_SELECT) && is_paused() && !debug_cam_on()) {
        exit = 1;
    }
    if (get_stage_flags() & 1) {
        exit = 1;
    }
    return exit;
}

/* Picks the exec code to run next: the next mission's stage after a clear. */
void choose_next_exec(void) {
    s32 exec = 0;
    s32 mission = get_area() / 3;

    switch (get_stage_end()) {
    case 2:
        exec = mission + 10;
        if (mission != 12) {
            mission++;
            if (mission > 11) {
                mission = 11;
            }
            exec = mission + 10;
        }
        break;
    case 3:
        if (mission == 12) {
            exec = 0x16;
        }
        break;
    default:
        exec = 0;
        break;
    }
    printf("Exec:%d\n", exec);
    svc_set_exec_code(exec);
}

void area_load_request(s32 duration) {
    s32 next_index;

    area_load_next = -1;
    area_load_timer = 0;
    area_load_duration = 1;
    next_index = area_sound_index + 1;
    if (area_is_loadable(next_index) != 0) {
        area_load_next = next_index;
        area_load_timer = duration + 8;
        area_load_duration = duration;
    }
}

s32 area_load_pending(void) {
    return area_load_timer > 0;
}

void area_load_commit(void) {
    if (area_load_next >= 0) {
        area_sound_index = area_load_next;
        area_load_next = -1;
        area_sound_requested = 0;
    }
}

void area_load_step(void) {
    s32 loaded;
    s32 tries;
    s32 fade;

    if (area_load_timer > 0) {
        fade = area_load_timer--;
        fade -= 9;
        if (fade < 0) {
            fade = 0;
        }
        sound_set_fade_rate(fade * area_fade_rate / area_load_duration);
        if (area_load_timer == 0) {
            area_load_commit();
        } else if (area_load_timer == 8) {
            sound_set_fade_rate(0);
            sound_poll_load();
        }
    }
    if (area_sound_requested == 0 && sound_is_paused() == 0) {
        sound_set_fade_rate(0);
        loaded = sound_load_begin(area_sound_index, 1) >= 0;
        if (loaded == 0) {
            printf("FileNotExist!%d\n", area_sound_index);
        }
        sound_set_fade_rate(area_fade_rate);
        area_sound_requested = 1;
        if (get_area() % 3 == 0 && loaded != 0) {
            for (tries = 300; tries > 0; tries--) {
                if (sound_is_ready() != 0) {
                    break;
                }
                svc_wait_frames(0);
            }
        }
    }
}

void area_load_init(void) {
    s32 area_now;
    s32 mission;
    s32 value;

    area_sound_requested = 0;
    pause_cooldown = 0;
    area_now = get_area();
    mission = area_now / 3;
    value = area_now % 3;
    FAKE_OPAQUE(mission);
    area_sound_index = mission * 3 + 0x20 + value;
    mission = get_area() / 3;
    value = 0x3B00;
    if (mission == 5 || mission == 3) {
        value = 0x40E6;
    }
    area_load_next = -1;
    area_fade_rate = value;
    area_load_timer = 0;
    area_load_duration = 1;
    sound_fade_start(0);
}
