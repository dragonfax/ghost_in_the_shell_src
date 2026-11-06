#ifndef LOADER_TYPES_H
#define LOADER_TYPES_H

/* loader's types (main.c's code, data.c and bss.c include this; types only, so the data files can include
 * it without main.c's declarations of the objects they define). */

#include "common.h"

/* from loader_draw_vram_rect */
typedef struct LoaderPolyFT4 {
    u8 pad_0[3];
    u8 len;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad_1E;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad_26;
} LoaderPolyFT4;

/* from loader_draw_vram_rect */
typedef struct LoaderDrMode {
    u32 tag;
    u32 code[2];
} LoaderDrMode;

/* from loader_movie_read_header */
typedef struct MovieFrameHeader {
    u8 pad_00[8];
    u32 size;
    u8 pad_0C[4];
    u16 w;
    u16 h;
    s32 key0;
    s32 key1;
} MovieFrameHeader;

/* from loader_draw_rect */
typedef struct LoaderTilePrim {
    u8 pad_0[3];
    u8 len;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} LoaderTilePrim;

/* from loader_run_event */
typedef struct LoaderEvent {
    s32 state;
    s32 unk_04;
    s32 unk_08;
} LoaderEvent;

/* from loader_register_sprite_sets */
typedef struct {
    s32 unk_0;
    u16 cell;
    u16 unk_6;
    u16 uv;
    u16 tpage;
} LoaderSprite;

/* from loader_register_sprite_sets */
typedef struct {
    s32 *data;
    s32 count;
} LoaderSpriteSet;

/* from loader_draw_fade_quad */
typedef struct LoaderSprt {
    u32 tag;
    u8 r, g, b, code;
    s16 x, y;
    u8 u, v;
    u16 clut;
    s16 w, h;
} LoaderSprt;

/* from loader_draw_fade_quad */
typedef struct LoaderOwner {
    u8 pad_0[0x30];
    s32 state;
} LoaderOwner;

/* from loader_draw_fade_quad */
typedef struct LoaderDrawObj {
    u8 pad_0[0x2C];
    LoaderOwner *task;
} LoaderDrawObj;

/* from loader_ot_insert_prim */
typedef struct LoaderDrawBuf {
    s16 unk_0;
    s16 unk_2;
    u8 pad_4[6];
    u16 unk_A;
    u8 pad_C[0x70 - 0xC];
    u32 ot[3];
    u8 prims[0x2007C - 0x7C];
    u8 *prim_next;
} LoaderDrawBuf;

/* from loader_draw_pair */
typedef struct LoaderPair {
    /* 0x00 */ s32 first;
    /* 0x04 */ s32 second;
} LoaderPair;

/* from loader_display_update */
typedef struct Raw20 { u8 b[20]; } Raw20;

/* from loader_display_update */
typedef union DisplayEnv {
    Raw20 raw;
    struct {
        s16 disp_x, disp_y, disp_w, disp_h;
        s16 screen_x, screen_y, screen_w, screen_h;
    } f;
} DisplayEnv;

/* from loader_play_event_movie */
typedef struct EventMovieEntry {
    s32 first;
    s32 flag;
} EventMovieEntry;

/* from loader_set_fade_table */
typedef struct { u8 b[256]; } Raw256;

typedef struct Bytes8 {
    u8 b[8];
} Bytes8;

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

/* from loader_init */
typedef struct LoaderTask {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ s16 unk_08; /* cleared */
    /* 0x0A */ s16 unk_0A; /* cleared */
    /* 0x0C */ u8 pad_0C[8];
    /* 0x14 */ void (*update)(); /* loader_ramp_update; the callbacks take (void *, LoaderTask *) */
    /* 0x18 */ s16 unk_18; /* cleared */
    /* 0x1A */ s16 unk_1A; /* cleared */
    /* 0x1C */ u8 pad_1C[8];
    /* 0x24 */ void *unk_24; /* &loader_draw_pair */
} LoaderTask;

/* from loader_entry_init */
typedef struct LoaderName {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ u8 *text;
} LoaderName;

/* from loader_entry_init */
typedef struct LoaderSource {
    /* 0x00 */ u8 pad_00[0x30];
    /* 0x30 */ s32 unk_30; /* counter; loader_entry_update acts when it is 2 */
    /* 0x34 */ LoaderName *name_info;
} LoaderSource;

/* from loader_entry_init */
typedef struct LoaderEntry {
    /* 0x00 */ u8 pad_00[0x2C];
    /* 0x2C */ LoaderSource *source;
    /* 0x30 */ s32 char_index; /* cleared */
    /* 0x34 */ s32 step_accum; /* cleared */
    /* 0x38 */ u8 *name;
    /* 0x3C */ u8 pad_3C[8];
    /* 0x44 */ s32 text_x; /* (0xFA - text width) / 2, text placement */
    /* 0x48 */ s32 phase; /* set to 0x800 */
    /* 0x4C */ s32 hold_counter; /* cleared */
} LoaderEntry;

/* from loader_copy_shared_header */
typedef struct UnalignedPair {
    s32 lo;
    s32 hi;
} __attribute__((packed)) UnalignedPair;

/* from dlist_insert_after */
typedef struct DListNode {
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

/* A VRAM rectangle (screen_reset). */
typedef struct Rect {
    s16 x, y, w, h;
} Rect;

/* from loader_node_init */
/* A node of the list loader_node_list_head returns (loader_run_callbacks2, loader_run_callbacks walk it). */
typedef struct LoaderNode {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ struct LoaderNode *next;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 flags;    /* loader_run_callbacks: runs callback when 0 */
    /* 0x0C */ u8 pad_0C[8];
    /* 0x14 */ void (*callback)(void *, struct LoaderNode *);
    /* 0x18 */ s16 unk_18;   /* its address is the callbacks' first argument */
    /* 0x1A */ s16 flags2;   /* loader_run_callbacks2: runs callback2 when 0 */
    /* 0x1C */ u8 pad_1C[8];
    /* 0x24 */ void (*callback2)(void *, struct LoaderNode *);
    /* 0x28 */ s32 state;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 owner;
    /* 0x34 */ s32 pair;
} LoaderNode;

/* from loader_job_init */
typedef struct LoaderJob {
    /* 0x00 */ Bytes8 head;
    /* 0x08 */ s32 disp_x;
    /* 0x0C */ s32 disp_y;
    /* 0x10 */ s32 screen_x;
    /* 0x14 */ s32 unk_14; /* set to 0x100 before the call */
    /* 0x18 */ s32 unk_18; /* set to 0xC0 */
    /* 0x1C */ s32 unk_1C; /* argument */
    /* 0x20 */ s32 unk_20; /* set to 0x28 */
    /* 0x24 */ u32 unk_24; /* table at 0x80040000 */
    /* 0x28 */ u32 unk_28; /* table at 0x80050000 */
    /* 0x2C */ u32 unk_2C; /* table at 0x80060000 */
    /* 0x30 */ u32 unk_30; /* table at 0x80066000 */
    /* 0x34 */ s32 unk_34; /* cleared */
    /* 0x38 */ s32 is_rgb24; /* set to 1 (24-bit movie) */
    /* 0x3C */ u8 pad_3C[12];
} LoaderJob;

/* from slot_release */
typedef struct LoaderSlot {
    /* 0x00 */ Node node;
    /* 0x08 */ u8 pad_08[2];
    /* 0x0A */ s16 unk_0A; /* set to 1 */
    /* 0x0C */ u8 pad_0C[8];
    /* 0x14 */ s32 unk_14; /* cleared */
    /* 0x18 */ u8 pad_18[2];
    /* 0x1A */ s16 unk_1A; /* set to 1 */
    /* 0x1C */ u8 pad_1C[8];
    /* 0x24 */ s32 unk_24; /* cleared */
    /* 0x28 */ s32 in_use; /* 1 while the slot is in use */
    /* 0x2C */ u8 pad_2C[0x40];
} LoaderSlot;

/* the loader context returned by service slot slot_shared_state */
typedef struct LoaderCtx {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 special_code; /* read clamped to 0..11 */
    /* 0x08 */ u8 pad_08[0x1E];
    /* 0x26 */ u8 unk_26;
    /* 0x27 */ u8 pad_27[0x7D];
    /* 0xA4 */ u8 flags[0x1C]; /* flags, set to 1 by index */
    /* 0xC0 */ s32 dev_mode;
    /* 0xC4 */ u8 pad_C4[8];
    /* 0xCC */ s32 unk_CC;
} LoaderCtx;

/* from loader_state_init */
typedef struct LoaderState {
    /* 0x00 */ u8 pad_00[0x2C];
    /* 0x2C */ s32 unk_2C; /* loader_state_init sets it, clears unk_30 */
    /* 0x30 */ s32 char_count;
    /* 0x34 */ u8 pad_34[4];
    /* 0x38 */ u8 *text;
    /* 0x3C */ s32 text_x; /* loader_state_reset copies unk_44 here, sets unk_40 to 0x8C */
    /* 0x40 */ s32 text_y;
    /* 0x44 */ s32 text_start_x;
    /* 0x48 */ s32 unk_48;
} LoaderState;

typedef struct TitleRect {
    s16 x, y, w, h;
} TitleRect;

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

struct TitleCmd {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 total_size;
};

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

typedef struct TitleSwap {
    /* 0x00 */ u8 pad_00[0x10];
    /* 0x10 */ s16 entries[2][4];
    /* 0x20 */ s32 toggle;
    /* 0x24 */ s16 x;
    /* 0x26 */ s16 y;
    /* 0x28 */ u8 pad_28[4];
    /* 0x2C */ s32 busy;
} TitleSwap;

typedef struct CdlLOC {
    u8 b[4];
} CdlLOC;

typedef struct CdlFILE {
    CdlLOC pos;
    u32 size;
    char name[16];
} CdlFILE;

/* One entry of the 64-slot loaded-image table (loaded_image_count counts the used ones). */
typedef struct LoaderImageRec {
    u8 u0;
    u8 v0;
    u8 u1;
    u8 v1;
    s16 width;
    s16 height;
    u16 tpage;
    u16 pad_A;
} LoaderImageRec;

/* PsyQ P_TAG: OT link and word count */
typedef struct LoaderPrimTag {
    u32 addr : 24;
    u32 len : 8;
} LoaderPrimTag;

/* Gouraud quad (GPU POLY_G4) */
typedef struct LoaderPolyG4 {
    LoaderPrimTag tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, pad1;
    s16 x1, y1;
    u8 r2, g2, b2, pad2;
    s16 x2, y2;
    u8 r3, g3, b3, pad3;
    s16 x3, y3;
} LoaderPolyG4;

/* Flat triangle (GPU POLY_F3) */
typedef struct LoaderPolyF3 {
    LoaderPrimTag tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
} LoaderPolyF3;

/* Flat quad (GPU POLY_F4) */
typedef struct LoaderPolyF4 {
    LoaderPrimTag tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} LoaderPolyF4;

/* Sound request block handed to slot_snd_alloc_channel: {0x117, tone id, 0}. */
typedef struct LoaderSndReq {
    s32 kind;
    s32 tone_id;
    s32 unk_08;
} LoaderSndReq;

/* Tone volume record: volume (written from slot_tone_volume) plus unknown defaults. */
typedef struct LoaderToneVol {
    s32 volume;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} LoaderToneVol;

#endif
