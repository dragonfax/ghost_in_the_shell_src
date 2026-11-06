#include "common.h"
#define STAGE 1
#define STAGE_ASM "../asm/s01/nonmatchings/main"
#include "s01.h"
#include "s01_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"
#include "enemy/keyholder_fuchikoma.c"

#include "../stage/enemy/smg_soldier.c"

#include "../stage/enemy/enemy.c"

#include "../stage/eng_fn_800bb148.c"

#include "../stage/eng_fn_800bb338.c"

#include "../stage/eng_fn_800bb3a0.c"

#include "../stage/eng_fn_800bb6a4.c"

#include "../stage/eng_fn_800bb95c.c"

#include "../stage/eng_fn_800bbb78.c"

#include "../stage/eng_fn_800bc098.c"

#include "../stage/enemy/ripple.c"

#include "../stage/enemy/pos_distance.c"

#include "../stage/enemy/enemy_ops.c"

#include "../stage/enemy/helicopter.c"

#include "../stage/enemy/enemy_aim.c"

#include "../stage/mission/mission_state.c"
#include "mission/key_table.c"

#include "../stage/camera/stage_camera.c"
#include "../stage/world/exit_doors.c"

#include "../stage/enemy/script_ops.c"

#include "../stage/enemy/giant_robot.c"

#include "../stage/enemy/giant_robot_fx.c"
#include "enemy/giant_robot_systems.c"

#include "../stage/enemy/hit_reaction.c"

#include "gfx/screen_fade.c"
#include "../stage/combat/shots.c"
#include "enemy/boss_systems.c"

#include "../stage/eng_fn_800c5620.c"

/* Registers fade_red_update for arg with fade_red_fx_template, then plays sound 0x3003 at arg (sound_play_at). */
void fade_red_start_at(void *arg0) {
    fx_spawn_template(arg0, &fade_red_fx_template, fade_red_update);
    sound_play_at_units(0x3003, 0x7F, 0x3C, arg0);
}

void obj_noop_hook(void) {
}

/* Runs fx_rec34_spawn_cb on `pos` with the parameter block at fx_rec34_params and no extra argument. */
void fx_rec34_spawn_pos(s32 *pos) {
    fx_rec34_spawn_cb(pos, &fx_rec34_params, 0);
}

#include "../stage/eng_fn_800c571c.c"

#include "../stage/eng_fn_800c57b4.c"

void obj_noop_update(void) {
}

#include "../stage/eng_fn_800c5ab8.c"

#include "../stage/eng_fn_800c5b9c.c"

#include "../stage/eng_fn_800c5bbc.c"

#include "../stage/lib/libc/printf.c"
#include "../stage/lib/libgte/square_root0.c"
#include "../stage/lib/libgte/trans_matrix.c"
#include "../stage/lib/libgte/set_rot_matrix.c"
#include "../stage/lib/libgte/set_trans_matrix.c"
#include "../stage/sys/lz.c"

#include "../stage/sys/pad_input.c"

#include "../stage/sys/vsync.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/lib/libgte/vector_normal.c"
#include "../stage/math/gte_helper.c"
#include "../stage/lib/libgte/matrix_normal.c"

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
#include "../stage/lib/libgte/gte_misc.c"
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
