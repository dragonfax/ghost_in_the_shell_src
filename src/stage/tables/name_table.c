/* name_table: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

u32 name_key_endian_swap(s32 key) {
    u32 result;
    if (d_8011DD70 == 0) {
        result = (u32)key >> 24;
        result += ((u32)key & 0xFF0000) >> 8;
        result += (((u32)key >> 8) & 0xFF) << 16;
        result += key << 24;
    } else {
        result = key;
    }
    return result;
}

/* strcpy: returns the length copied (without the terminator). */
s32 str_copy_len(u8 *src, u8 *dst) {
    s32 length;
    u8 *from;
    u8 *to;
    u8 ch;

    from = src;
    to = dst;
    length = -1;
    do {
        ch = *from;
        from += 1;
        length += 1;
        *to = ch;
        to += 1;
    } while (ch != 0);
    return length;
}

s32 str_length(u8 *str) {
    s32 len = 0;

    while (*str++ != 0) {
        len++;
    }
    return len;
}

/* Case-insensitive string equality (ASCII letters only). Returns 1 if equal. */
s32 str_text_eq_nocase(u8 *str_a, u8 *str_b) {
    s32 len;
    u8 c_a;
    u8 c_b;

    len = str_length(str_a);
    if (len == str_length(str_b)) {
        do {
            c_a = *str_a;
            str_a += 1;
            c_a = ((u32)(c_a - 'a') < 26) ? (c_a & 0xDF) : c_a;
            c_b = *str_b;
            str_b += 1;
            c_b = ((u32)(c_b - 'a') < 26) ? (c_b & 0xDF) : c_b;
            if (c_a != c_b) {
                return 0;
            }
        } while (c_a != 0);
        return 1;
    }
    return 0;
}

/* Checksum of a string: length plus the sum of its bytes, as a byte. */
s32 name_key(u8 *str) {
    u8 c;
    s32 sum = str_length(str);

    while ((c = *str++) != 0) {
        sum += c;
    }
    return sum & 0xFF;
}

/* Copies the directory part of a path (up to and including the last '/') to `out`; an empty path gives "/". */
void path_dirname(u8 *path, u8 *out) {
    u8 *p;
    u8 *end;
    u8 c;

    if (*path == 0) {
        *out = '/';
        return;
    }
    p = path;
    end = p;
    do {
        c = *p++;
        if (c == '/') {
            end = p;
        }
    } while (c != 0);
    p = path;
    if (end != p) {
        do {
            *out++ = *p++;
        } while (end != p);
    }
    *out = 0;
}

/* Copies the last component of a path (after the final '/') to dst; an empty path gives "/". */
void path_basename(u8 *path, u8 *dst) {
    u8 *p = path;
    u8 ch;

    if (*path == 0) {
        *dst = '/';
        return;
    }
    do {
        ch = *p++;
        if (ch == '/') {
            path = p;
        }
    } while (ch != 0);
    while ((ch = *path++) != 0) {
        *dst++ = ch;
    }
    *dst = 0;
}

/* Normalises a file path: drops a "drive:" prefix, makes sure it starts with '/', upper-cases letters and
 * turns '\' into '/'. */
void path_normalize(u8 *path, u8 *dst) {
    u8 *p = path;
    u8 ch;
    u8 upper;
    u8 out;

    do {
        ch = *p++;
        if (ch == ':') {
            path = p;
        }
    } while (ch != 0);
    ch = *path;
    if (ch != '/' && ch != '\\') {
        *dst++ = '/';
    }
    do {
        ch = *path++;
        if ((u32)(ch - 'a') < 26) {
            upper = ch & 0xDF;
        } else {
            upper = ch;
        }
        out = upper;
        if ((out & 0xFF) == '\\') {
            out = '/';
        }
        *dst++ = out;
    } while (out & 0xFF);
}

/* Sets the record table (name_table_root and its copy name_table_cwd). */
void name_table_set(NameEntry *recs) {
    name_table_root = recs;
    name_table_cwd = recs;
}

/* The entry of a 0x18-byte name table with this name (its key matches and the text compares equal), or NULL. */
NameEntry *name_table_find(NameEntry *table, char *name) {
    s32 key = name_key(name);

    char *text = table->text; /* the original walks the text pointer too and reads `used` as text[-1] */

    while (1) {
        if (text[-1] == 0) {
            return NULL;
        }
        if (key == table->key && str_text_eq_nocase(text, name) != 0) {
            return table;
        }
        text += sizeof(NameEntry);
        table++;
    }
}

/* The name_table_root entry for the one name_table_find finds by name, when its flag 0x10 at +0xF is set, else NULL.
 * One exit through `rec` is what matches. */
NameEntry *name_table_record(NameEntry *table, char *name) {
    u8 *entry = (u8 *)name_table_find(table, name);
    NameEntry *rec;

    if (entry == NULL) {
        rec = NULL;
    } else if (!(entry[0xF] & 0x10)) {
        rec = NULL;
    } else {
        rec = &name_table_root[name_key_endian_swap(*(s32 *)(entry + 0x14))];
    }
    return rec;
}

s32 name_table_chdir(char *path) {
    char name[256];
    NameEntry *entry = name_table_root;
    char *dst = name;
    u8 c;

    path++;
    for (;;) {
        c = *path++;
        if (c == 0) {
            name_table_cwd = entry;
            return 1;
        }
        if (c == '/') {
            *dst = 0;
            entry = name_table_record(entry, name);
            if (entry == NULL) {
                name_table_cwd = name_table_root;
                return 0;
            }
        } else {
            *dst++ = c;
        }
    }
}

NameEntry *name_table_get(void) {
    return name_table_cwd;
}

NameEntry *name_table_lookup(char *path) {
    u8 src[0x100];
    u8 dst[0x100];

    path_normalize(path, src);
    path_dirname(src, dst);
    name_table_chdir(dst);
    path_basename(src, dst);
    return name_table_find(name_table_get(), dst);
}
