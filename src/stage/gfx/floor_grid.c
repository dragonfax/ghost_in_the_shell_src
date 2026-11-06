/* floor_grid: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

#ifdef NON_MATCHING
/* Fills the 21x21 grid (step 0x800 over -0x5000..0x5000 in x and z, y = 0) of a flat surface with textured quads:
 * keeps two rows of projected FloorVerts in the scratchpad and hands every cell between them to floor_quad_draw.
 * Returns the packet pointer after the quads. C companion of hand-written asm (not compiled): the caller's GTE and
 * HI/LO state is the input (LO = the cell size scale, HI = the clip bounds, VXY1/VXY2/RGB = tpage word, OT
 * base and colour), so it is a parameter block here; the asm also falls straight into floor_quad_draw with $ra set by
 * hand to the loop's continuation (fn_800D5A8C), and keeps $fp and $gp (the scratchpad stack) as its own. */
typedef struct FloorVert {
    s16 z;
    s16 x;
    u32 sxy; /* screen position */
    s16 sz;
    u16 code; /* depth-cue IR0 & 0x7FE0 | clip flags (0x10 near, 1/2 y out, 4/8 x out) */
} FloorVert;

typedef struct GridCtx {
    u8 *packet; /* next free packet */
    u32 *ot;    /* the 7 OT slots the quads are sorted into */
    u32 clip;   /* HI: (height << 16) | width */
} GridCtx;

void floor_quad_draw(GridCtx *ctx, s32 size, FloorVert *tl, FloorVert *tr, FloorVert *bl, FloorVert *br);

/* Projects the point (v->x, 0, v->z) and fills in the screen position, depth and code. */
static void grid_project(FloorVert *v, u32 clip) {
    u32 sxy, sy, sx, code;
    s32 sz, ir0;

    gte_set(VXY0, (u16)v->x);
    gte_set(VZ0, v->z);
    gte_rtps();
    gte_get(SZ3, sz);
    gte_get(IR0, ir0);
    gte_get(SXY2, sxy);
    v->sxy = sxy;
    v->sz = sz;
    code = (sz <= 0x20) << 4;
    sy = sxy >> 16;
    sx = sxy & 0xFFFF;
    if ((s32)clip >> 16 < (s32)sy) {
        code |= (sy >> 15) + 1;
    }
    if ((clip & 0xFFFF) < sx) {
        code |= ((sx >> 15) + 1) << 2;
    }
    v->code = (ir0 & 0x7FE0) | code;
}

void *floor_grid_draw(void *packet) {
    GridCtx ctx;
    FloorVert *prev, *cur, *tmp;
    s32 x, z, size, col;

    mips_mflo(size);
    mips_mfhi(ctx.clip);
    gte_get(VXY2, ctx.ot);
    ctx.packet = packet;
    prev = scratch_alloc(21 * sizeof(FloorVert));
    cur = scratch_alloc(21 * sizeof(FloorVert));
    for (x = -0x5000; x <= 0x5000; x += 0x800) {
        for (z = -0x5000, col = 0; z <= 0x5000; z += 0x800, col++) {
            cur[col].z = z;
            cur[col].x = x;
            grid_project(&cur[col], ctx.clip);
        }
        if (x != -0x5000) {
            for (col = 0; col < 20; col++) {
                floor_quad_draw(&ctx, size, &prev[col], &prev[col + 1], &cur[col], &cur[col + 1]);
            }
        }
        tmp = prev;
        prev = cur;
        cur = tmp;
    }
    scratch_top -= 2 * 21 * sizeof(FloorVert);
    return ctx.packet;
}
#else
INCLUDE_ASM("../src/stage/asm", floor_grid_draw);
#endif

/* hand-written: subroutine saving $ra through $gp, entered by fall-through from floor_grid_draw (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Draws one cell of the grid (corners tl, tr, bl, br, side `size`) as a textured quad, or splits it in four.
 * Culled when all four corners share a clip flag; a cell larger than 0x100 is split when a corner is nearer than
 * its size. Otherwise one POLY_FT4 is built (depth-cued colour, clut from the corners' summed depth cue, uv from
 * the corners' grid position, scaled down by the leading zeros of the cell's size) and sorted into one of the
 * context's OT slots; far cells (cue sum >= 0x4000) are dropped. A split projects the 5 edge midpoints, fixes the
 * 4 edge ones with fn_800D5380 and recurses on the four quarters. C companion of hand-written asm (not compiled):
 * the corners arrive in $t8/$s0/$t9/$t6, the size in $t7, the packet in $t3 (carried through the recursion
 * unchanged by the callee), the recursion saves $ra on the scratchpad stack ($gp) instead of the stack, and it is
 * entered by fall-through from floor_grid_draw with $ra pointing into its own tail. */
void floor_quad_draw(GridCtx *ctx, s32 size, FloorVert *tl, FloorVert *tr, FloorVert *bl, FloorVert *br) {
    s32 cue, shift, lz, u, v, d, slot;
    PolyFT4 *prim;

    if (((*(u32 *)&tl->sz & *(u32 *)&tr->sz & *(u32 *)&bl->sz & *(u32 *)&br->sz) >> 16) & 0x1F) {
        return;
    }
    if (size > 0x100 &&
        (((tl->sz - size) | (tr->sz - size) | (bl->sz - size) | (br->sz - size)) & 0x8000)) {
        FloorVert *mid = scratch_alloc(5 * sizeof(FloorVert)); /* top, left, centre, right, bottom */
        s32 cz = (tl->z + br->z) >> 1;
        s32 cx = (tl->x + br->x) >> 1;

        mid[0].z = cz;
        mid[0].x = tl->x;
        mid[1].z = tl->z;
        mid[1].x = cx;
        mid[2].z = cz;
        mid[2].x = cx;
        mid[3].z = br->z;
        mid[3].x = cx;
        mid[4].z = cz;
        mid[4].x = br->x;
        grid_project(&mid[0], ctx->clip);
        grid_project(&mid[1], ctx->clip);
        grid_project(&mid[2], ctx->clip);
        grid_project(&mid[3], ctx->clip);
        grid_project(&mid[4], ctx->clip);
        fn_800D5380(size, tr, tl, &mid[0]);
        fn_800D5380(size, br, tr, &mid[3]);
        fn_800D5380(size, bl, br, &mid[4]);
        fn_800D5380(size, tl, bl, &mid[1]);
        size >>= 1;
        floor_quad_draw(ctx, size, tl, &mid[0], &mid[1], &mid[2]);
        floor_quad_draw(ctx, size, &mid[0], tr, &mid[2], &mid[3]);
        floor_quad_draw(ctx, size, &mid[1], &mid[2], bl, &mid[4]);
        floor_quad_draw(ctx, size, &mid[2], &mid[3], &mid[4], br);
        scratch_top -= 5 * sizeof(FloorVert);
        return;
    }

    cue = ((tl->code + tr->code) & 0x7FE0) + ((bl->code + br->code) & 0x7FE0);
    if (cue >= 0x4000) {
        return;
    }
    gte_set(IR0, cue >> 2);
    gte_dpcs();
    prim = (PolyFT4 *)ctx->packet;
    prim->len = 9;
    prim->clut = (((cue >> 9) + 0xE0) << 6) | 1;
    gte_get(RGB2, *(u32 *)&prim->r0);
    gte_get(VXY1, *(u32 *)&prim->u1); /* tpage in the high half, u1/v1 set below */
    *(u32 *)&prim->x0 = tl->sxy;
    *(u32 *)&prim->x1 = tr->sxy;
    *(u32 *)&prim->x2 = bl->sxy;
    *(u32 *)&prim->x3 = br->sxy;

    d = (bl->x - tl->x) >> 2;
    u = (tl->x >> 2) & 0x7F;
    v = (*(u16 *)&tl->z >> 2) & 0x7F;
    gte_set(LZCS, d);
    gte_get(LZCR, lz);
    shift = 0x19 - lz;
    if (shift > 2) {
        shift = 2;
    }
    slot = 0;
    if (shift > 0) {
        u >>= shift;
        v >>= shift;
        d >>= shift;
        slot = shift + 3;
    }
    prim->u0 = prim->u1 = u;
    prim->u2 = prim->u3 = u + d;
    prim->v0 = prim->v2 = v;
    prim->v1 = prim->v3 = v + d;
    ctx->packet += sizeof(PolyFT4);
    slot += ((u >> 6) << 1) + (v >> 6);
    addPrim(&ctx->ot[slot], prim);
}
#else
INCLUDE_ASM("../src/stage/asm", floor_quad_draw);
#endif

/* A GTE-drawn pass for the current view, shadow_pass_draw's sibling: when d_80120008 and img_upload_active are set and
 * the camera's height is within +-0x3FFF, loads the GTE screen state (H 0x40, the light environment's depth cue
 * with DQA doubled and clamped to s16, far colour 0x840, the environment's colour as RGB, the view's scale in LO
 * and VRAM size in HI for the hand-written floor_grid_draw, the view's offset and doubled rotation, the camera's
 * translation), lets floor_grid_draw fill 7 OT tags built in the scratchpad, copies them into the packet buffer and
 * links them, with three texture-window commands, into ot. x, y and z are reused as in the original (GCC 2.7.2
 * keeps one register per variable). */
void point_light_setup_draw(WorkArea *wa, u8 *ot) {
    s32 view_index;
    s32 *rot;
    SVECTOR *colour;
    s32 *depth_cue;
    ViewTail *view;
    s16 *ofs;
    Camera *cam;
    u32 *tags;
    u32 *tag;
    u32 *end;
    u32 *src;
    u32 *dst;
    u32 next;
    u32 mask;
    u8 *pkt;
    PrimGp0Cmd *prim;
    s32 x, y, z;
    s32 dqa, dqb;
    s32 n;
    s32 pad_stack[2]; /* unused: the original frame is 8 bytes larger than the locals need */

    if (d_80120008 == 0 || img_upload_active == 0) {
        return;
    }
    if (!(cameras[cur_camera_index].pos.vy >= -0x3FFF && cameras[cur_camera_index].pos.vy < 0x4000)) {
        return;
    }
    gte_set_ctrl(H, 0x40);
    x = light_envs[light_env_index].depth_cue[0] << 1;
    dqa = MAX(MIN(x, 0x7FFF), -0x8000);
    /* Unused, as in the original: its address constant stays in a register, and cse makes the colour pointer
     * below from it (addiu -0x18) instead of loading light_envs + 0x20. */
    depth_cue = light_envs[light_env_index].depth_cue;
    dqb = light_envs[light_env_index].depth_cue[1];
    gte_set_ctrl(DQA, dqa);
    gte_set_ctrl(DQB, dqb);
    gte_set_ctrl(RFC, 0x840);
    gte_set_ctrl(GFC, 0x840);
    gte_set_ctrl(BFC, 0x840);
    colour = light_envs[light_env_index].unk_20;
    gte_set(RGB, (colour[2].vx >> 5) | ((colour[2].vy >> 5) << 8) | ((colour[2].vz >> 5) << 16) | 0x2C000000);
    view_index = cur_view_index;
    x = views[view_index].unk_4A * 0x1400 / 0x1000;
    mips_mtlo(x);
    view = &view_tails[view_index];
    x = view->vram_w;
    y = view->vram_h;
    mips_mthi(x | (y << 16));
    ofs = &view_tails[view_index].ofs_x;
    {
        s32 ofx = ofs[0];
        s32 ofy = ofs[1];
        gte_set_ctrl(OFX, ofx << 16);
        gte_set_ctrl(OFY, ofy << 16);
    }
    rot = scratch_alloc(0x20);
    scale_rows(view_tails[view_index].rot[0], (s16 *)((u8 *)&view_tails[view_index] - 0x1C), (s16 *)rot);
    vector_double_even((Vec3 *)rot, (Vec3 *)rot);
    gte_load_R_v1a0v0(rot);
    cam = &cameras[cur_camera_index];
    scratch_top -= 0x20;
    x = -cam->pos.vx & 0x7FF;
    y = -cam->pos.vy;
    z = -cam->pos.vz & 0x7FF;
    y = MAX(MIN(y, 0x7FFF), -0x8000);
    /* Three statements: one gte_set_IR123 lets combine fold the copy of the clamped y into the asm. */
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_rtir();
    gte_get_MAC123(x, y, z);
    gte_set_TR(x, y, z);

    /* 7 chained tags in the scratchpad (the last one terminated), for floor_grid_draw; their copy goes to pkt. */
    tags = scratch_alloc(0x1C);
    pkt = wa->packet;
    tag = tags;
    mask = 0xFFFFFF;
    end = tags + 6;
    next = ((u32)pkt + 4) & mask;
    wa->packet = pkt + 0x1C;
    do {
        *tag++ = next;
        next += 4;
    } while (end != tag);
    *tag = mask;
    gte_set(VXY1, 0x110000);
    gte_set(VXY2, tags);
    wa->packet = floor_grid_draw(wa->packet);
    src = tags;
    dst = (u32 *)pkt;
    n = 7;
    do {
        *dst++ = *src++;
    } while (--n > 0);
    scratch_top -= 0x1C;
    tags = (u32 *)pkt;

    prim = wa->packet;
    wa->packet = prim + 1;
    prim->len = 2;
    prim->code = 0xE2000210;
    prim->pad = 0;
    addPrim(tags, prim);
    prim = wa->packet;
    wa->packet = prim + 1;
    prim->len = 2;
    prim->code = 0xE2004318;
    prim->pad = 0;
    addPrim(tags + 4, prim);
    prim = wa->packet;
    wa->packet = prim + 1;
    prim->len = 2;
    prim->code = 0xE200639C;
    prim->pad = 0;
    addPrim(tags + 5, prim);
    {
        u32 link, self;
        u32 *last = tags + 6;

        ot_link_load(link, ot);
        self = (u32)tags << 8;
        ot_link_store(last, link);
        ot_link_store(ot, self);
    }
}

void fn_800D5F3C(void) {

}

/* Runs `count` vectors through the GTE's mvmva (two words each: x and y packed, then z), writing MAC1 and
 * MAC2 as halfwords at 0 and 2 and MAC3 as the word at 4 of the 8-byte entries of `dst`. */
void gte_rtv_batch(s32 count, s32 *src, s16 *dst) {
    s32 value;

    if (count > 0) {
        do {
            gte_load(VXY0, src, 0);
            gte_load(VZ0, src, 4);
            gte_rtv0tr();
            gte_get(MAC2, value);
            gte_store(MAC1, dst, 0);
            gte_store(MAC3, dst, 4);
            dst[1] = value;
            count--;
            src += 2;
            dst += 4;
        } while (count > 0);
    }
}

/* Fills in each entry's inverse from its divisor. */
void recip_table_fill(s32 count, Recip *entry) {
    while (count > 0) {
        count--;
        entry->inverse = 0x80000 / entry->divisor;
        entry++;
    }
}

/* Replaces each point's w (a depth below 0x1000) with its GTE depth-cue factor (DQA/DQB), clamped to 0..0x1000. */
void prim_depth_cue_points(s32 count, ClipPoint *points)
{
    s32 dqa, dqb;
    s32 z;
    s32 fog;

    for (; count > 0; count--, points++) {
        z = points->w;
        fog = 0;
        if (z < 0x1000) {
            gte_get_ctrl(DQA, dqa);
            gte_get_ctrl(DQB, dqb);
            fog = ((dqb + dqa * z * 16) >> 18) << 6;
            fog = MAX(MIN(fog, 0x1000), 0);
        }
        points->w = fog;
    }
}

void *prim_depth_cue_strip(u8 *start, u32 *ot, s32 count, DepthCueRec *rec) {
    u8 *prim = start;
    s32 first, second, prev, ir;
    u32 link;

    FAKE_OPAQUE(prim);
    ir = rec->ir0;
    ot_link_load(link, ot);
    gte_set(IR0, ir);
    first = rec->rgb;
    rec++;
    gte_dpcs_b();
    ir = rec->ir0;
    gte_get(RGB2, second);
    gte_set(IR0, ir);
    prev = rec->rgb;
    rec++;
    gte_dpcs_b();
    count -= 2;
    if (count > 0) {
        s32 *wq;
        do {
            ir = rec->ir0;
            gte_store(RGB2, prim, 0xC);
            gte_set(IR0, ir);
            wq = (s32 *)prim;
            prim[3] = 6;
            wq[4] = prev;
            gte_dpcs_b();
            wq[1] = second;
            wq[2] = first;
            prev = rec->rgb;
            rec++;
            wq[6] = prev;
            ot_link_store(prim, link);
            link = (u32)prim << 8;
            gte_store(RGB2, prim, 0x14);
            prim += 0x1C;
            count--;
        } while (count > 0);
    }
    ot_link_store(ot, link);
    return prim;
}

static inline void clip_cross_800D60E0(ClipPoint *out, ClipPoint *in, ClipPoint *fwd, s32 edge) {
    s32 den, t;

    out->v = edge;
    den = fwd->u - in->u;
    t = ((edge - in->u) << 14) / den;
    out->u = (fwd->v - in->v) * t / 0x4000 + in->v;
    out->w = (fwd->w - in->w) * t / 0x4000 + in->w;
}
static inline s32 clip_axis_800D60E0(s32 count, ClipPoint *in, ClipPoint *dst, s32 lim) {
    s32 left = count;
    ClipPoint *e0 = in;
    ClipPoint *out = dst;
    s32 n = 0;
    s32 w0, w1;

    w1 = ((ClipPointWords *)in)->zw;
    w0 = ((ClipPointWords *)in)->uv;
    ((ClipPointWords *)(in + count))->uv = w0;
    ((ClipPointWords *)(in + count))->zw = w1;
    for (; left > 0; left--, e0++) {
        ClipPoint *e1 = e0 + 1;

        if (e0->u < 0) {
            if (e1->u < 0) continue;
            clip_cross_800D60E0(out, e0, e1, 0);
            out++;
            n++;
        } else if (lim < e0->u) {
            if (lim < e1->u) continue;
            clip_cross_800D60E0(out, e0, e1, lim);
            out++;
            n++;
        } else {
            out->u = e0->v;
            out->v = e0->u;
            out->w = e0->w;
            out++;
            n++;
        }
        if (e1->u < 0) {
            clip_cross_800D60E0(out, e1, e0, 0);
            out++;
            n++;
        } else if (lim < e1->u) {
            clip_cross_800D60E0(out, e1, e0, lim);
            out++;
            n++;
        }
    }
    return n;
}
static inline void near_cross_800D60E0(ClipPoint *out, ClipPoint *in, ClipPoint *fwd, s32 near_z, s32 ofx,
                                       s32 ofy) {
    s32 den, t, ix, iy, sx, sy;

    out->z = near_z;
    den = fwd->z - in->z;
    t = ((near_z - in->z) << 14) / den;
    ix = (fwd->u - in->u) * t / 0x4000 + in->u;
    iy = (fwd->v - in->v) * t / 0x4000 + in->v;
    sx = ((ix << 7) / near_z) + ofx;
    sy = ((iy << 7) / near_z) + ofy;
    out->u = sx;
    out->v = sy;
}
/* Draws a depth-cued polygon: transforms its `count` vertices, clips it against the near plane (z = 0x80) while
 * projecting, then against the view's screen rectangle, and emits the strip if 3 or more points remain. */
void *prim_depth_cue_quad(s32 prim, s32 ot, s32 count, SVECTOR *src, u8 *rgb, u8 *far) {
    ViewRecord *row;
    s16 *view;
    ClipPoint *buf0, *buf1, *e0, *e1, *out;
    s32 n, n_proj, left, ofx, ofy;
    s32 near_z;
    s32 w0, w1, ox, oy, fr, fg, fb;
    u32 colour;
    u8 *top0, *top1;
    s32 size;

    gte_set_ctrl(H, 0x80);
    row = view_screen_offsets;
    view = &row[cur_view_index].value;
    ox = view[0];
    oy = view[1];
    gte_set_ctrl(OFX, ox << 16);
    gte_set_ctrl(OFY, oy << 16);
    colour = *(u32 *)rgb;
    colour = (colour & 0xFFFFFF) | 0x30000000;
    gte_set(RGB, colour);
    fr = far[0];
    fg = far[1];
    fb = far[2];
    gte_set_ctrl(RFC, fr << 4);
    gte_set_ctrl(GFC, fg << 4);
    gte_set_ctrl(BFC, fb << 4);
    size = count * sizeof(ClipPoint);
    top0 = scratch_top;
    scratch_top += size + 0x40;
    top1 = scratch_top;
    scratch_top += size + 0x40;
    buf0 = (ClipPoint *)top0;
    buf1 = (ClipPoint *)top1;
    gte_rtv_batch(count, (s32 *)src, (s16 *)buf0);
    left = count;
    e0 = buf0;
    out = buf1;
    near_z = 0x80;
    gte_get_ctrl(OFX, ofx);
    gte_get_ctrl(OFY, ofy);
    ofx >>= 16;
    ofy >>= 16;
    n_proj = 0;
    w0 = ((ClipPointWords *)buf0)->uv;
    w1 = ((ClipPointWords *)buf0)->zw;
    ((ClipPointWords *)(buf0 + count))->uv = w0;
    ((ClipPointWords *)(buf0 + count))->zw = w1;
    for (; left > 0; left--, e0++) {
        e1 = e0 + 1;
        if (e0->z < near_z) {
            if (e1->z < near_z) continue;
            near_cross_800D60E0(out, e0, e1, near_z, ofx, ofy);
            out++;
            n_proj++;
        } else {
            out->u = (e0->u << 7) / e0->z + ofx;
            out->v = (e0->v << 7) / e0->z + ofy;
            out->z = e0->z;
            out++;
            n_proj++;
        }
        if (e1->z < near_z) {
            near_cross_800D60E0(out, e1, e0, near_z, ofx, ofy);
            out++;
            n_proj++;
        }
    }
    n = n_proj;
    recip_table_fill(n, (Recip *)buf1);
    n = clip_axis_800D60E0(n, buf1, buf0, d_801366D4[cur_view_index].value);
    n = clip_axis_800D60E0(n, buf0, buf1, d_801366D6[cur_view_index].value);
    if (n >= 3) {
        prim_depth_cue_points(n, buf1);
        prim = (s32)prim_depth_cue_strip((u8 *)prim, (u32 *)ot, n, (DepthCueRec *)buf1);
    }
    scratch_top -= count * 16 + 0x80;
    return (void *)prim;
}

void img_upload_pair(void) {
    s16 rect[4];
    s16 *r;
    u16 *image;

    r = rect;
    FAKE_OPAQUE(r);
    image = texture_image;
    rect[0] = 0x20;
    rect[1] = 0x140;
    rect[2] = (((image[0] & 0xFF) << 8) | (image[0] >> 8)) >> 1;
    rect[3] = ((texture_image[1] & 0xFF) << 8) | (texture_image[1] >> 8);
    svc_load_image(r, image + 2);
    svc_draw_sync(0);
    rect[0] = 0x100;
    rect[1] = 0xDC;
    rect[2] = 0x100;
    rect[3] = 1;
    svc_load_image(r, clut_image);
    svc_draw_sync(0);
    light_data_base = 0;
}

void set_data_base(s32 value) {
    light_data_base = value;
}
