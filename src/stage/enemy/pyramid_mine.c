/* pyramid_mine: one of the original source files (scripts/objmap.py); s10, s11. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

s32 vec_distance(VECTOR *from, VECTOR *to) {
    return SquareRoot0(length_sq((from->vx - to->vx) >> 12,
                                 (from->vy - to->vy) >> 12,
                                 (from->vz - to->vz) >> 12));
}

s32 vec_distance(VECTOR *from, VECTOR *to);

/* Passes the player's position and the object's placement position to vec_distance. */
s32 obj_placement_dist_to_player(Object *obj) {
    s32 *player = player_position();
    Placement *placement = obj->placement;
    Vec3 *offset = scratch_alloc(0x10);
    s32 dist;

    offset->x = placement->x;
    offset->y = placement->y;
    offset->z = placement->z;
    dist = vec_distance((VECTOR *)player, (VECTOR *)offset);
    scratch_top -= 0x10;
    return dist;
}

void obj_script_set_speed(Object *obj) {
    s16 *cursor = obj->script.pc;

    obj->script.pc = cursor + 1;
    obj->speed = *cursor;
}

void obj_script_read_next_state(Object *obj) {
    obj->next_state = obj_read_u16(obj);
}

void fn_800B7514(Object *obj) {
    obj->unk_242 = obj_read_u16(obj);
}

/* Steps obj's cursor over an entry (threshold, index) of its script: when the player is within
 * `threshold` of the object (distance from the object's aim point, height/2 above its position), the
 * cursor jumps to table entry `index`. */
void obj_script_branch_if_near(Object *obj) {
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

void obj_script_branch_if_far(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) obj_placement_dist_to_player(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void pyramid_mine_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

void obj_zigzag_move(Object *obj) {
    s32 out_x;
    s32 out_z;
    s32 speed;
    s32 step;

    out_x = 0;
    out_z = 0;
    obj->vars.pyramid_mine.zigzag_toggle ^= 1;
    if (obj->vars.pyramid_mine.zigzag_toggle == 0) {
        obj_turn_toward_player(obj, 0x200);
        fly_move(obj->yaw, obj->speed, &out_x, &out_z);
    } else {
        speed = (s16)rcossin_tbl[obj->vars.pyramid_mine.wave_angle & 0xFFF] * 10;
        step = speed >> 12;
        if (speed < 0) {
            step = (speed + 0xFFF) >> 12;
        }
        fly_move(obj->yaw + 0x400, step, &out_x, &out_z);
    }
    obj->vx = out_z;
    obj->vz = out_x;
}

void obj_death_effect_spawn(Object *obj);

/* While the object's timer (0x24C) is at least 0x1001, spawns an effect at its position and frees it. The timer then advances by 0xAA. */
void obj_expire_burst(Object *obj) {
    if (obj->vars.pyramid_mine.blend >= 0x1001) {
        Vec3 *pos = scratch_alloc(0x10);

        pos->x = obj->x >> 12;
        pos->y = obj->y >> 12;
        pos->z = obj->z >> 12;
        obj_death_effect_spawn(obj);
        particle_spawn_burst(pos->x, pos->y, pos->z, 0);
        spawn_effect(pos->x, pos->y - 0xC8, pos->z, 0);
        obj_free(obj);
        scratch_top -= 0x10;
    }
    obj->vars.pyramid_mine.blend = (u16)obj->vars.pyramid_mine.blend + 0xAA;
}

void pyramid_mine_update(Object *obj) {
    obj->vz = 0;
    obj->vx = 0;
    if (obj->unk_180 == -1) {
        obj->next_state = 2;
    }
    ((void (*)(Object *))obj_script_step)(obj); /* the original leaves a1 as it is */
    obj->vars.pyramid_mine.spin_yaw += 0x10;
    obj->vars.pyramid_mine.wave_angle += 0x20;
}

void pyramid_mine_draw(Object *obj, ObjHandler *handler) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot;
    SVECTOR *dir;
    s32 value;
    s32 colour;
    s32 pitch;
    s32 blend;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    rot[1] = obj->vars.pyramid_mine.spin_yaw;
    dir = scratch_alloc(8);
    if (test_bit(obj->flags, 6)) {
        s32 base = obj->type.unk_0E;

        value = base + model_slot_pchr(*(s32 *)obj->asset);
    } else {
        value = obj_keyframe_value(obj, 0);
    }
    colour = 0;
    if (obj->hit > 0) {
        FAKE_OPAQUE(colour);
        colour = 0x60C0FF;
    }
    blend = obj->vars.pyramid_mine.blend;
    if (blend != 0) {
        /* mix towards grey by blend/0x1000; the channel values reuse blend's and inv's registers */
        s32 inv = 0x1000 - blend;
        s32 green = (((blend << 11) + (inv << 12)) / 0x1000) >> 5;
        s32 total = blend + inv;

        blend = inv >> 5;  /* high channel */
        inv = total >> 5;  /* low channel */
        if ((inv | green | blend) == 0) {
            blend = 1;
        }
        colour = (blend << 16) | (green << 8) | inv;
    }
    spark_add(pos[0], pos[1], pos[2], rot[1], rot[0], rot[2], value, colour);
    pos[0] = obj->x;
    pos[1] = obj->y;
    pos[2] = obj->z;
    dir->vx = obj->width;
    dir->vy = obj->height;
    dir->vz = obj->unk_1E8[0];
    aim_marker_draw(2, dir, (Vec3 *)pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x10;
    scratch_top -= 8;
    scratch_top -= 8;
}

s32 obj_destroy(Object *obj) {
    s32 pos[3];
    s16 rot[3];
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = (s16) obj->pitch;
    rot[0] = -pitch;
    rot[1] = obj->yaw;
    rot[2] = obj->roll;
    obj->unk_17A = 0;
    obj->next_state = 3;
    particle_spawn_burst(pos[0], pos[1], pos[2], 0);
    spawn_effect(pos[0], pos[1] - 0xC8, pos[2], 0);
    obj_death_effect_spawn(obj);
    placement_list_pop((ListRecord *) obj->placement);
    ((u8 *) obj->placement)[4] = (((u8 *) obj->placement)[4] & 0xFC) | 2;
    return 0;
}

#if STAGE == 10 /* s11's copy uses its own data */
extern s16 pyramid_mine_script_pc[];
extern s16 *pyramid_mine_data[];
extern ModelSlotHead D_8011AFD0;
extern ScriptCallEntry D_8011B0F4[];
extern StateEntry D_8011B124[];
extern s16 *D_8011B0F0;
extern s16 *pyramid_mine_script_data[];
void pyramid_mine_draw(Object *obj, ObjHandler *handler);
s32 pyramid_mine_spawn(Placement *placement) {
    Object *obj;
    u8 placement_byte5;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *) &placement->unk_00[2] = 0x708;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) pyramid_mine_phase0;
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) pyramid_mine_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = pyramid_mine_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) obj_destroy;
    placement_byte5 = placement->unk_00[5];
    obj->asset = &D_8011AFD0;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = D_8011B0F4;
    obj->state_table = D_8011B124;
    obj->kind = placement_byte5;
    script_start((Script *) obj, pyramid_mine_script_pc, (s32) &pyramid_mine_data);
    obj->script.data = pyramid_mine_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_8011B0F0;
    obj_init_from_place(obj, placement, 0x27);
    obj->speed = 0;
    obj_set_part_bounds(obj, 0xB, 0x1000);
    obj->unk_180 = 0;
    obj->vars.pyramid_mine.zigzag_toggle = 0;
    obj->vars.pyramid_mine.blend = 0;
    obj->vars.pyramid_mine.wave_angle = 0;
    obj->vars.pyramid_mine.spin_yaw = (s16) (u16) obj->yaw;
    return 1;
}
#else
extern s16 moving_pyramid_mine_script_pc[];
extern s16 *moving_pyramid_mine_data[];
extern s32 D_80119DCC[3];
extern ScriptCallEntry D_80119EF0[];
extern StateEntry D_80119F20[];
extern s16 *D_80119EEC;
extern s16 *moving_pyramid_mine_script_data[];
/* Same code as pyramid_mine_spawn (s10). */
s32 pyramid_mine_spawn(Placement *placement) {
    Object *obj;
    u8 placement_byte5;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    *(s16 *) &placement->unk_00[2] = 0x708;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) pyramid_mine_phase0;
    obj->handlers[1].fn = (void (*)(Object *, ObjHandler *)) pyramid_mine_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = pyramid_mine_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) obj_destroy;
    placement_byte5 = placement->unk_00[5];
    obj->asset = D_80119DCC;
    obj->hit_cooldown_max = 0x30;
    obj->unk_1C6 = -0xC0;
    obj->call_table = D_80119EF0;
    obj->state_table = D_80119F20;
    obj->kind = placement_byte5;
    script_start((Script *) obj, moving_pyramid_mine_script_pc, (s32) &moving_pyramid_mine_data);
    obj->script.data = moving_pyramid_mine_script_data;
    obj->script.unk_0A = 0;
    obj->script.pc = D_80119EEC;
    obj_init_from_place(obj, placement, 0x27);
    obj->speed = 0;
    obj_set_part_bounds(obj, 0xB, 0x1000);
    obj->unk_180 = 0;
    obj->vars.pyramid_mine.zigzag_toggle = 0;
    obj->vars.pyramid_mine.blend = 0;
    obj->vars.pyramid_mine.wave_angle = 0;
    obj->vars.pyramid_mine.spin_yaw = (s16) (u16) obj->yaw;
    return 1;
}
#endif

/* Shared by s02, s10 and s11. The argument is an object or a FxEffect record;
   only its first three words (position) are read. */
void shoot_at_player(void *origin, s32 len) {
    s32 *from = origin;
    VECTOR *aim_pos = scratch_alloc(0x10);
    s32 dx = 0, dy = 0, dz = 0;
    s32 pitch = 0, yaw = 0;
    s16 target = 0;

    player_position_copy(aim_pos);
    dx = aim_pos->vx - from[0];
    dy = aim_pos->vy - from[1];
    dz = aim_pos->vz - from[2];
    vector_to_angles(dx, dy, dz, &yaw, &pitch);
    angles_to_vector(yaw, -pitch, len, &dx, &dy, &dz);
    aim_pos->vx = from[0] + (dx >> 12);
    aim_pos->vy = from[1] + (dy >> 12);
    aim_pos->vz = from[2] + (dz >> 12);
    set_collide_mode(1);
    if (trace_objects(origin, aim_pos, 8, aim_pos, &target) == 1) {
        hit_target_masked(target, 4, (s16)yaw, 10);
    }
    set_collide_mode(0);
    scratch_top -= 0x10;
}

#if STAGE == 10
/* Runs func_800B7B44 with the word at 0x18 (12 fraction bits dropped) while the halfword at 0x28 is below 0x999. */
void area_effect_pulse(Object *obj) {
    if (obj->script.unk_0C < 0x999) {
        shoot_at_player(obj, *(s32 *)&obj->type.unk_0C >> 12);
    }
}

extern RecTemplate area_effect_fx_main;
extern RecTemplate area_effect_fx_pulse;
/* Area effect: spawns two records at the object, marks (unk_180 = -1) every actor of its kind
 * within range unk_24C, frees itself after 0x23B steps; 24C grows by 5, 24E by 6. */
void area_effect_update(Object *obj) {
    s32 *list;
    Object *other;
    s32 *pos;

    get_obj_list_actors_tail();
    list = get_obj_list_actors();
    pos = scratch_alloc(0x10);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    if ((s16)obj->vars.area_effect.timer == 0) {
        fx_spawn_template(pos, &area_effect_fx_main, 0);
        fx_spawn_template(pos, &area_effect_fx_pulse, area_effect_pulse);
    }
    other = obj_find_by_id((Node *)list, obj->vars.area_effect.target_id);
    while (list != (s32 *)other) {
        if (other == 0) {
            break;
        }
        other = obj_find_by_id(&other->node, obj->vars.area_effect.target_id);
        if (other != 0) {
            if (obj->vars.area_effect.radius >= (s16)isqrt(length_sq((other->x - obj->x) >> 12,
                                                              ((other->y - obj->y) >> 12) - ((s16)other->height - (s16)obj->height) / 2,
                                                              (other->z - obj->z) >> 12))) {
                other->unk_180 = -1;
            }
        }
    }
    if ((s16)obj->vars.area_effect.timer >= 0x23B) {
        obj_free(obj);
    }
    scratch_top -= 0x10;
    obj->vars.area_effect.radius += 5;
    obj->vars.area_effect.timer += 6;
}

extern ModelSlotHead D_8011AFD0;
void area_effect_spawn(Object *parent, Vec3 *pos, u16 *rot) {
    Object *obj;
    s32 snd_arg;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = area_effect_update;
        obj->handlers[0].fn = 0;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->asset = &D_8011AFD0;
        obj_hit_clear(obj->index);
        obj->x = pos->x << 12;
        obj->y = pos->y << 12;
        obj->z = pos->z << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        snd_arg = parent->kind;
        obj->vars.area_effect.radius = 0;
        obj->vars.area_effect.timer = 0;
        obj->vars.snd.unk_248 = snd_arg;
    }
}

void area_effect_spawn(Object *parent, Vec3 *pos, u16 *rot);
/* Passes the object's position (whole units, y lowered by 100) and its rotation (pitch, yaw, roll) to area_effect_spawn. */
void obj_death_effect_spawn(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 pitch;
    s16 *rot = scratch_alloc(8);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    pos->y -= 0x64;
    area_effect_spawn(obj, pos, rot);
    scratch_top -= 0x10;
    scratch_top -= 8;
}
#endif

#if STAGE == 11
void shoot_at_player(void *origin, s32 len);
/* Runs shoot_at_player with the word at 0x18 (12 fraction bits dropped) while the halfword at 0x28 is below 0x999. */
void tetr_callback(Object *obj) {
    if (obj->script.unk_0C < 0x999) {
        shoot_at_player(obj, *(s32 *)&obj->type.unk_0C >> 12);
    }
}

extern s32 area_effect_fx_main;
extern s32 area_effect_fx_pulse;
void area_effect_update(Object *obj, ObjHandler *handler) {
    Object *head;
    Object *other;
    s32 *vec;

    get_obj_list_actors_tail();
    head = (Object *)get_obj_list_actors();
    vec = scratch_alloc(0x10);
    vec[0] = obj->x >> 12;
    vec[1] = obj->y >> 12;
    vec[2] = obj->z >> 12;
    if ((s16)obj->vars.area_effect.timer == 0) {
        fx_spawn_template(vec, (RecTemplate *)&area_effect_fx_main, NULL);
        fx_spawn_template(vec, (RecTemplate *)&area_effect_fx_pulse, tetr_callback);
    }
    other = obj_find_by_id(&head->node, (s16)obj->vars.area_effect.target_id);
    while (head != other) {
        if (other == NULL) {
            break;
        }
        other = obj_find_by_id(&other->node, (s16)obj->vars.area_effect.target_id);
        if (other != NULL &&
            (s16)obj->vars.area_effect.radius >=
                (s16)isqrt(length_sq((other->x - obj->x) >> 12,
                                     ((other->y - obj->y) >> 12) -
                                         (((s16)other->height - (s16)obj->height) / 2),
                                     (other->z - obj->z) >> 12))) {
            other->unk_180 = -1;
        }
    }
    if ((s16)obj->vars.area_effect.timer >= 0x23B) {
        obj_free(obj);
    }
    obj->vars.area_effect.radius = (u16)obj->vars.area_effect.radius + 5;
    obj->vars.area_effect.timer = (u16)obj->vars.area_effect.timer + 6;
    scratch_top -= 0x10;
}

extern s32 D_80119DCC[3];
void area_effect_update(Object *obj, ObjHandler *handler);
/* Spawns an object at a placement position (s32 units, 12 fractional bits) and rotation (u16 x3). */
void area_effect_spawn(Object *parent, s32 *pos, u16 *rot) {
    Object *obj;
    s32 snd_arg;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), (Node *) obj);
        obj->handlers[1].fn = area_effect_update;
        obj->handlers[0].fn = 0;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = 0;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = 0;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->callback = 0;
        obj->asset = D_80119DCC;
        obj_hit_clear(obj->index);
        obj->x = pos[0] << 12;
        obj->y = pos[1] << 12;
        obj->z = pos[2] << 12;
        obj->pitch = rot[0];
        obj->yaw = rot[1];
        obj->roll = rot[2];
        snd_arg = parent->kind;
        obj->vars.area_effect.radius = 0;
        obj->vars.area_effect.timer = 0;
        obj->vars.snd.unk_248 = snd_arg;
    }
}

void obj_death_effect_spawn(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    u16 *rot = scratch_alloc(8);
    s32 pitch;

    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    pitch = obj->pitch;
    rot[0] = -pitch;
    rot[1] = (u16)obj->yaw;
    rot[2] = (u16)obj->roll;
    pos[1] -= 0x64;
    area_effect_spawn(obj, pos, rot);
    scratch_top -= 0x10;
    scratch_top -= 8;
}
#endif
