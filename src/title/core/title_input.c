/* title_input: one of title's own original source files (scripts/objmap.py); part of src/title/main.c's unit, included there. */

extern s32 title_input_step_value;

s32 title_input_step(void) {
    return title_input_step_value;
}

extern s32 title_input_locked;

void title_input_lock(void) {
    title_pad_clear();
    title_input_locked = 1;
}

extern s32 title_input_locked;

void title_input_unlock(void) {
    title_input_locked = 0;
}

s32 title_track_sample(s32 x, s32 n, s32 *xs, u8 *table_entry) {
    s32 *ys = (s32 *)table_entry;
    s32 i, hi, mid, dx, d, curve, frac, base;
    s32 unused[2];

    if (n < 2 || xs[0] >= x) { return ys[0] << 12; }
    if (x >= xs[n - 1]) { return ys[n - 1] << 12; }
    hi = n - 1;
    if (n == 2) {
        i = 0;
        goto linear;
    }
    i = 0;
    if (hi > 0) {
        do {
            mid = (i + hi) >> 1;
            if (xs[mid] < x) { i = mid + 1; } else { hi = mid; }
        } while (i < hi);
    }
    if (i > 0) { i--; }
    if (x >= (xs[i] + xs[i + 1]) / 2) { i++; }
    if (i == 0) goto linear;
    if (i == n - 1) {
        i = n - 2;
        goto linear;
    }
    dx = xs[i + 1] - xs[i - 1];
    d = 2 * x - (xs[i] + xs[i - 1]);
    curve = ((ys[i - 1] + ys[i + 1] - 2 * ys[i]) << 15) / dx;
    frac = ((curve * d + ((ys[i] - ys[i - 1]) << 16)) / dx) * d;
    frac /= 16;
    base = (ys[i - 1] + ys[i]) << 11;
    return frac + base;
linear:
    {
        register s32 dist asm("$4");
        s32 x1 = xs[i + 1];
        register s32 x0 asm("$5") = xs[i];
        s32 slope;
        dx = x1 - x0;
        slope = ((ys[i + 1] - ys[i]) << 16) / dx;
        dist = x - x0;
        return (slope * dist) / 16 + (ys[i] << 12);
    }
}

extern s32 sprite_set_next_slot;

void title_flag_clear(void) {
    sprite_set_next_slot = 0;
}

extern TitleSetSlot title_set_slots[];
/* Registers the sprite sets in data at the next free title_set_slots slots and fixes up their
 * cells' tpage, clut, uv and texture window; returns the first slot's index. */
s32 sprite_sets_register(s32 *data, u16 *clut, u16 tpage, u16 clutDefault, s32 xoff, s32 yoff)
{
    s32 first;
    s32 noClut;
    s32 count, i, j, k;
    s32 groups, cells;
    TitleSetSlot *rec;
    s32 *p;
    TexSpritePrim *prim;
    u32 mode;
    s32 u;
    s32 cell;
    s32 tpLow;
    u16 tpHigh;

    xoff %= 256;
    yoff %= 256;
    p = data;
    count = *p++;
    rec = &title_set_slots[sprite_set_next_slot];
    first = sprite_set_next_slot;
    sprite_set_next_slot += count;
    noClut = clut == NULL;
    for (i = 0; i < count; i++, rec++) {
        if ((rec->present = *p++) == 0) {
            continue;
        }
        rec->sizeA = *p++;
        rec->tableA = p;
        rec->sizeA *= 8;
        p = (s32 *)((u8 *)p + rec->sizeA);
        rec->sizeB = *p++;
        rec->tableB = p;
        rec->sizeB *= 4;
        p = (s32 *)((u8 *)p + rec->sizeB);
        groups = *p++;
        rec->groups = p;
        for (j = 0; j < groups; j++) {
            cells = *p++;
            if (cells == 0) {
                if (j == 0) {
                    rec->groupCount = 0;
                }
                continue;
            }
            rec->groupCount = j + 1;
            *p = *p; /* the original rewrites this word in place */
            p += 3;
            prim = (TexSpritePrim *)p;
            for (k = 0; k < cells; k++, prim++) {
                tpLow = tpage & 0x3F;
                tpHigh = tpage & 0xFFC0;
                if (noClut == 1) {
                    continue;
                }
                mode = prim->mode;
                if (!((mode >> 24) & 2)) {
                    /* an 8x8 cell of a 16-wide sheet: tpage holds the cell index */
                    s32 page;
                    u32 window;

                    cell = prim->tpage;
                    page = cell / 16;
                    u = xoff + (cell - page * 16);
                    window = getTexWindow(u, yoff, 8, 8);
                    prim->tpage = tpHigh | ((tpLow + page) & 0x3F);
                    prim->clut = clut[4];
                    prim->u0 = u;
                    prim->v0 = yoff;
                    prim->u1 = u;
                    prim->v1 = yoff;
                    prim->u2 = u;
                    prim->v2 = yoff;
                    prim->u3 = u;
                    prim->v3 = yoff;
                    mode &= 0xFF000000;
                    window &= 0xFFFFFF;
                    mode |= window;
                    prim->mode = mode;
                } else {
                    /* the window is packed in mode: x 0-4, y 6-10, w-1 12-17, h-1 18-23 */
                    s32 w, h;
                    u32 window;

                    w = ((mode >> 12) & 0x3F) + 1;
                    h = ((mode >> 18) & 0x3F) + 1;
                    window = getTexWindow((s32)((mode & 0x1F) << 3), (s32)(((mode >> 6) & 0x1F) << 3),
                                          w << 3, h << 3);
                    mode &= 0xFF000000;
                    window &= 0xFFFFFF;
                    prim->clut = clut[prim->clut];
                    prim->tpage = clutDefault;
                    mode |= window;
                    prim->mode = mode;
                }
            }
            p = (s32 *)prim;
        }
    }
    return first;
}

extern s32 title_rec_index;
extern s32 title_scale;
extern TitleRecPoolEntry title_rec_pool[4];
void title_rec_pool_init(void) {
    TitleRecPoolEntry *rec;
    s32 i;

    title_rec_index = 0;
    i = 0;
    rec = title_rec_pool;
    do {
        i++;
        rec->pos_x = 0;
        rec->pos_y = 0;
        rec->pos_z = 0;
        rec->unk_30 = 0;
        rec->unk_34 = 0;
        rec->unk_38 = 0;
        rec->unk_40 = 0;
        rec->unk_44 = 0;
        rec->unk_48 = 0;
        rec->angle_x = 0;
        rec->angle_y = 0;
        rec->angle_z = 0;
        rec->unk_60 = 0;
        rec->unk_64 = 0;
        rec->unk_68 = 0;
        rec->unk_70 = 0;
        rec->unk_74 = 0;
        rec->unk_78 = 0;
        rec++;
    } while (i < 4);
    title_scale = 0x1000;
}

extern s32 title_rec_index;

void title_rec_select(s32 arg0) {
    title_rec_index = arg0;
}

extern TitleRecPoolEntry title_rec_pool[4];
/* The entry selected by title_rec_index. */
void *title_rec_current(void) {
    return &title_rec_pool[title_rec_index];
}

void *title_rec_get(s32 index) {
    return &title_rec_pool[index];
}

extern s32 title_scale;
extern Pad3dSoundInfo *title_shared_state_get(void);
void title_scale_set(s32 mode) {
    s32 v;
    Pad3dSoundInfo *p;

    p = title_shared_state_get();
    switch (mode) {
    case 0:
        v = 0x1000;
        title_scale = v;
        break;
    case 1:
        v = p->unk_25;
        if (v == 0) {
            v = 0x10E0;
        } else {
            v = 0xCFB;
        }
        title_scale = v;
        break;
    }
}

extern const s16 rcossin_tbl[][2];
/* Builds the selected rec's rotation matrix Rx * Ry, then Rz * that (angles unk_50/54/58, 20.12 fixed point),
 * scales its first row by title_scale, loads it into the GTE with a zero translation. */
void title_rec_matrix_update(void) {
    TitleMatrix rot;
    TitleRecPoolEntry *rec;
    register TitleMatrix *out asm("$11");
    register u32 sc_y asm("$3");
    register u32 sc_x asm("$3");
    u32 sc_z;
    register s32 temp asm("$5"); /* the Y cosine, then the Z angle */
    register u32 *trig asm("$4");
    register s32 one asm("$7");

    rec = &title_rec_pool[title_rec_index];
    sc_y = *(u32 *)rcossin_tbl[(rec->angle_y >> 12) & 0xFFF];
    one = 0x1000;
    rec->mat.m[0][1] = 0;
    rec->mat.m[1][0] = 0;
    rec->mat.m[1][1] = one;
    rec->mat.m[1][2] = 0;
    rec->mat.m[2][1] = 0;
    {
        s16 neg_sin;
        temp = sc_y >> 16;
        neg_sin = -sc_y;
        rec->mat.m[0][0] = temp;
        rec->mat.m[2][2] = temp;
        temp = rec->angle_z;
        rec->mat.m[0][2] = sc_y;
        rec->mat.m[2][0] = neg_sin;
    }
    sc_x = *(u32 *)rcossin_tbl[(rec->angle_x >> 12) & 0xFFF];
    out = &rec->mat;
    rot.m[0][0] = one;
    rot.m[0][1] = 0;
    rot.m[0][2] = 0;
    rot.m[1][0] = 0;
    rot.m[2][0] = 0;
    {
        register s16 cos asm("$4") = sc_x >> 16;
        s16 neg_sin = -sc_x;
        temp >>= 12;
        rot.m[1][1] = cos;
        rot.m[2][2] = cos;
        trig = (u32 *)rcossin_tbl;
        rot.m[1][2] = neg_sin;
        rot.m[2][1] = sc_x;
    }
    gte_mul_matrix_pinned_ptr(&rot, out, "$10", "$9", "$6");

    sc_z = trig[temp & 0xFFF];
    rot.m[0][2] = 0;
    rot.m[1][2] = 0;
    rot.m[2][0] = 0;
    rot.m[2][1] = 0;
    rot.m[2][2] = one;
    {
        s16 cos = sc_z >> 16;
        s16 neg_sin = -sc_z;
        rot.m[0][0] = cos;
        rot.m[0][1] = neg_sin;
        rot.m[1][0] = sc_z;
        rot.m[1][1] = cos;
    }
    gte_mul_matrix_pinned_ptr(&rot, out, "$6", "$5", "$4");

    rec->mat.m[0][0] = rec->mat.m[0][0] * title_scale / 4096;
    rec->mat.m[0][1] = rec->mat.m[0][1] * title_scale / 4096;
    out->m[0][2] = rec->mat.m[0][2] * title_scale / 4096;
    gte_load_R(out);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    out->t[0] = 0;
    out->t[1] = 0;
    out->t[2] = 0;
}

extern u8 title_row_scroll_task[];
extern u8 D_8010DAB8[];
void *title_item_get(s32 index);
void title_fog_setup(void);
void title_matrix_pool_init(void);
void mat3_set_column(s16 *table, s32 index, s16 x, s16 y, s32 z);
void title_row_scroll(u8 *obj);
void title_items_init(void) {
    u8 *item;
    s32 scale;

    item = title_item_get(0);
    title_fog_setup();
    item += 0x20;
    title_matrix_pool_init();
    mat3_set_column((s16 *)item, 0, 0x800, 0x800, 0);
    mat3_set_column((s16 *)item, 1, 0, 0x800, 0x800);
    mat3_set_column((s16 *)item, 2, 0, 0, 0);

    scale = 0xC00;
    item = (u8 *)title_item_get(1) + 0x20;
    mat3_set_column((s16 *)item, 0, 0xC00, 0xC00, scale);
    mat3_set_column((s16 *)item, 1, 0, 0, 0);
    mat3_set_column((s16 *)item, 2, 0, 0, 0);

    scale = 0x3FFF;
    item = (u8 *)title_item_get(2) + 0x20;
    mat3_set_column((s16 *)item, 0, 0x3FFF, 0x3FFF, scale);
    mat3_set_column((s16 *)item, 1, 0x3FFF, 0x3FFF, 0x1FFF);
    mat3_set_column((s16 *)item, 2, 0, 0, 0);

    task_reset((TitleCtl *)title_row_scroll_task);
    task_set((TitleTaskRec *)title_row_scroll_task, 0, (s32)title_row_scroll, 0, (s32)D_8010DAB8);
}

void *title_item_get(s32 index);
void mat3_set_row(s16 *out, s32 index, s32 b, s32 a);
void title_row_scroll(u8 *obj) {
    s16 *slot = *(s16 **)(obj + 0x14);
    void *item = title_item_get(0);

    switch (*(s16 *)(obj + 0x22)) {
    case 0:
        *slot = 0x200;
        *(s16 *)(obj + 0x22) += 1;
        break;
    case 1:
        break;
    default:
        return;
    }
    mat3_set_row(item, 0, *slot, 0);
    mat3_set_row(item, 1, *slot + 0x800, 0);
    *slot -= 0x10;
}

void title_fog_setup(void) {
    SetFogFar(0x4000, 0x100);
    SetFarColor(0, 0, 0);
    SetBackColor(0x60, 0x60, 0x60);
}

extern s32 title_matrix_index;

void title_item_select(s32 arg0) {
    title_matrix_index = arg0;
}

extern u8 title_matrix_pool[];
void *title_item_current(void) {
    return &title_matrix_pool[title_matrix_index << 6];
}

void *title_item_get(s32 index) {
    return title_matrix_pool + (index << 6);
}

void mat3_set_row(s16 *out, s32 index, s32 b, s32 a);
void mat3_set_column(s16 *table, s32 index, s16 x, s16 y, s32 z);
void title_matrix_pool_init(void) {
    s32 i;
    u8 *cur;

    cur = title_matrix_pool;
    i = 0;
    title_matrix_index = 0;
    do {
        mat3_set_row((s16 *)cur, 0, 0, 0);
        mat3_set_row((s16 *)cur, 1, 0, 0);
        mat3_set_row((s16 *)cur, 2, 0, 0);
        mat3_set_column((s16 *)(cur + 0x20), 0, 0x1000, 0x1000, 0x1000);
        mat3_set_column((s16 *)(cur + 0x20), 1, 0x1000, 0x1000, 0x1000);
        mat3_set_column((s16 *)(cur + 0x20), 2, 0x1000, 0x1000, 0x1000);
        i += 1;
        cur += 0x40;
    } while (i < 4);
}

extern const s16 rcossin_tbl[][2]; /* (x, y) pairs, 0x1000 of them */
extern const char D_801085E6[];
/* Writes three s16 values at out[index * 3]: the x and y products of
   entries a and b, and the negated, halved x of entry a. */
void mat3_set_row(s16 *out, s32 index, s32 b, s32 a) {
    s32 offA = (a & 0xFFF) * 4;
    s32 offB = (b & 0xFFF) * 4;
    s16 yA = *(s16 *)(D_801085E6 + offA);
    s16 xB = *(s16 *)((char *)rcossin_tbl + offB);
    s32 prodX = yA * xB;
    s16 yB = *(s16 *)(D_801085E6 + offB);
    s32 prodY = yA * yB;
    s32 xA;
    out = out + index * 3;
    xA = *(s16 *)((char *)rcossin_tbl + offA);
    out[0] = prodX >> 14;
    out[1] = -xA >> 2;
    out[2] = prodY >> 14;
}

void vec3s16_set_quarter(Vec3s16 *table, s32 index, s32 x, s32 y, s32 z) {
    Vec3s16 *entry = &table[index];

    entry->x = x >> 2;
    entry->y = y >> 2;
    entry->z = z >> 2;
}

/* Stores x, y and z as halfwords at byte offsets 0, 6 and 12 from
   table + index * 2 (index counts halfwords, not bytes). */
void mat3_set_column(s16 *table, s32 index, s16 x, s16 y, s32 z) {
    s32 offset = index * 2;
    s16 *dst = (s16 *) (offset + (s32) table);

    dst[0] = x;
    dst[3] = y;
    dst[6] = (s16) z;
}

extern s32 rec_queue_count;

void rec_queue_reset(void) {
    rec_queue_count = 0;
}

extern TitleRecQueueEntry rec_queue[];
s32 rec_queue_push(void *src, s32 tag) {
    TitleRecQueueEntry *rec;

    if (rec_queue_count >= 0x100) {
        return 0;
    }
    rec = &rec_queue[rec_queue_count];
    rec_queue_count++;
    rec->data = *(Unaligned8 *) src;
    rec->tag = tag;
    return 1;
}

s32 title_load_image(ClutRect *rect, u16 *data);
void rec_queue_flush(void) {
    s32 unused[2];
    TitleRecQueueEntry *rec;
    s32 i;

    rec = rec_queue;
    i = 0;
    if (rec_queue_count > 0) {
        do {
            title_draw_sync(0);
            {
                register TitleRecQueueEntry *arg asm("$4") = rec;
                do { i++; } while (0);
                title_load_image((ClutRect *) arg, (u16 *) rec->tag);
            }
            rec++;
        } while (i < rec_queue_count);
    }
    title_draw_sync(0);
}

/* Queues a sprite's pixels for upload at (x, y): the header holds big-endian
   width (in 8-bit pixels, halved to VRAM units) and height at bytes 4-7, the
   pixels follow at byte 8. Returns the 8-bit, semi-transparent tpage word. */
s32 sprite_load_tpage_be(u8 *sprite, s32 x, s32 y) {
    SpriteRect rect;
    s32 w_hi;
    s32 w_lo;
    s32 h_hi;
    s32 h_lo;
    s32 y_bits;
    s32 x_bits;

    w_hi = sprite[4];
    w_lo = sprite[5];
    h_hi = sprite[6];
    h_lo = sprite[7];
    rect.x = x;
    rect.y = y;
    rect.w = ((w_hi << 8) | w_lo) >> 1;
    rect.h = (h_hi << 8) | h_lo;
    sprite += 8;
    rec_queue_push(&rect, (s32) sprite);
    y_bits = (y & 0x100) >> 4;
    x_bits = ((x & 0x3FF) >> 6) | 0xA0;
    return y_bits | x_bits | ((y & 0x200) << 2);
}

/* Reads a 2-halfword header (w, h) from the sprite data, passes the rect and the
   remaining data to rec_queue_push, and returns x/y bits packed into one word. */
s32 sprite_load_tpage(void *sprite, s32 x, s32 y) {
    SpriteRect rect;
    s32 header_w;
    s32 header_h;
    s32 y_bits;
    s32 x_bits;

    header_w = *(s16 *)sprite;
    sprite = (s16 *)sprite + 1;
    header_h = *(s16 *)sprite;
    sprite = (s16 *)sprite + 1;
    rect.x = x;
    rect.y = y;
    rect.w = header_w / 4;
    rect.h = header_h;
    rec_queue_push(&rect, (s32) sprite);
    y_bits = (y & 0x100) >> 4;
    x_bits = ((x & 0x3FF) >> 6) | 0x20;
    return y_bits | x_bits | ((y & 0x200) << 2);
}

void clut_fade_load(s32 x, s32 y, u16 *src, s32 stp, s32 mode, s32 count);
s32 clut_load(void *sprite, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    s32 shifted_a1;

    shifted_a1 = a1 + 0x300;
    clut_fade_load(shifted_a1, a2, sprite, a3, a4, a5);
    return ((a2 << 6) | ((shifted_a1 >> 4) & 0x3F)) & 0xFFFF;
}

s32 title_load_image(ClutRect *rect, u16 *data);
void clut_load_set(s32 a0, s32 a1, s32 a2, s16 *out_a, s32 x, s32 y, s16 *out_b, s32 a7) {
    u16 clut[4];
    ClutRect rect;
    s32 i;
    s32 base;
    s32 y_bits;
    s32 x_bits;

    base = a1 + 0x300;
    clut_fade_load(base, a2, (u16 *)a0, 1, 1, a7);
    *out_a = (a2 << 6) | ((base >> 4) & 0x3F);
    rect.x = x;
    rect.y = y;
    rect.w = 4;
    rect.h = 1;
    for (i = 0; i < 4; i++) {
        s32 idx = i * 4;
        clut[i] = (i * 0x4000 + 0x3000) | (i * 0x400 + 0x200) | (i * 0x40 + 0x10) | idx;
    }
    title_draw_sync(0);
    title_load_image(&rect, clut);
    y_bits = (y & 0x100) >> 4;
    x_bits = ((x & 0x3FF) >> 6) | 0x20;
    *out_b = y_bits | x_bits | ((y & 0x200) << 2);
}

extern u16 clut_fade_buf[];
/* Writes count CLUT entries from src to clut_fade_buf, fading each colour from
   src towards to_r/g/b over steps uploads (one row each); entries that are 0
   (mode 1) or black (mode 2) stay transparent. */
void clut_fade_load(s32 x, s32 y, u16 *src, s32 stp, s32 mode, s32 count) {
    ClutRect rect;
    s32 c;
    s32 steps;
    s32 round;
    s32 step;
    s32 to_r;
    s32 to_g;
    s32 to_b;
    s32 i;
    s32 mask;
    s32 r;
    s32 g;
    s32 b;

    steps = 1;
    round = 0;
    step = 0;
    to_r = 0;
    to_g = 0;
    to_b = 0;
    rect.x = x;
    rect.y = y;
    rect.h = 1;
    rect.w = count;
    do {
        for (i = 0; i < count; i++) {
            c = src[i];
            mask = c & 0x8000;
            r = c & 0x1F;
            g = (c >> 5) & 0x1F;
            b = (c >> 10) & 0x1F;
            if (c == 0 && mode == 1) {
                clut_fade_buf[i] = 0;
            } else if ((c & 0x7FFF) == 0 && mode == 2) {
                clut_fade_buf[i] = 0;
            } else {
                r = (to_r * step + r * (steps - step) + round) / steps & 0x1F;
                g = (to_g * step + g * (steps - step) + round) / steps & 0x1F;
                b = (to_b * step + b * (steps - step) + round) / steps & 0x1F;
                clut_fade_buf[i] = mask | r | (g << 5) | (b << 10) | (stp << 15);
            }
        }
        title_draw_sync(0);
        title_load_image(&rect, clut_fade_buf);
        step++;
        rect.y++;
    } while (step < steps);
}

/* Callbacks and task nodes used by title_ctls_init, defined further down. */
extern u8 title_ctl_reset_task[];
extern u8 title_fade_task[];
extern u8 title_ramp_task[];
s32 title_ctl_reset(TitleCtlOuter *ctl);
void title_fade_reset(TitleFadeTask *task);
void title_ramp_update(TitleFadeTask *task);
void *title_rec_get(s32 index);

extern s32 title_ramp_key_count;
extern s32 title_ramp_keys_a;
extern s32 title_ramp_a_key1;
extern s32 title_ramp_a_key2;
extern s32 title_ramp_a_key3;
extern s32 title_ramp_a_key4;
extern s32 title_ramp_a_key5;
extern s32 title_ramp_keys_b;
extern s32 title_ramp_b_key1;
extern s32 title_ramp_b_y2;
extern s32 title_ramp_b_y3;
extern s32 title_ramp_b_y4;
extern s32 title_ramp_b_y5;
extern s32 title_ramp_knots;
void title_ctls_init(void) {
    s32 i;
    s32 *out;
    s32 count;
    s32 divisor;

    task_reset((TitleCtl *)title_ctl_reset_task);
    task_set((TitleTaskRec *)title_ctl_reset_task, (s32)title_ctl_reset, 0, 0, (s32)title_rec_get(0));
    task_reset((TitleCtl *)title_fade_task);
    task_set((TitleTaskRec *)title_fade_task, (s32)title_fade_reset, 0, 0, (s32)title_rec_get(0));
    task_reset((TitleCtl *)title_ramp_task);
    task_set((TitleTaskRec *)title_ramp_task, 0, (s32)title_ramp_update, 0, (s32)title_rec_get(0));

    title_ramp_key_count = 6;

    i = 0;
    count = 6;
    divisor = 5;
    out = &title_ramp_knots;
    title_ramp_keys_a = -0x2000;
    title_ramp_a_key1 = -0x1000;
    title_ramp_a_key2 = -0x400;
    title_ramp_a_key3 = 0x200;
    title_ramp_a_key4 = -0x20;
    title_ramp_keys_b = -0xA00;
    title_ramp_b_key1 = -0x600;
    title_ramp_b_y2 = -0x200;
    title_ramp_a_key5 = 0;
    title_ramp_b_y3 = 0x100;
    title_ramp_b_y4 = 0;
    title_ramp_b_y5 = 0;

    for (i = 0; i < count; i++) {
        *out++ = (i << 12) / divisor;
    }
}

extern s32 title_ramp_keys_a;
extern s32 title_ramp_keys_b;
s32 title_ctl_reset(TitleCtlOuter *ctl) {
    TitleCtlInner *inner = ctl->inner;

    inner->unk_20 = 0;
    inner->unk_24 = 0;
    inner->unk_28 = ((Word8010 *)&title_ramp_keys_a)->v << 12;
    inner->unk_50 = 0;
    inner->unk_54 = 0;
    inner->unk_58 = ((Word8010 *)&title_ramp_keys_b)->v << 12;
    return title_flag_test_set(ctl);
}

void title_fade_reset(TitleFadeTask *task) {
    Rec800A34E0 *rec = (Rec800A34E0 *)task->fade;

    rec->unk_20 = 0;
    rec->unk_24 = 0;
    rec->unk_28 = 0;
    rec->unk_50 = 0;
    rec->unk_54 = 0;
    rec->unk_58 = 0;
    title_flag_test_set(task);
}

extern s32 title_ramp_key_count;
extern s32 title_ramp_keys_a;
extern s32 title_ramp_keys_b;
extern s32 title_ramp_knots;
extern s32 title_ramp_progress;
s32 title_track_sample(s32 x, s32 n, s32 *xs, u8 *table_entry);
/* Ramp task: phase 0 clears the record and the progress counter, phase 1 stores
 * two interpolated levels (0x28, 0x58) and advances progress by 0x19 per frame;
 * once progress passes 0x1000 it returns control to title_flag_test_set. */
void title_ramp_update(TitleFadeTask *task) {
    TitleRampRec *rec = (TitleRampRec *)task->fade;

    switch (task->phase) {
    case 0:
        rec->unk_20 = 0;
        rec->unk_24 = 0;
        title_ramp_progress = 0;
        task->phase++;
        break;
    case 1:
        rec->unk_28 = title_track_sample(title_ramp_progress, title_ramp_key_count, &title_ramp_knots, (u8 *)&title_ramp_keys_a);
        rec->unk_58 = title_track_sample(title_ramp_progress, title_ramp_key_count, &title_ramp_knots, (u8 *)&title_ramp_keys_b);
        title_ramp_progress += 0x19;
        if (title_ramp_progress > 0x1000) {
            title_flag_test_set(task);
        }
        break;
    }
}

void title_scratch_init(void) {
    *(s16 *)0x1F8003F6 = -1;
    *(s16 *)0x1F8003F4 = 0;
    *(s16 *)0x1F8003F8 = 1;
    *(s16 *)0x1F8003FA = 1;
    *(s16 *)0x1F8003FC = 0;
}

void title_seq_flag_set(s16 arg0) {
    *(s16 *)0x1F8003FA = arg0;
}

void title_seq_depth_set(s16 arg0) {
    *(s16 *)0x1F8003F6 = arg0;
}

void title_seq_enable_set(s16 arg0) {
    *(s16 *)0x1F8003F8 = arg0;
}

s32 title_poly_depth(s32 vxy, s32 vz, s32 radius);
void title_draw_quad(TitleQuad *quad, s32 a, s32 b, s32 c, s32 fade);
/* Draws model model_index of the table at title_set_slots at pos (relative to the selected rec's position, 20.12),
 * rotated by rot (x, y, z angles: R = rec * Rz * Rx * Ry, the item's light matrix rotated with it) or, with rot
 * NULL, unrotated with the offset added to each group's centre and quad. Each group is depth-tested by its centre
 * and radius (title_poly_depth: -1 = not drawn); its quads go out last to first through title_draw_quad with
 * fade, into OT entry `level`, or with flat_shade set into consecutive entries from 0x78 - flat_shade * 4. */
void title_model_draw(s16 *pos, s16 *rot, s32 model_index, s32 fade) {
    s32 group;
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    TitleSetSlot *model;
    s32 x, y, z;
    TitleDrawCtx *ctx;
    TitleRecPoolEntry *rec;
    TitleLightMatrices *item;
    s32 *data;
    s16 *centre;
    TitleMatrix rm;
    TitleMatrix tm;
    TitleMatrix *m;
    TitleMatrix *t;
    s32 angles;
    s32 angle_z;
    s32 ty;
    u32 sy, sx, sz;
    s32 count;
    s32 radius;
    s32 vxy, vz;
    s32 shade;
    s32 level;
    s32 i;
    TitleQuad *quad;

    m = &rm;
    t = &tm;
    x = pos[0];
    y = pos[1];
    z = pos[2];
    model = &title_set_slots[model_index];
    ctx = title_draw_ctx_ptr;
    rec = title_rec_current();
    item = title_item_current();
    x -= rec->pos_x >> 12;
    y -= rec->pos_y >> 12;
    z -= rec->pos_z >> 12;
    sc->verts = model->tableA;
    data = model->groups;
    title_rec_matrix_update();
    gte_load_LC_pair(&item->colour);
    sc->colours = model->tableB;
    if (rot != NULL) {
        /* the translation: the rec's rotation applied to the offset. angles and angle_z carry MAC1 and MAC3
         * first (one register each in the original). */
        gte_set(VXY0, (x & 0xFFFF) | (y << 16));
        gte_set(VZ0, z);
        gte_rtv0tr();
        gte_get(MAC1, angles);
        gte_get(MAC2, ty);
        gte_get(MAC3, angle_z);
        tm.t[0] = angles;
        tm.t[1] = ty;
        tm.t[2] = angle_z;
        angles = *(s32 *)rot; /* x and y angles in one word */
        angle_z = rot[2];
        sy = *(u32 *)rcossin_tbl[(angles >> 16) & 0xFFF];
        rm.m[0][1] = 0;
        rm.m[1][0] = 0;
        rm.m[1][1] = 0x1000;
        rm.m[1][2] = 0;
        rm.m[2][1] = 0;
        {
            s16 cos = sy >> 16;
            s16 neg_sin = -sy;
            rm.m[0][2] = sy;
            rm.m[0][0] = cos;
            rm.m[2][0] = neg_sin;
            rm.m[2][2] = cos;
        }
        sx = *(u32 *)rcossin_tbl[angles & 0xFFF];
        tm.m[0][0] = 0x1000;
        tm.m[0][1] = 0;
        tm.m[0][2] = 0;
        tm.m[1][0] = 0;
        tm.m[1][1] = sx >> 16;
        tm.m[1][2] = -sx;
        tm.m[2][0] = 0;
        tm.m[2][1] = sx;
        tm.m[2][2] = sx >> 16;
        gte_load_R_pair(t);
        gte_mul_rot_columns(m, m);
        sz = *(u32 *)rcossin_tbl[angle_z & 0xFFF];
        tm.m[0][0] = sz >> 16;
        tm.m[0][1] = -sz;
        tm.m[0][2] = 0;
        tm.m[1][0] = sz;
        tm.m[1][1] = sz >> 16;
        tm.m[1][2] = 0;
        tm.m[2][0] = 0;
        tm.m[2][1] = 0;
        tm.m[2][2] = 0x1000;
        gte_load_R_pair(t);
        gte_mul_rot_columns(m, m);
        gte_set_ctrl(TRX, 0);
        gte_set_ctrl(TRY, 0);
        gte_set_ctrl(TRZ, 0);
        gte_load_R_pair(&item->dir);
        gte_mul_rot_columns(m, t);
        gte_load_L_pair(t);
        gte_load_R_pair(&rec->mat);
        gte_mul_rot_columns(m, t);
        gte_load_R_pair(t);
        gte_load_TR_last_base(t->t);
    }
    for (group = 0; group < model->groupCount; group++) {
        count = data[0];
        radius = data[1];
        data += 2;
        centre = (s16 *)data;
        data += 2;
        /* keeps reorg from moving `data += 2` into the branch's delay slot (the original's holds the next lui) */
        __asm__("");
        vxy = *(s32 *)centre;
        vz = centre[2];
        if (rot == NULL) {
            vxy = (vxy & 0xFFFEFFFF) + ((x & 0xFFFF) | (y << 16));
            vz += z;
        }
        shade = sc->flat_shade;
        level = title_poly_depth(vxy, vz, radius);
        if (level != -1) {
            if (shade == 0) {
                sc->ot = (u32 *)ctx->ot_base + level;
            } else {
                shade *= 4;
            }
            quad = (TitleQuad *)data + count - 1;
            i = 0;
            while (quad != (TitleQuad *)data - 1) {
                if (shade != 0) {
                    /* OT entry 0x78 - flat_shade * 4 + i */
                    sc->ot = (u32 *)(ctx->ot_base - (shade * 4 - 0x1E0) + i * 4);
                    i++;
                }
                if (rot != NULL) {
                    title_draw_quad(quad, 0, 0, 0, fade);
                } else {
                    title_draw_quad(quad, x, y, z, fade);
                }
                quad--;
            }
        }
        data = (s32 *)((TitleQuad *)data + count);
    }
    /* one more reference: global-alloc then gives group s4 before data, as in the original */
    FAKE_USE(group);
}

extern s16 D_800BDB0C[] __asm__(".L800BDB0C");
s32 title_poly_depth(s32 vxy, s32 vz, s32 radius)
{
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    s32 depth;
    s32 ir0;
    s32 x;
    s32 y;
    s32 half;
    s32 sq1;
    s32 sq2;
    s32 sq3;
    s32 dist;
    s32 lzcr;
    s32 half_shift;
    s32 exp_shift;
    u32 idx;
    s16 *table;
    s32 level;

    gte_set(VXY0, vxy);
    gte_set(VZ0, vz);
    half = radius * 3 / 2;
    gte_rtps_b();
    gte_get(MAC3, depth);
    gte_get(IR0, ir0);
    if (depth + radius < 0x80) {
        return -1;
    }
    gte_get(MAC1, x);
    gte_get(MAC2, y);
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, depth);
    gte_nop();
    sc->depth_cue = ir0;
    gte_sqr0_b();
    gte_get(MAC1, sq1);
    gte_get(MAC2, sq2);
    gte_get(MAC3, sq3);
    dist = sq1 + sq2 + sq3;
    idx = ~1;
    if (dist != 0) {
        gte_set(LZCS, dist);
        table = D_800BDB0C;
        gte_get(LZCR, lzcr);
        half_shift = 31 - lzcr;
        lzcr &= idx;
        exp_shift = lzcr - 24;
        idx = dist << exp_shift;
        if (exp_shift < 0) {
            idx = (u32)dist >> -exp_shift;
        }
        dist = table[idx];
        half_shift >>= 1;
        dist <<= half_shift;
        dist = (u32)dist >> 12;
    }
    if (dist - radius > 0x2000) {
        return -1;
    }
    if ((x >= 0 ? x : -x) >= depth * 160 / 256 + half) {
        return -1;
    }
    if ((y >= 0 ? y : -y) >= depth * 120 / 256 + half) {
        return -1;
    }
    if (sc->seq_depth != -1) {
        return sc->seq_depth;
    }
    level = dist / 64;
    if (level >= 0x7F) {
        level = 0x7F;
    }
    return level;
}

/* Transforms `count` indexed model vertices (offset by dx, dy, dz) into `out`,
   sets each one's clip bits; returns 0 when every vertex shares an off-screen
   bit, 1 when unk_20 is 0, else the sign of the triangle out[0..2]'s winding. */
s32 title_transform_verts(s16 *idx, TitleVertex *out, s32 dx, s32 dy, s32 dz, s32 count) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    s16 mac[3][2];
    s16 (*m)[2];
    TitleVertex *v, *b, *c;
    s16 *end;
    s16 *p, *clip;
    s16 *verts;
    s32 i;
    s32 x, y, z, nclip;
    s32 sxy, flags, mx, my;
    s32 any, all, ret;
    s32 z0, y1, y0, z1, x0, x1;

    v = out;
    m = mac;
    any = 0;
    all = 0xFFFF;
    verts = sc->verts;
    clip = &out->clip;
    i = *idx;
    end = idx + count;
    do {
        p = &verts[i];
        x = *(s32 *)p;
        z = p[2];
        y = x >> 16;
        x = (s16)x;
        x += dx;
        y += dy;
        z += dz;
        x = (x & 0xFFFF) | (y << 16);
        __asm__ volatile("");
        gte_set(VXY0, x);
        gte_set(VZ0, z);
        *(s32 *)&v->x = x;
        clip[-5] = z;
        gte_rtps_b();
        idx++;
        i = *idx;
        gte_get_ctrl(FLAG, flags);
        gte_get(SXY2, sxy);
        gte_store(MAC3, v, 0xC);
        v->sxy = sxy;
        gte_get(MAC1, mx);
        gte_get(MAC2, my);
        (*m)[0] = mx;
        (*m)[1] = my;
        __asm__ volatile("");
        x = (s16)sxy;
        y = sxy >> 16;
        flags = (flags >> 17) & 1;
        flags |= (x >> 31) & 2;
        flags |= (sxy >> 31) & 4;
        if (x >= 0x140) {
            flags |= 8;
        }
        if (y >= 0xF0) {
            flags |= 0x10;
        }
        *clip = flags;
        any |= flags;
        all &= flags;
        clip += 10;
        v++;
        m++;
    } while (idx != end);
    ret = 0;
    if (all == 0) {
        b = &out[1];
        if (sc->unk_20 == 0) {
            ret = 1;
        } else {
            c = &out[2];
            if (!(any & 1)) {
                gte_load(SXY0, out, 8);
                gte_load(SXY1, c, 8);
                gte_load(SXY2, b, 8);
                gte_nclip();
                gte_get(MAC0, nclip);
                gte_nop();
                ret = (u32)nclip >> 31;
            } else {
                z0 = out[0].sz >> 3;
                y1 = mac[1][1] >> 3;
                y0 = mac[0][1] >> 3;
                z1 = b->sz >> 3;
                x0 = mac[0][0] >> 3;
                x1 = mac[1][0] >> 3;
                ret = (u32)((mac[2][0] >> 3) * (z0 * y1 - y0 * z1) + (mac[2][1] >> 3) * (x0 * z1 - z0 * x1) +
                            (out[2].sz >> 3) * (y0 * x1 - x0 * y1)) >> 31;
            }
        }
    }
    return ret;
}

/* Runs ncds over count packed colours picked by idx, storing each result at out + 0x10 (0x14 stride). */
void title_light_colours(s16 *idx, u8 *out, s32 count) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    u8 *colours;
    s16 *end;
    u32 packed;

    FAKE_OPAQUE(sc);
    colours = sc->colours;

    packed = *(u32 *)(colours + *idx);
    do { } while (0);
    gte_set(VXY0, (packed & 0xFF00FF) << 8);
    gte_set(VZ0, packed & 0xFF00);
    end = idx + count;
    idx++;
    gte_ncds_b();
    do {
        packed = *(u32 *)(colours + *idx);
        gte_store(RGB2, out, 0x10);
        gte_set(VXY0, (packed & 0xFF00FF) << 8);
        gte_set(VZ0, packed & 0xFF00);
        idx++;
        out += 0x14;
        gte_ncds_b();
    } while (idx != end);
    gte_store(RGB2, out, 0x10);
}

void title_tri_subdivide(TitleVertex *a, TitleVertex *b, TitleVertex *c, s32 depth);
/* Draws a textured quad (or triangle when code's top nibble is 3): sets the corner UVs,
 * depth-cues the base colour by fade, lights or fills the vertex colours, subdivides it
 * and links a texture-window primitive into the ordering table. */
void title_draw_quad(TitleQuad *quad, s32 a, s32 b, s32 c, s32 fade) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    TitleVertex v[4];
    u32 code;
    u32 count;
    u32 i;
    u32 colour;
    register s32 *uv asm("$3");
    s32 uv01, uv23;
    TitleVertex *p;

    code = quad->code;
    count = code >> 28;
    if (title_transform_verts(quad->rect, v, a, b, c, count) != 0) {
        uv = (s32 *)quad->uv;
        p = v;
        FAKE_OPAQUE(uv);
        FAKE_OPAQUE(p);
        uv01 = uv[0];
        uv23 = uv[1];
        ((TitleFt3Vert *)&p[0])->uv = uv01;
        ((TitleFt3Vert *)&p[1])->uv = uv01 >> 16;
        do { } while (0);
        ((TitleFt3Vert *)&p[2])->uv = uv23;
        ((TitleFt3Vert *)&p[3])->uv = uv23 >> 16;
        if ((s16)sc->semi_trans_ok == 1) {
            colour = ((code & 0x8000000) >> 2) | 0x808080;
        } else {
            colour = 0x808080;
        }
        gte_set(RGB, colour);
        if (fade > 0) {
            gte_set(IR0, 0x1000 - fade);
        } else {
            gte_set(IR0, fade + 0x1000);
        }
        gte_dpcs_b();
        colour = *(u32 *)&quad->clut;
        sc->clut = colour & 0xFFFF0000;
        sc->tpage = colour << 16;
        gte_get(RGB2, colour);
        if (fade > 0) {
            gte_set(RGB, colour);
            gte_load(IR0, sc, 0x18); /* sc->depth_cue */
            title_light_colours(quad->unk_08, (u8 *)v, count);
        } else {
            p = v;
            for (i = 0; i < count; i++) {
                gte_store(RGB2, p, 0x10);
                p++;
            }
        }
        if (count == 3) {
            title_tri_subdivide(&v[0], &v[1], &v[2], 2);
        } else {
            title_tri_subdivide(&v[0], &v[1], &v[3], 2);
            title_tri_subdivide(&v[0], &v[3], &v[2], 2);
        }
        colour = (u32)sc->ot;
        SCHED_BARRIER();
        colour = *(u32 *)colour | 0x2000000;
        *(u32 *)(scratch_top + 0) = colour;
        *(s32 *)(scratch_top + 8) = 0;
        *sc->ot = (u32)scratch_top & 0xFFFFFF;
        *(u32 *)(scratch_top + 4) = (code & 0xFFFFFF) | 0xE2000000;
        scratch_top += 0xC;
    }
}

s32 title_spot_is_far(TitleSpot *a, TitleSpot *b) {
    s32 dx;
    s32 dy;
    s32 d;
    s32 ay = a->y;
    s32 by = b->y;

    dx = a->x - b->x;
    if (dx < 0) {
        dx = -dx;
    }
    d = ay - by;
    if (d >= 0) {
        dy = d;
    } else {
        d = -d;
        FAKE_OPAQUE(d);
        dy = d;
    }
    if (dx >= dy) {
        dy = dx;
    }
    return dy >= 0x55;
}

void title_point_clip_flags(TitleVertex *arg) {
    TitleVertex *p = arg;
    register s32 sxy __asm__("a0");
    s32 flag, flags, y;


    gte_get(SXY2, sxy);
    gte_get_ctrl(FLAG, flag);
    gte_store(MAC3, p, 0xC);
    p->sxy = sxy;
    flags = (flag >> 17) & 1;
    flags |= ((s16)sxy >> 31) & 2;
    flags |= (sxy >> 31) & 4;
    y = sxy >> 16;
    if ((s16)sxy >= 0x140) {
        flags |= 8;
    }
    if (y >= 0xF0) {
        flags |= 0x10;
    }
    p->clip = flags;
}

void title_vertex_midpoint(TitleVertex *out, TitleVertex *a, TitleVertex *b)
{
    s32 p, q, r, sum;

    p = a->x;
    q = b->x;
    r = a->y;
    out->x = (p + q) >> 1;
    p = b->y;
    q = a->z;
    out->y = (p + r) >> 1;
    p = b->z;
    r = a->u;
    out->z = (p + q) >> 1;
    p = b->u;
    q = a->v;
    sum = r + p;
    r = b->v;
    out->u = sum >> 1;
    p = q + r;
    r = 0xFEFEFE;
    out->v = p >> 1;
    p = a->rgb & r;
    q = b->rgb & r;
    r = ((u8 *)&a->rgb)[3];
    out->rgb = (p + q) >> 1;
    ((u8 *)&out->rgb)[3] = r;
}

/* Builds a gouraud textured triangle (POLY_GT3, 0x28 bytes) at $gp and links it into the current OT entry. */
void title_poly_gt3_add(TitleFt3Vert *p0, TitleFt3Vert *p1, TitleFt3Vert *p2) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    u32 *ot;
    u32 mask;
    u32 word, other, uv2;

    FAKE_OPAQUE(sc);
    ot = sc->ot;
    do { } while (0);
    mask = 0xFFFFFF;
    *(u32 *)(scratch_top + 0) = *ot | 0x9000000;
    *ot = (u32)scratch_top & mask;
    word = p0->xy;
    other = p2->xy;
    *(s32 *)(scratch_top + 8) = word;
    *(s32 *)(scratch_top + 0x14) = other;
    word = p1->xy;
    other = sc->clut;
    *(s32 *)(scratch_top + 0x20) = word;
    word = (u16)p0->uv;
    uv2 = (u16)p2->uv;
    word = word | other;
    other = sc->tpage;
    *(s32 *)(scratch_top + 0xC) = word;
    other = other | uv2;
    *(s32 *)(scratch_top + 0x18) = other;
    do { } while (0);
    word = p1->uv;
    other = p0->rgb;
    *(s16 *)(scratch_top + 0x24) = word;
    do { } while (0);
    *(s32 *)(scratch_top + 4) = other | 0x34000000;
    word = p1->rgb;
    other = p2->rgb;
    *(s32 *)(scratch_top + 0x1C) = word;
    *(s32 *)(scratch_top + 0x10) = other;
    scratch_top += 0x28;
}

/* Builds a flat textured triangle (POLY_FT3, 0x20 bytes) at $gp and links it into the current OT entry. */
void title_poly_ft3_add(TitleFt3Vert *p0, TitleFt3Vert *p1, TitleFt3Vert *p2) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    u32 *ot;
    u32 mask;
    u32 word, other, uv2;

    FAKE_OPAQUE(sc);
    ot = sc->ot;
    do { } while (0);
    mask = 0xFFFFFF;
    *(u32 *)(scratch_top + 0) = *ot | 0x7000000;
    *ot = (u32)scratch_top & mask;
    word = p0->xy;
    other = p2->xy;
    *(s32 *)(scratch_top + 8) = word;
    *(s32 *)(scratch_top + 0x10) = other;
    word = p1->xy;
    other = sc->clut;
    *(s32 *)(scratch_top + 0x18) = word;
    word = (u16)p0->uv;
    uv2 = (u16)p2->uv;
    word = word | other;
    other = sc->tpage;
    *(s32 *)(scratch_top + 0xC) = word;
    other = other | uv2;
    *(s32 *)(scratch_top + 0x14) = other;
    do { } while (0);
    word = p1->uv;
    other = p0->rgb;
    *(s16 *)(scratch_top + 0x1C) = word;
    do { } while (0);
    *(s32 *)(scratch_top + 4) = other | 0x24000000;
    scratch_top += 0x20;
}

/* All three vertices off the same screen edge (read as s32: the original's lh) */
#define TRI_CLIPPED(p, q, r) ({ s32 p_ = (p)->clip, q_ = (q)->clip, r_ = (r)->clip; p_ & q_ & r_; })

/* Draws triangle a b c, first splitting each edge longer than 0x54 pixels at its midpoint (projected and
 * clip-tested) up to depth times; sub-triangles entirely off one screen edge are dropped. */
void title_tri_subdivide(TitleVertex *a, TitleVertex *b, TitleVertex *c, s32 depth) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    TitleVertex mid[3];
    TitleVertex *m;
    TitleVertex *ab, *bc, *ca;
    s32 split;

    FAKE_OPAQUE(sc);
    depth--;
    if (depth >= 0) {
        split = 0;
        m = mid;
        if (title_spot_is_far((TitleSpot *)a, (TitleSpot *)b) == 1) {
            title_vertex_midpoint(m, a, b);
            gte_ldv0(m);
            split = 1;
            ab = m;
            gte_rtps_b();
            title_point_clip_flags(ab);
        } else {
            ab = b;
        }
        m++;
        if (title_spot_is_far((TitleSpot *)b, (TitleSpot *)c) == 1) {
            title_vertex_midpoint(m, b, c);
            gte_ldv0(m);
            split |= 1;
            bc = m;
            gte_rtps_b();
            title_point_clip_flags(bc);
        } else {
            bc = c;
        }
        m++;
        if (title_spot_is_far((TitleSpot *)c, (TitleSpot *)a) == 1) {
            ca = m;
            title_vertex_midpoint(ca, c, a);
            gte_ldv0(ca);
            split |= 1;
            gte_rtps_b();
            title_point_clip_flags(ca);
        } else {
            ca = a;
        }
        if (split) {
            goto subdivide;
        }
    }
    {
        if (sc->flat_shade) {
            title_poly_ft3_add((TitleFt3Vert *)a, (TitleFt3Vert *)b, (TitleFt3Vert *)c);
        } else {
            title_poly_gt3_add((TitleFt3Vert *)a, (TitleFt3Vert *)b, (TitleFt3Vert *)c);
        }
        return;
    }
subdivide:
    if (a != ca && TRI_CLIPPED(a, ab, ca) == 0) {
        title_tri_subdivide(a, ab, ca, depth);
    }
    if (b != ab && TRI_CLIPPED(b, bc, ab) == 0) {
        title_tri_subdivide(b, bc, ab, depth);
    }
    if (c != bc && TRI_CLIPPED(c, ca, bc) == 0) {
        title_tri_subdivide(c, ca, bc, depth);
    }
    if (TRI_CLIPPED(ab, bc, ca) == 0) {
        title_tri_subdivide(ab, bc, ca, depth);
    }
}

void title_gradient_fill(void);
void title_gradient_init(void) {
    title_gradient_fill();
}

extern u8 title_gradient_table[];
/* Fills 65 4-byte entries of title_gradient_table: three bytes ramp 0,4,..,252 then cap at 0xFF, fourth byte 0. */
void title_gradient_fill(void) {
    s32 i;
    s32 value;
    u8 *entry;

    entry = title_gradient_table;
    i = 0;
    do {
        value = i * 4;
        if (value >= 0x100) {
            value = 0xFF;
        }
        i++;
        entry[0] = value;
        entry[1] = value;
        entry[2] = value;
        entry[3] = 0;
        entry += 4;
    } while (i < 0x41);
}

/* Perspective-projects the vertices in verts (size bytes of SVECTOR-like 8-byte records) and stores each
 * screen x/y in out. Pipelined: the next vertex is loaded while RTPS works on the current one. */
void title_project_verts(u32 *verts, s32 size, u32 *out) {
    u32 *end;
    u32 v0;
    u32 v1;

    gte_ldv0(verts);
    end = (u32 *)((char *)verts + size);
    verts += 2;
    gte_rtps_b();
    do {
        v0 = verts[0];
        v1 = verts[1];
        gte_stsxy(out);
        gte_set(VXY0, v0);
        gte_set(VZ0, v1);
        out++;
        verts += 2;
        gte_rtps_b();
    } while (verts != end);
    gte_stsxy(out);
}

/* Projects `size` bytes of vertices (bit 16 of the xy word cleared), each offset by (xy_add, z_add),
 * storing every screen xy (SXY2) to out. */
void title_project_verts_offset(TitlePackedVertex *verts, s32 size, s32 *out, s32 xy_add, s32 z_add) {
    TitlePackedVertex *end;
    s32 xy;
    s32 z;

    SCHED_BARRIER();
    xy = verts->xy;
    z = verts->z;
    SCHED_BARRIER();
    xy = (xy & 0xFFFEFFFF) + xy_add;
    z += z_add;
    gte_set(VXY0, xy);
    gte_set(VZ0, z);
    end = (TitlePackedVertex *)((u8 *)verts + size);
    verts++;
    gte_rtps_b();
    do {
        xy = verts->xy;
        z = verts->z;
        xy = (xy & 0xFFFEFFFF) + xy_add;
        z += z_add;
        gte_store(SXY2, out, 0);
        gte_set(VXY0, xy);
        gte_set(VZ0, z);
        out++;
        verts++;
        gte_rtps_b();
    } while (verts != end);
    gte_store(SXY2, out, 0);
}

/* Originally C (with GTE macros), kept as asm: we can't yet reproduce it. A hand session got our C to 99.0%: the
 * only differences are the order of instructions in two spots, decided by cc1's final scheduling pass, and no C
 * form we found gives the original's order. Not a hand edit (both spots are slower in the original); likely a
 * source detail we haven't found, such as a volatile read or a PsyQ GTE macro. HISTORY "title title_model_draw_at by
 * hand"; draft with the analysis: agent_logs/sessions/a4a24_func_800A4A24.c. */
#ifdef NON_MATCHING
/* title_model_draw's sibling: draws model model_index at pos (relative to the selected rec), rotated by rot or, with
 * rot NULL, offset only. Lights the model's colours into title_lit_colors (nccs with the item's colour matrix for
 * shade > 0, else a flat gradient entry), then draws each depth-tested group's faces as GT4 (scratch +0x24 == 0)
 * or FT4 into OT entry `level`. C companion of an asm function our C only reached 99.0% on (the draft is
 * agent_logs/sessions/a4a24_func_800A4A24.c; registers, frame and code match except the order of 2 instruction
 * pairs, at 800A4FD0 and 800A50AC..C8, chosen by cc1's final scheduling pass; the draft reads vxy through a
 * volatile pointer and pins the GTE temporaries). Not compiled. */
extern u8 D_8010E928[]; /* projected screen xy */
extern u8 title_lit_colors[]; /* lit colours */
void title_draw_gt4_faces(s32 count, u8 *screen_xy, u8 *colours, TitleGt4Face *faces);
void title_ft4_faces_draw(s32 count, u8 *screen_xy, u8 *colours, TitleFt4Face *faces);
extern u8 title_gradient_table[];
extern const s16 rcossin_tbl[][2];
extern s16 D_800BDB0C[] __asm__(".L800BDB0C");
void title_project_verts_offset(TitlePackedVertex *verts, s32 size, s32 *out, s32 xy_add, s32 z_add);

/* packed sin/cos word of an angle: cos in the high half */
#define TITLE_TRIG(angle) (*(u32 *)rcossin_tbl[(angle) & 0xFFF])

/* title_poly_depth without the IR0 (depth_cue) store: -1 = off screen, else the OT level */
static s32 title_poly_depth_nocue(s32 vxy, s32 vz, s32 radius) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    s32 depth, x, y, half, sq1, sq2, sq3, dist, lzcr, half_shift, exp_shift;
    u32 idx;
    s16 *table;
    s32 level;

    gte_set(VXY0, vxy);
    gte_set(VZ0, vz);
    half = radius * 3 / 2;
    gte_rtps_b();
    gte_get_wait(MAC3, depth);
    if (depth + radius < 0x80) {
        return -1;
    }
    gte_get(MAC1, x);
    gte_get(MAC2, y);
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, depth);
    gte_sqr0();
    gte_get(MAC1, sq1);
    gte_get(MAC2, sq2);
    gte_get(MAC3, sq3);
    dist = sq1 + sq2 + sq3;
    idx = ~1;
    if (dist != 0) {
        gte_set(LZCS, dist);
        table = D_800BDB0C;
        gte_get(LZCR, lzcr);
        half_shift = 31 - lzcr;
        lzcr &= idx;
        exp_shift = lzcr - 24;
        idx = dist << exp_shift;
        if (exp_shift < 0) {
            idx = (u32)dist >> -exp_shift;
        }
        dist = table[idx];
        half_shift >>= 1;
        dist <<= half_shift;
        dist = (u32)dist >> 12;
    }
    if (dist - radius > 0x2000) {
        return -1;
    }
    if ((x >= 0 ? x : -x) >= depth * 160 / 256 + half) {
        return -1;
    }
    if ((y >= 0 ? y : -y) >= depth * 120 / 256 + half) {
        return -1;
    }
    level = sc->seq_depth;
    if (level == -1) {
        level = dist / 64;
        if (level >= 0x7F) {
            level = 0x7F;
        }
    }
    return level;
}

void title_model_draw_at(s16 *pos, s16 *rot, s32 model_index, s32 shade) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    TitleSetSlot *model;
    TitleDrawCtx *ctx;
    TitleRecPoolEntry *rec;
    TitleLightMatrices *item;
    TitleMatrix rm;
    TitleMatrix tm;
    TitleMatrix *m;
    TitleMatrix *t;
    s32 x, y, z;
    s32 angles, angle_z;
    s32 tx, ty, tz;
    u32 sy, sx, sz;
    u32 *colours, *colours_end, *out;
    u32 packed;
    s32 *data;
    s16 *centre;
    s32 group, i, n;
    s32 count, radius, vxy, vz, level;

    m = &rm;
    t = &tm;
    x = pos[0];
    y = pos[1];
    z = pos[2];
    model = &title_set_slots[model_index];
    ctx = title_draw_ctx_ptr;
    rec = title_rec_current();
    item = title_item_current();
    x -= rec->pos_x >> 12;
    y -= rec->pos_y >> 12;
    z -= rec->pos_z >> 12;
    title_rec_matrix_update();
    gte_load_LC_pair(&item->colour);
    if (rot == NULL) {
        title_project_verts_offset(model->tableA, model->sizeA, (s32 *)D_8010E928, (x & 0xFFFF) | (y << 16), z);
        gte_load_L_pair(&item->dir);
    } else {
        /* translation: the rec's rotation applied to the offset */
        gte_set(VXY0, (x & 0xFFFF) | (y << 16));
        gte_set(VZ0, z);
        gte_rtv0tr_b();
        gte_get(MAC1, tx);
        gte_get(MAC2, ty);
        gte_get(MAC3, tz);
        tm.t[0] = tx;
        tm.t[1] = ty;
        tm.t[2] = tz;
        angles = *(s32 *)rot; /* x and y angles in one word */
        angle_z = rot[2];
        /* rm = Ry */
        sy = TITLE_TRIG(angles >> 16);
        rm.m[0][1] = 0;
        rm.m[1][0] = 0;
        rm.m[1][1] = 0x1000;
        rm.m[1][2] = 0;
        rm.m[2][1] = 0;
        rm.m[0][0] = sy >> 16;
        rm.m[0][2] = sy;
        rm.m[2][0] = -sy;
        rm.m[2][2] = sy >> 16;
        /* tm = Rx */
        sx = TITLE_TRIG(angles);
        tm.m[0][0] = 0x1000;
        tm.m[0][1] = 0;
        tm.m[0][2] = 0;
        tm.m[1][0] = 0;
        tm.m[2][0] = 0;
        tm.m[1][1] = sx >> 16;
        tm.m[1][2] = -sx;
        tm.m[2][1] = sx;
        tm.m[2][2] = sx >> 16;
        gte_load_R_pair(t);
        gte_mul_rot_columns(m, m);
        /* tm = Rz */
        sz = TITLE_TRIG(angle_z);
        tm.m[0][0] = sz >> 16;
        tm.m[0][1] = -sz;
        tm.m[0][2] = 0;
        tm.m[1][0] = sz;
        tm.m[1][1] = sz >> 16;
        tm.m[1][2] = 0;
        tm.m[2][0] = 0;
        tm.m[2][1] = 0;
        tm.m[2][2] = 0x1000;
        gte_load_R_pair(t);
        gte_mul_rot_columns(m, m);
        gte_set_ctrl(TRX, 0);
        gte_set_ctrl(TRY, 0);
        gte_set_ctrl(TRZ, 0);
        gte_load_R_pair(&item->dir);
        gte_mul_rot_columns(m, t);
        gte_load_L_pair(t);
        gte_load_R_pair(&rec->mat);
        gte_mul_rot_columns(m, t);
        gte_load_R_pair(t);
        gte_load_TR_last_base(t->t);
        title_project_verts(model->tableA, model->sizeA, (u32 *)D_8010E928);
    }
    /* light the model's packed colours into title_lit_colors, or fill them with the gradient entry of -shade */
    colours = model->tableB;
    out = (u32 *)title_lit_colors;
    n = model->sizeB;
    if (shade > 0) {
        packed = colours[0];
        gte_set(VXY0, (packed & 0xFF00FF) << 8);
        gte_set(VZ0, packed & 0xFF00);
        gte_set(RGB, *(u32 *)(title_gradient_table + (shade >> 7) * 4));
        colours_end = (u32 *)((u8 *)colours + n);
        colours++;
        gte_nccs_b();
        do {
            packed = *colours;
            gte_store(RGB2, out, 0);
            gte_set(VXY0, (packed & 0xFF00FF) << 8);
            gte_set(VZ0, packed & 0xFF00);
            out++;
            colours++;
            gte_nccs_b();
        } while (colours != colours_end);
        gte_store(RGB2, out, 0);
    } else {
        u32 fill = *(u32 *)(title_gradient_table + (-shade / 128) * 4);

        for (i = 0; i < (s32)((u32)n >> 2); i++) {
            *out++ = fill;
        }
    }
    sc->colours = model->tableB;
    data = model->groups;
    for (group = 0; group < model->groupCount; group++) {
        count = data[0];
        radius = data[1];
        data += 2;
        centre = (s16 *)data;
        data += 2;
        vxy = ((volatile u32 *)centre)[0];
        vz = centre[2];
        if (rot == NULL) {
            vxy = (vxy & ~0x10000) + ((x & 0xFFFF) | (y << 16));
            vz += z;
        }
        level = title_poly_depth_nocue(vxy, vz, radius);
        if (level != -1) {
            sc->ot = (u32 *)(ctx->ot_base + level * 4);
            if (sc->unk_24 == 0) {
                title_draw_gt4_faces(count, D_8010E928, title_lit_colors, (TitleGt4Face *)data);
            } else {
                title_ft4_faces_draw(count, D_8010E928, title_lit_colors, (TitleFt4Face *)data);
            }
        }
        data = (s32 *)((u8 *)data + count * 0x20);
    }
}
#else
INCLUDE_ASM("../src/title/asm", title_model_draw_at);
#endif

/* Builds a texture-window word (0xE2) plus a POLY_GT3 or POLY_GT4 at $gp for each of count faces (last
 * first), all linked into the current OT entry; with scratch flag 0x20 set, back faces (NCLIP <= 0) are
 * skipped. */
void title_draw_gt4_faces(s32 count, u8 *screen_xy, u8 *colours, TitleGt4Face *faces) {
    /* the original keeps the loop invariants in fixed registers */
    register TitleGt4Face *end asm("$16");
    register TitleScratch3D8 *sc asm("$17");
    register s32 semi_bit asm("$18");
    register s32 one asm("$19");
    register u32 *ot asm("$20");
    register u32 mask asm("$7");
    register TitleGt4Face *face asm("$12");
    register s16 *colour asm("$14");
    u32 link;
    s32 word;
    s32 xy23;
    s32 quad;
    s32 hi;
    s32 area;
    u32 code;
    u32 rgb_a;
    u32 rgb_b;
    u32 uv01;
    u32 uv23;
    u32 tpage_clut;
    u32 bits;
    s32 ofs_a;
    s32 ofs_b;

    end = faces;
    FAKE_OPAQUE(end);
    sc = (TitleScratch3D8 *)0x1F8003D8;
    FAKE_OPAQUE(sc);
    ot = sc->ot;
    do { } while (0);
    end--;
    face = end + count;
    one = 1;
    semi_bit = 0x08000000;
    mask = 0xFFFFFF;
    colour = &face->colour[3];
    link = *ot;
    do {
        word = face->xy01;
        xy23 = face->xy23;
        gte_load(SXY0, screen_xy + (word & 0xFFFF), 0);
        gte_load(SXY1, screen_xy + ((u32)word >> 16), 0);
        gte_load(SXY2, screen_xy + (xy23 & 0xFFFF), 0);
        if ((s16)*(volatile u16 *)&sc->unk_20 == one) {
            gte_nclip();
            word = face->flags;
            gte_get_wait(MAC0, area);
            hi = word >> 30;
            if (area <= 0) {
                goto next;
            }
        } else {
            word = face->flags;
            hi = word >> 30;
        }
        quad = hi & 1;
        /* POLY_GT3 (0x34) or POLY_GT4 (0x3C), semi-transparent (0x02) when the face asks and it's allowed */
        if ((s16)*(volatile u16 *)&sc->semi_trans_ok == one) {
            if (!quad) {
                code = ((word & semi_bit) >> 2) | 0x34000000;
            } else {
                code = ((word & semi_bit) >> 2) | 0x3C000000;
            }
        } else if (!quad) {
            code = 0x34000000;
        } else {
            code = 0x3C000000;
        }
        ofs_a = colour[-3];
        ofs_b = colour[-2];
        rgb_a = *(u32 *)(colours + ofs_a);
        rgb_b = *(u32 *)(colours + ofs_b);
        do { } while (0);
        uv01 = face->uv01;
        uv23 = face->uv23;
        do { } while (0);
        word &= mask;
        word |= 0xE2000000;
        *(u32 *)(scratch_top + 4) = word;
        gte_store(SXY0, scratch_top, 0xC);
        gte_store(SXY1, scratch_top, 0x18);
        gte_store(SXY2, scratch_top, 0x24);
        tpage_clut = face->tpage_clut;
        do { } while (0);
        word = uv01 & 0xFFFF;
        bits = tpage_clut & 0xFFFF0000;
        word |= bits;
        *(u32 *)(scratch_top + 0x10) = word;
        do { } while (0);
        bits = tpage_clut << 16;
        word = uv01 >> 16;
        word |= bits;
        *(u32 *)(scratch_top + 0x1C) = word;
        word = uv23 & 0xFFFF;
        *(u32 *)(scratch_top + 0x28) = word;
        do { } while (0);
        *(u32 *)(scratch_top + 8) = rgb_a | code;
        *(u32 *)(scratch_top + 0x14) = rgb_b | code;
        SCHED_BARRIER();
        if (!quad) {
            *(u32 *)(scratch_top + 0) = link | 0x0A000000;
            rgb_a = *(u32 *)(colours + colour[-1]);
            link = (u32)scratch_top & mask;
            *(u32 *)(scratch_top + 0x20) = rgb_a | code;
            scratch_top += 0x2C;
        } else {
            u32 tag = link | 0x0D000000;
            link = (u32)scratch_top & mask;
            *(u32 *)(scratch_top + 0) = tag;
            word = *(u32 *)(screen_xy + (xy23 >> 16));
            *(u32 *)(scratch_top + 0x34) = uv23 >> 16;
            *(u32 *)(scratch_top + 0x30) = word;
            gte_store(RGB2, scratch_top, 0x2C); /* overwritten by rgb3 below */
            ofs_a = colour[-1];
            ofs_b = colour[0];
            rgb_a = *(u32 *)(colours + ofs_a);
            rgb_b = *(u32 *)(colours + ofs_b);
            *(u32 *)(scratch_top + 0x20) = rgb_a | code;
            *(u32 *)(scratch_top + 0x2C) = rgb_b | code;
            scratch_top += 0x38;
        }
    next:
        face--;
        colour -= sizeof(TitleGt4Face) / sizeof(s16);
    } while (face != end);
    *ot = link;
}

/* Builds a POLY_FT4 at $gp for each of count faces (last first), linked into OT entry 13 + index, then a
 * texture-window reset (0xE2) into OT entry 17. */
void title_ft4_faces_draw(s32 count, u8 *screen_xy, u8 *colours, TitleFt4Face *faces) {
    TitleScratch3D8 *sc = (TitleScratch3D8 *)0x1F8003D8;
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    TitleFt4Face *face;
    TitleFt4Face *end;
    u32 mask;
    u32 word;
    s32 xy23;
    u32 code;
    /* the original keeps these in fixed registers and reuses them: hi_uv is uv23, then the OT entry
     * (offset, then address); lo_uv is uv01, then the primitive; rgb is the colour, then a mask */
    register u32 hi_uv asm("$4");
    register u32 lo_uv asm("$5");
    register u32 rgb asm("$6");
    register u32 tex asm("$3");
    register u32 tpage asm("$2");
    s32 flags;

    end = faces - 1;
    face = end + count;
    mask = 0xFFFFFF;
loop:
    word = face->xy01;
    xy23 = face->xy23;
    gte_load(SXY0, screen_xy + (word & 0xFFFF), 0);
    gte_load(SXY1, screen_xy + (word >> 16), 0);
    gte_load(SXY2, screen_xy + (xy23 & 0xFFFF), 0);
    flags = face->flags;
    do { } while (0);
    if ((s16)sc->semi_trans_ok == 1) {
        code = ((flags & 0x08000000) >> 2) | 0x2C000000;
    } else {
        code = 0x2C000000;
    }
    rgb = *(u32 *)(colours + face->colour);
    do { } while (0);
    lo_uv = face->uv01;
    hi_uv = face->uv23;
    gte_store(SXY0, scratch_top, 8);
    gte_store(SXY1, scratch_top, 0x10);
    gte_store(SXY2, scratch_top, 0x18);
    tex = face->tpage_clut;
    do { } while (0);
    word = lo_uv & 0xFFFF;
    word |= tex & 0xFFFF0000;
    *(u32 *)(scratch_top + 0xC) = word;
    do { } while (0);
    tpage = tex << 16;
    word = lo_uv >> 16;
    word |= tpage;
    *(u32 *)(scratch_top + 0x14) = word;
    word = hi_uv & 0xFFFF;
    *(u32 *)(scratch_top + 0x1C) = word;
    do { } while (0);
    word = *(u32 *)(screen_xy + (xy23 >> 16));
    hi_uv >>= 16;
    *(u32 *)(scratch_top + 0x24) = hi_uv;
    *(u32 *)(scratch_top + 0x20) = word;
    do {
        rgb |= code;
    } while (0);
    *(u32 *)(scratch_top + 4) = rgb;
    hi_uv = count-- * 4;
    FAKE_OPAQUE(screen_xy);
    lo_uv = (u32)scratch_top;
    scratch_top += 0x28;
    face--;
    hi_uv += (u32)ctx->ot_base;
    hi_uv += 0x34;
    tex = *(u32 *)hi_uv;
    *(u32 *)lo_uv = (tex & mask) | 0x09000000;
    *(u32 *)hi_uv = lo_uv & mask;
    if (face != end) goto loop;
    rgb = 0xFFFFFF;
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    hi_uv = (u32)scratch_top;
    *(u32 *)(scratch_top + 8) = 0;
    lo_uv = (u32)ctx->ot_base;
    scratch_top += 0xC;
    *(u32 *)hi_uv = (*(u32 *)(lo_uv + 0x44) & rgb) | 0x02000000;
    *(u32 *)(lo_uv + 0x44) = hi_uv & rgb;
}

extern s32 title_font_tex;
extern u16 title_font_clut[16];
extern s32 title_menu_words_tex;
extern u16 title_menu_words_clut[16];
extern s32 title_mission_names_tex;
extern u16 title_mission_names_clut[16];
extern u16 D_800F70E4[450];
extern u16 D_800F7468[16];
extern s16 D_80110A2C;
extern s16 D_80110A30;
extern s16 D_80110A34;
extern s16 D_80110A38;
extern s16 D_80110A3C;
extern s16 D_80110A40;
extern s16 D_80110A48;
extern s16 D_80110A4C;
s32 sprite_load_tpage(void *sprite, s32 x, s32 y);
s32 clut_load(void *sprite, s32 x, s32 y, s32 a3, s32 a4, s32 a5);
void title_text_ot_depth_set(s32 value);
void title_slots_set_clut(void);
/* Title screen setup: places eight sprite entries (four pairs) and stores the returned ids in
 * 0x80110A2C..0x80110A4C. The 0x80110A3C entry is the constant 0x31, not a returned id. */
void title_sprites_load(void) {
    D_80110A2C = sprite_load_tpage(&title_font_tex, 0x40, 0x100);
    D_80110A30 = clut_load(title_font_clut, 0x50, 0xF0, 1, 1, 0x10);
    sprite_load_tpage(&title_menu_words_tex, 0x60, 0x100);
    D_80110A3C = 0x31;
    D_80110A40 = clut_load(title_menu_words_clut, 0x60, 0xF0, 1, 1, 0x10);
    D_80110A34 = sprite_load_tpage(&title_mission_names_tex, 0x100, 0x180);
    D_80110A38 = clut_load(title_mission_names_clut, 0x70, 0xF0, 1, 1, 0x10);
    D_80110A48 = sprite_load_tpage(&D_800F70E4, 0x1C0, 0x180);
    D_80110A4C = clut_load(D_800F7468, 0xD0, 0xF0, 1, 1, 0x10);
    title_text_ot_depth_set(2);
    title_slots_set_clut();
}

extern s32 title_text_ot_depth;
/* Stores the requested value in title_text_ot_depth, raised to a minimum of 2. */
void title_text_ot_depth_set(s32 value) {
    if (value < 2) {
        title_text_ot_depth = 2;
        return;
    }
    title_text_ot_depth = value;
}

/* Draws character ch at (x, y) from the title font: size 0 an 8x8 SPRT_8, 1 an 8x16 SPRT, 2 a 6x8 SPRT
 * (semi-transparent when semi_trans); shade 0..0xFFF gives the grey level. */
void title_draw_char(s32 x, s32 y, s32 ch, s32 size, s32 semi_trans, s32 shade) {
    register TitleDrawCtx *ctx asm("$9") = title_draw_ctx_ptr;
    s32 u;
    s32 v;
    s16 h;
    u8 *small_ot;
    u8 *small_pkt;
    u8 *ot;
    u8 *pkt;
    u16 clut;

    ch -= 0x20;
    shade /= 32;
    switch (size) {
    case 0:
        u = (ch & 0xF) * 8;
        v = (ch / 16) * 8;
        ((TitleSprt *)scratch_top)->code = 0x74;
        ((TitleSprt *)scratch_top)->len = 3;
        ((TitleSprt *)scratch_top)->r = shade;
        ((TitleSprt *)scratch_top)->g = shade;
        ((TitleSprt *)scratch_top)->b = shade;
        ((TitleSprt *)scratch_top)->u = u;
        ((TitleSprt *)scratch_top)->v = v;
        ((TitleSprt *)scratch_top)->code &= ~1;
        ((TitleSprt *)scratch_top)->x = x;
        ((TitleSprt *)scratch_top)->y = y;
        ((TitleSprt *)scratch_top)->clut = D_80110A30;
        small_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
        do { } while (0);
        small_pkt = scratch_top;
        addPrim(small_ot, small_pkt);
        scratch_top += 0x10;
        return;
    case 1:
        u = (ch & 0xF) * 8;
        v = (ch / 16) * 16 + 0x30;
        ((TitleSprt *)scratch_top)->code = 0x64;
        ((TitleSprt *)scratch_top)->len = 4;
        ((TitleSprt *)scratch_top)->code &= ~1;
        if (semi_trans) {
            ((TitleSprt *)scratch_top)->code |= 2;
        } else {
            ((TitleSprt *)scratch_top)->code &= ~2;
        }
        ((TitleSprt *)scratch_top)->r = shade;
        ((TitleSprt *)scratch_top)->g = shade;
        ((TitleSprt *)scratch_top)->b = shade;
        ((TitleSprt *)scratch_top)->u = u;
        ((TitleSprt *)scratch_top)->v = v;
        clut = D_80110A30;
        ((TitleSprt *)scratch_top)->w = 8;
        do { } while (0);
        h = 16;
        break;
    case 2:
        u = (ch & 0xF) * 8;
        v = (ch / 16) * 8 + 0x90;
        ((TitleSprt *)scratch_top)->code = 0x64;
        ((TitleSprt *)scratch_top)->len = 4;
        ((TitleSprt *)scratch_top)->code &= ~1;
        if (semi_trans) {
            ((TitleSprt *)scratch_top)->code |= 2;
        } else {
            ((TitleSprt *)scratch_top)->code &= ~2;
        }
        ((TitleSprt *)scratch_top)->r = shade;
        ((TitleSprt *)scratch_top)->g = shade;
        ((TitleSprt *)scratch_top)->b = shade;
        ((TitleSprt *)scratch_top)->u = u + 1;
        ((TitleSprt *)scratch_top)->v = v;
        clut = D_80110A30;
        ((TitleSprt *)scratch_top)->w = 6;
        do { } while (0);
        h = 8;
        break;
    default:
        return;
    }
    ((TitleSprt *)scratch_top)->h = h;
    ((TitleSprt *)scratch_top)->x = x;
    ((TitleSprt *)scratch_top)->y = y;
    ((TitleSprt *)scratch_top)->clut = clut;
    ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    do { } while (0);
    pkt = scratch_top;
    addPrim(ot, pkt);
    scratch_top += 0x14;
}

extern s32 title_decimal_divisors[];
/* Prints value as signed decimal (leading zeros skipped), then adds a texture-window reset and a draw-mode packet. */
void title_draw_number(s32 x, s32 y, s32 value, s32 size, s32 semi_trans, s32 shade) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 *div;
    s32 started;
    s32 i;
    s32 digit;
    s32 d;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    if (value < 0) {
        title_draw_char(x, y, '-', size, semi_trans, shade);
        value = -value;
        x += 8;
    }
    started = 0;
    div = title_decimal_divisors;
    for (i = 0; i < 10; i++, div++) {
        d = *div;
        digit = value / d;
        if (digit != 0 || i == 9 || started != 0) {
            title_draw_char(x, y, digit + '0', size, semi_trans, shade);
            started = 1;
            x += 8;
        }
        value -= digit * d;
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A2C & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

void title_draw_char(s32 x, s32 y, s32 ch, s32 size, s32 semi_trans, s32 shade);
/* Prints value as 8 hex digits (8 pixels apart), then adds a texture-window reset and a draw-mode packet. */
void title_draw_hex(s32 x, s32 y, u32 value, s32 zero, s32 unused, s32 maxLen) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 i;
    s32 digit;
    s32 offset;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    for (i = 0; i < 8; i++) {
        digit = value >> 28;
        if (digit < 10) {
            title_draw_char(x, y, digit | 0x30, zero, unused, maxLen);
        } else {
            title_draw_char(x, y, digit + 0x37, zero, unused, maxLen);
        }
        x += 8;
        value <<= 4;
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    offset = title_text_ot_depth * 4;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)offset + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A2C & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

void title_draw_text(s32 x, s32 y, u8 *text, s32 size, s32 mode) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 glyph_adv;
    s32 space_adv;
    s32 ch;
    s32 flag;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    if (size < 2) {
        glyph_adv = 8;
        space_adv = 8;
    } else {
        glyph_adv = 6;
        space_adv = 4;
    }
    flag = mode != 0x1000;
    ch = *text++;
    if (ch != 0) do {
        if ((u32)(ch - 0x20) < 0x60) {
            if (ch == 0x20) {
                x += space_adv;
            } else {
                if (size == 2 && ch == 0x49) {
                    x -= 1;
                }
                title_draw_char(x, y, ch, size, flag, mode);
                x += glyph_adv;
            }
        }
        ch = *text++;
    } while (ch != 0);
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A2C & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

extern u32 title_decimal_places[];
/* Prints value as `digits` unsigned decimal digits 8 pixels apart, leading zeros blank (the last digit
 * always shown), then adds a texture-window reset and a draw-mode packet. */
void title_draw_digits(s32 x, s32 y, s32 digits, u32 value, s32 size, s32 shade) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u32 *place; /* powers of ten, from 10^(digits-1) down */
    s32 started;
    s32 i;
    u32 d;
    u32 digit;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    started = 0;
    place = &title_decimal_places[10 - digits];
    for (i = 0; i < digits; value -= digit * d, i++, place++) {
        d = *place;
        digit = value / d;
        if (digit != 0 || i == digits - 1 || started != 0) {
            title_draw_char(x, y, digit + '0', size, 0, shade);
            started = 1;
            x += 8;
        } else {
            x += 8;
        }
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A2C & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)(title_text_ot_depth * 4) + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

void title_draw_text(s32 x, s32 y, u8 *text, s32 size, s32 mode);
void title_draw_number(s32 x, s32 y, s32 value, s32 size, s32 semi_trans, s32 shade);
/* Counts the characters of text (0 for an empty string), then draws it at
   x + count * 8. flag is set when mode is not 0x1000. */
void title_text_draw_tail(s32 x, s32 y, u8 *text, s32 arg3, s32 arg4, s32 mode) {
    u8 *tail;
    s32 count;
    s32 flag;

    flag = mode != 0x1000;
    count = 0;
    tail = text + 1;
    if (*text != 0) {
        do {
            count += 1;
        } while (*tail++ != 0);
    }
    title_draw_text(x, y, text, arg4, mode);
    title_draw_number(x + (count * 8), y, arg3, arg4, flag, mode);
}

void title_draw_hex(s32 x, s32 y, u32 value, s32 zero, s32 unused, s32 maxLen);
/* Measures str (strlen), then calls two helpers: at (x, y), and at
   (x + 8 * len, y). Purpose of the helpers is not yet identified. */
void text_draw_color(s32 x, s32 y, u8 *str, s32 color) {
    s32 len = 0;
    s32 zero = 0;
    s32 maxLen = 0x1000;
    u8 *p = str + 1;
    if (*str != 0) {
        do {
            len++;
        } while (*p++ != 0);
    }
    title_draw_text(x, y, str, zero, maxLen);
    title_draw_hex(x + len * 8, y, color, zero, 0, maxLen);
}

extern s32 title_menu_cell_widths[];
extern u16 title_glyph_tpage[];
extern u16 title_glyph_clut[];
/* Draws an 8-pixel-high strip (texture u 0x68, row 0xA0 + index * 8, width from title_menu_cell_widths) at OT slot 8,
   then a texture-window reset and a draw-mode packet. */
void title_draw_menu_cell(s32 x, s32 y, s32 index, s32 bright) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 w = title_menu_cell_widths[index];
    s32 v = index * 8 + 0xA0;
    s32 u = 0x68;
    s32 h = 8;
    u8 *rect_ot;
    u8 *rect_pkt;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    scratch_top[7] = 0x64;
    scratch_top[3] = 4;
    scratch_top[7] &= 0xFE;
    bright /= 32;
    scratch_top[4] = bright;
    scratch_top[5] = bright;
    scratch_top[6] = bright;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    scratch_top[0xC] = u;
    scratch_top[0xD] = v;
    *(s16 *)(scratch_top + 0x10) = w;
    *(s16 *)(scratch_top + 0x12) = h;
    *(u16 *)(scratch_top + 0xE) = title_glyph_tpage[0];
    rect_ot = (u8 *)8 + (u32)ctx->ot_base;
    rect_pkt = scratch_top;
    addPrim(rect_ot, rect_pkt);
    scratch_top += 0x14;

    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)8 + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (title_glyph_clut[0] & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)8 + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

void title_draw_menu_bar(s32 x, s32 y, s32 row, s32 bright) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *pkt;
    u8 *ot;
    u8 *pkt2;
    u8 *ot2;
    u8 *pkt3;
    u8 *ot3;
    s32 w;
    s32 h;

    row = row * 8 + 0x80;
    w = 0x1C;
    h = 8;
    scratch_top[3] = 4;
    scratch_top[7] = 0x64;
    scratch_top[7] &= 0xFE;
    bright /= 32;
    scratch_top[4] = bright;
    scratch_top[5] = bright;
    scratch_top[6] = bright;
    scratch_top[0xC] = 0;
    scratch_top[0xD] = row;
    *(u16 *)(scratch_top + 0xE) = D_80110A4C;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x10) = w;
    *(s16 *)(scratch_top + 0x12) = h;
    ot = ctx->ot_base + 8;
    pkt = scratch_top;
    addPrim(ot, pkt);
    scratch_top += 0x14;

    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    ot2 = ctx->ot_base + 8;
    pkt2 = scratch_top;
    addPrim(ot2, pkt2);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A48 & 0x9FF) | 0xE1000600;
    ot3 = ctx->ot_base + 8;
    pkt3 = scratch_top;
    addPrim(ot3, pkt3);
    scratch_top += 8;
}

void title_prim_textured_rect(s32 x, s32 y, s32 u, s32 v, s32 w, s32 h, s32 bright, s32 semi_trans) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *pkt;
    u8 *ot;
    s32 green;
    scratch_top[3] = 4;
    do {
    } while (0);
    scratch_top[7] = 0x64;
    scratch_top[7] &= 0xFE;
    /* the green channel is halved when bit 15 is set */
    do {
        green = bright;
        if (bright & 0x8000) {
            green = bright / 2;
        }
    } while (0);
    scratch_top[4] = bright;
    scratch_top[5] = green;
    scratch_top[6] = bright;
    if (semi_trans != 0) {
        scratch_top[7] |= 2;
    } else {
        scratch_top[7] &= 0xFD;
    }
    scratch_top[0xC] = u;
    scratch_top[0xD] = v;
    *(u16 *)(scratch_top + 0xE) = D_80110A38;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x10) = w;
    *(s16 *)(scratch_top + 0x12) = h;
    ot = ctx->ot_base + 8;
    pkt = scratch_top;
    addPrim(ot, pkt);
    scratch_top += 0x14;
}

extern s32 title_option_widths[];
void title_option_draw(s32 x, s32 y, s32 cur, s32 sel, s32 fade, s32 prev, s32 blink) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    s32 show;
    register s32 full asm("$16");
    s32 row;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    blink /= 32;
    show = sel;
    if (fade < 0x800) {
        show = cur;
    }
    full = 0x80;
    title_prim_textured_rect(x, y, 0, 0x80, 0x54, 8, full, 0);
    if (show != 0) {
        title_prim_textured_rect(x - 0xD, y, 0x40, 0x90, 8, 8, blink, 1);
    }
    if (sel == prev) {
        if (sel != 0xB) {
            title_prim_textured_rect(x + 0x6E, y, 0x58, 0x90, 8, 8, full, 0);
        }
    } else {
        title_prim_textured_rect(x + 0x6E, y, 0x48, 0x90, 8, 8, blink, 1);
    }
    row = sel / 8 * 8;
    title_prim_textured_rect(x + 0x5A, y, (sel - row) * 16, row + 0x88, 0x10, 8, 0x80, 0);
    if (fade == 0) {
        s32 tex_v = cur * 8 + 0x98;
        s32 width = title_option_widths[cur];
        title_prim_textured_rect(x - width / 2 + 0x34, y + 0xC, 0, tex_v, width, 8, 0x80, 0);
    } else {
        s32 level = fade / 64 | 0x8000;
        s32 tex_v = sel * 8 + 0x98;
        s32 width = title_option_widths[sel];
        title_prim_textured_rect(x - width / 2 + 0x34, y + 0xC, 0, tex_v, width, 8, level, 1);
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)8 + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;

    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A34 & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)8 + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

extern u16 D_800BDDEC[16];
extern u8 title_slots[];
/* Fills the 0x2 field of each of the 16 entries (stride 0xC) at title_slots
   with the value returned by the sprite setup call. */
void title_slots_set_clut(void) {
    s16 value;
    u8 *entry;
    s32 i;

    value = clut_load(D_800BDDEC, 0x80, 0xF0, 1, 1, 0x10);
    entry = title_slots;
    i = 0xF;
    do {
        *(s16 *)(entry + 2) = value;
        i -= 1;
        entry += 0xC;
    } while (i >= 0);
}

u8 * title_glyph_lookup(s32 code);
/* Renders the 2-byte character codes of text (0-terminated) as 16x15 4-bit glyphs into VRAM at
 * x, y (4 halfwords apart), set pixels in color, unknown codes filled with 3, and records the
 * row's tpages, texture row and glyph count in title_slots[index]. */
void title_glyph_row_build(s32 x, s32 y, s32 color, s32 index, u8 *text) {
    GlyphBuf buf;
    ClutRect rect;
    TitleGlyphRow *row;
    u8 *dst;
    u8 *glyph;
    u16 bits;
    s32 i;
    s32 j;
    s32 count;
    s32 tpage_y;
    s32 tpage_y_hi;
    s32 r;
    s32 c;

    rect.w = 4;
    rect.x = x;
    rect.y = y;
    rect.h = 15;
    count = 0;
    while (*text != 0) {
        dst = buf.pixels[0];
        glyph = title_glyph_lookup(text[1] | (*text << 8));
        if (glyph != (u8 *)-1) {
            for (j = 0; j < 15; j++) {
                bits = (glyph[0] << 8) | glyph[1];
                glyph += 2;
                for (i = 0; i < 16; i++) {
                    *dst++ = color & -((bits >> (15 - i)) & 1);
                }
            }
        } else {
            for (j = 14; j >= 0; j--) {
                for (i = 15; i >= 0; i--) {
                    *dst++ = 3;
                }
            }
        }
        for (r = 0; r < 16; r++) {
            for (c = 0; c < 4; c++) {
                buf.packed[r][c] = ((buf.pixels[r][c * 4 + 3] << 12) | (buf.pixels[r][c * 4 + 2] << 8) |
                    (buf.pixels[r][c * 4 + 1] << 4)) | buf.pixels[r][c * 4];
            }
        }
        title_draw_sync(0);
        title_load_image(&rect, buf.packed[0]);
        text += 2;
        rect.x += 4;
        count++;
    }
    row = (TitleGlyphRow *)title_slots + index;
    row->v = y % 256;
    tpage_y = (y & 0x100) >> 4;
    row->tpage = tpage_y | (((x & 0x3FF) >> 6) | 0x20) | (tpage_y_hi = (y & 0x200) << 2);
    row->count = count;
    row->tpage2 = tpage_y | ((((x + 0x40) & 0x3FF) >> 6) | 0x20) | tpage_y_hi;
}

/* Draws the glyph row title_slots[index] at x, y: each glyph as a shaded sprite (brightness / 32)
 * over a black shadow offset by (2, 1), each followed by its draw-mode packet; row 1 is proportionally
 * spaced. Ends with a texture-window reset. */
void title_glyph_row_draw(s32 ot_depth, s32 x, s32 y, s32 index, s32 brightness) {
    TitleGlyphRow *row = (TitleGlyphRow *)title_slots + index;
    u8 *ot;
    TitleGlyphPos pos;
    s32 i;
    u32 u;
    u32 v;
    u32 tpage;
    u32 draw_mode;
    s32 clut;
    s32 bright;

    u = 0;
    ot = title_draw_ctx_ptr->ot_base + ot_depth * 4;
    v = row->v;
    bright = brightness / 32;
    i = 0;
    tpage = row->tpage;
    clut = row->clut;
    for (; i < row->count; i++) {
        u16 glyph_clut = clut;

        pos.x = x;
        pos.y = y;
        pos.u = u;
        pos.v = v;
        ((TitleSprt *)scratch_top)->len = 4;
        ((TitleSprt *)scratch_top)->code = 0x64;
        ((TitleSprt *)scratch_top)->r = bright;
        ((TitleSprt *)scratch_top)->g = bright;
        ((TitleSprt *)scratch_top)->b = bright;
        ((TitleSprt *)scratch_top)->code &= 0xFE;
        ((TitleSprt *)scratch_top)->x = pos.x;
        ((TitleSprt *)scratch_top)->y = pos.y;
        ((TitleSprt *)scratch_top)->u = pos.u;
        ((TitleSprt *)scratch_top)->v = pos.v;
        ((TitleSprt *)scratch_top)->w = 0x10;
        ((TitleSprt *)scratch_top)->h = 0xF;
        ((TitleSprt *)scratch_top)->clut = glyph_clut;
        {
            u8 *prim = scratch_top;
            addPrim(ot, prim);
        }
        scratch_top += sizeof(TitleSprt);
        draw_mode = (tpage & 0x9FF) | 0xE1000600;
        scratch_top[3] = 1;
        *(u32 *)(scratch_top + 4) = draw_mode;
        {
            u8 *prim = scratch_top;
            addPrim(ot, prim);
        }
        scratch_top += 8;

        pos.x = x + 2;
        pos.y = y + 1;
        pos.u = u;
        pos.v = v;
        ((TitleSprt *)scratch_top)->len = 4;
        ((TitleSprt *)scratch_top)->code = 0x64;
        ((TitleSprt *)scratch_top)->r = 0;
        ((TitleSprt *)scratch_top)->g = 0;
        ((TitleSprt *)scratch_top)->b = 0;
        ((TitleSprt *)scratch_top)->code &= 0xFE;
        ((TitleSprt *)scratch_top)->x = pos.x;
        ((TitleSprt *)scratch_top)->y = pos.y;
        ((TitleSprt *)scratch_top)->u = pos.u;
        ((TitleSprt *)scratch_top)->v = pos.v;
        ((TitleSprt *)scratch_top)->w = 0x10;
        ((TitleSprt *)scratch_top)->h = 0xF;
        ((TitleSprt *)scratch_top)->clut = glyph_clut;
        {
            u8 *prim = scratch_top;
            addPrim(ot, prim);
        }
        scratch_top += sizeof(TitleSprt);
        scratch_top[3] = 1;
        *(u32 *)(scratch_top + 4) = draw_mode;
        {
            u8 *prim = scratch_top;
            addPrim(ot, prim);
        }
        scratch_top += 8;

        if (index == 1) {
            switch (i) {
            case 0: case 1: case 2: case 3: case 4: case 11: case 12:
                x += 0xF;
                break;
            case 5:
                x += 0xB;
                break;
            case 9: case 16:
                x += 0xE;
                break;
            default:
                x += 0x10;
                break;
            }
        } else {
            x += 0x10;
        }
        u += 0x10;
        if (u == 0x100) {
            u = 0;
            tpage = row->tpage2;
        }
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    {
        u8 *prim = scratch_top;
        addPrim(ot, prim);
    }
    scratch_top += 0xC;
}

void prim_add_textured_rect(s32 x, s32 y, s32 u, s32 v, s32 w, s32 h, s32 bright, s32 semi_trans) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *pkt;
    u8 *ot;
    bright /= 32;
    scratch_top[7] = 0x64;
    scratch_top[3] = 4;
    scratch_top[4] = bright;
    scratch_top[5] = bright;
    scratch_top[6] = bright;
    scratch_top[7] &= 0xFE;
    if (semi_trans != 0) {
        scratch_top[7] |= 2;
    } else {
        scratch_top[7] &= 0xFD;
    }
    scratch_top[0xC] = u;
    scratch_top[0xD] = v;
    *(u16 *)(scratch_top + 0xE) = D_80110A40;
    *(s16 *)(scratch_top + 8) = x;
    *(s16 *)(scratch_top + 0xA) = y;
    *(s16 *)(scratch_top + 0x10) = w;
    *(s16 *)(scratch_top + 0x12) = h;
    ot = ctx->ot_base + 8;
    pkt = scratch_top;
    addPrim(ot, pkt);
    scratch_top += 0x14;
}

/* Draws a 16x8 glyph cell (column col of the 0x80,0x70 texture row), then a texture-window reset and a semi-transparent draw-mode packet. */
void title_draw_swatch(s32 x, s32 y, s32 col, s32 bright) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;

    prim_add_textured_rect(x, y, col * 16 + 0x80, 0x70, 0x10, 8, bright, 1);
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)8 + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;
    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A3C & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)8 + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

extern s32 title_label_widths[];
/* Draws a menu line: a digit cell for num, a separator, the label glyph strip (width title_label_widths[label]), extra pieces for labels 5, 1 and 3; then resets the texture window and draw mode. */
void title_menu_cell_draw(s32 x, s32 y, s32 num, s32 label, s32 sub, s32 bright) {
    TitleDrawCtx *ctx = title_draw_ctx_ptr;
    u8 *win_ot;
    u8 *win_pkt;
    u8 *mode_ot;
    u8 *mode_pkt;
    s32 tex_v;
    register s32 dx asm("$4");
    s32 tex_u;
    s32 width;

    if (label == 4) {
        prim_add_textured_rect(x, y, 0x80, 0x20, title_label_widths[4], 8, bright, 0);
    } else {
        tex_u = (num % 8) * 16 + 0x80;
        tex_v = (num / 8) * 8 + 0x40;
        prim_add_textured_rect(x, y, tex_u, tex_v, 0x10, 8, bright, 0);
        prim_add_textured_rect(x + 0x10, y, 0x80, 0x58, 0x10, 8, bright, 0);
        tex_v = label * 8;
        prim_add_textured_rect(x + 0x18, y, 0x80, tex_v, title_label_widths[label], 8, bright, 0);
        if (label == 5) {
            dx = title_label_widths[5] + 0x18;
            prim_add_textured_rect(x + dx, y, 0x80, tex_v, title_label_widths[5], 8, bright, 0);
        }
        if (label == 1 || label == 3) {
            tex_u = (sub % 8) * 16 + 0x80;
            tex_v = (sub / 8) * 8 + 0x60;
            width = sub < 9 ? 0x10 : 0x18;
            dx = title_label_widths[label] + 0x1A;
            prim_add_textured_rect(x + dx, y, tex_u, tex_v, width, 8, bright, 0);
        }
    }
    scratch_top[3] = 2;
    *(u32 *)(scratch_top + 4) = 0xE2000000;
    *(u32 *)(scratch_top + 8) = 0;
    win_ot = (u8 *)8 + (u32)ctx->ot_base;
    win_pkt = scratch_top;
    addPrim(win_ot, win_pkt);
    scratch_top += 0xC;
    scratch_top[3] = 1;
    *(u32 *)(scratch_top + 4) = (D_80110A3C & 0x9FF) | 0xE1000600;
    mode_ot = (u8 *)8 + (u32)ctx->ot_base;
    mode_pkt = scratch_top;
    addPrim(mode_ot, mode_pkt);
    scratch_top += 8;
}

extern s32 title_sprite_flag;

s32 get_title_sprite_flag(void) {
    return title_sprite_flag;
}

extern s32 title_sprite_flag;

void set_title_sprite_flag(s32 arg0) {
    title_sprite_flag = arg0;
}

void title_sprite_reset(TitleAnimRatioOwner *outer);
void title_fade_step_update(TitleFadeOwner *obj);
void title_bars_draw(TitleObj *obj);
void title_file_menus_init(TitleFadeOwner *owner);
void title_sprite_start(void);
void title_menu_init(void);
void title_anim_init(void);
void title_slot_task_init(void);
void card_list_init(void);
void card_header_build(void);
void title_list_init(void);
void title_card_wait_init(void);
void title_step_init(void);
extern s32 title_label_strings[];
extern s16 D_80110D84, D_80110D88, D_80110D8C, D_80110D8E, D_80110D94, D_80110D96;
extern s16 D_80110D90, D_80110D9C;
extern s16 D_80110D98, D_80110D9A, D_80110DA0, D_80110DA2;
extern void * D_80110DA4;
extern void * D_80110DA8;
extern s32 D_80110D80, title_load_task, title_memcard_task;
extern u8 D_801177DE;
void title_text_init(void *task) {
    s32 *text;
    s32 i;
    s32 y;
    s32 x;

    task_reset(task);
    task_set(task, (s32)title_sprite_reset, (s32)title_fade_step_update, (s32)title_bars_draw, (s32)&D_80110D80);
    x = 0x300;
    y = 0x100;
    i = 0;
    text = title_label_strings;
    D_80110D84 = 0x1C;
    D_80110D88 = 0xF;
    D_80110DA4 = &title_load_task;
    D_80110DA8 = &title_memcard_task;
    D_80110D8C = 0x22;
    D_80110D90 = 0x1000;
    D_80110D94 = 0x8C - D_801177DE;
    D_80110D96 = 0xB8;
    D_80110D8E = 1;
    D_80110D98 = 0x20;
    D_80110D9C = 0x1000;
    D_80110DA0 = 0xB4;
    D_80110DA2 = 0xB8;
    D_80110D9A = 0;
    do {
        title_glyph_row_build(x, y, 1, i, (u8 *)*text);
        y += 0x10;
        text++;
        i++;
    } while (i < 10);
    title_file_menus_init(task);
    title_sprite_start();
    title_menu_init();
    title_anim_init();
    title_slot_task_init();
    card_list_init();
    card_header_build();
    title_list_init();
    title_card_wait_init();
    title_step_init();
}

u32 str_no[117] = {
    0xA282A282, 0x0000A682, 0xA282CD82, 0x00000000, 0xFA8A898F, 0xC982BB89,
    0x7394B88E, 0xDC82B582, 0xBD82B582, 0x00000000, 0xB997498F, 0xDC82B582,
    0xBD82B582, 0x00000000, 0xFA8A898F, 0x8692BB89, 0xB782C582, 0x00000000,
    0xFA8A898F, 0xB582BB89, 0xE682C482, 0xB582EB82, 0xC582A282, 0xA982B782,
    0x00004881, 0x82838183, 0x5B818A83, 0x5B814A83, 0xAA826883, 0xFA8A898F,
    0xB382BB89, 0xC482EA82, 0xDC82A282, 0xF182B982, 0x00000000, 0x82838183,
    0x5B818A83, 0x5B814A83, 0xAA826883, 0xB191DA90, 0xEA82B382, 0xA282C482,
    0xB982DC82, 0x0000F182, 0x82838183, 0x5B818A83, 0x5B814A83, 0xC9826883,
    0xAB82F38B, 0x8D837583, 0x4E836283, 0xA082AA82, 0xDC82E882, 0xF182B982,
    0x00000000, 0x5B816683, 0xCC825E83, 0xAB82918F, 0xDD829E8D, 0xB88EC982,
    0xB5827394, 0xB582DC82, 0x0000BD82, 0x00006F4E, 0x00736559, 0x4D524F46,
    0x49545441, 0x4620474E, 0x454C4941, 0x00000000, 0x4D524F46, 0x49545441,
    0x4320474E, 0x4C504D4F, 0x00455445, 0x4D524F46, 0x49545441, 0x0000474E,
    0x79206F44, 0x7720756F, 0x20746E61, 0x66206F74, 0x616D726F, 0x74692074,
    0x0000003F, 0x20656854, 0x6F6D656D, 0x63207972, 0x20647261, 0x6E207369,
    0x6620746F, 0x616D726F, 0x64657474, 0x74657920, 0x0000002E, 0x6F6D654D,
    0x43207972, 0x20647261, 0x6E207369, 0x7020746F, 0x65736572, 0x002E746E,
    0x6F6D654D, 0x63207972, 0x20647261, 0x66207369, 0x2E6C6C75, 0x61636156,
    0x6220746E, 0x6B636F6C, 0x61707320, 0x00006563, 0x61746144, 0x706E6920,
    0x66207475, 0x756C6961, 0x002E6572,
};

void title_glyph_row_draw(s32 ot_depth, s32 x, s32 y, s32 index, s32 brightness);
extern s32 title_card_msg_ptrs[];
/* Draws label `label` at (x, y): as glyphs (one row up for label 1) when func_800A1BB4() is 0, else as text from
 * title_card_msg_ptrs at OT depth ot_depth, with the memory card's "not enough space" lines under label 1. */
void title_draw_label(s32 ot_depth, s32 x, s32 y, s32 label, s32 brightness) {
    if (func_800A1BB4() == 0) {
        if (label == 1) {
            title_glyph_row_draw(ot_depth, x - 1, y, 1, brightness);
        } else {
            title_glyph_row_draw(ot_depth, x, y, label, brightness);
        }
    } else {
        title_text_ot_depth_set(ot_depth);
        title_draw_text(x, y, (u8 *)title_card_msg_ptrs[label], 1, brightness);
        if (label == 1) {
            title_draw_text(x, y + 0x10, (u8 *)"is less than required.Delete a saved", 1, brightness);
            title_draw_text(x, y + 0x20, (u8 *)"game or insert a new Memory card.", 1, brightness);
        }
        title_text_ot_depth_set(-1);
    }
}
