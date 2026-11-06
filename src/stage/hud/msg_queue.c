/* msg_queue: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void spark_add_view_angles(void) {
    s32 view_ry;
    s32 view_rx;
    s32 view_rz;
    SparkList *list;
    s32 n;
    s32 value;
    s32 ry, rx, rz;
    s32 colour;
    SparkRec *s;
    u8 *tail;

    matrix_to_angles(view_matrix_t_get(), &view_ry, &view_rx, &view_rz);
    colour = 0x1000000;
    list = &spark_list;
    n = spark_count;
    value = spark_model_base + 0xC;
    ry = view_ry;
    rx = view_rx;
    rz = view_rz;
    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = 0;
        s->y = 0;
        s->z = 0;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

static inline void id_table_add_list1(s32 x, s32 y, s32 depth, s32 flags, s32 scale) {
    IdTableRecords *tbl = (IdTableRecords *)&id_table;
    s32 index;
    IdRecord *rec;

    __asm__ volatile("");
    FAKE_OPAQUE(tbl);
    index = tbl->count;

    if (index < 0x100) {
        /* a plain (non-struct) store: the caller's track_base read then stays in its loop */
        *(s32 *)tbl = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = tbl->id[1];
        tbl->id[1] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = depth;
        rec->field_08 = 0;
        rec->field_0A = 0;
        rec->field_0C = 0;
        rec->field_10 = flags;
    }
}
/* Adds an id_table record for each layout entry (s16 x, y, frame, pad), up to the
 * first negative frame; screen position is (x - 0x51, y - 0x3E). */
void id_table_add_layout(s16 *layout) {
    for (; layout[2] >= 0; layout += 4) {
        id_table_add_list1(layout[0] - 0x51, layout[1] - 0x3E, track_base + layout[2], 0x01000000, 0x1000);
    }
}

void stage_reset(void) {
    if (untimed_part()) {
        rec_table_update();
        id_table_add_layout(d_8011E3C0);
        hud_grenades_draw(0, 0);
        hud_score_draw(-0x86, 0x19, 7, 6);
        hud_lock_gauge_draw(-0x4E, 0x18);
        req_queue_flush(0, 0);
        shield_meter_draw(0, 0);
        id_table_add_pair(0, 0);
        spark_add_view_angles();
        fade_mask_draw();
        fn_80100880();
        target_marker_draw();
        gauge_marker_draw();
        if (stage_end_state != 0) {
            ui_items_draw();
        }
        view_set_on(3, 0);
    }
}

s32 msg_queue_count(void) {
    return msg_queue_length;
}

void msg_queue_clear(void) {
    msg_read_index = 0;
    msg_write_index = 0;
    msg_queue_length = 0;
}
