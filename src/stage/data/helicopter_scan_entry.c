/* Data shared by s01, s12 (2 objects): scripts/stage_data.py. */

ScanEntry helicopter_scan_entry = {{0, (s32)helicopter_spawn}, helicopter_asset_slot, (s32)&d_8011770C, (s32)d_80117730, 0};

struct HelicopterAnims {
    s16 script[4];
    u32 table;
} helicopter_anims = {
    /* script */ {
        STEP(1, 0),
        GOTO(HELICOPTER_SCRIPT),
    },
    /* table */ (u32)helicopter_anims.script,
};
