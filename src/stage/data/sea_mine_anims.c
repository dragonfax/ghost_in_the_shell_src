/* Data shared by s02, s04: scripts/stage_data.py. */

struct SeaMineAnims {
    s16 script[4];
    s16 *table[1];
} sea_mine_anims = {
    /* script */ {
        STEP(1, 12),
        GOTO(SEA_MINE_SCRIPT),
    },
    /* table */ {
        sea_mine_anims.script,
    },
};
