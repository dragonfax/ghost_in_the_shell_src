/* ui_draw: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void view_reset(void) {
    ui_item_pool_init();
    view_scale = 0x1000;
    stage_transition_flag = 0;
    dim_level_b = 0x400;
    screen_fade_alpha = 0;
    view_set_on(4, 0);
    view_set_parent(4, -1);
    view_set_camera(4, -1);
    view_set_depth(4, 0);
    set_view_offset(4, 0, 0);
    view_set_size(4, 0x100, 0x100);
    fn_800C94D8(4, 0, 0);
    view_set_clip_size(4, 0x100, 0x100);
    view_set_colour(4, 0, 0, 0, 0);
    view_set_colour_b(4, 0, 0, 0, 0);
    view_set_colour_c(4, 0, 0, 0, 0);
}

void stage_frame_update(void) {
    Item7C *item;
    u8 next;
    s32 x;
    s32 y;

    if (stage_transition_flag == 0) {
        stage_transition_flag = 1;
        switch (stage_end_state) {
        case 2:
            if (get_area() / 3 != 12) {
                ui_item_alloc((void (*)(void))mission_results_setup);
            } else {
                ui_item_alloc(mission_result_update);
            }
            break;
        case 3:
            sound_stop_all();
            if (get_area() / 3 != 12) {
                ui_item_alloc((void (*)(void))stage_end_fade_update);
            } else {
                ui_item_alloc(mission_result_update);
            }
            break;
        }
    }
    next = ui_item_pool[0].next;
    if (next != 0) {
        do {
            item = &ui_item_pool[next];
            next = item->next;
            if (item->update) {
                ((void (*)(Item7C *))item->update)(item);
            }
        } while (next != 0);
    }
    x = stage_screen_w * view_scale;
    if (x < 0) {
        x += 0xFFF;
    }
    x >>= 12;
    y = stage_screen_h * view_scale;
    if (y < 0) {
        y += 0xFFF;
    }
    view_set_clip_size(0, x, y >> 12);
    view_set_on(4, 1);
    view_set_colour(4, 0, 0, 0, screen_fade_alpha);
}

static inline void digit_add(s32 x, s32 y, s32 scale, s32 src, s32 fade, s32 level) {
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
        rec->field_0E = src;
        rec->field_08 = 0;
        rec->field_0A = fade;
        rec->field_0C = 0;
        rec->field_10 = level;
    }
}
/* Draws value as six digits without leading zeros plus the units digit, 13 px
 * apart from x - 0x4E, glyphs of font set `font`, each faded by dist (which
 * drops by 0x400 per digit drawn). Returns the dist left. */
s32 hud_number_draw(s32 x, s32 y, s32 layer, s32 font, s32 dist, s32 value) {
    s32 leading;
    s32 level;
    s32 rest;
    s32 last_fade;
    s32 i;
    s32 digit;
    s32 divisor;
    s32 fade;
    s32 base;
    s32 glyphs;

    leading = 1;
    level = layer << 24;
    x -= 0x4E;
    i = 0;
    base = hud_gfx_base;
    glyphs = base + 0x20;
    base = glyphs + font * 0x10;
    do {
        divisor = number_divisors[i];
        digit = value / divisor;
        if (digit != 0) {
            leading = 0;
        }
        if (leading == 0) {
            fade = 0;
            if (dist < 0x401) {
                fade = 0x400 - dist;
            }
            digit_add(x, y, 0x1000, base + digit, fade, level);
            rest = dist - 0x400;
            if (rest < 0) {
                rest = 0;
            }
            dist = rest;
        }
        i++;
        value %= divisor;
        x += 0xD;
    } while (i < 6);
    if (dist < 0x401) {
        last_fade = 0x400 - dist;
    } else {
        last_fade = 0;
    }
    digit_add(x, y, 0x1000, base + value, last_fade, level);
    rest = dist - 0x400;
    if (rest < 0) {
        rest = 0;
    }
    return rest;
}

/* Pushes an IdRecord at (x, y), scale 0x1000, kind hud_gfx_base + 0x3A, with
 * a fade of 0x400 minus hud_number_draw's distance (0 beyond 0x400), into the
 * bucket given by id. */
void id_table_push(s32 x, s32 y, s32 id, s32 a, s32 b) {
    s32 dist;
    s32 gap;
    s32 level;
    s16 kind;
    s32 scale;
    s32 slot;
    s32 index;
    s32 off;
    IdTable *tbl;
    IdRecord *rec;

    dist = hud_number_draw(x - 0x10, y, id, 1, a, b);
    if (dist < 0x401) {
        gap = 0x400 - dist;
    } else {
        gap = 0;
    }
    level = id << 24;
    kind = hud_gfx_base + 0x3A;
    scale = 0x1000;
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
        rec->field_0E = kind;
        rec->field_08 = 0;
        rec->field_0A = gap;
        rec->field_0C = 0;
        rec->field_10 = level;
    }
}

/* Draws text as font sprites from x, y: colours from the 6-byte rgb table (index restarts at
 * the first character below 0x60), glyphs from 0x40 on fade in by fade (0x400 less each). */
void ui_string_draw(s32 x, s32 y, s32 alpha, s32 fade, u8 *text) {
    u32 colour;
    u8 c;
    s32 base;
    s32 i;
    s32 gap;
    s32 r, g, b;

    base = hud_gfx_base;
    i = 0;
    while (*text != 0) {
        c = *text++;
        if (c < 0x60) {
            i = 0;
        }
        /* Two insns more in c's live range only: colour gets t5, c t6 (global alloc priority). */
        SCHED_BARRIER();
        SCHED_BARRIER();
        r = (text_fade_colours[i].r << 12) / 31;
        r >>= 5;
        g = (text_fade_colours[i].g << 12) / 31;
        g >>= 5;
        b = (text_fade_colours[i].b << 12) / 31;
        b >>= 5;
        if ((r | g | b) == 0) {
            b = 1;
        }
        colour = (alpha << 24) | (b << 16) | (g << 8) | r;
        if (c >= 0x40) {
            if (fade < 0x401) {
                gap = 0x400 - fade;
            } else {
                gap = 0;
            }
            digit_add(x, y, 0x1000, c + base + 0x10, gap, colour);
            fade -= 0x400;
            if (fade < 0) {
                fade = 0;
            }
        }
        switch (c) {
        case '-':
            x += 6;
            break;
        case 'i':
            x += 3;
            break;
        case 'm':
        case 'q':
            x += 0xE;
            break;
        default:
            if (c < 0x60) {
                x += 0xD;
            } else {
                x += 0xC;
            }
            break;
        }
        i++;
    }
}

/* Queues the sprite or number of every used UI item (newest first) by its
 * unk_78 kind, then a fixed sprite at (-0x50, 0x6A) in bucket 4. */
void ui_items_draw(void) {
    u8 cur;
    s32 kind_base;
    Item7C *item;
    s32 index;

    cur = ui_item_used_tail;
    kind_base = hud_gfx_base;
    while (cur != 0) {
        index = cur;
        item = &ui_item_pool[index];
        cur = ui_item_pool_prev[index * sizeof(Item7C)];
        if (item->gfx_index >= 0) {
            switch (item->kind) {
            case 0:
                digit_add(item->x, item->y, item->width, item->gfx_index, 0, item->colour);
                break;
            case 1:
                digit_add(item->x, item->y, 0x1000, item->gfx_index, item->arg.value, item->colour);
                break;
            case 2:
                ui_string_draw(item->x, item->y, item->colour, item->unk_5C, item->arg.text);
                break;
            case 3:
                hud_number_draw(item->x, item->y, item->colour, item->gfx_index, item->unk_5C, *(s32 *)item->arg.text);
                break;
            case 4:
                draw_view_hline(item->x, item->y - 0xF, item->width, item->arg.value, item->unk_5C, 4);
                break;
            case 5:
                id_table_push(item->x, item->y, item->colour, item->unk_5C, *(s32 *)item->arg.text);
                break;
            }
        }
    }
    {
        s32 level = 0x04000000; /* a named local: loads the constant first */
        digit_add(-0x50, 0x6A, 0x1000, kind_base + 3, dim_level_b, level);
    }
}

s32 get_time_bonus(void) {
    s32 value;
    s32 left;
    s32 bonus;
    s32 diff;

    value = get_mission_timer();
    if (value > 0) {
        value = value / 10;
    } else {
        if (meter_mode != 0) {
            value = get_mission_elapsed() - meter_start_time;
        } else {
            value = meter_end_time - meter_start_time;
        }
        left = value;
        if (value < 0) {
            left = 0;
        }
        value = left;
        bonus = gauge_max / 32 * 4;
        diff = value - 0x258;
        value = bonus - diff;
    }
    value = MAX(MIN(value, 0x258), 0);
    return value;
}

s32 meter_is_full(void) {
    return meter_a_level == 0x400;
}

void meter_reset(void) {
    gauge_max = 0x28;
    gauge_value = 0x28;
    meter_mode = 0;
    gauge_flash_level = 0;
    meter_end_time = 0;
    meter_start_time = 0;
}

/* Sets the mode in meter_mode. Entering a nonzero mode from 0 stores get_mission_elapsed() in meter_start_time;
 * leaving mode 1 for 0 stores it in meter_end_time. */
void meter_set_mode(s32 mode) {
    if (mode != 0) {
        if (meter_mode == 0) {
            meter_start_time = get_mission_elapsed();
        }
    } else if (meter_mode == 1) {
        meter_end_time = get_mission_elapsed();
    }
    meter_mode = mode;
}

s32 meter_get_mode(void) {
    return meter_mode;
}
