#include "common.h"
#define STAGE 12
#include "stage.h"
#include "s12_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. */
const char file_ohel_tp1_clt[] = "ohel_tp1.clt";
const char file_ohel_tp0_clt[] = "ohel_tp0.clt";
const char file_ohel_ch0_clt[] = "ohel_ch0.clt";
const char file_ohel_tp1_xs3[] = "ohel_tp1.xs3";
const char file_ohel_tp0_xs3[] = "ohel_tp0.xs3";
const char file_ohel_ch0_vx1[] = "ohel_ch0.vx1";
const char file_ohel_ch0_cb4[] = "ohel_ch0.cb4";
const char file_hou1_tp0_clt[] = "hou1_tp0.clt";
const char file_hou1_ch0_clt[] = "hou1_ch0.clt";
const char file_hou1_tp0_xs3[] = "hou1_tp0.xs3";
const char file_hou1_ch0_vx1[] = "hou1_ch0.vx1";
const char file_hou1_ch0_cb4[] = "hou1_ch0.cb4";
const char file_arkb_tp0_clt[] = "arkb_tp0.clt";
const char file_arkb_ch0_clt[] = "arkb_ch0.clt";
const char file_arkb_tp0_xs3[] = "arkb_tp0.xs3";
const char file_arkb_ch0_vx1[] = "arkb_ch0.vx1";
const char file_arkb_ch0_cb4[] = "arkb_ch0.cb4";
const char file_bal2_tp0_clt[] = "bal2_tp0.clt";
const char file_bal2_ch0_clt[] = "bal2_ch0.clt";
const char file_bal2_tp0_xs3[] = "bal2_tp0.xs3";
const char file_bal2_ch0_vx1[] = "bal2_ch0.vx1";
const char file_bal2_ch0_cb4[] = "bal2_ch0.cb4";
const char file_msub_tp0_clt[] = "msub_tp0.clt";
const char file_msub_ch0_clt[] = "msub_ch0.clt";
const char file_msub_tp0_xs3[] = "msub_tp0.xs3";
const char file_msub_ch0_vx1[] = "msub_ch0.vx1";
const char file_msub_ch0_cb4[] = "msub_ch0.cb4";
const char file_jira_tp0_clt[] = "jira_tp0.clt";
const char file_jira_ch0_clt[] = "jira_ch0.clt";
const char file_jira_tp0_xs3[] = "jira_tp0.xs3";
const char file_jira_ch0_vx1[] = "jira_ch0.vx1";
const char file_jira_ch0_cb4[] = "jira_ch0.cb4";
const char file_dorc_ch0_cb4[] = "dorc_ch0.cb4";
const char file_bosc_tp1_clt[] = "bosc_tp1.clt";
const char file_bosc_tp0_clt[] = "bosc_tp0.clt";
const char file_bosc_ch0_clt[] = "bosc_ch0.clt";
const char file_bosc_tp1_xs3[] = "bosc_tp1.xs3";
const char file_bosc_tp0_xs3[] = "bosc_tp0.xs3";
const char file_bosc_ch4_vx1[] = "bosc_ch4.vx1";
const char file_bosc_ch3_vx1[] = "bosc_ch3.vx1";
const char file_bosc_ch2_vx1[] = "bosc_ch2.vx1";
const char file_bosc_ch1_vx1[] = "bosc_ch1.vx1";
const char file_bosc_ch0_vx1[] = "bosc_ch0.vx1";
const char file_bosc_ch3_cb4[] = "bosc_ch3.cb4";
const char file_bosc_ch2_cb4[] = "bosc_ch2.cb4";
const char file_bosc_ch1_cb4[] = "bosc_ch1.cb4";
const char file_bosc_ch0_cb4[] = "bosc_ch0.cb4";

#include "../stage/enemy/ripple.c"

#include "../stage/enemy/pos_distance.c"

#include "../stage/enemy/enemy_ops.c"

#include "../stage/enemy/helicopter.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/enemy/gun_turret.c"

#include "../stage/enemy/fuchikoma_b.c"

#include "../stage/enemy/script_radius_jumps.c"

#include "../stage/enemy/script_reads.c"
#include "enemy/timer_tail.c"

#include "../stage/enemy/smg_soldier.c"

#include "../stage/enemy/enemy.c"

extern s16 placed_actor_script[];
extern s16 *placed_actor_script_value[];
void obj_proximity_phase0(Object *obj);
void obj_script_update(Object *obj, ObjHandler *handler);
void placed_actor_draw(Object *obj, ObjHandler *handler);
s32 obj_effect_update(Object *obj);
extern s32 proximity_asset[3];
extern StateEntry placed_actor_states[1];
#include "../stage/object/placed_actor.c"
#include "world/proximity_sensor.c"
#include "boss/supermech.c"

#include "enemy/obj_init_common.c"

#include "math/vec_from_polar.c"

#include "../stage/enemy/hit_reaction.c"

#include "../stage/enemy/giant_robot.c"

#include "enemy/facing.c"

#include "../stage/gfx/clip_poly.c"
#include "enemy/aim_helpers.c"

#include "../stage/enemy/giant_robot_fx.c"
#include "enemy/giant_robot_fx_part2.c"
#include "core/stage.c"

extern s32 alert_flag, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, turn_flag, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, D_8011FEB8, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, mission_enemies_left, cam_timer;
extern GridEntry *flagged_grid_cells[];
extern s32 msg_text_id, D_8011FED0, msg_fade, cam_spin_step;
extern ScriptStep rooftop_supermech_m12_final_boss_anim_recover_hold[2], rooftop_supermech_m12_final_boss_anim_turn_recover[17]; /* script step lists in supermech_script_entry */
extern s32 msg_text_id, cam_side_blend, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FED0, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, D_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s16 msg_pos_x, msg_pos_y;
extern s16 msg_pos_x, msg_pos_y;
extern s32 msg_text_id, D_8011FED0, msg_fade, cam_spin_step;
extern s32 D_8011FEDC, d_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s32 D_8011FEDC, D_8011FEE4, D_8011FEE8, grid_flagged_count;
extern s32 D_8011FEDC, D_8011FEE4, timer_warn_shown, D_8011FEA8;
void cam_update_phase2();
void hud_frame_draw();
#include "../stage/mission/mission_state.c"
#include "mission/key_cells.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"
#include "../stage/sys/lz.c"

#include "../stage/sys/vsync.c"

#include "../stage/sys/pad_input.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

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

#include "../stage/core/pause_reset.c"
#include "../stage/core/pause.c"

#include "../stage/core/cells.c"
#include "../stage/core/stage_main.c"
#include "../stage/core/stage_loop.c"
#include "../stage/debug/debug_menu.c"
#include "../stage/debug/debug_print.c"
#include "../stage/core/part.c"
#include "../stage/tables/name_table_base.c"
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
