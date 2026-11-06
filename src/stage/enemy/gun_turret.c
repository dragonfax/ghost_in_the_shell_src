/* gun_turret: one of the original source files (scripts/objmap.py); s05, s09, s12. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* Per-stage data: the shot parameter block (s32 at +0..+8, then halfwords) at a different address in each stage. */
extern s32 shot_params_speed;
extern s32 d_8012003C;
extern s32 d_80120040;
extern u16 d_80120044;
extern s16 shot_params_hit_effect_index;
extern s16 d_80120048;
extern s16 d_8012004A;
extern s16 d_8012004C;
extern s16 d_8012004E;
extern s16 d_80120050;
extern s16 d_80120052;
extern s16 d_80120054;
extern s16 d_80120056;
extern s16 d_80120058;
extern s16 d_8012005A;
#define SHOT_PARAM_00 shot_params_speed
#define SHOT_PARAM_04 d_8012003C
#define SHOT_PARAM_08 d_80120040
#define SHOT_PARAM_0C d_80120044
#define SHOT_PARAM_0E shot_params_hit_effect_index
#define SHOT_PARAM_10 d_80120048
#define SHOT_PARAM_12 d_8012004A
#define SHOT_PARAM_14 d_8012004C
#define SHOT_PARAM_16 d_8012004E
#define SHOT_PARAM_18 d_80120050
#define SHOT_PARAM_1A d_80120052
#define SHOT_PARAM_1C d_80120054
#define SHOT_PARAM_1E d_80120056
#define SHOT_PARAM_20 d_80120058
#define SHOT_PARAM_22 d_8012005A

void gun_turret_shot_params_init(void) {
    s16 k = 0x2A;

    SHOT_PARAM_0E = 1;
    SHOT_PARAM_00 = 0x8000;
    SHOT_PARAM_04 = 0x18000;
    SHOT_PARAM_08 = 0x400;
    SHOT_PARAM_10 = k;
    SHOT_PARAM_12 = 0x66;
    SHOT_PARAM_14 = 0xA;
    SHOT_PARAM_16 = 0xA;
    SHOT_PARAM_18 = k;
    SHOT_PARAM_1A = 3;
    SHOT_PARAM_1C = 0xE;
    SHOT_PARAM_0C = 0xF;
    SHOT_PARAM_1E = 0;
    SHOT_PARAM_20 = k;
    SHOT_PARAM_22 = 0xAA;
}

/* Script op: read a yaw tolerance and a jump index; jump when the player is
 * within the tolerance of the object's facing and within 0x200 of level. */
void script_op_jump_if_facing_player(Object *obj) {
    ObjLink *link = &obj->script;
    s16 *cursor = link->pc;
    s32 facing = obj->vars.trace.aim_yaw;
    s32 facing_copy = facing; /* the negative arm uses its own copy */
    s32 tol;
    s32 target;
    s32 want_yaw;
    s32 want_pitch;
    s32 player_yaw;
    s32 player_pitch;
    s32 in_view;

    link->pc = cursor + 1;
    tol = *cursor;
    link->pc = cursor + 2;
    target = cursor[1];
    angles_to_player(obj->x >> 12, (obj->y >> 12) - ((s16)obj->height / 2), obj->z >> 12, &want_yaw, &want_pitch);
    player_yaw = want_yaw;
    player_pitch = want_pitch;
    if ((angle_diff(facing, player_yaw) >= 0 ? angle_diff(facing, player_yaw)
                                             : -angle_diff(facing_copy, player_yaw)) < tol
        && ABS(angle_diff(0, player_pitch)) < 0x200) {
        in_view = 1;
    } else {
        in_view = 0;
    }
    if (in_view) {
        link->pc = ((s16 **)link->data)[target];
    }
}

void gun_turret_phase0(Object *obj, ObjHandler *handler) {
    obj_link_script_run(obj, handler);
}

/* Turns the object's 0x24A angle toward the player by at most step. */
void obj_angle_toward_player(Object *obj, s32 step) {
    s32 *player = player_position();
    s32 angle = atan2(player[2] - (obj->z >> 12), player[0] - (obj->x >> 12));

    obj->vars.h.unk_24A = angle_approach((s16) obj->vars.h.unk_24A, angle, step);
}

#if STAGE == 9
void obj_angle_toward_player(Object *obj, s32 step);
#endif

void obj_turn_to_player_16(Object *obj) {
    obj_angle_toward_player(obj, 0x10);
}

/* Per-stage data: the muzzle offset tables and the shot parameters. */
extern s16 muzzle_x_table[], muzzle_y_table[];
/* Per-stage data: the shot parameter block (s32 at +0..+8, then halfwords) at a different address in each stage. */
extern s32 shot_params_speed;
#define MUZZLE_X muzzle_x_table
#define MUZZLE_Y muzzle_y_table
#define MUZZLE_SHOT shot_params_speed

/* Fires a shot from the next of 5 muzzle offsets (stepping by 2 each call):
 * rotates the offset by the object's heading, adds its position, plays the sound and spawns the shot. */
void obj_fire_muzzle_shot(Object *obj) {
    s32 *pos = scratch_alloc(0x10);
    s16 *rot = scratch_alloc(8);
    s32 muzzle;
    s32 base_y;
    s32 off_y;

    rot[0] = 0;
    rot[1] = obj->vars.h.unk_24A;
    rot[2] = 0;
    muzzle = obj->vars.h.unk_252;
    muzzle = (muzzle + 2) % 5;
    obj->vars.h.unk_252 = muzzle;
    pos[0] = MUZZLE_X[muzzle];
    pos[1] = MUZZLE_Y[muzzle] - 0x5F;
    pos[2] = 0xFA;
    rotate_xz_twice(rot[1], 0, pos, pos + 1, pos + 2);
    pos[0] = (obj->x >> 12) + pos[0];
    base_y = obj->y >> 12;
    off_y = pos[1] - 0x32;
    pos[1] = base_y + off_y;
    pos[2] = (obj->z >> 12) + pos[2];
    sound_play_at_units(SND_ENEMY_FIRE | SND_GROUP(1), 0x60, 0x3C, pos);
    shot_spawn_obj(pos, (u16 *)rot, 2, (s32)&MUZZLE_SHOT);
    scratch_top -= 0x18;
}

#if STAGE == 9
void obj_fire_muzzle_shot(Object *obj);
#endif

void obj_handle_result(Object *obj, ObjHandler *handler) {
    s16 result;

    result = handler->result;
    if (result == -2) {
        handler->queued_entry = -1;
        handler->result = 0xA0;
    }
    if (result == 0x78 || result == 0x96) {
        obj_fire_muzzle_shot(obj);
        return;
    }
    if (result < 0x64) {
        obj_angle_toward_player(obj, 0x10);
    }
    if (result == -1) {
        obj_request_state(obj, handler, 0, 0);
    }
}

void gun_turret_update(Object *obj, ObjHandler *handler) {
    obj_script_step(obj, handler);
}

/* Spawns an effect at the object's three scaled coordinates, then calls particle_spawn_burst with the same point. */
s32 obj_spawn_effect_burst(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    spawn_effect(pos->x, pos->y - 0xF0, pos->z, 0);
    particle_spawn_burst(pos->x, pos->y, pos->z, 0);
    scratch_top -= 0x10;
    return 0;
}

void gun_turret_draw(Object *obj, ObjHandler *handler) {
    Vec3 *pos;
    SVECTOR *rot;
    s32 colour;
    s32 *poses;
    s32 yaw;
    s32 slot;

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
    rot[1].vy = obj->vars.gun_turret.initial_yaw - yaw;
    rot[1].vz = 0;
    pose_rotate_range(poses, 0, 2, rot, &rot[1]);
    pose_rotate_range(poses, 3, 1, rot, &rot[1]);
    if (obj->hit > 0) {
        colour = 0x60C0FF;
    } else {
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

void fn_800BD11C(void) {
    gun_turret_shot_params_init();
}

/* Per-stage data of gun_turret_spawn: asset, link data, script position,
   call_table/state_table and the saved unk_184. */
extern u8 gun_turret_asset[];
extern s16 *gun_turret_link_data[];
extern StateEntry gun_turret_states[];
extern ScriptCallEntry gun_turret_call_table[];
extern s16 *gun_turret_script_pos;
extern u16 d_80120044;
#define TURRET_ASSET gun_turret_asset
#define TURRET_LINK_DATA gun_turret_link_data
#define TURRET_SCRIPT_POS gun_turret_script_pos
#define TURRET_UNK_194 gun_turret_call_table
#define TURRET_UNK_198 gun_turret_states
#define TURRET_SAVED_184 d_80120044
extern void gun_turret_draw(Object *obj, ObjHandler *handler);
extern s16 *gun_turret_data;

/* Spawns a gun turret from its placement: handlers, script, part bounds and
   its starting angles. Returns 0 if no object was free. */
s32 gun_turret_spawn(Placement *place) {
    Object *obj;
    s16 **script;
    ObjHandler *h;
    s32 variant;

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *)get_obj_list_actors(), (Node *)obj);
    *(s16 *)&place->unk_00[2] = -1;
    h = obj->handlers;
    obj->handlers[0].fn = (void *)gun_turret_phase0;
    obj->handlers[1].fn = gun_turret_update;
    obj->handlers[2].fn = obj_run_states_default;
    obj->handlers[3].fn = gun_turret_draw;
    obj->callback = (s32)obj_spawn_effect_burst;
    obj->call_table = TURRET_UNK_194;
    h[0].unk_11 = 0;
    h[0].state = 0;
    h[1].unk_11 = 0;
    h[1].state = 0;
    h[2].unk_11 = 0;
    h[2].state = 0;
    h[3].unk_11 = 0;
    h[3].state = 0;
    obj->state_table = TURRET_UNK_198;
    variant = place->unk_00[5];
    obj->asset = TURRET_ASSET;
    obj->hit_cooldown_max = 0x30;
    *(volatile s16 *)&obj->unk_1C6 = 0;
    *(volatile s16 *)&obj->kind = variant;
    obj->script.data = TURRET_LINK_DATA;
    obj->script.unk_0A = 0;
    obj->script.pc = TURRET_SCRIPT_POS;
    script = &gun_turret_data;
    script_start((Script *)obj, *script, (s32)script);
    obj_init_from_place(obj, place, 0x24);
    obj_set_part_bounds(obj, 0, 0x1000);
    *(s16 *)&obj->vars.gun_turret.unk_250 = -2;
    obj->vars.gun_turret.unused_252 = 0;
    obj->vars.gun_turret.initial_pitch = obj->pitch;
    obj->vars.gun_turret.initial_yaw = obj->yaw;
    obj->vars.gun_turret.initial_roll = obj->roll;
    TURRET_SAVED_184 = obj->damage;
    return 1;
}

/* Distance from the object to the player. The object's script cursor reads a
   (threshold, index) pair; when the distance is at most the threshold, the cursor
   jumps to the entry at index in the object's table. */
void script_branch_if_near_player(Object *obj) {
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
