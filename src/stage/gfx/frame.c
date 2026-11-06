/* frame: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

s32 arena_free_bytes(void) {
    return arena_size - (s32)arena_top_ptr + (s32)arena_base; /* bytes free in the arena */
}

/* Sets up the arena (arena_base, size arena_size, top arena_top_ptr) and empties it. */
void arena_init(u8 *base, s32 size) {
    arena_base = base;
    arena_size = size & ~7;
    arena_reset();
}

void ot_depth_set(s32 arg0) {
    frame_ot_depth = arg0 + 2;
}

/* Stores up to 3 tile positions (at least 1): tile_pos[i] = pos[i], tile_pos_next[i] = the next one, wrapping. */
void tile_positions_set(s32 count, void *positions)
{
    TilePos *pos = positions;
    s32 i;
    s32 lim;
    s32 n;

    n = count < 4 ? count : 3;
    lim = count < 4 ? count : 3;
    if (lim <= 0) {
        n = 1;
    }
    count = n;
    tile_pos_count = count;
    for (i = 0; i < count; i++) {
        ((TilePos *)tile_pos)[i] = pos[i];
        ((TilePos *)tile_pos_next)[i] = pos[(i + 1) % count];
    }
}

/* Fills `out` with (x, y) pairs for a row of 2 or 3 tiles: `size` is rounded up to 0x100, 0x140 or 0x200 and
 * is the step in x (0x140 or less gives 3 tiles). Returns the number of pairs. */
s32 tile_row_positions(s16 *out, s32 x, s32 y, s32 size, s32 unused_h) {
    s32 unused[2];
    s32 count;
    s32 i;

    if (size < 0x101) {
        size = 0x100;
    } else if (size < 0x141) {
        size = 0x140;
    } else {
        size = 0x200;
    }
    count = 2;
    if (size < 0x141) {
        count = 3;
    }
    i = 0;
    if (count != 0) {
        do {
            out[0] = x;
            out[1] = y;
            out += 2;
            i++;
            x += size;
        } while (i < count);
    }
    return count;
}

void tile_row_draw(s32 x, s32 y, s32 w, s32 h) {
    s16 rect[8];

    tile_positions_set(tile_row_positions(rect, x, y, w, h), rect);
}

void screen_area_set(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    screen_rect_x = arg0;
    screen_rect_y = arg1;
    stage_screen_w = arg2;
    stage_screen_h = arg3;
}

void video_mode_set(s32 arg0) {
    video_mode_id = arg0;
}

void text_color_set(s32 arg0, s32 arg1, s32 arg2) {
    fade_color_r = arg0;
    fade_color_g = arg1;
    fade_color_b = arg2;
}

/* Starts a frame: steps to the next work area of d_80121DF4 (frame_rec_index cycles through
   tile_pos_count of them), flips the arena's double buffer (frame_buf_parity) and lays out this
   frame's half of the free arena: the ordering table (frame_ot_depth entries, each linked to the
   next and the last one terminated) followed by the packet area. */
void frame_begin(void) {
    WorkArea *wa;
    u8 *buf;
    s32 half;
    /* a hard register keeps `links <<= 2` a second set of its own (the original's order and v1) */
    register s32 links asm("$3");
    u32 *ot;
    u32 *end;
    u32 link;
    u32 terminator;

    frame_rec_index++;
    if (frame_rec_index >= tile_pos_count) {
        frame_rec_index = 0;
    }
    buf = arena_top_ptr;
    half = arena_base + arena_size - buf;
    half = (half / 2) & ~3;
    frame_buf_parity ^= 1;
    wa = &((WorkArea *)d_80121DF4)[frame_rec_index];
    work_area_ptr = wa;
    if (frame_buf_parity != 0) {
        buf += half;
    }
    terminator = 0xFFFFFF; /* end of list, also the 24-bit address mask */
    wa->ot = (u32 *)buf;
    wa->packet_end = buf + half;
    wa->list_cursor = (s32)(buf + half);
    links = frame_ot_depth - 1;
    wa->packet_start = (u32 *)buf + frame_ot_depth;
    wa->packet = (u32 *)buf + frame_ot_depth;
    ot = wa->ot;
    if (links != 0) {
        links <<= 2;
        end = (u32 *)(links + (s32)ot);
        link = (u32)(ot + 1) & terminator;
        do {
            *ot = link;
            ot++;
            link += sizeof(u32);
        } while (end != ot);
    }
    *ot = terminator;
    cam_pair_count = 0;
}

/* Waits out the vblank callback, then hands the engine's packet to the display for a frame. */
void frame_present(void) {
    while (set_vblank_callback(NULL) != NULL) {
    }
    svc_draw_sync(0);
    wait_vblank_count(1);
    frame_work_area = (s32) work_area_ptr;
    if (tile_pos_count < 3) {
        put_disp_env_at_vblank(frame_env_build());
        set_vblank_count(0);
        wait_vblank_count(1);
    } else {
        put_disp_env_at_vblank(frame_env_build());
        set_vblank_count(0);
    }
    cam_frame_draw();
}

void *frame_env_build(void) {
    WorkArea *work = work_area_ptr;
    UiRecord *rec;
    s16 *pair;

    if (debug_cam_flag != 0) {
        rec = &ui_rec_table[frame_rec_index];
        pair = debug_cam_speed_table[debug_cam_speed_index];
        fn_800B6D78(rec, debug_cam_pan_x, debug_cam_pan_y, pair[0], pair[1]);
    } else {
        u16 cursor = *(u16 *)&screen_rect_y;
        rec = (UiRecord *) work;
        *(u16 *)&rec->unk_00[8] = *(u16 *)&screen_rect_x;
        rec->rect_y = cursor + 2;
    }
    ui_rec_advance(rec);
    if (first_frame_flag == 0) {
        rec = NULL;
        first_frame_flag += 1;
    }
    return rec;
}

/* Draws the camera's queued image pairs, then the fade tile over the screen, then links both into the OT. */
void cam_frame_draw(void) {
    WorkArea *wa;
    VramRect *rect;
    PrimTile *tile;
    IntPair *pair;
    u8 *fade_src;
    u8 *env;
    s32 i;

    wa = (WorkArea *)frame_work_area;
    if (cam_pair_count == 0) {
        rect = wa->packet;
        wa->packet = rect + 1;
        rect->x = wa->draw_x;
        rect->y = wa->draw_y;
        rect->w = 4;
        rect->h = 1;
        svc_load_image(rect, rect);
    }
    pair = cam_pairs;
    for (i = 0; i < cam_pair_count;) {
        svc_load_image((void *)pair->a, (void *)pair->b);
        i++;
        pair++;
    }
    cam_pair_count = 0;
    if (pause_state != 0) {
        pause_frame_copy();
    }
    if (cam_fade_level < 0x1000) {
        cam_fade_draw(wa);
    }
    fade_src = (u8 *)&fade_color_r;
    wa->fade_r = *fade_src;
    tile = wa->packet;
    wa->fade_g = (u8)fade_color_g;
    wa->fade_b = (u8)fade_color_b;
    wa->packet = tile + 1;
    tile->len = 3;
    tile->colour.c.code = 0x60;
    tile->colour.c.r = *fade_src;
    tile->colour.c.g = (u8)fade_color_g;
    tile->x = 0;
    tile->y = 0;
    tile->colour.c.b = (u8)fade_color_b;
    tile->w = wa->width;
    tile->h = wa->height;
    addPrim(wa->ot + 1, tile);
    /* A 0x40-byte DR_ENV packet, set up with the work area's drawing environment. */
    env = wa->packet;
    wa->packet = env + 0x40;
    svc_set_draw_env(env, &wa->draw_x);
    addPrim(wa->ot + 1, env);
    /* Without this barrier GCC reuses the ot value from the addPrim above; the original reloads it. */
    __asm__ volatile("" : : : "memory");
    svc_draw_otag(wa->ot);
}

#if STAGE == 2
RectU night_vision_rect = {0x300, 0x0, 0x100, 0xD8}; /* the night vision copy rect */
#endif

/* Rodata the original keeps before cam_fade_draw: the CLUT/UV pair its cell primitives take. */
const u32 cam_fade_tex_window[2] = {0x00000000, 0x01000100};

/* Screen fade overlay: a full-screen tinted rect, then 64-pixel-wide strips
 * covering the screen, then the two cell primitives that draw the scroll. The
 * do { } while (0) lines are scheduling barriers: they keep the stores in the
 * order the original has them (see docs/MATCH_RULES.md). */
void cam_fade_draw(WorkArea *work) {
    u32 *ot_tail;
    PrimBgRect *bg;
    PrimFadeStrip *strip;
    void *cell;
    s32 left;
    s32 x;
    s32 w;
    s32 scale;
    s32 blue;
    s32 shade;

    ot_tail = (u32 *)((u8 *)work->ot + (frame_ot_depth * 4 - 8));
    if (((u16)cam_fade_r | (u16)cam_fade_g | (u16)cam_fade_b) != 0) {
        bg = work->packet;
        work->packet = (u8 *)bg + sizeof(PrimBgRect);
        bg->len = 3;
        bg->code = 0x62;
        scale = 0x1000 - cam_fade_level;
        bg->r = (cam_fade_r * scale) >> 12;
        bg->g = (cam_fade_g * scale) >> 12;
        blue = cam_fade_b * scale;
        bg->x = 0;
        bg->y = 0;
        do {
        } while (0);
        bg->b = blue >> 12;
        bg->w = stage_screen_w;
        do {
        } while (0);
        bg->h = stage_screen_h;
        addPrim(ot_tail, bg);
    }

    left = stage_screen_w;
    x = 0;
    do {
        w = 0x40;
        if (left < 0x40) {
            w = left;
        }
        strip = work->packet;
        work->packet = (u8 *)strip + sizeof(PrimFadeStrip);
        strip->len = 4;
        strip->code = 0x64;
        shade = (u16)cam_fade_level >> 5;
        strip->x = x;
        strip->u = 0;
        strip->y = 0;
        strip->v = 0;
        strip->w = w;
        do {
        } while (0);
        strip->b = shade;
        strip->g = shade;
        strip->r = shade;
        left -= w;
        strip->h = stage_screen_h;
        addPrim(ot_tail, strip);

        cell = work->packet;
        work->packet = (u8 *)cell + 0xC;
        fn_800B6DB4(cell, 1, 0,
                    ((work->scroll_y >> 4) & 0x10) | 0x120 | (((work->scroll_x + x) & 0x3FF) >> 6) | ((work->scroll_y & 0x200) * 4),
                    cam_fade_tex_window);
        addPrim(ot_tail, cell);
        x += w;
    } while (left > 0);

    cell = work->packet;
    work->packet = (u8 *)cell + 0xC;
    svc_set_draw_area(cell, &work->draw_x);
    addPrim(ot_tail, cell);

    cell = work->packet;
    work->packet = (u8 *)cell + 0xC;
    svc_set_draw_offset(cell, &work->scroll_x);
    addPrim(ot_tail, cell);
}

/* While video_mode_id is set, sets the record's flag and moves unk_0A on by 0x18. */
void ui_rec_advance(UiRecord *rec) {
    if (video_mode_id != 0) {
        rec->flag = 1;
        rec->rect_y += 0x18;
    }
}

/* Sets up record i of table: its two areas at the tile positions tile_pos[i] / tile_pos_next[i],
   sized to the screen, with the rect (screen_rect_x, screen_rect_y + 2, w, h) at 0x08 between. */
void ui_rec_setup(void *table, s32 i) {
    UiRec84 *rec;
    s16 *screen_w;
    u16 cursor;
    u16 w;
    u16 *rect_y;

    rec = (UiRec84 *)((u8 *)table + i * sizeof(UiRec84));
    screen_w = &stage_screen_w;
    fn_800B6D78(&rec->draw, tile_pos[i][0], tile_pos[i][1], *screen_w, stage_screen_h);
    *(u16 *)&rec->draw.unk_00[8] = screen_rect_x;
    cursor = screen_rect_y;
    w = *screen_w;
    /* through a pointer: a direct draw.unk_0A store is scheduled differently */
    rect_y = &rec->draw.rect_y;
    *rect_y = cursor + 2;
    *(u16 *)&rec->draw.rect_size[0] = w;
    *(u16 *)&rec->draw.rect_size[2] = stage_screen_h;
    ui_rec_advance(&rec->draw);
    fn_800B6D8C(rec->disp, tile_pos_next[i][0], tile_pos_next[i][1], *screen_w, stage_screen_h);
    rec->unk_2D = 0;
    rec->unk_2E = 0;
    rec->unk_2F = 0;
}

void cam_reset(void) {
    s32 i;

    frame_buf_parity = 0;
    frame_rec_index = 0;
    first_frame_flag = 0;
    for (i = 0; i < tile_pos_count; i++) {
        ui_rec_setup(d_80121DF4, i);
    }
    debug_cam_flag = 0;
    debug_cam_speed_index = 0;
    debug_cam_pan_y = 0;
    debug_cam_pan_x = 0;
    cam_pair_count = 0;
    cam_fade_b = 0;
    cam_fade_g = 0;
    cam_fade_r = 0;
    cam_fade_level = 0x1000;
    pause_state_set(0);
}

s32 debug_cam_on(void) {
    return debug_cam_flag;
}

void debug_cam_set(s32 arg0) {
    debug_cam_flag = arg0 & 1;
}

void debug_cam_speed_next(void) {
    s16 temp_v0;

    temp_v0 = (u16) debug_cam_speed_index + 1;
    debug_cam_speed_index = temp_v0;
    if (temp_v0 >= 5) {
        debug_cam_speed_index = 0;
    }
}

s32 debug_cam_speed(void) {
    return debug_cam_speed_index;
}

void debug_cam_pan(s32 dx, s32 dy) {
    s16 x = (u16)debug_cam_pan_x + dx;
    debug_cam_pan_x = x;
    debug_cam_pan_y = (u16)debug_cam_pan_y + dy;
    x = MAX(MIN(x, 0x400), -0x400);
    debug_cam_pan_x = x;
    debug_cam_pan_y = MAX(MIN(debug_cam_pan_y, 0x200), -0x200);
}

/* Appends (a, b) to a list of up to 32 pairs. */
void cam_pair_add(s32 a, s32 b) {
    if (cam_pair_count < 32) {
        cam_pairs[cam_pair_count].a = a;
        cam_pairs[cam_pair_count].b = b;
        cam_pair_count++;
    }
}

void cam_offset_set(s32 x, s32 y, s32 z) {
    cam_fade_r = x;
    cam_fade_g = y;
    cam_fade_b = z;
}

/* Sets cam_fade_level to value limited to 0..0x1000. */
void cam_fade_set(s32 value) {
    s32 result = cap_1000(value);

    if (cap_1000(value) < 0) {
        result = 0;
    }
    cam_fade_level = result;
}

#if STAGE != 1
extern s16 cam_fade_level;
#endif

s16 cam_fade_level_get(void) {
    return cam_fade_level;
}

s32 pause_state_get(void) {
    return pause_state;
}

void pause_state_set(s32 arg0) {
    pause_state = arg0;
    pause_prev_work_area = 0;
}

/* Screen copy at the frame flip: on the first frame (no previous work area) clears the screen with a black
   TILE between mask-bit commands; afterwards draws the previous frame's drawing area onto this one as
   0x80 px wide semi-transparent POLY_FT4 strips. Then resets the texture window and the draw mode. */
void pause_frame_copy(void) {
    WorkArea *prev;
    WorkArea *wa;
    u32 *ot;
    PrimGp0Cmd *mask_off;
    PrimGp0Cmd *mask_on;
    PrimGp0Cmd *tex_window;
    PrimTile *tile;
    PolyFT4 *poly;
    PrimDrMode *mode;
    ScreenSize *screen;
    s16 *screen_h;
    s32 left;
    s32 w;
    s32 x;
    s32 x1;
    u16 dy;
    s32 tpage;
    s32 u;

    if (pause_state != 0) {
        wa = work_area_ptr;
        ot = &wa->ot[frame_ot_depth - 2];
        prev = (WorkArea *)pause_prev_work_area;
        pause_prev_work_area = (s32)wa;
        if (prev == NULL) {
            mask_off = wa->packet;
            wa->packet = mask_off + 1;
            mask_off->len = 2;
            mask_off->code = 0xE6000000;
            mask_off->pad = 0;
            addPrim(ot, mask_off);
            tile = wa->packet;
            wa->packet = tile + 1;
            tile->len = 3;
            tile->colour.c.code = 0x62;
            tile->colour.c.r = 0;
            tile->colour.c.g = 0;
            tile->colour.c.b = 0;
            tile->y = 0;
            tile->x = 0;
            tile->w = ((ScreenSize *)&stage_screen_w)->w;
            tile->h = ((ScreenSize *)&stage_screen_w)->h;
            addPrim(ot, tile);
            mask_on = wa->packet;
            wa->packet = mask_on + 1;
            mask_on->len = 2;
            mask_on->code = 0xE6000001;
            mask_on->pad = 0;
            addPrim(ot, mask_on);
        } else {
            screen = (ScreenSize *)&stage_screen_w;
            left = screen->w;
            x = 0;
            if (left > 0) {
                screen_h = &screen->h;
                do {
                    w = left;
                    if (left > 0x80) {
                        w = 0x80;
                    }
                    poly = wa->packet;
                    wa->packet = poly + 1;
                    poly->len = 9;
                    poly->code = 0x2F;
                    dy = prev->draw_y;
                    tpage = (dy >> 4) & 0x10;
                    tpage |= 0x100;
                    tpage |= ((prev->draw_x + x) & 0x3FF) >> 6;
                    tpage |= (dy & 0x200) << 2;
                    poly->tpage = tpage;
                    x1 = x + w;
                    poly->x0 = x;
                    poly->y0 = 0;
                    poly->x1 = x1;
                    poly->y1 = 0;
                    poly->x2 = x;
                    poly->y2 = *screen_h;
                    poly->x3 = x1;
                    poly->y3 = *screen_h;
                    u = x & 0x3F;
                    poly->u0 = u;
                    poly->v0 = 0;
                    poly->u1 = u + w;
                    poly->v1 = 0;
                    poly->u2 = u;
                    poly->v2 = *screen_h;
                    poly->u3 = u + w;
                    poly->v3 = *screen_h;
                    addPrim(ot, poly);
                    left -= w;
                    x = x1;
                } while (left > 0);
            }
        }
        tex_window = wa->packet;
        wa->packet = tex_window + 1;
        tex_window->len = 2;
        tex_window->code = 0xE2000000;
        tex_window->pad = 0;
        addPrim(ot, tex_window);
        mode = wa->packet;
        wa->packet = mode + 1;
        mode->len = 1;
        mode->cmd = 0xE1000420;
        addPrim(ot, mode);
    }
}
