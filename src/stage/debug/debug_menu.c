/* debug_menu: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void debug_menu_init(void) {
    debug_menu_cursor = 0;
    debug_info_flag = 0;
    dbg_animation = 1;
    dbg_fuchikoma = get_area() % 3 != 0;
    dbg_nodead = dev_mode();
    dbg_autostick = 1;
    if (!player_mode_allowed() || get_area() % 3 == 0) {
        dbg_fuchikoma = 0;
    }
    if (get_area() % 3 == 0) {
        debug_menu_enabled = 1;
    } else {
        debug_menu_enabled = dev_mode();
    }
}

/* debug_menu_apply: applies the debug menu's switches (docs/FINDINGS.md "Developer debug mode"). */
void debug_switches_apply(void) {
    part_timer_set(timed_part());
    player_mode_set(dbg_fuchikoma);
    if (dbg_nodead != 0) {
        set_player_status(get_player_status() | 0x80);
    } else {
        set_player_status(get_player_status() & ~0x80);
    }
    if (dbg_autostick != 0) {
        set_player_status(get_player_status() & ~0x400);
    } else {
        set_player_status(get_player_status() | 0x400);
    }
}

void debug_overlay_draw(void) {
    if (is_paused() != 0) {
        debug_menu_draw();
    }
    if (debug_info_flag != 0) {
        debug_info_draw();
    }
}

void debug_menu_input(void) {
    s32 pressed = pad1_pressed;
    s32 held = pad1.held;
    s32 area = get_area();
    s32 cursor;
    s32 step;

    if (area % 3 != 0 && (pressed & 4)) {
        debug_menu_enabled = debug_menu_enabled == 0;
    }
    if (debug_menu_enabled != 0) {
        if (pressed & PAD_UP) {
            debug_menu_cursor--;
        }
        if (pressed & PAD_DOWN) {
            debug_menu_cursor++;
        }
        cursor = NOT_NEGATIVE(debug_menu_cursor < 7 ? debug_menu_cursor : 6);
        debug_menu_cursor = cursor;
        switch (cursor) {
        case 0:
            if (pressed & (PAD_LEFT | PAD_RIGHT)) {
                area_reinit();
                fn_800E5A14();
                pause_changed();
            }
            break;
        case 3:
            if (pressed & (PAD_LEFT | PAD_RIGHT)) {
                dbg_fuchikoma = dbg_fuchikoma == 0;
            }
            if (player_mode_allowed() == 0 || get_area() % 3 == 0) {
                dbg_fuchikoma = 0;
            }
            debug_switches_apply();
            break;
        case 6:
            step = -2;
            if ((held & PAD_LEFT) || (step = 2, held & PAD_RIGHT)) {
                add_shield(step);
                status_update();
            }
            break;
        default:
            if (pressed & (PAD_LEFT | PAD_RIGHT)) {
                debug_menu_flags[debug_menu_cursor] = debug_menu_flags[debug_menu_cursor] == 0;
            }
            debug_switches_apply();
            break;
        }
    }
}

void debug_cursor_reset(void) {
    debug_menu_cursor = 0;
}
