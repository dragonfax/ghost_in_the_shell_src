/* view: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

static inline void scale_reset(s16 *scale) {
    scale[0] = 0x1000;
    scale[1] = 0x1000;
}
static inline void vector_clear(VECTOR *v) {
    v->vx = 0;
    v->vy = 0;
    v->vz = 0;
    v->pad = 0;
}
static inline void svector_clear(SVECTOR *v) {
    v->vx = 0;
    v->vy = 0;
    v->vz = 0;
    v->pad = 0;
}
static inline void rect_set_size(s16 *rect, s32 w, s32 h) {
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = w;
    rect[3] = h;
}
static inline void point_set_half(s16 *point, s16 w, s16 h) {
    point[0] = w / 2;
    point[1] = h / 2;
}
static inline void colour_clear(CVECTOR *c) {
    *(s32 *)c = 0;
}
/* Resets all cameras and views (views to full screen, no camera). */
void cam_view_reset_all(void) {
    s32 i;
    s16 *screen; /* stage_screen_w, stage_screen_h */
    s32 none;

    for (i = 0; i < 8; i++) {
        Camera *cam = &cameras[i];
        cam->user_count = 0;
        cam->rec_index = -1;
        scale_reset(cameras[i].scale);
        vector_clear(&cam->pos);
        svector_clear(&cameras[i].rot);
    }
    i = 0;
    none = -1;
    screen = &stage_screen_w;
    for (; i < 16; i++) {
        View *view = &views[i];
        view->on = 0;
        view->parent = none;
        view->camera = none;
        view->depth = 0;
        rect_set_size(&views[i].x, screen[0], screen[1]);
        point_set_half(&views[i].unk_10, screen[0], screen[1]);
        rect_set_size(&views[i].unk_14, screen[0], screen[1]);
        colour_clear(&views[i].colour);
        colour_clear(&views[i].colour_b);
        colour_clear(&views[i].colour_c);
        view->ot = 0;
    }
}

void scale_vec_set(s32 a, s32 b, s32 c) {
    s16 *p = scale_vec;

    FAKE_OPAQUE(p);
    p[0] = a;
    p[1] = b;
    p[2] = c;
}

s32 cam_point_in_box(s32 idx, s32 x, s32 y, s32 z)
{
    Camera *cam;
    s32 i;
    s32 radius, below, above;
    s32 d;
    LightSet *boxes;

    boxes = light_sets;
    radius = boxes[idx].v[0];
    below = -boxes[idx].v[1];
    above = boxes[idx].v[2];
    for (i = 0; i < 8; i++) {
        cam = &cameras[i];
        if (cam->user_count != 0 && cam->rec_index == idx) {
            d = x - cam->pos.vx;
            if (ABS(d) <= radius) {
                d = z - cam->pos.vz;
                if (ABS(d) <= radius) {
                    d = y - cam->pos.vy;
                    if (below < d && d < above)
                        return 1;
                }
            }
        }
    }
    return 0;
}

s32 view_order_build(s16 *out) {
    ViewSortEntry *order = scratch_alloc(0x40);
    s32 count = 0;
    s32 i = 0;
    s32 j;
    s32 view;
    s32 depth;

    View *v = views;

    for (; i < 16; i++, v++) {
        if (v->on != 0) {
            order[count].view = i;
            order[count].depth = v->depth;
            count++;
        }
    }
    for (i = 1; i < count; i++) {
        view = order[i].view;
        depth = order[i].depth;
        j = i - 1;
        while (j >= 0 && depth < order[j].depth) {
            order[j + 1] = order[j];
            j--;
        }
        order[j + 1].view = view;
        order[j + 1].depth = depth;
    }
    for (i = 0; i < count; i++) {
        out[i] = order[i].view;
    }
    scratch_top -= 0x40;
    return count;
}

/* Passes each id in view_order (count from view_order_build) through view_draw, threading the result. */
void view_draw_sorted(void *obj) {
    s16 *id = view_order;
    s32 count = view_order_build(view_order);
    s32 i;

    for (i = 0; i < count; i++) {
        obj = view_draw(obj, *id);
        id++;
    }
}

/* Sets up views[idx] once a frame (its parent first): its rect in VRAM, scale, projection origin,
 * ordering tables, and, with a camera, the projection scale, depth scale and rotations. */
void view_frame_setup(s32 idx) {
    ViewSetup *view = &((ViewSetup *)views)[idx];
    s32 n;
    s32 val; /* one variable for the x ratio, the right/bottom edge, the larger scale and the shift */
    s32 scale_y;
    s32 origin;
    s32 left, right;
    s32 top, bottom;
    s32 t, hi, lo, start;
    WorkArea *wa;
    Camera *cams;
    u32 *p;
    u32 *end;
    u32 next;
    u32 mask;
    s32 lim, depth;

    if (view->ready != 0) {
        return;
    }
    view->ready = 1;
    n = view->parent;
    if (n < 0) {
        s32 sw, sh;
        view->box_scale_x = 0x1000;
        view->box_scale_y = 0x1000;
        do {
        } while (0);
        sw = stage_screen_w;
        sh = stage_screen_h;
        view->box.x = 0;
        view->box.y = 0;
        view->box.w = sw;
        view->box.h = sh;
    } else {
        view_frame_setup(n);
        view->box_scale_x = ((ViewSetup *)views)[n].scale_x;
        view->box_scale_y = ((ViewSetup *)views)[n].scale_y;
        view->box = ((ViewSetup *)views)[n].vram;
    }

    left = view->unk_14 + view->x;
    right = left + view->clip_w;
    val = (view->clip_w << 12) / view->w;
    origin = view->origin_offset_x * val / 4096; /* unused: the original computes it too */
    origin = view->box.x + ((view->origin_offset_x * view->clip_w / view->w + view->x) * view->box_scale_x) / 4096;
    view->origin_x = origin;
    left = view->box.x + left * view->box_scale_x / 4096;
    right = view->box.x + right * view->box_scale_x / 4096;
    view->scale_x = val * view->box_scale_x / 4096;

    top = view->unk_16 + view->y;
    bottom = top + view->clip_h;
    scale_y = (view->clip_h << 12) / view->h;
    origin = view->origin_offset_y * scale_y / 4096; /* unused */
    origin = view->box.y + ((view->origin_offset_y * view->clip_h / view->h + view->y) * view->box_scale_y) / 4096;
    view->origin_y = origin;
    top = view->box.y + top * view->box_scale_y / 4096;
    bottom = view->box.y + bottom * view->box_scale_y / 4096;
    view->scale_y = scale_y * view->box_scale_y / 4096;
    view->scale_z = 0x1000;

    view->area_x = left;
    view->area_y = top;
    view->area_w = right - left;
    view->area_h = bottom - top;

    /* clip the area to the box */
    start = view->area_x;
    lo = view->box.x;
    val = start + view->area_w;
    hi = lo + view->box.w;
    t = start;
    if (hi < t) t = hi;
    if (lo < t) start = t; else start = lo;
    if (hi < val) val = hi;
    t = lo;
    if (t < val) t = val;
    view->vram.x = start;
    view->vram.w = t - start;

    start = view->area_y;
    lo = view->box.y;
    val = start + view->area_h;
    hi = lo + view->box.h;
    t = start;
    if (hi < t) t = hi;
    if (lo < t) start = t; else start = lo;
    t = val;
    if (hi < t) t = hi;
    val = lo;
    if (val < t) val = t;
    view->vram.y = start;
    view->vram.h = val - start;

    view->origin_x -= view->vram.x;
    view->origin_y -= view->vram.y;

    wa = work_area_ptr;
    view->prim = wa->packet;
    wa->packet = (u8 *)wa->packet + 0x10;
    mask = 0xFFFFFF;
    p = view->prim;
    end = p + 3;
    next = ((u32)p + 4) & mask;
    do {
        *p++ = next;
        next += 4;
    } while (end != p);
    *p = mask;

    n = view->camera;
    view->ot = NULL;
    if (n < 0 || cameras[n].rec_index < 0) {
        return;
    }
    wa = work_area_ptr;
    view->ot = wa->packet;
    wa->packet = (u8 *)wa->packet + 0x82C;
    mask = 0xFFFFFF;
    p = view->ot;
    end = p + 0x20A;
    next = ((u32)p + 4) & mask;
    do {
        *p++ = next;
        next += 4;
    } while (end != p);
    *p = mask;

    cams = cameras;
    val = view->scale_x;
    scale_y = view->scale_y;
    view->cam_scale[0] = cams[n].scale[0] * val / 4096;
    view->cam_scale[1] = cams[n].scale[1] * scale_y / 4096;
    view->cam_scale[2] = 0x1000;
    if (val < scale_y) {
        val = scale_y;
    }
    lim = 0x7FFF;
    gte_set(LZCS, MAX(CLAMP_HI(val, lim), 1));
    gte_nop();
    gte_nop();
    do {
        gte_get(LZCR, val);
        val = 32 - val;
        if (val >= 13) {
            val--;
        }
        view->depth_unit = 1 << val;
        val = 0x1000000 >> val;
        __asm__ volatile("");
        depth = MAX(CLAMP_HI(val, lim), 0);
    } while (0);
    view->depth_scale = depth;
    FAKE_USE(val);
    vec_scale_mvmva((s32 *)view->cam_scale, scale_vec, view->cam_scale);
    rot_matrix_b(view->rot, cams[n].rot.vy, cams[n].rot.vx, cams[n].rot.vz);
    rot_matrix_b(view->rot_b, 0, cams[n].rot.vx, cams[n].rot.vz);
}

/* Clear word 0x28 of all 16 entries, then run view_frame_setup on each active one. */
void view_update_all(void) {
    View *last;
    View *rec;
    s32 i;

    for (i = 15, last = &views[15]; i >= 0; i--, last--) {
        last->ready = 0;
    }
    for (i = 0, rec = views; i < 16; i++, rec++) {
        if (rec->on != 0) {
            view_frame_setup(i);
        }
    }
}

/* Copies the VRAM rect `rect` (x, y, w, h) to the screen at (0, 0) as textured quads at most 0x80 pixels
 * wide, each grey-shaded by `shade`, between two draw-mode packets and a texture-window reset, all linked
 * into `ot` from the packet pool `buf`. Returns the new pool top. */
u8 *vram_rect_show(u8 *ot, u8 *buf, s16 *rect, s32 shade) {
    PrimDrMode *mode;
    DrTwin *twin;
    PolyFT4 *poly;
    PolyFT4 *last;
    s32 u, v;
    s32 x, y, w, h;
    s32 n;
    s32 code; /* FAKE: set at the loop top so loop.c hoists 0x2C (and not 9) */
    s16 bottom; /* FAKE: an s16 copy of h made early in the loop orders the hoisted copies */
    s32 screen_x;

    mode = (PrimDrMode *)buf;
    buf += 8;
    mode->len = 1;
    mode->cmd = 0xE1000600;
    addPrim(ot, mode);
    poly = (PolyFT4 *)buf;
    screen_x = 0;
    x = rect[0];
    w = rect[2];
    y = rect[1];
    h = rect[3];
    u = x & 0x3F;
    v = y & 0xFF;
    while (w > 0) {
        if (w > 0x80) {
            n = 0x80;
        } else {
            n = w;
        }
        code = 0x2C;
        poly->len = 9;
        poly->tpage = (2 << 7) | (0 << 5) | ((y & 0x100) >> 4) | ((x & 0x3FF) >> 6) | ((y & 0x200) << 2);
        bottom = h;
        poly->x0 = poly->x2 = screen_x;
        poly->u1 = poly->u3 = u + n;
        poly->b0 = shade;
        poly->g0 = shade;
        poly->r0 = shade;
        poly->code = code;
        poly->x1 = poly->x3 = screen_x + n;
        poly->y0 = poly->y1 = 0;
        poly->y2 = poly->y3 = bottom;
        poly->u0 = poly->u2 = u;
        poly->v0 = poly->v1 = v;
        poly->v2 = poly->v3 = v + h;
        last = poly;
        poly++;
        addPrim(ot, last);
        screen_x += n;
        w -= n;
        x += n;
    }
    buf = (u8 *)poly;
    twin = (DrTwin *)buf;
    buf += sizeof(DrTwin);
    twin->len = 2;
    twin->code[0] = 0xE2000000;
    twin->code[1] = 0;
    addPrim(ot, twin);
    mode = (PrimDrMode *)buf;
    buf += 8;
    mode->len = 1;
    mode->cmd = 0xE1000400;
    addPrim(ot, mode);
    return buf;
}

/* Builds a textured rect (colour scaled by `scale`/0x40) and a DR_MODE primitive from the pool at
 * `prim_buf`, links both into the OT, and returns the new pool top. When scale != 0x40 the rgb word
 * must be non-zero, otherwise nothing is emitted. */
void *prim_tex_rect_add(void *ot, void *prim_buf, void *src, s32 scale, void *rgb) {
    PrimTexRect *rect;
    PrimDrMode *mode_prim;
    s32 blend_mode;
    s32 scaled;

    if (scale == 0x40) {
        blend_mode = 0;
    } else {
        if ((*(u32 *)rgb & 0xFFFFFF) == 0) {
            return prim_buf;
        }
        blend_mode = 1;
    }
    rect = prim_buf;
    prim_buf = (u8 *)prim_buf + 0x10;
    scaled = ((Rgb *)rgb)->r * scale;
    if (scaled < 0) {
        scaled += 0x7F;
    }
    rect->r = scaled >> 7;
    scaled = ((Rgb *)rgb)->g * scale;
    if (scaled < 0) {
        scaled += 0x7F;
    }
    rect->g = scaled >> 7;
    scaled = ((Rgb *)rgb)->b * scale;
    if (scaled < 0) {
        scaled += 0x7F;
    }
    rect->b = scaled >> 7;
    rect->len = 3;
    rect->code = 0x62;
    rect->x = 0;
    rect->y = 0;
    rect->uv = ((TexInfo *)src)->uv;
    rect->clut = ((TexInfo *)src)->clut;
    addPrim(ot, rect);

    mode_prim = prim_buf;
    prim_buf = (u8 *)prim_buf + 8;
    mode_prim->len = 1;
    mode_prim->cmd = (blend_mode << 5) | 0xE1000400;
    addPrim(ot, mode_prim);
    return prim_buf;
}

/* Draws the view's border as two polylines just outside its rectangle, relative to the box: the left
 * and top edges, then the bottom and right edges. Style 3 darkens the first (colour / 4), style 2 the
 * second, for a sunken or raised frame. Returns the next free packet. */
void *view_border_draw(u8 *ot, u8 *buf, ViewDraw *v) {
    PrimLineF3 *p;
    PrimLineF3 *first;
    PrimLineF3 *second;
    s32 word, colour;
    s32 left, top, right, bottom, right_out;
    s16 right_edge;
    s16 top_edge;
    s32 gap;

    gap = 1;
    p = (PrimLineF3 *)buf;
    word = *(s32 *)v->border_rgb;
    left = v->x - (v->box_x + gap);
    right = left + v->w;
    right_out = right + 1;
    colour = word;
    top = v->y - (v->box_y + gap);
    bottom = top + v->h + 1;
    if ((colour >> 24) == 3) {
        colour = (colour & 0xFCFCFC) >> 2;
    }
    p->colour.word = colour;
    p->len = 5;
    p->colour.c.code = 0x48;
    p->term = 0x55555555;
    p->x0 = p->x1 = left;
    p->x2 = right;
    p->y0 = bottom;
    top_edge = top;
    p->y1 = p->y2 = top_edge;
    first = p++;
    right_edge = right_out;
    addPrim(ot, first);

    colour = word;
    if ((colour >> 24) == 2) {
        colour = (colour & 0xFCFCFC) >> 2;
    }
    p->x0 = left + 1;
    p->colour.word = colour;
    p->len = 5;
    p->colour.c.code = 0x48;
    p->term = 0x55555555;
    p->x2 = right_edge;
    p->x1 = right_edge;
    p->y0 = p->y1 = bottom;
    p->y2 = top_edge;
    second = p++;
    addPrim(ot, second);
    return p;
}

static inline void link_prim(u8 *ot, u8 *tag, u8 *self) {
    u32 link, shifted;

    ot_link_load(link, ot);
    shifted = (u32)self << 8;
    ot_link_store(tag, link);
    ot_link_store(ot, shifted);
}

/* Emits the two fill tiles of view `v` (along its right and bottom edges, as thick as bits 24-27 of
 * the fill colour word, semi-transparent when bit 31 is set) into the pool at `buf`; returns the new
 * pool top. */
void *prim_view_edge_tiles(u8 *ot, u8 *buf, ViewDraw *v) {
    PrimTile *p;
    PrimTile *tile;
    PrimTile *last;
    s32 colour;
    s32 edge_w, edge_h;
    s32 thick_w, thick_h;
    s32 x, y, w, h;

    colour = *(s32 *)v->fill_rgb;
    edge_w = (s16)v->edge[2];
    thick_h = (colour >> 24) & 0xF;
    thick_w = thick_h;
    if (edge_w < thick_h) {
        thick_w = edge_w;
    }
    edge_h = (s16)v->edge[3];
    if (edge_h < thick_h) {
        thick_h = edge_h;
    }
    if (thick_w <= 0 || thick_h <= 0) {
        return buf;
    }
    p = (PrimTile *)buf;
    w = thick_w;
    h = edge_h;
    x = (s16)v->edge[0] + edge_w - v->box_x;
    y = (s16)v->edge[1] + thick_h - v->box_y;
    p->colour.word = colour;
    p->len = 3;
    p->colour.c.code = 0x60;
    if (colour < 0) {
        p->colour.c.code |= 2;
    }
    p->x = x;
    p->y = y;
    p->w = w;
    p->h = h;
    tile = p++;
    link_prim(ot, (u8 *)tile, buf);

    h = thick_h;
    x = (s16)v->edge[0] + w - v->box_x;
    y = (s16)v->edge[1] + (s16)v->edge[3] - v->box_y;
    w = (s16)v->edge[2] - w;
    p->colour.word = colour;
    p->len = 3;
    p->colour.c.code = 0x60;
    if (colour < 0) {
        p->colour.c.code |= 2;
    }
    p->x = x;
    p->y = y;
    p->w = w;
    p->h = h;
    last = p;
    p++;
    addPrim(ot, last);
    return p;
}

void *view_draw(u8 *ot, s32 index) {
    ViewDraw *v = (ViewDraw *)&views[index];
    RenderWork *wa = (RenderWork *)work_area_ptr;
    u8 *tab;
    u32 *w;
    u32 next;
    u32 mask;
    s32 unused[4];
    u32 *end;
    s32 x;
    s32 tile;
    u8 *env;
    u16 *rect;
    LightSet *rec;
    u8 *prim;
    u8 *tp;
    u8 *mp;

    if (v->w <= 0 || v->h <= 0) {
        return ot;
    }
    cur_view_index = index;
    light_env_index = 0;
    cur_camera_index = v->camera;
    if (cur_camera_index >= 0) {
        light_env_index = camera_light_env_table[v->camera * 16];
    }
    tab = wa->packet;
    mask = 0xFFFFFF;
    w = (u32 *)tab;
    end = (u32 *)(tab + 0x20);
    next = ((u32)tab + 4) & mask;
    wa->packet = tab + 0x24;
    do {
        *w++ = next;
        next += 4;
    } while (end != w);
    *w = mask;
    draw_view_entries_scratch(v->prim + 4);
    link_prim(tab + 0x18, v->prim + 0xC, v->prim);
    if (v->ctx != 0) {
        tex_upload_set_flag(light_sets[light_env_index].point.tex_flag);
        fn_800D5370(light_sets[light_env_index].point.unk_12);
        fn_800D425C(light_sets[light_env_index].point.flag);
        shadow_pass_draw_scratch(work_area_ptr, tab + 8);
        point_light_setup_draw(work_area_ptr, tab + 0xC);
        cylinder_draw_scratch(work_area_ptr, tab + 0x10);
        point_light_glow_draw(v->ctx + 0x24);
        light_table_init();
        rec = light_sets;
        point_search_set(rec[light_env_index].v[0], rec[light_env_index].v[1], rec[light_env_index].v[2]);
        scene_models_project_scratch();
        spark_list_collect_near();
        gte_light_setup(v->ctx);
        light_backdrop_draw(tab);
        link_prim(tab + 0x14, v->ctx + 0x828, v->ctx);
    }

    x = 0;
    if (v->border) {
        wa->packet = view_border_draw(tab + 0x1C, wa->packet, v);
        x = 1;
        v->edge[0]--;
        v->edge[1]--;
        v->edge[2] += 2;
        v->edge[3] += 2;
    }
    if (v->fill) {
        wa->packet = prim_view_edge_tiles(tab + 0x1C, wa->packet, v);
        x = 1;
    }
    if (x) {
        env = scratch_top;
        fn_800B6D8C(env, wa->off_x + v->box_x, wa->off_y + v->box_y, v->box_w, v->box_h);
        prim = wa->packet;
        wa->packet = prim + 0x40;
        svc_set_draw_env(prim, env);
        addPrim(tab + 0x1C, prim);
    }
    env = scratch_top;
    fn_800B6D8C(env, wa->off_x + v->x, wa->off_y + v->y, v->w, v->h);
    x = v->mode;
    rect = (u16 *)&v->x;
    switch (x) {
    case 0x80:
        tile = 1;
        if (v->camera >= 0) {
            env[0x19] = (light_sets[light_env_index].unk_06[10] << 7) / 132;
            env[0x1A] = (light_sets[light_env_index].unk_06[11] << 7) / 132;
            env[0x1B] = (light_sets[light_env_index].unk_06[12] << 7) / 132;
        } else {
            env[0x19] = (v->colour[0] << 7) / 132;
            env[0x1A] = (v->colour[1] << 7) / 132;
            env[0x1B] = (v->colour[2] << 7) / 132;
        }
        break;
    case 0x40:
        wa->packet = prim_tex_rect_add(tab + 4, wa->packet, env, 0x40, v->colour);
        tile = 0;
        break;
    case 0:
        tile = 0;
        break;
    default:
        wa->packet = prim_tex_rect_add(tab + 4, wa->packet, env, x, v->colour);
        wa->packet = vram_rect_show(tab + 4, wa->packet, (s16 *)env, 0x80 - x);
        tile = 0;
        break;
    }
    if (tile) {
        tp = wa->packet;
        wa->packet = tp + 0x10;
        tp[3] = 3;
        tp[7] = 0x60;
        tp[4] = env[0x19];
        tp[5] = env[0x1A];
        tp[6] = env[0x1B];
        *(s16 *)(tp + 8) = 0;
        *(s16 *)(tp + 0xA) = 0;
        *(u16 *)(tp + 0xC) = rect[2];
        *(u16 *)(tp + 0xE) = rect[3];
        addPrim(tab + 4, tp);
    }
    mp = wa->packet;
    wa->packet = mp + 0xC;
    mp[3] = 2;
    *(u32 *)(mp + 4) = 0xE6000001;
    *(u32 *)(mp + 8) = 0;
    addPrim(tab + 4, mp);
    prim = wa->packet;
    wa->packet = prim + 0x40;
    svc_set_draw_env(prim, env);
    addPrim(tab + 4, prim);
    link_prim(ot, tab + 0x20, tab);
    return tab + 0x20;
}

/* Sets the three bytes (r, g, b) of colour `index` of record `rec` (the 24-bit colours at +8 of a LightSet). */
void rec_set_colour(s32 rec, s32 index, s32 r, s32 g, s32 b) {
    u8 *c = (u8 *)&light_sets[rec] + 8 + index * 4;
    c[0] = r;
    c[1] = g;
    c[2] = b;
}

void rec_set_point(s32 index, s32 x, s32 y, s32 z) {
    ScreenPoint *point = &light_sets[index].point;

    point->scale = 0x80;
    point->x = x;
    point->y = y;
    point->z = z;
    point_calc_projection(x, y, 0x80, &point->out_a, &point->out_b);
}

void rec_set_vec(s32 index, s32 x, s32 y, s32 z) {
    LightSet *rec = &light_sets[index];

    rec->v[0] = x;
    rec->v[1] = y;
    rec->v[2] = z;
}

void rec_set_tex_flag(s32 index, s32 value) {
    light_sets[index].point.tex_flag = value;
}

/* Sets the halfword at +0x7E of record `id` (in the screen point's unknown bytes). */
void rec_set_on(s32 id, s32 on) {
    *(s16 *)((u8 *)&light_sets[id] + 0x7E) = on;
}

void rec_set_flag(s32 index, s32 value) {
    light_sets[index].point.flag = value;
}

/* Sets row `index` of light set `set`'s direction matrix to the direction
   given by yaw and pitch, scaled to 0x400:
   x = cos(pitch) * sin(yaw), y = -sin(pitch), z = cos(pitch) * cos(yaw).
   The three hard-register locals give the original's register choice:
   the matrix base in a0, the row offset in v0 and z in v1. */
void light_set_dir_from_angles(s32 set, s32 index, s32 yaw, s32 pitch) {
    s32 pitch_off = (pitch & 0xFFF) * 4;
    s32 yaw_off = (yaw & 0xFFF) * 4;
    s32 cos_pitch = *(s16 *)((char *)cos_table + pitch_off);
    s16 cos_yaw = *(s16 *)((char *)cos_table + yaw_off);
    s32 z_product = cos_pitch * cos_yaw;
    s32 set_off = set * sizeof(LightSet);
    register char *dirs asm("$4") = (char *)light_sets[0].light_dir;
    s32 sin_yaw = *(s16 *)((char *)rcossin_tbl + yaw_off);
    s32 x_product = cos_pitch * sin_yaw;
    char *matrix = set_off + dirs;
    register s32 row_off asm("$2") = index * sizeof(light_sets[0].light_dir[0]);
    s16 *row = (s16 *)(matrix + row_off);
    s16 sin_pitch = *(u16 *)((char *)rcossin_tbl + pitch_off);
    register s32 z asm("$3");

    row[1] = -(sin_pitch >> 2);
    z = z_product >> 14;
    row[2] = z;
    row[0] = x_product >> 14;
}

#if STAGE == 13
char str_ctlt_spr_so3[16] = "ctlt_spr.so3";

char str_ctlt_spr_grc[16] = "ctlt_spr.grc";

char str_ctlt_spr_clt[16] = "ctlt_spr.clt";

char str_ctlt_objcb4[16] = "ctlt_obj.cb4";
#endif

void rec_set_part(s32 rec, u32 field, s32 x, s32 y, s32 z) {
    LightColourMatrix *mid = (LightColourMatrix *) ((u8 *) &light_sets[rec] + 0x34);

    switch (field) {
    case 0:
    case 1:
    case 2:
        mid->m[0][field] = x;
        mid->m[1][field] = y;
        mid->m[2][field] = z;
        return;
    case 3:
        mid->w[0] = x;
        mid->w[1] = y;
        mid->w[2] = z;
        return;
    case 4:
    case 5:
    case 6: {
        LightVector *tri = (LightVector *) ((u8 *) &light_sets[rec] + 0x54);
        tri = (LightVector *) ((u8 *) tri + (field * 8 - 0x20));
        tri->x = x;
        tri->y = y;
        tri->z = z;
        return;
    }
    default:
        return;
    }
}

void cam_set_rec(s32 index, s32 value) {
    cameras[index].rec_index = value;
}

/* Sets both fields of entry `index` of d_80136594. */
void cam_set_scale(s32 index, s32 a, s32 b) {
    s16 *pair = cameras[index].scale;

    pair[0] = a;
    pair[1] = b;
}

void cam_set_pos(s32 index, s32 x, s32 y, s32 z) {
    VECTOR *pos = &cameras[index].pos;

    pos->vx = x;
    pos->vy = y;
    pos->vz = z;
}

/* Set the three halfwords of entry `index` (note b, a order). */
void cam_set_rot(s32 index, s32 yaw, s32 pitch, s32 roll) {
    SVECTOR *rot = &cameras[index].rot;

    rot->vx = pitch;
    rot->vy = yaw;
    rot->vz = roll;
}

/* Turns view `view` on (on = 1) or off. */
void view_set_on(s32 view, s32 on) {
    views[view].on = (s16) on;
}

/* Sets the halfword at +2 of view `index`. */
void view_set_parent(s32 index, s32 value) {
    *(s16 *)&views[index].parent = value;
}

void view_set_depth(s32 index, s32 value) {
    views[index].depth = value;
}

/* Moves a view to another camera: drops the old camera's user count (not below 0) and raises the new one's.
 * The old camera's address is built as offset + base (the original's register order). */
void view_set_camera(s32 view, s32 camera)
{
    s16 users;
    Camera *cam;
    s32 old;

    old = views[view].camera;
    if (old != camera) {
        if (old >= 0) {
            cam = (Camera *)(old * sizeof(Camera));
            cam = (Camera *)((u8 *)cam + (s32)cameras);
            users = cam->user_count;
            if (users > 0) {
                cam->user_count = users - 1;
            }
        }
        views[view].camera = camera;
        if (camera >= 0) {
            cam = &cameras[camera];
            cam->user_count++;
        }
    }
}

void set_view_offset(s32 view, s32 x, s32 y) {
    views[view].x = x;
    views[view].y = y;
}

/* Sets the size (w, h) of a view: made even, limited to 2..0x3FFF. */
void view_set_size(s32 index, s32 w, s32 h) {
    s32 offset;

    w = (w + 1) & ~1;
    h = (h + 1) & ~1;
    w = MAX(w < 0x4000 ? w : 0x3FFF, 2);
    h = MAX(h < 0x4000 ? h : 0x3FFF, 2);
    offset = index * sizeof(View);
    *(s16 *)((u8 *)views + offset + 0xC) = w;
    *(s16 *)((u8 *)views + offset + 0xE) = h;
}

void view_set_pivot(s32 index, s32 a, s32 b) {
    s32 offset = index * sizeof(View);

    *(s16 *)((u8 *)views + offset + 0x10) = a;
    *(s16 *)((u8 *)views + offset + 0x12) = b;
}

/* Sets two halfwords at +0x14 of view `index`. */
void fn_800C94D8(s32 index, s32 a, s32 b) {
    s32 offset = index * sizeof(View);

    *(s16 *)((u8 *)views + offset + 0x14) = a;
    *(s16 *)((u8 *)views + offset + 0x16) = b;
}

void view_set_clip_size(s32 view, s32 w, s32 h)
{
    s32 max_w;
    s32 max_h;

    w = (w + 1) & ~1;
    max_w = views[view].w * 2;
    h = (h + 1) & ~1;
    if (max_w > 0x7FFE) {
        max_w = 0x7FFE;
    }
    max_h = views[view].h * 2;
    if (max_h > 0x7FFE) {
        max_h = 0x7FFE;
    }
    w = MAX(MIN(w, max_w), 0);
    h = MAX(MIN(h, max_h), 0);
    views[view].clip_w = w;
    views[view].clip_h = h;
}

void view_set_colour(s32 index, s32 r, s32 g, s32 b, s32 cd) {
    CVECTOR *colour = &views[index].colour;

    colour->r = r;
    colour->g = g;
    colour->b = b;
    colour->cd = cd;
}

/* Set the four bytes at the start of entry `index` of the table at 0x8013669C. */
void view_set_colour_b(s32 index, s32 r, s32 g, s32 b, s32 cd) {
    CVECTOR *colour = &views[index].colour_b;

    colour->r = r;
    colour->g = g;
    colour->b = b;
    colour->cd = cd;
}

void view_set_colour_c(s32 index, s32 r, s32 g, s32 b, s32 cd) {
    CVECTOR *colour = &views[index].colour_c;

    colour->r = r;
    colour->g = g;
    colour->b = b;
    colour->cd = cd;
}
