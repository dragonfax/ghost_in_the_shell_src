/* keyholder_fuchikoma: one of s01's own original source files (scripts/objmap.py); part of src/s01/main.c's unit, included there. */

/* The stage's model and message files: data tables point to them by address. */
const char file_arka_tp0_clt[] = "arka_tp0.clt";
const char file_arka_ch0_clt[] = "arka_ch0.clt";
const char file_arka_tp0_xs3[] = "arka_tp0.xs3";
const char file_arka_ch0_vx1[] = "arka_ch0.vx1";
const char file_arka_ch0_cb4[] = "arka_ch0.cb4";
const char file_msub_tp0_clt[] = "msub_tp0.clt";
const char file_msub_ch0_clt[] = "msub_ch0.clt";
const char file_msub_tp0_xs3[] = "msub_tp0.xs3";
const char file_msub_ch0_vx1[] = "msub_ch0.vx1";
const char file_msub_ch0_cb4[] = "msub_ch0.cb4";
const char file_mth1_tp0_clt[] = "mth1_tp0.clt";
const char file_mth1_ch0_clt[] = "mth1_ch0.clt";
const char file_mth1_tp0_xs3[] = "mth1_tp0.xs3";
const char file_mth1_ch0_vx1[] = "mth1_ch0.vx1";
const char file_mth1_ch0_cb4[] = "mth1_ch0.cb4";
const char file_ohel_tp1_clt[] = "ohel_tp1.clt";
const char file_ohel_tp0_clt[] = "ohel_tp0.clt";
const char file_ohel_ch0_clt[] = "ohel_ch0.clt";
const char file_ohel_tp1_xs3[] = "ohel_tp1.xs3";
const char file_ohel_tp0_xs3[] = "ohel_tp0.xs3";
const char file_ohel_ch0_vx1[] = "ohel_ch0.vx1";
const char file_ohel_ch0_cb4[] = "ohel_ch0.cb4";
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

/* Sets the object's aim (vars.h.unk_24C, an angle) toward a randomly jittered point of its placement. */
void obj_aim_jitter_placement(Object *obj) {
    PlacedTarget *placement = (PlacedTarget *)obj->placement;
    s32 span = 0x1770;
    s32 jitter;
    s32 target_x;
    s32 target_z;

    jitter = ((s32) (rand_a_next() * span) / 4096) - 0xBB8;
    target_x = placement->x + jitter;
    jitter = ((s32) (rand_a_next() * span) / 4096) - 0xBB8;
    target_z = placement->z + jitter;
    obj->vars.keyholder_fuchikoma.target_yaw = atan2((target_z - obj->z) >> 12, (target_x - obj->x) >> 12);
}

/* Sets obj 0x24C to the direction of the player's position seen from obj. */
void obj_aim_at_player(Object *obj) {
    s32 *player;
    s32 dx;

    player = player_position();
    dx = player[0] - (obj->x >> 12);
    obj->vars.keyholder_fuchikoma.target_yaw = atan2(player[2] - (obj->z >> 12), dx);
}

void obj_script_set_selector(Object *obj) {
    obj->vars.h.unk_25A = obj_read_u16(obj);
}

/* Script op: if the op equals obj->unk_25A, jump to the table entry given by the next word. */
void script_jump_table_match(Object *obj) {
    s16 op = obj_read_s16(obj);
    s16 target = obj_read_s16(obj);

    if (op == obj->vars.keyholder_fuchikoma.script_state) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Reads a radius and a table index from the object's script stream. When the player is more than 0x100
 * units below the object (and player_landed is 1), or the object is at least `radius` from its placement
 * target, the link's value is set to the table entry at `index`. */
void obj_script_jump_if_outside(Object *obj) {
    ObjLink *link;
    s32 index;
    s32 radius;
    s32 *pos;
    PlacedTarget *target;
    s32 dist;

    link = &obj->script;
    radius = obj_read_s16(obj);
    index = obj_read_s16(obj);
    if ((player_position()[1] < ((s32) obj->y >> 12) - 0x100 && player_landed == 1) ||
        (pos = player_position(), target = (PlacedTarget *) obj->placement,
         dist = isqrt(length_sq(pos[0] - ((s32) target->x >> 12), pos[1] - ((s32) target->y >> 12),
                                 pos[2] - ((s32) target->z >> 12))),
         dist >= radius)) {
        link->pc = ((s16 **)link->data)[index];
    }
}

void keyholder_fuchikoma_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

void obj_turn_to_aim(Object *obj) {
    obj->yaw = angle_approach(obj->yaw, obj->vars.keyholder_fuchikoma.target_yaw, 0x14);
}

void enemy_wall_avoid(Object *obj) {
    VECTOR *base;
    VECTOR *probe;
    VECTOR *hit;
    ObjHandler *handler;
    s32 limit;
    s32 speed;
    register s32 hits asm("$19");
    s32 shifted;
    s32 i;
    s32 angle;
    s32 flags;
    s32 delay;
    s32 turn;
    register s32 state asm("$3");

    limit = obj->vars.keyholder_fuchikoma.unk_248;
    if (obj->vars.keyholder_fuchikoma.unk_25E != 0) {
        limit = limit * (0x1000 - obj->vars.keyholder_fuchikoma.unk_25E) / 4096;
    }
    delay = 4;
    turn = 16;
    handler = &obj->handlers[1];
    obj->speed += obj->speed_accel;
    flags = obj->ground_flags;
    speed = MAX(CLAMP_HI(obj->speed, limit), 0);
    obj->speed = speed;
    if (flags & 0x3C) {
        state = 3;
    } else {
        state = 0;
        if (handler->timer == 0) {
            base = scratch_alloc(0x30);
            probe = base + 1;
            hit = base + 2;
            base->vx = obj->x >> 12;
            base->vy = obj->y >> 12;
            base->vz = obj->z >> 12;
            base->vy -= 105;
            hits = 0;
            angle = obj->yaw - 300;
            for (i = 0; i < 2; i++) {
                probe->vz = 400;
                probe->vx = 0;
                probe->vy = 0;
                rotate_xz_twice(angle, 0, &probe->vx, &probe->vy, &probe->vz);
                probe->vx += base->vx;
                probe->vy += base->vy;
                probe->vz += base->vz;
                shifted = hits << 1;
                if (trace_world(8, 100, base, probe, hit) != 0) {
                    hits = shifted | 1;
                } else {
                    hits = shifted;
                }
                angle += 600;
            }
            scratch_top -= 0x30;
            state = hits;
            handler->timer = delay;
        }
    }
    switch (state) {
    case 0:
        if (handler->turn_timer == 0) {
            obj_turn_to_aim(obj);
            break;
        }
        obj->yaw += obj->unk_226[0];
        break;
    case 1:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = -16;
        }
        break;
    case 2:
        if (handler->turn_timer == 0) {
            obj->unk_226[0] = turn;
        }
        break;
    case 3:
        if (handler->turn_timer == 0) {
            handler->turn_timer = 30;
        }
        obj->yaw += obj->unk_226[0];
        break;
    }
    fly_move(obj->yaw, obj->speed >> 12, &obj->vz, &obj->vx);
    if (handler->turn_timer > 0) {
        handler->turn_timer--;
    }
    if (handler->timer > 0) {
        handler->timer--;
    }
}

/* Raises the level at unk_25E while the player is within 0x320 and in front (within 0x40 of yaw), lowers it otherwise; plays sound 0x4072 while it is not full. */
void enemy_alert_update(Object *obj) {
    s32 *player;
    s32 *target;
    s32 yaw;
    s16 level;
    s16 clamped;

    player = player_position();
    if (isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12))) > 0x320) {
        if (obj->vars.keyholder_fuchikoma.unk_25E > 0) {
            obj->vars.keyholder_fuchikoma.unk_25E -= 0x400;
        }
    } else {
        target = player_position();
        yaw = atan2(target[2] - (obj->z >> 12), target[0] - (obj->x >> 12));
        if (ANG_ABS_DIFF(yaw, obj->yaw) < 0x40) {
            if (obj->vars.keyholder_fuchikoma.unk_25E < 0x1000) {
                obj->vars.keyholder_fuchikoma.unk_25E += 0x155;
            }
        } else if (obj->vars.keyholder_fuchikoma.unk_25E > 0) {
            obj->vars.keyholder_fuchikoma.unk_25E -= 0x800;
        }
    }
    level = obj->vars.keyholder_fuchikoma.unk_25E;
    clamped = NOT_NEGATIVE(MIN(level, 0x1000));
    obj->vars.keyholder_fuchikoma.unk_25E = clamped;
    enemy_wall_avoid(obj);
    if (obj->vars.keyholder_fuchikoma.unk_25E != 0x1000 && obj->script_flag == 0xF) {
        sound_play_at(SND_FOOTSTEP | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
    }
}

/* Spawns a burst from a scratch position/rotation pair offset in front of the object. */
void keyholder_fuchikoma_burst(Object *obj, s32 idx) {
    s32 *pos = scratch_alloc(0x10);
    SVECTOR *rot = scratch_alloc(8);

    s32 side = fuchikoma_burst_offsets[idx];

    rot->vx = 0;
    rot->vy = obj->yaw;
    rot->vz = 0;
    pos[1] = -0x46;
    pos[0] = side;
    pos[2] = 0x78;
    rotate_xz_twice(rot->vy, 0, pos, pos + 1, pos + 2);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    sound_play_at_units(SND_SHOT_FIRE_ALT | SND_GROUP(1), 0x40, 0x3C, pos);
    shot_spawn_obj(pos, (u16 *)rot, 3, (obj->damage << 16) | 0x38);
    scratch_top -= 0x18;
}

void keyholder_fuchikoma_sound_tick(Object *obj) {
    s32 i;
    s32 which;

    for (i = 0; i < 2; i++) {
        if (obj->vars.enemy.sound_channel[i] > 0) {
            if (--obj->vars.enemy.sound_channel[i] == 6) {
                keyholder_fuchikoma_burst(obj, i);
            }
        }
    }
    switch (obj->vars.keyholder_fuchikoma.unk_25C) {
    case -2:
        obj->vars.keyholder_fuchikoma.unk_25C = 0x50;
        obj->vars.keyholder_fuchikoma.sound_timer = 8;
        break;
    case -1:
        if (obj->vars.enemy.sound_channel[0] <= 0 && obj->vars.enemy.sound_channel[1] <= 0) {
            obj->vars.keyholder_fuchikoma.script_state = 0;
            obj->vars.keyholder_fuchikoma.unk_25C = -2;
        }
        break;
    default:
        obj->vars.keyholder_fuchikoma.sound_timer--;
        if ((obj->vars.keyholder_fuchikoma.sound_timer << 16) <= 0) {
            obj->vars.keyholder_fuchikoma.sound_timer = 8;
            which = rand_a_next() / 2048;
            if (obj->vars.enemy.sound_channel[which] <= 0) {
                obj->vars.enemy.sound_channel[which] = 0x22;
            }
        }
        break;
    }
}

void keyholder_fuchikoma_update(Object *obj, ObjHandler *handler) {
    if (obj->health > 0) {
        obj_script_step(obj, handler);
        if (obj->vars.keyholder_fuchikoma.script_state == 1) {
            keyholder_fuchikoma_sound_tick(obj);
        }
        if (obj->vars.keyholder_fuchikoma.unk_25C >= 0) {
            obj->vars.keyholder_fuchikoma.unk_25C--;
        }
    }
}

extern s16 snd_wave_offset_table[];
/* Spawns the sound-wave effect of channel `channel` at its offset from the object, faded by its timer. */
void snd_wave_effect_spawn(Object *obj, s32 channel) {
    s32 *pos = scratch_alloc(16);
    s16 *rot = scratch_alloc(8);
    s32 level;
    s32 scale;
    s32 clamped;
    s32 size;
    s32 model;
    s32 shade;
    s32 colour;
    s32 blue;

    s32 offset = snd_wave_offset_table[channel];

    rot[0] = -obj->pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    pos[1] = -0x46;
    pos[0] = offset;
    pos[2] = 0x78;
    rotate_xz_twice(rot[1], rot[0], &pos[0], &pos[1], &pos[2]);
    pos[0] = (obj->x >> 12) + pos[0];
    pos[1] = (obj->y >> 12) + pos[1];
    pos[2] = (obj->z >> 12) + pos[2];
    model = get_model_slot_base() + 0xF;
    level = obj->vars.enemy.sound_channel[channel];
    if (level >= 6) {
        level -= 6;
        clamped = MAX(MIN(level, 28), 0);
        scale = (clamped << 12) / 28;
        scale = 0x1000 - scale;
    } else {
        level = MAX(MIN(level, 6), 0);
        scale = (level << 12) / 6;
    }
    size = scale * 3000 / 4096;
    model = pool_spawn_scaled(model, size, size, size);
    shade = scale >> 5;
    blue = shade;
    if (shade == 0) {
        blue = 1;
    }
    colour = (blue << 16) | (shade << 8) | shade;
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, model, colour);
    scratch_top -= 0x18;
}

/* Update both sound channels that are playing. */
void snd_move(Object *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (obj->vars.enemy.sound_channel[i] > 0) {
            snd_wave_effect_spawn(obj, i);
        }
    }
}

/* Draws the Fuchikoma keyholder: its model (blended by the 0x25E weight), highlighted while hit. */
void keyholder_fuchikoma_draw(Object *obj) {
    Vec3 *pos = scratch_alloc(16);
    s32 model = obj_keyframe_value(obj, 0);
    s32 weight = obj->vars.keyholder_fuchikoma.unk_25E;
    s32 colour;
    s32 x, y, z;

    if (weight != 0) {
        weight = 0x1000 - weight;
        model = pchr_blend(model, model_slot_pchr(*(s32 *)obj->asset) + 0xC, weight, 0);
    }
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    } else {
        colour = 0;
    }
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    x = pos->x >> 12;
    y = pos->y >> 12;
    z = pos->z >> 12;
    spark_add(x, y, z, obj->yaw, 0, 0, model, colour);
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 16;
    snd_move(obj);
}

extern u8 keyholder_asset[];
extern s16 *keyholder_script[];
extern StateEntry D_80116F9C[];
extern ScriptCallEntry D_80116F50[];
extern s16 *D_80116F4C;
s32 keyholder_fuchikoma_spawn(Placement *place) {
    Object *obj;
    s16 **script;
    ObjHandler *h;
    s32 once;
    s32 kind;
    s32 setting;
    s32 yaw;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    once = place->unk_04[0] & 8;
    setting = 0x708;
    if (once != 0) {
        setting = -1;
    }
    place->unk_02 = setting;
    h = obj->handlers;
    obj->handlers[0].fn = (ObjHandlerFn)keyholder_fuchikoma_phase0;
    obj->handlers[1].fn = (ObjHandlerFn)keyholder_fuchikoma_update;
    obj->handlers[2].fn = (ObjHandlerFn)obj_run_states_default;
    obj->handlers[3].fn = (ObjHandlerFn)keyholder_fuchikoma_draw;
    *(volatile u8 *)&h[0].unk_11 = 0;
    *(volatile s16 *)&h[0].state = 0;
    *(volatile u8 *)&h[1].unk_11 = 0;
    *(volatile s16 *)&h[1].state = 0;
    *(volatile u8 *)&h[2].unk_11 = 0;
    *(volatile s16 *)&h[2].state = 0;
    *(volatile u8 *)&h[3].unk_11 = 0;
    *(volatile s16 *)&h[3].state = 0;
    *(volatile s32 *)&obj->callback = (s32)obj_respawn;
    kind = place->unk_04[1];
    obj->asset = keyholder_asset;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_80116F50;
    obj->state_table = D_80116F9C;
    *(volatile s16 *)&obj->unk_1C6 = 0;
    *(volatile s16 *)&obj->kind = kind;
    obj->script.data = keyholder_script;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80116F4C;
    script = keyholder_fuchikoma_data;
    script_start((Script *)obj, *script, (s32)script);
    setting = 0x27;
    if (once != 0) {
        setting = 0x227;
    }
    obj_init_from_place(obj, place, setting);
    obj_set_part_bounds(obj, 0xC, 0x1000);
    obj->vars.dmech.unused_252 = -2;
    yaw = (u16)obj->yaw;
    obj->vars.keyholder_fuchikoma.unk_248 = 0x8000;
    obj->speed_accel = 0x200;
    obj->speed = 0;
    obj->handlers[1].turn_timer = 0;
    obj->handlers[1].timer = 0;
    obj->unk_226[0] = 0x10;
    obj->vars.enemy.sound_channel[0] = 0;
    obj->vars.enemy.sound_channel[1] = 0;
    obj->vars.keyholder_fuchikoma.script_state = 0;
    obj->vars.keyholder_fuchikoma.unk_25C = -2;
    obj->vars.keyholder_fuchikoma.unk_25E = 0;
    obj->vars.keyholder_fuchikoma.target_yaw = yaw;
    return 1;
}

/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_respawn(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 kind;
    Placement *placement;
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    kind = *(s16 *)&obj->type.unk_0E;
    object_spawn_at(pos, rot, kind + model_slot_pchr(*(s32 *)obj->asset));
    placement_list_pop((ListRecord *)obj->placement);
    placement = obj->placement;
    placement->unk_00[4] = (placement->unk_00[4] & 0xFC) | 2;
    return 0;
}

/* Script op (near_radius, far_radius, index): when the player is within far_radius of the object's
 * placement and within near_radius of the object, jump to table entry `index`. */
void script_jump_if_player_in_radius(Object *obj) {
    s32 near_radius;
    s32 far_radius;
    s32 index;

    near_radius = obj_read_s16(obj);
    far_radius = obj_read_s16(obj);
    index = obj_read_s16(obj);
    if (player_dist_to_obj_point(obj, 1) <= far_radius && player_dist_to_obj_point(obj, 0) <= near_radius) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

/* Script op: jump to the target given by the operand pair when the object is within radius of a cell corner. */
void script_jump_near_corner(Object *obj) {
    s32 cx;
    s32 cy;
    s32 radius;
    s32 target;
    s16 *cursor;
    s32 dx;
    s32 dy;
    s32 inside;
    s32 px;
    s32 py;
    s32 pz;

    px = obj->x;
    py = obj->y;
    cursor = obj->script.pc;
    pz = obj->z;
    /* shifted in place: a register set twice keeps its load where it is (sched1 moves single-set loads) */
    px >>= 12;
    py >>= 12;
    pz >>= 12;
    obj->script.pc++;
    radius = cursor[0];
    obj->script.pc++;
    target = cursor[1];
    point_to_view_angles(px, py, pz, &cx, &cy);
    dx = cx;
    dy = cy;
    if (dx > 0x800) {
        dx = 0x1000 - dx;
    }
    if (dy > 0x800) {
        dy = 0x1000 - dy;
    }
    inside = dx < radius && dy < radius;
    if (inside) {
        obj->script.pc = ((s16 **)obj->script.data)[target];
    }
}

/* Script op (radius, range, near, far): when the player is within `radius`, jumps the script cursor to table
 * entry `near` if the object faces the player (yaw within `range`, pitch within 0x155), else to `far`. */
void script_jump_by_player_view(Object *obj) {
    s32 *player;
    s32 dist;
    s16 *cursor;
    s32 radius;
    s32 range;
    s32 near_index;
    s32 far_index;
    ObjLink *link;
    s32 obj_yaw;
    s32 obj_pitch;
    s32 yaw;
    s32 pitch;
    s32 facing;
    s32 to_yaw;
    s32 to_pitch;

    player = player_position();
    dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    radius = cursor[0];
    obj->script.pc = cursor + 2;
    range = cursor[1];
    obj->script.pc = cursor + 3;
    near_index = cursor[2];
    obj->script.pc = cursor + 4;
    far_index = cursor[3];
    link = &obj->script;
    if (radius < dist) {
        return;
    }
    obj_yaw = obj->yaw;
    obj_pitch = obj->pitch;
    angles_to_player(obj->x >> 12, (obj->y >> 12) - (s16) obj->height / 2, obj->z >> 12, &yaw, &pitch);
    to_yaw = yaw;
    to_pitch = pitch;
    if (ANG_ABS_DIFF(obj_yaw, to_yaw) < range && ANG_ABS_DIFF(obj_pitch, to_pitch) < 0x155) {
        facing = 1;
    } else {
        facing = 0;
    }
    if (facing) {
        link->pc = ((s16 **)link->data)[near_index];
    } else {
        link->pc = ((s16 **)link->data)[far_index];
    }
}

/* An angle (low 12 bits) limited to 0..0x200 in its first half turn, 0xEE4..0xFFF in its second. */
s16 angle_clamp_pitch(s32 angle) {
    s32 result;

    angle &= 0xFFF;
    if (angle >= 0x801) {
        result = MAX(cap_FFF(angle), 0xEE4);
    } else {
        result = NOT_NEGATIVE(cap_200(angle));
    }
    return result;
}

/* Turns a direction vector into rotation angles: out[0] from the pitch, out[1] the yaw, out[2] 0. */
void dir_to_angles_clamped(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vy = yaw;
    out->vx = -angle_clamp_pitch((s16)pitch);
    out->vz = 0;
}
