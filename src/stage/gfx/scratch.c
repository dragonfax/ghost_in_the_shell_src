/* scratch: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void scratch_reset(void) {
    s32 i;
    s32 off;

    pspr_top = 0;
    scratch_slot_count = 0;
    for (i = 7; i >= 0; i--) {
        scratch_slots[i] = 0;
    }
    for (off = 0x1BFC; off >= 0; off -= 4) {
        *(s32 *)(shape_slot_table + off) = 0;
    }
}

void scratch_save(void) {
    scratch_saved_top = pspr_top;
    scratch_saved_slot_count = scratch_slot_count;
}

void scratch_restore(void) {
    pspr_top = scratch_saved_top;
    scratch_slot_count = scratch_saved_slot_count;
}

s32 scratch_slot_get(s32 index) {
    if (index >= 0) {
        if (index <= scratch_slot_count - 1) {
            return scratch_slots[index];
        }
    }
    return 0;
}

void tile_pos_code(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    *arg2 = arg1 & 0xFF;
    *arg3 = arg0 + 0xD8;
}

/* Returns the high nibble shared by all 0x40 bytes at `p`, or -1 if they differ. */
s32 block_uniform_nibble(u8 *p) {
    u8 *end = p + 0x40;
    u32 hi = *p & 0xF0;
    u32 rep;

    rep = (hi << 8) | hi;
    rep = (rep << 8) | hi;
    rep = (rep << 8) | hi;
    while (p != end) {
        if ((*(u32 *)p & 0xF0F0F0F0) != rep) {
            return -1;
        }
        p += 4;
    }
    return hi >> 4;
}

/* Packs a 4-byte colour record into a word (bit 31 set when arg1 != 0, which adds (arg1 - 1) & 3 << 5 to byte 3). */
s32 colour_pack(u8 *c, s32 arg1, s32 arg2) {
    s32 flag = 0;
    s32 sum = arg2 + c[2];
    u8 v = c[3];
    s32 r = c[0];
    s32 g = c[1];

    if (arg1 != 0) {
        flag = 0x80000000;
        v |= ((arg1 - 1) & 3) << 5;
    }
    return flag | ((sum << 22) | (v << 13) | ((g >> 3) << 8) | (r >> 3));
}

/* Uploads `len` bytes of 64-byte texture blocks to free VRAM cells (4-bit blocks of one
 * uniform high nibble are repacked to bytes first), records each block's tpage in the arena,
 * uploads the palette row, then repacks the colour records of `list` in place and registers
 * them as a new scratch slot. Returns the slot's first index, or -1 when it doesn't fit. */
s32 scratch_slot_load(s32 *list, void *pal_image, u8 *blocks, s32 len) {
    s32 count;
    u8 *buf;
    TexCellEntry *entry;
    s32 i, k, rec_count;
    s32 nibble, full, cell, page, sub_index, cell_x, cell_y, cell_y2;
    RECT rect;
    s32 *slot;

    list++;
    count = list[-1];
    if (pspr_top + count > 0x700) {
        return -1;
    }
    buf = arena_top();
    entry = (TexCellEntry *)(buf + 0x40);
    len /= 64;
    for (i = 0; i < len; i++) {
        nibble = block_uniform_nibble(blocks);
        full = (u32)nibble >> 31;
        cell = cell_take_next(full);
        if (cell < 0) {
            cell = 0;
        }
        svc_draw_sync(0);
        rect.x = grid_cell_index(cell);
        rect.y = cell_index_offset(cell);
        rect.h = 8;
        rect.w = full ? 4 : 2;
        if (full) {
            svc_load_image(&rect, blocks);
        } else {
            s32 *src = (s32 *)blocks;
            s32 *end = src + 16;
            u8 *dst = buf;

            while (src != end) {
                s32 v = *src++;
                s32 lo, hi, b0, b1;

                lo = v & 0xF;
                v >>= 4;
                hi = v & 0xF0;
                v >>= 12;
                b0 = lo + hi;
                lo = v & 0xF;
                v >>= 4;
                hi = v & 0xF0;
                b1 = lo + hi;
                dst[0] = b0;
                dst[1] = b1;
                dst += 2;
            }
            svc_load_image(&rect, buf);
        }
        full = full != 0;
        page = cell_index_plain(cell, full);
        sub_index = grid_cell_sub_index(cell, full);
        entry->tpage = (page << 8) + sub_index;
        cell_y = cell_index_offset(cell);
        cell_x = grid_cell_index(cell);
        cell_y2 = cell_index_offset(cell);
        /* getTPage(full, 0, cell_x, cell_y) in place; the y & 0x200 term falls outside the byte. */
        full <<= 7;
        full |= (cell_y & 0x100) >> 4;
        full |= (cell_x & 0x3FF) >> 6;
        full |= (cell_y2 & 0x200) << 2;
        entry->flags = full;
        if (nibble >= 0) {
            entry->nib = nibble;
        } else {
            entry->nib = 0;
        }
        entry++;
        blocks += 0x40;
    }
    svc_draw_sync(0);
    i = 0;
    rect.x = 0;
    rect.w = 0x100;
    rect.h = 1;
    rect.y = scratch_slot_count + 0xD8;
    svc_load_image(&rect, pal_image);
    buf = arena_top();
    entry = (TexCellEntry *)(buf + 0x40);
    slot = (s32 *)shape_slot_table + pspr_top;
    for (; i < count; i++, slot++) {
        list++;
        rec_count = list[-1];
        if (rec_count != 0) {
            ColourRec *rec;

            *slot = (s32)(list - 1);
            rec = (ColourRec *)list;
            for (k = 0; k < rec_count; k++, rec++) {
                rec->u.packed = colour_pack((u8 *)&entry[rec->u.src.index], rec->u.src.mode, scratch_slot_count << 6);
            }
            list = (s32 *)rec;
        }
    }
    scratch_slots[scratch_slot_count] = pspr_top;
    scratch_slot_count++;
    pspr_top += count;
    svc_draw_sync(0);
    return pspr_top - count;
}

void id_table_init(void) {
    s32 none;
    s32 i;
    s16 *p = (s16 *)&id_table;

    id_table.count = 0;
    none = -1;
    for (i = 15; i >= 0; i--) {
        p[i + 2] = none;
    }
}

void draw_view_entries(u8 *ot) {
    DrawXform *xf;
    DrawEntry *e;
    u8 *cursor;
    s32 idx;
    s16 flags;
    s32 x, y, w, h;
    s32 rx, ry, rz;
    s32 uv;
    DrawMatrix *m;
    DrawIdTable *tbl;
    s32 view;
    s32 unused[2];
    s32 one;
    s32 scale, rot;
    DrawView *vw;
    s16 *centre;
    ClipRect *clip;

    view = cur_view_index;
    idx = view_index_table[view];
    tbl = (DrawIdTable *)&id_table;
    if (idx < 0) {
        return;
    }
    xf = scratch_alloc(sizeof(DrawXform));
    one = 0x1000;
    {
        DrawView *views = draw_views;

        vw = &views[view];
    }
    ((s32 *)&xf->base)[2] = one;
    ((s32 *)&xf->base)[0] = one;
    xf->base.m[2][2] = one;
    ((s32 *)&xf->base)[3] = 0;
    ((s32 *)&xf->base)[1] = 0;
    xf->scale_x = vw->scale_x;
    xf->scale_y = vw->scale_y;
    centre = &draw_views[view].centre_x;
    xf->ox = centre[0] << 12;
    xf->oy = centre[1] << 12;
    clip = &draw_views[view].clip;
    x = clip->w;
    y = clip->h;
    xf->clip_w = x << 12;
    xf->clip_h = y << 12;
    cursor = work_area_ptr->packet;
    do {
        e = &tbl->entry[idx];
        flags = e->flags;
        idx = e->next;
        if (flags & 0x8000) {
            u8 *prim;
            WorkArea *wa;
            if ((flags & 0xFFF) == 0) {
                x = (&draw_views[cur_view_index].clip)->x;
                y = (&draw_views[cur_view_index].clip)->y;
                w = (&draw_views[cur_view_index].clip)->w;
                h = (&draw_views[cur_view_index].clip)->h;
            } else {
                x = e->x;
                y = e->y;
                w = x + e->w;
                h = y + e->h;
                x = (x * xf->scale_x + xf->ox) / 4096;
                w = (w * xf->scale_x + xf->ox) / 4096;
                y = (y * xf->scale_y + xf->oy) / 4096;
                h = (h * xf->scale_y + xf->oy) / 4096;
                x = MAX(MIN(x, (&draw_views[cur_view_index].clip)->w), 0);
                w = MAX(MIN(w, (&draw_views[cur_view_index].clip)->w), 0);
                y = MAX(MIN(y, (&draw_views[cur_view_index].clip)->h), 0);
                h = MAX(MIN(h, (&draw_views[cur_view_index].clip)->h), 0);
                w -= x;
                h -= y;
                x += (&draw_views[cur_view_index].clip)->x;
                y += (&draw_views[cur_view_index].clip)->y;
            }
            prim = cursor;
            wa = work_area_ptr;
            cursor += 0xC;
            prim[3] = 2;
            *(u32 *)(prim + 4) = (((wa->draw_y + y) & 0x3FF) << 10) | ((wa->draw_x + x) & 0x3FF) | 0xE3000000;
            *(u32 *)(prim + 8) =
                (((wa->draw_y + y + h - 1) & 0x3FF) << 10) | ((wa->draw_x + x + w - 1) & 0x3FF) | 0xE4000000;
            addPrim(ot, prim);
        } else {
            u32 colour = e->colour;

            colour &= 0xFFFFFF;
            if (colour == 0) {
                colour = 0x848484;
            }
            gte_set(RGB, colour | 0x2C000000);
            /* rx holds the product: a variable used elsewhere keeps it out of LO
             * (FINDINGS "A product evicted from LO by reload") */
            rx = e->x * xf->scale_x;
            x = rx + xf->ox;
            y = e->y * xf->scale_y;
            y += xf->oy;
            gte_set_TR(x, y, 0);
            scale = e->scale;
            x = xf->scale_x * scale / 4096;
            if (x > 0x2000) {
                x = 0x2000;
            }
            xf->base.m[0][0] = x;
            y = xf->scale_y * scale / 4096;
            if (y > 0x2000) {
                y = 0x2000;
            }
            xf->base.m[1][1] = y;
            rx = e->w;
            ry = e->h;
            rz = e->rot_z;
            rx &= 0xFFF;
            ry &= 0xFFF;
            rz &= 0xFFF;
            rot = rx | ry | rz;
            uv = 8;
            if (!(x < 0x2000 && rz == 0 && rx == 0)) {
                uv--;
            }
            uv = (uv << 16) | 0x800;
            if (!(y < 0x2000 && rz == 0 && ry == 0)) {
                uv -= 0x100;
            }
            gte_set(VXY2, uv);
            m = &xf->base;
            if (rot) {
                m = &xf->rot;
                rot_matrix(m, rx, ry, rz);
                mul_matrix(&xf->base, m, m);
            }
            gte_load_R_v1a0v0(m);
            /* Hand-written: draws the sprite list `shape` (count, then pairs of position and uv/clut words) as POLY_FT4s
             * through the GTE rotation, culled against the view, linked in front of the OT entry. %0: cursor, %1: shape,
             * %2: ot, %3: ot again (kept in LO while HI/LO hold the view's clip size). */
            __asm__ volatile(".set\tnoreorder\n\t.set\tnoat\n\t"
                             "lw $t9,0x10(%2)\n\t"
                             "nop\n\t"
                             "mthi $t9\n\t"
                             "lw $t9,0xC(%2)\n\t"
                             "nop\n\t"
                             "mtlo $t9\n\t"
                             "lh $v0,0xE(%1)\n\t"
                             "addu $a1,%3,$zero\n\t"
                             "sll $v0,$v0,2\n\t"
                             "lui $at,%%hi(shape_slot_table)\n\t"
                             "addu $at,$at,$v0\n\t"
                             "lw $v1,%%lo(shape_slot_table)($at)\n\t"
                             "nop\n\t"
                             "beqz $v1,8f\n\t"
                             "nop\n\t"
                             "mtc2 $zero,$1\n\t"
                             "addiu $t9,$zero,0x8\n\t"
                             "mtc2 $t9,$0\n\t"
                             "lui $t9,0x8\n\t"
                             "mtc2 $t9,$2\n\t"
                             "mtc2 $zero,$3\n\t"
                             "nop\n\t"
                             "nop\n\t"
                             ".word 0x4A406012\n\t"
                             "addu $v0,%0,$zero\n\t"
                             "lw $a0,0x0($v1)\n\t"
                             "addiu $t3,$v1,0x4\n\t"
                             "sll $v1,$a0,3\n\t"
                             "addu $t8,$t3,$v1\n\t"
                             "mfc2 $t4,$25\n\t"
                             "mfc2 $t5,$26\n\t"
                             ".word 0x4A40E012\n\t"
                             "lwl $at,0x2(%4)\n\t"
                             "mfc2 $s0,$25\n\t"
                             "mfc2 $t6,$26\n\t"
                             "addu $t1,$zero,$zero\n\t"
                             "xor $v1,$t4,$s0\n\t"
                             "bgez $v1,1f\n\t"
                             "addu $t2,$t4,$s0\n\t"
                             "addu $t1,$s0,$zero\n\t"
                             "addu $t2,$t4,$zero\n"
                             "1:\n\t"
                             "bgez $t4,2f\n\t"
                             "addu $v1,$t1,$zero\n\t"
                             "addu $t1,$t2,$zero\n\t"
                             "addu $t2,$v1,$zero\n"
                             "2:\n\t"
                             "mflo $v1\n\t"
                             "negu $t2,$t2\n\t"
                             "subu $t1,$v1,$t1\n\t"
                             "subu $t1,$t1,$t2\n\t"
                             "mtlo $a1\n\t"
                             "addu $a3,$zero,$zero\n\t"
                             "xor $v1,$t5,$t6\n\t"
                             "bgez $v1,3f\n\t"
                             "addu $t0,$t5,$t6\n\t"
                             "addu $a3,$t5,$zero\n\t"
                             "addu $t0,$t6,$zero\n"
                             "3:\n\t"
                             "bgez $t6,4f\n\t"
                             "addu $v1,$a3,$zero\n\t"
                             "addu $a3,$t0,$zero\n\t"
                             "addu $t0,$v1,$zero\n"
                             "4:\n\t"
                             "mfhi $v1\n\t"
                             "negu $t0,$t0\n\t"
                             "subu $a3,$v1,$a3\n\t"
                             "subu $a3,$a3,$t0\n\t"
                             "mfc2 $t7,$4\n\t"
                             "cfc2 %0,$5\n\t"
                             "cfc2 %1,$6\n"
                             "5:\n\t"
                             "lwc2 $0,0x0($t3)\n\t"
                             "swc2 $6,0x4($v0)\n\t"
                             "nop\n\t"
                             ".word 0x4A406012\n\t"
                             "lw $a0,0x4($t3)\n\t"
                             "addiu $v1,$zero,0x9\n\t"
                             "bgez $a0,6f\n\t"
                             "sb $v1,0x3($v0)\n\t"
                             "addiu $v1,$zero,0x2E\n\t"
                             "sb $v1,0x7($v0)\n\t"
                             "sll $a0,$a0,1\n\t"
                             "srl $a0,$a0,1\n"
                             "6:\n\t"
                             "mfc2 $a1,$25\n\t"
                             "mfc2 $a2,$26\n\t"
                             "addu $a1,$a1,%0\n\t"
                             "subu $v1,$a1,$t2\n\t"
                             "sltu $v1,$t1,$v1\n\t"
                             "bnez $v1,7f\n\t"
                             "addu $a2,$a2,%1\n\t"
                             "subu $v1,$a2,$t0\n\t"
                             "sltu $v1,$a3,$v1\n\t"
                             "bnez $v1,7f\n\t"
                             "sra $v1,$a0,22\n\t"
                             "ori $v1,$v1,0x3600\n\t"
                             "sh $v1,0xE($v0)\n\t"
                             "sll $a0,$a0,3\n\t"
                             "sh $a0,0xC($v0)\n\t"
                             "sra $v1,$t7,16\n\t"
                             "addu $a0,$a0,$v1\n\t"
                             "sw $a0,0x14($v0)\n\t"
                             "sb $zero,0x17($v0)\n\t"
                             "addu $a0,$a0,$t7\n\t"
                             "sh $a0,0x24($v0)\n\t"
                             "subu $a0,$a0,$v1\n\t"
                             "sh $a0,0x1C($v0)\n\t"
                             "sra $v1,$a1,12\n\t"
                             "sh $v1,0x8($v0)\n\t"
                             "sra $v1,$a2,12\n\t"
                             "sh $v1,0xA($v0)\n\t"
                             "addu $a1,$a1,$t4\n\t"
                             "addu $a2,$a2,$t5\n\t"
                             "sra $v1,$a1,12\n\t"
                             "sh $v1,0x10($v0)\n\t"
                             "sra $v1,$a2,12\n\t"
                             "sh $v1,0x12($v0)\n\t"
                             "addu $a1,$a1,$s0\n\t"
                             "addu $a2,$a2,$t6\n\t"
                             "sra $v1,$a1,12\n\t"
                             "sh $v1,0x20($v0)\n\t"
                             "sra $v1,$a2,12\n\t"
                             "sh $v1,0x22($v0)\n\t"
                             "subu $a1,$a1,$t4\n\t"
                             "subu $a2,$a2,$t5\n\t"
                             "sra $v1,$a1,12\n\t"
                             "sh $v1,0x18($v0)\n\t"
                             "sra $v1,$a2,12\n\t"
                             "sh $v1,0x1A($v0)\n\t"
                             "addu $v1,$v0,$zero\n\t"
                             "addiu $v0,$v0,0x28\n\t"
                             "swl $at,0x2($v1)\n\t"
                             "sll $at,$v1,8\n"
                             "7:\n\t"
                             "addiu $t3,$t3,0x8\n\t"
                             "bne $t3,$t8,5b\n\t"
                             "nop\n\t"
                             "mflo $a1\n\t"
                             "swl $at,0x2($a1)\n\t"
                             "addu %0,$v0,$zero\n\t"
                             "8:\n\t"
                             ".set\tat\n\t.set\treorder" : "=r"(cursor) : "r"(e), "r"(xf), "r"(ot), "r"(ot), "0"(cursor)
                             : "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14",
                               "$15", "$16", "$24", "memory");
        }
    } while (idx >= 0);
    scratch_top -= sizeof(DrawXform);
    cursor[3] = 2;
    *(u32 *)(cursor + 4) = 0xE2000000;
    *(u32 *)(cursor + 8) = 0;
    {
        u8 *end = cursor;
        u8 *next = end + 0xC;

        addPrim(ot, end);
        work_area_ptr->packet = next;
    }
}

#ifdef NON_MATCHING
/* Calls draw_view_entries(ot) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * C companion of hand-written asm (not compiled): the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void draw_view_entries_scratch(u8 *ot) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    draw_view_entries(ot);
    SCRATCH_STACK_LEAVE_BELOW();
}
#else
INCLUDE_ASM("../src/stage/asm", draw_view_entries_scratch);
#endif

void track_reset_all(void) {
    Track *track;
    s32 i;
    s32 j;
    s32 *slot;

    track = track_table;
    for (i = 0; i < 8; i++, track++) {
        j = 3;
        slot = (s32 *)&track->colour;
        track->enabled = 0;
        *(s16 *)&track->unk_08 = 0;
        track->mode = 0;
        for (; j >= 0; j--) {
            slot[3] = 0;
            slot--;
        }
    }
}

void track_set_enabled(s32 index, s32 value) {
    track_table[index].enabled = value;
}
