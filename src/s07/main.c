#include "common.h"
#define STAGE 7
#define STAGE_ASM "../asm/s07/nonmatchings/main"
#include "stage.h"
#include "s07_types.h"
#include "sounds.h"
#include "gte.h"

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"
#include "enemy/stationary_rocket_launcher.c"

#include "../stage/sound/obj_sound2.c"
#include "enemy/stationary_laser.c"

#include "../stage/enemy/fuchikoma_b.c"

#include "../stage/enemy/script_radius_jumps.c"

#include "../stage/enemy/script_reads.c"

#include "../stage/enemy/walker_mech.c"

#include "../stage/enemy/enemy_sounds.c"

#include "../stage/enemy/enemy_ops.c"
#include "../stage/enemy/helicopter2.c"

#include "../stage/eng_fn_800bf13c.c"

#include "../stage/eng_fn_800bf8b4.c"

void obj_yaw_step(Object *obj);
void obj_sound2_start(Object *obj);
void obj_avoid_walls(Object *obj);
#include "../stage/eng_fn_800c00f4.c"

void obj_track_player(Object *obj, s32 yaw_step, s32 pitch_step);
#include "../stage/eng_fn_800c0144.c"

#include "../stage/eng_fn_800c05b8.c"

void obj_muzzle_effect(Object *obj);
#include "../stage/eng_fn_800c0708.c"

#include "../stage/eng_fn_800c0764.c"

extern s32 tank2_asset[3];
extern s32 model_pchr_saved;
#include "../stage/eng_fn_800c0e88.c"

#include "../stage/eng_fn_800c12c0.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/enemy/gun_turret_2.c"

#include "../stage/eng_fn_800bb148.c"

/* Same code as func_800B7534 (s01). */
void rocket_fuchikoma_phase0(Object *obj) {
    if (obj->health > 0) {
        obj_link_script_run();
    }
}

void obj_yaw_turn(Object *obj) {
    obj->yaw = angle_approach(obj->yaw, obj->vars.h.unk_254, 0x10);
}

#include "../stage/eng_fn_800bb3a0.c"

extern s16 spawn_offset_x_table[], D_80116850[], D_80116868[];
extern s16 D_80116838[], spawn_offset_y_table[], D_80116868[];
extern s16 D_80116838[], D_80116850[], spawn_offset_z_table[];
/* Spawns a randomly offset effect in front of the object: rotates a fixed offset by the object's angles. */
void shot_burst_spawn(Object *obj) {
    s32 *v = scratch_alloc(0x20);
    s16 *rot = scratch_alloc(8);
    s32 *w;
    s32 i;

    rot[0] = -obj->vars.h.unk_248 + 0x100;
    rot[1] = obj->yaw;
    rot[2] = 0;
    v[1] = -0x88;
    v[0] = 0;
    v[2] = -0x2C;
    rotate_xz_twice(rot[1], -obj->pitch, v, v + 1, v + 2);
    w = v + 4;
    i = rand_a_next() * 11 / 4096;
    v[4] = spawn_offset_x_table[i];
    v[5] = spawn_offset_y_table[i] - 0x42;
    v[6] = spawn_offset_z_table[i] + 0x50;
    rotate_xz_twice(rot[1], rot[0], w, w + 1, w + 2);
    v[4] = (obj->x >> 12) + v[0] + v[4];
    v[5] = (obj->y >> 12) + v[1] + v[5];
    v[6] = (obj->z >> 12) + v[2] + v[6];
    sound_play_at_units(SND_S07_ENEMY_FIRE | SND_GROUP(1), 0x60, 0x3C, w);
    shot_spawn_obj(w, (u16 *)rot, 2, (s32)&shot_params);
    scratch_top -= 0x28;
}

void shot_burst_spawn();
/* Handler step: result -2 counts vars.h.unk_248 down and then finishes with state 3 and 0x3C steps left,
 * -1 starts the next state, and every 12th step of a running count calls func_800BB6A4. */
void obj_countdown_step(Object *obj, ObjHandler *handler) {
    s32 result = handler->result;

    switch (result) {
    case -2:
        if (obj->vars.h.unk_248 >= -0xC7) {
            obj->vars.h.unk_248 -= 0x10;
        } else {
            handler->queued_entry = -1;
            handler->result = 0x3C;
            obj->vars.h.unk_258 = 3;
        }
        break;
    case -1:
        obj_request_state(obj, handler, 0, 0);
        break;
    default:
        if ((s16)obj->vars.h.unk_258 > 0 && result % 12 == 0) {
            shot_burst_spawn(obj);
            obj->vars.h.unk_258 = obj->vars.h.unk_258 - 1;
        }
        break;
    }
}

/* Rotates a copy of src by the object's yaw, adds the object's position (whole units), and calls spark_pair_spawn. */
void spark_pair_spawn_at_obj(Object *obj, s32 *src) {
    s32 *out = scratch_alloc(0x10);

    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    rotate_xz_twice(obj->yaw, 0, out, out + 1, out + 2);
    out[0] += obj->x >> 12;
    out[1] = obj->y >> 12;
    out[2] += obj->z >> 12;
    spark_pair_spawn((Vec3 *)out, 0x1800, 0x1000);
    scratch_top -= 0x10;
}

typedef struct SplashEntry {
    s32 id;
    s32 spark_a[4];
    s32 spark_b[4];
} SplashEntry;

/* Each stage's copy reads its own table (s05: splash_table, s07: splash_table). */
extern SplashEntry splash_table[];
#define SPLASH_TABLE splash_table

void obj_splash_update(Object *obj, ObjHandler *handler) {
    s32 wet;
    s32 surface;
    s32 i;
    s32 id;
    SplashEntry *rec;

    if (obj->health > 0) {
        obj_script_step(obj, handler);
        if (get_area() / 3 == 4) {
            surface = (surface_of(obj->ground_id) & 0x300) >> 8;
            wet = surface == 1;
        } else {
            wet = 0;
        }
        id = obj->type.unk_0C;
        rec = SPLASH_TABLE;
        for (i = 0; i < 2; i++, rec++) {
            if (rec->id == id && id != obj->vars.fn_800BBF9C_obj.unk_25A) {
                if (wet == 1) {
                    spark_pair_spawn_at_obj(obj, rec->spark_a);
                    spark_pair_spawn_at_obj(obj, rec->spark_b);
                    sound_play_at(SND_SMALL_SPLASH | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                    break;
                }
                sound_play_at(SND_FOOTSTEP | SND_GROUP(2), 0x7F, 0x3C, &obj->x);
                break;
            }
        }
        obj->vars.fn_800BBF9C_obj.unk_25A = id;
    }
}

#include "../stage/eng_fn_800bb95c.c"

#include "../stage/eng_fn_800bbf9c.c"

/* Spawns an object of this object's kind (its type plus the index of its asset) at its position in whole
 * units, with its angles (pitch negated), then marks its placement as spawned (byte 4 bits 0-1 = 2). */
s32 obj_spawn_here(Object *obj) {
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
void script_jump_near_player(Object *obj) {
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
void script_jump_near(Object *obj) {
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

/* Reads two halfwords from the script stream and combines them into the speed. */
void script_read_speed_long(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;
    s32 hi;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    hi = pc[1] << 16;
    obj->speed = (lo & 0xFFFF) | hi;
}

/* Same code as func_800BC020 (s01). */
void script_read_long(Object *obj) {
    s16 *pc = obj->script.pc;
    s32 lo;

    obj->script.pc = pc + 1;
    lo = *pc;
    obj->script.pc = pc + 2;
    obj->speed_accel = pc[1] << 16;
    obj->speed_accel = (lo & 0xFFFF) | obj->speed_accel;
}

/* Reads the next script halfword (cursor at +0x20). With the flag at +0xF8 set, the cursor jumps to the
 * entry of the type's table (+0x1C) that the halfword selects. */
void script_branch_on_flag(Object *obj) {
    s16 *cursor = obj->script.pc;
    s32 index;

    obj->script.pc = cursor + 1;
    index = *cursor;
    if (obj->script_flag != 0) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

#include "../stage/eng_fn_800bc098.c"
#include "enemy/script_bounds_ops.c"
#include "enemy/script_turn_jumps.c"
#include "enemy/script_jump_ops.c"

#include "boss/bomb_mech.c"

#include "../stage/enemy/giant_robot_fx.c"
#include "enemy/giant_robot_fx_part2.c"
#include "core/stage.c"
#include "../stage/combat/shots.c"
#include "core/stage_timers.c"

#include "../stage/eng_fn_800c5620.c"

extern RecTemplate fade_red_fx_template;
void fade_red_update();
/* Starts a record from the template fade_red_fx_template with fade_red_update as its callback; pos is passed through. */
s32 effect_spawn_at_pos(s32 *pos) {
    return fx_spawn_template(pos, &fade_red_fx_template, fade_red_update);
}

void obj_noop_hook(void) {
}

extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void fx_rec34_spawn_default(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}

extern RecTemplate D_801177C8, D_801177E0, fx_owner_template_a, D_8011873C;
extern RecTemplate D_801177C8, D_801177E0, D_80118724, fx_owner_template_b;
#include "../stage/eng_fn_800c571c.c"

char str_hou2_tp0_clt[16] = "hou2_tp0.clt";

char str_hou2_ch0_clt[16] = "hou2_ch0.clt";

char str_hou2_tp0_xs3[16] = "hou2_tp0.xs3";

char str_hou2_ch0_vx1[16] = "hou2_ch0.vx1";

char str_hou2_ch0cb4[16] = "hou2_ch0.cb4";

char str_mth2_tp0_clt[16] = "mth2_tp0.clt";

char str_mth2_ch0_clt[16] = "mth2_ch0.clt";

char str_mth2_tp0_xs3[16] = "mth2_tp0.xs3";

char str_mth2_ch0_vx1[16] = "mth2_ch0.vx1";

char str_mth2_ch0cb4[16] = "mth2_ch0.cb4";

char str_bos7_tp1_clt[16] = "bos7_tp1.clt";

char str_bos7_tp0_clt[16] = "bos7_tp0.clt";

char str_bos7_ch0_clt[16] = "bos7_ch0.clt";

char str_bos7_tp1_xs3[16] = "bos7_tp1.xs3";

char str_bos7_tp0_xs3[16] = "bos7_tp0.xs3";

char str_bos7_ch2_vx1[16] = "bos7_ch2.vx1";

char str_bos7_ch1_vx1[16] = "bos7_ch1.vx1";

char str_bos7_ch0_vx1[16] = "bos7_ch0.vx1";

char str_bos7_ch1cb4[16] = "bos7_ch1.cb4";

char str_bos7_ch0cb4[16] = "bos7_ch0.cb4";

#include "../stage/eng_fn_800c4368.c"

void obj_noop_update(void) {
}

#include "../stage/eng_fn_800c5ab8.c"

#include "../stage/eng_fn_800c5b9c.c"

#include "../stage/eng_fn_800c5bbc.c"
#include "core/scene_intro.c"

extern s32 alert_flag, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, turn_flag, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, mission_enemies_left, cam_timer;
extern GridEntry *flagged_grid_cells[];
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_side_blend, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, D_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s16 msg_pos_x, msg_pos_y;
extern s16 msg_pos_x, msg_pos_y;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 D_8011FEDC, d_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s32 D_8011FEDC, D_8011FEE4, D_8011FEE8, grid_flagged_count;
extern s32 D_8011FEDC, D_8011FEE4, timer_warn_shown, D_8011FEA8;
void cam_update_phase2();
void hud_frame_draw();
#include "../stage/mission/mission_state.c"
#include "core/grid_areas.c"

#include "../stage/lib/libc/printf.c"
#include "../stage/lib/libgte/square_root0.c"
#include "../stage/lib/libgte/trans_matrix.c"
#include "../stage/lib/libgte/set_rot_matrix.c"
#include "../stage/lib/libgte/set_trans_matrix.c"
#include "../stage/sys/lz.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/lib/libgte/vector_normal.c"
#include "../stage/math/gte_helper.c"
#include "../stage/lib/libgte/matrix_normal.c"

#include "../stage/sys/pad_input.c"

#include "../stage/sys/vsync.c"

#include "../stage/gfx/cam_view_reset.c"
#include "../stage/gfx/view.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"

#include "../stage/gfx/shadow.c"

#include "../stage/gfx/model_slots.c"

#include "../stage/gfx/pchr_pose.c"
#include "../stage/gfx/cylinder.c"
#include "../stage/gfx/floor_grid.c"
#include "../stage/gfx/lens_flare.c"

#include "../stage/gfx/scratch.c"
#include "../stage/gfx/track.c"
#include "../stage/world/world_query.c"

#include "../stage/core/pause_reset.c"
#include "../stage/core/pause.c"

#include "../stage/core/cells.c"
#include "../stage/core/stage_main.c"
#include "../stage/core/stage_loop.c"
#include "../stage/debug/debug_menu.c"
#include "../stage/debug/debug_print.c"
#include "../stage/core/part.c"
#include "../stage/tables/name_table_base.c"

#include "../stage/gfx/interp.c"
#include "../stage/gfx/interp38b.c"
#include "../stage/tables/name_load.c"
#include "../stage/core/stage_data.c"

#include "../stage/tables/stage_info.c"
#include "../stage/tables/name_table.c"
#include "../stage/math/transform_point.c"
#include "../stage/player/player_state.c"
#include "../stage/player/player.c"

#include "../stage/object/pair_table.c"
#include "../stage/object/grid_hooks.c"
#include "../stage/tables/scan_items.c"
#include "../stage/object/object_system.c"
#include "../stage/combat/effects.c"
#include "../stage/mission/mission_status.c"
#include "../stage/mission/mission_clock.c"
#include "../stage/mission/shield.c"
#include "../stage/mission/mission_counts.c"
#include "../stage/mission/mission_rank.c"
#include "../stage/mission/stage_round.c"
#include "../stage/hud/hud.c"
#include "../stage/hud/msg_queue.c"
#include "../stage/hud/msg_line.c"
#include "../stage/hud/ui_items.c"
#include "../stage/hud/ui_draw.c"
#include "../stage/hud/meter.c"
#include "../stage/camera/rec_table.c"
#include "../stage/camera/camera.c"
#include "../stage/combat/object_slots.c"
#include "../stage/combat/spark_count.c"
#include "../stage/combat/sparks.c"
#include "../stage/combat/grenades.c"
#include "../stage/combat/pickups.c"
#include "../stage/camera/lock_mode.c"
#include "../stage/camera/lock_on.c"
#include "../stage/combat/shots_fx.c"
#include "../stage/sound/sound.c"
#include "../stage/lib/libgte/gte_misc.c"
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
