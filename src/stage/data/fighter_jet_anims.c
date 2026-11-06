/* Data shared by s04, s05: scripts/stage_data.py. */

struct FighterJetAnims {
    s16 script[4];
    s16 *table[1];
} fighter_jet_anims = {
    /* script */ {
        STEP(4, 0),
        GOTO(FIGHTER_JET_SCRIPT),
    },
    /* table */ {
        fighter_jet_anims.script,
    },
};
