/* Data shared by s05, s07: scripts/stage_data.py. */

StateEntry walker_state_table_alt[3] = {
    {0, WALKER_MECH_ANIM_IDLE, 0},
    {(u32)walker_mech_patrol, WALKER_MECH_ANIM_WALK, 0},
    {(u32)walker_mech_attack, WALKER_MECH_ANIM_FIRE, 0},
};
