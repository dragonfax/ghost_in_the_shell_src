/* card_wait: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

s32 card_status(void);
s32 title_input_mask(void);
s32 title_input_step(void);
void title_card_wait_update(TitleCtl *ctl) {
    struct TitleAnim *anim;
    u32 *pad;
    s32 buttons;

    anim = ctl->anim;
    pad = title_get_pad_state(ctl);
    switch (ctl->step) {
    case 0:
        title_record_restart(anim->unk_3A, 6);
        title_entries_reset(0x3FFFF);
        *(s16 *)(anim->unk_1A + 2) = 0;
        ctl->step++;
        break;
    case 1:
        if (title_record_is_active(anim->unk_3A) != 1) {
            break;
        }
        *(s16 *)(anim->unk_1A + 2) = 1;
        ctl->step++;
        break;
    case 2:
        if (card_status() == 2) {
            ctl->step++;
            break;
        }
        buttons = title_input_mask();
        buttons |= title_input_step();
        if ((pad[1] & buttons) == 0) {
            break;
        }
        title_entries_reset(0x2FFFF);
        ctl->step++;
        break;
    case 3:
        title_record_close(anim->unk_3A, 6);
        *(s16 *)(anim->unk_1A + 2) = 0;
        ctl->step++;
        break;
    case 4:
        if (title_record_is_ready(anim->unk_3A) == 1) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

/* Same code as title_slot_draw (title). */
void title_card_wait_draw(TitleSlotDrawObj *obj) {
    TitleSlotDrawData *data = obj->data;

    if (data->flag != 0) {
        s32 x = data->x + 4;
        s32 y = data->y + 4;

        title_draw_label(data->index, x, y, data->extra, 0x1000);
    }
}

extern TitleCtl title_step_task;
extern u8 title_step_data[];
void title_step_update(TitleStepObj *obj);
void title_message_draw(TitleTextTask *task);
extern s16 D_80111428;
extern s16 D_8011142A;
extern s16 D_80111426;
/* Same code as title_list_init (title). */
void title_step_init(void) {
    task_reset(&title_step_task);
    task_set((TitleTaskRec *)&title_step_task, 0, (s32)title_step_update, (s32)title_message_draw, (s32)title_step_data);
    D_80111428 = 6;
    D_8011142A = 5;
    D_80111426 = 5;
}

extern TitleBlock *title_request_block;
extern TitleCtl title_step_task;
/* Same code as title_request_start (title). */
void title_step_start(void *req, s16 value) {
    TitleBlock *blk = title_request_block;

    blk->src = ((TitleArg *)req)->ctx;
    blk->unk_24 = value;
    blk->unk_0C = ((TitleSrc *)blk->src)->unk_28;
    blk->unk_10 = ((TitleSrc *)blk->src)->unk_2C;
    blk->unk_14 = ((TitleSrc *)blk->src)->unk_30;
    blk->unk_18 = ((TitleSrc *)blk->src)->unk_34;
    task_start((s32)req, &title_step_task, 0);
}

extern s16 D_801113E0;
/* Same code as pad3d_gone (title). */
s32 func_800AB2A0(void) {
    return D_801113E0 == 0;
}

/* Runs the title animation state machine on obj: 0 places the window, 1 waits for the anim, 2 waits for input or timeout, 3 resets the entry, 4 runs the finish. */
void title_step_update(TitleStepObj *obj) {
    TitleStepAnim *anim = obj->anim;
    TitleStepRect *rect = anim->rect;
    TitleStepPad *pad;
    s32 input;
    s32 half;

    pad = (TitleStepPad *)title_get_pad_state(obj);
    switch (obj->state) {
    case 0: {
        s32 rect_y = rect->y;
        s32 rect_h = rect->h;
        s32 rect_x = rect->x;
        s32 rect_w = rect->w;

        anim->width = 0x60;
        anim->height = 0x14;
        half = (rect_w - 0x50) / 2;
        anim->x = rect_x + half - 0xB;
        anim->y = rect_y + rect_h + 4;
        title_record_set(anim->index, anim->sub_index, (u16 *)&anim->x, anim->unk_0C, anim->unk_10, anim->unk_14, anim->unk_18, 0);
        title_record_restart(anim->index, 4);
        anim->phase = 0;
        obj->state++;
        break;
    }
    case 1:
        if (title_record_is_active(anim->index) == 1) {
            anim->phase = 1;
            anim->timer = 0;
            obj->state++;
        }
        break;
    case 2:
        anim->timer = anim->timer + 1;
        input = title_input_mask();
        input |= title_input_step();
        if ((pad->pad_released & input) != 0 || (s16)anim->timer >= 0x3D) {
            anim->phase = 0;
            obj->state++;
        }
        break;
    case 3:
        title_record_close(anim->index, 6);
        anim->phase = 0;
        obj->state++;
        break;
    case 4:
        if (title_record_is_ready(anim->index) == 1) {
            title_flag_test_set(obj);
        }
        break;
    }
}

/* Draws the title's text line for the record when it is active, bracketed by the id select (func_800A5864). */
void title_message_draw(TitleTextTask *task) {
    TitleTextRec *rec = task->rec;

    if (rec->active != 0) {
        title_text_ot_depth_set(rec->id);
        title_draw_text(rec->x + 0xF, rec->y + 4, (u8 *)"Complete.", 1, 0x1000);
        title_text_ot_depth_set(-1);
    }
}

SVC_HEADER_CONSTS(message);

extern u8 title_records[];
extern TitleSideEntry title_record_sides[];
void title_track_update();  /* a function reached by pointer */
void title_box_side_draw(TitleTaskRec *task);  /* a function reached by pointer */
/* Resets the 8 title records (0x28 bytes each) and their 0x24-byte side entries. */
void title_records_init(void) {
    s32 i;
    TitleSideEntry *side = title_record_sides;
    u8 *rec = title_records;

    i = 0;
    do {
        task_reset((TitleCtl *)rec);
        task_set((TitleTaskRec *)rec, 0, (s32)title_track_update, (s32)title_box_side_draw, (s32)side);
        i++;
        rec += 0x28;
        side += 1;
    } while (i < 8);
}

/* Fills record `index` from a 4-halfword source block and eight scalar values. */
void title_record_set(s32 index, s32 val_20, u16 *src, s32 val_18, s32 val_1C, s32 val_10, s32 val_14, s32 val_0A) {
    TitleSideEntry *rec = &title_record_sides[index];

    rec->x = src[0];
    rec->y = src[1];
    rec->width = src[2];
    rec->height = src[3];
    rec->unk_20 = val_20;
    rec->unk_18 = val_18;
    rec->unk_1C = val_1C;
    rec->unk_10 = val_10;
    rec->unk_14 = val_14;
    rec->unk_0A = val_0A;
}

void title_entries_reset(u32 slot_ids);
/* Sets the title record `index` to `value`, clears its second halfword, and resets its node. */
void title_record_restart(s32 index, s16 value) {
    TitleSideBlock *block;
    u8 *rec = &title_records[index * 0x28];

    block = *(TitleSideBlock **)(rec + 0x14);
    task_start(0, rec, 0);
    title_entries_reset(0xFFFFFF);
    block->unk_0C = value;
    block->unk_0E = 0;
}

/* Sets both halfwords at +0x0C/+0x0E of the side entry for record `index` to `value`. */
void title_record_close(s32 index, s16 value) {
    TitleTaskRec *rec = (TitleTaskRec *)(title_records + index * 0x28);
    TitleCtl *ctl = (TitleCtl *)rec;
    s16 *side = (s16 *)rec->param;

    title_entries_reset(0xFFFFFF);
    side[6] = value;
    side[7] = value;
    ctl->step = 2;
}

extern s16 D_8011144E[];
/* Returns 1 when entry `index` is in state 1, else 0. */
s32 title_record_is_active(s32 index) {
    return D_8011144E[index * 20] == 1;
}

extern s16 title_record_states[];
/* Same code as title_record_is_active (title). */
s32 title_record_is_ready(s32 index) {
    return title_record_states[index * 20] == 1;
}
