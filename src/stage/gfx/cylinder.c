/* cylinder: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void cyl_table_build(void) {
    s16 *p = cyl_table;
    s16 *q;
    s32 row;
    s32 i;
    s32 scale = cyl_scale;

    row = 2;
    do {
        s32 base = -row * (scale << 6);
        i = 0;
        q = p + 2;
        do {
            s32 k = (i << 10) & 0x3C00;
            s32 cs = *(s16 *)((u8 *)cos_table + k);
            s32 sn = *(s16 *)((u8 *)rcossin_tbl + k);
            s32 x = cs * scale / 0x1000;
            s32 z = sn * scale / 0x1000;
            s32 y = base / 0x80 * 15 / 16;
            i++;
            p[0] = z;
            q[-1] = y;
            q[0] = x;
            q += 4;
            p += 4;
        } while (i <= 16);
        row--;
    } while (row >= 0);
}

/* Checks a 0x40-byte block of nibble-repeated words: when every word has the high nibble of the first
 * byte in all its eight nibbles, returns that nibble + 1; otherwise 0. */
s32 block_solid_index(u8 *block) {
    s32 *word = (s32 *) block;
    s32 *end = (s32 *) (block + 0x40);
    s32 high = block[0] & 0xF0;
    s32 pattern = high;

    pattern = (pattern << 8) | high;
    pattern = (pattern << 8) | high;
    pattern = (pattern << 8) | high;
    if (word != end) {
        do {
            if ((*word & 0xF0F0F0F0) != pattern) {
                return 0;
            }
            word++;
        } while (word != end);
    }
    return (high >> 4) + 1;
}

/* Uploads `size` bytes of 64-byte texture blocks to free VRAM cells (solid blocks
 * as a packed 4-bit CLUT image, the others as-is), then builds the cell lookup
 * table at cyl_tex_table from the 0x800 block indices that follow `header[2]`. */
void texture_page_decode(s16 *header, s16 *out, u8 *data, s32 size) {
    s16 rect[4];
    u8 *packed;
    s32 *table;
    s32 *entry;
    s32 *dst;
    s16 *idx;
    s32 i;
    s32 cell;
    s32 x;
    s32 y;
    s32 page;
    s32 u;
    s32 v;
    s32 slot;
    s32 kind;
    s32 height = 8;

    *out = 0;
    rect[0] = 0x100;
    rect[1] = 0xD8;
    rect[2] = 0x100;
    rect[3] = 1;
    svc_load_image(rect, out);
    packed = arena_alloc(0x40);
    table = arena_alloc(0x2000);

    for (i = 0, entry = table; i < size / 64; i++) {
        s32 *word;
        s32 *end;
        u8 *o;

        slot = block_solid_index(data);
        if (slot != 0) {
            kind = slot - 1;
            end = (s32 *)data + 16;
            for (word = (s32 *)data, o = packed; word != end; word++) {
                s32 bits = *word;
                s32 lo = bits & 0xF;
                s32 hi;
                s32 b0, b1;

                bits >>= 4;
                hi = bits & 0xF0;
                b0 = lo + hi;
                bits >>= 12;
                lo = bits & 0xF;
                bits >>= 4;
                hi = bits & 0xF0;
                b1 = lo + hi;
                o[0] = b0;
                o[1] = b1;
                o += 2;
            }
            cell = cell_take_next(0);
            x = grid_cell_index(cell);
            y = cell_index_offset(cell);
            page = ((y & 0x100) >> 4) | ((x & 0x3FF) >> 6) | ((y & 0x200) << 2);
            u = cell_index_plain(cell, 0);
            v = grid_cell_sub_index(cell, 0);
            slot = ((y / 32) % 8) * 4 + (x / 32) % 4;
            svc_draw_sync(0);
            rect[0] = x;
            rect[1] = y;
            rect[2] = 2;
            rect[3] = height;
            svc_load_image(rect, packed);
        } else {
            s32 col;
            s32 bank;

            kind = 0;
            cell = cell_take_next(1);
            x = grid_cell_index(cell);
            y = cell_index_offset(cell);
            bank = (y & 0x100) >> 4;
            col = ((x & 0x3FF) >> 6) | 0x80;
            page = bank | col | ((y & 0x200) << 2);
            u = cell_index_plain(cell, 1);
            v = grid_cell_sub_index(cell, 1);
            slot = ((y / 32) % 8) * 4 + (x / 32) % 4;
            svc_draw_sync(0);
            rect[0] = x;
            rect[1] = y;
            rect[2] = 4;
            rect[3] = height;
            svc_load_image(rect, data);
        }
        *entry = (kind << 26) | (slot << 21) | (page << 13) | ((u >> 3) << 8) | (v >> 3);
        data += 0x40;
        entry++;
    }
    idx = header + 2;
    *table = 0;
    dst = (s32 *)heap_bump_alloc(0x2000);
    cyl_tex_table = (s32)dst;
    for (i = 0; i < 0x800; i++) {
        *dst++ = table[*idx++];
    }
    arena_pop(0x2040);
    svc_draw_sync(0);
}

void tile_pos_wide(s32 index, s32 *out_x, s32 *out_y) {
    *out_x = (index & 0xFF) + 0x100;
    *out_y = 0xD8;
}

/* Final asm (hand_regs): the textured cylinder renderer. Half of it is compiler output: the setup (camera
 * matrix via rot_matrix_to_angles, rot_matrix_b, scale_rows, rcossin_tbl), so it began as C. Its inner
 * primitive loop was then hand-optimized in assembly: HI/LO hold the clip bounds and a pointer, $at holds
 * texture coordinates (GCC uses neither), so the whole function stays asm. */
#ifdef NON_MATCHING
/* Draws the textured cylinder (2 sections x 16 columns of 8x8-quad cells) into ot. Builds the camera-relative GTE
 * state, projects the 3x17 cyl_table corners into clip codes, then per visible cell projects a 9x9 vertex grid and
 * links a textured quad (POLY_FT4) per non-zero entry of the cyl_tex_table texture table into 32 chained OT slots in the
 * packet buffer, which are linked into ot at the end. C companion of hand-written asm (not compiled): the inner quad
 * loop keeps the texture entry in $at and the packet pointer and OT head in HI/LO ($s3 = ot is parked in LO). */
typedef struct CylVertex {
    u32 sxy;
    s16 sz;
    u16 code; /* clip flags: 0x10 near, 1/2 y out, 4/8 x out */
} CylVertex;

static inline u32 cyl_clip_code(u32 sxy, s32 sz, u32 clip) {
    u32 code = (sz < 0x41) << 4;
    u32 sy = sxy >> 16;
    u32 sx = sxy & 0xFFFF;

    if ((s32)clip >> 16 < (s32)sy) {
        code |= (sy >> 15) + 1;
    }
    if ((clip & 0xFFFF) < sx) {
        code |= ((sx >> 15) + 1) << 2;
    }
    return code;
}

void cylinder_draw(WorkArea *wa, u32 *ot) {
    RotMatrix *m;
    s16 *rot;
    s16 *scale;
    Camera *cam;
    ViewRecord *screen;
    ViewTail *tail;
    s32 a, b, c;
    s32 sc, v, sx, sy, x, z;
    u32 clip, sxy;
    s32 sz;
    u8 *codes;
    s16 *p;
    CylVertex *grid;
    u32 *tex;
    u32 *ots;
    u32 *pk;
    u32 *q;
    u32 link;
    PrimGp0Cmd *cmd;
    s32 sec, col, i, j, qi, qj;

    if (cyl_tex_table == 0 || d_8011FFF8 == 0) {
        return;
    }
    gte_set_ctrl(H, 0x80);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);

    /* Pass 1: the view's roll only, to get the screen offset the vertical tilt adds. */
    rot = scratch_alloc(0x20);
    cam = &cameras[cur_camera_index];
    rot_matrix_to_angles((RotMatrix *)&cam_rotations[cur_view_index], &a, &b, &c);
    scale = (s16 *)((u8 *)&cam_rotations[cur_view_index] - 0x28);
    sc = rcossin_tbl[c & 0xFFF];
    rot[0] = sc >> 16;
    rot[1] = -sc;
    rot[2] = 0;
    rot[3] = sc;
    rot[4] = sc >> 16;
    rot[5] = 0;
    rot[6] = 0;
    rot[7] = 0;
    rot[8] = 0x1000;
    scale_rows(rot, scale, rot);
    gte_SetRotMatrix(rot);
    gte_set_ctrl(OFX, 0);
    gte_set_ctrl(OFY, 0);

    v = -cam->pos.vy * vec3_y / 0x1000;
    v = v * ABS(cos_table[b & 0xFFF].value) / 0x1000;
    v = MAX(MIN(v, 0x7FFF), -0x8000);
    gte_set(VXY0, v << 16);
    gte_set(VZ0, cyl_scale);
    gte_rtps();
    gte_get(SXY2, sxy);
    sx = MAX(MIN((s16)sxy, 0x7FFF), -0x8000);
    sy = MAX(MIN((s32)sxy >> 16, 0x7FFF), -0x8000);
    screen = &view_screen_offsets[cur_view_index];
    gte_set_ctrl(OFX, (screen->value + sx) << 16);
    gte_set_ctrl(OFY, (screen->offset_y + sy) << 16);

    /* Pass 2: the full view rotation; the camera's offset (scaled by vec3) becomes the translation. */
    rot_matrix_b(rot, a, b, c);
    scale_rows(rot, scale, rot);
    gte_SetRotMatrix(rot);
    x = -cam->pos.vx * vec3_x / 0x1000;
    z = -cam->pos.vz * vec3_z / 0x1000;
    x = MAX(MIN(x, 0x7FFF), -0x8000);
    z = MAX(MIN(z, 0x7FFF), -0x8000);
    gte_set(VXY0, x & 0xFFFF);
    gte_set(VZ0, z);
    gte_rtv0();
    gte_get(MAC1, x);
    gte_get(MAC2, v);
    gte_get(MAC3, z);
    gte_set_ctrl(TRX, x);
    gte_set_ctrl(TRY, v);
    gte_set_ctrl(TRZ, z);
    tail = &view_tails[cur_view_index];
    clip = ((u32)tail->vram_h << 16) | (u16)tail->vram_w;
    mips_mthi(clip); /* the clip bounds stay in HI for the whole function */
    scratch_top -= 0x20;

    /* Clip code of each of the 3x17 table corners. */
    codes = scratch_alloc(0x34);
    p = cyl_table;
    for (i = 0; i < 0x33; i++, p += 4) {
        gte_set(VXY0, *(s32 *)p);
        gte_set(VZ0, *(s32 *)(p + 2));
        gte_rtps();
        gte_get(SZ3, sz);
        gte_get(SXY2, sxy);
        codes[i] = cyl_clip_code(sxy, sz, clip);
    }

    mips_mtlo(ot);
    grid = scratch_alloc(0x288);
    tex = (u32 *)cyl_tex_table;
    gte_set(VXY1, 0x2D000000); /* the quads' code word: textured, semi-transparent */
    gte_set(VXY2, 0x09000000); /* their tag: 9 words */
    /* 32 chained OT slots followed by a terminator, built in the scratchpad and copied to the packet buffer. */
    ots = scratch_alloc(0x84);
    pk = wa->packet;
    wa->packet = pk + 0x21;
    link = (u32)(pk + 1) & 0xFFFFFF;
    for (q = ots; q != ots + 0x20; q++, link += 4) {
        *q = link;
    }
    *q = 0xFFFFFF;

    for (sec = 0; sec < 2; sec++) {
        for (col = 0; col < 16; col++) {
            u8 *cc = &codes[sec * 17 + col];
            u32 any = cc[0] | cc[1] | cc[17] | cc[18];
            s32 dx, dy, dz, x0, y0, z0;

            if (cc[0] & cc[1] & cc[17] & cc[18]) {
                continue; /* the whole cell is off screen */
            }
            p = &cyl_table[(sec * 17 + col) * 4];
            dx = p[72] - p[0];
            dy = p[73] - p[1];
            dz = p[74] - p[2];
            x0 = p[0] << 3;
            y0 = p[1] << 3;
            z0 = p[2] << 3;
            /* The 9x9 vertices of the cell, interpolated between its corners (3 fractional bits). */
            for (i = 0; i < 9; i++) {
                for (j = 0; j < 9; j++) {
                    CylVertex *vtx = &grid[i * 9 + j];

                    gte_set(VXY0, ((x0 + j * dx) >> 3 & 0xFFFF) | (((y0 + i * dy) >> 3) << 16));
                    gte_set(VZ0, (z0 + j * dz) >> 3);
                    gte_rtps();
                    gte_get(SZ3, sz);
                    gte_get(SXY2, sxy);
                    vtx->sz = sz;
                    vtx->sxy = sxy;
                    vtx->code = any ? cyl_clip_code(sxy, sz, clip) : 0;
                }
            }
            /* One textured quad per non-zero table entry; the entry packs u/v (bits 0-12), tpage, the OT slot
             * (bits 21-25) and the clut (bits 26+). */
            for (qi = 0; qi < 8; qi++) {
                u32 *row = &tex[((sec * 8 + qi) * 16 + col) * 8];

                for (qj = 0; qj < 8; qj++) {
                    CylVertex *v00 = &grid[qi * 9 + qj];
                    CylVertex *v01 = v00 + 1;
                    CylVertex *v10 = v00 + 9;
                    CylVertex *v11 = v00 + 10;
                    u32 e = row[qj];
                    u32 t;
                    PolyFT4 *prim;

                    if (e == 0) {
                        continue;
                    }
                    if (any && (v00->code & v01->code & v10->code & v11->code)) {
                        continue;
                    }
                    prim = wa->packet;
                    gte_get(VXY1, *(u32 *)&prim->r0);
                    gte_get(VXY2, *(u32 *)prim);
                    prim->clut = ((s32)e >> 26) + 0x3610;
                    t = e << 3;
                    *(u32 *)&prim->x0 = v00->sxy;
                    *(u32 *)&prim->x1 = v01->sxy;
                    *(u32 *)&prim->x2 = v10->sxy;
                    *(u32 *)&prim->x3 = v11->sxy;
                    *(u16 *)&prim->u0 = t;
                    *(u32 *)&prim->u1 = t + 7;
                    ((u8 *)prim)[0x17] = 0;
                    *(u16 *)&prim->u3 = t + 0x707;
                    *(u16 *)&prim->u2 = t + 0x700;
                    wa->packet = prim + 1;
                    addPrim(&ots[(e >> 21) & 0x1F], prim);
                }
            }
        }
    }

    /* Copy the 33 OT words to the packet buffer and link them into ot (the last one takes ot's old link). */
    for (i = 0; i < 0x21; i++) {
        pk[i] = ots[i];
    }
    scratch_top -= 0x84;
    mips_mflo(ot);
    {
        u32 old, self;

        ot_link_load(old, ot);
        self = (u32)pk << 8;
        ot_link_store(pk + 0x20, old);
        ot_link_store(ot, self);
    }
    scratch_top -= 0x288;
    scratch_top -= 0x34;

    /* GP0 command E2 (texture window), linked at the head of ot. */
    cmd = wa->packet;
    wa->packet = cmd + 1;
    cmd->len = 2;
    cmd->code = 0xE2000000;
    cmd->pad = 0;
    addPrim(ot, cmd);
}
#else
INCLUDE_ASM("../src/stage/asm", cylinder_draw);
#endif

#ifdef NON_MATCHING
/* Calls cylinder_draw(wa, ot) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * C companion of hand-written asm (not compiled): the asm keeps the old $sp in $at and sets up the frame by hand
 * (FINDINGS "$sp in C"). */
void cylinder_draw_scratch(WorkArea *wa, u32 *ot) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    cylinder_draw(wa, ot);
    SCRATCH_STACK_LEAVE_BELOW();
}
#else
INCLUDE_ASM("../src/stage/asm", cylinder_draw_scratch);
#endif

void img_upload_4bpp(u16 *arg0, u8 *arg1) {
    s16 rect[4];
    s16 *r;
    u16 *buf;
    s32 i;
    s32 stride;
    u8 *src;
    u16 w;

    img_upload_active = 1;
    buf = arena_top();
    palette_buf_write(0x10, 0x10, arg0);
    tint_pixels(0x10, arg0, 0);
    for (i = 0; i < 0x20; i++) {
        rect[0] = 0x10;
        rect[1] = i + 0xE0;
        rect[2] = 0x10;
        rect[3] = 1;
        svc_load_image(rect, arg0);
        svc_draw_sync(0);
    }
    clut_make_pair(0x10, arg0, buf, 0);
    r = rect;
    r[0] = 0x10;
    r[1] = 0xDE;
    r[2] = 0x10;
    r[3] = 2;
    svc_load_image(rect, buf);
    svc_draw_sync(0);
    w = *(u16 *)(arg1 + 4);
    src = arg1 + 8;
    stride = ((w & 0xFF) << 8) | (w >> 8);
    pack_4bpp(stride, 0x80, 0x80, 0, src, (u8 *)buf);
    r[0] = 0x40;
    r[1] = 0x100;
    r[2] = 0x20;
    r[3] = 0x80;
    svc_load_image(rect, buf);
    svc_draw_sync(0);
    pack_4bpp(stride, 0x80, 0x80, 1, src, (u8 *)buf);
    r[0] = 0x60;
    r[1] = 0x100;
    r[2] = 0x10;
    r[3] = 0x40;
    svc_load_image(rect, buf);
    svc_draw_sync(0);
    pack_4bpp(stride, 0x80, 0x80, 2, src, (u8 *)buf);
    r[0] = 0x70;
    r[1] = 0x100;
    r[2] = 8;
    r[3] = 0x20;
    svc_load_image(rect, buf);
    svc_draw_sync(0);
}

void tile_pos_grid16(s32 index, s32 *out_x, s32 *out_y) {
    *out_x = (index & 0xF) + 0x10;
    *out_y = 0xE0;
}

void img_upload_clear(void) {
    cell_block_rect(0x40, 0x100, 0x20, 0x80);
    cell_block_rect(0x60, 0x100, 0x10, 0x40);
    cell_block_rect(0x70, 0x100, 8, 0x20);
    img_upload_active = 0;
    d_80120008 = 0;
}

void fn_800D5370(s32 value) {
    d_80120008 = value;
}

#ifdef NON_MATCHING
/* Back-face test and a one-pixel nudge of the third vertex (a3) of a triangle (a0 = z limit; a1, a2, a3 = vertices,
 * the screen x/y at +4/+6 and z at +8). Returns early if either of a1/a2 is below z_min, or if the triangle is
 * front-facing (nclip >= 0). Otherwise a3's y (+6) moves one pixel by the ordering of a1 and a2's x (+4), and a3's
 * x (+4) by the ordering of their y (+6). C companion of hand-written asm (not compiled): the GTE loads the three
 * SXY words (SXY0 = a1, SXY1 = a2, SXY2 = a3) and runs NCLIP; the asm reads MAC0 in the branch delay slot and keeps
 * the adjusted values in $at. */
typedef struct ProjVert {
    u32 hdr;  /* +0 */
    s16 sx;   /* +4: SXY word, low half */
    s16 sy;   /* +6: SXY word, high half */
    s16 z;    /* +8 */
} ProjVert;

void fn_800D5380(s32 z_min, ProjVert *v1, ProjVert *v2, ProjVert *v3) {
    s32 winding;

    if ((((s32)v1->z - z_min) | ((s32)v2->z - z_min)) & 0x8000) {
        return;
    }
    gte_load(SXY0, v1, 4);
    gte_load(SXY1, v2, 4);
    gte_load(SXY2, v3, 4);
    gte_nclip();
    gte_get(MAC0, winding);
    if (winding >= 0) {
        return;
    }
    if (v1->sx != v2->sx) {
        v3->sy += (v1->sx < v2->sx) ? 1 : -1;
    }
    if (v1->sy != v2->sy) {
        v3->sx += (v1->sy < v2->sy) ? -1 : 1;
    }
}
#else
INCLUDE_ASM("../src/stage/asm", fn_800D5380);
#endif
