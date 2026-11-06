/* player: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void player_read_input(void) {
    if (player_input_skip == 0) {
        player_pressed = 0;
        player_held = 0;
        if (!(get_stage_flags() & 8) && !(player_status & 0x60)) {
            player_held = pad1.held;
            player_pressed = pad1.pressed;
        } else {
            idle_steps = 0;
        }
    }
    player_input_skip = 0;
    if (player_status & 0x60) {
        set_d_801202C8(0);
    }
}

s32 player_controls_enabled(void) {
    return (player_status & 0x60) == 0;
}

void player_frame_update(void) {
    PlayerObj *p = &player_obj;
    PlayerObj *src = p;
    Collider *coll = &p->coll;
    s32 damage;
    s32 fade;

    if (player_hit_flash < 0) {
        player_hit_flash = 0;
    }
    if (player_hit_cooldown > 0) {
        player_hit_cooldown--;
        if (player_hit_cooldown == 0) {
            sound_timer_stop();
        }
    } else {
        damage = (s16)obj_hit_damage(0);
        if (damage > 0 && get_stage_end() == 0 && !(get_stage_flags() & 0x10) && !(player_status & 0x60)) {
            if (damage >= 0xF) {
                sound_timer_set(0x20);
                sound_start(SND_PLAYER_HIT_HEAVY, 0x7F, 0, 0);
            } else {
                sound_start(SND_PLAYER_HIT_LIGHT, 0x7F, 0, 0);
                sound_timer_set(8);
            }
            p->slowdown = 0x20;
            player_charge_timer = 0;
            if (lock_get_mode() == 0) {
                fire_hold_steps = -1;
            }
            player_shake_index = 0;
            player_fade_level = 0x1000;
            add_shield(-damage);
            if (p->x114 == 0) {
                p->x114 = 1;
            }
        }
    }
    if (get_shield() <= 0 && !(player_status & 0x80)) {
        set_player_status(player_status | 0x20);
        if (player_status & 0x100) {
            set_player_status(player_status | 0x40);
        }
    }
    obj_hit_clear(0);
    *(SubPos *)coll->sub = *(SubPos *)src->pos;
    coll->angle[0] = -src->rot[0];
    coll->angle[1] = -src->rot[1];
    coll->angle[2] = -src->rot[2];
    if (!(player_status & 0x60)) {
        solid_setup_scratch(p->coll.solid, coll, player_coll_part + 1, 0x1000);
    } else if (p->coll.solid >= 0) {
        solid_free(p->coll.solid);
        p->coll.solid = -1;
    }
    if (player_mode != 0 && get_stage_end() == 0) {
        fade = player_fade_level;
        if (fade > 0) {
            fade -= 0x100;
            if (fade < 0) {
                fade = 0;
            }
            player_fade_level = fade;
        }
        cam_offset_set(0xFF, 0x5C, 0);
        cam_fade_set(0x1000 - player_fade_level / 2);
    }
}

/* Speed loss from a slowdown counter of 0x10 or more. */
s32 player_slowdown(void) {
    PlayerObj *player = &player_obj;
    s32 result;

    FAKE_OPAQUE(player);
    if (player->slowdown >= 0x10) {
        result = (player->slowdown - 0x10) << 8;
    } else {
        result = 0;
    }
    return result;
}

void debug_fly(void) {
    PlayerObj *player;
    s32 held;
    s32 speed;
    s32 walk;
    s32 strafe;

    /* the empty loop keeps the register saves ahead of the pad read (scheduling barrier) */
    do { } while (0);
    /* keeps &player_obj in a saved register instead of lui/%lo per field */
    player = &player_obj;
    FAKE_OPAQUE(player);
    held = pad1.held;
    speed = 1;

    if (held & 0x100) {
        speed = 4;
    }

    player->spin_yaw = (held & 0x2000) ? 0x10000 : ((held & 0x8000) ? -0x10000 : 0);
    player->spin_roll = (held & 0x20) ? 0x10000 : ((held & 0x80) ? -0x10000 : 0);
    player->spin_pitch = (held & 0x40) ? 0x10000 : ((held & 0x10) ? -0x10000 : 0);

    if (held & 0x2) {
        player->vy = speed * 0x18000;
    } else if (held & 0x1) {
        player->vy = -(speed * 0x18000);
    } else {
        player->vy = 0;
    }
    player->y += player->vy;

    walk = (held & 0x1000) ? (speed << 5) : ((held & 0x4000) ? -(speed << 5) : 0);
    fly_move(player->yaw >> 12, walk, &player->vz, &player->vx);

    if (held & get_key_config()->action[8]) {
        strafe = speed << 5;
    } else if (held & get_key_config()->action[9]) {
        strafe = -(speed << 5);
    } else {
        strafe = 0;
    }
    if (strafe != 0) {
        fly_strafe((player->yaw >> 12) + 0x400, strafe, &player->vz, &player->vx);
    }

    player->yaw += player->spin_yaw;
    player->pitch += player->spin_pitch;
    player->roll += player->spin_roll;
    player->x += player->vx;
    player->z += player->vz;
}

/* Fires the player's blast: when player_model_on_get is set, from a point offset in the player's
 * rotated frame (the spawn_effect flash there), else from the player position along the view direction; plays its sound and spawns the projectile object. */
void player_blast(void) {
    PlayerObj *player;
    PlayerObj *obj;
    VECTOR *muzzle;
    s16 *spawn_rot;
    s16 *mat;
    s16 *tilt;
    s32 angles[3];
    u16 ang_y, ang_x;
    register u16 ang_z asm("$8");
    s32 spawn_index;
    u32 sincos;
    s16 cos;
    s16 neg_sin;
    s32 t0, t1, t2;

    do {
    } while (0);
    player = &player_obj;
    FAKE_OPAQUE(player);
    muzzle = scratch_alloc(0x10);
    spawn_rot = scratch_alloc(8);
    mat = scratch_alloc(0x40);
    obj = player;
    FAKE_OPAQUE(obj);
    if (player_model_on_get() != 0) {
        rot_matrix(mat, player->yaw >> 12, 0, 0);
        tilt = mat + 16;
        rot_matrix(tilt, -player->rot[1], -player->rot[0], -player->rot[2]);
        mul_matrix(tilt, mat, mat);
        gte_load_R012(mat, t0, t1, t2);
        gte_load_R34(mat, t0, t1);
        gte_set_TR_a0v0v1(player->x >> 12, player->y >> 12, player->z >> 12);
        muzzle->vy = -0x86;
        muzzle->vx = 0;
        muzzle->vz = 0x70;
        transform_point(muzzle, muzzle);
        matrix_to_angles(mat, &angles[0], &angles[1], &angles[2]);
        spawn_effect(muzzle->vx, muzzle->vy, muzzle->vz, 0);
    } else {
        sincos = view_sincos[0];
        muzzle->vx = obj->x >> 12;
        muzzle->vy = obj->y >> 12;
        cos = sincos >> 16;
        muzzle->vz = obj->z >> 12;
        neg_sin = -sincos;
        mat[0] = cos;
        mat[1] = 0;
        mat[2] = sincos;
        mat[3] = 0;
        mat[4] = 0x1000;
        mat[5] = 0;
        mat[6] = neg_sin;
        mat[7] = 0;
        mat[8] = cos;
        mul_matrix(view_matrix_get(), mat, mat);
        matrix_to_angles(mat, &angles[0], &angles[1], &angles[2]);
    }
    ang_x = angles[1];
    ang_y = angles[0];
    spawn_index = player_pose_base + 0x53;
    ang_z = angles[2];
    spawn_rot[0] = ang_x;
    spawn_rot[1] = ang_y;
    spawn_rot[2] = ang_z;
    sound_start(SND_PAIR(SND_LARGE_EXPLOSION | SND_GROUP(1), SND_MEDIUM_EXPLOSION | SND_GROUP(1)), 0x7F, 0, 0);
    object_spawn_at(muzzle, spawn_rot, spawn_index);
    sound_timer_set(0x20);
    scratch_top -= 0x58;
}

/* Two effects (type 2) at random directions 0x38-0x5F units around the player. */
void player_sparks(void) {
    s32 dx, dy, dz;
    s32 *pos = player_position();
    s32 i = 0;
    s32 x = pos[0];
    s32 y = pos[1];
    s32 z = pos[2];

    do {
        s32 yaw = rand_a_next();
        s32 pitch = rand_a_next();

        angles_to_vector(yaw, pitch, rand_a_next() * 0xA8 / 0x1000 + 0x38, &dx, &dy, &dz);
        spawn_effect(x + (dx >> 12), y + (dy >> 12), z + (dz >> 12), 2);
        i++;
    } while (i < 2);
    sound_timer_set(8);
}

/* The strafe direction from the held buttons: 0x3000 right, -0x3000 left, 0 for neither or both.
 * Configurations 0-2 also strafe with actions 10/11 unless dev_mode() is set. */
s32 strafe_input(s32 held) {
    s32 right;
    s32 left;

    right = held & get_key_config()->action[KEY_STRAFE_RIGHT];
    left = held & get_key_config()->action[KEY_STRAFE_LEFT];
    if (dev_mode() == 0 && get_key_config_index() < 3) {
        right |= held & get_key_config()->action[10];
        left |= held & get_key_config()->action[11];
    }
    if (right) {
        if (left) {
            return 0;
        }
    } else {
        return left ? -0x3000 : 0;
    }
    return 0x3000;
}

/* Whether both strafe directions are held (configurations 0-2 also strafe with actions 10/11). */
s32 can_move(s32 held) {
    s32 left;
    s32 right;
    s32 both;

    right = held & get_key_config()->action[KEY_STRAFE_RIGHT];
    left = held & get_key_config()->action[KEY_STRAFE_LEFT];
    if ((dev_mode() == 0) && (get_key_config_index() < 3)) {
        right |= held & get_key_config()->action[10];
        left |= held & get_key_config()->action[11];
    }
    both = 0;
    if (right != 0) {
        both = left != 0;
    }
    return both;
}

/* The pad buttons that strafe: the R1/L1 pair of the current key configuration, plus the R2/L2 pair
 * when the configuration index is below 3. */
s32 strafe_mask(void) {
    KeyConfig *cfg;
    s32 mask;

    cfg = get_key_config();
    mask = cfg->action[KEY_STRAFE_RIGHT] | get_key_config()->action[KEY_STRAFE_LEFT];
    if (dev_mode() == 0) {
        if (get_key_config_index() < 3) {
            cfg = get_key_config();
            mask |= cfg->action[10] | get_key_config()->action[11];
        }
    }
    return mask;
}

/* The held buttons of action 2 (configuration 3 also action 10). */
s32 alt_pressed(s32 held) {
    s32 buttons;
    s32 result;

    buttons = held & get_key_config()->action[2];
    result = buttons;
    if (get_key_config_index() == 3) {
        result = buttons | (held & get_key_config()->action[10]);
    }
    return result;
}

/* The movement loop sound: volume from the speed (less while standing on something moving), pitch from the
 * speed along one axis. */
void move_sound(void) {
    s32 strafe;
    s32 walk;
    s32 level;
    s32 pitch;
    PlayerObj *player;

    do { /* scheduling barrier: keeps the loads below the register saves */
    } while (0);
    player = &player_obj;
    FAKE_OPAQUE(player);

    strafe = ABS(player->strafe_speed);
    walk = ABS(move_speed);
    level = (strafe + walk) / 32;
    level = MAX(MIN(level, 0x1000), 0);
    pitch = walk / 3072;
    if (player_status & 1) {
        if (player_status & 2) {
            level = 0;
        } else {
            level = (level + 0x1000) / 3;
            pitch = strafe / 3072;
        }
    }
    if (level > 0) {
        if (move_sound_handle == 0) {
            if (player->x110 != 0) {
                sound_start(SND_PLAYER_MOVE_START, 0x7F, 0, 0);
            }
            move_sound_handle = sound_start(SND_PAIR(SND_SLOW_MECH_MOVE | SND_HELD, SND_FAST_MECH_MOVE | SND_HELD), 0x7F, 0, 0);
            sound_set_flag_bit3(move_sound_handle, 1);
            sound_set_flag_bit0(move_sound_handle, 0);
        }
        level = level * (0x1000 - player_air_blend) / 0x1000;
        if (move_sound_handle != 0) {
            sound_set_volume(move_sound_handle, sound_volume_of(SND_PAIR(SND_SLOW_MECH_MOVE | SND_HELD, SND_FAST_MECH_MOVE | SND_HELD), level));
            sound_set_pitch(move_sound_handle, pitch + 0x1E00);
        }
    } else if (move_sound_handle != 0) {
        sound_stop(move_sound_handle);
        move_sound_handle = 0;
    }
}

extern s32 player_ground_y; /* the player's y at the last ground step */
/* The player's step: idle lines, cooldowns, firing and lock-on, the dying/out-of-area timers, the jump
 * coroutine (on ground, jump held, rising, falling, landing), the dev-mode toggles, turning, the
 * forward/walk/strafe speeds, the pose, the move and collision, then the view offset and move sound. */
void player_control(void) {
    PlayerObj *obj; /* both point at player_obj: obj for flags, ground, pose and move, p for the rest */
    s32 held;
    s32 pressed;
    PlayerObj *p;
    Coroutine *co;
    s32 boost;   /* speed limit multiplier: 4 with the dev-mode button 0x100 held */
    s32 accel;   /* one register in the original: the thrust input, then the slowdown factor,
                  * move_speed >> 12, and the strafe input */
    s32 fwd;     /* the forward speed for fly_move, then the walk input */
    s32 walking; /* strafing (or walking in modes 1+2): ramps player_strafe_meter */
    s32 toggle;
    s32 vx, vy, vz;
    s32 unused[2]; /* the original's 8 bytes of locals */

    /* An empty do-while(0) (a no-op macro in the original?): its loop notes keep sched2 from moving
     * the first loads into the register saves. */
    do {
    } while (0);
    /* obj = &player_obj through an empty asm: GCC must not know obj's value (FAKE_OPAQUE with one
     * reference less, for the register order) */
    __asm__("" : "=r"(obj) : "0"(&player_obj));
    held = player_held;
    pressed = player_pressed;
    p = obj;
    if (held == 0 && get_stage_end() == 0) {
        if (++idle_steps > 0x4B0) {
            idle_steps = 0;
            switch (rand_a_next() * 3 / 0x1000) {
            case 0:
                show_line((s32)"Keep working!\xA1");
                break;
            case 1:
                show_line((s32)"Pursue your mission");
                break;
            default:
                show_line((s32)"What are you doing?");
                break;
            }
        }
    } else {
        idle_steps = 0;
    }
    cooldown_194 = MAX(cooldown_194 - 1, 0);
    cooldown_19c = MAX(cooldown_19c - 1, 0);
    cooldown_18c = MAX(cooldown_18c - 1, 0);
    if (alt_pressed(pressed)) {
        throw_grenade();
    }
    if (held & get_key_config()->action[0]) {
        if (spark_active_count() <= 0 && missiles_left <= 0 && fire_hold_steps >= 0) {
            if (fire_hold_steps < 0xC6) {
                fire_hold_steps++;
            }
            if (fire_hold_steps == 0x4E) {
                lock_set_mode(1);
            } else if (fire_hold_steps == 0xC6) {
                lock_set_mode(0);
                fire_hold_steps = -1;
            }
        }
    } else {
        if (lock_count() > 0) {
            lock_targets();
            player_charge_phase = 0;
            player_charge_timer = 0;
        }
        fire_hold_steps = 0;
        lock_set_mode(0);
    }
    charge_sound();
    if (missiles_left > 0) {
        fire_missiles();
        player_charge_blend = MIN(player_charge_blend + 0x400, 0x1000);
    } else {
        if (pressed & get_key_config()->action[0]) {
            player_charge_timer = 0x1C;
            if (charge_sound_handle == 0) {
                charge_sound_handle = sound_start(SND_SMG_FIRE | SND_HELD, 0x40, 0, 0);
            }
        }
        if (player_charge_timer > 0 && --player_charge_timer > 0) {
            player_charge_blend = MIN(player_charge_blend + 0x400, 0x1000);
            player_charge_phase = (player_charge_phase + 0x200) & 0xFFF;
        } else {
            player_charge_blend = MAX(player_charge_blend - 0x200, 0);
            player_charge_phase = MAX(player_charge_blend - 0x400, 0);
            if (charge_sound_handle != 0) {
                sound_stop(charge_sound_handle);
                charge_sound_handle = 0;
            }
        }
    }
    if ((player_status & 0x40) && player_death_fade >= 0) {
        if (++player_exit_timer >= 0x78) {
            player_death_fade = -1;
            set_stage_end(3);
        }
    }
    if ((player_status & 0x20) && player_death_fade >= 0) {
        if (--player_death_spark_timer < 0) {
            if (p->x114 == 0) {
                p->x114 = 1;
            }
            player_fade_level = 0x1000;
            player_shake_index = 0;
            player_sparks();
            player_death_spark_timer = 10;
        }
        if (player_death_fade >= 0 && ++player_death_frames >= 0xB4) {
            player_death_fade = -1;
            player_blast();
            player_model_state_set(0);
            set_stage_end(3);
        }
    }
    if (player_status & 0x400) {
        player_run_timer = 0;
        if (!(held & get_key_config()->action[1])) {
            jump_latch = 0;
        }
        if (p->x110 != 0) {
            if ((obj->flags & 0xC) && !(obj->flags & 0x40) && (held & get_key_config()->action[1])) {
                jump_latch = 1;
            }
            if ((obj->flags & 0x30) && !(obj->flags & 0x80) && (held & get_key_config()->action[1])) {
                jump_latch = 1;
            }
        } else if (pressed & get_key_config()->action[1]) {
            jump_latch = 1;
        }
    } else {
        jump_latch = 0;
        if ((held & (strafe_mask() | get_key_config()->action[4] | get_key_config()->action[5])) && (obj->flags & 0x3C)) {
            player_run_timer = CLAMP_HI(player_run_timer + 1, 6);
        } else {
            player_run_timer = 0;
        }
    }

    /* The jump coroutine: on the ground, jump held (up to 0x17 steps), rising, falling. */
    co = &p->co;
    if (co->resume[co->level] != 0) {
        goto *(void *)co->resume[co->level];
    }
landed:
    co->resume[co->level] = (u32)&&on_ground;
on_ground:
    if (player_status & 0x20) {
        player_death_blend = CLAMP_HI(player_death_blend + 0x200, 0x1000);
        if (player_death_fade >= 0) {
            player_death_fade = CLAMP_HI(player_death_fade + 0x22, 0x1000);
            if (player_death_fade == 0x1000) {
                player_death_fade = -1;
                player_blast();
                player_model_state_set(0);
                set_stage_end(3);
            }
        }
    }
    p->vy = 0;
    p->gravity = 0;
    player_air_blend = MAX(player_air_blend - 0xE3, 0);
    player_land_blend = MIN(player_land_blend + 0x555, 0x1000);
    if (player_land_blend == 0x1000) {
        player_rise_phase = 0;
        player_fall_blend = 0;
    }
    player_ground_y = p->y;
    if ((pressed & get_key_config()->action[1]) && jump_latch == 0) {
        p->vy = -0x32000;
        if (player_mode_flags() & 6) {
            p->vy = -0x26000;
        }
        player_rise_phase = 0;
        obj->flags &= ~1;
        p->x110 = 0;
        p->gravity = 0x1A00;
        sound_start(SND_PLAYER_JUMP, 0x7F, 0, 0);
        if (move_sound_handle != 0) {
            sound_stop(move_sound_handle);
            move_sound_handle = 0;
        }
    } else {
        if (obj->flags & 1) {
            goto moved;
        }
        player_rise_phase = 0x1000;
        p->vy = 0;
        p->x110 = 0;
        p->gravity = 0x1A00;
        goto fall;
    }
    co->level = (co->level + 1) & 7;
    co->resume[co->level] = (u32)&&jump_held;
    co->count[co->level] = 0x17;
jump_held:
    if (!(held & get_key_config()->action[1]) || --co->count[co->level & 7] <= 0) {
        p->gravity += co->count[co->level & 7] * 0x340;
        co->resume[co->level] = (u32)&&rising;
    }
rising:
    if (obj->flags & 2) {
        p->vy = 0;
    }
    if (p->vy < 0) {
        player_land_blend = MAX(player_land_blend - 0x400, 0);
        p->vy = MIN(p->vy + p->gravity, 0x30000);
        player_air_blend = MIN(player_air_blend + 0x200, 0x1000);
        player_rise_phase = MIN(player_rise_phase + 0x199, 0x1000);
        player_fall_blend = MAX(player_fall_blend - 0x200, 0);
        obj->flags &= ~1;
        goto moved;
    }
fall:
    co->resume[co->level] = (u32)&&falling;
falling:
    player_land_blend = MAX(player_land_blend - 0x400, 0);
    p->vy = MIN(p->vy + p->gravity, 0x30000);
    player_air_blend = MIN(player_air_blend + 0x200, 0x1000);
    player_fall_blend = MIN(player_fall_blend + 0x100, 0x1000);
    if (obj->flags & 1) {
        p->vy = 0;
        p->x110 = 1;
        sound_start(((surface_of(obj->ground) & 0x300) >> 8) == 1 && !(player_status & 2) ? SND_LANDING_THUD_ALT : SND_PLAYER_LAND, 0x7F, 0, 0);
        co->resume[co->level] = (u32)&&landed;
    }
moved:
    if (dev_mode()) {
        toggle = pressed & get_key_config()->action[3];
    } else {
        toggle = pressed & 0x100;
    }
    if (toggle) {
        set_player_mode_flags(player_mode_flags() ^ 1);
    }
    boost = 1;
    if (dev_mode() && (held & 0x100)) {
        boost = 4;
    }
    p->spin_yaw = (held & get_key_config()->action[6]) ? 0x10000 : (held & get_key_config()->action[7]) ? -0x10000 : 0;
    if (held & get_key_config()->action[5]) {
        p->spin_yaw *= 2;
    }
    p->spin_pitch = 0;
    if (dev_mode() && pitch_recenter == 0) {
        if ((held & get_key_config()->action[10]) && (held & get_key_config()->action[11])) {
            pitch_recenter = 1;
        } else {
            pitch_recenter = 0;
            p->spin_pitch = (held & get_key_config()->action[10]) ? 0x10000 : (held & get_key_config()->action[11]) ? -0x10000 : 0;
        }
    }
    if (dev_mode() && pitch_recenter != 0) {
        if (p->pitch != 0) {
            p->spin_pitch = CLAMP_HI(ABS(p->pitch), 0x20000);
            if (p->pitch > 0) {
                p->spin_pitch = -p->spin_pitch;
            }
        } else {
            pitch_recenter = (held & get_key_config()->action[10]) || (held & get_key_config()->action[11]);
        }
    }
    accel = (held & get_key_config()->action[4]) ? 0x3000 : (held & get_key_config()->action[5]) ? -0x3000 : 0;
    if (player_status & 1) {
        accel = 0;
    }
    if (accel != 0 && can_move(held)) {
        if (accel > 0) {
            if (move_speed < 0) {
                accel <<= 1;
            }
        } else if (move_speed > 0) {
            accel <<= 1;
        }
        move_speed += accel;
        /* limited to +-(boost << 17): MIN first, the low bound tested last */
        move_speed = -(boost << 17) > MIN(move_speed, boost << 17) ? -(boost << 17) : MIN(move_speed, boost << 17);
        moving = 1;
    } else {
        move_speed = move_speed * 7 / 8;
        if (ABS(move_speed) < 0x1000) {
            move_speed = 0;
        }
        moving = 0;
    }
    accel = 0x1000 - player_slowdown();
    if (held & get_key_config()->action[4]) {
        fwd = boost * (accel << 4) / 0x1000;
    } else if (held & get_key_config()->action[5]) {
        fwd = -(boost << 4) * accel / 0x1000;
    } else {
        fwd = 0;
    }
    accel = move_speed >> 12;
    if (ABS(accel) > ABS(fwd)) {
        fwd = accel;
    }
    fly_move(p->yaw >> 12, fwd, &p->vz, &p->vx);
    fwd = (held & get_key_config()->action[4]) ? 0x1800 : (held & get_key_config()->action[5]) ? -0x1800 : 0;
    if (fwd != 0) {
        if (fwd > 0) {
            if (p->walk_speed < 0) {
                fwd <<= 1;
            }
        } else if (p->walk_speed > 0) {
            fwd <<= 1;
        }
        p->walk_speed += fwd;
        p->walk_speed = -(boost << 16) > MIN(p->walk_speed, boost << 16) ? -(boost << 16) : MIN(p->walk_speed, boost << 16);
    } else {
        p->walk_speed = p->walk_speed * 3 / 4;
        if (ABS(p->walk_speed) < 0x1000) {
            p->walk_speed = 0;
        }
    }
    accel = strafe_input(held);
    if (accel != 0) {
        if (accel > 0) {
            if (p->strafe_speed < 0) {
                accel <<= 1;
            }
        } else if (p->strafe_speed > 0) {
            accel <<= 1;
        }
        p->strafe_speed += accel;
        p->strafe_speed = -(boost * 0x1A000) > MIN(p->strafe_speed, boost * 0x1A000)
                              ? -(boost * 0x1A000)
                              : MIN(p->strafe_speed, boost * 0x1A000);
    } else {
        p->strafe_speed = p->strafe_speed * 4 / 5;
        if (ABS(p->strafe_speed) < 0x1000) {
            p->strafe_speed = 0;
        }
    }
    /* do-while(0) (a macro in the original?): refs inside a loop count double, so player_status' register
     * is allocated (v1) before walking's (a0) */
    do {
        if (player_status & 1) {
            walking = accel;
            if ((player_status & 2) && p->spin_yaw == 0) {
                walking = accel || fwd;
            }
        } else {
            walking = accel;
        }
    } while (0);
    walking |= moving;
    if (walking) {
        player_strafe_meter = MIN(player_strafe_meter + 0x199, 0x1000);
    } else {
        player_strafe_meter = MAX(player_strafe_meter - 0x124, 0);
    }
    if (fwd || p->spin_yaw || accel) {
        player_walk_meter = MIN(player_walk_meter + 0x199, 0x1000);
    } else {
        player_walk_meter = MAX(player_walk_meter - 0x124, 0);
    }
    if (player_status & 1) {
        if (player_status & 2) {
            obj->pose = 0x211;
        } else {
            player_strafe_meter = 0x1000;
            obj->pose = 0x31;
        }
    } else if (player_status & 0x200) {
        obj->pose = 0x31;
    } else if ((p->x110 == 0 && p->vy < 0) || moving) {
        player_run_timer = 0;
        obj->pose = 0x71;
    } else if (player_status & 0x400) {
        if (jump_latch) {
            obj->pose = 0xF1;
        } else {
            obj->pose = 0x71;
        }
    } else if (player_run_timer >= 6) {
        obj->pose = 0xF1;
    } else {
        obj->pose = 0x71;
    }
    fly_strafe((p->yaw >> 12) + 0x400, (p->strafe_speed >> 12) * (0x1000 - player_slowdown()) / 0x1000, &p->vz, &p->vx);
    p->pitch += p->spin_pitch;
    p->pitch = MAX(MIN(p->pitch, 0x200000), -0x200000);
    p->roll += p->spin_roll;
    p->yaw += p->spin_yaw;
    /* the velocity is read before move is written (p and obj may alias for GCC) */
    vx = p->vx;
    vy = p->vy;
    vz = p->vz;
    obj->move[0] = vx;
    obj->move[1] = vy;
    obj->move[2] = vz;
    if (player_status & 0x100) {
        player_move_simple(p);
    } else {
        player_collide(p);
    }
    player_glow_level += player_glow_step;
    player_glow_level = MAX(MIN(player_glow_level, 0x4000), 0);
    player_walk_phase = (player_walk_phase + 0x92) & 0xFFF;
    player_step_phase += 0x92;
    if (player_step_phase > 0x800) {
        player_step_flag = 1;
    }
    player_step_phase &= 0x7FF;
    if (player_walk_meter == 0) {
        player_walk_phase = 0;
        player_step_phase = 0;
        player_step_flag = 0;
    }
    if (area_warnings() && (obj->flags & 0x10000) && cooldown_194 == 0) {
        show_line((s32)"Don't exit from theassigned area!\xA1"); /* sic */
        cooldown_194 = 0xF0;
    }
    fire_beam();
    cam_follow_update();
    if (player_mode != 0 && get_stage_end() == 0) {
        s32 y = views[0].y;
        s32 x = views[0].x;

        if (player_shake_index >= 0) {
            y += shake_table[player_shake_index];
        }
        set_view_offset(0, x + view_nudge[0], y + view_nudge[1]);
        set_view_nudge(0, 0);
    }
    move_sound();
}

/* Debug-display formats that follow player_control's strings in the original's rodata; nothing in the
 * stages references them (s01 and s03's debug_info_draw use their own copies). */
const char str_stat_fmt[] = "STAT:%x4";
const char str_char_fmt[] = "CHAR:%x6";
const char str_plan_fmt[] = "PLAN:%x6";
const char str_ceil_fmt[] = "CEIL:%x6";
const char str_land_fmt[] = "LAND:%x6";

s32 *rotate_vector(s32 *src, s32 *dst) {
    s32 rot_frac_x, rot_frac_y, rot_frac_z;
    s32 x = src[0];
    s32 y = src[1];
    s32 z = src[2];

    gte_set(IR1, x & 0xFFF);
    gte_set(IR2, y & 0xFFF);
    gte_set(IR3, z & 0xFFF);
    gte_rtir_sf0();
    x >>= 12;
    y >>= 12;
    z >>= 12;
    gte_get(MAC1, rot_frac_x);
    gte_get(MAC2, rot_frac_y);
    gte_get(MAC3, rot_frac_z);
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_rtir_sf0();
    rot_frac_x >>= 12;
    rot_frac_y >>= 12;
    rot_frac_z >>= 12;
    gte_get(MAC1, x);
    gte_get(MAC2, y);
    gte_get(MAC3, z);

    dst[0] = x + rot_frac_x;
    dst[1] = y + rot_frac_y;
    dst[2] = z + rot_frac_z;
    return dst;
}

/* Rotates move by -angle about Y, divides its Z by 3, rotates back (keeps move[1]). */
void damp_along(s32 *move, s32 angle) {
    s32 *mat32 = scratch_alloc(0x20);
    s16 *mat = (s16 *)mat32;
    s32 *tmp = scratch_alloc(0x10);
    s32 saved;
    s32 offset; /* byte offset into the 4-byte angle tables */
    s32 cos_v;
    s32 sin_v;
    s32 neg_sin;

    offset = (-angle & 0xFFF) * 4;
    do {
    } while (0);
    saved = move[1];
    cos_v = *(s16 *)((u8 *)cos_table + offset);
    sin_v = *(s16 *)((u8 *)rcossin_tbl + offset);
    neg_sin = -sin_v;

    mat[1] = 0;
    mat[3] = 0;
    mat[4] = 0x1000;
    mat[5] = 0;
    mat[7] = 0;
    mat[2] = sin_v;
    mat[0] = cos_v;
    mat[6] = neg_sin;
    mat[8] = cos_v;
    set_rot_matrix(mat32);
    rotate_vector(move, tmp);
    tmp[2] = tmp[2] / 3;
    mat[2] = neg_sin;
    mat[6] = sin_v;
    set_rot_matrix(mat32);
    rotate_vector(tmp, move);
    scratch_top -= 0x30;
    move[1] = saved;
}

/* Each step: ramps the current up (or down while the player is hurt or hiding), then moves and turns
 * the player with it. */
void flow_update(void) {
    PlayerObj *player;
    PlayerObj *player_opaque;
    Flow *f;
    Flow *f_held;
    s32 status;
    s16 turn;

    status = player_status;
    player = &player_obj;
    f = &flow;
    player_opaque = player;
    f_held = f;
    FAKE_OPAQUE(player_opaque);
    FAKE_OPAQUE(f_held);
    if (!(status & 0x60)) {
        flow_ramp = flow_ramp + flow_step;
    } else {
        flow_ramp = flow_ramp - 0x44;
    }
    flow_ramp = MAX(MIN(flow_ramp, 0x1000), 0);
    f->speed = flow_max * flow_ramp / 0x1000;
    flow_sample(f, *(s16 *)&player->x18, player->sub, flow_move, &turn);
    flow_turn = turn;
    add_displacement(flow_move[0], 0, flow_move[2]);
    fly_move(f->angle, f->speed, &flow_move[2], &flow_move[0]);
    if (f->state >= 0) {
        if (player_status & 8) {
            add_turn(flow_turn);
        }
        if (dev_mode() == 0 || !(player_held & PAD_SELECT)) {
            damp_along(player->move, get_flow_angle());
        }
    }
}

void push_decay(void) {
    s32 x, z;

    x = push_x;
    x = x * 15 / 16;
    if (abs(x) < 0x4000) {
        x = 0;
    }
    push_x = x;
    z = push_z;
    z = z * 15 / 16;
    if (abs(z) < 0x4000) {
        z = 0;
    }
    push_z = z;
    if (!(player_status & 0x60)) {
        displacement.x += x;
        d_8012BBD0 += z;
    }
}

/* When the ground is an object (ground id: (index + 1) << 8 | type, type 1), pushes the player away
 * from it: 0x20, or during a flow half the flow maximum + 0x28 (ending the flow ramp). Returns 1 if
 * pushed. */
s32 ground_push(s32 ground) {
    Object *obj;
    s32 angle;
    u32 index;

    index = (ground >> 8) - 1;
    if (index >= 0xFF || (ground & 0xFF) != 1) {
        return 0;
    }
    obj = obj_table[index & 0x7F];
    angle = atan2((player_xyz[2] - obj->z) >> 12, (player_xyz[0] - obj->x) >> 12);
    if (get_flow_max() > 0) {
        fly_move(angle, get_flow_max() / 2 + 0x28, &push_z, &push_z - 2);
        set_flow_ramp(0);
    } else {
        fly_move(angle, 0x20, &push_z, &push_z - 2);
    }
    return 1;
}

/* Moves `pos` (x and z) with the object the player stands on (`ground`: (index + 1) << 8 | type). */
void platform_carry(s32 ground, s32 *pos) {
    u32 index = (ground >> 8) - 1;
    Object *obj;
    s16 *delta;
    s32 dx;
    s32 dz;

    if (index < 0xFF) {
        obj = obj_table[index & 0x7F];
        if (test_bit(obj->flags, 5)) {
            delta = obj->move_delta;
            dx = delta[0];
            dz = delta[2];
            pos[0] += dx << 12;
            pos[2] += dz << 12;
        }
    }
}

/* Unless player_hit_cooldown is set, reports a hit between the player and object `index` through hit_target_masked:
 * to the object with the direction from the player to it and `a`, to the player (0) with the opposite
 * direction and `b`. */
void hit_feedback(s32 index, s32 a, s32 b) {
    Object *obj;
    s32 angle;

    if (index > 0 && player_hit_cooldown == 0) {
        obj = obj_table[index & 0x7F];
        angle = atan2((obj->z - player_xyz[2]) >> 12, (obj->x - player_xyz[0]) >> 12);
        hit_target_masked(index, 1, angle, a);
        hit_target_masked(0, 1, angle + 0x800, b);
    }
}

/* One step of player movement and collision: rotates the move into world space, adds the
 * displacement and the platform's carry, keeps the sub-cell position, collides with solids and
 * objects, rotates the result back, then turns contact into flow pushes, a bump sound and the
 * landing ground. */
void player_collide(PlayerObj *p) {
    s32 hit_angle;
    PlayerObj *obj;
    Collider *coll;
    s32 *mat;
    s16 *rows;
    s32 *vec;
    s16 hit[2];
    s32 x, y, z, sub_x, sub_y, sub_z;
    s32 cell_x, cell_z;
    s32 bumped;
    s32 contact;
    s16 *flow;
    s32 *push;
    s32 base, side;
    s32 turn;

    push_decay();
    flow_update();
    coll = &p->coll;
    collider_begin(coll);
    mat = scratch_alloc(0x20);
    vec = scratch_alloc(0x10);
    rot_matrix(mat, -p->angle[1], -p->angle[0], -p->angle[2]);
    obj = p;
    /* the empty loops here and below weight refs for register priority (mat, hit_angle) */
    do {
        set_rot_matrix(mat);
    } while (0);
    rotate_vector(p->move, vec);
    platform_carry(p->ground, vec);
    x = vec[0];
    y = vec[1];
    z = vec[2];
    sub_x = p->sub[0];
    sub_y = p->sub[1];
    sub_z = p->sub[2];
    x += displacement.x;
    y += displacement.y;
    z += displacement.z;
    x += sub_x & 0xFFF;
    y += sub_y & 0xFFF;
    z += sub_z & 0xFFF;
    sub_x = (sub_x >> 12 << 12) + (x & 0xFFF);
    sub_y = (sub_y >> 12 << 12) + (y & 0xFFF);
    sub_z = (sub_z >> 12 << 12) + (z & 0xFFF);
    p->sub[0] = sub_x;
    p->sub[1] = sub_y;
    p->sub[2] = sub_z;
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    limit_move(p->sub, vec);
    x = vec[0];
    z = vec[2];
    y = vec[1];
    z >>= 12;
    p->coll.pos[0] = (u32)x >> 12;
    {
        register s32 cell_y asm("$3") = (u32)y >> 12;

        coll->pos[1] = cell_y;
    }
    coll->pos[2] = z;
    cell_x = coll->pos[0];
    *(SubPos *)coll->sub = *(SubPos *)p->sub;
    coll->angle[0] = -p->rot[0];
    coll->angle[1] = -p->rot[1];
    coll->angle[2] = -p->rot[2];
    cell_z = (s16)z;
    if (!(player_status & 0x60)) {
        hit[0] = 0;
        hit[1] = 0;
        if (contact_20_steps > 0x78 && !meter_get_mode()) {
            set_collide_mode(3);
        } else {
            set_collide_mode(2);
        }
        collide_solids_y(coll);
        push_out_of_solids_xz(coll, hit);
        set_collide_mode(0);
    }
    x = coll->pos[0];
    y = coll->pos[1];
    z = coll->pos[2];
    vec[0] = x << 12;
    vec[1] = y << 12;
    vec[2] = z << 12;
    transpose_matrix(mat, mat);
    do {
        set_rot_matrix(mat);
    } while (0);
    rotate_vector(vec, obj->move);
    player_step_move_scratch(obj);
    if (!(player_status & 0x60)) {
        coll->contact &= ~8;
        vec[0] = obj->sub[0] >> 12;
        vec[1] = obj->sub[1] >> 12;
        vec[2] = obj->sub[2] >> 12;
        set_collide_mode(2);
        do {
            hit_angle = collide_objects(coll, vec, &hit[1]);
        } while (0);
        set_collide_mode(0);
        rot_matrix_b(mat, obj->angle[1], obj->angle[0], obj->angle[2]);
        rows = (s16 *)mat;
        if (rows[4] == 0x1000) { /* m[1][1] == 1.0: upright */
            if (coll->contact & 0x10) {
                obj->flags |= 2;
            }
            if (coll->contact & 8) {
                obj->flags |= 1;
                contact = coll->contact_id << 16;
                hit_angle = contact >> 16;
                if (get_flow_max() > 0) {
                    hit_feedback(hit_angle, 0x12C, 10);
                }
                obj->ground = (((hit_angle & 0xFF) + 1) << 8) | ((u32)contact >> 24);
                p->x110 = 1;
                ground_push(obj->ground);
            }
        }
    }
    p->x = obj->pos[0];
    p->y = obj->pos[1];
    p->z = obj->pos[2];
    if (coll->contact & 0x20) {
        contact_20_steps++;
    } else {
        contact_20_steps = 0;
    }
    if (get_flow_max() > 0 && (coll->contact & 5) && !p->slowdown) {
        hit_feedback(hit[0], 0x12C, 10);
        flow = &flow_angle;
        base = *flow;
        side = base - 0x800;
        do {
            hit_angle = ((hit_angle - side) << 20) >> 20;
        } while (0);
        if (ABS(hit_angle) <= 0x400) {
            push = &push_z;
            fly_strafe(hit_angle / 2 + base, 0x3C, push, push - 2);
            side = hit_angle > 0 ? 0x400 : -0x400;
            fly_strafe(side + *flow, 0x3C, push, push - 2);
        }
    }
    if (get_flow_max() > 0) {
        bumped = 0;
        if (cell_z && ((obj->flags & 0xC) || (coll->contact & 4))) {
            s32 *ramp;

            hit_angle = cell_z > 0 ? -0x28 : 0x28;
            ramp = &push_z;
            *ramp += (hit_angle - cell_z) << 12;
            set_flow_ramp(0);
            player_shake_index = 0;
            bumped = 1;
        }
        if (cell_x && ((obj->flags & 0x30) || (coll->contact & 1))) {
            s32 *ramp;

            hit_angle = cell_x > 0 ? -0x28 : 0x28;
            ramp = &push_x;
            *ramp += (hit_angle - cell_x) << 12;
            set_flow_ramp(0);
            player_shake_index = 0;
            bumped = 1;
        }
        if (bumped) {
            sound_start(SND_COLLISION_IMPACT | SND_GROUP(1), 0x7F, 0, 0);
        }
    }
    turn = pending_turn;
    displacement.x = 0;
    displacement.y = 0;
    displacement.z = 0;
    p->yaw += turn << 12;
    add_d_80136404(turn);
    scratch_top -= 0x20;
    scratch_top -= 0x10;
    pending_turn = 0;
}

/* Move the player without collision against the world: run the mover on its move, copy the result
 * to x/y/z, clear the displacement and apply the pending turn to yaw. */
void player_move_simple(PlayerObj *p) {
    collider_begin(&p->coll);
    p->move[1] = 0;
    player_rise_phase = 0x1000;
    player_fall_blend = 0;
    mover_move(&mover, -p->move[2], -p->move[0], 0);
    mover_apply(&mover, p);
    p->x = p->pos[0];
    p->y = p->pos[1];
    p->z = p->pos[2];
    displacement.x = 0;
    displacement.y = 0;
    displacement.z = 0;
    p->yaw += pending_turn << 12;
    add_d_80136404(pending_turn);
    pending_turn = 0;
}

void player_update(void) {
    player_update_begin();
    if (player_mode != 0) {
        player_control();
    } else {
        debug_fly();
    }
    timers_update();
    fade_list_update();
}

/* Builds slotA's poses, then moves both joint groups: each group's offset is
 * its first joint's position in slotA minus that in the next slot
 * (player_pose_base + 1), written to out[group]; all five joints of the group take
 * slotB's pose shifted by that offset. */
void pchr_pose_shift_copy(s32 slotA, s32 slotB, SVECTOR *out) {
    PchrPoseList *poses;
    PchrPoseList *src;
    PchrPoseList *next;
    s32 *joint;
    s32 group, k;
    s32 off;
    s32 dx, dy, dz;
    s32 idx;
    SVECTOR unused[2]; /* unused; the original's frame holds 16 bytes of locals */

    poses = (PchrPoseList *)pchr_poses_build(slotA);
    group = 0;
    off = 0;
    pchr_table[slotA & 0x7FF].unk_0C = (s32 *)poses;
    src = (PchrPoseList *)pchr_table[slotB & 0x7FF].unk_0C;
    next = (PchrPoseList *)pchr_table[(player_pose_base + 1) & 0x7FF].unk_0C;
    do {
        joint = (s32 *)((u8 *)pose_joint_indices + off);
        k = 0;
        idx = *(s32 *)((u8 *)pose_joint_indices + off);
        dx = poses->pose[idx].pos[0] - next->pose[idx].pos[0];
        dy = poses->pose[idx].pos[1] - next->pose[idx].pos[1];
        dz = poses->pose[idx].pos[2] - next->pose[idx].pos[2];
        out[group].vx = dx;
        out[group].vy = dy;
        out[group].vz = dz;
        do {
            idx = *joint;
            poses->pose[idx].pos[0] = src->pose[idx].pos[0] + dx;
            poses->pose[idx].pos[1] = src->pose[idx].pos[1] + dy;
            poses->pose[idx].pos[2] = src->pose[idx].pos[2] + dz;
            poses->pose[idx].rot[0] = src->pose[idx].rot[0];
            poses->pose[idx].rot[1] = src->pose[idx].rot[1];
            poses->pose[idx].rot[2] = src->pose[idx].rot[2];
            k++;
            joint++;
        } while (k < 5);
        group++;
        off += 0x14;
    } while (group < 2);
}

/* Interpolates a 5-entry s16 table at x (4096 units per entry; the entries wrap, 4 -> 0). */
s32 interp_table5(s32 x, s16 *table) {
    s32 biased, index, base, cur, next, step;

    biased = x;
    if (x < 0) {
        biased = x + 0xFFF;
    }
    index = biased >> 12;
    base = index << 12;
    x -= base;
    cur = table[index];
    next = table[(index + 1) % 5];
    step = (next - cur) * x;
    if (step < 0) {
        step += 0xFFF;
    }
    return (step >> 12) + cur;
}

/* Interpolates between entries base+i and base+i+1 (wrapping to base) at position count*step (or
 * (count-1)*step when `last` is 0) in 20.12 fixed point. */
s32 ring_sample_lerp(s32 base, s32 count, s32 step, s32 last) {
    s32 pos;
    s32 i;
    s32 frac;

    if (last) {
        pos = count * step;
    } else {
        pos = (count - 1) * step;
    }
    i = pos >> 12;
    last = i + 1; /* reused as the next index */
    if (last >= count) {
        last = 0;
    }
    frac = pos & 0xFFF;
    return pchr_blend(i + base, last + base, 0x1000 - frac, 0);
}

s32 player_move_anim_index(void)
{
    PlayerObj *pl = &player_obj;
    s32 base = player_pose_base;
    s32 neutral;
    s32 idle = 1;
    s32 model;
    s32 strafe;
    s32 walk;
    s32 strafe_model;
    s32 walk_model;
    s32 total;

    if ((player_status & 3) == 1) {
        idle = 0xD;
    }
    if (player_turn_dir > 0) {
        model = base + 0x20;
    } else if (player_turn_dir < 0) {
        model = base + 0x21;
    } else {
        model = base + idle;
    }
    strafe = ABS(pl->strafe_speed) / 26;
    neutral = base + idle;
    strafe_model = pchr_blend(model, neutral, strafe, 0);
    if (pl->walk_speed > 0) {
        model = base + 0x23;
    } else if (pl->walk_speed < 0) {
        model = base + 0x22;
    } else {
        model = neutral;
    }
    walk = ABS(pl->walk_speed) / 16;
    neutral = base + idle;
    walk_model = pchr_blend(model, neutral, walk, 0);
    total = walk + strafe;
    if (total > 0) {
        model = pchr_blend(strafe_model, walk_model, (strafe << 12) / total, 0);
    } else {
        model = neutral;
    }
    return model;
}

/* Fires a fly_move-aimed effect at (x, y, z) when player_status bit 2 is set or mode == 1,
 * the cooldown has expired, player_strafe_meter is at least 0x400 and player_landed is set. */
void fly_effect_spawn(s32 x, s32 y, s32 z, s32 unk_a3, s32 unk_a4, s32 unk_a5, s32 unk_a6, s32 mode) {
    s32 fly_dx;
    s32 fly_dz;
    Vec3 *pos;
    u16 *rot;
    s32 angle;
    s32 base;

    if (((player_status & 4) || (mode == 1)) && (cooldown_19c <= 0) && (player_strafe_meter >= 0x400) && (player_landed != 0)) {
        fly_dx = d_801395B8;
        fly_dz = d_801395B4;
        if (fly_dx != 0 || fly_dz != 0) {
            angle = atan2(fly_dx, fly_dz) + 0x800;
            fly_move(angle, -0x8C, &fly_dx, &fly_dz);
            pos = scratch_alloc(0x10);
            rot = scratch_alloc(8);
            cooldown_19c = 4;
            pos->y = y;
            base = beam_model_base + 0x52;
            x += fly_dz >> 12;
            z += fly_dx >> 12;
            pos->x = x;
            pos->z = z;
            rot[0] = 0;
            rot[1] = angle;
            rot[2] = 0;
            fade_list_add(pos, rot, base, 0, 5, 0x100, 0x1000, 0);
            scratch_top -= 0x18;
        }
    }
}

/* Sets the four words ending at d_8012BC30 to 1, last first. */
void flag_words_set_one(void) {
    s32 value = 1;
    s32 i = 3;
    s32 *p = &d_8012BC30;

    do {
        *p = value;
        i--;
        p--;
    } while (i >= 0);
}

/* Clears the four words ending at d_8012BC30, last first. */
void flag_words_clear(void) {
    s32 i = 3;
    s32 *p = &d_8012BC30;

    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}

/* 1 when base + bias is non-negative, where bias is 8 if mode is set, else 2. */
u32 step_threshold_crossed(s32 base, s32 mode) {
    s32 sum;

    if (mode != 0) {
        sum = base + 8;
    } else {
        sum = base + 2;
    }
    return (u32) ~sum >> 31;
}

/* Footstep check for the four tracked body parts: builds the pose list of sequence seq, and for each part whose
 * height change against the previous pose crosses the step threshold (step_threshold_crossed on the old flag) starts a sound
 * (0x2008, 0x2009 for mode 1) and for mode 1 also two fade-list effects at the part's position rotated by angle.
 * Meter at or over 0x400: flag_words_set_one; no pose data yet: flag_words_clear. */
extern s32 footstep_part_flags[4];
extern s32 d_8011DDE8[4];

void player_footstep_check(s32 x, s32 y, s32 z, s32 angle, s32 unused0, s32 unused1, s32 seq, s32 mode) {
    s32 hit = 0;
    Vec3 *pos = scratch_alloc(0x10);
    s16 *frac = scratch_alloc(8);
    s32 tex;
    s32 i;
    PchrPoseList *cur;
    PchrPoseList *prev;
    s32 dx;
    s32 dy;
    s32 dz;

    if (player_strafe_meter < 0x400) {
        if (player_landed != 0) {
            prev = (PchrPoseList *)pchr_table[(player_pose_base + 1) & 0x7FF].unk_0C;
            pchr_lists_build(seq);
            cur = (PchrPoseList *)pchr_table[seq & 0x7FF].unk_0C;
            for (i = 0; i < 4; i++) {
                s32 *flag = &footstep_part_flags[i];
                s32 old = *flag;
                s32 part = d_8011DDE8[i];
                s32 now = step_threshold_crossed(cur->pose[part].pos[1] - prev->pose[part].pos[1], old);

                *flag = now;
                if (old != 1 && now != 0) {
                    hit = 1;
                    if (mode == 1) {
                        dx = cur->pose[part].pos[0];
                        dy = 0;
                        dz = cur->pose[part].pos[2];
                        rotate_xz_twice(angle, 0, &dx, &dy, &dz);
                        pos->x = x + dx;
                        pos->y = y + dy;
                        pos->z = z + dz;
                        tex = beam_model_base + 0x803E;
                        frac[0] = 0;
                        frac[1] = 0;
                        frac[2] = 0;
                        fade_list_add(pos, (u16 *)frac, tex, 0x600, 0x1200, 0xCC, 0x1800, -0x133);
                        tex = beam_model_base + 0x4E;
                        frac[0] = -0x400;
                        frac[1] = 0;
                        frac[2] = 0;
                        fade_list_add(pos, (u16 *)frac, tex, 0, mode, 0x200, 0x1000, -0x155);
                    }
                }
            }
            if (hit) {
                sound_start(mode == 1 ? SND_SMALL_SPLASH | SND_GROUP(1) : 0x2008, 0x40, 0, 0);
            }
        } else {
            flag_words_clear();
        }
    } else {
        flag_words_set_one();
    }
    scratch_top -= 0x18;
}

s32 pchr_attach_seq(s32 model, s32 size) {
    SVECTOR *pos = scratch_alloc(8);
    SVECTOR *rot = scratch_alloc(8);
    s32 *seq;
    register s32 half asm("$5");

    model = pchr_copy_slot(model);
    seq = pchr_poses_build(model);
    half = (u32)(size + ((u32)size >> 31)) >> 1;
    pchr_table[model & 0x7FF].unk_0C = seq;
    pos->vy = -0x54;
    pos->vx = 0;
    pos->vz = -0xD;
    rot->vy = half;
    rot->vx = size;
    rot->vz = 0;
    pose_rotate_range(seq, 0, 0x1B, pos, rot);
    scratch_top -= 16;
    return model;
}

static inline s32 spark_rgb(s32 r, s32 g, s32 b) {
    s32 blue = b;

    if (!(r | g)) {
        blue = 1;
    }
    return (blue << 16) | (g << 8) | r;
}
static inline s32 spark_rgb_pinned(s32 r, s32 g, s32 b) {
    register s32 blue asm("$4") = b;
    register s32 word asm("$2");

    if (!(r | g)) {
        blue = 1;
    }
    word = blue << 16;
    return word | (g << 8) | r;
}
void player_sparks_update(void) {
    s32 pose;
    s32 walk;
    s32 anim;
    s32 blend;
    s32 base;
    s32 *m;
    s32 x, y, z;
    s32 ax, ay, az;
    s32 *hit;
    s32 r, g;
    s32 shade;
    s32 *from;
    s32 value;

    if (player_mode == 0) {
        return;
    }
    if (player_shake_index >= 0) {
        player_shake_index++;
        if (shake_table[player_shake_index] < 0) {
            player_shake_index = -1;
        }
    }
    base = player_pose_base;
    if (player_air_blend != 0x1000) {
        register s32 meter asm("$6") = player_walk_meter;

        if (meter != 0) {
            walk = meter - player_strafe_meter;
            if (walk != 0) {
                pose = ring_sample_lerp(base + 0x10, 0x10, player_walk_phase, 1);
            }
            if (walk != 0x1000) {
                anim = player_move_anim_index();
            }
            pose = pchr_blend(pose, anim, walk, 0);
        }
        player_step_flag = 0;
        anim = base + 1;
        if ((player_status & 3) == 1) {
            anim = base + 0xD;
        }
        walk = pchr_blend(pose, anim, player_walk_meter, 0);
    }
    if (player_air_blend != 0) {
        if (player_land_blend != 0x1000) {
            if (player_fall_blend != 0x1000) {
                anim = ring_sample_lerp(base + 5, 4, player_rise_phase, 0);
            }
            anim = pchr_blend(base + 0xB, anim, player_fall_blend, 0);
        }
        blend = pchr_blend(base + 0xC, anim, player_land_blend, 0);
    }
    value = pchr_blend(blend, walk, player_air_blend, 0);
    if (player_charge_blend > 0) {
        pchr_lists_build(value);
        value = pchr_copy_slot(value);
        pose = pchr_blend(ring_sample_lerp(base + 2, 2, player_charge_phase, 1), base + 1, player_charge_blend, 0);
        pchr_lists_build(pose);
        pchr_pose_shift_copy(value, pose, (SVECTOR *)&pose_shift_vx);
    }
    if (player_death_fade >= 0) {
        value = pchr_blend(ring_sample_lerp(base + 0x31, 0x23, player_death_fade, 0), value, player_death_blend, 0);
    }
    m = scratch_alloc(0x40);
    rot_matrix(m, (player_angles[0] >> 12) + 0x800, 0, 0);
    rot_matrix(m + 8, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
    mul_matrix(m + 8, m, m);
    matrix_to_angles(m, &ax, &ay, &az);
    z = player_xyz[2] >> 12;
    x = player_xyz[0] >> 12;
    y = player_xyz[1] >> 12;
    if (!(player_status & 2)) {
        player_footstep_check(x, y, z, ax, ay, az, value, (surface_of(player_ground_id) & 0x300) >> 8);
        fly_effect_spawn(x, y, z, ax, ay, az, value, (surface_of(player_ground_id) & 0x300) >> 8);
    }
    if (player_slowdown()) {
        ax += player_slowdown() / 16;
        value = pchr_blend(base + 0x20, value, player_slowdown(), 0);
    }
    anim = 0;
    if (player_glow_level) {
        FAKE_OPAQUE(anim);
        value |= 0x8000;
        r = interp_table5(player_glow_level, spark_red_table);
        g = interp_table5(player_glow_level, spark_green_table);
        shade = r >> 5;
        anim = spark_rgb_pinned(shade, g >> 5, anim);
    }
    if (player_hit_flash > 0) {
        value &= ~0x8000;
        anim = 0x40C0FF;
    }
    if (player_death_fade >= 0) {
        if (player_exit_timer > 0) {
            value = pchr_attach_seq(base + 8, (player_exit_timer << 12) / 48);
        }
        spark_add(x, y, z, ax, ay, az, value, anim);
    }
    if (player_hit_flash != 0) {
        player_hit_flash = -1;
    }
    from = scratch_alloc(0x20);
    rot_load(m);
    gte_set_ctrl(TRX, x);
    gte_set_ctrl(TRY, y);
    gte_set_ctrl(TRZ, z);
    hit = from + 4;
    hit[0] = 0;
    hit[1] = 0x800;
    hit[2] = 0;
    transform_point((VECTOR *)hit, (VECTOR *)hit);
    from[0] = x;
    from[1] = y;
    from[2] = z;
    if (trace_world(1, 8, from, hit, from)) {
        value = hit_spark_pchr;
        anim = isqrt(length_sq(from[0] - x, from[1] - y, from[2] - z));
        anim = MAX(MIN(anim, 0x800), 0);
        x = from[0];
        y = from[1];
        z = from[2];
        anim = 0x800 - anim;
        if (player_death_fade >= 0) {
            shade = anim >> 5;
            spark_add(x, y, z, ax, ay, az, value, spark_rgb(shade, shade, shade));
        }
    }
    scratch_top -= 0x20;
    scratch_top -= 0x40;
    engine_sparks();
    beam_timer_sparks_emit();
    fade_emit_sparks();
}

/* Points camera 0 at the player (or lets the player's own camera do it) and updates the sound listener. */
void place_view(void) {
    PlayerObj *player;
    PlayerObj *held;
    s16 *angles;
    s32 mode;

    cam_set_rec(0, 0);
    cam_set_scale(0, 0x1000, 0x1000);
    mode = player_mode;
    player = &player_obj;
    held = player;
    FAKE_OPAQUE(held);
    if (mode != 0) {
        cam_blend_view(0);
    } else {
        cam_set_pos(0, player_xyz[0] >> 12, (player_xyz[1] >> 12) - 0x90, player_xyz[2] >> 12);
        cam_set_rot(0, -player_angles[0] >> 12, -player_angles[1] >> 12, -player_angles[2] >> 12);
    }
    sound_set_listener_pos(player->x >> 12, player->y >> 12, player->z >> 12);
    angles = view_angles_get();
    sound_set_listener_angles(-angles[0], -angles[1], -angles[2]);
}

/* Copies the position to a scratch Vec3 as 20.12 fixed point and passes it to sound_set_pos. */
s32 sound_set_pos_from_rec(SoundPosSource *src, s32 arg) {
    Vec3 *vec = scratch_alloc(0x10);

    vec->x = src->pos.x << 12;
    vec->y = src->pos.y << 12;
    vec->z = src->pos.z << 12;
    sound_set_pos(arg, vec);
    scratch_top -= 0x10;
    return 0;
}

extern PlayerCoord player_y __asm__("player_xyz_y");
extern PlayerCoord player_z __asm__("player_xyz_z");
void fire_beam(void) {
    VECTOR *v;
    s32 *rot;
    s32 *pitch_rot;
    s32 t0, t1, t2;
    VECTOR *beam_end;
    s32 hit;
    s32 surf;
    void *impact;
    s16 target;
    s32 x, y, z, dx, dy, dz;
    s32 tx, ty, tz;

    if (player_charge_blend < 0x1000 || player_charge_timer <= 0) {
        beam_countdown = 0;
        target_hit_steps = 0;
        return;
    }
    if (--beam_countdown > 0) {
        return;
    }
    v = scratch_alloc(0x30);
    rot = scratch_alloc(0x40);
    beam_countdown = 4;
    rot_matrix(rot, player_angles[0] >> 12, 0, 0);
    pitch_rot = rot + 8;
    rot_matrix(pitch_rot, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
    mul_matrix(pitch_rot, rot, rot);
    gte_set_R012(t0, t1, t2, rot[0], rot[1], rot[2]);
    gte_set_R34(t0, t1, rot[3], rot[4]);
    tx = player_xyz[0] >> 12;
    ty = player_y.v >> 12;
    tz = player_z.v >> 12;
    gte_set_ctrl(TRX, tx);
    gte_set_ctrl(TRY, ty);
    gte_set_ctrl(TRZ, tz);
    v[0].vx = 0; v[0].vy = -0x50; v[0].vz = 0x68;
    transform_point(&v[0], &v[0]);
    beam_end = &v[1];
    beam_end->vx = 0; beam_end->vy = -0x50; beam_end->vz = 0x700;
    transform_point(beam_end, beam_end);
    v[2].vx = 0x26; v[2].vy = 0; v[2].vz = 0;
    rotate_point(&v[2], &v[2]);
    if (target_hit_steps > 0) {
        target_hit_steps--;
    }
    add_mission_total(1);
    beam_find_target(beam_end);
    hit = trace_world(4, 8, v, beam_end, beam_end);
    surf = (surface_of(v[1].pad) & 0x300) >> 8;
    set_collide_mode(2);
    if (trace_objects(v, beam_end, 8, beam_end, &target)) {
        if (target & 0x100) {
            hit_target(target, 1, (s16)atan2(v[1].vz - v[0].vz, v[1].vx - v[0].vx), 0x20, 1 << v[1].pad);
            target_hit_steps = 6;
        }
        hit = 1;
        surf = 0;
    }
    set_collide_mode(0);
    if (target_hit_steps > 0) {
        add_mission_count(1);
    }
    if (hit) {
        x = v[1].vx;
        dx = v[2].vx;
        y = v[1].vy;
        z = v[1].vz;
        dy = v[2].vy;
        dz = v[2].vz;
        beam_impact(x - dx, y - dy, z - dz, surf);
        impact = beam_impact(x + dx, y + dy, z + dz, surf);
        if (impact) {
            sound_attach(sound_start(SND_RICOCHET | SND_GROUP(1), 0x40, 0, 0), impact, (void (*)())sound_set_pos_from_rec);
        }
    }
    scratch_top -= 0x70;
}

void spark_add_offset(s32 *base, s32 *offset, s32 *extra, s32 value, s32 level) {
    s32 e0, e1, e2;
    s32 c;
    s32 hi;
    s32 bx = base[0], by = base[1], bz = base[2];
    s32 ox = offset[0], oy = offset[1], oz = offset[2];

    e2 = 0;
    e0 = 0;
    e1 = 0;
    if (extra != NULL) {
        e0 = extra[0];
        e1 = extra[1];
        e2 = extra[2];
    }
    c = level >> 5;
    hi = c;
    if (hi == 0) {
        hi = 1;
    }
    spark_add(bx + ox, by + oy, bz + oz, e1, e0, e2, value, (hi << 16) | (c << 8) | c);
}

void engine_sparks(void) {
    VECTOR *out;
    s32 *rot;
    s32 ax, ay, az;
    VECTOR *p1, *p2;
    s32 *extra;
    s32 frame, phase, level, value, i;

    if (player_charge_blend >= 0x1000 && player_charge_timer > 0) {
        out = scratch_alloc(0x40);
        rot = scratch_alloc(0x40);
        rot_matrix(rot, (player_angles[0] >> 12) + 0x800, 0, 0);
        rot_matrix(rot + 8, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
        mul_matrix(rot + 8, rot, rot);
        matrix_to_angles(rot, &ax, &ay, &az);
        out[3].vx = ay;
        out[3].vy = ax;
        out[3].vz = az;
        {
            register s32 w0 asm("$3") = rot[0];
            register s32 w1 asm("$4") = rot[1];
            register s32 w2 asm("$2") = rot[2];
            gte_set_ctrl(R11R12, w0);
            gte_set_ctrl(R13R21, w1);
            gte_set_ctrl(R22R23, w2);
        }
        {
            register s32 w3 asm("$3") = rot[3];
            register s32 w4 asm("$4") = rot[4];
            gte_set_ctrl(R31R32, w3);
            gte_set_ctrl(R33, w4);
        }
        {
            register s32 px asm("$4") = player_xyz[0] >> 12;
            register s32 py asm("$2") = player_xyz[1] >> 12;
            register s32 pz asm("$3") = player_xyz[2] >> 12;
            gte_set_TR(px, py, pz);
        }
        scratch_top -= 0x40;
        p1 = &out[1];
        p1->vx = pose_shift_vx - 0x26;
        p1->vy = pose_shift_vy;
        p1->vz = pose_shift_vz;
        rotate_point(p1, p1);
        p2 = &out[2];
        p2->vx = pose_shift2_vx + 0x26;
        p2->vy = pose_shift2_vy;
        p2->vz = pose_shift2_vz;
        rotate_point(p2, p2);
        frame = beam_model_base;
        phase = (player_charge_phase + 0x555) & 0xFFF;
        if (phase >= 0xAAA) {
            level = (0x1000 - phase) * 3;
            value = spark_point_table[4].pad + frame + 1;
            transform_point(&spark_point_table[4], out);
            spark_add_offset((s32 *)out, (s32 *)p1, 0, value, level);
            spark_add_offset((s32 *)out, (s32 *)p2, 0, value, level);
        }
        if (player_charge_phase >= 0xAAB) {
            level = player_charge_phase * 3 - 0x2000;
            i = 0;
            extra = (s32 *)&out[3];
            for (; i < 4; i++) {
                value = spark_point_table[i].pad + frame + 1;
                transform_point(&spark_point_table[i], out);
                if (i != 1) {
                    spark_add_offset((s32 *)out, (s32 *)&out[1], 0, value, level);
                    spark_add_offset((s32 *)out, (s32 *)&out[2], 0, value, level);
                } else {
                    spark_add_offset((s32 *)out, (s32 *)&out[1], extra, value, level);
                    spark_add_offset((s32 *)out, (s32 *)&out[2], extra, value, level);
                }
            }
        }
        scratch_top -= 0x40;
    }
}

/* Locks every target of the current lock (lock_count), listed in reverse in missile_targets. */
void lock_targets(void) {
    s32 i;
    s32 next;

    missiles_left = lock_count();
    missile_delay = 4;
    for (i = 0; i < missiles_left; i = next) {
        s16 target = locked_target(i);
        next = i + 1;
        missile_targets[missiles_left - next] = target;
    }
}

extern PlayerCoord player_y __asm__("player_xyz_y");
extern PlayerCoord player_z __asm__("player_xyz_z");
extern s32 player_yaw __asm__("player_angles");
/* Fires the next missile of the salvo every 4 frames, alternating sides, aimed with a random spread. */
void fire_missiles(void) {
    VECTOR *origin;
    u16 *aim;
    s32 *rot;
    s32 *view_rot;
    s32 pitch;
    s32 side;
    s32 ax, ay, az;
    u16 hx, hy, hz;
    s32 tx, ty, tz;

    if (missiles_left <= 0) {
        return;
    }
    if (--missile_delay > 0) {
        return;
    }
    origin = scratch_alloc(0x10);
    aim = (u16 *)scratch_top;
    scratch_top += 8;
    rot = scratch_alloc(0x40);
    do {
        view_rot = rot + 8;
        missile_delay = 4;
        missiles_left--;
        rot_matrix(view_rot, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
    } while (0);
    side = rand_a_next() * 0x180 / 4096 + 0x80;
    if (missiles_left & 1) {
        side = -side;
    }
    pitch = rand_a_next() / 16;
    rot_matrix(rot, (player_yaw >> 12) + side, pitch + 0x100, 0);
    mul_matrix(view_rot, rot, rot);
    matrix_to_angles(rot, &ax, &ay, &az);
    hy = *(u16 *)&ay;
    hx = *(u16 *)&ax;
    hz = *(u16 *)&az;
    aim[0] = hy;
    aim[1] = hx;
    aim[2] = hz;
    /* the array read keeps the load below the aim stores */
    rot_matrix(rot, player_angles[0] >> 12, 0, 0);
    mul_matrix(view_rot, rot, rot);
    rot_load(rot);
    tx = player_xyz[0] >> 12;
    ty = player_y.v >> 12;
    tz = player_z.v >> 12;
    gte_set_ctrl(TRX, tx);
    gte_set_ctrl(TRY, ty);
    gte_set_ctrl(TRZ, tz);
    side = 0x26;
    if (missiles_left & 1) {
        side = -0x26;
    }
    origin->vx = side;
    origin->vy = -0x50;
    origin->vz = 0x68;
    transform_point(origin, origin);
    add_mission_total(1);
    launch_missile((s32 *)origin, (Bytes8 *)aim, missile_targets[missiles_left]);
    scratch_top -= 0x58;
}

void throw_grenade(void) {
    PlayerObj *obj = &player_obj;
    VECTOR *dir;
    SVECTOR *aim;
    RotMatrix *m;
    RotMatrix *m2;
    u16 ang[6];
    u16 pa, pb, pc;
    PlayerObj *body = obj;
    volatile s32 *mv;
    s32 rot0, rot1, rot2;
    s32 tx, ty, tz;

    if (mission_status_active() && get_meter_run_flag()) {
        if (grenades_get() == 0) {
            sound_start(SND_PICKUP_DENIED | SND_VOICE_FLAG, 0x64, 0, 0);
            if (cooldown_18c <= 0) {
                show_line((s32)"No grenades.\xA1");
                cooldown_18c = 0x3C;
            }
            if (!dev_mode()) {
                return;
            }
        }
        if (grenades_in_air() <= 0) {
            grenades_add(-1);
            dir = scratch_alloc(0x10);
            aim = scratch_alloc(8);
            m = scratch_alloc(0x40);
            mv = (volatile s32 *)m;
            m2 = m + 1;
            rot_matrix(m2, -body->rot[1], -body->rot[0], -body->rot[2]);
            rot_matrix(m, obj->yaw >> 12, 0, 0);
            mul_matrix(m2, m, m);
            matrix_to_angles(m, &ang[0], &ang[2], &ang[4]);
            pa = ang[2];
            pb = ang[0];
            pc = ang[4];
            aim->vx = pa;
            aim->vy = pb;
            aim->vz = pc;
            rot0 = mv[0];
            rot1 = mv[1];
            rot2 = mv[2];
            gte_set_ctrl(R11R12, rot0);
            gte_set_ctrl(R13R21, rot1);
            gte_set_ctrl(R22R23, rot2);
            rot0 = mv[3];
            rot1 = mv[4];
            gte_set_ctrl(R31R32, rot0);
            gte_set_ctrl(R33, rot1);
            tx = obj->x >> 12;
            ty = obj->y >> 12;
            tz = obj->z >> 12;
            gte_set_ctrl(TRX, tx);
            gte_set_ctrl(TRY, ty);
            gte_set_ctrl(TRZ, tz);
            dir->vy = -0x50;
            dir->vx = 0;
            dir->vz = 0x50;
            transform_point(dir, dir);
            add_mission_total(1);
            launch_grenade((Vec3 *)dir, (AimPacket *)aim);
            scratch_top -= 0x58;
        }
    }
}

void beam_timers_reset(void) {
    timer_first = 0;
    beam_timer_next = 0;
    timer_count = 0;
    d_80120204 = 0;
}

void *beam_impact(s32 x, s32 y, s32 z, s32 kind) {
    BeamTimer *t;
    s32 length;
    s32 phase;

    if (timer_count == 0x10) {
        return NULL;
    }
    timer_count += 1;
    t = (BeamTimer *)&timers[beam_timer_next & 0xF];
    t->x = x;
    t->y = y;
    t->z = z;
    t->unk_04 = 0;
    if (kind == 1) {
        length = 0x48;
        phase = 5;
    } else {
        length = ((rand_b_next() * 3) / 4096) * 4 + 0x30;
        phase = 4;
    }
    t->phase = phase;
    t->length = beam_model_base + length;
    beam_timer_next = (beam_timer_next + 1) & 0xF;
    return t;
}

void timers_update(void) {
    u8 i;
    s16 phase;
    Timer *t;
    s32 n;

    i = timer_first & 0xF;
    for (n = timer_count; n > 0; n--, i = (i + 1) & 0xF) {
        t = &timers[i];
        phase = t->phase + 0x200;
        t->phase = phase;
        if (phase >= 0x1000) {
            timer_count--;
            timer_first = (timer_first + 1) & 0xF;
        }
    }
}

/* Spawn a spark at each live beam timer's position, its value sampled along the beam ring. */
void beam_timer_sparks_emit(void) {
    s32 count = timer_count;
    u16 idx = timer_first & 0xF;
    BeamTimer *t;

    if (count > 0) {
        do {
            t = (BeamTimer *)&timers[idx];
            spark_add_head(&spark_list, t->x, t->y, t->z, 0, 0, 0,
                           ring_sample_lerp(t->length, t->phase, (s16)t->unk_04, 0), 0);
            count--;
            idx = (idx + 1) & 0xF;
        } while (count > 0);
    }
}

/* View-cone test of a camera-space point with a radius: in front (z >= 0x80),
   |x| within min(z / 4, radius + 0x1C0), and |y| * 4 / 3 within |z| + radius. */
s32 view_cone_contains(VECTOR *pos, s32 radius)
{
    s32 z = pos->vz;
    s32 x = pos->vx;
    s32 y = pos->vy;
    s32 limit;
    s32 inside;

    if (z < 0x80) {
        return 0;
    }
    limit = MIN(z / 4, radius + 0x1C0);
    if (ABS(x) > limit) {
        inside = 0;
    } else {
        s32 reach = ABS(z) + radius;
        register s32 short_of asm("$2") = reach < ABS(y) * 4 / 3;
        inside = short_of ^ 1;
    }
    return inside;
}

static inline void rot_store(s32 *m) {
    s32 a, b, c;

    gte_get_ctrl(R11R12, a);
    gte_get_ctrl(R13R21, b);
    gte_get_ctrl(R22R23, c);
    m[0] = a;
    m[1] = b;
    m[2] = c;
    gte_get_ctrl(R31R32, a);
    gte_get_ctrl(R33, b);
    m[3] = a;
    m[4] = b;
    do {
    } while (0);
}
s32 beam_find_target(VECTOR *out) {
    s32 best_dist;
    s32 best_angle;
    s32 px, py, pz;
    s32 solid;
    s32 part;
    s32 found;
    s16 *box;
    s32 *view;
    s32 *pos;
    s32 *vm;
    s32 *m;
    s32 dz;
    s32 dy;
    s32 dx;
    s32 radius;
    register u32 mask asm("$20");
    Object *obj;
    VECTOR *pt;
    s32 dist;
    s32 angle;

    view = scratch_alloc(0x20);
    pt = scratch_alloc(0x20);
    box = scratch_alloc(8);
    pos = player_position();
    px = pos[0];
    py = pos[1];
    pz = pos[2];
    vm = view_matrix_t_get();
    rot_load(vm);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    rot_store(view);
    best_dist = 0x310000;
    obj = *(Object **)get_obj_list_actors();
    best_angle = 0x400;
    found = 0;
    for (; obj->node.next != NULL; obj = (Object *)obj->node.next) {
        if (!test_bit(obj->flags, 5)) {
            continue;
        }
        radius = isqrt(length_sq(obj->width, (s16)obj->height / 2, obj->unk_1E8[0]));
        dx = (obj->x >> 12) - px;
        dy = (obj->y >> 12) - (s16)obj->height / 2 - py;
        dz = (obj->z >> 12) - pz;
        if (ABS(dx) - radius > 0x700) {
            continue;
        }
        if (ABS(dy) - radius > 0x700) {
            continue;
        }
        if (ABS(dz) - radius > 0x700) {
            continue;
        }
        if (length_sq(dx, dy, dz) - radius * radius >= best_dist) {
            continue;
        }
        m = scratch_alloc(0x20);
        rot_matrix(m, obj->yaw, -obj->pitch, obj->roll);
        rot_load(m);
        gte_set(VXY0, (-(s16)obj->height / 2) << 16);
        gte_set(VZ0, 0);
        gte_rtv0();
        gte_get(MAC1, dx);
        gte_get(MAC2, dy);
        gte_get(MAC3, dz);
        scratch_top -= 0x20;
        dx += (obj->x >> 12) - px;
        dy += (obj->y >> 12) - py;
        dz += (obj->z >> 12) - pz;
        rot_load(view);
        pt[0].vx = dx;
        pt[0].vy = dy;
        pt[0].vz = dz;
        transform_point(pt, pt);
        if (!view_cone_contains(pt, radius)) {
            continue;
        }
        solid = obj->solid_id;
        part = 0;
        mask = solid_part_mask(solid);
        mask &= obj_hit_get_unk08(obj->index);
        for (; mask != 0; mask >>= 1, part++) {
            if (!(mask & 1)) {
                continue;
            }
            if (!solid_part_box(solid, part, &pt[1].vx, box)) {
                continue;
            }
            dx = pt[1].vx;
            dy = pt[1].vy;
            dz = pt[1].vz;
            dx -= px;
            dy -= py;
            dz -= pz;
            dist = length_sq(dx, dy, dz);
            if (dist - radius * radius >= best_dist) {
                continue;
            }
            rot_load(view);
            pt[0].vx = dx;
            pt[0].vy = dy;
            pt[0].vz = dz;
            transform_point(pt, pt);
            radius = MIN(box[0], box[2]);
            radius = MIN(radius, box[1]);
            if (!view_cone_contains(pt, radius)) {
                continue;
            }
            angle = atan2(dz, dx) << 20 >> 20;
            angle = ABS(angle);
            if (found && angle >= best_angle) {
                continue;
            }
            dist -= radius;
            *out = pt[1];
            found = 1;
            best_dist = dist;
            if (dist < 0) {
                best_dist = 0;
            }
            best_angle = angle;
        }
    }
    scratch_top -= 0x48;
    return found;
}

void player_update_begin(void) {
    view_cache_flags = 0;
}

void view_matrix_refresh(void) {
    void *mat = &view_matrix_buf;
    void *scratch;

    if (!(view_cache_flags & 1)) {
        view_cache_flags |= 3;
        scratch = scratch_alloc(0x20);
        rot_matrix(mat, player_angles[0] >> 12, 0, 0);
        rot_matrix(scratch, -player_tilt_x, -player_obj.rot[0], -player_tilt_z);
        mul_matrix(scratch, mat, mat);
        transpose_matrix(mat, &view_matrix_t_buf);
        scratch_top -= 0x20;
    }
}

s32 *view_matrix_get(void) {
    view_matrix_refresh();
    return &view_matrix_buf;
}

/* Copies the 5 words view_matrix_t_get points to into dst. */
s32 *view_matrix_copy(s32 *dst) {
    s32 *src = view_matrix_get();
    s32 i;
    s32 a;
    s32 b;
    s32 c;

    /* the do-while(0) wrappers are scheduling barriers (loop notes); they give the original's order */
    do {
        do {
            a = src[0];
            b = src[i = 1];
            c = src[2];
            dst[0] = a;
            dst[1] = b;
            dst[2] = c;
            a = src[3];
            b = src[4];
        } while (0);
        dst[3] = a;
        dst[4] = b;
    } while (0);
    return dst;
}

s32 *view_matrix_t_get(void) {
    view_matrix_refresh();
    return &view_matrix_t_buf;
}

/* Copies the 5 words view_matrix_t_get points to into dst. */
s32 *view_matrix_t_copy(s32 *dst) {
    s32 *src = view_matrix_t_get();
    s32 i;
    s32 a;
    s32 b;
    s32 c;

    /* the do-while(0) wrappers are scheduling barriers (loop notes); they give the original's order */
    do {
        do {
            a = src[0];
            b = src[i = 1];
            c = src[2];
            dst[0] = a;
            dst[1] = b;
            dst[2] = c;
            a = src[3];
            b = src[4];
        } while (0);
        dst[3] = a;
        dst[4] = b;
    } while (0);
    return dst;
}

void view_angles_refresh(void) {
    u16 *angles;
    u16 v;

    if (!(view_cache_flags & 4)) {
        angles = (u16 *)(scratch_top += 0x20);
        view_cache_flags |= 4;
        scratch_alloc(0x10);
        matrix_to_angles(view_matrix_get(), angles + 2, angles, angles + 4);
        v = angles[0];
        d_8012020C = v;
        scratch_top -= 0x20;
        v = angles[2];
        d_8012020E = v;
        scratch_top -= 0x10;
        v = angles[4];
        d_80120210 = v;
    }
}

s16 *view_angles_get(void) {
    view_angles_refresh();
    return &d_8012020C;
}

/* Copies the 8 bytes view_angles_get points to (unaligned) to dst; returns dst. */
void *view_angles_copy(void *dst) {
    *(Bytes8 *)dst = *(Bytes8 *)view_angles_get();
    return dst;
}

extern PlayerCoord player_y __asm__("player_xyz_y");
extern PlayerCoord player_z __asm__("player_xyz_z");
void player_position_refresh(void) {
    s32 *m;
    s32 a, b, c;
    s32 tx, ty, tz;
    VECTOR *p = (VECTOR *)&player_rel_vx;
    if (!(view_cache_flags & 8)) {
        view_cache_flags |= 8;
        m = view_matrix_get();
        a = m[0];
        b = m[1];
        c = m[2];
        __asm__ volatile("" : : : "memory");
        gte_set_ctrl(R11R12, a);
        gte_set_ctrl(R13R21, b);
        gte_set_ctrl(R22R23, c);
        a = m[3];
        b = m[4];
        __asm__ volatile("" : : : "memory");
        gte_set_ctrl(R31R32, a);
        gte_set_ctrl(R33, b);
        tx = player_xyz[0] >> 12;
        ty = player_y.v >> 12;
        tz = player_z.v >> 12;
        gte_set_ctrl(TRX, tx);
        gte_set_ctrl(TRY, ty);
        gte_set_ctrl(TRZ, tz);
        *(s32 *)p = 0;
        player_rel_vz = 0;
        player_rel_vy = -player_height / 2;
        transform_point(p, p);
    }
}

s32 *player_position(void) {
    player_position_refresh();
    return &player_rel_vx;
}

/* Copies the player's position (a VECTOR) to `out`. */
VECTOR *player_position_copy(VECTOR *out) {
    VECTOR *pos = (VECTOR *)player_position();

    *out = *pos;
    return out;
}

/* Angles of the vector from (x, y, z) to the player's position. */
void angles_to_player(s32 x, s32 y, s32 z, s32 *yaw, s32 *pitch) {
    Vec3 *pos = (Vec3 *) player_position();

    vector_to_angles(pos->x - x, pos->y - y, pos->z - z, yaw, pitch);
}

extern PlayerCoord player_y __asm__("player_xyz_y");
extern PlayerCoord player_z __asm__("player_xyz_z");
void point_to_view_angles(s32 x, s32 y, s32 z, s32 *yaw, s32 *pitch) {
    s32 *m = view_matrix_t_get();
    VECTOR *v;
    s32 a, b, c;

    a = m[0];
    b = m[1];
    c = m[2];
    __asm__ volatile("" : : : "memory");
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = m[3];
    b = m[4];
    __asm__ volatile("" : : : "memory");
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    v = (VECTOR *)scratch_top;
    v->vx = x - (player_xyz[0] >> 12);
    scratch_top += sizeof(VECTOR);
    v->vy = y - (player_y.v >> 12);
    v->vz = z - (player_z.v >> 12);
    transform_point(v, v);

    vector_to_angles(v->vx, v->vy + player_height / 2, v->vz, yaw, pitch);
    scratch_top -= sizeof(VECTOR);
}

void add_displacement(s32 dx, s32 dy, s32 dz) {
    displacement.x += dx;
    displacement.y += dy;
    displacement.z += dz;
}

void add_turn(s32 arg0) {
    pending_turn += arg0;
}

s32 cam_find_box(void) {
    return clamp_find_box((s32) cam_pos >> 0xC, (s32) cam_pos_y >> 0xC, (s32) cam_pos_z >> 0xC);
}

s32 flow_state_get(void) {
    return flow.state;
}

s16 cam_angle_get(void) {
    return d_801201AE;
}

/* Chains the fade links into a free list: link i points to i - 1, the head is the last. */
void fade_list_init(void) {
    s32 prev = -1;
    s32 i;

    for (i = 0; i < 32; i++) {
        fade_links[i] = prev;
        prev = i;
    }
    fade_head = -1;
    fade_free_head = prev;
    fade_free_count = 32;
}

/* Takes an item off the fade free list (fade_free_head) and pushes it onto the active list (fade_head,
 * the halfword after it); returns its index, or -1 when none is free. */
s32 fade_item_alloc(void) {
    u16 *heads;
    u16 *links;
    s32 item;
    u16 *link;
    u16 active;

    if (fade_free_count == 0) {
        return -1;
    }
    __asm__("" : "=r"(heads) : "0"(&fade_free_head));
    links = heads - 32;
    fade_free_count -= 1;
    item = (s16)heads[0];
    active = heads[1]; /* fade_head */
    link = (u16 *)(item * 2 + (s32)links);
    heads[0] = *link;
    *link = active;
    heads[1] = item;
    return item;
}

/* Unlinks the item that fade_links[index] points to and puts it on the free list. */
void fade_list_remove(s32 index) {
    s16 *links = fade_links;
    s16 *link;
    s32 item;
    u16 *next;

    link = &links[index];
    item = *link;
    if (item >= 0) {
        next = (u16 *)&links[item];
        *link = *next;
        fade_free_count += 1;
        *next = fade_free_head;
        fade_free_head = item;
    }
}

/* Starts a fade item at whole position pos plus the 12-bit fractions in frac. */
void fade_list_add(Vec3 *pos, u16 *frac, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    s32 i = fade_item_alloc();

    if (i >= 0) {
        FadeItem *item = &fade_items[i];
        item->x = (pos->x << 12) + (frac[0] & 0xFFF);
        item->y = (pos->y << 12) + (frac[1] & 0xFFF);
        item->z = (pos->z << 12) + (frac[2] & 0xFFF);
        item->unk_0C = a;
        item->range_start = b;
        item->range_end = c;
        item->level = 0;
        item->level_step = d;
        item->brightness = e;
        item->brightness_step = f;
    }
}

/* Advances each fade item in the list at fade_head (linked through fade_links): level grows by step and
 * pos by pos_step; an item whose level reaches 0x1000 is removed from the list. */
void fade_list_update(void) {
    s32 index;
    s32 prev;
    FadeWords *item;
    u16 level;

    index = fade_head;
    prev = 0x21;
    if (index >= 0) {
        do {
            item = (FadeWords *) &fade_items[index];
            item->pos = item->pos + item->pos_step;
            level = item->level + item->step;
            item->level = level;
            if ((s16) level >= 0x1000) {
                fade_list_remove(prev);
            } else {
                prev = index;
            }
            index = fade_links[prev];
        } while (index >= 0);
    }
}

void fade_emit_sparks(void) {
    s32 i; /* fade item index */
    FadeItem *it;
    s32 value;
    s32 level; /* brightness, 0..0x80 */
    s32 colour, hi, bright;
    s32 x, y, z, fx, fy, fz;
    s32 n;
    SparkRec *s;
    u8 *tail;
    SparkList *list;

    for (i = fade_head; i >= 0; i = fade_links[i]) {
        it = &fade_items[i];
        value = it->unk_0C;
        if (value & 0x8000) {
            s32 scale = ((it->range_end - it->range_start) * it->level) / 4096 + it->range_start;
            value = pool_spawn_scaled(value & 0x7FFF, scale, scale, scale);
        } else {
            value = ring_sample_lerp(value + it->range_start, it->range_end - it->range_start + 1, it->level, 0);
        }
        colour = it->brightness;
        bright = NOT_NEGATIVE(colour < 0x1001 ? colour : 0x1000);
        level = bright >> 5;
        hi = level;
        if (level == 0) {
            hi = 1;
        }
        colour = (hi << 16) | (level << 8) | level;
        fx = it->x & 0xFFF;
        fy = it->y & 0xFFF;
        fz = it->z & 0xFFF;
        x = it->x >> 12;
        y = it->y >> 12;
        z = it->z >> 12;
        n = spark_count;
        list = &spark_list;
        if (n < 0xFF) {
            s = &list->items[n];
            n++;
            spark_count = n;
            *(s32 *)s->colour = colour;
            tail = list->tail[colour >> 24];
            list->tail[colour >> 24] = &s->next;
            *tail = n;
            s->next = 0;
            s->x = x;
            s->y = y;
            s->z = z;
            s->unk_12 = value;
            s->yaw = fy;
            s->pitch = fx;
            s->roll = fz;
        }
    }
}
