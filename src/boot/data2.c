/* boot data 0x80041938-0x80042000: the binary's data as C, made by
   scripts/data_c.py from splat's split: the code's types where they reproduce the bytes, else plain
   arrays. */

#include "common.h"
#include "incbin.h"
#include "boot_types.h"

extern void ClearImage();
extern void ClearOTag();
extern void ClearOTagR();
extern void DecDCTGetEnv();
extern void DecDCTPutEnv();
extern void DecDCTin();
extern void DecDCTout();
extern void DecDCToutCallback();
extern void DrawOTag();
extern void DrawPrim();
extern void DrawSync();
extern void DrawSyncCallback();
extern void GetDispEnv();
extern void GetDrawEnv();
extern void GetGraphType();
extern void GetVideoMode();
extern void LoadImage();
extern void MoveImage();
extern void SetDispMask();
extern void SetDrawArea();
extern void SetDrawEnv();
extern void SetDrawMode();
extern void SetDrawOffset();
extern void SetTexWindow();
extern void SetVideoMode();
extern void StoreImage();
extern void boot_flag_get();
extern void card_check_slot();
extern void card_clear_slot();
extern void card_close();
extern void card_create_checked();
extern void card_create_file();
extern void card_erase_checked();
extern void card_erase_file();
extern void card_find_entry();
extern void card_find_entry_checked();
extern void card_format_slot();
extern void card_info_slot();
extern void card_load_slot();
extern void card_next_entry();
extern void card_poll_event();
extern void card_poll_result();
extern void card_poll_status();
extern void card_read_file();
extern void card_read_file_checked();
extern void card_write_data();
extern void card_write_data_checked();
extern void cardname_buf_get();
extern void cd_cmd_guarded();
extern void cd_cmd_set_volume();
extern void cd_get_sector();
extern void cd_msf_to_sector();
extern void cd_sector_poll();
extern void cd_sector_to_bcd_msf();
extern void cd_sector_to_msf();
extern void cd_seek();
extern void cd_wait_idle();
extern void cdfs_file_size();
extern void cdfs_open();
extern void cdfs_open_from_root();
extern void cdfs_read();
extern void cdfs_read_done();
extern void cdfs_read_file();
extern void cdfs_try_read();
extern void cdfs_wait_read();
extern void dct_reset();
extern void disp_rect_init_mode();
extern void draw_env_put();
extern void exec_get_code();
extern void exec_get_entry();
extern void exec_get_index();
extern void exec_set_index();
extern void font_glyph_get();
extern void frame_task_add();
extern void frame_task_remove();
extern void frame_wait_ticks();
extern void func_80018F48();
extern void func_80019034();
extern void func_8001A48C();
extern void func_8001A6EC();
extern void func_8001A7C8();
extern void func_8001CB0C();
extern void func_8001D0C8();
extern void func_80021C00();
extern void func_80021C08();
extern void get_cd_sector_ready();
extern void get_frame_counter();
extern void get_pad_port_byte();
extern void graph_buf_init_wrap();
extern void graph_reset();
extern void movie_get_entry();
extern void msg_queue_has_items();
extern void music_get_offset();
extern void music_play_by_id();
extern void music_table_find();
extern void pad_read_buttons();
extern void put_disp_env_checked();
extern void read_background();
extern void reverb_set();
extern void sched_lock();
extern void sched_unlock();
extern void snd_alloc_channel();
extern void snd_cd_fade_in();
extern void snd_cd_fade_out();
extern void snd_fade_in();
extern void snd_fade_out();
extern void snd_get_mode();
extern void snd_is_cd_fading();
extern void snd_is_fading();
extern void snd_set_cd_volume();
extern void snd_set_mode();
extern void snd_set_volume();
extern void snd_volume_busy_set();
extern void sound_active_mask();
extern void sound_key_on();
extern void sound_key_on_all();
extern void sound_req_active_id();
extern void sound_slot_flag_set();
extern void sound_slots_mark_all();
extern void spu_transfer_flag_set();
extern void spufunc_reverb_enable();
extern void spufunc_set_reverb_depth();
extern void stream_setup();
extern void stream_slot_release();
extern void stream_slot_take_ready();
extern void stream_stop();
extern void svc_unimplemented();
extern void sys_get_country();
extern void sys_get_settings();
extern void sys_get_warning();
extern void sys_is_pal();
extern void thread_change();
extern void thread_close();
extern void thread_open();
extern void thread_set_handle();
extern void unpex_decompress();
extern void vab_load();
extern void vab_open();
extern void vab_slot_set_range();
extern void vab_slot_unload_guarded();
extern void vab_tone_volume();
extern void xa_pause_if_flagged();
extern void xa_play_start();
extern void *actors_slot_table[16];
extern void *D_80041978[];
extern char sys_default_root[];
extern u8 *cfg_cache_key;
extern u8 *cfg_find_cache_result;
extern u8 *cfg_cache_entry;
extern s32 cfg_cache_pos;
extern char cfg_separators[];
extern void *D_800419A8[];
extern void *file_slot_table[];
extern void *mdec_slot_table[];
extern void *gpu_slot_table[];
extern void *sound_svc_slot_table[];
extern void *pad_slot_table[];
extern void *thread_slot_table[];
extern void *frame_slot_table[];
extern u32 cfg_value_buffer[];
extern s32 cfg_text;
extern s32 cfg_section;
extern u32 D_80041CD4[];

void *actors_slot_table[16] = {
    (void *)func_8001A48C, (void *)func_8001A6EC, (void *)sys_get_country, (void *)sys_get_warning, (void *)sys_is_pal, (void *)unpex_decompress,
    (void *)exec_set_index, (void *)exec_get_index, (void *)exec_get_code, (void *)cardname_buf_get, (void *)movie_get_entry, (void *)sys_get_settings,
    (void *)func_8001A7C8, (void *)boot_flag_get, (void *)exec_get_entry, NULL,
};

void *D_80041978[2] = {
    (void *)font_glyph_get, NULL,
};

char sys_default_root[16] = "\134GITS_TEC\134ROOT\000";

u8 *cfg_cache_key = NULL;

u8 *cfg_find_cache_result = (u8 *)0x80000000;

u8 *cfg_cache_entry = (u8 *)0x80000000;

s32 cfg_cache_pos = 0x7FFF;

char cfg_separators[8] = "*;#:'\042\000";

void *D_800419A8[23] = {
    (void *)card_poll_event, (void *)card_create_checked, (void *)card_read_file_checked, (void *)card_write_data_checked, (void *)card_format_slot, (void *)card_find_entry_checked,
    (void *)card_next_entry, (void *)card_check_slot, (void *)card_erase_checked, (void *)card_poll_status, (void *)card_poll_result, (void *)func_80018F48,
    (void *)func_80019034, (void *)card_info_slot, (void *)card_clear_slot, (void *)card_load_slot, (void *)card_create_file, (void *)card_read_file,
    (void *)card_write_data, (void *)card_erase_file, (void *)card_find_entry, (void *)card_close, NULL,
};

void *file_slot_table[31] = {
    (void *)cd_cmd_guarded, (void *)cd_wait_idle, (void *)svc_unimplemented, (void *)music_play_by_id, (void *)xa_pause_if_flagged, (void *)cdfs_read_file,
    (void *)read_background, (void *)cdfs_read, (void *)cdfs_wait_read, (void *)cdfs_read_done, (void *)cdfs_try_read, (void *)stream_setup,
    (void *)xa_play_start, (void *)stream_slot_take_ready, (void *)stream_slot_release, (void *)stream_stop, (void *)cd_sector_poll, (void *)get_cd_sector_ready,
    (void *)cd_seek, (void *)cdfs_open, (void *)cdfs_open_from_root, (void *)svc_unimplemented, (void *)music_get_offset, (void *)cdfs_file_size,
    (void *)cd_get_sector, (void *)cd_sector_to_msf, (void *)cd_msf_to_sector, (void *)cd_sector_to_bcd_msf, (void *)msg_queue_has_items, (void *)music_table_find,
    NULL,
};

void *mdec_slot_table[7] = {
    (void *)dct_reset, (void *)DecDCToutCallback, (void *)DecDCTin, (void *)DecDCTout, (void *)DecDCTPutEnv, (void *)DecDCTGetEnv,
    NULL,
};

void *gpu_slot_table[28] = {
    (void *)graph_reset, (void *)put_disp_env_checked, (void *)draw_env_put, (void *)frame_wait_ticks, (void *)SetDispMask, (void *)ClearOTag,
    (void *)ClearOTagR, (void *)DrawOTag, (void *)LoadImage, (void *)ClearImage, (void *)DrawSync, (void *)SetDrawMode,
    (void *)GetGraphType, (void *)GetDispEnv, (void *)GetDrawEnv, (void *)SetDrawEnv, (void *)SetDrawOffset, (void *)SetDrawArea,
    (void *)StoreImage, (void *)MoveImage, (void *)DrawPrim, (void *)SetVideoMode, (void *)GetVideoMode, (void *)SetTexWindow,
    (void *)DrawSyncCallback, (void *)graph_buf_init_wrap, (void *)disp_rect_init_mode, NULL,
};

void *sound_svc_slot_table[31] = {
    (void *)vab_open, (void *)vab_load, (void *)spu_transfer_flag_set, (void *)vab_slot_unload_guarded, (void *)snd_set_volume, (void *)snd_is_fading,
    (void *)snd_fade_in, (void *)snd_fade_out, (void *)snd_set_cd_volume, (void *)snd_is_cd_fading, (void *)snd_cd_fade_in, (void *)snd_cd_fade_out,
    (void *)snd_volume_busy_set, (void *)func_8001CB0C, (void *)snd_set_mode, (void *)snd_get_mode, (void *)sound_req_active_id, (void *)snd_alloc_channel,
    (void *)sound_key_on, (void *)sound_slots_mark_all, (void *)reverb_set, (void *)sound_slot_flag_set, (void *)func_8001D0C8, (void *)spufunc_reverb_enable,
    (void *)cd_cmd_set_volume, (void *)spufunc_set_reverb_depth, (void *)sound_active_mask, (void *)vab_slot_set_range, (void *)vab_tone_volume, (void *)sound_key_on_all,
    NULL,
};

void *pad_slot_table[5] = {
    (void *)pad_read_buttons, (void *)get_pad_port_byte, (void *)func_80021C00, (void *)func_80021C08, NULL,
};

void *thread_slot_table[7] = {
    (void *)thread_open, (void *)thread_close, (void *)thread_change, (void *)thread_set_handle, (void *)sched_lock, (void *)sched_unlock,
    NULL,
};

void *frame_slot_table[5] = {
    (void *)frame_task_add, (void *)frame_task_remove, (void *)frame_wait_ticks, (void *)get_frame_counter, NULL,
};

u32 cfg_value_buffer[64] = {0};

s32 cfg_text = 0;

s32 cfg_section = 0;

u32 D_80041CD4[203] = {0};

