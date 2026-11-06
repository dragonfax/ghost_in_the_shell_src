#ifndef STAGE_H
#define STAGE_H

/* The stage engine, shared by all 13 stage overlays (src/stage/). Each stage's main.c defines STAGE (1-13)
 * and STAGE_ASM, the folder its not-yet-decompiled functions are included from, before including engine
 * files. The stages were built from slightly different versions of some files: `#if STAGE == n` marks
 * code that only some stages have. */

#include "stage_types.h"

extern Object obj_pool[OBJ_POOL_SIZE];
/* View-shake offsets, read as s16 by index (player_control, player_sparks_update). */
extern s16 shake_table[];
extern Object *obj_table[OBJ_POOL_SIZE];
extern Node obj_free_head, obj_free_tail;
/* Live objects: actors (enemies, figures, projectiles; run each step by world_update), list b, list c. */
extern Node obj_list_actors, obj_list_actors_tail;
extern Node obj_list_b, obj_list_b_tail;
extern Node obj_list_c, obj_list_c_tail;
extern s16 obj_free_count;
extern u16 obj_serial;
extern s16 obj_pending_count; /* freed objects not reset yet, oldest first from obj_pending */
extern Object *obj_pending;
extern Node *obj_list_cursor; /* the node obj_list_run is at; obj_free steps it back */

Node *list_remove(Node *node);
Node *list_insert_before(Node *pos, Node *node);
void list_init(Node *head, Node *tail);
void obj_set_handler(Object *obj, s32 phase, ObjHandler *handler);
void obj_free(Object *obj);
void obj_flush_one(void);
Object *obj_new(void);

extern VblankState vblank_state;
extern PadLog pad_log;
extern s32 vblank_task_handle;

void vsync_init(void);
void vsync_shutdown(void);
void *set_vblank_callback(void *callback);
void vblank_task(void);
void count_draw(void);
s32 get_fps(void);
void pad_log_enable(void);
void pad_log_disable(void);
void put_disp_env_at_vblank(void *env);
void wait_vblank_count(u32 count);
u32 get_vblank_count(void);
void set_vblank_count(u16 count);
void pad_log_reset(void);
s32 pad_log_count(void);
u32 pad_log_pop(void);
void rand_nop(void);

extern Rand rand_a; /* also mixes in the pad's high bits */
extern Rand rand_b;
extern u16 rand_seed_table[RAND_SIZE]; /* 0..4095: rand's seeds */
extern s16 SQRT[192];          /* PsyQ LIBGTE's: sqrt(n) * 0x200 for n = 64..255 (SquareRoot0's table) */

void rand_nop(void);
void rand_init(void);
void rand_reset(Rand *rand);
void rand_init_states(void);
s32 rand_a_next(void);
s32 rand_b_next(void);

extern s32 rcossin_tbl[0x1000]; /* sin in the low half, cos in the high half */
extern s16 atan_table[0x401];

s32 atan2(s32 x, s32 y);
void vector_to_angles(s32 x, s32 y, s32 z, s32 *yaw, s32 *pitch);
s32 length_sq(s32 x, s32 y, s32 z);
s32 angle_approach(s32 from, s32 to, s32 step);
void fly_move(s32 angle, s32 speed, s32 *dx, s32 *dz);
void fly_strafe(s32 angle, s32 speed, s32 *x, s32 *z);
void angles_to_vector(s32 yaw, s32 pitch, s32 len, s32 *x, s32 *y, s32 *z);
void rotate_xz_twice(s32 angle2, s32 angle1, s32 *a, s32 *x, s32 *z);
void vector_normal_scaled(VECTOR *v, SVECTOR *out);
void clut_set_stp(s32 n, u16 *clut);
void clut_make_pair(s32 n, u16 *src, u16 *dst, u8 *mask);
void pack_4bpp(s32 stride, s32 w, s32 h, s32 shift, u8 *src, u8 *dst);
s32 isqrt(s32 n);
void scale_rows(s16 *m, s16 *scale, s16 *out);
void vector_double_even(Vec3 *in, Vec3 *out);

/* PsyQ LIBGTE */
void VectorNormal(VECTOR *v, SVECTOR *out);

extern PadInput pad1;
extern s32 player_held;       /* the player's input this step (player_read_input) */
extern s32 player_pressed;
extern u32 player_status;
extern s32 move_sound_handle; /* the movement loop sound (move_sound) */

/* 1 when a lies within r of b: |a - b| <= r, as one unsigned compare. r is changed in the body so that
 * an inlined call computes it at the call, after a and b (cc1 keeps an unchanged parameter's sum until
 * its first use). */
static inline s32 in_range(s32 a, s32 b, s32 r) {
    s32 d = a - b + r;
    r <<= 1;
    return (u32)d <= (u32)r;
}

/* Loads the GTE rotation matrix from words m[0..4] (rotate_vector's matrix; damp_along, player_collide). */
static inline void set_rot_matrix(s32 *m) {
    s32 r0, r1, r2;

    __asm__ volatile("lw %1, 0(%3)\n\tlw %0, 4(%3)\n\tlw %2, 8(%3)\n\t"
                     "ctc2 %1, $0\n\tctc2 %0, $1\n\tctc2 %2, $2\n\t"
                     "lw %1, 12(%3)\n\tlw %0, 16(%3)\n\t"
                     "ctc2 %1, $3\n\tctc2 %0, $4"
                     : "=&r"(r0), "=&r"(r1), "=&r"(r2) : "r"(m));
}

extern PlayerObj player_obj;
extern s32 player_xyz[3]; /* the player's position (20.12) */
extern s32 push_z;        /* a push applied to the player; its x is 8 bytes before (ground_push) */

/* ---- Boot exe services (jump stubs through the service table at 0x80010000) ---- */

s32 svc_add_frame_task(void (*fn)(void), s32 period);
s32 svc_remove_frame_task(s32 handle);
void svc_put_disp_env(void *env);
void svc_set_disp_mask(s32 on);
s32 svc_read_pad(s32 port);

/* Service table entries the stage code calls directly. */
extern s32 (*slot_add_frame_task)(void (*fn)(void), s32 period); /* add a frame task */
extern void (*slot_sound_key_on)(s32 *block);                  /* sound key-on block (sound_voice_release) */
extern s32 (*slot_snd_alloc_channel)(s32 *block);                   /* sound request block (sound_voice_request) */
extern s32 (*slot_143)(s32 a, s32 b, s32 c);
extern s32 (*slot_0A9)(void);
extern s32 (*slot_156)(void);
extern s32 (*const slot_0B0)(s32 *block); /* const: its load may move above stores (sound_voice_keyon) */
extern void (*slot_0B3)(void);
extern void *(*slot_get_exec_code)(void);
extern s32 (*slot_148)(void);
extern s32 (*slot_15D)(s32 index);
extern s32 (*slot_remove_frame_task)(s32 handle); /* remove a frame task */
/* The heap's start (the end of the stage's bss): a word the linker put in the text section, after the libgte
 * objects. splat splits it as a one-word function (in s03, s06, s11 as a label inside the library function
 * before it); it stays asm there. */
extern s32 heap_base;
extern void (*slot_1C0)(s32);
extern void (*slot_wait_frames)(s32);
extern void (*slot_set_disp_mask)(s32);
void *svc_get_shared_state(void); /* service stub (asm, tail jump): returns a record with words at 0xC0, 0xD0 */
extern s32 (*slot_read_file)(u8 *name, void *dest, s32 mode); /* read a file (file_read_sync) */
extern s32 (*slot_read_background)(u8 *name, void *dest, s32 mode); /* read a background (file_read_background) */
extern s32 (*slot_seek)(u8 *name);                        /* seek (file_seek) */
extern void (*handler_fn_table[])(s32 index, s32 param);         /* handler_range_call's handlers */
extern void (*clear_handler_table[])(s32 index, s32 param);         /* handler_range_call_zero's handlers */
extern s32 (*slot_tone_volume)(s32);  /* VAB tone volume (sound_volume_of) */
extern s32 (*slot_144)(void);
extern void (*slot_042)(s32);
extern void (*slot_043)(s32);
extern void (*slot_0A3)(s32);
extern void (*slot_0A8)(s32);
extern void (*slot_0AA)(s32);
extern void (*slot_0AB)(s32);
extern void (*slot_0B9)(s32);
extern ResourceEntry *(*slot_resource_entry)(void *);
extern u8 exec_path_buf[]; /* path buffer get_exec_path fills */
extern s32 name_table_base;  /* set_name_table_ptr sets, name_base_get reads */

extern u8 obj_lock_counts[];  /* nonzero: obj_find_lowest_score skips the actor with that index */
extern u8 sound_handle_head;
extern u8 sound_handle_dirty;
extern ColorShift palette_expanded[32];
extern u16 palette_colours[32];
extern ObjHandlerFn obj_state_handlers[]; /* state handlers obj_run_states_default runs */
extern ObjHandlerFn obj_state_steps[]; /* obj_state_run */
extern ObjHandlerFn obj_state_steps_b[]; /* obj_state_run_b */
extern s32 hud_gfx_base;
extern const TextRgb text_fade_colours[15]; /* ui_string_draw's 5-bit colours by character index */
extern const s32 d_800B654C[5];
extern u8 d_80131E1B[];
extern u8 d_801363F3;
extern s16 view_order[];
extern void (*slot_0A4)(s32 arg);
extern void (*slot_0B7)(s32 arg);

s32 svc_video_mode(void);
void svc_draw_sync(s32 mode);
s32 printf(const char *fmt, ...);
extern char fmt_file_not_found[]; /* "File Not Found: %s\n" (shared by three file readers) */
extern char fmt_read_error[];     /* "Read Error: %s\n" */

/* Both return 1 in the retail build. */
s32 debug_check_a(void);
s32 debug_check_b(void);
extern Camera cameras[8];
extern View views[16];
extern SoundHandle sound_handles[];

s32 sound_start(s32 id, s32 volume, s32 delay, s32 arg3);
void sound_attach(s32 handle, void *owner, void (*update)());
void sound_stop(s32 handle);
extern Solid solids[32];
extern s32 solid_slot_next; /* solids in use */
extern s32 solid_active_count; /* active solids */
extern ObjHit obj_hits[128];
extern Pchr pchr_table[];
extern s32 model_pchr_saved; /* S06/S07/S09: a model slot (eng_fn_800c0e88) */
extern s16 pchr_count;
extern InterpRec18 interp_records[];
extern InterpRec1C interp1c_table[];
extern InterpRec2C interp2c_table[];
extern InterpRec38 interp38_table[];
extern InterpRec38 interp38b_table[];
extern u8 view_recs_on[]; /* 16 records of 0xA4 bytes; the s16 at +0 is cleared by view_slots_clear */
void interp_reset(Interp *interp);
extern Track track_table[8];
extern GridEntry *grid_entries;
extern GridKind grid_kind_handlers[]; /* per GridEntry kind */
extern s16 grid_buckets[0x401]; /* bucket heads: 32x32 cells, then an overflow bucket */
extern s16 grid_pending_head;        /* head of the pending list */
extern Request req_queue[64];
extern s32 req_queue_count;
extern FxRecord fx_rec34_pool[32];
extern LightSet light_sets[];
extern PointSlot point_slots[];
extern TextSlotEntry text_slots[];
extern s32 msg_id_base;

/* HUD state that the shared stage code (src/stage/eng_fn_800beabc.c ...) reads; hud_frame_draw draws it. */
extern s32 mission_enemies_left;                         /* counter value (get_enemies_left) */
extern s32 msg_text_id;                         /* message glyph (msg_show_at) */
extern s32 cam_side_blend, cam_ramp_b, msg_fade; /* fades 0..0x1000: counter, mission timer, message */
extern s32 cam_angle_acc;                         /* message blink phase */
extern s16 msg_pos_x, msg_pos_y;             /* message x, y */
extern s32 d_8011FEE4;                         /* message sound played */
extern u32 eng_mode;
extern u32 mission_state;
extern s32 grid_flagged_count;                 /* entries in the key table */
extern GridEntry *flagged_grid_cells[];                /* the pending entries flagged for the key table (get_key_table), up to 256 */
/* HUD glyph tables right after msg_id_base, at the same offsets in every stage, where they have no
 * symbols of their own (s01 d_80117920, d_80117934, d_80117948): aliases at those offsets. */
extern s32 hud_eng_glyph[5] __asm__("msg_id_base+0x4");      /* per eng_mode: counter label */
extern s32 hud_eng_digit_x[5] __asm__("msg_id_base+0x18");   /* per eng_mode: counter digits' x */
extern s32 hud_mission_glyph[3] __asm__("msg_id_base+0x2C"); /* per mission_state */
extern LightData data_base_area;  /* passed to set_data_base by obj_noop */
extern s16 loop_state_scale;
extern s16 scale_vec[3]; /* three halfwords scale_vec_set sets */   /* LoopState.scale in S01, written by loop_state_set_scale */
extern ScreenSize stage_screen_default; /* default screen size (stage_screen_size) */
extern Mover mover;
extern Vec3 displacement;
extern s32 pending_turn;
extern ModelGroup rec_table[];
extern NameEntry *name_table_root;
extern NameEntry *name_table_cwd; /* set with name_table_root by name_table_set */

/* Debug name buffers: file_name_build copies debug_name_buf, then a name, uppercased into file_name_buf. */
extern u8 debug_name_buf[];
extern u8 file_name_buf[];
extern PartSlot part_slot_recs[16];
extern AobjEntry aobj_table[];
extern KeyframeCell keyframe_cells[];
extern Slot14 lock_slots[6];
extern u8 lock_flag_counts[];
extern NodePair node_pair_table[];
extern Item7C ui_item_pool[];
extern Spark spark_pool[8];
extern HalfPair half_pairs[8];
extern IdTable id_table;
extern s32 particle_free_head; /* record 0: first free record */
extern s32 particle_free_count; /* record 0: records free */
extern u8 particle_list_tail;  /* record 0: prev */
/* The same table under a second name: the original addresses it both ways (a second name keeps GCC from
 * holding the address in a register). */
extern Particle particles[] __asm__("particle_free_head");
extern Record object_slots[8];
extern Timer timers[16];
extern s32 timer_count;
extern s32 timer_first;
extern SparkList spark_list;
extern u8 *spark_list_tail; /* tail[0] */
extern s16 spark_count; /* records in use */

/* Adds a record to the effect list (S01 giant_robot_draw; S10 func_800C6C18). */
static inline void spark_add(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

/* spark_add with the roll as u16 (no re-extension of a u16 argument; S09 func_800C7D00). */
static inline void spark_add_u(s32 x, s32 y, s32 z, s32 ry, s32 rx, u16 rz, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = list->tail[colour >> 24];
        list->tail[colour >> 24] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

/* The same add, always on chain 0 (tail[0] read as its own global spark_list_tail) and with the count read as a
 * plain scalar (S08 func_800C2128). */
static inline void spark_add_head(SparkList *list, s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    s32 n = spark_count;
    SparkRec *s;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = spark_list_tail;
        spark_list_tail = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

/* The same add with the chain's tail link located before the colour store, as a word pointer from the list
 * base (tail[chain] is link[2]: the 8 head bytes come first). The colour's last use is then the store, so in
 * a loop loop.c doesn't drag `colour >> 24` out with a hoisted colour (S12 fx_slot_draw). */
static inline void spark_add_link(s32 x, s32 y, s32 z, s32 ry, s32 rx, s32 rz, s32 value, s32 colour) {
    SparkList *list = &spark_list;
    s32 n = SPARK_COUNT;
    SparkRec *s;
    u8 **link;
    u8 *tail;

    if (n < 0xFF) {
        s = &list->items[n];
        link = (u8 **)list + (colour >> 24);
        n++;
        spark_count = n;
        *(s32 *)s->colour = colour;
        tail = link[2];
        link[2] = &s->next;
        *tail = n;
        s->next = 0;
        s->x = x;
        s->y = y;
        s->z = z;
        s->unk_12 = value;
        s->yaw = ry;
        s->pitch = rx;
        s->roll = rz;
    }
}

/* A script stream: the s16 words at an object's unk_1C.unk_04, read in order. */
static inline s32 obj_read_s16(Object *obj) {
    s16 *p = obj->script.pc;

    obj->script.pc = p + 1;
    return *p;
}

/* The same read, unsigned (script ops that store a u16). */
static inline u16 obj_read_u16(Object *obj) {
    u16 *p = (u16 *)obj->script.pc;

    obj->script.pc = p + 1;
    return *p;
}
extern ShotParams shot_params;

/* Upper clamps written as functions with the bound inside (a bound passed as a parameter compiles
 * differently). Used twice, for the value and for the test against 0 (`d = cap_1000(x); if (cap_1000(x) < 0)
 * d = 0;`), they give the original's shared compare. */
static inline s32 cap_1000(s32 v) {
    if (v > 0x1000) {
        v = 0x1000;
    }
    return v;
}

static inline s32 cap_FFF(s32 v) {
    if (v > 0xFFF) {
        v = 0xFFF;
    }
    return v;
}

static inline s32 cap_20(s32 v) {
    if (v > 0x20) {
        v = 0x20;
    }
    return v;
}
extern SceneModel scene_models[];
extern GrenadeMover grenade_pool[];
extern AllocRec sound_alloc_pool[65];
extern s32 sound_alloc_states[0x41];
extern s32 alloc_owner_tags[0x41];
extern s32 alloc_free_tags[0x41];
extern s32 alloc_prev_tags[0x41];
extern u8 sound_alloc_free_head;
extern u8 sound_alloc_used_tail;
extern s32 sound_alloc_free_count;
extern FadeRec fade_records[];
extern u8 fades_head;
extern u8 fades_free;
extern RingEntry trail_ring[RING_SIZE];

/* The stage's resource tables (resource.h): the engine's loader steps (ptr_entry_table: entry 1's model block is
 * the player's), their root, and the mission's three parts. */
extern ScanItem ptr_entry_table[];
extern ResourceRoot rec_root;
extern AreaEntry *area_entry_table[3];
void svc_load_image(void *rect, void *data); /* LoadImage */
void fn_800C4368(Object *obj, ObjHandler *handler); /* boss death sequence actor */
extern TrackRec cam_tracks[];
extern TrackRec cam_track_recs[];
extern TrackRec part_recs[];
extern ViewRec view_recs[];
extern FxEffect fx_rec30_pool[16];
extern VECTOR sound_listener_prev_pos; /* copied from sound_listener_pos at stage setup (sound_stage_init) */
extern VECTOR sound_listener_pos; /* set by sound_set_listener_pos */
extern IntPair hook_table[0x80]; /* hook_set sets one; used index range hook_range_lo..hook_range_hi */
extern IntPair cam_pairs[32];   /* count cam_pair_count (cam_pair_add) */
extern ModelSlot model_slots[];
extern void *ptr_table[0x400];  /* count ptr_table_len (ptr_table_append) */
extern s32 *block_map_buf, *texel_mask_buf; /* the buffers of the last model slot (model_slot_new) */
extern u8 *clut_used_flags;             /* 16 palette-used flags per slot (palette_mark_ranges) */
extern u8 image_buf[];
extern u8 cell_flags[256];       /* per 64-unit cell: nonzero taken, bit 0 blocked (cell_next_free) */
extern char debug_menu_text_rows[][0x20];  /* debug menu text rows */
extern s16 d_8011E3C0[];         /* layout data for id_table_add_layout */
extern KeyConfig key_configs[5];  /* the five key configurations (get_key_config) */
extern s32 key_config_index;           /* the selected one */
extern FadeItem fade_items[];
extern WorkArea *work_area_ptr;

/* The current area (mission * 3 + part; get_area, set_area): a data word at the end of the code, which splat
 * splits as a 4-byte "function" (its INCLUDE_ASM stays). */
extern s32 area;
extern u32 bg_buffer;          /* the background job's buffer (an address, compared with the heap top) */
extern PadInput pad_mirror; /* a second input state, reset with pad1 (input_reset) */
extern s16 stage_screen_w;      /* screen width */
extern UnalignedVec warp_rot;
extern s32 object_slots_free;
extern s32 sound_release_caller;
extern s32 sound_release_reason;

extern s16 pchr_count_saved;           /* spark_list_clear copies pchr_count into it */
extern void *(*part_record_resolve_table[])(u32); /* part_record_read's handlers, by bits 16-23 of the key */
extern u32 fx_style_table[24];
extern s32 d_80120470;
extern s32 cam_distance;
extern s32 cam_offset_blend;
extern s32 d_80136418, d_80136414, d_80136410;
extern s32 d_80136430, d_8013642C, d_80136428;
extern s32 d_80136448, d_80136444, d_80136440;
extern s32 cam_view_state_table, cam_view_handler0;
extern s32 cam_follow_blend;
extern s32 d_8012049C;
extern s32 d_80136408, player_roll;
extern s32 player_mode_flags_saved;
extern s32 d_8013644C, d_80136450;
extern s32 d_801364C8, d_801364E4;
extern s32 wall_query_cache;
extern s32 d_801363F8;
extern s32 d_801363FC;
extern s32 d_80136400;
extern u8 tex_tint_rgb, tex_pal0_g, tex_pal0_b;
extern void *text_packet_cur;
extern s16 text_packet_index;
extern u8 text_packets[];
extern s32 font_page_x;
extern s32 font_page_y;
extern s32 font_y_offset;
extern s32 texpage_current;
extern RECT font_tex_window;
extern u8 font_cell_uv_table;
extern u8 font_cell_v;

static inline void *scratch_alloc(s32 size) {
    u8 *p = scratch_top;

    scratch_top += size;
    return p;
}

/* x / 3 for x >= 0: the mult by 0x55555556 whose mfhi the shell sorts schedule themselves */
static inline s32 div3_pos(s32 x)
{
    s32 q;
    div3_hi(q, x);
    return q;
}

/* Loads the 3x3 rotation matrix at m (5 words, as rot_matrix writes it) into the GTE. */
static inline void rot_load(s32 *m) {
    s32 a, b, c;

    __asm__ volatile("lw %0, 0(%3)\n\tlw %1, 4(%3)\n\tlw %2, 8(%3)\n\t"
                     "ctc2 %0, $0\n\tctc2 %1, $1\n\tctc2 %2, $2"
                     : "=&r"(a), "=&r"(b), "=&r"(c)
                     : "r"(m));
    __asm__ volatile("lw %0, 12(%2)\n\tlw %1, 16(%2)\n\tctc2 %0, $3\n\tctc2 %1, $4"
                     : "=&r"(a), "=&r"(b)
                     : "r"(m));
}

/* a - b for 12-bit angles, each wrapped to -0x7FF..0x800 */
static inline s32 angle_diff(s32 a, s32 b) {
    s32 d;

    a &= 0xFFF;
    if (a > 0x800) {
        a -= 0x1000;
    }
    b &= 0xFFF;
    if (b > 0x800) {
        b -= 0x1000;
    }
    d = (a - b) & 0xFFF;
    if (d > 0x800) {
        d -= 0x1000;
    }
    return d;
}
/* The GTE rotation matrix from mat / to mat (words 0..4). */
static inline void rot_matrix_load(RotMatrix *mat) {
    s32 a, b, c;

    gte_load_R012(mat, a, b, c);
    gte_load_R34(mat, a, b);
}
static inline void rot_matrix_save(RotMatrix *mat) {
    s32 a, b, c;

    gte_store_R012(mat, a, b, c);
    gte_store_R34(mat, a, b);
}

extern void (*actor_hook)(); /* actor_hook_fn while the actors run (actors_phase1) */
extern RecTemplate grenade_burst_templates[];
extern s16 gun_hit_effect_table[][9];
extern SolidCoords solid_slots[];
extern s32 value_queue_index;
extern s16 value_queue[];
extern Next800C5620 *fade_red_obj;
extern SoundPair sway_state;
extern TrackDims track_dims[];
/* Takes a record off fades_free and pushes it on fades_head; NULL when none is free (effect_spawn_at). */
static inline FadeRecFull *fade_alloc(void) {
    u32 idx = fades_free;
    FadeRecFull *r;

    if (idx == 0xFF) {
        return NULL;
    }
    r = &((FadeRecFull *)fade_records)[idx];
    fades_free = r->next;
    r->next = fades_head;
    fades_head = idx;
    return r;
}
extern s16 debug_cam_pan_x;
extern s16 debug_cam_pan_y;
extern AngleEntry801188EE cos_table[];
extern s32 rec_pos_total;
extern u16 fx_grey_clut_buf[];
extern u16 fx_palette_table[];
extern s32 placement_angle_table;
extern FxRecordParams ripple_fx_params;
extern s16 cyl_table[];
extern s32 beam_model_base;
extern s16 debug_cam_speed_table[][2];
extern UiRecord ui_rec_table[];
extern s16 player_tilt_x;
extern s16 player_tilt_z;
extern LoopState loop_state;
extern s32 id_marker_pushed;
extern u8 rec_table_pos[];
extern u8 rec_table_flag[];
extern s32 clut_count;

static inline s32 in_box_800C0D44(GridBox *box, s32 x, s32 y, s32 z) {
    if (x < box->x0 || x > box->x1 || y < box->z0 || y > box->z1 || z < box->y0 || z > box->y1) {
        return 0;
    }
    return 1;
}

/* v / 0x2000 rounded toward zero */
static inline s32 half_shift(u32 v) {
    return (s32)(v + (v >> 31)) >> 13;
}
extern s32 wall_tables_ptr;
extern s16 d_801395B8;
extern s16 d_801395B4;
extern s32 max_apex_count;
extern s32 max_poly_count;
extern ScriptPcSlot smg_soldier_hit_script;
extern s16 *smg_soldier_data[9];
extern s16 *rocket_fuchikoma_data[];
extern s32 player_vertical_blocked;
extern s32 player_ground_id;
extern s32 d_8011E460;
extern s32 d_8011E464;
extern s32 shade_angle;
extern GunSetup shot_twin_desc;

extern s32 d_80137118[];

extern u8 debug_menu_marks[];
extern u8 debug_menu_flag_cell[];
extern u16 stage_image_width;
extern u16 stage_image_height;
extern u8 stage_image_pixels[];
extern u16 stage_clut[16];   /* 16-colour CLUT, uploaded at (0x70, 0x120) */
extern TrailOffset trail_offsets[];

extern char str_total_label[];
extern char str_score_label[];
extern s32 result_time_bonus;
extern s32 result_shield_bonus;
extern s32 result_grenade_bonus;
extern s32 result_total;
extern s32 result_score;
extern PathPoint cam_path_smooth;
extern s32 cam_path_smooth_y;
extern s32 cam_path_smooth_z;
extern s32 cur_view_index;
extern s32 light_env_index;
extern LightEnv light_envs[];
extern s16 view_scale_base[];
extern u8 light_env_depth_cue[];
extern s16 player_height;
extern ViewRecord d_801366D4[];
extern ViewRecord d_801366D6[];
extern ViewRecord view_screen_offsets[];

extern s32 mission_result_slide_x, mission_result_base_y, mission_result_zoom, mission_result_zoom_slow;
extern s32 result_hitrate, result_kill_count, result_class, result_rank_place, mission_result_exit_flag;

extern s32 cam_fade_amount;
extern s32 view_split_amount;
extern s32 cur_camera_index;
extern s16 camera_light_env_table[];

extern s16 tint_scale_r;
extern s16 tint_scale_g;
extern s16 tint_scale_b;
extern s16 tint_add_r;
extern s16 tint_add_g;
extern s16 tint_add_b;

extern u16 d_8012020E;
extern u16 d_80120210;

extern s32 player_rel_vy;
extern s32 player_rel_vz;

extern s32 d_8011DD70;

extern s32 last_env_colour_a;
extern s32 last_env_colour_b;
extern s32 last_env_colour_c;
extern InterpPair interp2c_parts[];
extern InterpTriple interp38_parts[];
extern TexelRemapRow texel_remap_rows[];

extern void (*part_cmd_table[])(PartSlot *slot, s32 *args, s32 cmd);

extern u8 particle_list_head;

extern s16 cur_cam_index;

extern s32 clamp_table_default[];
extern s32 colour_table_default[];
extern s32 slope_table_default[];
extern s32 d_8011D744[];
extern s32 d_8011D768[];
extern s32 d_8011D778[];
extern s32 *d_80153348;
extern s32 *ground_tile_table;
extern s32 *d_80153350;
extern s32 *d_80153354;

extern s16 capture_width;
extern s16 capture_height;
extern u8 screenshot_name_ptr[];
extern AllocLink sound_alloc_links[];
extern s16 tile_pos[][2]; /* tile (x, y), copied as TilePos */
extern s16 tile_pos_next[][2];

extern s16 d_8011E510[];

extern u16 texture_image[];
extern u16 clut_image[256];  /* 256-colour CLUT row, uploaded at (0x100, 0xDC) */
extern CameraReach camera_reach_normal;
extern CameraReach camera_reach_wide;
extern DrawView draw_views[];
extern s16 view_index_table[];

extern s32 pose_joint_indices[2][5];

extern s32 player_turn_dir;

extern u32 sincos_deg270[];
extern u32 sincos_deg90[];

extern s16 pose_shift_vx, pose_shift_vy, pose_shift_vz;
extern s16 pose_shift2_vx, pose_shift2_vy, pose_shift2_vz;
extern VECTOR spark_point_table[5];
extern s32 fx_depth_thresholds[];

extern s32 number_divisors[7]; /* powers of ten 1e6..10, then -1 */
extern RectU mask_buf_rect; /* the mask buffer's VRAM rect {0x300, 0, 0x100, 0xD8} */

extern s32 stage_saved_flag;
extern s32 stage_heap_mark;
extern u8 d_800A0000[];
extern CamViewSource cam_view_src_default;
extern CamViewSource cam_view_src_model;
extern s16 mask_area_x;
extern s16 mask_area_y;
extern s16 mask_area_w;
extern s16 mask_area_h;
extern s16 mask_fade_x;
extern s16 mask_fade_y;
extern u32 *mask_draw_ot;

extern s32 player_coll_part;
extern s32 hit_spark_pchr;
extern s32 *player_model_id_ptr;
extern s32 d_8012BBDC;
extern s32 d_8012BBF8;
extern s32 d_8012BBFC;

extern s32 d_8011FFE4;

extern s32 sound_key_voice;
extern s32 sound_key_volume;
extern s32 sound_key_rate;
extern s16 sound_key_pan;
extern s16 sound_key_note;
extern s16 sound_key_pitch;
extern s16 sound_key_mode;

extern u8 light_env_colours[];
extern const u32 cam_fade_tex_window[2];

extern s16 clip_index_stream[];
extern s32 player_hit_flash;

extern s16 *fx_glow_tables[];
extern ViewTail view_tails[];
extern s16 light_rec_head;

extern InterpTriple interp38b_triples[];
extern LampColour lamp_table[];

extern s16 d_800B6604[];

extern s16 spark_red_table[];
extern s16 spark_green_table[];
extern LensFlare lens_flare_table[];
extern Solid solid_backup;
extern CamRotation cam_rotations[];
extern ViewLightParams view_light_params[];

/* Low-bit masks (1 << (i + 1)) - 1, indexed by solid_count - 1 (solid collision, eng_rotate_vector.c). */
extern u32 solid_masks[];
/* The view's sin/cos pairs: cos in the high halfword, sin in the low (S01's own table; an alias into rcossin_tbl elsewhere). */
extern u32 view_sincos[];

#ifndef NO_STAGE_DECLS
#include "stage_decls.h"

/* Byte-swaps the low halfword (handle_load). */
static inline s32 swap16(s32 v) {
    return ((v & 0xFF) << 8) | ((v & 0xFF00) >> 8);
}

/* A script command word read with its halfwords byte-swapped (handle_load). */
static inline s32 cmd_swap(s32 w) {
    s32 hi = swap16(w) << 16;
    s32 lo = swap16(w >> 16);

    return hi | lo;
}

/* Bit `bit` of a (signed) field: lh, srl, andi 1. */
static inline s32 test_bit(u32 value, s32 bit) {
    return (value >> bit) & 1;
}

/* Inlined in several functions: the area is not the first of its group of three and the part timer
 * (part_timer_get) is not on. */
static inline s32 untimed_part(void) {
    if (get_area() % 3 == 0) {
        return 0;
    }
    return part_timer_get() != 1;
}

/* Whether the area is the last of a final stage (record_run_result; early returns, not one condition). */
static inline s32 is_final_area(void) {
    if (get_area() / 3 == 0xC) {
        return 1;
    }
    if (get_stage_end() == 3) {
        return 1;
    }
    if (get_stage_end() == 2 && get_area() / 3 == 0xB) {
        return 1;
    }
    return 0;
}

/* The player's distance to the object, or to its placement's target point. */
static inline s32 player_dist_to_obj_point(Object *obj, s32 from_placement) {
    s32 *pos = player_position();
    s32 *point = from_placement ? &((PlacedTarget *)obj->placement)->x : &obj->x;

    return isqrt(length_sq(pos[0] - (point[0] >> 12), pos[1] - (point[1] >> 12), pos[2] - (point[2] >> 12)));
}

/* Enemy turning helpers inlined in the soldiers' shot starts (enemy_start_burst, enemy_start_shot). */
static inline s32 bearing_to_player(Object *obj) {
    s32 *player_pos = player_position();
    return atan2(player_pos[2] - (obj->z >> 12), player_pos[0] - (obj->x >> 12));
}
static inline s16 player_outside_arc(Object *obj, s32 limit) {
    s32 yaw;

    if (bearing_to_player(obj) - (yaw = obj->yaw) >= 0) {
        if (bearing_to_player(obj) - obj->yaw > limit) {
            return 1;
        }
        return 0;
    } else {
        if (yaw - bearing_to_player(obj) > limit) {
            return 1;
        }
        return 0;
    }
}
static inline void turn_toward_player(Object *obj, s32 rate) {
    s16 aim_yaw = bearing_to_player(obj);
    s32 old_yaw = obj->yaw;
    s16 new_yaw = angle_approach(old_yaw, aim_yaw, rate);
    s32 turn = new_yaw;

    obj->yaw = new_yaw;
    turn -= old_yaw;
    obj->turn = turn;
}
#endif

/* a - b as an angle in (-0x800, 0x800]. */
static inline s32 ang_diff(s32 a, s32 b) {
    s32 d;

    a &= 0xFFF;
    if (a >= 0x801) {
        a -= 0x1000;
    }
    b &= 0xFFF;
    if (b >= 0x801) {
        b -= 0x1000;
    }
    d = (a - b) & 0xFFF;
    if (d >= 0x801) {
        d -= 0x1000;
    }
    return d;
}

/* |ang_diff(a, b)|. */
static inline s32 ang_abs_diff(s32 a, s32 b) {
    if (ang_diff(a, b) >= 0) {
        return ang_diff(a, b);
    }
    return -ang_diff(a, b);
}

/* |ang_diff(a, b)| as an expression: a comparison against it is folded into both arms (obj_patrol_update). */
#define ANG_ABS_DIFF(a, b) (ang_diff(a, b) >= 0 ? ang_diff(a, b) : -ang_diff(a, b))

#endif
