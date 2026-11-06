/* title_menu: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

extern u8 title_sprite_image[];
extern u16 title_sprite_clut_data[16];
extern u16 title_sprite_clut_set_data[256];
extern u8 title_sprite_anim_data[];
extern s16 title_sprite_handles[];
extern u16 title_sprite_clut_id;
extern u16 title_sprite_clut_set_id;
extern u8 *title_sprite_data_ptr;
extern TitleSpriteAnim title_sprite_anim;
extern s32 title_sprite_task;
s32 sprite_sets_register(s32 *data, u16 *clut, u16 tpage, u16 clutDefault, s32 xoff, s32 yoff);
void title_sprite_update(TitleSpriteCtl *ctl);
void title_ctx_draw(TitleArg *arg);

/* Loads the title sprite's tpage and cluts, starts its task and sets up its two tracks. */
void title_sprite_start(void) {
    TitleSpriteAnim *anim;
    TitleSpriteTrack *track;
    s32 i;

    title_sprite_handles[0] = sprite_load_tpage(title_sprite_image, 0x200, 0x100);
    title_sprite_clut_id = clut_load(title_sprite_clut_data, 0xB0, 0xF0, 0, 0, 0x10);
    clut_load_set((s32)title_sprite_clut_set_data, 0, 0xF4, (s16 *)&title_sprite_clut_set_id, 0x300, 0xFE, &title_sprite_handles[4], 0x100);
    title_sprite_data_ptr = (u8 *)sprite_sets_register((s32 *)title_sprite_anim_data, (u16 *)title_sprite_handles, title_sprite_clut_set_id, title_sprite_clut_id, 0x300, 0xFE);
    task_reset((TitleCtl *)&title_sprite_task);
    anim = &title_sprite_anim;
    task_set((TitleTaskRec *)&title_sprite_task, 0, (s32)title_sprite_update, (s32)title_ctx_draw, (s32)anim);

    track = &anim->track_a;
    anim->vel_y = 0x20;
    anim->vel_x = 0;
    anim->vel_z = 0;
    track->key_count = 4;
    for (i = 0; i < track->key_count; i++) {
        ((s32 *)track->table_00)[i] = 0;
    }
    ((s32 *)track->table_20)[0] = 0;
    ((s32 *)track->table_20)[1] = 0x1C0;
    ((s32 *)track->table_20)[2] = 0xC0;
    ((s32 *)track->table_20)[3] = 0xC0;
    ((s32 *)track->table_40)[0] = 0x2000;
    ((s32 *)track->table_40)[1] = 0x1800;
    ((s32 *)track->table_40)[2] = 0xE00;
    ((s32 *)track->table_40)[3] = 0x1000;
    for (i = 0; i < track->key_count; i++) {
        track->key_times[i] = (i << 12) / (track->key_count - 1);
    }

    track = &anim->track_b;
    track->key_count = 4;
    for (i = 0; i < track->key_count; i++) {
        ((s32 *)track->table_00)[i] = 0;
    }
    ((s32 *)track->table_20)[0] = 0xC0;
    ((s32 *)track->table_20)[1] = 0xC0;
    ((s32 *)track->table_20)[2] = 0xC0;
    ((s32 *)track->table_20)[3] = 0xC0;
    ((s32 *)track->table_40)[0] = 0x1000;
    ((s32 *)track->table_40)[1] = 0x1400;
    ((s32 *)track->table_40)[2] = 0x1800;
    ((s32 *)track->table_40)[3] = 0x2000;
    for (i = 0; i < track->key_count; i++) {
        track->key_times[i] = (i << 12) / (track->key_count - 1);
    }
}

extern TitleState *title_state_ptr;
extern s16 title_mode;
extern s32 title_sprite_task;
/* Resets the title mode, runs task_start on the table at title_sprite_task, then sets the state block's sizes and the value at +0x124. */
void title_mode_begin(s32 value) {
    TitleState *state;

    state = title_state_ptr;
    task_start(0, &title_sprite_task, 0);
    title_mode = 0;
    state->unk_08 = 0x20;
    state->unk_0A = 0x400;
    state->unk_0C = 0x80;
    state->mode_value = value;
    state->unk_126 = 0;
}

extern s16 title_mode;

s32 is_title_mode_1(void) {
    return title_mode == 1;
}

extern TitleState *title_state_ptr;
/* Sets the title mode to 2 and stores the value and a zero in the state block. */
void title_mode_set_value(s16 value) {
    title_mode = 2;
    title_state_ptr->mode_value = value;
    title_state_ptr->unk_126 = 0;
}

extern s16 D_80110C8C;
/* Same code as pad3d_gone (title). */
s32 func_800A9464(void) {
    return D_80110C8C == 0;
}

s32 title_track_sample(s32 x, s32 n, s32 *xs, u8 *table_entry);
/* Moves the sprite by its velocity each frame. State 0 runs track_a and state 2 runs track_b
 * (fractions of the frame count, scaled by 0x1000); state 0 hands over to state 1 when the
 * frames run out, state 2 calls title_flag_test_set. State 1 only moves the sprite. */
void title_sprite_update(TitleSpriteCtl *ctl) {
    TitleSpriteAnim *anim;
    s32 progress;

    anim = ctl->anim;
    switch (ctl->state) {
    case 0:
        progress = ((s16)anim->frame << 12) / anim->frames;
        anim->unk_00 = title_track_sample(progress, anim->track_a.key_count, anim->track_a.key_times,
                                     anim->track_a.table_00) >> 12;
        anim->unk_02 = title_track_sample(progress, anim->track_a.key_count, anim->track_a.key_times,
                                     anim->track_a.table_20) >> 12;
        anim->unk_04 = title_track_sample(progress, anim->track_a.key_count, anim->track_a.key_times,
                                     anim->track_a.table_40) >> 12;
        anim->pos_x += anim->vel_x;
        anim->pos_y += anim->vel_y;
        anim->pos_z += anim->vel_z;
        anim->scale = progress;
        anim->frame++;
        if (anim->frames < (s16)anim->frame) {
            ctl->state = 1;
        }
        break;
    case 1:
        anim->pos_x += anim->vel_x;
        anim->pos_y += anim->vel_y;
        anim->pos_z += anim->vel_z;
        break;
    case 2:
        progress = ((s16)anim->frame << 12) / anim->frames;
        anim->scale = 0x1000 - progress;
        anim->unk_00 = title_track_sample(progress, anim->track_b.key_count, anim->track_b.key_times,
                                     anim->track_b.table_00) >> 12;
        anim->unk_02 = title_track_sample(progress, anim->track_b.key_count, anim->track_b.key_times,
                                     anim->track_b.table_20) >> 12;
        anim->unk_04 = title_track_sample(progress, anim->track_b.key_count, anim->track_b.key_times,
                                     anim->track_b.table_40) >> 12;
        anim->pos_x += anim->vel_x;
        anim->pos_y += anim->vel_y;
        anim->pos_z += anim->vel_z;
        anim->frame++;
        if (anim->frames < (s16)anim->frame) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

void title_rec_select(s32 arg0);
void title_item_select(s32 arg0);
void title_model_draw_at(void *a0, void *a1, void *a2, s32 a3);
extern u8 *title_sprite_data_ptr;
void title_ctx_draw(TitleArg *arg) {
    TitleCtx *ctx = arg->ctx;

    title_rec_select(1);
    title_item_select(1);
    title_model_draw_at(ctx, (u8 *)ctx + 8, title_sprite_data_ptr + 0x10, ctx->unk_120);
}

extern s32 title_menu_task;
extern s32 title_menu_task_data;
void title_menu_update(void *ptr);  /* a function reached by pointer */
void title_menu_button_draw(TitleSlot *slot);  /* a function reached by pointer */
extern s16 title_menu_x;
extern s16 title_menu_y;
extern s16 title_menu_w;
extern s16 title_menu_h;
extern s32 title_menu_list_a;
extern s32 title_menu_list_a_end;
extern s32 title_menu_list_b;
extern s32 title_menu_list_b_end;
extern s16 title_menu_cursor;
extern s16 D_80110FB6;
extern s16 D_80110FB8;
extern s16 D_80110FBA;
extern s32 title_list_colors_a[2];
extern s32 title_list_colors_b[2];
void title_menu_init(void) {
    s32 width;

    task_reset((TitleCtl *)&title_menu_task);
    task_set((TitleTaskRec *)&title_menu_task, 0, (s32)&title_menu_update, (s32)&title_menu_button_draw, (s32)&title_menu_task_data);
    width = title_label_width(3) + 8;
    /* centre horizontally on the 320-pixel screen */
    title_menu_x = ((0x140 - width) / 2) - 3;
    title_menu_y = 0x50;
    title_menu_w = width;
    title_menu_h = 0x58;
    title_menu_list_a = (s32)title_list_colors_a;
    title_menu_list_a_end = (s32)title_list_colors_a + 4;
    title_menu_list_b = (s32)title_list_colors_b;
    title_menu_list_b_end = (s32)title_list_colors_b + 4;
    D_80110FB8 = 8;
    D_80110FBA = 7;
    D_80110FB6 = 4;
    title_menu_cursor = 0;
}

extern TitleMenuState *title_menu_rec;
extern s32 title_menu_task;
/* Clears the field at +0x1C and sets the field at +0x36 to -4 on the title record, then runs task_start on the table at title_menu_task. */
void title_menu_start(void) {
    title_menu_rec->unk_1C = 0;
    title_menu_rec->unk_36 = -4;
    task_start(0, &title_menu_task, 0);
}

extern s16 D_80110D04;

s32 title_is_idle(void) {
    return D_80110D04 == 0;
}

char str_data3[24] RODATA = "DATA-3\000\000DATA-2\000\000DATA-1\000";

u8 title_str_new_game[12] RODATA = "NEW GAME";

u8 title_str_complete[12] RODATA = "COMPLETE";

u8 title_str_mission[12] RODATA = "MISSION-";

u8 title_str_no_file[8] RODATA = "NO FILE";

u8 title_str_read_error[12] RODATA = "READ ERROR";

u8 title_str_save_error[12] RODATA = "SAVE ERROR";

u8 title_str_exit[8] RODATA = "EXIT";

void title_entries_reset(u32 slot_ids);
void title_entries_set_rate(s32 divisor);
void title_flags_update(s16 *self) {
    u32 flags;

    flags = title_get_pad_state(self)[1];
    if (flags & 0x4000) {
        title_entries_reset(0x4FFFF);
        self[0xF] = 1;
        return;
    }
    if (flags & 0x1000) {
        title_entries_reset(0x4FFFF);
        self[0xF] = 0;
    }
}

s32 title_record_is_active(s32 index);
void title_record_set(s32 index, s32 val_20, u16 *src, s32 val_18, s32 val_1C, s32 val_10, s32 val_14, s32 val_0A);
void title_record_restart(s32 index, s16 value);
void card_list_show(void);
s32 card_status(void);
s32 func_800AA3C4(void);
void title_record_close(s32 index, s16 value);
s32 title_record_is_ready(s32 index);
void title_menu_update(void *ptr) {
    TitleMenuObj *obj = ptr;
    TitleMenuData *data = obj->data;
    u32 *input;

    input = title_get_pad_state(obj);
    ok_box_animate((TitleScrollState *)&data->unk_2C);

    switch (obj->step) {
    case 0:
        data->choice = 1;
        title_record_set(data->slot, data->sub_index, data->rect, data->unk_0C, data->unk_10, data->unk_0C, data->unk_10, 0);
        title_record_restart(data->slot, 6);
        title_entries_reset(0x3FFFF);
        data->unk_1C = 0;
        data->unk_22 = 0;
        data->unk_2C = 0;
        data->unk_2E = 0;
        data->unk_30 = 0;
        obj->step++;
        break;
    case 1:
        if (title_record_is_active(data->slot) != 1) {
            break;
        }
        data->unk_1C = 1;
        data->unk_22 = 1;
        obj->step++;
        break;
    case 2:
        if (card_status() == 2) {
            title_entries_reset(0x2FFFF);
            goto finish;
        }
        title_flags_update((s16 *)data);
        if (data->choice == 0) {
            if (input[1] & title_input_mask()) {
                title_entries_reset(0x1FFFF);
                obj->step++;
                break;
            }
        }
        if (data->choice == 1) {
            if (input[1] & title_input_mask()) {
                title_entries_reset(0x2FFFF);
                goto finish;
            }
        }
        if (input[1] & title_input_step()) {
            title_entries_reset(0x2FFFF);
            goto finish;
        }
        break;
    case 3:
        data->unk_22 = 0;
        card_list_show();
        obj->step++;
        break;
    case 4:
        if (func_800AA3C4() != 1) {
            break;
        }
    finish:
        title_record_close(data->slot, 10);
        obj->step = 10;
        data->unk_1C = 0;
        break;
    case 10:
        if (title_record_is_ready(data->slot) == 1) {
            title_flag_test_set(obj);
        }
        break;
    }
}
