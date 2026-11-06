/* Data shared by s01, s06, s12 (5 objects): scripts/stage_data.py. */

ModelBlockRef d_801176C4[4] = {
    {(s32)file_ohel_ch0_clt, 0, 0},
    {(s32)file_ohel_tp0_clt, 0, 0},
    {(s32)file_ohel_tp1_clt, 0, 0},
    {0, 0, 0},
};

ModelBlockRef d_801176E4[3] = {
    {(s32)file_ohel_tp0_xs3, 1, 0},
    {(s32)file_ohel_tp1_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef d_801176FC[2] = {
    {(s32)file_ohel_ch0_vx1, 0, 0},
    {0, 0, 0},
};

ModelBlock d_8011770C = {(s32)d_801176C4, (s32)d_801176FC, (s32)d_801176E4, 0, 0, 0, 0, 0, 0};

u8 *d_80117730[2] = {
    file_ohel_ch0_cb4, NULL,
};
