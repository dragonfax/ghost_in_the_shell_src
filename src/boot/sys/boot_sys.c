/* boot_sys: one of boot's own original source files (scripts/objmap.py); part of src/boot/main.c's unit, included there. */

extern s32 dct_reset_done_flag;
void DecDCTReset(s32 mode);
/* Resets the MDEC/DCT decoder (PsyQ DecDCTReset). Mode 0 is passed through only on the first call (which
 * sets dct_reset_done_flag); after that a mode 0 request resets with mode 1. */
void dct_reset(s32 mode) {
    if (mode == 0) {
        if (dct_reset_done_flag == 0) {
            dct_reset_done_flag = 1;
        } else {
            mode = 1;
        }
    }
    DecDCTReset(mode);
}

void InitGeom(void);
/* Same code as pause_changed (s01). */
void geom_init(void) {
    InitGeom();
}

/* Hand-written: no frame, $ra kept in $t6 and returned through `jr $t6`, bytes copied through $at, a trapping
 * `sub`. unpex_last_word_get returns an address inside this code. */
#ifdef NON_MATCHING
/* Decompresses a PEX stream (format in scripts/unpex.py) from src (starting at the size word) to dst and returns
   the number of bytes written. C companion of hand-written asm (not compiled): the asm keeps $ra in $t6 and
   returns with `jr $t6`, holds the bit buffer, bit count and pointers in $t0-$t5, copies bytes through $at, and
   computes the size with a trapping `sub`. */
s32 unpex_decompress(void *src, s32 dst) {
    u8 *in = (u8 *)src + 4; /* skip the size word */
    u8 *out = (u8 *)dst;
    u8 *match;
    s32 flags = *in++;
    s32 nbits = 7;
    s32 offset;
    s32 len;

#define GET_BIT() \
    ((nbits <= 0 ? (nbits = 8, flags = *in++) : 0), nbits--, (flags >> nbits) & 1)

    *out++ = *in++; /* the first byte is always a literal */
    for (;;) {
        while (!GET_BIT()) { /* 0: literal */
            *out++ = *in++;
        }
        if (!GET_BIT()) { /* 10 b: short match, b == 0 ends the stream */
            offset = *in++;
            if (offset == 0) {
                return (s32)out - dst;
            }
            offset -= 256;
        } else { /* 11 b xxxx: long match */
            offset = *in++ - 256;
            offset = (offset << 1) | GET_BIT();
            offset = (offset << 1) | GET_BIT();
            offset = (offset << 1) | GET_BIT();
            offset = (offset << 1) | GET_BIT();
            offset -= 255;
        }
        match = out + offset;
        len = 1; /* Elias-gamma length; copies len + 1 bytes */
        if (GET_BIT()) {
            do {
                len = (len << 1) | GET_BIT();
            } while (GET_BIT());
        }
        do {
            *out++ = *match++;
        } while (--len >= 0);
    }
#undef GET_BIT
}
#else
INCLUDE_ASM("../src/boot/asm", unpex_decompress);
#endif

#ifdef NON_MATCHING
extern s32 D_80021E80;
/* Returns the word at D_80021E80, an address inside unpex_decompress (its last instruction). C companion of
   hand-written asm (not compiled): the asm reaches it with `la $at` + `lw`, which C can't do on a label in code. */
s32 unpex_last_word_get(void) {
    return D_80021E80;
}
#else
/* hand-written: loads a word inside unpex_decompress through `la $at` (config/not_c_manual.txt) */
INCLUDE_ASM("../src/boot/asm", unpex_last_word_get);
#endif

void func_80021E98(void) {
}

void func_80021EA0(void) {
    frame_wait_ticks(0);
}

void func_80021EC0(void) {
}

void func_80021EC8(void) {
}

void func_80021ED0(void) {
}

void func_80021ED8(void) {
}

void func_80021EE0(void) {
}

void func_80021EE8(void) {
}

void func_80021EF0(void) {
}

void func_80021EF8(void) {
}

void func_80021F00(void) {
}

void func_80021F08(void) {
}

void func_80021F10(void) {
}

extern u8 font_fallback_glyph[32];
void *Krom2RawAdd(u32 code);
/* Maps a one-byte character to a 0x82xx font code (codes from 0x61 up are shifted by one first),
 * then looks the glyph up with Krom2RawAdd. Falls back to font_fallback_glyph when there is no glyph. */
void *font_glyph_get(u32 code) {
    void *glyph;

    if ((code >> 8) == 0) {
        if (code >= 0x61) {
            code += 1;
        }
        code += 0x821F;
    }
    glyph = Krom2RawAdd(code);
    if (glyph == (void *)-1) {
        glyph = font_fallback_glyph;
    }
    return glyph;
}

void thread_set_current(s32 idx) {
    Tcb **cur_slot;
    Tcb *tcbs;
    Tcb *tcb;

    cur_slot = *(Tcb ***)0x108;
    tcbs = *(Tcb **)0x110;
    idx &= 0xFFFFFF;
    if (idx < 4) {
        tcb = &tcbs[idx];
        if (tcb->status == 0x4000) {
            *cur_slot = tcb;
        }
    }
}

extern s32 sched_counter;
extern ThreadSlot sched_thread_slots[4];
void thread_schedule(void) {
    s32 prev_counter;
    s32 counter;
    s32 ring_idx;
    s32 count;
    s32 limit;
    s32 payload;
    ThreadSlot *slot;

    prev_counter = sched_counter;
    counter = prev_counter + 1;
    sched_counter = counter;
    ring_idx = counter;
    if (counter < 0) {
        ring_idx = prev_counter + 4;
    }
    slot = &sched_thread_slots[counter - ((ring_idx >> 2) * 4)];
    count = slot->count;
    count = count + 1;
    limit = slot->limit;
    payload = 0xFF000000;
    if (limit < count) {
        count = 0;
        if (limit != 0x80000000) {
            payload = slot->handle;
        }
    }
    slot->count = count;
    thread_set_current(payload);
}

void ChangeTh(s32 th);
/* Switches to thread th: inside an interrupt (the scheduler's timer event) by pointing the BIOS at its TCB,
 * otherwise through ChangeTh. */
void thread_switch(s32 th) {
    if (in_interrupt()) {
        thread_set_current(th);
    } else {
        ChangeTh(th);
    }
}

void thread_slot_init(s32 arg, s32 limit) {
    s32 idx;
    s32 handle;
    s32 base;

    idx = arg;
    FAKE_OPAQUE(idx);
    handle = idx;
    idx &= 0xFFFFFF;
    base = *(s32 *)0x110;
    if ((u32)idx < 4) {
        *(s32 *)(base + idx * 0xC0 + 0x94) = 0x40000404;
        sched_thread_slots[idx].limit = limit;
        sched_thread_slots[idx].count = 0;
        sched_thread_slots[idx].handle = handle;
    }
}

s32 OpenTh(s32 a0, s32 a1, s32 a2);
void thread_slot_init(s32 arg, s32 limit);
extern s32 thread_open_count;
s32 thread_open(void (*handler)(void), u8 *stack, s32 mode) {
    s32 handle;

    if (thread_open_count < 3) {
        handle = OpenTh((s32)handler, (s32)stack, 0);
        if (handle != -1) {
            thread_slot_init(handle, mode);
            thread_open_count += 1;
            return handle;
        }
    }
    return -1;
}

extern ThreadSlot sched_thread_slots[4];
extern s32 CloseTh(s32 th);
void thread_close(s32 th) {
    ThreadSlot *slot;
    s32 i;

    sched_lock();
    i = 0;
    if (th == 1) {
        do {
            slot = &sched_thread_slots[i];
            if (slot->handle != 0xFF000000) {
                CloseTh(slot->handle);
                slot->count = 0;
                slot->limit = 0;
                slot->handle = 0xFF000000;
            }
            i += 1;
        } while (i < 3);
        return;
    }
    if (CloseTh(th) != 0) {
        th &= 0xFFFFFF;
        sched_thread_slots[th].count = 0;
        sched_thread_slots[th].limit = 0;
        sched_thread_slots[th].handle = 0xFF000000;
        thread_open_count -= 1;
    }
    sched_unlock();
}

/* Passes value to thread_switch; a zero value is replaced by 0xFF000000 first. */
void thread_change(s32 value) {
    if (value == 0) {
        value = 0xFF000000;
    }
    thread_switch(value);
}

void thread_set_handle(s32 index, s32 value) {
    sched_thread_slots[index & 0xFFFFFF].limit = value;
}

extern s32 sched_event_handle;

void event_disable(void) {
    DisableEvent(sched_event_handle);
}

/* Stops the scheduler's timer event; outside an interrupt inside a critical section. */
void sched_lock(void) {
    s32 irq = in_interrupt();

    if (!irq) {
        EnterCriticalSection();
    }
    event_disable();
    if (!irq) {
        ExitCriticalSection();
    }
}

extern s32 sched_event_handle;

void sched_event_enable(void) {
    EnableEvent(sched_event_handle);
}

/* Restarts the scheduler's timer event; outside an interrupt inside a critical section. */
void sched_unlock(void) {
    s32 irq = in_interrupt();

    if (!irq) {
        EnterCriticalSection();
    }
    sched_event_enable();
    if (!irq) {
        ExitCriticalSection();
    }
}

extern s32 OpenEvent(s32 class, s32 spec, s32 mode, void (*handler)(void));
extern void SetRCnt(s32 timer, s32 target, s32 mode);
extern void StartRCnt(s32 timer);
void sched_init(void) {
    s32 i;

    thread_open_count = 0;
    sched_counter = 0;
    for (i = 0; i < 4; i++) {
        sched_thread_slots[i].count = 0;
        sched_thread_slots[i].limit = 0;
        sched_thread_slots[i].handle = 0xFF000000;
    }
    EnterCriticalSection();
    sched_event_handle = OpenEvent(0xF2000002, 2, 0x1000, thread_schedule);
    SetRCnt(0xF2000002, 0x2710, 0x1000);
    StartRCnt(0xF2000002);
    EnableEvent(sched_event_handle);
    ExitCriticalSection();
}

extern s32 StopRCnt(s32 rcnt);
extern s32 CloseTh(s32 th);
/* Teardown: stop the timer counter, close the event and every live thread. */
void sched_shutdown(void) {
    s32 i;

    EnterCriticalSection();
    StopRCnt(0xF2000002);
    i = 0;
    CloseEvent(sched_event_handle);
    do {
        if (sched_thread_slots[i].handle != (s32)0xFF000000) {
            CloseTh(sched_thread_slots[i].handle);
        }
        i++;
    } while (i < 3);
    ExitCriticalSection();
}

#ifdef NON_MATCHING
/* Returns the address of music_section_name, read from the rodata word D_80018340. C companion of hand-written asm (not compiled): the word's address is built in $at (lui/addiu), then lw into $v0. */
extern char *D_80018340;

char *func_80022510(void) {
    return D_80018340;
}
#else
INCLUDE_ASM("../src/boot/asm", func_80022510);
#endif
