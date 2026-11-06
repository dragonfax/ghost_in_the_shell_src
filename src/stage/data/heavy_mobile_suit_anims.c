/* Data shared by s04, s09: scripts/stage_data.py. */

struct HeavyMobileSuitAnims {
    s16 script[4];
    s16 anim_patrol_enter[12];
    s16 anim_search_hold[4];
    s16 anim_search_end[12];
    s16 anim_alt_enter[12];
    s16 anim_alt_hold[4];
    s16 anim_alt_end[12];
    s16 anim_spotted_enter[12];
    s16 anim_pursue_enter[16];
    s16 anim_pursue_alt_enter[16];
    s16 anim_approach_hold[4];
    s16 anim_fire_enter[12];
    s16 anim_disengage[10];
    s16 *table[13];
} heavy_mobile_suit_anims = {
    /* script */ {
        STEP(1, 17),
        GOTO(HEAVY_MOBILE_SUIT_SCRIPT),
    },
    /* anim_patrol_enter */ {
        STEP(8, 37),
        STEP(8, 36),
        STEP(8, 35),
        STEP(8, 34),
        STEP(8, 33),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_SEARCH_HOLD),
    },
    /* anim_search_hold */ {
        STEP(1, 33),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_SEARCH_HOLD),
    },
    /* anim_search_end */ {
        STEP(8, 33),
        STEP(8, 34),
        STEP(8, 35),
        STEP(8, 36),
        STEP(8, 37),
        GOTO(HEAVY_MOBILE_SUIT_SCRIPT),
    },
    /* anim_alt_enter */ {
        STEP(8, 45),
        STEP(8, 44),
        STEP(8, 43),
        STEP(8, 42),
        STEP(8, 41),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_ALT_HOLD),
    },
    /* anim_alt_hold */ {
        STEP(1, 41),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_ALT_HOLD),
    },
    /* anim_alt_end */ {
        STEP(8, 41),
        STEP(8, 42),
        STEP(8, 43),
        STEP(8, 44),
        STEP(8, 45),
        GOTO(HEAVY_MOBILE_SUIT_SCRIPT),
    },
    /* anim_spotted_enter */ {
        STEP(8, 121),
        STEP(8, 122),
        STEP(8, 123),
        STEP(8, 124),
        STEP(8, 125),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD),
    },
    /* anim_pursue_enter */ {
        STEP(8, 49),
        STEP(8, 50),
        STEP(8, 51),
        STEP(8, 52),
        STEP(8, 53),
        STEP(8, 54),
        STEP(8, 55),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD),
    },
    /* anim_pursue_alt_enter */ {
        STEP(8, 57),
        STEP(8, 58),
        STEP(8, 59),
        STEP(8, 60),
        STEP(8, 61),
        STEP(8, 62),
        STEP(8, 63),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD),
    },
    /* anim_approach_hold */ {
        STEP(1, 117),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD),
    },
    /* anim_fire_enter */ {
        STEP(64, 113),
        STEP(8, 114),
        STEP(8, 115),
        STEP(8, 116),
        STEP(8, 117),
        GOTO(HEAVY_MOBILE_SUIT_ANIM_APPROACH_HOLD),
    },
    /* anim_disengage */ {
        STEP(8, 125),
        STEP(8, 124),
        STEP(8, 123),
        STEP(8, 122),
        GOTO(HEAVY_MOBILE_SUIT_SCRIPT),
    },
    /* table */ {
        heavy_mobile_suit_anims.script, heavy_mobile_suit_anims.anim_patrol_enter, heavy_mobile_suit_anims.anim_search_hold, heavy_mobile_suit_anims.anim_search_end, heavy_mobile_suit_anims.anim_alt_enter, heavy_mobile_suit_anims.anim_alt_hold,
        heavy_mobile_suit_anims.anim_alt_end, heavy_mobile_suit_anims.anim_spotted_enter, heavy_mobile_suit_anims.anim_pursue_enter, heavy_mobile_suit_anims.anim_pursue_alt_enter, heavy_mobile_suit_anims.anim_approach_hold, heavy_mobile_suit_anims.anim_fire_enter,
        heavy_mobile_suit_anims.anim_disengage,
    },
};
