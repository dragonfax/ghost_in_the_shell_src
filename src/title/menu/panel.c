/* panel: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

extern s32 panel_two_lines_flag;

s32 panel_is_two_lines(void) {
    return panel_two_lines_flag;
}

extern Rec80111DB4 *panel_state_ptr;
extern TitlePanelFlag panel_mode_flag;
extern s32 panel_task;
/* Stores the two arguments into the record at panel_state_ptr (+0x10 and +0xC), clears panel_mode_flag, then runs task_start on the table at panel_task. */
void panel_show(s16 value_10, s16 value_0C) {
    panel_state_ptr->unk_10 = value_10;
    panel_state_ptr->unk_0C = value_0C;
    panel_mode_flag.unk_00 = 0;
    task_start(0, &panel_task, 0);
}

void title_panel_start(s32 value_10, s32 value_0C) {
    panel_state_ptr->unk_10 = value_10;
    panel_state_ptr->unk_0C = value_0C;
    panel_mode_flag.unk_00 = 4;
}

void panel_update(TitleSpriteCtl *ctl) {
    TitleStepTrack *track = (TitleStepTrack *)ctl->anim;

    switch (ctl->state) {
    case 0:
        track->count = 0;
        track->step = 0;
        track->value = 0;
        ctl->state++;
        break;
    case 1:
        track->count++;
        if (track->limit < (s16)track->count) {
            ctl->state++;
        }
        break;
    case 2:
        track->value = ((s16)track->step << 12) / track->period;
        track->step++;
        if (track->period < (s16)track->step) {
            ctl->state++;
        }
        break;
    case 4:
        track->count = 0;
        ctl->state++;
        break;
    case 5:
        track->count++;
        if (track->limit < (s16)track->count) {
            track->value = 0x1000;
            track->step = track->period;
            ctl->state++;
        }
        break;
    case 6:
        track->value = ((s16)track->step << 12) / track->period;
        track->step--;
        if ((s16)track->step < 0) {
            title_flag_test_set(ctl);
        }
        break;
    }
}

extern u8 *settings_item_name_table[];
extern u8 *settings_screen_value_names[];
extern u8 *settings_movie_value_names[];
extern u8 *settings_mission_value_names[];
extern u8 *settings_item_name_table_b[];
extern u8 str_sound_label[];
extern u8 str_monoral_indent[];
extern u8 str_stereo_indent[];
extern u8 str_3d_stereo_indent[];
extern u8 str_sound_page_title[];
extern u8 str_monoral[];
extern u8 str_stereo[];
extern u8 str_3d_stereo[];
/* panel task draw: a semi-transparent tile that opens vertically by rect->scale,
   and once fully open the sound settings text (two layouts) */
void sound_panel_draw(TitleTaskRec *task) {
    TitlePanelRect *rect = (TitlePanelRect *)task->param;
    Pad3dSoundInfo *info;
    TitleDrawCtx *ctx;
    register TitleDrawCtx *dc asm("$4");
    u8 *opts;
    s32 inner_h;
    s32 x, y, w, scale, open_h, top, left;
    s16 h;
    s32 pad[6];

    info = title_shared_state_get();
    ctx = title_draw_ctx_ptr;
    opts = &info->unk_24;
    if (panel_is_two_lines() == 1) {
        h = rect->h;
        scale = rect->scale;
        x = rect->x;
        y = rect->y;
        w = rect->w;
        open_h = h * scale / 4096;
        top = y + h / 2 - open_h / 2;

        /* DR_TPAGE: semi-transparency mode */
        *(u32 *)(scratch_top + 4) = 0xE1000620;
        dc = title_draw_ctx_ptr;
        scratch_top[3] = 1;
        title_add_prim(dc->ot_base + 0xC, scratch_top);
        scratch_top += 8;
        /* TILE, semi-transparent */
        scratch_top[3] = 3;
        scratch_top[7] = 0x60;
        scratch_top[4] = 0x20;
        scratch_top[5] = 0x60;
        *(s16 *)(scratch_top + 8) = x;
        *(s16 *)(scratch_top + 0xA) = top;
        *(s16 *)(scratch_top + 0xC) = w;
        *(s16 *)(scratch_top + 0xE) = open_h;
        scratch_top[6] = 0x30;
        scratch_top[7] |= 2;
        title_add_prim(ctx->ot_base + 0xC, scratch_top);
        scratch_top += 0x10;
        {
            register TitleDrawCtx *dc2 asm("$3") = title_draw_ctx_ptr;
            scratch_top[3] = 1;
            *(u32 *)(scratch_top + 4) = 0xE1000600;
            title_add_prim(dc2->ot_base + 0xC, scratch_top);
            scratch_top += 8;
        }

        if (scale == 0x1000) {
            x += 4;
            y += 4;
            title_draw_text(x, y, settings_item_name_table[info->selected_index], 0, scale);
            title_draw_text(x, y + 8, str_sound_label, 0, scale);
            switch (*opts) {
            case 0:
                title_draw_text(x, y + 0x10, str_monoral_indent, 0, scale);
                break;
            case 1:
                title_draw_text(x, y + 0x10, str_stereo_indent, 0, scale);
                break;
            case 2:
                title_draw_text(x, y + 0x10, str_3d_stereo_indent, 0, scale);
                break;
            }
            x += 0x88;
            title_draw_text(x, y, settings_screen_value_names[opts[1]], 0, 0x1000);
            title_draw_text(x, y + 8, settings_movie_value_names[opts[2]], 0, 0x1000);
            title_draw_text(x, y + 0x10, settings_mission_value_names[opts[3]], 0, 0x1000);
        }
    } else {
        inner_h = rect->h - 4;
        scale = rect->scale;
        y = rect->y;
        left = rect->x;
        x = left + 4;
        w = rect->w - 8;
        open_h = inner_h * scale / 4096;
        top = y + inner_h / 2 - open_h / 2;

        *(u32 *)(scratch_top + 4) = 0xE1000620;
        dc = title_draw_ctx_ptr;
        scratch_top[3] = 1;
        title_add_prim(dc->ot_base + 0xC, scratch_top);
        scratch_top += 8;
        scratch_top[3] = 3;
        scratch_top[7] = 0x60;
        scratch_top[4] = 0x20;
        scratch_top[5] = 0x60;
        *(s16 *)(scratch_top + 8) = x;
        *(s16 *)(scratch_top + 0xA) = top;
        *(s16 *)(scratch_top + 0xC) = w;
        *(s16 *)(scratch_top + 0xE) = open_h;
        scratch_top[6] = 0x30;
        scratch_top[7] |= 2;
        title_add_prim(ctx->ot_base + 0xC, scratch_top);
        scratch_top += 0x10;
        {
            register TitleDrawCtx *dc2 asm("$3") = title_draw_ctx_ptr;
            scratch_top[3] = 1;
            *(u32 *)(scratch_top + 4) = 0xE1000600;
            title_add_prim(dc2->ot_base + 0xC, scratch_top);
            scratch_top += 8;
        }

        if (scale == 0x1000) {
            x = left + 8;
            y += 4;
            title_draw_text(x, y, settings_item_name_table_b[info->selected_index], 0, scale);
            title_draw_text(x, y + 0xC, str_sound_page_title, 0, scale);
            switch (*opts) {
            case 0:
                title_draw_text(left + 0x48, y + 0xC, str_monoral, 0, scale);
                break;
            case 1:
                title_draw_text(left + 0x48, y + 0xC, str_stereo, 0, scale);
                break;
            case 2:
                title_draw_text(left + 0x48, y + 0xC, str_3d_stereo, 0, scale);
                break;
            }
            x += 0x98;
            title_draw_text(x, y, settings_movie_value_names[opts[2]], 0, 0x1000);
            title_draw_text(x, y + 0xC, settings_mission_value_names[opts[3]], 0, 0x1000);
        }
    }
}

extern s16 D_800BDB0C[] __asm__(".L800BDB0C");
void quad_points_init(TitleRec8 *out);
void title_uv_quad_fill(u8 *out);
void title_glyph_quad_uv(TitleGlyphQuad *q, s32 index);
/*
 * Writes a 12-cell primitive list at buf: header word 0xC, then per cell a
 * 0x70-byte block (scale words, 4 TitleRec8, 16 uv bytes, a TitleGlyphQuad).
 * scale = table[value's fixed-point root] (LZCS/LZCR normalisation, as isqrt).
 * Returns the end pointer.
 */
s32 title_cell_table_build(s32 buf) {
    s32 *p;
    TitleCellTail *tail;
    s32 value;
    s32 lzcr;
    s32 exp_shift;
    u32 table_idx; /* first the even mask for lzcr, then the table index (one register) */
    s32 half_shift;
    s32 scale;
    s32 i;
    s16 *table;

    p = (s32 *)buf;
    value = 0xB78;
    table_idx = ~1;
    gte_set(LZCS, value);
    table = D_800BDB0C;
    gte_get(LZCR, lzcr);
    half_shift = 31 - lzcr;
    lzcr &= table_idx;
    exp_shift = lzcr - 24;
    table_idx = value << exp_shift;
    if (exp_shift < 0) {
        table_idx = (u32)value >> -exp_shift;
    }
    value = table[table_idx];
    half_shift >>= 1;
    value <<= half_shift;
    scale = (u32)value >> 12;

    *p++ = 0xC;
    i = 0;
    do {
        *p++ = scale;
        *p++ = 4;
        quad_points_init((TitleRec8 *)p);
        p += 8;
        *p++ = 4;
        title_uv_quad_fill((u8 *)p);
        p += 4;
        *p++ = 1;
        *p++ = 1;
        *p++ = scale;
        tail = (TitleCellTail *)p;
        tail->unk_00 = 0;
        tail->unk_02 = 0;
        tail->unk_04 = 0;
        p += 2;
        title_glyph_quad_uv((TitleGlyphQuad *)p, i);
        p += 8;
        i++;
    } while (i < 12);
    return (s32)p;
}

extern u16 title_glyph_tpage[];
extern u16 title_glyph_clut[];

/* Fills glyph quad q for cell index of a 0x68 x 0x20 grid, 8 cells a row (title_glyph_quad_fill's twin). */
void title_glyph_quad_uv(TitleGlyphQuad *q, s32 index) {
    s32 row;
    s32 u;
    s8 u0;
    s8 u1;
    s32 v0;
    s32 v1;

    q->x0 = 0;
    q->y0 = 4;
    q->y1 = 8;
    q->x1 = 12;
    q->x2 = 0;
    q->y2 = 4;
    q->y3 = 8;
    q->x3 = 12;
    row = index / 8;
    /* u and v are each set twice: sched1 then keeps u1's add after v's shift */
    u = row * 13;
    u <<= 3;
    u0 = u;
    v0 = index - row * 8;
    v0 <<= 5;
    q->v0 = v0;
    q->v1 = v0;
    v1 = v0 + 0x1F;
    q->v3 = v1;
    q->v2 = v1;
    q->u0 = u0;
    u1 = u0 + 0x68;
    q->u1 = u1;
    q->u3 = u1;
    q->u2 = u0;
    q->code = 0x4A000000;
    q->tpage = title_glyph_tpage[0];
    q->clut = title_glyph_clut[0];
}

extern s32 quad_points_x_table[4];
extern s32 quad_points_y_table[4];
/* Fills four records: x from quad_points_x_table, y from quad_points_y_table, z = 0. */
void quad_points_init(TitleRec8 *out) {
    s16 *z_ptr;
    s32 *x_src;
    s32 *y_src;
    s32 y;
    s32 i;

    i = 0;
    z_ptr = (s16 *)out + 2;
    y_src = quad_points_y_table;
    x_src = quad_points_x_table;
    do {
        out->x = *x_src++;
        i++;
        y = *y_src++;
        z_ptr[0] = 0;
        z_ptr[-1] = y;
        z_ptr += 4;
        out++;
    } while (i < 4);
}

extern TitleUv title_uv_u0[3584];
extern TitleUv title_uv_u1[128];
/* Packs four 16-bit values (>>6) into a 16-byte block; byte 2/6/10/14 are cleared. */
void title_uv_quad_fill(u8 *out) {
    u32 val_a;
    u32 val_b;
    u32 val_c;
    u32 val_d;

    val_a = title_uv_u0[0].u >> 6;
    val_b = title_uv_u0[0].v >> 6;
    val_c = title_uv_u1[0].u >> 6;
    val_d = title_uv_u1[0].v >> 6;
    out[2] = 0;
    out[6] = 0;
    out[10] = 0;
    out[14] = 0;
    out[0] = val_a;
    out[1] = val_b;
    out[4] = val_c;
    out[5] = val_d;
    out[8] = val_c;
    out[9] = val_d;
    out[12] = val_a;
    out[13] = val_b;
}

extern TitleMenuQuad menu_quads[];
extern TitleMenuQuad D_8011776C[];
extern TitleMenuQuad D_801177CC[];
extern TitleMenuQuad D_801177EC[];
extern TitleMenuQuad D_8011780C[];
extern TitleMenuQuad D_8011782C[];
extern TitleMenuQuad D_8011784C[];
extern TitleMenuQuad D_8011785C[];
extern TitleMenuQuad D_8011786C[];
extern u16 title_glyph_tpage[];
extern u16 title_clut_b[];
extern u16 title_glyph_clut[];
extern u16 title_tpage_b[];
void menu_quads_init(void) {
    s32 i;
    TitleMenuQuad *p;
    TitleMenuQuad *q;

    p = &menu_quads[0];
    for (i = 0; i < 12; i++, p++) {
        p->a = (i / 8) * 0x68;
        p->b = (i % 8) << 5;
        p->c = 0x68;
        p->d = 0x1F;
        p->e = title_glyph_clut[0];
        p->f = title_glyph_tpage[0];
    }

    p = &menu_quads[20];
    for (i = 0; i < 12; i++, p++) {
        p->a = (i % 2) * 0x68;
        p->b = (i / 2) * 0x18;
        p->c = 0x68;
        p->d = 0x18;
        p->e = title_tpage_b[0];
        p->f = title_clut_b[0];
    }

    q = D_8011776C;
    FAKE_OPAQUE(q);
    p = &q[12];
    for (i = 0; i < 4; i++, p++) {
        p->a = (i % 2) * 0x48;
        p->b = (i / 2) * 0x18 - 0x70;
        p->c = 0x48;
        p->d = 0x18;
        p->e = title_tpage_b[0];
        p->f = title_clut_b[0];
    }

    q = D_801177CC;
    FAKE_OPAQUE(q);
    p = &q[4];
    for (i = 0; i < 4; i++, p++) {
        p->a = (i % 2) * 0x30;
        p->b = (i / 2) * 0x18 - 0x40;
        p->c = 0x30;
        p->d = 0x18;
        p->e = title_tpage_b[0];
        p->f = title_clut_b[0];
    }

    q = D_801177EC;
    FAKE_OPAQUE(q);
    p = &q[4];
    for (i = 0; i < 4; i++, p++) {
        p->a = (i % 2) * 0x30 + 0x60;
        p->b = (i / 2) * 0x18 - 0x40;
        p->c = 0x30;
        p->d = 0x18;
        p->e = title_tpage_b[0];
        p->f = title_clut_b[0];
    }

    q = D_8011780C;
    FAKE_OPAQUE(q);
    p = &q[4];
    for (i = 0; i < 4; i++, p++) {
        p->a = 0x68 + i * 8;
        p->b = 0xC0;
        p->c = 8;
        p->d = 8;
        p->e = title_glyph_clut[0];
        p->f = title_glyph_tpage[0];
    }

    q = D_8011782C;
    FAKE_OPAQUE(q);
    p = &q[4];
    for (i = 0; i < 2; i++, p++) {
        p->a = 0x68;
        p->b = -0x38 + i * 8;
        p->c = 0x10;
        p->d = 8;
        p->e = title_glyph_clut[0];
        p->f = title_glyph_tpage[0];
    }

    q = D_8011784C;
    FAKE_OPAQUE(q);
    p = &q[2];
    for (i = 0; i < 2; i++, p++) {
        p->a = 0x68 + i * 8;
        p->b = 0x80;
        p->c = 8;
        p->d = 0x10;
        p->e = title_glyph_clut[0];
        p->f = title_glyph_tpage[0];
    }

    q = D_8011785C;
    FAKE_OPAQUE(q);
    p = &q[2];
    for (i = 0; i < 2; i++, p++) {
        p->a = 0x78 + i * 8;
        p->b = 0x80;
        p->c = 8;
        p->d = 8;
        p->e = title_glyph_clut[0];
        p->f = title_glyph_tpage[0];
    }

    q = D_8011786C;
    FAKE_OPAQUE(q);
    p = &q[3];
    for (i = 0; i < 6; i++, p++) {
        p->a = 0x68;
        p->b = -0x70 + i * 8;
        p->c = 0x68;
        p->d = 8;
        p->e = title_glyph_clut[0];
        p->f = title_glyph_tpage[0];
    }
}

void title_menu_quad_draw(s32 depth, s32 x, s32 y, s32 index, s32 semi_trans, s32 bright, s32 twice) {
    TitleMenuQuad *quad;
    TitleDrawCtx *ctx;
    s32 u, v, w, h;
    s32 offset;
    u32 tpage;

    ctx = title_draw_ctx_ptr;
    quad = &menu_quads[index];
    u = quad->a;
    v = quad->b;
    w = quad->c;
    h = quad->d;
    bright /= 32;
    if (bright >= 0x100) {
        bright = 0xFF;
    }
    scratch_top[3] = 4;
    scratch_top[7] = 0x64;
    if (semi_trans != 0) {
        scratch_top[7] |= 2;
    } else {
        scratch_top[7] &= 0xFD;
    }
    scratch_top[4] = bright;
    scratch_top[5] = bright;
    scratch_top[6] = bright;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    scratch_top[0xC] = u;
    scratch_top[0xD] = v;
    *(s16 *)(scratch_top + 0x10) = w;
    *(s16 *)(scratch_top + 0x12) = h;
    offset = depth * 4;
    *(u16 *)(scratch_top + 0xE) = quad->f;
    addPrimA0A1((u8 *)offset + (u32)ctx->ot_base, scratch_top);
    scratch_top += 0x14;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (quad->e & 0x9FF) | 0xE1000600;
    addPrimA0A1((u8 *)offset + (u32)ctx->ot_base, scratch_top);
    scratch_top += 8;

    if (semi_trans == 1 && twice == semi_trans) {
        tpage = quad->e;
        scratch_top[7] = 0x64;
        scratch_top[3] = 4;
        scratch_top[4] = bright;
        scratch_top[5] = bright;
        scratch_top[6] = bright;
        *(s16 *)(scratch_top + 8) = x;
        *(s16 *)(scratch_top + 0xA) = y;
        scratch_top[0xC] = u;
        scratch_top[0xD] = v;
        *(s16 *)(scratch_top + 0x10) = w;
        *(s16 *)(scratch_top + 0x12) = h;
        scratch_top[7] |= 2;
        *(u16 *)(scratch_top + 0xE) = quad->f;
        addPrimA0A1((u8 *)offset + (u32)ctx->ot_base, scratch_top);
        scratch_top += 0x14;

        scratch_top[3] = 1;
        *(u32 *)(scratch_top + 4) = ((tpage | 0x40) & 0x9DF) | 0xE1000600;
        addPrimA0A1((u8 *)offset + (u32)ctx->ot_base, scratch_top);
        scratch_top += 8;
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    addPrimA0A1((u8 *)(depth * 4) + (u32)ctx->ot_base, scratch_top);
    scratch_top += 0xC;
}

void title_quad_pos_fill(u8 *out);
/*
 * Writes a 39-cell primitive list at buf (title_cell_table_build's twin):
 * header word 0x27, then per cell scale words, 4 vertices, uv words and a
 * TitleGlyphQuad. Returns the end pointer.
 */
void title_quad_verts_fill(TitleVec4 *out, s32 count);

void title_glyph_quad_fill(TitleGlyphQuad *q, s32 index);

s32 title_cell_list_build(s32 buf) {
    s32 *p;
    TitleCellTail *tail;
    s32 value;
    s32 lzcr;
    s32 exp_shift;
    u32 table_idx;
    s32 half_shift;
    s32 scale;
    s32 i;
    s16 *table;

    p = (s32 *)buf;
    value = 0x290;
    table_idx = ~1;
    gte_set(LZCS, value);
    table = D_800BDB0C;
    gte_get(LZCR, lzcr);
    half_shift = 31 - lzcr;
    lzcr &= table_idx;
    exp_shift = lzcr - 24;
    table_idx = value << exp_shift;
    if (exp_shift < 0) {
        table_idx = (u32)value >> -exp_shift;
    }
    value = table[table_idx];
    half_shift >>= 1;
    value <<= half_shift;
    scale = (u32)value >> 12;

    *p++ = 0x27;
    i = 0;
    do {
        *p++ = scale;
        *p++ = 4;
        title_quad_verts_fill((TitleVec4 *)p, i);
        p += 8;
        *p++ = 4;
        title_quad_pos_fill((u8 *)p);
        p += 4;
        *p++ = 1;
        *p++ = 1;
        *p++ = scale;
        tail = (TitleCellTail *)p;
        tail->unk_00 = 0;
        tail->unk_02 = 0;
        tail->unk_04 = 0;
        p += 2;
        title_glyph_quad_fill((TitleGlyphQuad *)p, i);
        p += 8;
        i++;
    } while (i < 39);
    return (s32)p;
}

void title_glyph_quad_fill(TitleGlyphQuad *q, s32 index) {
    s32 w;
    s32 u;
    s32 v;
    s32 row;
    s32 h = 32;

    q->x0 = 0;
    q->y0 = 4;
    q->y1 = 8;
    q->x1 = 12;
    q->x2 = 0;
    q->y2 = 4;
    q->y3 = 8;
    q->x3 = 12;
    row = index / 6;
    v = row << 5;
    if (index >= 37) {
        w = 48;
        u = (index - 37) * w + 40;
    } else {
        w = 40;
        u = (index - row * 6) * w;
    }
    q->u1 = u + w;
    q->u3 = u + w;
    q->u0 = u;
    q->v0 = v;
    q->v1 = v;
    q->v3 = v + h - 1;
    q->u2 = u;
    q->v2 = v + h - 1;
    q->code = 0x4A000000;
    q->tpage = title_sprite_clut_b;
    q->clut = title_sprite_tpage_b;
}

extern s32 title_quad_vx_small[];
extern s32 title_quad_vy_table[];
extern s32 title_quad_vx_large[];
void title_quad_verts_fill(TitleVec4 *out, s32 count)
{
    s32 i;

    if (count >= 37) {
        for (i = 0; i < 4; i++, out++) {
            out->vx = title_quad_vx_large[i];
            out->vy = title_quad_vy_table[i];
            out->vz = 0;
        }
    } else {
        for (i = 0; i < 4; i++, out++) {
            out->vx = title_quad_vx_small[i];
            out->vy = title_quad_vy_table[i];
            out->vz = 0;
        }
    }
}

extern u16 title_quad_x0[256];
extern u16 title_quad_y0;
extern u16 title_quad_x1[256];
extern u16 title_quad_y1;
void title_quad_pos_fill(u8 *out) {
    u32 val_a;
    u32 val_b;
    u32 val_c;
    u32 val_d;

    val_a = title_quad_x0[0] >> 6;
    val_b = title_quad_y0 >> 6;
    val_c = title_quad_x1[0] >> 6;
    val_d = title_quad_y1 >> 6;
    out[2] = 0;
    out[6] = 0;
    out[10] = 0;
    out[14] = 0;
    out[0] = val_a;
    out[1] = val_b;
    out[4] = val_c;
    out[5] = val_d;
    out[8] = val_c;
    out[9] = val_d;
    out[12] = val_a;
    out[13] = val_b;
}

void title_button_clear(TitleSlot *slot);
void title_list_draw(TitleListTask *task);
extern u8 title_panel_tex_a[];
extern u16 title_panel_clut_data[256];
extern u8 title_strip_tex[];
extern u8 title_panel_tex_b[];
extern u16 D_800EAED8[16];
extern u8 title_timer_tex[1344];
extern u16 title_timer_clut_data[16];
extern u16 title_panel_clut;
extern u16 title_panel_clut_alt;
extern u16 title_panel_tpage;
extern u16 title_bar_clut;
extern s32 D_80111DEC;
extern u16 title_timer_tpage;
extern u16 title_timer_tpage_alt;
extern u16 title_timer_clut;
extern u16 title_strip_tpage;
extern u16 title_strip_clut;
extern u16 title_sprite_tpage;
extern u16 title_sprite_tpage_alt;
extern u16 title_sprite_clut;
extern s32 card_work_buf;
extern u8 title_list_tasks[];
extern TitleListRec title_list_recs[];
s32 sprite_load_tpage_be(u8 *sprite, s32 x, s32 y);
void title_list_slide_update(TitleListTask *task);
s32 clut_load(void *sprite, s32 x, s32 y, s32 a3, s32 a4, s32 a5);
s32 sprite_load_tpage(void *sprite, s32 x, s32 y);
void *panel_prims_build(s32 *out);
s32 sprite_sets_register(s32 *data, u16 *clut, u16 tpage, u16 clutDefault, s32 xoff, s32 yoff);
void logo_init(void);
void title_task_init(void);

void title_panel_init(void) {
    TitleListRec *rec;
    u8 *task;
    s32 i, j;
    s32 prims;

    sprite_load_tpage_be(title_panel_tex_a, 0x80, 0x100);
    title_panel_clut = 0xB2;
    title_panel_clut_alt = 0xB4;
    title_panel_tpage = clut_load(title_panel_clut_data, 0, 0xF1, 1, 2, 0x100);
    title_bar_clut = clut_load(title_panel_clut_data, 0, 0xF2, 0, 0, 0x100);
    title_strip_tpage = sprite_load_tpage_be(title_strip_tex, 0x80, 0x180);
    title_strip_clut = title_bar_clut;
    sprite_load_tpage(title_panel_tex_b, 0x80, 0x130);
    title_sprite_tpage = 0x32;
    title_sprite_tpage_alt = 0x33;
    title_sprite_clut = clut_load(D_800EAED8, 0x90, 0xF0, 0, 0, 0x10);
    sprite_load_tpage(title_timer_tex, 0x200, 0xF4);
    title_timer_tpage = 0x28;
    title_timer_tpage_alt = 0x29;
    title_timer_clut = clut_load(title_timer_clut_data, 0xA0, 0xF0, 1, 2, 0x10);
    prims = card_work_buf;
    card_work_buf = (s32)panel_prims_build((s32 *)prims);
    D_80111DEC = sprite_sets_register((s32 *)prims, NULL, 0, 0, 0, 0);
    rec = title_list_recs;
    task = title_list_tasks;
    i = 0;
    do {
        task_reset((TitleCtl *)task);
        task_set((TitleTaskRec *)task, (s32)title_button_clear, (s32)title_list_slide_update,
                 (s32)title_list_draw, (s32)rec);
        rec->x = i * 0x78 - 0xF0;
        rec->y = -0x74;
        rec->w = 0x200;
        rec->h = 0x80;
        rec->y2 = rec->y + 0x80;
        for (j = 0; j < 5; j++) {
            rec->ent[j][0].x = rec->x;
        }
        rec->slide_period = 0x46;
        rec->count = D_80111DEC + i;
        i++;
        rec++;
        task += 0x28;
    } while (i < 5);
    logo_init();
    title_task_init();
}

void title_grid_fill_row(TitleGridVtx *v, s32 index);

void panel_face(TitleQuad *quad, s32 a, s32 mode);
/* Writes the title's display-list block into out: a header word (5), then five rows of
 * a 0x30-word section plus four TitleQuads each. Returns the write position after the last quad. */
void *panel_prims_build(s32 *out) {
    s32 *p;
    s32 row;
    s32 col;
    u8 *bytes;
    s16 *halves;

    p = out;
    *p++ = 5;
    row = 0;
    do {
        *p++ = 0x30;
        *p++ = 9;
        title_grid_fill_row((TitleGridVtx *)p, row);
        p += 18;
        *p++ = 1;
        bytes = (u8 *)p;
        bytes[0] = 0;
        bytes[2] = 0;
        bytes[1] = 0x40;
        p++;
        *p++ = 1;
        *p++ = 4;
        *p++ = 0x30;
        halves = (s16 *)p;
        halves[0] = 0;
        halves[1] = 0;
        halves[2] = 0;
        p += 2;
        col = 0;
        do {
            panel_face((TitleQuad *)p, row, col);
            col++;
            p += 8;
        } while (col < 4);
        row++;
    } while (row < 5);
    return p;
}

extern s32 panel_lo_table[];
extern s32 panel_hi_table[];
extern s32 panel_rect_table[];
extern u16 title_panel_clut;
extern u16 title_panel_clut_alt;
extern u16 title_panel_tpage;
void panel_face(TitleQuad *quad, s32 a, s32 mode) {
    s32 lo;
    s32 hi;
    s32 v_lo;
    s32 v_hi;
    s32 i;
    s16 *out;
    s32 *src;
    s32 *base;
    s32 unused[2];
    u16 tex;

    if (a != 4) {
        lo = panel_lo_table[a];
        hi = panel_hi_table[a];
        quad->clut = title_panel_clut;
    } else {
        lo = 0;
        hi = 0x40;
        quad->clut = title_panel_clut_alt;
    }
    v_lo = 0;
    v_hi = 0x30;
    switch (mode) {
    case 0:
        hi = (lo + hi) / 2;
        v_hi = 0x18;
        break;
    case 1:
        lo = (lo + hi) / 2;
        v_hi = 0x18;
        break;
    case 2:
        hi = (lo + hi) / 2;
        v_lo = 0x18;
        break;
    case 3:
        lo = (lo + hi) / 2;
        v_lo = 0x18;
        break;
    }
    i = 0;
    out = quad->rect;
    base = panel_rect_table;
    src = base + mode * 4;
    quad->unk_08[0] = 0;
    quad->unk_08[1] = 0;
    quad->unk_08[2] = 0;
    quad->unk_08[3] = 0;
    do {
        *out++ = *src++ * 4;
        i++;
    } while (i < 4);
    quad->uv[0][0] = lo;
    quad->uv[1][0] = hi;
    quad->uv[2][0] = lo;
    quad->uv[3][0] = hi;
    quad->uv[0][1] = v_lo;
    quad->uv[1][1] = v_lo;
    quad->uv[2][1] = v_hi;
    quad->uv[3][1] = v_hi;
    tex = title_panel_tpage;
    quad->code = 0x4A000000;
    quad->tpage = tex;
}

extern s32 title_grid_left_edges[];
extern s32 title_grid_right_edges[];
/* Writes the 3x3 vertex grid of panel row index: columns at the row's left edge,
 * midpoint and right edge (from the edge table), rows at y = -48, 0, 48. */
void title_grid_fill_row(TitleGridVtx *v, s32 index) {
    s32 left = title_grid_left_edges[index * 2];
    s32 right = title_grid_right_edges[index * 2];
    s32 mid;

    v->x = left; v->y = -0x30; v->z = 0; v++;
    mid = (left + right) / 2;
    v->x = mid; v->y = -0x30; v->z = 0; v++;
    v->x = right; v->y = -0x30; v->z = 0; v++;
    v->x = left; v->y = 0; v->z = 0; v++;
    v->x = mid; v->y = 0; v->z = 0; v++;
    v->x = right; v->y = 0; v->z = 0; v++;
    v->x = left; v->y = 0x30; v->z = 0; v++;
    v->x = mid; v->y = 0x30; v->z = 0; v++;
    v->x = right; v->y = 0x30; v->z = 0;
}

void title_button_clear(TitleSlot *slot) {
    TitleButton *button = slot->button;

    *(s16 *)&button->unk_2C[0xE] = 0;
    button->value_3E = 0;
}

/* Steps a list panel's open animation: while the task is selected (sel 0), blends the
 * panel's w/y toward h/y2 by progress (0x1000 = all w/y) and spreads the five entries
 * evenly between; progress advances 0x1000 / unk_38 per frame, and at the end the
 * title entries are reset and the task deselected (sel -1). */
void title_list_slide_update(TitleListTask *task) {
    s32 blend_y;
    TitleListRec *rec;
    s32 progress;
    s32 w, y;
    s32 h;
    s32 blend_w;
    s32 dw, dy;
    s32 i, steps;
    s32 remain;
    s32 entry_x, entry_y;
    s32 acc_w;

    rec = task->rec;
    if (task->sel == -1) {
        return;
    }
    if (task->sel != 0) {
        return;
    }
    w = rec->w;
    progress = rec->slide_progress;
    h = rec->h;
    y = rec->y;
    blend_y = rec->y2;
    remain = 0x1000 - progress;
    blend_w = (w * progress + h * remain) / 0x1000;
    /* blend_y set twice keeps its load before the first division */
    blend_y = (y * progress + blend_y * remain) / 0x1000;
    i = 0;
    steps = 4;
    dy = y - blend_y;
    dw = w - blend_w;
    acc_w = 0;
    do {
        entry_y = y - i * dy / steps;
        entry_x = w - acc_w / steps;
        rec->ent[i][0].y = entry_y;
        rec->ent[i][1].x = entry_x;
        acc_w += dw;
        i++;
    } while (i < 5);
    rec->slide_progress += 0x1000 / rec->slide_period;
    if (rec->slide_progress > 0x1000) {
        title_entries_reset(0x16FFFF);
        task->sel = -1;
    }
}

void title_draw_mode_link(s32 ot_index, s32 semi_trans, s32 tpage);

void title_list_draw(TitleListTask *task) {
    TitleListRec *rec = task->rec;
    s32 i;
    s32 off;
    TitleScratchFlag *scratch = (TitleScratchFlag *)0x1F8003D8;
    /* second view of the same block, kept in a register across the calls */
    TitleScratchFlag *scratch_reg = (TitleScratchFlag *)0x1F8003D8;

    FAKE_OPAQUE(scratch_reg);

    title_seq_enable_set(0);
    title_rec_select(1);
    title_draw_mode_link(0x11, 0, 1);
    gte_set_ctrl(H, 0x100);
    scratch->flag = 1;
    i = 0;
    if (task->sel == -1) {
        title_seq_flag_set(0);
        title_model_draw_at(rec, 0, (void *)(s32)rec->count, -0x1258);
        title_seq_flag_set(1);
        scratch_reg->flag = 0;
    } else {
        off = 0x10;
        for (; i < 5; i++) {
            title_model_draw_at((u8 *)rec + off, 0, (void *)(s32)rec->count, -0x4C3);
            off += 8;
        }
        scratch_reg->flag = 0;
    }
    title_rec_select(0);
    title_draw_mode_link(0xD, 1, 1);
    title_seq_enable_set(1);
}

void wave_reset(void);
extern TitleLogoSlider logo_slider;
extern u8 logo_task[];
void logo_update();  /* a function reached by pointer */
void logo_draw(TitleTaskRec *task);  /* a function reached by pointer */
void logo_init(void) {
    TitleLogoSlider *s = &logo_slider;
    s32 i;
    s32 unused;

    task_reset((TitleCtl *)logo_task);
    task_set((TitleTaskRec *)logo_task, 0, (s32)logo_update, (s32)logo_draw, (s32)s);
    s->x = 0;
    s->y = 0x26;
    s->count_b = 2;
    s->unk_44 = -0x140;
    s->unk_40 = 0;
    s->unk_50 = 0;
    s->unk_54 = 0x140;
    i = 0;
    do {
        s->steps_b[i] = (i << 12) / (s->count_b - 1);
        i++;
    } while (i < s->count_b);
    s->count_a = 4;
    s->left = s->x - 0x140;
    s->top = s->x - 0xA0;
    s->mid_x = s->x;
    s->mid_y = s->x;
    s->right = s->x + 0x140;
    s->bottom = s->x + 0xA0;
    s->edge_x = s->x;
    s->edge_y = s->x;
    for (i = 0; i < s->count_a; i++) {
        s->steps_a[i] = (i << 12) / (s->count_a - 1);
    }
    s->unk_76 = 1;
    wave_reset();
}

extern TitleLogoRec *logo_rec_ptr;
extern u8 logo_task[];
/* Copies the arguments into the record at logo_rec_ptr, clears unk_0A, copies unk_0C into unk_00, then calls task_start. */
void logo_show(s16 value74, s16 value08, s16 value04) {
    logo_rec_ptr->unk_74 = value74;
    logo_rec_ptr->unk_08 = value08;
    logo_rec_ptr->unk_04 = value04;
    logo_rec_ptr->unk_0A = 0;
    logo_rec_ptr->unk_00 = logo_rec_ptr->unk_0C;
    task_start(0, logo_task, 0);
}

extern TitleLogoRec *logo_rec_ptr;
extern s16 logo_state;
/* Sets the record's unk_74 to value74 and unk_04 to value04, clears unk_06, and sets logo_state to 3. */
void logo_hide(s16 value74, s16 value04) {
    TitleLogoRec *rec = logo_rec_ptr;

    FAKE_OPAQUE(rec);
    rec->unk_04 = value04;
    rec->unk_06 = 0;
    rec->unk_74 = value74;
    logo_state = 3;
}

extern s16 logo_state;

s32 logo_shown(void) {
    return logo_state == 2;
}

extern s16 D_80111E9C;
/* Same code as pad3d_gone (title). */
s32 func_800B14BC(void) {
    return D_80111E9C == 0;
}

void wave_advance(void);
/* Fade task update: phase 0 counts hold_count up to hold_frames, then phase 1
 * ramps progress up with the steps_a table; phase 3 ramps it with steps_b and
 * returns control to title_flag_test_set once progress passes 0x1000. */
void logo_update(TitleFadeTask *task) {
    TitleFadeRec *s = task->fade;
    s16 next_progress;
    s32 r;
    u8 *entry;

    if (s->unk_76 == 1) {
        wave_advance();
    }
    switch (task->phase) {
    case 0:
        s->hold_count++;
        if (!(s->hold_frames < (s16)s->hold_count)) {
            break;
        }
        s->progress = 0;
        task->phase++;
        /* fallthrough */
    case 1:
        entry = (u8 *)s + (s->table_index * 16 + 0xC);
        next_progress = s->progress + 0x1000 / s->period;
        s->progress = next_progress;
        r = title_track_sample(next_progress, s->count_a, s->steps_a, entry);
        s->level = r >> 12;
        if ((s16)s->progress > 0x1000) {
            task->phase++;
        }
        break;
    case 2:
        break;
    case 3:
        r = title_track_sample((s16)s->progress, s->count_b, s->steps_b, (u8 *)s + (s->table_index * 16 + 0x40));
        s->level = r >> 12;
        s->progress = s->progress + 0x1000 / s->period;
        if ((s16)s->progress > 0x1000) {
            title_flag_test_set(task);
        }
        break;
    }
}

extern u16 title_sprite_tpage;
extern u16 title_sprite_tpage_alt;
extern u16 title_sprite_clut;
/* Two textured sprites at (x, y) and (x + 0xFF, y), 0x100 and 0x40 wide, 0x30 high at texture row tex_v. Each is
 * followed by a draw-mode packet; then a texture-window reset. Packets are built at $gp and linked into the OT at +0x24.
 * flag sets semi-transparency (bit 1 of the sprite code). Packets use raw offsets, as the other TITLE packet builders do. */
void title_draw_sprite_clut(s32 x, s32 y, s32 unused_w, s32 tex_v, s32 flag) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u16 clut;

    /* first sprite */
    scratch_top[7] = 0x64;
    scratch_top[3] = 4;
    scratch_top[7] |= 1;
    if (flag) {
        scratch_top[7] |= 2;
    } else {
        scratch_top[7] &= 0xFD;
    }
    scratch_top[0xC] = 0;
    scratch_top[0xD] = tex_v;
    /* barrier: keeps the byte stores ahead of the CLUT load (the scheduler would sink them past it) */
    do { } while (0);
    clut = title_sprite_clut;
    *(s16 *)(scratch_top + 0x10) = 0x100;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x12) = 0x30;
    *(u16 *)(scratch_top + 0xE) = clut;
    title_add_prim(ctx->ot_base + 0x24, scratch_top);
    scratch_top += 0x14;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (title_sprite_tpage & 0x9FF) | 0xE1000600;
    title_add_prim(ctx->ot_base + 0x24, scratch_top);
    scratch_top += 8;

    /* second sprite, 0x40 wide, shifted 0xFF to the right */
    scratch_top[7] = 0x64;
    scratch_top[3] = 4;
    scratch_top[7] |= 1;
    if (flag) {
        scratch_top[7] |= 2;
    } else {
        scratch_top[7] &= 0xFD;
    }
    scratch_top[0xC] = 0;
    scratch_top[0xD] = tex_v;
    do { } while (0);
    clut = title_sprite_clut;
    *(s16 *)(scratch_top + 8) = x + 0xFF;
    *(s16 *)(scratch_top + 0x10) = 0x40;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x12) = 0x30;
    *(u16 *)(scratch_top + 0xE) = clut;
    title_add_prim(ctx->ot_base + 0x24, scratch_top);
    scratch_top += 0x14;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (title_sprite_tpage_alt & 0x9FF) | 0xE1000600;
    title_add_prim(ctx->ot_base + 0x24, scratch_top);
    scratch_top += 8;

    /* texture-window reset (GP0 E2) */
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    title_add_prim(ctx->ot_base + 0x24, scratch_top);
    scratch_top += 0xC;
}

extern s16 title_wave_phase;
extern s16 title_wave_step;
extern s16 title_wave_center_x;
extern s16 title_wave_center_y;

void wave_reset(void) {
    title_wave_center_x = 0xA0;
    title_wave_center_y = 0x41;
    title_wave_phase = 0;
    title_wave_step = 0x40;
}

void wave_advance(void) {
    s16 *p = &title_wave_phase;
    *p += title_wave_step;
}

/* Fills 41 line segments of a wavy beam: a straight line from (x0, y0) along
 * dir, paired with a sine-modulated point around (0x80, 0x98). */
void title_wave_line_points(s16 *out, s32 x0, s32 y0, s32 phase, s32 dir)
{
    s32 off = (dir & 0xFFF) * 4;
    s16 sin_dir = *(s16 *)(D_801085E6 + off);
    s16 cos_dir = *(s16 *)((char *)rcossin_tbl + off);
    s32 dist = 0;
    s32 count = 40;
    s32 i = 0;
    s32 amp;
    s32 radius;
    s32 line_x, line_y, wave_x, wave_y;

    do {
        line_x = dist * sin_dir / 2048 + x0;
        line_y = dist * cos_dir / 2048 + y0;
        amp = 12;
        if (i < 3) {
            amp = (i * 3 + 1) * amp / 8;
        }
        radius = rcossin_tbl[phase & 0xFFF][0] * amp / 4096 + dist;
        wave_x = radius * sin_dir / 4096 + 0x80;
        wave_y = radius * cos_dir / 4096 + 0x98;
        out[0] = line_x;
        out[2] = wave_x;
        out[1] = line_y;
        out[3] = wave_y;
        out += 4;
        i++;
        dist += 2;
        phase -= 0x155;
    } while (i <= count);
}

extern s16 title_clip_rect[4];
extern u16 title_strip_tpage;
extern u16 title_strip_clut;
/* Builds 40 textured quads between the two vertex rows a and b (quad i uses a[i], a[i+1], b[i], b[i+1]),
 * keeps those overlapping the clip rect, links each into OT ot, then links a texture-window packet.
 * Primitives come from scratch_top. */
void title_draw_strip_clipped(void *ot, StripVtx *a, StripVtx *b) {
    TitlePolyFT4 *prim;
    TitleDrTwin *tw;
    s32 i;
    s32 count;
    s16 *clip;

    prim = (TitlePolyFT4 *)scratch_top;
    clip = title_clip_rect;
    count = 40;
    for (i = 0; i < count; i++, a++, b++) {
        if ((a[0].x >= clip[0] || b[0].x >= clip[0]) &&
            (clip[1] >= a[0].x || clip[1] >= b[0].x) &&
            (a[0].y >= clip[2] || b[0].y >= clip[2]) &&
            (clip[3] >= a[0].y || clip[3] >= b[0].y)) {
            prim->x0 = a[0].x;
            prim->y0 = a[0].y;
            prim->u0 = a[0].u;
            prim->v0 = a[0].v;
            prim->x1 = a[1].x;
            prim->y1 = a[1].y;
            prim->u1 = a[1].u;
            prim->v1 = a[1].v;
            prim->x2 = b[0].x;
            prim->y2 = b[0].y;
            prim->u2 = b[0].u;
            prim->v2 = b[0].v;
            prim->x3 = b[1].x;
            prim->y3 = b[1].y;
            prim->u3 = b[1].u;
            prim->v3 = b[1].v;
            prim->len = 9;
            prim->code = 0x2D;
            prim->tpage = title_strip_tpage;
            prim->clut = title_strip_clut;
            addPrim(ot, prim);
            prim++;
        }
    }

    scratch_top = (u8 *)prim;
    ((TitleDrTwin *)scratch_top)->len = 2;
    ((TitleDrTwin *)scratch_top)->code[0] = 0xE2000000;
    ((TitleDrTwin *)scratch_top)->code[1] = 0;
    tw = (TitleDrTwin *)scratch_top;
    addPrim(ot, tw);
    scratch_top += sizeof(TitleDrTwin);
}

char str_mission_off[152] RODATA = "MISSION..OFF\000\000\000\000MISSION..ON\000MOVIE....OFF\000\000\000\000MOVIE....ON\000SCREEN...WIDE\000\000\000SCREEN...NORMAL\000KEY......Type-D\000KEY......Type-C\000KEY......Type-B\000KEY......Type-A";

u8 str_sound_label[8] RODATA = "SOUND..";

u8 str_monoral_indent[16] RODATA = "  ....MONORAL";

u8 str_stereo_indent[16] RODATA = "  ....STEREO";

u8 str_3d_stereo_indent[80] RODATA = {
    0x20, 0x20, 0x2E, 0x2E, 0x2E, 0x2E, 0x33, 0x44, 0x2D, 0x53, 0x54, 0x45,
    0x52, 0x45, 0x4F, 0x00, 0x4B, 0x45, 0x59, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
    0x54, 0x79, 0x70, 0x65, 0x2D, 0x44, 0x00, 0x00, 0x4B, 0x45, 0x59, 0x2E,
    0x2E, 0x2E, 0x2E, 0x2E, 0x54, 0x79, 0x70, 0x65, 0x2D, 0x43, 0x00, 0x00,
    0x4B, 0x45, 0x59, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x54, 0x79, 0x70, 0x65,
    0x2D, 0x42, 0x00, 0x00, 0x4B, 0x45, 0x59, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E,
    0x54, 0x79, 0x70, 0x65, 0x2D, 0x41, 0x00, 0x00,
};

u8 str_sound_page_title[12] RODATA = "SOUND...";

u8 str_monoral[8] RODATA = "MONORAL";

u8 str_stereo[8] RODATA = "STEREO";

u8 str_3d_stereo[12] RODATA = "3D-STEREO";

/* Draws the wave beam inside the clip rect (x, y, w, h): sets the draw area to the rect, draws 16 strips
 * of wave rows rotating around the rect's centre, then restores the draw area. */
void title_draw_wave_band(s32 x, s32 y, s32 w, s32 h)
{
    StripVtx rowA[0x2E];
    StripVtx rowB[0x2E];
    StripVtx *cur = rowA;
    StripVtx *next = rowB;
    StripVtx *tmp;
    TitleDrawCtx *ctx;
    u8 *ot;
    s32 i;
    s16 *wave = &title_wave_phase;

    title_clip_rect[1] = x + w;
    title_clip_rect[3] = y + h;
    ctx = title_draw_ctx_ptr;
    title_clip_rect[0] = x;
    title_clip_rect[2] = y;
    ot = ctx->ot_base + 0x24;
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = (*(u16 *)ctx->draw_env & 0x3FF) | 0xE3000000;
    *(u32 *)(scratch_top + 8) = ((*(s16 *)ctx->draw_env + 0x13F) & 0x3FF) | 0xE403BC00;
    title_add_prim(ot, scratch_top);
    scratch_top += 0xC;
    title_wave_center_x = x + w / 2;
    title_wave_center_y = y + h / 2;
    title_wave_line_points((s16 *)cur, (s16)(x + w / 2), (s16)(y + h / 2), wave[0], 0);
    for (i = 1; i < 0x11; i++) {
        title_wave_line_points((s16 *)next, wave[2], wave[3], wave[0], i << 8);
        title_draw_strip_clipped(ot, cur, next);
        tmp = cur;
        cur = next;
        next = tmp;
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = ((y & 0x3FF) << 10) | (*(u16 *)ctx->draw_env & 0x3FF) | 0xE3000000;
    *(u32 *)(scratch_top + 8) = (((y + h - 1) & 0x3FF) << 10) | ((*(s16 *)ctx->draw_env + 0x13F) & 0x3FF) | 0xE4000000;
    title_add_prim(ot, scratch_top);
    scratch_top += 0xC;
}

void title_draw_wave_band(s32 x, s32 y, s32 w, s32 h);
void title_draw_sprite_clut(s32 x, s32 y, s32 unused_w, s32 tex_v, s32 flag);
static const u8 logo_paren_text[4] = "()";
void logo_draw(TitleTaskRec *task) {
    TitleXY *pos = (TitleXY *)task->param;

    title_text_ot_depth_set(0xF);
    title_draw_text(pos->x + 0x130, pos->y - 6, (u8 *)logo_paren_text, 1, 0x1000);
    title_text_ot_depth_set(-1);

    /* Mask-settings packet (GP0 0xE6, mask off), linked into OT entry 9. */
    {
        TitleDrawCtx *ctx = title_draw_ctx_ptr;
        u8 *entry;
        u8 *prim;

        scratch_top[3] = 2;
        *(u32 *)(scratch_top + 4) = 0xE6000000;
        *(u32 *)(scratch_top + 8) = 0;
        entry = ctx->ot_base + 0x24;
        prim = scratch_top;
        addPrim(entry, prim);
        scratch_top += 0xC;
    }

    title_draw_wave_band(pos->x, pos->y, 0x140, 0x30);

    /* Mask-settings packet (GP0 0xE6, set mask bit and check mask bit), linked into OT entry 9. */
    {
        TitleDrawCtx *ctx = title_draw_ctx_ptr;
        u8 *entry;
        u8 *prim;

        scratch_top[3] = 2;
        *(u32 *)(scratch_top + 4) = 0xE6000003;
        *(u32 *)(scratch_top + 8) = 0;
        entry = ctx->ot_base + 0x24;
        prim = scratch_top;
        addPrim(entry, prim);
        scratch_top += 0xC;
    }

    title_draw_sprite_clut(pos->x, pos->y, 0x80, 0x30, 1);
}
