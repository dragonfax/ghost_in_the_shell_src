/* svc: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Empty: the first function of every stage's text. */
void svc_nop(void) {
}

/* Boot exe service stubs jump through the service table at 0x80010000 with the caller's arguments and
 * return address: `goto *slot` at a function's end compiles to the bare jump, with no frame or return. */

/* The current area: mission * 3 + part. */
s32 get_area(void) {
    return area;
}

void set_area(s32 value) {
    area = value;
}

void *get_area_entry(void) {
    return area_entry_table[area % 3];
}

void debug_nop_b(void) {

}

s32 debug_check_b(void) {
    return 1;
}

extern void *slot_004;

/* Tail-jumps into the boot exe's video-mode service; the return is dead code. */
s32 svc_video_mode(void) {
    /* Empty asm takes the label's address so GCC keeps the dead return after the jump. */
    __asm__("" : : "X"(&&done));
    goto *slot_004;
done:
    return 0;
}

extern void *slot_read_pad;

/* Reads a pad: returns its buttons pressed (active high). */
s32 svc_read_pad(s32 port) {
    goto *slot_read_pad;
}

/* Copies the NUL-terminated string src into the debug name buffer debug_name_buf. A NULL src clears it. */
void debug_name_copy(u8 *src) {
    u8 *dst;
    u8 c;

    if (src == NULL) {
        debug_name_buf[0] = 0;
    } else {
        dst = debug_name_buf;
        *dst = 0;
        do {
            c = *src++;
            *dst++ = c;
        } while (c != 0);
    }
}

/* Copies the file name part of a path (after the last backslash) to dst. */
void path_file_name(u8 *path, u8 *dst) {
    u8 *p = path;
    u8 *name = p;
    s32 sep = '\\';
    u8 c;

    do {
        c = *p++;
        if (c == sep) {
            name = p;
        }
    } while (c != 0);
    p = path;
    if (name != p) {
        do {
            *dst++ = *p++;
        } while (name != p);
    }
    *dst = 0;
}

/* Builds the debug name in file_name_buf: debug_name_buf, then `name` if given, both uppercased. */
void file_name_build(u8 *name) {
    u8 *src = debug_name_buf;
    u8 *dst = file_name_buf;
    u8 c;
    u32 o;
    do {
        c = *src++;
        if ((u32)(c - 0x61) < 26) {
            c &= 0x5F;
        }
        o = c;
        *dst++ = o;
    } while (o != 0);
    dst--;
    src = name;
    if (src != 0) {
        do {
            c = *src++;
            if ((u32)(c - 0x61) < 26) {
                c &= 0x5F;
            }
            o = c;
            *dst++ = o;
        } while (o != 0);
    }
}

s32 *get_file_name(void) {
    return (s32 *) &file_name_buf;
}

/* Starts a seek for a debug name (-2 for none): prints the name and the seek's result while pad 1 is down. */
s32 file_seek(char *name) {
    s32 result;

    if (name == NULL) {
        return -2;
    }
    file_name_build((u8 *) name);
    result = slot_seek(file_name_buf);
    if (result < 0) {
        result = -2;
    }
    if (svc_read_pad(1) != 0) {
        printf("[seek]: %s (%d)\n", file_name_buf, result);
    }
    return result;
}

/* Reads the record named by name into dest. Returns the service result, or -2 when name is NULL. */
s32 file_read_sync(const char *name, void *dest) {
    s32 result;

    if (name == NULL) {
        return -2;
    }
    file_name_build((u8 *) name);
    do {
        result = slot_read_file(file_name_buf, dest, 0);
    } while (result == -1);
    if (svc_read_pad(1) != 0) {
        printf("[read]: %s %X (%d)\n", file_name_buf, dest, result);
    }
    return result;
}

/* Reads the record named by name into buf. Returns the service result, or -2 when name is NULL. */
s32 file_read_background(char *name, void *buf) {
    s32 result;

    if (name == NULL) {
        return -2;
    }
    file_name_build((u8 *) name);
    do {
        result = slot_read_background(file_name_buf, buf, 0);
    } while (result == -1);
    if (svc_read_pad(1) != 0) {
        printf("[readBG]: %s %X (%d)\n", file_name_buf, buf, result);
    }
    return result;
}

/* Returns 1 when the service at slot_148 returns 0. */
s32 is_file_io_done(void) {
    return slot_148() == 0;
}

/* Callers pass 2 or 3 arguments (the third is the length; this stub ignores it), so no prototype. */
s32 file_write_stub(arg0, arg1, arg2)
s32 arg0;
s32 arg1;
s32 arg2;
{
    file_name_build((u8 *)arg0);
    if (svc_read_pad(1) != 0) {
        printf("[write]: %s %X (%d)\n", file_name_buf, arg1, -1);
    }
    return -1;
}

/* Copies the entry's path into exec_path_buf and returns that buffer. */
u8 *get_exec_path(void) {
    ResourceEntry *entry = slot_resource_entry(slot_get_exec_code());

    path_file_name(entry->path, exec_path_buf);
    return exec_path_buf;
}

/* Waits the given number of frames. */
void svc_wait_frames(s32 frames) {
    goto *slot_wait_frames;
}

/* Boot exe service: run fn every `period` frames; returns a handle. */
s32 svc_add_frame_task(void (*fn)(void), s32 period) {
    return slot_add_frame_task(fn, period - 1);
}

/* Removes a frame task; the handle is not passed on (the service takes none). */
s32 svc_remove_frame_task(s32 handle) {
    return slot_remove_frame_task(handle);
}

static const RECT screen_rect = {0, 0, 0x400, 0x200};
/* Stage start-up: stops with the BIOS version message unless the services report version 0x300, then waits a
 * frame, runs service 0x1C0, blanks the display and clears the whole frame buffer to black. */
void svc_0(void) {
    if (((s32 (*)(void))SVC_TABLE[0])() != 0x300) {
        printf(BIOS_VERSION_ERROR);
        for (;;) {
        }
    }
    slot_wait_frames(0);
    slot_1C0(0);
    svc_wait_frames(0);
    svc_set_disp_mask(0);
    svc_clear_image((void *)&screen_rect, 0, 0, 0);
    svc_draw_sync(0);
}

/* Shuts down the stage's services in order. */
void stage_exit(void) {
    slot_wait_frames(0);
    slot_set_disp_mask(0);
    slot_1C0(3);
}

/* Returns the code of the program the boot exe runs. */
s32 svc_get_exec_code(void) {
    goto *slot_get_exec_code;
}

extern void *slot_006;

/* Sets the next program's exec code. */
void svc_set_exec_code(s32 exec) {
    goto *slot_006;
}

extern void *slot_shared_state;

/* Returns the state block shared between programs. */
void *svc_get_shared_state(void) {
    goto *slot_shared_state;
}

extern void *slot_draw_sync;

void svc_draw_sync(s32 mode) {
    goto *slot_draw_sync;
}

extern void *slot_LoadImage;

void svc_load_image(void *rect, void *data) {
    goto *slot_LoadImage;
}

extern void *slot_StoreImage;

void svc_store_image(s32 rect, s32 data) {
    goto *slot_StoreImage;
}

extern void *slot_clear_image;

void svc_clear_image(void *rect, s32 r, s32 g, s32 b) {
    goto *slot_clear_image;
}

extern void *slot_DrawOTag;

void svc_draw_otag(void *ot) {
    goto *slot_DrawOTag;
}

void svc_set_disp_mask(s32 on) {
    goto *slot_set_disp_mask;
}

extern void *slot_put_disp_env;

void svc_put_disp_env(void *env) {
    goto *slot_put_disp_env;
}

extern void *slot_1DA;

void fn_800B6D78(void *rec, s32 x, s32 y, s32 w, s32 h) {
    goto *slot_1DA;
}

extern void *slot_1D9;

void fn_800B6D8C(void *env, s32 x, s32 y, s32 w, s32 h) {
    goto *slot_1D9;
}

extern void *slot_SetDrawEnv;

void svc_set_draw_env(void *packet, const void *env) {
    goto *slot_SetDrawEnv;
}

extern void *slot_SetDrawMode;

void fn_800B6DB4(void *packet, s32 dfe, s32 dtd, s32 tpage, const void *tex_window) {
    goto *slot_SetDrawMode;
}

extern void *slot_SetTexWindow;

void svc_set_tex_window(void *packet, const void *tex_window) {
    goto *slot_SetTexWindow;
}

extern void *slot_SetDrawOffset;

void svc_set_draw_offset(void *packet, const void *offset) {
    goto *slot_SetDrawOffset;
}

extern void *slot_SetDrawArea;

void svc_set_draw_area(void *packet, const void *area) {
    goto *slot_SetDrawArea;
}

extern void *slot_0BA;

s32 fn_800B6E04(void) {
    goto *slot_0BA;
}

/* Returns 1 when the service at slot_15D returns nonzero. */
s32 area_is_loadable(s32 index) {
    return slot_15D(index) != 0;
}
