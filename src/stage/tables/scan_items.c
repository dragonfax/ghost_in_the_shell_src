/* scan_items: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

s32 ptr_table_load_ids(u8 **ids, s32 *count) {
    void *table;

    *count = ptr_table_count();
    while (*ids != 0) {
        table = record_data_get(*ids);
        if (table == NULL) {
            return 0;
        }
        ptr_table_append(table);
        ids++;
    }
    ptr_table_trim();
    return 1;
}

s32 scan_items_run(s32 index, ScanItem *items) {
    ScanItem *item;
    ScanEntry *entry;
    s32 *out;

    item = items;
    if (item->entry != (ScanEntry *)-1) {
        do {
            if (item->entry != NULL) {
                debug_name_set(item->name);
                entry = item->entry;
                out = entry->out;
                if (index >= 0) {
                    hook_set(index, entry->hooks[0], entry->hooks[1]);
                }
                out[0] = -1;
                if (entry->model_block != 0) {
                    if (stage_model_block_load((ModelBlock *)entry->model_block, out) == 0) {
                        return 0;
                    }
                }
                out[2] = -1;
                if (entry->stage_files != 0) {
                    if (stage_files_load((u8 **)entry->stage_files, out + 2) == 0) {
                        return 0;
                    }
                }
                out[1] = -1;
                if (entry->ptr_table_ids != 0) {
                    if (ptr_table_load_ids((u8 **)entry->ptr_table_ids, out + 1) == 0) {
                        return 0;
                    }
                }
                debug_name_set(NULL);
            }
            item++;
            index++;
        } while (item->entry != (ScanEntry *)-1);
    }
    return 1;
}

/* Sets the debug name from the entry; when it has a key that record_data_get finds, runs stage_data_set on it,
 * clears the name and returns 1. */
s32 named_entry_run(NamedEntry *entry) {
    void *found;

    if (entry != NULL) {
        debug_name_set(entry->name);
        if (entry->key != 0) {
            found = record_data_get(entry->key);
            if (found != NULL) {
                stage_data_set((s32)found);
                debug_name_set(NULL);
                return 1;
            }
        }
    }
    return 0;
}

s32 scan_record_run(u8 *rec) {
    ScanItem *items;

    if (rec != NULL) {
        items = *(ScanItem **)(rec + 0x24);
        if (items != NULL) {
            if (scan_items_run(0, items) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

/* Skips leading '.' characters of a name. */
u8 *name_skip_dots(u8 *s) {
    if (s != 0 && *s == '.') {
        s++;
        do {
        } while (*s++ == '.');
    }
    return s;
}

void debug_name_set(u8 *name) {
    if (name != NULL && debug_check_a() != 0) {
        debug_name_store(exec_path_get());
    } else {
        if (debug_check_b() != 0) {
            name = name_skip_dots(name);
        }
        debug_name_store(name);
    }
}

u8 *exec_path_get(void) {
    return get_exec_path();
}
