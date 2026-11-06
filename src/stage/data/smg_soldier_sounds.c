/* Data shared by s01, s08, s10 (4 objects): scripts/stage_data.py. */

SoundVolume smg_soldier_sounds[1] = {
    {SND_GROUND_IMPACT | SND_GROUP(2), 0x1000},
};

struct SmgSoldierAnims {
    s16 idle[6];
    s16 idle_alt[32];
    s16 walk_start[30];
    s16 walk[28];
    s16 run_start[36];
    s16 run[26];
    s16 aim[70];
    s16 hold[8];
    s16 hit[22];
    s16 *table[9];
} smg_soldier_anims = {
    /* idle */ {
        STEP(20, 4),
        FLY(0),
        GOTO(SMG_SOLDIER_ANIM_IDLE),
    },
    /* idle_alt */ {
        STEP(40, 4),
        STEP(40, 98),
        STEP(20, 97),
        STEP(20, 97),
        STEP(20, 97),
        STEP(40, 98),
        STEP(40, 4),
        STEP(20, 4),
        STEP(20, 4),
        STEP(40, 98),
        STEP(20, 98),
        STEP(20, 97),
        STEP(20, 97),
        STEP(40, 98),
        STEP(40, 4),
        GOTO(SMG_SOLDIER_ANIM_IDLE_ALT),
    },
    /* walk_start */ {
        STEP(6, 4),
        FLY(1),
        STEP(6, 5),
        FLY(3),
        STEP(6, 6),
        SOUND(0),
        FLY(4),
        STEP(6, 7),
        STEP(6, 8),
        STEP(6, 9),
        STEP(6, 10),
        SOUND(0),
        STEP(6, 2),
        STEP(6, 3),
        GOTO(SMG_SOLDIER_ANIM_WALK),
    },
    /* walk */ {
        STEP(6, 4),
        FLY(4),
        STEP(6, 5),
        STEP(6, 6),
        SOUND(0),
        STEP(6, 7),
        STEP(6, 8),
        STEP(6, 9),
        STEP(6, 10),
        SOUND(0),
        STEP(6, 1),
        STEP(6, 2),
        STEP(6, 3),
        GOTO(SMG_SOLDIER_ANIM_WALK),
    },
    /* run_start */ {
        STEP(6, 4),
        STEP(3, 15),
        FLY(1),
        STEP(3, 16),
        FLY(6),
        STEP(3, 17),
        SOUND(0),
        STEP(3, 18),
        FLY(6),
        STEP(3, 19),
        STEP(3, 20),
        FLY(9),
        STEP(3, 21),
        STEP(3, 12),
        SOUND(0),
        STEP(3, 13),
        STEP(3, 14),
        GOTO(SMG_SOLDIER_ANIM_RUN),
    },
    /* run */ {
        STEP(3, 15),
        STEP(3, 16),
        STEP(3, 17),
        SOUND(0),
        STEP(3, 18),
        STEP(3, 19),
        STEP(3, 20),
        STEP(3, 21),
        STEP(3, 12),
        SOUND(0),
        STEP(3, 13),
        STEP(3, 14),
        GOTO(SMG_SOLDIER_ANIM_RUN),
    },
    /* aim */ {
        FLY(0),
        STEP(8, 90),
        STEP(8, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 89),
        STEP(2, 89),
        SET_F8(255),
        STEP(2, 90),
        STEP(2, 90),
        STEP(2, 89),
        GOTO(SMG_SOLDIER_ANIM_AIM),
    },
    /* hold */ {
        FLY(2),
        FLY(0),
        STEP(14, 92),
        GOTO(SMG_SOLDIER_ANIM_HOLD),
    },
    /* hit */ {
        STEP(12, 75),
        STEP(4, 77),
        STEP(4, 78),
        STEP(4, 79),
        STEP(4, 80),
        STEP(4, 81),
        STEP(4, 83),
        STEP(4, 85),
        STEP(4, 86),
        STEP(10, 87),
        GOTO(SMG_SOLDIER_ANIM_HIT),
    },
    /* table */ {
        smg_soldier_anims.idle, smg_soldier_anims.idle_alt, smg_soldier_anims.walk_start, smg_soldier_anims.walk, smg_soldier_anims.run_start, smg_soldier_anims.run,
        smg_soldier_anims.aim, smg_soldier_anims.hold, smg_soldier_anims.hit,
    },
};

struct SmgSoldierScripts {
    s16 idle[6];
    s16 idle_pause[4];
    s16 idle_cycle[10];
    s16 patrol[6];
    s16 patrol_cycle[12];
    s16 patrol_wait[6];
    s16 hold[4];
    s16 hold_pause[4];
    s16 hold_cycle[10];
    s16 walk[4];
    s16 walk_step[4];
    s16 walk_cycle[10];
    s16 walk_pause[4];
    s16 walk_pause_cycle[10];
    s16 *table[14];
    s16 *script[5];
} smg_soldier_scripts = {
    /* idle */ {
        JUMP_RANDOM(3072, SMG_SOLDIER_PATROL),
        SET_COUNTER_RANDOM(3, 1),
    },
    /* idle_pause */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_WAIT),
    },
    /* idle_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_IDLE_CYCLE),
        LOOP(SMG_SOLDIER_IDLE_PAUSE),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* patrol */ {
        WAIT(1),
        WANDER(1),
        NEXT_STATE(SMG_SOLDIER_STATE_PATROL),
    },
    /* patrol_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_PATROL_CYCLE),
        SET_SPEED(0),
        WANDER(1),
        SET_COUNTER_RANDOM(5, 3),
    },
    /* patrol_wait */ {
        WAIT(1),
        LOOP(SMG_SOLDIER_PATROL_WAIT),
        JUMP(SMG_SOLDIER_IDLE),
    },
    /* hold */ {
        SET_COUNTER_RANDOM(3, 1),
    },
    /* hold_pause */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_WAIT),
    },
    /* hold_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_HOLD_CYCLE),
        LOOP(SMG_SOLDIER_HOLD_PAUSE),
        JUMP(SMG_SOLDIER_HOLD),
    },
    /* walk */ {
        SET_COUNTER_RANDOM(4, 1),
    },
    /* walk_step */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_PATROL),
    },
    /* walk_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_WALK_CYCLE),
        LOOP(SMG_SOLDIER_WALK_STEP),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* walk_pause */ {
        WAIT(8),
        NEXT_STATE(SMG_SOLDIER_STATE_WAIT),
    },
    /* walk_pause_cycle */ {
        WAIT(1),
        JUMP_UNLESS_STATE(SMG_SOLDIER_STATE_IDLE, SMG_SOLDIER_WALK_PAUSE_CYCLE),
        LOOP(SMG_SOLDIER_WALK_PAUSE),
        JUMP(SMG_SOLDIER_WALK),
    },
    /* table */ {
        smg_soldier_scripts.idle, smg_soldier_scripts.idle_pause, smg_soldier_scripts.idle_cycle, smg_soldier_scripts.patrol, smg_soldier_scripts.patrol_cycle, smg_soldier_scripts.patrol_wait,
        smg_soldier_scripts.hold, smg_soldier_scripts.hold_pause, smg_soldier_scripts.hold_cycle, smg_soldier_scripts.walk, smg_soldier_scripts.walk_step, smg_soldier_scripts.walk_cycle,
        smg_soldier_scripts.walk_pause, smg_soldier_scripts.walk_pause_cycle,
    },
    /* script */ {
        smg_soldier_scripts.idle, smg_soldier_scripts.hold, smg_soldier_scripts.walk, smg_soldier_scripts.hold, smg_soldier_scripts.walk,
    },
};

StateEntry smg_soldier_states[9] = {
    {0, SMG_SOLDIER_ANIM_IDLE, 0},
    {(u32)enemy_wait_switch, SMG_SOLDIER_ANIM_IDLE_ALT, 0},
    {(u32)enemy_move_or_wait, SMG_SOLDIER_ANIM_WALK_START, 0},
    {(u32)enemy_walk_step, SMG_SOLDIER_ANIM_RUN_START, 0},
    {(u32)flyer_wander, SMG_SOLDIER_ANIM_RUN_START, 0},
    {(u32)enemy_shoot_update, SMG_SOLDIER_ANIM_AIM, 0},
    {(u32)flyer_retreat, SMG_SOLDIER_ANIM_WALK, 0},
    {(u32)enemy_shoot_update, SMG_SOLDIER_ANIM_HOLD, 0},
    {0, SMG_SOLDIER_ANIM_HIT, 0},
};
