/* title_anim: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

extern s32 title_row_label_ids[];
void title_draw_label(s32 index, s32 x, s32 y, s32 extra, s32 flags);
void title_menu_button_draw(TitleSlot *slot) {
    TitleButton *btn = slot->button;
    s32 x;
    s32 y;
    s32 centerX;
    s32 rowY;
    s32 labelW;
    s32 w8;
    s32 maxWidth;
    s32 shade;
    s32 i;

    if (btn->visible == 0) {
        return;
    }
    x = btn->x;
    y = btn->y;
    centerX = x + 4;
    title_draw_label(btn->value_3E, centerX, y + 8, 3, 0x1000);
    rowY = y + 0x1C;
    {
        s32 w4 = title_label_width(4) + 8;
        s32 labelX = centerX + (btn->width - w4) / 2;
        title_draw_label(btn->value_3E, labelX, rowY, 4, 0x1000);
    }
    w8 = title_label_width(8);
    maxWidth = title_label_width(9);
    if (w8 >= maxWidth) {
        maxWidth = w8;
    }
    labelW = maxWidth + 8;
    centerX += (btn->width - labelW) / 2;
    rowY = y + 0x30;
    for (i = 0; i < 2; i++) {
        if (btn->mode_1E == i) {
            shade = 0x1000;
            if (btn->unk_22 == 1) {
                title_cursor_draw(btn->value_3E, (u16 *)btn->unk_2C, centerX - 10, rowY + 7, 2, 0x1000);
            }
        } else {
            shade = 0x800;
        }
        title_draw_label(btn->value_3E, centerX, rowY, title_row_label_ids[i], shade);
        rowY += 0x14;
    }
}

extern u8 title_str_memcard_access[];
void title_win_update();  /* a function reached by pointer */
void title_anim_draw();  /* a function reached by pointer */
extern u8 title_anim_task[];
extern u8 title_anim_data[];
extern void *title_anim_text_ptr;
extern s16 D_80111020;
extern s16 D_80111022;
extern s16 D_8011101E;
extern s16 title_anim_x;
extern s16 title_anim_y;
extern s16 title_anim_width;
extern s16 title_anim_height;
extern void *D_80110FF0;
extern void *D_80110FF4;
extern void *D_80110FF8;
extern void *D_80110FFC;
/* Title screen setup: sets up the task table title_anim_task, then stores the
 * centred X position (half of 320 minus the span), the layout values and the
 * two sprite-table pointers. The unused[2] pads the frame to match the original. */
void title_anim_init(void) {
    s32 span;
    s32 unused[2];
    u8 *table = title_anim_task;

    span = title_str_length((s32)title_str_memcard_access) * 8 + 8;
    title_anim_text_ptr = title_str_memcard_access;
    task_reset((TitleCtl *)table);
    task_set((TitleTaskRec *)table, 0, (s32)title_win_update, (s32)title_anim_draw, (s32)title_anim_data);
    D_80111020 = 8;
    D_80111022 = 7;
    D_8011101E = 4;
    title_anim_x = ((0x140 - span) >> 1) - 3;
    title_anim_y = 0x6E;
    title_anim_height = 0x14;
    D_80110FF0 = (u8 *)title_list_colors_a;
    D_80110FF4 = (u8 *)title_list_colors_a + 4;
    D_80110FF8 = (u8 *)title_list_colors_b;
    title_anim_width = span;
    D_80110FFC = (u8 *)title_list_colors_b + 4;
}

extern TitleBlock *title_block_ptr;
extern u8 title_anim_task[];
/* Stores the value in the title block's unk_06, then calls task_start with table title_anim_task. */
void title_block_start(s16 value) {
    title_block_ptr->unk_06 = value;
    task_start(0, title_anim_task, 0);
}

extern u16 title_counter;
/* Advances the title counter at title_counter by one. */
void title_counter_advance(void) {
    title_counter += 1;
}

s32 title_counter_is_two(void) {
    return (s16)title_counter == 2;
}

extern s16 D_80110FD8;
/* Same code as pad3d_gone (title). */
s32 func_800A9E00(void) {
    return D_80110FD8 == 0;
}

void title_record_set(s32 index, s32 val_20, u16 *src, s32 val_18, s32 val_1C, s32 val_10, s32 val_14, s32 val_0A);
void title_record_restart(s32 index, s16 value);
void title_record_close(s32 index, s16 value);
s32 title_record_is_active(s32 index);
s32 title_record_is_ready(s32 index);
void title_win_update(TitleCtl *ctl) {
    TitleWin *win = (TitleWin *)ctl->anim;

    switch (ctl->step) {
    case 0:
        title_record_set(win->v3A, win->v3C, (u16 *)&win->x, win->v0C, win->v10, win->v14, win->v18, 0);
        title_record_restart(win->v3A, 4);
        *(s16 *)win->pad1C = 0;
        ctl->step++;
        break;
    case 1:
        if (title_record_is_active(win->v3A) == 1) {
            *(s16 *)win->pad1C = 1;
            ctl->step++;
        }
        break;
    case 2:
        break;
    case 3:
        title_record_close(win->v3A, 6);
        *(s16 *)win->pad1C = 0;
        ctl->step++;
        break;
    case 4:
        if (title_record_is_ready(win->v3A) == 1) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

void title_anim_draw(TitleCtl *ctl) {
    struct TitleAnimSprite *anim = (struct TitleAnimSprite *)ctl->anim;
    s32 x;
    s32 y;

    if (anim->active != 0) {
        x = anim->x + 4;
        y = anim->y + 4;
        title_text_ot_depth_set(anim->ot_depth);
        title_draw_text(x, y, anim->text, 1, 0x1000);
        title_text_ot_depth_set(-1);
    }
}

void title_anim_slot_update(TitleCtl *ctl);
void title_slot_draw(TitleSlotDrawObj *obj);
extern s32 title_slot_task;
extern u8 title_slot_data[];
extern s16 title_slot_box_x;
extern s16 title_slot_box_y;
extern s16 title_slot_box_w;
extern s16 title_slot_box_h;
extern s32 *title_slot_ptr0;
extern s32 *title_slot_ptr0_next;
extern s32 *title_slot_ptr1;
extern s32 *title_slot_ptr1_next;
extern s16 title_slot_mode;
extern s16 D_80111086;
extern s16 D_80111088;
extern s16 D_8011108A;
/* Sets up the task at title_slot_task and its box, centred on the 320-pixel screen; height 22, or 20 when func_800A1BB4 is set. */
void title_slot_task_init(void) {
    s32 width;

    title_slot_mode = 2;
    width = title_label_width(2) + 8;
    task_reset((TitleCtl *)&title_slot_task);
    task_set((TitleTaskRec *)&title_slot_task, 0, (s32)title_anim_slot_update, (s32)title_slot_draw, (s32)title_slot_data);
    D_80111088 = 8;
    D_8011108A = 7;
    D_80111086 = 4;
    title_slot_ptr0 = title_list_colors_a;
    title_slot_ptr0_next = title_list_colors_a + 1;
    title_slot_ptr1 = title_list_colors_b;
    title_slot_ptr1_next = title_list_colors_b + 1;
    if (func_800A1BB4() == 0) {
        title_slot_box_x = (0x140 - width) / 2 - 3;
        title_slot_box_y = 0x6E;
        title_slot_box_w = width;
        title_slot_box_h = 0x16;
    } else {
        title_slot_box_x = (0x140 - width) / 2 - 3;
        title_slot_box_y = 0x6E;
        title_slot_box_w = width;
        title_slot_box_h = 0x14;
    }
}

extern TitleCardState *title_card_state_ptr;
/* Returns the halfword at +0x36 of the record at title_card_state_ptr. */
s16 no_card_result(void) {
    return title_card_state_ptr->unk_36;
}

extern TitleCardState *title_card_state_ptr;
extern s32 title_slot_task;
/* Clears the field at +0x1C and sets the field at +0x36 to -2 on the record at title_card_state_ptr, then runs task_start on the table at title_slot_task. */
void title_record_reset(void) {
    title_card_state_ptr->unk_1C = 0;
    title_card_state_ptr->unk_36 = -2;
    task_start(0, &title_slot_task, 0);
}
extern u16 logo_step;
void logo_advance(void) {
    logo_step += 1;
}

/* Same code as logo_shown (title). */
s32 logo_is_shown(void) {
    return *(s16 *)&logo_step == 2;
}

extern s16 D_80111040;
/* Same code as pad3d_gone (title). */
s32 func_800AA178(void) {
    return D_80111040 == 0;
}

/* Runs the title animation state machine: steps ctl->unk_22 through five states, driving the anim slot. */
void title_anim_slot_update(TitleCtl *ctl) {
    TitleAnimSlot *anim = (TitleAnimSlot *)ctl->anim;

    switch (ctl->step) {
    case 0:
        title_record_set(anim->record_index, anim->unk_3C, anim->src, anim->unk_0C, anim->unk_10, anim->unk_14, anim->unk_18, 0);
        title_record_restart(anim->record_index, 6);
        ctl->step++;
        break;
    case 1:
        if (title_record_is_active(anim->record_index) == 1) {
            anim->active = 1;
            ctl->step++;
        }
        break;
    case 2:
        break;
    case 3:
        title_record_close(anim->record_index, 6);
        anim->active = 0;
        ctl->step++;
        break;
    case 4:
        if (title_record_is_ready(anim->record_index) == 1) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

void title_draw_label(s32 index, s32 x, s32 y, s32 extra, s32 flags);
void title_slot_draw(TitleSlotDrawObj *obj) {
    TitleSlotDrawData *data = obj->data;

    if (data->flag != 0) {
        s32 x = data->x + 4;
        s32 y = data->y + 4;

        title_draw_label(data->index, x, y, data->extra, 0x1000);
    }
}

extern s32 card_list_task;
extern s32 card_list_task_arg;
void card_list_update(TitleCardTask *task);
void title_card_list_draw();  /* a function reached by pointer */
extern s32 title_list_colors_a[2];
extern s32 title_list_colors_b[2];
extern s16 D_801110F0;
extern s16 D_801110F2;
extern s16 D_801110EE;
extern s32 D_801110C0;
extern s32 D_801110C4;
extern s32 D_801110C8;
extern s32 D_801110CC;
void card_list_init(void) {
    task_reset((TitleCtl *)&card_list_task);
    task_set((TitleTaskRec *)&card_list_task, 0, (s32)&card_list_update, (s32)&title_card_list_draw, (s32)&card_list_task_arg);
    D_801110F0 = 6;
    D_801110F2 = 5;
    D_801110EE = 5;
    D_801110C0 = (s32)title_list_colors_a;
    D_801110C4 = (s32)(title_list_colors_a + 1);
    D_801110C8 = (s32)title_list_colors_b;
    D_801110CC = (s32)(title_list_colors_b + 1);
}

extern CardListState *card_list_rec_ptr;
extern s32 card_list_task;
/* Clears the 16-bit field at +0x1C of the title record, then runs task_start on the table at card_list_task. */
void card_list_show(void) {
    card_list_rec_ptr->unk_1C = 0;
    task_start(0, &card_list_task, 0);
}

extern s16 D_801110A8;
/* Same code as pad3d_gone (title). */
s32 func_800AA3C4(void) {
    return D_801110A8 == 0;
}

u32 * title_get_pad_state();
s32 title_label_width(s32 index);
s32 func_800A1BB4(void);
void title_record_set(s32 index, s32 val_20, u16 *src, s32 val_18, s32 val_1C, s32 val_10, s32 val_14, s32 val_0A);
void title_record_restart(s32 index, s16 value);
s32 title_record_is_active(s32 index);
void card_format(s32 value);
s32 card_op_result_get(void);
void title_record_close(s32 index, s16 value);
s32 title_record_is_ready(s32 index);
void title_entries_reset(u32 slot_ids);
s32 card_result(void);
s32 card_status(void);
s32 title_input_mask(void);
s32 title_input_step(void);
s32 title_flag_test_set(void *p);

static inline void card_win_show(TitleCardWin *win, s32 mode, s32 y) {
    s32 w;

    win->mode = mode;
    w = title_label_width(mode) + 8;
    if (func_800A1BB4() == 0) {
        win->x = (0x140 - w) / 2 - 3;
        win->y = y;
        win->w = w;
        win->h = 0x16;
    } else {
        win->x = (0x140 - w) / 2 - 3;
        win->y = y;
        win->w = w;
        win->h = 0x14;
    }
    title_record_set(win->index, win->v3C, (u16 *)&win->x, win->v0C, win->v10, win->v14, win->v18, 1);
    title_record_restart(win->index, 4);
}


void card_list_update(TitleCardTask *task) {
    TitleCardWin *win = task->win;
    u32 *input = title_get_pad_state(task);
    s32 y = 0x86;
    s32 r;
    s32 mask;

    switch (task->state) {
    case 0:
        card_win_show(win, 5, y);
        win->v38 = 0;
        task->state++;
        break;
    case 1:
        if (title_record_is_active(win->index) == 1) {
            win->active = 1;
            task->state++;
        }
        break;
    case 2:
        task->state++;
        break;
    case 3:
        card_format(0x10);
        task->state++;
        break;
    case 4:
        if (card_op_result_get() == 1) {
            task->state++;
        }
        break;
    case 5:
        title_record_close(win->index, 6);
        win->active = 0;
        task->state++;
        break;
    case 6:
        r = title_record_is_ready(win->index);
        if (r == 1) {
            title_entries_reset(0x4FFFF);
            if (card_result() == r) {
                task->state = 10;
            } else {
                task->state = 20;
            }
        }
        break;
    case 10:
        card_win_show(win, 6, y);
        task->state = 30;
        break;
    case 20:
        card_win_show(win, 7, y);
        task->state = 30;
        break;
    case 30:
        if (title_record_is_active(win->index) == 1) {
            win->active = 1;
            task->state++;
        }
        break;
    case 31:
        if (card_status() != 2) {
            mask = title_input_mask();
            mask |= title_input_step();
            if ((input[1] & mask) == 0) {
                break;
            }
        }
        title_entries_reset(0x2FFFF);
        win->active = 0;
        title_record_close(win->index, 6);
        task->state++;
        break;
    case 32:
        if (title_record_is_ready(win->index) == 1) {
            title_flag_test_set(task);
        }
        break;
    }
}

/* Same code as title_slot_draw (title). */
void title_card_list_draw(TitleSlotDrawObj *obj) {
    TitleSlotDrawData *data = obj->data;

    if (data->flag != 0) {
        s32 x = data->x + 4;
        s32 y = data->y + 4;

        title_draw_label(data->index, x, y, data->extra, 0x1000);
    }
}

extern u8 card_frame_buf[];
extern u8 card_frame_magic_c;
extern u8 card_icon_frames;
extern u8 card_icon_palette[0x20];
extern CardIconImage card_icon_frame0;
extern CardIconImage card_icon_frame1;
extern CardIconImage card_icon_frame2;
s32 title_video_is_pal(void);
void mem_copy(s32 arg0, u8 *arg1, u8 *arg2);
void card_header_build(void) {
    u8 *base;
    u8 *p;
    s32 i;

    base = card_frame_buf;
    base[0] = 0x53;
    card_frame_magic_c = 0x43;
    if (title_video_is_pal() == 1) {
        card_icon_frames = 0x11;
    } else {
        card_icon_frames = 0x13;
    }
    base[3] = 1;
    i = 0x1B;
    p = base + 0x1B;
    do {
        p[0x44] = 0;
        i--;
        p--;
    } while (i >= 0);
    mem_copy(0x20, card_icon_palette, base + 0x60);
    mem_copy(0x80, card_icon_frame0.pixels, base + 0x80);
    mem_copy(0x80, card_icon_frame1.pixels, base + 0x100);
    mem_copy(0x80, card_icon_frame2.pixels, base + 0x180);
}

extern u8 *card_comment_prefix;
extern u8 *card_comment_table_a[];
extern u8 *card_comment_b_table[];
/* Appends three strings into card_frame_buf starting at byte 4: the fixed
   string at card_comment_prefix, then the entries picked by index_a and index_b.
   title_str_length gives the length of each string. */
void card_comment_build(s32 index_a, s32 index_b) {
    u8 *text;
    u8 *out;
    s32 end;
    s32 pos;

    out = card_frame_buf;
    text = card_comment_prefix;
    pos = 0;
    end = title_str_length((s32)text);
    for (; pos < end; pos++) {
        (out + pos)[4] = *text++;
    }

    text = card_comment_table_a[index_a];
    end += title_str_length((s32)text);
    for (; pos < end; pos++) {
        (out + pos)[4] = *text++;
    }

    text = card_comment_b_table[index_b];
    end += title_str_length((s32)text);
    for (; pos < end; pos++) {
        (out + pos)[4] = *text++;
    }
}

/* Same code as get_file_name (s01). */
s32 *get_card_frame_buf(void) {
    return (s32 *) &card_frame_buf;
}

extern TitleCtl title_list_task;
extern s16 D_80111356;
extern s16 D_80111358;
extern s16 D_8011135A;
extern u8 title_list_data[];
void title_list_update(TitleMenuObj *obj);  /* a function reached by pointer */
void title_button_draw(void *slot_ptr);  /* a function reached by pointer */
void title_list_init(void) {
    task_reset(&title_list_task);
    task_set((TitleTaskRec *)&title_list_task, 0, (s32)title_list_update, (s32)title_button_draw, (s32)title_list_data);
    D_80111358 = 6;
    D_8011135A = 5;
    D_80111356 = 5;
}

extern TitleBlock *D_80111308;
void title_request_start(void *req, s16 value) {
    TitleBlock *blk = D_80111308;

    blk->src = ((TitleArg *)req)->ctx;
    blk->unk_24 = value;
    blk->unk_0C = ((TitleSrc *)blk->src)->unk_28;
    blk->unk_10 = ((TitleSrc *)blk->src)->unk_2C;
    blk->unk_14 = ((TitleSrc *)blk->src)->unk_30;
    blk->unk_18 = ((TitleSrc *)blk->src)->unk_34;
    task_start((s32)req, &title_list_task, 0);
}

extern s16 title_ready_flag;

s32 title_is_ready_flag(void) {
    return title_ready_flag == 0;
}

u32 str_ghost_in_the_shell[49] RODATA = {
    0x67826682, 0x72826E82, 0x40817382, 0x6D826882, 0x73824081, 0x64826782,
    0x72824081, 0x64826782, 0x6B826B82, 0x63824081, 0x73826082, 0x40816082,
    0x8F826D82, 0x00004481, 0x40815282, 0x00000000, 0x40815182, 0x00000000,
    0x40815082, 0x00000000, 0x6C826282, 0x00006F82, 0x50826C82, 0x00005182,
    0x50826C82, 0x00005082, 0x50826C82, 0x00004F82, 0x58826C82, 0x00004081,
    0x57826C82, 0x00004081, 0x56826C82, 0x00004081, 0x55826C82, 0x00004081,
    0x54826C82, 0x00004081, 0x53826C82, 0x00004081, 0x52826C82, 0x00004081,
    0x51826C82, 0x00004081, 0x50826C82, 0x00004081, 0x64826D82, 0x00007682,
    0x00000000,
};

void title_slot_update(void *arg0) {
    TitleSlotRec *slot;
    s32 flags;

    slot = ((TitleSlotOwner *)arg0)->slot;
    flags = title_get_pad_state(arg0)[1];
    if (flags & 0x8000) {
        title_entries_reset(0x4FFFF);
        slot->unk_1E = 0;
        return;
    }
    if (flags & 0x2000) {
        slot->unk_1E = 1;
        title_entries_reset(0x4FFFF);
    }
}

void title_list_update(TitleMenuObj *obj) {
    TitleMenuData *data = obj->data;
    u32 *input = title_get_pad_state(obj);
    TitleCell *cell = data->cell;

    switch (obj->step) {
    case 0:
        {
            s32 y = cell->rect_y + cell->rect_height + 4;
            s32 x = cell->rect_x + (cell->rect_width - 0x60) / 2 - 0xB;

            data->rect[2] = 0x70;
            data->rect[3] = 0x14;
            data->rect[0] = x;
            data->rect[1] = y;
        }
        title_record_set(data->slot, data->sub_index, data->rect, data->unk_0C, data->unk_10, data->unk_14, data->unk_18, 0);
        title_record_restart(data->slot, 4);
        data->choice = 1;
        data->unk_2C = 0;
        data->unk_2E = 0;
        data->unk_30 = 0;
        data->unk_1C = 0;
        obj->step++;
        break;
    case 1:
        if (title_record_is_active(data->slot) != 1) {
            return;
        }
        data->unk_1C = 1;
        obj->step++;
        break;
    case 2:
        ok_box_animate((TitleScrollState *)&data->unk_2C);
        if (card_status() == 1) {
            title_slot_update(obj);
            if (input[1] & title_input_mask()) {
                if (data->choice == 0) {
                    title_entries_reset(0x1FFFF);
                } else {
                    title_entries_reset(0x2FFFF);
                }
                obj->ctrl->done = data->choice;
                obj->step++;
                break;
            }
            if (!(input[1] & title_input_step())) {
                return;
            }
        }
        title_entries_reset(0x2FFFF);
        obj->ctrl->done = -1;
        obj->step++;
        break;
    case 3:
        title_record_close(data->slot, 4);
        data->unk_1C = 0;
        obj->step++;
        break;
    case 4:
        if (title_record_is_ready(data->slot) == 1) {
            title_flag_test_set(obj);
        }
        return;
    }
}

void title_button_draw(void *slot_ptr) {
    TitleSlot *slot = (TitleSlot *)slot_ptr;
    TitleButton *btn;
    s32 x;
    s32 y;
    s32 width;
    s32 px;
    s32 py;

    btn = slot->button;
    if (btn->visible == 0) {
        return;
    }
    title_text_ot_depth_set(btn->value_3E);
    x = btn->x;
    y = btn->y;
    px = x + 0x14;
    py = y + 4;
    if (btn->mode_1E == 0) {
        width = 0x1000;
        title_cursor_draw(btn->value_3E, (u16 *)btn->unk_2C, x + 0xC, y + 0xA, btn->value_24, width);
    } else {
        width = 0x800;
    }
    title_draw_text(px, py, "OK", 1, width);
    px += 0x28;
    if (btn->mode_1E == 1) {
        width = 0x1000;
        title_cursor_draw(btn->value_3E, (u16 *)btn->unk_2C, px - 8, py + 6, btn->value_24, width);
    } else {
        width = 0x800;
    }
    title_draw_text(px, py, "CANCEL", 1, width);
    title_text_ot_depth_set(-1);
}

extern u8 title_card_wait_task[];
extern s32 title_card_wait_data;
extern s16 D_801113C0;
extern s16 D_801113C2;
extern s16 D_801113BE;
extern s32 title_card_wait_ptr0;
extern s32 title_card_wait_ptr0_next;
extern s32 title_card_wait_ptr1;
extern s32 title_card_wait_ptr_b;
void title_card_wait_update(TitleCtl *ctl);
void title_card_wait_draw(TitleSlotDrawObj *obj);
/* Resets the card wait task (its update is title_card_wait_update), then sets up
   the two 16-bit counters and the two pointer pairs (+0 / +4 entries of title_list_colors_a and title_list_colors_b). */
void title_card_wait_init(void) {
    task_reset((TitleCtl *)&title_card_wait_task);
    task_set((TitleTaskRec *)&title_card_wait_task, 0, (s32)&title_card_wait_update, (s32)&title_card_wait_draw, (s32)&title_card_wait_data);
    D_801113C0 = 6;
    D_801113C2 = 5;
    D_801113BE = 5;
    title_card_wait_ptr0 = (s32)title_list_colors_a;
    title_card_wait_ptr0_next = (s32)(title_list_colors_a + 1);
    title_card_wait_ptr1 = (s32)title_list_colors_b;
    title_card_wait_ptr_b = (s32)(title_list_colors_b + 1);
}

extern TitleWin *title_window_ptr;
extern u8 title_card_wait_task[];
void title_record_set(s32 index, s32 val_20, u16 *src, s32 val_18, s32 val_1C, s32 val_10, s32 val_14, s32 val_0A);
void title_window_show(s32 mode, s32 y) {
    TitleWin *win = title_window_ptr;
    s32 w;

    win->mode = mode;
    w = title_label_width((s16)mode) + 8;
    if (func_800A1BB4() == 0) {
        win->x = (0x140 - w) / 2 - 3;
        win->y = y - 1;
        win->w = w;
        win->h = 0x16;
    } else {
        if (mode == 1) {
            win->x = (0x140 - w) / 2 - 3;
            win->y = y;
            win->w = w;
            win->h = 0x34;
        } else {
            win->x = (0x140 - w) / 2 - 3;
            win->y = y;
            win->w = w;
            win->h = 0x14;
        }
    }
    title_record_set(win->v3A, win->v3C, (u16 *)&win->x, win->v0C, win->v10, win->v14, win->v18, 0);
    task_start(0, title_card_wait_task, 0);
}

extern s16 D_80111378;
/* Same code as pad3d_gone (title). */
s32 func_800AB01C(void) {
    return D_80111378 == 0;
}
