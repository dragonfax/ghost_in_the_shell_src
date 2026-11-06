/* Data shared by s01, s03, s05, s07, s10 (4 objects): scripts/stage_data.py. */

ScriptCallEntry script_call_table[12] = {
    {NULL, 0},
    {script_jump_near, 0},
    {script_read_speed_long, 0},
    {obj_read_s32, 0},
    {script_read_long, 0},
    {obj_aim_jittered, 0},
    {obj_face_player, 0},
    {script_branch_on_flag, 0},
    {script_jump_if_not_below_speed, 0},
    {script_jump_near_player, 0},
    {script_jump_if_beyond_radius, 0},
    {script_jump_if_facing_player_in_radius, 0},
};

s16 spawn_offset_x_table[12] = {
    -0x4C, -0x26, 0, 0x26, 0x4C, -0x5A, 0x36, -0x12,
    0x12, 0x36, 0x5A, 0,
};

s16 spawn_offset_y_table[12] = {
    14, 14, 14, 14, 14, -14, -14, -14,
    -14, -14, -14, 0,
};

s16 spawn_offset_z_table[12] = {
    6, 6, 6, 6, 6, -6, -6, -6,
    -6, -6, -6, 0,
};
