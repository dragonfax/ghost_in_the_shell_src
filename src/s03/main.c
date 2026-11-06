#include "common.h"
#define STAGE 3
#define STAGE_ASM "../asm/s03/nonmatchings/main"
#include "stage.h"
#include "s03_types.h"
#include "sounds.h"
#include "gte.h"

#include "../stage/sys/svc.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. In the original they are their own object, after the engine's file_write_named. */
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

extern s32 alert_flag, pursue_flag, orbit_flag, enemies_remaining, cam_timer;
extern s32 D_8011FEAC, turn_flag, orbit_flag, enemies_remaining, cam_timer;
extern s32 D_8011FEAC, pursue_flag, orbit_flag, enemies_remaining, cam_timer;
extern s32 D_8011FEAC, pursue_flag, orbit_flag, enemies_remaining, cam_timer;
extern s32 D_8011FEAC, pursue_flag, orbit_flag, mission_enemies_left, cam_timer;
extern GridEntry *flagged_grid_cells[];
extern u8 cam_hurry_blend[8];  /* byte table, 0x10 each */
extern u8 msg_active_flag[20]; /* byte table, descending 7..0 steps */
extern s32 msg_text_id, cam_pursue_blend, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_side_blend, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_pursue_blend, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_pursue_blend, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, D_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s16 msg_pos_x, msg_pos_y;
extern s16 msg_pos_x, msg_pos_y;
extern s32 msg_text_id, cam_pursue_blend, msg_fade, cam_spin_step;
extern s32 cam_orbit_angle, d_8011FEE4, D_8011FEE8, D_8011FEA8;
extern s32 cam_orbit_angle, D_8011FEE4, D_8011FEE8, grid_flagged_count;
extern s32 cam_orbit_angle, D_8011FEE4, timer_warn_shown, D_8011FEA8;
void cam_update_phase2();
void hud_frame_draw();
#include "../stage/mission/mission_state.c"
#include "../stage/object/slot_list.c"
#include "mission/stage_controller.c"

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

void obj_offset_to_world_shifted(Object *obj, s32 *out);
extern s32 shot_params_b;
#include "../stage/enemy/enemy_ai.c"

#include "../stage/enemy/enemy.c"

#include "../stage/enemy/gun_turret_2.c"

#include "../stage/enemy/enemy_sounds.c"

#include "../stage/enemy/enemy_ops.c"
#include "../stage/enemy/helicopter2.c"

#include "../stage/enemy/enemy_aim.c"
#include "world/time_bomb.c"

#include "../stage/enemy/ripple.c"

#include "enemy/enemy.c"
#include "combat/bazooka_rocket.c"

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

#include "../stage/eng_fn_800c4368.c"

void obj_noop_update(void) {
}

#include "../stage/eng_fn_800c5ab8.c"

#include "../stage/eng_fn_800c5b9c.c"

#include "../stage/eng_fn_800c5bbc.c"
#include "combat/respawn.c"

#include "../stage/lib/libc/printf.c"
#include "../stage/lib/libgte/square_root0.c"
#include "../stage/lib/libgte/trans_matrix.c"
#include "../stage/lib/libgte/set_rot_matrix.c"
#include "../stage/lib/libgte/set_trans_matrix.c"
#include "lib/floatsidf.c"
#include "lib/fltsidf.c"
#include "lib/dbl_shift_us.c"
#include "lib/dbshiftu.c"
#include "lib/ltdf2.c"
#include "../stage/lib/libgcc/ltdf2_obj.c"
#include "../stage/sys/lz.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/lib/libgte/vector_normal.c"
#include "../stage/math/gte_helper.c"
#include "../stage/lib/libgte/matrix_normal.c"

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
#include "../stage/lib/libgte/gte_misc.c"
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
