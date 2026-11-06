#include "common.h"
#include "cop0.h"
#include "loader_types.h"

extern s32 loader_draw_bufs;
extern s32 loader_disp_env_b;
extern s32 loader_draw_env;
extern s32 loader_sprite_sets;
extern u16 loader_clut_data[];
extern u8 loader_font_tiles[];
extern s32 loader_brightness;
extern u8 D_80154590[];
extern u8 D_80154591[];
extern u8 D_80154592[];
extern u8 D_80154593[];
extern u8 D_8015458E[];
void loader_set_disp_env(void *buf, s32 x, s32 y, s32 w, s32 h);
void loader_set_draw_env(void *buf, s32 x, s32 y, s32 w, s32 h);
s32 loader_get_video_mode(void);
s32 loader_alloc_sprite_slots(u8 *src, s32 count);
void loader_upload_clut(u16 *clut, s32 x);
void loader_set_enabled(s32 enable);
void loader_pool_init(void);

#include "core/loader.c"
#include "core/loader_screen.c"
#include "sys/start.c"

