/* night_vision_flag: one of s02's own original source files (scripts/objmap.py); part of src/s02/main.c's unit, included there. */

extern s32 night_vision_target;

void set_night_vision_flag(s32 arg0) {
    night_vision_target = arg0;
}

extern s32 night_vision_target;

s32 get_night_vision_flag(void) {
    return night_vision_target;
}


extern s32 night_vision_level;

s32 func_800C5048(void) {
    return night_vision_level;
}
