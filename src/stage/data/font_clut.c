/* Data shared by s01, s02, s03, s04, s05, s06, s07, s08, s09, s10, s11, s12, s13 (97 objects): scripts/stage_data.py. */

s16 font_clut[4] = {
    -0x8000, -0x8000, 0x7FFF, 0,
};

s32 text_origin_x = 0;

s32 text_origin_y = 0;

s32 text_cursor_x = 0;

s32 text_cursor_y = 0;

void *text_packet_cur = (void *)text_packets;

s16 text_packet_index = 0;

s32 font_page_x = 0x3C0;

s32 font_page_y = 0;

s32 font_y_offset = 0xE0;

s32 font_semi_trans_flag = 1;

s32 texpage_current = 0;

u32 d_8011DCD4[2] = {
    0x00000000, 0x01000100,
};

RECT font_tex_window = {0, 0, 0, 0};

void (*handler_fn_table[6])(s32, s32) = {
    interp1c_set_state, interp2c_set_state, interp_set_state, interp38b_set_state, interp38_set_state, part_slot_set_state,
};

void (*clear_handler_table[5])(s32, s32) = {
    cam_track_set_on, view_rec_set_on, cam_track_set_active, part_rec_set_active, track_set_enabled,
};

void *(*part_record_resolve_table[4])(u32) = {
    cam_track_slot_get, view_rec_get, cam_track_get, part_rec_get,
};

void (*part_cmd_table[12])(PartSlot *, s32 *, s32) = {
    fn_800E8030, fn_800E8024, handler_range_call, handler_range_call_zero, part_record_read, cam_track_setup,
    view_rec_setup, cam_track_init, cam_track_b_setup, track_setup, text_slot_setup, ramp_start_script,
};

s32 name_table_base = 0;

s32 pause_blocked_flag = 0;

u32 screenshot_name_ptr = 0x57454956;

char digits4_out_ptr[12] = "0000.BMP\000\000\000";

s32 screenshot_counter = 0;

ScreenSize stage_screen_default = {0x100, 0xF0};

s32 d_8011DD70 = 1;

s16 spark_red_table[12] = {
    0x1000, 0x1000, 0x800, 0, 0, 0, 0, 0,
    0, 0x800, 0x1000, 0x1000,
};

s16 spark_green_table[12] = {
    0x1000, 0, 0, 0x800, 0x1000, 0x1000, 0x1000, 0x800,
    0, 0x800, 0x1000, 0x1000,
};

s16 shake_table[14] = {
    3, 0, 3, 0, 3, 0, 2, 0,
    2, 0, 1, 0, -1, 0,
};

s32 pose_joint_indices[2][5] = {
    {0x17, 3, 11, 12, 0x12}, {14, 4, 13, 0x16, 0x1A},
};

u32 d_8011DDE8[4] = {
    0x00000006, 0x00000019, 0x00000000, 0x00000008,
};

VECTOR spark_point_table[5] = {
    {0, -0x50, -0x7B, 0}, {0, -0x50, -0x87, 1}, {0, -0x50, -0xB7, 2}, {0, -0x50, -0xDB, 3}, {0, -0x50, -0x93, 4},
};

s32 ptr_table_len = 0;

s32 ptr_table_mark = 0;

s32 solid_slot_next = 0;

s32 solid_grid_parity = 0;

s16 solid_count = -1;

s16 collide_mode = 0;

s32 grid_origin_x = 0;

s32 grid_origin_y = 0;

s32 grid_origin_z = 0;

s32 solid_active_count = 0;

u32 solid_masks[32] = {
    1, 3, 7, 0xF, 0x1F, 0x3F,
    0x7F, 0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF,
    0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF, 0x1FFFF, 0x3FFFF,
    0x7FFFF, 0xFFFFF, 0x1FFFFF, 0x3FFFFF, 0x7FFFFF, 0xFFFFFF,
    0x1FFFFFF, 0x3FFFFFF, 0x7FFFFFF, 0xFFFFFFF, 0x1FFFFFFF, 0x3FFFFFFF,
    0x7FFFFFFF, 0xFFFFFFFF,
};

Node *obj_list_cursor = NULL;

void (*actor_hook)() = NULL;

ObjHandlerFn obj_state_handlers[2] = {
    obj_release_check, obj_hook_or_free,
};

ObjHandlerFn obj_state_steps[2] = {
    obj_hit_handle, obj_call_hook,
};

ObjHandlerFn obj_state_steps_b[2] = {
    obj_area_update, obj_hook_or_free,
};

s16 obj_free_count = 0;

u16 obj_serial = 0;

s16 obj_pending_count = 0;

Object *obj_pending = NULL;

u8 *test_sprite_names[3] = {
    str_tst_spr_clt, str_tst_spr_grc, str_tst_spr_so3,
};

ScanEntry d_8011DF24 = {{0, 0}, (s32 *)d_8012D3AC, 0, 0, (s32)test_sprite_names};

u8 *message_sprite_names[3] = {
    str_msgspr_clt, str_msgspr_grc, str_msgspr_so3,
};

ScanEntry d_8011DF48 = {{0, 0}, (s32 *)d_8012D3B8, 0, 0, (s32)message_sprite_names};

u8 *target_display_names[3] = {
    str_tg_disp_clt, str_tg_disp_grc, str_tg_disp_so3,
};

ScanEntry d_8011DF6C = {{0, 0}, (s32 *)d_8012D3C4, 0, 0, (s32)target_display_names};

ModelBlockRef d_8011DF84[2] = {
    {(s32)str_fc_tp0_clt, 0, 0}, {0, 0, 0},
};

ModelBlockRef d_8011DF94[2] = {
    {(s32)str_fc_obj_vx1, 0, 0}, {0, 0, 0},
};

ModelBlockRef d_8011DFA4[2] = {
    {(s32)str_fc_tp0_xs3, 0, 0}, {0, 0, 0},
};

ModelBlockRange d_8011DFB4 = {-1, 0, 0, 0};

ModelBlockRange d_8011DFBC[2] = {
    {1, 0x53, -0x800, 0}, {-1, 0, 0, 0},
};

ModelBlock fuchikoma_model_block = {(s32)d_8011DF84, (s32)d_8011DF94, (s32)d_8011DFA4, 0, 0, (s32)d_8011DFBC, (s32)&d_8011DFB4, 0, 0};

u8 *d_8011DFF0[2] = {
    str_fc_objcb4, NULL,
};

ScanEntry d_8011DFF8 = {{0, 0}, (s32 *)d_8012D3D0, (s32)&fuchikoma_model_block, (s32)d_8011DFF0, 0};

ModelBlockRef d_8011E010[2] = {
    {(s32)str_sdw_tp0_clt, 0, 0}, {0, 0, 0},
};

ModelBlockRef d_8011E020[2] = {
    {(s32)str_sdw_obj_vx1, 0, 0}, {0, 0, 0},
};

ModelBlockRef d_8011E030[2] = {
    {(s32)str_sdw_tp0_xs3, 0, 1}, {0, 0, 0},
};

ModelBlockRange d_8011E040 = {-1, 0, 0, 0};

ModelBlockRange d_8011E048 = {-1, 0, 0, 0};

ModelBlockRange d_8011E050[2] = {
    {0, 0, 0xC00, 0}, {-1, 0, 0, 0},
};

s16 d_8011E060[4] = {
    1, -0x8000, 0x1F, 0,
};

ModelBlock shadow_model_block = {(s32)d_8011E010, (s32)d_8011E020, (s32)d_8011E030, (s32)d_8011E050, (s32)&d_8011E040, 0, (s32)&d_8011E048, 0, (s32)d_8011E060};

ScanEntry d_8011E08C = {{0, 0}, (s32 *)d_8012D3DC, (s32)&shadow_model_block, 0, 0};

ModelBlockRef d_8011E0A4[3] = {
    {(s32)str_tst_tp0_clt, 0, 0}, {(s32)str_tst_tp1_clt, 0, 0}, {0, 0, 0},
};

ModelBlockRef d_8011E0BC[4] = {
    {(s32)str_tst_tp0_xs3, 0, 0}, {(s32)str_tst_tp1_xs3, 1, 0}, {(s32)str_tst_tp2_xs3, 1, 0},
    {0, 0, 0},
};

ModelBlockRef d_8011E0DC[3] = {
    {(s32)str_tst_obj_vx1, 0, 0},
    {(s32)str_tst_obj2_vx1, 1, 1},
    {0, 0, 0},
};

ModelBlockRange d_8011E0F4[16] = {
    {1, 1, 0x2000, 0}, {3, 7, 0x2000, 0}, {14, 15, 0x2000, 0}, {0x10, 0x11, 0x2000, 0},
    {0x14, 0x14, 0x2000, 0}, {0x16, 0x16, 0x2000, 0}, {0x20, 0x29, 0x2000, 0}, {0x30, 0x3B, 0x2000, 0},
    {0x40, 0x4C, 0x1000, 0}, {0x58, 0x6F, 0x2000, 0}, {0x71, 0x71, 0x2000, 0}, {0x73, 0x73, 0x2000, 0},
    {0x80, 0x8E, 0x2000, 0}, {0x90, 0x99, 0x2000, 0}, {0xA0, 0xAA, 0x2000, 0}, {-1, 0, 0, 0},
};

ModelBlockRange d_8011E174[4] = {
    {0x30, 0x3B, -0x400, 0}, {0x17, 0x17, -0x28, 0}, {0x18, 0x18, 0x40, 0}, {-1, 0, 0, 0},
};

ModelBlockRange d_8011E194[4] = {
    {13, 14, 0x1800, 0}, {0x20, 0x29, 0x1800, 0}, {0xA0, 0xAA, 0x800, 0}, {-1, 0, 0, 0},
};

s16 d_8011E1B4[10] = {
    4, -0x8000, 0x1F, -0x7FCE, 0x35, -0x7FB0, 0x6F, -0x7F00,
    0x10F, 0,
};

ModelBlock d_8011E1C8 = {(s32)d_8011E0A4, (s32)d_8011E0DC, (s32)d_8011E0BC, 0, (s32)d_8011E0F4, (s32)d_8011E174, (s32)d_8011E194, 0, (s32)d_8011E1B4};

ScanEntry d_8011E1EC = {{0, 0}, (s32 *)model_base_slot, (s32)&d_8011E1C8, 0, 0};

ScanItem ptr_entry_table[7] = {
    {&d_8011DF24, str_main_data}, {&d_8011DFF8, str_main_data}, {&d_8011E08C, str_main_data},
    {&d_8011E1EC, str_main_data}, {&d_8011DF48, str_main_data}, {&d_8011DF6C, str_main_data},
    {(ScanEntry *)-1, NULL},
};

ResourceRoot rec_root = {str_main_data, str_com_dat_fac, ptr_entry_table};

KeyConfig key_configs[5] = {
    {{0x80, 0x40, 0x20, 0x10, 0x1000, 0x4000, 0x2000, 0x8000, 8, 4, 2, 1}},
    {{0x80, 0x40, 0x10, 0x20, 0x1000, 0x4000, 0x2000, 0x8000, 8, 4, 2, 1}},
    {{0x20, 0x40, 0x10, 0x80, 0x1000, 0x4000, 0x2000, 0x8000, 8, 4, 2, 1}},
    {{0x10, 0x40, 8, 4, 0x1000, 0x4000, 0x2000, 0x8000, 0x20, 0x80, 2, 1}},
    {{0x80, 0x40, 0x20, 0x10, 0x1000, 0x4000, 8, 4, 0x2000, 0x8000, 2, 1}},
};

u16 palette_colours[32] = {
    0x7E40, 0x7280, 0x6AA0, 0x62C0, 0x5AE0, 0x5300, 0x4B40, 0x4360,
    0x3B80, 0x33A0, 0x2BC0, 0x27A4, 0x23A7, 0x1FAA, 0x1B8D, 0x1790,
    0x1393, 0xF96, 0xB79, 0x77C, 0x37F, 0x33F, 0x2FF, 0x2BF,
    0x29F, 0x25F, 0x21F, 0x1DF, 0x1BF, 0x17F, 0x13F, 0x11F,
};

u16 stage_clut[16] = {
    0, 0xFFFF, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

LampColour lamp_table[5] = {
    {0xF80, 0x900, 0, 0}, {0, 0xF80, 0, 0}, {0xF80, 0xF80, 0xF80, 0}, {0xF80, 0xF80, 0xF80, 0},
    {0x800, 0x1000, 0x800, 0},
};

s16 d_8011E3C0[24] = {
    0x51, 0x3E, 0x31, 0, 3, 0x56, 0x28, 0,
    3, 0x56, 0x28, 0, -0x7D, 0x5F, 0x36, 0,
    -0x7D, 0x5F, 0x36, 0, 0, 0, -1, 0,
};

s32 number_divisors[7] = {
    0xF4240, 0x186A0, 0x2710, 0x3E8, 0x64, 10,
    -1,
};

RecTemplate grenade_burst_templates[3] = {
    {1, 0, 0, 0xFF, 0, 0x40, 0, 0x80000, -0x3000, 0x4000},
    {1, 0x80, 0x80, 0x80, 0, 0x40, 0, 0x60000, -0x3000, 0x4000},
    {1, 0x40, 0x40, 0x40, 0, 0x40, 0, 0x40000, -0x1800, 0x2000},
};

u32 d_8011E454[3] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
};

s32 d_8011E460 = (s32)fn_801090F8;

s32 d_8011E464 = (s32)placement_spawn;

u32 d_8011E468 = (u32)d_8011E454;

s32 *player_model_id_ptr = NULL;
