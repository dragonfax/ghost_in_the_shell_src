#ifndef TITLE_TYPES_H
#define TITLE_TYPES_H

/* title's types (main.c's code, data.c and bss.c include this; types only, so the data files can include
 * it without main.c's declarations of the objects they define). */

#include "common.h"

/* from sprite_sets_register */
typedef struct TitleSetSlot {
    s32 sizeA;      /* byte size of table A (entries * 8) */
    s32 present;    /* first word of the set; 0 = empty */
    s32 sizeB;      /* byte size of table B (entries * 4) */
    void *tableA;   /* 0x0C: sprite set: table A; model (title_model_draw): vertex table (x, y, z) the quads index */
    void *tableB;   /* 0x10: sprite set: table B; model: colour table */
    s32 groupCount; /* 0x14: index + 1 of the last non-empty group; model: group count */
    s32 *groups;    /* 0x18: model: per group quad count, radius, centre (x | y << 16, z), then the TitleQuads */
    s32 pad_1C;
} TitleSetSlot;

/* from sprite_sets_register */
typedef struct TexSpritePrim {
    u8 pad_0[0x10];
    u8 u0, v0, u1, v1, u2, v2, u3, v3;
    u16 clut;
    u16 tpage;
    u32 mode; /* texture window in 8-pixel units, flags in the top byte */
} TexSpritePrim;

/* from title_draw_gt4_faces */
typedef struct TitleGt4Face {
    u32 xy01;       /* 0x00: offsets of vertices 0 (low half) and 1 (high half) into the screen xy table */
    s32 xy23;       /* 0x04: offsets of vertices 2 and 3 */
    s16 colour[4];  /* 0x08: byte offsets into the colour table, one per vertex */
    u32 uv01;       /* 0x10: uv0 | uv1 << 16 */
    u32 uv23;       /* 0x14: uv2 | uv3 << 16 */
    u32 tpage_clut; /* 0x18: clut | tpage << 16 */
    s32 flags;      /* 0x1C: texture window (low 24 bits), semi-transparent (bit 27), quad (bit 30) */
} TitleGt4Face;

/* from title_sprite_draw */
typedef struct TitleTile {
    u8 link[3];
    u8 len;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    s16 w;
    s16 h;
} TitleTile;

/* from title_project_verts_offset */
typedef struct TitlePackedVertex {
    s32 xy;
    s16 z;
    s16 pad_6;
} TitlePackedVertex;

/* from title_ft4_faces_draw */
typedef struct TitleFt4Face {
    u32 xy01;       /* 0x00: offsets of vertices 0 (low half) and 1 (high half) */
    s32 xy23;       /* 0x04: offsets of vertices 2 and 3 */
    s16 colour;     /* 0x08: byte offset into the colour table */
    u8 pad_0A[6];
    u32 uv01;       /* 0x10: uv0 | uv1 << 16 */
    u32 uv23;       /* 0x14: uv2 | uv3 << 16 */
    u32 tpage_clut; /* 0x18: tpage | clut << 16 */
    s32 flags;      /* 0x1C */
} TitleFt4Face;

/* from title_cursor_draw */
typedef struct TitleCursorTri {
    s32 a, b, c;
} TitleCursorTri;

/* from title_cursor_draw */
typedef struct TitleMatrix {
    s16 m[3][3];
    s32 t[3];
} TitleMatrix;

/* A title_matrix_pool entry (title_item_current): light directions, then light colours (title_model_draw). */
typedef struct TitleLightMatrices {
    TitleMatrix dir;
    TitleMatrix colour;
} TitleLightMatrices;

/* from title_menu_task_update */
typedef struct TitleMenuChild {
    u8 pad_00[0x1C];
    s16 state; /* 0x1C */
} TitleMenuChild;

/* from title_menu_task_update */
typedef struct TitleSoundModeView {
    u8 pad_00[0x94];
    s32 unk_94;
} TitleSoundModeView;

/* from title_file_menu_draw */
typedef struct TitleFileMenu {
    s16 unk_00;
    s16 visible;
    s16 state;
    s16 pad_06;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u8 *title;
    s16 cursor;
    s16 pad_16;
    s16 slot_status[3];
    s16 pad_1E;
    u8 cursor_buf[8];
    u8 *colors[4]; /* 0x28: corner colors (RGB bytes) for title_record_set */
} TitleFileMenu;

/* from title_file_menu_draw */
typedef struct TitleFileMenuTask {
    u8 pad_00[0x14];
    TitleFileMenu *menu;
} TitleFileMenuTask;

/* from title_cell_table_build */
typedef struct TitleCellTail {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u16 pad_06;
} TitleCellTail;

/* from sound_panel_draw */
typedef struct TitlePanelRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 scale; /* 0x1000 = fully open */
} TitlePanelRect;

/* from title_glyph_row_build */
typedef struct GlyphBuf {
    u8 pixels[16][16];
    u16 packed[16][4];
} GlyphBuf;

/* from title_seq_init */
typedef struct TitleXformSeed {
    u16 x;
    u16 y;
    u16 z;
    u16 unk_06;
} TitleXformSeed;

/* from title_seq_init */
typedef struct TitleXformRec {
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    u8 pad_06[0x0A];
    u16 vel_x;
    u16 vel_y;
    u16 vel_z;
    u16 unk_16;
    u16 origin_x;
    u16 origin_y;
    u16 origin_z;
    u8 pad_1E[0x0A];
    u16 dir_x;
    u16 dir_y;
    u16 dir_z;
    u16 unk_2E;
    u16 frames_left;
    u8 pad_32[2];
} TitleXformRec;

/* from title_state_update */
typedef struct TitleVec3 {
    s32 x, y, z;
} TitleVec3;

/* from title_state_update */
typedef struct TitleSubState {
    u8 mode[5];                 /* 0x00: mode[0] = 2 on init */
    u8 pad_05[3];
    TitleVec3 a[5];      /* 0x08 */
    TitleVec3 b[5];      /* 0x44 */
    u8 flag;                    /* 0x80: set to 1 on init */
    u8 pad_81[0x13];            /* 0x81..0x93: 0x80..0x90 cleared on init */
    s32 unk_94;
} TitleSubState;

/* from title_state_update */
typedef struct TitleMainState {
    s32 inited;                 /* 0x00 */
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 input_mask;
    s32 input_step;
    s16 rect_x;
    s16 rect_y;
    s16 rect_w;
    s16 rect_h;
    s32 unk_20;
    TitleSubState sub;       /* 0x24 */
    s32 unk_BC;
    s32 unk_C0;
    s32 unk_C4;
    s32 unk_C8;
    s32 unk_CC;
} TitleMainState;

/* from title_fade_draw */
typedef struct TitleFadeParams {
    s16 level;
    s16 unk_02;
    s16 unk_04;
    s16 mode;
} TitleFadeParams;

/* from title_glyph_row_draw */
typedef struct TitleGlyphRow {
    u16 tpage;  /* draw-mode tpage for the first 256 pixels */
    u16 clut;
    u16 v;      /* texture row */
    u16 count;  /* glyphs */
    u16 tpage2; /* tpage once u wraps past 256 */
    u16 pad_A;
} TitleGlyphRow;

/* from title_glyph_row_draw */
typedef struct TitleGlyphPos {
    s16 x, y;
    s16 pad_4[2];
    u16 u, v;
} TitleGlyphPos;

/* from title_spark_init */
typedef struct TitleSpark {
    u8 color_r;
    u8 color_g;
    u8 color_b;
    u8 unk_03;
    s16 pos_x;
    s16 pos_y;
    s16 pos_z;
    u8 pad_0A[0xA];
    s16 vel_x;
    s16 vel_y;
    s16 vel_z;
    u8 pad_1A[2];
    s16 life;
    u8 pad_1E[4];
    s16 life_step;
} TitleSpark;

/* from title_fx_update */
typedef struct TitleRecAddrs {
    /* 0x00 */ u8 unk_00[0x54];
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
} TitleRecAddrs;

/* from title_timer_draw */
typedef struct TitleSprt {
    u8 link[3];
    u8 len;
    u8 r, g, b, code;
    s16 x, y;
    u8 u, v;
    u16 clut;
    s16 w, h;
} TitleSprt;

/* from title_timer_draw */
typedef struct TitleDrTpage {
    u8 link[3];
    u8 len;
    u32 code;
} TitleDrTpage;

/* from title_draw_strip_clipped */
typedef struct TitlePolyFT4 {
    u8 link[3];
    u8 len;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad1;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u16 pad2;
} TitlePolyFT4;

/* from title_draw_strip_clipped */
typedef struct TitleDrTwin {
    u8 link[3];
    u8 len;
    u32 code[2];
} TitleDrTwin;

/* from title_draw_strip_clipped */
typedef struct StripVtx {
    s16 x;
    s16 y;
    u16 u;
    u16 v;
} StripVtx;

/* from title_waves_draw */
typedef struct Hdr8 {
    u8 b[8];
} Hdr8;

/* from title_list_draw */
typedef struct TitleListEnt {
    s16 x;
    s16 y;
} TitleListEnt;

typedef struct TitleListRec {
    s16 x;     /* 0x00 */
    s16 y;     /* 0x02 */
    s16 w;     /* 0x04 */
    u8 pad_06[4];
    s16 y2;    /* 0x0A */
    s16 h;     /* 0x0C */
    u8 pad_0E[2];
    TitleListEnt ent[5][2]; /* 0x10 */
    s16 slide_period;
    s16 slide_progress;
    s16 count; /* 0x3C */
    u8 pad_3E[2];
} TitleListRec;

/* from title_list_draw */
typedef struct TitleListTask {
    u8 pad_00[0x14];
    TitleListRec *rec; /* 0x14 */
    u8 pad_18[0xA];
    s16 sel;           /* 0x22 */
} TitleListTask;

/* from title_list_draw */
typedef struct TitleScratchFlag {
    u8 pad_00[0x24];
    s16 flag; /* 0x24 */
} TitleScratchFlag;

/* from title_waves_init */
typedef struct TitleWaveBand {
    s16 unk_00;
    s16 offset;
    s16 unk_04;
    s16 pad_06;
    s16 unk_08;
    s16 offset_speed;
    s16 unk_0C;
    s16 pad_0E;
    s16 scroll_v;
    s16 scroll_v_speed;
    s16 phase;
    s16 phase_speed;
    s16 unk_18;
    s16 flash_timer;
    s16 unk_1C;
    s16 unk_1E;
    s32 tex_u[16];
} TitleWaveBand;

/* from title_block_draw */
typedef struct TitleDrawBlock {
    s16 fade;
    u8 pad_02[2];
    s16 x;
    s16 y;
    u16 width;
    u8 pad_0A[2];
    s16 cur;
    s16 prev;
    s16 sel;
    u8 pad_12[2];
    s16 visible;
    u16 phase;
} TitleDrawBlock;

/* from title_block_draw */
typedef struct TitleDrawObj {
    u8 pad_00[0x14];
    TitleDrawBlock *block;
} TitleDrawObj;

/* from title_name_entry_draw */
typedef struct NameEntryView {
    u8 pad_00[0x56];
    s16 unk_56;
} NameEntryView;

/* from title_name_entry_draw */
typedef struct NameEntryState {
    u8 pad_00[0xA];
    s16 ring_angle;      /* 0x0A */
    u8 pad_0C[0xE];
    s16 ring_count;      /* 0x1A */
    u8 pad_1C[0x12];
    s16 ring_rec;        /* 0x2E */
    u8 pad_30[6];
    s16 ring_spread;     /* 0x36 */
    u8 pad_38[0x78];
    s16 ring_ofx;        /* 0xB0 */
    s16 ring_ofy;        /* 0xB2 */
    NameEntryView *sub; /* 0xB4 */
    u8 pad_B8[6];
    s16 mode;            /* 0xBE */
    u16 unk_C0;          /* 0xC0 */
    u8 pad_C2[2];
    u16 unk_C4;          /* 0xC4 */
    u8 pad_C6[2];
    s16 unk_C8;          /* 0xC8 */
    u8 pad_CA[4];
    s16 unk_CE;          /* 0xCE */
} NameEntryState;

/* from title_name_entry_draw */
typedef struct NameEntryCtx {
    u8 pad_00[0x14];
    NameEntryState *obj; /* 0x14 */
} NameEntryCtx;

/* from logo_draw */
typedef struct TitleXY {
    s16 x;
    s16 y;
} TitleXY;

/* from title_quant_scale */
typedef struct DctEnv {
    u8 b[0x100];
} DctEnv;

/* from title_ellipsoid_fill */
typedef struct TitleRingParams {
    u8 pad_00[0x14];
    s16 phase;
    s16 pad_16;
    s16 phase_step;
    s16 pad_1A;
    s16 radius_x;
    s16 radius_y;
} TitleRingParams;

/* from title_screen_setup_init */
typedef struct TitleRect {
    s16 x, y, w, h;
} TitleRect;

/* from title_screen_setup_init */
typedef struct TitleScreenSetup {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    TitleRect disp;
    TitleRect screen;
    s32 unk_20;
    TitleRect clip;
    s32 unk_2C;
} TitleScreenSetup;

/* from title_screen_setup_init */
typedef struct TitleScreenParams {
    s32 unk_00;
    s32 unk_04;
    s32 dispX;
    s32 dispY;
    s32 screenX;
    s32 screenY;
    s32 pad_18[3];
    s32 unk_24;
    s32 unk_28;
    s32 unk_2C;
} TitleScreenParams;

/* from title_glyph_quad_fill */
typedef struct TitleGlyphQuad {
    s16 x0, y0, x1, y1, x2, y2, x3, y3;
    u8 u0, v0, u1, v1, u2, v2, u3, v3;
    u16 clut;
    u16 tpage;
    s32 code;
} TitleGlyphQuad;

/* from title_quad_verts_fill */
typedef struct TitleVec4 {
    s16 vx, vy, vz, pad;
} TitleVec4;

/* from title_skel_pose_rest */
typedef struct TitleBone {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ s16 rest[3];
    /* 0x0A */ u8 pad_0A[2];
    /* 0x0C */ s16 pos[3];
    /* 0x12 */ u8 pad_12[2];
    /* 0x14 */ s16 dir[3];
    /* 0x1A */ u8 pad_1A[2];
    /* 0x1C */ s16 scale;
    /* 0x1E */ s16 scale_counter;
    /* 0x20 */ s16 fade;
    /* 0x22 */ s16 fade_step;
} TitleBone;

/* from title_skel_pose_rest */
typedef struct TitleSkeleton {
    /* 0x00 */ u8 pad_00[0x20];
    /* 0x20 */ TitleBone *bones;
    /* 0x24 */ s16 count;
} TitleSkeleton;

/* from title_restart_entries */
typedef struct {
    s32 id;
    u8 pad_04[0x12];
    s16 loop_flag; /* 0x16: bit 31 of the sound word */
    s16 volume;    /* 0x18: VAB tone volume */
    s16 unk_1A;
    s16 pad_1C;
    s16 unk_1E;
    u8 pad_20[2];
    s16 unk_22;    /* 0x22: bits 8-15 of the sound word */
    u8 pad_24[4];
    s32 next_tone; /* 0x28: the next entry's packed tone id */
} TitleRestartEntry;

/* A vertex of the title's subdivided meshes (title_tri_subdivide). TitleSpot and TitleFt3Vert read the same
 * 0x14 bytes as halves of sxy and as one uv word (cc1 2.7.2 has no anonymous unions to fold them in here). */
typedef struct TitleVertex {
    s16 x, y, z; /* 0x00: model position (gte_ldv0) */
    u8 u, v;     /* 0x06 */
    s32 sxy;     /* 0x08: screen position (SXY2) */
    s16 sz;      /* 0x0C: MAC3 */
    s16 clip;    /* 0x0E: off-screen bits (title_point_clip_flags) */
    s32 rgb;     /* 0x10 */
} TitleVertex;

/* from title_poly_ft3_add */
typedef struct TitleFt3Vert {
    u8 pad_00[6];
    s16 uv;
    s32 xy;
    u8 pad_0C[4];
    s32 rgb;
} TitleFt3Vert;

/* from title_poly_ft3_add */
typedef struct TitleScratch3D8 {
    s32 tpage;
    s32 clut;
    s16 *verts; /* 0x08: model vertex table (x, y, z) */
    u8 *colours;
    u32 *ot;
    u8 pad_14[4];
    s32 depth_cue; /* 0x18: IR0 of the last rtps */
    s16 flat_shade; /* 0x1C: draw POLY_FT3 instead of POLY_GT3 */
    s16 seq_depth;  /* 0x1E: fixed depth level, -1 = from distance */
    u16 unk_20;
    u16 semi_trans_ok; /* 0x22: 1 = faces with TITLE_FACE_SEMI_TRANS draw semi-transparent */
    u16 unk_24;        /* 0x24: 0 = GT4 faces, else FT4 (title_model_draw_at) */
} TitleScratch3D8;

/* A textured quad panel_face fills (one quarter or all of a 0x40 x 0x30 image). */
typedef struct TitleQuad {
    /* 0x00 */ s16 rect[4];   /* from panel_rect_table, times 4 */
    /* 0x08 */ s16 unk_08[4];
    /* 0x10 */ u8 uv[4][2];   /* u, v of the four corners */
    /* 0x18 */ u16 clut;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ s32 code;
} TitleQuad;

/* from title_menu_anim_update */
typedef struct TitleMenuAnim {
    s16 frame;
    s16 frames;
    s16 step;
    s16 steps;
    s16 origin_x;   /* 0x08 */
    s16 origin_y;   /* 0x0A */
    s16 pad_0C;
    s16 extent_y;   /* 0x0E */
    s16 choice[0x11];
    s16 pad_32[3];
    s16 glow_enabled;
    s16 cursor;
    s16 scale;
    s16 delay;
    s16 pad_40;
    u16 spin_x;
    u16 spin_y;
    s16 pad_46;
    s16 glow;
    u16 phase;
    s16 first_visible_row;
    s16 window_row;
} TitleMenuAnim;

/* from title_menu_anim_update */
typedef struct TitleMenuTask {
    u8 pad_00[0x1C];
    s16 state;
} TitleMenuTask;

/* from title_menu_anim_update */
typedef struct TitleMenuCtl {
    u8 pad_00[0x14];
    TitleMenuAnim *anim;
    TitleMenuTask *task;
    u8 pad_1C[6];
    s16 state;
} TitleMenuCtl;

/* from title_box_side_draw */
typedef struct TitleBoxSide {
    s16 x;
    s16 y;
    s16 w;
    u16 h;
    s16 ratio;
    s16 mode;
    u8 pad_0C[4];
    s32 *fill_colour;
    s32 *edge_colour_c;
    s32 *edge_colour_a;
    s32 *edge_colour_b;
    s32 ot_index;
} TitleBoxSide;

/* from title_fade_step_update */
typedef struct TitleFadeNode {
    u8 pad_00[0x1C];
    s16 kind;
} TitleFadeNode;

/* from title_fade_step_update */
typedef struct TitleFadeVec {
    u8 pad_00[4];
    s16 x;
    u8 pad_06[2];
    s16 label0_x; /* block 0x14: screen x of label 0 (entries[0]) */
    u8 pad_0A[6];
    s16 y;
} TitleFadeVec;

/* from title_fade_step_update */
typedef struct TitleFadeBlock {
    s16 fade;
    s16 unk_02;
    s16 steps;
    s16 step;
    s16 speed;
    s16 ramp;
    TitleFadeVec vec;
    u8 pad_1E[2];
    s16 label1_x; /* 0x20: screen x of label 1 (entries[1]) */
    u8 pad_22[2];
    void *entries[2];
    s16 locked;
    s16 unk_2E;
} TitleFadeBlock;

/* from title_fade_step_update */
typedef struct TitleFadeOwner {
    u8 pad_00[0x14];
    TitleFadeBlock *block;
    TitleFadeNode *node;
    u8 pad_1C[6];
    s16 state;
} TitleFadeOwner;

/* from title_phase_update */
typedef struct TitlePhaseTask {
    u8 pad_00[0x1C];
    s16 active;
} TitlePhaseTask;

/* from title_phase_update */
typedef struct TitlePhaseState {
    u8 pad_00[0x30];
    s16 step_div;   /* 0x30: 0x1000 / step_div is added to pos each frame */
    s16 pos;        /* 0x32 */
    u8 pad_34[2];
    s16 value_36;   /* 0x36: (counter << 12) / limit */
    s16 limit;      /* 0x38 */
    s16 counter;    /* 0x3A */
    u8 pad_3C[0x6E];
    s16 frames;     /* 0xAA */
} TitlePhaseState;

/* from title_phase_update */
typedef struct TitlePhaseObj {
    u8 pad_00[0x14];
    TitlePhaseState *anim;  /* 0x14 */
    TitlePhaseTask *task;   /* 0x18 */
    u8 pad_1C[6];
    s16 phase;              /* 0x22 */
} TitlePhaseObj;

/* from title_box_edge_add */
typedef struct TitlePrim {
    u8 pad_00[3];
    u8 len;    /* 0x03: words after the tag */
    u32 rgb;   /* 0x04: colour, top byte is the command code */
    s16 x0;    /* 0x08 */
    s16 y0;    /* 0x0A */
    u32 size;  /* 0x0C */
    s16 x1;    /* 0x10 */
    s16 y1;    /* 0x12 */
} TitlePrim;

/* from title_step_seq_update */
typedef struct TitleStepSeq {
    u16 phase_timer;
    s16 phase_rate;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 index;
    s16 limit;
    u16 saved_index;
    s16 state;
    s16 record_active;
    u16 unk_16;
    s16 delay_limit;
    u16 delay_timer;
} TitleStepSeq;

/* from title_step_seq_update */
typedef struct TitleStepLink {
    u8 pad_00[0x1C];
    s16 unk_1C;
} TitleStepLink;

/* from title_step_seq_update */
typedef struct TitleStepTask {
    u8 pad_00[0x14];
    TitleStepSeq *seq;
    TitleStepLink *link;
    u8 pad_1C[6];
    s16 step;
} TitleStepTask;

/* from title_step_seq_update */
typedef struct TitleStepSub {
    u8 pad_00[0x94];
    s32 flag_94;
} TitleStepSub;

/* from title_step_seq_update */
typedef struct TitleStepScene {
    u8 pad_00[8];
    s32 unk_08;
    u8 pad_0C[0x20 - 0x0C];
    s32 unk_20;
    TitleStepSub sub_24;
    u8 pad_BC[0xD0 - 0xBC];
    s32 unk_D0;
} TitleStepScene;

/* from title_load_update */
typedef struct TitleSaveSlot {
    s32 data[0x25];
    s32 comment; /* 0x94: passed to card_comment_build */
} TitleSaveSlot;

/* from title_load_update */
typedef struct TitleLoadState {
    u8 pad_00[2];
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[0x0E];
    s16 slot; /* cursor: card slot 0-2, 3 = cancel */
    s16 timer;
    s16 slot_status[3];
    s16 index;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
} TitleLoadState;

typedef struct TitleEntry {
    u8 pad_00[4];
    u32 flags;
    u8 pad_08[0x0E];
    u16 state_16;
    u8 pad_18[2];
    u16 state_1A;
} TitleEntry;

/* from title_load_update */
typedef struct TitleLoadShared { u8 pad_00[0x2C]; s16 unk_2C; } TitleLoadShared;

/* from title_load_update */
typedef struct TitleLoadTaskLink { u8 pad_00[0x14]; TitleLoadShared *shared; } TitleLoadTaskLink;

/* from title_load_update */
typedef struct TitleLoadTask {
    u8 pad_00[0x14];
    TitleLoadState *state;
    TitleLoadTaskLink *link;
    u8 pad_1C[6];
    s16 phase;
    s32 unk_24;
} TitleLoadTask;

/* from title_load_update */
typedef struct TitleLoadBase { u8 pad_00[0x20]; s32 unk_20; TitleSaveSlot save; u8 pad_BC[0x18]; s32 unk_D4; } TitleLoadBase;

/* from title_menu_update */
typedef struct TitleMenuData {
    /* 0x00 */ struct TitleCell *cell;
    /* 0x04 */ u16 rect[4];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 choice;
    /* 0x20 */ u8 pad_20[2];
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ u8 pad_24[8];
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u8 pad_32[8];
    /* 0x3A */ s16 slot;
    /* 0x3C */ s16 sub_index;
} TitleMenuData;

/* from title_menu_update */
typedef struct TitleMenuObj {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ TitleMenuData *data;
    /* 0x18 */ struct TitleCtrl *ctrl;
    /* 0x1C */ u8 pad_1C[6];
    /* 0x22 */ s16 step;
} TitleMenuObj;

/* from title_timer_rec_update */
typedef struct TitleTimerRec {
    s16 x;          /* 0x00 */
    s16 y;          /* 0x02 */
    s16 duration;   /* 0x04 */
    s16 elapsed;    /* 0x06 */
    s16 counter_limit;     /* 0x08 */
    s16 counter;    /* 0x0A */
    s16 ratio;      /* 0x0C */
} TitleTimerRec;

/* from title_timer_rec_update */
typedef struct TitleTimerObj {
    u8 pad_00[0x14];
    TitleTimerRec *timer;   /* 0x14 */
    u8 pad_18[0xA];
    s16 state;              /* 0x22 */
} TitleTimerObj;

/* from title_timer_tick */
typedef struct TitleTimer {
    u16 count;      /* 0x0 */
    s16 period;     /* 0x2 */
    s16 value;      /* 0x4 */
    s16 mode;       /* 0x6 */
} TitleTimer;

/* from title_ctl_reset */
typedef struct Word8010 {
    s32 v;
} Word8010;

/* from title_ctl_reset */
typedef struct TitleCtlInner {
    /* 0x00 */ u8 pad_00[0x20];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ u8 pad_2C[0x24];
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
} TitleCtlInner;

/* from title_ctl_reset */
typedef struct TitleCtlOuter {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ TitleCtlInner *inner;
} TitleCtlOuter;

/* from title_fade_reset */
typedef struct Rec800A34E0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x24];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
} Rec800A34E0;

/* from title_spot_is_far */
typedef struct TitleSpot {
    u8 pad_00[8];
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
} TitleSpot;

/* from func_800B2468 */
typedef struct TitleClutRgb {
    u8 r, g, b, pad;
} TitleClutRgb;

/* from title_sliders_init: a slider with `count` evenly spaced steps (0..0x1000) */
typedef struct TitleSlider {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 pad_08[2];
    /* 0x10 */ s32 steps[4];
    /* 0x20 */ s32 count;
} TitleSlider;

/* from title_name_entry_update */
typedef struct TitleNameEntry {
    /* 0x00 */ TitleSlider bars[2];
    u8 pad_48[0xC];
    s16 unk_54;
    u16 unk_56;
} TitleNameEntry;

/* from title_name_entry_update */
typedef struct TitleMenuNode {
    void (*update)(void *node);
    u8 pad_04[0x10];
    struct TitleMenuRec *menu;
    struct TitleMenuChild *child; /* 0x18 */
    u8 pad_1C[6];
    s16 phase;           /* 0x22 */
    s32 mode;            /* 0x24 */
} TitleMenuNode;

/* from title_name_entry_update */
typedef struct TitleMenuRec {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[6];
    s16 angle;           /* 0x0A */
    u8 pad_0C[4];
    s16 step_speed;
    s16 target_angle;
    s16 speed;           /* 0x14 */
    s16 unk_16;
    s16 unk_18;
    s16 period;          /* 0x1A */
    u8 pad_1C[0x10];
    u16 selected_index;
    u8 pad_2E[2];
    s16 unk_30;
    u16 count;           /* 0x32 */
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x72];
    s16 unk_AC;
    u16 unk_AE;
    u8 pad_B0[4];
    struct TitleNameEntry *entry; /* 0xB4 */
    u8 *buf;             /* 0xB8 */
    u8 pad_BC[0];
} TitleMenuRec;

/* from title_name_entry_update */
typedef struct TitleMenuRec2 {
    u8 pad_00[0xB4];
    struct TitleNameEntry *entry; /* 0xB4 */
    u8 *buf;             /* 0xB8 */
    u8 pad_BC[0];
    s16 unk_BC;
    s16 unk_BE;
    u16 angle_a;
    u16 angle_a_speed;
    u16 angle_b;
    u16 angle_b_speed;
    s16 seconds_left;
    u16 frame_countdown;
    u16 frames_per_second;
    s16 show_countdown;
} TitleMenuRec2;

/* from title_name_entry_update */
typedef struct TitleMenuInfo { u8 pad[0xC]; s32 unk_0C; } TitleMenuInfo;

/* from title_menu_draw */
typedef struct TitleMenuDrawState {
    u8 pad_000[8];
    s16 unk_008;
    u8 pad_00A[0x396];
    s16 unk_3A0;
    u8 pad_3A2[6];
    s16 fade_level;
    u8 pad_3AA[6];
    s16 menu_index;
} TitleMenuDrawState;

/* from title_menu_draw */
typedef struct TitleMenuDrawObj {
    u8 pad_00[0x14];
    TitleMenuDrawState *state;
    u8 pad_18[0xA];
    s16 active;
} TitleMenuDrawObj;

/* from title_step_update */
typedef struct TitleStepRect {
    u8 pad_00[8];
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} TitleStepRect;

/* from title_step_update */
typedef struct TitleStepAnim {
    TitleStepRect *rect; /* 0x00 */
    s16 x;               /* 0x04 */
    s16 y;               /* 0x06 */
    s16 width;           /* 0x08 */
    s16 height;          /* 0x0A */
    s32 unk_0C;          /* 0x0C */
    s32 unk_10;          /* 0x10 */
    s32 unk_14;          /* 0x14 */
    s32 unk_18;          /* 0x18 */
    s16 phase;           /* 0x1C */
    u8 pad_1E[0x1A];
    u16 timer;           /* 0x38 */
    s16 index;           /* 0x3A */
    s16 sub_index;       /* 0x3C */
} TitleStepAnim;

/* from title_step_update */
typedef struct TitleStepObj {
    u8 pad_00[0x14];
    TitleStepAnim *anim; /* 0x14 */
    u8 pad_18[0xA];
    s16 state;            /* 0x22 */
} TitleStepObj;

/* from title_step_update */
typedef struct TitleStepPad {
    s32 pad_cur;
    s32 pad_released;
    s32 pad_held;
} TitleStepPad;

/* from title_timer_update */
typedef struct TitleTimedRec {
    s16 ratio;      /* 0x00: elapsed * 0x1000 / duration */
    u8 unk_02[2];
    s16 duration;   /* 0x04 */
    s16 elapsed;    /* 0x06 */
    u8 unk_08[2];
    s16 unk_0A;     /* 0x0A */
} TitleTimedRec;

/* from title_timer_update */
typedef struct TitleTimedOwner {
    u8 pad_00[0x14];
    TitleTimedRec *timer;   /* 0x14 */
    void *node;             /* 0x18: TitleTaskNode */
    u8 pad_1C[6];
    s16 state;              /* 0x22 */
} TitleTimedOwner;

/* from title_pad3d_update */
typedef struct TitleStepRec {
    /* 0x00 */ s16 ratio;
    /* 0x02 */ u8 pad_02[2];
    /* 0x04 */ s16 span;
    /* 0x06 */ s16 count;
} TitleStepRec;

/* from title_button_draw */
typedef struct TitleButton {
    u8 pad_00[4];
    s16 x;            /* 0x04 */
    s16 y;            /* 0x06 */
    s16 width;       /* 0x08 */
    u8 pad_0A[0x12];
    s16 visible;       /* 0x1C: nonzero shows the button */
    s16 mode_1E;      /* 0x1E */
    u8 pad_20[2];
    s16 unk_22;       /* 0x22 */
    s16 value_24;     /* 0x24 */
    u8 pad_26[6];
    u8 unk_2C[0x12];  /* 0x2C: buffer passed to title_cursor_draw */
    s16 value_3E;     /* 0x3E */
} TitleButton;

/* from title_button_draw */
typedef struct TitleSlot {
    u8 pad_00[0x14];
    TitleButton *button; /* 0x14 */
} TitleSlot;

/* from title_start_update */
typedef struct TitleSeqState {
    s32 started;   /* 0x00 */
    u32 pad_wait;  /* 0x04 */
    u32 idle;      /* 0x08 */
} TitleSeqState;

/* from title_start_update */
typedef struct TitleSys {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x24];
    u8 flags_34[0x84];
    s32 unk_B8;
    u8 pad_BC[0xC];
    s32 unk_C8;
    u8 pad_CC[8];
    s32 unk_D4;
} TitleSys;

/* from title_start_update */
typedef struct TitleSeqNode {
    u8 pad_00[0x14];
    TitleSeqState *state;
    u8 pad_18[0xA];
    s16 step;
} TitleSeqNode;

/* from title_anim_slot_update */
typedef struct TitleAnimSlot {
    u8 unk_00[4];
    u16 src[4];   /* 0x04 */
    s32 unk_0C;   /* 0x0C */
    s32 unk_10;   /* 0x10 */
    s32 unk_14;   /* 0x14 */
    s32 unk_18;   /* 0x18 */
    s16 active;   /* 0x1C */
    u8 unk_1E[0x1C];
    s16 record_index;   /* 0x3A */
    s16 unk_3C;   /* 0x3C */
} TitleAnimSlot;

/* from title_message_draw */
typedef struct TitleTextRec {
    u8 pad_00[0x04];
    s16 x;           /* 0x04 */
    s16 y;           /* 0x06 */
    u8 pad_08[0x14];
    s16 active;      /* 0x1C */
    u8 pad_1E[0x20];
    s16 id;          /* 0x3E */
} TitleTextRec;

/* from title_message_draw */
typedef struct TitleTextTask {
    u8 pad_00[0x14];
    TitleTextRec *rec; /* 0x14 */
} TitleTextTask;

/* from title_obj_update */
typedef struct TitleAnimEntry {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s32 unk_10[4];
    /* 0x20 */ s32 unk_20;
} TitleAnimEntry;

/* from menu_quads_init */
typedef struct TitleMenuQuad {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
    u16 e;
    u16 f;
} TitleMenuQuad;

/* from title_seq_phase2 */
typedef struct TitleSeqRec {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} TitleSeqRec;

/* from title_seq_phase2 */
typedef struct TitleSeqTask {
    u8 pad_00[0x14];
    TitleSeqRec *recs;  /* 0x14 */
} TitleSeqTask;

/* from title_pair_update */
typedef struct TitleSlotState {
    u8 unk_00[0x0C];
    s16 mode;            /* 0x0C: 0 or 1 selects the case below */
    u8 *flag;            /* 0x10 */
    s16 self_pair[3];    /* 0x14 */
    s16 unk_1A;          /* 0x1A */
    u8 unk_1C[0x04];
    s16 other_pair[3];   /* 0x20 */
    s16 unk_26;          /* 0x26 */
    u8 unk_28[0x04];
    s16 third_pair[2];   /* 0x2C */
    s16 unk_30;          /* 0x30 */
} TitleSlotState;

/* from title_cursor_update */
typedef struct TitleCursor {
    /* 0x00 */ u16 phase_timer;
    /* 0x02 */ s16 phase_rate;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 index;
    /* 0x0E */ s16 limit;
    /* 0x10 */ u16 saved_index;
    /* 0x12 */ s16 state;
} TitleCursor;

/* from panel_update */
typedef struct TitleStepTrack {
    u8 pad_00[8];
    s16 value;  /* 0x08 */
    u8 pad_0A[2];
    s16 period; /* 0x0C */
    u16 step;   /* 0x0E */
    s16 limit;  /* 0x10 */
    u16 count;  /* 0x12 */
} TitleStepTrack;

/* from title_ramp_update */
typedef struct TitleRampRec {
    u8 unk_00[0x20];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    u8 unk_2C[0x2C];
    s32 unk_58;
} TitleRampRec;

/* from xform_pair_extrapolate */
typedef struct XformPair {
    u16 pos[3];       /* 0x00 */
    u16 unk_06;       /* 0x06 */
    u16 pos_out[3];   /* 0x08 */
    u16 unk_0E;       /* 0x0E */
    u16 vel[3];       /* 0x10 */
    u16 unk_16;       /* 0x16 */
    u16 origin[3];    /* 0x18 */
    u16 unk_1E;       /* 0x1E */
    u16 origin_out[3]; /* 0x20 */
    u16 unk_26;       /* 0x26 */
    u16 dir[3];       /* 0x28 */
    u16 unk_2E;       /* 0x2E */
    u16 scale;        /* 0x30 */
    u16 scale_copy;   /* 0x32 */
} XformPair;

/* from xform_pair_extrapolate */
typedef struct XformHost {
    u8 unk_00[0x14];
    XformPair *pair; /* 0x14 */
} XformHost;

/* from title_cells_init */
typedef struct TitleCell {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 rect_x;
    /* 0x0A */ s16 rect_y;
    /* 0x0C */ s16 rect_width;
    /* 0x0E */ s16 rect_height;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
} TitleCell;

/* from title_anim_draw */
struct TitleAnimSprite {
    u8 unk_00[4];
    s16 x;
    s16 y;
    u8 unk_08[0x14];
    s16 active;
    u8 unk_1E[0xA];
    u8 *text;
    u8 unk_2C[0x12];
    s16 ot_depth;
};

/* from title_slot_update */
typedef struct TitleSlotRec {
    /* 0x00 */ u8 pad_00[0x1E];
    /* 0x1E */ s16 unk_1E;
} TitleSlotRec;

/* from title_slot_update */
typedef struct TitleSlotOwner {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ TitleSlotRec *slot;
} TitleSlotOwner;

/* from title_block_update */
typedef struct TitleBlockOutput {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} TitleBlockOutput;

/* from title_block_update */
typedef struct TitleBlockArg {
    u8 pad_00[0x14];
    TitleBlockOutput *out;
} TitleBlockArg;

/* from title_block_update */
typedef struct Rec800B854CShared {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0xB8 - 0x24];
    s32 unk_B8;
} Rec800B854CShared;

/* from title_pair_toggle */
typedef struct TitlePairState {
    u8 unk_00[0x0C];
    s16 self_pair[3];
    s16 unk_12[3];
    s16 other_pair[3];
} TitlePairState;

/* from title_pair_toggle */
typedef struct TitlePairOwner {
    u8 unk_00[0x14];
    TitlePairState *pair;
} TitlePairOwner;

/* from title_ctx_draw */
typedef struct TitleCtx {
    u8 pad_00[0x120];
    s16 unk_120;
} TitleCtx;

/* from title_slot_draw */
typedef struct TitleSlotDrawData {
    u8 unk_00[4];
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    u8 unk_08[0x14];
    /* 0x1C */ s16 flag;
    u8 unk_1E[2];
    /* 0x20 */ s16 extra;
    u8 unk_22[0x1C];
    /* 0x3E */ s16 index;
} TitleSlotDrawData;

/* from title_slot_draw */
typedef struct TitleSlotDrawObj {
    u8 unk_00[0x14];
    /* 0x14 */ TitleSlotDrawData *data;
} TitleSlotDrawObj;

/* from title_anim_step */
typedef struct TitleAnimTrack {
    u8 unk_00[8];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 delta_x;
    u16 delta_y;
    u16 delta_z;
    u8 unk_16[0xA];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 unk_2E[4];
    u16 frames_left;
} TitleAnimTrack;

/* from title_highlight_set_pos */
typedef struct TitleHighlight {
    s16 unk_00;
    s16 unk_02;
    s16 x;
    s16 y;
    s16 unk_08;
} TitleHighlight;

/* from title_label_flags_update */
typedef struct Rec800B6CACTail {
    u8 pad_00[2];
    s16 unk_02;          /* 0x16 */
    s16 unk_04;          /* 0x18 */
    s16 unk_06;          /* 0x1A */
    u8 pad_08[6];
    s16 unk_0E;          /* 0x22 */
} Rec800B6CACTail;

/* from title_label_flags_update */
typedef struct TitleLabelFlagRec {
    u8 pad_00[0x10];
    u8 *state_ptr;
    Rec800B6CACTail tail;   /* 0x14 */
    s16 scale_x;
    s16 scale_y;
} TitleLabelFlagRec;

/* from title_label_flags_update */
typedef struct TitleLabelFlagOwner {
    u8 pad_00[0x14];
    TitleLabelFlagRec *flag_rec;
} TitleLabelFlagOwner;

/* from title_label_update */
typedef struct TitleLabelTask {
    u8 pad_00[4];
    s16 unk_04;
    u8 pad_06[6];
    s16 unk_0C;
    u8 pad_0E[2];
    s32 state_ptr;   /* points at the state byte, read as u8 */
    s16 unk_14;
    s16 flag_16;     /* 1 when the state byte is 0, else 0 */
    s16 bar_a_scale_x;
    s16 bar_a_scale_y;
    u8 pad_1C[6];
    s16 unk_22;
    s16 bar_b_scale_x;
    s16 bar_b_scale_y;
    u8 pad_28[6];
    s16 unk_2E;
    s16 bar_c_scale_x;
    s16 bar_c_scale_y;
} TitleLabelTask;

/* from title_label_update */
typedef struct TitleLabelTail {
    u8 pad_00[0xE];
    s16 unk_0E;
    u8 pad_10[0xA];
    s16 unk_1A;
} TitleLabelTail;

/* from title_pos_draw */
typedef struct TitlePosObj {
    u8 unk_00[0x14];
    s16 *pos; /* 0x14: x at [0], y at [1] */
} TitlePosObj;

/* from title_menu_setup */
typedef struct TitleMenuSetupObj {
    u8 pad_00[0x14];
    s16 *unk_14;
} TitleMenuSetupObj;

/* from title_bars_draw */
typedef struct TitleBarRect {
    s16 x;
    s16 y;                /* 1 = size is scaled by the params scale */
    s16 len;              /* scaled by the params scale */
    s16 pad_06;
    s16 x2;
    s16 y2;
} TitleBarRect;

/* Label record drawn by title_label_draw (title_label_init / title_label_index_init). */
typedef struct TitleLabelDraw {
    s16 scale;           /* 0x00: 0x1000 = 1.0 */
    s16 value;           /* 0x02 */
    u8 pad_04[0x08];
    s16 mode;            /* 0x0C: 0 two bars, 1 three bars */
    u8 pad_0E[0x06];
    TitleBarRect bar_a;  /* 0x14 */
    TitleBarRect bar_b;  /* 0x20 */
    TitleBarRect bar_c;  /* 0x2C */
} TitleLabelDraw;

typedef struct TitleLabelOwner {
    u8 pad_00[0x14];
    TitleLabelDraw *label;  /* 0x14 */
} TitleLabelOwner;

/* from title_obj_draw */
typedef struct TitleParams {
    s16 scale;           /* 0x00: 0x1000 = 1.0 */
    u8 pad_02[0x0A];
    TitleBarRect bar_a;  /* 0x0C */
    TitleBarRect bar_b;  /* 0x18 */
    u8 pad_24[0x12];
    s16 unk_36;
    u8 pad_38[0x10];
    s16 anim_level;      /* 0x48: result >> 12 */
    u8 pad_4A[0x4];
    s16 anim_index;      /* 0x4E: table entry index, entries are 0x24 bytes */
    s16 anim_period;     /* 0x50: 0x1000 / period = progress per frame */
    s16 anim_progress;   /* 0x52: runs to 0x1000 */
    u8 pad_54[0x5A];
    s16 unk_AE;
} TitleParams;

/* from title_obj_draw */
typedef struct TitleObj {
    u8 pad_00[0x14];
    TitleParams *params;
    u8 pad_18[0x0A];
    s16 state;           /* 0x22: 0 idle, 1 animating */
} TitleObj;

/* from title_sprite_reset */
typedef struct TitleSpriteScale {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 pad_12[0x0A];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ u8 pad_1E[0x0E];
    /* 0x2C */ s16 unk_2C;
} TitleSpriteScale;

/* from title_task_phase0 */
typedef struct TitleLink {
    u8 pad_00[0x28];
    u16 unk_28;
    u16 unk_2A;
} TitleLink;

/* from title_ref_draw */
typedef struct TitleRef {
    u8 unk_00[0x14];
    s16 *pos;
} TitleRef;

/* from title_anim_ratio_init */
/* A 12-byte track slot set up by title_scene_track_init. */
typedef struct TitleSceneTrack {
    /* 0x00 */ void *data;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} TitleSceneTrack;

/* Animated title scene (title_ring_a, title_anim_ratio_alt), set up by title_scene_init. */
typedef struct TitleAnimRatio {
    /* 0x00 */ s16 center_x;
    /* 0x02 */ s16 center_y;
    /* 0x04 */ s16 center_z;
    /* 0x06 */ u8 pad_06[2];
    /* 0x08 */ s16 tilt;
    /* 0x0A */ s16 angle;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 pad_0E[2];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 target_angle;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ u16 base_radius;
    /* 0x1A */ s16 item_count; /* entries used in unk_1C */
    /* 0x1C */ s16 item_cells[8];
    /* 0x2C */ s16 selected_index;
    /* 0x2E */ s16 rec_index;
    /* 0x30 */ s16 width;
    /* 0x32 */ u8 pad_32[2];
    /* 0x34 */ u16 radius;
    /* 0x36 */ s16 brightness;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ u8 pad_3A[2];
    /* 0x3C */ TitleSceneTrack tracks[9];
    /* 0xA8 */ u8 pad_A8[4];
    /* 0xAC */ s16 unk_AC;
    /* 0xAE */ s16 quad_index;
    /* 0xB0 */ s16 offset_x;
    /* 0xB2 */ s16 offset_y;
} TitleAnimRatio;

/* from title_anim_ratio_init */
typedef struct TitleAnimRatioOwner {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ TitleAnimRatio *inner;
} TitleAnimRatioOwner;

/* from logo_update */
typedef struct TitleFadeRec {
    s16 level;           /* 0x00: result >> 12 */
    s16 unk_02;
    s16 period;          /* 0x04: 0x1000 / period = progress per frame */
    u16 progress;        /* 0x06 */
    s16 hold_frames;     /* 0x08 */
    u16 hold_count;      /* 0x0A */
    u8 pad_0C[0x20];
    s32 steps_a[4];      /* 0x2C */
    s32 count_a;         /* 0x3C */
    u8 pad_40[0x20];
    s32 steps_b[4];      /* 0x60 */
    s32 count_b;         /* 0x70 */
    s16 table_index;     /* 0x74 */
    s16 unk_76;          /* 0x76: 1 calls wave_advance */
} TitleFadeRec;

/* from logo_update */
typedef struct TitleFadeTask {
    void (*update)(void *node);
    u8 pad_04[0x10];
    TitleFadeRec *fade;
    u8 pad_18[0xA];
    s16 phase;           /* 0x22 */
} TitleFadeTask;

/* from title_sprite_update */
typedef struct TitleSpriteTrack {
    u8 table_00[0x20];
    u8 table_20[0x20];
    u8 table_40[0x20];
    s32 key_times[8];
    s32 key_count;
} TitleSpriteTrack;

/* from title_sprite_update */
typedef struct TitleSpriteAnim {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[2];
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    u8 pad_0E[2];
    u16 vel_x;
    u16 vel_y;
    u16 vel_z;
    u8 pad_16[2];
    TitleSpriteTrack track_a;
    TitleSpriteTrack track_b;
    s16 scale;
    u8 pad_122[2];
    s16 frames;
    u16 frame;
} TitleSpriteAnim;

/* from title_sprite_update */
typedef struct TitleSpriteCtl {
    u8 unk_00[0x14];
    TitleSpriteAnim *anim; /* 0x14 */
    u8 unk_18[0xA];
    s16 state; /* 0x22 */
} TitleSpriteCtl;

/* A 16x16 4-bit image with its w/h header word (card_header_build copies the pixels) */
typedef struct CardIconImage {
    u16 w;
    u16 h;
    u8 pixels[0x80];
} CardIconImage;

/* from title_rec_pool_init */
typedef struct TitleRecPoolEntry {
    TitleMatrix mat; /* 0x00: rotation built by title_rec_matrix_update */
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    u8 pad_2C[4];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[4];
    s32 angle_x;
    s32 angle_y;
    s32 angle_z;
    u8 pad_5C[4];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[4];
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    u8 pad_7C[4];
} TitleRecPoolEntry;

/* from clut_load_set */
typedef struct ClutRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ClutRect;

/* from title_window_show */
typedef struct TitleWin {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 w;
    /* 0x0A */ s16 h;
    /* 0x0C */ s32 v0C;
    /* 0x10 */ s32 v10;
    /* 0x14 */ s32 v14;
    /* 0x18 */ s32 v18;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ s16 mode;
    /* 0x22 */ u8 pad22[0x18];
    /* 0x3A */ s16 v3A;
    /* 0x3C */ s16 v3C;
} TitleWin;

/* from logo_init */
typedef struct TitleLogoSlider {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ u8 pad_04[8];
    /* 0x0C */ s32 left, top, mid_x, mid_y, right, bottom, edge_x, edge_y;
    /* 0x2C */ s32 steps_a[4];
    /* 0x3C */ s32 count_a;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ u8 pad_48[8];
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ u8 pad_58[8];
    /* 0x60 */ s32 steps_b[4];
    /* 0x70 */ s32 count_b;
    /* 0x74 */ u8 pad_74[2];
    /* 0x76 */ s16 unk_76;
} TitleLogoSlider;

/* from movie_read_frame */
typedef struct MovieFrameHeader {
    u8 pad_00[8];
    u32 size;
    u8 pad_0C[4];
    u16 w;
    u16 h;
    s32 key0;
    s32 key1;
} MovieFrameHeader;

/* from title_pad_update */
typedef struct {
    s32 pad_cur;
    s32 pad_released;
    s32 pad_held;
    u16 hold_frames[14];
} TitlePadState;

/* from title_anim_update */
struct TitleAnim {
    u8 unk_00[0x16];
    s16 state;      /* 0x16 */
    u16 base;       /* 0x18 */
    u8 unk_1A[6];
    TitleBone *bones; /* 0x20 (as TitleSkeleton) */
    s16 bone_count; /* 0x24 */
    u8 unk_26[8];
    s16 unk_2E;     /* 0x2E */
    u8 unk_30[0x4];
    u16 unk_34;     /* 0x34 */
    s16 progress;     /* 0x36 */
    s16 frame_count;     /* 0x38 */
    s16 unk_3A;     /* 0x3A */
    u8 unk_3C[0x6E];
    u16 unk_AA;     /* 0xAA */
};

/* from title_fade_in_update */
typedef struct TitleFadeInData {
    /* 0x00 */ u8 unk_00[8];
    /* 0x08 */ s16 tilt;
    /* 0x0A */ u8 unk_0A[0xC];
    /* 0x16 */ s16 state;
    /* 0x18 */ u16 base_radius;
    /* 0x1A */ u8 unk_1A[0x14];
    /* 0x2E */ s16 rec_index;
    /* 0x30 */ u8 unk_30[4];
    /* 0x34 */ u16 radius;
    /* 0x36 */ s16 brightness;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 count;
} TitleFadeInData;

/* from title_fade_in_update */
typedef struct TitleFadeInObj {
    /* 0x00 */ u8 unk_00[0x14];
    /* 0x14 */ TitleFadeInData *data;
    /* 0x18 */ u8 unk_18[0xA];
    /* 0x22 */ u16 step;
} TitleFadeInObj;

/* from display_buffer_init */
typedef struct TitleWindow {
    s16 x;          /* 0x00 */
    s16 y;          /* 0x02 */
    s16 w;          /* 0x04 */
    s16 h;          /* 0x06 */
    s16 screen_x;     /* 0x08 */
    s16 screen_y;     /* 0x0A */
    s16 screen_w;     /* 0x0C */
    s16 screen_h;     /* 0x0E */
    s8 isinter;      /* 0x10 */
    s8 isrgb24;      /* 0x11 */
    s8 unk_12;      /* 0x12 */
    s8 unk_13;      /* 0x13 */
    s8 sub_14[0x14];/* 0x14: passed to set_def_draw_env */
    s16 tpage;     /* 0x28 */
    s8 dtd;      /* 0x2A */
    s8 unk_2B;      /* 0x2B */
    s8 isbg;      /* 0x2C */
    s8 bg_r;      /* 0x2D */
    s8 bg_g;      /* 0x2E */
    s8 bg_b;      /* 0x2F */
} TitleWindow;

/* from title_prim_tex_init */
typedef struct PrimTexLayout {
    s16 s[8];
    u8 uv[8];
    u16 clut;
    u16 tpage;
    s32 cmd;
} PrimTexLayout;

/* from title_fade_out_update */
typedef struct TitleFadeOutData {
    /* 0x00 */ u8 unk_00[8];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u8 unk_0A[0xC];
    /* 0x16 */ s16 state;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u8 unk_1A[0x1A];
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 fade_ratio;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 count;
} TitleFadeOutData;

/* from title_fade_out_update */
typedef struct TitleFadeOutObj {
    /* 0x00 */ u8 unk_00[0x14];
    /* 0x14 */ TitleFadeOutData *data;
    /* 0x18 */ u8 unk_18[0xA];
    /* 0x22 */ s16 step;
} TitleFadeOutObj;

/* from movie_start */
struct TitleCmd {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 total_size;
};

/* from tasks_update */
typedef struct TitleTaskListNode {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ void (*update)(struct TitleTaskListNode *);
    /* 0x08 */ u8 pad_08[4];
    /* 0x0C */ struct TitleTaskListNode *next;
    /* 0x10 */ u8 pad_10[0xA];
    /* 0x1A */ s16 pad_1A;
    /* 0x1C */ s16 active;
    /* 0x1E */ s16 state;
    /* 0x20 */ s16 hold;
} TitleTaskListNode;

/* from card_has_room */
typedef struct DirEntry {
    u8 unk_00[0x18];
    s32 size;
    u8 unk_1C[0xC];
} DirEntry;

/* from title_build_sprite_packets: views of single words of the block it writes */
typedef struct TitleWordBytes {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} TitleWordBytes;

typedef struct TitleWordSVec {
    s16 x;
    s16 y;
    s16 z;
} TitleWordSVec;

/* from title_slide_update */
typedef struct TitleAnimState {
    u8 unk_00[0x16];
    s16 step;          /* 0x16: 0 = start, 1 = running */
    u8 unk_18[0x16];
    s16 unk_2E;        /* 0x2E */
    u8 unk_30[0x4];
    u16 unk_34;        /* 0x34: advances by 0xC per frame */
    s16 unk_36;        /* 0x36: set from counter << 12 / 28 */
    u8 unk_38[0x2];
    s16 counter;       /* 0x3A: frames left */
} TitleAnimState;

/* from title_slide_update */
typedef struct TitleAnimObj {
    u8 unk_00[0x14];
    TitleAnimState *anim;  /* 0x14 */
    u8 unk_18[0xA];
    u16 step;            /* 0x22: bumped when the counter runs out */
} TitleAnimObj;

/* from tasks_restart_with */
typedef struct TitleListNode {
    s32 unk_00[3];
    struct TitleListNode *next;
    s32 unk_10;
    s32 unk_14[2];
    s16 state;
    s16 flag;
} TitleListNode;

/* from tasks_draw */
typedef struct TitleCallbackNode {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ void (*callback)(void *node);
    /* 0x0C */ struct TitleCallbackNode *next;
    /* 0x10 */ u8 pad_10[0xE];
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
} TitleCallbackNode;

/* from sprite_load_tpage */
typedef struct SpriteRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} SpriteRect;

/* from title_request_start */
typedef struct TitleSrc {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[4];
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} TitleSrc;

/* from title_request_start */
typedef struct TitleArg {
    u8 pad_00[0x14];
    void *ctx;
} TitleArg;

/* from title_record_restart */
typedef struct TitleSideBlock {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} TitleSideBlock;

/* from movie_decode_frame */
typedef struct DctBufPair {
    /* 0x00 */ void *buf[2];
    /* 0x08 */ s32 active;
    /* 0x0C */ u8 pad_0C[8];
    /* 0x14 */ u16 width_a;  /* movie_read_frame sets these from the movie frame's size */
    /* 0x16 */ u16 height_a;
    /* 0x18 */ u8 pad_18[4];
    /* 0x1C */ u16 width_b;
    /* 0x1E */ u16 height_b;
    /* 0x20 */ u8 pad_20[0xA];
    /* 0x2A */ u16 height_c;
} DctBufPair;

/* from movie_mdec_wait: two (x, y) entries, the selected one copied out after a countdown */
typedef struct TitleSwap {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s16 entries[2][4];
    /* 0x20 */ s32 toggle;
    /* 0x24 */ s16 x;
    /* 0x26 */ s16 y;
    /* 0x28 */ u8 pad_28[4];
    /* 0x2C */ s32 busy;
} TitleSwap;

/* from task_start */
typedef struct TitleTaskNode {
    /* 0x00 */ void (*update)(void *node);
    /* 0x04 */ u8 pad_04[8];
    /* 0x0C */ void *prev;
    /* 0x10 */ void *next;
    /* 0x14 */ void *unk_14;
    /* 0x18 */ s32 mode;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 sub_state;
    /* 0x24 */ s32 param;
} TitleTaskNode;

/* from rec_queue_push */
typedef struct {
    u32 word0;
    u32 word1;
} __attribute__((packed)) Unaligned8;

/* from rec_queue_push */
typedef struct TitleRecQueueEntry {
    Unaligned8 data;
    s32 tag;
} TitleRecQueueEntry;

/* from title_record_set */
typedef struct TitleSideEntry {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} TitleSideEntry;

/* from title_sprite_init */
typedef struct TitleSprite {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    u8 unk_10[6];
    s16 unk_16;
    s16 tpage;
    s16 clut;
    s32 unk_1C;
} TitleSprite;

/* from tasks_pause_others */
typedef struct TitleFlagNode {
    /* 0x00 */ u8 pad_00[0xC];
    /* 0x0C */ struct TitleFlagNode *next;
    /* 0x10 */ u8 pad_10[0x10];
    /* 0x20 */ s16 flag;
} TitleFlagNode;

/* from title_entries_set_rate */
typedef struct TitleEntry2C {
    u8 pad_00[0x8];
    s32 sound_channel;
    s32 volume;
    u8 pad_10[0x8];
    s16 unk_18;
    u8 pad_1A[0x6];
    s16 base_volume;
    s16 fade_level;
    s16 fade_step;
    s16 fade_state;
    s16 alloc_retries;
    u16 default_value;
} TitleEntry2C; /* 0x2C */

/* from quad_points_init */
typedef struct TitleRec8 {
    s16 x;
    s16 y;
    s16 z;
    s16 unk_06;
} TitleRec8;

/* from vec3s16_set_quarter */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s16;

/* from title_flag_test_set */
typedef struct TitleFlagRec {
    u8 unk_00[0x1E];
    s16 unk_1E;
} TitleFlagRec;

/* from title_table_request */
typedef struct TitleTableReq {
    u8 pad_00[0x10];
    s32 unk_10[4];
    s32 unk_20;
    u8 unk_24[0x10];
    s32 unk_34[4];
    s32 unk_44;
    s16 x_offset;
    s16 y;
    s16 unk_4C;
    s16 timer;
    s16 start_delay;
    u8 pad_52[2];
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
} TitleTableReq;

/* from title_table_request */
typedef struct TitleTable {
    u8 pad_00[0x14];
    TitleTableReq *req;
    u8 pad_18[0x22 - 0x18];
    s16 state;
} TitleTable;

/* from pad3d_show */
typedef struct Bytes8 {
    u8 b[8];
} Bytes8;

/* one row of title_draw_menu_list's table: two numbers and a short text */
typedef struct Pad3dSoundRow {
    s32 unk_0;
    s32 unk_4;
    u8 name[4];
} Pad3dSoundRow;

/* a 12-byte row of the save-info table drawn by title_score_list_draw */
typedef struct TitleScoreRow {
    s32 score;
    s32 unk_4;
    u8 name[4];
} TitleScoreRow;

/* View of Pad3dSoundInfo from 0x24: the name rows of the two record tables. */
typedef struct TitleNameSave {
    u8 unk_00[8];
    Pad3dSoundRow rows[5];
    TitleScoreRow scores[5];
} TitleNameSave;

typedef struct Pad3dSoundInfo {
    u8 pad_00[8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[8];
    Bytes8 unk_18;
    u8 pad_20[4];
    u8 unk_24; /* mode (apply_sound_mode) */
    u8 unk_25; /* picks title_scale's value */
    u8 pad_26[2];
    u8 selected_index;
    u8 pad_29[3];
    Pad3dSoundRow menu_rows[5]; /* rows drawn by title_draw_menu_list */
    TitleScoreRow score_rows[5]; /* rows drawn by title_score_list_draw */
} Pad3dSoundInfo;

/* movie playback parameters filled for play_movie (title_movie_play) */
typedef struct MovieParams {
    Bytes8 head;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 width;
    s32 height;
    s32 unk_1C;
    s32 unk_20;
    u8 *buf0;
    u8 *buf1;
    u8 *buf2;
    u8 *buf2_end;
    s32 unk_34;
    s32 rgb24;
    u8 pad_3C[0xC];
} MovieParams;

/* PsyQ CdlLOC: a disc position (minute, second, sector, mode) */
typedef struct CdlLOC {
    u8 b[4];
} CdlLOC;

/* PsyQ CdlFILE, filled by CdSearchFile */
typedef struct CdlFILE {
    CdlLOC pos;
    u32 size;
    char name[16];
} CdlFILE;

/* PsyQ DISPENV (0x14 bytes); the original's stack frame keeps 0x64 more after it */
typedef struct MovieDispEnv {
    s16 disp_x;
    s16 disp_y;
    s16 disp_w;
    s16 disp_h;
    Bytes8 screen;
    u8 isinter;
    u8 isrgb24;
    u8 pad_12[0x66];
} MovieDispEnv;

/* from pad3d_show */
/* one animation track of the 3D pad: 6 key tables, their times and count */
typedef struct Pad3dTrack {
    /* 0x00 */ u8 keys[6][0x20];
    /* 0xC0 */ s32 times[8];
    /* 0xE0 */ s32 count;
} Pad3dTrack;

typedef struct Pad3dState {
    s16 pos_x;
    s16 pos_y;
    s16 pos_z;
    u8 pad_006[2];
    s16 rot_x;
    s16 rot_y;
    s16 rot_z;
    u8 pad_00E[2];
    Pad3dTrack tracks[4];
    s16 unk_3A0;
    u8 pad_3A2[2];
    s16 duration;
    s16 frame;
    s16 unk_3A8;
    s16 track_index;
    s16 from_index;
    s16 to_index;
    s16 shown_index;
} Pad3dState;

/* from title_rec_place */
typedef struct TitlePlaceRec {
    u8 pad_00[4];
    s16 y;
    u8 pad_06[2];
    s16 x;
    s16 unk_0A;
    s16 unk_0C;
} TitlePlaceRec;

/* from title_cursor_set_pos */
typedef struct TitleCursorPos {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 unk_08;
} TitleCursorPos;

/* from title_label_init */
typedef struct TitleLabel {
    u8 pad_00[4];
    s16 unk_04;
    u8 pad_06[2];
    s16 unk_08;
    u8 pad_0A[2];
    s16 mode;
    u8 pad_0E[2];
    s32 state_ptr;
    s16 bar_a_x;
    u8 pad_16[6];
    s16 bar_a_x2;
    s16 bar_a_y2;
    s16 bar_b_x;
    u8 pad_22[6];
    s16 bar_b_x2;
    s16 bar_b_y2;
    s16 bar_c_x;
    u8 pad_2E[6];
    s16 bar_c_x2;
    s16 bar_c_y2;
} TitleLabel;

/* from title_panel_open */
typedef struct TitlePanelState {
    s16 unk_00;
    u8 pad_02[2];
    s16 unk_04;
    u8 pad_06[2];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x74 - 0x10];
    s16 unk_74;
} TitlePanelState;

/* from card_read */
typedef struct TitleCtrlReq {
    u8 unk_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    u8 unk_20[4];
    s32 unk_24;
} TitleCtrlReq;

/* from title_record_reset */
typedef struct TitleCardState {
    u8 pad_00[0x1C];
    s16 unk_1C;
    u8 pad_1E[0x18];
    s16 unk_36;
} TitleCardState;

/* from title_table_start */
typedef struct Rec801116A0 {
    u8 pad_00[0x48];
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
} Rec801116A0;

/* from panel_show */
typedef struct Rec80111DB4 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
} Rec80111DB4;

/* from panel_show */
typedef struct TitlePanelFlag {
    s16 unk_00;
} TitlePanelFlag;

/* from title_menu_start */
typedef struct TitleMenuState {
    u8 unk_00[0x1C];
    s16 unk_1C;
    u8 unk_1E[0x36 - 0x1E];
    s16 unk_36;
} TitleMenuState;

/* from title_block_start, title_request_start */
typedef struct TitleBlock {
    void *src;
    u8 pad_04[2];
    s16 unk_06;
    u8 pad_08[4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[8];
    s16 unk_24;
} TitleBlock;

/* from card_list_show */
typedef struct CardListState {
    u8 unk_00[0x1C];
    s16 unk_1C;
} CardListState;

/* from frame_end */
typedef struct TitleDrawCtx {
    u8 unk_00[0x14];
    u8 draw_env[0x5C];
    u8 *prim_base; /* 0x70 */
    u8 *ot_base; /* 0x74 */
} TitleDrawCtx;

/* card_ctrl, returned by card_get_ctrl */
typedef struct TitleCtrl {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 result;
    /* 0x0C */ s32 file_name;
    /* 0x10 */ s32 buffer;
    /* 0x14 */ s32 offset;
    /* 0x18 */ s32 size;
    /* 0x1C */ s32 value;
    /* 0x20 */ s32 wait_count;
    /* 0x24 */ s32 done;
} TitleCtrl;

/* from title_mode_set_value */
typedef struct TitleState {
    u8 pad_00[8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x124 - 0x0E];
    s16 mode_value;
    s16 unk_126;
} TitleState;

/* from logo_hide */
typedef struct TitleLogoRec {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x64];
    s16 unk_74;
} TitleLogoRec;

/* from task_reset */
typedef struct TitleCtl {
    u8 unk_00[0x14];
    struct TitleAnim *anim; /* 0x14 */
    s32 unk_18;
    s16 unk_1C;
    s16 unk_1E;
    u8 unk_20[2];
    s16 step;
    s32 unk_24;
} TitleCtl;

/* from task_set */
typedef struct TitleTaskRec {
    /* 0x00 */ s32 reset_fn;
    /* 0x04 */ s32 update_fn;
    /* 0x08 */ s32 draw_fn;
    /* 0x0C */ u8 pad_0C[8];
    /* 0x14 */ s32 param;
} TitleTaskRec;

/* from task_unlink */
typedef struct TitleLinkNode {
    /* 0x00 */ u8 pad_00[0xC];
    /* 0x0C */ struct TitleLinkNode *prev;
    /* 0x10 */ struct TitleLinkNode *next;
} TitleLinkNode;

/* from ok_box_animate */
typedef struct TitleScrollState {
    /* 0x00 */ u8 pad_00[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} TitleScrollState;

typedef struct TitleCardWin {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 w;
    /* 0x0A */ s16 h;
    /* 0x0C */ s32 v0C;
    /* 0x10 */ s32 v10;
    /* 0x14 */ s32 v14;
    /* 0x18 */ s32 v18;
    /* 0x1C */ s16 active;
    /* 0x1E */ u8 pad_1E[2];
    /* 0x20 */ s16 mode;
    /* 0x22 */ u8 pad_22[0x16];
    /* 0x38 */ s16 v38;
    /* 0x3A */ s16 index;
    /* 0x3C */ s16 v3C;
} TitleCardWin;

typedef struct TitleCardTask {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ TitleCardWin *win;
    /* 0x18 */ u8 pad_18[0x0A];
    /* 0x22 */ s16 state;
} TitleCardTask;

/* Fade/scroll state driven by title_fx_update (overlays TitleMenuRec). */
/* one choice of a title menu: the task it starts and its transition */
typedef struct TitleMenuChoice {
    /* 0x00 */ TitleMenuNode *task;
    /* 0x04 */ u16 kind;
    /* 0x06 */ s16 effect_b;
    /* 0x08 */ s16 fx_kind;
    /* 0x0A */ s16 effect_a;
} TitleMenuChoice;

typedef struct TitleFxState {
    /* 0x00 */ u8 unk_00[0x16];
    /* 0x16 */ s16 step;
    /* 0x18 */ u8 unk_18[4];
    /* 0x1C */ u16 choice_values[8];
    /* 0x2C */ u8 unk_2C[2];
    /* 0x2E */ s16 rec_index;
    /* 0x30 */ s16 duration_frames;
    /* 0x32 */ s16 progress;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ s16 fade_scale;
    /* 0x38 */ u16 fade_frames;
    /* 0x3A */ u16 fade_counter;
    /* 0x3C */ TitleMenuChoice choices[5];
    /* 0x78 */ u8 unk_78[0x24];
    /* 0x9C */ TitleMenuNode *back_task;
    /* 0xA0 */ u16 back_kind;
    /* 0xA2 */ s16 back_effect_b;
    /* 0xA4 */ s16 back_fx_kind;
    /* 0xA6 */ s16 back_effect_a;
    /* 0xA8 */ s16 direction;
} TitleFxState;

/* One 8-byte vertex of a title panel's 3x3 grid (SVECTOR layout). */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} TitleGridVtx;

/* A GTE rotation + translation matrix (PsyQ MATRIX layout) as the words the control registers take, or halves:
 * w[0..4] = R11R12, R13R21, R22R23, R31R32, R33; h[8] = R33 alone. */
typedef union TitleRotWords {
    s32 w[8];
    s16 h[16];
} TitleRotWords;

struct TitleExitTask;

typedef struct TitleExitTask {
    u8 pad_00[0x14];
    s16 *counter; /* 0x14 */
    u8 pad_18[0xA];
    s16 state;    /* 0x22 */
} TitleExitTask;

typedef struct TitleExitInfo {
    u8 pad_00[8];
    s32 unk_08;
} TitleExitInfo;

/* A texture coordinate pair (title_uv_quad_fill reads the first of title_uv_u0 and of title_uv_u1, >> 6). */
typedef struct TitleUv {
    u16 u;
    u16 v;
} TitleUv;

#endif
