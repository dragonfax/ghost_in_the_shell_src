/* stage_info: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void stage_data_clear(void) {
    stage_data_ptr = 0;
}

/* Returns stage_data_ptr. */
s32 stage_data_get(void) {
    return stage_data_ptr;
}

void stage_data_set(s32 value) {
    stage_data_ptr = value;
}

s32 stage_data_count(void) {
    s32 result = -1;

    if (stage_data_ptr != 0) {
        result = ((s16 *)stage_data_ptr)[1];
    }
    return result;
}

/* stage_data_ptr is a table header; each word at +0x14 etc. is a 24-bit offset from the header (0 or negative: none). */
ScreenSize *stage_screen_size(void) {
    s32 block;

    if (stage_data_ptr == 0) {
        return &stage_screen_default;
    }
    block = *(s32 *)(stage_data_ptr + 0x14);
    if (block > 0) {
        block = stage_data_ptr + ((block << 8) >> 8);
    }
    return (ScreenSize *)block;
}

/* The block at +0x18 of the table header stage_data_ptr (24-bit offset; non-positive means none). */
void *fn_800EB618(void) {
    s32 block = *(s32 *)(stage_data_ptr + 0x18);

    if (block > 0) {
        block = stage_data_ptr + ((block << 8) >> 8);
    }
    return (void *)block;
}

/* The block at +0x4 of the table header stage_data_ptr (24-bit offset; non-positive means none). */
StageSetupBlock *get_stage_setup_block(void) {
    s32 block = *(s32 *)(stage_data_ptr + 0x4);

    if (block > 0) {
        block = stage_data_ptr + ((block << 8) >> 8);
    }
    return (StageSetupBlock *)block;
}

/* The block at +0x8 of the table header stage_data_ptr (24-bit offset; non-positive means none). */
void *get_stage_model_block(void) {
    s32 block = *(s32 *)(stage_data_ptr + 0x8);

    if (block > 0) {
        block = stage_data_ptr + ((block << 8) >> 8);
    }
    return (void *)block;
}

/* The block at +0x10 of the table header stage_data_ptr (24-bit offset; non-positive means none). */
void *get_stage_file_list(void) {
    s32 block = *(s32 *)(stage_data_ptr + 0x10);

    if (block > 0) {
        block = stage_data_ptr + ((block << 8) >> 8);
    }
    return (void *)block;
}

/* Address of record `index` (0x68 bytes each, from +4) in the data block stage_data_ptr points to; the
 * word at +0xC links to another block (a 24-bit offset when positive, else used as is). */
s32 get_stage_record(s32 index) {
    s32 block = stage_data_ptr;
    s32 link = *(s32 *)(block + 0xC);

    if (link <= 0) {
        block = link;
    } else {
        block += (link << 8) >> 8;
    }
    return block + 4 + index * 0x68;
}

/* Returns the word the table header at stage_data_ptr points to at 0xC. A positive word is a 24-bit offset
 * from the header to the entry to read; otherwise the word is a pointer and is read directly. */
s32 stage_record_count(void) {
    u8 *header = (u8 *)stage_data_ptr;
    s32 ref = *(s32 *)(header + 0xC);
    if (ref > 0) {
        ref = (ref << 8) >> 8;
        return *(s32 *)(header + ref);
    }
    return *(s32 *)ref;
}

/* Entry `index` (0-5) of the table header at stage_data_ptr, or 0 past the end. The header's word at +0x1C is
 * a 24-bit signed offset from the header to the entries; when it is not positive it is the entries' address. */
s32 get_stage_table_entry(u32 index) {
    s32 *entries;
    u8 *header;
    s32 offset;

    if (index >= 6) {
        return 0;
    }
    header = (u8 *)stage_data_ptr;
    offset = *(s32 *)(header + 0x1C);
    if (offset <= 0) {
        entries = (s32 *)offset;
    } else {
        offset = (offset << 8) >> 8;
        entries = (s32 *)(header + offset);
    }
    return entries[index];
}
