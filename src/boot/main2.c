#include "common.h"
#include "boot.h"
#include "boot_types.h"

/* Copies a zero-terminated list of service functions into svc_table from index first_svc. */
void svc_register(void *fns, s32 first_svc);

s32 svc_unimplemented(void);

#define SVC_TABLE_ADDR 0x80010000
#define SVC_SLOT_COUNT 0x400

/* Fills every service slot with svc_unimplemented. */
void svc_table_reset(void) {
    s32 (**slot)(void) = (s32 (**)(void))SVC_TABLE_ADDR;
    s32 i;

    for (i = 0; i < SVC_SLOT_COUNT; i++) {
        *slot++ = svc_unimplemented;
    }
}

void shared_state_clear(void) {
    s32 var_v0;
    s8 *var_v1;

    var_v1 = (s8 *)0x80014000;
    var_v0 = 0x3FFF;
    do {
        *var_v1 = 0;
        var_v0 -= 1;
        var_v1 += 1;
    } while (var_v0 >= 0);
}

extern void *actors_slot_table[16];
extern Node obj_list_actors_tail;
/* Same code as actors_phase0 (s01). */
void svc_register_actors(void) {
    svc_register(actors_slot_table, 0);
}

void boot_init(void) {
    svc_table_reset();
    shared_state_clear();
    svc_register_actors();
    func_800417F8();
    gpu_register_slots();
    sound_register_slots();
    file_register_slots();
    mdec_register_slots();
    pad_register_slots();
    frame_register_slots();
    func_80040090();
    thread_register_slots();
}

extern void *D_80041978[];

void func_80040090(void) {
    svc_register(D_80041978, 0x38);
}

s32 boot_str_length(u8 *str);
s32 mem_equal(s32 len, u8 *lhs, u8 *rhs);
/* Scans [start, end) for the first position where the string 'needle' occurs; returns that position, or 0. */
u8 *str_find_in_range(u8 *needle, u8 *start, u8 *end) {
    u8 *pos;
    u8 *found;
    u8 c;

    pos = start;
    while (pos < end) {
        found = pos;
        if (mem_equal(boot_str_length(needle), needle, pos) != 0) {
            return found;
        }
        do {
            c = *pos;
            pos++;
        } while (c != 0);
    }
    return 0;
}

u8 music_section_name[8] = "[MUSIC]";

extern u8 music_section_name[];

s32 printf(const char *fmt, ...);
void cfg_set_section(u8 *section);
s32 cfg_get_number(s32 table_index, s32 skip_count);
s32 cfg_section_exists(void);
u8 *cfg_get_value(s32 key, s32 count);
u8 *cd_track_table_get(void);
s32 boot_str_length(u8 *str);
u8 *str_find_in_range(u8 *needle, u8 *start, u8 *end);
void str_copy(u8 *src, u8 *dst);

/* Reads the [MUSIC] section into the music table and the name buffer;
   returns the new end of the name buffer. */
s32 music_register(s32 buf, s32 used) {
    MusicSlot *table;
    MusicSlot *slot;
    u8 *cur;
    u8 *found;
    u8 *name;
    s32 count;
    s32 idx;
    s32 section;
    s32 music_no;
    s32 attr1;
    s32 attr2;
    s32 attr3;
    s32 attr4;
    s32 attr6;

    cur = (u8 *)(buf + used);
    cfg_set_section(music_section_name);
    idx = 0;
    slot = (MusicSlot *)cd_track_table_get();
    do {
        idx++;
        slot->music_no = 0xFF;
        slot->unk_01 = 0xC8;
        slot->attr1 = 0;
        slot->unk_03 = 0;
        slot->name = NULL;
        slot->attr2 = 0;
        slot->attr3 = 0;
        slot->attr4 = 0;
        slot->active = 1;
        slot++;
    } while (idx < 0x80);

    if (cfg_section_exists() == 0) {
        return used;
    }
    count = cfg_get_number(0, 0);
    if (count == 0x80000000) {
        return used;
    }
    if (count >= 0x80) {
        printf("FATAL:[MUSIC] No Free Work.");
        return used;
    }

    table = (MusicSlot *)cd_track_table_get();
    slot = table;
    for (idx = 0; idx < count; idx++) {
        section = idx + 1;
        music_no = cfg_get_number(section, 0);
        if (music_no == 0x80000000) {
            return used;
        }
        if (music_no == 0xFF) {
            break;
        }
        attr1 = cfg_get_number(section, 1);
        if (attr1 == 0x80000000) {
            return used;
        }
        attr2 = cfg_get_number(section, 2);
        if (attr2 == 0x80000000) {
            return used;
        }
        attr3 = cfg_get_number(section, 3);
        if (attr3 == 0x80000000) {
            return used;
        }
        attr4 = cfg_get_number(section, 4);
        if (attr4 == 0x80000000) {
            return used;
        }
        name = cfg_get_value(section, 5);
        if ((s32)name == 0x80000000) {
            return used;
        }
        attr6 = cfg_get_number(section, 6);
        if (attr6 == 0x80000000) {
            return used;
        }
        if (used + boot_str_length(name) + 1 >= 0x1000) {
            printf("FATAL:[MUSIC] No Free Name Buffer .\n");
            return used;
        }
        if (music_no >= 0xFF) {
            printf("FATAL:[MUSIC] Music Number is out of range.\n");
            return used;
        }
        found = str_find_in_range(name, (u8 *)buf, cur);
        if (found == NULL) {
            found = cur;
            str_copy(name, cur);
            cur += boot_str_length(name) + 1;
        }
        slot->music_no = music_no;
        slot->unk_01 = 0xC8;
        slot->attr1 = attr1;
        slot->unk_03 = attr6;
        slot->attr2 = attr2;
        slot->attr3 = attr3;
        slot->attr4 = attr4;
        slot->name = found;
        slot->active = 1;
        slot++;
    }
    return (s32)(cur - (u8 *)buf);
}

s32 cfg_section_exists(void);
u8 *cfg_get_value(s32 key, s32 count);
s32 sysini_country(s32 *out) {
    u8 *p;
    cfg_set_section("[COUNTRY]");
    *out = 0;
    if (!cfg_section_exists()) {
        return 0;
    }
    p = cfg_get_value(0, 0);
    if (p == (u8 *)0x80000000) {
        return 0;
    }
    switch (*p | 0x20) {
    case 0x6A:
        *out = 0;
        break;
    case 0x75:
        *out = 1;
        break;
    case 0x65:
        *out = 2;
        break;
    case 0x61:
        *out = 3;
        break;
    default:
        return 0;
    }
    return 1;
}

void cfg_set_section(u8 *section);
s32 cfg_section_exists(void);
u8 *cfg_get_value(s32 key, s32 count);
s32 sysini_video(s32 *out) {
    u8 *p;

    cfg_set_section("[VIDEO]");
    *out = 0;
    if (cfg_section_exists() == 0) {
        return 0;
    }
    p = (u8 *)cfg_get_value(0, 0);
    if (p == (u8 *)0x80000000) {
        return 0;
    }
    switch (*p | 0x20) {
    case 0x6E:
        *out = 0;
        break;
    case 0x70:
        *out = 1;
        break;
    default:
        return 0;
    }
    return 1;
}

s32 sysini_warning(s32 *out) {
    u8 *p;

    cfg_set_section("[WARNING]");
    *out = 0;
    if (cfg_section_exists() == 0) {
        return 0;
    }
    p = (u8 *)cfg_get_value(0, 0);
    if (p == (u8 *)0x80000000) {
        return 0;
    }
    switch (*p | 0x20) {
    case 0x79:
        *out = 1;
        return 1;
    case 0x6E:
        *out = 0;
        break;
    default:
        return 0;
    }
    return 1;
}

void cfg_set_section(u8 *section);
s32 cfg_section_exists(void);
void str_copy(u8 *src, u8 *dst);
s32 sysini_cardname(u8 *dst) {
    s32 handle;

    cfg_set_section("[CARDNAME]");
    if (cfg_section_exists() != 0) {
        handle = (s32)cfg_get_value(0, 0);
        if (handle != 0x80000000) {
            str_copy((u8 *)handle, dst);
            return 1;
        }
    }
    return 0;
}

void sys_set_root(u8 *path);
/* Sets the root path from the caller's argument (passed through to
   cfg_set_section), dropping one trailing backslash. Returns 1 on success. */
s32 sysini_set_root(s32 caller_arg) {
    s32 root;
    s32 root_len;
    u8 *end;

    cfg_set_section((u8 *)caller_arg);
    if (cfg_section_exists() == 0) {
        return 0;
    }
    root = (s32)cfg_get_value(0, 0);
    if (root == 0x80000000) {
        return 0;
    }
    root_len = boot_str_length((u8 *)root);
    if (root_len >= 2) {
        end = (u8 *)(root_len + root);
        if (end[-1] == '\\') {
            end[-1] = 0;
        }
    }
    sys_set_root((u8 *)root);
    return 1;
}

void * get_movie_table(void);
/* Reads the [MOVIE] section into the movie table and the name buffer;
   returns the new used size of the name buffer. */
s32 sysini_movie(s32 buf, s32 used) {
    u8 *cur;
    u8 *found;
    u8 *name;
    s32 count;
    s32 idx;
    s32 section;
    s32 movie_no;
    s32 movie_id;
    MovieSlot *slot;

    cur = (u8 *)(buf + used);
    cfg_set_section("[MOVIE]");
    slot = get_movie_table();
    idx = 0;
    do {
        idx++;
        slot->name = NULL;
        slot->movie_id = 0;
        slot++;
    } while (idx < 0x40);

    if (cfg_section_exists() == 0) {
        return used;
    }
    count = cfg_get_number(0, 0);
    if (count == 0x80000000) {
        return used;
    }
    for (idx = 0; idx < count; idx++) {
        section = idx + 1;
        movie_no = cfg_get_number(section, 0);
        if (movie_no == 0x80000000) {
            return used;
        }
        if (movie_no == 0xFF) {
            break;
        }
        movie_id = cfg_get_number(section, 1);
        if (movie_id == 0x80000000) {
            return used;
        }
        name = cfg_get_value(section, 2);
        if ((s32)name == 0x80000000) {
            return used;
        }
        slot = get_movie_table();
        slot += movie_no;
        if (movie_no >= 0x40) {
            printf("Movie Number Limit Over.\n");
            return used;
        }
        if (used + boot_str_length(name) + 1 >= 0x1000) {
            printf("FATAL:[MOVIE] No Free Name Buffer .\n");
            return used;
        }
        if (movie_no >= 0xFF) {
            printf("FATAL:[MOVIE] Movie Number is out of range.\n");
            return used;
        }
        found = str_find_in_range(name, (u8 *)buf, cur);
        if (found == NULL) {
            found = cur;
            str_copy(name, cur);
            cur += boot_str_length(name) + 1;
        }
        slot->movie_id = movie_id;
        slot->name = found;
    }
    return (s32)(cur - (u8 *)buf);
}

void *get_exec_table(void);

/* Reads the [EXEC] section into the exec program table and the name buffer;
   returns the new end of the name buffer. */
s32 sysini_exec(s32 buf, s32 used) {
    struct ExecProgram *table;
    u8 *cur;
    u8 *found;
    u8 *name;
    s32 count;
    s32 idx;
    s32 section;
    s32 code;
    s32 flags;

    cur = (u8 *)(buf + used);
    cfg_set_section("[EXEC]");
    table = get_exec_table();
    idx = 0;
    do {
        idx++;
        table->name = NULL;
        table->flags = -1;
        table++;
    } while (idx < 0x60);

    if (cfg_section_exists() == 0) {
        return used;
    }
    count = cfg_get_number(0, 0);
    if (count == 0x80000000) {
        return used;
    }

    table = get_exec_table();
    for (idx = 0; idx < count; idx++) {
        section = idx + 1;
        code = cfg_get_number(section, 0);
        if (code == 0x80000000) {
            return used;
        }
        if (code == 0xFF) {
            break;
        }
        flags = cfg_get_number(section, 1);
        if (flags == 0x80000000) {
            return used;
        }
        name = cfg_get_value(section, 2);
        if ((s32)name == 0x80000000) {
            return used;
        }
        if (code >= 0x60) {
            printf("FATAL:[EXEC] EXEC Code Number is out of range.\n");
            return used;
        }
        if (used + boot_str_length(name) + 1 >= 0x1000) {
            printf("FATAL:[EXEC] No Free Name Buffer .\n");
            return used;
        }
        if (flags & ~2) {
            flags |= 0x80000000;
        }
        found = str_find_in_range(name, (u8 *)buf, cur);
        if (found == NULL) {
            found = cur;
            str_copy(name, cur);
            cur += boot_str_length(name) + 1;
            used += boot_str_length(name) + 1;
        }
        table[code].name = (char *)found;
        table[code].flags = flags;
    }
    return (s32)(cur - (u8 *)buf);
}

#define CFG_NONE ((s32)0x80000000)
#define NAME_BUF_LIMIT 0x1000


BootExecRequest *get_exec_request(void);
s32 cfg_get_number(s32 table_index, s32 skip_count);
s32 printf(const char *fmt, ...);

s32 sysini_startup(u8 *start, s32 size) {
    BootExecRequest *req;
    s32 flags;
    u8 *name;
    u8 *end;
    u8 *found;

    end = start + size;
    cfg_set_section("[STARTUP]");
    req = get_exec_request();
    req->name = NULL;
    req->flags = -1;

    if (cfg_section_exists() == 0) {
        return size;
    }
    if (cfg_get_number(0, 0) == CFG_NONE) {
        return size;
    }
    flags = cfg_get_number(0, 0);
    if (flags == CFG_NONE) {
        return size;
    }
    name = cfg_get_value(0, 1);
    if ((s32)name == CFG_NONE) {
        return size;
    }
    if (size + boot_str_length(name) + 1 >= NAME_BUF_LIMIT) {
        printf("FATAL:[STARTUP] No Free Name Buffer .\n");
        return size;
    }
    if (flags & ~2) {
        flags |= CFG_NONE;
    }
    found = str_find_in_range(name, start, end);
    if (found == NULL) {
        found = end;
        str_copy(name, end);
        end += boot_str_length(name) + 1;
        boot_str_length(name);
    }
    req->name = (char *)found;
    req->flags = flags;
    return end - start;
}

s32 sysini_gamemode(s32 *out) {
    u8 *p;

    cfg_set_section("[GAMEMODE]");
    *out = 0;
    if (cfg_section_exists() == 0) {
        return 0;
    }
    p = (u8 *)cfg_get_value(0, 0);
    if (p == (u8 *)0x80000000) {
        return 0;
    }
    switch (*p | 0x20) {
    case 0x67:
        *out = 0;
        break;
    case 0x64:
        *out = 1;
        return 1;
    default:
        return 0;
    }
    return 1;
}

extern u8 sys_default_root[];
extern char system_txt_name[]; /* "SYSTEM.TXT" */
extern char fatal_no_cardname_msg[]; /* "FATAL:NO MEMORY CARDNAME\n" */
extern char section_root_name[]; /* "[ROOT]" */
extern char section_cdroot_name[]; /* "[CDROOT]" */
s32 unpex_last_word_get(void);
s32 get_ramp_state(void);
s32 cdfs_read_file(void *name, u8 *dst, s32 size);
void cfg_set_text(s32 arg0);
s32 sysini_country(s32 *out);
void sys_set_country(s32 arg0);
s32 sysini_video(s32 *out);
void sys_set_video_mode(s32 arg0);
s32 sysini_warning(s32 *out);
void sys_set_warning(s32 arg0);
s32 sysini_gamemode(s32 *out);
void sys_set_gamemode(s32 arg0);
s32 cardname_buf_get(void);
s32 sysini_cardname(u8 *dst);
s32 sysini_startup(u8 *start, s32 size);
s32 music_register(s32 a, s32 b);
s32 sysini_exec(s32 a, s32 b);
s32 sysini_movie(s32 a, s32 b);
void sysini_load(void) {
    s32 cfg;
    s32 root;
    s32 sys_ctx;

    root = unpex_last_word_get();
    sys_ctx = get_ramp_state();
    sys_set_root(sys_default_root);
    cfg = cdfs_read_file("SYSTEM.TXT", (u8 *)root, 0);
    cfg_set_text(root);
    sysini_country(&cfg);
    sys_set_country(cfg);
    sysini_video(&cfg);
    sys_set_video_mode(cfg);
    sysini_warning(&cfg);
    sys_set_warning(cfg);
    sysini_gamemode(&cfg);
    sys_set_gamemode(cfg);
    cfg = sysini_cardname((u8 *)cardname_buf_get());
    if (cfg == 0) {
        printf("FATAL:NO MEMORY CARDNAME\n");
        for (;;) {}
    }
    sysini_set_root((s32)"[ROOT]");
    sysini_set_root((s32)"[CDROOT]");
    cfg = 0;
    cfg = sysini_startup((u8 *)sys_ctx, 0);
    cfg = music_register(sys_ctx, cfg);
    cfg = sysini_exec(sys_ctx, cfg);
    cfg = sysini_movie(sys_ctx, cfg);
}

s32 cfg_filter_char(s32 arg0) {
    s32 var_a0;
    u32 temp_v1;

    var_a0 = arg0;
    temp_v1 = var_a0 & 0xFF;
    if ((temp_v1 != 0x1A) && (temp_v1 < 0x21U)) {
        var_a0 = 0;
    }
    return var_a0 & 0xFF;
}

extern u8 cfg_separators[];
s32 cfg_is_sep(u8 c) {
    u8 *cursor;
    u8 cur_char;

    cursor = cfg_separators;
    cur_char = *cursor;
    while (cur_char != 0) {
        if (c == cur_char) {
            return 1;
        }
        cursor++;
        cur_char = *cursor;
    }
    return 0;
}

u8 *cfg_skip_gap(u8 *p) {
    while (!(cfg_filter_char(*p) & 0xFF)) {
        p++;
    }
    return p;
}

s32 is_space_or_tab(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    temp_a0 = arg0 & 0xFF;
    var_v1 = 0;
    if ((temp_a0 == 0x20) || (temp_a0 == 9)) {
        var_v1 = 1;
    }
    return var_v1;
}

u8 *cfg_skip_token(u8 *cur) {
    while (*cur != 0x1A) {
        if (!(cfg_filter_char(*cur) & 0xFF)) {
            break;
        }
        cur++;
    }
    return cur;
}

/* Skips leading spaces and tabs; returns the first other byte. */
u8 *skip_blanks(u8 *str) {
    while (is_space_or_tab(*str)) {
        str++;
    }
    return str;
}

u8 *cfg_skip_line(u8 *p)
{
    while (*p != 0x1A && *p != 0xD && *p != 0xA) {
        p++;
    }
    while (*p == 0xD || *p == 0xA) {
        p++;
    }
    return p;
}

u8 * cfg_skip_line(u8 *p);
s32 cfg_is_sep(u8 c);

/* Advances past the current token: skips to the next entry with cfg_skip_line and cfg_skip_gap
 * until the byte under the pointer fails the cfg_is_sep test. Returns the pointer that stopped it. */
u8 *cfg_skip_entry(u8 *p) {
    do {
        p = cfg_skip_gap(cfg_skip_line(p));
    } while (cfg_is_sep(*p) != 0);
    return p;
}

/* Scans forward to the next entry, then returns it once it fails the cfg_is_sep test. */
/* Walks the entries from p: each step lands on the next entry with cfg_skip_gap and
 * moves past it with cfg_skip_line, until the byte under the pointer fails the cfg_is_sep test. */
u8 *cfg_next_entry(u8 *p) {
    u8 *cur;

    cur = cfg_skip_gap(p);
    while (cfg_is_sep(*cur) != 0) {
        p = cfg_skip_line(cur);
        cur = cfg_skip_gap(p);
    }
    return cur;
}

/* Copies up to 256 bytes of src through cfg_filter_char into dst, stopping after a zero byte. */
s32 cfg_copy_value(u8 *src, s8 *dst) {
    s32 len;
    u8 c;

    len = 0;
    do {
        c = cfg_filter_char(*src++);
        *dst++ = c;
        if (c == 0) {
            break;
        }
        len++;
    } while (len < 0x100);
    dst[-1] = 0;
    return len;
}

/* Returns 0 if the string `prefix` matches the start of `str`, else 1.
 * An empty prefix returns 1. */
s32 str_prefix_cmp(u8 *str, u8 *prefix) {
    u8 expected = *prefix;
    s32 result = 1;

    if (expected != 0) {
        do {
            result = 0;
            prefix++;
            if (*str++ == expected) {
                expected = *prefix;
            } else {
                result = 1;
                break;
            }
        } while (expected != 0);
    }
    return result;
}

/* Parses a hex string (case-insensitive) up to the first filtered-out
 * character; returns 0x80000000 on a non-hex character. */
s32 parse_hex(u8 *str) {
    s32 value;
    u8 c;
    s32 base;

    value = 0;
    for (;;) {
        register s32 raw asm("$4") = cfg_filter_char(*str++);
        c = raw;
        if (c == 0) {
            break;
        }
        value <<= 4;
        c |= 0x20;
        if ((u8)(c - '0') < 10) {
            base = value - '0';
            value = base + c;
        } else if ((u8)(c - 'a') < 6) {
            base = value - 'a' + 10;
            value = base + c;
        } else {
            return 0x80000000;
        }
    }
    return value;
}

/* Parses a binary number ('0'/'1' digits, '_' separators) from a string.
   Stops at the NUL terminator; returns 0x80000000 on any other character. */
s32 parse_binary(u8 *str) {
    s32 value;
    s32 raw;
    s32 c;
    s32 biased;

    value = 0;
    for (;;) {
        raw = cfg_filter_char(*str);
        str++;
        c = raw & 0xFF;
        if (c != 0) {
            if ((u32)((raw - '0') & 0xFF) < 2 || c == '_') {
                if (c != '_') {
                    value *= 2;
                    biased = value - '0';
                    value = biased + c;
                }
            } else {
                return 0x80000000;
            }
        } else {
            return value;
        }
    }
}

/* Parses a decimal number from a string. Stops at the NUL terminator;
   returns 0x80000000 on a non-digit character. Symbol to be renamed
   parse_decimal at install. */
s32 parse_decimal(u8 *str) {
    s32 value;
    s32 raw;
    s32 scaled;

    value = 0;
    for (;;) {
        raw = cfg_filter_char(*str);
        str++;
        if ((raw & 0xFF) != 0) {
            value = value * 10;
            if ((u32)((raw - 0x30) & 0xFF) < 10) {
                scaled = value - 0x30;
                value = scaled + (raw & 0xFF);
            } else {
                return 0x80000000;
            }
        } else {
            return value;
        }
    }
}

s32 parse_hex(u8 *str);
s32 parse_binary(u8 *str);
/* Parses an optional '+' or '-' sign, then a '$' hex or '%' binary
   prefix, else decimal. Returns 0x80000000 on error. */
s32 parse_number(u8 *str) {
    s32 negative;
    s32 value;
    s32 c;

    c = *str;
    if (c != '+') {
        negative = 0;
        if (c == '-') {
            str++;
            negative = 1;
            c = *str;
        }
    } else {
        str++;
        negative = 0;
        c = *str;
    }

    if (c == '$') {
        value = parse_hex(str + 1);
    } else if (c == '%') {
        value = parse_binary(str + 1);
    } else {
        value = parse_decimal(str);
    }

    if (value < 0) {
        return 0x80000000;
    }
    if (negative != 0) {
        value = -value;
    }
    return value;
}

extern u8 *cfg_cache_key;
extern u8 *cfg_find_cache_result;
extern s32 cfg_cache_pos;
u8 *cfg_next_entry(u8 *p);
u8 *cfg_skip_entry(u8 *p);
s32 str_prefix_cmp(u8 *str, u8 *prefix);
u8 *cfg_find_section(s32 start, s32 key) {
    u8 *p;
    u8 *prefix;

    p = (u8 *)start;
    prefix = (u8 *)key;
    if (prefix == cfg_cache_key) {
        return cfg_find_cache_result;
    }
    cfg_cache_pos = 0x7FFF;
    cfg_cache_key = prefix;
    cfg_find_cache_result = (u8 *)0x80000000;
    p = cfg_next_entry(p);
    goto test;
body:
    if (str_prefix_cmp(p, prefix) == 0) {
        cfg_find_cache_result = p;
        return p;
    }
    p = cfg_skip_entry(p);
test:
    if (*p != 0x1A) goto body;
    return (u8 *)0x80000000;
}

extern u8 *cfg_cache_entry;
u8 *cfg_find_entry(s32 start, s32 key, s32 pos) {
    s32 n;
    u8 *p;

    if (key == (s32)cfg_cache_key && pos >= cfg_cache_pos) {
        n = pos - cfg_cache_pos;
        p = cfg_cache_entry;
        cfg_cache_pos = pos;
        while (n > 0) {
            p = cfg_skip_entry(p);
            if (*p == 0x1A) {
                return (u8 *)0x80000000;
            }
            n--;
        }
    } else {
        cfg_cache_pos = pos;
        p = cfg_find_section(start, key);
        if (p == (u8 *)0x80000000) {
            return (u8 *)0x80000000;
        }
        do {
            p = cfg_skip_entry(p);
            if (*p == 0x1A) {
                return (u8 *)0x80000000;
            }
        } while (pos-- > 0);
    }
    cfg_cache_entry = p;
    return p;
}

extern s32 cfg_text;

void cfg_set_text(s32 arg0) {
    cfg_text = arg0;
}

extern s32 cfg_section;

void cfg_set_section(u8 *section) {
    cfg_section = (s32)section;
}

extern s32 cfg_section;

s32 cfg_get_section(void) {
    return cfg_section;
}

extern s32 cfg_text;
extern s32 cfg_section;

s32 cfg_section_exists(void) {
    return cfg_find_section(cfg_text, cfg_section) != 0x80000000;
}

extern u8 cfg_value_buffer[256];
u8 * cfg_find_entry(s32 start, s32 key, s32 pos);
/* Finds the token that follows `count` separators after the entry looked up by `key`.
 * Returns ((u8 *)0x80000000) on failure, otherwise cfg_value_buffer after copying the result there. */
u8 *cfg_get_value(s32 key, s32 count) {
    u8 *cur;
    u8 c;

    cur = cfg_find_entry(cfg_text, cfg_section, key);
    if (cur == ((u8 *)0x80000000)) {
        return ((u8 *)0x80000000);
    }

    if (count-- > 0) {
        do {
            cur = skip_blanks(cfg_skip_token(cur));
            c = *cur;
            if (c == 0x1A) {
                return ((u8 *)0x80000000);
            }
            if (!(cfg_filter_char(c) & 0xFF)) {
                return ((u8 *)0x80000000);
            }
        } while (count-- > 0);
    }

    if (cfg_is_sep(*cur) != 0) {
        return ((u8 *)0x80000000);
    }
    if (cfg_copy_value(cur, cfg_value_buffer) == 0) {
        return ((u8 *)0x80000000);
    }
    return cfg_value_buffer;
}

/* Advances through the string from the lookup result skip_count times, then
 * passes the final position to parse_number. Returns 0x80000000 on failure. */
s32 cfg_get_number(s32 table_index, s32 skip_count) {
    u8 *cur;
    u8 c;

    cur = cfg_find_entry(cfg_text, cfg_section, table_index);
    if (cur == (u8 *)0x80000000) {
        return 0x80000000;
    }
    if (skip_count-- > 0) {
        do {
            cur = skip_blanks(cfg_skip_token(cur));
            c = *cur;
            /* 0x1A is the terminator byte */
            if (c == 0x1A) {
                return 0x80000000;
            }
            if (!(cfg_filter_char(c) & 0xFF)) {
                return 0x80000000;
            }
        } while (skip_count-- > 0);
    }
    if (cfg_is_sep(*cur) != 0) {
        return 0x80000000;
    }
    return parse_number(cur);
}

extern void *D_800419A8[];

void func_800417F8(void) {
    svc_register(D_800419A8, 0x80);
}

extern void *file_slot_table[];

void file_register_slots(void) {
    svc_register(file_slot_table, 0x140);
}

extern void *mdec_slot_table[];

void mdec_register_slots(void) {
    svc_register(mdec_slot_table, 0x120);
}

extern void *gpu_slot_table[];

void gpu_register_slots(void) {
    svc_register(gpu_slot_table, 0x1C0);
}

extern void *sound_svc_slot_table[];

void sound_register_slots(void) {
    svc_register(sound_svc_slot_table, 0xA0);
}

extern void *pad_slot_table[];

void pad_register_slots(void) {
    svc_register(pad_slot_table, 0x40);
}

extern void *thread_slot_table[];

void thread_register_slots(void) {
    svc_register(thread_slot_table, 0x100);
}

extern void *frame_slot_table[];

void frame_register_slots(void) {
    svc_register(frame_slot_table, 0x30);
}

