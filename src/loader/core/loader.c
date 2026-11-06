/* loader: one of loader's own original source files (scripts/objmap.py); part of src/loader/main.c's unit, included there. */

void loader_screen_init(void) {
    s32 i;
    s32 off;

    loader_set_disp_env(&loader_draw_bufs, 0, 0, 0x100, 0xF0);
    loader_set_disp_env(&loader_disp_env_b, 0, 0x100, 0x100, 0xF0);
    loader_set_draw_env(&loader_draw_env, 0, 0, 0x100, 0xF0);
    loader_set_draw_env((u8 *)&loader_draw_bufs + 0x14, 0, 0x100, 0x100, 0xF0);

    for (i = 0; i < 2; i++) {
        off = i * sizeof(LoaderDrawBuf);
        D_80154590[off] = 1;
        D_80154591[off] = 0;
        D_80154592[off] = 0;
        D_80154593[off] = 0;
        D_8015458E[off] = 0;
        if (loader_get_video_mode() != 0) {
            ((LoaderDrawBuf *)((u8 *)&loader_draw_bufs + off))->unk_A += 0x18;
        }
    }

    loader_set_enabled(0);
    loader_register_sprite_sets(&loader_sprite_sets, 0);
    loader_alloc_sprite_slots(loader_font_tiles, ((u32)&loader_brightness - (u32)loader_font_tiles) >> 6);
    for (i = 0; i < 0x10; i++) {
        loader_upload_clut(loader_clut_data, i);
    }
    loader_pool_init();
}

extern s32 loader_buf_ptr;
extern s32 loader_draw_bufs;
u32 *loader_ot_clear(s32 ot, s32 n);
void loader_buf_switch(void) {
    s32 next = (s32)&loader_draw_bufs;

    if (loader_buf_ptr == next) {
        next += 0x20080;
    }
    loader_buf_ptr = next;
    loader_ot_clear(next + 0x70, 3);
    *(s32 *)(loader_buf_ptr + 0x2007C) = loader_buf_ptr + 0x7C;
}

extern s32 loader_buf_ptr;

s32 loader_buf_current(void) {
    return loader_buf_ptr;
}

s32 loader_state_at_least_2(void) {
    return loader_get_status() >= 2U;
}

extern EventMovieEntry event_movie_table[];
extern s32 loader_event_flag;
void loader_set_flag(s32 index);
s32 loader_get_bank_offset(void);
s32 loader_is_ready(void);
s32 loader_get_dev_mode(void);
void loader_show_entry(s32 unused, s32 mode);
void loader_play_event_movie(s32 first) {
    s32 saved;
    s32 flag;
    s32 index;

    if (first >= 0) {
        index = 0x17;
        if (first < 0x18) {
            index = first;
        }
    } else {
        index = 0;
    }
    first = event_movie_table[index].first;
    flag = event_movie_table[index].flag;
    saved = first;
    if (first >= 0) {
        loader_set_flag(first);
        first += loader_get_bank_offset();
        if (loader_is_ready() != 0) {
            if (loader_get_dev_mode() == 1) {
                flag = 1;
            }
            loader_show_entry(first, flag);
        }
        if (saved == 5) {
            loader_event_flag = loader_state_at_least_2();
            loader_set_flag(6);
            first = loader_get_bank_offset() + 6;
            loader_show_entry(first, loader_get_dev_mode() == 1);
        }
    }
}

extern u8 svc_table[];

char loader_bios_error_msg[24] = "BIOS:Version Error.\r";
extern char loader_bios_error_msg[];

extern u8 *vab_file_names[24];
extern s32 func_800E2AE8(void);
extern void (*slot_0A0)(s32, void *, s32);
extern void (*slot_0A3)(s32);
extern s32 (*slot_read_file)(u8 *name, void *dest, s32 mode);
extern s32 printf(const char *fmt, ...);
void loader_load_vab(s32 index) {
    s32 slot;
    u8 *name;
    void *buffer;

    if (index >= 0) {
        slot = 0x17;
        if (index < 0x18) {
            slot = index;
        }
    } else {
        slot = 0;
    }
    name = vab_file_names[slot];
    if (name != NULL) {
        buffer = (void *) func_800E2AE8();
        while (slot_read_file(name, buffer, 0) < 0) {
            printf("Retry:%s\n", name);
        }
        slot_0A3(1);
        slot_0A0(1, buffer, 0);
    }
}

extern void (*slot_0A2)(s32);
void loader_spu_transfer_on(void) {
    slot_0A2(1);
}

extern s32 stage_exec_codes[];
/* Returns table[idx], with idx clamped to 0..0x17 (negative -> 0, >= 0x18 -> 0x17). */
s32 loader_stage_exec_code(s32 idx) {
    s32 i;

    if (idx >= 0) {
        i = 0x17;
        if (idx < 0x18) {
            i = idx;
        }
    } else {
        i = 0;
    }
    return stage_exec_codes[i];
}

extern s32 loader_event_flag;
void loader_set_stage(s32 idx) {
    register void (**slot)(s32) __asm__("$16");
    s32 value;

    value = loader_stage_exec_code(idx);
    slot = (void (**)(s32))0x80010018;
    (*slot)(value);
    if (loader_event_flag == 0) {
        (*slot)(8);
    }
}

extern ResourceEntry *loader_stage_exe; /* the stage exe to run (loader_main) */
extern s32 loader_stage_vab_index;           /* its VAB index */
extern s32 loader_finished_flag;
extern void (*slot_102)(s32);
/* Loads the stage's VAB, reads the stage exe to its load address (retrying until the read works), marks the
 * loader finished and hands over: service 0x102 never returns. */
void loader_run_stage(void) {
    u32 addr;

    loader_load_vab(loader_stage_vab_index);
    addr = loader_stage_exe->unk_00;
    addr &= ~3;
    while (slot_read_file(loader_stage_exe->path, (void *)addr, 0) < 0) {
        printf("EXE Retry:%s\n", loader_stage_exe->path);
    }
    loader_finished_flag = 1;
    loader_spu_transfer_on();
    for (;;) {
        slot_102(0);
    }
}

extern s32 loader_finished_flag;

s32 loader_is_finished(void) {
    return loader_finished_flag;
}

extern s32 loader_stop_flag;

void loader_request_stop(void) {
    loader_stop_flag = 1;
}

void loader_init(s32 arg);
s32 loader_set_brightness(s32 value);
void loader_run_callbacks(void);
void loader_run_callbacks2(void);
void loader_display_update(s32 src_env, s32 buf_b, s32 arg_c);
void screen_reset(void);
void loader_thread_loop(s32 *ctx) {
    s32 state;

    loader_init((s32)ctx);
    state = *ctx;
    loader_stop_flag = 0;
    if (state >= 0) {
        while (1) {
            loader_buf_switch();
            loader_set_brightness(0x80);
            loader_run_callbacks();
            loader_run_callbacks2();
            if (loader_stop_flag != 0) {
                break;
            }
            loader_display_update(loader_buf_ptr, loader_buf_ptr + 0x14, loader_buf_ptr + 0x70);
        }
    }
}

extern u8 svc_table[];
extern LoaderEvent loader_events[];
extern u16 loader_stage_rot[];
extern s32 loader_stage_trans[];
extern s32 loader_stage_scale[];
extern u32 loader_run_stage_arg[];
extern s32 loader_run_stage_id;
extern ResourceEntry *loader_stage_exe;
extern s32 loader_stage_vab_index;
extern void (*slot_0B3)(void);
extern s32 (*slot_0A5)(void);
extern s32 (*slot_0A9)(void);
extern void (*slot_0A6)(s32);
extern void (*slot_0AA)(s32);
extern void (*slot_101)(s32);
extern s32 (*slot_100)(void *fn, void *arg, s32 mode);
extern ResourceEntry *(*slot_resource_entry)(void *);
void func_800E5FC4(void);
void loader_run_stage(void);
void loader_set_disp_mask(s32 mask);
void loader_screen_reset(void);
void loader_set_shared_cc(s32 value);
void loader_read_tone_volume(void);
s32 loader_get_event(void);
void loader_set_matrices(u16 *rot, void *trans, void *scale);
void loader_run_event(void) {
    LoaderEvent *event;
    void (**slot_0A4_ptr)(s32); /* the slot table entry at 0x80010290 */
    void (**slot_0A8_ptr)(s32); /* the slot table entry at 0x800102A0 */
    void (**slot_1C3_ptr)(s32); /* the slot table entry at 0x8001070C */

    func_800E5FC4();
    loader_event_flag = 1;
    if ((*(s32 (**)(void))svc_table)() != 0x300) {
        printf(loader_bios_error_msg);
        while (1) {}
    }
    loader_screen_reset();
    loader_set_shared_cc(0);
    loader_read_tone_volume();
    slot_0A4_ptr = (void (**)(s32))0x80010290;
    (*slot_0A4_ptr)(0);
    slot_0A8_ptr = (void (**)(s32))0x800102A0;
    (*slot_0A8_ptr)(0);
    slot_0B3();
    slot_1C3_ptr = (void (**)(s32))0x8001070C;
    (*slot_1C3_ptr)(0);
    (*slot_1C3_ptr)(0);
    (*slot_0A4_ptr)(0x3FFF);
    (*slot_0A8_ptr)(0x3900);
    slot_0A6(1);
    slot_0AA(1);
    while (slot_0A5() != 0) {}
    while (slot_0A9() != 0) {}
    loader_play_event_movie(loader_get_event());
    event = &loader_events[loader_get_event()];
    if (event->state >= 0) {
        screen_reset();
        loader_screen_init();
        loader_finished_flag = 0;
        loader_stage_vab_index = loader_get_event();
        loader_stage_exe = slot_resource_entry((void *)loader_stage_exec_code(loader_get_event()));
        loader_run_stage_id = slot_100(loader_run_stage, loader_run_stage_arg, 0);
        loader_set_matrices(loader_stage_rot, loader_stage_trans, loader_stage_scale);
        if (event->unk_08 != 0) {
            loader_thread_loop((s32 *)event);
        }
        while (loader_is_finished() == 0) {}
        slot_101(loader_run_stage_id);
    }
    loader_set_stage(loader_get_event());
    loader_set_disp_mask(0);
}
