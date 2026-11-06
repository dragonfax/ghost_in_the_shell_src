/* debug_print: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* strcpy without the terminator */
void str_copy_no_nul(u8 *dst, u8 *src) {
    u8 c;

    while ((c = *src++) != 0) {
        *dst++ = c;
    }
}

/* Debug menu rows: blank the 7 row slots of the text buffer, put the
   marker in the current row, then print ON/OFF for each of the 5 flags. */
void debug_menu_text(void) {
    s32 i;
    s32 *flag;
    u8 *row;

    i = 0;
    do {
        s32 next = i + 1;
        *(debug_menu_marks + (next << 5)) = 0x20;
        i = next;
    } while (i < 7);

    i = 1;
    row = debug_menu_flag_cell;
    flag = &debug_info_flag;
    *(debug_menu_marks + ((debug_menu_cursor + 1) << 5)) = 0x6A;
    for (; i < 6; i++) {
        if (*flag != 0) {
            str_copy_no_nul(row, "ON ");
        } else {
            str_copy_no_nul(row, "OFF");
        }
        row += 0x20;
        flag++;
    }
}

/* Draws the debug menu: 7 rows, two rows with a number, and a last row. */
void debug_menu_draw(void) {
    s32 x;
    s32 y;
    s32 row;

    if (debug_menu_enabled != 0) {
        debug_menu_text();
        x = (stage_screen_w / 8 - 18) / 2;
        y = 10;
        for (row = 0; row < 7; row++) {
            debug_set_cursor(x, y++);
            debug_print_str(debug_menu_text_rows[row]);
        }
        debug_set_cursor(x, y++);
        debug_printf(debug_menu_text_rows[row++], get_shield());
        debug_set_cursor(x, y++);
        debug_printf(debug_menu_text_rows[row++], heap_get_top());
        debug_set_cursor(x, y);
        debug_print_str(debug_menu_text_rows[row]);
    }
}

void debug_info_draw(void) {
    s32 row;
    s32 x, y, z;
    s32 ax, ay, az;
    s16 *rec;
    s32 id;
    s32 col;

    col = 0;
    debug_set_cursor(0, 0);
    debug_print_str("agggggggggc");
    row = 2;
    debug_set_cursor(0, 1);
    debug_printf("eSYNC:%d1/%d2f", frames_pending, get_fps());
    if (timed_part()) {
        row = 3;
        debug_set_cursor(0, 2);
        if (part_time_get() >= 0) {
            x = part_time_get();
        } else {
            x = -part_time_get();
        }
        debug_printf("eT:%d4.%d2f", x / 60, x % 60);
    } else {
        if (player_mode) {
            x = player_xyz[0] >> 12;
            y = player_xyz[1] >> 12;
            z = player_xyz[2] >> 12;
        } else {
            x = cameras[0].pos.vx;
            y = cameras[0].pos.vy;
            z = cameras[0].pos.vz;
        }
        debug_set_cursor(col, row++);
        debug_printf("eX:%l7f", x);
        debug_set_cursor(col, row++);
        debug_printf("eY:%l7f", y);
        debug_set_cursor(col, row++);
        debug_printf("eZ:%l7f", z);
        ax = cameras[0].rot.vx;
        ay = cameras[0].rot.vy;
        az = cameras[0].rot.vz;
        debug_set_cursor(col, row++);
        debug_printf("eAZX:  %x3f", ay);
        debug_set_cursor(col, row++);
        debug_printf("eAYZ:  %x3f", ax);
        debug_set_cursor(col, row++);
        debug_printf("eAXY:  %x3f", az);
    }
    if (player_mode) {
        debug_set_cursor(col, row);
        id = player_ground_id;
        row++;
        rec = (s16 *)rec_table_word_addr(id);
        if (rec) {
            debug_printf("eCH:%x2/%x3f", id & 0xFF, rec[3]);
            debug_set_cursor(col, row++);
            debug_printf("eSTAT:%x4f", surface_of(id));
        } else {
            debug_print_str("eCH:--/---f");
            debug_set_cursor(col, row++);
            debug_print_str("eSTAT:----f");
        }
    }
    id = ((WorkAreaPool *)work_area_ptr)->limit - ((WorkAreaPool *)work_area_ptr)->packet;
    debug_set_cursor(col, row++);
    debug_printf("eMEM:%x5f", id);
    if (debug_check_b()) {
        debug_set_cursor(col, row++);
        debug_printf("eUV:%x6f", fn_800B6E04());
    }
    debug_set_cursor(col, row);
    debug_print_str("bhhhhhhhhhd");
}

/* Draw a cols x rows block of 8x8 glyph cells from the 1-bit font at font_bitmap into video memory:
 * each cell is 2 words wide (4 bits per pixel: 2 = set, 1 = set in the previous row's shadow). */
void font_load_glyphs(s32 x, s32 y, s32 cols, s32 rows) {
    s32 buf[8];
    u16 rect[4];
    u8 *src = font_bitmap;
    s32 col, i, bit;
    u8 cur;
    u8 prev;
    s32 word;

    rect[2] = 2;
    rect[3] = 8;
    rect[1] = y;
    while (rows > 0) {
        rect[0] = x;
        for (col = 0; col < cols; col++) {
            for (i = 0; i < 8; i++) {
                cur = *src++;
                prev = 0;
                if (i != 0) {
                    prev = src[-2];
                }
                prev >>= 1;
                word = 0;
                for (bit = 8; bit > 0; bit--) {
                    word *= 16;
                    if (cur & 1) {
                        word |= 2;
                    } else if (prev & 1) {
                        word |= 1;
                    }
                    cur >>= 1;
                    prev >>= 1;
                }
                buf[i] = word;
            }
            svc_load_image(rect, buf);
            rect[0] += rect[2];
        }
        rows--;
        rect[1] += rect[3];
    }
    svc_draw_sync(0);
}

void font_load_clut(s16 x, s16 y) {
    s16 rect[4];

    rect[0] = x;
    rect[2] = 4;
    rect[1] = y;
    rect[3] = 1;
    svc_load_image(rect, font_clut);
    svc_draw_sync(0);
}

/* Draws character c at the text cursor (an 8x8 glyph sprite) and advances the cursor. */
void text_put_char(u8 c) {
    GlyphSprite *sprite;
    u8 *ot;
    s32 code;

    sprite = work_area_ptr->packet;
    work_area_ptr->packet = sprite + 1;
    sprite->len = 3;
    /* SPRT_8, raw texture; an int temp keeps cse from dropping the else store */
    code = 0x75;
    sprite->code = code;
    /* PsyQ setSemiTrans */
    if (font_semi_trans_flag) {
        sprite->code = 0x77;
    } else {
        sprite->code = 0x75;
    }
    sprite->clut = ((font_page_y + font_y_offset) << 6) | ((font_page_x >> 4) & 0x3F);
    sprite->x = (text_cursor_x + text_origin_x) * 8;
    sprite->y = (text_cursor_y + text_origin_y) * 8;
    sprite->uv = ((u16 *)&font_cell_uv_table)[c & 0x7F];
    do {
    } while (0);
    ot = text_packet_cur;
    {
        /* addPrim(ot, sprite) */
        u32 link, self;
        ot_link_load(link, ot);
        self = (u32)sprite << 8;
        ot_link_store(sprite, link);
        ot_link_store_mem(ot, self);
    }
    text_cursor_x++;
}

void debug_print_str(char *text) {
    u8 c;

    while ((c = *text++) != 0) {
        text_put_char(c);
    }
}

/* Print n in decimal, zero-padded to at least `digits` digits (text_put_char prints one character). */
void debug_print_dec(u32 n, s32 digits) {
    u32 div = 1000000000;
    s32 skip = 10;
    u32 d;

    if (digits < 10) {
        skip -= digits;
    }
    do {
        d = n / div;
        if (skip <= 0 || d != 0 || div == 1) {
            skip = 0;
            text_put_char(d + '0');
        }
        skip--;
        n -= d * div;
        div /= 10;
    } while (div != 0);
}

/* Prints a sign (' ' or '-') and then the magnitude of n. */
void debug_print_signed(s32 n, s32 width) {
    s32 sign = ' ';

    if (n < 0) {
        sign = '-';
        n = -n;
    }
    text_put_char(sign);
    debug_print_dec(n, width - 1);
}

/* Prints the low nibble of value as a hex digit (text_put_char prints a character). */
void debug_print_hex_digit(s32 value) {
    u32 digit;

    digit = value & 0xF;
    if (digit >= 10) {
        digit += 'A' - '0' - 10;
    }
    text_put_char((u8)(digit + '0'));
}

/* Prints the low `bits` bits of value as hex digits (at most 8), most significant first. `bits` is reused
 * for the digit count. */
void debug_print_hex(u32 value, s32 bits) {
    s32 i;

    bits = (bits + 3) / 4;
    bits = MAX(MIN(bits, 8), 0);
    for (i = 0; i < bits; i++) {
        debug_print_hex_digit(value >> ((bits - 1 - i) * 4));
    }
}

/* Print a byte as two hex digits (text_put_char prints one character). */
void debug_print_hex_byte(u32 n) {
    u32 digit;

    digit = (n & 0xF0) >> 4;
    if (digit >= 10) {
        digit += 'A' - '0' - 10;
    }
    text_put_char(digit + '0');
    digit = n & 0xF;
    if (digit >= 10) {
        digit += 'A' - '0' - 10;
    }
    text_put_char(digit + '0');
}

/* Print a word as 8 hex digits. */
void debug_print_hex32(u32 value) {
    debug_print_hex_byte(value >> 0x18);
    debug_print_hex_byte((value >> 0x10) & 0xFF);
    debug_print_hex_byte((value >> 8) & 0xFF);
    debug_print_hex_byte(value & 0xFF);
}

/* Print the low halfword as 4 hex digits. */
void debug_print_hex16(u32 value) {
    debug_print_hex_byte((value >> 8) & 0xFF);
    debug_print_hex_byte(value & 0xFF);
}

/* Prints the text at *text up to a '%' and parses the conversion after it: *kind 1 for 's', 2 for 'd',
 * 3 for 'l', 4 for 'x' (the last three followed by a digit, the width, in *width); 0 for none. *text is
 * left after what was read. */
void debug_printf_parse(char **text, s32 *kind, s32 *width) {
    u8 *p;
    s32 w;
    s32 k;
    u8 c;

    p = *text;
    w = *p;
    k = 0;
    c = w;
    w = 0;
    if (c != 0) {
        do {
            if (c == '%') {
                goto spec;
            }
            p++;
            text_put_char(c);
            c = *p;
        } while (c != 0);
    }
    if (c == '%') {
spec:
        p++;
        c = *p;
        p++;
        if (c == 's') {
            k = 1;
        } else {
            if (c == 'd') {
                k = 2;
            } else if (c == 'l') {
                k = 3;
            } else if (c == 'x') {
                k = 4;
            } else {
                goto done;
            }
            w = *p++ - '0';
        }
    }
done:
    *text = p;
    *kind = k;
    *width = w;
}

/* Debug print: the string `format` and then one argument per item that debug_printf_parse finds in it
 * (kind 1 text, 2 and 3 numbers, 4 a block of `count` words), until it reports kind 0. */
void debug_printf(char *format, ...) {
    s32 kind;
    s32 count;
    char **args;
    char *arg;

    args = &format + 1;
    do {
        debug_printf_parse(&format, &kind, &count);
        arg = *args++;
        if (kind == 1) {
            debug_print_str(arg);
        } else if (kind == 2) {
            debug_print_dec((u32)arg, count);
        } else if (kind == 3) {
            debug_print_signed((s32)arg, count);
        } else if (kind == 4) {
            debug_print_hex((u32)arg, count * 4);
        }
    } while (kind != 0);
}

/* Set the text cursor (column, row). */
void debug_set_cursor(s32 x, s32 y) {
    text_cursor_x = x;
    text_cursor_y = y;
}

void text_set_origin(s32 a, s32 b) {
    text_origin_x = a;
    text_origin_y = b;
}

void text_flip(void) {
    u16 index;
    u8 *packet;

    svc_draw_otag(text_packet_cur);
    index = text_packet_index + 1;
    text_packet_index = index;
    if ((s16)index >= 2) {
        text_packet_index = 0;
    }
    packet = text_packets + (s16)text_packet_index * 0xC;
    text_packet_cur = packet;
    TERM_LINK(packet, -0x100);
}

/* Set the font position in VRAM (texture page x/y). */
void font_set_page(s32 x, s32 y) {
    font_page_x = x & 0x3C0;
    font_page_y = y & 0x100;
    font_y_offset = y & 0xFF;
}

void font_set_palette(s32 a, s32 b, s32 c) {
    font_clut[0] = a;
    font_clut[1] = b;
    font_clut[2] = c;
    font_semi_trans_flag = 0;
    if ((a | b | c) & 0x8000) {
        font_semi_trans_flag = 1;
    }
}

#if STAGE != 1
extern s32 texpage_current;
#endif

void texpage_set(s32 arg0) {
    texpage_current = arg0;
}

/* Rebuilds the 128 texture-cell tables at font_cell_uv_table/09 (the cell index split into 8-pixel units), then
 * writes two DR_MODE packets with the current texture page. */
void font_init(void) {
    s32 i;
    s32 col;
    s32 row;
    s32 off;
    u8 *packet;

    font_load_glyphs(font_page_x, font_page_y + font_y_offset, 0x20, 4);
    ((void (*)(s32, s32))font_load_clut)(font_page_x, font_page_y + font_y_offset); /* no s16 truncation at the call */

    i = 0;
    off = 0;
    do {
        col = i;
        if (i < 0) {
            col = i + 0x1F;
        }
        row = col >> 5;
        *(&font_cell_uv_table + off) = (i - (row << 5)) * 8;
        *(&font_cell_v + off) = (row * 8) + font_y_offset;
        i++;
        off += 2;
    } while (i < 0x80);

    packet = text_packets;
    for (i = 0; i < 2; i++) {
        fn_800B6DB4(packet, 0, 0,
                    ((texpage_current & 3) << 5) | ((font_page_y & 0x100) >> 4) | ((font_page_x & 0x3FF) >> 6) |
                        ((font_page_y & 0x200) * 4),
                    &font_tex_window);
        TERM_LINK(packet, -0x100);
        packet += 0xC;
    }
}

/* Returns ramp_is_done's result (stage_exit_ready tests it). */
s32 part_is_done(void) {
    return ramp_is_done();
}

s32 part_time_get(void) {
    return part_time;
}

s32 part_timer_get(void) {
    return part_timer_on;
}

/* Turn the part timer on or off. */
void part_timer_set(s32 value) {
    part_timer_on = value;
}
