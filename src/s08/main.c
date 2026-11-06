#include "common.h"
#define STAGE 8
#include "stage.h"
#include "s08_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"
#include "sys/svc_part1.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. */
const char file_sel2_tp0_clt[] = "sel2_tp0.clt";
const char file_sel2_ch0_clt[] = "sel2_ch0.clt";
const char file_sel2_tp0_xs3[] = "sel2_tp0.xs3";
const char file_sel2_ch0_vx1[] = "sel2_ch0.vx1";
const char file_sel2_ch0_cb4[] = "sel2_ch0.cb4";
const char file_msub_tp0_clt[] = "msub_tp0.clt";
const char file_msub_ch0_clt[] = "msub_ch0.clt";
const char file_msub_tp0_xs3[] = "msub_tp0.xs3";
const char file_msub_ch0_vx1[] = "msub_ch0.vx1";
const char file_msub_ch0_cb4[] = "msub_ch0.cb4";
const char file_stk2_tp0_clt[] = "stk2_tp0.clt";
const char file_stk2_ch0_clt[] = "stk2_ch0.clt";
const char file_stk2_tp0_xs3[] = "stk2_tp0.xs3";
const char file_stk2_ch0_vx1[] = "stk2_ch0.vx1";
const char file_stk2_ch0_cb4[] = "stk2_ch0.cb4";
const char file_maxe_tp1_clt[] = "maxe_tp1.clt";
const char file_maxe_tp0_clt[] = "maxe_tp0.clt";
const char file_maxe_ch0_clt[] = "maxe_ch0.clt";
const char file_maxe_tp1_xs3[] = "maxe_tp1.xs3";
const char file_maxe_tp0_xs3[] = "maxe_tp0.xs3";
const char file_maxe_ch0_vx1[] = "maxe_ch0.vx1";
const char file_maxe_ch0_cb4[] = "maxe_ch0.cb4";
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

#include "../stage/enemy/pos_distance.c"

#include "../stage/enemy/enemy_ops.c"
#include "enemy/laser_drone.c"

#include "../stage/enemy/enemy.c"
#include "../stage/math/angle_clamp.c"

#include "../stage/enemy/smg_soldier.c"
#include "enemy/stationary_rocket_launcher_2.c"

#include "../stage/enemy/enemy_aim.c"

extern s32 alert_flag, D_8011FEB0, orbit_flag, enemies_left, cam_timer;
extern s32 hurry_flag, turn_flag, orbit_flag, enemies_left, cam_timer;
extern s32 hurry_flag, D_8011FEB0, orbit_flag, enemies_left, cam_timer;
extern s32 hurry_flag, D_8011FEB0, orbit_flag, enemies_left, cam_timer;
extern s32 hurry_flag, D_8011FEB0, orbit_flag, mission_enemies_left, cam_timer;
extern GridEntry *flagged_grid_cells[];
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, cam_side_blend, D_8011FED0, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, D_8011FEE4, hurry_msg_flag, D_8011FEA8;
extern s16 msg_pos_x, msg_pos_y;
extern s16 msg_pos_x, msg_pos_y;
extern s32 msg_text_id, D_8011FECC, D_8011FED0, msg_fade, cam_spin_step;
extern s32 D_8011FEDC, d_8011FEE4, hurry_msg_flag, D_8011FEA8;
extern s32 D_8011FEDC, D_8011FEE4, hurry_msg_flag, grid_flagged_count;
extern s32 D_8011FEDC, D_8011FEE4, timer_warn_shown, D_8011FEA8;
void cam_update_phase2();
void hud_frame_draw();
#include "../stage/mission/mission_state.c"
#include "core/grid_flagged.c"

void night_vision_ramp(void);
void night_vision_draw(void);
extern s32 night_vision_level;
extern s32 night_vision_target;
extern s32 night_vision_copy_flag;
extern s32 night_vision_active;
#include "../stage/gfx/night_vision.c"
#include "core/stage.c"

#include "../stage/enemy/script_reads.c"
#include "boss/quick_fuchikoma_weapons.c"

#include "../stage/sound/obj_sound2.c"
#include "combat/projectiles.c"

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

extern RecTemplate fx_owner_template_a;
extern RecTemplate fx_owner_template_b;
void obj_spawn_with_two_fx(void *owner, void *pos, s32 index) {
    fx_spawn_template(owner, &fx_owner_template_a, 0);
    fx_spawn_template(owner, &fx_owner_template_b, 0);
    object_spawn_at(owner, pos, index);
    sound_play(SND_LARGE_EXPLOSION | SND_GROUP(1), 0x64, 0xC0, 0x30);
    sound_play(SND_MEDIUM_EXPLOSION | SND_GROUP(1), 0x64, 0x3F, 0x30);
}

static inline void rot_to_world(volatile s32 *m, s32 *v) {
    s32 a = m[0], b = m[1], c = m[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = m[3];
    b = m[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    gte_set_ctrl(TRX, 0);
    gte_set_ctrl(TRY, 0);
    gte_set_ctrl(TRZ, 0);
    gte_load(IR1, v, 0);
    gte_load(IR2, v, 4);
    gte_load(IR3, v, 8);
    gte_rtirtr();
    gte_store(MAC1, v, 0);
    gte_store(MAC2, v, 4);
    gte_store(MAC3, v, 8);
}
static inline BossDeathVars *E(Object *o) {
    return (BossDeathVars *)o;
}
void boss_death_update(Object *obj) {
    s32 rx, ry, rz;
    s32 t, sel;
    s16 *rot;

    switch (E(obj)->state) {
    case 1:
        t = E(obj)->timer;
        if (t % 3 == 0) {
            s32 *v;
            rx = obj->width;
            ry = (s16)obj->height;
            rz = obj->unk_1E8[0];
            rx = rx * (rand_a_next() - 0x800) / 4096;
            ry = ry * (rand_a_next() - 0x800) / 4096;
            rz = rz * (rand_a_next() - 0x800) / 4096;
            ry -= (s16)obj->height / 2 + (s16)obj->height / 4;
            v = (s32 *)scratch_top;
            scratch_top += 0x10;
            v[0] = rx;
            v[1] = ry;
            v[2] = rz;
            rot_to_world(world_matrix_get(), v);
            v[0] += obj->x >> 12;
            v[1] += obj->y >> 12;
            sel = t - t / 6 * 6 == 0;
            spawn_effect(v[0], v[1], v[2] += obj->z >> 12, (sel << 1) + 0x7F00 | 0x80000000);
            scratch_top -= 0x10;
        }
        E(obj)->timer++;
        if (E(obj)->timer >= 0x3C) {
            E(obj)->state = 2;
            E(obj)->timer = 0;
        }
        break;
    case 2:
        E(obj)->timer++;
        if (E(obj)->timer >= 0xC) {
            s32 *v;
            v = (s32 *)scratch_top;
            scratch_top += 0x10;
            v[0] = 0;
            v[1] = -(s16)obj->height / 2;
            v[2] = 0;
            rot_to_world(world_matrix_get(), v);
            v[0] += obj->x >> 12;
            v[1] += obj->y >> 12;
            v[2] += obj->z >> 12;
            effect_spawn_at_pos(v);
            scratch_top -= 0x10;
            E(obj)->state = 3;
            E(obj)->timer = 0;
        }
        break;
    case 4:
        E(obj)->state = 5;
        E(obj)->timer = 0;
        break;
    case 5:
        E(obj)->timer++;
        if (E(obj)->timer >= 6) {
            E(obj)->state = 6;
            E(obj)->timer = 0;
        }
        break;
    case 6: {
        s32 *v = (s32 *)scratch_top;
            scratch_top += 0x10;
        rot = scratch_alloc(8);
        v[0] = 0;
        v[1] = -(s16)obj->height / 2;
        v[2] = 0;
        rot_to_world(world_matrix_get(), v);
        v[0] += obj->x >> 12;
        v[1] += obj->y >> 12;
        v[2] += obj->z >> 12;
        rot[0] = obj->pitch;
        rot[1] = obj->yaw;
        rot[2] = obj->roll;
        obj_spawn_with_two_fx(v, rot, E(obj)->fx_arg);
        v[0] = obj->x >> 12;
        v[1] = obj->y >> 12;
        v[2] = obj->z >> 12;
        effect_spawn_plain(v);
        scratch_top -= 0x18;
        E(obj)->state = 7;
        break;
    }
    case 7:
        E(obj)->timer++;
        if (E(obj)->timer >= 0xD2) {
            set_stage_end(2);
            E(obj)->state = 8;
        }
        break;
    }
}

void obj_noop_update(void) {
}

#include "../stage/eng_fn_800c5ab8.c"

#include "../stage/eng_fn_800c5b9c.c"

#include "../stage/eng_fn_800c5bbc.c"

#include "../stage/sys/arena.c"
#include "../stage/gfx/frame.c"
#include "../stage/sys/lz.c"

#include "../stage/sys/vsync.c"

#include "../stage/math/rand_init.c"
#include "../stage/math/math.c"

#include "../stage/sys/pad_input.c"

#include "../stage/gfx/cam_view_reset.c"
#include "../stage/gfx/view.c"

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
#include "../stage/combat/particles.c"
#include "../stage/world/wall_query.c"
#include "../stage/player/player_flags.c"
#include "../stage/camera/camera_follow.c"
#include "../stage/object/mover.c"
