/* model_slots: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void stage_pair_set_vectors(SVECTOR *a, SVECTOR *b) {
    s32 x;
    s32 y;
    s32 z;

    y = 0x1000;
    if (a != NULL) {
        x = a->vx;
        y = a->vy;
        z = a->vz;
    } else {
        z = 0x1000;
        x = 0x1000;
    }
    tint_scale_r = x;
    tint_scale_g = y;
    tint_scale_b = z;
    if (b != NULL) {
        x = b->vx;
        y = b->vy;
        z = b->vz;
    } else {
        z = 0;
        y = 0;
        x = 0;
    }
    tint_add_r = x;
    tint_add_g = y;
    tint_add_b = z;
}

static inline s32 tint_clamp(s32 v) {
    v = MAX(MIN(v, 31), 0);
    return v;
}
/* Tints count 15-bit pixels in place with the scale (tint_scale_r..D0, 0x1000 = 1) and offset
 * (tint_add_r..D8) set by stage_pair_set_vectors, skipping zero pixels and those whose mask
 * byte has bit 1 set; a result of 0 (transparent) becomes 0x400. */
void tint_pixels(s32 count, u16 *pixels, u8 *mask) {
    s32 scale_r = tint_scale_r;
    s32 scale_g = tint_scale_g;
    s32 scale_b = tint_scale_b;
    s32 add_r = tint_add_r;
    s32 add_g = tint_add_g;
    s32 add_b = tint_add_b;
    s32 i;
    s32 pixel;
    s32 r;
    s32 g;
    s32 b;
    s32 stp;

    for (i = 0; i < count; i++, pixels++) {
        if (mask == NULL || !(mask[i] & 2)) {
            pixel = *pixels;
            if (pixel != 0) {
                r = pixel & 0x1F;
                g = (pixel >> 5) & 0x1F;
                b = (pixel >> 10) & 0x1F;
                stp = pixel & 0x8000;
                r = tint_clamp((r * scale_r + 0x800) / 4096 + add_r);
                g = tint_clamp((g * scale_g + 0x800) / 4096 + add_g);
                b = tint_clamp((b * scale_b + 0x800) / 4096 + add_b);
                pixel = stp | r | (g << 5) | (b << 10);
                if (pixel == 0) {
                    pixel = 0x400;
                }
                *pixels = pixel;
            }
        }
    }
}

void palette_buf_write(s32 index, s32 count, u16 *src) {
    u16 *dst = &palette_buf[index];

    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

void palette_buf_read(s32 offset, s32 count, u16 *dst) {
    u16 *src = palette_buf + offset;

    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

/* Copies count bytes from src into the buffer at image_buf + offset. */
void image_buf_write(s32 offset, s32 count, u8 *src) {
    u8 *dst = image_buf + offset;

    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}

/* Address of byte `offset` in the image_buf buffer. */
void *image_buf_at(s32 offset) {
    return image_buf + offset;
}

/* Clears a pchr entry (0x1C bytes): the first 0x0C bytes as words (the casts keep the word stores), then the
 * halfwords, with unk_14 set to 0x7FFF. */
void pchr_clear(Pchr *entry) {
    *(s32 *)&entry->unk_00 = 0;
    *(s32 *)&entry->link = 0;
    entry->data = 0;
    entry->unk_0C = 0;
    entry->unk_14 = 0x7FFF;
    entry->far_bias = 0;
    entry->unk_12 = 0;
    entry->bounds_radius = 0;
    entry->angle = 0;
    entry->unk_1A = 0;
}

/* Resets the pchr table (1536 entries) and the model, effect and view state.
   The table starts 4 bytes after pchr_count; the loop ends on the entry at
   (count + 4 + sizeof(Pchr) * 1535), since the compare is on the pre-increment value. */
void pchr_table_reset(void) {
    s16 *count;
    Pchr *entry;
    Pchr *last;

    /* Empty loop: a scheduling barrier so the register saves stay first. */
    do {
    } while (0);
    count = &pchr_count;
    *count = 1;
    entry = (Pchr *) (count + 2);
    last = (Pchr *) ((u8 *) count + (4 + sizeof(Pchr) * 1535));
    do {
        pchr_clear(entry);
    } while (entry++ != last);
    clut_count = 0;
    model_slot_count = 0;
    model_atlas_y = 0;
    model_atlas_x = 0;
    vram_pattern_upload();
    last_env_colour_a = -1;
    last_env_colour_b = -1;
    last_env_colour_c = -1;
    cell_flags_clear();
    stage_pair_set_vectors(NULL, 0);
    cell_block_rect(0, 0x100, 0x80, 0x80);
}

void stage_counts_save(void) {
    saved_pchr_count = pchr_count;
    saved_clut_count = clut_count;
    saved_model_count = model_slot_count;
    saved_atlas_y = model_atlas_y;
    saved_atlas_x = model_atlas_x;
    cell_flags_save();
}

/* Restores the counts stage_counts_save recorded and clears the pchr entries from the restored count to the
   table end. The loads come first; FAKE_OPAQUE makes the count be re-read after its store, as the original does. */
void stage_counts_restore(void) {
    s16 *count;
    Pchr *entry;
    Pchr *last;
    s32 saved_count;
    s32 saved_ac;
    s32 saved_models;
    s32 saved_a4;
    s32 saved_a8;

    do {
    } while (0);
    count = &pchr_count;
    do {
    } while (0);
    saved_count = saved_pchr_count;
    saved_ac = saved_clut_count;
    saved_models = saved_model_count;
    saved_a4 = saved_atlas_y;
    saved_a8 = saved_atlas_x;
    *count = saved_count;
    FAKE_OPAQUE(count);
    last = (Pchr *) ((u8 *) (count + 2) + sizeof(Pchr) * 1535);
    entry = (Pchr *) ((u8 *) (count + 2) + *count * sizeof(Pchr));
    clut_count = saved_ac;
    model_slot_count = saved_models;
    model_atlas_y = saved_a4;
    model_atlas_x = saved_a8;
    do {
        pchr_clear(entry);
    } while (entry++ != last);
    last_env_colour_a = -1;
    last_env_colour_b = -1;
    last_env_colour_c = -1;
    cell_flags_restore();
    stage_pair_set_vectors(NULL, NULL);
}

void model_slot_upload_clut(void) {
    s16 entries[0x20][4];
    s16 rect[4];
    s32 i;
    s32 origin_x;
    s32 count;
    s32 origin_y;
    u16 *buf;

    buf = arena_top();
    count = clut_count * 0x10;
    origin_x = vram_origin_x(0);
    i = 0;
    origin_y = vram_origin_y(0);
    palette_buf_read(origin_x, count, buf);
    tint_pixels(count, buf, image_buf_at(origin_x));
    do {
        entries[i][0] = origin_x;
        entries[i][1] = origin_y + i;
        entries[i][2] = count;
        entries[i][3] = 1;
        svc_load_image(entries[i], buf);
        i += 1;
    } while (i < 0x20);
    clut_make_pair(count, buf, buf, image_buf_at(origin_x));
    rect[0] = origin_x;
    rect[1] = origin_y - 2;
    rect[2] = count;
    rect[3] = 2;
    svc_load_image(rect, buf);
    svc_draw_sync(0);
}

/* Draws a strip `count` pixels wide from VRAM column x_start, in pieces of at most 0xC0: per piece a
 * semi-transparent quad shaded from rgb/32 (top) to rgb (bottom), then a 0x848484-to-0x040404 one. */
void light_backdrop_strip_draw(u8 *ot, s32 rgb, s32 x_start, s32 count)
{
    /* hard registers: the original has x in t0 and width in t4 (global-alloc ranks the prim pointer first) */
    register s32 x asm("$8") = x_start;
    register s32 width asm("$12") = count;
    WorkArea *wa = work_area_ptr;
    PolyGT4Rgb *p = wa->packet;
    s32 w;
    s32 tpage;
    s32 dim;
    s32 full;
    s32 r, g, b;
    s16 left;
    s16 right;
    u8 u_left;
    u8 u_right;
    s32 x_next;

    while (width > 0) {
        w = 0xC0;
        if (width < 0xC0) {
            w = width;
        }
        width -= w;
        tpage = ((x & 0x3FF) >> 6) | 0x120;
        p->tpage = tpage;
        r = rgb & 0xFF;
        g = (rgb >> 8) & 0xFF;
        b = (rgb >> 16) & 0xFF;
        r /= 32;
        g /= 32;
        b /= 32;
        dim = (b << 16) | (g << 8) | r;
        p->rgb1 = dim;
        p->rgb0.rgb = dim;
        r = rgb & 0xFF;
        g = (rgb >> 8) & 0xFF;
        b = (rgb >> 16) & 0xFF;
        full = (b << 16) | (g << 8) | r;
        u_left = x & 0x3F;
        u_right = u_left + w;
        p->rgb3 = full;
        p->rgb2 = full;
        left = x;
        x_next = x + w;
        right = x_next;
        p->x2 = left;
        p->x0 = left;
        p->x3 = right;
        p->x1 = right;
        p->y1 = 0;
        p->y0 = 0;
        p->y3 = 0x20;
        p->y2 = 0x20;
        p->u2 = u_left;
        p->u0 = u_left;
        p->u3 = u_right;
        p->u1 = u_right;
        p->v3 = 0xDE;
        p->v2 = 0xDE;
        p->v1 = 0xDE;
        p->v0 = 0xDE;
        p->len = 0xC;
        p->rgb0.c[3] = 0x3C;    /* setPolyGT4 */
        p->rgb0.c[3] |= 2;      /* setSemiTrans */
        addPrimOnce(ot, p++);

        p->tpage = tpage;
        p->rgb1 = 0x848484;
        p->rgb0.rgb = 0x848484;
        p->rgb3 = 0x40404;
        p->rgb2 = 0x40404;
        p->x2 = left;
        p->x0 = left;
        p->x3 = right;
        p->x1 = right;
        p->y1 = 0;
        p->y0 = 0;
        p->y3 = 0x20;
        p->y2 = 0x20;
        p->u2 = u_left;
        p->u0 = u_left;
        p->u3 = u_right;
        p->u1 = u_right;
        p->v3 = 0xDF;
        p->v2 = 0xDF;
        p->v1 = 0xDF;
        p->v0 = 0xDF;
        p->len = 0xC;
        p->rgb0.c[3] = 0x3C;
        addPrimOnce(ot, p++);
        x = x_next;
    }
    wa->packet = p;
}

/* Draws the backdrop colours of the current light set when they change, then a full-screen
 * draw env into a new packet, linked into ot. */
void light_backdrop_draw(u8 *ot)
{
    u8 env[0x5C];
    WorkArea *wa;
    ScreenPoint *point;
    void *packet;
    s32 colour;

    if (light_sets[light_env_index].point.tex_flag) {
        colour = ((LightSetColours *)light_sets)[light_env_index].colour_a & 0xFFFFFF;
        if (colour != last_env_colour_a) {
            last_env_colour_a = colour;
            light_backdrop_strip_draw(ot, colour, 0, 0x10);
        }
    }
    point = &light_sets[light_env_index].point;
    if (point->out_a || point->out_b) {
        if (light_sets[light_env_index].point.unk_12) {
            colour = ((LightSetColours *)&light_sets[light_env_index])->colour_b & 0xFFFFFF;
            if (colour != last_env_colour_b) {
                last_env_colour_b = colour;
                light_backdrop_strip_draw(ot, colour, 0x10, 0x10);
            }
        }
        colour = ((LightSetColours *)light_sets)[light_env_index].colour_c & 0xFFFFFF;
        if (colour != last_env_colour_c) {
            last_env_colour_c = colour;
            light_backdrop_strip_draw(ot, colour, 0x20, clut_count * 0x10);
        }
    }
    wa = work_area_ptr;
    fn_800B6D8C(env, 0, 0xE0, 0x400, 0x20);
    env[0x16] = 0;
    packet = wa->packet;
    wa->packet = (u8 *)packet + 0x40;
    svc_set_draw_env(packet, env);
    addPrim(ot, packet);
}

/* Uploads a 4x1 16-bit block (eight bytes 0x10, 0x32, ... 0xFE, each step
 * +0x22) to VRAM at (256, 221), then waits for the transfer to finish. */
void vram_pattern_upload(void) {
    s16 rect[4];
    u8 pixels[8];
    s32 value;
    u8 *p;

    value = 0x10;
    p = pixels;
    do {
        *p = value;
        p++;
        value += 0x22;
    } while ((s32) p < (s32) (pixels + 8));

    rect[0] = 0x100;
    rect[1] = 0xDD;
    rect[2] = 4;
    rect[3] = 1;
    svc_load_image(rect, pixels);
    svc_draw_sync(0);
}

/* Adds delta to pchr_count; returns the old count. */
s32 pchr_count_add(s32 delta) {
    s32 unused[2];
    s16 *count = &pchr_count;
    s32 old;

    do {
        old = *count;
        *count = old + delta;
    } while (0);
    return old;
}

/* Drops the empty entries (first word 0) from the end of the pchr table, clearing each, and stores the new
   count. The table starts 4 bytes after pchr_count, so entry count - 1 is at count * sizeof(Pchr) - 0x18. */
void pchr_trim_tail(void) {
    s16 *counter;
    s32 count;
    s32 offset;
    Pchr *entry;

    do {
    } while (0);
    /* hides the address from cse, which would put the constant operand second in the add */
    __asm__("" : "=r"(counter) : "0"(&pchr_count));
    count = *counter;
    offset = count * sizeof(Pchr) - 0x18;
    entry = (Pchr *)((u8 *)counter + offset);
    while (count > 0 && *(s32 *)entry == 0) {
        pchr_clear(entry);
        count--;
        entry--;
    }
    *counter = count + 1;
}

/* Creates slot number model_slot_count of width x height: allocates its three buffers (the first one,
 * width * 1024 bytes, cleared up to the arena end), records pchr_count and its position, and
 * advances the position. Returns the slot number, or -1 when all 32 are used. */
s32 model_slot_new(s32 width, s32 height) {
    s32 index;
    s32 *p;
    s32 *end;
    ModelSlot *slot;

    index = model_slot_count;
    model_slot_width = 0;
    model_slot_height = 0;
    if (index >= 0x20) {
        return -1;
    }
    model_slot_count = index + 1;
    model_slot_width = width;
    model_slot_height = height;
    block_map_buf = arena_alloc(width << 10);
    clut_used_flags = arena_alloc(model_slot_height << 4);
    texel_mask_buf = arena_alloc(model_slot_height << 8);
    p = block_map_buf;
    end = arena_top();
    while (p != end) {
        *p = 0;
        p++;
    }
    slot = model_slot_get(index);
    slot->pchr = pchr_count;
    slot->y = model_atlas_y;
    slot->x = model_atlas_x;
    model_atlas_y += height;
    model_atlas_x += width;
    return index;
}

void model_slot_free_buffers(void) {
    arena_pop(model_slot_height << 8);
    arena_pop(model_slot_height * 0x10);
    arena_pop(model_slot_width << 0xA);
    model_slot_width = 0;
    model_slot_height = 0;
}

/* The pchr of model slot `index`; 0 when the index is negative or above model_slot_count. */
s32 model_slot_pchr(s32 index) {
    if ((index < 0) || (model_slot_count < index)) {
        return 0;
    }
    return model_slot_get(index)->pchr;
}

ModelSlot *model_slot_get(s32 i) {
    return &model_slots[i];
}

void palette_mark_ranges(s16 *list) {
    s32 count;
    s32 lo;
    s32 hi;

    if (list != NULL) {
        count = *list;
        list++;
        while (count > 0) {
            lo = *list++;
            hi = *list++;
            lo /= 16;
            hi /= 16;
            for (; lo <= hi; lo++) {
                clut_used_flags[lo] = 1;
            }
            count--;
        }
    }
}

/* Walks a list: a count, then (start | 0x8000 for flag 2, end) pairs; marks each id in start..end of
 * texel_mask_buf with 1 (or 2 when flagged). */
void id_flags_mark_ranges(s16 *list) {
    s32 count;
    s32 start;
    s32 end;
    s32 value;

    if (list == NULL) {
        return;
    }
    count = list[0];
    list++;
    if (count <= 0) {
        return;
    }
    do {
        start = list[0];
        list++;
        end = list[0];
        list++;
        value = (start & 0x8000) ? 2 : 1;
        start &= 0x7FFF;
        while (start <= end) {
            ((u8 *)texel_mask_buf)[start] = value;
            start++;
        }
        count--;
    } while (count > 0);
}

/* Marks which of the 16 palette indexes a 4-bit image uses, in slot `slot` of clut_used_flags (16 bytes each):
 * the header has big-endian width and height at 4 and 6, the pixels follow at 8. */
void model_slot_mark_palette(u8 *image, s32 slot) {
    u16 be_w = *(u16 *)(image + 4);
    u16 be_h = *(u16 *)(image + 6);
    u32 *pixels = (u32 *)(image + 8);
    u32 *end;
    u8 *used;
    u32 v;

    end = (u32 *)((u8 *)pixels + (((be_w & 0xFF) << 8) | (be_w >> 8)) * (((be_h & 0xFF) << 8) | (be_h >> 8)));
    used = clut_used_flags + slot * 16;
    while (pixels != end) {
        v = *pixels;
        pixels++;
        v >>= 4;
        used[v & 0xF] = 1;
        v >>= 8;
        used[v & 0xF] = 1;
        v >>= 8;
        used[v & 0xF] = 1;
        v >>= 8;
        used[v] = 1;
    }
}

void model_slots_mark_used(s32 *p, s32 slot)
{
    s32 n, count, groups, recs, kind, skip;
    s16 *flags;
    s32 v;

    p++; n = p[-1];
    slot <<= 4;
    for (; n > 0; n--) {
        p++; kind = p[-1];
        if (kind == 0)
            continue;
        if (kind < 0) {
            p++; skip = p[-1];
            p += skip * 3;
            continue;
        }
        p++; skip = p[-1];
        p += skip * 2;
        p++; skip = p[-1];
        p += skip;
        p++; count = p[-1];
        flags = (s16 *)p;
        p = (s32 *)((s16 *)p + ((count + 1) & ~1));
        for (; count > 0; count--) {
            flags++;
            if (flags[-1] < 0)
                continue;
            p++; groups = p[-1];
            for (; groups > 0; groups--) {
                p++; skip = p[-1];
                p += skip;
                p++; recs = p[-1];
                for (; recs > 0; recs--) {
                    v = *(u16 *)p;
                    if (v & 0x8000)
                        clut_used_flags[((v & 0xFF) >> 4) + slot] = 1;
                    p += 7;
                }
            }
        }
    }
}

/* Uploads the used palettes of a model slot's group: gives each used one of
 * the group's 16 palettes a remap index, then writes it to VRAM line by line
 * along with its paired CLUT. */
void model_remap_palettes(s32 slot, s32 group, u16 *src) {
    TexelRemapRow *row;
    Rect lines[32];
    Rect clut_rect;
    Rect *line;
    s32 i, j;
    s32 used;
    s32 x, y;
    s32 mask_offset;
    s32 total;
    void *pair;

    row = &texel_remap_rows[model_slot_get(slot)->y + group];
    row->base = clut_count;
    used = 0;
    for (i = 0; i < 16; i++) {
        row->remap[i] = -0x80;
        if (clut_used_flags[(group << 4) + i] != 0) {
            row->remap[i] = used;
            used++;
        }
    }
    i = 0;
    line = lines;
    total = clut_count;
    row->palette_count = used;
    clut_count = total + used;
    mask_offset = group << 8;
    pair = arena_top();
    /* a goto loop around a do/while(0) body: a for loop lets loop.c hoist
     * clut_rect.w's 16 together with the line loop's (registers differ) */
next_palette:
    do {
        if (row->remap[i] >= 0) {
            x = vram_origin_x(row->base + row->remap[i]);
            y = vram_origin_y(row->base + row->remap[i]);
            palette_buf_write(x, 0x10, src);
            image_buf_write(x, 0x10, (u8 *)texel_mask_buf + mask_offset);
            tint_pixels(0x10, src, (u8 *)texel_mask_buf + mask_offset);
            for (j = 0; j < 32; j++) {
                line[j].x = x;
                line[j].y = y + j;
                line[j].w = 0x10;
                line[j].h = 1;
                svc_load_image(&line[j], src);
            }
            clut_make_pair(0x10, src, pair, (u8 *)texel_mask_buf + mask_offset);
            clut_rect.x = x;
            clut_rect.y = y - 2;
            clut_rect.w = 0x10;
            clut_rect.h = 2;
            svc_load_image(&clut_rect, pair);
            svc_draw_sync(0);
        }
        mask_offset += 0x10;
        src += 0x10;
    } while (0);
    i++;
    if (i < 16) goto next_palette;
}

void model_texel_to_vram(s32 slot, s32 packed, s32 *out_x, s32 *out_y) {
    s32 v = packed >> 8;
    TexelRemapRow *row;
    s32 base;
    s32 idx;

    packed &= 0xFF;
    row = &texel_remap_rows[model_slot_get(slot)->y + v];
    base = row->base;
    idx = packed / 16;
    v = base + row->remap[idx];
    *out_x = vram_origin_x(v) + (packed - idx * 16);
    *out_y = vram_origin_y(v);
}

s32 vram_origin_x(s32 arg0) {
    return (arg0 * 0x10) + 0x20;
}

s32 vram_origin_y(s32 arg0) {
    return 0xE0;
}

/* Remaps the high nibble of each byte of a block (big-endian w*h bytes after an 8-byte header) through the slot row's table. */
void xs3_remap_palette_rows(s32 model, s32 row, u8 *block)
{
    s32 count;
    u16 w;
    u16 h;
    TexelRemapRow *rec;
    u8 *p;
    register s32 b asm("$3"); /* pinned: original keeps the byte in v1 */
    ModelSlot *slot;

    slot = model_slot_get(model);
    w = *(u16 *)(block + 4);
    h = *(u16 *)(block + 6);
    p = block + 8;
    count = (((w & 0xFF) << 8) | (w >> 8)) * (((h & 0xFF) << 8) | (h >> 8));
    rec = &texel_remap_rows[slot->y + row];
    while (count > 0) {
        b = *p;
        count--;
        row = rec->remap[b >> 4];
        *p = (b & 0xF) + (row << 4);
        p++;
    }
}

/* Build a 1/8-scale map of an image (one byte per 8x8 block: the top-left pixel's high nibble),
 * 32 bytes per row, at map `index` of block_map_buf (0x400 bytes each). */
/* K&R: tex_block_upload calls it with only the image, leaving its own index in a1. */
void tex_block_build_map(image, index)
TexBlockHeader *image;
s32 index;
{
    s32 width;
    s32 w;
    s32 h;
    s32 x;
    s32 y;
    u8 *map;
    u8 *src;
    u8 *row;

    width = ((image->width & 0xFF) << 8) | (image->width >> 8);
    map = (u8 *)block_map_buf + (index << 10);
    w = width / 8;
    h = (((image->height & 0xFF) << 8) | (image->height >> 8)) / 8;
    src = image->pixels;
    y = 0;
    while (y < h) {
        row = map + y * 32;
        for (x = 0; x < w; x++) {
            row[x] = *src >> 4;
            src += 8;
        }
        y++;
        src += w * 56;
    }
}

/* Uploads a texture block to VRAM: records its cell in keyframe_cells, packs
   8-bit pixels to 4-bit when mode is 0, then LoadImage. */
void tex_block_upload(s32 slot, s32 index, s32 kind, u8 *block, s32 mode)
{
    KeyframeCell *cell;
    s32 height;
    s32 cellNo;
    s32 *src;
    s32 *end;
    u8 *dst;
    u8 *data;
    s32 pitch;
    s32 word;
    s32 nibLo;
    s32 nibHi;
    s32 byte0;
    s32 byte1;
    s32 x;
    s32 y;
    s16 rect[4];

    if (mode == 0) {
        tex_block_build_map((TexBlockHeader *)block);
    } else {
        xs3_remap_palette_rows(slot, kind, block);
    }
    cell = &keyframe_cells[model_slot_get(slot)->x + index];
    cell->value = mode;
    cell->angle = 0;
    cell->pad = kind;
    /* slot is dead here: its variable holds the width (matches the register reuse) */
    slot = swap16(((TexBlockHeader *)block)->width);
    height = swap16(((TexBlockHeader *)block)->height);
    cellNo = cell_block_alloc(slot, height, mode);
    if (cellNo < 0) {
        return;
    }
    cell->angle = cellNo;
    if (mode == 0) {
        data = arena_top();
        src = (s32 *)((TexBlockHeader *)block)->pixels;
        end = (s32 *)((u8 *)src + slot * height);
        dst = data;
        while (src != end) {
            word = *src++;
            nibLo = word & 0xF;
            word >>= 4;
            nibHi = word & 0xF0;
            byte0 = nibLo + nibHi;
            word >>= 12;
            nibLo = word & 0xF;
            word >>= 4;
            nibHi = word & 0xF0;
            byte1 = nibLo + nibHi;
            dst[0] = byte0;
            dst[1] = byte1;
            dst += 2;
        }
        pitch = slot / 4;
    } else {
        data = ((TexBlockHeader *)block)->pixels;
        pitch = (u32)slot >> 1;
    }
    x = grid_cell_index(cellNo);
    y = cell_index_offset(cellNo);
    rect[0] = x;
    rect[1] = y;
    rect[2] = pitch;
    rect[3] = height;
    svc_load_image(rect, data);
    svc_draw_sync(0);
}

void keyframe_lookup(s32 slot, s32 index, s32 *out_a, s32 *out_b, s32 *out_value) {
    KeyframeCell *rec;

    rec = &keyframe_cells[model_slot_get(slot)->x + index];
    *out_value = rec->value;
    *out_a = grid_cell_index(rec->angle);
    *out_b = cell_index_offset(rec->angle);
}

extern PchrBank pchr_bank __asm__("pchr_count");
void pchr_bank_load(s32 slot, s32 row, s32 cell_base, s32 *data) {
    s32 count;
    s32 i;
    s32 nhalfs;
    Pchr *entry;
    s16 *halfs;
    TexelRemapRow *rows;
    KeyframeCell *cells;
    s32 v;
    s32 kind;
    s32 n;
    s32 groups;
    s32 nprims;
    PchrPrim *prim;
    u8 u8_min;
    s32 clut;
    s32 base;
    s32 vv;
    s32 cellNo;
    s32 mode;
    s32 a, b, c;
    s32 u0, v0, w, h;
    u8 *texel;
    s32 page;
    s32 idx;

    rows = &texel_remap_rows[model_slot_get(slot)->y];
    cells = &keyframe_cells[model_slot_get(slot)->x + cell_base];
    data++;
    i = 0;
    entry = &pchr_bank.table[pchr_bank.count];
    count = data[-1];

    for (; i < count; i++, entry++) {
        pchr_clear(entry);
        kind = (data += 1)[-1];
        entry->unk_0C = 0;
        entry->bounds_radius = kind;
        if (kind == 0) {
            continue;
        }
        if (kind < 0) {
            entry->unk_0C = data;
            n = (data += 1)[-1];
            data += n * 3;
            continue;
        }
        *(s32 **)&entry->unk_00 = data;
        n = (data += 1)[-1];
        data += n * 2;
        *(s32 **)&entry->link = data;
        n = (data += 1)[-1];
        data += n;
        entry->data = data;
        nhalfs = (data += 1)[-1];
        halfs = (s16 *)data;
        data = (s32 *)((s16 *)data + ((nhalfs + 1) & ~1));
        for (; nhalfs > 0; nhalfs--) {
            if ((halfs += 1)[-1] < 0) {
                continue;
            }
            groups = (data += 1)[-1];
            for (; groups > 0; groups--) {
                n = (data += 1)[-1];
                data += n;
                nprims = (data += 1)[-1];
                prim = (PchrPrim *)data;
                for (; nprims > 0; nprims--, prim++) {
                    prim->rgb[0] *= 3;
                    prim->rgb[1] *= 3;
                    prim->rgb[2] *= 3;
                    prim->rgb[3] *= 3;
                    if (prim->clut & 0x8000) {
                        idx = prim->tpage;
                        prim->tpage = (idx & 0x8000) | ((s32)((idx & 0x3000U) >> 7) | 4);
                        clut = (u8)prim->clut;
                        base = rows[row].base + rows[row].remap[clut / 16];
                        clut &= 0xF;
                        clut |= 0xDD00;
                        prim->clut = (vram_origin_y(base) << 6) | ((vram_origin_x(base) >> 4) & 0x3F);
                        prim->c.clut4[0] = clut;
                        prim->c.clut4[1] = clut;
                        prim->c.clut4[2] = clut;
                        prim->c.clut4[3] = clut;
                        prim->tex.word = 0xE2000000;
                        continue;
                    }
                    idx = prim->tpage & 0xF;
                    mode = cells[idx].value;
                    if (mode == 0) {
                        u8_min = prim->c.uv[0];
                        if (prim->c.uv[2] < u8_min) u8_min = prim->c.uv[2];
                        base = u8_min;
                        if (prim->c.uv[4] < base) base = prim->c.uv[4];
                        u8_min = prim->c.uv[1];
                        if (prim->c.uv[3] < u8_min) u8_min = prim->c.uv[3];
                        vv = u8_min;
                        if (prim->c.uv[5] < vv) vv = prim->c.uv[5];
                        if (prim->rgb[3] != 0) {
                            if (prim->c.uv[6] < base) base = prim->c.uv[6];
                            if (prim->c.uv[7] < vv) vv = prim->c.uv[7];
                        }
                        base >>= 3;
                        vv >>= 3;
                        base &= prim->tex.b.w - 1;
                        vv &= prim->tex.b.h - 1;
                        base += prim->tex.b.u_base;
                        vv += prim->tex.b.v_base;
                        page = ((cell_base + idx) << 10) + (s32)block_map_buf;
                        texel = (u8 *)((vv << 5) + page);
                        base = texel[base];
                        base = rows[cells[idx].pad].base + rows[cells[idx].pad].remap[base];
                    } else {
                        base = rows[cells[idx].pad].base;
                    }
                    prim->clut = (vram_origin_y(base) << 6) | ((vram_origin_x(base) >> 4) & 0x3F);
                    cellNo = cells[idx].angle;
                    idx = prim->tpage;
                    a = cell_index_offset(cellNo);
                    b = grid_cell_index(cellNo);
                    c = cell_index_offset(cellNo);
                    prim->tpage = (idx & 0x8000) | (((mode & 3) << 7) | ((idx & 0x3000U) >> 7) | ((a & 0x100) >> 4)
                                                   | ((b & 0x3FF) >> 6) | ((c & 0x200) << 2));
                    base = grid_cell_sub_index(cellNo, mode);
                    vv = cell_index_plain(cellNo, mode);
                    u0 = prim->tex.b.u_base << 3;
                    v0 = prim->tex.b.v_base << 3;
                    w = prim->tex.b.w << 3;
                    h = prim->tex.b.h << 3;
                    if (prim->tex.b.w == 32) {
                        prim->c.uv[0] += base;
                        prim->c.uv[2] += base;
                        prim->c.uv[4] += base;
                        prim->c.uv[6] += base;
                    } else {
                        u0 += base;
                    }
                    if (prim->tex.b.h == 32) {
                        prim->c.uv[1] += vv;
                        prim->c.uv[3] += vv;
                        prim->c.uv[5] += vv;
                        prim->c.uv[7] += vv;
                    } else {
                        v0 += vv;
                    }
                    prim->tex.word = 0xE2000000 | (((v0 & 0xFF) >> 3) << 15) | (((u0 & 0xFF) >> 3) << 10)
                                     | ((((-h) & 0xFF) >> 3) << 5) | (((-w) & 0xFF) >> 3);
                }
                data = (s32 *)prim;
            }
        }
    }
    i = 0;
    entry = &pchr_bank.table[pchr_bank.count];
    for (; i < count; i++) {
        v = entry[i].bounds_radius;
        if (v < 0) {
            Pchr *src;
            v &= 0x7FFF;
            src = (Pchr *)(v * sizeof(Pchr) + (u32)entry);
            entry[i].bounds_radius = model_bounds_radius(src->bounds_radius, entry[i].unk_0C);
            *(s32 *)&entry[i].unk_00 = *(s32 *)&src->unk_00;
            *(s32 *)&entry[i].link = *(s32 *)&src->link;
            entry[i].data = src->data;
            entry[i].unk_1A = pchr_bank.count + v;
        }
    }
    pchr_bank.count += count;
}

/* Calls pchr_bank_load(slot, row, cell_base, data) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * The original is hand-written asm: the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void pchr_bank_load_scratch(s32 slot, s32 row, s32 cell_base, s32 *data) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    pchr_bank_load(slot, row, cell_base, data);
    SCRATCH_STACK_LEAVE_BELOW();
}

/* Bounding radius of a vertex table ({count; 12-byte records with s16 x, y, z}), each axis extent grown by offset. */
s32 model_bounds_radius(s32 offset, s32 *table) {
    s32 n;
    ModelVert *v;
    s32 max_x, min_x, max_y, min_y, min_z, max_z;
    s32 val;

    table++;
    n = table[-1];
    v = (ModelVert *)table;
    max_x = 0;
    min_x = 0;
    max_y = 0;
    min_y = 0;
    max_z = 0;
    min_z = 0;

    for (; n > 0; n--, v++) {
        val = (s16)v->x;
        if (min_x < val) val = min_x;
        min_x = val;
        val = (s16)v->x;
        if (val < max_x) val = max_x;
        max_x = val;
        val = (s16)v->y;
        if (min_y < val) val = min_y;
        min_y = val;
        val = (s16)v->y;
        if (val < max_y) val = max_y;
        max_y = val;
        val = (s16)v->z;
        if (min_z < val) val = min_z;
        min_z = val;
        val = (s16)v->z;
        if (val < max_z) val = max_z;
        max_z = val;
    }
    max_x = (ABS(max_x + offset) < ABS(min_x - offset)) ? ABS(min_x - offset) : ABS(max_x + offset);
    max_y = (ABS(max_y + offset) < ABS(min_y - offset)) ? ABS(min_y - offset) : ABS(max_y + offset);
    max_z = (ABS(max_z + offset) < ABS(min_z - offset)) ? ABS(min_z - offset) : ABS(max_z + offset);
    return isqrt(length_sq(max_x, max_y, max_z));
}

/* Sets unk_14 of `count` pchr entries from `first` (both clamped to 0..pchr_count) to unk_10 * 2048 / divisor
 * (clamped to 0..0x7FFF; divisor outside 1..256 means 0x60) and clears unk_16; entries with unk_10 == 0 are skipped. */
void pchr_set_link_range(s32 first, s32 count, s32 divisor) {
    s16 *total;
    Pchr *table;
    Pchr *entry;
    s32 offset;
    s32 value;

    if ((u32)(divisor - 1) >= 0x100) {
        divisor = 0x60;
    }
    count += first;
    total = &pchr_count;
    first = MAX(MIN(first, *total), 0);
    count = MAX(MIN(count, *total), 0);
    count -= first;
    offset = first * sizeof(Pchr);
    table = (Pchr *)(total + 2);
    entry = (Pchr *)((u8 *)table + offset);
    while (count > 0) {
        value = entry->bounds_radius;
        if (value != 0) {
            value = (value << 11) / divisor;
            value = MAX(MIN(value, 0x7FFF), 0);
            entry->unk_14 = value;
            entry->far_bias = 0;
        }
        count--;
        entry++;
    }
}

/* Set unk_14/unk_16 of the pchr entries [first, first+count); both zero: pchr_set_link_range. */
void pchr_set_link_offsets(s32 first, s32 count, s32 a, s32 b) {
    s16 *total;
    Pchr *entry;
    Pchr *table;
    s32 offset;
    s32 end;
    s32 pad[2]; /* unused: the original frame is 8 bytes larger */

    if (a == 0 && b == 0) {
        pchr_set_link_range(first, count, 0);
        return;
    }
    count += first;
    total = &pchr_count;
    first = MAX(MIN(first, *total), 0);
    end = MAX(MIN(count, *total), 0);
    count = end - first;
    if (end - 1 + b >= *total) {
        /* two pad NULs: the original string takes 32 bytes */
        printf("FarBias Over!!:$%x (%d,%d) \n\0\0", first, a);
        b = 0;
    }
    offset = first * sizeof(Pchr);
    table = (Pchr *)(total + 2);
    entry = (Pchr *)((u8 *)table + offset);
    while (count > 0) {
        count--;
        entry->unk_14 = a;
        entry->far_bias = b;
        entry++;
    }
}

/* Read the two halfwords at 0x14/0x16 of pchr_table entry `index`. */
void pchr_get_link(s32 index, s32 *a, s32 *b) {
    Pchr *entry = &pchr_table[index];

    *a = entry->unk_14;
    *b = entry->far_bias;
}

extern PchrBank pchr_bank __asm__("pchr_count");
void pchr_set_value_range(s32 start, s32 end, s32 value) {
    s32 count;
    Pchr *p;

    end += start;
    count = pchr_bank.count;
    start = CLAMP_HI(start, count) < 0 ? 0 : CLAMP_HI(start, count);
    end = CLAMP_HI(end, count) < 0 ? 0 : CLAMP_HI(end, count);
    end -= start;
    p = &pchr_bank.table[start];
    while (end > 0) {
        p->unk_12 = value;
        end--;
        p++;
    }
}

s32 fn_800CDE8C(s32 index) {
    return pchr_table[index].unk_12;
}

/* Sets unk_18 of `count` pchr entries from `first` (both clamped to 0..pchr_count) to `value`.
 * The table is addressed from pchr_count (pchr_table is the symbol 4 bytes after it). */
void pchr_set_angle_range(s32 first, s32 count, s32 value) {
    s16 *total = &pchr_count;
    Pchr *table;
    Pchr *entry;
    s32 offset;

    count += first;
    first = MAX(MIN(first, *total), 0);
    count = MAX(MIN(count, *total), 0);
    count -= first;
    offset = first * sizeof(Pchr);
    table = (Pchr *)(total + 2);
    entry = (Pchr *)((u8 *)table + offset);
    while (count > 0) {
        entry->angle = value;
        count--;
        entry++;
    }
}

/* Field 0 of entry `index` of d_8013B6BC. */
s32 pchr_get_angle(s32 index) {
    return pchr_table[index].angle;
}

/* Scales a counted list of 12-byte records (an s32 count, then the records) by scale/4096; svec_list_scale with a 12-byte stride. */
void scaled_rec_list_scale(s32 *tbl, s32 scale) {
    ScaledRec *v;
    ScaledRec *end;
    s16 x, y, z;

    tbl++;
    end = (ScaledRec *)tbl + tbl[-1];
    v = (ScaledRec *)tbl;
    while (v != end) {
        x = (u32)(v->v[0] * scale) >> 12;
        y = (u32)(v->v[1] * scale) >> 12;
        z = (u32)(v->v[2] * scale) >> 12;
        v++;
        v[-1].v[0] = x;
        v[-1].v[1] = y;
        v[-1].v[2] = z;
    }
}

/* Scales a counted list of SVECTORs (an s32 count, then the vectors) by scale/4096.
 * `end` is computed from `tbl` before `v = tbl`: that keeps the original's copy. */
void svec_list_scale(s32 *tbl, s32 scale) {
    SVECTOR *v;
    SVECTOR *end;
    s16 x, y, z;

    tbl++;
    end = (SVECTOR *)tbl + tbl[-1];
    v = (SVECTOR *)tbl;
    while (v != end) {
        x = (u32)(v->vx * scale) >> 12;
        y = (u32)(v->vy * scale) >> 12;
        z = (u32)(v->vz * scale) >> 12;
        v++;
        v[-1].vx = x;
        v[-1].vy = y;
        v[-1].vz = z;
    }
}

/* pchr_count followed by pchr_table, addressed from one base */
void pchr_scale_range(s32 start, s32 count, u32 scale)
{
    PchrScaleRec *rec;
    s32 n;

    n = count;
    if (scale != 0x1000 && (n += start, scale <= 0x4000)) {
        start = NOT_NEGATIVE(MIN(start, ((PchrScaleTable *)&pchr_count)->count));
        n = NOT_NEGATIVE(MIN(n, ((PchrScaleTable *)&pchr_count)->count));
        n -= start;
        rec = &((PchrScaleTable *)&pchr_count)->recs[start];
        for (; n > 0; n--, rec++) {
            if (rec->locked == 0 && rec->tracks != NULL) {
                svec_list_scale(rec->tracks, scale);
            }
            if (rec->list != NULL) {
                scaled_rec_list_scale(rec->list, scale);
            }
            rec->scale = (s32)(rec->scale * scale) / 4096;
        }
    }
}

/* Copies a counted SVECTOR list ({s32 count; SVECTOR v[count];}) into dst,
 * scaling each axis by a 4.12 factor; returns the end of the written list. */
SVECTOR *svec_list_copy_scaled(SVECTOR *src, s32 *dst, s32 scale_x, s32 scale_y, s32 scale_z)
{
    SVECTOR *out;
    SVECTOR *end;
    s32 count;
    s32 x, y, z;
    u16 out_z;

    src = (SVECTOR *)((s32 *)src + 1);
    count = *((s32 *)src - 1);
    *dst++ = count;
    out = (SVECTOR *)dst;
    end = out + count;
    for (; out != end; out++) {
        x = src->vx;
        y = src->vy;
        z = src->vz;
        x = x * scale_x / 4096;
        y = y * scale_y / 4096;
        out_z = z * scale_z / 4096;
        src++;
        out->vx = x;
        out->vy = y;
        out->vz = out_z;
    }
    return out;
}

/* Appends a copy of pchr entry `index` at the end of the table (a new link, and a scaled value from three
 * clamped parameters), and returns the new entry's index. Returns `index` when the table is full, 0 for
 * a bad index. */
s32 pchr_clone(s32 index, s32 a, s32 b, s32 c) {
    s16 *total = &pchr_count;
    s32 count;
    Pchr *table;
    Pchr *src;
    Pchr *dst;
    s32 biggest;
    s32 offset;

    FAKE_OPAQUE(total);
    if (*total > 0x600) {
        return index;
    }
    count = *total;
    if (index <= 0 || count - 1 < index) {
        return 0;
    }
    offset = index * sizeof(Pchr); /* before table: sched1 keeps this order (FINDINGS) */
    table = (Pchr *)(total + 2);
    src = (Pchr *)(offset + (s32)table);
    dst = (Pchr *)(count * sizeof(Pchr) + (s32)table);
    *dst = *src;
    dst->far_bias = 0;
    if (*(s32 *)src != 0) {
        a = MAX(MIN(a, 0x7FFF), 0);
        b = MAX(MIN(b, 0x7FFF), 0);
        c = MAX(MIN(c, 0x7FFF), 0);
        *(s32 *)dst = heap_get_top();
        heap_set_top((s32)svec_list_copy_scaled(*(SVECTOR **)src, *(s32 **)dst, a, b, c));
        biggest = a;
        if (biggest < b) {
            biggest = b;
        }
        if (biggest < c) {
            biggest = c;
        }
        dst->bounds_radius = src->bounds_radius * biggest / 0x1000;
    }
    (*(u16 *)&pchr_count)++;
    return count;
}

/* Copies pchr entry `link` (header words, data, unk_10) into the live entries of [first, first+count), clamped to
 * 0..pchr_count; an entry with a sequence (unk_0C) records `link` in unk_1A and gets unk_10 from model_bounds_radius. */
void pchr_copy_range(s32 first, s32 count, s32 link) {
    s16 *total;
    s32 n;
    Pchr *table;
    Pchr *src;
    Pchr *dst;
    s32 offset;

    if (link > 0) {
        total = &pchr_count;
        n = *total;
        if (link <= n) {
            count += first;
            offset = (link & 0x7FF) * sizeof(Pchr);
            table = (Pchr *)(total + 2);
            src = (Pchr *)((u8 *)table + offset);
            first = MAX(MIN(first, n), 0);
            count = MAX(MIN(count, n), 0);
            count -= first;
            dst = &table[first & 0x7FF];
            while (count > 0) {
                if (dst->bounds_radius != 0) {
                    ((PchrWords *)dst)->head = ((PchrWords *)src)->head;
                    ((PchrWords *)dst)->link = ((PchrWords *)src)->link;
                    dst->data = src->data;
                    dst->bounds_radius = src->bounds_radius;
                    if (dst->unk_0C != 0) {
                        dst->unk_1A = link;
                        dst->bounds_radius = model_bounds_radius(src->bounds_radius, dst->unk_0C);
                    }
                }
                count--;
                dst++;
            }
        }
    }
}

s16 fn_800CE5C0(s32 i) {
    return pchr_table[i].unk_1A;
}

/* Sets (value bit set) or clears the top bit of the entries a pchr's table lists, one bit of `value` each. */
void pchr_set_entry_flags(s32 id, u32 value) {
    Pchr *p = &pchr_table[id & 0x7FF];
    s32 *base;
    s16 *index;
    s32 *entry;
    s32 count;
    s32 i;
    u32 word;
    s32 unused;

    if (p->bounds_radius != 0) {
        base = p->data;
        if (base != 0) {
            base++;
            i = base[-1];
            index = (s16 *)base;
            count = i;
            for (i = 0; i < count; i++) {
                entry = base + *index++;
                word = *entry;
                if (value & 1) {
                    word |= 0x80000000;
                } else {
                    word &= 0x7FFFFFFF;
                }
                *entry = word;
                value >>= 1;
            }
        }
    }
}
