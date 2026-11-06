/* Data shared by s05, s09, s12: scripts/stage_data.py. */

StateEntry gun_turret_states[3] = {
    {0, GUN_TURRET_ANIM_IDLE, 1},
    {(u32)obj_turn_to_player_16, GUN_TURRET_ANIM_IDLE, 1},
    {(u32)obj_handle_result, GUN_TURRET_ANIM_IDLE, 1},
};
