/* title_main: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

void title_main(void) {
    s32 i;
    s32 count;

    title_noop();
    title_init();
    title_ctl_start();
    do {
        title_draw_buffer_swap();
        count = title_queue_count();
        for (i = 0; i < count; i++) {
            title_get_pad_state();
            title_pad_update(i);
            tasks_update();
            title_sound_update();
            if (title_phase_get() == 1) {
                break;
            }
        }
        SCRATCH_STACK_ENTER_BELOW(0x1F8003D0);
        tasks_draw();
        SCRATCH_STACK_LEAVE_BELOW();
        title_draw_sync(0);
        frame_wait();
        frame_end();
    } while (title_phase_get() != 1);
    title_teardown();
}

extern s32 card_work_buf;
void clear_image(void *rect, s32 r, s32 g, s32 b);
void func_800A1818(void);
void title_set_disp_mask(s32 mask);
void InitGeom(void);
void title_input_init(void);
s32 func_800BC1D0(void);
void rec_queue_reset(void);
void title_state_update(void);
void title_items_init(void);
void title_flag_clear(void);
void title_sprites_load(void);
void tasks_init(void);
void title_ctls_init(void);
void title_screen_init(void);
void title_seq_init(void);
void title_load_assets(void);
void title_prims_init(void);
void title_panel_init(void);
void title_init_menu_ctls(void);
void title_timer_init(void);
void title_scene_init(void);
void title_records_init(void);
void title_scratch_init(void);
void title_gradient_init(void);
void title_ctl_init(void);
void title_setup(void);
void rec_queue_flush(void);
void display_init(void);
void title_init(void) {
    s16 rect[4];
    void title_rec_pool_init(void);

    func_800A1818();
    title_set_disp_mask(0);
    rect[2] = 0x400;
    rect[0] = 0;
    rect[1] = 0;
    rect[3] = 0x200;
    clear_image(rect, 0, 0, 0);
    InitGeom();
    gte_set_ctrl(OFX, 0xA00000);
    gte_set_ctrl(OFY, 0x780000);
    gte_set_ctrl(H, 0x100);
    title_input_init();
    card_work_buf = func_800BC1D0();
    rec_queue_reset();
    title_state_update();
    title_items_init();
    title_flag_clear();
    title_sprites_load();
    tasks_init();
    title_rec_pool_init();
    title_ctls_init();
    title_screen_init();
    title_seq_init();
    title_load_assets();
    title_prims_init();
    title_panel_init();
    title_init_menu_ctls();
    title_timer_init();
    title_scene_init();
    title_records_init();
    title_scratch_init();
    title_gradient_init();
    title_ctl_init();
    title_setup();
    rec_queue_flush();
    display_init();
    title_set_disp_mask(1);
}

void title_rect_pad_move(s32 pad, u16 *rect) {
    if (pad & 0x2000) {
        rect[0] += 0x10;
    }
    if (pad & 0x8000) {
        rect[0] -= 0x10;
    }
    if (pad & 0x1000) {
        rect[1] -= 0x10;
    }
    if (pad & 0x4000) {
        rect[1] += 0x10;
    }
    if (pad & 0x8) {
        rect[2] = 0x100;
        rect[3] = 0xF0;
    }
    if (pad & 0x2) {
        rect[2] = 0x200;
        rect[3] = 0x1E0;
    }
}

extern s32 D_8010D6F0[6];
extern s32 task_list_sentinel[3];
extern void *task_list_head;
extern void *task_list_insert_slot[6];
extern s32 D_8010D714;
void tasks_init(void) {
    void *next = task_list_sentinel;
    s32 *p = D_8010D6F0;

    *p = 0;
    task_list_head = next;
    task_list_insert_slot[0] = (char *)p - 0x10;
    D_8010D714 = 0;
}

void task_reset(TitleCtl *ctl) {
    ctl->unk_1C = 0;
    ctl->step = 0;
    ctl->unk_1E = 1;
}

void task_set(TitleTaskRec *rec, s32 a1, s32 a2, s32 a3, s32 a4) {
    rec->reset_fn = a1;
    rec->update_fn = a2;
    rec->draw_fn = a3;
    rec->param = a4;
}

void task_link(void **node);
/* Starts a task node: stores mode and param, marks it active (state 1; the
 * 32-bit read at 0x1C checks state and unk_1E together), clears unk_1E/20/22,
 * runs the node's update callback if set, then links the node into the list. */
s32 task_start(s32 mode, void *node_ptr, s32 param) {
    TitleTaskNode *node = node_ptr;
    void (*update)(void *node);

    if (*(s32 *) &node->state == 1) {
        return 0;
    }
    update = node->update;
    node->mode = mode;
    node->state = 1;
    node->unk_1E = 0;
    node->sub_state = 0;
    node->unk_20 = 0;
    node->param = param;
    if (update != NULL) {
        update(node);
    }
    task_link((void **) node);
    return 1;
}

void task_unlink(TitleLinkNode *link);
void tasks_update(void) {
    TitleTaskListNode *node = task_list_head;
    TitleTaskListNode *cur;

    while (node->next != 0) {
        if (node->update != 0 && node->state == 0 && node->hold == 0) {
            node->update(node);
        }
        cur = node;
        node = node->next;
        if (cur->state == 1) {
            task_unlink((TitleLinkNode *)cur);
            cur->active = 0;
        }
    }
}

/* Walks the list headed by task_list_head, calling each node's callback when
 * both of its 16-bit flags (0x1E, 0x20) are clear. The last node is not visited. */
void tasks_draw(void) {
    TitleCallbackNode *node = task_list_head;

    if (node->next != NULL) {
        do {
            if (node->callback != NULL && node->unk_1E == 0 && node->unk_20 == 0) {
                node->callback(node);
            }
            node = node->next;
        } while (node->next != NULL);
    }
}

/* Returns 1 and marks the record as set the first time it is called; returns 0 once it is already set. */
s32 title_flag_test_set(void *p) {
    TitleFlagRec *rec = p;

    if (rec->unk_1E == 1) {
        return 0;
    }
    rec->unk_1E = 1;
    return 1;
}

/* Resets every node of the list headed by task_list_head (state 0, flagged,
 * unlinked), empties the list (as tasks_init does), then links node in
 * as the only active one. */
void tasks_restart_with(TitleListNode *node) {
    TitleListNode *prev;
    TitleListNode *cur;
    void **head;

    cur = task_list_head;
    if (cur->next != 0) {
        do {
            prev = cur;
            cur->state = 0;
            cur->flag = 1;
            cur->unk_10 = 0;
            cur = cur->next;
            prev->next = 0;
        } while (cur->next != 0);
    }
    head = &task_list_head;
    *head = task_list_sentinel;
    task_list_insert_slot[0] = head - 3;
    task_link((void **)node);
    node->state = 1;
    node->flag = 0;
}

/* Sets the flag on every node of the list headed by task_list_head except skip.
 * The last node (next == 0) is not visited. */
void tasks_pause_others(TitleFlagNode *skip) {
    TitleFlagNode *node = task_list_head;

    if (node->next != 0) {
        do {
            if (node != skip) {
                node->flag = 1;
            }
            node = node->next;
        } while (node->next != 0);
    }
}

void tasks_resume(void) {
    TitleFlagNode *node = task_list_head;

    if (node->next != NULL) {
        do {
            node->flag = 0;
            node = node->next;
        } while (node->next != NULL);
    }
}

extern void *task_list_insert_slot[6];
/* Push node onto the front of the list headed by task_list_insert_slot.
 * Node links sit at 0xC (prev, points at the head slot minus 0x10)
 * and 0x10 (next, the old head). */
void task_link(void **node) {
    void **head_slot = task_list_insert_slot;
    void *old_head = *head_slot;

    node[3] = (char *) head_slot - 0x10;
    node[4] = old_head;
    ((void **) old_head)[3] = node;
    *head_slot = node;
}

void task_unlink(TitleLinkNode *link) {
    TitleLinkNode *next = link->next;
    TitleLinkNode *prev = link->prev;

    next->prev = prev;
    prev->next = next;
}

extern TitleDrawCtx title_draw_ctx;
extern s32 title_frame_count;
extern s32 title_second_timer;
extern volatile s32 title_vblank_ready;
extern s32 title_fps;
extern s32 frame_wait_count;
void title_vblank_task();  /* a function reached by pointer */
void set_display_on(s32 arg0);
void display_buffer_init(TitleWindow *win, s32 x, s32 y, s32 a3, s32 a4);
void set_def_draw_env(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void display_start(void);
void title_phase_set(s32 arg0);
void title_table_request(s32 which, s32 x, s32 y, s32 w, s32 value);
void title_vblank_unpause(void);
void add_vblank_task(void (*task)(void));
void display_init(void) {
    title_frame_count = 0;
    title_second_timer = 0;
    title_vblank_ready = 0;
    title_fps = 0;
    frame_wait_count = 0;
    set_display_on(1);
    display_buffer_init((TitleWindow *)&title_draw_ctx, 0x140, 0, 0, 0);
    display_buffer_init((TitleWindow *)((u8 *)&title_draw_ctx + 0x78), 0x280, 0, 0x140, 0);
    display_buffer_init((TitleWindow *)((u8 *)&title_draw_ctx + 0xF0), 0, 0, 0x280, 0);
    display_start();
    title_phase_set(0);
    title_vblank_unpause();
    add_vblank_task((void (*)(void))title_vblank_task);
}

extern TitleDrawCtx title_draw_ctx;
extern u8 prim_buf_start[];
extern void *prim_buf_cur;
extern TitleDrawCtx *title_draw_ctx_ptr;
void title_put_disp_env(TitleDrawCtx *ctx);
void *func_800A1A10(void *env);
void title_wait_frame(void);
void title_draw_buffer_swap(void);
void title_pad_clear(void);
void title_queue_clear(void);
void display_start(void) {
    title_put_disp_env(&title_draw_ctx);
    func_800A1A10(&title_draw_ctx.draw_env);
    title_wait_frame();
    title_wait_frame();
    prim_buf_cur = prim_buf_start;
    title_draw_ctx_ptr = &title_draw_ctx;
    title_draw_buffer_swap();
    title_pad_clear();
    title_queue_clear();
}

s32 title_video_is_pal(void);
void display_buffer_init(TitleWindow *win, s32 x, s32 y, s32 a3, s32 a4) {
    s16 var_v1;

    set_def_draw_env((s32)win->sub_14, a3, a4, 0x140, 0xF0);
    win->dtd = 1;
    win->w = 0x140;
    win->x = x;
    win->y = y;
    win->h = 0xF0;
    if (title_video_is_pal() == 1) {
        var_v1 = 0x18;
        win->unk_12 = 1;
    } else {
        var_v1 = 0;
        win->unk_12 = 0;
    }
    win->screen_x = 1;
    win->screen_w = 0xFE;
    win->screen_h = 0xF0;
    win->tpage = 0x2C;
    win->screen_y = var_v1;
    win->isinter = 0;
    win->isrgb24 = 0;
    win->isbg = 1;
    win->bg_r = 0;
    win->bg_g = 0;
    win->bg_b = 0;
}

/* Same code as get_area (s01). */
s32 title_get_fps(void) {
    return title_fps;
}

/* Same code as heap_get_top (s01). */
s32 title_get_heap_top(void) {
    return frame_wait_count;
}

extern s32 title_frame_count;
extern volatile s32 title_vblank_ready;
extern s32 frame_wait_count;
void frame_wait(void) {
    title_frame_count += 1;
    if (title_vblank_ready == 0) {
        do {
            frame_wait_count += 1;
        } while (title_vblank_ready == 0);
    }
}

extern u8 prim_buf_end[];
extern TitleDrawCtx draw_ctx_last;
u32 *title_ot_clear(u8 *ot, s32 n);
/* Swaps to the next primitive buffer and draw context, clears its OT. */
void title_draw_buffer_swap(void) {
    TitleDrawCtx *ctx;
    u8 *ot;
    u8 *buf;

    frame_wait_count = 0;
    if (prim_buf_cur == prim_buf_end) {
        prim_buf_cur = prim_buf_start;
    } else {
        prim_buf_cur = (u8 *)prim_buf_cur + 0x28200;
    }
    if (title_draw_ctx_ptr == &draw_ctx_last) {
        title_draw_ctx_ptr -= 2;
    } else {
        title_draw_ctx_ptr++;
    }
    buf = prim_buf_cur;
    scratch_top = buf;
    ctx = title_draw_ctx_ptr;
    ot = buf + 0x28000;
    ctx->ot_base = ot;
    ctx->prim_base = buf;
    title_ot_clear(ot, 0x80);
    title_vblank_ready = 0;
}

extern s32 title_display_on_flag;

void set_display_on(s32 arg0) {
    title_display_on_flag = arg0;
}

extern s32 title_vblank_paused;

void vblank_pause(void) {
    title_vblank_paused = 1;
}

/* Same code as sway_disable (s01). */
void title_vblank_unpause(void) {
    title_vblank_paused = 0;
}

s32 read_pad(s32 code);
void title_queue_push(s32 value);
void title_vblank_task(void) {
    s32 prev;

    if (title_vblank_paused == 1) {
        return;
    }
    if (title_vblank_ready == 0) {
        if (title_display_on_flag == 1) {
            title_put_disp_env(title_draw_ctx_ptr);
        }
        title_vblank_ready = 1;
        title_queue_clear();
    }
    title_queue_push(read_pad(0));
    title_second_timer = title_second_timer + 1;
    if (title_second_timer < 60) {
        return;
    }
    prev = title_frame_count;
    title_frame_count = 0;
    title_second_timer = 0;
    title_fps = prev;
}

extern TitleDrawCtx *title_draw_ctx_ptr;
void *func_800A1A10(void *env);
void title_draw_otag(void *draw_env);
/* Hands the sub-block and the ordering-table entry at +0x1FC to the title draw helpers. */
void frame_end(void) {
    func_800A1A10(&title_draw_ctx_ptr->draw_env);
    title_draw_otag(title_draw_ctx_ptr->ot_base + 0x1FC);
}

extern void (*slot_1C0)(s32);
/* Stops with the BIOS version message unless the boot exe's services report version 0x300, then calls
 * service 0x1C0 with 0. */
void func_800A1818(void) {
    if (((s32 (*)(void))SVC_TABLE[0])() != 0x300) {
        printf(BIOS_VERSION_ERROR);
        for (;;) {
        }
    }
    slot_1C0(0);
}

extern void (*slot_1D9)(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void set_def_draw_env(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    slot_1D9(a0, a1, a2, a3, a4);
}

extern void (*slot_1DA)(MovieDispEnv *, s32, s32, s32, s32);
void func_800A18AC(MovieDispEnv *env, s32 a1, s32 a2, s32 a3, s32 a4) {
    slot_1DA(env, a1, a2, a3, a4);
}

extern s32 (*slot_LoadImage)(ClutRect *rect, u16 *data);
s32 title_load_image(ClutRect *rect, u16 *data) {
    return slot_LoadImage(rect, data);
}

extern void (*slot_clear_image)(void *rect, s32 r, s32 g, s32 b);
void clear_image(void *rect, s32 r, s32 g, s32 b) {
    slot_clear_image(rect, r & 0xFF, g & 0xFF, b & 0xFF);
}

extern u32 *(*slot_ClearOTagR)(u8 *ot, s32 n);
u32 *title_ot_clear(u8 *ot, s32 n) {
    return slot_ClearOTagR(ot, n);
}

extern s32 (*slot_draw_sync)(s32 mode);
/* Same code as loader_wait_frames (loader). */
s32 title_draw_sync(s32 mode) {
    return slot_draw_sync(mode);
}

extern s32 title_frame_task_id;
extern s32 (*slot_add_frame_task)(void (*fn)(void), s32 period);
void add_vblank_task(void (*task)(void)) {
    title_frame_task_id = slot_add_frame_task(task, 0);
}

extern void (*slot_006)(void);
void title_phase_set(s32 arg0);
/* Calls the hook at slot_006, then stores 1 through title_phase_set.
 * Callers pass an id (0x16 from the exit task) that is unused. */
void title_request_exit(s32 unused) {
    slot_006();
    title_phase_set(1);
}

extern void (*slot_put_disp_env)(MovieDispEnv *);
/* Forwards its argument (the draw context) to the PutDispEnv slot unchanged. */
void title_put_disp_env(TitleDrawCtx *ctx) {
    slot_put_disp_env((MovieDispEnv *)ctx);
}

extern void *(*slot_1C2)(void *env);
/* Forwards its draw env (the title draw context's draw_env) to slot 0x1C2 unchanged. */
void *func_800A1A10(void *env) {
    return slot_1C2(env);
}

extern void (*slot_DrawOTag)(void *draw_env);
/* Same code as func_800A1A10 (title). */
void title_draw_otag(void *draw_env) {
    slot_DrawOTag(draw_env);
}

extern void (*slot_set_disp_mask)(s32 mask);
/* Same code as loader_wait_frames (loader). */
void title_set_disp_mask(s32 mask) {
    slot_set_disp_mask(mask);
}

extern s32 (*slot_read_pad)(s32);
s32 read_pad(s32 code) {
    return slot_read_pad(code & 0xFFFF);
}

extern u8 *(*slot_038)(s32);
u8 *title_glyph_lookup(s32 code) {
    return slot_038(code & 0xFFFF);
}

extern Pad3dSoundInfo *(*slot_shared_state)(void);
/* Same code as svc_remove_frame_task (s01). */
Pad3dSoundInfo *title_shared_state_get(void) {
    return slot_shared_state();
}

extern s32 title_phase;

void title_phase_set(s32 arg0) {
    title_phase = arg0;
}

extern s32 title_phase;

s32 title_phase_get(void) {
    return title_phase;
}

extern s32 title_frame_task_id;
extern void (*slot_remove_frame_task)(s32);
extern void (*slot_0A4)(s32);
extern void (*slot_0A8)(s32);
extern void (*slot_144)(void);
extern void (*slot_141)(void);
s32 title_draw_sync(s32 mode);
void title_stop_services(void);
void title_teardown(void) {
    title_draw_sync(0);
    slot_remove_frame_task(title_frame_task_id);
    slot_0A4(0);
    slot_0A8(0);
    slot_144();
    title_stop_services();
    slot_141();
}

extern s32 (*slot_002)(void);
/* Same code as func_800E12C0 (loader). */
s32 func_800A1BB4(void) {
    return slot_002();
}

extern void (*slot_0A7)(s32 handle);
/* Same code as svc_remove_frame_task (s01). */
void func_800A1BDC(s32 handle) {
    slot_0A7(handle);
}

extern void (*slot_0A6)(s32 handle);
/* Same code as svc_remove_frame_task (s01). */
void title_remove_frame_task(s32 handle) {
    slot_0A6(handle);
}

extern void (*slot_0B3)(void);
/* Same code as loader_remove_frame_task (loader). */
void func_800A1C2C(void) {
    slot_0B3();
}

extern s32 (*slot_004)(void);
/* Same code as svc_remove_frame_task (s01). */
s32 title_video_is_pal(void) {
    return slot_004();
}

extern void (*slot_1C3)(s32);
void title_wait_frame(void) {
    slot_1C3(0);
}

extern u8 *(*slot_009)(void);
s32 title_is_t_build(void) {
    u8 c;

    c = *slot_009();
    if (c == 'T' || c == 't') {
        return 1;
    }
    return 0;
}

extern s32 title_input_locked; /* cleared on setup */
extern s32 title_input_mask_value; /* 0x820 or 0x840, picked by func_800A1BB4 */
extern s32 title_input_step_value; /* 0x40 or 0x10, paired with title_input_mask_value */
s32 func_800A1BB4(void);
void title_pad_clear(void);
void title_queue_clear(void);
void title_input_init(void) {
    s32 step;

    title_pad_clear();
    title_queue_clear();
    title_input_locked = 0;
    if (func_800A1BB4() == 0) {
        title_input_mask_value = 0x820;
        step = 0x40;
    } else {
        title_input_mask_value = 0x840;
        step = 0x10;
    }
    title_input_step_value = step;
}

extern u8 title_pad_state[];
u32 *title_get_pad_state() {
    return (u32 *)title_pad_state;
}

extern u8 title_pad_state[];
extern s32 title_pad_last[8];
extern u32 title_idle_timer;
extern s32 title_button_masks[];
void title_pad_update(s32 index) {
    TitlePadState *pad = (TitlePadState *)title_pad_state;
    s32 new_buttons;
    u32 i;

    title_pad_last[0] = pad->pad_cur;
    new_buttons = title_queue_get(index);
    if (new_buttons == 0) {
        title_idle_timer = title_idle_timer + 1;
        if (title_idle_timer > 0x34BC0) {
            title_idle_timer = 0x34BC0;
        }
    } else {
        title_idle_timer = 0;
    }
    if (title_input_locked == 1) {
        new_buttons = 0;
    }
    for (i = 0; i < 14; i++) {
        s32 mask = title_button_masks[i];
        if (pad->pad_held & mask) {
            if (new_buttons & mask) {
                pad->hold_frames[i]++;
            } else {
                pad->hold_frames[i] = 0;
            }
        }
    }
    pad->pad_cur = new_buttons;
    pad->pad_released = ~pad->pad_held & new_buttons;
}

extern u8 title_pad_state[];
extern s32 D_8010D774;
extern s32 title_pad_last[8];
/* Clears title-screen state: words at offsets 0 and 0x28 of title_pad_state,
 * 14 halfwords at offsets 0x0C..0x26, and the globals D_8010D774/title_pad_last. */
void title_pad_clear(void) {
    s32 i;
    u8 *base;
    s16 *p;

    i = 13;
    base = title_pad_state;
    p = (s16 *)(base + 0x1A);
    title_pad_last[0] = 0;
    *(s32 *)base = 0;
    D_8010D774 = 0;
    do {
        p[6] = 0;
        i -= 1;
        p -= 1;
    } while (i >= 0);
    *(s32 *)(base + 0x28) = 0;
}

extern s32 title_queue_len;
extern s32 D_8010D768;
void title_queue_clear(void) {
    s32 *ptr;
    s32 i;

    title_queue_len = 0;
    i = 5;
    ptr = &D_8010D768;
    do {
        *ptr = 0;
        i -= 1;
        ptr -= 1;
    } while (i >= 0);
}

extern s32 title_queue[];
void title_queue_push(s32 value) {
    if (title_queue_len < 6) {
        title_queue[title_queue_len] = value;
        title_queue_len += 1;
    }
}

extern s32 title_queue_len;

s32 title_queue_count(void) {
    return title_queue_len;
}

extern s32 title_queue[];
s32 title_queue_get(s32 index) {
    return title_queue[index];
}

extern s32 title_input_mask_value;

s32 title_input_mask(void) {
    return title_input_mask_value;
}
