#include "common.h"
#define STAGE 10
#define STAGE_ASM "../asm/s10/nonmatchings/main"
#include "stage.h"
#include "s10_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. In the original they are their own object, after the engine's file_write_named. */
const char file_tetr_tp0_clt[] = "tetr_tp0.clt";
const char file_tetr_ch0_clt[] = "tetr_ch0.clt";
const char file_tetr_tp0_xs3[] = "tetr_tp0.xs3";
const char file_tetr_ch0_vx1[] = "tetr_ch0.vx1";
const char file_tetr_ch0_cb4[] = "tetr_ch0.cb4";
const char file_msub_tp0_clt[] = "msub_tp0.clt";
const char file_msub_ch0_clt[] = "msub_ch0.clt";
const char file_msub_tp0_xs3[] = "msub_tp0.xs3";
const char file_msub_ch0_vx1[] = "msub_ch0.vx1";
const char file_msub_ch0_cb4[] = "msub_ch0.cb4";
const char file_troi_tp0_clt[] = "troi_tp0.clt";
const char file_troi_ch0_clt[] = "troi_ch0.clt";
const char file_troi_tp0_xs3[] = "troi_tp0.xs3";
const char file_troi_ch0_vx1[] = "troi_ch0.vx1";
const char file_troi_ch0_cb4[] = "troi_ch0.cb4";
const char file_ball_tp0_clt[] = "ball_tp0.clt";
const char file_ball_ch0_clt[] = "ball_ch0.clt";
const char file_ball_tp0_xs3[] = "ball_tp0.xs3";
const char file_ball_ch0_vx1[] = "ball_ch0.vx1";
const char file_ball_ch0_cb4[] = "ball_ch0.cb4";
const char file_mfir_tp0_clt[] = "mfir_tp0.clt";
const char file_mfir_ch0_clt[] = "mfir_ch0.clt";
const char file_mfir_tp0_xs3[] = "mfir_tp0.xs3";
const char file_mfir_ch0_vx1[] = "mfir_ch0.vx1";
const char file_mfir_ch0_cb4[] = "mfir_ch0.cb4";
const char file_mth1_tp0_clt[] = "mth1_tp0.clt";
const char file_mth1_ch0_clt[] = "mth1_ch0.clt";
const char file_mth1_tp0_xs3[] = "mth1_tp0.xs3";
const char file_mth1_ch0_vx1[] = "mth1_ch0.vx1";
const char file_mth1_ch0_cb4[] = "mth1_ch0.cb4";
const char file_hou2_tp0_clt[] = "hou2_tp0.clt";
const char file_hou2_ch0_clt[] = "hou2_ch0.clt";
const char file_hou2_tp0_xs3[] = "hou2_tp0.xs3";
const char file_hou2_ch0_vx1[] = "hou2_ch0.vx1";
const char file_hou2_ch0_cb4[] = "hou2_ch0.cb4";
const char file_dora_ch0_cb4[] = "dora_ch0.cb4";

#include "../stage/enemy/pyramid_mine.c"

#include "../stage/enemy/enemy.c"
#include "../stage/math/angle_clamp.c"

#include "../stage/enemy/smg_soldier.c"

#include "../stage/eng_fn_800be3c8.c"

#include "../stage/eng_fn_800bb5e4.c"

#include "../stage/eng_fn_800be470.c"

#include "../stage/eng_fn_800bf0b4.c"

#include "../stage/eng_fn_800bab20_obj_sound_handle_stop.c"

extern ModelSlotHead timer_tail_data;
extern s16 d_8011B7AC[];
extern s32 loop_sound_fade_handle;
#include "../stage/eng_fn_800bbd28.c"
#include "enemy/red_laser_ball.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/enemy/beam_enemy.c"

extern ShotParams shot_params;
#include "../stage/eng_fn_800bb148.c"

#include "../stage/eng_fn_800bb338.c"

#include "../stage/eng_fn_800bb3a0.c"

extern s16 spawn_offset_x_table[];
extern s16 spawn_offset_y_table[];
extern s16 spawn_offset_z_table[];
extern ShotParams shot_params;
#include "../stage/eng_fn_800bb6a4.c"

#include "../stage/eng_fn_800bb95c.c"

#include "../stage/eng_fn_800bbb78.c"

#include "../stage/eng_fn_800bc098.c"

#include "../stage/enemy/gun_turret_2.c"
#include "world/elevator_doors.c"

#include "../stage/camera/cam_zone.c"
#include "boss/dual_mech.c"

#include "../stage/gfx/clip_poly.c"
#include "combat/projectiles.c"
#include "../stage/object/copy_slots.c"
#include "world/doors.c"

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
#include "core/grid_flagged.c"

#include "../stage/lib/libc/printf.c"
#include "../stage/lib/libgte/square_root0.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"
#include "../stage/sys/lz.c"

#include "../stage/sys/vsync.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/lib/libgte/vector_normal.c"
#include "../stage/math/gte_helper.c"
#include "../stage/lib/libgte/matrix_normal.c"

#include "../stage/sys/pad_input.c"

#include "../stage/gfx/cam_view_reset.c"
#include "../stage/gfx/view.c"

#include "../stage/gfx/shadow.c"

#include "../stage/gfx/model_slots.c"

#include "../stage/gfx/pchr_pose.c"
#include "../stage/gfx/cylinder.c"
#include "../stage/gfx/floor_grid.c"
#include "../stage/gfx/lens_flare.c"

#include "../stage/gfx/interp.c"
#include "../stage/gfx/interp38b.c"

#include "../stage/gfx/scratch.c"
#include "../stage/gfx/track.c"
#include "../stage/world/world_query.c"

#include "../stage/core/cells.c"
#include "../stage/core/stage_main.c"
#include "../stage/core/stage_loop.c"
#include "../stage/debug/debug_menu.c"
#include "../stage/debug/debug_print.c"
#include "../stage/core/part.c"
#include "../stage/tables/name_table_base.c"
#include "../stage/tables/name_load.c"
#include "../stage/core/stage_data.c"

#include "../stage/core/pause_reset.c"
#include "../stage/core/pause.c"

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
