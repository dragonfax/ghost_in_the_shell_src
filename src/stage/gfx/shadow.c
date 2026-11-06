/* shadow: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void tex_load_4bpp(u16 *pal, u8 *file) {
    s16 rect[4];
    s16 *r;
    s32 i;
    s32 stride;
    u32 w;
    u32 h;
    s32 unused[2];
    s32 result;
    u16 *buf;
    u32 c;
    u8 *pixels;

    tex_loaded_flag = 1;
    buf = arena_top();
    w = ((u16 *)file)[2];
    h = ((u16 *)file)[3];
    stride = ((w & 0xFF) << 8) | (w >> 8);
    result = mem_has_byte(0, stride * (((h & 0xFF) << 8) | (h >> 8)), file);
    tex_has_transparent = result;
    c = *pal;
    tex_tint_rgb = (c & 0x1F) * 8;
    tex_pal0_g = (c >> 2) & 0xF8;
    tex_pal0_b = (c >> 7) & 0xF8;
    if (result != 0) {
        *pal = 0;
    }
    palette_buf_write(0, 0x10, pal);
    tint_pixels(0x10, pal, 0);
    for (i = 0; i < 0x20; i++) {
        rect[0] = 0;
        rect[1] = i + 0xE0;
        rect[2] = 0x10;
        rect[3] = 1;
        svc_load_image(rect, pal);
        svc_draw_sync(0);
    }
    clut_make_pair(0x10, pal, buf, NULL);
    r = rect;
    rect[1] = 0xDE;
    rect[0] = 0;
    rect[2] = 0x10;
    rect[3] = 2;
    svc_load_image(r, buf);
    svc_draw_sync(0);
    pixels = file + 8;
    pack_4bpp(stride, 0x80, 0x80, 0, pixels, (u8 *)buf);
    rect[0] = 0;
    rect[1] = 0x100;
    rect[2] = 0x20;
    rect[3] = 0x80;
    svc_load_image(r, buf);
    svc_draw_sync(0);
    pack_4bpp(stride, 0x80, 0x80, 1, pixels, (u8 *)buf);
    rect[0] = 0x20;
    rect[1] = 0x100;
    rect[2] = 0x10;
    rect[3] = 0x40;
    svc_load_image(r, buf);
    svc_draw_sync(0);
    pack_4bpp(stride, 0x80, 0x80, 2, pixels, (u8 *)buf);
    rect[0] = 0x30;
    rect[1] = 0x100;
    rect[2] = 8;
    rect[3] = 0x20;
    svc_load_image(r, buf);
    svc_draw_sync(0);
}

/* Whether byte c occurs in the first count bytes of p. */
s32 mem_has_byte(s32 c, s32 count, u8 *p) {
    s32 found = 0;

    while (count > 0) {
        found = *p == c;
        count--;
        p++;
        if (count <= 0 || found) {
            break;
        }
    }
    return found;
}

void clut_xy_get(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = arg0 & 0xF;
    *arg2 = 0xE0;
}

void set_anim_clock_rate(s16 arg0) {
    anim_clock_rate = (u16) arg0;
}

void anim_clock_reset(void) {
    anim_clock = 0;
}

void tex_upload_reset(void) {
    cell_block_rect(0, 0x100, 0x20, 0x80);
    cell_block_rect(0x20, 0x100, 0x10, 0x40);
    cell_block_rect(0x30, 0x100, 8, 0x20);
    tex_loaded_flag = 0;
    tex_has_transparent = 0;
    light_env_tex_flag = 0;
    anim_clock_rate = 8;
    anim_clock_reset();
}

void tex_upload_set_flag(s32 arg0) {
    light_env_tex_flag = arg0;
}

void clock_step(void) {
    anim_clock += anim_clock_rate;
}

/* hand-written: works in $at as an ordinary register */
/* Crack fixer for the quad subdivision: if the triangle (a, b, mid) is front-facing (nclip < 0) and a, b are
 * both farther than `size`, moves the new edge midpoint `mid` one pixel sideways, perpendicular to a-b.
 * The original is hand-written asm: it uses $at as a general register. */
typedef struct GridVert {
    s16 gz; /* grid coordinates, as fed to the GTE (VZ0, VXY0) */
    s16 gx;
    s16 sx; /* projected */
    s16 sy;
    s16 sz;
    u16 flags; /* bits 5..14: GTE IR0 depth cue; bits 0,1: y outside screen; bits 2,3: x outside; bit 4: too near */
} GridVert;

void grid_crack_fix(s32 size, GridVert *a, GridVert *b, GridVert *mid) {
    s32 mac0;

    gte_load(SXY0, a, 4);
    gte_load(SXY2, mid, 4);
    gte_load(SXY1, b, 4);
    gte_nclip();
    gte_get(MAC0, mac0);
    if (((a->sz - size) | (b->sz - size)) & 0x8000) {
        return;
    }
    if (mac0 >= 0) {
        return;
    }
    if (a->sx != b->sx) {
        mid->sy += (a->sx < b->sx) ? 1 : -1;
    }
    if (a->sy != b->sy) {
        mid->sx += (a->sy < b->sy) ? -1 : 1;
    }
}

/* hand-written: sets $ra by hand and falls into grid_quad_draw */
/* Draws the 8x8-cell ground mesh into the packet buffer `packet` and returns the new packet pointer. Rows of
 * 9 vertices (spacing 0x800, range -0x2000..0x2000) are projected with the GTE one row at a time into two
 * alternating buffers on the scratchpad stack ($gp); each cell between the previous and the current row goes
 * to the recursive quad drawer grid_quad_draw. Depth cue (IR0) and clip bits go into GridVert.flags. Inputs the
 * caller leaves in registers: LO = the cell size, HI = the screen limits (high half y, low half x). GTE VZ1
 * is set here to the texture scroll (anim_clock >> 4) and read back by the drawer.
 * The original is hand-written asm: the asm sets $ra to the label fn_800CB174 (an alias inside
 * its own body) and falls into grid_quad_draw, which returns there; that is a plain call below. */
void grid_quad_draw(GridVert *a, GridVert *b, GridVert *c, GridVert *d, s32 size, u8 **packet);
void *grid_mesh_draw(u8 *packet) {
    GridVert *prev;
    GridVert *cur;
    GridVert *tmp;
    s32 size;
    s32 row;
    s32 i;
    u32 limits;
    u32 sxy;
    u32 flags;
    u32 sz;

    gte_set(VZ1, (s16)anim_clock >> 4);
    mips_mflo(size);
    mips_mfhi(limits);
    prev = scratch_alloc(9 * sizeof(GridVert));
    cur = scratch_alloc(9 * sizeof(GridVert));
    for (row = -0x2000; row <= 0x2000; row += 0x800) {
        gte_set(VXY0, (u16)row);
        gte_set(VZ0, -0x2000);
        gte_rtps();
        for (i = 0; i < 9; i++) {
            cur[i].gz = -0x2000 + i * 0x800;
            cur[i].gx = row;
            gte_get(SZ3, sz);
            gte_get(IR0, flags);
            gte_get(SXY2, sxy);
            gte_set(VZ0, cur[i].gz + 0x800); /* next vertex */
            gte_rtps();
            cur[i].sx = sxy;
            cur[i].sy = sxy >> 16;
            cur[i].sz = sz;
            flags &= 0x7FE0;
            if (sz <= 0x40) {
                flags |= 0x10;
            }
            if ((s16)(limits >> 16) < (sxy >> 16)) {
                flags |= (sxy >> 31) + 1;
            }
            if ((limits & 0xFFFF) < (sxy & 0xFFFF)) {
                flags |= (((sxy & 0xFFFF) >> 15) + 1) << 2;
            }
            cur[i].flags = flags;
        }
        if (row != -0x2000) {
            for (i = 0; i < 8; i++) {
                grid_quad_draw(prev + i, prev + i + 1, cur + i, cur + i + 1, size, &packet);
            }
        }
        tmp = prev;
        prev = cur;
        cur = tmp;
    }
    scratch_top -= 2 * 9 * sizeof(GridVert);
    return packet;
}

/* hand-written: subroutine saving $ra through $gp, entered by fall-through from grid_mesh_draw */
/* Draws one ground-mesh quad (corners a, b in one grid row, c, d in the next; `size` = the cell size from LO;
 * `*packet` = the cursor, $t3; GTE VXY1 holds a constant tpage word, RGB the base color) or splits it in four
 * and recurses. Culled if all four corners are outside the same screen edge. Split if the cell is bigger than
 * 0x140 and any corner is nearer than `size`: 5 new midpoints (GridVerts on the $gp scratch stack) are
 * projected and the crack fixer grid_crack_fix runs on the edges. Otherwise it fills a textured quad whose color
 * is the depth cue (dpcs) and whose UVs come from the grid coordinates, and sorts it into one of the 8
 * ordering-table buckets of the caller's table (VXY2 = its address) by detail level and texture quadrant.
 * The original is hand-written asm: its arguments and the cursor live in $t3, $t6..$t9, $s0 across
 * the recursion, $ra is saved through $gp, and it is also entered by fall-through from grid_mesh_draw. */
typedef struct GridQuad {
    u32 tag;
    u8 r, g, b, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad2;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad3;
} GridQuad;

void grid_quad_draw(GridVert *a, GridVert *b, GridVert *c, GridVert *d, s32 size, u8 **packet) {
    GridQuad *p;
    GridVert *m;
    s32 sum;
    s32 u, v, step, shift, bucket, scroll;
    u32 *tags;

    if (((*(u32 *)&a->sz & *(u32 *)&b->sz & *(u32 *)&c->sz & *(u32 *)&d->sz) >> 16) & 0x1F) {
        return;
    }
    if (size > 0x140 && (((a->sz - size) | (b->sz - size) | (c->sz - size) | (d->sz - size)) & 0x8000)) {
        s32 mz = (a->gz + d->gz) >> 1;
        s32 mx = (a->gx + d->gx) >> 1;
        s32 i;

        m = scratch_alloc(5 * sizeof(GridVert));
        /* midpoints: (mz, a.x) (a.z, mx) (mz, mx) (d.z, mx) (mz, d.x) */
        m[0].gz = mz;     m[0].gx = a->gx;
        m[1].gz = a->gz;  m[1].gx = mx;
        m[2].gz = mz;     m[2].gx = mx;
        m[3].gz = d->gz;  m[3].gx = mx;
        m[4].gz = mz;     m[4].gx = d->gx;
        for (i = 0; i < 5; i++) {
            /* VXY0 = gx, VZ0 = gz, rtps; sx, sy, sz and flags filled as in grid_mesh_draw */
            gte_set(VXY0, (u16)m[i].gx);
            gte_set(VZ0, m[i].gz);
            gte_rtps();
            gte_get(SXY2, sum);
            m[i].sx = sum;
            m[i].sy = sum >> 16;
            gte_get(SZ3, sum);
            m[i].sz = sum;
            gte_get(IR0, sum);
            m[i].flags = (sum & 0x7FE0) | (m[i].sz <= 0x40 ? 0x10 : 0); /* clip bits as in grid_mesh_draw */
        }
        grid_crack_fix(size, a, b, &m[0]);
        grid_crack_fix(size, b, d, &m[3]);
        grid_crack_fix(size, d, c, &m[4]);
        grid_crack_fix(size, c, a, &m[1]);
        size >>= 1;
        grid_quad_draw(a, &m[0], &m[1], &m[2], size, packet);
        grid_quad_draw(&m[0], b, &m[2], &m[3], size, packet);
        grid_quad_draw(&m[1], &m[2], c, &m[4], size, packet);
        grid_quad_draw(&m[2], &m[3], &m[4], d, size, packet);
        scratch_top -= 5 * sizeof(GridVert);
        return;
    }
    sum = ((a->flags + b->flags) & 0x7FE0) + ((c->flags + d->flags) & 0x7FE0);
    if (sum >= 0x4000) {
        return; /* too foggy */
    }
    gte_set(IR0, sum >> 2);
    p = (GridQuad *)*packet;
    p->clut = ((sum >> 9) + 0xE0) << 6;
    gte_dpcs();
    gte_store(RGB2, p, 4);
    gte_store(VXY1, p, 0x14); /* constant: u1 = v1 = 0, tpage 0x10 */
    p->x0 = a->sx; p->y0 = a->sy;
    p->x1 = b->sx; p->y1 = b->sy;
    p->x2 = c->sx; p->y2 = c->sy;
    p->x3 = d->sx; p->y3 = d->sy;
    p->tag = p->tag & 0xFFFFFF | 9 << 24;
    gte_get(VZ1, scroll);
    step = (c->gz - a->gz) >> 3;
    u = (a->gx >> 3) & 0x7F;
    v = ((a->gz >> 3) + scroll) & 0x7F;
    gte_set(LZCS, step);
    gte_get(LZCR, shift);
    shift = 0x19 - shift;
    if (shift > 2) {
        shift = 2;
    }
    bucket = 0;
    if (shift > 0) { /* big on screen: coarser texture, other bucket group */
        u >>= shift;
        v >>= shift;
        step >>= shift;
        bucket = shift + 3;
    }
    p->u0 = u;         p->v0 = v;
    p->u1 = u;         p->v1 = v + step;
    p->u2 = u + step;  p->v2 = v;
    p->u3 = u + step;  p->v3 = v + step;
    gte_get(VXY2, tags);
    bucket += ((u >> 6) << 1) + (v >> 6);
    addPrim(tags + bucket, p);
    *packet = (u8 *)(p + 1);
}

/* Sets the four corners of a flat quad: x = -0x3FFF for corners 1 and 2, +0x3FFF for 0 and 3, height y, depth
 * z0 for corners 0 and 1 and z1 for corners 2 and 3. The stores are in the original's order. */
void quad_set_flat(SVECTOR *corners, s32 y, s32 z0, s32 z1) {
    corners[2].vx = -0x3FFF;
    corners[1].vx = -0x3FFF;
    corners[3].vy = y;
    corners[2].vy = y;
    corners[1].vy = y;
    corners[0].vy = y;
    corners[1].vz = z0;
    corners[0].vz = z0;
    corners[3].vz = z1;
    corners[2].vz = z1;
    corners[3].vx = 0x3FFF;
    corners[0].vx = 0x3FFF;
}

/* Seven depth-cued quads at height y between mask-bit off/on packets; returns the next free prim. */
void *shadow_bands_draw(u8 *prim, u32 *ot, s32 y) {
    s32 *rot;
    SVECTOR *quad;
    u8 *rgb;
    u8 *table; /* light records (0x84 bytes), later the far colour of the current one */
    PrimGp0Cmd *mask_off;
    PrimGp0Cmd *mask_on;
    u8 *band1, *band2, *band3, *band4, *band5, *band6;
    s32 r0, r1, r2;
    s32 ir1, ir2, ir3;
    s32 offset;
    u8 *rec;

    rot = (s32 *)scratch_top;
    scratch_top += 0x20;
    scale_rows((s16 *)((u8 *)view_scale_base + cur_view_index * 0xA8), (s16 *)((u8 *)view_scale_base + cur_view_index * 0xA8 - 0x48), (s16 *)rot);
    gte_set_R012(r0, r1, r2, rot[0], rot[1], rot[2]);
    gte_set_R34(r0, r1, rot[3], rot[4]);
    scratch_top -= 0x20;
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    table = light_env_colours;
    offset = light_env_index * 0x84;
    rec = offset + table;
    ir1 = *(s16 *)(rec + 8);
    ir2 = *(s16 *)(rec + 0xA);
    ir3 = *(s16 *)(rec + 0xC);
    gte_ldrgb(&tex_tint_rgb);
    gte_lddp(0);
    gte_set(IR1, ir1);
    gte_set(IR2, ir2);
    gte_set(IR3, ir3);
    gte_dpcl();
    rgb = scratch_top;
    scratch_top += 4;
    quad = (SVECTOR *)scratch_top;
    scratch_top += 0x20;
    __asm__("" : "=r"(table) : "0"(table));
    table += offset;
    table -= 0x48;
    gte_store(RGB2, rgb, 0);

    mask_off = (PrimGp0Cmd *)prim;
    prim += sizeof(PrimGp0Cmd);
    mask_off->len = 2;
    mask_off->code = 0xE6000000;
    mask_off->pad = 0;
    addPrim(ot, mask_off);

    quad_set_flat(quad, y, 0x2100, 0x693);
    band1 = prim_depth_cue_quad((s32)prim, (s32)ot, 4, quad, rgb, table);
    quad_set_flat(quad, y, 0x693, 0x349);
    band2 = prim_depth_cue_quad((s32)band1, (s32)ot, 4, quad, rgb, table);
    quad_set_flat(quad, y, 0x349, -0x349);
    band3 = prim_depth_cue_quad((s32)band2, (s32)ot, 4, quad, rgb, table);
    quad_set_flat(quad, y, -0x349, -0x693);
    band4 = prim_depth_cue_quad((s32)band3, (s32)ot, 4, quad, rgb, table);
    quad_set_flat(quad, y, -0x693, -0x2100);
    band5 = prim_depth_cue_quad((s32)band4, (s32)ot, 4, quad, rgb, table);
    quad_set_flat(quad, y, -0x2100, -0x3FFF);
    band6 = prim_depth_cue_quad((s32)band5, (s32)ot, 4, quad, rgb, table);
    quad_set_flat(quad, y, 0x2100, 0x2100);
    quad[1].vy = -0x84;
    quad->vy = -0x84;
    mask_on = prim_depth_cue_quad((s32)band6, (s32)ot, 4, quad, rgb, table);

    prim = (u8 *)(mask_on + 1);
    mask_on->len = 2;
    mask_on->code = 0xE6000001;
    mask_on->pad = 0;
    addPrim(ot, mask_on);
    scratch_top -= 0x24;
    return prim;
}

void shadow_draw(s32 arg0, s32 arg1, s32 arg2) {
    volatile s32 *m;
    SVECTOR *quad;
    s32 a, b, c;

    m = (volatile s32 *)scratch_top;
    scratch_top += 0x20;
    scale_rows((s16 *)((u8 *)view_scale_base + cur_view_index * 0xA8), (s16 *)((u8 *)view_scale_base + cur_view_index * 0xA8 - 0x48), (s16 *)(s32 *)m);
    a = m[0]; b = m[1]; c = m[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = m[3]; b = m[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    scratch_top -= 0x20;
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    quad = (SVECTOR *)scratch_top;
    scratch_top += 0x20;
    quad_set_flat(quad, arg2, 0x2100, -0x2100);
    quad[1].vy = -0x84;
    quad->vy = -0x84;
    prim_depth_cue_quad(arg0, arg1, 4, quad, light_env_depth_cue + light_env_index * 0x84, light_env_depth_cue + light_env_index * 0x84);
    scratch_top -= 0x20;
}

void shadow_pass_draw(WorkArea *wa, u32 *ot) {
    s32 n; /* end of the tag fill, then the copy count */
    s32 sx, sy, sz;
    s32 y, t;
    s32 dqb, blue;
    u32 *tags;
    u32 *pkt;
    u32 *cur;
    u32 *prim;
    u32 link;
    u32 mask;
    LightEnvColour *env;
    ViewTail *view;
    volatile s32 *mat;
    s16 *ofs;

    if (light_env_tex_flag == 0) {
        if (views[cur_view_index].colour.cd == 0x80) {
            wa->packet = (void *)((s32 (*)(s32, s32, s32))shadow_draw)((s32)wa->packet, (s32)ot, -0x300);
        }
        return;
    }
    if (tex_loaded_flag == 0) {
        return;
    }
    gte_set_ctrl(H, 0x80);
    point_calc_projection(0x666, 0x2000, 0x80, &sx, &sy);
    dqb = sy;
    gte_set_ctrl(DQA, sx);
    gte_set_ctrl(DQB, dqb);
    gte_set_ctrl(RFC, 0x880);
    gte_set_ctrl(GFC, 0x880);
    gte_set_ctrl(BFC, 0x880);
    env = (LightEnvColour *)light_env_colours + light_env_index;
    sx = env->x * 0x88 / 0x1000;
    sy = env->y * 0x88 / 0x1000;
    blue = env->z * 0x88 / 0x1000;
    gte_set(RGB, sx | (sy << 8) | (blue << 16) | 0x2C000000);
    t = views[cur_view_index].unk_4A * 0x1600 / 0x1000;
    sx = t;
    __asm__ volatile("mtlo %0" : : "r"(t));
    view = &view_tails[cur_view_index];
    sx = view->vram_w;
    sy = view->vram_h;
    __asm__ volatile("mthi %0" : : "r"(sx | (sy << 16)));
    ofs = &view_tails[cur_view_index].ofs_x;
    {
        s32 ofx = ofs[0];
        s32 ofy = ofs[1];
        gte_set_ctrl(OFX, ofx << 16);
        gte_set_ctrl(OFY, ofy << 16);
    }
    tags = (u32 *)scratch_top;
    scratch_top += 0x20;
    scale_rows(view_tails[cur_view_index].rot[0], (s16 *)((u8 *)&view_tails[cur_view_index] - 0x1C), (s16 *)tags);
    mat = (volatile s32 *)tags;
    {
        s32 r0 = mat[0];
        s32 r1 = mat[1];
        s32 r2 = mat[2];
        gte_set_ctrl(R11R12, r0);
        gte_set_ctrl(R13R21, r1);
        gte_set_ctrl(R22R23, r2);
        r0 = mat[3];
        r1 = mat[4];
        gte_set_ctrl(R31R32, r0);
        gte_set_ctrl(R33, r1);
    }
    scratch_top -= 0x20;
    gte_set(VXY0, 0xFD000000);
    gte_set(VZ0, 0);
    gte_rtv0();
    gte_get_wait(MAC1, sx);
    gte_get_wait(MAC2, sy);
    gte_get(MAC3, sz);
    y = sy;
    gte_set_ctrl(TRX, sx);
    gte_set_ctrl(TRY, y);
    gte_set_ctrl(TRZ, sz);
    tags = scratch_alloc(0x20);
    cur = tags;
    mask = 0xFFFFFF;
    pkt = wa->packet;
    link = ((u32)pkt + 4) & mask;
    wa->packet = pkt + 8;
    n = (s32)(tags + 7);
    do {
        *cur++ = link;
        link += 4;
    } while ((u32 *)n != cur);
    *cur = mask;
    gte_set(VXY1, 0x100000);
    gte_set(VXY2, tags);
    wa->packet = grid_mesh_draw(wa->packet);
    cur = tags;
    prim = pkt;
    for (n = 8; n > 0; n--) {
        *prim++ = *cur++;
    }
    scratch_top -= 0x20;
    cur = tags = pkt; /* dead store to cur: keeps cse addressing "*cur = mask" through cur, not n */
    prim = wa->packet;
    wa->packet = (PrimGp0Cmd *)prim + 1;
    ((PrimGp0Cmd *)prim)->len = 2;
    ((PrimGp0Cmd *)prim)->code = 0xE2000210;
    ((PrimGp0Cmd *)prim)->pad = 0;
    addPrim(tags, prim);
    prim = wa->packet;
    wa->packet = (PrimGp0Cmd *)prim + 1;
    ((PrimGp0Cmd *)prim)->len = 2;
    ((PrimGp0Cmd *)prim)->code = 0xE2004318;
    ((PrimGp0Cmd *)prim)->pad = 0;
    addPrim(tags + 4, prim);
    prim = wa->packet;
    wa->packet = (PrimGp0Cmd *)prim + 1;
    ((PrimGp0Cmd *)prim)->len = 2;
    ((PrimGp0Cmd *)prim)->code = 0xE200639C;
    ((PrimGp0Cmd *)prim)->pad = 0;
    addPrim(tags + 5, prim);
    {
        u32 link_, self_;
        u32 *last = tags + 7;
        ot_link_load(link_, ot);
        self_ = (u32)tags << 8;
        ot_link_store(last, link_);
        ot_link_store(ot, self_);
    }
    if (tex_has_transparent != 0) {
        wa->packet = shadow_bands_draw(wa->packet, ot, -0x300);
    }
}

/* Hand-written: calls shadow_pass_draw on the scratchpad stack (FINDINGS \"$sp in C\"). */
/* Calls shadow_pass_draw(wa, ot) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * The original is hand-written asm: the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void shadow_pass_draw_scratch(WorkArea *wa, u32 *ot) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    shadow_pass_draw(wa, ot);
    SCRATCH_STACK_LEAVE_BELOW();
}
