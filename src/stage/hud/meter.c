/* meter: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void meter_set(s32 a, s32 b) {
    s32 t;
    s32 clipped;

    t = b;
    if (b > 0x7FFF) {
        clipped = 0x7FFF;
        t = clipped;
    }
    clipped = b > 0x7FFF;
    if (clipped) {
        b = 0x7FFF;
    }
    if (b <= 0) {
        t = 1;
    }
    b = t;
    a = NOT_NEGATIVE(CLAMP_HI(a, b));
    gauge_max = b;
    gauge_value = a;
}

/* Per frame: gauge_flash_level ramps up by 0x200 (capped at 0x1000) while the mode in meter_mode is set and
 * meter_is_full says yes; otherwise it ramps down by 0x200 to 0. */
void meter_update(void) {
    s32 level;
    s32 next;

    if (meter_mode != 0 && meter_is_full() != 0) {
        next = gauge_flash_level + 0x200;
        level = 0x1000;
        if (next < 0x1001) {
            level = next;
        }
        gauge_flash_level = level;
        return;
    }
    gauge_flash_level = NOT_NEGATIVE(gauge_flash_level - 0x200);
}

static inline void id_record_add(s32 x, s32 y, s32 scale, s32 kind, s32 z, s32 level) {
    IdTable *tbl = &id_table;
    s32 slot = level >> 24;
    s32 index;
    IdRecord *rec;

    FAKE_OPAQUE(tbl);
    index = tbl->count;
    if (index < 0x100) {
        tbl->count = index + 1;
        rec = (IdRecord *)((u8 *)tbl + (index * 0x14 + 0x24));
        rec->prev_id = tbl->id[slot];
        tbl->id[slot] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = kind;
        rec->field_08 = 0;
        rec->field_0A = z;
        rec->field_0C = 0;
        rec->field_10 = level;
    }
}
/* Spawns 8 records 10 units apart starting at x - 70; their kinds
 * 0xF1 + n split the gauge value (gauge_value * 40 / gauge_max, rounded up)
 * into steps of at most 5. */
void gauge_segments_add(s32 x, s32 y, s32 z, s32 level) {
    s32 i;
    s32 remaining;
    s32 step;

    x -= 70;
    i = 0;
    level <<= 24;
    remaining = (gauge_value * 40 + gauge_max - 1) / gauge_max;
    for (; i < 8; i++) {
        step = 5;
        if (remaining < 6) {
            step = remaining;
        }
        remaining -= step;
        id_record_add(x, y, 0x1000, step + 0xF1, z, level);
        x += 10;
    }
}

static inline void id_record_add_marker(s32 x, s32 y, s32 z, s32 f0e, s32 f08, s32 step, s32 f0c)
{
    IdTable *tbl;
    s32 index;
    IdRecord *rec;

    /* scheduling barrier: keeps the 0xF0 load above the table address */
    do {
    } while (0);
    /* keeps the table address in a register */
    __asm__("" : "=r"(tbl) : "0"(&id_table));
    index = tbl->count;

    if (index < 0x100) {
        tbl->count = index + 1;
        rec = (IdRecord *)((u8 *)tbl + (index * 0x14 + 0x24));
        rec->prev_id = tbl->id[0];
        tbl->id[0] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = z;
        rec->field_0E = f0e;
        rec->field_08 = f08;
        rec->field_0A = step;
        rec->field_0C = f0c;
        rec->field_10 = 0;
    }
    gauge_segments_add(x, y, step, 0);
}
void gauge_marker_draw(void)
{
    s32 x, y, z, f0e, step;

    if (gauge_flash_level != 0) {
        z = 0x1000;
        x = 0x74;
        y = -0x4E;
        step = (z - gauge_flash_level) / 4;
        f0e = 0xF0;
        id_record_add_marker(x, y, z, f0e, 0, step, 0);
    }
}
