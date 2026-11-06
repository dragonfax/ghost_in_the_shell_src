/* player_state: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

VECTOR *rotate_point(VECTOR *in, VECTOR *out) {
    gte_load(IR1, in, 0);
    gte_load(IR2, in, 4);
    gte_load(IR3, in, 8);
    gte_rtir();
    gte_store(MAC1, out, 0);
    gte_store(MAC2, out, 4);
    gte_store(MAC3, out, 8);
    return out;
}

/* Set player_status; the 0x20 bit is dropped once the stage is ending. */
void set_player_status(s32 status) {
    s32 masked;

    masked = status;
    if (get_stage_end() != 0) {
        masked &= ~0x20;
    }
    player_status = masked;
}

s32 get_player_status(void) {
    return player_status;
}

s32 *get_mover(void) {
    return &mover;
}

void set_flow_max(s32 value) {
    flow_max = value;
}

void set_flow_ramp(s32 value) {
    flow_ramp = value;
}

void set_flow_step(s32 value) {
    flow_step = value;
}

s32 *get_flow_move(void) {
    return &flow_move;
}

s32 get_flow_max(void) {
    return flow_max;
}

s32 get_flow_angle(void) {
    return flow_angle;
}

void set_view_nudge(s32 x, s32 y) {
    view_nudge[0] = x;
    view_nudge[1] = y;
}

s32 *get_view_nudge(void) {
    return &view_nudge;
}

/* Fire-button charge meter, 0..0x1000. fire_hold_steps counts frames the button is held.
 * Charge ramps from 0x1C steps up to 0x4F, holds full until 0x8B, then drains. */
s32 charge_level(void) {
    s32 level = fire_hold_steps - 0x1C;
    s32 held;

    if (fire_hold_steps < 0x4F) {
        if (level < 0) {
            level = 0;
        }
        level = (level << 12) / 50;
    } else {
        level = 0x1000;
        held = fire_hold_steps;
        if (held >= 0x8B) {
            level = 0xC6 - held;
            level = (level << 12) / 60;
        }
    }
    return level;
}

/* The two charge hums (left and right ear): they start while the charge level is nonzero, follow its
 * magnitude in volume and pitch and its sign in pan, and stop when it returns to 0. */
void charge_sound(void) {
    s32 level;
    s32 handle;
    s32 side;   /* the right hum's level: the left's mirrored */
    s32 mirror; /* the same, kept apart because the original uses a copy for the pan */

    level = charge_level();
    if (level == 0) {
        if (charge_hum_a != 0) {
            sound_stop(charge_hum_a);
            charge_hum_a = 0;
        }
        if (charge_hum_b != 0) {
            sound_stop(charge_hum_b);
            charge_hum_b = 0;
        }
    } else {
        handle = charge_hum_a;
        if (handle == 0) {
            charge_hum_a = sound_start(SND_PAIR(SND_LIGHT_MONITOR_HUM | SND_HELD | SND_VOICE_FLAG, SND_HEAVY_MONITOR_HUM | SND_HELD | SND_VOICE_FLAG), 0x7F, 0, 0);
            handle = charge_hum_a;
        }
        if (handle != 0) {
            sound_set_volume(handle,
                             ((abs(level) * 0x5F / 0x1000) + 0x20) * sound_volume_of(SND_PAIR(SND_LIGHT_MONITOR_HUM | SND_HELD | SND_VOICE_FLAG, SND_HEAVY_MONITOR_HUM | SND_HELD | SND_VOICE_FLAG), 0x1000) / 0x80);
            sound_set_pitch(handle, abs(level) / 2 + 0x1000);
            sound_set_pan(handle, ((level / 0x20) + 0xC0) & 0xFF);
        }
        handle = charge_hum_b;
        mirror = -level;
        side = mirror;
        if (handle == 0) {
            charge_hum_b = sound_start(SND_PAIR(SND_HEAVY_WARBLE | SND_HELD | SND_VOICE_FLAG, SND_LIGHT_WARBLE | SND_HELD | SND_VOICE_FLAG), 0x7F, 0, 0);
            handle = charge_hum_b;
        }
        if (handle != 0) {
            sound_set_volume(handle,
                             ((abs(mirror) * 0x5F / 0x1000) + 0x20) * sound_volume_of(SND_PAIR(SND_HEAVY_WARBLE | SND_HELD | SND_VOICE_FLAG, SND_LIGHT_WARBLE | SND_HELD | SND_VOICE_FLAG), 0x1000) / 0x80);
            sound_set_pitch(handle, abs(mirror) / 2 + 0x1000);
            sound_set_pan(handle, ((side / 0x20) + 0xC0) & 0xFF);
        }
    }
}

s32 player_mode_allowed(void) {
    return 1;
}

/* Follows the player on x unless a recording plays back; fixed y offset. */
void stage_offset_follow_player(void) {
    register PlayerObj *addr asm("v0");
    PlayerObj *player;

    do { } while (0);
    addr = &player_obj;
    FAKE_OPAQUE(addr);
    player = addr;
    if (has_rec_entries() == 0) {
        stage_set_offset_x(*(s32 *)player->unk_10C >> 12);
    }
    stage_set_offset_y(-0x80000);
}

/* Switches the player mode on or off (only on when allowed); entering it resets the pose. */
void player_mode_set(s32 on) {
    register PlayerObj *addr asm("v0");
    PlayerObj *player;

    do { } while (0);
    addr = &player_obj;
    FAKE_OPAQUE(addr);
    player = addr;
    if (player_mode_allowed() == 0) {
        on = 0;
    }
    if (player_mode != on) {
        if (on != 0) {
            *(s32 *)player->unk_10C = player->y;
            stage_offset_follow_player();
            player->rot[0] = 0;
            player->rot[1] = 0;
            player->rot[2] = 0;
            player->angle[0] = 0;
            player->angle[1] = 0;
            player->angle[2] = 0;
            player->sub[0] = player->x;
            player->sub[1] = player->y;
            player->sub[2] = player->z;
            player_refresh_state_scratch(player);
            player->co.level = 0;
            player->co.resume[0] = 0;
            player_stage_reset();
        }
        player_mode = on;
        place_view();
    }
}

/* Queues a warp: position (a 16-byte record), optional rotation (8 bytes, any alignment) and turn. */
void player_warp_request(VECTOR *pos, UnalignedVec *rot, s32 turn) {
    s32 *request = &warp_pending;
    s32 *held = request;

    FAKE_OPAQUE(held);
    request[0] = 1;
    *(VECTOR *) &warp_x = *pos;
    if (rot != NULL) {
        warp_rot = *rot;
    } else {
        ((SVECTOR *) &warp_rot)->vx = 0;
        ((SVECTOR *) &warp_rot)->vy = 0;
        ((SVECTOR *) &warp_rot)->vz = 0;
    }
    request[7] = turn;
}

void cam_follow_update(void);

void player_warp(void) {
    PlayerObj *p;
    s32 *pending;
    s32 turn;
    s32 x, y, z;

    do { } while (0);
    p = &player_obj;
    pending = &warp_pending;
    FAKE_OPAQUE(p);
    FAKE_OPAQUE(pending);
    if (*pending != 0) {
        *pending = 0;
        turn = warp_turn;
        do { } while (0);
        x = warp_x;
        y = warp_y;
        z = warp_z;
        do { } while (0);
        p->sub[0] = x << 12;
        p->sub[1] = y << 12;
        p->sub[2] = z << 12;
        player_refresh_state_scratch(p);
        p->x = p->pos[0];
        p->y = p->pos[1];
        p->z = p->pos[2];
        p->yaw += turn << 12;
        add_d_80136404(turn);
        cam_follow_update();
        place_view();
        grid_camera_reset();
        player_update_begin();
    }
}

void player_spawn(void) {
    PlayerObj *p;
    StageSetupBlock *setup;
    s32 *entry;
    s32 yaw;
    s32 roll;
    s32 model_ptr;
    s32 model_id;
    s32 y;

    do { } while (0);
    p = &player_obj;
    setup = get_stage_setup_block();
    __asm__("" : "=r"(p) : "0"(p), "r"(setup));
    p->x = setup->x << 12;
    p->y = setup->y << 12;
    p->z = setup->z << 12;
    do { } while (0);
    yaw = setup->yaw;
    player_glow_level = 0;
    player_walk_phase = 0;
    player_walk_meter = 0;
    player_strafe_meter = 0;
    player_air_blend = 0;
    player_rise_phase = 0;
    player_fall_blend = 0;
    player_land_blend = 0;
    do { } while (0);
    yaw = (yaw & 0xFFF) << 12;
    p->yaw = yaw;
    p->pitch = (setup->pitch & 0xFFF) << 12;
    y = p->y;
    do { } while (0);
    roll = setup->roll;
    player_glow_step = -0x80;
    p->vz = 0;
    p->vy = 0;
    p->vx = 0;
    p->spin_roll = 0;
    p->spin_pitch = 0;
    p->spin_yaw = 0;
    p->strafe_speed = 0;
    p->walk_speed = 0;
    p->gravity = 0;
    *(s32 *)&p->unk_10C = y;
    p->x110 = 1;
    do { } while (0);
    p->roll = (roll & 0xFFF) << 12;
    player_charge_blend = 0;
    player_charge_phase = 0;
    player_charge_timer = 0;
    target_hit_steps = 0;
    fire_hold_steps = 0;
    missile_delay = 0;
    missiles_left = 0;
    stage_offset_follow_player();
    stage_set_offset_x(0);
    p->pose = 0xF1;
    ((s16 *)&p->x18)[0] = 0x70;
    ((s16 *)&p->x18)[1] = 0xA0;
    ((s16 *)&p->x18)[2] = 0x70;
    ((s16 *)&p->x18)[3] = isqrt(length_sq(0x70, 0xA0, 0x70));
    p->rot[0] = 0;
    p->rot[1] = 0;
    p->rot[2] = 0;
    p->angle[0] = 0;
    p->angle[1] = 0;
    p->angle[2] = 0;
    p->sub[0] = p->x;
    p->sub[1] = p->y;
    p->sub[2] = p->z;
    player_refresh_state_scratch(p);
    p->co.level = 0;
    p->co.resume[0] = 0;
    beam_countdown = 0;
    beam_timers_reset();
    player_mode = 0;
    player_mode_set(0);
    entry = (s32 *)get_ptr_entry_word2(1);
    player_pose_base = model_slot_pchr(entry[0]);
    player_coll_part = entry[1];
    entry = (s32 *)get_ptr_entry_word2(0);
    track_base_set(entry[2]);
    lock_frame_base_set(entry[2]);
    entry = (s32 *)get_ptr_entry_word2(2);
    impact_effect_base_set(model_slot_pchr(entry[0]));
    hit_spark_pchr = model_slot_pchr(entry[0]);
    entry = (s32 *)get_ptr_entry_word2(3);
    model_ptr = model_slot_pchr(entry[0]);
    model_id = entry[0];
    beam_model_base = model_ptr;
    spark_model_base_set(model_slot_pchr(model_id));
    effect_set_base(model_slot_pchr(entry[0]));
    spark_set_effect_base(model_slot_pchr(entry[0]));
    grenade_spark_set_base(model_slot_pchr(entry[0]));
    ((void (*)(s32))fn_8010CBD8)(model_slot_pchr(entry[0]));
    *player_model_id_ptr = entry[0];
    p->x114 = 0;
    p->slowdown = 0;
    obj_hit_clear(0);
    player_shake_index = -1;
    player_fade_level = 0;
    obj_clear_block54(&p->coll);
    model_part_extents_max(player_coll_part + 1, 0x1000, &p->coll.dim);
    p->coll.solid = solid_alloc();
    ((u8 *)&p->coll)[1] = 2;
    ((u8 *)&p->coll)[0] = 0;
    cooldown_18c = 0;
    idle_steps = 0;
    cooldown_194 = 0;
    cooldown_19c = 0;
    rec_reset((PartSlot *)&flow);
    displacement.x = 0;
    d_8012BBCC = 0;
    d_8012BBD0 = 0;
    pending_turn = 0;
    set_view_nudge(0, 0);
    player_update_begin();
    fade_list_init();
    flag_words_set_one();
    push_x = 0;
    d_8012BBDC = 0;
    push_z = 0;
    set_flow_max(0);
    set_flow_ramp(0x1000);
    set_flow_step(0x2A);
    flow_move[0] = 0;
    d_8012BBF8 = 0;
    d_8012BBFC = 0;
    player_input_skip = 0;
    warp_pending = 0;
    set_player_status(0);
    player_death_fade = 0;
    player_death_blend = 0;
    player_death_spark_timer = 0;
    player_death_frames = 0;
    player_exit_timer = 0;
    pitch_recenter = 0;
    charge_sound_handle = 0;
    move_sound_handle = 0;
    charge_hum_a = 0;
    charge_hum_b = 0;
    player_step_phase = 0;
    player_step_flag = 0;
    mover_set(&mover, 0x400000, 0, 0);
    player_stage_reset();
    contact_20_steps = 0;
    jump_latch = 0;
    player_run_timer = 0;
    moving = 0;
    move_speed = 0;
}

/* Feed the player a scripted input for this step (pressed is limited to the held buttons). */
void player_set_input(s32 held, s32 pressed) {
    player_held = held;
    player_pressed = pressed & held;
    player_input_skip = 1;
    idle_steps = 0;
}

s32 get_player_held(void) {
    return player_held;
}

s32 get_player_pressed(void) {
    return player_pressed;
}
