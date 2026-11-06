/* Data shared by s01, s03, s10: scripts/stage_data.py. */

StateEntry rocket_fuchikoma_state_table[3] = {
    {0, ROCKET_FUCHIKOMA_ANIM_IDLE, 0},
    {(u32)obj_settle_offset, ROCKET_FUCHIKOMA_ANIM_FLY, 0},
    {(u32)obj_countdown_step, ROCKET_FUCHIKOMA_ANIM_DETONATE, 0},
};
