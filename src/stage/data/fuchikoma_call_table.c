/* Data shared by s07, s09, s11, s12: scripts/stage_data.py. */

ScriptCallEntry fuchikoma_call_table[16] = {
    {NULL, 0},
    {script_jump_if_within_range, 0},
    {script_op_jump_if_player_in_range, 0},
    {script_op_jump_if_flag_in_range, 0},
    {script_op_jump_if_in_range, 0},
    {script_jump_near_corner, 0},
    {obj_script_read_speed, 0},
    {script_op_set_enemy_sound, 0},
    {obj_script_read_s32, 0},
    {enemy_retarget_jitter, 0},
    {script_op_aim_and_track, 0},
    {obj_script_read_jump, 0},
    {script_jump_if_player_in_radius, 0},
    {script_jump_if_player_far, 0},
    {script_op_set_mode, 0},
    {script_jump_if_mode, 0},
};
