/* time_bomb: one of s03's own original source files (scripts/objmap.py); part of src/s03/main.c's unit, included there. */

void obj_noop(void) {
}

extern s32 time_bomb_asset[3];
extern StateEntry time_bomb_params[1];
extern s16 time_bomb_script[4];
extern s32 time_bomb_data;
void time_bomb_update(Object *obj, ObjHandler *handler);
void time_bomb_phase0(Object *obj, ObjHandler *handler);
void time_bomb_draw(Object *obj, ObjHandler *handler);
s32 time_bomb_detonate(Object *obj);
/* Spawns an object from a placement: links it into the actor list, sets its four state
   handlers and asset, runs its script and sets up the placement. Returns 1, or 0 if no slot. */
s32 time_bomb_spawn(Placement *place) {
    Object *obj;
    s16 *script_pc;
    s32 script_arg;
    s16 place_byte5;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    script_arg = (s32) &time_bomb_data;
    script_pc = time_bomb_script;
    obj->handlers[0].fn = time_bomb_phase0;
    obj->handlers[1].fn = time_bomb_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = time_bomb_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) &time_bomb_detonate;
    place_byte5 = place->unk_00[5];
    obj->asset = time_bomb_asset;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = 0;
    obj->state_table = time_bomb_params;
    obj->kind = place_byte5;
    script_start((Script *) obj, script_pc, script_arg);
    obj_init_from_place(obj, place, 0x266);
    obj->speed = 0;
    obj_set_part_bounds(obj, 1, 0x400);
    obj->vars.time_bomb.unk_248 = 0;
    return 1;
}

void time_bomb_phase0(Object *obj, ObjHandler *handler) {
}

extern FxRecordParams time_bomb_burst_params;
extern RecTemplate time_bomb_burst_templates[2];
void time_bomb_update(Object *obj, ObjHandler *handler) {
    s32 phase;
    s32 *player;
    s16 *cam;
    s32 clamped, check, dx, dz, dist, near, angle;
    s32 pos[3];
    s32 *coords;
    s32 cell;

    if (obj->vars.time_bomb.unk_248 == 0) {
        phase = mission_timer_get();
        if (phase == 1) {
            player = player_position();
            cam = view_angles_get();
            dx = obj->x / 0x1000 - player[0];
            dz = obj->z / 0x1000 - player[2];
            dist = isqrt(length_sq(dx, 0, dz));
            if (dist < 0xBB8) {
                angle = atan2(dz, dx) - cam[1];
                angle &= 0xFFF;
                clamped = dist;
                if (dist > 0xBB8) {
                    clamped = 0xBB8;
                }
                check = dist;
                if (dist > 0xBB8) {
                    check = 0xBB8;
                }
                if (check < 0) {
                    clamped = 0;
                }
                dist = 0x1000 - (clamped << 12) / 0xBB8;
                near = dist * 0x576 / 0x1000 + 0x28A;
                if (0x1000 - near < angle || angle < near) {
                    time_bomb_clear_armed();
                }
            }
        }
        if (phase == 0) {
            /* Phase 0: spawn the burst at the bomb's tile (position >> 12), then free it. */
            coords = pos;
            cell = obj->x;
            cell >>= 12;
            coords[0] = cell;
            cell = obj->y;
            cell >>= 12;
            coords[1] = cell;
            cell = obj->z;
            cell >>= 12;
            coords[2] = cell;
            fx_rec34_spawn_cb(coords, &time_bomb_burst_params, 0);
            fx_spawn_template(coords, time_bomb_burst_templates, 0);
            fx_spawn_template(coords, time_bomb_burst_templates + 1, 0);
            obj_free(obj);
            return;
        }
    }
    obj_script_step(obj, handler);
}


void time_bomb_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos = scratch_alloc(0x10);
    ScratchRot *blk = scratch_alloc(0x10);
    s32 colour;
    s32 pitch;
    s32 value;

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    blk->spark_rot.vx = -pitch;
    blk->spark_rot.vy = obj->yaw;
    blk->spark_rot.vz = obj->roll;
    value = model_slot_pchr(*(s32 *)obj->asset) + 1;
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        colour = 0;
        FAKE_OPAQUE(obj);
    }
    spark_add(pos->x, pos->y, pos->z, blk->spark_rot.vy, blk->spark_rot.vx, blk->spark_rot.vz, value, colour);
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    blk->rot.vx = obj->width * 3;
    blk->rot.vy = obj->height;
    blk->rot.vz = obj->unk_1E8[0] * 3;
    aim_marker_draw(2, &blk->rot, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}


/* Wreck tumbling down: smoke puffs every 16 frames, explodes on landing or after 120 frames. */
s32 time_bomb_detonate(Object *obj) {
    s32 rx, ry, rz;
    s32 spread;

    if (obj->vars.enemy.mode == 0) {
        register s32 rise asm("$3") = -0x24000;
        obj->vy = rise;
        spread = -0xC000;
        obj->flags = 0x66;
        obj->unk_17A = 0;
        obj->scale[1] = 0x80000;
        obj->unk_1B7 = 0;
        obj->vars.enemy.mode++;
        obj->vx = rand_a_next() * 0x18 + spread;
        obj->vz = rand_a_next() * 0x18 + spread;
        spawn_effect(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000, 1);
        placement_list_pop((ListRecord *) obj->placement);
        obj->placement->unk_00[4] |= 3;
    } else {
        obj->vars.enemy.mode++;
        if ((obj->vars.enemy.mode & 0xF) == 0) {
            rx = obj->x / 0x1000 + rand_a_next() % 32 - 0x10;
            ry = obj->y / 0x1000 + rand_a_next() % 32 - 0x10;
            rz = obj->z / 0x1000 + rand_a_next() % 32 - 0x10;
            spawn_effect(rx, ry, rz, 0x80000000);
            sound_play_at(SND_PAIR(SND_TIME_BOMB_EXPLOSION | SND_GROUP(1), SND_TIME_BOMB_EXPLOSION_ALT | SND_GROUP(1)), 0x7F, 0x3C, &obj->x);
        }
        obj->yaw += rand_a_next() % 128;
        obj->pitch += rand_a_next() % 128;
        obj->roll += rand_a_next() % 128;
        if (obj->unk_1B7 != 0 || obj->vars.enemy.mode >= 0x79) {
            particle_spawn_burst(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000, 1);
            spawn_effect(obj->x / 0x1000, obj->y / 0x1000, obj->z / 0x1000, 1);
            return 0;
        }
    }
    return 1;
}

extern s32 door_pattern_base;

void door_pattern_base_set(void) {
    door_pattern_base = point_base + 0xB0;
}

void receding_wall_door_phase0(Object *obj, ObjHandler *handler);
void receding_wall_door_update(Object *obj, ObjHandler *handler);
void receding_wall_door_phase2(Object *obj, ObjHandler *handler);
void receding_wall_door_draw(Object *obj, ObjHandler *handler);
s32 receding_wall_door_spawn(Placement *placement) {
    Object *obj = obj_new();
    s32 unused[2];
    s32 roll;
    register s32 health asm("$4");

    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_b(), &obj->node);
    obj->handlers[0].fn = receding_wall_door_phase0;
    obj->handlers[1].fn = receding_wall_door_update;
    obj->handlers[2].fn = receding_wall_door_phase2;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = receding_wall_door_draw;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = ((s32) placement->x >> 12) << 12;
    obj->y = ((s32) placement->y >> 12) << 12;
    obj->z = ((s32) placement->z >> 12) << 12;
    obj->yaw = placement->y & 0xFFF;
    obj->pitch = placement->x & 0xFFF;
    roll = placement->z & 0xFFF;
    obj->placement = placement;
    obj->roll = roll;
    obj->solid_id = solid_alloc();
    health = (s16) placement->health;
    obj->vars.receding_wall_door.health = health;
    door_open_level[health] = 0x1000;
    return 1;
}

void receding_wall_door_phase0(Object *obj, ObjHandler *handler) {
}

void receding_wall_door_update(Object *obj, ObjHandler *handler) {
}

extern s32 receding_wall_base_index[2];
void receding_wall_door_phase2(Object *obj, ObjHandler *handler) {
    s16 span[2];
    s16 range[2];
    s32 pad[2];
    u16 step;
    s32 result;
    s16 *rot;
    s32 pitch;
    s32 roll;
    s32 yaw;
    u8 *block;

    step = door_open_level[obj->vars.receding_wall_door.health];
    block = obj->unk_A4;
    range[0] = step;
    if (step != 0) {
        range[1] = 0x1000 - step;
        span[0] = (u16)obj->vars.receding_wall_door.health + receding_wall_base_index[0];
        span[1] = span[0] + 0x20;
        rot = (s16 *)&obj->unk_A4[0x2C];
        pitch = obj->pitch;
        yaw = (u16)obj->yaw;
        roll = (u16)obj->roll;
        rot[0] = -pitch;
        rot[1] = yaw;
        rot[2] = roll;
        result = ((s32 (*)())solid_add)(span, range);
        block[1] = 4;
        block[0] = obj->index;
        obj_block_fill(obj, block);
        solid_setup_scratch(obj->solid_id, block, (s16)result, 0x1000);
        fn_800FB460(obj, block);
    }
}

/* Adds a spark at the door's position and rotation; its value blends two pool entries by the door's
 * eased phase (two segments: 0x60 and 0x240 of 0x2A0). */
void receding_wall_door_draw(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot;
    s32 pitch;
    s32 frame;
    s32 phase;
    s32 entry;
    s32 weight;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot = scratch_alloc(0x10);
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    frame = obj->vars.receding_wall_door.health;
    phase = (door_open_level[frame] * 0x2A0) / 4096;
    if (phase < 0x60) {
        entry = door_pattern_base + frame + 0x10;
        weight = (phase << 12) / 0x60;
    } else {
        entry = door_pattern_base + frame;
        phase -= 0x60;
        weight = (phase << 12) / 0x240;
    }
    entry = pchr_blend(entry, entry + 0x10, weight, 1);
    spark_add_head(&spark_list, pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], entry, 0);
    scratch_top -= 0x20;
}
