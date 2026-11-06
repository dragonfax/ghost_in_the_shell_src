/* Data shared by s02, s03, s07, s10, s11: scripts/stage_data.py. */

StateEntry gun_turret_2_states[3] = {
    {0, GUN_TURRET_2_POSE, 1},
    {(u32)turret_track_player, GUN_TURRET_2_POSE, 1},
    {(u32)obj_state_dispatch, GUN_TURRET_2_POSE, 1},
};
