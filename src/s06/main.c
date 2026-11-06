#include "common.h"
#define STAGE 6
#define STAGE_ASM "../asm/s06/nonmatchings/main"
#include "stage.h"
#include "s06_types.h"
#include "sounds.h"

#include "../stage/sys/svc.c"
#include "../stage/sys/file_heap.c"
#include "enemy/motorcycle.c"

/* Writes a position offset to out: a fixed vector turned by the object's yaw and pitch, plus its position. */
void obj_mount_pos(Object *obj, Vec3 *out) {
    s32 delta_x;
    s32 delta_y;
    s32 delta_z;

    out->y = -0xC2;
    out->x = 0;
    out->z = -0x48;
    rotate_xz_twice(obj->yaw + obj->vars.flier.floor_slope, obj->pitch, &out->x, &out->y, &out->z);
    delta_x = 0x12;
    delta_y = 0;
    delta_z = 0xAF;
    rotate_xz_twice(obj->vars.words[3] + obj->vars.flier.floor_slope, obj->vars.flier.pitch & 0xFFF, &delta_x, &delta_y, &delta_z);
    out->x = (obj->x >> 12) + delta_x + out->x;
    out->y = (obj->y >> 12) + delta_y + out->y;
    out->z = (obj->z >> 12) + delta_z + out->z;
}

void dir_to_angles_clamped(Vec3 *dir, SVECTOR *out);
/* Runs two helpers, then turns the object's two angles at 0x258 and 0x254 toward the two angles
   of rot by 0x10 per call. */
void obj_turn_to_angles(Object *obj, Vec3 *dir, SVECTOR *rot) {
    obj_mount_pos(obj, dir);
    dir_to_angles_clamped(dir, rot);
    obj->vars.flier.pitch = angle_approach(obj->vars.flier.pitch, rot->vx, 0x10);
    obj->vars.words[3] = angle_approach(obj->vars.words[3], rot->vy, 0x10);
}

#include "../stage/eng_fn_800ba06c.c"

void enemy_fire_fx(Object *obj) {
    Vec3 pos;
    SVECTOR rot;
    s32 handle;
    s32 rnd;
    u16 base;

    obj_turn_to_angles(obj, &pos, &rot);
    rot.vy = (obj->vars.words[3] + rand_a_next() % 24) - 0xC;
    rnd = rand_a_next();
    base = rot.vx;
    base -= 0xC;
    rot.vx = base + rnd % 24;
    if (*(u8 *)&obj->vars.enemy.shot_timer == 0) {
        handle = sound_start(SND_HEAVY_MACHINE_GUN_FIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, 0);
        *(u8 *)&obj->vars.enemy.shot_timer = handle;
    }
    shot_spawn_obj((s32 *)&pos, (u16 *)&rot, 1, ((s32) obj->damage << 16) | 1);
}

void burst_enemy_shoot(Object *obj) {
    s32 origin[4];
    s32 pos[3];
    SVECTOR spread;
    u8 *slot;
    s32 handle;
    s32 rnd;
    u16 base;

    obj_turn_to_angles(obj, (Vec3 *)origin, &spread);
    spread.vy = obj->vars.words[3] + rand_a_next() % 24 - 0xC;
    rnd = rand_a_next();
    base = spread.vx - 0xC;
    spread.vx = base + (rnd % 24);
    pos[0] = obj->vx >> 12;
    pos[1] = obj->vy >> 12;
    pos[2] = obj->vz >> 12;
    slot = (u8 *) &obj->vars.enemy.shot_timer;
    if (*slot == 0) {
        handle = sound_start(SND_HEAVY_MACHINE_GUN_FIRE | SND_HELD | SND_GROUP(1), 0x60, 0, 0);
        sound_attach(handle, &obj->x, 0);
        *slot = handle;
    }
    shot_spawn_target(origin, (u16 *)&spread, pos, 1, (obj->damage << 16) | 1);
}

void burst_enemy_shoot(Object *obj);
/* Burst enemy step: turns toward the target, fires a burst of shots, then pauses before re-arming.
   handler->result: -2 re-arms, -1 starts the pause, 1 keeps firing. */
void enemy_burst_update(Object *obj, ObjHandler *handler) {
    Vec3 dir;
    SVECTOR rot;
    u8 timer;

    obj_turn_to_angles(obj, &dir, &rot);
    switch (handler->result) {
    case -2:
        handler->result = 1;
        obj->vars.burst_enemy.fire_gap = 0;
        obj->vars.burst_enemy.shots_left = (u8)(rand_a_next() % 8 + 4);
        obj->vars.burst_enemy.pause_timer = (u8)(rand_a_next() % 48 + 0x18);
        return;
    case -1:
        timer = obj->vars.burst_enemy.pause_timer;
        obj->vars.burst_enemy.pause_timer = (u8)(timer + 0xFF);
        if (timer != 0) {
            if (obj->vars.burst_enemy.sound != 0) {
                sound_stop(obj->vars.burst_enemy.sound);
                obj->vars.burst_enemy.sound = 0;
            }
            return;
        }
        handler->result = -2;
        if (obj->vars.burst_enemy.sound != 0) {
            sound_stop(obj->vars.burst_enemy.sound);
            obj->vars.burst_enemy.sound = 0;
        }
        return;
    default:
        if (obj->vars.burst_enemy.player_distance >= 0x801) {
            if (obj->vars.burst_enemy.sound != 0) {
                sound_stop(obj->vars.burst_enemy.sound);
                obj->vars.burst_enemy.sound = 0;
            }
            return;
        }
        if (obj->vars.burst_enemy.shots_left == 0) {
            handler->result = -1;
            return;
        }
        if (obj->vars.burst_enemy.fire_gap++ >= 4) {
            obj->vars.burst_enemy.fire_gap = 0;
            obj->vars.burst_enemy.shots_left--;
            burst_enemy_shoot(obj);
        }
        handler->result = 1;
        return;
    }
}

#include "../stage/eng_fn_800ba504.c"

#include "../stage/enemy/ripple.c"

#include "../stage/enemy/pos_distance.c"

#include "../stage/enemy/enemy_ops.c"
#include "enemy/script_jump_table.c"

#include "../stage/enemy/flier.c"
#include "enemy/helicopter.c"

#include "../stage/enemy/enemy_aim.c"
#include "enemy/minicopter.c"

#include "../stage/eng_fn_800bf13c.c"

s32 obj_dist_to_target(Object *obj);
#include "../stage/eng_fn_800bf8b4.c"

void obj_yaw_step(Object *obj);
void obj_sound2_start(Object *obj);
#include "../stage/eng_fn_800c00f4.c"

#include "../stage/eng_fn_800c0144.c"

s32 shot_spawn_trace(Vec3 *pos, SVECTOR *rot, s32 kind);
#include "../stage/eng_fn_800c05b8.c"

void obj_muzzle_effect(Object *obj);
#include "../stage/eng_fn_800c0708.c"

#define FLOW(obj) ((Flow *)&(obj)->vars)
#include "../stage/eng_fn_800c0764.c"

extern s32 tank2_asset[3];
extern s32 model_pchr_saved;
#include "../stage/eng_fn_800c0e88.c"

#include "../stage/eng_fn_800c12c0.c"
#include "world/road_barrier.c"

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
#include "boss/semi_truck_mech.c"

#include "enemy/part_extents.c"

#include "math/vec_from_polar.c"

#include "../stage/enemy/hit_reaction.c"

#include "../stage/enemy/giant_robot.c"

#include "enemy/hit_reaction.c"

#include "gfx/pchr_angle_span.c"
#include "boss/semi_truck_mech_parts.c"
#include "../stage/world/exit_doors.c"
#include "enemy/part_attach.c"

#include "../stage/enemy/giant_robot_fx.c"
#include "combat/fx_frame.c"

#include "../stage/lib/libc/printf.c"
#include "../stage/lib/libgte/square_root0.c"
#include "../stage/lib/libgte/trans_matrix.c"
#include "../stage/lib/libgte/set_rot_matrix.c"
#include "../stage/lib/libgte/set_trans_matrix.c"
#include "math/ratan2.c"
#include "../stage/math/ratan_obj.c"
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
