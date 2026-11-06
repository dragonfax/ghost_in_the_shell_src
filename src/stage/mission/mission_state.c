/* mission_state: one of the original source files (scripts/objmap.py); s01, s02, s03, s04, s05, s06, s07, s08, s09, s10, s12, s13. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

void mission_state_reset(void) {
    Object *obj;

    alert_flag = 0;
    turn_flag = 0;
    orbit_flag = 0;
    cam_timer = 0;
    mission_enemies_left = 0;
    set_mission_timer(0);
    cam_spin_step = 0x44;
    cam_side_blend = 0;
    cam_ramp_b = 0;
    msg_fade = 0;
    cam_angle_acc = 0;
    msg_pos_x = 0;
    msg_pos_y = 0x36;
    msg_text_id = 0;
    d_8011FEE4 = 0;
    grid_flagged_count = grid_collect_flagged(flagged_grid_cells);
    timer_warn_shown = 0;
    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *)get_obj_list_b(), (Node *)obj);
        obj->handlers[2].fn = cam_update_phase2;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = NULL;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = hud_frame_draw;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
    }
}

#if STAGE == 9 || STAGE == 10 || STAGE == 12
char str_msgs_spr_so3[16] RODATA = "msgs_spr.so3";

char str_msgs_spr_grc[16] RODATA = "msgs_spr.grc";

char str_msgs_spr_clt[16] RODATA = "msgs_spr.clt";
#endif

#if STAGE == 1
void cam_update_phase2(void) {
    s32 flag;

    if (cam_timer > 0) {
        cam_timer--;
        if (cam_timer == 0) {
            msg_fade = 0;
        }
    }
    if (meter_is_full() != 0) {
        if (turn_flag != 0) {
            cam_side_blend = CLAMP_HI(cam_side_blend + 0x200, 0x1000);
        } else {
            cam_side_blend = NOT_NEGATIVE(cam_side_blend - 0x200);
        }
        if (alert_flag != 0) {
            cam_ramp_b = CLAMP_HI(cam_ramp_b + 0x200, 0x1000);
            if (get_mission_timer() < 0x258) {
                alert_add(2);
                if (timer_warn_shown == 0) {
                    show_line((s32)"#1Move quickly!\xA1");
                    timer_warn_shown = 1;
                }
            } else {
                timer_warn_shown = 0;
            }
        } else {
            cam_ramp_b = NOT_NEGATIVE(cam_ramp_b - 0x200);
        }
        if (orbit_flag != 0 && cam_timer != 0) {
            cam_angle_acc = (cam_angle_acc + cam_spin_step) & 0xFFF;
            msg_fade = CLAMP_HI(msg_fade + 0x200, 0x1000);
        } else {
            msg_fade = NOT_NEGATIVE(msg_fade - 0x200);
        }
        flag = 0;
        if (cam_side_blend == 0 || cam_side_blend == 0x1000) {
            flag = 1;
        }
    } else {
        cam_side_blend = NOT_NEGATIVE(cam_side_blend - 0x200);
        cam_ramp_b = NOT_NEGATIVE(cam_ramp_b - 0x200);
        msg_fade = NOT_NEGATIVE(msg_fade - 0x200);
        flag = 0;
    }
    cam_set_mode(flag);
    if (cam_side_blend > 0) {
        cam_set_offset(-2, 0x16);
    } else {
        cam_set_offset(0, 0);
    }
}
#else
void cam_update_phase2(void) {
    s32 mode;

    if (cam_timer > 0) {
        cam_timer--;
        if (cam_timer == 0) {
            msg_fade = 0;
        }
    }

    if (meter_is_full()) {
        if (turn_flag) {
            cam_side_blend = (cam_side_blend + 0x200 > 0x1000) ? 0x1000 : cam_side_blend + 0x200;
        } else {
            cam_side_blend = MAX(cam_side_blend - 0x200, 0);
        }

        if (alert_flag) {
            cam_ramp_b = (cam_ramp_b + 0x200 > 0x1000) ? 0x1000 : cam_ramp_b + 0x200;
            if (get_mission_timer() < 0x258) {
                alert_add(2);
                if (!timer_warn_shown) {
                    /* 24-byte message block: text, then zero padding up to the next table */
                    show_line((s32)"#1Move quickly!\xA1\0\0\0\0\0\0\0");
                    timer_warn_shown = 1;
                }
            } else {
                timer_warn_shown = 0;
            }
        } else {
            cam_ramp_b = MAX(cam_ramp_b - 0x200, 0);
        }

        if (orbit_flag && cam_timer) {
            cam_angle_acc = (cam_angle_acc + cam_spin_step) & 0xFFF;
            msg_fade = (msg_fade + 0x200 > 0x1000) ? 0x1000 : msg_fade + 0x200;
        } else {
            msg_fade = MAX(msg_fade - 0x200, 0);
        }

        mode = (cam_side_blend == 0 || cam_side_blend == 0x1000);
    } else {
        cam_side_blend = MAX(cam_side_blend - 0x200, 0);
        cam_ramp_b = MAX(cam_ramp_b - 0x200, 0);
        msg_fade = MAX(msg_fade - 0x200, 0);
        mode = 0;
    }

    cam_set_mode(mode);
    if (cam_side_blend > 0) {
        cam_set_offset(-2, 0x16);
    } else {
        cam_set_offset(0, 0);
    }
}
#endif

s32 hud_draw_digit(s32 x, s32 y, s32 num, s32 den, s32 base, s32 arg5) {
    u32 neg;
    s32 quot;

    neg = (u32)den >> 31;
    den = ABS(den);
    quot = num / den;
    num -= quot * den;
    if (neg == 0 || quot != 0) {
        quot += base + msg_id_base;
        id_table_add(x, y, 0x1000, quot, 0, arg5, 0);
    }
    return num;
}

/* id_table_add with the table address taken after a barrier and rebuilt for each sprite. */
static inline void hud_sprite_add(s32 x, s32 y, s32 scale, s32 glyph, s32 f08, s32 fade, s32 f0C) {
    IdTableRecords *tbl;
    s32 index;
    IdRecord *rec;

    SCHED_BARRIER();
    tbl = (IdTableRecords *)&id_table;
    FAKE_OPAQUE_VOLATILE(tbl);
    index = tbl->count;

    if (index < 0x100) {
        tbl->count = index + 1;
        rec = &tbl->rec[index];
        rec->prev_id = tbl->id[0];
        tbl->id[0] = index;
        rec->field_00 = x;
        rec->field_02 = y;
        rec->field_04 = scale;
        rec->field_0E = glyph;
        rec->field_08 = f08;
        rec->field_0A = fade;
        rec->field_0C = f0C;
        rec->field_10 = 0;
    }
}

/* Object handler: marks the flagged keys, then draws the HUD's counter, mission timer and message. */
void hud_frame_draw(Object *obj, ObjHandler *handler) {
    s32 i; /* key index, then the timer row's y */
    s32 x; /* key table cursor, then the digits' x */
    s32 fade;
    s32 count;
    s32 glyph;
    s32 alarm;
    s32 ones;
    s32 timer_glyph;
    s32 flagged; /* the key state to mark (1), loaded before the cursor */
    s32 *id_base;

    i = 0;
    if (i < grid_flagged_count) {
        OPAQUE_COPY(flagged, 1);
        for (x = (s32)flagged_grid_cells; i < grid_flagged_count; x += 4, i++) {
            GridEntry *key = *(GridEntry **)x;
            if ((key->flags & 3) == flagged) {
                req_queue_push(key->x >> 12, key->y >> 12, key->z >> 12, 0);
            }
        }
    }

    if (cam_side_blend > 0) {
        count = mission_enemies_left;
        glyph = hud_eng_glyph[eng_mode] + msg_id_base;
        count = MAX(MIN(count, 99), 0);
        if (count != 0 || eng_mode == 3) {
            if (count > 0) {
                glyph++;
            }
            fade = (0x1000 - cam_side_blend) / 4;
            hud_sprite_add(0x78, -0x4F, 0x1000, glyph, 0, fade, 0);
            if (count > 0) {
                s32 digit_x = hud_eng_digit_x[eng_mode];
                x = digit_x + 0x78;
                ones = hud_draw_digit(digit_x + 0x6B, -0x4F, count, -10, 8, fade);
                hud_draw_digit(x, -0x4F, ones, 1, 8, fade);
            }
        }
    }

    if (cam_ramp_b > 0) {
        x = -0x78;
        i = -0x48;
        fade = (0x1000 - cam_ramp_b) / 4;
        id_base = &msg_id_base;
        hud_sprite_add(x, i, 0x1000, hud_mission_glyph[mission_state] + *id_base, 0, fade, 0);
        count = get_mission_timer();
        alarm = (count < 600) ? 0x18 : 0;
        timer_glyph = alarm + 0x20;
        hud_sprite_add(x, i, 0x1000, *id_base + timer_glyph, 0, fade, 0);
        count = hud_draw_digit(-0x89, -0x48, count, 600, timer_glyph + 1, fade);
        count = hud_draw_digit(x, -0x48, count, 60, timer_glyph + 1, fade);
        count = hud_draw_digit(-0x85, -0x48, count * 100 / 60, 10, timer_glyph + 11, fade);
        hud_draw_digit(x, -0x48, count, 1, timer_glyph + 11, fade);
    }

    if (msg_fade > 0 && cam_angle_acc < 0x800) {
        glyph = msg_text_id;
        fade = (0x1000 - msg_fade) / 4;
        hud_sprite_add(msg_pos_x, msg_pos_y, 0x1000, glyph, 0, fade, 0);
        if (d_8011FEE4 == 0) {
            switch (glyph - msg_id_base) {
            case 0x51:
                sound_start(SND_BELL | SND_VOICE_FLAG, 0x7F, 0, 0);
                break;
            case 0x52:
            case 0x53:
            case 0x56:
            case 0x57:
            case 0x58:
            case 0x59:
            case 0x5A:
                sound_start(SND_MESSAGE_POPUP | SND_VOICE_FLAG, 0x7F, 0, 0);
                break;
            }
            d_8011FEE4 = 1;
        }
    } else {
        d_8011FEE4 = 0;
    }
}

extern s32 turn_flag;

void pursue_flag_set(s32 arg0) {
    turn_flag = arg0;
}

extern u32 eng_mode;

void eng_set_mode(u32 arg0) {
    if (arg0 < 5U) {
        eng_mode = arg0;
    }
}

#if STAGE != 8
extern s32 mission_enemies_left;
#endif

#if STAGE == 8
extern s32 hurry_flag, D_8011FEB0, orbit_flag, mission_enemies_left, cam_timer;
#endif

void set_enemies_left(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    mission_enemies_left = var_a0;
}

extern s32 mission_enemies_left;

/* Same code as animation_on (s01). */
s32 get_enemies_left(void) {
    return mission_enemies_left;
}

extern s32 alert_flag;

void mission_timer_active_set(s32 arg0) {
    alert_flag = arg0;
}

extern u32 mission_state;

void mission_state_set(u32 arg0) {
    if (arg0 < 3U) {
        mission_state = arg0;
    }
}

void mission_timer_set(s32 time) {
    set_mission_timer(time);
}

s32 mission_timer_get(void) {
    return get_mission_timer();
}

#if STAGE == 1
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 orbit_flag;
extern s32 cam_timer;
extern s32 msg_text_id;
extern s32 msg_fade;
extern s32 cam_spin_step;
extern s16 msg_pos_x;
extern s16 msg_pos_y;
#endif

#if STAGE == 2
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FECC, D_8011FED0, cam_tilt, cam_sweep_step;
extern s32 D_8011FEAC, D_8011FEB0, D_8011FEB4, D_8011FEB8, cam_timer;
extern s16 msg_pos_x, D_8011FEE2;
extern s16 D_8011FEE0, msg_pos_y;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, cam_tilt, cam_spin_step;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, msg_fade, cam_sweep_step;
#endif

#if STAGE == 3
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, cam_pursue_blend, D_8011FED4, msg_wobble_step;
extern s32 D_8011FEAC, pursue_flag, enemies_remaining, cam_timer;
extern s16 msg_pos_x, msg_pos_y;
extern u8 msg_offset_x[1396], msg_offset_y[]; /* offset table; _y is msg_offset_x+2 */
extern s32 msg_text, cam_pursue_blend, D_8011FED4, cam_spin_step;
extern s32 msg_text, cam_pursue_blend, msg_fade, msg_wobble_step;
#endif

#if STAGE == 4
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FECC, D_8011FED0, D_8011FED4, D_8011FED8;
extern s32 D_8011FEAC, D_8011FEB0, cam_effect_flag, D_8011FEB8, cam_timer;
extern s16 msg_pos_x, D_8011FEE2;
extern s16 D_8011FEE0, msg_pos_y;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, D_8011FED4, cam_spin_step;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, msg_fade, D_8011FED8;
#endif

#if STAGE == 5 || STAGE == 6 || STAGE == 7 || STAGE == 10
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FECC, D_8011FED0, D_8011FED4, D_8011FED8;
extern s32 D_8011FEAC, D_8011FEB0, D_8011FEB4, D_8011FEB8, cam_timer;
extern s16 msg_pos_x, D_8011FEE2;
extern s16 D_8011FEE0, msg_pos_y;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, D_8011FED4, cam_spin_step;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, msg_fade, D_8011FED8;
#endif

#if STAGE == 8
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FECC, D_8011FED0, D_8011FED4, D_8011FED8;
extern s32 hurry_flag, D_8011FEB0, cam_sway_flag, enemies_left, cam_timer;
extern s16 msg_pos_x, D_8011FEE2;
extern s16 D_8011FEE0, msg_pos_y;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, D_8011FED4, cam_spin_step;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, msg_fade, D_8011FED8;
#endif

#if STAGE == 9
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FECC, D_8011FED0, D_8011FED4, D_8011FED8;
extern s32 D_8011FEAC, D_8011FEB0, D_8011FEB4, enemy_count, cam_timer;
extern s16 msg_pos_x, msg_y;
extern s16 msg_x, msg_pos_y;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, D_8011FED4, cam_spin_step;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, msg_fade, D_8011FED8;
#endif

#if STAGE == 12
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FED0, D_8011FED8;
extern s32 D_8011FEAC, D_8011FEB0, D_8011FEB4, D_8011FEB8, cam_timer;
extern s16 msg_pos_x, D_8011FEE2;
extern s16 D_8011FEE0, msg_pos_y;
extern s32 D_8011FEC8, D_8011FED0, cam_spin_step;
extern s32 D_8011FEC8, D_8011FED0, msg_fade, D_8011FED8;
#endif

#if STAGE == 13
extern s32 orbit_flag;

void warning_ack_set(s32 arg0) {
    orbit_flag = arg0;
}

extern s32 msg_text_id, D_8011FECC, D_8011FED0, D_8011FED4, spin_speed;
extern s32 D_8011FEAC, D_8011FEB0, ui_active_flag, ammo_count, cam_timer;
extern s16 msg_pos_x, ui_pos_y;
extern s16 ui_pos_x, msg_pos_y;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, D_8011FED4, cam_spin_step;
extern s32 D_8011FEC8, D_8011FECC, D_8011FED0, msg_fade, spin_speed;
#endif

void msg_show_at(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    msg_text_id = arg2;
    cam_timer = arg3;
    msg_pos_x = arg0;
    msg_pos_y = arg1;
    cam_spin_step = arg4;
    if (meter_is_full() != 0) {
        msg_fade = 0x1000;
    } else {
        msg_fade = 0;
    }
    orbit_flag = 1;
}

#if STAGE != 1
extern s32 msg_slot_ids[12];
extern s32 msg_id_base;
#endif

s32 msg_slot_to_id(s32 i) {
    i = NOT_NEGATIVE(i < 12 ? i : 11);
    return msg_slot_ids[i] + msg_id_base;
}

#if STAGE != 1
void msg_show_at(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4);
#endif

void msg_show_slot(u32 i, s32 arg) {
    if (i < 12) {
        msg_show_at(0, 0x36, msg_slot_ids[i] + msg_id_base, arg, 0x44);
    }
}
