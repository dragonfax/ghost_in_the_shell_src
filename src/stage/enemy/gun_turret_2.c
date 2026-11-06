/* gun_turret_2: one of the original source files (scripts/objmap.py); s02, s03, s07, s10, s11. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Puts a point 60 units above and 160 ahead of the object, turned by its yaw, into `index`'s slot (sound_set_pos). */
s32 obj_sound_track_ahead(Object *obj, s32 index) {
    Vec3 *offset = scratch_alloc(0x10);

    offset->x = 0;
    offset->y = -0x3C;
    offset->z = 0xA0;
    rotate_xz_twice((s16)obj->vars.h.unk_24A, 0, &offset->x, &offset->y, &offset->z);
    offset->x = obj->x + (offset->x << 12);
    offset->y = obj->y + ((offset->y - 0x32) << 12);
    offset->z = obj->z + (offset->z << 12);
    sound_set_pos(index, offset);
    scratch_top -= 0x10;
    return 0;
}

static inline s32 wrap_angle(s32 angle) {
    s32 wrapped = angle & 0xFFF;
    if (wrapped > 0x800) {
        wrapped -= 0x1000;
    }
    return wrapped;
}
static inline s32 yaw_off_neg(s32 a, s32 b) {
    do {
        a &= 0xFFF;
        if (a > 0x800) {
            a -= 0x1000;
        }
    } while (0);
    b &= 0xFFF;
    if (b > 0x800) {
        b -= 0x1000;
    }
    return -wrap_angle(a - b);
}
static inline s32 turret_aimed(s32 yaw, s32 aim_yaw, s32 aim_pitch, s32 tolerance) {
    if ((wrap_angle(wrap_angle(yaw) - wrap_angle(aim_yaw)) >= 0
             ? wrap_angle(wrap_angle(yaw) - wrap_angle(aim_yaw))
             : yaw_off_neg(yaw, aim_yaw)) < tolerance) {
        if (ABS(wrap_angle(-wrap_angle(aim_pitch))) < 0x200) {
            return 1;
        }
    }
    return 0;
}
static inline s32 script_next_s16(ObjLink *link) {
    s16 *pc = link->pc;
    link->pc = pc + 1;
    return *pc;
}
/* script op: jump to target idx when the turret faces the player (within the
 * script's yaw tolerance; 0x400 for variant 2) at about the player's height */
void turret_branch_if_aimed(Object *obj) {
    ObjLink *link;
    s32 tolerance;
    s32 target, yaw, height, *player, dy;
    s32 aimed;
    s32 aim[2];

    link = &obj->script;
    tolerance = script_next_s16(link);
    target = script_next_s16(link);
    player = player_position();
    height = obj->y >> 12;
    dy = player[1] - height;
    if (dy < 0) {
        dy = -dy;
    }
    if (dy > 0x200) {
        return;
    }
    switch ((s16)obj->vars.turret.variant) {
    case 0:
    case 1:
        yaw = (s16)obj->vars.turret.yaw;
        angles_to_player(obj->x >> 12, height - (s16)obj->height / 2, obj->z >> 12, &aim[0], &aim[1]);
        aimed = turret_aimed(yaw, aim[0], aim[1], tolerance);
        break;
    case 2:
        yaw = (s16)obj->vars.turret.yaw;
        angles_to_player(obj->x >> 12, height - (s16)obj->height / 2, obj->z >> 12, &aim[0], &aim[1]);
        tolerance = 0x400;
        aimed = turret_aimed(yaw, aim[0], aim[1], tolerance);
        break;
    default:
        return;
    }
    if (aimed) {
        /* the do/while doubles link's register priority, as in the original */
        do {
            link->pc = ((s16 **)link->data)[target];
        } while (0);
    }
}

void fn_s02_800BBD64(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Turns the object's 0x24A angle toward the player by at most step. */
void obj_angle_toward_player(Object *obj, s32 step) {
    s32 *player = player_position();
    s32 angle = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));

    obj->vars.h.unk_24A = angle_approach((s16) obj->vars.h.unk_24A, angle, step);
}

void obj_angle_toward_player(Object *obj, s32 step);

/* Runs script_jump_if_wanted_matches with 16 while the halfword at 0x252 is below 2. */
void turret_track_player(Object *obj) {
    if ((s16)obj->vars.h.unk_252 < 2) {
        obj_angle_toward_player(obj, 0x10);
    }
}

/* Builds a position (object x/y/z, shifted to world units, plus a fixed offset) and a yaw-rotated
 * base in $gp scratch, then hands both to shot_spawn_obj. */
void obj_emit_forward_effect(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    u16 *rot = scratch_alloc(8);
    s32 y_term;
    s32 y_base;

    pos[0] = 0;
    pos[1] = -0x3C;
    pos[2] = 0xA0;
    rot[0] = 0;
    rot[1] = obj->vars.h.unk_24A;
    rot[2] = 0;
    rotate_xz_twice((s16)rot[1], 0, pos, pos + 1, pos + 2);
    pos[0] = (obj->x >> 12) + pos[0];
    y_term = obj->y >> 12;
    y_base = pos[1] - 0x32;
    pos[1] = y_term + y_base;
    pos[2] = (obj->z >> 12) + pos[2];
    shot_spawn_obj(pos, rot, 1, (obj->damage << 16) | 1);
    scratch_top -= 0x18;
}

void obj_turn_to_player_step(Object *obj, ObjHandler *handler) {
    s32 *player;
    s32 handle;
    s32 yaw;
    s32 aim;
    s32 dir;
    s32 step;
    s32 result;

    result = handler->result;
    switch (result) {
    case -2:
        handle = obj->vars.words[3];
        if (handle == 0) {
            handle = sound_start(SND_LIGHT_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
            obj->vars.words[3] = handle;
            sound_attach(handle, obj, (void (*)())obj_sound_track_ahead);
        }
        handler->queued_entry = -1;
        handler->result = 0x78;
        player = player_position();
        aim = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));
        yaw = (s16)obj->vars.trace.aim_yaw;
        yaw &= 0xFFF;
        if (yaw >= 0x801) {
            yaw -= 0x1000;
        }
        aim &= 0xFFF;
        if (aim >= 0x801) {
            aim -= 0x1000;
        }
        dir = (yaw - aim) & 0xFFF;
        if (dir >= 0x801) {
            dir -= 0x1000;
        }
        step = -1;
        if (dir >= 0) {
            step = 1;
        }
        obj->unk_226[0] = -(step * 8);
        break;
    case -1:
        if (obj->vars.words[3] != 0) {
            sound_stop(obj->vars.words[3]);
            obj->vars.words[3] = 0;
        }
        obj_request_state(obj, handler, 0, 0);
        break;
    default:
        obj->vars.h.unk_24A += obj->unk_226[0];
        if (result == (result / 6) * 6) {
            obj_emit_forward_effect(obj);
        }
        break;
    }
}

void obj_face_player_step(Object *obj, ObjHandler *handler) {
    s32 result;
    s32 *player;
    s32 handle;

    result = handler->result;
    player = player_position();
    obj->vars.trace.aim_yaw = angle_approach(obj->vars.trace.aim_yaw,
                                         atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12)),
                                         0x10);
    switch (result) {
    case -2:
        /* words[3] holds the handle of the looping sound (0x254) */
        if (obj->vars.words[3] == 0) {
            handle = sound_start(SND_LIGHT_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
            obj->vars.words[3] = handle;
            sound_attach(handle, obj, (void (*)()) obj_sound_track_ahead);
        }
        handler->queued_entry = -1;
        handler->result = 0x78;
        return;
    case -1:
        if (obj->vars.words[3] != 0) {
            sound_stop(obj->vars.words[3]);
            obj->vars.words[3] = 0;
        }
        obj_request_state(obj, handler, 0, 0);
        return;
    default:
        if (result == (result / 6) * 6) {
            obj_emit_forward_effect(obj);
        }
        return;
    }
}

/* Behaviour step: -2 starts the loop sound (kept in vars word 0x254) and
 * moves on; -1 stops it and runs the step's follow-up; any other result
 * calls obj_emit_forward_effect when it is a multiple of 6. */
void obj_loop_sound_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;
    s32 sound;

    switch (result) {
    case -2:
        if (obj->vars.words[3] == 0) {
            sound = sound_start(SND_LIGHT_GUNFIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
            obj->vars.words[3] = sound;
            sound_attach(sound, obj, (void (*)())obj_sound_track_ahead);
        }
        handler->queued_entry = -1;
        handler->result = 0x78;
        return;
    case -1:
        if (obj->vars.words[3] != 0) {
            sound_stop(obj->vars.words[3]);
            obj->vars.words[3] = 0;
        }
        obj_request_state(obj, handler, 0, 0);
        return;
    default:
        if (result == (result / 6) * 6) {
            obj_emit_forward_effect(obj);
        }
        return;
    }
}

#if STAGE == 7
void obj_turn_to_player_step();
void obj_loop_sound_step(Object *obj, ObjHandler *handler);
#endif

void obj_state_dispatch(Object *obj, ObjHandler *handler) {
    switch (((ObjState *) obj)->state) {
    case 0:
        obj_turn_to_player_step(obj, handler);
        break;
    case 1:
        obj_face_player_step(obj, handler);
        break;
    default:
        obj_loop_sound_step(obj, handler);
        break;
    }
}

void obj_script_run(Object *obj, ObjHandler *handler) {
    obj_script_step(obj, handler);
}

/* Spawns an effect at the object's position and stops its loop sound, if it has one. */
s32 obj_spawn_effect_stop_sound(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    spawn_effect(pos->x, pos->y - 0xF0, pos->z, 0);
    particle_spawn_burst(pos->x, pos->y, pos->z, 0);
    if (obj->vars.gun_turret_2.sound_channel != 0) {
        sound_stop(obj->vars.gun_turret_2.sound_channel);
        obj->vars.gun_turret_2.sound_channel = 0;
    }
    scratch_top -= 0x10;
    return 0;
}

void gun_turret_2_draw(Object *obj) {
    /* Pins the slot to $s2; a plain local lands in $s3 and swaps the two saved registers. */
    register s32 slot asm("$18");
    Vec3 *pos;
    SVECTOR *rot;
    s32 colour;
    s32 *poses;
    s32 yaw;

    pos = scratch_alloc(0x10);
    rot = scratch_alloc(0x10);
    yaw = obj->yaw;
    slot = pchr_copy_slot(model_slot_pchr(*(s32 *)obj->asset));
    poses = pchr_poses_build(slot);
    pchr_table[slot & 0x7FF].unk_0C = poses;
    rot[0].vx = 0;
    rot[0].vy = -0x32;
    rot[0].vz = 0;
    rot[1].vx = 0;
    rot[1].vy = obj->vars.gun_turret_2.turret_yaw - yaw;
    rot[1].vz = 0;
    pose_rotate_range(poses, 0, 4, rot, &rot[1]);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
        /* The second store keeps jump.c from turning this select into slt/negu/and; as a branch,
         * colour's known bits still let combine fold spark_add's chain (colour >> 24) to 0. */
        colour = 0;
        colour = 0;
    }
    pos->x = obj->x;
    pos->y = obj->y;
    pos->z = obj->z;
    spark_add(pos->x >> 12, pos->y >> 12, pos->z >> 12, yaw, 0, 0, slot, colour);
    aim_marker_draw(2, (SVECTOR *)&obj->width, pos, 0);
    if (obj->hit != 0) {
        obj->hit = -1;
    }
    scratch_top -= 0x20;
}

/* Stops the sound in the vars word at 0x254, if one is playing. */
void obj_loop_sound_clear(Object *obj) {
    if (obj->vars.gun_turret_2.sound_channel != 0) {
        sound_stop(obj->vars.gun_turret_2.sound_channel);
        obj->vars.gun_turret_2.sound_channel = 0;
    }
}

extern s16 *gun_turret_2_data;
/* The stage's copy of the turret's data. */
extern ModelSlotHead gun_turret_2_asset;
extern s16 *gun_turret_2_link_data[];
extern s16 *gun_turret_2_script_pos[];
extern ScriptCallEntry gun_turret_2_calls[];
extern StateEntry gun_turret_2_states[];
#define TURRET_ASSET gun_turret_2_asset
#define TURRET_LINK_DATA gun_turret_2_link_data
#define TURRET_SCRIPT_POS gun_turret_2_script_pos
#define TURRET_UNK_194 gun_turret_2_calls
#define TURRET_UNK_198 gun_turret_2_states

/* Spawns gun turret 2 from its placement: handlers, script, angles and a variant (0..2) from the placement. Returns 0 if no object was free. */
s32 gun_turret_2_spawn(Placement *place) {
    Object *obj;
    s32 variant;
    s16 **script;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_actors(), &obj->node);
    place->unk_02 = -1;
    obj->handlers[0].fn = (void (*)(Object *, ObjHandler *)) fn_s02_800BBD64;
    obj->handlers[1].fn = obj_script_run;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = (void (*)(Object *, ObjHandler *)) gun_turret_2_draw;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->callback = (s32) obj_spawn_effect_stop_sound;
    obj->destructor = obj_loop_sound_clear;
    obj->kind = place->unk_04[1];
    obj->asset = &TURRET_ASSET;
    obj->hit_cooldown_max = 0x30;
    obj->call_table = TURRET_UNK_194;
    obj->state_table = TURRET_UNK_198;
    obj->unk_1C6 = 0;
    obj->script.pc = TURRET_SCRIPT_POS[0];
    obj->script.data = TURRET_LINK_DATA;
    obj->script.unk_0A = 0;
    script = &gun_turret_2_data;
    script_start((Script *) obj, *script, (s32) script);
    obj_init_from_place(obj, place, 0x24);
    obj_set_part_bounds(obj, 0, 0x1000);
    obj->vars.turret.unused_250 = -2;
    obj->vars.turret.pitch = obj->pitch;
    obj->vars.turret.yaw = obj->yaw;
    obj->vars.turret.roll = obj->roll;
    variant = *(u16 *) &place->unk_1A >> 8;
    variant = MAX(MIN(variant, 2), 0);
    obj->vars.turret.variant = variant;
    obj->vars.turret.sound = 0;
    return 1;
}

/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void obj_script_jump_within(Object *obj) {
    s32 *player = player_position();
    s32 dist = isqrt(length_sq(player[0] - (obj->x >> 12), player[1] - (obj->y >> 12), player[2] - (obj->z >> 12)));
    s16 *cursor = obj->script.pc;
    s32 threshold;
    s32 index;

    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold >= dist) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

#if STAGE == 11
/* Stops the two sound effects an object may have playing (sound handles are bytes at 0x27C and 0x27D).
 * Proposed stage.h fields: Object u8 sound_a @0x27C, sound_b @0x27D (not in stage.h yet). */
void obj_stop_sound_slots(Object *obj) {
    if (((u8 *)obj)[0x27C] != 0) {
        sound_stop(((u8 *)obj)[0x27C]);
        ((u8 *)obj)[0x27C] = 0;
    }
    if (((u8 *)obj)[0x27D] != 0) {
        sound_stop(((u8 *)obj)[0x27D]);
    }
}

/* An angle (low 12 bits) limited to 0..0x20 in its first half turn, 0xEE4..0xFFF in its second. */
s16 angle_clamp_pitch(s32 angle) {
    s32 result;

    angle &= 0xFFF;
    if (angle >= 0x801) {
        result = MAX(cap_FFF(angle), 0xEE4);
    } else {
        result = NOT_NEGATIVE(cap_20(angle));
    }
    return result;
}
#endif

#if STAGE == 11
/* Turns a direction vector into rotation angles: out[0] from the pitch, out[1] the yaw, out[2] 0. */
void dir_to_angles_clamped(Vec3 *dir, SVECTOR *out) {
    s32 yaw;
    s32 pitch;

    angles_to_player(dir->x, dir->y, dir->z, &yaw, &pitch);
    out->vy = yaw;
    out->vx = -angle_clamp_pitch((s16)pitch);
    out->vz = 0;
}
#endif
