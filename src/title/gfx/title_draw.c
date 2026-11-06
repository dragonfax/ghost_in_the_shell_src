/* title_draw: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

void title_track_update(TitleCtl *ctl) {
    TitleAnimTrack *track;

    track = (TitleAnimTrack *)ctl->anim;
    switch (ctl->step) {
    case 0:
        track->unk_08 = ((s16)track->unk_0E << 12) / (s16)track->unk_0C;
        track->unk_0E++;
        if ((s16)track->unk_0C < (s16)track->unk_0E) {
            ctl->step++;
        }
        break;
    case 1:
        break;
    case 2:
        track->unk_08 = ((s16)track->unk_0E << 12) / (s16)track->unk_0C;
        track->unk_0E--;
        if ((s16)track->unk_0E < 0) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

void title_line_add(s32 ot_index, s32 x0, s32 y0, s32 x1, s32 y1, s32 colour) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *entry;
    u8 *pkt;

    scratch_top[3] = 3;
    *(s16 *)(scratch_top + 8) = x0;
    *(s16 *)(scratch_top + 0xA) = y0;
    *(s16 *)(scratch_top + 0xC) = x1;
    *(s32 *)(scratch_top + 4) = colour;
    scratch_top[7] = 0x40;
    *(s16 *)(scratch_top + 0xE) = y1;
    entry = (u8 *)(ot_index * 4) + (u32)ctx->ot_base;
    pkt = scratch_top;
    addPrim(entry, pkt);
    scratch_top += 0x10;
}

void title_box_edge_add(s32 ot_index, s32 x0, s32 y0, s32 x1, s32 y1, s32 rgb, s32 size) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *entry;
    u8 *prim;

    ((TitlePrim *)scratch_top)->len = 4;
    ((TitlePrim *)scratch_top)->x0 = x0;
    ((TitlePrim *)scratch_top)->y0 = y0;
    ((TitlePrim *)scratch_top)->x1 = x1;
    ((TitlePrim *)scratch_top)->rgb = rgb;
    ((TitlePrim *)scratch_top)->size = size;
    ((u8 *)&((TitlePrim *)scratch_top)->rgb)[3] = 0x50;
    ((TitlePrim *)scratch_top)->y1 = y1;
    entry = (u8 *)(ot_index * 4) + (u32)ctx->ot_base;
    prim = scratch_top;
    addPrim(entry, prim);
    scratch_top += 0x14;
}

void title_box_side_draw(TitleTaskRec *task) {
    TitleBoxSide *side = (TitleBoxSide *)task->param;
    s32 h = (s16)side->h;
    s32 prod = side->ratio * h;
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 ot = side->ot_index;
    s32 center = side->y + h / 2;
    s32 left;
    s32 len;
    s32 top;
    s32 bottom;
    s32 right;
    s32 c0;
    s32 c1;
    s32 not_flat;
    s32 mode_cmd;
    TitleDrawCtx *ctx2;
    u8 *entry1;
    u8 *entry2;
    u8 *entry3;
    u8 *entry4;
    u8 *pkt1;
    u8 *pkt2;
    u8 *pkt3;
    u8 *pkt4;
    len = prod / 0x1000;
    left = side->x;
    right = left + side->w;
    top = center - len / 2;
    bottom = top + len;

    if (side->edge_colour_a != 0) {
        c0 = *side->edge_colour_a;
        if (side->edge_colour_b != 0) {
            c1 = *side->edge_colour_b;
            title_box_edge_add(ot, left, top, right, top, c0, c0);
            title_box_edge_add(ot, right, top, right, bottom, c0, c1);
            title_box_edge_add(ot, right, bottom, left, bottom, c1, c1);
            title_box_edge_add(ot, left, bottom, left, top, c1, c0);
        } else {
            title_line_add(ot, left, top, right, top, c0);
            title_line_add(ot, right, top, right, bottom, c0);
            title_line_add(ot, right, bottom, left, bottom, c0);
            title_line_add(ot, left, bottom, left, top, c0);
        }
    }

    not_flat = side->mode != 2;
    c0 = *side->fill_colour;
    if (side->edge_colour_c != 0) {
        c1 = *side->edge_colour_c;
        scratch_top[3] = 8;
        *(s32 *)(scratch_top + 4) = c0;
        *(s32 *)(scratch_top + 0xC) = c0;
        scratch_top[7] = 0x38;
        *(s32 *)(scratch_top + 0x14) = c1;
        *(s32 *)(scratch_top + 0x1C) = c1;
        if (not_flat) {
            scratch_top[7] |= 2;
        } else {
            scratch_top[7] &= ~2;
        }
        *(s16 *)(scratch_top + 8) = left + 1;
        *(s16 *)(scratch_top + 0xA) = top + 1;
        *(s16 *)(scratch_top + 0x10) = right + 1;
        *(s16 *)(scratch_top + 0x12) = top + 1;
        *(s16 *)(scratch_top + 0x18) = left + 1;
        *(s16 *)(scratch_top + 0x1A) = bottom + 1;
        *(s16 *)(scratch_top + 0x20) = right + 1;
        *(s16 *)(scratch_top + 0x22) = bottom + 1;
        entry1 = (u8 *)(ot * 4) + (u32)ctx->ot_base;
        pkt1 = scratch_top;
        addPrim(entry1, pkt1);
        scratch_top += 0x24;
    } else {
        scratch_top[3] = 3;
        *(s32 *)(scratch_top + 4) = c0;
        scratch_top[7] = 0x60;
        if (not_flat) {
            scratch_top[7] |= 2;
        } else {
            scratch_top[7] &= ~2;
        }
        *(s16 *)(scratch_top + 8) = left + 1;
        *(s16 *)(scratch_top + 0xA) = top + 1;
        *(s16 *)(scratch_top + 0xC) = right - left;
        *(s16 *)(scratch_top + 0xE) = bottom - top;
        entry2 = (u8 *)(ot * 4) + (u32)ctx->ot_base;
        pkt2 = scratch_top;
        addPrim(entry2, pkt2);
        scratch_top += 0x10;
    }

    if (side->mode == 1) {
        scratch_top[3] = 3;
        scratch_top[7] = 0x60;
        *(s16 *)(scratch_top + 8) = left + 1;
        *(s16 *)(scratch_top + 0xA) = top + 1;
        *(s16 *)(scratch_top + 0xC) = right - left;
        scratch_top[4] = 0;
        scratch_top[5] = 0;
        scratch_top[6] = 0;
        *(s16 *)(scratch_top + 0xE) = bottom - top;
        scratch_top[7] |= 2;
        entry3 = (u8 *)(ot * 4) + (u32)ctx->ot_base;
        pkt3 = scratch_top;
        addPrim(entry3, pkt3);
        scratch_top += 0x10;
    }

    mode_cmd = 0xE1000600;
    ctx2 = title_draw_ctx_ptr;
    scratch_top[3] = 1;
    *(s32 *)(scratch_top + 4) = mode_cmd;
    entry4 = (u8 *)(ot * 4) + (u32)ctx2->ot_base;
    pkt4 = scratch_top;
    addPrim(entry4, pkt4);
    scratch_top += 8;
}

void title_phase_update(void *self);
void title_spans_init(void);
void title_sliders_init(void);
extern u8 title_obj_task[];
extern s16 title_obj_ready;
extern s16 D_80111844;
extern u8 title_sprites_ctl[];
void title_sprites_init(TitleCtl *ctl);
extern void title_obj_draw(TitleObj *obj);
void title_obj_init(TitleCtl *ctl) {
    task_reset(ctl);
    task_set((TitleTaskRec *)ctl, 0, (s32)title_phase_update, (s32)title_obj_draw, (s32)title_obj_task);
    title_obj_ready = 1;
    D_80111844 = 0x40;
    title_spans_init();
    title_sprites_init((TitleCtl *)title_sprites_ctl);
    title_sliders_init();
}

extern void title_table_set_req(s32 which, s32 a1, s32 a2);
extern void title_transition_start(s32 kind, s32 effect_a, s32 effect_b);
extern void title_rec_store_value(s32 slot, s32 index);
extern void title_base_set(s32 arg0);
extern s32 title_base_get(void);
void title_phase_update(void *self) {
    TitlePhaseObj *obj = self;
    u32 *pad;
    TitlePhaseState *state;
    s32 input;

    pad = title_get_pad_state(obj);
    state = obj->anim;
    switch (obj->phase) {
    case 0:
        state->value_36 = 0;
        state->frames = 0;
        obj->phase++;
        break;
    case 1:
        state->frames++;
        if (state->frames < 0x22) {
            break;
        }
        state->limit = 0x22;
        state->counter = 0;
        title_table_request(0, 0, 0x1E, 0x44, 1);
        title_table_request(1, 0, 0x1E, 0x92, -1);
        obj->phase++;
        break;
    case 2:
        state->value_36 = (state->counter << 12) / state->limit;
        state->counter++;
        if (state->limit < state->counter) {
            state->counter = 0;
            obj->phase++;
        }
        break;
    case 3:
        if (obj->task != NULL && obj->task->active == 1) {
            break;
        }
        input = title_input_mask();
        if (!(*pad & input)) {
            input = title_input_step();
            if (!(*pad & input)) {
                break;
            }
        }
        task_start((s32)obj, obj->task, 0);
        title_table_set_req(0, 0x12, -1);
        title_table_set_req(1, 0x12, 1);
        title_transition_start(2, 0, 3);
        state->pos = 0;
        state->counter = 0x1E;
        obj->phase++;
        break;
    case 4:
        if (state->counter > 0) {
            state->counter--;
            state->value_36 = ((state->counter << 16) >> 4) / state->limit;
        }
        title_rec_store_value(state->pos, 0);
        state->pos += 0x1000 / state->step_div;
        if (state->pos < 0x1001) {
            break;
        }
        title_base_set(title_base_get() - 0x400000);
        title_flag_test_set(obj);
        break;
    }
}

void title_menu_quad_draw(s32 depth, s32 x, s32 y, s32 index, s32 semi_trans, s32 bright, s32 twice);
void title_obj_draw(TitleObj *obj) {
    TitleParams *p = obj->params;

    title_menu_quad_draw(12, 10, 24, p->unk_AE, p->unk_36 != 0x1000, p->unk_36, 1);
}

extern struct TitleTable title_table_0;
extern struct TitleTable title_table_1;
extern s16 title_table_0_mode;
extern s16 title_table_1_mode;
void title_span_update(TitleTable *table);
void table_draw(TitleTable *table);
extern TitleNameEntry title_name_rows_entry;
extern TitleNameEntry title_name_scores_entry;
/* Sets up the two title spans: a span of `count` evenly spaced fractions (i << 12) / (count - 1) */
void title_spans_init(void) {
    TitleSlider *table;
    TitleSlider *span;
    struct TitleTable *ctl;
    s32 i;

    ctl = &title_table_0;
    table = title_name_rows_entry.bars;
    title_table_0_mode = 0;
    task_reset((struct TitleCtl *)ctl);
    task_set((struct TitleTaskRec *)ctl, 0, (s32)&title_span_update, (s32)&table_draw, (s32)table);
    span = table;
    i = 0;
    table->count = 2;
    span->x = 0;
    table->y = 0x140;
    do {
        span->steps[i] = (i << 12) / (span->count - 1);
        i++;
    } while (i < span->count);
    span = table + 1;
    i = 0;
    table[1].count = 4;
    table[1].x = 0x140;
    table[1].y = 0xA0;
    table[1].pad_08[0] = 0;
    table[1].pad_08[1] = 0;
    for (; i < span->count; i++) {
        span->steps[i] = (i << 12) / (span->count - 1);
    }

    ctl = &title_table_1;
    table = title_name_scores_entry.bars;
    title_table_1_mode = 1;
    task_reset((struct TitleCtl *)ctl);
    task_set((struct TitleTaskRec *)ctl, 0, (s32)&title_span_update, (s32)&table_draw, (s32)table);
    span = table;
    i = 0;
    table->count = 2;
    span->x = 0;
    table->y = 0x140;
    do {
        span->steps[i] = (i << 12) / (span->count - 1);
        i++;
    } while (i < span->count);
    span = table + 1;
    i = 0;
    table[1].count = 4;
    table[1].x = 0x140;
    table[1].y = 0xA0;
    table[1].pad_08[0] = 0;
    table[1].pad_08[1] = 0;
    for (; i < span->count; i++) {
        span->steps[i] = (i << 12) / (span->count - 1);
    }
}

extern TitleTable title_table_1;
extern TitleTable title_table_0;
/* Fills the request block of one of the two title tables (table 0 is title_table_0, otherwise title_table_1), then runs task_start on it. */
void title_table_request(s32 which, s32 x, s32 y, s32 w, s32 value) {
    TitleTable *table;
    TitleTableReq *req;

    table = &title_table_1;
    if (which == 0) {
        table = &title_table_0;
    }
    req = table->req;
    req->unk_54 = -1;
    req->start_delay = x;
    req->unk_4C = y;
    req->timer = 0;
    req->y = w;
    req->unk_56 = 0x1000;
    req->unk_58 = value;
    task_start(0, table, 0);
    table->state = 0;
}

/* Sets y and value in one title table's request block (as title_table_request does) and puts the table in state 2. */
void title_table_set_req(s32 which, s32 y, s32 value) {
    TitleTable *table;
    TitleTableReq *req;

    table = &title_table_1;
    if (which == 0) {
        table = &title_table_0;
    }
    req = table->req;
    req->unk_4C = y;
    req->timer = 0;
    req->unk_58 = value;
    table->state = 2;
}

void title_span_update(TitleTable *table) {
    TitleTableReq *req = table->req;
    s32 state = table->state;
    s32 ret;

    if (state == 0) {
        goto state_0;
    }
    if (state <= 0) {
        return;
    }
    if (state == 1) {
        goto state_1;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    req->timer++;
    if (req->timer < req->start_delay) {
        return;
    }
    req->timer = 0;
    table->state = 1;

state_1:
    ret = title_track_sample(req->timer, req->unk_44, req->unk_34, req->unk_24);
    req->x_offset = req->unk_58 * (ret >> 12) + 0xC;
    req->timer += 0x1000 / req->unk_4C;
    if (req->timer < 0x1001) {
        return;
    }
    table->state = -1;
    return;

state_2:
    ret = title_track_sample(req->timer, req->unk_20, req->unk_10, (u8 *)req);
    req->x_offset = req->unk_58 * (ret >> 12) + 0xC;
    req->timer += 0x1000 / req->unk_4C;
    if (req->timer < 0x1001) {
        return;
    }
    title_flag_test_set(table);
}

static inline void title_add_prim(u8 *ot, u8 *pkt) {
    addPrim(ot, pkt);
}
/* Draws a gouraud line strip (LINE_G2 packets at $gp) through count points; closed == 1 also joins the last point to the first. */
void title_polyline_add(s32 count, s32 closed, s32 *xys, s32 *colors) {
    TitleDrawCtx *ctx;
    s32 i;
    s32 *firstXy;
    s32 *firstColor;
    s32 last;

    i = 0;
    firstXy = xys;
    ctx = title_draw_ctx_ptr;
    last = count - 1;
    firstColor = colors;
    for (; i < last; i++) {
        *(s32 *)(scratch_top + 8) = *xys++;
        *(s32 *)(scratch_top + 0x10) = *xys;
        *(s32 *)(scratch_top + 4) = *colors++;
        *(s32 *)(scratch_top + 0xC) = *colors;
        scratch_top[3] = 4;
        scratch_top[7] = 0x50;
        title_add_prim(ctx->ot_base + 0x10, scratch_top);
        scratch_top += 0x14;
    }
    if (closed == 1) {
        *(s32 *)(scratch_top + 8) = *xys;
        *(s32 *)(scratch_top + 0x10) = *firstXy;
        *(s32 *)(scratch_top + 4) = *colors;
        *(s32 *)(scratch_top + 0xC) = *firstColor;
        scratch_top[3] = 4;
        scratch_top[7] = 0x50;
        title_add_prim(ctx->ot_base + 0x10, scratch_top);
        scratch_top += 0x14;
    }
}

extern s32 D_800BDF14[];
extern s32 D_800BDF24[];
extern s32 D_800BDF34[];
extern s32 D_800BDF48[];

/* One frame: a closed box (the title bar, width wide, 12 high) and an open rule under it
 * down to y + 0x46 and across to x + 0x124. */
static inline void title_frame_lines(s16 *pts, s32 x, s32 y, s32 width, s32 *box_colors, s32 *rule_colors) {
    s32 right = x + width;
    pts[0] = x;
    pts[1] = y;
    pts[2] = right;
    pts[3] = y;
    pts[4] = right;
    pts[5] = y + 0xC;
    pts[6] = x;
    pts[7] = y + 0xC;
    title_polyline_add(4, 1, (s32 *)pts, box_colors);
    pts[0] = x + 6;
    pts[1] = y + 0xD;
    pts[2] = x + 6;
    pts[3] = y + 0x46;
    pts[4] = x + 0x124;
    pts[5] = y + 0x46;
    pts[6] = x + 0x124;
    pts[7] = y + 8;
    pts[8] = right + 1;
    pts[9] = y + 8;
    title_polyline_add(5, 0, (s32 *)pts, rule_colors);
}

/* Draws a menu panel frame twice (shadow, then 4,3 lower right), then a semi-transparent
 * dark TILE behind its body and a DR_TPAGE resetting the blend mode. */
void title_menu_frame_draw(s32 x, s32 y, s32 wide) {
    TitleDrawCtx *ctx;
    s16 pts[16];
    s32 width;

    ctx = title_draw_ctx_ptr;
    width = 0x91;
    if (wide == 0) {
        width = 0x87;
    }
    title_frame_lines(pts, x, y, width, D_800BDF14, D_800BDF34);
    x += 4;
    y += 3;
    title_frame_lines(pts, x, y, width, D_800BDF24, D_800BDF48);

    /* Without this, cse stores x through an s16 copy (move v0,s3) instead of sh s3. */
    __asm__("" : "=r"(x) : "0"(x));
    /* TILE, semi-transparent */
    scratch_top[3] = 3;
    scratch_top[7] = 0x60;
    scratch_top[4] = 4;
    scratch_top[5] = 0x10;
    scratch_top[6] = 8;
    *(s16 *)(scratch_top + 0xA) = y + 6;
    *(s16 *)(scratch_top + 0xC) = 0x126;
    *(s16 *)(scratch_top + 0x8) = x;
    *(s16 *)(scratch_top + 0xE) = 0x3E;
    scratch_top[7] |= 2;
    title_add_prim(ctx->ot_base + 0x14, scratch_top);
    scratch_top += 0x10;

    /* DR_TPAGE */
    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = 0xE1000600;
    title_add_prim(ctx->ot_base + 0x14, scratch_top);
    scratch_top += 8;
}

void title_draw_glow(s32 x, s32 y, s32 level) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 r;
    s32 g;
    s32 b;
    u8 *quad_ot;
    u8 *quad_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    scratch_top[3] = 8;
    scratch_top[7] = 0x38;
    r = level * 0x70 / 4096;
    g = level * 0x7C / 4096;
    b = level * 0x5C / 4096;
    scratch_top[4] = r;
    scratch_top[5] = g;
    scratch_top[6] = b;
    scratch_top[0xC] = r;
    scratch_top[0xD] = g;
    scratch_top[0xE] = b;
    r = level / 256;
    g = level * 0x3C / 4096;
    b = level / 1024;
    scratch_top[0x15] = g;
    scratch_top[0x1D] = g;
    scratch_top[0x16] = b;
    scratch_top[0x1E] = b;
    scratch_top[0x14] = r;
    scratch_top[0x1C] = r;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x10) = x + 0x119;
    *(s16 *)(scratch_top + 0x12) = y;
    *(s16 *)(scratch_top + 0x18) = x;
    *(s16 *)(scratch_top + 0x1A) = y + 8;
    *(s16 *)(scratch_top + 0x20) = x + 0x119;
    *(s16 *)(scratch_top + 0x22) = y + 8;
    scratch_top[7] |= 2;
    quad_ot = (u8 *)0xC + (u32)ctx->ot_base;
    quad_pkt = scratch_top;
    addPrim(quad_ot, quad_pkt);
    scratch_top += 0x24;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = 0xE1000620;
    mode_ot = (u8 *)0xC + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

void title_menu_frame_draw(s32 x, s32 y, s32 arg2);
void title_draw_digits(s32 x, s32 y, s32 digits, u32 value, s32 size, s32 shade);
extern u8 *title_menu_labels[];

void title_draw_menu_list(s32 x, s32 y, s32 selected, s32 glow) {
    Pad3dSoundInfo *info;
    s32 *first;
    u8 *text;
    u8 **label;
    s32 row;
    s32 bright;

    info = title_shared_state_get();
    first = &info->menu_rows[0].unk_0;
    title_draw_menu_cell(x, y, 0, 0x1000);
    title_draw_menu_cell(x + 0x4E, y, 2, 0x1000);
    title_menu_frame_draw(x - 3, y - 3, 0);
    y += 0xD;
    title_draw_menu_cell(x + 8, y, 3, 0x1000);
    title_draw_menu_cell(x + 0x44, y, 4, 0x1000);
    title_draw_menu_cell(x + 0x90, y, 6, 0x1000);
    title_draw_menu_cell(x + 0xE8, y, 5, 0x1000);
    y += 9;
    row = 0;
    text = info->menu_rows[0].name;
    label = title_menu_labels;
    do {
        if (row == selected) {
            bright = glow;
            title_draw_glow(x + 8, y, bright);
        } else {
            bright = 0x1000;
        }
        title_draw_text(x + 0x14, y, *label, 0, bright);
        label += 1;
        row++;
        title_draw_digits(x + 0x47, y, 7, *first, 0, bright);
        first += 3;
        title_draw_digits(x + 0xA6, y, 4, ((Pad3dSoundRow *)(text - (u32)&((Pad3dSoundRow *)0)->name))->unk_4, 0, bright);
        title_draw_text(x + 0xF6, y, text, 0, bright);
        y += 9;
        text += sizeof(Pad3dSoundRow);
    } while (row < 5);
}

extern u8 *title_score_labels[];
void title_draw_digits(s32 x, s32 y, s32 digits, u32 value, s32 size, s32 shade);
void title_score_list_draw(s32 x, s32 y, s32 selected, s32 glow) {
    Pad3dSoundInfo *info;
    TitleScoreRow *row;
    s32 i;
    s32 bright;
    s32 tx;

    info = title_shared_state_get();
    row = info->score_rows;
    title_draw_menu_cell(x, y, 1, 0x1000);
    title_draw_menu_cell(x + 0x58, y, 2, 0x1000);
    title_menu_frame_draw(x - 3, y - 3, 1);
    y += 0xD;
    title_draw_menu_cell(x + 8, y, 3, 0x1000);
    title_draw_menu_cell(x + 0x44, y, 4, 0x1000);
    title_draw_menu_cell(x + 0xE8, y, 5, 0x1000);
    title_draw_menu_cell(x + 0x97, y, 7, 0x1000);
    y += 9;
    i = 0;
    do {
        if (i == selected) {
            bright = 0x1000;
            title_draw_glow(x + 8, y, glow);
            tx = x + 0x14;
        } else {
            bright = 0x1000;
            tx = x + 0x14;
        }
        title_draw_text(tx, y, title_score_labels[i], 0, bright);
        i++;
        title_draw_digits(x + 0x47, y, 7, row->score, 0, bright);
        title_draw_menu_bar(x + 0xA9, y, row->unk_4, bright);
        title_draw_text(x + 0xF6, y, row->name, 0, bright);
        y += 9;
        row++;
    } while (i < 5);
}

void title_draw_menu_list(s32 a0, s32 a1, s32 a2, s32 a3);
void table_draw(TitleTable *table) {
    TitleTableReq *req = table->req;
    s16 mode;

    if (table->state != 0) {
        mode = *(s16 *)&req->pad_52;
        switch (mode) {
        case 0:
            title_draw_menu_list(*(s16 *)&req->pad_00[0x48], req->y, req->unk_54, req->unk_56);
            break;
        case 1:
            title_score_list_draw(*(s16 *)&req->pad_00[0x48], req->y, req->unk_54, req->unk_56);
            break;
        }
    }
}

extern s16 title_sprite_tpage_a;
extern s16 title_sprite_clut_a;
/* Draws a 44x40 textured sprite at (x, y) with its draw-mode packets.
 * mode 0: grey sprite plus a grey semi-transparent tile over it;
 * mode 2: black sprite; mode 1: bright sprite from the texture's second cell. */
void title_sprite_draw(s32 x, s32 y, s32 depth, s32 mode) {
    s32 u, v, tex_h, tex_w;
    u8 *ot;
    s32 shade;
    s32 bottom, right;
    s32 ot_offset;
    TitleDrawCtx *ctx;

    tex_w = 0x38;
    tex_h = 0x28;
    do {
        u = 0;
    } while (0);
    v = 0;
    ot_offset = depth * 4;
    do {
        ctx = title_draw_ctx_ptr;
    } while (0);
    do {
        x -= 0x16;
    } while (0);
    ot = ctx->ot_base + ot_offset;
    do {
        y -= 0x14;
    } while (0);
    switch (mode) {
    case 0:
        shade = 0x80;
        goto draw;
    case 2:
        shade = 0;
    draw:
        {
            TitleDrawCtx *draw_ctx = title_draw_ctx_ptr;
            u8 *entry;
            u8 *packet;

            scratch_top[3] = 2;
            *(u32 *)(scratch_top + 4) = 0xE6000000;
            *(u32 *)(scratch_top + 8) = 0;
            entry = (u8 *)(depth * 4) + (u32)draw_ctx->ot_base;
            packet = scratch_top;
            addPrim(entry, packet);
            scratch_top += 0xC;
        }
        ((TitlePolyFT4 *)scratch_top)->len = 9;
        ((TitlePolyFT4 *)scratch_top)->code = 0x2C;
        ((TitlePolyFT4 *)scratch_top)->x0 = x;
        ((TitlePolyFT4 *)scratch_top)->code &= ~1;
        ((TitlePolyFT4 *)scratch_top)->r0 = shade;
        ((TitlePolyFT4 *)scratch_top)->g0 = shade;
        ((TitlePolyFT4 *)scratch_top)->b0 = shade;
        ((TitlePolyFT4 *)scratch_top)->y0 = y;
        ((TitlePolyFT4 *)scratch_top)->x1 = x + 0x2C;
        ((TitlePolyFT4 *)scratch_top)->y1 = y;
        ((TitlePolyFT4 *)scratch_top)->x2 = x;
        ((TitlePolyFT4 *)scratch_top)->u0 = u;
        ((TitlePolyFT4 *)scratch_top)->v0 = v;
        ((TitlePolyFT4 *)scratch_top)->u1 = u + tex_w;
        ((TitlePolyFT4 *)scratch_top)->v1 = v;
        ((TitlePolyFT4 *)scratch_top)->u2 = 0;
        ((TitlePolyFT4 *)scratch_top)->v2 = v + tex_h;
        ((TitlePolyFT4 *)scratch_top)->u3 = u + tex_w;
        ((TitlePolyFT4 *)scratch_top)->v3 = v + tex_h;
        ((TitlePolyFT4 *)scratch_top)->x3 = x + 0x2C;
        ((TitlePolyFT4 *)scratch_top)->code |= 2;
        ((TitlePolyFT4 *)scratch_top)->y2 = y + tex_h;
        ((TitlePolyFT4 *)scratch_top)->y3 = y + tex_h;
        ((TitlePolyFT4 *)scratch_top)->tpage = title_sprite_tpage_a;
        ((TitlePolyFT4 *)scratch_top)->clut = title_sprite_clut_a;
        {
            u8 *poly = scratch_top;

            addPrim(ot, poly);
        }
        scratch_top += 0x28;
        {
            u8 *packet;

            scratch_top[3] = 2;
            *(u32 *)(scratch_top + 4) = 0xE2000000;
            *(u32 *)(scratch_top + 8) = 0;
            packet = scratch_top;
            addPrim(ot, packet);
            scratch_top += 0xC;
        }
        {
            TitleDrawCtx *draw_ctx = title_draw_ctx_ptr;
            u8 *entry;
            u8 *packet;

            scratch_top[3] = 2;
            *(u32 *)(scratch_top + 4) = 0xE6000001;
            *(u32 *)(scratch_top + 8) = 0;
            entry = (u8 *)(depth * 4) + (u32)draw_ctx->ot_base;
            packet = scratch_top;
            addPrim(entry, packet);
            scratch_top += 0xC;
        }
        if (mode == 0) {
            ((TitleTile *)scratch_top)->len = 3;
            ((TitleTile *)scratch_top)->code = 0x60;
            ((TitleTile *)scratch_top)->w = 0x2C;
            ((TitleTile *)scratch_top)->x0 = x;
            ((TitleTile *)scratch_top)->y0 = y;
            ((TitleTile *)scratch_top)->h = tex_h;
            ((TitleTile *)scratch_top)->r0 = shade;
            ((TitleTile *)scratch_top)->g0 = shade;
            ((TitleTile *)scratch_top)->b0 = shade;
            ((TitleTile *)scratch_top)->code |= 2;
            {
                u8 *tile = scratch_top;

                addPrim(ot, tile);
            }
            scratch_top += 0x10;
            {
                TitleDrawCtx *draw_ctx = title_draw_ctx_ptr;
                u8 *entry;
                u8 *packet;

                scratch_top[3] = 1;
                *(u32 *)(scratch_top + 4) = 0xE1000640;
                entry = (u8 *)(depth * 4) + (u32)draw_ctx->ot_base;
                packet = scratch_top;
                addPrim(entry, packet);
            }
            scratch_top += 8;
        }
        break;
    case 1:
        shade = 0xE6;
        {
            TitleDrawCtx *draw_ctx = title_draw_ctx_ptr;
            u8 *entry;
            u8 *packet;

            scratch_top[3] = 2;
            *(u32 *)(scratch_top + 4) = 0xE6000000;
            *(u32 *)(scratch_top + 8) = 0;
            entry = (u8 *)(depth * 4) + (u32)draw_ctx->ot_base;
            packet = scratch_top;
            addPrim(entry, packet);
            scratch_top += 0xC;
        }
        ((TitlePolyFT4 *)scratch_top)->len = 9;
        do {
            ((TitlePolyFT4 *)scratch_top)->code = 0x2C;
            right = x + 0x2C;
            bottom = y + 0x28;
        } while (0);
        ((TitlePolyFT4 *)scratch_top)->y2 = bottom;
        ((TitlePolyFT4 *)scratch_top)->y3 = bottom;
        ((TitlePolyFT4 *)scratch_top)->x1 = right;
        ((TitlePolyFT4 *)scratch_top)->code &= ~1;
        ((TitlePolyFT4 *)scratch_top)->x3 = right;
        ((TitlePolyFT4 *)scratch_top)->r0 = shade;
        ((TitlePolyFT4 *)scratch_top)->g0 = shade;
        ((TitlePolyFT4 *)scratch_top)->b0 = shade;
        ((TitlePolyFT4 *)scratch_top)->x0 = x;
        ((TitlePolyFT4 *)scratch_top)->y0 = y;
        ((TitlePolyFT4 *)scratch_top)->y1 = y;
        ((TitlePolyFT4 *)scratch_top)->x2 = x;
        ((TitlePolyFT4 *)scratch_top)->u0 = tex_w;
        ((TitlePolyFT4 *)scratch_top)->v0 = v;
        ((TitlePolyFT4 *)scratch_top)->u1 = 0x70;
        ((TitlePolyFT4 *)scratch_top)->v1 = v;
        ((TitlePolyFT4 *)scratch_top)->u2 = 0x38;
        ((TitlePolyFT4 *)scratch_top)->v2 = 0x28;
        ((TitlePolyFT4 *)scratch_top)->u3 = 0x70;
        ((TitlePolyFT4 *)scratch_top)->v3 = 0x28;
        ((TitlePolyFT4 *)scratch_top)->code |= 2;
        ((TitlePolyFT4 *)scratch_top)->tpage = title_sprite_tpage_a & ~0x60;
        ((TitlePolyFT4 *)scratch_top)->clut = title_sprite_clut_a;
        {
            u8 *poly = scratch_top;

            addPrim(ot, poly);
        }
        scratch_top += 0x28;
        {
            u8 *packet;

            scratch_top[3] = 2;
            *(u32 *)(scratch_top + 4) = 0xE2000000;
            *(u32 *)(scratch_top + 8) = 0;
            packet = scratch_top;
            addPrim(ot, packet);
            scratch_top += 0xC;
        }
        {
            TitleDrawCtx *draw_ctx = title_draw_ctx_ptr;
            u8 *entry;
            u8 *packet;

            scratch_top[3] = 2;
            *(u32 *)(scratch_top + 4) = 0xE6000002;
            *(u32 *)(scratch_top + 8) = 0;
            entry = (u8 *)(depth * 4) + (u32)draw_ctx->ot_base;
            packet = scratch_top;
            addPrim(entry, packet);
            scratch_top += 0xC;
        }
        break;
    }
}

extern s16 title_sprite_tpage_b;
extern s16 title_sprite_clut_b;
static inline s32 fixed_mul(s32 a, s32 b) {
    return a * b / 4096;
}
/* Draws a 40x32 (times scale/4096) grey-shaded textured quad centred on (x, y), then resets the texture window. */
void title_draw_scaled_sprite(s32 x, s32 y, s32 shade, s32 scale) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 half_w = fixed_mul(scale, 20);
    s32 half_h = fixed_mul(scale, 16);
    u8 *ot;
    u8 *prim;
    u8 *ot2;
    u8 *prim2;
    s32 u_left;
    s32 v_top;
    s32 right;

    x -= half_w;
    y -= half_h;
    u_left = 0x88;
    v_top = 0xC0;
    shade /= 32;
    right = x + half_w * 2;

    ((TitlePolyFT4 *)scratch_top)->len = 9;
    ((TitlePolyFT4 *)scratch_top)->code = 0x2C;
    ((TitlePolyFT4 *)scratch_top)->u0 = u_left;
    ((TitlePolyFT4 *)scratch_top)->code &= ~1;
    ((TitlePolyFT4 *)scratch_top)->x0 = x;
    ((TitlePolyFT4 *)scratch_top)->x2 = x;
    ((TitlePolyFT4 *)scratch_top)->r0 = shade;
    ((TitlePolyFT4 *)scratch_top)->g0 = shade;
    ((TitlePolyFT4 *)scratch_top)->b0 = shade;
    ((TitlePolyFT4 *)scratch_top)->y0 = y;
    ((TitlePolyFT4 *)scratch_top)->x1 = right;
    ((TitlePolyFT4 *)scratch_top)->y1 = y;
    ((TitlePolyFT4 *)scratch_top)->v0 = v_top;
    ((TitlePolyFT4 *)scratch_top)->u1 = 0xB0;
    ((TitlePolyFT4 *)scratch_top)->v1 = v_top;
    ((TitlePolyFT4 *)scratch_top)->u2 = 0x88;
    ((TitlePolyFT4 *)scratch_top)->v2 = 0xE0;
    ((TitlePolyFT4 *)scratch_top)->u3 = 0xB0;
    ((TitlePolyFT4 *)scratch_top)->v3 = 0xE0;
    ((TitlePolyFT4 *)scratch_top)->x3 = right;
    ((TitlePolyFT4 *)scratch_top)->y2 = y + half_h * 2;
    ((TitlePolyFT4 *)scratch_top)->y3 = y + half_h * 2;
    ((TitlePolyFT4 *)scratch_top)->tpage = title_sprite_tpage_b;
    {
        register u16 clut asm("$5") = title_sprite_clut_b;
        ((TitlePolyFT4 *)scratch_top)->clut = clut;
    }
    ot = ctx->ot_base + 8;
    prim = scratch_top;
    addPrim(ot, prim);
    scratch_top += sizeof(TitlePolyFT4);

    /* texture window reset */
    ((TitleDrTwin *)scratch_top)->len = 2;
    ((TitleDrTwin *)scratch_top)->code[0] = 0xE2000000;
    ((TitleDrTwin *)scratch_top)->code[1] = 0;
    ot2 = ctx->ot_base + 8;
    prim2 = scratch_top;
    addPrim(ot2, prim2);
    scratch_top += sizeof(TitleDrTwin);
}

extern s32 title_sprite_image_b;
extern u16 title_clut_image[16];
extern s32 title_sprite_src[561];
extern u16 title_clut_src[16];
void title_name_entry_init(TitleMenuNode *task);  /* a function reached by pointer */
void title_name_entry_update(void *node);  /* a function reached by pointer */
void title_name_entry_draw(NameEntryCtx *ctx);  /* a function reached by pointer */
extern s32 title_name_entry_state;
extern s16 title_sprite_tpage_b;
extern s16 title_sprite_clut_b;
extern s16 title_sprite_tpage_a;
extern s16 title_sprite_clut_a;
extern s32 card_work_buf;
extern s32 title_cell_list;
extern s16 D_80111902;
extern s16 title_pos_x;
extern s16 D_8011197C;
extern s16 title_pos_y;
s32 title_cell_list_build(s32 buf);
s32 sprite_sets_register(s32 *data, u16 *clut, u16 tpage, u16 clutDefault, s32 xoff, s32 yoff);
void title_sprites_init(TitleCtl *ctl) {
    s32 prev;

    title_sprite_tpage_b = sprite_load_tpage(&title_sprite_image_b, 0x240, 0x100);
    title_sprite_clut_b = 0x3C3E;
    clut_load(title_clut_image, 0, 0xFA, 0, 0, 0x10);
    clut_load(title_clut_image, 0x10, 0xFA, 1, 1, 0x10);
    title_sprite_tpage_a = sprite_load_tpage(title_sprite_src, 0x280, 0x100);
    title_sprite_clut_a = clut_load(title_clut_src, 0xF0, 0xF0, 1, 1, 0x10);
    prev = card_work_buf;
    card_work_buf = title_cell_list_build(prev);
    title_cell_list = sprite_sets_register((s32 *)prev, NULL, 0, 0, 0, 0);
    task_reset(ctl);
    task_set((TitleTaskRec *)ctl, (s32)&title_name_entry_init, (s32)&title_name_entry_update, (s32)&title_name_entry_draw,
                  (s32)&title_name_entry_state);
    D_80111902 = 2;
    title_pos_x = 0xA0;
    D_8011197C = 0;
    title_pos_y = 0x68;
}

/* Builds a 0x18-byte primitive in the scratchpad at scratch_top and links it into the
 * title OT at slot 0x1FC. index picks the sprite's x position (16 px steps from 0x300). */
void title_sprite_add(s32 index) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *prim = scratch_top;
    u8 *ot;
    s32 pos_x;
    u32 flag;

    prim[3] = 5;
    prim[7] = 1;
    /* empty loop: scheduling barrier, keeps the flag and x setup after the byte stores */
    do {
    } while (0);
    flag = 0x80000000;
    pos_x = index << 4;
    pos_x += 0x300;
    *(u32 *)(prim + 8) = flag;
    *(s16 *)(prim + 0xE) = 0xFA;
    *(s16 *)(prim + 0x10) = 0x3E0;
    *(s16 *)(prim + 0x12) = 0xF0;
    *(s16 *)(prim + 0x14) = 0x10;
    *(s16 *)(prim + 0xC) = pos_x;
    *(s16 *)(prim + 0x16) = 1;
    ot = ctx->ot_base + 0x1FC;
    addPrim(ot, prim);
    scratch_top = prim + 0x18;
}

extern s32 title_name_slot;
extern u8 title_name_chars[];
void title_table_start(void);
extern TitleNameEntry title_name_rows_entry;
extern TitleNameEntry title_name_scores_entry;
/* Name-entry screen init (task_set): picks the record row being named
   (sound-test rows or score rows), clears the 4-char name, sets the wheel up. */
void title_name_entry_init(TitleMenuNode *task) {
    Pad3dSoundInfo *info;
    TitleMenuRec *r;
    TitleMenuRec2 *menu;
    s32 row;
    TitleNameSave *save;
    s32 i;

    info = title_shared_state_get();
    save = (TitleNameSave *)&info->unk_24;
    r = task->menu;
    title_base_set(0x400000);
    title_rec_store_value(0, 0);
    menu = (TitleMenuRec2 *)r;
    row = info->unk_0C - 1;
    if (info->unk_08 == 0) {
        r->entry = &title_name_rows_entry;
        r->buf = save->rows[row].name;
        menu->unk_BC = 0;
    } else {
        r->entry = &title_name_scores_entry;
        r->buf = save->scores[row].name;
        menu->unk_BC = 1;
    }
    title_table_request(menu->unk_BC, 0, 1, 0x20, 0);
    menu->entry->unk_54 = row;
    for (i = 0; i < 4; i++) {
        title_name_chars[i] = 0xFF;
        menu->buf[i] = 0;
    }
    title_name_chars[0] = 0;
    title_name_slot = 0;
    title_table_start();
    title_sprite_add(0);
    menu->unk_BE = 1;
    menu->angle_a_speed = 0x80;
    menu->angle_b_speed = 0x400;
    menu->show_countdown = 0;
    menu->angle_a = 0;
    menu->angle_b = 0;
    menu->seconds_left = 0x1E;
    if (title_video_is_pal() == 1) {
        menu->frames_per_second = 0x32;
    } else {
        menu->frames_per_second = 0x3C;
    }
    menu->frame_countdown = menu->frames_per_second;
    r->period = 0x27;
    r->selected_index = 0;
    r->unk_16 = 0;
    r->unk_18 = 0;
    r->unk_34 = 0;
    r->speed = 0;
    r->unk_30 = 0x40;
    r->unk_36 = 0x1000;
    r->unk_38 = 0x1C;
    r->step_speed = 0x1000 / (r->period * 5);
    r->target_angle = r->angle = ((s16)r->selected_index << 12) / r->period;
}

extern s32 D_80167D50;

void func_800AD56C(s32 arg0) {
    D_80167D50 = arg0;
}

char D_800A0688[20] = "5th\0004th\0003rd\0002nd\0001st";

/* Maps a glyph index to its ASCII code: 0-25 -> 'A'-'Z', 26 -> '.',
 * 27-36 -> '0'-'9'. Any other index gives 0. */
s32 title_glyph_to_ascii(u32 glyph) {
    switch (glyph) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
        return glyph + 0x41;
    case 26:
        return 0x2E;
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
        return glyph + 0x15;
    default:
        return 0;
    }
}

extern TitleNameEntry title_slider_bars;
extern s32 title_name_slot;
extern u8 title_name_chars[];
extern u8 title_scene_task[];
s32 title_menu_scroll(TitleMenuRec *r, s32 repeat, s32 limit, s32 sound);
s32 title_angle_to_index(s32 angle, s32 count);
extern void title_transition_start(s32 a, s32 b, s32 c);
extern void title_table_set_req(s32 a, s32 b, s32 c);
void title_table_req_commit(s16 value_4E, s16 value_50);
void title_sprite_add(s32 index);
void title_fx_update(TitleMenuNode *task, TitleFxState *fx);
void title_name_entry_update(void *node) {
    TitleMenuNode *task = node;
    TitleMenuInfo *info = (TitleMenuInfo *)title_shared_state_get();
    TitleMenuRec *r = task->menu;
    TitleMenuRec2 *q = (TitleMenuRec2 *)r;
    u32 *input = ((u32 *(*)())title_get_pad_state)();
    TitleNameEntry *d = &title_slider_bars;
    s32 hit;
    s32 angle;
    s32 limit;

    if (task->mode == 1 && ((TitleMenuRec2 *)r)->seconds_left > 0) {
        s32 t = --q->frame_countdown;
        if ((s16)t < 0) {
            q->frame_countdown = q->frames_per_second;
            if (q->seconds_left > 0) {
                q->seconds_left--;
            }
        }
    }
    switch (task->phase) {
    case 0:
        q->angle_a += q->angle_a_speed;
        q->angle_b += q->angle_b_speed;
        if (task->mode == 1) {
            q->show_countdown = 1;
            task->phase = 1;
        }
        break;
    case 1:
        q->angle_a += q->angle_a_speed;
        q->angle_b += q->angle_b_speed;
        if (title_name_slot >= 3) {
            hit = title_menu_scroll(r, 0x14, 0x25, 1);
        } else {
            hit = title_menu_scroll(r, 0x14, 0, 1);
        }
        angle = title_angle_to_index(r->angle, 0x27);
        title_name_chars[title_name_slot] = angle;
        q->buf[title_name_slot] = title_glyph_to_ascii(angle);
        if (q->seconds_left <= 0) {
            if (title_name_slot < 3) {
                title_name_chars[title_name_slot] = 0xFF;
                q->buf[title_name_slot] = 0;
            }
            goto finish;
        }
        if (hit == -1) {
            break;
        }
        if (input[1] & title_input_mask()) {
            title_entries_reset(0x1FFFF);
            if (hit == 0x25) {
                goto cancel;
            }
            if (hit == 0x26) {
finish:
                r->count = 0;
                q->angle_a = 0;
                q->angle_b = 0;
                q->unk_BE = 0;
                d->unk_54 = 1;
                task->phase = 3;
                break;
            }
            if (title_name_slot < 3) {
                q->buf[title_name_slot] = title_glyph_to_ascii(hit);
                title_name_slot++;
                if (title_name_slot >= 3) {
                    r->speed = angle < 0x13 ? -0x30 : 0x30;
                    r->angle &= 0xFFF;
                    task->phase = 2;
                }
            }
        } else if (input[1] & title_input_step()) {
cancel:
            title_entries_reset(0x2FFFF);
            if (title_name_slot > 0) {
                q->buf[title_name_slot] = 0;
                title_name_slot--;
            }
        }
        break;
    case 2:
        if (r->speed >= 0) {
            limit = ((r->period - 1) << 12) / r->period;
            r->angle += r->speed;
            if ((s16)r->angle < limit) {
                break;
            }
            r->angle = limit;
            r->target_angle = limit;
            r->speed = 0;
            r->selected_index = r->period - 1;
        } else {
            limit = -0x1000 / r->period;
            r->angle += r->speed;
            if (limit < (s16)r->angle) {
                break;
            }
            limit = ((r->period - 1) << 12) / r->period;
            r->speed = 0;
            r->selected_index = r->period - 1;
            r->angle = limit;
            r->target_angle = limit;
        }
        if (q->seconds_left > 0) {
            task->phase = 1;
            break;
        }
        goto finish;
    case 3:
        d->unk_56 += 0x20;
        r->count++;
        if ((s16)r->count < 0x2E) {
            break;
        }
        if (!q->unk_BC) {
            title_table_set_req(0, 0x13, -1);
        } else {
            title_table_set_req(1, 0x13, -1);
        }
        title_table_req_commit(0, 0x13);
        q->show_countdown = 0;
        d->unk_54 = 0;
        r->count = 0;
        task->phase = 4;
        break;
    case 4:
        r->count++;
        if ((s16)r->count > 0) {
            task_start((s32)task, title_scene_task, 0);
            title_transition_start(2, 0, 3);
            r->count = 0;
            title_sprite_add(1);
            task->phase = 5;
        }
        break;
    case 5:
        title_fx_update(task, (TitleFxState *)r);
        break;
    case 6:
        info->unk_0C = 0;
        title_flag_test_set(task);
        break;
    }
}

/* Signed 12-bit difference of two coordinates: each operand is folded into
   (-0x800..0x800] and the result is folded the same way. */
s32 angle_diff(s32 arg0, s32 arg1) {
    s32 a = arg0 & 0xFFF;
    s32 b;
    s32 diff;

    if (a > 0x800) {
        a -= 0x1000;
    }
    b = arg1 & 0xFFF;
    if (b > 0x800) {
        b -= 0x1000;
    }
    diff = (a - b) & 0xFFF;
    if (diff > 0x800) {
        diff -= 0x1000;
    }
    return diff;
}

/* Index of the direction (out of `count` evenly spaced) nearest to `angle`. */
s32 title_angle_to_index(s32 angle, s32 count) {
    s32 step;
    s32 below;
    s32 above;
    s32 dist_below;
    s32 dir_above;
    s32 dist_above;

    step = 0x1000 / count;
    angle &= 0xFFF;
    below = angle / step;
    dist_below = (below << 12) / count;
    above = (below + 1) % count;
    dir_above = (above << 12) / count;

    dist_below = angle_diff(angle, dist_below) >= 0 ? angle_diff(angle, dist_below)
                                                 : -angle_diff(angle, dist_below);
    do { /* loop note: register priority of dir_above */
        dist_above = angle_diff(angle, dir_above) >= 0 ? angle_diff(angle, dir_above)
                                                     : -angle_diff(angle, dir_above);
        if (dist_below < dist_above) {
            return below;
        }
    } while (0);
    return above;
}

void title_model_draw(s16 *pos, s16 *rot, s32 model_index, s32 fade);
/* Draws obj->ring_count items spaced evenly around an ellipse that widens as
 * ring_spread falls from 0x1000. */
void title_name_entry_ring_draw(NameEntryState *obj) {
    s16 pos[4];
    s16 rot[4];
    s32 spread;
    s32 count;
    s32 radius_x;
    register s32 radius_y asm("$17");
    s32 i;
    s32 rest3;
    s32 scaled;
    s32 ofx;
    s32 ofy;

    spread = obj->ring_spread;
    count = obj->ring_count;
    rest3 = (0x1000 - spread) * 3;
    radius_x = 0x10A;
    /* Updating the product in place keeps cse from reusing the sum below. */
    scaled = rest3 + spread;
    scaled *= radius_x;
    radius_x = scaled / 4096;
    radius_y = 0x190;
    radius_y = (rest3 + spread) * radius_y / 4096;
    title_seq_enable_set(0);
    gte_set_ctrl(H, 0x100);
    ofx = obj->ring_ofx;
    ofy = obj->ring_ofy;
    gte_set_ctrl(OFX, ofx << 16);
    gte_set_ctrl(OFY, ofy << 16);
    title_rec_select(obj->ring_rec);
    title_item_select(1);
    for (i = 0; i < count; i++) {
        s32 step;
        s32 angle;
        s32 x;
        s16 height;
        s32 y;

        step = (i << 12) / count - 0x800;
        angle = obj->ring_angle - step;
        x = radius_x * rcossin_tbl[angle & 0xFFF][0] / 4096;
        height = 0x28;
        y = radius_y * rcossin_tbl[angle & 0xFFF][1] / 4096 + 0x100;
        pos[2] = radius_y + y;
        rot[1] = angle + 0x800;
        pos[0] = x;
        pos[1] = height;
        rot[0] = 0;
        rot[2] = 0;
        if (spread == 0x1000) {
            title_seq_flag_set(0);
            title_model_draw(pos, rot, title_cell_list + i, spread);
            title_seq_flag_set(1);
        } else {
            title_model_draw(pos, rot, title_cell_list + i, spread);
        }
    }
    gte_set_ctrl(H, 0x100);
    gte_set_ctrl(OFX, 0xA00000);
    gte_set_ctrl(OFY, 0x780000);
    title_seq_enable_set(1);
}

extern s16 D_80111700;
void title_sprite_draw(s32 x, s32 y, s32 depth, s32 mode);
void title_name_entry_ring_draw(NameEntryState *obj);
void title_draw_digits(s32 x, s32 y, s32 digits, u32 value, s32 size, s32 shade);
void title_name_entry_draw(NameEntryCtx *ctx) {
    NameEntryState *obj = ctx->obj;
    NameEntryView *sub = obj->sub;

    if (obj->mode == 1) {
        title_sprite_draw(0xA0, 0x8E, 0x40, 0);
        title_sprite_draw(0xA0, 0x8E, 0x2, 1);
    }
    title_name_entry_ring_draw(obj);
    sub->unk_56 = (*(s16 *)(D_801085E6 + ((obj->unk_C0 & 0xFFF) << 2)) + 0x1FFF) / 2;
    D_80111700 = (*(s16 *)(D_801085E6 + ((obj->unk_C4 & 0xFFF) << 2)) + 0x1FFF) / 2;
    /* Keeps the unk_CE load after the D_80111700 store; without it GCC hoists the load above. */
    __asm__ __volatile__("" ::: "memory");
    if (obj->unk_CE == 1) {
        title_draw_digits(0x104, 0xC2, 2, obj->unk_C8, obj->unk_CE, 0x1000);
    }
}

void title_obj_update(TitleObj *obj);
extern u8 title_table_task[];
void title_table_draw(TitleTable *table);
static inline void slider_init_steps(TitleSlider *bar) {
    s32 i;

    for (i = 0; i < bar->count; i++) {
        bar->steps[i] = (i << 12) / (bar->count - 1);
    }
}
/* Starts the title task on title_table_task and sets up the two sliders of title_slider_bars. */
void title_sliders_init(void) {
    TitleSlider *bars = title_slider_bars.bars;
    TitleSlider *bar;

    task_reset((void *)title_table_task);
    task_set((void *)title_table_task, 0, (s32)title_obj_update, (s32)title_table_draw, (s32)bars);
    bar = &bars[0];
    title_slider_bars.bars[0].count = 2;
    title_slider_bars.unk_54 = 0;
    title_slider_bars.unk_56 = 0;
    bar->x = 0xA0;
    title_slider_bars.bars[0].y = 0x1E0;
    slider_init_steps(bar);
    bar = &bars[1];
    bar->count = 2;
    bar->x = 0xA0;
    bar->y = -0xA0;
    slider_init_steps(bar);
}

extern Rec801116A0 *title_table_req_ptr;
extern u8 title_table_task[];
/* Sets three s16 fields of the record at title_table_req_ptr, then calls task_start with table title_table_task. */
void title_table_start(void) {
    title_table_req_ptr->unk_4C = 0x1000;
    title_table_req_ptr->unk_48 = 0xA0;
    title_table_req_ptr->unk_4A = 0xBC;
    task_start(0, title_table_task, 0);
}

extern u16 title_table_set_count;
/* Sets the record's 0x4E/0x50 fields, clears 0x52, bumps the title_table_set_count counter. */
void title_table_req_commit(s16 value_4E, s16 value_50) {
    title_table_req_ptr->unk_4E = value_4E;
    title_table_req_ptr->unk_52 = 0;
    title_table_req_ptr->unk_50 = value_50;
    do {
    } while (0);
    title_table_set_count++;
}

void title_obj_update(TitleObj *obj) {
    TitleParams *params;
    TitleAnimEntry *entry;
    s32 r;
    s16 step;

    params = obj->params;
    if (obj->state != 0) {
        if (obj->state == 1) {
            entry = (TitleAnimEntry *)((u8 *)params + params->anim_index * 0x24);
            r = title_track_sample(params->anim_progress, entry->unk_20, entry->unk_10, (u8 *)entry);
            step = 0x1000 / params->anim_period;
            params->anim_level = r >> 12;
            params->anim_progress += step;
            if ((s16)params->anim_progress > 0x1000) {
                title_flag_test_set(obj);
            }
        }
    }
}

void title_model_draw(s16 *pos, s16 *rot, s32 model_index, s32 fade);
void title_table_item_draw(s32 off_x, s32 off_y, s32 angle, s32 scale, TitleTableReq *req) {
    s16 a[4];
    s16 b[4];
    void *item;
    s32 idx;
    s32 x;
    s32 y;

    title_seq_enable_set(0);
    gte_set_ctrl(H, 0x100);
    gte_set_ctrl(OFX, off_x << 16);
    gte_set_ctrl(OFY, off_y << 16);
    title_rec_select(1);
    if (req->unk_54 == 1) {
        item = title_item_get(2);
        idx = req->unk_56 & 0xFFF;
        x = rcossin_tbl[idx][0] * 2 - 1;
        y = rcossin_tbl[idx][1] * 2 - 1;
        vec3s16_set_quarter(item, 0, x, y, 0x800);
        vec3s16_set_quarter(item, 1, -x, -y, 0x800);
        scale = 0x400;
        title_item_select(2);
    } else {
        title_item_select(1);
    }
    a[0] = 0;
    a[1] = 0;
    a[2] = 0x100;
    b[0] = 0;
    b[1] = 0;
    b[2] = 0;
    title_seq_flag_set(0);
    title_model_draw(a, b, title_cell_list + angle, scale);
    title_seq_flag_set(1);
    gte_set_ctrl(H, 0x100);
    gte_set_ctrl(OFX, 0xA00000);
    gte_set_ctrl(OFY, 0x780000);
    title_seq_enable_set(1);
}

extern s16 title_cell_x_offsets[];
void title_table_item_draw(s32 off_x, s32 off_y, s32 angle, s32 scale, TitleTableReq *req);
void title_draw_scaled_sprite(s32 x, s32 y, s32 shade, s32 scale);
/* Task draw step for the title table: for each of the three cells, calls the
   two helpers with the request's offsets. The request pointer is pinned to
   s5 (a plain local lands in s4 and the registers swap). */
void title_table_draw(TitleTable *table) {
    s32 slot = title_name_slot;
    s32 i;
    s32 x;
    s32 y;
    s32 scale;
    register TitleTableReq *req asm("$21") = table->req;

    slot = MAX(MIN(slot, 2), 0);

    for (i = 0; i < 3; i++) {
        u8 angle;

        x = req->x_offset + title_cell_x_offsets[i];
        y = req->y;
        angle = title_name_chars[i];
        if (slot >= i && angle < 0x25) {
            if (i == title_name_slot || title_name_slot == 3) {
                scale = req->unk_4C;
            } else {
                scale = 0x1000;
            }
            if (i != title_name_slot || i == 3) {
                title_sprite_draw(x, y, 0x40, 2);
                title_sprite_draw(x, y, 2, 1);
            }
            title_table_item_draw(x, y, angle, scale, req);
        }
        if (i == title_name_slot || title_name_slot == 3) {
            scale = req->unk_4C;
        } else {
            scale = 0x1000;
        }
        title_draw_scaled_sprite(x, y + 0x21, scale, 0x1000);
    }
}

void pad3d_anim_update(TitleTaskNode *task);
void title_menu_draw(TitleMenuDrawObj *obj);
extern u8 pad3d_anim_src[], pad3d_sprite_src[];
extern u16 pad3d_clut_src[16], pad3d_clut_set_src[256];
extern Pad3dState pad3d_anim_state;
extern s16 D_80111D5A;
extern s16 pad3d_tpage_ids[];
extern u16 pad3d_clut_id, D_80111D9C;
extern u8 *title_menu_gfx_ptr;
extern u8 pad3d_task[];
/* Loads the 3D pad's sprite and CLUTs, starts its task and fills its four
   animation tracks (keys and evenly spaced times). */
void pad3d_init(void) {
    Pad3dState *st = &pad3d_anim_state;
    Pad3dTrack *track;
    s32 i;

    pad3d_tpage_ids[0] = sprite_load_tpage(pad3d_sprite_src, 0x1C0, 0x100);
    pad3d_clut_id = clut_load(pad3d_clut_src, 0xC0, 0xF0, 1, 1, 0x10);
    clut_load_set((s32)pad3d_clut_set_src, 0, 0xF3, (s16 *)&D_80111D9C, 0x300, 0xFF, &pad3d_tpage_ids[4], 0x100);
    title_menu_gfx_ptr = (u8 *)sprite_sets_register((s32 *)pad3d_anim_src, (u16 *)pad3d_tpage_ids, D_80111D9C, pad3d_clut_id, 0x300, 0xFF);
    task_reset((TitleCtl *)pad3d_task);
    task_set((TitleTaskRec *)pad3d_task, 0, (s32)pad3d_anim_update, (s32)title_menu_draw, (s32)st);

    track = &st->tracks[0];
    i = 0;
    D_80111D5A = -1;
    track->count = 4;
    ((s32 *)track->keys[0])[0] = -0x200;
    ((s32 *)track->keys[0])[1] = -0x200;
    ((s32 *)track->keys[0])[2] = -0x200;
    ((s32 *)track->keys[0])[3] = -0x200;
    ((s32 *)track->keys[1])[0] = 0x40;
    ((s32 *)track->keys[1])[1] = 0x40;
    ((s32 *)track->keys[1])[2] = 0x40;
    ((s32 *)track->keys[1])[3] = 0x40;
    ((s32 *)track->keys[2])[0] = 0x2000;
    ((s32 *)track->keys[2])[1] = 0x1800;
    ((s32 *)track->keys[2])[2] = 0x1000;
    ((s32 *)track->keys[2])[3] = 0x900;
    ((s32 *)track->keys[3])[0] = 0x118;
    ((s32 *)track->keys[3])[1] = 0x118;
    ((s32 *)track->keys[3])[2] = 0x118;
    ((s32 *)track->keys[3])[3] = 0x118;
    ((s32 *)track->keys[4])[0] = 0;
    ((s32 *)track->keys[4])[1] = 0x40;
    ((s32 *)track->keys[4])[2] = 0x80;
    ((s32 *)track->keys[4])[3] = 0x100;
    ((s32 *)track->keys[5])[0] = -0x1000;
    ((s32 *)track->keys[5])[1] = -0x800;
    ((s32 *)track->keys[5])[2] = -0x400;
    ((s32 *)track->keys[5])[3] = 0;
    do {
        track->times[i] = (i << 12) / (track->count - 1);
        i++;
    } while (i < track->count);

    track = &st->tracks[1];
    track->count = 4;
    ((s32 *)track->keys[0])[0] = -0x200;
    ((s32 *)track->keys[0])[1] = -0x200;
    ((s32 *)track->keys[0])[2] = -0x200;
    ((s32 *)track->keys[0])[3] = -0x200;
    ((s32 *)track->keys[1])[0] = 0x40;
    ((s32 *)track->keys[1])[1] = 0x40;
    ((s32 *)track->keys[1])[2] = 0x40;
    ((s32 *)track->keys[1])[3] = 0x40;
    ((s32 *)track->keys[2])[0] = 0x900;
    ((s32 *)track->keys[2])[1] = 0x1000;
    ((s32 *)track->keys[2])[2] = 0x1800;
    ((s32 *)track->keys[2])[3] = 0x2000;
    ((s32 *)track->keys[3])[0] = 0x118;
    ((s32 *)track->keys[3])[1] = 0x118;
    ((s32 *)track->keys[3])[2] = 0x118;
    ((s32 *)track->keys[3])[3] = 0x118;
    ((s32 *)track->keys[4])[0] = 0x100;
    ((s32 *)track->keys[4])[1] = 0x80;
    ((s32 *)track->keys[4])[2] = 0x40;
    ((s32 *)track->keys[4])[3] = 0;
    ((s32 *)track->keys[5])[0] = 0;
    ((s32 *)track->keys[5])[1] = -0x400;
    ((s32 *)track->keys[5])[2] = -0x800;
    ((s32 *)track->keys[5])[3] = -0x1000;
    for (i = 0; i < track->count; i++) {
        track->times[i] = (i << 12) / (track->count - 1);
    }

    track = &st->tracks[2];
    track->count = 4;
    ((s32 *)track->keys[4])[0] = 0x100;
    ((s32 *)track->keys[4])[1] = 0x700;
    ((s32 *)track->keys[4])[2] = 0xD00;
    ((s32 *)track->keys[4])[3] = 0x1100;
    ((s32 *)track->keys[4])[4] = 0x1100;
    for (i = 0; i < track->count; i++) {
        track->times[i] = (i << 12) / (track->count - 1);
    }

    track = &st->tracks[3];
    track->count = 4;
    ((s32 *)track->keys[4])[0] = 0x1100;
    ((s32 *)track->keys[4])[1] = 0xB00;
    ((s32 *)track->keys[4])[2] = 0x500;
    ((s32 *)track->keys[4])[3] = 0x101;
    ((s32 *)track->keys[4])[4] = 0x101;
    for (i = 0; i < track->count; i++) {
        track->times[i] = (i << 12) / (track->count - 1);
    }
}

extern Pad3dState *pad3d_state;
extern u8 pad3d_task[];
extern s16 pad3d_phase;
Pad3dSoundInfo *title_shared_state_get(void);
void pad3d_show(s16 arg0) {
    u8 value;
    Pad3dSoundInfo *src;
    Pad3dState *rec;

    src = title_shared_state_get();
    rec = pad3d_state;
    task_start(0, pad3d_task, 0);
    pad3d_phase = 1;
    rec->duration = arg0;
    rec->frame = 0;
    value = src->selected_index;
    rec->from_index = (s16) value;
    rec->shown_index = (s16) value;
}

extern s16 pad3d_phase;

s32 pad3d_arrived(void) {
    return pad3d_phase >= 2;
}

extern s16 pad3d_present_flag;

s32 pad3d_gone(void) {
    return pad3d_present_flag == 0;
}

s32 title_track_sample(s32 x, s32 n, s32 *xs, u8 *table_entry);
/* Scans the entries of state->unk_3A4 slots for the first one whose
 * title_track_sample result (>> 12) reaches `value` (index 2) or drops to
 * `value` or below (index 3). Returns the slot index, or 0 for other indices. */
s32 pad3d_find_slot(Pad3dState *state, s32 index, s32 value) {
    u8 *entry;
    s32 i;

    entry = (u8 *)state + (index * 0xE4 + 0x10);
    switch (index) {
    case 2:
        for (i = 0; i < state->duration; i++) {
            if (title_track_sample((i << 12) / (s16)state->duration, *(s32 *)(entry + 0xE0),
                              (s32 *)(entry + 0xC0), entry + 0x80) >> 12 >= value) {
                return i;
            }
        }
        return i;
    case 3:
        for (i = 0; i < state->duration; i++) {
            if (title_track_sample((i << 12) / (s16)state->duration, *(s32 *)(entry + 0xE0),
                              (s32 *)(entry + 0xC0), entry + 0x80) >> 12 <= value) {
                return i;
            }
        }
        return i;
    default:
        return 0;
    }
}

extern s16 pad3d_phase;

s32 pad3d_turning(void) {
    return pad3d_phase == 2;
}

void pad3d_left(s32 arg0) {
    Pad3dState *state;
    Pad3dSoundInfo *info;
    u8 *base;
    s32 tmp;
    s32 idx;
    u8 count;

    state = pad3d_state;
    base = pad3d_task;
    info = title_shared_state_get();
    if (state->track_index == 2) {
        return;
    }
    if (state->track_index == 3) {
        title_entries_reset(0x4FFFF);
        tmp = state->to_index;
        state->to_index = (u16)state->from_index;
        state->from_index = tmp;
        state->frame = pad3d_find_slot(state, 2, state->rot_y);
    } else {
        count = info->selected_index;
        idx = count - 1;
        state->from_index = count;
        if (idx >= 0) {
            title_entries_reset(0x4FFFF);
            state->to_index = idx;
            state->frame = 0;
        } else {
            return;
        }
    }
    state->track_index = 2;
    state->duration = arg0;
    *(s16 *)(base + 0x22) = 2;
}

void pad3d_right(s16 value) {
    Pad3dState *state;
    Pad3dSoundInfo *obj;
    u8 *table;
    s16 mode;
    s32 next;
    s32 tmp;
    u8 count;

    state = pad3d_state;
    table = pad3d_task;
    obj = title_shared_state_get();
    mode = state->track_index;
    if (mode != 3) {
        if (mode == 2) {
            title_entries_reset(0x4FFFF);
            tmp = state->to_index;
            state->to_index = (u16)state->from_index;
            state->from_index = tmp;
            state->frame = pad3d_find_slot(state, 3, state->rot_y);
        } else {
            count = obj->selected_index;
            next = count + 1;
            state->from_index = count;
            if (next >= 4) {
                return;
            }
            title_entries_reset(0x4FFFF);
            state->to_index = next;
            state->frame = 0;
        }
        state->track_index = 3;
        state->duration = value;
        ((s16 *)table)[0x11] = 2;
    }
}

void pad3d_start(s16 value) {
    pad3d_phase = 3;
    pad3d_state->duration = value;
    pad3d_state->frame = 0;
}

void pad3d_anim_update(TitleTaskNode *task) {
    Pad3dState *st;
    u8 *mode;
    Pad3dTrack *track;
    s32 t;
    s16 w;

    st = task->unk_14;
    mode = &title_shared_state_get()->unk_24;
    switch (task->sub_state) {
    case 0:
        break;
    case 1:
        t = (st->frame << 12) / st->duration;
        track = &st->tracks[0];
        st->pos_x = title_track_sample(t, track->count, track->times, track->keys[0]) >> 12;
        st->pos_y = title_track_sample(t, track->count, track->times, track->keys[1]) >> 12;
        st->pos_z = title_track_sample(t, track->count, track->times, track->keys[2]) >> 12;
        st->rot_x = title_track_sample(t, track->count, track->times, track->keys[3]) >> 12;
        st->rot_y = title_track_sample(t, track->count, track->times, track->keys[4]) >> 12;
        st->rot_z = title_track_sample(t, track->count, track->times, track->keys[5]) >> 12;
        st->unk_3A0 = t;
        st->unk_3A8 = t;
        st->frame++;
        if (st->duration < st->frame) {
            task->sub_state = 10;
        }
        break;
    case 2:
        t = (st->frame << 12) / st->duration;
        track = &st->tracks[st->track_index];
        st->rot_y = title_track_sample(t, track->count, track->times, track->keys[4]) >> 12;
        if (t < 0x801) {
            w = st->from_index;
            st->unk_3A8 = (0x800 - t) * 2;
            st->shown_index = w;
        } else {
            w = st->to_index;
            st->unk_3A8 = (t - 0x800) * 2;
            st->shown_index = w;
        }
        st->frame++;
        if (st->duration < st->frame) {
            mode[4] = st->to_index;
            st->track_index = -1;
            task->sub_state = 10;
        }
        break;
    case 3:
        t = (st->frame << 12) / st->duration;
        track = &st->tracks[1];
        st->unk_3A0 = 0x1000 - t;
        st->unk_3A8 = 0x1000 - t;
        st->pos_x = title_track_sample(t, track->count, track->times, track->keys[0]) >> 12;
        st->pos_y = title_track_sample(t, track->count, track->times, track->keys[1]) >> 12;
        st->pos_z = title_track_sample(t, track->count, track->times, track->keys[2]) >> 12;
        st->rot_x = title_track_sample(t, track->count, track->times, track->keys[3]) >> 12;
        st->rot_y = title_track_sample(t, track->count, track->times, track->keys[4]) >> 12;
        st->rot_z = title_track_sample(t, track->count, track->times, track->keys[5]) >> 12;
        st->frame++;
        if (st->duration < st->frame) {
            title_flag_test_set(task);
        }
        break;
    case 10:
        break;
    }
}

char keypage_callout_text[108] = "NO USE\000\000USE GRENADE\000SLIDE TO THE RIGHT\000\000SLIDE TO THE LEFT\000\000\000SHOOT\000\000\000JUMP\000\000\000\000TYPE-D\000\000TYPE-C\000\000TYPE-B\000\000TYPE-A\000";

extern s32 title_tile_offset_x_table[];
extern s32 title_tile_offset_y_table[];
/* A flat polyline (x0,y0)-(mid,y1)-(x1,y1) in r,g,b scaled by scale/0x1000, then five 1x1 tiles at offsets
 * from (x0,y0) (title_tile_offset_x_table/title_tile_offset_y_table), the last one grey. y1 pinned to $t0 to match the allocation. */
void title_menu_panel_draw(s32 ot_index, s32 x0, s32 y0, s32 x1, s32 y1, s32 r, s32 g, s32 b, s32 scale, s32 unused) {
    register s32 bottom asm("$8") = y1;
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 semi = 0;
    s32 mid = (x0 + x1) / 2;
    s32 grey;
    s32 i;

    r = r * scale / 0x1000;
    g = g * scale / 0x1000;
    b = b * scale / 0x1000;
    scratch_top[7] = 0x48;
    *(s16 *)(scratch_top + 0xE) = bottom;
    *(s16 *)(scratch_top + 0x12) = bottom;
    scratch_top[3] = 5;
    *(s32 *)(scratch_top + 0x14) = 0x55555555;
    *(s16 *)(scratch_top + 8) = x0;
    *(s16 *)(scratch_top + 0xA) = y0;
    *(s16 *)(scratch_top + 0xC) = mid;
    *(s16 *)(scratch_top + 0x10) = x1;
    scratch_top[4] = r;
    scratch_top[5] = g;
    scratch_top[6] = b;
    scratch_top[7] &= ~2;
    {
        u8 *entry = (u8 *)(ot_index * 4) + (u32)ctx->ot_base;
        u8 *pkt = scratch_top;
        addPrim(entry, pkt);
    }
    scratch_top += 0x18;

    grey = scale * 0xFF / 0x1000;
    for (i = 0; i < 5; i++) {
        scratch_top[3] = 2;
        scratch_top[7] = 0x68;
        if (i != 4) {
            scratch_top[4] = r;
            scratch_top[5] = g;
            scratch_top[6] = b;
        } else {
            scratch_top[4] = grey;
            scratch_top[5] = grey;
            scratch_top[6] = grey;
        }
        if (semi) {
            scratch_top[7] |= 2;
        } else {
            scratch_top[7] &= ~2;
        }
        *(s16 *)(scratch_top + 8) = x0 + title_tile_offset_x_table[i];
        *(s16 *)(scratch_top + 0xA) = y0 + title_tile_offset_y_table[i];
        {
            u8 *entry = (u8 *)(ot_index * 4) + (u32)ctx->ot_base;
            u8 *pkt = scratch_top;
            addPrim(entry, pkt);
        }
        scratch_top += 0xC;
    }
}

extern u8 *title_menu_gfx_ptr;
extern u8 *title_menu_page_title_table[];
extern u8 title_menu_page_items_table[][6];
extern u8 *title_menu_item_name_table[];
void title_menu_panel_draw(s32 ot_index, s32 x0, s32 y0, s32 x1, s32 y1, s32 r, s32 g, s32 b, s32 scale, s32 unused);
void title_menu_draw(TitleMenuDrawObj *obj) {
    TitleMenuDrawState *st = obj->state;
    s32 sel;
    s32 dim;
    s32 diff;
    s32 col;
    u8 *row;
    if (obj->active == 0) {
        return;
    }
    title_rec_select(1);
    title_item_select(1);
    st->unk_008 = 0x118;
    title_model_draw_at(st, &st->unk_008, title_menu_gfx_ptr + 2, st->unk_3A0);

    sel = st->fade_level;
    diff = sel ^ 0x1000;
    dim = diff != 0;
    title_menu_panel_draw(0x14, 0x96, 0x78, 0xBE, 0x6E, 0x40, 0xFF, 0x40, sel, dim);
    title_menu_panel_draw(0x14, 0xA5, 0x89, 0xBE, 0x91, 0xFF, 0x20, 0x20, sel, dim);
    title_menu_panel_draw(0x14, 0x89, 0x84, 0xBE, 0x7D, 0xFF, 0x20, 0x80, sel, dim);
    title_menu_panel_draw(0x14, 0x96, 0x96, 0xBE, 0xA0, 0x40, 0x40, 0xFF, sel, dim);
    title_menu_panel_draw(0x14, 0x96, 0x5A, 0xBE, 0x52, 0xA8, 0xA8, 0xA8, sel, dim);
    title_menu_panel_draw(0x14, 0x4E, 0x51, 0x64, 0x46, 0xA8, 0xA8, 0xA8, sel, dim);
    title_draw_text(0x30, 0xAA, title_menu_page_title_table[st->menu_index], 1, sel);
    col = (diff == 0) ? 0x1C18 : 0;
    if (st->menu_index != 0) {
        title_menu_quad_draw(0xC, 0x20, 0xA8, 0x32, 1, col, 1);
    }
    if (st->menu_index != 3) {
        title_menu_quad_draw(0xC, 0x68, 0xA8, 0x33, 1, col, 1);
    }
    title_text_ot_depth_set(0x14);
    row = title_menu_page_items_table[st->menu_index];
    title_draw_text(0xC0, 0x8D, (u8 *)"!", 0, sel);
    title_draw_text(0xC0, 0x6A, (u8 *)"\"", 0, sel);
    title_draw_text(0xC0, 0x9C, (u8 *)"#", 0, sel);
    title_draw_text(0xC0, 0x79, (u8 *)"$", 0, sel);
    title_draw_text(0x66, 0x42, (u8 *)"()", 0, sel);
    title_draw_text(0xC0, 0x4E, (u8 *)"&'", 0, sel);
    title_text_ot_depth_set(-1);
    title_draw_text(0xC8, 0x8D, title_menu_item_name_table[*row++], 2, sel);
    title_draw_text(0xC8, 0x6A, title_menu_item_name_table[*row++], 2, sel);
    title_draw_text(0xC8, 0x9C, title_menu_item_name_table[*row++], 2, sel);
    title_draw_text(0xC8, 0x79, title_menu_item_name_table[*row++], 2, sel);
    title_draw_text(0x78, 0x42, title_menu_item_name_table[*row++], 2, sel);
    title_draw_text(0xD2, 0x4E, title_menu_item_name_table[*row], 2, sel);
}

s32 title_video_is_pal(void);
extern s32 panel_task;
extern s16 D_80111DC8;
extern s16 panel_y;
extern s16 D_80111DCC;
extern s16 D_80111DCE;
extern s16 D_80111DD4;
extern s32 panel_two_lines_flag;
void panel_update();  /* a function reached by pointer */
void sound_panel_draw(TitleTaskRec *task);  /* a function reached by pointer */
void panel_init(void) {
    s16 *panel_slot;
    task_reset((TitleCtl *)&panel_task);
    panel_slot = &D_80111DC8;
    task_set((TitleTaskRec *)&panel_task, 0, (s32)&panel_update, (s32)&sound_panel_draw, (s32)panel_slot);
    *panel_slot = 0x1C;
    D_80111DCC = 0x107;
    D_80111DCE = 0x1F;
    D_80111DD4 = 0x10;
    if (title_video_is_pal() == 1) {
        panel_y = 0xC0;
        panel_two_lines_flag = 0;
    } else {
        panel_y = 0xBC;
        panel_two_lines_flag = 1;
    }
}
