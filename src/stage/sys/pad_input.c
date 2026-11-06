/* pad_input: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void pad_input_reset(PadInput *pad) {
    pad->held = -1;
    pad->unk_06 = 0;
    pad->unk_04 = 0;
    pad->pressed = 0;
}

void input_reset(void) {
    pad_input_reset(&pad1);
    pad_input_reset(&pad_mirror);
    pad_log_reset();
}

void pad_input_set(PadInput *pad, s32 buttons) {
    s32 old;

    old = pad->held;
    pad->held = buttons;
    pad->pressed = (buttons ^ old) & buttons;
}

/* Feeds pad_mirror's held buttons back into it and into pad1. */
void input_repeat(void) {
    s16 buttons = pad_mirror.held;

    pad_input_set(&pad_mirror, buttons);
    pad_input_set(&pad1, buttons);
}

/* Takes the next logged pad reading and updates both pad states with it. */
void input_next(void) {
    u32 buttons;

    buttons = pad_log_pop();
    pad_input_set(&pad_mirror, buttons);
    pad_input_set(&pad1, buttons);
}
