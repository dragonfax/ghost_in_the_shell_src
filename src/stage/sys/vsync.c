/* vsync: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void vsync_init(void) {
    VblankState *state;

    // The empty asm keeps the $ra save ahead of the state pointer setup.
    __asm__ __volatile__("" ::: "memory");
    state = &vblank_state;
    FAKE_OPAQUE(state);
    state->put_env = 0;
    state->count = 0;
    state->pad_flags = 0;
    state->env = NULL;
    state->disp_on = 0xFFFF;
    state->callback = NULL;
    state->draws = 0;
    state->ticks = 0;
    state->fps = 0;
    pad_log_reset();
    vblank_task_handle = svc_add_frame_task(vblank_task, 1);
}

void vsync_shutdown(void) {
    svc_remove_frame_task(vblank_task_handle);
}

void *set_vblank_callback(void *callback) {
    void *old = vblank_state.callback;

    if (callback != NULL) {
        vblank_state.callback = callback;
    }
    return old;
}

/* Vertical blank task: puts the display environment at the next vblank, measures the frame rate and
 * logs one pad reading per vblank for the game loop to consume. */
void vblank_task(void) {
    VblankState *vb;

    /* scheduling barrier: the register saves come before the state address load */
    do { } while (0);
    vb = &vblank_state;
    FAKE_OPAQUE(vb);

    if (vb->put_env != 0) {
        vb->put_env = 0;
        if (vb->env != NULL) {
            svc_put_disp_env(vb->env);
            if (vb->disp_on != 1) {
                vb->disp_on = 1;
                svc_set_disp_mask(1);
            }
        } else if (vb->disp_on != 0) {
            vb->disp_on = 0;
            svc_set_disp_mask(0);
        }
    }
    if ((s16)vb->pad_flags > 0) {
        PadLog *log = &pad_log;

        FAKE_OPAQUE(log);
        vb->count++;
        if (debug_check_a() == 0 || debug_check_b() == 0) {
            /* the pad log runs for 600 vblanks (10 s), then the debugger trap fires */
            if (vb->count > 600) {
                vb->count -= 600;
                debug_break();
            }
        }
        log->toggle ^= 1;
        log->buttons[log->write++] = svc_read_pad(1);
        log->write &= PAD_LOG_SIZE - 1;
    }
    if (++vb->ticks >= 60) {
        vb->fps = vb->draws;
        vb->draws = 0;
        vb->ticks = 0;
    }
    if (vb->callback != NULL) {
        vb->callback();
    }
    vb->callback = NULL;
}

void count_draw(void) {
    vblank_state.draws++;
}

s32 get_fps(void) {
    return vblank_state.fps;
}

void pad_log_enable(void) {
    vblank_state.pad_flags |= 1;
}

void pad_log_disable(void) {
    vblank_state.pad_flags &= ~1;
}

void put_disp_env_at_vblank(void *env) {
    vblank_state.env = env;
    vblank_state.put_env = 1;
}

void wait_vblank_count(u32 count) {
    while (*(volatile u16 *)&vblank_state.count < count) {
    }
}

u32 get_vblank_count(void) {
    return vblank_state.count;
}

void set_vblank_count(u16 count) {
    vblank_state.count = count;
}

void pad_log_reset(void) {
    PadLog *log = &pad_log;
    u16 *flags = &vblank_state.pad_flags;

    FAKE_OPAQUE(log);
    FAKE_OPAQUE(flags);
    *flags |= 0x8000;
    log->read = 0;
    log->write = 0;
    log->toggle = 0;
    *flags &= 0x7FFF;
}

s32 pad_log_count(void) {
    PadLog *log = &pad_log;
    s32 n;

    FAKE_OPAQUE(log);
    n = log->write - log->read;
    if (n < 0) {
        n += PAD_LOG_SIZE;
    }
    return n;
}

static inline s32 pad_log_pending(void) {
    PadLog *log = &pad_log;
    s32 n;

    FAKE_OPAQUE(log);
    n = log->write - log->read;
    if (n < 0) {
        n += PAD_LOG_SIZE;
    }
    return n;
}
u32 pad_log_pop(void) {
    register PadLog *base asm("$2") = &pad_log;
    PadLog *log;
    u16 buttons;

    buttons = 0;
    /* hide the address: copy into log, then make the v0 value unknown */
    __asm__("" : "=r"(log) : "0"(base));
    __asm__ volatile("" : "=r"(base) : "0"(base));
    if (pad_log_pending() != 0) {
        buttons = log->buttons[log->read++];
        log->read &= PAD_LOG_SIZE - 1;
    }
    return buttons;
}
