#include "common.h"
#include "title_types.h"

/* TITLE builds primitives at $gp and bumps it, like the stages' scratch allocator (scratch_top: common.h) */

extern TitleCtrl card_ctrl;

void title_noop(void);
void title_init(void);
void title_ctl_start(void);
void title_draw_buffer_swap(void);
s32 title_queue_count(void);
u32 * title_get_pad_state();
void title_pad_update(s32 index);
void tasks_update(void);
void title_sound_update(void);
s32 title_phase_get(void);
void tasks_draw(void);
s32 title_draw_sync(s32 mode);
void frame_wait(void);
void frame_end(void);
void title_teardown(void);

/* TITLE's frame loop: per frame one input step for each pad reading queued since the last frame, then the draw pass
 * on a scratchpad stack, until the phase becomes 1 (FINDINGS "TITLE's frame loop"). */
#include "core/title_main.c"
#include "core/title_input.c"
#include "menu/file_menu.c"
#include "menu/title_menu.c"
#include "menu/title_anim.c"
#include "menu/card_wait.c"
#include "gfx/title_draw.c"
#include "menu/panel.c"
#include "scene/title_scene.c"
#include "sound/sound_mode.c"
#include "sound/title_tones.c"
#include "sys/start.c"

