/* hud: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void alert_check_actors(void) {
    Node *head;
    Object *obj;
    s32 player_x;
    s32 player_y;
    s32 player_z;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 found;

    player_x = player_position()[0];
    player_y = player_position()[1];
    player_z = player_position()[2];
    head = (Node *) get_obj_list_actors();
    obj = (Object *) head->next;
    found = 0;
    while (obj->node.next != NULL) {
        if (((u8 *) obj)[0x17A] != 0) {
            dx = (obj->x >> 12) - player_x;
            if (ABS(dx) < 0x801) {
                dy = (obj->y >> 12) - player_y;
                if (ABS(dy) < 0x801) {
                    dz = (obj->z >> 12) - player_z;
                    if (ABS(dz) < 0x801) {
                        found++;
                        break;
                    }
                }
            }
        }
        obj = (Object *) obj->node.next;
    }
    if (found > 0) {
        alert_add(1);
    }
}

void status_update(void) {
    s32 stage_flag4;
    s32 level; /* meter delta, then the shield reading (one register in the original) */
    s32 count;
    s32 shift;
    s32 count_lt3;
    s32 area;
    s32 round_due;

    stage_flag4 = get_stage_flags() & 4;
    if (stage_flag4 == 0) {
        if (meter_is_full()) {
            level = (get_shield() << 12) - shield_gauge;
            if (level > 0) {
                if (level >= 0x3556) {
                    level = 0x3555;
                }
            } else if (level < 0 && level < -0x3555) {
                level = -0x3555;
            }
            shield_gauge += level;
        }
        alert_check_actors();
        level = get_shield();
        if (level < 0x32) {
            alert_add(1);
            if (shield_prev >= 0x32 && level > 0) {
                show_line((s32) "#1Shield energy is low!\xA1");
            }
        }
        if (level < 0x64) {
            alert_add(1);
        }
        count = alert_count;
        alert_count = 0;
        alert_level = count;
        shift = count;
        count_lt3 = shift < 3;
        if (!count_lt3) {
            shift = 2;
        }
        /* empty barrier: stops GCC 2.7.2 merging the two count_lt3 branches */
        __asm__ __volatile__("");
        if (!count_lt3) {
            count = 2;
        }
        if (count < 0) {
            shift = 0;
        }
        alert_level = shift;
        pulse_phase -= 0x44 << shift;
        shade_angle += 0x88;
    }
    shield_prev = get_shield();
    area = get_area();
    if (area == (area / 3) * 3) {
        round_due = 0;
    } else {
        round_due = part_timer_get() != 1;
    }
    if (round_due) {
        stage_round_run();
        stage_view_split_setup();
        meters_update();
    }
    hud_update();
    pursuit_view_update();
    if (stage_flag4 == 0) {
        meter_update();
        angle_advance();
        lock_slots_update();
    }
}

/* Pushes count digit records of the score (lowest digit first) into id_table
 * bucket 1, at (x, y), stepping x back by step per digit. */
void hud_score_draw(s32 x, s32 y, s32 count, s32 step)
{
    s32 score;
    IdTable *tbl;
    s32 index;
    IdRecord *rec;
    s32 digit;
    s32 rem;
    s32 scale;
    s32 tag;

    score = get_score();
    if (count <= 0)
        return;
    tag = 0x01000000;
    scale = 0x1000;
    do {
        /* rem = score % 10; the quotient stays in LO for the mflo below */
        div10_rem_mem(rem, score, 9);
        digit = rem + track_base;
        digit += 0x40;
        __asm__ volatile("");
        __asm__ volatile("" : "=r"(tbl) : "0"(&id_table));
        index = tbl->count;
        if (index < 0x100) {
            tbl->count = index + 1;
            rec = (IdRecord *)((u8 *)tbl + (index * 0x14 + 0x24));
            rec->prev_id = tbl->id[1];
            tbl->id[1] = index;
            rec->field_00 = x;
            rec->field_02 = y;
            rec->field_04 = scale;
            rec->field_0E = digit;
            rec->field_08 = 0;
            rec->field_0A = 0;
            rec->field_0C = 0;
            rec->field_10 = tag;
        }
        /* score /= 10 */
        mips_mflo(score);
        count--;
        x -= step;
    } while (count > 0);
}

static inline void id_table_add_colour(s32 x, s32 y, s32 scale, s32 depth, s32 colour)
{
    IdTableRecords *tbl;
    s32 index;
    IdRecord *rec;
    s32 list;

    __asm__ volatile("");
    __asm__ volatile("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;
    list = colour >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = *(s16 *)((u8 *)tbl->id + list * 2);
        *(s16 *)((u8 *)tbl->id + list * 2) = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = depth;
        rec->field_08 = 0;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = colour;
    }
}
static inline s32 pack_colour(s32 r, s32 g, s32 b)
{
    s32 high = 0x01000000;

    return (b << 16) | high | (g << 8) | r;
}
static inline s32 rgb_colour(s32 r, s32 g, s32 b)
{
    if ((r | g | b) == 0) {
        b = 1;
    }
    return pack_colour(r, g, b);
}
void shield_meter_draw(s32 x, s32 y)
{
    s32 depth;
    s32 colour;
    s32 level;
    ColorShift *pal;
    s32 b, g, r;
    s32 i;

    level = shield_gauge >> 12;
    depth = level * 54 / 200;
    if (depth == 0 && level > 0) {
        depth = 1;
    }
    depth = 0xEE - depth;
    colour = get_shield() * 32 / 200 - 1;
    if (colour < 0) {
        colour = 0;
    }
    pal = &palette_expanded[31 - colour];
    level = get_shield();
    if (level < 50) {
        s32 lit_r, lit_g, lit_b;

        /* low shield: dim the colour with the 0x1000-period pulse */
        colour = (3 * (pulse_phase & 0xFFF) + 0x1000) / 4;
        lit_r = (s16)pal->r * colour / 4096;
        lit_g = (s16)pal->g * colour / 4096;
        lit_b = (s16)pal->b * colour / 4096;
        colour = rgb_colour(lit_r >> 5, lit_g >> 5, lit_b >> 5);
    } else {
        b = (s16)pal->b >> 5;
        g = (s16)pal->g >> 5;
        r = (s16)pal->r >> 5;
        colour = rgb_colour(r, g, b);
    }
    for (i = 0; i < 2; i++) {
        id_table_add_colour(x, y, 0x1000, track_base + depth, colour);
    }

    if (level < 50) {
        s32 flash_g, flash_b;

        colour = pulse_phase & 0xFFF; /* the pulse */
        flash_g = (3 * colour + 0x1000) / 4;
        flash_b = colour >> 5;
        flash_g >>= 5;
        colour = rgb_colour(0x80, flash_g, flash_b);
    } else {
        colour = 0x01000000;
    }
    id_table_add_colour(x, y, 0x1000, track_base + 0x30, colour);
}

/* Adds two records to id_table at (x, y), coloured by pulse_phase's brightness. */
void id_table_add_pair(s32 x, s32 y) {
    s32 bright;
    s32 width;
    s32 colour;
    s32 flag;
    s32 i;
    s32 index;
    s32 head; /* byte offset of the id[] list head */
    s32 scale;
    s32 depth;
    IdTableRecords *tbl;
    IdRecord *rec;

    bright = ((3 * (pulse_phase & 0xFFF) + 0x1000) / 4) >> 5;
    width = bright;
    if (width == 0) {
        width = 1;
    }
    i = 0;
    scale = 0x1000;
    flag = 0x01000000;
    colour = (width << 16) | flag | (bright << 8) | bright;
    depth = alert_level + 0x32;
    head = (colour >> 24) * sizeof(s16);
loop:
    /* hides the address from cse, which would put the constant operand second */
    __asm__("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = *(s16 *)((u8 *)tbl->id + head);
        *(s16 *)((u8 *)tbl->id + head) = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = depth;
        rec->field_08 = 0;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = colour;
    }
    i++;
    if (i < 2) goto loop;
}

static inline void id_record_push(u32 tag, s32 x, s32 y, s32 scale, s32 kind, s32 f08)
{
    IdTable *tbl;
    s32 index;
    IdRecord *rec;
    u16 *head;

    do {
    } while (0);
    /* keeps the table address in the loop */
    __asm__ volatile("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = (IdRecord *)((u8 *)tbl + (index * 0x14 + 0x24));
        /* list head chosen by the tag's top byte */
        head = (u16 *)((tag >> 23) + (u32)tbl + 4);
        rec->prev_id = *head;
        *head = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = kind;
        rec->field_08 = f08;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = tag;
    }
}

/* Pushes the grenade-count record (kind = track base + grenades + 0x4B). */
void hud_grenades_draw(s32 x, s32 y)
{
    id_record_push(0x01000000, x, y, 0x1000, track_base + grenades_get() + 0x4B, 0);
}

/* Draws the 6 lock-on slots (two records each; lit while i < lock_count())
 * and the charge gauge record below them. */
void hud_lock_gauge_draw(s32 x, s32 y)
{
    s32 locks;
    s32 i, j;
    u32 tag;
    u32 lit_hi;
    u32 unlit_hi;
    s32 level;

    locks = lock_count();
    i = 0;
    lit_hi = 0x01000000;
    unlit_hi = 0x011C0000;
    for (; i < 6; i++) {
        tag = lit_hi | 0x487C;
        if (i >= locks) tag = unlit_hi | 0x1C1C;
        for (j = 0; j < 2; j++) {
            id_record_push(tag, x, y, 0x1000, i + track_base + 0x2A, 0);
        }
    }
    level = (0x1000 - charge_level()) / 4;
    id_record_push(0x01000000, x - 0x25, y + 4, 0x1000, track_base + 0x29, level);
}

void fn_800FE278(void) {

}

void req_state_reset(void) {
    req_queue_count = 0;
    d_801202D4 = 0;
    draw_enabled = 1;
    area_warnings_flag = 0;
}

void angle_advance(void) {
    d_801202D4 = (d_801202D4 + 0xAA) & 0xFFF;
}

static inline void lamp_add(s32 tag, s32 x, s32 y, s32 scale, s32 depth)
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
/* Projects every queued request's offset from the camera through the view rotation and adds
 * a coloured id_table record at (x, y) plus the scaled offset. Kinds 0 and 4 are
 * clamped to the edge when far away and fade with d_801202D4; the others are culled. */
void req_queue_lamps_draw(s32 x, s32 y)
{
    s32 *mat;
    Request *req;
    s32 i;
    s32 cx, cy, cz;
    s32 w0, w1, w2;
    s32 dx, dy, dz;
    s32 kind;
    s32 r, g, b;
    s32 red, green;
    s32 base, tile;
    s32 fade;
    s32 prod;
    s32 colour;
    s32 flags, high;
    VECTOR *dir;
    LampColour *lamp;

    mat = view_matrix_t_get();
    w0 = mat[0];
    w1 = mat[1];
    w2 = mat[2];
    __asm__ volatile("" ::: "memory");
    gte_set_ctrl(R11R12, w0);
    gte_set_ctrl(R13R21, w1);
    gte_set_ctrl(R22R23, w2);
    w0 = mat[3];
    w1 = mat[4];
    __asm__ volatile("" ::: "memory");
    gte_set_ctrl(R31R32, w0);
    gte_set_ctrl(R33, w1);
    cx = cam_pos;
    cy = cam_pos_y;
    cz = cam_pos_z;
    cx >>= 12;
    cy >>= 12;
    cz >>= 12;
    req = req_queue;
    for (i = req_queue_count; i > 0; i--, req++) {
        dx = req->a - cx;
        dy = req->b - cy;
        dz = req->c - cz;
        kind = req->kind;
        if (ABS(dx) >= 0x4000 || ABS(dy) >= 0x4000 || ABS(dz) >= 0x4000) {
            if (kind != 0 && kind != 4) {
                continue;
            }
            dir = scratch_alloc(0x10);
            dir->vx = dx;
            dir->vy = dy;
            dir->vz = dz;
            vector_normal_scaled(dir, (SVECTOR *)dir);
            scratch_top -= 0x10;
            dx = dir->vx;
            dy = dir->vy;
            dz = dir->vz;
        }
        gte_set(IR1, dx);
        gte_set(IR2, dy);
        gte_set(IR3, dz);
        gte_rtir();
        gte_get(MAC1, dx);
        gte_get(MAC2, dy);
        gte_get(MAC3, dz);
        if ((u32)(dy + 0x1000) > 0x2000 && kind != 0 && kind != 4) {
            continue;
        }
        gte_sqr0_b();
        gte_get(MAC1, r);
        gte_get(MAC3, g);
        r += g;
        if (kind != 0 && kind != 4) {
            if (r > 0x900000) {
                continue;
            }
        } else if (r > 0x640000) {
            r = isqrt(r);
            dx = dx * 0xA00 / r;
            dz = dz * 0xA00 / r;
        }
        dx = dx * 21 / 3072;
        dz = dz * 21 / 3072;
        lamp = &lamp_table[kind];
        r = lamp->r;
        g = lamp->g;
        b = lamp->b;
        base = track_base;
        tile = base + 0x38;
        if (kind == 0) {
            register s32 rounded asm("$2");

            fade = d_801202D4;
            prod = fade * 3;
            rounded = prod;
            if (prod < 0) {
                rounded = prod + 0xFFF;
            }
            red = rounded >> 12;
            if (red < 3) {
                tile += red;
            } else {
                tile = base + 0x3A;
            }
            g = g * (0x1000 - fade / 2) / 0x1000;
        } else if (kind == 4) {
            register s32 rounded asm("$2");

            fade = d_801202D4;
            prod = fade * 3;
            rounded = prod;
            if (prod < 0) {
                rounded = prod + 0xFFF;
            }
            red = rounded >> 12;
            if (red < 3) {
                tile += red;
            } else {
                tile = base + 0x3A;
            }
            base = 0x1000 - fade / 2;
            r = r * base / 0x1000;
            g = g * (0x1000 - fade / 3) / 0x1000;
            b = b * base / 0x1000;
        } else if (kind == 3) {
            tile = base + 0x3B;
        }
        /* fade's register is reused for the blue component */
        fade = b >> 5;
        red = r >> 5;
        green = g >> 5;
        if ((red | green | fade) == 0) {
            fade = 1;
        }
        flags = 0x1000000;
        high = fade << 16;
        colour = high | flags | (green << 8) | red;
        lamp_add(colour, x + dx - 1, y - dz, 0x1000, tile);
    }
}

static inline s32 flag_test(s32 flags, s32 mask) {
    return flags & mask;
}
static inline s32 marker_color(s32 r, s32 g, s32 b, s32 mode) {
    return (mode << 24) | (b << 16) | (g << 8) | r;
}
static inline void id_marker_add(s32 px, s32 py, s32 scale, s32 sprite, s32 color) {
    IdTableRecords *tbl = (IdTableRecords *)&id_table;
    s32 index;
    s32 slot;
    IdRecord *rec;

    __asm__ volatile("");
    FAKE_OPAQUE(tbl);
    index = tbl->count;
    slot = color >> 24;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = tbl->id[slot];
        tbl->id[slot] = index;
        rec->field_00 = px;
        rec->field_02 = py;
        rec->field_04 = scale;
        rec->field_0E = sprite;
        rec->field_08 = 0;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = color;
    }
}
/* Draws a map marker of colour kind for each object of list, relative to the camera, at (x, y). */
void map_markers_draw(s32 x, s32 y, s32 kind, s32 *list)
{
    Object *obj;
    s32 dx, dy, dz;
    s32 cam_x, cam_y, cam_z;
    s32 r, g, b;
    s32 cr, cg, cb;
    s32 sprite;
    s32 color;
    s32 ang, base;
    s32 *tmp;
    LampColour *lamp;
    s32 *view;

    view = view_matrix_t_get();
    rot_load(view);
    cam_x = cam_pos;
    obj = *(Object **)list;
    cam_y = cam_pos_y;
    cam_z = cam_pos_z;
    for (; obj->node.next != 0; obj = (Object *)obj->node.next) {
        dx = (obj->x - cam_x) >> 12;
        dy = (obj->y - cam_y) >> 12;
        dz = (obj->z - cam_z) >> 12;
        if (ABS(dx) >= 0x4000 || ABS(dy) >= 0x4000 || ABS(dz) >= 0x4000) {
            if (kind != 0 && kind != 4) {
                continue;
            }
            tmp = scratch_alloc(0x10);
            tmp[0] = dx;
            tmp[1] = dy;
            tmp[2] = dz;
            vector_normal_scaled((VECTOR *)tmp, (SVECTOR *)tmp);
            scratch_top -= 0x10;
            dx = tmp[0];
            dy = tmp[1];
            dz = tmp[2];
        }
        gte_set(IR1, dx);
        gte_set(IR2, dy);
        gte_set(IR3, dz);
        gte_rtir();
        gte_get(MAC1, dx);
        gte_get(MAC2, dy);
        gte_get(MAC3, dz);
        if ((u32)(dy + 0x1000) > 0x2000 && kind != 0 && kind != 4) {
            continue;
        }
        gte_sqr0_b();
        gte_get(MAC1, r);
        gte_get(MAC3, g);
        r += g;
        if (kind != 0 && kind != 4) {
            if (r > 0x900000) {
                continue;
            }
        } else if (r > 0x640000) {
            r = isqrt(r);
            dx = dx * 0xA00 / r;
            dz = dz * 0xA00 / r;
        }
        dx = dx * 21 / 0xC00;
        dz = dz * 21 / 0xC00;
        lamp = &lamp_table[kind];
        r = lamp->r;
        g = lamp->g;
        b = lamp->b;
        base = track_base;
        sprite = base + 0x38;
        if (kind == 0) {
            ang = d_801202D4;
            if (ang * 3 / 0x1000 < 3) {
                sprite += ang * 3 / 0x1000;
            } else {
                sprite = base + 0x3A;
            }
            g = g * (0x1000 - ang / 2) / 0x1000;
        } else if (kind == 4) {
            ang = d_801202D4;
            if (ang * 3 / 0x1000 < 3) {
                sprite += ang * 3 / 0x1000;
            } else {
                sprite = base + 0x3A;
            }
            base = 0x1000 - ang / 2;
            r = r * base / 0x1000;
            g = g * (0x1000 - ang / 3) / 0x1000;
            b = b * base / 0x1000;
        } else if (kind == 3) {
            sprite = base + 0x3B;
        }
        cr = r >> 5;
        cg = g >> 5;
        cb = b >> 5;
        if ((cr | cg | cb) == 0) {
            cb = 1;
        }
        color = marker_color(cr, cg, cb, 1);
        id_marker_add(x + dx - 1, y - dz, 0x1000, sprite, color);
    }
}


void actor_markers_draw(s32 x, s32 y, Object **list) {
    Object *obj;
    s32 kind;
    s32 dx, dy, dz;
    s32 cam_y, cam_x, cam_z;
    s32 r, g, b;
    s32 cr, cg, cb;
    s32 sprite;
    s32 color;
    s32 ang, base;
    s32 *tmp;
    LampColour *lamp;
    s32 *view;

    view = view_matrix_t_get();
    gte_load_R_a0a1v1(view);
    cam_x = cam_pos;
    obj = *list;
    cam_y = cam_pos_y;
    cam_z = cam_pos_z;
    for (; obj->node.next != 0; obj = (Object *)obj->node.next) {
        if ((u8)obj->unk_17A == 0) {
            if (!flag_test(obj->flags, 0x80)) {
                continue;
            }
            kind = 3;
        } else {
            kind = flag_test(obj->flags, 0x200) == 0 ? 2 : 0;
        }
        dx = (obj->x - cam_x) >> 12;
        dy = (obj->y - cam_y) >> 12;
        dz = (obj->z - cam_z) >> 12;
        if (ABS(dx) >= 0x4000 || ABS(dy) >= 0x4000 || ABS(dz) >= 0x4000) {
            if (kind != 0 && kind != 4) {
                continue;
            }
            tmp = scratch_alloc(0x10);
            tmp[0] = dx;
            tmp[1] = dy;
            tmp[2] = dz;
            vector_normal_scaled((VECTOR *)tmp, (SVECTOR *)tmp);
            scratch_top -= 0x10;
            dx = tmp[0];
            dy = tmp[1];
            dz = tmp[2];
        }
        gte_set(IR1, dx);
        gte_set(IR2, dy);
        gte_set(IR3, dz);
        gte_rtir();
        gte_get(MAC1, dx);
        gte_get(MAC2, dy);
        gte_get(MAC3, dz);
        if ((u32)(dy + 0x1000) > 0x2000 && kind != 0 && kind != 4) {
            continue;
        }
        gte_sqr0_b();
        gte_get(MAC1, r);
        gte_get(MAC3, g);
        r += g;
        if (kind != 0 && kind != 4) {
            if (r > 0x900000) {
                continue;
            }
        } else if (r > 0x640000) {
            r = isqrt(r);
            dx = dx * 0xA00 / r;
            dz = dz * 0xA00 / r;
        }
        dx = dx * 21 / 0xC00;
        dz = dz * 21 / 0xC00;
        base = track_base;
        sprite = base + 0x38;
        lamp = &lamp_table[kind];
        r = lamp->r;
        g = lamp->g;
        b = lamp->b;
        if (kind == 0) {
            ang = d_801202D4;
            if (ang * 3 / 0x1000 < 3) {
                sprite += ang * 3 / 0x1000;
            } else {
                sprite = base + 0x3A;
            }
            g = g * (0x1000 - ang / 2) / 0x1000;
        } else if (kind == 4) {
            ang = d_801202D4;
            if (ang * 3 / 0x1000 < 3) {
                sprite += ang * 3 / 0x1000;
            } else {
                sprite = base + 0x3A;
            }
            base = 0x1000 - ang / 2;
            r = r * base / 0x1000;
            g = g * (0x1000 - ang / 3) / 0x1000;
            b = b * base / 0x1000;
        } else if (kind == 3) {
            sprite = base + 0x3B;
        }
        cr = r >> 5;
        cg = g >> 5;
        cb = b >> 5;
        if ((cr | cg | cb) == 0) {
            cb = 1;
        }
        color = marker_color(cr, cg, cb, 1);
        id_marker_add(x + dx - 1, y - dz, 0x1000, sprite, color);
    }
}

void req_queue_flush(s32 x, s32 y) {
    if (draw_enabled != 0) {
        actor_markers_draw(x, y, (Object **)get_obj_list_actors());
        map_markers_draw(x, y, 1, get_obj_list_c());
        req_queue_lamps_draw(x, y);
    }
    req_queue_count = 0;
}

/* Appends a request; dropped if the queue is full or the kind is out of range. */
void req_queue_push(s32 a, s32 b, s32 c, u32 kind) {
    s32 count = req_queue_count;

    if (count < 64 && kind < 5) {
        Request *entry;

        req_queue_count = count + 1;
        entry = &req_queue[count];
        entry->a = a;
        entry->b = b;
        entry->c = c;
        entry->kind = kind;
    }
}

/* Draws a 64x64 sprite as four mirrored 32x32 quadrants around (x, y), then a tpage primitive; returns the
 * next free primitive. */
void *prim_draw_mirrored_sprite(u32 *ot, PolyFT4 *prim, s16 x, s16 y)
{
    PolyFT4 *p;
    DrTexWindow *dr;
    s16 right;
    s16 bottom;

    p = prim++;
    right = x + 32;
    bottom = y + 32;
    p->len = 9;
    p->code = 0x2D;
    p->tpage = 0x10;
    p->clut = 0x4807;
    p->u2 = 0;
    p->u0 = 0;
    p->u3 = 0x1F;
    p->u1 = 0x1F;
    p->v1 = 0;
    p->v0 = 0;
    p->v3 = 0x1F;
    p->v2 = 0x1F;
    p->x2 = x;
    p->x0 = x;
    p->x3 = right;
    p->x1 = right;
    p->y1 = y;
    p->y0 = y;
    p->y3 = bottom;
    p->y2 = bottom;
    addPrim(ot, p);
    p = prim++;
    p->len = 9;
    p->code = 0x2D;
    p->tpage = 0x10;
    p->clut = 0x4807;
    p->u2 = 0;
    p->u0 = 0;
    p->u3 = 0x1F;
    p->u1 = 0x1F;
    p->v1 = 0;
    p->v0 = 0;
    p->v3 = 0x1F;
    p->v2 = 0x1F;
    p->x2 = x;
    p->x0 = x;
    p->x3 = x - 32;
    p->x1 = x - 32;
    p->y1 = y;
    p->y0 = y;
    p->y3 = bottom;
    p->y2 = bottom;
    addPrim(ot, p);
    p = prim++;
    p->len = 9;
    p->code = 0x2D;
    p->tpage = 0x10;
    p->clut = 0x4807;
    p->u2 = 0;
    p->u0 = 0;
    p->u3 = 0x1F;
    p->u1 = 0x1F;
    p->v1 = 0;
    p->v0 = 0;
    p->v3 = 0x1F;
    p->v2 = 0x1F;
    p->x2 = x;
    p->x0 = x;
    p->x3 = right;
    p->x1 = right;
    p->y1 = y;
    p->y0 = y;
    p->y3 = y - 32;
    p->y2 = y - 32;
    addPrim(ot, p);
    p = prim++;
    p->len = 9;
    p->code = 0x2D;
    p->tpage = 0x10;
    p->clut = 0x4807;
    p->u2 = 0;
    p->u0 = 0;
    p->u3 = 0x1F;
    p->u1 = 0x1F;
    p->v1 = 0;
    p->v0 = 0;
    p->v3 = 0x1F;
    p->v2 = 0x1F;
    p->x2 = x;
    p->x0 = x;
    p->x3 = x - 32;
    p->x1 = x - 32;
    p->y1 = y;
    p->y0 = y;
    p->y3 = y - 32;
    p->y2 = y - 32;
    addPrim(ot, p);
    dr = (DrTexWindow *)prim;
    prim = (PolyFT4 *)(dr + 1);
    dr->len = 2;
    dr->code[0] = 0xE202639C;
    dr->code[1] = 0;
    addPrim(ot, dr);
    return prim;
}

/* Adds a fading 64x64 textured quad centred on (x, y) and a texture-window reset to OT entry ot, its shade a
 * sine pulse scaled by a field of view_matrix_t_get's record. Returns the next free packet. */
void *prim_fade_quad(u32 *ot, u8 *prim, s32 x, s32 y) {
    s32 shade;
    s32 product;
    DrTwin *twin;
    s16 left, right, top, bottom;
    PolyFT4 *quad;

    /* the table is const in the original: the read doesn't wait for the prologue's stack stores */
    shade = ((s16)((const s32 *)rcossin_tbl)[shade_angle & 0xFFF] + 0x1000) / 64;
    if (((s16 *)view_matrix_t_get())[4] >= 0) {
        product = shade * ((s16 *)view_matrix_t_get())[4];
    } else {
        product = shade * -((s16 *)view_matrix_t_get())[4];
    }
    shade = product / 0x1000;

    quad = (PolyFT4 *)prim;
    prim += sizeof(PolyFT4);
    left = x - 0x20;
    right = x + 0x20;
    top = y - 0x20;
    bottom = y + 0x20;
    quad->len = 9;
    quad->code = 0x2E;
    quad->tpage = 0x12C;
    quad->r0 = shade;
    quad->g0 = shade;
    quad->b0 = shade;
    quad->u2 = 0;
    quad->u0 = 0;
    quad->u3 = 0x40;
    quad->u1 = 0x40;
    quad->v1 = 0;
    quad->v0 = 0;
    quad->v3 = 0x40;
    quad->v2 = 0x40;
    quad->x2 = left;
    quad->x0 = left;
    quad->x3 = right;
    quad->x1 = right;
    quad->y1 = top;
    quad->y0 = top;
    quad->y3 = bottom;
    quad->y2 = bottom;
    addPrim(ot, quad);
    twin = (DrTwin *)prim;
    prim += sizeof(DrTwin);
    twin->len = 2;
    twin->code[0] = 0xE2000000;
    twin->code[1] = 0;
    addPrim(ot, twin);
    return prim;
}

/* Clip a closed polygon of n points against c = +-0x20; output has (o, c) swapped. */
s32 prim_clip_band(s32 n, ClipIn *in, s16 *out) {
    s32 lo = -0x20;
    s32 hi = 0x20;
    s32 count;
    s32 t0, t1, t2, t3;
    s32 d0, d1, d2, d3;

    in[n] = in[0];
    count = 0;
    for (; n > 0; n--, in++) {
        if (in[0].c < lo) {
            if (in[1].c < lo) {
                continue;
            }
            out[1] = lo;
            d0 = in[1].c - in[0].c;
            t0 = ((lo - in[0].c) << 14) / d0;
            out[0] = in[0].o + (in[1].o - in[0].o) * t0 / 0x4000;
            out += 2;
            count++;
        } else if (in[0].c > hi) {
            if (in[1].c > hi) {
                continue;
            }
            out[1] = hi;
            d1 = in[1].c - in[0].c;
            t1 = ((hi - in[0].c) << 14) / d1;
            out[0] = in[0].o + (in[1].o - in[0].o) * t1 / 0x4000;
            out += 2;
            count++;
        } else {
            out[0] = in[0].o;
            out[1] = in[0].c;
            out += 2;
            count++;
        }
        if (in[1].c < lo) {
            out[1] = lo;
            d2 = in[0].c - in[1].c;
            t2 = ((lo - in[1].c) << 14) / d2;
            out[0] = in[1].o + (in[0].o - in[1].o) * t2 / 0x4000;
            out += 2;
            count++;
        } else if (in[1].c > hi) {
            out[1] = hi;
            d3 = in[0].c - in[1].c;
            t3 = ((hi - in[1].c) << 14) / d3;
            out[0] = in[1].o + (in[0].o - in[1].o) * t3 / 0x4000;
            out += 2;
            count++;
        }
    }
    return count;
}

/* Adds a fan of count - 2 black flat triangles to ot, built at prim: triangle i has the vertices xy[0],
 * xy[i + 1], xy[i + 2] (packed (x, y) words). Returns the next free primitive. The loop is a goto loop,
 * which loop.c leaves alone: the invariants are hoisted by hand (FINDINGS "A loop loop.c leaves alone"). */
void *prim_triangle_fan_add(PolyF3 *prim, u32 *ot, s32 count, u32 *xy) {
    u32 link;
    u32 first, last;
    u32 rgb_code;
    u8 len;
    PolyF3 *p;
    PolyF3 *prev;

    ot_link_load(link, ot);
    first = *xy++;
    last = *xy++;
    count -= 2;
    rgb_code = 0x20000000;
    if (count > 0) {
        len = 4;
        p = prim;
    loop:
        p->len = len;
        p->xy[1] = last;
        p->rgb_code = rgb_code;
        p->xy[0] = first;
        last = *xy++;
        prim++;
        p->xy[2] = last;
        prev = p;
        p++;
        TERM_LINK(prev, link);
        link = (u32)prev << 8;
        if (--count > 0)
            goto loop;
    }
    TERM_LINK(ot, link);
    return prim;
}

void uvec2_rotate_array(s32 count, UVec2 *v) {
    s32 x, z;

    while (count > 0) {
        gte_set(IR1, v->x);
        gte_set(IR2, 0);
        gte_set(IR3, v->y);
        gte_rtir();
        gte_get(IR1, x);
        gte_get(IR3, z);
        count--;
        v->x = x;
        v->y = -z;
        v++;
    }
}

void *clamp_table_draw_quads(u32 *ot, void *packet, void *areas) {
    s16 *quad; /* 4 (x, z) corners; the clipped polygon is built at quad + 0x14 */
    s32 *block;
    s32 *entry;
    s32 count;
    s32 cam_x;
    s32 cam_z;
    s32 x0, x1, z0, z1;
    s32 n;

    rot_load(view_matrix_t_get());
    /* FAKE: 12 empty insns where only packet is live lengthen its life, so global-alloc ranks it below
     * the clip buffer and the camera cells (packet in $fp as in the original) */
    __asm__(""); __asm__(""); __asm__(""); __asm__("");
    __asm__(""); __asm__(""); __asm__(""); __asm__("");
    __asm__(""); __asm__(""); __asm__(""); __asm__("");
    quad = scratch_alloc(8);
    block = (s32 *)clamp_table_get();
    entry = block + 1;
    count = block[0];
    cam_x = cam_pos >> 12;
    cam_z = cam_pos_z >> 12;
    if (count > 0) {
        do {
            if (entry[3] != 0) {
                x0 = entry[0];
                x0 = (x0 - cam_x) * 21 / 3072 - 1;
                x1 = entry[4];
                x1 = (x1 - cam_x) * 21 / 3072 + 1;
                z0 = entry[2];
                z0 = (z0 - cam_z) * 21 / 3072 - 1;
                z1 = entry[6];
                z1 = (z1 - cam_z) * 21 / 3072 + 1;
                quad[0] = x0;
                quad[6] = x0;
                quad[2] = x1;
                quad[4] = x1;
                quad[1] = z0;
                quad[3] = z0;
                quad[5] = z1;
                quad[7] = z1;
                uvec2_rotate_array(4, (UVec2 *)quad);
                n = prim_clip_band(4, (ClipIn *)quad, quad + 0x14);
                if (n >= 3) {
                    n = prim_clip_band(n, (ClipIn *)(quad + 0x14), quad);
                    if (n >= 3) {
                        packet = prim_triangle_fan_add(packet, ot, n, (u32 *)quad);
                    }
                }
            }
            count--;
            entry += 8;
        } while (count > 0);
    }
    scratch_top -= 8;
    return packet;
}

/* Returns 1 when any of the entries behind clamp_table_get's block has its flag
 * word (offset 0xC of each 0x20-byte entry) equal to 1, else 0. The block is
 * a count word followed by the entries. */
s32 clamp_table_has_flag(void) {
    s32 *block;
    s32 *entry;
    s32 count;

    block = (s32 *) clamp_table_get();
    if (block == NULL) {
        return 0;
    }
    count = block[0];
    entry = block + 1;
    if (count > 0) {
        do {
            if (entry[3] == 1) {
                return 1;
            }
            count -= 1;
            entry += 8;
        } while (count > 0);
    }
    return 0;
}

/* Adds the screen's fade quad, its draw-area commands and a dark 64x64 tile to OT entry ot, with the mask
 * command on each side. The globals are re-read after each packet store: the original does not keep them
 * across it, so each store is followed by an empty memory barrier (it emits nothing). */
void fade_mask_draw(void) {
    WorkArea *wa;
    u32 *ot;
    PrimMaskCmd *mask_on;
    PrimDrawAreas *areas;
    PrimTile *tile;
    PrimMaskCmd *mask_off;
    s32 y_bits;
    s32 x_bits;

    if (draw_enabled != 0 && area_warnings_flag != 0 && clamp_table_has_flag() != 0) {
        wa = work_area_ptr;
        ot = mask_draw_ot;
        mask_on = prim_fade_quad(ot, wa->packet, mask_fade_x, mask_fade_y);
        wa->packet = (u8 *)mask_on + sizeof(PrimMaskCmd);
        mask_on->len = 2;
        mask_on->cmd = 0xE6000001;
        mask_on->data = 0;
        addPrim(ot, mask_on);

        areas = wa->packet;
        wa->packet = (u8 *)areas + sizeof(PrimDrawAreas);
        areas->len = 3;
        areas->e3 = (((wa->draw_y + mask_area_y) & 0x3FF) << 10) | ((wa->draw_x + mask_area_x) & 0x3FF) | 0xE3000000;
        __asm__ volatile("" : : : "memory");
        areas->e4 = ((((wa->draw_y + mask_area_y + mask_area_h) - 1) & 0x3FF) << 10) | (((wa->draw_x + mask_area_x + mask_area_w) - 1) & 0x3FF) | 0xE4000000;
        __asm__ volatile("" : : : "memory");
        y_bits = (wa->draw_y + mask_area_y) & 0x7FF;
        x_bits = ((wa->draw_x + mask_area_x) & 0x7FF) | 0xE5000000;
        areas->e5 = (y_bits << 11) | x_bits;
        addPrim(ot, areas);

        wa->packet = clamp_table_draw_quads(ot, wa->packet, areas);
        tile = prim_draw_mirrored_sprite(ot, wa->packet, 0, 0);
        wa->packet = (u8 *)tile + sizeof(PrimTile);
        tile->colour.c.code = 0x60;
        tile->x = -0x20;
        tile->y = -0x20;
        tile->len = 3;
        tile->colour.c.r = 0;
        tile->colour.c.g = 0;
        tile->colour.c.b = 0;
        tile->w = 0x40;
        tile->h = 0x40;
        addPrim(ot, tile);

        mask_off = wa->packet;
        wa->packet = (u8 *)mask_off + sizeof(PrimMaskCmd);
        mask_off->len = 2;
        mask_off->cmd = 0xE6000000;
        mask_off->data = 0;
        addPrim(ot, mask_off);

        areas = wa->packet;
        wa->packet = (u8 *)areas + sizeof(PrimDrawAreas);
        areas->len = 3;
        areas->e3 = 0xE3000300;
        areas->e4 = 0xE400FF3F;
        areas->e5 = 0xE5010320;
        addPrim(ot, areas);
    }
}

void set_draw_enabled(s32 value) {
    draw_enabled = value;
}

s32 get_draw_enabled(void) {
    return draw_enabled;
}

void set_area_warnings(s32 value) {
    area_warnings_flag = value;
}

s32 area_warnings(void) {
    return area_warnings_flag;
}
