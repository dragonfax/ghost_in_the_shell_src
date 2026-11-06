#include "common.h"
#define STAGE 9
#include "stage.h"
#include "s09_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"
#include "core/stage.c"

#include "../stage/object/obj_script.c"

/* Same code as func_800BC8AC (s01). */
void script_op_switch(Object *obj) {
    s32 limit;
    s16 *cursor;
    s32 threshold;
    s32 index;

    limit = (s16) obj_player_dist(obj);
    cursor = obj->script.pc;
    obj->script.pc = cursor + 1;
    threshold = cursor[0];
    obj->script.pc = cursor + 2;
    index = cursor[1];
    if (threshold < limit) {
        obj->script.pc = ((s16 **)obj->script.data)[index];
    }
}

void script_dispatch(ScriptReader *rd) {
    u8 *pc = rd->pc;
    s16 jump;
    s32 op;

    rd->pc = pc + 2;
    jump = rd->jump_enabled;
    op = *(s16 *)pc;
    if (jump != 0) {
        rd->pc = rd->op_table[op];
    }
}

#include "enemy/timer_sound.c"
#include "enemy/chaser.c"

#include "../stage/enemy/fuchikoma_b.c"

#include "../stage/enemy/script_radius_jumps.c"

#include "../stage/enemy/script_reads.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/eng_fn_800be3c8.c"

#include "../stage/eng_fn_800bb5e4.c"

#include "../stage/eng_fn_800be470.c"

#define SOUND_HANDLE(obj) (*(u8 *)&(obj)->vars.h.unk_25A)
void obj_pitch_toward_player(Object *obj, s32 step);
#include "../stage/eng_fn_800bf0b4.c"

#include "../stage/eng_fn_800bab20_obj_sound_handle_stop.c"

#include "../stage/enemy/pos_distance.c"

#include "../stage/enemy/enemy_ops.c"
#include "../stage/enemy/rocket_drone.c"

#include "../stage/enemy/gun_turret.c"

#include "../stage/eng_fn_800bf13c.c"

s32 obj_dist_to_target(Object *obj);
#include "../stage/eng_fn_800bf8b4.c"

void obj_yaw_step(Object *obj);
void obj_sound2_start(Object *obj);
#include "../stage/eng_fn_800c00f4.c"

#include "../stage/eng_fn_800c0144.c"

#include "../stage/eng_fn_800c05b8.c"

void obj_muzzle_effect(Object *obj);
#include "../stage/eng_fn_800c0708.c"

#include "../stage/eng_fn_800c0764.c"

extern s32 tank2_asset[3];
extern s32 model_pchr_saved;
#include "../stage/eng_fn_800c0e88.c"

char elevator_start_msg[32] = "#2Accessed!  Elevatorstarting.\241";

char str_land_tp1_clt[16] = "land_tp1.clt";

char str_land_tp0_clt[16] = "land_tp0.clt";

char str_land_ch0_clt[16] = "land_ch0.clt";

char str_land_tp1_xs3[16] = "land_tp1.xs3";

char str_land_tp0_xs3[16] = "land_tp0.xs3";

char str_land_ch0_vx1[16] = "land_ch0.vx1";

char str_land_ch0cb4[16] = "land_ch0.cb4";

char str_arkb_tp0_clt[16] = "arkb_tp0.clt";

char str_arkb_ch0_clt[16] = "arkb_ch0.clt";

char str_arkb_tp0_xs3[16] = "arkb_tp0.xs3";

char str_arkb_ch0_vx1[16] = "arkb_ch0.vx1";

char str_arkb_ch0cb4[16] = "arkb_ch0.cb4";

char str_troi_tp0_clt[16] = "troi_tp0.clt";

char str_troi_ch0_clt[16] = "troi_ch0.clt";

char str_troi_tp0_xs3[16] = "troi_tp0.xs3";

char str_troi_ch0_vx1[16] = "troi_ch0.vx1";

char str_troi_ch0cb4[16] = "troi_ch0.cb4";

char str_sel1_tp0_clt[16] = "sel1_tp0.clt";

char str_sel1_ch0_clt[16] = "sel1_ch0.clt";

char str_sel1_tp0_xs3[16] = "sel1_tp0.xs3";

char str_sel1_ch0_vx1[16] = "sel1_ch0.vx1";

char str_sel1_ch0cb4[16] = "sel1_ch0.cb4";

char str_hou1_tp0_clt[16] = "hou1_tp0.clt";

char str_hou1_ch0_clt[16] = "hou1_ch0.clt";

char str_hou1_tp0_xs3[16] = "hou1_tp0.xs3";

char str_hou1_ch0_vx1[16] = "hou1_ch0.vx1";

char str_hou1_ch0cb4[16] = "hou1_ch0.cb4";

char str_tnk2_tp0_clt[16] = "tnk2_tp0.clt";

char str_tnk2_ch0_clt[16] = "tnk2_ch0.clt";

char str_tnk2_tp0_xs3[16] = "tnk2_tp0.xs3";

char str_tnk2_ch0_vx1[16] = "tnk2_ch0.vx1";

char str_tnk2_ch0cb4[16] = "tnk2_ch0.cb4";

#include "../stage/eng_fn_800c12c0.c"

extern s32 alert_flag, D_8011FEB0, orbit_flag, enemy_count, cam_timer;
extern s32 D_8011FEAC, turn_flag, orbit_flag, enemy_count, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, enemy_count, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, enemy_count, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, mission_enemies_left, cam_timer;
extern GridEntry *flagged_grid_cells[];
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_side_blend, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, D_8011FEE4, hurry_msg_shown, D_8011FEA8;
extern s16 msg_pos_x, msg_pos_y;
extern s16 msg_pos_x, msg_pos_y;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 spin_angle, d_8011FEE4, hurry_msg_shown, D_8011FEA8;
extern s32 spin_angle, D_8011FEE4, hurry_msg_shown, grid_flagged_count;
extern s32 spin_angle, D_8011FEE4, timer_warn_shown, D_8011FEA8;
void cam_update_phase2();
void hud_frame_draw();
#include "../stage/mission/mission_state.c"
#include "boss/reactor_control_rods.c"

#include "../stage/sys/lz.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/sys/pad_input.c"

#include "../stage/sys/vsync.c"

#include "../stage/gfx/model_slots.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"

#include "../stage/gfx/cam_view_reset.c"
#include "../stage/gfx/view.c"

#include "../stage/gfx/shadow.c"

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
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
