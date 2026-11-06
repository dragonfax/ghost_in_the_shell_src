/* Data shared by s06, s11: scripts/stage_data.py. */

struct FlierScriptPtrAnims {
    s16 idle[4];
    s16 *table;
} flier_script_ptr_anims = {
    /* idle */ {
        STEP(20, 0),
        GOTO(FLIER_SCRIPT_PTR_ANIM_IDLE),
    },
    /* table */ flier_script_ptr_anims.idle,
};
