/* msg_line: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void msg_line_push(s32 value) {
    if (msg_queue_length != 0x40) {
        msg_queue_length += 1;
        msg_queue[msg_write_index] = value;
        msg_write_index = (msg_write_index + 1) & 0x3F;
    }
}

/* Pops the next value from the 64-entry ring msg_queue (count msg_queue_length, read index msg_read_index);
 * 0 when empty. */
s32 msg_line_pop(void) {
    s32 value;

    if (msg_queue_length == 0) {
        return 0;
    }
    msg_queue_length--;
    value = msg_queue[msg_read_index];
    msg_read_index = (msg_read_index + 1) & 0x3F;
    return value;
}

void fn_8010016C(void) {

}

void hud_set_on(s32 value) {
    hud_on_flag = value;
}

void set_msg_enabled(s32 value) {
    msg_enabled = value;
}
