#include "common.h"
#define STAGE 2
#define STAGE_ASM "../asm/s02/nonmatchings/main"
#include "stage.h"
#include "s02_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"

#include "../stage/sys/start.c"
#include "../stage/sys/file_heap.c"

/* The stage's model and message files: data tables point to them by address. In the original they are their own object, after the engine's file_write_named. */
const char file_msgs_spr_so3[] = "msgs_spr.so3";
const char file_msgs_spr_grc[] = "msgs_spr.grc";
const char file_msgs_spr_clt[] = "msgs_spr.clt";

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

extern GridEntry *flagged_grid_cells[];
/* Same code as get_key_table (s01). */
GridEntry **func_800B7EE8(void) {
    return flagged_grid_cells;
}

extern s32 grid_flagged_count;

s32 func_800B7EF8(void) {
    return grid_flagged_count;
}

#include "../stage/enemy/beam_enemy.c"

#include "../stage/enemy/enemy.c"

#include "../stage/enemy/pos_distance.c"

#include "../stage/enemy/enemy_ops.c"
#include "enemy/script_jump_table.c"
#include "../stage/enemy/rocket_drone.c"

#include "../stage/enemy/gun_turret_2.c"

#include "../stage/enemy/enemy_aim.c"

extern u8 sea_mine_script[];
extern s16 *sea_mine_script_arg[];
extern void sea_mine_trigger();
extern void sea_mine_update();
void sea_mine_draw(Object *obj, ObjHandler *handler);
s32 sea_mine_frame_callback(Object *obj);
extern u8 sea_mine_asset[];
extern StateEntry d_80116F10[];
#include "../stage/enemy/sea_mine.c"

extern s16 placed_actor_script[];
extern s16 *placed_actor_script_value[];
void obj_proximity_phase0(Object *obj);
void obj_script_update(Object *obj, ObjHandler *handler);
void placed_actor_draw(Object *obj, ObjHandler *handler);
s32 obj_effect_update(Object *obj);
extern s32 proximity_asset[3];
extern StateEntry placed_actor_states[1];
#include "../stage/object/placed_actor.c"

#include "boss/tunnel_mech.c"

#include "../stage/gfx/clip_poly.c"
#include "enemy/tunnel_mech_weapons.c"

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

void spark_record_draw(Object *obj) {
    s32 pos[3];
    u16 rot[3];
    s32 value, px, py, pz;
    u16 r0, r1, r2;
    s32 n;
    s32 colour;
    SparkRec *s;
    SparkList *list;
    u8 *tail;

    if (obj->vars.words[1] < 7) {
        px = obj->x >> 12;
        pos[0] = px;
        colour = 0x60C0FF;
        py = obj->vars.words[3] >> 12;
        pos[1] = py;
        pz = obj->z >> 12;
        pos[2] = pz;
        n = spark_count;
        r0 = obj->pitch;
        rot[0] = r0;
        r1 = obj->yaw;
        rot[1] = r1;
        list = &spark_list;
        r2 = obj->roll;
        rot[2] = r2;
        value = obj->vars.words[0];
        if (n < 0xFF) {
            s = &list->items[n];
            n++;
            spark_count = n;
            *(s32 *)s->colour = colour;
            tail = spark_list_tail;
            spark_list_tail = &s->next;
            *tail = n;
            s->next = 0;
            s->x = px;
            s->y = py;
            s->z = pz;
            s->unk_12 = value;
            s->yaw = r1;
            s->pitch = r0;
            s->roll = r2;
        }
    }
}

#include "../stage/eng_fn_800c5b9c.c"
#include "combat/spark_obj.c"

extern s32 night_vision_level;
extern s32 night_vision_target;
extern s32 night_vision_copy_flag;
extern s32 night_vision_active;
void night_vision_ramp(void);
void night_vision_draw(void);
#include "../stage/gfx/night_vision.c"
#include "mission/night_vision_flag.c"

#include "../stage/camera/cam_zone.c"
#include "camera/cam_zone.c"

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
