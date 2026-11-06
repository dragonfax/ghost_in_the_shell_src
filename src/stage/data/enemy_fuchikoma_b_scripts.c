/* Data shared by s07, s09, s11, s12: scripts/stage_data.py. */

struct EnemyFuchikomaBScripts {
    s16 idle[6];
    s16 start[8];
    s16 accelerate[10];
    s16 wait_trigger[6];
    s16 chase_start[6];
    s16 search[10];
    s16 engage[2];
    s16 aim[20];
    s16 corner_check[8];
    s16 corner_turn[2];
    s16 await_mode[8];
    s16 death_wait[6];
    s16 death[4];
    s16 await_chase[8];
    s16 *table[14];
    s16 *fuchikoma_anim_link;
} enemy_fuchikoma_b_scripts = {
    /* idle */ {
        FUCHIKOMA_READ_JUMP, ENEMY_FUCHIKOMA_B_START,
        WAIT(1),
        JUMP(ENEMY_FUCHIKOMA_B_IDLE),
    },
    /* start */ {
        NEXT_STATE(FUCHIKOMA_STATE_STATE_IDLE),
        FUCHIKOMA_READ_SPEED, 0, 0,
        SET_COUNTER(8),
    },
    /* accelerate */ {
        WAIT(1),
        LOOP(ENEMY_FUCHIKOMA_B_ACCELERATE),
        FUCHIKOMA_SET_ENEMY_SOUND, -32768, 0,
        FUCHIKOMA_READ_S32, 341, 0,
    },
    /* wait_trigger */ {
        FUCHIKOMA_READ_JUMP, ENEMY_FUCHIKOMA_B_CHASE_START,
        WAIT(1),
        JUMP(ENEMY_FUCHIKOMA_B_WAIT_TRIGGER),
    },
    /* chase_start */ {
        NEXT_STATE(FUCHIKOMA_STATE_STATE_CHASE),
        FUCHIKOMA_ENEMY_RETARGET_JITTER,
        SET_COUNTER(30),
    },
    /* search */ {
        WAIT(1),
        FUCHIKOMA_JUMP_IF_PLAYER_IN_RADIUS, 1800, 2500, ENEMY_FUCHIKOMA_B_ENGAGE,
        LOOP(ENEMY_FUCHIKOMA_B_SEARCH),
        JUMP(ENEMY_FUCHIKOMA_B_WAIT_TRIGGER),
    },
    /* engage */ {
        NEXT_STATE(FUCHIKOMA_STATE_STATE_CHASE),
    },
    /* aim */ {
        WAIT(1),
        FUCHIKOMA_AIM_AND_TRACK,
        FUCHIKOMA_JUMP_IF_PLAYER_FAR, 2500, ENEMY_FUCHIKOMA_B_WAIT_TRIGGER,
        WAIT(1),
        FUCHIKOMA_JUMP_IF_FLAG_IN_RANGE, 600, ENEMY_FUCHIKOMA_B_DEATH_WAIT,
        FUCHIKOMA_JUMP_IF_PLAYER_IN_RANGE, 1800, 300, ENEMY_FUCHIKOMA_B_CORNER_CHECK,
        FUCHIKOMA_JUMP_IF_WITHIN_RANGE, 1800, ENEMY_FUCHIKOMA_B_AIM,
        JUMP(ENEMY_FUCHIKOMA_B_WAIT_TRIGGER),
    },
    /* corner_check */ {
        WAIT(1),
        FUCHIKOMA_JUMP_NEAR_CORNER, 1024, ENEMY_FUCHIKOMA_B_CORNER_TURN,
        JUMP(ENEMY_FUCHIKOMA_B_AIM),
    },
    /* corner_turn */ {
        FUCHIKOMA_SET_MODE, 1,
    },
    /* await_mode */ {
        WAIT(1),
        FUCHIKOMA_AIM_AND_TRACK,
        FUCHIKOMA_JUMP_IF_MODE, 0, ENEMY_FUCHIKOMA_B_ENGAGE,
        JUMP(ENEMY_FUCHIKOMA_B_AWAIT_MODE),
    },
    /* death_wait */ {
        FUCHIKOMA_READ_JUMP, ENEMY_FUCHIKOMA_B_DEATH,
        WAIT(1),
        JUMP(ENEMY_FUCHIKOMA_B_DEATH_WAIT),
    },
    /* death */ {
        NEXT_STATE(FUCHIKOMA_STATE_STATE_DEAD),
        FUCHIKOMA_SET_MODE, 1,
    },
    /* await_chase */ {
        WAIT(1),
        FUCHIKOMA_AIM_AND_TRACK,
        JUMP_IF_STATE(FUCHIKOMA_STATE_STATE_CHASE, ENEMY_FUCHIKOMA_B_ENGAGE),
        JUMP(ENEMY_FUCHIKOMA_B_AWAIT_CHASE),
    },
    /* table */ {
        enemy_fuchikoma_b_scripts.idle, enemy_fuchikoma_b_scripts.start, enemy_fuchikoma_b_scripts.accelerate, enemy_fuchikoma_b_scripts.wait_trigger, enemy_fuchikoma_b_scripts.chase_start, enemy_fuchikoma_b_scripts.search,
        enemy_fuchikoma_b_scripts.engage, enemy_fuchikoma_b_scripts.aim, enemy_fuchikoma_b_scripts.corner_check, enemy_fuchikoma_b_scripts.corner_turn, enemy_fuchikoma_b_scripts.await_mode, enemy_fuchikoma_b_scripts.death_wait,
        enemy_fuchikoma_b_scripts.death, enemy_fuchikoma_b_scripts.await_chase,
    },
    /* fuchikoma_anim_link */ enemy_fuchikoma_b_scripts.idle,
};
