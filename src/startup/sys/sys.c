/* sys: one of startup's own original source files (scripts/objmap.py); part of src/startup/main.c's unit, included there. */

/* sys.c's RCS id. */
static const char sys_c_rcsid[] = "$Id: sys.c,v 1.126 1996/09/13 06:29:54 noda Exp $";

/* Returns the data word at func_800E8718. The original is hand-written asm: the word's address is built in $at (lui/addiu), then lw into $v0. */
extern u32 func_800E8718;

u32 func_800E871C(void) {
    return func_800E8718;
}

/* Reads the big-endian 32-bit offset stored at entry `index` of the table
 * at `base` (4 bytes per entry) and returns the address it points to. */
s32 offset_table_entry(u8 *base, s32 index) {
    u8 *entry;
    s32 offset;
    s32 remaining;
    s32 byte;

    entry = (u8 *)(index * 4 + (s32)base);
    offset = 0;
    remaining = 3;
    do {
        offset = offset << 8;
        byte = *entry;
        entry++;
        remaining--;
        offset = offset + byte;
    } while (remaining >= 0);
    return (s32)base + offset;
}

/* hand-written: PsyQ libgpu GetTPage bit layout computed in $at */
/* PsyQ GetTPage: texture page id from page mode tp, blend abr and VRAM position (x, y). The original is hand-written asm: the asm builds each field in $at with no temporaries. */
u16 func_800E8760(s32 tp, s32 abr, s32 x, s32 y) {
    return ((tp << 7) & 0x180) | ((abr << 5) & 0x60) | ((y & 0x100) >> 4) | ((x & 0x3C0) >> 6);
}

/* Sets the semi-transparency (STP) bit on a 256-entry 16-bit palette.
 * Entry 0 and any entry with color bits zero are cleared to bit 15 off;
 * other entries get bit 15 on, except the last entry (255), which is left alone. */
void palette_set_stp(u16 *palette) {
    s32 i;
    u16 *entry;
    u16 color;

    entry = palette;
    i = 0;
    do {
        color = *entry;
        if (i == 0 || !(color & 0x7FFF)) {
            color &= 0x7FFF;
        } else if (i != 0xFF) {
            color |= 0x8000;
        }
        *entry = color;
        i += 1;
        entry += 1;
    } while (i < 0x100);
}

extern void (*slot_draw_sync)(s32 mode);
extern void (*slot_clear_image)(void *rect, s32 r, s32 g, s32 b);
/* Waits for drawing to finish (DrawSync), clears the 1024x512 VRAM area at (0,0) to black through
 * slot_clear_image, then waits for drawing again. */
void vram_clear(void) {
    Rect rect;
    /* service slot 0x1CA (slot_draw_sync), read through its fixed address */
    void (**draw_sync)(s32) = (void (**)(s32))0x80010728;

    rect.x = 0;
    rect.y = 0;
    rect.w = 0x400;
    rect.h = 0x200;
    (*draw_sync)(0);
    slot_clear_image(&rect, 0, 0, 0);
    (*draw_sync)(0);
}
