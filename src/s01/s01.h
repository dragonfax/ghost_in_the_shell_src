#ifndef S01_H
#define S01_H

/* Declarations for code only stage 1 has (src/s01/main.c). D_ names are S01 addresses. */

#include "stage.h"
#include "s01_types.h"

/* 12-byte records at sound_zones (one in S01), indexed by an object's vars.h.unk_248: a sound zone whose
 * loop sound plays while the player is near the object (key_code_exit_doors_phase0), and whose level fades in while near
 * and out otherwise (key_code_exit_doors_update). */
typedef struct SoundZone {
    s32 enabled;
    s32 near;  /* the player was in range last step */
    s16 level; /* 0..0x1000 (sound_zone_get_level gives 0x1000 out of range) */
    s16 step;
} SoundZone;
extern SoundZone sound_zones[1];


/* 16 records of 0x24 bytes at keyframe_slots. */
typedef struct KeyframeSlot {
    /* 0x00 */ void *owner;
    /* 0x04 */ u16 start[3];
    /* 0x0A */ u8 unk_0A[2];
    /* 0x0C */ s32 tick;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ struct Keyframe *keys;
    /* 0x18 */ u16 key_from;
    /* 0x1A */ u16 key_to;
    /* 0x1C */ u16 key_t;
    /* 0x1E */ s16 active; /* keyframe_step's result: 0 once the keys end */
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ u8 unk_22[2];
} KeyframeSlot;
extern KeyframeSlot keyframe_slots[16];

/* 40 spark burst sources (SparkBurst) at spark_burst_table, run by rec_list_run. */
extern SparkBurst spark_burst_table[40];

/* 4 records of 0x28 bytes at keyframe_ramp_recs. */
typedef struct KeyframeRamp {
    /* 0x00 */ void *owner;
    /* 0x04 */ u16 start[3]; /* point on the owner, for obj_point_to_world */
    /* 0x0A */ u8 unk_0A[0xA];
    /* 0x14 */ s32 tick;
    /* 0x18 */ struct Keyframe *keys;
    /* 0x1C */ u16 key_from; /* 0xA3 moves unk_24 up (keyframe_ramp_step) */
    /* 0x1E */ u16 key_to;
    /* 0x20 */ s16 key_t;
    /* 0x22 */ s16 active;   /* keyframe_step's result: nonzero while the keyframes run */
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26[2];
} KeyframeRamp;
extern KeyframeRamp keyframe_ramp_recs[4];

extern s16 shot_fire_timer;
extern s16 loop_state_active;
extern s16 *keyholder_fuchikoma_data[2]; /* script */

extern ShotParams shot_params;

/* The record sound_emitter_start starts a looping sound for. */
typedef struct SoundOwner {
    /* 0x00 */ s32 object;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 sound; /* handle from sound_start */
    /* 0x20 */ s32 pitch;
    /* 0x24 */ s32 volume;
} SoundOwner;
/* MAX(MIN(x, hi), lo) with MIN evaluated twice, the result held in register reg (giant_robot_sound_update) */
#define CLAMP_IN_REG(x, lo, hi, reg) ({ s32 _v = (x); register s32 _r asm(reg) = MIN(_v, hi); if (MIN(_v, hi) < (lo)) _r = (lo); _r; })
#define SOUND_LOOP_800C3A98 0x900B900C
#define SLOT_UNSET (-0x80) /* sound_loop_slot_a/sound_loop_slot_b with no slot */
extern SoundOwner sound_loop; /* sound_loop_start sets it up */
/* Its fields as the original code names them: separate globals (a struct shares one address load). */
extern s32 sound_loop_level, sound_loop_slot_a, sound_loop_intensity, sound_loop_slot_b, giant_robot_tick, sound_loop_handle, sound_loop_pitch, sound_loop_volume;
extern s32 giant_robot_on_flag;


/* A kind that keeps two sound handles in its vars block, at 0x268 and 0x26C (obj_sound_pair_stop). */
typedef struct SoundVars {
    /* 0x248 */ u8 unk_248[0x20];
    /* 0x268 */ s32 sound_a; /* stopped unconditionally */
    /* 0x26C */ s32 sound_b; /* 0 when not playing */
} SoundVars;

/* A script whose operand pointer is at 0x20 (script_op_set_target). */
typedef struct ObjScript {
    /* 0x00 */ u8 unk_00[0x20];
    /* 0x20 */ s16 *pc;
} ObjScript;

static inline s32 cap_200(s32 v) {
    if (v > 0x200) {
        v = 0x200;
    }
    return v;
}

extern Shot shot_slots[32];

/* 0x1C-byte records at seq_slots; the first word is a sequence pointer (giant_robot_draw). */
typedef struct Seq1C {
    s32 first;
    u8 unk_04[0x18];
} Seq1C;
extern Seq1C seq_slots[];
extern s32 giant_robot_aim_result, giant_robot_aim_x, giant_robot_aim_y, giant_robot_aim_z;
void enemy_turn_toward(Object *obj, s32 n);
s32 fade_colour_from_level(s32 value);
void obj_target_pchr_update();
void giant_robot_systems_draw(void);
extern u8 giant_robot_asset[]; /* giant_robot_spawn's assets and tables */
extern s16 *giant_robot_link_data[];
extern SoundVolume D_80117B30[];
extern StateEntry D_80118574[];
extern ScriptCallEntry giant_robot_call_table[42];
extern s32 giant_robot_sound_handle_a;
extern s32 giant_robot_sound_handle_b;
extern Keyframe shot_burst_keys[]; /* the burst (shot_trace) */
extern s32 ambient_sound_timer;
extern s32 D_8011FF00;
extern s32 fade_dir;
extern s32 sound_slot_pos, sound_slot_pos_y, sound_slot_pos_z;
extern VECTOR sound_slot_points[];
extern s16 giant_robot_sound_data_a[];
extern s16 giant_robot_sound_data_b[];
extern s32 giant_robot_damage_scale;   /* damage scale, 0x1000 = 1 */
extern s16 giant_robot_hit_factors[]; /* damage factor per hit type, 0x1000 = 1 */
extern s32 msg_slot_ids[12];
extern s32 msg_id_base;
extern RecTemplate fade_red_fx_template;

s16 angle_clamp_pitch(s32 angle);
void enemy_muzzle_shot(Object *obj);
void enemy_sense(Object *obj);
void enemy_hit_update(Object *obj);
void enemy_wait_step(Object *obj, ObjHandler *handler, s32 arg);
void enemy_wander_step(Object *obj, ObjHandler *handler);
s32 enemy_in_range(Object *obj, s32 a, s32 b);
void obj_sound_release(Object *obj);
void obj_hit_reaction(Object *obj, s32 arg);
s32 obj_hit_mask_avg(s32 type, s16 *factors);
void obj_set_hit_reaction(Object *obj, s32 arg);
void shot_update(Shot *rec);
void shot_draw(Shot *rec);
s32 trace_shot_segment(VECTOR *from, VECTOR *to, VECTOR *hit, s32 a, s32 b, s32 c);
void loop_state_sound_start(LoopState *state);
void shot_fire_sound_stop(void);
s32 sound_emitter_update(SoundEmitter *emitter, s32 handle);
s32 spark_burst_emit(SparkBurst *burst);
void rec_keyframe_step(KeyframeSlot *rec);
void keyframe_slot_emit_spark(KeyframeSlot *rec);
void keyframe_ramp_step(KeyframeRamp *rec);
void keyframe_ramp_emit_spark(KeyframeRamp *rec);
void fade_red_update();
void snd_wave_effect_spawn(Object *obj, s32 channel);
s32 obj_spawn_replacement(Object *src, s32 arg1);

/* Callees and globals of functions matched in batches 16-51 (still asm or unnamed). */
void sway_reset_params();
void enemy_wall_steer(Object *obj);
void sound_loop_stop(void);
void flag_set(void);
void state_stop(void);
void giant_robot_fx_tick(void);
s32 obj_sound_track(Object *obj, s32 arg);
void giant_robot_fx_sound_start(Object *obj);
void giant_robot_fx_set_active(s32 flag);
extern s32 giant_robot_fx_timer;
extern s32 giant_robot_fx_active;
extern s32 giant_robot_systems_active;
void giant_robot_side_fx_tick(void);
void giant_robot_spark_draw(void);
void keyframe_run_all(void);
void rec_list_update(void);
void keyframe_ramp_run_all(void);
void shot_draw_all(void);
void loop_state_spark_emit(void);
void fade_in_full(void);
void sound_loop_reset(s32 flag);
void keyframe_clear_all(void);
void keyframe_ramp_clear_all(void);
void shot_pool_clear(void);
void loop_state_init(void);
void obj_clear_target(void);
void giant_robot_fx_bind(s32 flag);
void fade_clear(void);
void sound_loop_clear(void);
void sway_stop(void);
void loop_state_stop(void);
void set_fade_full(void);
s32 sound_track_pos(Object **objp, s32 arg);
s32 sound_pair_update0(SoundPair *owner, s32 handle);
s32 sound_pair_update1(SoundPair *owner, s32 handle);
extern s32 sway_flag;
void rec_list_run(void);
extern s32 sway_rate;
extern s32 D_80121AF4;
extern s32 sway_phase;
void func_800C3E60(SoundPair *owner);

extern FxRecordParams fx_rec34_params; /* parameter block fx_rec34_spawn_pos passes to fx_rec34_spawn_cb */

/* S01 functions in C (scripts/s01_protos.py). */
void obj_aim_at_player();
void obj_script_set_selector();
void script_jump_table_match();
void keyholder_fuchikoma_phase0();
void obj_turn_to_aim();
void keyholder_fuchikoma_sound_tick();
void keyholder_fuchikoma_update();
void dir_to_angles_clamped();
void enemy_muzzle_pos();
void enemy_fire_burst();
void enemy_shoot_update();
void smg_soldier_update();
void enemy_destroy();
void vec3_to_angles();
void enemy_reset();
void enemy_script_start();
s32 obj_placement_angle();
s32 obj_placement_dist();
void enemy_turn_toward_wobble();
void enemy_move_or_wait();
void enemy_wait_switch();
void enemy_hit_knockback();
void params_set_defaults();
void obj_read_s32();
void obj_face_player();
void rocket_fuchikoma_phase0();
void rocket_fuchikoma_turn();
void obj_settle_offset();
void obj_countdown_step();
void rocket_fuchikoma_update();
void script_read_speed_long();
void script_read_long();
void script_branch_on_flag();
void script_jump_if_not_below_speed();
s32 pos_distance();
void obj_set_next_state();
void script_set_turn_mode();
void script_op_jump_clear_flag();
void script_op_seek_target();
void enemy_fly_move();
void enemy_fly_aim();
void enemy_fly_approach();
void enemy_fly_spin();
void helicopter_phase2();
void obj_sound_pair_stop();
void obj_step_axes_toward();
s32 obj_player_in_arc();
void eng_set_mode();
void set_enemies_left();
void mission_state_set();
s32 msg_slot_to_id();
void msg_show_slot();
void func_800BF598();
void stage_camera_start();
void stage_camera_fade_in_step();
s32 * sound_position_for_slot();
void ambient_sound_tick();
void debug_toggle_rec();
void debug_draw_toggle();
void debug_step_selection();
void stage_pursue_draw();
void sound_zones_init();
void key_code_exit_doors_phase0();
void key_code_exit_doors_update();
void key_code_exit_doors_phase2();
void key_code_exit_doors_draw();
void sound_zone_set_enabled();
s32 sound_zone_get_level();
void obj_script_skip_operand();
void script_case_match();
void obj_script_read_u16_var();
void script_op_set_vy();
void script_op_jump_if_vy_nonneg();
void obj_script_set_var();
void obj_script_set_var_rand();
void obj_attack_player();
void obj_roll_random();
void obj_script_jump_if_roll_le();
void obj_script_jump_if_equal();
void script_set_enemy_var();
void script_op_set_yaw_rate();
void obj_loop_anim_start();
void script_op_set_target();
void giant_robot_fx_start();
void giant_robot_fx_stop();
void script_counter_inc();
void script_set_flag();
void giant_robot_reset_scale();
void script_jump_if_player_low();
void script_jump_if_rand_le();
void giant_robot_update();
void giant_robot_take_hit();
void obj_hook_call();
void giant_robot_phase2();
void giant_robot_draw();
void giant_robot_sounds_start();
s32 player_horiz_dist();
void player_distance();
s32 player_dist_sq();
s32 get_angle_to_player();
s32 keyframe_step();
void tick_reset();
s32 giant_robot_aim_test();
void req_queue_push_vec();
void giant_robot_systems_update();
void giant_robot_systems_init();
void giant_robot_systems_teardown();
void giant_robot_teardown();
void fade_step();
void shots_update();
void shot_trace();
Shot * shot_slot_find_free();
s32 func_800C3324();
void cam_get_pos();
s32 obj_angle_to();
void pchr_set_angle_span();
void sound_emitter_start();
void sound_stop_global();
void sound_pair_start_loops();
s32 move_box_step();
void keyframe_update_all();
void keyframe_hook_run_all();
KeyframeSlot * keyframe_slot_alloc();
void sound_loop_start();
void keyframe_ramp_update_all();
KeyframeRamp * keyframe_ramp_alloc();
void keyframe_ramp_alloc_wrapper();
void fade_red_start_at();
void fx_rec34_spawn_pos();
void obj_sound_clear();

void sway_start();

/* S01 functions in C (scripts/s01_protos.py). */
void obj_speed_approach();
void script_op_jump_table_if_player_far();
s32 obj_script_loop();
void obj_sway_start();
void script_jump_if_counter_eq();
void giant_robot_aim_trace();

extern FxRecordParams fx_send_rec34_params_a, fx_send_rec34_params_b;
extern RecTemplate fx_send_template_a, fx_send_template_b, fx_owner_template_a, fx_owner_template_b; /* fx_spawn_template templates */
void tick_reset();

/* S01 functions in C (scripts/s01_protos.py). */
void obj_offset_to_world_shifted();
void obj_offset_to_fixed();
void obj_effect_send_pos();
void script_jump_if_below();
void shot_pool_take();
void keyframe_start();
void obj_spawn_with_two_fx();

/* S01 functions in C (scripts/s01_protos.py). */
void obj_aim_jitter_placement();
s32 obj_respawn();
s32 obj_spawn_from_placement();
void obj_aim_jittered();
s32 obj_spawn_here();
void script_jump_if_beyond_radius();
void obj_jump_if_player_near();
void func_800C02FC();
void obj_script_jump_if_far();
void obj_point_to_world();

extern s16 D_8013B6A2;
extern s16 *smg_soldier_script[];
extern s16 *smg_soldier_jump_table[];
extern u8 smg_soldier_asset[];
extern SoundVolume smg_soldier_sounds[];
extern StateEntry smg_soldier_states[];
extern s16 *smg_soldier_data[9];
extern s32 alert_flag, turn_flag, orbit_flag, mission_enemies_left, cam_timer;
extern s32 msg_text_id, cam_side_blend, cam_ramp_b, msg_fade, cam_spin_step;
extern s32 cam_angle_acc, d_8011FEE4, timer_warn_shown, grid_flagged_count;
extern s16 msg_pos_x, msg_pos_y;
extern GridEntry *flagged_grid_cells[];
extern s32 obj_target_index;
extern s16 obj_target_pchr_table[];

s32 enemy_spawn_step(Object *obj);
void cam_update_phase2();
void hud_frame_draw();

/* S01 functions in C (scripts/s01_protos.py). */
s32 smg_soldier_spawn();
void mission_state_reset();

/* S01 functions in C (scripts/s01_protos.py). */
void script_jump_near_corner();
void script_jump_near();

extern Object *giant_robot_fx_owner;
extern s32 sway_level;

/* S01 functions in C (scripts/s01_protos.py). */
void obj_script_jump_if_outside();
void obj_fire_shot();
void sway_update();

extern s32 helicopter_asset_slot[3];
extern s16 *helicopter_label_table[];
extern ScriptCallEntry d_801178BC[];
extern StateEntry helicopter_slot_table[];
extern s16 helicopter_script[];
extern s16 helicopter_data[];
extern s16 *helicopter_script_entry;
extern s16 *giant_robot_data[14];
extern s16 *D_80118570;

/* handlers helicopter_spawn installs */
void helicopter_update();
void helicopter_draw();
s32 helicopter_crash(Object *obj);

/* S01 functions in C (scripts/s01_protos.py). */
s32 helicopter_spawn();
s32 giant_robot_spawn();

/* S01 functions in C (scripts/s01_protos.py). */
s32 obj_player_dist_whole();
void obj_set_fall_speed();
s32 obj_probe_hit();
void shots_trace();

extern s16 fuchikoma_burst_offsets[];

/* S01 functions in C (scripts/s01_protos.py). */
void keyholder_fuchikoma_burst();

extern s16 spawn_offset_x_table[];
extern s16 spawn_offset_y_table[];
extern s16 spawn_offset_z_table[];

/* S01 functions in C (scripts/s01_protos.py). */
void shot_burst_spawn();

extern s32 D_801070EC;
extern s32 D_801070E0;

/* S01 functions in C (scripts/s01_protos.py). */
void script_jump_if_counter_ge();

/* S01 functions in C (scripts/s01_protos.py). */
s32 key_code_exit_doors_spawn();

extern s32 key_codes_acquired;
extern s32 key_codes_complete_flag;
extern s32 stage_exit_flag;
extern s32 warehouse_hint_timer;
extern GunSetup giant_robot_side_shot_setup;
extern SegVec sway_pos;
extern AimPacket sway_aim;
extern s32 D_80121AE8;
extern s32 D_80121B00;
extern s32 D_80121B04;

/* S01 functions in C (scripts/s01_protos.py). */
s32 stage_init_pursue();
void giant_robot_side_fx();

/* S01 functions in C (scripts/s01_protos.py). */
void sound_pair_set_pose();

/* S01 functions in C (scripts/s01_protos.py). */
s32 obj_turn_to_cam_done();

/* S01 functions in C (scripts/s01_protos.py). */
void key_progress_update();

extern s32 giant_robot_level;

extern s16 snd_wave_offset_table[];

extern s32 move_box_hit_state;

/* S01 functions in C (scripts/s01_protos.py). */
void move_box_sweep();

/* S01 functions in C (scripts/s01_protos.py). */
void script_jump_by_player_view();

/* S01 functions in C (scripts/s01_protos.py). */
void enemy_alert_update();

extern s16 fade_colour_x_from[][2];
extern s16 fade_colour_x_to[][2];
extern s16 fade_colour_y_from[][2];
extern s16 fade_colour_y_to[][2];

extern Keyframe giant_robot_sound_keys_start[3];
extern Keyframe giant_robot_sound_keys_end[5];

/* S01 functions in C (scripts/s01_protos.py). */
void giant_robot_sound_update();

extern u8 keyholder_asset[];
extern s16 *keyholder_script[];
extern ScriptCallEntry D_80116F50[];
extern StateEntry D_80116F9C[];
extern s16 *D_80116F4C;

/* S01 functions in C (scripts/s01_protos.py). */
s32 keyholder_fuchikoma_spawn();

/* S01 functions in C (scripts/s01_protos.py). */
void enemy_wall_avoid();

extern s32 loop_state_pos_x;
extern s32 loop_state_pos_y;
extern s32 loop_state_pos_z;
extern s16 loop_state_noisy;
extern s16 loop_state_spark_id;

/* S01 functions in C (scripts/s01_protos.py). */
void obj_play_fade_sound();

#endif
