/* track: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void fn_800D9E3C(s32 track, s32 value) {
    track_table[track].unk_08 = value;
}

void track_set_slot(s32 n, u32 slot, s32 a, s32 b, s32 c) {
    u8 *entry;

    if (slot < 4) {
        entry = track_table[n].colour[slot];
        entry[0] = a;
        entry[1] = b;
        entry[2] = c;
    }
}

/* Sets track `index`'s mode (0-3; others are ignored). */
void track_set_mode(s32 index, u32 mode) {
    if (mode < 4) {
        track_table[index].mode = mode;
    }
}

void track_set_origin(s32 index, s32 a, s32 b) {
    (track_table + index)->origin_x = a;
    (track_table + index)->origin_y = b;
}

/* Stores a clamped width/height/depth/scale for one slot. Depth is capped
   so depth * (scale) stays under 0x100. */
void track_set_dims(s32 slot, s32 width, s32 height, s32 depth, s32 scale_in) {
    s32 scale;
    s32 tmp;
    TrackDims *rec;

    tmp = width;
    if (width <= 0) {
        tmp = 1;
    }
    width = tmp;
    tmp = height;
    if (height <= 0) {
        tmp = 1;
    }
    height = tmp;
    tmp = depth;
    if (depth <= 0) {
        tmp = 1;
    }
    depth = tmp;
    scale = 2;
    if (scale_in > 0) {
        scale = scale_in + 1;
    }
    scale_in = scale;
    if (depth * scale_in >= 0x101) {
        depth = 0x100 / scale_in;
    }
    rec = &track_dims[slot];
    rec->width = width;
    rec->height = height;
    rec->depth = depth;
    rec->scale = scale_in;
}

/* Sets the halfword at +0x28 of track `index`. */
void track_set_x(s32 index, s32 value) {
    *(s16 *)&track_table[index].pos_x = value;
}

void track_set_y(s32 index, s32 value) {
    track_table[index].pos_y = value;
}

void track_set_phase_rate(s32 n, s32 value) {
    Track *tracks = track_table;
    Track *track = tracks + n;

    track->phase_step = value;
    track->phase = 0;
}

void track_set_angle(s32 index, s32 angle) {
    Track *track;

    angle = MAX(MIN(angle, 0xFFF), 0);
    track = track_table;
    FAKE_OPAQUE(track);
    *(s16 *)track[index].angle_step = angle;
    track[index].angle = 0;
}

/* Resets track `index`. */
void track_reset(s32 index) {
    Track *track;
    s32 *slot;
    s32 i;

    track = &track_table[index];
    slot = track->slots;
    i = 0x80;
    track->phase = 0;
    track->angle = 0;
    track->write_col = 0;
    track->write_row = 0;
    track->last_row = track->rows - 1;
    do {
        *slot = 0;
        i--;
        slot++;
    } while (i > 0);
}

void ring_cursor_advance(RingCursor *cur) {
    s32 pos;
    s32 wrap_at;
    s32 period;

    pos = cur->pos;
    wrap_at = cur->wrap_at;
    period = cur->period;
    pos++;
    cur->hit = 0;
    if (pos >= period) {
        pos -= period;
    }
    cur->pos = pos;
    if (pos == wrap_at) {
        wrap_at++;
        if (wrap_at >= period) {
            wrap_at -= period;
        }
        cur->wrap_at = wrap_at;
        cur->held = cur->hold;
    }
}

/* Appends a command code to track `index`'s slot list (halfwords at +0x34).
 * 0xA1 forces the track's callback; 0xA5 hands off to track_reset.
 * When the list is full the callback runs; the slot after the cursor is cleared. */
void track_push_char(s32 index, s32 cmd) {
    Track *t = &track_table[index];
    s32 modeBits;
    s32 slotOff;

    if (t->enabled == 0 || t->angle != 0) {
        return;
    }
    cmd &= 0xFF;
    modeBits = *(s16 *)&t->mode << 8;
    t->phase = 0;
    if (cmd == 0xA1) {
        goto call_track;
    }
    if (cmd == 0xA5) {
        track_reset(index);
        return;
    }
    if (cmd != 0) {
        cmd |= modeBits;
    }
    slotOff = (t->write_row * *(s16 *)&t->unk_20[4] + t->write_col) * 2 + 0x34;
    *(s16 *)((u8 *)t + slotOff) = cmd;
    t->write_col++;
    if (t->write_col < *(s16 *)&t->unk_20[4]) {
        goto clear_slot;
    }
call_track:
    ring_cursor_advance((RingCursor *)t);
clear_slot:
    slotOff = (t->write_row * *(s16 *)&t->unk_20[4] + t->write_col) * 2 + 0x34;
    *(s16 *)((u8 *)t + slotOff) = 0;
}

s32 track_is_running(s32 i) {
    return track_table[i].angle != 0;
}

/* Field 0 of track `index`. */
s16 track_get_enabled(s32 index) {
    return track_table[index].enabled;
}

/* Advance the two 12-bit phase counters of every active track:
 * unk_32 += unk_30 (wraps), and if unk_2E is running, unk_2E += unk_2C
 * (the s16 view of unk_2C), stopping at 0x1000. */
void track_step_all(void) {
    Track *track = track_table;
    s32 i = 0;
    s16 *phase; /* &track->unk_2E: [-1] unk_2C, [1] unk_30, [2] unk_32 */
    s32 value;

    do {
        phase = &track->angle;
        if (track->enabled != 0) {
            value = phase[2];
            value += phase[1];
            phase[2] = value & 0xFFF;
            value = phase[0];
            if (value != 0) {
                value += phase[-1];
                if (value >= 0x1000) {
                    value = 0;
                }
                phase[0] = value;
            }
        }
        i++;
        track++;
    } while (i < 8);
}

/* track_table's records seen as text tracks: rows of glyphs (high byte the
 * colour slot, low byte the glyph + 0x20), scrolled and drawn as sprites. */
typedef struct TrackText {
    /* 0x000 */ s16 enabled;
    /* 0x002 */ s16 row;
    /* 0x004 */ s16 unk_04;
    /* 0x006 */ s16 last_row;
    /* 0x008 */ s16 priority;
    /* 0x00A */ u16 mode;
    /* 0x00C */ u32 colour[4];
    /* 0x01C */ s16 x;
    /* 0x01E */ s16 y;
    /* 0x020 */ s16 advance;
    /* 0x022 */ s16 line_h;
    /* 0x024 */ s16 cols;
    /* 0x026 */ s16 rows;
    /* 0x028 */ s16 z;
    /* 0x02A */ s16 cursor_z;
    /* 0x02C */ s16 unk_2C;
    /* 0x02E */ s16 scroll;
    /* 0x030 */ s16 unk_30;
    /* 0x032 */ s16 cursor_tick;
    /* 0x034 */ s16 glyphs[0x100];
} TrackText;

/* Queues one sprite record into id_table's bucket level >> 24. */
static inline void text_sprite_add(s32 x, s32 y, s32 scale, s32 z, s32 w, s32 h, s32 level) {
    IdTable *tbl;
    s32 slot;
    s32 index;
    s32 off;
    IdRecord *rec;

    __asm__ volatile("");
    __asm__("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;
    slot = level >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        off = index * 0x14 + 0x24;
        rec = (IdRecord *)((u8 *)tbl + off);
        rec->prev_id = tbl->id[slot];
        tbl->id[slot] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = z;
        rec->field_08 = w;
        rec->field_0A = h;
        rec->field_0C = 0;
        rec->field_10 = level;
    }
}

/* Draws the 8 text tracks: a frame sprite, one sprite per glyph row by row,
 * a blinking cursor, and an end marker. */
void track_text_draw(void) {
    TrackText *t = (TrackText *)track_table;
    s32 i;

    for (i = 0; i < 8; i++, t++) {
        register s32 layer_bits asm("$16");
        s32 row, n, colour, x, y, rows, line_h, cols, advance, z, x0, last_row, cursor;
        s16 *p;

        if (t->enabled == 0) {
            continue;
        }
        z = t->z;
        if (z < 0) {
            continue;
        }
        row = t->row;
        y = t->y;
        last_row = t->last_row;
        cols = t->cols;
        rows = t->rows;
        x0 = t->x;
        advance = t->advance;
        line_h = t->line_h;
        {
            register s32 layer asm("$2") = t->priority;
            layer_bits = layer << 24;
        }
        colour = t->colour[0] | layer_bits;
        if (t->scroll != 0) {
            y -= line_h * t->scroll / 0x1000;
        } else {
            row++;
            if (row >= rows) {
                row -= rows;
            }
        }
        text_sprite_add(t->x, t->y, 0, 0x8001, advance * cols, line_h * (rows - 1), layer_bits);
    next_row:
        {
            p = &t->glyphs[row * cols];
            x = x0;
            for (n = cols; n > 0; n--) {
                register s32 glyph asm("$3") = *p++;
                if (glyph == 0) {
                    break;
                }
                colour = glyph >> 8;
                glyph = (glyph & 0xFF) - 0x20;
                colour = t->colour[colour] | layer_bits;
                if (glyph > 0) {
                    text_sprite_add(x, y, 0x1000, z + glyph, 0, 0, colour);
                }
                x += advance;
            }
            y += line_h;
            if (row != last_row) {
                row++;
                if (row >= rows) {
                    row -= rows;
                }
                goto next_row;
            }
        }
        cursor = t->cursor_z;
        if (cursor >= 0 && t->cursor_tick < 0x800 && t->scroll == 0) {
            text_sprite_add(x, y - line_h, 0x1000, cursor, 0, 0, colour);
        }
        text_sprite_add(0, 0, 0, 0x8000, 0, 0, layer_bits);
    }
}

void fn_800DA718(s32 arg0) {
    d_8012006C = arg0;
}

s32 fn_800DA728(void) {
    return d_8012006C;
}

s32 get_rec_count(void) {
    return rec_count;
}

/* Returns the word that record `index` of rec_table points at, or 0 when index is out of range. */
s32 rec_deref_word(s32 index) {
    if (index >= 0) {
        if (rec_count - 1 >= index) {
            return *(s32 *)rec_table[index].unk_00[0];
        }
    }
    return 0;
}

void *get_rec_data(s32 index) {
    if (index < 0 || rec_count - 1 < index) {
        return 0;
    }
    return &rec_table[index].unk_00[1];
}

s32 get_rec_id(s32 index) {
    if (index >= 0) {
        if (index <= rec_count - 1) {
            return rec_table[index].id;
        }
    }
    return 1;
}

s32 has_rec_entries(void) {
    s32 var_v1;

    var_v1 = 0;
    if (rec_count > 0) {
        var_v1 = aobj_entry_count > 0;
    }
    return var_v1;
}

void colour_table_set(s32 arg0) {
    colour_table_ptr = arg0;
}

s32 colour_table_get(void) {
    return colour_table_ptr;
}

/* Set the first halfword of `count` entries from `first` of the table at 0x80153344. */
void aobj_fill_value(s32 first, s32 count, s32 value) {
    AobjEntry *rec = &aobj_table[first];

    for (; count > 0; count--, rec++) {
        rec->value = value;
    }
}

void clamp_table_set(s32 arg0) {
    clamp_table_ptr = arg0;
}

s32 clamp_table_get(void) {
    return clamp_table_ptr;
}

/* Sets max.x of clamp box index (ignored when out of range). */
void clamp_set_max_x(s32 index, s32 value) {
    u8 *table;

    if (index < 0) {
        return;
    }
    table = (u8 *)clamp_table_ptr;
    if (index <= *(s32 *)table - 1) {
        ((ClampEntry *)(table + (index << 5)))->max.x = value;
    }
}

void slope_table_set(s32 arg0) {
    slope_table_ptr = arg0;
}

s32 slope_table_get(void) {
    return slope_table_ptr;
}

void stage_tables_reset(void) {
    s32 i;
    s32 *words;
    AobjEntry *entry;

    clamp_table_set((s32)clamp_table_default);
    colour_table_set((s32)colour_table_default);
    slope_table_set((s32)slope_table_default);

    entry = aobj_table;
    max_apex_count = 0;
    max_poly_count = 0;
    max_unit_count = 0;
    square_count = 0;
    poly_count = 0;
    i = 0;
    do {
        i++;
        entry->unk_04[0] = 0;
        entry->unk_04[1] = 0;
        entry->unk_04[2] = 0;
        entry->unk_04[3] = 0;
        entry->value = 0;
        entry->flag = 1;
        entry++;
    } while (i < 0x200);
    for (i = 0; i < 0x18; i++) {
        rec_table[i].unk_00[0] = 0;
        words = &rec_table[i].unk_00[1];
        words[0] = 0;
        words[1] = 0;
        words[2] = 0;
        rec_table[i].id = 0;
    }
    stage_offset_y = 0xFFF80000;
    d_80153348 = d_8011D744;
    ground_tile_table = d_8011D768;
    d_80153350 = d_8011D778;
    d_80153354 = d_8011D778;
    rec_count = 0;
    rec_pos_total = 0;
    aobj_entry_count = 0;
    stage_offset_x = 0;
    aobj_entry_count = 1;
    fn_800DA718(0);
}

#if STAGE != 1 && STAGE != 6 && STAGE != 8 && STAGE != 10 && STAGE != 12
RectU mask_buf_rect = {0x300, 0x0, 0x100, 0xD8};
#endif

#if STAGE == 8
u16 msg_areas_remaining[4] = {
    0x0300, 0x0000, 0x0100, 0x00D8,
};
#endif

/* Prints the debug counters: map, unit and object; max apex, polygon and unit; polygon and square. */
void print_load_stats(void) {
    printf("Map:%d Unit:%d Obj:%d\r", rec_count, rec_pos_total, aobj_entry_count);
    printf("MaxApex:%d Poly:%d Unit:%d\r", max_apex_count, max_poly_count, max_unit_count);
    printf("Poly:%d Square:%d \r", poly_count, square_count);
}

void stage_set_offset_x(s32 value) {
    value = MAX(MIN(value, 0x7FFFF), -0x80000);
    stage_offset_x = value;
}

void stage_set_offset_y(s32 value) {
    value = MAX(MIN(value, 0x7FFFF), -0x80000);
    stage_offset_y = value;
}

s32 aobj_count(void) {
    return aobj_entry_count;
}
