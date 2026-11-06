/* Data shared by s01, s04, s06, s07, s13 (3 objects): scripts/stage_data.py. */

s16 video_mode_id = 0;

s16 debug_cam_speed_table[5][2] = {
    {0x100, 0xF0}, {0x140, 0xF0}, {0x200, 0xF0}, {0x280, 0xF0}, {0x280, 0x1E0},
};

s32 pause_prev_work_area = 0;
