/* file_heap: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE != 6
void debug_nop_a(void) {
}
#endif

#if STAGE == 6
void debug_nop_a(void) {
}
/* hand-written: `j stage_main` with no frame, GCC 2.7.2 never emits a sibling call (config/not_c_manual.txt) */
#ifdef NON_MATCHING
/* Entry thunk: tail-jumps to stage_main with the caller's arguments and return address. C companion of
   hand-written asm (not compiled): `j stage_main` has no frame; GCC 2.7.2 never emits a sibling call. */
extern void stage_main(void);
void stage_main_thunk(void) {
    stage_main();
}
#else
INCLUDE_ASM("../src/s06/asm", stage_main_thunk);
#endif
#endif

s32 debug_check_a(void) {
    return 1;
}

void debug_name_store(u8 *name) {
    debug_name_copy(name);
}

char fmt_file_not_found[20] = "File Not Found: %s\n";

/* Opens a file by name, retrying while it is not found. */
s32 file_seek_retry(char *name) {
    s32 result;

    while ((result = file_seek(name)) == -1) {
        printf(fmt_file_not_found, name);
    }
    if (result < 0) {
        printf("Seek Error: %s\n", name);
    }
    return result;
}

/* Rounds the result of file_seek_retry to a multiple of 0x800 (a CD sector); negative results pass through. */
s32 file_sector_size(char *name) {
    s32 size;

    size = file_seek_retry(name);
    if (size < 0) {
        return size;
    }
    return ((size + 0x800) / 0x800) << 11;
}

/* Reads file `name` to `dest`: retries while not found, reports read errors; returns the result. */
s32 file_read_retry(const char *name, void *dest) {
    s32 result;

    while ((result = file_read_sync(name, dest)) == -1) {
        printf(fmt_file_not_found, name);
    }
    if (result < 0) {
        printf(fmt_read_error, name);
    }
    return result;
}

/* Reads file `name` into buf with file_read_background, retrying while it isn't found (-1); returns its result
 * (negative: read error). */
s32 file_read_bg_retry(char *name, void *buf) {
    s32 result;

    while ((result = file_read_background(name, buf)) == -1) {
        printf(fmt_file_not_found, name);
    }
    if (result < 0) {
        printf(fmt_read_error, name);
    }
    return result;
}

s32 file_io_poll(void) {
    return is_file_io_done();
}

/* Loads file `name` at the heap top and keeps it there; returns its address, or 0 on error. */
void *file_load_to_heap(const char *name) {
    void *dest = (void *)heap_get_top(); /* the heap top */
    s32 size = file_read_retry(name, dest);

    if (size < 0) {
        return 0;
    }
    heap_bump_alloc(size);
    return dest;
}

char fmt_read_error[16] = "Read Error: %s\n";

/* Runs file_write_stub on `name` and `dest`; prints a write error with the name when it fails. (The file names
 * after its string in the rodata are the stage's: each stage's main.c defines them after this file.) */
s32 file_write_named(const char *name, void *dest) {
    s32 result = file_write_stub((s32)name, (s32)dest);

    if (result < 0) {
        printf("Write Error: %s\n", name);
    }
    return result;
}

/* Resets both heaps: the main heap (heap_top) starts at heap_base, the second heap (heap2_top, grows down)
 * at 0x801F8000. */
void heap_reset(void) {
    heap2_top = 0x801F8000;
    heap_top = heap_base;
}

/* Bump allocator: returns the current top and advances it by size rounded up to 4. */
s32 heap_bump_alloc(s32 size) {
    s32 top = heap_top;
    heap_top = top + ((size + 3) & ~3);
    return top;
}

void heap_bump_free(s32 arg0) {
    heap_top -= (arg0 + 3) & ~3;
}

s32 heap_get_top(void) {
    return heap_top;
}

void heap_set_top(s32 arg0) {
    heap_top = (arg0 + 3) & ~3;
}

/* Returns the heap's start (see heap_reset). */
s32 heap_get_base(void) {
    return heap_base;
}

/* Takes `size` bytes (rounded up to 4) off the top of the second heap; returns the new top. */
s32 heap2_alloc(s32 size) {
    return heap2_top -= (size + 3) & ~3;
}

void heap2_free(s32 arg0) {
    heap2_top += (arg0 + 3) & ~3;
}

/* memcpy-like: 16-byte word blocks, then the byte tail; returns dst. */
void *mem_copy_blocks(void *src, void *dst, u32 size)
{
    register CopyBlock16 *s asm("a3") = (CopyBlock16 *)src;
    register CopyBlock16 *d asm("t1") = (CopyBlock16 *)dst;
    register u32 blocks asm("v0") = size >> 4 << 4;
    register CopyBlock16 *end asm("t2") = (CopyBlock16 *)((s8 *)s + blocks);
    size &= 0xF;
    while (s != end) {
        register s32 w0 asm("t0") = s->w0;
        register s32 w1 asm("v0") = s->w1;
        register s32 w2 asm("v1") = s->w2;
        register s32 w3 asm("a0") = s->w3;
        d->w0 = w0;
        d->w1 = w1;
        d->w2 = w2;
        d->w3 = w3;
        __asm__ volatile(""); /* scheduling barrier: keeps the src increment after the stores */
        d++;
        s++;
    }
    {
        register s8 *bs asm("a0") = (s8 *)s;
        register s8 *bend asm("v0") = bs + size;
        register s8 *bd asm("v1") = (s8 *)d;
        while (bs != bend) {
            register s32 c asm("t0") = *bs;
            bs++;
            *bd = c;
            bd++;
        }
    }
    return dst;
}
