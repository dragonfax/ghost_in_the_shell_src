#include "common.h"
#define STAGE 13
#include "stage.h"
#include "s13_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. */
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

extern s32 alert_flag, D_8011FEB0, orbit_flag, ammo_count, cam_timer;
extern s32 D_8011FEAC, turn_flag, orbit_flag, ammo_count, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, ammo_count, cam_timer;
extern s32 D_8011FEAC, D_8011FEB0, orbit_flag, ammo_count, cam_timer;
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
#include "../stage/object/slot_list.c"
#include "core/stage.c"

#include "../stage/eng_fn_800c5620.c"

extern RecTemplate fade_red_fx_template;
void fade_red_update();
/* Starts a record from the template D_8011E054 with fade_red_update as its callback; pos is passed through. */
s32 effect_spawn_at_pos(s32 *pos) {
    return fx_spawn_template(pos, &fade_red_fx_template, fade_red_update);
}

void obj_noop_hook(void) {
}

extern FxRecordParams fx_rec34_params;
/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at D_80118754 and no extra argument. */
void effect_spawn_plain(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}

extern RecTemplate D_801177C8, D_801177E0, fx_owner_template_a, D_8011873C;
extern RecTemplate D_801177C8, D_801177E0, D_80118724, fx_owner_template_b;
#include "../stage/eng_fn_800c571c.c"

char str_targ_tp0_clt[16] = "TARG_tp0.clt";

char str_targ_ch0_clt[16] = "TARG_ch0.clt";

char str_targ_tp0_xs3[16] = "TARG_tp0.xs3";

char str_targ_ch0_vx1[16] = "TARG_ch0.vx1";

char str_targcb0cb4[16] = "TARG_cb0.cb4";

char str_bosd_tp1_clt[16] = "bosd_tp1.clt";

char str_bosd_tp0_clt[16] = "bosd_tp0.clt";

char str_bosd_ch0_clt[16] = "bosd_ch0.clt";

char str_bosd_tp1_xs3[16] = "bosd_tp1.xs3";

char str_bosd_tp0_xs3[16] = "bosd_tp0.xs3";

char str_bosd_ch1_vx1[16] = "bosd_ch1.vx1";

char str_bosd_ch0_vx1[16] = "bosd_ch0.vx1";

char str_bosd_ch0cb4[16] = "bosd_ch0.cb4";

#define fade_red_start_at effect_spawn_at_pos
#define fx_rec34_spawn_pos effect_spawn_plain
#include "../stage/eng_fn_800c57b4.c"
#undef fade_red_start_at
#undef fx_rec34_spawn_pos

void obj_noop_update(void) {
}

#include "../stage/eng_fn_800c5ab8.c"

#include "../stage/eng_fn_800c5b9c.c"

#include "../stage/eng_fn_800c5bbc.c"
#include "combat/effects.c"

#include "../stage/sys/lz.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

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
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
