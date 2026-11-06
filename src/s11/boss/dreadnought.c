/* dreadnought: one of s11's own original source files (scripts/objmap.py); part of src/s11/main.c's unit, included there. */

extern PlacedRectState placed_rects[2];
extern s32 spark_blend_base;
extern s32 placed_rect_sound_handle;
void placed_rects_init(void) {
    s32 i;
    PlacedRectState *p;

    p = placed_rects;
    i = 0;
    spark_blend_base = point_base;
    do {
        i += 1;
        p->active = 1;
        p->unk_01 = 0;
        p->unk_02 = 0;
        p->level = 0x1000;
        p->fade_rate = 0x80;
        p += 1;
    } while (i < 2);
    placed_rect_sound_handle = 0;
}

void placed_rect_trigger(Object *obj);
void placed_rect_fade_update(Object *obj);
void placed_rect_phase2(Object *obj);
void fn_s11_800BF5C0(Object *obj);
extern s32 solid_point_base[2];
extern PlacedRectDefs obj_pair_model_table;
/* Spawns up to two child objects for a placement; health (read as signed) is the kind, 0 or 1. */
s32 obj_spawn_pair_from_placement(Placement *place) {
    Object *obj;
    s32 kind;
    s32 i;
    s32 table_off;
    s32 raw_z;

    if (get_obj_free_count() < 2) {
        return 0;
    }
    kind = *(s16 *) &place->health;
    if ((u32) kind >= 2U) {
        return 0;
    }
    i = 0;
    table_off = kind * 0x28;
    do {
        obj = obj_new();
        list_insert_after((Node *) get_obj_list_b(), (Node *) obj);
        obj->handlers[0].fn = placed_rect_trigger;
        obj->handlers[1].fn = placed_rect_fade_update;
        obj->handlers[2].fn = placed_rect_phase2;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = fn_s11_800BF5C0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->x = ((s32) place->x >> 12) << 12;
        obj->y = ((s32) place->y >> 12) << 12;
        raw_z = place->z;
        obj->vars.pair_from_placement.sub_index = i;
        i += 1;
        obj->placement = place;
        obj->vars.pair_from_placement.rect_index = kind;
        obj->z = (raw_z >> 12) << 12;
        obj_clear_block54(obj->unk_A4);
        model_part_extents_max(solid_point_base[0] + *(s16 *) ((u8 *) &obj_pair_model_table + table_off), 0x1000, &obj->unk_A4[0x34]);
        table_off += 0x14;
        obj->solid_id = solid_alloc();
        obj->unk_A4[1] = 4;
        obj->unk_A4[0] = obj->index;
    } while (i < 2);
    return 1;
}

void placed_rect_trigger(Object *obj) {
    PlacedRectState *rect;
    s16 kind;
    s32 *player;
    s32 dx;
    s32 dz;
    s32 bounds_off;
    s32 x_min;
    s32 x_max;
    s32 z_min;
    s32 z_max;

    kind = (s16)obj->vars.pair_from_placement.sub_index;
    if (kind != 1) {
        return;
    }
    rect = &placed_rects[obj->vars.pair_from_placement.rect_index];
    player = player_position();
    dx = player[0] - (obj->x >> 12);
    dz = player[2] - (obj->z >> 12);
    bounds_off = (s16)obj->vars.pair_from_placement.sub_index * 0x14 + obj->vars.pair_from_placement.rect_index * 0x28;
    x_min = -*(s16 *)((u8 *)&obj_pair_model_table.rects[0].x_min + bounds_off);
    z_max = *(s16 *)((u8 *)&obj_pair_model_table.rects[0].z_max + bounds_off);
    z_min = -*(s16 *)((u8 *)&obj_pair_model_table.rects[0].z_min + bounds_off);
    x_max = *(s16 *)((u8 *)&obj_pair_model_table.rects[0].x_max + bounds_off);
    /* The player is inside the placed rect's bounds, and the rect is active. */
    if (dz < z_max && z_min < dz && dx < x_max && x_min < dx && rect->active != 0) {
        if (rect->unk_01 != kind && placed_rect_sound_handle == 0) {
            placed_rect_sound_handle = sound_start(0xB323B324, 0x7F, 0, 0);
            sound_attach(placed_rect_sound_handle, &obj->x, NULL);
        }
        rect->unk_01 = 1;
        return;
    }
    if (rect->unk_01 != 0 && placed_rect_sound_handle == 0) {
        placed_rect_sound_handle = sound_start(0xB323B324, 0x7F, 0, 0);
        sound_attach(placed_rect_sound_handle, &obj->x, NULL);
    }
    rect->unk_01 = 0;
}

void placed_rect_fade_update(Object *obj) {
    PlacedRectState *rect;
    s32 delta;
    s16 level;

    if (obj->vars.trace.aim_yaw == 1) {
        rect = &placed_rects[obj->vars.pair_from_placement.rect_index];
        delta = rect->fade_rate;
        if (rect->active != 0 && rect->unk_01 != 0) {
            delta = -delta;
        }
        level = rect->level += delta;
        rect->level = level = MAX(MIN(level, 0x1000), 0);
        if (placed_rect_sound_handle != 0 && (level == 0x1000 || level == 0)) {
            sound_attach(sound_start(SND_PAIR(SND_PLACED_RECT_END | SND_GROUP(1), SND_PLACED_RECT_FADE_END | SND_GROUP(1)), 0x60, 0, 0), &obj->x, NULL);
            sound_stop(placed_rect_sound_handle);
            placed_rect_sound_handle = 0;
        }
    }
}

extern u8 spark_offset_table[];
/* Placed-rect handler: samples the floor under the object into its rect (cam_range_check_alt), frees the object
 * when that reports 0, otherwise adds the rect as a solid and gives the solid block its position. */
void placed_rect_phase2(Object *obj) {
    PlacedRectState *rect;
    Placement *place;
    SparkOffset *off;
    /* pts[0], pts[1] are the two point pairs for solid_add; the third row only keeps the frame size */
    s16 pts[3][4];
    s32 *block;
    s32 rect_idx;
    s16 sub_idx;
    s16 solid_id;
    s16 width;

    block = (s32 *)obj->unk_A4;
    rect_idx = obj->vars.pair_from_placement.rect_index;
    sub_idx = obj->vars.pair_from_placement.sub_index;
    rect = &placed_rects[rect_idx];
    off = (SparkOffset *)(spark_offset_table + rect_idx * 0x28 + sub_idx * 0x14);

    if (sub_idx == 1) {
        rect->unk_02 = cam_range_check_alt(obj->x >> 12, obj->y >> 12, obj->z >> 12);
    }
    if (rect->unk_02 == 0) {
        if ((s16)obj->vars.pair_from_placement.sub_index == 1) {
            place = obj->placement;
            place->unk_02 = 0;
            place->unk_04[0] = (place->unk_04[0] & 0xFC) | 2;
        }
        solid_free(obj->solid_id);
        obj_free(obj);
        return;
    }
    width = rect->level;
    if (width > 0) {
        pts[1][0] = width;
        pts[1][1] = 0x1000 - width;
        pts[0][0] = off->unk_04 + solid_point_base[0];
        pts[0][1] = off->unk_06 + solid_point_base[0];
        solid_id = ((SolidAddFn)solid_add)(pts[0], pts[1]);
        block[7] = obj->x + (off->dx << 12);
        block[8] = obj->y;
        block[9] = obj->z + (off->dz << 12);
        solid_setup_scratch(obj->solid_id, block, solid_id, 0x1000);
    }
}

extern u8 spark_offset_table[];
extern u8 spark_weight_table[];

/* Emits a plain spark (colour 0) at the object's position, offset by a table entry picked by the object's
 * 0x248 and 0x24A values. The spark's value is pchr_blend's result. */
void fn_s11_800BF5C0(Object *obj) {
    s32 idx = *(s16 *)&obj->vars;
    s32 sub = ((s16 *)&obj->vars)[1];
    s32 idx8 = idx << 3;
    SparkOffset *off = (SparkOffset *)((u8 *)(spark_offset_table + ((idx * 5) << 3)) + sub * 0x14);
    s32 x = obj->x >> 12;
    s32 y = obj->y >> 12;
    s32 z = obj->z >> 12;
    s32 weight = *(s16 *)(spark_weight_table + idx8);
    s32 value = pchr_blend(spark_blend_base + off->ay, spark_blend_base + off->ax, weight, 1);

    spark_add(x + off->dx, y, z + off->dz, 0, 0, 0, value, 0);
}

/* Reads a halfword from the object's data cursor (+0x20), advances the cursor by 2, and stores the value at +0x250. */
void obj_script_read_u16_var(Object *obj) {
    u16 *cursor = (u16 *)obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->vars.h.unk_250 = *cursor;
}

/* Same code as func_800BC7AC (s01). */
void script_set_next_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

/* Same code as func_800BC7C8 (s01). */
void func_800BF730(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void script_jump_if_player_within(Object *obj) {
    s32 *player;
    s32 dist;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 half;
    s16 *cursor;
    s32 threshold;
    s32 index;

    player = player_position();
    half = (s16) obj->height / 2;
    dx = player[0] - (obj->x >> 12);
    dy = player[1] - ((obj->y >> 12) - half);
    dz = player[2] - (obj->z >> 12);
    dist = (s16) isqrt(length_sq(dx, dy, dz));

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < dist) {
        return;
    }
    obj->script.pc = ((s16 **)obj->script.data)[index];
}

/* Reads four s16 table indices from the object's script stream and jumps
   the stream to the entry picked by the player's bearing relative to the
   object's yaw. The empty do/while loops only weight register allocation. */
void script_branch_by_bearing(Object *obj) {
    s32 *player;
    s16 *cursor;
    ObjLink *link;
    s32 front;
    s16 left, back, right, fallback;
    s32 bearing;
    s32 self_x, self_z, player_x, player_z;

    player = player_position();
    cursor = obj->script.pc;
    self_x = obj->x >> 12;
    self_z = obj->z >> 12;
    obj->script.pc++;
    front = cursor[0];
    obj->script.pc++;
    left = cursor[1];
    obj->script.pc++;
    back = cursor[2];
    obj->script.pc++;
    do {
        player_z = player[2];
        player_x = player[0];
        right = cursor[3];
    } while (0);
    fallback = front;
    link = &obj->script;
    bearing = (obj->yaw - atan2(player_z - self_z, player_x - self_x)) & 0xFFF;
    if (bearing < 0x200 && bearing > 0xE00) {
        do {
            obj->script.pc = ((s16 **)obj->script.data)[front];
        } while (0);
    } else if (bearing > 0x200 && bearing < 0x600) {
        do {
            link->pc = ((s16 **)link->data)[back];
        } while (0);
    } else if (bearing > 0x600 && bearing < 0xA00) {
        link->pc = ((s16 **)link->data)[left];
    } else if (bearing > 0xA00 && bearing < 0xE00) {
        do {
            link->pc = ((s16 **)link->data)[right];
        } while (0);
    } else {
        link->pc = ((s16 **)link->data)[fallback];
    }
}

/* Picks a new 0..5 value for obj->unk_252 from rand_a_next(), keeping it in
 * the same half (0-2 or 3-5) as the current value. Retries up to 3 times if
 * the roll matches the current value. */
void dir_state_pick_new(DirState *obj) {
    s32 roll;
    s32 tries = 0;

    do {
        roll = rand_a_next() % 6;
        if (roll < 3) {
            if (obj->unk_252 < 3) {
                roll += 3;
            }
        }
        if (roll >= 3 && obj->unk_252 >= 3) {
            roll -= 3;
        }
        tries++;
        if (roll != obj->unk_252) {
            obj->unk_252 = roll;
            return;
        }
    } while (tries < 3);
}

void script_jump_if_z_in_range(Object *obj) {
    s16 *cursor;
    s32 op;

    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    op = cursor[0];
    if ((u32) ((obj->z >> 12) + 0x125B) < 0x6A3U) {
        obj->script.pc = ((s16 **)obj->script.data)[op];
    }
}

void dreadnought_m11_request_muzzle_fx(Object *obj) {
    obj->vars.dreadnought_m11_boss.muzzle_fx_pending = 1;
}


void script_clear_salvo_timer(Object *obj) {
    obj->vars.enemy.unk_25C = 0;
}


void func_800BFA80(Object *obj) {
    obj->vars.dreadnought_m11_boss.unk_25E = 0;
}

extern s16 dreadnought_cycle;
void dreadnought_m11_reset(Object *obj) {
    *(s16 *)&obj->vars.enemy.unk_260[2] = 0;
    *(s16 *)&obj->vars.enemy.unk_260[0] = 0;
    dreadnought_cycle = 0;
}

void dreadnought_m11_randomize_flag(Object *obj) {
    obj->vars.dreadnought_m11_boss.turn_around = rand_a_next() % 2;
}

void dreadnought_m11_request_attack(Object *obj) {
    *(s16 *)&obj->vars.enemy.unk_260[4] = 1; /* 0x264 */
}

void script_branch_on_repeat(Object *obj) {
    ObjLink *link = &obj->script;
    s16 *script = link->pc;
    s32 key;
    s16 saved;
    s32 off;

    link->pc = script + 1;
    key = script[0];
    saved = key;
    link->pc = script + 2;
    off = (u16)script[1];
    if (key == ((s16 *)obj->vars.words)[0x10]) {
        ((u16 *)obj->vars.words)[0x11] += 1;
    } else {
        ((u16 *)obj->vars.words)[0x11] = 0;
    }
    if (((s16 *)obj->vars.words)[0x11] >= 2) {
        link->pc = ((s16 **)link->data)[(s16)off];
    } else {
        ((s16 *)obj->vars.words)[0x10] = saved;
    }
}

void dreadnought_m11_walk_begin(Object *obj) {
    obj->vars.enemy.walk_state = 1;
}

void dreadnought_m11_walk_end(Object *obj) {
    obj->vars.enemy.walk_state = 0;
}

void dreadnought_m11_boss_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Rotate the offset (x, y, z) by the angles in rot (yaw sign reversed) and add the result to pos. */
void pos_add_rotated_offset(Vec3 *pos, SVECTOR *rot, s32 x, s32 y, s32 z) {
    s32 dx = x;
    s32 dy = y;
    s32 dz = z;

    rotate_xz_twice(rot->vy, -rot->vx, &dx, &dy, &dz);
    pos->x += dx;
    pos->y += dy;
    pos->z += dz;
}

void dreadnought_m11_turn_toward(Object *obj, s32 angle, s32 step) {
    s32 pos[3];
    s32 target;

    if (obj->vars.dreadnought_m11_boss.turn_around != *(s16 *)&obj->vars.dreadnought_m11_boss.prev_turn_around) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_DREADNOUGHT_TURN | SND_GROUP(2), 0x60, 0x3C, pos);
    }
    target = angle + 0x800;
    if (obj->vars.dreadnought_m11_boss.turn_around == 0) {
        target = angle;
    }
    obj->vars.dreadnought_m11_boss.body_yaw = angle_approach(obj->vars.dreadnought_m11_boss.body_yaw, target, step);
    /* Empty volatile asm: stops GCC 2.7.2 hoisting the 0x254 load above the 0x24C store. */
    __asm__ __volatile__("");
    obj->vars.dreadnought_m11_boss.prev_turn_around = (u16)obj->vars.dreadnought_m11_boss.turn_around;
}

extern s16 dreadnought_m11_sound_flag;

void dreadnought_m11_clear_sound_flag(void) {
    if (dreadnought_m11_sound_flag == 1) {
        dreadnought_m11_sound_flag = 0;
    }
}

void dreadnought_m11_turn_toward(Object *obj, s32 angle, s32 unk_c);
/* Turns obj to face the player: angle from obj's position (x/z in whole units) to the player's. */
void dreadnought_m11_face_player(Object *obj) {
    s32 *player;

    player = player_position();
    dreadnought_m11_turn_toward(obj, atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)), 0x20);
    obj_turn_toward_player(obj, 0xA);
}

extern RoutePoint dreadnought_route[];
s32 dreadnought_m11_spawn_follow(Object *obj);
void dreadnought_m11_spawn_part_fx(Object *obj, s32 which);
s32 obj_spawn_follow(Object *parent);
void dreadnought_m11_fly_route(Object *obj) {
    RoutePoint pt;
    s32 dx;
    s32 dz;
    s32 *target;
    s32 flag;

    dx = 0;
    dz = 0;
    pt = dreadnought_route[(s16)obj->vars.fly.phase];
    obj->yaw = angle_approach(obj->yaw, atan2(pt.c - (obj->z >> 12), pt.a - (obj->x >> 12)), 10);
    target = player_position();
    dreadnought_m11_turn_toward(obj, atan2(target[2] - (obj->z >> 12), target[0] - (obj->x >> 12)), 0x20);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vx = dz;
    obj->vz = dx;
    dreadnought_m11_spawn_follow(obj);
    if (*(s16 *)&obj->vars.dreadnought_m11_boss.frame_toggle == 0) {
        dreadnought_m11_spawn_part_fx(obj, 0);
    } else {
        dreadnought_m11_spawn_part_fx(obj, 1);
    }
}

void dreadnought_m11_fly_route(Object *obj);
void dreadnought_m11_sound_start(Object *obj);
void dreadnought_m11_cycle_spawn(Object *obj);
/* Per-frame update. While sound channel 0 is idle it starts dreadnought_m11_sound_start once (flag unk_25E).
 * Once it plays, the u16 at unk_260 + 2 counts up while it is in 0x3B..0xB3, and the s16 at
 * unk_260 accumulates 0x100 per frame. At 0x1001 it calls dreadnought_m11_cycle_spawn, clears the accumulator
 * and advances the cycle dreadnought_cycle (0..5). */
void dreadnought_m11_cycle_update(Object *obj) {
    u16 next;

    dreadnought_m11_fly_route(obj);
    if (obj->vars.enemy.sound_channel[0] == 0) {
        if (obj->vars.dreadnought_m11_boss.unk_25E == 0) {
            dreadnought_m11_sound_start(obj);
            obj->vars.dreadnought_m11_boss.unk_25E = 1;
        }
    } else {
        if ((u32) (*(u16 *) &obj->vars.enemy.unk_260[2] - 0x3B) < 0x79U) {
            if (*(s16 *) obj->vars.enemy.unk_260 >= 0x1001) {
                next = dreadnought_cycle + 1;
                dreadnought_cycle = next;
                if ((s16) next >= 6) {
                    dreadnought_cycle = 0;
                }
                dreadnought_m11_cycle_spawn(obj);
                *(s16 *) obj->vars.enemy.unk_260 = 0;
            }
            *(s16 *) obj->vars.enemy.unk_260 = (s16) ((u16) *(s16 *) obj->vars.enemy.unk_260 + 0x100);
        }
        *(u16 *) &obj->vars.enemy.unk_260[2] = (u16) (*(u16 *) &obj->vars.enemy.unk_260[2] + 1);
    }
}

void dreadnought_m11_node_sfx(Object *obj, s32 which);
/* Turns the object toward the player (rate 0x20). Unless vars.h.unk_24A is set, it also resets
 * both of its sound channels (dreadnought_m11_node_sfx), then steps step 0xA and flies along its yaw and
 * speed, storing the two components in unk_208 and unk_210. */
void dreadnought_m11_chase_fly(Object *obj) {
    s32 dx = 0;
    s32 dz = 0;
    s32 *player;

    player = player_position();
    dreadnought_m11_turn_toward(obj, atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)), 0x20);
    if ((s16) obj->vars.dreadnought_m11_boss.frame_toggle == 0) {
        dreadnought_m11_node_sfx(obj, 0);
        dreadnought_m11_node_sfx(obj, 1);
    }
    obj_turn_toward_player(obj, 0xA);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vx = dz;
    obj->vz = dx;
}

void dreadnought_m11_fly_forward(Object *obj) {
    s32 dx;
    s32 dz;

    dx = 0;
    dz = 0;
    obj_turn_toward_player(obj, 0x20);
    fly_move(obj->yaw, obj->speed, &dx, &dz);
    obj->vx = dz;
    obj->vz = dx;
}

void dreadnought_m11_spark_trail(Object *obj);
void dreadnought_m11_aim_player(Object *obj) {
    s32 *player_pos;
    s32 px;
    s32 pz;
    s32 oz;
    s32 ox;
    s32 angle;

    if (*(s16 *)&obj->vars.enemy.unk_260[4] == 1) {
        dreadnought_m11_spark_trail(obj);
        *(s16 *)&obj->vars.enemy.unk_260[4] = 0;
    }
    player_pos = player_position();
    px = player_pos[0];
    oz = obj->z;
    pz = player_pos[2];
    ox = obj->x;
    obj->vars.enemy.sound_channel[0] = 0;
    angle = atan2(pz - (oz >> 12), px - (ox >> 12));
    dreadnought_m11_turn_toward(obj, angle, 0x20);
}

void dreadnought_m11_muzzle_fx(TrailObjPose *obj);
void dreadnought_m11_aim_player_fx(Object *obj) {
    s32 *target;
    s32 target_x;
    s32 target_z;
    s32 obj_x;
    s32 obj_z;
    s32 angle;

    if (*(s16 *)&obj->vars.dreadnought_m11_boss.muzzle_fx_pending == 1) {
        dreadnought_m11_muzzle_fx((TrailObjPose *)obj);
        *(s16 *)&obj->vars.dreadnought_m11_boss.muzzle_fx_pending = 0;
    }
    target = player_position();
    target_x = target[0];
    obj_z = obj->z;
    target_z = target[2];
    obj_x = obj->x;
    obj->vars.dreadnought_m11_boss.turn_around = 0;
    angle = atan2(target_z - (obj_z >> 12), target_x - (obj_x >> 12));
    dreadnought_m11_turn_toward(obj, angle, 0x20);
}

void dreadnought_m11_burst_fx(Object *obj);
extern long long __floatsidf(s32 x);
extern s32 __ltdf2(long long a, long long b);
/* Turns to face the player (turn flag set) and plays the one-shot sound at the object. While the counter at 0x25C is
 * above 0x1000 and below 10240.0 it runs the burst timer at 0x25A: past 0x1000 it fires a burst effect and restarts.
 * The counter grows by 0x2A every call. */
void dreadnought_m11_approach(Object *obj) {
    s32 *player;
    s32 dx, dz;
    s32 pos[3];
    long long counter, limit;

    player = player_position();
    dx = player[0] - (obj->x >> 12);
    dz = player[2] - (obj->z >> 12);
    obj->vars.dreadnought_m11_boss.turn_around = 1;
    dreadnought_m11_turn_toward(obj, atan2(dz, dx), 0x20);
    if (dreadnought_m11_sound_flag == 0) {
        pos[0] = obj->x >> 12;
        pos[1] = obj->y >> 12;
        pos[2] = obj->z >> 12;
        sound_play_at_units(SND_DREADNOUGHT_APPROACH | SND_GROUP(2), 0x60, 0x3C, pos);
        dreadnought_m11_sound_flag = 1;
    }
    if (obj->vars.dreadnought_m11_boss.unk_25C > 0x1000) {
        /* (double)unk_25C < 10240.0. The empty asm keeps the limit's load ahead of the argument move. */
        counter = __floatsidf(obj->vars.dreadnought_m11_boss.unk_25C);
        limit = 0x40C4000000000000LL;
        __asm__("" : "=r"(limit) : "0"(limit));
        if (__ltdf2(counter, limit) < 0) {
            if (obj->vars.dreadnought_m11_boss.burst_timer > 0x1000) {
                dreadnought_m11_burst_fx(obj);
                obj->vars.dreadnought_m11_boss.burst_timer = 0;
            }
            obj->vars.dreadnought_m11_boss.burst_timer += 0x80;
        }
    }
    obj->vars.dreadnought_m11_boss.unk_25C += 0x2A;
}

void func_800C02C8(Object *obj) {
    obj->vars.dreadnought_m11_boss.unk_266 += 0x10;
}

extern s16 dreadnought_m11_walk_sound_on;
extern s32 dreadnought_m11_walk_sound_handle;
void dreadnought_m11_walk_sound(Object *obj, ObjHandler *handler) {
    s32 handle;

    if (obj->vars.enemy.walk_state == 1) {
        if (dreadnought_m11_walk_sound_on == 0) {
            handle = sound_start(0x915B915C, 0x60, 0, 0);
            dreadnought_m11_walk_sound_handle = handle;
            sound_attach(handle, &obj->x, NULL);
            dreadnought_m11_walk_sound_on = 1;
        }
    } else if (dreadnought_m11_walk_sound_on == 1) {
        sound_stop(dreadnought_m11_walk_sound_handle);
        dreadnought_m11_walk_sound_handle = 0;
        dreadnought_m11_walk_sound_on = 0;
    }
}

void dreadnought_m11_boss_update(Object *obj, ObjHandler *handler) {
    s16 target_speed;
    s32 cur_speed;
    s32 step_speed;
    s32 health;

    obj->vz = 0;
    obj->vx = 0;
    obj_script_step(obj, handler);
    if (obj->vars.dreadnought_m11_boss.speed_step_timer >= 0x1001) {
        target_speed = obj->vars.dreadnought_m11_boss.target_speed;
        if (target_speed == obj->speed) {
            obj->speed = obj->speed;
        } else {
            cur_speed = obj->speed;
            if (cur_speed < target_speed) {
                step_speed = cur_speed + 1;
            } else {
                step_speed = cur_speed - 1;
            }
            obj->speed = step_speed;
        }
        obj->vars.dreadnought_m11_boss.speed_step_timer = 0;
    }
    health = obj->health;
    obj->vars.dreadnought_m11_boss.frame_toggle ^= 1;
    obj->vars.dreadnought_m11_boss.speed_step_timer += 0x200;
    if (health < 0) {
        health = 0;
    }
    meter_set(health + 0x1388, obj->vars.dreadnought_m11_boss.max_health + 0x1388);
    dreadnought_m11_walk_sound(obj, handler);
}


/* Rotates the vector v by the pose record table[index] (position and angles), in place. */
void pose_transform_vec(u8 *table, s32 index, SVECTOR *v) {
    s32 offset = index * 12;
    PosRot12 *rec;
    u8 *mat;
    SVECTOR ang;
    Vec3 pos;
    s32 mx, my, mz;

    offset += 4;
    rec = (PosRot12 *)(table + offset);
    pos.x = rec->x;
    pos.y = rec->y;
    pos.z = rec->z;
    mat = scratch_alloc(0x20);
    TransMatrix(mat, &pos);
    ang.vx = rec->ax;
    ang.vy = rec->ay;
    ang.vz = rec->az;
    rot_matrix(mat, ang.vy, ang.vx, ang.vz);
    SetRotMatrix(mat);
    SetTransMatrix(mat);
    gte_load(VXY0, v, 0);
    gte_load(VZ0, v, 4);
    gte_rtv0tr();
    gte_get(MAC1, mx);
    gte_get(MAC2, my);
    gte_get(MAC3, mz);
    scratch_top -= 0x20;
    v->vx = mx;
    v->vy = my;
    v->vz = mz;
}


extern Rec8013C970 seq_slots[];
void dreadnought_m11_boss_draw(Object *obj, ObjHandler *handler) {
    Vec3 pos;
    SVECTOR rot;
    SVECTOR aim;
    SVECTOR rot2;
    s32 pitch;
    s32 value;
    s32 colour;
    s32 *seq;
    s32 base;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    if (test_bit(obj->flags, 6)) {
        base = obj->type.unk_0E;
        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    pchr_lists_build(value);
    value = pchr_copy_slot(value);
    seq = pchr_poses_build(value);
    seq_slots[value & 0x7FF].first = seq;
    rot2.vx = 0;
    rot2.vy = 0;
    rot2.vz = 0;
    {
        SVECTOR rot3;
        rot3.vx = 0;
        rot3.vy = obj->vars.dreadnought_m11_boss.body_yaw - obj->yaw;
        rot3.vz = 0;
        pose_rotate_range(seq, 2, 1, &rot2, &rot3);
        pose_rotate_range(seq, 3, 1, &rot2, &rot3);
        pose_rotate_range(seq, 4, 1, &rot2, &rot3);
        pose_rotate_range(seq, 5, 1, &rot2, &rot3);
        pose_rotate_range(seq, 6, 1, &rot2, &rot3);
        pose_rotate_range(seq, 0xE, 1, &rot2, &rot3);
        pose_rotate_range(seq, 0xF, 1, &rot2, &rot3);
        pose_rotate_range(seq, 0x10, 1, &rot2, &rot3);
        pose_rotate_range(seq, 0x11, 1, &rot2, &rot3);
    }
    spark_add(pos.x, pos.y, pos.z, rot.vy, rot.vx, rot.vz, value, colour);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    aim.vx = obj->width;
    aim.vy = obj->height;
    aim.vz = obj->unk_1E8[0];
    aim_marker_draw(2, &aim, &pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
}

void dreadnought_m11_health_record(Object *obj);
s32 dreadnought_m11_death(Object *obj) {
    s32 pos[3];
    struct {
        s16 vx;
        s16 vy;
        s16 vz;
    } rot;
    s32 off[3];
    s32 base;
    s32 r2, r3;
    s32 pitch;
    s32 adj;
    s32 rise;

    off[0] = rand_a_next() % 0x200;
    off[1] = rand_a_next() % 0x100;
    r2 = rand_a_next();
    adj = r2;
    if (r2 < 0) {
        adj = r2 + 0x1FF;
    }
    obj->next_state = 0xB;
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = (u16)obj->yaw;
    rot.vz = (u16)obj->roll;
    off[2] = r2 - ((adj >> 9) << 9);
    obj->unk_17A = 0;
    if (dreadnought_m11_walk_sound_on == 1) {
        sound_stop(dreadnought_m11_walk_sound_handle);
        dreadnought_m11_walk_sound_handle = 0;
        dreadnought_m11_walk_sound_on = 0;
    }
    vec3_rotate(rot.vy, rot.vx, rot.vz, &off[0], &off[1], &off[2]);
    if (obj->vars.dreadnought_m11_boss.unk_266 == 0) {
        spawn_effect(pos[0] + off[0], pos[1] - off[1], pos[2] + off[2], 0x80007F01);
        spawn_effect(pos[0] - off[0], pos[1] - off[1], pos[2] - off[2], 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x200, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x300, pos[2], 0x80000000);
        spawn_effect(pos[0], pos[1] - 0x380, pos[2], 0x80007F02);
        set_mission_active(0);
    }
    rise = 0x200;
    r3 = rand_a_next();
    if (r3 == (r3 / 5) * 5) {
        if ((s16)obj->vars.dreadnought_m11_boss.frame_toggle == 0) {
            spawn_effect(pos[0] + off[0], pos[1] - (off[1] + rise), pos[2] + off[2], 0x80007F00);
            spawn_effect(pos[0] - off[0], pos[1] - (off[1] + rise), pos[2] - off[2], 0x80000001);
        } else {
            spawn_effect(pos[0] - off[0], pos[1] - (off[1] + rise), pos[2] - off[2], 0x80000000);
            spawn_effect(pos[0] + off[0], pos[1] - (off[1] + rise), pos[2] + off[2], 0x80007F01);
        }
    }
    if (obj->vars.dreadnought_m11_boss.unk_266 > 0x1000) {
        spawn_effect(pos[0] + off[0], pos[1] - 0x200, pos[2] + off[2], 0x80007F01);
        spawn_effect(pos[0] - off[0], pos[1] - 0x300, pos[2] - off[2], 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x400, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x500, pos[2], 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x600, pos[2], 0x80007F00);
        spawn_effect(pos[0], pos[1] - 0x700, pos[2], 0x80000001);
        spawn_effect(pos[0], pos[1] - 0x800, pos[2], 0x80007F02);
        base = obj->type.unk_0E;
        object_spawn_at(pos, &rot, base + model_slot_pchr(*(s32 *)obj->asset));
        dreadnought_m11_health_record(obj);
        obj_free(obj);
        set_mission_active(1);
        return 0;
    }
    return 1;
}

char str_arkb_tp0_clt[16] = "arkb_tp0.clt";

char str_arkb_ch0_clt[16] = "arkb_ch0.clt";

char str_arkb_tp0_xs3[16] = "arkb_tp0.xs3";

char str_arkb_ch0_vx1[16] = "arkb_ch0.vx1";

char str_arkb_ch0cb4[16] = "arkb_ch0.cb4";

char str_hou2_tp0_clt[16] = "hou2_tp0.clt";

char str_hou2_ch0_clt[16] = "hou2_ch0.clt";

char str_hou2_tp0_xs3[16] = "hou2_tp0.xs3";

char str_hou2_ch0_vx1[16] = "hou2_ch0.vx1";

char str_hou2_ch0cb4[16] = "hou2_ch0.cb4";

char str_tnk1_tp0_clt[16] = "TNK1_tp0.clt";

char str_tnk1_ch0_clt[16] = "TNK1_ch0.clt";

char str_tnk1_ch0_vx1[16] = "TNK1_ch0.vx1";

char str_tnk1_tp0_xs3[16] = "TNK1_tp0.xs3";

char str_tnk1_ch0cb4[16] = "TNK1_ch0.cb4";

char str_jira_tp0_clt[16] = "jira_tp0.clt";

char str_jira_ch0_clt[16] = "jira_ch0.clt";

char str_jira_tp0_xs3[16] = "jira_tp0.xs3";

char str_jira_ch0_vx1[16] = "jira_ch0.vx1";

char str_jira_ch0cb4[16] = "jira_ch0.cb4";

char str_dorb_ch0cb4[16] = "dorb_ch0.cb4";

char str_bosb_tp1_clt[16] = "bosb_tp1.clt";

char str_bosb_tp0_clt[16] = "bosb_tp0.clt";

char str_bosb_ch0_clt[16] = "bosb_ch0.clt";

char str_bosb_tp1_xs3[16] = "bosb_tp1.xs3";

char str_bosb_tp0_xs3[16] = "bosb_tp0.xs3";

char str_bosb_ch1_vx1[16] = "bosb_ch1.vx1";

char str_bosb_ch0_vx1[16] = "bosb_ch0.vx1";

char str_bosb_ch1cb4[16] = "bosb_ch1.cb4";

char str_bosb_ch0cb4[16] = "bosb_ch0.cb4";

extern s16 dreadnought_m11_boss_script[];
extern u8 D_8011A6EC[];
extern ScriptCallEntry D_8011AD58[];
extern StateEntry D_8011ADE0[];
extern s16 *dreadnought_m11_script_data[];
extern s16 *D_8011AD54;
extern s16 *dreadnought_m11_boss_data[];
extern s32 giant_robot_on_flag;
extern s16 dreadnought_m11_sfx_count;
s32 dreadnought_m11_death(Object *obj);
void dreadnought_m11_boss_phase0(Object *obj, ObjHandler *handler);
void dreadnought_m11_boss_update(Object *obj, ObjHandler *handler);
void dreadnought_m11_boss_draw(Object *obj, ObjHandler *handler);
s32 dreadnought_m11_boss_spawn(Placement *place) {
    Object *obj;
    u8 place_byte5;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    obj->handlers[0].fn = (ObjHandlerFn) dreadnought_m11_boss_phase0;
    obj->handlers[1].fn = dreadnought_m11_boss_update;
    obj->handlers[2].fn = obj_state_run;
    obj->handlers[3].fn = dreadnought_m11_boss_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) &dreadnought_m11_death;
    place_byte5 = place->unk_00[5];
    obj->asset = &D_8011A6EC;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = D_8011AD58;
    obj->unk_1C6 = 0;
    obj->state_table = D_8011ADE0;
    obj->kind = place_byte5;
    script_start((Script *) obj, dreadnought_m11_boss_script, (s32) &dreadnought_m11_boss_data);
    obj->script.data = &dreadnought_m11_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_8011AD54;
    obj_init_from_place(obj, place, 0x27);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0x1400);
    obj->y = -0x1E0000;
    obj->z = -0x1450000;
    obj->vars.dreadnought_m11_boss.frame_toggle = 0;
    obj->vars.dreadnought_m11_boss.speed_step_timer = 0;
    obj->vars.dreadnought_m11_boss.target_speed = 0;
    obj->vars.dreadnought_m11_boss.unused_252 = 0;
    obj->vars.dreadnought_m11_boss.turn_around = 0;
    obj->vars.dreadnought_m11_boss.prev_turn_around = 0;
    obj->vars.dreadnought_m11_boss.muzzle_fx_pending = 1;
    obj->vars.dreadnought_m11_boss.burst_timer = 0;
    obj->vars.dreadnought_m11_boss.unk_25C = 0;
    obj->vars.dreadnought_m11_boss.unk_25E = 0;
    *(s16 *) &obj->vars.enemy.unk_260[0] = 0;
    *(s16 *) &obj->vars.enemy.unk_260[2] = 0;
    *(s16 *) &obj->vars.enemy.unk_260[4] = 1;
    obj->vars.dreadnought_m11_boss.unk_266 = 0;
    *(s16 *) &obj->vars.dreadnought_m11_boss.unk_268 = 0;
    obj->vars.enemy.target_yaw = 0;
    obj->vars.enemy.walk_state = 0;
    obj->vars.dreadnought_m11_boss.max_health = obj->health;
    obj->vars.dreadnought_m11_boss.body_yaw = obj->yaw;
    obj_hit_flag_set(obj->index, 0x80);
    dreadnought_cycle = 0;
    dreadnought_m11_sound_flag = 0;
    giant_robot_on_flag = 0;
    dreadnought_m11_walk_sound_on = 0;
    dreadnought_m11_walk_sound_handle = 0;
    dreadnought_m11_sfx_count = 0;
    meter_set(obj->health, obj->vars.dreadnought_m11_boss.max_health);
    meter_set_mode(1);
    show_line((s32) "#1Warning!  Warning! Target confirmed onthe other side.\xA1");
    return 1;
}

extern s16 dreadnought_m11_sfx_count;
void dreadnought_m11_node_sfx(Object *obj, s32 which) {
    Vec3 pos;
    SVECTOR rot;
    s32 p;

    solid_part_box(obj->solid_id, which, &pos.x, 0);
    p = obj->pitch;
    rot.vx = -p;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    if (which == 0 || which == 7) {
        pos_add_rotated_offset(&pos, &rot, -0x64, 0, -0xC8);
    } else {
        pos_add_rotated_offset(&pos, &rot, 0x64, 0, -0xC8);
    }
    if ((u32)(((s32)obj->z >> 12) + 0x125C) >= 0x6A5U) {
        sound_effect_spawn(&pos, model_slot_pchr(*(s32 *)obj->asset) + 0xF7);
        dreadnought_m11_sfx_count += 1;
    }
    if (dreadnought_m11_sfx_count >= 9) {
        sound_play_at_units(SND_DREADNOUGHT_NODE_SPARK | SND_GROUP(1), 0x60, 0x3C, &pos);
        dreadnought_m11_sfx_count = 0;
    }
}

s32 dreadnought_m11_spawn_follow(Object *obj) {
    return obj_spawn_follow(obj);
}

s32 obj_spawn_at_point(s32 *pos, u16 *rot, s32 dist);
void dreadnought_m11_spawn_part_fx(Object *obj, s32 which) {
    Vec3 pos;
    SVECTOR rot;

    if (solid_part_box(obj->solid_id, which, &pos.x, 0) != 0) {
        rot.vx = obj->pitch;
        rot.vy = obj->yaw;
        rot.vz = obj->roll;
        pos_add_rotated_offset(&pos, &rot, 0, 0x32, -0xC8);
        if ((u32)(((s32)obj->z >> 12) + 0x125C) >= 0x6A5U) {
            obj_spawn_at_point((s32 *)&pos, (u16 *)&rot, model_slot_pchr(*(s32 *)obj->asset) + 0xC8);
        }
    }
}

void spark_emit_spawn(TrailObjPose *obj, Vec3 *pos, SVECTOR *rot);
void dreadnought_m11_muzzle_fx(TrailObjPose *obj) {
    Vec3 pos;
    SVECTOR rot;
    Vec3 *posp = &pos;
    SVECTOR *rotp = &rot;
    s32 pitch;

    posp->x = obj->x >> 12;
    posp->y = obj->y >> 12;
    posp->z = obj->z >> 12;
    pitch = obj->pitch;
    rotp->vx = -pitch;
    rotp->vy = obj->unk_220;  /* overwritten below; the original keeps this load */
    rotp->vz = obj->unk_224;
    rotp->vy = obj->yaw;
    pos_add_rotated_offset(posp, rotp, 0x118, -0x190, 0x1D6);
    spark_emit_spawn(obj, posp, rotp);
    sound_play_at_units(SND_DREADNOUGHT_MUZZLE_FIRE | SND_GROUP(1), 0x60, 0x3C, posp);
}

void burst_obj_spawn(s32 kind, Vec3 *pos, SVECTOR *rot);
void dreadnought_m11_side_fx(Object *obj, s32 flag);
void dreadnought_m11_burst_fx(Object *obj) {
    Vec3 posv;
    SVECTOR rotv;
    Vec3 *pos = &posv;
    SVECTOR *rot = &rotv;
    s32 tilt;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    tilt = -obj->pitch;
    rot->vx = tilt;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    rot->vy = obj->vars.dreadnought_m11_boss.body_yaw;
    rot->vx = tilt - 0x70;
    pos_add_rotated_offset(pos, rot, 0, -0x1A4, -0x82);
    rot->vy += 0x800;
    burst_obj_spawn(model_slot_pchr(*(s32 *)obj->asset), pos, rot);
    dreadnought_m11_side_fx(obj, 0);
    dreadnought_m11_side_fx(obj, 1);
    sound_play_at_units(SND_PAIR(SND_DREADNOUGHT_BURST_EXPLOSION | SND_GROUP(1), SND_DREADNOUGHT_BURST_EXPLOSION_ALT | SND_GROUP(1)), 0x60, 0x3C, pos);
}

extern s32 obj_spawn_ramp(s32 arg, s32 *pos, u16 *rot);
void dreadnought_m11_side_fx(Object *obj, s32 flag) {
    Vec3 pos;
    SVECTOR rot;
    Vec3 *origin;
    s32 spawn_id;
    s32 pitch;

    spawn_id = model_slot_pchr(*(s32 *)obj->asset);
    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    rot.vx -= 0x70;
    origin = &pos;
    if (flag == 0) {
        rot.vy = obj->vars.part.parent_yaw - 0x118;
        pos_add_rotated_offset(origin, &rot, 0, -0x1A4, -0x82);
        spawn_id += 0xCC;
    } else {
        rot.vy = obj->vars.part.parent_yaw + 0x118;
        pos_add_rotated_offset(origin, &rot, 0, -0x1A4, -0x82);
        spawn_id += 0xCD;
    }
    obj_spawn_ramp(spawn_id, (s32 *)&pos, (u16 *)&rot);
}

void obj_spawn_sound_loop(s32 extra, s32 *pos, u16 *angles);
/* Starts the object's sound loop at the origin, turned like the object but with its parent's yaw. */
void dreadnought_m11_sound_start(Object *obj) {
    s32 pos[4] = {0, 0, 0, 0};
    SVECTOR rot;
    s32 pitch;

    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    rot.vy = obj->vars.part.parent_yaw;
    obj_spawn_sound_loop((s32)obj, pos, (u16 *)&rot);
}

void obj_spawn_typed(s32 kind, s32 *pos, u16 *angles);
void dreadnought_m11_cycle_spawn(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    Vec3 *pos_ptr;
    SVECTOR *rot_ptr;
    s32 phase;
    s32 span_x;
    s32 span_y;
    s32 span_z;
    s32 pitch;

    span_x = 0xFA;
    span_z = 0xC8;
    phase = dreadnought_cycle;
    if (phase >= 3) {
        s32 step = phase - 3;
        span_y = (step * 0x32) - 0x190;
        span_x = (step * 0xF) - 0x113;
    } else {
        span_y = (phase * 0x32) - 0x190;
        span_x -= (phase - 3) * 0xF;
    }

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pos_ptr = &pos;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    rot_ptr = &rot;
    rot.vy = obj->vars.dreadnought_m11_boss.body_yaw + 0x800;

    pos_add_rotated_offset(pos_ptr, rot_ptr, span_x, span_y, span_z);
    sound_play_at_units(SND_TWIN_SHOT_FIRE | SND_GROUP(1), 0x60, 0x3C, pos_ptr);
    obj_spawn_typed(model_slot_pchr(*(s32 *)obj->asset) + 0xE6, (s32 *)pos_ptr, (u16 *)rot_ptr);
}

void spark_trail_spawn(Object *obj, Vec3 *pos, SVECTOR *rot);
void dreadnought_m11_spark_trail(Object *obj) {
    Vec3 pos_v;
    Vec3 *pos = &pos_v;
    SVECTOR rot;
    s32 pitch;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;      /* overwritten below: the original stores it twice */
    rot.vz = obj->roll;
    rot.vy = obj->vars.dreadnought_m11_boss.body_yaw;
    pos_add_rotated_offset(pos, &rot, -0x12C, -0x15E, 0x190);
    spark_trail_spawn(obj, pos, &rot);
}

s32 damage_record_spawn(DamageRecord *rec);
void dreadnought_m11_health_record(Object *obj) {
    DamageRecord rec;
    Vec3 pos;
    SVECTOR rot;
    s32 pitch;
    u16 amt;
    s32 avx, avy, avz;

    pos.x = obj->x >> 12;
    pos.y = obj->y >> 12;
    pos.z = obj->z >> 12;
    pitch = obj->pitch;
    rot.vx = -pitch;
    rot.vy = obj->yaw;
    rot.vz = obj->roll;
    rot.vy = obj->vars.dreadnought_m11_boss.body_yaw;
    pos_add_rotated_offset(&pos, &rot, 0, -0x190, 0);
    rec.kind = 4;
    rec.sub = 5;
    rec.unk_1A = 0;
    rec.unk_1E = 0;
    rec.x = (pos.x << 12) + (rec.x & 0xFFF);
    rec.y = (pos.y << 12) + (rec.y & 0xFFF);
    rec.z = (pos.z << 12) + (rec.z & 0xFFF);
    avx = rot.vx;
    rec.x = ((rec.x >> 12) << 12) + (avx & 0xFFF);
    avy = rot.vy;
    rec.y = ((rec.y >> 12) << 12) + (avy & 0xFFF);
    avz = rot.vz;
    rec.z = ((rec.z >> 12) << 12) + (avz & 0xFFF);
    amt = obj->vars.dreadnought_m11_boss.max_health;
    rec.code = 0x6590;
    rec.zero[0] = 0;
    rec.zero[1] = 0;
    rec.zero[2] = 0;
    rec.zero[3] = 0;
    amt += 0x1388;
    rec.amount = amt;
    damage_record_spawn(&rec);
}

extern s32 giant_robot_on_flag;


/* Sets the flag at giant_robot_on_flag. */
void flag_set(void) {
    giant_robot_on_flag = 1;
}


extern s32 giant_robot_on_flag;

s32 flag_get(void) {
    return giant_robot_on_flag;
}
