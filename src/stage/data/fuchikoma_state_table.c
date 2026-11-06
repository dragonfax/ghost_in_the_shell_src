/* Data shared by s07, s09, s11, s12: scripts/stage_data.py. */

StateEntry fuchikoma_state_table[3] = {
    {0, ENEMY_FUCHIKOMA_B_ANIM_IDLE, 0},
    {(u32)fuchikoma_chase_update, ENEMY_FUCHIKOMA_B_ANIM_WALK, 0},
    {(u32)obj_fall_update, ENEMY_FUCHIKOMA_B_ANIM_IDLE, 0},
};
