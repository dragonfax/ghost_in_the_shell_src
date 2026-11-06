/* boot: one of boot's own original source files (scripts/objmap.py); part of src/boot/main.c's unit, included there. */

void str_copy(u8 *src, u8 *dst) {
    u8 c;

    while ((c = *src++) != 0) {
        *dst++ = c;
    }
    *dst = 0;
}

/* Concatenates two NUL-terminated strings into dst (dst must have room). */
void str_concat(u8 *first, u8 *second, u8 *dst) {
    u8 c;

    while ((c = *first++) != 0) {
        *dst++ = c;
    }
    while ((c = *second++) != 0) {
        *dst++ = c;
    }
    *dst = 0;
}

/* Copies a NUL-terminated string, upper-casing ASCII letters. */
void str_copy_upper(u8 *src, u8 *dst) {
    u8 c;

    while ((c = *src++) != 0) {
        if ((u32)(c - 'a') < 26) {
            c &= 0xDF;
        }
        *dst++ = c;
    }
    *dst = 0;
}

u8 to_upper(u8 c) {
    u8 r = c;
    if ((u8)(c - 0x61) < 0x1A) {
        r = c & 0xDF;
    }
    return r;
}

/* Compares len bytes of lhs and rhs; returns 1 if they are all equal, else 0. */
s32 mem_equal(s32 len, u8 *lhs, u8 *rhs) {
    s32 equal = 1;

    while (len > 0) {
        if (equal != 1) {
            break;
        }
        if (*lhs != *rhs) {
            equal = 0;
        }
        lhs++;
        len--;
        rhs++;
    }
    return equal;
}

/* Byte copy of size bytes; copies backward when dst is above src so overlapping ranges survive. */
void mem_move(s32 size, void *src, void *dst) {
    u8 *s;
    u8 *d;
    u8 tmp;

    if ((u32)src < (u32)dst) {
        s = (u8 *)src + size;
        d = (u8 *)dst + size;
        if (size > 0) {
            do {
                d--;
                s--;
                size--;
                *d = *s;
            } while (size > 0);
        }
    } else if (size > 0) {
        do {
            tmp = *(u8 *)src;
            src = (u8 *)src + 1;
            size--;
            *(u8 *)dst = tmp;
            dst = (u8 *)dst + 1;
        } while (size > 0);
    }
}

void mem_set(s8 *arg0, s32 arg1, s8 arg2) {
    s32 var_a1;
    s8 *var_a0;

    var_a0 = arg0;
    var_a1 = arg1;
    if (var_a1 > 0) {
        do {
            *var_a0 = arg2;
            var_a1 -= 1;
            var_a0 += 1;
        } while (var_a1 > 0);
    }
}

/* Same code as str_length (s01). */
s32 boot_str_length(u8 *str) {
    s32 len = 0;

    while (*str++ != 0) {
        len++;
    }
    return len;
}

s32 round_up(s32 value, s32 align) {
    s32 biased = value - 1;
    return (biased + align) / align * align;
}

s32 clamp_value(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_a1;

    var_a1 = arg1;
    if (arg0 >= var_a1) {
        var_a1 = arg2;
        if (arg2 >= arg0) {
            var_a1 = arg0;
        }
    }
    return var_a1;
}

/* Reads a 4-byte value from src, most significant byte first (src[3] down to src[0]). */
s32 read_be32(u8 *src) {
    s32 value;
    s32 i;
    u8 *p;
    s32 byte;

    value = 0;
    p = src + 3;
    i = 3;
    do {
        value = value << 8;
        byte = *p;
        p -= 1;
        i -= 1;
        value += byte;
    } while (i >= 0);
    return value;
}

// Reads a little-endian u16 from a byte pointer.
s32 read_le16(u8 *bytes) {
    s32 high = bytes[1];
    s32 value = bytes[0];
    high <<= 8;
    value |= high;
    return value;
}

extern u32 pow10_table[];
/* Writes the decimal digits of val to out, one per table entry, then a NUL. */
void u32_to_decimal(u32 val, s8 *out) {
    s32 digit;
    u32 *pow;
    u32 place;

    pow = pow10_table;
    if (*pow != 0) {
        do {
            place = *pow;
            digit = 0;
            if (val >= place) {
                do {
                    val -= place;
                    digit += 1;
                } while (val >= place);
                *out = digit + '0';
            } else {
                *out = '0';
            }
            pow += 1;
            out += 1;
        } while (*pow != 0);
    }
    *out = 0;
}

extern u8 D_8002DEE7;

void func_80018D60(void) {
    D_8002DEE7 = 1;
}

void func_80018D74(void) {
    D_8002DEE7 = 0;
}

s32 get_event_latch_flag(void) {
    return D_8002DEE7;
}

void wait_next_vsync(s32 arg) {
    s32 temp_s0;

    temp_s0 = get_frame_counter();
    do {

    } while (temp_s0 == get_frame_counter());
}

s32 get_event_latch_flag(void);
void event_flags_clear(void);
void event_flags_set(void);
s32 TestEvent(s32 event);
extern s32 card_sw_timeout_event;
extern s32 card_hw_timeout_event;
extern s32 card_sw_timeout_flag;
extern s32 card_hw_timeout_flag;
/* If get_event_latch_flag reports nothing pending, reset state and latch any
   fired event (card_sw_timeout_event / card_hw_timeout_event) into its flag word. */
void event_latch_task(void) {
    if (get_event_latch_flag() == 0) {
        event_flags_clear();
        if (TestEvent(card_sw_timeout_event) != 0) {
            card_sw_timeout_flag = 1;
            event_flags_set();
        }
        if (TestEvent(card_hw_timeout_event) != 0) {
            card_hw_timeout_flag = 1;
            event_flags_set();
        }
    }
}

extern s32 card_hw_timeout_flag;

s32 card_take_hw_timeout(void) {
    s32 temp_v0;

    temp_v0 = card_hw_timeout_flag;
    card_hw_timeout_flag = 0;
    return temp_v0;
}

extern s32 card_sw_timeout_flag;

s32 card_take_sw_timeout(void) {
    s32 temp_v0;

    temp_v0 = card_sw_timeout_flag;
    card_sw_timeout_flag = 0;
    return temp_v0;
}

extern s32 card_sw_done_event;
extern s32 card_sw_error_event;
extern s32 card_sw_new_card_event;
s32 card_poll_status(void) {
    if (TestEvent(card_sw_done_event) == 1) {
        return 1;
    }
    if (TestEvent(card_sw_error_event) == 1) {
        return 2;
    }
    if (card_take_sw_timeout() != 0) {
        return 3;
    }
    return (TestEvent(card_sw_new_card_event) == 1) * 4;
}

extern s32 card_sw_done_event;
extern s32 card_sw_error_event;
extern s32 card_sw_new_card_event;

void card_clear_sw_events(void) {
    TestEvent(card_sw_done_event);
    TestEvent(card_sw_error_event);
    card_take_sw_timeout();
    TestEvent(card_sw_new_card_event);
}

void func_80018F48(void) {
    card_clear_sw_events();
}

extern s32 card_hw_done_event;
extern s32 card_hw_error_event;
extern s32 card_hw_new_card_event;
/* Same code as card_poll_status (boot). */
s32 card_poll_result(void) {
    if (TestEvent(card_hw_done_event) == 1) {
        return 1;
    }
    if (TestEvent(card_hw_error_event) == 1) {
        return 2;
    }
    if (card_take_hw_timeout() != 0) {
        return 3;
    }
    return (TestEvent(card_hw_new_card_event) == 1) * 4;
}

extern s32 card_hw_done_event;
extern s32 card_hw_error_event;
extern s32 card_hw_new_card_event;

void card_clear_hw_events(void) {
    TestEvent(card_hw_done_event);
    TestEvent(card_hw_error_event);
    card_take_hw_timeout();
    TestEvent(card_hw_new_card_event);
}

void func_80019034(void) {
    card_clear_hw_events();
}

extern u8 D_8002DEE0[];
void str_copy(u8 *src, u8 *dst);
void card_init(s32 port, s32 arg1, void *info, s32 arg3) {
    s32 slot;
    s32 block;
    u8 *out;

    out = info;
    slot = clamp_value(port, 0, 1);
    block = clamp_value(arg1, 0, 3);
    str_copy(D_8002DEE0, out);
    out[2] = slot + '0';
    out[3] = block + '0';
    str_copy((u8 *)arg3, out + 5);
}

s32 open(char *name, u32 flags);
s32 file_open(char *name, u32 flags) {
    return open(name, flags);
}

s32 write(s32 fd, void *buf, s32 len);
s32 file_write(s32 fd, void *buf, s32 len) {
    return write(fd, buf, len);
}

s32 read(s32 arg0, void *arg1, s32 arg2);
s32 file_read(s32 arg0, void *arg1, s32 arg2) {
    return read(arg0, arg1, arg2);
}

s32 card_file_first(void *name, s32 dir) {
    return firstfile(name, dir);
}

s32 erase(char *info);
s32 card_file_erase(char *info) {
    return erase(info);
}

extern void card_init(s32 port, s32 arg1, void *info, s32 arg3);
extern void *nextfile(void *info);
extern char D_80018000[];
s32 card_file_count(s32 port, s32 arg1) {
    u8 info[0x20];
    u8 entry[0x28];
    s32 count;
    void *found;

    count = 0;
    FAKE_OPAQUE(count);
    card_init(port, arg1, info, (s32)D_80018000);
    if (card_file_first(info, (s32)entry) == 0) {
        count += 1;
        do {
            found = nextfile(entry);
            count += 1;
        } while (found == entry);
        count -= 1;
    }
    return count;
}

s32 card_free_slots(s32 port, s32 arg1) {
    return 0xF - card_file_count(port, arg1);
}

s32 card_poll_status(void);
s32 card_wait_result(void) {
    s32 i;
    s32 result;

    i = 0;
    do {
        result = card_poll_status();
        if (result != 0) {
            i += 1;
            return result;
        }
        i += 1;
        wait_next_vsync(0);
        result = 5;
    } while (i < 0xB4);
    return result;
}

s32 card_poll_result(void);
s32 card_wait_async(void) {
    s32 attempt;
    s32 result;

    /* Poll card_poll_result up to 0x4000 times; return its first nonzero result, or 2 on timeout. */
    for (attempt = 0; attempt < 0x4000; attempt++) {
        result = card_poll_result();
        if (result != 0) {
            return result;
        }
    }
    return 2;
}

s32 card_info_slot(s32 arg0, s32 arg1) {
    return _card_info((arg0 * 0x10) + arg1);
}

s32 card_clear_slot(s32 arg0, s32 arg1) {
    return _card_clear((arg0 * 0x10) + arg1);
}

s32 card_load_slot(s32 arg0, s32 arg1) {
    return _card_load((arg0 * 0x10) + arg1);
}

/* Polls memory card (port, slot) info up to 0xB4 times, pausing between polls; falls back to card_wait_result when the card reports a status. */
s32 card_info_wait(s32 port, s32 slot) {
    s32 attempts = 0;

    while (card_info_slot(port, slot) == 0) {
        if (attempts < 0xB4) {
            attempts++;
            wait_next_vsync(0);
        } else {
            return 3;
        }
    }
    return card_wait_result();
}

s32 card_clear_wait(s32 arg0, s32 arg1) {
    s32 retries;

    retries = 0;
    while (card_clear_slot(arg0, arg1) == 0) {
        if (retries < 0xB4) {
            retries++;
            wait_next_vsync(0);
        } else {
            return 5;
        }
    }
    return card_wait_async();
}

s32 card_load_retry(s32 port, s32 slot);

/* Same code as card_clear_wait (boot). */
s32 card_load_retry(s32 arg0, s32 arg1) {
    s32 retries;

    retries = 0;
    while (card_load_slot(arg0, arg1) == 0) {
        if (retries < 0xB4) {
            retries++;
            wait_next_vsync(0);
        } else {
            return 5;
        }
    }
    return card_wait_result();
}

extern u8 card_recheck_flags[][4];
extern u8 card_fail_flags[][4];

/* Checks memory card (port, slot): polls its info, clears it when it is new
 * and runs card_load_retry, retrying up to three times. Returns 0 when ready,
 * negative codes (-2..-5) on errors; card_recheck_flags flags slots to recheck,
 * card_fail_flags slots that failed. */
s32 card_check_slot(s32 port, s32 slot) {
    s32 retries = 3;
    s32 res;

retry:
    res = card_info_wait(port, slot);
    if (card_recheck_flags[port][slot] != 0 && res == 1) {
        res = 4;
    }
    card_recheck_flags[port][slot] = 0;
    switch (res) {
    case 4:
        res = card_clear_wait(port, slot);
        switch (res) {
        case 1:
            do { /* loop note: register priority */
                res = card_load_retry(port, slot);
            } while (0);
            switch (res) {
            case 1:
                card_fail_flags[port][slot] = 0;
                return 0;
            case 3:
                return -2;
            case 4:
                if (--retries < 0) {
                    card_fail_flags[port][slot] = 1;
                    return -4;
                }
                card_recheck_flags[port][slot] = 1;
                goto retry;
            case 2:
            default:
                card_recheck_flags[port][slot] = 1;
                return -3;
            }
        case 3:
            card_recheck_flags[port][slot] = 1;
            return -2;
        case 2:
            card_recheck_flags[port][slot] = 1;
            return -3;
        default:
            goto fail;
        }
    case 3:
        return -2;
    case 1:
        return card_fail_flags[port][slot] ? -4 : 0;
    case 2:
        card_recheck_flags[port][slot] = 1;
        return -3;
    default:
    fail:
        card_recheck_flags[port][slot] = 1;
        return -5;
    }
}

void InitCARD(s32 pad_enable);
void StartCARD(void);
void _bu_init(void);
void _card_auto(s32 flag);
void ChangeClearPAD(s32 flag);
s32 EnterCriticalSection(void);
void ExitCriticalSection(void);
void EnableEvent(s32 event);
extern u8 card_subsystem_ready_flag;
void frame_task_add_small(void *callback, s32 param);
/* One-time init: memory card and pad setup, then open and enable the
 * card and pad events and clear the per-slot status bytes. */
void card_subsystem_init(void) {
    s32 entry;
    u8 *ready;
    u8 *status;
    u8 *status_end;
    u8 *status_p;
    u8 *ready_p;
    u8 set;

    if (card_subsystem_ready_flag != 1) {
        card_subsystem_ready_flag = 1;
        InitCARD(1);
        StartCARD();
        _bu_init();
        _card_auto(0);
        ChangeClearPAD(0);
        EnterCriticalSection();
        card_sw_done_event = OpenEvent(0xF4000001, 4, 0x2000, 0);
        card_sw_error_event = OpenEvent(0xF4000001, 0x8000, 0x2000, 0);
        card_sw_timeout_event = OpenEvent(0xF4000001, 0x100, 0x2000, 0);
        card_sw_new_card_event = OpenEvent(0xF4000001, 0x2000, 0x2000, 0);
        card_hw_done_event = OpenEvent(0xF0000011, 4, 0x2000, 0);
        card_hw_error_event = OpenEvent(0xF0000011, 0x8000, 0x2000, 0);
        card_hw_timeout_event = OpenEvent(0xF0000011, 0x100, 0x2000, 0);
        card_hw_new_card_event = OpenEvent(0xF0000011, 0x2000, 0x2000, 0);
        EnableEvent(card_sw_done_event);
        EnableEvent(card_sw_error_event);
        EnableEvent(card_sw_timeout_event);
        EnableEvent(card_sw_new_card_event);
        EnableEvent(card_hw_done_event);
        EnableEvent(card_hw_error_event);
        EnableEvent(card_hw_timeout_event);
        EnableEvent(card_hw_new_card_event);
        ExitCriticalSection();
        entry = 0;
        set = 1;
        status = card_fail_flags[0];
        ready = card_recheck_flags[0];
        do {
            status_p = status;
            ready_p = ready;
            status_end = status + 4;
            do {
                *ready_p = set;
                *status_p = 0;
                status_p++;
                ready_p++;
            } while ((s32) status_p < (s32) status_end);
            status += 4;
            entry++;
            ready += 4;
        } while (entry <= 0);
        frame_task_add_small(event_latch_task, 0);
    }
}

extern u8 card_subsystem_ready_flag;
extern s32 card_sw_done_event;
extern s32 card_sw_error_event;
extern s32 card_sw_timeout_event;
extern s32 card_sw_new_card_event;
extern s32 card_hw_done_event;
extern s32 card_hw_error_event;
extern s32 card_hw_timeout_event;
extern s32 card_hw_new_card_event;

void card_subsystem_shutdown(void) {
    if (card_subsystem_ready_flag != 0) {
        card_subsystem_ready_flag = 0;
        EnterCriticalSection();
        CloseEvent(card_sw_done_event);
        CloseEvent(card_sw_error_event);
        CloseEvent(card_sw_timeout_event);
        CloseEvent(card_sw_new_card_event);
        CloseEvent(card_hw_done_event);
        CloseEvent(card_hw_error_event);
        CloseEvent(card_hw_timeout_event);
        CloseEvent(card_hw_new_card_event);
        ExitCriticalSection();
    }
}

s32 card_check_slot(s32 port, s32 slot);
void card_init(s32 port, s32 arg1, void *info, s32 arg3);
extern char D_80018000[];
s32 card_find_entry_checked(s32 port, s32 mode, u8 *src, s32 extra) {
    u8 card_info[0x20];

    if (card_check_slot(port, mode) != 0) {
        return 0;
    }
    card_init(port, mode, card_info, (s32)D_80018000);
    str_copy(src, &card_info[5]);
    return card_file_first(card_info, extra);
}

s32 card_find_entry(s32 port, s32 arg1, u8 *src, s32 arg3) {
    u8 card_buf[0x20];

    card_init(port, arg1, card_buf, (s32)D_80018000);
    str_copy(src, card_buf + 5);
    return card_file_first(card_buf, arg3);
}

void *card_next_entry(void *info) {
    return nextfile(info);
}

char D_80018000[4] = "*";

/* The empty file name card_init appends: an array, not a "" literal, which cc1 would share with the later
 * one (the original's objects each had their own). */
static const char card_no_file_name[] = "";
/* Formats the memory card in port/slot and flags the slot for a recheck; 1 when the format succeeded. */
s32 card_format_slot(s32 port, s32 slot) {
    u8 info[0x20];
    s32 result;

    card_init(port, slot, info, (s32)card_no_file_name);
    format((char *)info);
    result = card_wait_async();
    card_recheck_flags[port][slot] = 1;
    return result == 1;
}

s32 card_close(s32 arg0) {
    do {

    } while (close(arg0) != arg0);
    return arg0;
}

extern s32 read_fd(s32 fd, void *buf, s32 len) __asm__("file_read");
extern s32 read_fd(s32 fd, void *buf, s32 len) __asm__("file_read");
s32 card_read_file(s32 port, s32 mode, u8 *src, u8 *buf, s32 size, s32 offset, s32 keep_open) {
    u8 name[0x20];
    u8 info[0x28];
    u8 tail[0x80];
    s32 res;
    s32 fd;
    s32 retries;
    s32 chunk;
    s32 rem;
    s32 flags;

    res = card_find_entry(port, mode, src, (s32)info);
    if (res != (s32)info) {
        return -1;
    }
    if (size == 0) {
        return 0;
    }
    card_init(port, mode, name, (s32)src);
    if (keep_open != 0) {
        flags = 0x8001;
        size = ((size + 0x80) / 0x80) * 0x80;
    } else {
        flags = 1;
    }
    fd = file_open(name, flags);
    if (fd == -1) {
        return -3;
    }
    lseek(fd, offset, 0);
    retries = 0xB4;
    if (keep_open == 0) {
        chunk = (size / 0x80) * 0x80;
        if (chunk == 0 || (res = read_fd(fd, buf, chunk), res == chunk)) {
            rem = size - chunk;
            buf += chunk;
            if (rem != 0) {
                lseek(fd, offset + chunk, 0);
                if (read_fd(fd, tail, 0x80) != 0x80) {
                    res = 0;
                } else {
                    mem_move(rem, tail, buf);
                    res = chunk + rem;
                }
            }
        } else {
            res = 0;
        }
    } else {
        do {
            res = read_fd(fd, buf, size);
            retries--;
        } while (res == 0 && retries > 0);
        if (retries <= 0) {
            return -3;
        }
    }
    if (keep_open != 0) {
        return fd;
    }
    card_close(fd);
    if (res <= 0) {
        return -3;
    }
    return res;
}

/* card_read_file, unless card_check_slot reports the slot unusable. */
void card_read_file_checked(s32 port, s32 mode, u8 *src, u8 *buf, s32 size, s32 offset, s32 keep_open) {
    if (card_check_slot(port, mode) == 0) {
        card_read_file(port, mode, src, buf, size, offset, keep_open);
    }
}

extern s32 lseek(s32 fd, s32 off, s32 whence);
s32 card_write_data(s32 port, s32 arg1, s32 arg2, void *buf, s32 len, s32 offset, s32 retry) {
    u8 name[0x20];
    u8 info[0x28];
    s32 fd;
    s32 res;
    s32 flags;

    if ((u8 *)card_find_entry(port, arg1, (u8 *)arg2, (s32)info) != info) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }
    card_init(port, arg1, name, arg2);
    if (retry != 0) {
        flags = 0x8003;
        len = (len + 0x80) / 0x80 * 0x80;
    } else {
        flags = 3;
    }
    fd = file_open(name, flags);
    if (fd == -1) {
        return -3;
    }
    lseek(fd, offset, 0);
    res = file_write(fd, buf, len);
    if (retry != 0) {
        for (port = 0xB4; res == 0; port--) {
            if (port <= 0) {
                return -3;
            }
            res = file_write(fd, buf, len);
        }
        if (port <= 0) {
            return -3;
        }
        if (retry != 0) {
            return fd;
        }
    }
    card_close(fd);
    if (res > 0) {
        return res;
    }
    return -3;
}

s32 card_write_data_checked(s32 port, s32 arg1, s32 arg2, void *buf, s32 len, s32 offset, s32 retry) {
    s32 res;

    res = card_check_slot(port, arg1);
    if (res == 0) {
        return card_write_data(port, arg1, arg2, buf, len, offset, retry);
    }
    return res;
}

/* Opens a card file sized for `bytes` (rounded up to 8 KB blocks).
   Returns 0 on success, -3 if the open failed. */
s32 card_create_file(s32 port, s32 arg1, s32 arg2, s32 bytes) {
    u8 info[0x20];
    s32 result;
    s32 size;
    s32 fd;

    result = 0;
    card_init(port, arg1, info, arg2);
    size = bytes + 0x1FFF;
    if (size < 0) {
        size = bytes + 0x3FFE;
    }
    bytes = size >> 13;
    fd = file_open(info, (bytes << 16) | 0x200);
    if (fd == -1) {
        result = -3;
        close(-1);
    } else {
        card_close(fd);
    }
    return result;
}

s32 card_check_slot(s32 port, s32 slot);
s32 card_create_file(s32 a, s32 b, s32 c, s32 d);
/* Forward four arguments to card_create_file unless card_check_slot reports
   non-zero. */
void card_create_checked(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (card_check_slot(arg0, arg1) == 0) {
        card_create_file(arg0, arg1, arg2, arg3);
    }
}

void card_init(s32 port, s32 arg1, void *info, s32 arg3);
s32 card_erase_file(s32 port, s32 arg1, s32 arg2) {
    u8 card_info[0x48];

    card_init(port, arg1, card_info, arg2);
    return card_file_erase(card_info);
}

s32 card_erase_checked(s32 port, s32 arg1, s32 arg2) {
    if (card_check_slot(port, arg1) != 0) {
        return 0;
    }
    return card_erase_file(port, arg1, arg2);
}

s32 card_poll_status(void);
/* Polls card_poll_status (a ready check) up to 0x960 times when wait is set, calling wait_next_vsync(0) between polls. */
void card_poll_event(s32 wait) {
    s32 retries;

    if (wait != 0) {
        retries = 0x960;
        while (card_poll_status() == 0) {
            wait_next_vsync(0);
            retries--;
            if (retries <= 0) {
                card_poll_status();
                return;
            }
        }
    } else {
        card_poll_status();
    }
}

s32 unpex_last_word_get(void);
s32 func_80022510(void);
void exec_report(void) {
    printf("LAST:%x\n", unpex_last_word_get());
    printf("EXEC:%x\n", func_80022510());
}

void exec_report(void);
void ResetCallback(void);
void frame_tasks_reset(void);
void sched_init(void);
void func_8001B15C(void);
void snd_volume_set(s32 arg);
void func_80021F10(void);
void pad_setup(void);
void card_subsystem_init(void);
void spufunc_init(void);
void sound_init(s32 unused0, s32 unused1);
void cd_init(void);
void sysini_load(void);
void display_setup(void);
void dct_reset(s32 mode);
void geom_init(void);
/* Boot init: runs the subsystem setup calls in order. */
void boot_early_init(void) {
    exec_report();
    ResetCallback();
    frame_tasks_reset();
    sched_init();
    func_8001B15C();
    snd_volume_set(0xC8);
    func_80021F10();
    pad_setup();
    card_subsystem_init();
    spufunc_init();
    sound_init(0, 0x18);
    cd_init();
    sysini_load();
    display_setup();
    dct_reset(0);
    geom_init();
}

void vsync_callback_clear(void);
void sched_shutdown(void);
/* Same code as sound_stage_stop (s01). */
void system_shutdown(void) {
    vsync_callback_clear();
    card_subsystem_shutdown();
    sched_shutdown();
}

s32 svc_unimplemented(void) {
    return 0;
}

void *get_exec_request(void);
void exec_set_code(s32 arg0);
s32 exec_by_name(s32 flags, char *name);
/* Reads the boot exec request at exec_request, sets the exec_code flag to 0, and runs the named exec if it has a name. */
void boot_exec_request(void) {
    BootExecRequest *request;

    request = get_exec_request();
    exec_set_code(0);
    if (request->name != NULL) {
        exec_by_name(request->flags, request->name);
    }
}

s32 exec_get_index(void);
s32 sys_get_gamemode(void);
s32 *get_exec_table(void);
void exec_set_index(s32 arg0);
void exec_set_program(void) {
    struct ExecProgram *entry;
    s32 idx;

    for (;;) {
        idx = exec_get_index();
        if (idx < 0) {
            if (sys_get_gamemode() == 1) {
                return;
            }
            idx = 0;
        }
        exec_set_code(idx);
        idx = clamp_value(idx, 0, 0x5F);
        entry = (struct ExecProgram *)((u8 *)get_exec_table() + idx * 8);
        if (entry->name == NULL) {
            printf("EXEC: No Program Name\n");
        }
        exec_set_index(0);
        exec_by_name(entry->flags, entry->name);
    }
}

extern s32 boot_ready_flag;

void boot_flag_clear(void) {
    boot_ready_flag = 0;
}

extern s32 boot_ready_flag;

void boot_flag_set(void) {
    boot_ready_flag = 1;
}

extern s32 boot_ready_flag;

s32 boot_flag_get(void) {
    return boot_ready_flag;
}

void func_8001A404(void) {
    boot_flag_set();
}

void main(void) {
    boot_early_init();
    boot_init();
    func_8001A404();
    boot_exec_request();
    exec_set_program();
    system_shutdown();
    ResetGraph(3);
    CdFlush();
    boot_psdemo();
}

s32 func_8001A48C(void) {
    return 0x300;
}

extern u8 sys_root_path[];
s32 boot_str_length(u8 *str);
void sys_set_root(u8 *path) {
    u8 *name;
    u8 *p;

    p = path;
    name = path;
    while (*p != 0) {
        if (*p == ':') {
            name = p + 1;
        }
        p++;
    }
    if (*name == '\\') {
        name++;
    }
    p = sys_root_path;
    *p = '\\';
    p++;
    if (boot_str_length(name) >= 0x3F) {
        p--;
        FAKE_OPAQUE(p);
        *p = '\\';
        p[1] = 0;
        printf("SYSTEM ROOT: Too Long Path name\n");
        return;
    }
    str_copy(name, p);
    p--;
    p = p + boot_str_length(p);
    p--;
    if (*p == '\\') {
        *p = 0;
    }
}

/* Same code as get_file_name (s01). */
s32 *get_sys_root_path(void) {
    return (s32 *) &sys_root_path;
}

extern s32 sys_country;

s32 sys_get_country(void) {
    return sys_country;
}

extern s32 sys_country;

void sys_set_country(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (var_a0 >= 4) {
        var_a0 = 0;
    }
    sys_country = var_a0;
}

extern s32 sys_video_mode;
void sys_set_tick_rate(s32 flag);
void sys_set_video_mode(s32 mode) {
    sys_set_tick_rate(mode);
    sys_video_mode = mode;
}

extern s32 sys_video_mode;

s32 sys_is_pal(void) {
    s32 var_v0;

    var_v0 = 0;
    if (sys_video_mode != 0) {
        var_v0 = sys_video_mode == 1;
    }
    return var_v0;
}

extern s32 sys_gamemode;

void sys_set_gamemode(s32 arg0) {
    sys_gamemode = arg0;
}

extern s32 sys_gamemode;

s32 sys_get_gamemode(void) {
    return sys_gamemode;
}

extern s32 sys_warning;

void sys_set_warning(s32 arg0) {
    sys_warning = arg0;
}

extern s32 sys_warning;

s32 sys_get_warning(void) {
    return sys_warning;
}

extern MovieSlot movie_table[64];
/* Returns the address of the movie table (8 bytes per movie). */
void *get_movie_table(void) {
    return movie_table;
}

extern struct ExecProgram exec_table[96];
/* Same code as get_file_name (s01). */
s32 *get_exec_table(void) {
    return (s32 *) exec_table;
}

extern BootExecRequest exec_request;
/* Same code as get_movie_table (boot). */
void *get_exec_request(void) {
    return &exec_request;
}

extern u8 ramp_state[0x1000];
/* Same code as ramp_get_state (s08). */
s32 *get_ramp_state(void) {
    return (s32 *) ramp_state;
}

#define SVC_TABLE_ADDR 0x80010000

/* Copies a zero-terminated list of service functions into the service table from slot first_svc. */
void svc_register(void *fns, s32 first_svc) {
    s32 *src = fns;
    u8 *table;
    s32 slot = first_svc;
    s32 offset;

    while (*src != 0) {
        slot++;
        offset = slot * 4 - 4;
        table = (u8 *)SVC_TABLE_ADDR;
        *(s32 *)(table + offset) = *src++;
    }
}

void func_8001A6EC(void) {
}

extern s32 exec_index;

void exec_set_index(s32 arg0) {
    exec_index = arg0;
}

extern s32 exec_index;

s32 exec_get_index(void) {
    return exec_index;
}

extern struct ExecProgram exec_table[96];
/* Returns the 8-byte entry in exec_table selected by clamp_value(index, 0, 0x5F). */
void *exec_get_entry(s32 index) {
    return &exec_table[clamp_value(index, 0, 0x5F)];
}

extern s32 exec_code;

void exec_set_code(s32 arg0) {
    exec_code = arg0;
}

extern s32 exec_code;

s32 exec_get_code(void) {
    return exec_code;
}

extern u8 D_80032364[24];
/* Same code as func_800CC7A8 (s12). */
u8 *cardname_buf_get(void) {
    return D_80032364;
}

extern MovieSlot movie_table[64];
/* Returns the 8-byte entry for movie_no in movie_table, or NULL when movie_no is out of range. */
void *movie_get_entry(s32 movie_no) {
    if (movie_no < 0x40) {
        return &movie_table[movie_no];
    }
    printf("MOVIE NUMBER ERROR\n");
    return NULL;
}

s32 sys_get_settings(void) {
    return 0x80014000;
}

void func_8001A7C8(void) {
}

void cache_flush_critical(void) {
    EnterCriticalSection();
    FlushCache();
    ExitCriticalSection();
}

extern s32 frame_tasks_lock_flag;

void frame_tasks_lock(void) {
    frame_tasks_lock_flag = 1;
}

extern s32 frame_tasks_lock_flag;

void frame_tasks_unlock(void) {
    frame_tasks_lock_flag = 0;
}

extern u32 frame_counter;
/* Same code as get_player_status (s01). */
s32 get_frame_counter(void) {
    return frame_counter;
}

extern s32 frame_tick_period;
void sys_set_tick_rate(s32 flag) {
    s32 value = 5;

    if (flag == 0) {
        value = 6;
    }
    frame_tick_period = value;
}

extern u32 frame_counter; /* free-running counter, folded back into 0..7 past 2^30 */
extern u32 frame_sec_ticks; /* ticks since the last second */
extern u32 frame_seconds; /* whole seconds */
void frame_clock_tick(void) {
    u32 counter;
    u32 ticks;

    counter = frame_counter + 1;
    frame_counter = counter;
    if (counter > 0x40000000U) {
        frame_counter = counter >> 29;
    }

    ticks = frame_sec_ticks + 1;
    frame_sec_ticks = ticks;
    if (ticks >= (u32)frame_tick_period) {
        frame_sec_ticks = 0;
        frame_seconds += 1;
    }
}

/* Waits for `ticks` changes of the free-running counter (get_frame_counter).
 * A negative count returns the whole-seconds counter instead. */
s32 frame_wait_ticks(s32 ticks) {
    s32 prev;
    s32 now;

    prev = get_frame_counter();
    if (ticks < 0) {
        return frame_seconds;
    }
    do {
        do {
            now = get_frame_counter();
        } while (prev == now);
        ticks -= 1;
        prev = now;
    } while (ticks >= 0);
    return 0;
}

/* Ticks each slot's counter (unk_04); when it passes the period (unk_06),
   resets it and calls the slot's callback. */
void frame_tasks_run(FrameTaskSlot *slot, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++, slot++) {
        if (slot->callback != NULL) {
            if (slot->interval < ++slot->frame_counter) {
                slot->frame_counter = 0;
                slot->callback();
            }
        }
    }
}

extern FrameTaskSlot frame_task_table_small[8];
extern FrameTaskSlot frame_task_table[16];
void frame_tasks_run(FrameTaskSlot *slot, s32 count);
/* Runs frame_clock_tick, then, while frame_tasks_lock_flag is clear, passes the two tables frame_task_table_small (size 8) and frame_task_table (size 0x10) to frame_tasks_run, which runs each slot whose counter passes its period. */
void vsync_callback(void) {
    frame_clock_tick();
    if (frame_tasks_lock_flag == 0) {
        frame_tasks_run(frame_task_table_small, 8);
        frame_tasks_run(frame_task_table, 0x10);
    }
}

/* Clears the two record tables (16 slots at frame_task_table, 8 at frame_task_table_small), then the flag at frame_counter. */
void frame_tasks_clear(void) {
    s32 offset;

    offset = 0;
    do {
        *(s32 *)((u8 *)frame_task_table + offset) = 0;
        *(s16 *)((u8 *)&frame_task_table[0].frame_counter + offset) = 0;
        *(s16 *)((u8 *)&frame_task_table[0].interval + offset) = 0;
        offset += 8;
    } while (offset < 0x80);

    offset = 0;
    do {
        *(s32 *)((u8 *)frame_task_table_small + offset) = 0;
        *(s16 *)((u8 *)&frame_task_table_small[0].frame_counter + offset) = 0;
        *(s16 *)((u8 *)&frame_task_table_small[0].interval + offset) = 0;
        offset += 8;
    } while (offset < 0x40);

    frame_tasks_unlock();
    frame_counter = 0;
}

s32 callback_table_add(s32 *table, void *callback, s32 param, s32 count) {
    s32 found = -1;
    s32 i;

    frame_tasks_lock();
    for (i = 0; i < count; i++, table += 2) {
        CallbackSlot *slot = (CallbackSlot *)table;
        if (slot->callback == 0) {
            found = i;
            slot->callback = (s32)callback;
            slot->unk_04 = 0;
            slot->param = param;
            break;
        }
    }
    frame_tasks_unlock();
    return found;
}

extern FrameTaskSlot frame_task_table[16];
s32 callback_table_add(s32 *table, void *callback, s32 param, s32 count);
/* Registers callback with param in a free slot (16 of them) of the table at frame_task_table. */
void frame_task_add(void *callback, s32 param) {
    callback_table_add((s32 *)frame_task_table, callback, param, 0x10);
}

extern FrameTaskSlot frame_task_table_small[8];
/* Registers callback with param in a free slot (8 of them) of the table at frame_task_table_small. */
void frame_task_add_small(void *callback, s32 param) {
    callback_table_add((s32 *)frame_task_table_small, callback, param, 8);
}

s32 frame_task_slot_clear(FrameTaskSlot *table, s32 index) {
    table = (FrameTaskSlot *)((u8 *)table + index * 8);
    table->callback = 0;
    table->frame_counter = 0;
    table->interval = 0;
    return 1;
}

/* Indices 0..15 are valid. A negative index refreshes every slot of
   frame_task_table; otherwise only that slot. Returns 1, or -1 for a bad index. */
s32 frame_task_remove(s32 index) {
    s32 i;

    if (index >= 0x10) {
        return -1;
    }
    frame_tasks_lock();
    if (index < 0) {
        for (i = 0; i < 0x10; i++) {
            frame_task_slot_clear(frame_task_table, i);
        }
    } else {
        frame_task_slot_clear(frame_task_table, index);
    }
    frame_tasks_unlock();
    return 1;
}

/* Clears slot `index` (0..7) of the 8-entry table at frame_task_table_small, bracketed by
 * frame_tasks_lock / frame_tasks_unlock (not identified). Returns 1, or -1 if index is out of range. */
s32 frame_task_remove_small(s32 index) {
    if ((u32)index >= 8) {
        return -1;
    }
    frame_tasks_lock();
    frame_task_slot_clear(frame_task_table_small, index);
    frame_tasks_unlock();
    return 1;
}

void VSyncCallback(void (*func)(void));
void frame_tasks_clear(void);
void frame_tasks_reset(void) {
    VSyncCallback(NULL);
    frame_tasks_clear();
    VSyncCallback(vsync_callback);
}

/* Same code as pending_grid_reset_saved (s01). */
void vsync_callback_clear(void) {
    VSyncCallback(0);
}

void graph_reset(s32 arg0) {
    ResetGraph(1);
    if (arg0 == 0) {
        SetDispMask(0);
    }
}

s32 PutDispEnv(void *env);
/* Slot 0x1C1 (slot_put_disp_env) target: copies the DISPENV, runs the check
 * sys_is_pal, then hands the original DISPENV to PutDispEnv. */
void put_disp_env_checked(void *env) {
    DispEnv local;

    local = *(DispEnv *)env;
    if (sys_is_pal() == 1) {
        local.bytes[18] = 1;
    }
    PutDispEnv(env);
}

void *PutDrawEnv(void *env);
void *draw_env_put(void *env) {
    return PutDrawEnv(env);
}

s32 GetGraphType();
void *graph_buf_init(GraphBuf *buf, s32 x, s32 y, s32 a3, s32 a4) {
    s32 one = 1;

    buf->x = x;
    buf->y = y;
    buf->x2 = x;
    buf->y2 = y;
    buf->unk4 = a3;
    buf->unk0C = 0;
    buf->unk0E = 0;
    buf->unk10 = 0;
    buf->unk12 = 0;
    buf->unk19 = 0;
    buf->unk1A = 0;
    buf->unk1B = 0;
    buf->unk16 = one;
    buf->unk6 = a4;
    if (a4 != 0x1E0) {
        buf->unk17 = one;
    } else {
        buf->unk17 = 0;
    }
    buf->unk18 = 0;
    if (GetGraphType(one) != 1) {
        GetGraphType();
    }
    buf->unk14 = 0xA;
    return buf;
}

/* Fills a DispRect with three s16 values (a, b, c) and d (stored at 0x06); clears the rest, sets 0x100x0xF0 at 0x0C/0x0E. Returns rec. */
DispRect *disp_rect_init(DispRect *rec, s32 a, s32 b, s32 c, s32 d) {
    rec->unk_00 = a;
    rec->unk_02 = b;
    rec->unk_04 = c;
    rec->screen_x = 0;
    rec->screen_y = 0;
    rec->screen_width = 0x100;
    rec->screen_height = 0xF0;
    rec->unk_10 = 0;
    rec->unk_11 = 0;
    rec->flag = 0;
    rec->unk_06 = d;
    return rec;
}

DispRect *disp_rect_init_mode(DispRect *rec, s32 a, s32 b, s32 c, s32 d) {
    DispRect *result;

    result = disp_rect_init(rec, a, b, c, d);
    rec->flag = 0;
    if (sys_is_pal() == 1) {
        rec->flag = 1;
    }
    return result;
}

void graph_buf_init_wrap(GraphBuf *buf, s32 x, s32 y, s32 a3, s32 a4) {
    graph_buf_init(buf, x, y, a3, a4);
}

void sched_lock(void);
void sched_unlock(void);
void SetVideoMode(s32 mode);
void SetGraphDebug(s32 level);
extern u8 display_setup_done;
/* One-time display setup: runs once, then latches display_setup_done. */
void display_setup(void) {
    if (display_setup_done == 0) {
        sched_lock();
        SetVideoMode(sys_is_pal());
        frame_wait_ticks(0);
        ResetGraph(0);
        SetGraphDebug(0);
        SetDispMask(0);
        display_setup_done = 1;
        sched_unlock();
    }
}

void snd_volume_table_build(s32 unk_a0, s32 unk_a1) {
    s32 *table;
    s32 *cur;
    s32 level;
    s32 scale;
    s32 i;

    table = (s32 *)unk_a1;
    cur = table;
    level = clamp_value(unk_a0, 0, 0xFF);
    i = 0;
    do {
        FAKE_OPAQUE(i);
        scale = level * 0x7F;
        *cur = i * scale / 32385;
        i++;
        cur++;
    } while (i < 0x80);
    *table = 0;
}

extern s32 snd_volume_table[128];
void snd_volume_table_build(s32 unk_a0, s32 unk_a1);
/* unk_a0 is passed through in $a0 unchanged; only $a1 is set here. */
void snd_volume_set(s32 unk_a0) {
    snd_volume_table_build(unk_a0, (s32)snd_volume_table);
}

extern s32 cd_volume_table[128];
/* Same code as snd_volume_set (boot). */
void func_8001B0A8(s32 unk_a0) {
    snd_volume_table_build(unk_a0, (s32)cd_volume_table);
}

s32 table_get(s32 index, s32 *table) {
    return table[index];
}

/* unk_a0 is passed through in $a0 unchanged; only $a1 is set here. */
s32 snd_volume_lookup(s32 unk_a0) {
    return table_get(unk_a0, snd_volume_table);
}

/* unk_a0 is passed through in $a0 unchanged; only $a1 is set here. */
s32 cd_volume_lookup(s32 unk_a0) {
    return table_get(unk_a0, cd_volume_table);
}

void snd_volume_max(void) {
    snd_volume_set(0xFF);
    func_8001B0A8(0xFF);
}

/* Same code as fn_800C0B80 (s01). */
void func_8001B15C(void) {
    snd_volume_max();
}

extern s32 spu_busy_flag;

void spu_busy_set(void) {
    spu_busy_flag = 1;
}

extern s32 spu_busy_flag;

void spu_busy_clear(void) {
    spu_busy_flag = 0;
}

extern s32 spu_busy_flag;

s32 spu_busy_get(void) {
    return spu_busy_flag;
}

extern s32 reverb_mode;
extern s32 reverb_pending;
void SpuSetReverb(s32 on);
void SpuSetReverbModeParam(SpuReverbAttr *attr);
void SpuSetReverbDepth(SpuReverbAttr *attr);
void reverb_set(s32 mode, s32 depth) {
    SpuReverbAttr attr;

    attr.mask = 7;
    attr.mode = mode;
    attr.depth_left = depth;
    attr.depth_right = depth;
    spu_busy_set();
    if (mode != reverb_mode) {
        SpuSetReverb(0);
        attr.depth_left = 0;
        attr.depth_right = 0;
        attr.mode |= 0x100;
    }
    SpuSetReverbModeParam(&attr);
    if (mode != reverb_mode) {
        attr.mask = 6;
        attr.depth_left = depth;
        attr.depth_right = depth;
        SpuSetReverbDepth(&attr);
    }
    spu_busy_clear();
    reverb_mode = mode;
    reverb_pending = 1;
}

void spu_set_common_attr(s32 arg0) {
    spu_busy_set();
    SpuSetCommonAttr(arg0);
    spu_busy_clear();
}

extern s32 reverb_mode; /* index of the memory-size table entry (0..9) */
/* Returns 0x80000 minus a per-index reserve, in bytes. */
s32 reverb_reserve_bytes(void) {
    s32 reserve;

    switch (reverb_mode) {
    case 0:
        reserve = 0x80;
        break;
    case 1:
        reserve = 0x26C0;
        break;
    case 2:
        reserve = 0x1F40;
        break;
    case 3:
        reserve = 0x4840;
        break;
    case 4:
        reserve = 0x6FE0;
        break;
    case 5:
        reserve = 0xADE0;
        break;
    case 6:
        reserve = 0xF6C0;
        break;
    case 9:
        reserve = 0x3C00;
        break;
    default:
        reserve = 0x18040;
        break;
    }
    return 0x80000 - reserve;
}

void spufunc_key_on(s32 arg0) {
    if (arg0 != 0) {
        spu_busy_set();
        SpuSetKey(1, arg0);
        spu_busy_clear();
    }
}

void spufunc_key_off(s32 arg0) {
    if (arg0 != 0) {
        spu_busy_set();
        SpuSetKey(0, arg0);
        spu_busy_clear();
    }
}

void spufunc_set_voice_attr(s32 arg0) {
    spu_busy_set();
    SpuSetVoiceAttr(arg0);
    spu_busy_clear();
}

void spufunc_key_on_attr(s32 arg0) {
    spu_busy_set();
    SpuSetKeyOnWithAttr(arg0);
    spu_busy_clear();
}

extern s32 spu_heap_top;

s32 spufunc_get_last_address(void) {
    return spu_heap_top;
}

extern s32 spu_heap_top;
extern s32 spu_heap_base;

void spufunc_set_heap_base(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 & 0x7FFFF;
    spu_heap_base = temp_a0;
    spu_heap_top = temp_a0;
}

extern s32 spu_heap_size;
s32 spufunc_malloc(s32 size) {
    s32 start;
    s32 end;

    start = spu_heap_top;
    end = start + size;
    if (spu_heap_base + spu_heap_size < end) {
        printf("SpuFunc SpuSpuMalloc:Size Error\n");
        printf("SpuLastAddress:%x\n", spu_heap_top);
        printf("size          :%x\n", size);
        printf("ofst          :%x\n", spu_heap_top + size);
        printf("StartAddress  :%x\n", spu_heap_base);
        printf("MallocSize    :%x\n", spu_heap_size);
        printf("LimitPos      :%x\n", spu_heap_base + spu_heap_size);
        return -1;
    }
    spu_heap_top = end;
    return start;
}

extern s32 spu_heap_top;
extern s32 spu_heap_base;

s32 spufunc_free_top(s32 arg0) {
    s32 temp_v0;

    temp_v0 = spu_heap_top - arg0;
    spu_heap_top = temp_v0;
    if (temp_v0 < spu_heap_base) {
        spu_heap_top = spu_heap_base;
    }
    return spu_heap_top;
}

s32 SpuIsTransferCompleted(s32 flag);
s32 spufunc_transfer_done(s32 flag) {
    return SpuIsTransferCompleted(flag);
}

u32 SpuSetTransferStartAddr(u32 addr);
u32 spufunc_set_transfer_addr(u32 addr) {
    return SpuSetTransferStartAddr(addr);
}

s32 SpuWrite(void *ram_addr, u32 size);
/* SPU write: sets spufunc_transfer_done(1), sets the SPU transfer address, then SpuWrite from RAM. */
void spufunc_write(void *ram_addr, s32 spu_addr, u32 size) {
    spufunc_transfer_done(1);
    spufunc_set_transfer_addr(spu_addr);
    SpuWrite(ram_addr, size);
}

s32 SpuRead(void *ram_addr, u32 size);
/* SPU read: sets spufunc_transfer_done(1), sets the SPU transfer address, then SpuRead into RAM. */
void spufunc_read(s32 spu_addr, void *ram_addr, u32 size) {
    spufunc_transfer_done(1);
    spufunc_set_transfer_addr(spu_addr);
    SpuRead(ram_addr, size);
}

extern s32 spu_heap_size;

void spufunc_set_heap_size(s32 unused) { /* spufunc_init passes -1 */
    spu_heap_size = reverb_reserve_bytes() - 0x1010;
}

extern s32 spu_heap_size;

s32 spufunc_get_heap_size(void) {
    return spu_heap_size;
}

void spufunc_get_key_status(s32 arg0) {
    spu_busy_set();
    SpuGetAllKeysStatus(arg0);
    spu_busy_clear();
}

extern s32 reverb_pending;
extern s32 reverb_enabled;

void spufunc_flush_reverb(void) {
    spu_busy_set();
    if (reverb_pending != 0) {
        SpuSetReverb(reverb_enabled);
        reverb_pending = 0;
    }
    spu_busy_clear();
}

void SpuSetReverbVoice(s32 voice, s32 on);
void spufunc_set_reverb_voice(s32 voice, s32 on) {
    spu_busy_set();
    SpuSetReverbVoice(voice, on);
    spu_busy_clear();
}

/* Turns SPU reverb on (non-zero) or off (zero) and records the state in reverb_enabled; reverb_pending is set to 1 afterwards. */
void spufunc_reverb_enable(s32 enabled) {
    spu_busy_set();
    if (enabled == 0) {
        SpuSetReverb(0);
        reverb_enabled = 0;
    } else {
        reverb_enabled = 1;
    }
    reverb_pending = 1;
    spu_busy_clear();
}

void SpuSetReverbDepth(SpuReverbAttr *attr);
void SpuClearReverbWorkArea(s32 mode);
void spufunc_set_reverb_depth(s32 depth) {
    SpuReverbAttr attr;

    attr.mask = 6;
    attr.depth_left = depth;
    attr.depth_right = depth;
    spu_busy_set();
    SpuSetReverbDepth(&attr);
    if (depth == 0) {
        SpuClearReverbWorkArea(reverb_mode);
    }
    spu_busy_clear();
}

void spufunc_flush(void) {
    spu_busy_set();
    SpuFlush(0);
    spu_busy_clear();
}

extern s32 spufunc_init_done;
extern s32 spu_malloc_table[14];
void SpuInit(void);
void SpuInitMalloc(s32 count, s32 *table);
s32 SpuMalloc(s32 size);
void SpuSetIRQ(s32 on);
void SpuSetTransferMode(s32 mode);
void SpuReserveReverbWorkArea(s32 on);
void spufunc_init(void) {
    SpuCommonAttrInit common;
    SpuVoiceAttrInit voice;
    s32 temp;

    if (spufunc_init_done == 0) {
        spufunc_init_done = 1;
        SpuInit();
        SpuInitMalloc(6, spu_malloc_table);
        spufunc_set_heap_size(-1);
        temp = SpuMalloc(spufunc_get_heap_size());
        if (temp == -1) {
            printf("spufunc InitSpuFunc: SpuMalloc Error\n");
            for (;;) {}
        }
        spufunc_set_heap_base(temp);
        SpuSetIRQ(0);
        SpuSetTransferMode(0);
        SpuReserveReverbWorkArea(1);
        reverb_set(0x103, 0x3000);
        common.mask = 0x3FCF;
        common.mvol_l = 0x3000;
        common.mvol_r = 0x3000;
        common.mvolmode_l = 0;
        common.mvolmode_r = 0;
        common.ext_reverb = 0;
        common.ext_mix = 0;
        common.ext_vol_l = 0;
        common.ext_vol_r = 0;
        common.cd_reverb = 0;
        common.cd_mix = 1;
        common.cd_vol_l = 0x3000;
        common.cd_vol_r = 0x3000;
        spu_set_common_attr((s32)&common);
        voice.voice = 0xFFFFFF;
        voice.mask = 0xFF8F;
        voice.r_mode = 3;
        voice.volmode_l = 0;
        voice.volmode_r = 0;
        voice.addr = 0;
        voice.loop_addr = 0;
        voice.unk_0C = 0;
        voice.unk_0E = 0;
        voice.a_mode = 1;
        voice.s_mode = 1;
        voice.ar = 0x1F;
        voice.dr = 0;
        voice.sr = 0;
        voice.rr = 0x1F;
        voice.sl = 0;
        SpuSetVoiceAttr(&voice);
        voice.unk_40 = 1;
        voice.unk_44 = 1;
    }
}

extern u8 vab_busy_flag;
void vab_busy_set(s32 arg0) {
    vab_busy_flag = arg0;
}

extern u8 vab_busy_flag;
/* Same code as get_cd_status (boot). */
s32 vab_busy_get(void) {
    return vab_busy_flag;
}

extern u8 rec_count_lo;
extern u8 rec_count_hi;

s32 rec_count_get(void) {
    return (rec_count_hi << 0x10) | rec_count_lo;
}

extern VabSlot vab_slots[5];
void vab_slot_reset(s32 arg0) {
    VabSlotEntry *entry;

    if (arg0 < 5) {
        entry = (VabSlotEntry *) &vab_slots[arg0];
        entry->unk_0E = rec_count_lo;
        entry->prog_start = 0;
        entry->prog_count = 0;
        entry->unk_0C = 0;
        entry->tone_start = 0;
        entry->tone_count = 0;
        entry->pair_start = 0;
        entry->pair_count = 0;
        entry->spu_base = 0;
        entry->spu_addr = 0;
        entry->unk_0F = rec_count_hi;
    }
}

s32 round_up(s32 value, s32 unit);
s32 spufunc_malloc(s32 size);
/* Size a request with round_up, allocate it from the SPU heap and,
   on success, hand the buffer to spufunc_write. Returns the buffer, or a
   negative value when the allocation failed. */
s32 spufunc_upload_alloc(void *src, s32 value) {
    s32 size;
    s32 buf;

    size = round_up(value, 8);
    buf = spufunc_malloc(size);
    if (buf >= 0) {
        spufunc_write(src, buf, size);
    }
    return buf;
}

void spufunc_copy(s32 src_spu, s32 dst_spu, s32 size) {
    u8 buf[0x4000];
    s32 chunk;
    s32 remaining;
    s32 diff;
    s32 abs_diff;

    remaining = size;
    chunk = 0x1000;
    if (src_spu != dst_spu) {
        if (remaining == -1) {
            remaining = spufunc_get_last_address() - dst_spu;
        }
        diff = src_spu - dst_spu;
        if (remaining >= 0) {
            abs_diff = diff >= 0 ? diff : -diff;
            if (abs_diff < 0x1000) {
                chunk = abs_diff;
            }
            if (remaining > 0) {
                do {
                    if (remaining < chunk) {
                        chunk = remaining;
                    }
                    spufunc_read(src_spu, buf, chunk);
                    spufunc_transfer_done(1);
                    spufunc_write(buf, dst_spu, chunk);
                    spufunc_transfer_done(1);
                    remaining -= chunk;
                } while (remaining > 0);
            }
        }
    }
}

/* 1 if base starts with a VAB header's magic ("pBAV": "VABp" read as a little-endian word), else -1. */
s32 vab_header_check(u8 *base) {
    if (mem_equal(4, (u8 *)"pBAV", base) == 0) {
        return -1;
    }
    return 1;
}

s32 vab_prog_count(BootSlot *slot) {
    return slot->prog_count;
}

int boot_rec_empty_count(u8 *base) {
    s32 unused;
    s32 i;
    s32 count;
    u8 *rec = base + 0x20;

    count = *(u16 *)(base + 0x12);
    for (i = 0; i < count; i++) {
        if (*rec == 0) {
            count += 1;
        }
        rec += 0x10;
    }
    return count;
}

s32 boot_rec_group_count(BootRec *rec) {
    return rec->group_count;
}

s32 boot_rec_pair_count(BootRec *rec) {
    return rec->pair_count;
}

/* Returns unk_0C - 0x820 - (unk_12 << 9) - 0x200, clamped at 0. */
s32 boot_rec_free_bytes(BootRec *rec) {
    s32 remaining;

    remaining = rec->total_size;
    remaining -= 0x820;
    remaining -= rec->unk_12 << 9;
    remaining -= 0x200;
    if (remaining < 0) {
        remaining = 0;
    }
    return remaining;
}

extern VabProgEntry vab_prog_table[640];
extern u16 vab_prog_entries;

/* Appends the programs of a VAB header to the program table. */
void vab_progs_append(BootSlot *slot) {
    VabProgAtr *src = slot->progs;
    VabProgEntry *dst = &vab_prog_table[vab_prog_entries];
    s32 count = vab_prog_count(slot);
    s32 toneIndex = 0;
    s32 program = 0;
    s32 i = 0;
    s32 unused[2];

    if (count > 0) {
        do {
            s32 tones;
            u8 mvol, prior, mode, mpan;
            s32 attr;
            while (src->tones == 0) {
                src++;
                program++;
            }
            i++;
            tones = src->tones;
            mvol = src->mvol;
            dst->num = tones;
            dst->mvol = mvol;
            prior = src->prior;
            mode = src->mode;
            dst->prior = prior;
            dst->mode = mode;
            mpan = src->mpan;
            attr = src->attr;
            src++;
            dst->key = program;
            program++;
            dst->mpan = mpan;
            dst->attr = attr;
            dst->index = toneIndex;
            toneIndex += dst->num;
            dst++;
        } while (i < count);
    }
    vab_prog_entries += count;
}

extern u16 vab_tone_entries;
extern VagAtr vab_tone_table[384];
void vab_tones_install(u8 *base, s32 slot) {
    VagAtr *src;
    VagAtr *dst;
    u8 *prog;
    s32 i;
    s32 j;
    s32 count;
    s32 added;
    s32 tones;
    u8 b0;
    u8 b1;
    s32 h0;
    s32 h1;

    src = (VagAtr *)(base + 0x820);
    prog = base + 0x20;
    dst = &vab_tone_table[vab_tone_entries];
    count = vab_prog_count((BootSlot *)base);
    added = 0;
    for (i = 0; i < count; i++, prog += 0x10) {
        tones = *prog;
        if (tones == 0) {
            count++;
            continue;
        }
        for (j = 0; j < tones; j++) {
            b0 = src->prior;
            b1 = src->mode;
            dst->prior = b0;
            dst->mode = b1;
            b0 = src->vol;
            b1 = src->pan;
            dst->vol = b0;
            dst->pan = b1;
            b0 = src->center;
            b1 = src->shift;
            dst->center = b0;
            dst->shift = b1;
            b0 = src->min;
            b1 = src->max;
            dst->min = b0;
            dst->max = b1;
            b0 = src->vibW;
            b1 = src->vibT;
            dst->vibW = b0;
            dst->vibT = b1;
            b0 = src->porW;
            b1 = src->porT;
            dst->porW = b0;
            dst->porT = b1;
            b0 = src->pbmin;
            b1 = src->pbmax;
            dst->pbmin = b0;
            dst->pbmax = b1;
            b0 = src->reserved1;
            b1 = src->reserved2;
            dst->reserved1 = b0;
            dst->reserved2 = b1;
            h0 = src->adsr1;
            h1 = src->adsr2;
            dst->adsr1 = h0;
            dst->adsr2 = h1;
            h0 = src->prog;
            h1 = src->vag;
            dst->prog = h0;
            dst->vag = h1;
            dst->reserved[0] = slot;
            dst++;
            src++;
            added++;
        }
        src += 0x10 - tones;
    }
    vab_tone_entries += added;
}

extern u16 boot_pair_count;
extern BootPair boot_pairs[];
void boot_pairs_load(BootRec *rec) {
    u16 *cur;
    s32 count;
    s32 i;
    s32 value;
    s32 delta;
    BootPair *dst;

    cur = (u16 *)((u8 *)rec + ((rec->unk_12 << 9) + 0x820));
    dst = &boot_pairs[boot_pair_count];
    count = boot_rec_pair_count(rec);
    value = *cur;
    cur++;
    for (i = 0; i < count; i++) {
        delta = *cur;
        cur++;
        dst->unk_00 = value;
        value += delta;
        dst->unk_04 = delta;
        dst++;
    }
    boot_pair_count += count;
}

/* Returns a pointer 0xA20 past the block at base, offset by (u16 at base+0x12) * 512. */
void *boot_rec_body_ptr(u8 *base) {
    u32 offset = *(u16 *)(base + 0x12) << 9;
    return (u8 *)(offset + (u32)base) + 0xA20;
}

extern u16 vab_tone_entries;
s32 vab_header_check(u8 *base);
void vab_tones_install(u8 *base, s32 slot);
s32 vab_slot_load(s32 slot, s32 base, s32 src) {
    VabSlotFields *entry;
    u8 *rec;
    s32 value;

    /* Empty asm: gives slot a fresh register so CSE keeps the move into $a0
       before the vab_slot_reset call (without it the move is dropped). */
    __asm__("" : "=r"(slot) : "0"(slot));
    rec = (u8 *)base;
    if (slot < 5) {
        entry = (VabSlotFields *)&vab_slots[slot];
        if (entry->prog_count == 0) {
            vab_slot_reset(slot);
            if (vab_header_check(rec) >= 0) {
                value = vab_prog_count((BootSlot *)rec);
                entry->prog_count = value;
                entry->prog_start = vab_prog_entries;
                if (vab_prog_entries + value < 0x280) {
                    entry->unk_0C = boot_rec_empty_count(rec);
                    value = boot_rec_group_count((BootRec *)rec);
                    entry->tone_count = value;
                    entry->tone_start = vab_tone_entries;
                    if (vab_tone_entries + value < 0x180) {
                        value = boot_rec_pair_count((BootRec *)rec);
                        entry->pair_count = value;
                        entry->pair_start = boot_pair_count;
                        if (boot_pair_count + value < 0x180) {
                            value = boot_rec_free_bytes((BootRec *)rec);
                            if (value != 0) {
                                entry->spu_size = value;
                                if (src == 0) {
                                    src = (s32)boot_rec_body_ptr(rec);
                                }
                                value = spufunc_upload_alloc((void *)src, value);
                                if (value >= 0) {
                                    entry->spu_addr = value;
                                    vab_progs_append((BootSlot *)rec);
                                    vab_tones_install(rec, slot);
                                    boot_pairs_load((BootRec *)rec);
                                    return slot;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void vab_busy_set(s32 arg0);
s32 vab_slot_load(s32 slot, s32 base, s32 src);
void vab_slot_reset(s32 a);
/* Call vab_slot_load with the three arguments (after vab_busy_set(1));
   on a negative result, call vab_slot_reset and return the result. */
s32 vab_open(s32 arg0, s32 arg1, s32 arg2) {
    s32 result;

    vab_busy_set(1);
    result = vab_slot_load(arg0, arg1, arg2);
    if (result < 0) {
        vab_slot_reset(arg0);
    }
    return result;
}

void spu_transfer_flag_set(s32 flag) {
    if (flag != 0) {
        flag = 1;
    }
    spufunc_transfer_done(flag);
}

/* Open a VAB with the caller's three arguments, then flag the SPU transfer; returns vab_open's result. */
s32 vab_load(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = vab_open(arg0, arg1, arg2);

    spu_transfer_flag_set(1);
    return result;
}

s32 vab_slot_unload(s32 index) {
    VabSlotEntry *slot;
    VabSlotEntry *other;
    s32 base;
    u32 size;
    s32 j;
    s32 k;

    if (index >= 5) {
        return -1;
    }
    slot = (VabSlotEntry *)&vab_slots[index];
    if (slot->prog_count == 0) {
        return -1;
    }
    base = slot->spu_base;
    size = boot_pairs[slot->pair_start].unk_00 * 8;
    k = 0;
    do {
        other = (VabSlotEntry *)&vab_slots[k];
        if (other->prog_count != 0 && size < boot_pairs[other->pair_start].unk_00 * 8) {
            spufunc_copy(size + base, size, -1);
            break;
        }
    } while (++k < 5);
    spufunc_free_top(base);

    {
        VabProgEntry *src, *dst;
        j = slot->prog_start + slot->prog_count;
        src = &vab_prog_table[j];
        dst = &vab_prog_table[slot->prog_start];
        for (; j < vab_prog_entries; j++) {
            *dst++ = *src++;
        }
    }
    {
        VagAtr *src, *dst;
        j = slot->tone_start + slot->tone_count;
        src = &vab_tone_table[j];
        dst = &vab_tone_table[slot->tone_start];
        vab_prog_entries -= slot->prog_count;
        for (; j < vab_tone_entries; j++) {
            *dst++ = *src++;
        }
    }
    {
        BootPair *src, *dst;
        j = slot->pair_start + slot->pair_count;
        src = &boot_pairs[j];
        dst = &boot_pairs[slot->pair_start];
        vab_tone_entries -= slot->tone_count;
        for (; j < boot_pair_count; j++) {
            *dst++ = *src++;
        }
    }
    boot_pair_count -= slot->pair_count;
    for (j = 0, other = (VabSlotEntry *)vab_slots; j < 5; j++, other++) {
        if (j != index) {
            if (slot->prog_start < other->prog_start) {
                other->prog_start -= slot->prog_count;
            }
            if (slot->tone_start < other->tone_start) {
                other->tone_start -= slot->tone_count;
            }
            if (slot->pair_start < other->pair_start) {
                other->pair_start -= slot->pair_count;
            }
        }
    }
    vab_slot_reset(index);
    return index;
}

s32 vab_slot_unload_guarded(s32 arg0) {
    s32 temp_s0;

    vab_busy_set(1);
    temp_s0 = vab_slot_unload(arg0);
    vab_busy_set(0);
    return temp_s0;
}

/* Stores the two limits as bytes; an inline helper so the u8 copies
   get their own registers as in the original. */
static inline void set_limits(u8 lo, u8 hi) {
    rec_count_lo = lo;
    rec_count_hi = hi;
}

/* Clamps a to 0..23 and b to 0..24, trims b so a + b stays within 24,
   then stores both. */
void snd_set_limits(s32 a, s32 b) {
    a = clamp_value(a, 0, 23);
    b = clamp_value(b, 0, 24);
    if (a + b > 24) {
        b = 24 - a;
    }
    set_limits(a, b);
}

/* Sets the clamped pair unk_0C[2], unk_0C[3] of slot idx (0..4), if the slot is in use.
   Returns 1 on success, -1 for a bad or unused slot, -2 if the pair sums to 0x19 or more. */
s32 vab_slot_set_range(s32 idx, s32 lo, s32 hi) {
    VabSlot *entry;
    s32 clamped;

    if ((idx >= 5) || (entry = &vab_slots[idx], entry->prog_count == 0)) {
        return -1;
    }
    if (lo >= 0) {
        clamped = 0x17;
        if (lo < 0x18) {
            clamped = lo;
        }
    } else {
        clamped = 0;
    }
    lo = clamped;
    if (hi > 0) {
        clamped = 0x18;
        if (hi < 0x19) {
            clamped = hi;
        }
    } else {
        clamped = 1;
    }
    hi = clamped;
    if ((lo + hi) >= 0x19) {
        return -2;
    }
    entry->voice_first = lo;
    entry->voice_count = hi;
    return 1;
}

extern VabProgEntry vab_prog_table[640];

extern VagAtr vab_tone_table[384];
extern u16 vab_prog_entries;
extern u16 vab_tone_entries;
void snd_reset(void) {
    s8 *p1;
    s8 *p2;
    s8 *p3;
    s32 i;

    p1 = (s8 *)vab_prog_table;
    p2 = (s8 *)vab_tone_table;
    p3 = (s8 *)boot_pairs;
    vab_prog_entries = 0;
    vab_tone_entries = 0;
    boot_pair_count = 0;
    for (i = 0; i < 5; i++) {
        vab_slot_reset(i);
    }
    for (i = 0; i < 0x280; i++) {
        mem_set(p1, 0xC, 0);
        p1 += 0xC;
    }
    for (i = 0; i < 0x180; i++) {
        mem_set(p2, 0x20, 0);
        p2 += 0x20;
    }
    for (i = 0; i < 0x180; i++) {
        mem_set(p3, 8, 0);
        p3 += 8;
    }
    spufunc_set_reverb_depth(0);
}

extern VabSlot vab_slots[5];
s32 vab_slot_get(s32 index) {
    VabSlot *entry;

    if (index >= 5) {
        return 0;
    }
    entry = &vab_slots[index];
    return entry->prog_count ? (s32)entry : 0;
}

/* Finds program `key` in VAB slot `slot`; returns its tone record `tone` or 0. */
VagAtr *vab_prog_find(s32 slot, s32 key, s32 tone) {
    VabSlot *vab;
    VabProgEntry *prog;
    s32 i;
    s32 notFound;
    s32 count;
    s32 stride;

    if (slot < 5) {
        vab = &vab_slots[slot];
        i = 0;
        if (vab->max_prog_key < key) {
            return 0;
        }
        if (0) {
        found:
            notFound = 0;
            goto done;
        }
        notFound = 1;
        stride = sizeof(VabProgEntry);
        count = vab->prog_count;
        prog = &vab_prog_table[vab->prog_start];
    loop:
        if (i >= count) {
            goto done;
        }
        i += notFound;
        if (prog->key == key) {
            goto found;
        }
        prog = (VabProgEntry *)((u8 *)prog + stride);
        if (i >= 0) {
            goto loop;
        }
    done:
        if (notFound) {
            return 0;
        }
        if (tone < prog->num) {
            return &vab_tone_table[vab->tone_base + prog->index + tone];
        }
    }
    return 0;
}

s32 vab_tone_offset(VabToneRef *ref) {
    VabSlotEntry *entry = (VabSlotEntry *)&vab_slots[ref->slot_index];
    s32 pair;
    s32 result;

    pair = boot_pairs[entry->pair_start + ref->pair_index - 1].unk_00;
    result = entry->spu_addr;
    result += pair * 8;
    return result;
}

VagAtr *vab_tone_find(u32 arg0) {
    return vab_prog_find(arg0 >> 0x18, (u32) (arg0 & 0xFF00) >> 8, arg0 & 0xF);
}

u8 vab_tone_volume(u32 arg0) {
    u8 *entry = (u8 *) vab_tone_find(arg0);

    return (entry != NULL) ? entry[2] : 0;
}

void spu_set_main_volume(s32 volume) {
    SpuCommonAttrBlock attr;

    attr.mask = 3;
    attr.mvol_left = volume;
    attr.mvol_right = volume;
    spu_set_common_attr((s32)&attr);
}

s32 cd_volume_lookup(s32 unk_a0);
void spu_set_cd_volume(s32 value) {
    SpuCommonAttrInit attr;
    s32 vol;

    value /= 128;
    vol = cd_volume_lookup(value) << 8;
    attr.mask = 0xC0;
    attr.cd_vol_l = vol;
    attr.cd_vol_r = vol;
    spu_set_common_attr((s32)&attr);
}

void cd_set_volume(s32 mode);
extern s32 snd_mode;
void snd_set_mode(s32 arg) {
    snd_mode = clamp_value(arg, 0, 2);
    cd_set_volume(snd_mode);
}

extern s32 snd_mode;

s32 snd_get_mode(void) {
    return snd_mode;
}

extern u8 snd_volume_busy_flag;
/* Same code as vab_busy_set (boot). */
void snd_volume_busy_set(s32 arg0) {
    snd_volume_busy_flag = arg0;
}

extern u8 snd_volume_busy_flag;
s32 func_8001CB0C(void) {
    return snd_volume_busy_flag != 0;
}

extern s32 snd_main_level;
extern s32 snd_main_fade_step;

void snd_set_main_level_now(s32 arg0) {
    snd_main_fade_step = 0;
    snd_main_level = arg0 << 0xA;
}

extern s32 snd_main_target;
extern s32 snd_main_fade_step;

void snd_set_volume(s32 arg0) {
    vab_busy_set(1);
    snd_main_target = (s32) (arg0 * 0xC00) / 4096;
    snd_volume_busy_set(1);
    if (snd_main_fade_step == 0) {
        spu_set_main_volume(snd_main_target);
    }
    snd_volume_busy_set(0);
    vab_busy_set(0);
}

extern s32 snd_cd_level;
extern s32 snd_cd_fade_step;

void snd_set_cd_level_now(s32 arg0) {
    snd_cd_fade_step = 0;
    snd_cd_level = arg0 << 0xA;
}

extern u8 snd_cd_enabled;
void snd_set_cd_enabled(s32 enable) {
    if (enable != 0) {
        snd_cd_enabled = 1;
        return;
    }
    snd_cd_enabled = 0;
}

extern s32 snd_cd_user_level;
extern s32 snd_cd_target;
void spu_set_cd_volume(s32 value);
/* Sets the level kept in snd_cd_user_level (a negative argument reads it back instead),
   clamps it to 0 unless snd_cd_enabled is set, and stores the clamped result. */
void snd_set_cd_volume(s32 level) {
    vab_busy_set(1);
    if (level < 0) {
        level = snd_cd_user_level;
    } else {
        snd_cd_user_level = level;
    }
    if (snd_cd_enabled == 0) {
        level = 0;
    }
    snd_cd_target = clamp_value(level, 0, 0x3FFF);
    snd_volume_busy_set(1);
    if (snd_cd_fade_step == 0) {
        spu_set_cd_volume(snd_cd_target);
    }
    snd_volume_busy_set(0);
    vab_busy_set(0);
}

void cd_cmd_guarded(s32 param_a, s32 param_b);
void cd_cmd_set_volume(s32 arg0) {
    s32 sp10;

    sp10 = arg0;
    cd_cmd_guarded(0xB0, (s32)&sp10);
}

void snd_fade_in(int arg0) {
    int v = snd_main_target << 11;
    arg0 += 1;
    v = v / arg0;
    snd_main_level = 0;
    snd_main_fade_step = v;
}

void snd_fade_out(s32 n) {
    s32 v = snd_main_target;
    s32 d = n + 1;
    snd_main_level = v << 10;
    snd_main_fade_step = -((v << 11) / d);
}

/* Same code as snd_fade_in (boot). */
void snd_cd_fade_in(int arg0) {
    int v = snd_cd_target << 11;
    arg0 += 1;
    v = v / arg0;
    snd_cd_level = 0;
    snd_cd_fade_step = v;
}

/* Same code as snd_fade_out (boot). */
void snd_cd_fade_out(s32 n) {
    s32 v = snd_cd_target;
    s32 d = n + 1;
    snd_cd_level = v << 10;
    snd_cd_fade_step = -((v << 11) / d);
}

extern s32 snd_main_fade_step;

s32 snd_is_fading(void) {
    return snd_main_fade_step != 0;
}

extern s32 snd_cd_fade_step;

s32 snd_is_cd_fading(void) {
    return snd_cd_fade_step != 0;
}

extern s32 snd_cd_level;

s32 snd_get_cd_level(void) {
    return snd_cd_level;
}

extern s32 snd_main_level;

s32 snd_get_main_level(void) {
    return snd_main_level;
}

s32 vab_busy_get(void);
s32 spu_busy_get(void);
/* Volume fades: the snd_main_level/snd_cd_level accumulators are 10-bit fixed point
   (0x400 = 1.0), clamped to the target levels in snd_main_target/snd_cd_target. */
void snd_fade_update(void) {
    s32 vol;

    if ((snd_main_fade_step != 0 || snd_cd_fade_step != 0) && func_8001CB0C() == 0) {
        snd_main_level += snd_main_fade_step;
        snd_cd_level += snd_cd_fade_step;
        if (spu_busy_get() == 0 && vab_busy_get() == 0) {
            if (snd_main_level < 0) {
                snd_main_fade_step = 0;
                snd_main_level = 0;
            }
            vol = snd_main_level / 0x400;
            if (snd_main_target < vol) {
                snd_main_fade_step = 0;
                snd_main_level = snd_main_target * 0x400;
                vol = snd_main_level / 0x400;
            }
            spu_set_main_volume(vol);
            if (snd_cd_level < 0) {
                snd_cd_fade_step = 0;
                snd_cd_level = 0;
            }
            vol = snd_cd_level / 0x400;
            if (snd_cd_target < vol) {
                snd_cd_fade_step = 0;
                snd_cd_level = snd_cd_target * 0x400;
                vol = snd_cd_level / 0x400;
            }
            spu_set_cd_volume(vol);
        }
    }
}

extern u8 snd_fade_inited_flag;
void snd_fade_update(void);
/* One-time setup: registers snd_fade_update with frame_task_add_small (argument 1) the first time it runs.
 * snd_fade_inited_flag is the done flag. */
void snd_fade_init(void) {
    if (snd_fade_inited_flag == 0) {
        frame_task_add_small(&snd_fade_update, 1);
        snd_fade_inited_flag = 1;
    }
}

void snd_set_limits(s32 a, s32 b);
void snd_reset(void);
void sound_slots_clear(void);
void sound_tick_init(void);
void snd_set_mode(s32 arg);
/* Boot-time setup: runs the init steps in order, then snd_set_mode(1) and four calls with 0x3FFF.
 * Its caller passes (0, 0x18), handed on to snd_set_limits. */
void sound_init(s32 a, s32 b) {
    snd_set_limits(a, b);
    snd_reset();
    sound_slots_clear();
    sound_tick_init();
    snd_fade_init();
    snd_set_mode(1);
    snd_set_main_level_now(0x3FFF);
    snd_set_volume(0x3FFF);
    snd_set_cd_level_now(0x3FFF);
    snd_set_cd_volume(0x3FFF);
}

extern s32 D_800387A4;
/* Same code as get_vec3_ptr (s12). */
s32 *func_8001D0C8(void) {
    return &D_800387A4;
}

extern BootSoundSlot sound_slots[24];
extern volatile s32 sound_slot_flags;
extern volatile s32 D_80038798;
extern volatile s32 sound_slot_pref_mask;
extern s32 D_800387A8;
extern s32 sound_tick_busy_flag;
void SpuGetVoiceAttr(SpuVoiceAttr *attr);
/* Per-frame sound task: follows each voice's SPU key status (keys off voices that stay silent or
 * released too long and frees their slots), then sends the attributes of the voices requested in
 * D_80038798, keys on the new ones and updates their reverb. Slot 0's state and timer are copied
 * to D_800387A4 / D_800387A8. */
void sound_tick(void) {
    u8 key_status[24];
    SpuVoiceAttr cur;
    SpuVoiceAttr attr;
    s32 first_voice;
    s32 count;
    s32 i;
    u8 *key;
    SoundVoiceSlot *slot;
    s32 voices;
    s32 reverb_on;
    s32 reverb_off;
    s32 change;
    s32 voice_bit;
    u8 status;
    s32 busy;
    s32 state;

    {
        s32 *first_state = &D_800387A4;

        FAKE_OPAQUE(first_state);
        *first_state = 0;
    }
    D_800387A8 = 0;
    if (spu_busy_get() != 0 || vab_busy_get() != 0) {
        return;
    }
    busy = sound_tick_busy_flag;
    sound_tick_busy_flag = 1;
    if (busy == 0) {
        spufunc_get_key_status((s32)key_status);
        i = 0;
        /* voice count << 16 | first voice */
        first_voice = rec_count_get();
        count = first_voice >> 16;
        first_voice &= 0xFFFF;
        key = key_status + first_voice;
        slot = (SoundVoiceSlot *)sound_slots;
        voices = 0;
        for (; i < count; i++, slot++) {
            if (i == 0) {
                register s32 state0 asm("$3") = slot->state;
                s32 *first_state;

                SCHED_BARRIER();
                first_state = &D_800387A4;
                __asm__ volatile("" : "=r"(first_state) : "0"(first_state));
                *first_state = state0;
                D_800387A8 = slot->timer;
            }
            status = *key++;
            if (status == SPU_ON) {
                cur.voice = 1 << (first_voice + i);
                SpuGetVoiceAttr(&cur);
                if ((cur.volumex.left >= 0 ? cur.volumex.left : -cur.volumex.left)
                        + (cur.volumex.right >= 0 ? cur.volumex.right : -cur.volumex.right) == 0) {
                    status = SPU_ON_ENV_OFF;
                }
            }
            switch (status) {
            case SPU_ON:
                if (slot->state == 0) {
                    sound_slot_flags |= 1 << (first_voice + i);
                }
                slot->timer = 1;
                break;
            case SPU_OFF:
                if (slot->state >= 2) {
                    slot->timer = 0;
                    slot->state = 0;
                }
                break;
            case SPU_ON_ENV_OFF:
                slot->timer++;
                if (!(slot->flags & 2)) {
                    if (slot->timer > 16) {
                        voices |= 1 << (first_voice + i);
                        slot->timer = 0;
                        slot->state = 0;
                    }
                } else {
                    slot->timer = 2;
                }
                break;
            case SPU_OFF_ENV_ON:
                slot->timer++;
                if (!(slot->flags & 2)) {
                    if (slot->timer > 32) {
                        voices |= 1 << (first_voice + i);
                        slot->timer = 0;
                        slot->state = 0;
                    }
                } else {
                    slot->timer = 2;
                }
                break;
            }
            if (slot->state >= 2) {
                slot->state = slot->state + 1;
                if (slot->state > 0x3FFFFFFF) {
                    slot->state /= 2;
                }
            }
        }
        if (sound_slot_flags != 0) {
            s32 n;
            s32 freed = sound_slot_flags;

            slot = (SoundVoiceSlot *)sound_slots;
            for (n = 0; n < count; n++, slot++) {
                s32 bit = 1 << n;

                if (freed & bit) {
                    slot->timer = 0;
                    slot->state = 0;
                }
            }
        }
        if (voices | sound_slot_flags) {
            spufunc_key_off(voices | sound_slot_flags);
        }
        sound_slot_flags = 0;
        reverb_on = 0;
        if (D_80038798 != 0) {
            slot = (SoundVoiceSlot *)sound_slots;
            reverb_off = 0;
            i = 0;
            voices = 0;
            for (; i < count; i++, slot++) {
                s32 bit = 1 << i;

                if (D_80038798 & bit) {
                    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH;
                    attr.voice = 1 << (first_voice + i);
                    attr.pitch = slot->pitch;
                    attr.volume.left = slot->volume.left;
                    attr.volume.right = slot->volume.right;
                    if (slot->state == 1) {
                        attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH | SPU_VOICE_WDSA
                                  | SPU_VOICE_LSAX | SPU_VOICE_ADSR_ADSR1 | SPU_VOICE_ADSR_ADSR2;
                        attr.adsr1 = slot->adsr1;
                        attr.adsr2 = slot->adsr2;
                        attr.addr = slot->addr;
                        attr.loop_addr = 0;
                    }
                    spufunc_set_voice_attr((s32)&attr);
                }
                state = slot->state;
                if (state == 1) {
                    /* state is 1: the voice's bit */
                    voice_bit = state << (first_voice + i);
                    slot->state = 2;
                    voices |= voice_bit;
                    if (slot->reverb != 0) {
                        if (slot->flags & 1) {
                            reverb_off |= voice_bit;
                        } else {
                            reverb_on |= voice_bit;
                        }
                    }
                }
            }
            if (reverb_on & reverb_off) {
                reverb_on &= ~(reverb_on & reverb_off);
            }
            if (reverb_on != 0) {
                change = ~sound_slot_pref_mask & reverb_on;
                if (change != 0) {
                    spufunc_flush_reverb();
                    spufunc_set_reverb_voice(1, change);
                }
                sound_slot_pref_mask |= reverb_on;
            }
            if (reverb_off != 0) {
                change = reverb_off & sound_slot_pref_mask;
                if (change != 0) {
                    spufunc_flush_reverb();
                    spufunc_set_reverb_voice(0, change);
                }
                sound_slot_pref_mask &= ~reverb_off;
            }
            spufunc_key_on(voices);
            spufunc_flush();
            D_80038798 = 0;
        }
    }
    sound_tick_busy_flag = 0;
}

extern BootSoundSlot sound_slots[24];
s32 sound_active_mask(void) {
    s32 mask = 0;
    s32 i = 0;
    BootSoundSlot *rec = sound_slots;

    do {
        if (rec->flag_04 != 0) {
            mask |= 1 << i;
        }
        i++;
        rec++;
    } while (i < 24);
    return mask;
}

s32 vab_slot_get(s32 index);
s32 Lzc();
extern BootSoundSlot sound_slots[24];
extern volatile s32 sound_slot_pref_mask;

/* Picks a sound slot for VAB slot `index` (-1 when it has none): the highest free slot of its range,
 * preferring slots in sound_slot_pref_mask (or outside it with `invert`); with none free, the slot with the
 * highest score_18, ties going to the larger flag_04. */
s32 sound_voice_pick(s32 index, s32 unused, s32 invert) {
    VabSlot *vab;
    s32 mask;
    s32 i;
    s32 first;
    s32 count;
    volatile BootSoundSlot *rec;
    s32 best_idx;
    s16 score;
    s32 best_score;

    vab = (VabSlot *)(index = vab_slot_get(index));
    mask = 0;
    if (vab == NULL) {
        return -1;
    }
    first = vab->voice_first;
    count = vab->voice_count;
    rec = &sound_slots[first];
    for (i = 0; i < count; i++, rec++) {
        if (rec->flag_04 == 0) {
            mask |= 1 << (first + i);
        }
    }
    if (mask != 0) {
        if (invert != 0) {
            index = ~sound_slot_pref_mask;
        } else {
            index = sound_slot_pref_mask;
        }
        index &= mask;
        index &= 0xFFFFFF;
        if (index == 0) {
            index = mask;
        }
        {
            /* 31 built in v0 keeps the copy of Lzc's result the original has */
            s32 zeros = Lzc(index);
            register s32 bit asm("$2") = 31;

            return bit - zeros;
        }
    }
    best_idx = first + count - 1;
    best_score = 0;
    index = 0;
    rec = &sound_slots[first];
    for (i = 0; i < count; i++, rec++) {
        score = ((volatile SoundSlotScore *)rec)->score_18;
        if (best_score < score) {
            best_idx = i + first;
            best_score = score;
            index = 0;
        } else if (best_score == score && index < (s32)rec->flag_04) {
            best_idx = i + first;
            index = rec->flag_04;
        }
    }
    return best_idx;
}

extern u16 sound_semitone_table[];
/* Pitch ratio (0x1000 = 1.0) from note/fine (each clamped to 0..127) to
 * base_note/base_fine: octaves of 0x600 give the shift, the remainder
 * indexes the semitone table sound_semitone_table. */
s32 sound_pitch_ratio(s32 base_note, s32 base_fine, s32 note, s32 fine) {
    s32 octave;
    s32 base;
    s32 scale;

    if (note >= 0) {
        octave = 0x7F;
        if (note < 0x80) {
            octave = note;
        }
    } else {
        octave = 0;
    }
    note = octave;
    if (fine >= 0) {
        octave = 0x7F;
        if (fine < 0x80) {
            octave = fine;
        }
    } else {
        octave = 0;
    }
    note = (note << 7) | octave;
    base = (base_note << 7) | base_fine;
    octave = 0;
    if (note == base) {
        return 0x1000;
    }
    if (note < base) {
        do {
            note += 0x600;
            octave--;
        } while (note < base);
        note -= 0x600;
        octave++;
    } else {
        while (base < note) {
            note -= 0x600;
            octave++;
        }
    }
    note = base - note;
    if (note < 0) {
        note = -note;
    }
    octave += 12;
    scale = 1;
    scale <<= octave;
    scale = scale * sound_semitone_table[note];
    return clamp_value((u32)scale >> 12, 1, 0x3FFF);
}

/* Copies the two u16 values at src+0x10/0x12 to dst+0x2C/0x2E (volatile:
   the original keeps the last store out of the jr delay slot). */
void snd_copy_volume_pair(s32 channel, u8 *dst, u8 *src, s32 unused) {
    u16 first = *(u16 *)(src + 0x10);
    u16 second = *(u16 *)(src + 0x12);
    *(volatile u16 *)(dst + 0x2C) = first;
    *(volatile u16 *)(dst + 0x2E) = second;
}

extern volatile s32 sound_slot_flags;
/* Marks the request's sound slot in sound_slot_flags (under vab_busy_set(1)/(0))
 * if its id is valid and still owns the slot. */
void sound_slot_flag_set(SoundRequest *req) {
    s32 unused[8];
    s32 id;
    s32 idx;

    id = req->id_08;
    idx = id & 0x1F;
    if (id >= 0 && id == ((BootSoundSlotState *)&sound_slots[idx])->id_0C) {
        s32 unlock;

        vab_busy_set(1);
        unlock = 0;
        FAKE_OPAQUE(unlock);
        sound_slot_flags |= 1 << idx;
        vab_busy_set(unlock);
    }
}

s32 snd_alloc_channel(SndAllocBlock *req);
void sound_key_on_slot(SndAllocBlock *req, s32 mode) {
    SndAllocBlock block;
    BootSoundSlot *entry;
    if (mode != 0 || req->unk_08 >= 0) {
        block = *req;
        entry = &sound_slots[req->unk_08 & 0x1F];
        if (block.unk_08 == *(s32 *)&entry->unk_08[4]) {
            block.volume = 0x3F;
            block.unk_0C = 0;
            block.kind = 2;
            snd_alloc_channel(&block);
            entry->flag_04 = 0;
        }
    }
}

/* slot_sound_key_on: sound_key_on_slot on the block, mode 0. */
void sound_key_on(SndAllocBlock *req) {
    sound_key_on_slot(req, 0);
}

extern volatile s32 sound_slot_flags;
void sound_tick(void);
void sound_slots_mark_all(void) {
    s32 n = rec_count_get() >> 16;
    s32 i;

    for (i = 0; i < n; i++) {
        sound_slot_flags |= 1 << i;
    }
    sound_tick();
}

/* For each record in sound_slots (count from rec_count_get high half),
 * copy its word at +0x0C into a stack request block and key the slot on. */
void sound_key_on_all(void) {
    struct {
        SndAllocBlock req;
        s32 pad[2];
    } frame;
    s32 i;
    s32 count;
    BootSoundSlot *rec;

    i = 0;
    count = rec_count_get() >> 16;
    FAKE_OPAQUE(i);
    if (count > 0) {
        rec = sound_slots;
        do {
            frame.req.unk_08 = *(s32 *)&rec->unk_08[4];
            rec++;
            i++;
            sound_key_on_slot(&frame.req, 0);
        } while (i < count);
    }
}

extern volatile s32 D_80038798;
extern u16 snd_pan_table[];
/* Starts a voice for the request (kind bit 0: pick a free slot and key the
 * tone req->unk_04 names) or updates the live voice whose handle is
 * req->unk_08; the other kind bits pick which request fields override the
 * defaults (4 pan, 2 volume, 0x20 priority, 0x10 note/fine, 8 pitch,
 * 0x80 pitch scale). Returns the voice handle ((serial << 5) | slot), or -1. */
s32 snd_alloc_channel(SndAllocBlock *req) {
    u32 flags = req->kind;
    s32 idx;
    s32 priority;
    s32 pan;
    s32 volume;
    s32 addr;
    s32 rate;
    s32 handle;
    s32 pan_arg;
    s32 volume_arg;
    s32 pan_arg2;
    s32 priority_arg;
    s32 note;
    s32 scale;
    s32 clamped;
    s32 pitch;
    s32 cur_priority;
    s32 new_priority;
    u8 bank;
    s32 pan_index;
    s32 left, right;
    register s32 off_mask asm("$2");
    s16 *out;
    VagAtr *tone;
    SndAllocVoice *rec;

    if (flags == 0) {
        flags = 0x37;
    }
    if (flags & 1) {
        priority_arg = 2;
        if (flags & 0x20) {
            priority_arg = req->priority;
        }
        priority = priority_arg;
        bank = (u32)req->tone_key >> 24;
        idx = sound_voice_pick(bank, priority_arg, flags & 0x100);
        if (idx < 0) {
            printf("No Channel\n");
            return -1;
        }
        tone = vab_prog_find(bank, (req->tone_key & 0xFF00) >> 8, req->tone_key & 0xF);
        if (tone == NULL) {
            return -1;
        }
        addr = vab_tone_offset((VabToneRef *)tone);
        pan_arg = 0x3F;
        if (flags & 4) {
            pan_arg = req->volume;
        }
        pan = clamp_value(pan_arg, 0, 0xFF);
        volume_arg = 100;
        if (flags & 2) {
            volume_arg = req->unk_0C;
        }
        volume = clamp_value(volume_arg, 0, 0xFF);
        rec = (SndAllocVoice *)&sound_slots[idx];
        note = 60;
        if (flags & 0x10) {
            rate = sound_pitch_ratio(tone->center, tone->shift, req->unk_1A, req->unk_1C);
        } else {
            rate = sound_pitch_ratio(tone->center, tone->shift, note, 0);
        }
        if (flags & 8) {
            rate = req->unk_10;
        }
        if (flags & 0x80) {
            rate = (rate * req->unk_14) / 0x1000;
        }
        if (rate >= 0) {
            clamped = 0x3FFF;
            if (rate < 0x4000) {
                clamped = rate;
            }
        } else {
            clamped = 0;
        }
        pitch = clamped;
        snd_copy_volume_pair(flags, (u8 *)rec, (u8 *)tone, pan);
        rec->serial = rec->serial + 1;
        rec->serial; /* the original reads it once more */
        rec->serial = rec->serial & 0x3FF;
        rec->in_use = 1;
        rec->addr = addr;
        rec->active = 1;
        rec->key = req->tone_key;
        rec->flags = 0;
        rec->pan = pan;
        handle = (rec->serial << 5) | (idx & 0x1F);
        off_mask = sound_slot_flags;
        off_mask &= ~(1 << idx);
        sound_slot_flags = off_mask;
    } else {
        if (req->unk_08 < 0) {
            return -1;
        }
        idx = req->unk_08 & 0x1F;
        if (idx >= (rec_count_get() >> 16)) {
            return -1;
        }
        rec = (SndAllocVoice *)&sound_slots[idx];
        if (rec->in_use == 0) {
            return -1;
        }
        if (rec->active == 0) {
            return -1;
        }
        if (req->unk_08 != rec->handle) {
            return -1;
        }
        handle = rec->handle;
        rec->pan;
        do { } while (0);
        pan_arg2 = 0x3F;
        if (flags & 4) {
            pan_arg2 = req->volume;
        }
        pan = clamp_value(pan_arg2, 0, 0xFF);
        rec->volume;
        volume_arg = 100;
        if (flags & 2) {
            volume_arg = req->unk_0C;
        }
        volume = clamp_value(volume_arg, 0, 0xFF);
        cur_priority = rec->priority;
        if (flags & 0x20) {
            new_priority = req->priority;
        } else {
            new_priority = cur_priority;
        }
        tone = rec->tone;
        if (tone == NULL) {
            return -1;
        }
        priority = new_priority;
        rate = rec->pitch;
        note = 60;
        if (flags & 0x10) {
            rate = sound_pitch_ratio(tone->center, tone->shift, req->unk_1A, req->unk_1C);
        } else {
            rate = sound_pitch_ratio(tone->center, tone->shift, note, 0);
        }
        if (flags & 8) {
            rate = req->unk_10;
        }
        if (flags & 0x80) {
            rate = (rate * req->unk_14) / 0x1000;
        }
        if (rate >= 0) {
            clamped = 0x3FFF;
            if (rate < 0x4000) {
                clamped = rate;
            }
        } else {
            clamped = 0;
        }
        pitch = clamped;
        addr = rec->addr;
    }
    vab_busy_set(1);
    if (flags & 0x100) {
        rec->flags = rec->flags | 1;
    } else {
        rec->flags = rec->flags & ~1;
    }
    if (flags & 0x200) {
        rec->flags = rec->flags | 2;
    } else {
        rec->flags = rec->flags & ~2;
    }
    rec->handle = handle;
    rec->pan;
    rec->tone = tone;
    rec->volume = volume;
    rec->pitch = pitch;
    rec->priority = priority;
    scale = snd_volume_lookup(volume);
    pan_index = pan & 0xFF;
    out = &rec->vol_left;
    if (!(flags & 0x40) || snd_get_mode() != 2) {
        if (pan_index >= 0x80) {
            pan_index = 0x100 - pan_index;
        }
    }
    if (snd_get_mode() == 0) {
        pan_index = 0x3F;
    }
    if (pan_index < 0x80) {
        left = snd_pan_table[pan_index];
        right = snd_pan_table[0x80 - pan_index];
    } else {
        pan_index = 0x100 - pan_index;
        left = snd_pan_table[pan_index];
        right = -snd_pan_table[0x80 - pan_index];
    }
    out[0] = (left * scale) / 32;
    out[1] = (right * scale) / 32;
    rec->pan = pan_index;
    D_80038798 |= 1 << idx;
    vab_busy_set(0);
    return handle;
}

/* Returns the request's id if its table entry is active and has a flag set, else -1. */
s32 sound_req_active_id(SoundRequest *req) {
    s32 id;
    s32 idx;
    BootSoundSlotState *entry;

    id = req->id_08;
    if (id < 0) {
        return -1;
    }
    idx = id & 0x1F;
    if (idx >= (rec_count_get() >> 16)) {
        return -1;
    }
    entry = (BootSoundSlotState *) &sound_slots[idx];
    if (req->id_08 != entry->id_0C) {
        return -1;
    }
    if (entry->active_1E == 0) {
        return -1;
    }
    if (entry->flag_04 == 0) {
        return -1;
    }
    return req->id_08;
}

extern volatile s32 D_80038798;
extern volatile s32 sound_slot_flags;
void sound_slots_clear(void) {
    BootSoundSlot *rec = sound_slots;
    s32 i = 0;

    do {
        mem_set((s8 *)rec, 0x30, 0);
        i++;
        rec++;
    } while (i < 24);
    D_80038798 = 0;
    sound_slot_flags = 0;
    sound_slot_pref_mask = 0;
}

extern u8 sound_tick_inited_flag;
void sound_tick(void);
/* One-time setup: registers sound_tick with frame_task_add_small (argument 0) the first time it runs.
 * sound_tick_inited_flag is the done flag. */
void sound_tick_init(void) {
    if (sound_tick_inited_flag == 0) {
        frame_task_add_small(&sound_tick, 0);
        sound_tick_inited_flag = 1;
    }
}

int CdControlF(u8 com, u8 *param);
/* Repeats the CD-ROM control command until it returns 1 (success). */
void cd_command_retry(u8 com, u8 *param) {
    while (CdControlF(com, param) != 1) {
    }
}

extern s32 msg_queue_write_idx;
extern MsgQueueEntry msg_queue_entries[64];
void *msg_queue_alloc(void) {
    s32 index = msg_queue_write_idx;
    s32 next = index + 1;
    s32 wrapped;
    void *entry = &msg_queue_entries[index];

    msg_queue_write_idx = next;
    wrapped = next;
    if (next < 0) {
        wrapped = index + 0x40;
    }
    msg_queue_write_idx = next - ((wrapped >> 6) << 6);
    return entry;
}

extern u8 cd_status[8];

s32 get_cd_status(void) {
    return cd_status[0];
}

s32 CdSync(s32 mode, u8 *result);
/* Calls cd_command_retry on cd_status, waits with CdSync on the same buffer, then calls get_cd_status and returns its status byte. */
s32 cd_command_sync(void) {
    cd_command_retry(1, cd_status);
    CdSync(0, cd_status);
    return get_cd_status();
}

/* Allocates a 8-byte node: word 0 = value, word 1 = pointer to a copy of
   an 8-byte block at src (or NULL when src is NULL). */
void msg_queue_push(s32 value, void *src) {
    void *node;
    void *copy;

    node = msg_queue_alloc();
    *(s32 *)node = value;
    if (src == NULL) {
        ((void **)node)[1] = NULL;
        return;
    }
    copy = (u8 *)node + 8;
    mem_move(8, src, copy);
    ((void **)node)[1] = copy;
}

void func_8001E39C(void) {
    msg_queue_push(9, 0);
}

void func_8001E3C0(void) {
    msg_queue_push(1, 0);
}

extern s32 msg_queue_read_idx;
extern MsgQueueEntry msg_queue_entries[64];
void *msg_queue_peek(void) {
    return &msg_queue_entries[msg_queue_read_idx];
}

extern s32 msg_queue_read_idx;

void msg_queue_pop(void) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_v0;

    temp_a0 = msg_queue_read_idx;
    temp_v1 = temp_a0 + 1;
    msg_queue_read_idx = temp_v1;
    var_v0 = temp_v1;
    if (temp_v1 < 0) {
        var_v0 = temp_a0 + 0x40;
    }
    msg_queue_read_idx = temp_v1 - ((var_v0 >> 6) << 6);
}

extern s32 msg_queue_read_idx;
extern s32 msg_queue_write_idx;

s32 msg_queue_has_items(void) {
    s32 temp_s0;

    sched_lock();
    temp_s0 = msg_queue_write_idx != msg_queue_read_idx;
    sched_unlock();
    return temp_s0;
}

s32 CdDiskReady(s32 mode);
s32 CdGetDiskType(void);
void thread_change(s32 value);
/* Calls thread_change(0), retries CdDiskReady(1) while it returns 2, then calls CdGetDiskType. */
s32 cd_wait_disk_type(void) {
    do {
        thread_change(0);
    } while (CdDiskReady(1) == 2);
    return CdGetDiskType();
}

extern s8 cd_recovered_flag;
void sector_cache_clear(void);
/* Waits for CdSync, polls cd_wait_disk_type until it returns 2, calls sector_cache_clear, then sets the flag cd_recovered_flag. */
void cd_error_recover(void) {
    CdSync(0, 0);
    do {
    } while (cd_wait_disk_type() != 2);
    sector_cache_clear();
    cd_recovered_flag = 1;
}

void cd_ready_callback_clear(void) {
    CdReadyCallback(0);
}

extern u8 cd_sector_ready_flag;
void cd_teardown(void) {
    cd_sector_ready_flag = 0;
    CdReadyCallback(0);
}

extern s8 D_8002EC6E;

void func_8001E568(s32 arg0) {
    D_8002EC6E = arg0;
}

/* Same code as get_cd_status (boot). */
s32 get_cd_sector_ready(void) {
    return cd_sector_ready_flag;
}

void stream_finish(void);
void stream_sector_put(void *arg);
void cd_sector_poll(void) {
    u8 sector[44];

    if (cd_sector_ready_flag != 0) {
        cd_sector_ready_flag = 0;
        CdGetSector(sector, 0xB);
        if (sector[6] & 0x80) {
            stream_finish();
            return;
        }
        if (sector[6] & 0xA) {
            stream_sector_put(&sector[12]);
        }
    }
}

int DecDCToutSync(int mode);
int DecDCTinSync(int mode);
void cd_sector_poll(void);
/* CD ready callback for mode 1: sets the cd_sector_ready_flag flag, syncs the DecDCT output and input, and calls
 * cd_sector_poll when both report 0. */
void cd_ready_callback(s32 mode) {
    s32 out;

    if ((mode & 0xFF) == 1) {
        cd_sector_ready_flag = 1;
        out = DecDCToutSync(1);
        if ((out | DecDCTinSync(1)) == 0) {
            cd_sector_poll();
        }
    }
}

s32 cd_stream_read_sector(void *buf);
void cd_stream_advance(void);
extern void cd_service_state_set(s32 mode);
/* mode 1: zero a 12-byte buffer, read sector 3 into it and act on the result;
   any other mode: run cd_ready_callback_clear then cd_service_state_set(3). */
void cd_ready_callback_plain(s32 mode) {
    u8 sector[12];
    s32 i;
    u8 *p;

    if ((mode & 0xFF) == 1) {
        i = 11;
        p = &sector[11];
        do {
            *p = 0;
            i -= 1;
            p -= 1;
        } while (i >= 0);
        CdGetSector(sector, 3);
        if (cd_stream_read_sector(sector) != 0) {
            cd_stream_advance();
        }
    } else {
        cd_ready_callback_clear();
        cd_service_state_set(3);
    }
}

void cd_ready_callback_plain();
/* Sets the CD ready callback: mode 1 picks cd_ready_callback (and clears cd_sector_ready_flag), any other mode picks cd_ready_callback_plain. */
void cd_set_ready_callback(s32 mode) {
    void (*callback)();

    if (mode == 1) {
        cd_sector_ready_flag = 0;
        callback = cd_ready_callback;
    } else {
        callback = cd_ready_callback_plain;
    }
    CdReadyCallback(callback);
    CdSyncCallback(0);
}

s32 cd_service_state_get(void);
void cd_service_loop(void) {
    s32 result;
    s32 keep_going;

    do {
        keep_going = 1;
        thread_change(0);
        result = cd_service_state_get();
        if (result == 2) {
            cd_service_state_set(0);
            keep_going = 0;
        }
        if (result == 3) {
            cd_service_state_set(1);
            keep_going = 0;
        }
        cd_command_sync();
        if (get_cd_status() & 0x10) {
            cd_service_state_set(3);
            cd_service_state_set(1);
            keep_going = 0;
            cd_error_recover();
        }
        thread_change(0);
    } while (keep_going);
}

void xa_start_flag_set(void);
void xa_start_flag_clear(void);
void stream_wait_done(void);
void cd_msg_dispatch(void) {
    s32 *msg;

    msg = msg_queue_peek();
    switch (msg[0]) {
    case 0x80:
        xa_start_flag_set();
        break;
    case 0x81:
        xa_start_flag_clear();
        break;
    case 0xA0:
        cd_service_state_set(5);
        cd_set_ready_callback(0);
        break;
    case 0xA2:
        cd_set_ready_callback(1);
        break;
    case 0xA3:
        stream_wait_done();
        break;
    case 0xA1:
        cd_service_loop();
        break;
    case 0xB0:
        spu_set_cd_volume(msg[2]);
        snd_set_cd_volume(-1);
        break;
    case 0xB1:
        snd_set_cd_enabled(1);
        snd_set_cd_volume(-1);
        break;
    case 0xB2:
        snd_set_cd_enabled(0);
        snd_set_cd_volume(-1);
        break;
    }
}

void cd_msg_poll(void) {
    cd_msg_dispatch();
}

extern u8 cd_sync_result[];
/* While reading (status 0x20) issues GetlocP (0x11) and waits; then sends the
 * queued CD message's command, or Nop (1) after polling an 0x80 message. */
void cd_queue_service(void) {
    s32 *msg;

    if (get_cd_status() & 0x20) {
        cd_command_retry(0x11, 0);
        CdSync(0, cd_sync_result);
    }
    if (msg_queue_has_items() != 0) {
        msg = msg_queue_peek();
        if (msg[0] & 0x80) {
            cd_msg_poll();
        } else {
            cd_command_retry(msg[0], (u8 *)msg[1]);
            return;
        }
    }
    cd_command_retry(1, 0);
}

void mem_move(s32 size, void *src, void *dst);
/* Copies the 8-byte block at cd_status to dst; does nothing for a null dst. */
void cd_copy_result(void *dst) {
    if (dst != NULL) {
        mem_move(8, cd_status, dst);
    }
}

s32 cd_sync_wait(s32 mode, void *dst) {
    s32 result;

    result = CdSync(mode, cd_status);
    cd_copy_result(dst);
    if (result != 0) {
        while (get_cd_status() & 0x10) {
            result = 5;
            cd_error_recover();
            cd_command_sync();
        }
    }
    return result;
}

extern u8 cd_pos_minute;
extern u8 cd_pos_second;
extern u8 cd_pos_frame;
s32 cd_get_sector();
s32 cd_get_position(void) {
    u8 pos[4];
    s32 status;

    status = get_cd_status();
    if (status & 0x55) {
        return -1;
    }
    if (!(status & 0x20)) {
        return -1;
    }
    sched_lock();
    pos[0] = cd_pos_minute;
    pos[1] = cd_pos_second;
    pos[2] = cd_pos_frame;
    sched_unlock();
    return cd_get_sector(pos);
}

void cd_queue_service(void);
void xa_update(void);
void cd_thread_main(void) {
    s32 status;

    while (1) {
        status = cd_sync_wait(1, 0);
        if (status != 2) {
            if (status < 3) {
                if (status == 0) {
                    goto skip;
                }
            }
        } else if (msg_queue_has_items()) {
            msg_queue_pop();
        }
        cd_queue_service();
    skip:
        xa_update();
        thread_change(0);
    }
}

void cd_wait_idle(void) {
    do {

    } while (msg_queue_has_items() != 0);
}

extern s32 cd_thread_handle;
/* Runs the three-step teardown when the flag at cd_thread_handle is set; the two
 * parameters are passed through to msg_queue_push (meaning not yet known). */
void cd_cmd_guarded(s32 param_a, s32 param_b) {
    if (cd_thread_handle != 0) {
        sched_lock();
        msg_queue_push(param_a, (void *)param_b);
        sched_unlock();
    }
}

/* Clears 64 x 16-byte records at msg_queue_entries: word 0 = 1, word 4 = 0,
 * bytes 8..15 = 0. Then calls cd_cmd_guarded(1, 0). */
void cd_clear_records(void) {
    u8 *record;
    u8 *field;
    s32 i;
    s32 j;

    record = (u8 *)msg_queue_entries;
    for (i = 0; i < 0x40; i++) {
        *(s32 *)record = 1;
        *(s32 *)(record + 4) = 0;
        field = record + 8;
        for (j = 7; j >= 0; j--) {
            *field++ = 0;
        }
        record += 0x10;
    }
    cd_cmd_guarded(1, 0);
}

int CdMix(CdlATV *vol);
void cd_set_volume(s32 mode) {
    CdlATV vol;

    if (mode == 0) {
        vol.left_to_left = 0x5B;
        vol.left_to_right = 0x5B;
        vol.right_to_left = 0x5B;
        vol.right_to_right = 0x5B;
    } else {
        vol.left_to_left = 0x80;
        vol.left_to_right = 0;
        vol.right_to_left = 0x80;
        vol.right_to_right = 0;
    }
    CdMix(&vol);
}

extern s32 msg_queue_read_idx;
extern s32 msg_queue_write_idx;
extern s8 D_8002EC6C;
extern s8 cd_recovered_flag;

void cd_reset_state(void) {
    msg_queue_read_idx = 0;
    msg_queue_write_idx = 0;
    D_8002EC6C = 0;
    cd_recovered_flag = 0;
    cd_clear_records();
}

extern u8 cd_thread_arg[];
s32 CdInit(void);
void CdSetDebug(s32 level);
void CdDataCallback(void (*callback)(void));
void cd_set_volume(s32 mode);
void cd_stream_reset(void);
void stream_reset(void);
s32 thread_open(void (*handler)(void), u8 *data, s32 mode);
void cd_thread_main(void);
void func_800211B8(void);
/* Boot-time CD setup: retries CdInit until it succeeds, then sets up the CD
   subsystem and its callbacks, and starts the handler cd_thread_handle (-1 = failed). */
void cd_init(void) {
    s32 handle;

    do {

    } while (CdInit() == 0);
    CdSetDebug(0);
    cd_set_volume(snd_get_mode());
    cd_reset_state();
    cd_stream_reset();
    stream_reset();
    CdSyncCallback(0);
    CdReadyCallback(0);
    CdDataCallback(0);
    sched_lock();
    if (cd_thread_handle == 0) {
        handle = thread_open(cd_thread_main, cd_thread_arg, 1);
        cd_thread_handle = handle;
        if (handle == -1) {
            cd_thread_handle = 0;
        }
    }
    sector_cache_clear();
    sched_unlock();
    func_800211B8();
}

/* Closes the CD thread: __builtin_delete(cd_thread_handle). The original is hand-written asm: the
   asm only loads $a0 and falls through into __builtin_delete, which follows it (no call, no frame). */
void cd_thread_close(void) {
    __builtin_delete((void *)cd_thread_handle);
}

void thread_close(s32 th);
/* Compiler delete helper: a null pointer is a no-op, anything else goes to thread_close. */
void __builtin_delete(void *block) {
    if (block != NULL) {
        thread_close((s32)block);
    }
}

s32 cd_get_sector() { /* callers may pass the CdlLOC through (xa_play) */
    return CdPosToInt();
}

void *CdIntToPos(s32 i, u8 *pos);
void *cd_sector_to_msf(s32 i, u8 *pos) {
    return CdIntToPos(i, pos);
}

/* Converts a BCD minute:second:frame triple to a sector count (75 frames/s, 60 s/min). */
s32 cd_msf_to_sector(u8 *msf) {
    s32 sectors;
    s32 minutes;
    s32 seconds;
    s32 frames;

    minutes = msf[0];
    sectors = (((minutes >> 4) * 10) + (minutes & 0xF)) * 4500;
    seconds = msf[1];
    frames = msf[2];
    sectors += (((seconds >> 4) * 10) + (seconds & 0xF)) * 75;
    return sectors + (((frames >> 4) * 10) + (frames & 0xF));
}

static inline s32 int_to_bcd(s32 value)
{
    s32 bcd = value % 10;
    bcd += value / 10 * 16;
    return bcd;
}
/* Sector count to BCD minute/second/frame (75 frames a second). */
u8 *cd_sector_to_bcd_msf(s32 sectors, u8 *out)
{
    out[2] = int_to_bcd(sectors % 75);
    sectors /= 75;
    out[1] = int_to_bcd(sectors % 60);
    sectors /= 60;
    out[0] = int_to_bcd(sectors % 99);
    return out;
}

extern u8 xa_start_flag;

void xa_start_flag_set(void) {
    xa_start_flag = 1;
}

void xa_start_flag_clear(void) {
    xa_start_flag = 0;
}

s32 xa_get_start_flag(void) {
    return xa_start_flag;
}

extern u8 xa_playing_flag;
/* Same code as func_80018D74 (boot). */
void xa_playing_clear(void) {
    xa_playing_flag = 0;
}

extern u8 xa_playing_flag;
/* Same code as get_cd_status (boot). */
s32 xa_playing_get(void) {
    return xa_playing_flag;
}

extern u8 xa_flags_hi[];
extern u8 xa_flags_ext[];
void xa_start_at(s32 index) {
    u8 sp10[8];

    cd_sector_to_msf(index, sp10);
    sched_lock();
    msg_queue_push(0xB, NULL);
    msg_queue_push(0xB2, NULL);
    msg_queue_push(2, sp10);
    msg_queue_push(0x15, NULL);
    msg_queue_push(0xD, xa_flags_hi);
    msg_queue_push(0xE, xa_flags_ext);
    msg_queue_push(0xC, NULL);
    msg_queue_push(0x1B, sp10);
    msg_queue_push(0xB1, NULL);
    msg_queue_push(0x80, NULL);
    func_8001E3C0();
    sched_unlock();
}

extern s32 xa_base_sector;
extern s32 xa_end_sector;

s32 xa_pause(s32 arg0) {
    s32 var_s0;

    var_s0 = cd_get_position();
    if ((var_s0 == -1) || (xa_end_sector < var_s0) || (var_s0 < xa_base_sector)) {
        var_s0 = xa_base_sector;
    }
    sched_lock();
    msg_queue_push(0xB2, 0);
    func_8001E3C0();
    msg_queue_push(0xB, 0);
    msg_queue_push(0x81, 0);
    if (arg0 == 0) {
        func_8001E39C();
        func_8001E3C0();
    }
    sched_unlock();
    return var_s0 - xa_base_sector;
}

extern u8 xa_playing_flag;
// Consumes the one-shot flag xa_playing_flag; if it was set, clears it and
// forwards to xa_pause(0). Returns 0 when the flag was already clear.
s32 xa_pause_if_flagged(void) {
    if (xa_playing_flag == 0) {
        return 0;
    }
    xa_playing_flag = 0;
    return xa_pause(0);
}

void xa_pause_keep_pos(void) {
    xa_pause(1);
}

extern u8 xa_keep_pos_flag;
extern u8 xa_flags_lo[];
void xa_play(s32 unused_arg, s32 skip_sectors, s32 flags_hi, u8 *end_msf, s32 flags) {
    s32 seek_sector;
    s32 end_sector;
    s32 cur_sector;

    seek_sector = skip_sectors;
    if (xa_playing_flag != 0) {
        xa_pause_if_flagged();
    }
    xa_playing_flag = 1;
    cur_sector = cd_get_sector(unused_arg);
    seek_sector += cur_sector;
    xa_base_sector = cur_sector;
    end_sector = cd_msf_to_sector(end_msf);
    end_sector += xa_base_sector;
    if (seek_sector >= end_sector) {
        seek_sector = xa_base_sector;
    }
    xa_flags_ext[0] = (u8) (flags >> 16);
    xa_end_sector = end_sector;
    xa_keep_pos_flag = (u8) flags;
    xa_flags_hi[0] = (u8) (flags_hi >> 16);
    xa_flags_lo[0] = (u8) flags_hi;
    xa_start_at(seek_sector);
}

s32 xa_get_start_flag(void);
void xa_start_at(s32 arg);
s32 xa_pause_if_flagged(void);
extern u8 xa_keep_pos_flag;
/* When xa_get_start_flag reports ready and cd_get_position returns a value
   (not -1) at or above xa_end_sector: if xa_keep_pos_flag is set, run xa_pause_keep_pos
   and xa_start_at(xa_base_sector); otherwise run xa_pause_if_flagged. */
void xa_update(void) {
    s32 index;

    if (xa_get_start_flag() != 0) {
        index = cd_get_position();
        if (index != -1 && index >= xa_end_sector) {
            if (xa_keep_pos_flag != 0) {
                xa_pause_keep_pos();
                xa_start_at(xa_base_sector);
                return;
            }
            xa_pause_if_flagged();
        }
    }
}

s32 xa_get_start_flag(void);
/* Returns the offset of the entry found by clamp_value from xa_base_sector,
 * or -1 when the setup check or the lookup fails. */
s32 music_get_offset(void) {
    s32 index;

    if (xa_get_start_flag() == 0) {
        return -1;
    }
    index = cd_get_position();
    if (index < 0) {
        return -1;
    }
    return clamp_value(index, xa_base_sector, xa_end_sector) - xa_base_sector;
}

extern CdEntry cd_track_table[128];
s32 cdfs_open(s32 name, s32 arg);
u8 * cd_sector_to_bcd_msf(s32 sectors, u8 *out);
/* Searches the CD table (at most 0x80 entries) for id, opens its file and
   sets up the seek range. Returns 0 on success, -2 if the open fails and
   -3 if the id is not in the table. */
s32 music_play_by_id(s32 id, s32 flags, s32 skip) {
    CdEntry *entry;
    s32 count;
    Unaligned32 msf_buf;
    s32 handle[6];

    entry = cd_track_table;
    id = id & 0xFF;
    count = 0;
    for (;;) {
        if (entry->id == 0xFF) {
            return -3;
        }
        count++;
        if (entry->id == id) {
            if (cdfs_open((s32)handle, entry->open_arg) == 0) {
                return -2;
            }
            if (entry->flags & 0x80) {
                cd_sector_to_bcd_msf(cd_msf_to_sector(entry->msf) * 2, (u8 *)&msf_buf);
            } else {
                msf_buf = *(Unaligned32 *)entry->msf;
            }
            xa_play((s32)handle, skip, (entry->msf[3] << 16) | entry->unk_03,
                          (u8 *)&msf_buf, (entry->flags << 16) | flags);
            return 0;
        }
        entry++;
        if (count >= 0x80) {
            return -3;
        }
    }
}

/* Same code as get_movie_table (boot). */
void *cd_track_table_get(void) {
    return cd_track_table;
}

void *cd_track_table_get(void);
/* Scans up to 0x80 twelve-byte records from cd_track_table_get()'s table for the
 * first whose leading byte equals id. Returns NULL on 0xFF terminator or
 * when the scan limit is reached. */
u8 *music_table_find(s32 id) {
    s32 count;
    u8 *rec;
    u8 b;

    rec = cd_track_table_get();
    count = 0;
    for (;;) {
        b = *rec;
        if (b == 0xFF) {
            return NULL;
        }
        count++;
        if (b != id) {
            rec += 0xC;
            if (count < 0x80) {
                continue;
            }
            return NULL;
        }
        return rec;
    }
}

extern u8 xa_keep_pos_flag;
extern u8 xa_playing_flag;
void music_state_reset(void) {
    xa_base_sector = 0;
    xa_end_sector = 0;
    xa_keep_pos_flag = 0;
    xa_start_flag = 0;
    xa_playing_flag = 0;
}

extern s32 stream_slots[];
void stream_slot_clear_all(void) {
    s32 *p;
    s32 i;

    p = stream_slots;
    i = 0;
    do {
        i += 1;
        p[0] = 0;
        p[1] = 0;
        p += 2;
    } while (i < 4);
}

extern s32 stream_buf_base;

s32 stream_hdr_addr(s32 arg0, s32 arg1) {
    return stream_buf_base + (arg0 << 0xB) + (arg1 << 5);
}

extern s32 stream_area_size;
extern s32 stream_buf_base;

s32 stream_data_addr(s32 arg0, s32 arg1) {
    return stream_buf_base + (arg0 << 0xB) + (stream_area_size << 5) + (arg1 * 0x7E0);
}

extern u8 stream_done_flag;
s32 stream_slot_take_ready(s32 *arg0, s32 *arg1) {
    s32 best;
    s32 idx;
    s32 i;
    s32 *p;

    if (stream_done_flag != 0) {
        return -1;
    }
    best = 0;
    idx = -1;
    p = stream_slots;
    for (i = 0; i < 4; i++, p += 2) {
        if (p[0] == 2) {
            if (best < p[1]) {
                best = p[1];
                idx = i;
            }
        }
    }
    if (idx < 0) {
        return 0;
    }
    i = idx * stream_area_size;
    stream_slots[idx * 2] = 3;
    *arg0 = stream_hdr_addr(i, 0);
    *arg1 = stream_data_addr(i, 0);
    return idx + 1;
}

extern s32 stream_area_size;

void stream_slot_addrs(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 temp_lo;

    temp_lo = (arg0 - 1) * stream_area_size;
    *arg1 = stream_hdr_addr(temp_lo, 0);
    *arg2 = stream_data_addr(temp_lo, 0);
}

extern s32 stream_slot_aux[];
void stream_slot_release(s32 count) {
    s32 idx;

    if (count > 0) {
        idx = (clamp_value(count, 1, 4) - 1) * 2;
        stream_slots[idx] = 0;
        stream_slot_aux[idx] = 0;
    }
}

s32 stream_slot_alloc(void) {
    StreamSlot *p;
    s32 i;
    s32 best;
    s32 best_value;

    p = (StreamSlot *)stream_slots;
    for (i = 0; i < 4; i++, p++) {
        if (p->type == 0) {
            return i;
        }
    }
    p = (StreamSlot *)stream_slots;
    best_value = 0x7FFFFFFF;
    best = -1;
    for (i = 0; i < 4; i++, p++) {
        if (p->type == 2) {
            s32 v = p->value;
            if (v < best_value) {
                best_value = v;
                best = i;
            }
        }
    }
    if (best >= 0) {
        p = (StreamSlot *)stream_slots + best;
        p->type = 0;
        p->value = 0;
    } else {
        best = -1;
    }
    return best;
}

extern u8 stream_active_flag;
void stream_slots_reset(void);
/* If the boot flag at stream_active_flag is set, runs the teardown steps (cd_teardown, stream_slots_reset, the 0xB2 and 0xB calls to msg_queue_push with their wrappers), then clears the flag. */
void stream_teardown(void) {
    if (stream_active_flag != 0) {
        cd_teardown();
        stream_slots_reset();
        msg_queue_push(0xB2, 0);
        func_8001E3C0();
        msg_queue_push(0xB, 0);
        func_8001E39C();
        func_8001E3C0();
        stream_active_flag = 0;
    }
}

extern u8 stream_done_flag;
extern void (*stream_done_hook)(void);
/* One-shot: the first call sets the stream_done_flag flag, runs stream_teardown, then calls the hook at stream_done_hook if one is set. */
void stream_finish(void) {
    if (stream_done_flag == 0) {
        stream_done_flag = 1;
        stream_teardown();
        if (stream_done_hook != NULL) {
            stream_done_hook();
        }
    }
}

extern s32 stream_frame_index;
extern s32 stream_cur_slot;

void stream_reset_pos(void) {
    stream_frame_index = 0;
    stream_cur_slot = -1;
}

extern s32 stream_frame_end;
extern s32 stream_frame_start;
extern StreamState *stream_state_ptr;
void stream_frame(StreamSectorHdr *hdr) {
    u32 id;
    u32 size;
    StreamState *slot;

    stream_frame_index = 0;
    stream_cur_slot = stream_slot_alloc();
    size = hdr->frame_size;
    id = hdr->id;
    if (id >= (u32)stream_frame_end) {
        stream_finish();
    }
    size = (size + 0x7FF) >> 11;
    if ((u32)stream_area_size < size) {
        printf("Frame Over Run\n");
    }
    if (stream_cur_slot >= 0 && id >= (u32)stream_frame_start && id < (u32)stream_frame_end && (u32)stream_area_size >= size) {
        slot = (StreamState *)stream_slots + stream_cur_slot;
        slot->state = 1;
        slot->id = id;
        stream_state_ptr = slot;
        stream_cur_slot *= stream_area_size;
        return;
    }
    stream_cur_slot = -1;
}

extern StreamState *stream_state_ptr;
void stream_frame(StreamSectorHdr *hdr);
void stream_sector_put(void *arg) {
    StreamSectorHdr *hdr = arg;
    StreamSectorHdr *dst;
    void *data;
    u8 buf[0x800];

    if (hdr->magic == 0x160) {
        if (hdr->frame == 0) {
            stream_frame(hdr);
        }
        if (stream_state_ptr->state != 2) {
            if (stream_frame_index != hdr->frame || stream_state_ptr->id != hdr->id || stream_cur_slot == -1) {
                stream_state_ptr->state = 0;
            }
            if (stream_state_ptr->state == 1) {
                dst = (StreamSectorHdr *)stream_hdr_addr(stream_cur_slot, stream_frame_index);
                data = (void *)stream_data_addr(stream_cur_slot, stream_frame_index);
                *dst = *hdr;
                CdGetSector(data, 0x1F8);
                stream_frame_index++;
                if (stream_frame_index == hdr->frame_count) {
                    stream_cur_slot = -1;
                    stream_state_ptr->state = 2;
                }
            } else {
                CdGetSector(buf, 0x1F8);
            }
        }
    }
}

void stream_finish(void);
extern u8 stream_done_flag;
/* Poll until cd_command_sync reports bit 0x10: then run stream_finish and
   return. Also returns early once stream_done_flag is set. */
void stream_wait_done(void) {
    while (1) {
        thread_change(0);
        if (cd_command_sync() & 0x10) {
            stream_finish();
            return;
        }
        if (stream_done_flag != 0) {
            return;
        }
    }
}

/* Same code as giant_robot_phase0 (s01). */
void stream_slots_reset(void) {
    stream_slot_clear_all();
    stream_reset_pos();
}

void stream_stop(void) {
    stream_finish();
}

void xa_play_start(void *buf, s32 flags, s32 packed, s32 extra) {
    func_8001E568(extra);
    stream_reset_pos();
    xa_flags_ext[0] = flags | 0x20;
    xa_flags_hi[0] = (s8) (packed >> 0x10);
    xa_flags_lo[0] = packed;
    sched_lock();
    msg_queue_push(0xB, NULL);
    msg_queue_push(0xB2, NULL);
    msg_queue_push(2, buf);
    msg_queue_push(0x15, NULL);
    msg_queue_push(0xD, xa_flags_hi);
    msg_queue_push(0xE, xa_flags_ext);
    msg_queue_push(0xC, NULL);
    msg_queue_push(0xA2, NULL);
    msg_queue_push(0x1B, buf);
    msg_queue_push(0xB1, NULL);
    msg_queue_push(0xA3, NULL);
    sched_unlock();
}

extern s32 stream_area_count;
extern s32 stream_frame_start;
extern s32 stream_frame_end;
s32 stream_setup(StreamFrameParam *param) {
    const char *msg;
    u32 area_count;
    u32 divisor;
    u32 start;
    u32 end;

    xa_pause_if_flagged();
    stream_teardown();
    divisor = param->area_size;
    area_count = param->buffer_size / divisor;
    stream_area_size = divisor;
    stream_area_count = area_count;
    if (area_count < 2) {
        msg = "STREAM:No Free Area\n";
    } else {
        start = param->frame_start;
        end = param->frame_end;
        stream_frame_start = start;
        stream_frame_end = end;
        stream_done_hook = (void (*)(void))param->callback;
        if (start < end) {
            stream_area_count = clamp_value(area_count, 2, 4);
            stream_active_flag = 1;
            stream_done_flag = 0;
            stream_buf_base = param->buffer_base;
            stream_slots_reset();
            return 1;
        }
        msg = "STREAM:Frame Param Err\n";
    }
    printf(msg);
    return 0;
}

extern u8 stream_active_flag;
extern u8 stream_done_flag;
void stream_slot_clear_all(void);
void stream_slots_reset(void);
/* Clears the two boot flags, then runs the stream_slot_clear_all and stream_slots_reset setup steps. */
void stream_reset(void) {
    stream_active_flag = 0;
    stream_done_flag = 0;
    stream_slot_clear_all();
    stream_slots_reset();
}

extern s32 stream_sector_limit;

void stream_set_limit(s32 arg0) {
    stream_sector_limit = arg0;
}

extern s32 stream_sector;

void stream_set_sector(s32 arg0) {
    stream_sector = arg0;
}

extern s32 stream_sector;

s32 stream_get_sector(void) {
    return stream_sector;
}

extern u8 cd_service_state;
/* Same code as vab_busy_set (boot). */
void cd_service_state_set(s32 arg0) {
    cd_service_state = arg0;
}

extern u8 cd_service_state;
/* Same code as get_cd_status (boot). */
s32 cd_service_state_get(void) {
    return cd_service_state;
}

extern s32 stream_buf;

void stream_set_buf(s32 arg0) {
    stream_buf = arg0;
}

extern s32 stream_buf;

s32 stream_get_buf(void) {
    return stream_buf;
}

extern s32 stream_sector;
extern s32 stream_buf;

void cd_stream_advance(void) {
    stream_sector += 1;
    stream_buf += 0x800;
}

s32 cd_stream_read_sector(void *buf) {
    s32 pos = cd_get_sector();
    s32 mode;
    s32 unused[2]; /* keeps the original's 0x20-byte stack frame */

    if (pos != stream_sector) {
        cd_ready_callback_clear();
        mode = 3;
    } else {
        if (stream_sector_limit >= pos) {
            CdGetSector((void *)stream_get_buf(), 0x200);
            return 1;
        }
        cd_ready_callback_clear();
        mode = 2;
    }
    cd_service_state_set(mode);
    return 0;
}

int cdfs_read_status(void) {
    int r = cd_service_state_get();
    switch (r) {
    case 0: r = 1; break;
    case 1: r = -1; break;
    default: r = 0; break;
    }
    return r;
}

extern s32 D_8002EC78[2];
s32 cdfs_start_read(void *src, s32 mode, s32 extra) {
    s32 entries;

    if (cdfs_read_status() == 0) {
        return 0;
    }
    if (extra == 0) {
        return 1;
    }
    xa_pause_if_flagged();
    sched_lock();
    cd_service_state_set(4);
    stream_set_buf(mode);
    entries = cd_get_sector(src);
    stream_set_sector(entries);
    entries -= 1;
    stream_set_limit(entries + extra);
    func_8001E39C();
    func_8001E3C0();
    msg_queue_push(0xE, D_8002EC78);
    func_8001E3C0();
    msg_queue_push(2, src);
    msg_queue_push(0xA0, NULL);
    msg_queue_push(6, NULL);
    msg_queue_push(0xA1, NULL);
    func_8001E39C();
    func_8001E3C0();
    sched_unlock();
    return 1;
}

s32 cdfs_start_read(void *src, s32 mode, s32 extra);
s32 cdfs_try_read(s32 arg0, s32 arg1, s32 arg2) {
    return cdfs_start_read((void *)arg0, arg1, arg2);
}

void cd_seek(s32 arg0) {
    cd_cmd_guarded(2, arg0);
    cd_cmd_guarded(0x15, 0);
}

int cdfs_read_status(void);
/* Maps the result of cdfs_read_status to a sign: 1 when it returns 0, -1 when it returns a negative value, 0 otherwise. */
s32 cdfs_read_done(void) {
    s32 result = cdfs_read_status();

    if (result == 0) {
        return 1;
    }
    return -(result < 1);
}

/* Polls cdfs_read_status, calling frame_wait_ticks(0) while it returns 0; returns that status, or 0 if it is positive. */
s32 cdfs_wait_read(void) {
    s32 status;

    while ((status = cdfs_read_status()) == 0) {
        frame_wait_ticks(0);
    }
    if (status > 0) {
        status = 0;
    }
    return status;
}

/* Retry cdfs_try_read (waiting a frame between tries) until it succeeds,
   then retry the follow-up check cdfs_wait_read until it reports no error. */
s32 cdfs_read(s32 arg0, s32 arg1, s32 arg2) {
    do {
        while (cdfs_try_read(arg0, arg1, arg2) == 0) {
            frame_wait_ticks(0);
        }
    } while (cdfs_wait_read() < 0);
    return 0;
}

void cd_stream_reset(void) {
    stream_set_sector(0);
    stream_set_limit(0);
    cd_service_state_set(0);
}

void stream_depth_check(s32 *table, u8 *path) {

    u8 buf[16];
    u8 *p;
    s32 depth;
    s32 i;
    u8 c;

    p = buf;
    depth = 0;
    if (*path == '\\' || *path == '/') {
        path++;
    }
    for (;;) {
        c = *path++;
        if (c <= ' ' || c == ';') {
            break;
        }
        if (depth >= 8) {
            printf("DEPTH ERROR\n");
            break;
        }
        if (c == '\\' || c == '/') {
            *p = 0;
            str_copy(buf, ((CdPathTable *)table)->names[depth]);
            depth++;
            p = buf;
        } else {
            *p++ = c;
        }
    }
    *p = 0;
    str_copy(buf, ((CdPathTable *)table)->names[depth]);
    ((CdPathTable *)table)->depth = depth;
    for (i = 0; i <= ((CdPathTable *)table)->depth; i++) {
        str_copy_upper(((CdPathTable *)table)->names[i], ((CdPathTable *)table)->names[i]);
    }
    str_concat(((CdPathTable *)table)->names[depth], ";1", ((CdPathTable *)table)->names[depth]);
}

extern CdfsPathRecord cdfs_path_records[128];
extern s32 D_80039E2C;
s32 boot_str_length(u8 *str);
s32 cdfs_path_chain_match(u8 *base, s32 index, s32 rec) {
    u8 *key;
    CdfsPathRecord *e;

again:
    if (rec == 0) {
        return 1;
    }
    key = base + (index * 16 + 4);
    e = &cdfs_path_records[rec];
    if (mem_equal(boot_str_length(key) + 1, e->name, key) == 0) {
        return 0;
    }
    index--;
    rec = e->next;
    goto again;
}

extern s32 cdfs_path_count;
/* Returns the first index in [1, cdfs_path_count) for which cdfs_path_chain_match returns 1, or -1 if none (0 when depth is 0). */
s32 cdfs_path_find(u8 *base, s32 depth) {
    s32 i;

    if (depth == 0) {
        return 0;
    }
    for (i = 1; i < cdfs_path_count; i++) {
        if (cdfs_path_chain_match(base, depth - 1, i) == 1) {
            return i;
        }
    }
    return -1;
}

extern BootBlock84 cdfs_path_table;
extern s32 cdfs_path_index;
s32 cdfs_path_resolve(BootBlock84 *src) {
    s32 r = cdfs_path_find((u8 *)src, src->w[0]);
    cdfs_path_table = *src;
    cdfs_path_index = r;
    return r;
}

s32 sector_cache_get(u8 *pos);
/* Opens a stream at sector index: position 0, buf = that sector's data. */
void sector_stream_open(SectorStream *s, s32 index) {
    u8 pos[4];

    s->pos = 0;
    s->sector = index;
    cd_sector_to_msf(index, pos);
    s->buf = (u8 *)sector_cache_get(pos);
}

/* Copies len bytes from the stream to dst, fetching the next sector as needed. */
void sector_stream_read(SectorStream *s, s32 len, u8 *dst) {
    u8 sectorPos[8];
    s32 pos;

    pos = s->pos;
    if (pos + len >= 0x801) {
        do {
            s32 chunk = 0x800 - pos;
            mem_move(chunk, s->buf + pos, dst);
            dst += chunk;
            len -= chunk;
            pos = 0;
            s->sector++;
            cd_sector_to_msf(s->sector, sectorPos);
            s->buf = (u8 *)sector_cache_get(sectorPos);
        } while (len >= 0x801);
    }
    mem_move(len, s->buf + pos, dst);
    pos += len;
    s->pos = pos;
}

u8 *cdfs_lookup(s32 index, s32 *table, u8 *out) {
    u8 buf[0x4C0];
    u8 stream[0x10];
    u8 *b;
    SectorStream *st;
    s32 left;
    s32 n, t;

    sector_stream_open((SectorStream *)stream, index);
    b = buf;
    sector_stream_read((SectorStream *)stream, 1, b);
    sector_stream_read((SectorStream *)stream, buf[0] - 1, buf + 1);
    st = (SectorStream *)stream;
    left = read_be32(buf + 0xA);
    for (;;) {
        if (left <= 0) return 0;
        sector_stream_read(st, 1, b);
        left--;
        if (b[0] != 0) {
            sector_stream_read(st, b[0] - 1, b + 1);
            t = left + 1;
            n = b[0];
            left = t - n;
            if (mem_equal(b[0x20], (u8 *)table + (table[0] * 16 + 4), b + 0x21)) {
                cd_sector_to_msf(read_be32(b + 2), out);
                *(s32 *)(out + 4) = read_be32(b + 0xA);
                str_copy((u8 *)table + (table[0] * 16 + 4), out + 8);
                return out;
            }
        }
    }
}

extern s32 cdfs_path_count;
extern CdfsPathRecord cdfs_path_records[128];
extern s32 D_80039E2C;
/* Clears cdfs_path_records and D_80039E2C (= cdfs_path_records[0].next, kept as a scalar for the codegen), and the 16 bytes after the first word,
 * 128 times over. Clears the same block each pass. */
void cdfs_path_reset(void) {
    s32 entry;
    s32 byte_idx;
    u8 *byte_ptr;
    s32 *block;

    cdfs_path_count = 0;
    entry = 0;
    block = &cdfs_path_records[0].pad0;
    for (; entry < 0x80; entry++) {
        byte_ptr = (u8 *)block + 8;
        byte_idx = 0xF;
        D_80039E2C = 0;
        *block = 0;
        do {
            *byte_ptr = 0;
            byte_idx--;
            byte_ptr++;
        } while (byte_idx >= 0);
    }
}

/* Parses the ISO9660 path table into cdfs_path_records (at most 128). */
s32 cdfs_path_table_read(u8 *table, s32 len) {
    CdfsPathRecord *rec;
    u8 *name;
    s32 n;

    rec = cdfs_path_records;
    cdfs_path_count = 0;
    if (len > 0) {
        name = rec->name;
        while (len > 0) {
            if (cdfs_path_count >= 0x80) {
                break;
            }
            n = *table;
            mem_move(n, table + 8, name);
            *((u8 *)rec + *table + 8) = 0;
            *(s32 *)(name - 4) = read_le16(table + 6) - 1;
            rec->pad0 = read_be32(table + 2);
            n = round_up(n + 8, 2);
            table += n;
            len -= n;
            name += sizeof(CdfsPathRecord);
            rec++;
            cdfs_path_count++;
        }
    }
    return cdfs_path_count;
}

extern u8 cdfs_pvd_loc[];
s32 cdfs_path_table_read(u8 *table, s32 len);
/* Reads the ISO9660 primary volume descriptor and loads the path table. */
void cdfs_init(void) {
    u8 sector[0x1000];
    u8 pos[8];
    u8 *pvd;
    u8 *msf;
    s32 len;

    pvd = sector;
    cdfs_read((s32)cdfs_pvd_loc, (s32)pvd, 1);
    if (mem_equal(5, "CD001", pvd + 1) == 0) {
        printf("NO CD-ROM DISC\n");
        while (1) {
        }
    }
    len = read_be32(pvd + 0x84);
    if (len > 0x800) {
        printf("PATH TABLE LENGTH ERROR\n");
        while (1) {
        }
    }
    msf = pos;
    cd_sector_to_msf(*(s32 *)(pvd + 0x8C), msf);
    cdfs_read((s32)msf, (s32)sector, 1);
    cdfs_path_table_read(sector, len);
}

s32 cdfs_path_verify(s32 *table) {
    s32 count;
    s32 offset;
    u8 *entry;
    BootBlock84 *block;

    block = &cdfs_path_table;
    count = *table;
    if (count == 0) {
        return 0;
    }
    if (count != block->w[0]) {
        return -1;
    }
    if (count > 0) {
        offset = (count * 0x10) + 4;
        do {
            entry = (u8 *)table + offset;
            if (mem_equal(boot_str_length(entry) + 1, entry, (u8 *)block + offset) == 0) {
                return -1;
            }
            count -= 1;
            offset -= 0x10;
        } while (count > 0);
    }
    return cdfs_path_index;
}

s32 boot_str_length(u8 *s);
/* Appends "\" and name (skipping a leading "\" on name) to dir, copying into dst. */
void cdfs_path_join(u8 *dir, u8 *name, u8 *dst) {
    if (*name == '\\') {
        name++;
    }
    str_copy(dir, dst);
    dst += boot_str_length(dst);
    *dst = '\\';
    str_copy(name, dst + 1);
}

s32 *get_sys_root_path(void);
void stream_depth_check(s32 *table, u8 *path);
/* Looks up a CD file: joins its path (from the root when fromRoot is set), verifies or resolves it, then reads the record. */
s32 cdfs_open_impl(s32 fromRoot, s32 out, s32 filename) {
    s32 table[34];
    u8 path[0x80];
    s32 idx;

    if (!fromRoot)
        cdfs_path_join((u8 *)get_sys_root_path(), (u8 *)filename, path);
    else
        cdfs_path_join("", (u8 *)filename, path);
    stream_depth_check(table, path);
    idx = cdfs_path_verify(table);
    if (idx >= 0 || (idx = cdfs_path_resolve((BootBlock84 *)table)) >= 0)
        return (s32)cdfs_lookup(cdfs_path_records[idx].pad0, table, (u8 *)out);
    return 0;
}

s32 cdfs_open_impl(s32 mode, s32 name, s32 arg);
/* Opens a CD file with mode 0 (the shared open routine, cdfs_open_impl); returns its result. */
s32 cdfs_open(s32 name, s32 arg) {
    return cdfs_open_impl(0, name, arg);
}

/* Same as cdfs_open but with mode 1 (the shared open routine, cdfs_open_impl); returns its result. */
s32 cdfs_open_from_root(s32 name, s32 arg) {
    return cdfs_open_impl(1, name, arg);
}

s32 cdfs_load_file(s32 mode, void *name, u8 *dst, s32 size) {
    u8 file[0x18];
    u8 sector[0x800];
    u8 tail[8];
    s32 sectors;
    s32 bytes;
    s32 status;

    if (cdfs_open((s32)file, (s32)name) == 0) {
        return -1;
    }
    if (size == 0) {
        size = *(s32 *)(file + 4);
    }
    if (mode == 1) {
        size = round_up(size, 0x800);
    }
    sectors = size / 0x800;
    if (sectors > 0) {
        cdfs_try_read((s32)file, (s32)dst, sectors);
    }
    if (mode == 0) {
        cd_sector_to_msf(cd_get_sector(file) + sectors, tail);
        bytes = sectors << 11;
        status = cdfs_wait_read();
        cd_wait_idle();
        if (status < 0) {
            while (cdfs_read((s32)file, (s32)dst, sectors) < 0) {
            }
        }
        dst += bytes;
        while (cdfs_read((s32)tail, (s32)sector, 1) < 0) {
        }
        mem_move(size - bytes, sector, dst);
    }
    return size;
}

extern char cdfs_msg_file_not_found[];
/* Opens the CD file `name` into a 0x98-byte local handle and returns handle word 1.
   On failure prints cdfs_msg_file_not_found with the name and returns -1. */
s32 cdfs_find(s32 name) {
    s32 handle[38];

    if (cdfs_open((s32)handle, name) == 0) {
        printf(cdfs_msg_file_not_found, name);
        return -1;
    }
    return handle[1];
}

extern u8 pc_init_flag;
void PCinit(void);
s32 PCopen(u8 *path, s32 mode, s32 flags);
s32 PClseek(s32 fd, s32 offset, s32 whence);
void PCclose(s32 fd);
s32 *get_sys_root_path(void);
/* Builds the path of `name` under the base dir into buf, opens it with PCopen,
   stores its size (seek to end) in info->size and closes it. Returns info, or 0 if open failed. */
s32 pc_file_stat(FileInfo *info, s32 name, char *buf) {
    s32 fd;

    if (pc_init_flag == 0) {
        PCinit();
        pc_init_flag = 1;
    }
    cdfs_path_join((u8 *)get_sys_root_path(), (u8 *)name, (u8 *)buf);
    fd = PCopen((u8 *)buf, 0, 0);
    if (fd < 0) {
        return 0;
    }
    info->size = PClseek(fd, 0, 2);
    PClseek(fd, 0, 0);
    PCclose(fd);
    return (s32)info;
}

extern s32 pc_file_stat(FileInfo *info, s32 name, char *buf);
s32 pc_file_size(s32 name) {
    FileInfo info;
    char buf[0x80];

    if (pc_file_stat(&info, name, buf) == 0) {
        printf(cdfs_msg_file_not_found, name);
        return -1;
    }
    return info.size;
}

s32 PCread(s32 fd, void *buf, s32 size);
s32 pc_file_read(s32 unused, s32 name, u8 *dst, s32 size) {
    char path[0x80];
    FileInfo info;
    s32 fd;
    s32 total;
    s32 chunk;
    s32 fsize;

    if (pc_file_stat(&info, name, path) == 0) {
        return -1;
    }
    fsize = info.size;
    if (size == 0) {
        size = fsize;
    }
    total = clamp_value(size, 0, fsize);
    size = total;
    fd = PCopen(path, 0, 0);
    if (fd < 0) {
        return -1;
    }
    PClseek(fd, 0, 0);
    if (total > 0x8000) {
        chunk = 0x8000;
        do {
            PCread(fd, dst, 0x8000);
            size -= chunk;
            dst += chunk;
        } while (size > chunk);
    }
    PCread(fd, dst, size);
    PCclose(fd);
    return total;
}

s32 cdfs_file_size(s32 name) {
    return cdfs_find(name);
}

s32 cdfs_check_file(s32 name) {
    return cdfs_find(name);
}

s32 cdfs_load_file(s32 mode, void *name, u8 *dst, s32 size);
/* Calls the shared routine cdfs_load_file with mode 0; returns its result. */
s32 cdfs_read_file(void *name, u8 *dst, s32 size) {
    return cdfs_load_file(0, name, dst, size);
}

/* Calls the shared routine cdfs_load_file with mode 0; returns its result. */
s32 read_foreground(void *name, u8 *dst, s32 size) {
    return cdfs_load_file(0, name, dst, size);
}

/* Calls the shared routine cdfs_load_file with mode 1; returns its result. */
s32 read_background(void *name, u8 *dst, s32 size) {
    return cdfs_load_file(1, name, dst, size);
}

/* Calls the shared routine cdfs_load_file with mode 1; returns its result. */
s32 func_800210EC(void *name, u8 *dst, s32 size) {
    return cdfs_load_file(1, name, dst, size);
}

extern BootBlock84 cdfs_path_table;
extern s32 cdfs_path_index;
void cdfs_table_reset(void) {
    s32 i;
    s32 *base;
    s8 *p;

    i = 0;
    base = cdfs_path_table.w;
    p = (s8 *)(base + 1);
    cdfs_path_index = -1;
    base[0] = 0;
    do {
        mem_set(p, 0x10, 0);
        i += 1;
        p += 0x10;
    } while (i < 8);
}

void cdfs_reset(void) {
    cdfs_path_reset();
    cdfs_init();
    cdfs_table_reset();
}

void func_800211B8(void) {
    /* Unused: the original's 0x30-byte frame needs this padding to match. */
    s32 unused[6];

    cdfs_reset();
}

extern SectorCacheEntry sector_cache[7];
/* Clears the header of each record, then spins a countdown after each one. */
void sector_cache_clear(void) {
    s32 i;
    s32 countdown;
    SectorCacheEntry *rec;

    rec = sector_cache;
    i = 0;
    do {
        countdown = 0x7FF;
        rec->flag = 0;
        rec->pos_tail[0] = 0;
        rec->pos_tail[1] = 0;
        rec->pos_tail[2] = 0;
        rec->age = 0;
        while (countdown >= 0) {
            countdown -= 1;
        }
        i += 1;
        rec += 1;
    } while (i < 7);
}

void sector_cache_touch(s32 idx) {
    s32 old;
    s32 i;

    old = sector_cache[idx].age;
    i = old + 2;
    sector_cache[idx].age = old + 1;
    if (i > 0x3FFFFFFF) {
        for (i = 0; i < 7; i++) {
            sector_cache[i].age /= 2;
        }
    }
}

void *sector_cache_alloc(u8 *src) {
    SectorCacheEntry *best;
    SectorCacheEntry *cur;
    s32 minVal;
    s32 i;

    minVal = 0;
    best = sector_cache;
    cur = sector_cache;
    i = 6;
    do {
        if (minVal >= cur->age) {
            minVal = cur->age;
            best = cur;
        }
        i -= 1;
        cur++;
    } while (i >= 0);

    best->age = 1;
    best->flag = src[0];
    best->pos_tail[0] = src[1];
    best->pos_tail[1] = src[2];
    return best->sector_data;
}

/* Looks up the CD sector at pos in the sector cache, reading it on a miss.
   keep != 0: returns the cached buffer; else copies it to dst and returns whether it was cached. */
s32 sector_cache_fetch(s32 keep, u8 *pos, void *dst) {
    SectorCacheEntry *rec;
    s32 i;
    u8 *buf;
    u8 p0, p1, p2;

    rec = sector_cache;
    p0 = pos[0];
    p1 = pos[1];
    p2 = pos[2];
    for (i = 0; i < 7; i++, rec++) {
        if (rec->flag == p0 && rec->pos_tail[0] == p1 && rec->pos_tail[1] == p2) {
            if (keep == 0) {
                mem_move(0x800, rec->sector_data, dst);
                sector_cache_touch(i);
                return 1;
            }
            sector_cache_touch(i);
            return (s32)rec->sector_data;
        }
    }
    buf = sector_cache_alloc(pos);
    cdfs_read((s32)pos, (s32)buf, 1);
    if (keep == 0) {
        mem_move(0x800, buf, dst);
        return 0;
    }
    return (s32)buf;
}

s32 sector_cache_read(u8 *pos, void *dst) {
    return sector_cache_fetch(0, pos, dst);
}

s32 sector_cache_get(u8 *pos) {
    return sector_cache_fetch(1, pos, 0);
}

char cdfs_msg_file_not_found[20] = "File Not Found:%s\n";

s32 cdfs_read(s32 arg0, s32 arg1, s32 arg2);
void unpex_decompress(void *src, s32 dst);
extern char exec_header_read_error_msg[]; /* "ExecLoad: Header Read Error\n" */
extern char exec_program_read_error_msg[]; /* "ExecLoad: Program Read Error\n" */
/* Loads the PS-X EXE header and program from the open CD file; flags != 0 unpacks the program to t_addr. */
s32 exec_load(s32 flags, char *name, ExecImageHeader *exec) {
    u8 sector[0x800];
    s32 file[2];
    s32 unused[4]; /* stack padding: the frame is 0x840 bytes in the original */
    u8 *dst;
    s32 size;
    s32 rounded;

    if (cdfs_open((s32)file, (s32)name) == 0) {
        return -1;
    }
    size = round_up(file[1], 0x800);
    rounded = (size < 0) ? size + 0x7FF : size;
    size = rounded >> 11;
    size -= 1;
    while (cdfs_read((s32)file, (s32)sector, 1) == -1) {
        printf("ExecLoad: Header Read Error\n");
    }
    *exec = *(ExecImageHeader *)(sector + 0x10);
    cd_sector_to_msf(cd_get_sector((s32)file) + 1, (u8 *)file);
    if (flags != 0) {
        dst = (u8 *)(flags & ~3);
    } else {
        dst = (u8 *)exec->t_addr;
    }
    while (cdfs_read((s32)file, (s32)dst, size) == -1) {
        printf("ExecLoad: Program Read Error\n");
    }
    if (flags != 0) {
        unpex_decompress(dst, exec->t_addr);
    }
    return 0;
}

extern void unpex_decompress(void *src, s32 dst);
s32 exec_load_mem(u32 image, s32 size, ExecImageHeader *exec) {
    s32 unused[6];
    u8 *base;
    ExecImageHeader *dst;

    base = (u8 *)(image & ~3);
    dst = exec;
    *dst = *(ExecImageHeader *)(base + 0x10);
    base += 0x800;
    image &= 1;
    if (image) {
        unpex_decompress(base, exec->t_addr);
    } else {
        mem_move(size, base, (void *)exec->t_addr);
    }
    return 0;
}

s32 Exec(PsxExec *exec, s32 argc, char **argv);
/* Runs the loader setup, clears s_addr in the EXEC header, then starts the program with one argument. */
void exec_run(PsxExec *exec) {
    cache_flush_critical();
    exec->s_addr = 0;
    Exec(exec, 1, NULL);
}

s32 exec_load(s32 flags, char *name, ExecImageHeader *exec);
s32 exec_load_mem(u32 image, s32 size, ExecImageHeader *exec);
void exec_run(PsxExec *exec);
s32 exec_by_name(s32 flags, char *name) {
    ExecImageHeader exec;
    s32 size;

    if (flags & 2) {
        size = cdfs_file_size((s32)name);
        if (size < 0) {
            printf("File not Found\n");
        } else {
            exec_load_mem(flags, size, &exec);
        }
        goto run;
    }
    if (exec_load(flags, name, &exec) < 0) {
        printf("No Exec File:%s\n", name);
        return 0;
    }
run:
    exec_run((PsxExec *)&exec);
    return 1;
}

extern s32 pad_send_buf[];
extern s32 D_8003E374[];
extern s32 D_8003E36C[];
extern u8 D_8003E388[];
/* Clears two 4-byte slots: the word tables at E36C and E374, the byte at E388,
   and the four bytes of each slot in pad_send_buf. */
void pad_state_clear(void) {
    s32 i;
    s32 j;
    s8 *p;

    for (i = 0; i < 2; i++) {
        D_8003E36C[i] = 0;
        D_8003E374[i] = 0;
        D_8003E388[i] = 0;
        p = (s8 *)&pad_send_buf[i];
        for (j = 3; j >= 0; j--) {
            p[j] = 0;
        }
    }
}

extern s8 event_flags;
/* Sets the byte at event_flags and the one before it to 1. */
void event_flags_set(void) {
    s8 *cell;
    s32 remaining;
    s32 value;

    value = 1;
    remaining = 1;
    cell = &event_flags;
    do {
        *cell = value;
        remaining -= 1;
        cell -= 1;
    } while (remaining >= 0);
}

extern s8 event_flags;
/* Clears the byte at event_flags and the one before it. */
void event_flags_clear(void) {
    s8 *p;
    s32 i;

    i = 1;
    p = &event_flags;
    do {
        *p = 0;
        i -= 1;
        p -= 1;
    } while (i >= 0);
}

extern u8 pad_buffers[0x80];
/* Sets up the pad buffers (0x40 bytes each), waits until the pad answers, then sends the 4-byte command block. */
void pad_setup(void) {
    InitPAD(pad_buffers, 0x40, pad_buffers + 0x40, 0x40);
    while (StartPAD() == 0) {
    }
    pad_state_clear();
    SendPAD((char *)pad_send_buf, 4, (char *)pad_send_buf + 4, 4);
}

void StopPAD(void);
/* Same code as spufunc_flush (boot). */
void pad_stop(void) {
    StopPAD();
    ChangeClearPAD(0);
    pad_state_clear();
}

extern u8 pad_type_byte;
extern u8 pad_port_bytes[];
/* Returns p[4] - 0x80 of the first pad (or multitap slot) whose type nibble is
   0x20 and id nibble 3, else 0. The goto loop and the do-while(0) around the
   found block keep loop.c's notes such that reorg predicts the exit taken. */
s32 pad_analog_axis(void) {
    u8 type;
    u8 *pad;
    s32 ret = 0;
    s32 slot;

    pad = pad_buffers;
    if (*pad == 0xFF) {
        pad_port_bytes[0] = 0;
        return 0;
    }
    type = pad_type_byte;
    type &= 0xF0;
    if (type == 0x80) {
        pad = pad_buffers + 2;
        slot = 0;
    search:
        if (pad[0] == 0) goto found;
        slot++;
        pad += 8;
        if (slot < 4) goto search;
        return 0;
        do {
        found:
            type = pad[1];
            type &= 0xF0;
        } while (0);
    }
    if (type == 0x20) {
        ret = 0;
        if ((pad[1] & 0xF) == 3) ret = pad[4] - 0x80;
    }
    return ret;
}

/* Reads port 0's pad (or the first multitap slot holding one): stores the
   active-high button word in D_8003E36C[port], adds the analog-stick bits
   (type 0x20 with id 3: sticks 5..7 pushed past 0x10; type 0x70: stick
   6/7 near either end), marks the port in pad_port_bytes, and copies the word to
   D_8003E374[port]. With no pad answering it returns the latched word once
   if D_8003E388 is set, else 0. The goto loop and the do-while(0) around the
   found block keep loop.c's notes as in pad_analog_axis; the table base in
   its own variable, set before the index, keeps sched1's order (lui before
   sll). */
s32 pad_read_buttons(void) {
    u8 *pad = pad_buffers;
    s32 port = 0;
    u8 type;
    s32 slot;
    u8 stick_x;
    u8 stick_y;
    s32 *buttons;
    s32 *button_table;
    s32 raw;

    if (pad[0] == 0xFF) {
        pad_port_bytes[port] = 0;
        if (D_8003E388[port] != 0) {
            D_8003E388[port] = 0;
            raw = D_8003E374[port];
            return raw;
        }
        return 0;
    }
    type = pad_type_byte;
    type &= 0xF0;
    if (type == 0x80) {
        pad += 2;
        slot = 0;
    search:
        if (pad[0] == 0) {
            goto found;
        }
        do {
            slot++;
            pad += 8;
        } while (0);
        if (slot < 4) {
            goto search;
        }
        return 0;
        do {
        found:
            type = pad[1];
        } while (0);
        type &= 0xF0;
    }
    if (type == 0x40 || type == 0x20 || type == 0x70) {
        raw = pad[2] << 8;
        raw |= pad[3];
        raw = ~raw;
        button_table = D_8003E36C;
        buttons = button_table + port;
        *buttons = raw & 0xFFFF;
        pad_port_bytes[port] = 1;
        if (type == 0x20) {
            if ((pad[1] & 0xF) == 3) {
                if (pad[5] >= 0x10) {
                    *buttons |= 0x40;
                }
                if (pad[6] >= 0x10) {
                    *buttons |= 0x80;
                }
                if (pad[7] >= 0x10) {
                    *buttons |= 4;
                }
            }
        } else if (type == 0x70) {
            stick_x = pad[6];
            stick_y = pad[7];
            if (stick_x > 0xE0) {
                *buttons |= 0x2000;
            }
            if (stick_x < 0x20) {
                *buttons |= 0x8000;
            }
            if (stick_y > 0xE0) {
                *buttons |= 0x4000;
            }
            if (stick_y < 0x20) {
                *buttons |= 0x1000;
            }
        }
    } else {
        pad_port_bytes[port] = 0;
    }
    D_8003E374[port] = D_8003E36C[port];
    return D_8003E36C[port];
}

extern u8 pad_port_bytes[];
/* Returns table entry `index` for index 0..1, otherwise -1. */
s32 get_pad_port_byte(s32 index) {
    if (index < 2) {
        return *(pad_port_bytes + index);
    }
    return -1;
}

extern s32 pad_send_buf[];
s32 *get_pad_send_buf(s32 index) {
    return &pad_send_buf[index];
}

void func_80021C00(void) {
}

void func_80021C08(void) {
}
