/* file_menu: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

/* Labels a data table (D_800BDE8C) points to by address; they follow this function's strings. */
const char title_label_load[] = "L O A D";
const char title_label_save[] = "S A V E";

extern s32 title_label_strings[];
extern s32 title_card_msg_ptrs[];
s32 title_str_length(s32 text_addr);
s32 title_label_width(s32 index) {
    s32 result;
    s32 value;

    if (func_800A1BB4() == 0) {
        value = title_str_length(title_label_strings[index]);
        result = (value / 2) * 0x10;
        if (index == 1) {
            result -= 0x12;
        }
    } else {
        result = title_str_length(title_card_msg_ptrs[index]) * 8;
    }
    return result;
}

void title_memcard_update(TitleLoadTask *task);
void title_load_update(TitleLoadTask *task);
void title_file_menu_draw(TitleFileMenuTask *task);
void title_record_set(s32 index, s32 val_20, u16 *src, s32 val_18, s32 val_1C, s32 val_10, s32 val_14, s32 val_0A);
extern u8 *D_800BDE8C;
extern u8 *D_800BDE90;
extern u8 D_80110B10;
extern u8 D_80110B11;
extern u8 D_80110B12;
extern u8 D_80110B14;
extern u8 D_80110B15;
extern u8 D_80110B16;
extern u8 D_80110B18;
extern u8 D_80110B19;
extern u8 D_80110B1A;
extern u8 D_80110B1C;
extern u8 D_80110B1D;
extern u8 D_80110B1E;
extern u8 title_memcard_colors[];
extern TitleFileMenu title_memcard_menu;
extern TitleFileMenu title_load_menu;
/* Sets up the two file menus the title's label choice starts (owner->block->entries). */
void title_file_menus_init(TitleFadeOwner *owner) {
    u16 rect[4];
    TitleFadeBlock *labels = owner->block;
    void *task = &title_memcard_task;
    TitleFileMenu *menu = &title_memcard_menu;
    u16 label_x;
    s16 memcard_x;
    s16 memcard_left;
    s16 load_x;
    /* in v1: a hard register sched1 moves past the store of 1, as in the original */
    register s16 load_left asm("$3");
    s32 dark;
    u8 *colors;

    task_reset(task);
    task_set(task, 0, (s32)title_memcard_update, (s32)title_file_menu_draw, (s32)menu);
    menu->width = 0xA4;
    menu->height = 0x58;
    label_x = labels->label1_x;
    menu->y = 0x44;
    memcard_x = label_x - 0x2E;
    memcard_left = label_x - 0x31;
    menu->x = memcard_x;
    /* unk_00 (cursor color set) as a scalar store: a member store
       may pass the color byte stores in sched */
    *(s16 *)menu = 0;
    rect[0] = memcard_left;
    menu->cursor = 0;
    rect[1] = 0x44;
    rect[2] = 0xA4;
    rect[3] = 0x58;
    title_memcard_colors[0] = 0xFF;
    title_memcard_colors[1] = 0x5C;
    title_memcard_colors[2] = 0;
    title_memcard_colors[4] = 0xC8;
    title_memcard_colors[5] = 0x5C;
    title_memcard_colors[6] = 0;
    title_memcard_colors[8] = 0xC8;
    dark = 0x2E;
    title_memcard_colors[9] = dark;
    title_memcard_colors[10] = 0;
    title_memcard_colors[12] = 0x64;
    title_memcard_colors[13] = 0x2E;
    title_memcard_colors[14] = 0;
    menu->colors[2] = title_memcard_colors + 8;
    menu->colors[3] = title_memcard_colors + 12;
    menu->colors[0] = title_memcard_colors;
    menu->colors[1] = title_memcard_colors + 4;
    menu->title = D_800BDE8C;
    title_record_set(3, 8, rect, (s32)menu->colors[0], (s32)menu->colors[1], (s32)menu->colors[2], (s32)menu->colors[3], 0);

    task = &title_load_task;
    menu = &title_load_menu;
    task_reset(task);
    task_set(task, 0, (s32)title_load_update, (s32)title_file_menu_draw, (s32)menu);
    menu->width = 0xA4;
    menu->height = 0x58;
    label_x = labels->vec.label0_x;
    menu->y = 0x44;
    load_x = label_x - 0x2E;
    load_left = label_x - 0x31;
    menu->x = load_x;
    *(s16 *)menu = 1;
    rect[0] = load_left;
    menu->cursor = 0;
    rect[1] = 0x44;
    rect[2] = 0xA4;
    rect[3] = 0x58;
    colors = &D_80110B10;
    D_80110B10 = 0;
    D_80110B11 = 0xB8;
    D_80110B12 = 0xFF;
    D_80110B14 = 0;
    D_80110B15 = 0x5C;
    D_80110B16 = 0xC8;
    D_80110B18 = 0;
    D_80110B19 = 0x5C;
    D_80110B1A = 0xC8;
    D_80110B1C = 0;
    D_80110B1D = 0x2E;
    D_80110B1E = 0x64;
    menu->colors[2] = colors + 8;
    menu->colors[3] = colors + 12;
    menu->colors[0] = colors;
    menu->colors[1] = colors + 4;
    menu->title = D_800BDE90;
    title_record_set(2, 8, rect, (s32)menu->colors[0], (s32)menu->colors[1], (s32)menu->colors[2], (s32)menu->colors[3], 0);
}

void title_sprite_reset(TitleAnimRatioOwner *outer) {
    TitleSpriteScale *sprite = (TitleSpriteScale *)outer->inner;

    sprite->unk_10 = 0x1000;
    sprite->unk_1C = 0x1000;
    sprite->unk_2C = 0;
    set_title_sprite_flag(0);
}

u32 * title_get_pad_state();
void title_toggle_pair(s16 *self, s16 *other);
s32 title_pair_toggle(TitlePairOwner *obj) {
    TitlePairState *pair;

    title_get_pad_state(obj);
    pair = obj->pair;
    title_toggle_pair(pair->self_pair, pair->other_pair);
    return pair->self_pair[1] != 1;
}

s32 card_op_start(void);
void title_mode_begin(s32 value);
void title_entries_reset(u32 slot_ids);
void card_exit(void);
s32 card_shutdown(void);
s32 is_title_mode_1(void);
s32 func_800A9464(void);
void logo_show(s16 a, s16 b, s16 c);
void title_panel_open(s16 value74, s16 value08, s16 value04);
void title_rec_place(s16 x, s16 y);
void title_mode_set_value(s16 value);
void title_fade_step_update(TitleFadeOwner *obj) {
    TitleFadeBlock *blk;
    TitleFadeVec *vec;
    u32 *input;
    s32 sel;

    blk = obj->block;
    vec = &blk->vec;
    input = title_get_pad_state(obj);
    switch (obj->state) {
    case 0:
        title_mode_begin(0x24);
        do {
            blk->step = 0;
            blk->ramp = 0;
            blk->fade = 0;
        } while (0);
        obj->state++;
        break;
    case 1:
        obj->state++;
    case 2:
        blk->fade = (blk->step << 12) / blk->steps;
        blk->step++;
        if (blk->steps < blk->step) {
            obj->state++;
        }
        break;
    case 3:
        if (obj->node != 0 && obj->node->kind == 1) {
            break;
        }
        if (is_title_mode_1() == 0) {
            break;
        }
        do {
            if (vec->x > 0x1000) {
                vec->x -= 0x80;
            }
            if (vec->y > 0x1000) {
                vec->y -= 0x80;
            }
        } while (0);
        if (blk->locked == 1) {
            break;
        }
        sel = title_pair_toggle((TitlePairOwner *)obj);
        if (input[1] & title_input_mask()) {
            if (get_title_sprite_flag() == 0) {
                set_title_sprite_flag(card_op_start());
            }
            if (get_title_sprite_flag() == 1) {
                blk->locked = 1;
                title_entries_reset(0x1FFFF);
                task_start((s32)obj, blk->entries[sel], 0);
                break;
            }
        }
        if (input[1] & title_input_step()) {
            if (get_title_sprite_flag() == 1) {
                card_exit();
            }
            obj->state++;
        }
        break;
    case 4:
        sel = get_title_sprite_flag();
        if (sel == 1) {
            if (card_shutdown() == sel) {
                set_title_sprite_flag(0);
            }
        }
        if (get_title_sprite_flag() == 0) {
            blk->step = blk->steps;
            title_entries_reset(0x18FFFF);
            task_start((s32)obj, obj->node, 2);
            title_panel_open(1, 0, 0x22);
            logo_show(0, 0, 0x22);
            title_rec_place(0, 0x22);
            blk->ramp = 0;
            title_mode_set_value(0xF);
            obj->state++;
        }
        break;
    case 5:
        if (blk->step >= 0) {
            blk->fade = (blk->step << 12) / blk->steps;
            blk->step--;
        }
        blk->ramp += 0x1000 / blk->speed;
        if (blk->ramp > 0x1000) {
            if (func_800A9464() == 1) {
                title_flag_test_set(obj);
            }
        }
        break;
    }
}

void title_menu_quad_draw(s32 depth, s32 x, s32 y, s32 index, s32 semi_trans, s32 bright, s32 twice);
void title_bars_draw(TitleObj *obj) {
    TitleParams *p = obj->params;
    s32 scale = p->scale;
    s32 not_full = scale != 0x1000;
    TitleBarRect *ra = &p->bar_a;
    TitleBarRect *rb = &p->bar_b;
    s32 scaled;
    s32 left_a;
    s32 top_a;
    s32 x_a;
    s32 h_a;
    s32 left_b;
    s32 top_b;
    s32 x_b;
    s32 h_b;

    if (ra->y == 1) {
        scaled = scale * 0x1448 / 0x1000;
    } else {
        scaled = scale;
    }
    left_a = ra->x2 - 3;
    top_a = ra->y2;
    x_a = ra->x;
    h_a = ra->y - 1;
    title_menu_quad_draw(12, left_a, top_a, x_a - h_a, not_full, scaled, 1);

    if (rb->y == 1) {
        scaled = scale * 0x1448 / 0x1000;
    } else {
        scaled = scale;
    }
    left_b = rb->x2 - 3;
    top_b = rb->y2;
    x_b = rb->x;
    h_b = rb->y - 1;
    title_menu_quad_draw(12, left_b, top_b, x_b - h_b, not_full, scaled, 1);

    scaled = ra->len * scale / 0x1000;
    title_menu_quad_draw(12, 0x91, ra->y2 + 4, 0x32, not_full, scaled, 1);
    scaled = rb->len * scale / 0x1000;
    title_menu_quad_draw(12, 0xA1, ra->y2 + 4, 0x33, not_full, scaled, 1);
    title_menu_quad_draw(12, 0x20, 0x20, 9, not_full, scale, 1);
}

void title_save_slot_step(TitleLoadState *s) {
    register TitleEntry *e asm("$16");

    e = (TitleEntry *)title_get_pad_state(s);
    if (e->state_16 < 0x17) {
        if (!(e->flags & 0x4000)) {
            goto check_1A;
        }
    } else {
        e->state_16 = 0xF;
    }
    title_entries_reset(0x4FFFF);
    s->slot++;
    if (s->slot >= 4) {
        s->slot = 0;
        return;
    }
check_1A:
    if (e->state_1A < 0x17) {
        if (!(e->flags & 0x1000)) {
            return;
        }
    } else {
        e->state_1A = 0xF;
    }
    title_entries_reset(0x4FFFF);
    s->slot--;
    if (s->slot < 0) {
        s->slot = 3;
    }
}

extern TitleSaveSlot title_save_slots[];
s32 title_counter_is_two(void);
extern s32 func_800A9E00(void);
extern s32 card_status(void);
extern u8 *card_file_name(s32 level);
extern s32 card_op_result_get(void);
extern s32 card_result(void);
extern void title_counter_advance(void);
extern void title_entries_reset(u32 ids);
extern s32 title_record_is_active(s32 idx);
extern void title_save_slot_step(TitleLoadState *s);
extern s32 title_record_is_ready(s32 idx);
s32 title_is_ready_flag(void);
extern void title_step_start(void *req, s16 value);
extern s32 func_800AB2A0(void);
extern s32 logo_is_shown(void);
void logo_advance(void);
extern s32 func_800AA178(void);
s32 title_is_idle(void);
extern void title_record_close(s32 index, s16 value);
extern void mem_copy(s32 arg0, u8 *arg1, u8 *arg2);
void title_menu_start(void);
void title_block_start(s16 value);
void title_record_restart(s32 index, s16 value);
void title_record_reset(void);
void title_request_start(void *req, s16 value);
void apply_sound_mode(void);
void ok_box_animate(TitleScrollState *s);
void card_read(s32 a, s32 b, s32 c, s32 d, s32 e);
void title_load_update(TitleLoadTask *task) {
    TitleLoadState *st;
    TitleLoadShared *shared;
    u32 *flags;
    TitleLoadBase *base;
    s32 status;
    s32 res;
    s32 r;
    s32 rec = 2;

    flags = title_get_pad_state(task);
    base = (TitleLoadBase *)title_shared_state_get();
    st = task->state;
    shared = task->link->shared;
    ok_box_animate((TitleScrollState *)&st->unk_20);
    switch (task->phase) {
    case 0:
        title_block_start(0x6E);
        st->unk_02 = 0;
        st->unk_04 = 0;
        st->index = 0;
        st->timer = 0;
        st->unk_20 = 0;
        st->unk_22 = 0;
        st->unk_24 = 0;
        task->phase = 1;
        break;
    case 1:
        if (title_counter_is_two() != 0) {
            status = card_status();
            switch (status) {
            case 3:
                task->phase = 0x16;
                break;
            case 1:
                task->phase = 2;
                break;
            case 2:
                st->timer++;
                if (st->timer >= 0xB5) {
                    task->phase = 0xF;
                }
                break;
            }
        }
        break;
    case 2:
        card_read((s32)card_file_name(st->index), card_work_buf, 0x400, 0, 0x10);
        task->phase = 3;
        break;
    case 3:
        if (card_op_result_get() == 1) {
            res = card_result();
            if (res == 0x400) {
                st->slot_status[st->index] = 1;
                mem_copy(0x98, (u8 *)card_work_buf + 0x200, (u8 *)&title_save_slots[st->index]);
            } else if (res == -1) {
                st->slot_status[st->index] = 0;
            } else {
                st->slot_status[st->index] = -1;
            }
            if (st->index == 2) {
                task->phase = 4;
            } else {
                st->index = st->index + 1;
                task->phase = 2;
            }
        }
        break;
    case 4:
        title_counter_advance();
        task->phase = 5;
        break;
    case 5:
        if (func_800A9E00() == 1) {
            if (st->slot_status[0] != 1 && st->slot_status[1] != 1 && st->slot_status[2] != 1) {
                st->slot = 3;
            }
            title_entries_reset(0x1FFFF);
            title_record_restart(rec, 6);
            st->unk_02 = 0;
            task->phase = 6;
        }
        break;
    case 6:
        if (title_record_is_active(rec) == 1) {
            st->unk_02 = 1;
            st->unk_04 = 1;
            task->phase = 7;
        }
        break;
    case 7:
        status = card_status();
        if (status == 1) {
            title_save_slot_step(st);
            if (st->slot == 3 && (flags[1] & title_input_mask())) {
                goto reset2;
            }
            if (flags[1] & title_input_mask()) {
                if (st->slot_status[st->slot] == status) {
                    task->phase = 10;
                    title_entries_reset(0x1FFFF);
                    break;
                }
                title_entries_reset(0x3FFFF);
                break;
            }
            if (!(flags[1] & title_input_step())) {
                break;
            }
        }
    reset2:
        title_entries_reset(0x2FFFF);
        task->phase = 8;
        break;
    case 8:
        title_record_close(rec, 8);
        st->unk_02 = 0;
        task->phase = 9;
        break;
    case 9:
        if (title_record_is_ready(rec) == 1) {
            shared->unk_2C = 0;
            title_flag_test_set(task);
        }
        break;
    case 10:
        title_request_start(task, 1);
        st->unk_04 = 0;
        task->phase = 0xB;
        break;
    case 11:
        if (title_is_ready_flag() == 1) {
            if (task->unk_24 == 0) {
                title_block_start(0xA0);
                st->timer = 0;
                task->phase = 0xC;
            } else {
                task->phase = 7;
            }
        }
        break;
    case 12:
        if (title_counter_is_two() != 0) {
            st->timer++;
            if (st->timer >= 0x31) {
                base->save = title_save_slots[st->slot];
                apply_sound_mode();
                base->unk_20 = 1;
                base->unk_D4 = 0;
                title_counter_advance();
                task->phase = 0xD;
            }
        }
        break;
    case 13:
        if (func_800A9E00() == 1) {
            title_step_start(task, 0);
            task->phase = 0xE;
        }
        break;
    case 14:
        if (func_800AB2A0() == 1) {
            st->unk_04 = 1;
            title_entries_reset(0x4FFFF);
            task->phase = 7;
        }
        break;
    case 15:
        title_counter_advance();
        task->phase = 0x10;
        break;
    case 16:
        if (func_800A9E00() == 1) {
            title_record_reset();
            title_entries_reset(0x3FFFF);
            task->phase = 0x11;
        }
        break;
    case 17:
        r = logo_is_shown();
        if (r == 1) {
            status = card_status();
            if (status == r || status == 3) {
                task->phase = 0x14;
                title_entries_reset(0x1FFFF);
            } else {
                r = title_input_step();
                r |= title_input_mask();
                if (flags[1] & r) {
                    task->phase = 0x12;
                    title_entries_reset(0x2FFFF);
                }
            }
        }
        break;
    case 18:
        logo_advance();
        task->phase = 0x13;
        break;
    case 19:
        if (func_800AA178() == 1) {
            shared->unk_2C = 0;
            title_flag_test_set(task);
        }
        break;
    case 20:
        logo_advance();
        task->phase = 0x15;
        break;
    case 21:
        if (func_800AA178() == 1) {
            task->phase = 0;
        }
        break;
    case 22:
        title_counter_advance();
        task->phase = 0x17;
        break;
    case 23:
        if (func_800A9E00() == 1) {
            title_menu_start();
            task->phase = 0x18;
        }
        break;
    case 24:
        if (title_is_idle() == 1) {
            shared->unk_2C = 0;
            title_flag_test_set(task);
        }
        break;
    }
}

s32 *get_card_frame_buf(void);
s32 func_800AB01C(void);
s32 title_input_mask(void);
s32 title_input_step(void);
void title_window_show(s32 mode, s32 y);
void card_write(s32 a, s32 b, s32 c, s32 d, s32 e);
void card_free_space(void);
void card_comment_build(s32 index_a, s32 index_b);
void title_memcard_update(TitleLoadTask *task) {
    u32 *input = title_get_pad_state(task);
    TitleLoadBase *base = (TitleLoadBase *)title_shared_state_get();
    TitleLoadState *st = task->state;
    TitleLoadShared *shared = task->link->shared;
    s32 r;
    s32 rec = 3;
    u8 *comment_buf;
    u8 *save_buf;

    ok_box_animate((TitleScrollState *)&st->unk_20);
    switch (task->phase) {
    case 0:
        title_block_start(0x6E);
        st->unk_02 = 0;
        st->unk_04 = 0;
        st->index = 0;
        st->timer = 0;
        st->unk_20 = 0;
        st->unk_22 = 0;
        st->unk_24 = 0;
        task->phase = 1;
        break;
    case 1:
        if (title_counter_is_two()) {
            switch (card_status()) {
            case 1:
                task->phase = 2;
                break;
            case 2:
                st->timer++;
                if (st->timer >= 0xB5) {
                    task->phase = 0x17;
                }
                break;
            case 3:
                task->phase = 0x1E;
                break;
            }
        }
        break;
    case 2:
        card_read((s32)card_file_name(st->index), card_work_buf, 0x400, 0, 0x10);
        task->phase = 3;
        break;
    case 3:
        if (card_op_result_get() == 1) {
            r = card_result();
            if (r == 0x400) {
                st->slot_status[st->index] = 1;
                mem_copy(0x98, (u8 *)card_work_buf + 0x200, (u8 *)&title_save_slots[st->index]);
            } else if (r == -1) {
                st->slot_status[st->index] = 0;
            } else {
                st->slot_status[st->index] = -1;
            }
            if (st->index == 2) {
                task->phase = 4;
            } else {
                st->index++;
                task->phase = 2;
            }
        }
        break;
    case 4:
        title_counter_advance();
        task->phase = 5;
        break;
    case 5:
        if (func_800A9E00() == 1) {
            title_entries_reset(0x1FFFF);
            title_record_restart(rec, 6);
            st->unk_02 = 0;
            task->phase = 6;
        }
        break;
    case 6:
        if (title_record_is_active(rec) == 1) {
            st->unk_02 = 1;
            st->unk_04 = 1;
            task->phase = 7;
        }
        break;
    case 7:
        if (card_status() == 1) {
            title_save_slot_step(st);
            if (st->slot != 3 || !(input[1] & title_input_mask())) {
                if (input[1] & title_input_mask()) {
                    title_entries_reset(0x1FFFF);
                    if (st->slot_status[st->slot]) {
                        task->phase = 0xC;
                    } else {
                        task->phase = 0xA;
                    }
                    break;
                }
                if (!(input[1] & title_input_step())) {
                    break;
                }
            }
        }
        title_entries_reset(0x2FFFF);
        task->phase = 8;
        break;
    case 8:
        title_record_close(rec, 8);
        st->unk_02 = 0;
        task->phase = 9;
        break;
    case 9:
        if (title_record_is_ready(rec) == 1) {
            shared->unk_2C = 0;
            title_flag_test_set(task);
        }
        break;
    case 10:
        card_free_space();
        task->phase = 0xB;
        break;
    case 11:
        {
            s32 done = card_op_result_get();
            if (done == 1) {
                if (card_result() == done) {
                    task->phase = 0xC;
                } else {
                    task->phase = 0x21;
                }
            }
        }
        break;
    case 12:
        title_request_start(task, 0);
        st->unk_04 = 0;
        task->phase = 0xD;
        break;
    case 13:
        {
            s32 got = title_is_ready_flag();
            if (got == 1) {
                if (task->unk_24 != 0) {
                    if (task->unk_24 <= 0 ? task->unk_24 == -1 : task->unk_24 == got) {
                        st->unk_04 = 1;
                        task->phase = 7;
                    }
                } else {
                    task->phase = 0xE;
                }
            }
        }
        break;
    case 14:
        st->unk_04 = -1;
        title_block_start(0xA0);
        task->phase = 0xF;
        break;
    case 15:
        if (title_counter_is_two()) {
            if (card_status() != 1) {
                title_counter_advance();
                task->phase = 7;
            } else {
                comment_buf = (u8 *)get_card_frame_buf();
                card_comment_build(st->slot, base->save.comment);
                mem_copy(0x200, comment_buf, (u8 *)card_work_buf);
                save_buf = (u8 *)&base->save;
                mem_copy(sizeof(TitleSaveSlot), save_buf, (u8 *)card_work_buf + 0x200);
                FAKE_USE(save_buf);
                card_write((s32)card_file_name(st->slot), card_work_buf, 0x400, 0, 0x10);
                st->timer = 0;
                task->phase = 0x10;
            }
        }
        break;
    case 16:
        if (card_op_result_get() == 1) {
            if (card_result() == 0x400) {
                task->phase = 0x11;
            } else {
                title_counter_advance();
                task->phase = 0x15;
            }
        }
        break;
    case 17:
        card_read((s32)card_file_name(st->slot), card_work_buf, 0x400, 0, 0x10);
        task->phase = 0x12;
        break;
    case 18:
        if (card_op_result_get() == 1) {
            title_counter_advance();
            if (card_result() == 0x400) {
                st->slot_status[st->slot] = 1;
                title_save_slots[st->slot] = base->save;
                FAKE_USE(base);
                task->phase = 0x13;
            } else {
                st->slot_status[st->slot] = -2;
                task->phase = 0x15;
            }
        }
        break;
    case 19:
        if (func_800A9E00() == 1) {
            title_step_start(task, 1);
            task->phase = 0x14;
        }
        break;
    case 20:
        if (func_800AB2A0() == 1) {
            st->unk_04 = 1;
            title_entries_reset(0x4FFFF);
            task->phase = 7;
        }
        break;
    case 21:
        if (func_800A9E00() == 1) {
            title_window_show(0, 0xA0);
            task->phase = 0x16;
        }
        break;
    case 23:
        title_counter_advance();
        task->phase = 0x18;
        break;
    case 24:
        if (func_800A9E00() == 1) {
            title_entries_reset(0x3FFFF);
            title_record_reset();
            task->phase = 0x19;
        }
        break;
    case 25:
        {
        s32 pend = logo_is_shown();
        if (pend == 1) {
            r = card_status();
            if (r == pend || r == 3) {
                task->phase = 0x1C;
                title_entries_reset(0x1FFFF);
            } else if (input[1] & (title_input_mask() | title_input_step())) {
                task->phase = 0x1A;
                title_entries_reset(0x2FFFF);
            }
        }
        }
        break;
    case 26:
        logo_advance();
        task->phase = 0x1B;
        break;
    case 27:
        if (func_800AA178() == 1) {
            shared->unk_2C = 0;
            title_flag_test_set(task);
        }
        break;
    case 28:
        logo_advance();
        task->phase = 0x1D;
        break;
    case 29:
        if (func_800AA178() == 1) {
            task->phase = 0;
        }
        break;
    case 30:
        title_counter_advance();
        task->phase = 0x1F;
        break;
    case 31:
        if (func_800A9E00() == 1) {
            title_menu_start();
            task->phase = 0x20;
        }
        break;
    case 32:
        if (title_is_idle() == 1) {
            shared->unk_2C = 0;
            title_flag_test_set(task);
        }
        break;
    case 33:
        title_window_show(1, 0xA0);
        st->unk_04 = 0;
        task->phase = 0x22;
        break;
    case 22:
    case 34:
        if (func_800AB01C() == 1) {
            st->unk_04 = 1;
            task->phase = 7;
        }
        break;
    }
}

extern u8 *title_slot_label_ptrs[];
extern u8 title_str_new_game[];
extern u8 title_str_complete[];
extern u8 title_str_mission[];
extern u8 title_str_no_file[];
extern u8 title_str_read_error[];
extern u8 title_str_save_error[];
extern u8 title_str_exit[];
void title_cursor_draw(s32 ot_index, u16 *angles, s32 ofx, s32 ofy, s32 color_set, s32 depth);
void title_file_menu_draw(TitleFileMenuTask *task) {
    TitleFileMenu *menu = task->menu;
    s32 i;
    s32 left;
    s32 top;
    s32 menu_y;
    s32 x;
    s32 text_x;
    s32 status;
    s32 y;
    s32 bright;
    TitleSaveSlot *slot;

    if (menu->visible == 0) {
        return;
    }
    title_text_ot_depth_set(7);
    left = menu->x;
    top = menu->y;
    x = left + 10;
    {
        register s32 indent asm("$2") = (menu->width - 0x38) / 2;
        register s32 title_x asm("$4") = left + indent;
        title_draw_text(title_x - 2, top + 5, menu->title, 1, 0x1000);
    }
    y = top + 0x17;
    for (i = 0; i < 3; i++) {
        if (menu->cursor == i) {
            bright = 0x1000;
            if (menu->state == -1) {
                bright = 0xFFF;
            }
        } else {
            bright = 0x800;
        }
        title_draw_text(x + 8, y, title_slot_label_ptrs[i], 1, bright);
        text_x = x + 0x44;
        slot = &title_save_slots[i];
        status = menu->slot_status[i];
        switch (status) {
        case 1:
            switch (slot->comment) {
            case 0:
                title_draw_text(text_x, y, title_str_new_game, 1, bright);
                break;
            case 13:
                title_draw_text(text_x, y, title_str_complete, 1, bright);
                break;
            default:
                title_text_draw_tail(text_x, y, title_str_mission, slot->comment, 1, bright);
                break;
            }
            break;
        case 0:
            title_draw_text(text_x, y, title_str_no_file, 1, bright);
            break;
        case -1:
            title_draw_text(text_x, y, title_str_read_error, 1, bright);
            break;
        case -2:
            title_draw_text(text_x, y, title_str_save_error, 1, bright);
            break;
        }
        y += 0x10;
    }
    bright = 0x800;
    if (menu->cursor == 3) {
        bright = 0x1000;
    }
    title_draw_text(x + 8, y, title_str_exit, 1, bright);
    if (menu->state == 1) {
        menu_y = menu->y;
        y = menu->cursor * 16 + menu_y;
        title_cursor_draw(7, (u16 *)menu->cursor_buf, menu->x + 10, y + 0x1B, menu->unk_00, 0x1000);
    }
    title_text_ot_depth_set(-1);
}
