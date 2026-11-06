/* Data shared by s04, s05, s10: scripts/stage_data.py. */

void (*effect_callback_table[4])() = {
    obj_fade_level, obj_sound_volume_update, sound_volume_phase2, sound_volume_ramp,
};
