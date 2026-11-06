/* Data shared by s09, s10: scripts/stage_data.py. */

StateEntry triple_barrel_robot_state_table[3] = {
    {0, TRIPLE_BARREL_ROBOT_ANIM_IDLE, 0},
    {(u32)obj_patrol_update, TRIPLE_BARREL_ROBOT_ANIM_FIRE, 0},
    {(u32)sound_emitter_step, TRIPLE_BARREL_ROBOT_ANIM_WALK, 0},
};
