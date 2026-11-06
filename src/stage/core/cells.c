/* cells: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void cell_flags_clear(void) {
    s32 i;
    u8 *cell;

    i = 0xFF;
    cell = &cell_flags[0xFF];
    do {
        *cell = 0;
        i -= 1;
        cell -= 1;
    } while (i >= 0);
    cell_cursor_step2 = 0;
    cell_cursor_step1 = 0;
}

void cell_flags_save(void) {
    s32 i;

    i = 0;
    do {
        cell_flags_saved[i] = cell_flags[i];
        i++;
    } while (i < 0x100);
    cell_cursor_step1_saved = cell_cursor_step1;
    cell_cursor_step2_saved = cell_cursor_step2;
}

void cell_flags_restore(void) {
    s32 i;

    for (i = 0; i < 256; i++) {
        cell_flags[i] = cell_flags_saved[i];
    }
    cell_cursor_step1 = cell_cursor_step1_saved;
    cell_cursor_step2 = cell_cursor_step2_saved;
}

void cell_block_rect(s32 x, s32 y, s32 w, s32 h)
{
    s32 top = y - 0x100;
    s32 i, j;

    w += x;
    x = MAX(MIN(x, 0x400), 0);
    w = MAX(MIN(w, 0x400), 0);
    x = (x + 15) / 16;
    w = (w + 15) / 16;
    w -= x;
    h += top;
    top = MAX(MIN(top, 0x100), 0);
    h = MAX(MIN(h, 0x100), 0);
    top = (top + 63) / 64;
    h = (h + 63) / 64;
    h -= top;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            s32 cell = (x + i) * 4 + (top + j);
            cell_flags[cell] = 1;
        }
    }
}

/* Finds a free width x height block in cell_flags, marks it taken, returns its offset (-1 if none). */
s32 cell_block_alloc(s32 width, s32 height, s32 full)
{
    s32 colStep, rowStep, rowsPer, found, base, limit, row, col, idx;
    s32 used, i, j;
    u8 *p;
    s32 unused[2]; /* unused local: the original frame is 8 bytes larger */

    height = (height + 63) / 64;
    width = (width + 31) / 32;
    colStep = 1;
    while (colStep < width) {
        colStep *= 2;
    }
    rowStep = 1;
    while (rowStep < height) {
        rowStep *= 2;
    }
    rowsPer = 2;
    if (full == 0) {
        width /= 2;
        colStep /= 2;
        rowsPer = 1;
    }
    found = -1;
    for (base = 0; base <= 64 - colStep; base += 4) {
        limit = 64 - base;
        if (rowsPer * 4 < limit) {
            limit = rowsPer * 4;
        }
        for (row = 0; row <= limit - colStep; row += colStep) {
            for (col = 0; col <= 4 - rowStep; col += rowStep) {
                idx = (base + row) * 4 + col;
                used = 0;
                p = &cell_flags[idx];
                for (i = 0; i < width;) {
                    j = 0;
                    if (height > 0) {
                        do {
                            j++;
                            used |= *p;
                            p++;
                        } while (j < height);
                    }
                    i++;
                    p += 4 - height;
                }
                if (used == 0) {
                    p = &cell_flags[idx];
                    for (i = 0; i < width;) {
                        for (j = 0; j < height; j++) {
                            *p |= 1;
                            p++;
                        }
                        i++;
                        p += 4 - height;
                    }
                    found = idx;
                    goto done;
                }
            }
        }
    }
done:
    if (found >= 0) {
        found <<= 6;
    }
    return found;
}

/* Index into an 8-wide grid of 2-halfword cells, 4 rows of 64 per group of 16 words (n / 256 * 16 + n % 8 * 2). */
s32 grid_cell_index(s32 n) {
    s32 col = n % 8 * 2;

    n = n / 64;
    return n / 4 * 16 + col;
}

/* cell_index_plain plus 0x100; `base` keeps the add on `lo`. */
s32 cell_index_offset(s32 angle)
{
    s32 fine = angle / 8;
    s32 coarse = fine / 8;
    s32 lo = (fine % 8) * 8;
    s32 base = 0x100;

    angle = coarse;
    return (angle % 4) * 64 + (lo + base);
}

s32 grid_cell_sub_index(s32 index, s32 half) {
    /* unused: keeps the 8-byte stack frame the original reserves */
    s32 unused[2];
    s32 bias8;
    s32 bias64;
    s32 x;
    s32 y;

    bias8 = index;
    if (index < 0) {
        bias8 = index + 7;
    }
    bias64 = index;
    do {
        x = (index - ((bias8 >> 3) << 3)) << 3;
    } while (0);
    if (index < 0) {
        bias64 = index + 63;
    }
    index = bias64 >> 6;
    index /= 4;
    if (half == 0) {
        y = (index % 4) << 6;
    } else {
        y = (index % 4) << 5;
        x >>= 1;
    }
    return y + x;
}

/* `lo` uses `coarse` before `angle = coarse`: that keeps the original's copy (FINDINGS "Copies cse deletes"). */
s32 cell_index_plain(s32 angle, s32 half)
{
    s32 fine = angle / 8;
    s32 coarse = fine / 8;
    s32 lo = (fine % 8) * 8;

    angle = coarse;
    return (angle % 4) * 64 + lo;
}

s32 cell_next_free(s32 pos, s32 mode) {
    s32 cell = pos / 64;

    if (mode == 1) {
        if ((cell / 4) % 8 == 7 && pos % 8 >= 6) {
            pos += 2;
            cell = pos / 64;
        }
    } else {
        if ((cell / 4) % 4 == 3 && pos % 8 >= 7) {
            pos += 1;
            if (pos < cell_cursor_step2) {
                pos = cell_cursor_step2;
            }
            cell = pos / 64;
        }
    }
    if (!(cell % 4 == 3 && (pos / 8) % 8 == 7) && !(cell_flags[cell] & 1)) {
        return pos;
    }
    for (; cell < 256; cell++) {
        if (cell_flags[cell] == 0) {
            break;
        }
    }
    if (cell < 256) {
        return cell << 6;
    }
    return -1;
}

/* Takes the next position for `mode`. Mode 1 uses the cursor cell_cursor_step2 and moves it on by 2; any other mode uses
 * cell_cursor_step1 and moves it on by 1. The position's 64-unit cell is marked taken (bit 1 of cell_flags). Then the
 * cursors are kept level: the lower one moves up past the other (rounded to an even position). */
s32 cell_take_next(s32 mode) {
    s32 pos;
    s32 offset;
    s32 cell;

    if (mode == 1) {
        pos = cell_next_free(cell_cursor_step2, 1);
        cell_cursor_step2 = pos + 2;
    } else {
        pos = cell_next_free(cell_cursor_step1, mode);
        cell_cursor_step1 = pos + 1;
    }
    offset = pos;
    if (pos < 0) {
        offset = pos + 0x3F;
    }
    cell = offset >> 6;
    cell_flags[cell] = cell_flags[cell] | 2;
    if (cell_cursor_step2 < cell_cursor_step1) {
        cell_cursor_step2 = (cell_cursor_step1 + 1) & ~1;
    } else if ((cell_cursor_step1 < cell_cursor_step2) && !(cell_cursor_step1 & 1)) {
        cell_cursor_step1 = cell_cursor_step2;
    }
    return pos;
}
