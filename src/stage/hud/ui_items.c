/* ui_items: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

s32 msg_is_busy(void) {
    s32 result;

    result = 0;
    if (msg_enabled != 0) {
        result = meter_is_full() != 0;
    }
    return result;
}

s32 id_table_default_bucket(void) {
    return 2;
}

void set_view_rect(s16 a, s16 b, s16 c, s16 d) {
    hud_view_x = a;
    hud_view_y = b;
    hud_view_w = c;
    hud_view_h = d;
}

s32 msg_scroll_started(void) {
    return (u32) ~msg_scroll_timer >> 0x1F;
}

void gauge_reset(void) {
    msg_queue_clear();
    msg_wait_timer = 0;
    msg_text_ptr = 0;
    if (untimed_part()) {
        track_reset(0);
    }
}

/* Area setup: resets the msg_scroll_timer state, then, except on the first area of a group of three or
 * when part_timer_get() is 1, configures overlay 2 and track 0. */
void area_setup(void) {
    s32 setup;

    msg_scroll_timer = 0;
    gauge_reset();
    hud_set_on(1);
    set_msg_enabled(1);
    hud_view_x = 3;
    hud_view_y = 0xAD;
    hud_view_w = 0x60;
    hud_view_h = 0x1E;
    if (get_area() % 3 == 0) {
        setup = 0;
    } else {
        setup = part_timer_get() != 1;
    }
    if (setup) {
        view_set_on(2, 0);
        view_set_parent(2, 0);
        view_set_depth(2, 0);
        view_set_camera(2, -1);
        view_set_colour(2, 0, 0, 0, 0x30);
        view_set_colour_b(2, 0, 0, 0, 0);
        view_set_colour_c(2, 0, 0, 0, 0);
        track_set_enabled(0, 1);
        fn_800D9E3C(0, 2);
        track_set_origin(0, 0, 0);
        track_set_dims(0, 5, 7, 0x13, 4);
        track_set_x(0, track_base + 0x50);
        track_set_y(0, track_base + 0x8F);
        track_set_phase_rate(0, 0x200);
        track_set_angle(0, 0x200);
        track_set_slot(0, 0, 0x28, 0x70, 0x18);
        track_set_slot(0, 3, 0x28, 0x70, 0x18);
        track_set_slot(0, 1, 0x7C, 0x40, 0x10);
        track_set_slot(0, 2, 0x6C, 0x70, 0x20);
        track_set_mode(0, 0);
        track_reset(0);
    }
}

/* Message typewriter step: feeds the next character of the current line
 * (msg_text_ptr) to track 0, popping a new line from msg_queue when done.
 * "#n" sets the track mode (0-3), "|n" waits n*20 frames, '_' is a space.
 * Returns 1 while busy, 0 when nothing is left (or stage flag 4 is set). */
s32 msg_typewriter_step(void) {
    u8 *text;
    s32 c;
    s32 frames;
    s32 track;

    if (get_stage_flags() & 4) {
        return 0;
    }
    if (track_is_running(0) != 0) {
        return 1;
    }
    if (msg_wait_timer > 0) {
        msg_wait_timer--;
        return 1;
    }
    text = msg_text_ptr;
    track = 0;
    if (text == NULL) {
    next_line:
        msg_text_ptr = NULL;
        text = (u8 *)msg_line_pop();
        if (text == NULL) {
            return 0;
        }
    }
    for (;;) {
        c = *text++;
        if (c == 0) {
        end_line:
            track_set_mode(track, 0);
            goto next_line;
        }
        if (c == '#') {
            c = *text++;
            if (c == 0) {
                goto end_line;
            }
            c -= '0';
            {
                register s32 mode asm("$2") = MIN(c, 3);

                if (MIN(c, 3) < 0) {
                    mode = 0;
                }
                track_set_mode(track, mode);
            }
            continue;
        }
        if (c == '|') {
            c = *text++;
            if (c == 0) {
                goto end_line;
            }
            c -= '0';
            frames = MIN(c, 9);
            if (MIN(c, 9) < 0) {
                frames = 0;
            }
            msg_wait_timer = frames * 20;
        } else {
            if (c == '_') {
                c = ' ';
            }
            if (c == 0xA1) {
                msg_wait_timer = 3;
            } else {
                msg_wait_timer = 0;
            }
            track_push_char(0, c);
        }
        msg_text_ptr = text;
        return 1;
    }
}

void hud_update(void) {
    s32 offset;
    s32 rest;
    s16 *width;

    if (untimed_part()) {
        view_set_on(2, hud_on_flag != 0);
        width = &hud_view_w;
        view_set_size(2, *width, hud_view_h);
        view_set_pivot(2, 0, 0);
        fn_800C94D8(2, 0, 0);
        offset = hud_view_h * (s16)rcossin_tbl[meter_b_level & 0xFFF] >> 12;
        rest = hud_view_h - offset;
        set_view_offset(2, hud_view_x, rest / 2 + hud_view_y);
        view_set_clip_size(2, *width, offset);
        track_set_enabled(0, msg_enabled != 0);
        if (meter_b_level >= 0x400) {
            if (msg_typewriter_step() != 0) {
                msg_scroll_timer = 0;
            } else {
                msg_scroll_timer = msg_scroll_timer + 1;
                if (msg_scroll_timer >= 0xF0) {
                    msg_scroll_timer = -0x1E;
                }
            }
        } else {
            msg_scroll_timer = MIN(msg_queue_count() - 1, msg_scroll_timer + 1);
        }
        if (msg_enabled == 0) {
            msg_scroll_timer = 0;
        }
    }
}

void fn_80100880(void) {

}

void show_line(s32 line) {
    if (msg_enabled != 0) {
        msg_line_push(line);
        message_shown_flag = 1;
    }
}

void pause_menu_setup(void) {
    view_set_on(3, 0);
    view_set_parent(3, 0);
    view_set_depth(3, 0);
    view_set_camera(3, -1);
    set_view_offset(3, 0x40, 0x56);
    fn_800C94D8(3, 0, 0);
    view_set_size(3, 0x78, 0x2C);
    view_set_clip_size(3, 0x78, 0x2C);
    view_set_pivot(3, 0, 0);
    view_set_colour(3, 0, 0, 0, 0x60);
    view_set_colour_b(3, 0, 0, 0, 0);
    view_set_colour_c(3, 0, 0, 0, 0);
    pause_menu_angle = 0;
    pause_menu_cursor = 0;
    pause_menu_cursor_prev = 0;
    pause_menu_choice = 0;
}

/* The pause menu: three entries (1 continue, 2 set_stage_end(1), 3 quit: set_stage_end(4)); the window opens and closes with a
 * sine-shaped height. Returns the choice once it has closed, else 0. */
s32 pause_menu(void) {
    static const s16 choices[4] = { 1, 2, 3, 0 };
    s32 result = 0;
    s32 layer = 3;
    s32 pressed;
    s32 angle;
    s32 cursor;
    s32 choice;
    s32 t;
    s32 h;

    choice = pause_menu_choice;
    if (choice == 0) {
        angle = pause_menu_angle;
        angle = CLAMP_HI(angle + 0xC0, 0x400);
        pause_menu_angle = angle;
        pressed = pad1_pressed;
        if (pressed & PAD_UP) {
            pause_menu_cursor--;
        }
        if (pressed & PAD_DOWN) {
            pause_menu_cursor++;
        }
        cursor = pause_menu_cursor;
        if (cursor > 2) {
            cursor = 2;
        }
        t = pause_menu_cursor;
        if (t > 2) {
            t = 2;
        }
        if (t < 0) {
            cursor = 0;
        }
        pause_menu_cursor = cursor;
        if (pause_menu_cursor != pause_menu_cursor_prev) {
            sound_play_note(SND_MENU_CURSOR_MOVE | SND_VOICE_FLAG, 0x78, 0x3F, 0x3C);
        }
        pause_menu_cursor_prev = pause_menu_cursor;
        if (pressed & PAD_START) {
            pause_menu_choice = choices[pause_menu_cursor];
            sound_play_note(SND_MENU_CONFIRM | SND_VOICE_FLAG, 0x78, 0x3F, 0x3C);
        }
    } else {
        angle = pause_menu_angle - 0x100;
        if (angle < 0) {
            angle = 0;
        }
        pause_menu_angle = angle;
        if (angle == 0) {
            result = choice;
            pause_menu_choice = 0;
            pause_menu_cursor = 0;
            pause_menu_cursor_prev = 0;
            view_set_on(layer, 0);
            switch (result) {
            case 3:
                sound_stop_list();
                set_stage_end(4);
                set_stage_flags(get_stage_flags() | 6);
                break;
            case 2:
                set_stage_end(1);
                break;
            }
        }
    }
    view_set_on(layer, 1);
    h = (s16)rcossin_tbl[pause_menu_angle & 0xFFF] * 11 >> 10;
    set_view_offset(layer, 0x40, (0x2C - h) / 2 + 0x56);
    view_set_clip_size(layer, 0x78, h);
    return result;
}

static inline void pause_item_add(s32 tag, s32 x, s32 y, s32 scale, s32 depth)
{
    IdTableRecords *tbl;
    s32 index;
    IdRecord *rec;
    s32 list;

    tbl = (IdTableRecords *)&id_table;
    __asm__ volatile("");
    __asm__ volatile("" : "=r"(tbl) : "0"(tbl));
    index = tbl->count;
    list = tag >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = tbl->id[list];
        tbl->id[list] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = depth;
        rec->field_08 = 0;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = tag;
    }
}
/* Pause menu: the frame, the cursor and three items (highlighted at the cursor). */
void pause_menu_draw(void)
{
    s32 colors[2];
    s32 now;
    s32 i;
    s32 item_depth;
    s32 y;
    s32 depth;
    s32 *color;

    now = hud_gfx_base;
    if (pause_menu_angle != 0) {
        view_set_on(3, 1);
        colors[0] = 0x03404040;
        colors[1] = 0x03000000;
        pause_item_add(0x03000000, 0, 0, 0x1000, hud_gfx_base + 8);
        pause_item_add(colors[1], 7, pause_menu_cursor * 12 + 6, 0x1000, now + 9);
        for (i = 0, y = 6, depth = now + 0xA; i < 3; y += 12, i++, depth += 2) {
            register s32 cur asm("$3") = pause_menu_cursor;

            item_depth = depth + (cur == i);
            color = &colors[0];
            if (cur == i) {
                color = &colors[1];
            }
            pause_item_add(*color, 0x12, y, 0x1000, item_depth);
        }
    }
}

void ui_item_pool_init(void) {
    u8 *p;
    s32 i;

    ui_item_free_count = 0x28;
    i = 0;
    p = ui_item_next_field;
    do {
        p[-1] = i - 1;
        i++;
        *p = i;
        p += 0x7C;
    } while (i < 0x29);
    ui_item_next_field[0] = 0;
    ui_item_pool_prev[0] = 0;
    d_8012DB2E = 0;
    d_8012EE13 = 0;
    ui_item_free_head = 1;
    ui_item_used_tail = 0;
}

/* Takes an item from the free list, appends it to the used list and sets it up to call `update`. */
s32 ui_item_alloc(void (*update)(void)) {
    s32 *head = &ui_item_free_head;
    u8 first;
    s32 index;
    s32 last;
    s32 offset;
    u8 *item;
    u8 *base;

    first = *head;
    index = first;
    if (index != 0) {
        offset = index * sizeof(Item7C);
        *head = ui_item_next_field[offset];
        last = ui_item_used_tail & 0xFF;
        ui_item_next_field[last * sizeof(Item7C)] = first;
        ui_item_pool_prev[offset] = last;
        ui_item_next_field[offset] = 0;
        ui_item_used_tail = index;
        base = (u8 *)head - 0x60;
        item = offset + base;
        *(s16 *)(item + 0x54) = -1;
        *(s32 *)(item + 0x00) = 0;
        *(s32 *)(item + 0x04) = 0;
        *(void **)(item + 0x44) = update;
        *(s16 *)(item + 0x78) = 0;
        *(s32 *)(item + 0x48) = 0;
        *(s16 *)(item + 0x56) = 0x1000;
    }
    ui_item_free_count--;
    return index;
}

void ui_item_free(s32 index) {
    s32 idx = index & 0xFF;
    u8 prev;
    u8 next;
    s32 *cursor;

    if (idx != 0) {
        prev = ui_item_pool[idx].prev;
        next = ui_item_pool[idx].next;
        ui_item_pool[prev].next = next;
        ui_item_pool[next].prev = prev;
        cursor = &ui_item_used_tail;
        if (idx == *cursor) {
            *cursor = prev;
        }
        ui_item_pool[idx].prev = 0;
        ui_item_pool[idx].next = ui_item_free_head;
        ui_item_free_head = idx;
        ui_item_free_count += 1;
    }
}

/* Item update: sets unk_48 to 4, then raises unk_5C by 0x200 per frame up to 0x4000 and stops. */
void ui_grow_update(CoItem *item) {
    Item7C *self = (Item7C *)item;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    self->colour = 4;
    item->resume[item->level] = &&grow;
    return;
grow:
    if ((self->unk_5C += 0x200) < 0x4000) {
        return;
    }
    item->resume[item->level] = &&done;
done:
    return;
}

/* Fades item's value down by 0x40 per frame, then stops. */
void ui_fade_update(CoItem *item) {
    Item7C *self = (Item7C *)item;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    item->resume[item->level] = &&fade;
    return;
fade:
    if ((self->arg.value -= 0x40) > 0) {
        return;
    }
    item->resume[item->level] = &&done;
done:
    return;
}

/* Sits one pixel below its parent item each frame; frees itself once the parent's unk_6C is set. */
void ui_follow_update(UiFollower *item) {
    UiFollower *parent;
    u8 idx;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    item->unk_54 = hud_gfx_base + 0x49;
    item->resume[item->level] = &&follow;
follow:
    parent = item->parent;
    item->x = parent->x;
    item->y = parent->y + 1;
    if (parent->parent_done != 0) {
        idx = (Item7C *)item - ui_item_pool;
        ui_item_free(idx);
    }
}

/* Item update for a sliding box (coroutine style: +0 holds the level, +4 + 4 * level the address to
 * resume at). It slides unk_56 (an s16) to -0x80..0x80, moves x between unk_64 and unk_68 at speed unk_60,
 * then fades unk_56 back to 0 and frees itself. */
void ui_box_update(Item7C *item) {
    Item7C *self;
    Item7C *label;
    s32 old_x;
    s32 nx;
    s32 lo;
    u8 idx;
    s32 unused[4];
    void **slot = &((void **)item)[1 + *(s32 *)item];

    self = item;
    if (*slot != NULL) {
        goto *(*slot);
    }
    item->kind = 4;
    item->gfx_index = 0;
    item->width = 0;
    item->arg.value = 0x78FFB0;
    item->unk_5C = 0x2000;
    *(s32 *)item->unk_6C = 0;
    label = &ui_item_pool[ui_item_alloc((void (*)(void))ui_follow_update) & 0xFF];
    label->arg.value = (s32)item;
    ((void **)item)[1 + *(s32 *)item] = &&slide;
slide:
    item->width -= item->slide_speed;
    item->width = MAX(MIN(item->width, 0x80), -0x80);
    old_x = item->x;
    item->x = old_x + item->slide_speed;
    nx = item->x;
    nx = MIN(nx, item->right_x);
    lo = item->left_x;
    if (lo < nx) {
        lo = nx;
    }
    item->x = lo;
    if (old_x == item->x) {
        *(s32 *)item->unk_6C = 1;
        ((void **)self)[1 + *(s32 *)self] = &&fade;
fade:
        item->width += item->slide_speed;
        item->width = MAX(MIN(item->width, 0), -0x80);
        if (item->width == 0) {
            idx = item - ui_item_pool;
            ui_item_free(idx);
        }
    }
}

/* Coroutine UI item: follows its parent item (arg) with a size/colour from unk_5C, spawning a smaller
 * child while unk_5C > 0x80; each frame trails the parent and scales its unk_56, freed when mission_result_exit_flag is set. */
void ui_gauge_segment_update(Item7C *item) {
    Item7C *parent;
    Item7C *child;
    s32 level;
    s32 width;
    s32 colour;
    s32 flags;
    s32 high;
    s32 index;
    s32 scaled;
    s32 unused[2];
    u8 idx;

    if (((CoItem *)item)->resume[((CoItem *)item)->level] != NULL) {
        goto *((CoItem *)item)->resume[((CoItem *)item)->level];
    }
    parent = (Item7C *)item->arg.value;
    level = item->unk_5C >> 5;
    item->x0 = item->x = parent->x0;
    item->y0 = item->y = parent->y0;
    item->gfx_index = hud_gfx_base + 0x42;
    width = level;
    if (level == 0) {
        width = 1;
    }
    flags = 0x4000000;
    high = width << 16;
    colour = high | flags;
    colour |= level << 8;
    colour |= level;
    item->colour = colour;
    if (item->unk_5C >= 0x81) {
        index = ui_item_alloc((void (*)(void))ui_gauge_segment_update) & 0xFF;
        child = &ui_item_pool[index];
        child->arg.value = (s32)item;
        child->unk_5C = item->unk_5C - 0x100;
    }
    ((CoItem *)item)->resume[((CoItem *)item)->level] = &&update;
    return;
update:
    if (mission_result_exit_flag != 0) {
        idx = item - ui_item_pool;
        ui_item_free(idx);
        return;
    }
    parent = (Item7C *)item->arg.value;
    scaled = parent->width * mission_result_zoom;
    item->x0 = item->x;
    item->y0 = item->y;
    item->width = scaled >> 12;
    item->x = parent->x0;
    item->y = parent->y0;
}

/* Item update: places the box at the screen corner and starts ui_gauge_segment_update's item on it, then each
 * frame sets its colour from mission_result_zoom_slow and moves it to the opposite corner. */
void mission_result_gauge_update(CoItem *co) {
    Item7C *item = (Item7C *)co;
    Item7C *label;
    s32 level;
    s32 width;
    s32 colour;
    s32 flags;
    s32 unused[2];

    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    item->x0 = item->x = mission_result_slide_x - 0x2C;
    item->y0 = item->y = mission_result_base_y - 0x2E;
    item->gfx_index = hud_gfx_base + 2;
    label = &ui_item_pool[ui_item_alloc((void (*)(void))ui_gauge_segment_update) & 0xFF];
    label->arg.value = (s32)item;
    label->unk_5C = 0x600;
    co->resume[co->level] = &&update;
    return;
update:
    level = mission_result_zoom_slow;
    level >>= 5;
    width = level;
    if (level == 0) {
        width = 1;
    }
    flags = 0x4000000;
    colour = (width << 16) | flags;
    colour |= level << 8;
    item->colour = colour | level;
    item->x0 = item->x;
    item->y0 = item->y;
    item->x = mission_result_slide_x + 0x14;
    item->y = mission_result_base_y - 0x6C;
}

/* Item update: follows its parent item (arg) with a box sized unk_5C >> 5, spawning a smaller copy of itself
 * on top while unk_5C > 0x80; each frame scales unk_56 from the parent's by mission_result_zoom and frees itself when
 * mission_result_exit_flag is set. */
void ui_bar_segment_update(CoItem *co) {
    Item7C *item = (Item7C *)co;
    Item7C *parent;
    Item7C *child;
    s32 size;
    s32 width;
    s32 flags;
    s32 colour;
    s32 scaled;
    s32 unused[2];
    u8 index;

    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    parent = (Item7C *)item->arg.value;
    {
        register s16 parent_x asm("$3") = parent->x0;
        item->x0 = item->x = parent_x;
    }
    item->y0 = item->y = parent->y0;
    size = item->unk_5C >> 5;
    width = size;
    if (size == 0) {
        width = 1;
    }
    flags = 0x4000000;
    colour = (width << 16) | flags;
    colour |= size << 8;
    item->colour = colour | size;
    if (item->unk_5C >= 0x81) {
        child = &ui_item_pool[ui_item_alloc((void (*)(void))ui_bar_segment_update) & 0xFF];
        child->gfx_index = item->gfx_index;
        child->arg.value = (s32)item;
        child->unk_5C = item->unk_5C - 0x100;
    }
    co->resume[co->level] = &&follow;
    return;
follow:
    if (mission_result_exit_flag != 0) {
        index = item - ui_item_pool;
        ui_item_free(index);
        return;
    }
    parent = (Item7C *)item->arg.value;
    scaled = parent->width * mission_result_zoom;
    item->x0 = item->x;
    item->y0 = item->y;
    item->width = scaled >> 12;
    item->x = parent->x0;
    item->y = parent->y0;
}

/* Item update: places the box at the screen corner and starts ui_bar_segment_update's item on it, then each
 * frame sets its colour from mission_result_zoom_slow and moves it to the opposite corner (mission_result_gauge_update's twin). */
void mission_result_bar_update(CoItem *co) {
    Item7C *item = (Item7C *)co;
    Item7C *label;
    s32 level;
    s32 width;
    s32 flags;
    s32 high;
    s32 colour;
    s16 x;
    s16 y;
    s32 unused[2];

    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    item->x0 = item->x = mission_result_slide_x - 0x40;
    item->y0 = item->y = mission_result_base_y - 0x48;
    item->gfx_index = hud_gfx_base + 1;
    label = &ui_item_pool[ui_item_alloc((void (*)(void))ui_bar_segment_update) & 0xFF];
    label->arg.value = (s32)item;
    label->unk_5C = 0x600;
    label->gfx_index = item->gfx_index + 0x40;
    co->resume[co->level] = &&update;
    return;
update:
    level = mission_result_zoom_slow;
    level >>= 5;
    width = level;
    if (level == 0) {
        width = 1;
    }
    x = item->x;
    y = item->y;
    /* flags and high are each set once, so sched1 keeps their source order (lui before sll) */
    flags = 0x4000000;
    high = width << 16;
    colour = high | flags;
    colour |= level << 8;
    item->colour = colour | level;
    item->x0 = x;
    item->y0 = y;
    item->x = -0x20 - mission_result_slide_x;
    item->y = mission_result_base_y - 0x80;
}

/* mission_result_bar_update with the bar 0x40 higher and no draw-order offset. */
void mission_result_bar_raised_update(CoItem *co) {
    Item7C *item = (Item7C *)co;
    Item7C *label;
    s32 level;
    s32 width;
    s32 flags;
    s32 high;
    s32 colour;
    s16 x;
    s16 y;
    s32 unused[2];

    if (co->resume[co->level] != NULL) {
        goto *co->resume[co->level];
    }
    item->x0 = item->x = mission_result_slide_x - 0x40;
    item->y0 = item->y = mission_result_base_y - 0x40;
    item->gfx_index = hud_gfx_base;
    label = &ui_item_pool[ui_item_alloc((void (*)(void))ui_bar_segment_update) & 0xFF];
    label->arg.value = (s32)item;
    label->unk_5C = 0x600;
    label->gfx_index = item->gfx_index + 0x40;
    co->resume[co->level] = &&update;
    return;
update:
    level = mission_result_zoom_slow;
    level >>= 5;
    width = level;
    if (level == 0) {
        width = 1;
    }
    x = item->x;
    y = item->y;
    /* flags and high are each set once, so sched1 keeps their source order (lui before sll) */
    flags = 0x4000000;
    high = width << 16;
    colour = high | flags;
    colour |= level << 8;
    item->colour = colour | level;
    item->x0 = x;
    item->y0 = y;
    item->x = -0x20 - mission_result_slide_x;
    item->y = mission_result_base_y - 0x80;
}

/* Width in pixels of a string in the small font: '-' 6, 'i' 3, 'm' and 'q' 14, other characters
 * below 0x60 (capitals, digits) 13, the rest 12. */
s32 ui_text_width(u8 *str) {
    s32 width;

    width = 0;
    while (*str != 0) {
        switch (*str) {
            case '-':
                width += 6;
                break;
            case 'i':
                width += 3;
                break;
            case 'm':
            case 'q':
                width += 14;
                break;
            default:
                if (*str < 0x60) {
                    width += 13;
                } else {
                    width += 12;
                }
                break;
        }
        str++;
    }
    return width;
}

/* Width of a number in the small font apart from its first digit (13 per extra digit). */
s32 font_number_extra_width(s32 value) {
    s32 extra = 0;

    do {
        value /= 10;
        if (value != 0) {
            extra++;
        }
    } while (value != 0);
    return extra * 13;
}

void ui_show_text(s32 x, s32 y, u8 *text) {
    Item7C *box;
    Item7C *label;

    box = &ui_item_pool[ui_item_alloc((void (*)(void))ui_box_update) & 0xFF];
    box->x0 = box->x = x - 0x10;
    box->y0 = box->y = y + 0x10;
    box->slide_speed = 10;
    box->left_x = box->x;
    box->right_x = x + ui_text_width(text);
    label = &ui_item_pool[ui_item_alloc((void (*)(void))ui_grow_update) & 0xFF];
    label->x = x;
    label->y = y;
    label->gfx_index = 0;
    label->kind = 2;
    label->unk_5C = 0;
    label->arg.text = text;
    sound_play(SND_UI_BOX_OPEN | SND_VOICE_FLAG, 0x40, 0, 0x3C);
}

/* Shows the number *value at (x, y) in a box sized to its width (like ui_show_text does for text). */
void ui_show_number(s32 x, s32 y, s32 unk, s32 *value) {
    Item7C *box;
    Item7C *label;

    box = &ui_item_pool[ui_item_alloc((void (*)(void))ui_box_update) & 0xFF];
    box->left_x = x - font_number_extra_width(*value) - 0x10;
    box->y0 = box->y = y + 0x10;
    box->x0 = box->x = box->left_x;
    box->right_x = x + 0x10;
    box->slide_speed = 10;
    label = &ui_item_pool[ui_item_alloc((void (*)(void))ui_grow_update) & 0xFF];
    label->x = x;
    label->y = y;
    label->gfx_index = unk;
    label->kind = 3;
    label->unk_5C = 0;
    label->arg.text = (u8 *)value;
    sound_play(SND_UI_BOX_OPEN | SND_VOICE_FLAG, 0x40, 0x80, 0x3C);
}

void ui_show_number_box(s32 x, s32 y, s32 *text) {
    Item7C *item;
    Item7C *text_item;
    s16 top;
    u16 left;

    item = &ui_item_pool[ui_item_alloc((void (*)(void))ui_box_update) & 0xFF];
    item->left_x = x - font_number_extra_width(*text) - 0x20;
    top = y + 0x10;
    item->y = top;
    item->y0 = top;
    left = item->left_x;
    item->right_x = x + 0x10;
    item->slide_speed = 10;
    item->x = left;
    item->x0 = left;
    text_item = &ui_item_pool[ui_item_alloc((void (*)(void))ui_grow_update) & 0xFF];
    text_item->x = x;
    text_item->y = y;
    text_item->gfx_index = 0;
    text_item->kind = 5;
    text_item->unk_5C = 0;
    text_item->arg.text = (u8 *)text;
    sound_play(SND_UI_BOX_OPEN | SND_VOICE_FLAG, 0x40, 0x80, 0x3C);
}

void ui_box_spawn(s32 x, s32 y, s32 z) {
    Item7C *box;
    Item7C *fade;
    s32 offset;

    box = &ui_item_pool[ui_item_alloc((void (*)(void))ui_box_update) & 0xFF];
    box->left_x = x - 8;
    box->y0 = box->y = y + 0x10;
    box->x0 = box->x = box->left_x;
    box->right_x = x + 0x28;
    box->slide_speed = 10;
    fade = &ui_item_pool[ui_item_alloc((void (*)(void))ui_fade_update) & 0xFF];
    fade->x = x - 4;
    fade->y = y + 1;
    fade->kind = 1;
    fade->colour = 0x4000000;
    fade->arg.value = 0x400;
    offset = z + 0x10;
    fade->gfx_index = hud_gfx_base + offset;
    sound_play(SND_UI_BOX_OPEN | SND_VOICE_FLAG, 0x40, 0x80, 0x3C);
}

void ui_box_bar_spawn(s32 x, s32 y, s32 z) {
    Item7C *box;
    Item7C *bar;

    box = &ui_item_pool[ui_item_alloc((void (*)(void))ui_box_update) & 0xFF];
    box->left_x = x - 0x10;
    box->y0 = box->y = y + 0x10;
    box->x0 = box->x = *(u16 *)&box->left_x;
    box->right_x = x + 0x20;
    box->slide_speed = 10;
    bar = &ui_item_pool[ui_item_alloc((void (*)(void))ui_fade_update) & 0xFF];
    bar->x = x;
    bar->y = y + 1;
    bar->kind = 1;
    bar->colour = 0x04000000;
    bar->arg.value = 0x400;
    bar->gfx_index = hud_gfx_base + (s16)(z + 0x18);
    sound_play(SND_UI_BOX_OPEN | SND_VOICE_FLAG, 0x40, 0x80, 0x3C);
}

/* Text colours ui_string_draw steps through, one per character: white fading to green. */
const TextRgb text_fade_colours[15] = {
    { 0x1F, 0x1F, 0x1F }, { 0x1C, 0x1F, 0x17 }, { 0x1A, 0x1F, 0x0F }, { 0x18, 0x1F, 0x07 },
    { 0x13, 0x1B, 0x05 }, { 0x0E, 0x17, 0x04 }, { 0x09, 0x13, 0x02 }, { 0x04, 0x0F, 0x01 },
    { 0x00, 0x0C, 0x00 }, { 0x00, 0x0A, 0x00 }, { 0x00, 0x08, 0x00 }, { 0x00, 0x07, 0x00 },
    { 0x00, 0x05, 0x00 }, { 0x00, 0x04, 0x00 }, { 0x00, 0x01, 0x00 },
};
const s32 d_800B654C[5] = { 10, 100, 1000, 10000, 100000 };

/* Mission results screen: shows each label then its value, one step at a time. */
void mission_results_update(CoItem *item) {
    CoItem *self = item;
    u8 idx;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&wait_time;
    item->count[item->level] = 7;
wait_time:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, -0x20, "Time-Bonus");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_time_val;
    self->count[self->level] = 3;
wait_time_val:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, -0x16, 1, &result_time_bonus);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_shield;
    self->count[self->level] = 7;
wait_shield:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, -0xC, "Shield-Bonus");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_shield_val;
    self->count[self->level] = 3;
wait_shield_val:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, -2, 1, &result_shield_bonus);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_grenade;
    self->count[self->level] = 7;
wait_grenade:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 8, "Grenade-Bonus");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_grenade_val;
    self->count[self->level] = 3;
wait_grenade_val:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, 0x12, 1, &result_grenade_bonus);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_total;
    self->count[self->level] = 0x17;
wait_total:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x28, str_total_label);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_total_val;
    self->count[self->level] = 3;
wait_total_val:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, 0x28, 1, &result_total);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_score;
    self->count[self->level] = 7;
wait_score:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x44, str_score_label);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_score_val;
    self->count[self->level] = 3;
wait_score_val:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, 0x44, 0, &result_score);
    idx = (Item7C *)item - ui_item_pool;
    ui_item_free(idx);
}

/* Mission results screen setup: counts the bonuses, then fades in and holds. */
void mission_results_setup(CoItem *item) {
    CoItem *self = item;
    s32 grenades, shield;
    s32 mins, secs;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    set_stage_flags(get_stage_flags() | 0x10);
    ui_item_alloc((void (*)(void))mission_result_bar_raised_update);
    ui_item_alloc((void (*)(void))mission_result_gauge_update);
    mission_result_slide_x = 0x100;
    mission_result_base_y = 0x30;
    mission_result_zoom = 0x1000;
    mission_result_zoom_slow = 0x1000;
    mission_result_exit_flag = 0;
    view_set_on(4, 1);
    self->resume[self->level] = &&s1;
    return;
s1:
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&s2;
    meter_b_rate = -0x80;
    meter_a_rate = -0x80;
    self->count[self->level] = 3;
s2:
    screen_fade_alpha = CLAMP_HI(screen_fade_alpha + 2, 0x40);
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    self->resume[self->level] = &&s3;
    return;
s3:
    {
        register s32 time asm("$2");

        if (get_stage_end() == 2) {
            s32 left;
            if (get_area() / 3 == 0xC) {
                left = get_mission_timer();
            } else {
                left = get_time_bonus();
            }
            mins = left / 60;
            secs = left % 60;
            left = mins * 100 + secs * 100 / 60;
            time = left * 100;
        } else {
            time = 0;
        }
        result_time_bonus = time;
    }
    shield = get_shield();
    if (get_area() / 3 == 0xC) {
        shield = shield * 1000;
    } else if (shield == 0xC8) {
        shield = 50000;
    } else {
        shield = shield * 100;
    }
    result_shield_bonus = shield;
    grenades = grenades_get();
    if (get_area() / 3 == 0xC) {
        grenades = grenades * 50000;
    } else {
        grenades = grenades * 10000;
    }
    result_grenade_bonus = grenades;
    result_total = result_time_bonus + result_shield_bonus + grenades;
    set_score(get_score() + result_total);
    result_score = get_score();
    self->resume[self->level] = &&s4;
s4:
    screen_fade_alpha = CLAMP_HI(screen_fade_alpha + 2, 0x40);
    if (meter_b_level > 0) {
        return;
    }
    mission_result_slide_x = MAX(mission_result_slide_x - 0x10, 0);
    if (mission_result_slide_x > 0) {
        return;
    }
    self->resume[self->level] = &&s5;
    return;
s5:
    ui_item_alloc((void (*)(void))mission_results_update);
    mission_result_zoom_slow = 0x1FFF;
    mission_result_zoom = 0x1200;
    sound_start(SND_PAIR(SND_PLAYER_HIT_HEAVY | SND_VOICE_FLAG, SND_PLAYER_JUMP | SND_VOICE_FLAG), 0x7F, 0, 0);
    self->resume[self->level] = &&s6;
    return;
s6:
    mission_result_zoom = MAX(mission_result_zoom - 0x20, 0x1000);
    mission_result_zoom_slow = MAX(mission_result_zoom_slow - 0xC0, 0x1000);
    if (mission_result_zoom > 0x1000) {
        return;
    }
    self->resume[self->level] = &&s7;
    return;
s7:
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&s8;
    mission_result_exit_flag = 1;
    self->count[self->level] = 0x58;
s8:
    mission_result_zoom_slow = MAX(mission_result_zoom_slow - 0xC0, 0x1000);
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    self->resume[self->level] = &&s9;
    return;
s9:
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&s10;
    self->count[self->level] = 0x77;
s10:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    set_stage_flags(get_stage_flags() | 2);
    self->resume[self->level] = &&done;
done:
    return;
}

/* Fades the screen in then out: meter_a_rate/C4 start at -0x80, view_scale/dim_level_b count down. */
void stage_end_fade_update(CoItem *item) {
    CoItem *self = item;
    u8 idx;
    s32 unused[2];

    s32 lvl = *(volatile s32 *)&item->level; /* volatile: the original re-reads level below */

    if (item->resume[lvl] != NULL) {
        goto *item->resume[lvl];
    }
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&wait_in;
    meter_b_rate = -0x80;
    meter_a_rate = -0x80;
    item->count[item->level] = 0xF;
wait_in:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    set_stage_flags(get_stage_flags() | 4);
    self->resume[self->level] = &&dim_a;
dim_a:
    view_scale -= 0x40;
    if (view_scale >= 0xAAB) {
        return;
    }
    self->resume[self->level] = &&dim_b;
    return;
dim_b:
    dim_level_b -= 0x40;
    if (dim_level_b > 0) {
        return;
    }
    self->resume[self->level] = &&start_out;
    return;
start_out:
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&wait_out;
    self->count[self->level] = 0x77;
wait_out:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    set_stage_flags(get_stage_flags() | 2);
    idx = (Item7C *)item - ui_item_pool;
    ui_item_free(idx);
}

char str_total_label[8] RODATA = "Total";

char str_score_label[8] RODATA = "Score";

/* Results screen part 2: bonus rows, then rank/hitrate/destroy/class. */
void mission_result_rows_update(CoItem *item) {
    CoItem *self = item;
    u8 idx;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&l0;
    item->count[item->level] = 7;
l0:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, -0x20, "Time");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l1;
    self->count[self->level] = 3;
l1:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, -0x20, 1, &result_time_bonus);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l2;
    self->count[self->level] = 3;
l2:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, -0x14, "Shield");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l3;
    self->count[self->level] = 3;
l3:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, -0x14, 1, &result_shield_bonus);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l4;
    self->count[self->level] = 3;
l4:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, -8, "Grenade");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l5;
    self->count[self->level] = 3;
l5:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, -8, 1, &result_grenade_bonus);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l6;
    self->count[self->level] = 11;
l6:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0xA, str_total_label);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l7;
    self->count[self->level] = 3;
l7:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, 0xA, 1, &result_total);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l8;
    self->count[self->level] = 7;
l8:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x1A, str_score_label);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l9;
    self->count[self->level] = 3;
l9:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, 0x1A, 0, &result_score);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l10;
    self->count[self->level] = 3;
l10:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x26, "Rank");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l11;
    self->count[self->level] = 3;
l11:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_box_spawn(0x44, 0x26, result_rank_place);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l12;
    self->count[self->level] = 7;
l12:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x3A, "Hitrate");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l13;
    self->count[self->level] = 3;
l13:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number_box(0x58, 0x3A, &result_hitrate);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l14;
    self->count[self->level] = 7;
l14:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x46, "Destroy");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l15;
    self->count[self->level] = 3;
l15:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_number(0x58, 0x46, 1, &result_kill_count);
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l16;
    self->count[self->level] = 7;
l16:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_show_text(-0x60, 0x56, "Class");
    self->level = (self->level + 1) & 7;
    self->resume[self->level] = &&l17;
    self->count[self->level] = 3;
l17:
    if (--self->count[self->level] >= 0) {
        return;
    }
    self->level = (self->level - 1) & 7;
    ui_box_bar_spawn(0x44, 0x56, result_class);
    idx = (Item7C *)item - ui_item_pool;
    ui_item_free(idx);
}

/* Mission results intro/outro: computes the bonuses, then fades the screen in and out. */
void mission_result_update(item)
    CoItem *item;
{
    s32 done_pct, base, mins, secs, time_bonus, t, v, pct, rank_bonus;
    s32 unused[2];

    if (item->resume[item->level] != NULL) {
        goto *item->resume[item->level];
    }
    set_stage_flags(get_stage_flags() | 0x10);
    ui_item_alloc((void (*)(void))mission_result_bar_update);
    ui_item_alloc((void (*)(void))mission_result_gauge_update);
    mission_result_slide_x = 0x100;
    mission_result_base_y = 0x30;
    mission_result_zoom = 0x1000;
    mission_result_zoom_slow = 0x1000;
    mission_result_exit_flag = 0;
    view_set_on(4, 1);
    item->resume[item->level] = &&push_wait;
    return;
push_wait:
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&wait_a;
    meter_b_rate = -0x80;
    meter_a_rate = -0x80;
    item->count[item->level] = 3;
wait_a:
    screen_fade_alpha = CLAMP_HI(screen_fade_alpha + 2, 0x40);
    if (--item->count[item->level] >= 0) {
        return;
    }
    item->level = (item->level - 1) & 7;
    item->resume[item->level] = &&calc;
    return;
calc:
    if (get_stage_end() == 2) {
        t = get_area() / 3 == 0xC ? get_mission_timer() : get_time_bonus();
        mins = t / 60;
        secs = t - mins * 60;
        t = mins * 100 + secs * 100 / 60;
        time_bonus = t * 100;
    } else {
        time_bonus = 0;
    }
    result_time_bonus = time_bonus;
    v = get_shield();
    if (get_area() / 3 == 0xC) {
        v *= 1000;
    } else if (v == 0xC8) {
        v = 50000;
    } else {
        v *= 100;
    }
    result_shield_bonus = v;
    v = grenades_get();
    if (get_area() / 3 == 0xC) {
        v *= 50000;
    } else {
        v *= 10000;
    }
    result_grenade_bonus = v;
    if (get_stage_end() == 2) {
        pct = 0;
        v = get_mission_total();
        if (v != 0) {
            pct = get_mission_count() * 100 / v;
        }
        rank_bonus = pct;
        if (rank_bonus == 100) {
            base = 250000;
        } else if (rank_bonus >= 95) {
            base = 200000;
        } else if (rank_bonus >= 90) {
            base = 150000;
        } else if (rank_bonus >= 85) {
            base = 120000;
        } else if (rank_bonus >= 80) {
            base = 100000;
        } else if (rank_bonus >= 70) {
            base = 80000;
        } else {
            base = rank_bonus / 10 * 10000;
        }
        rank_bonus = base + rank_bonus % 10 * 1000;
    } else {
        rank_bonus = 0;
    }
    result_total = result_time_bonus + result_shield_bonus + result_grenade_bonus + rank_bonus;
    set_score(get_score() + result_total);
    result_score = get_score();
    done_pct = 0;
    v = get_mission_total();
    if (v != 0) {
        done_pct = get_mission_count() * 100 / v;
    }
    result_hitrate = done_pct;
    result_kill_count = get_kill_count();
    result_rank_place = ranking_place();
    result_class = mission_rank();
    item->resume[item->level] = &&fade_in;
fade_in:
    screen_fade_alpha = CLAMP_HI(screen_fade_alpha + 2, 0x40);
    if (meter_b_level > 0) {
        return;
    }
    mission_result_slide_x = MAX(mission_result_slide_x - 0x10, 0);
    if (mission_result_slide_x > 0) {
        return;
    }
    item->resume[item->level] = &&start_zoom;
    return;
start_zoom:
    ui_item_alloc((void (*)(void))mission_result_rows_update);
    mission_result_zoom_slow = 0x1FFF;
    mission_result_zoom = 0x1200;
    sound_start(SND_PAIR(SND_PLAYER_HIT_HEAVY | SND_VOICE_FLAG, SND_PLAYER_JUMP | SND_VOICE_FLAG), 0x7F, 0, 0);
    item->resume[item->level] = &&zoom;
    return;
zoom:
    mission_result_zoom = MAX(mission_result_zoom - 0x20, 0x1000);
    mission_result_zoom_slow = MAX(mission_result_zoom_slow - 0xC0, 0x1000);
    if (mission_result_zoom > 0x1000) {
        return;
    }
    item->resume[item->level] = &&push_hold;
    return;
push_hold:
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&hold;
    mission_result_exit_flag = 1;
    item->count[item->level] = 0x58;
hold:
    mission_result_zoom_slow = MAX(mission_result_zoom_slow - 0xC0, 0x1000);
    if (--item->count[item->level] >= 0) {
        return;
    }
    item->level = (item->level - 1) & 7;
    item->resume[item->level] = &&push_end;
    return;
push_end:
    item->level = (item->level + 1) & 7;
    item->resume[item->level] = &&end_wait;
    item->count[item->level] = 0x77;
end_wait:
    if (--item->count[item->level] >= 0) {
        return;
    }
    item->level = (item->level - 1) & 7;
    set_stage_flags(get_stage_flags() | 2);
    item->resume[item->level] = &&done;
done:
    return;
}
