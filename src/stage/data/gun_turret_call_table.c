/* Data shared by s05, s09, s12: scripts/stage_data.py. */

ScriptCallEntry gun_turret_call_table[3] = {
    {NULL, 0},
    {script_branch_if_near_player, 0},
    {script_op_jump_if_facing_player, 0},
};
