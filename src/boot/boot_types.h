#ifndef BOOT_TYPES_H
#define BOOT_TYPES_H

/* boot's types (main.c, main2.c, data*.c include this; types only, so the data files can include it without the
 * declarations of the objects they define). */

#include "common.h"
#include "boot.h"

/* from sound_tick */
typedef struct SpuVolume {
    s16 left;
    s16 right;
} SpuVolume;

/* from sound_tick */
typedef struct SpuVoiceAttr {
    /* 0x00 */ u32 voice;
    /* 0x04 */ u32 mask;
    /* 0x08 */ SpuVolume volume;
    /* 0x0C */ SpuVolume volmode;
    /* 0x10 */ SpuVolume volumex;
    /* 0x14 */ u16 pitch;
    /* 0x16 */ u16 note;
    /* 0x18 */ u16 sample_note;
    /* 0x1A */ s16 envx;
    /* 0x1C */ u32 addr;
    /* 0x20 */ u32 loop_addr;
    /* 0x24 */ s32 a_mode;
    /* 0x28 */ s32 s_mode;
    /* 0x2C */ s32 r_mode;
    /* 0x30 */ u16 ar;
    /* 0x32 */ u16 dr;
    /* 0x34 */ u16 sr;
    /* 0x36 */ u16 rr;
    /* 0x38 */ u16 sl;
    /* 0x3A */ u16 adsr1;
    /* 0x3C */ u16 adsr2;
} SpuVoiceAttr;

/* from sound_tick */
typedef struct SoundVoiceSlot {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ volatile s32 state; /* 0 free, 1 key-on pending, then frames since key-on (from 2) */
    /* 0x08 */ u8 unk_08[0x08];
    /* 0x10 */ volatile s32 pitch;
    /* 0x14 */ u8 unk_14[0x08];
    /* 0x1C */ volatile u16 reverb;
    /* 0x1E */ volatile s16 timer;  /* frames in the current key status */
    /* 0x20 */ volatile s32 flags;  /* bit 0: reverb off, bit 1: never key off a silent voice */
    /* 0x24 */ SpuVolume volume;
    /* 0x28 */ volatile s32 addr;
    /* 0x2C */ volatile u16 adsr1;
    /* 0x2E */ volatile u16 adsr2;
} SoundVoiceSlot;

/* from snd_alloc_channel */
typedef struct SndAllocVoice {
    /* 0x00 */ u32 key;
    /* 0x04 */ volatile s32 in_use;
    /* 0x08 */ struct VagAtr *volatile tone;
    /* 0x0C */ volatile s32 handle;
    /* 0x10 */ volatile s32 pitch;
    /* 0x14 */ volatile u32 serial;
    /* 0x18 */ volatile s16 priority;
    /* 0x1A */ volatile u16 pan;
    /* 0x1C */ volatile u16 volume;
    /* 0x1E */ volatile u16 active;
    /* 0x20 */ volatile u32 flags;
    /* 0x24 */ s16 vol_left;
    /* 0x26 */ s16 vol_right;
    /* 0x28 */ volatile s32 addr;
    /* 0x2C */ u16 adsr1;
    /* 0x2E */ u16 adsr2;
} SndAllocVoice;

/* from vab_tones_install */
typedef struct VagAtr {
    u8 prior;
    u8 mode;
    u8 vol;
    u8 pan;
    u8 center;
    u8 shift;
    u8 min;
    u8 max;
    u8 vibW;
    u8 vibT;
    u8 porW;
    u8 porT;
    u8 pbmin;
    u8 pbmax;
    u8 reserved1;
    u8 reserved2;
    u16 adsr1;
    u16 adsr2;
    s16 prog;
    s16 vag;
    s16 reserved[4];
} VagAtr;

/* from stream_depth_check */
typedef struct {
    s32 depth;
    u8 names[9][16];
} CdPathTable;

/* from vab_slot_load */
typedef struct VabSlotFields {
    u32 spu_size;
    u32 spu_addr;
    u16 prog_start;
    u16 prog_count;
    u16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
    u16 tone_start;
    u16 tone_count;
    u16 pair_start;
    u16 pair_count;
} VabSlotFields;

/* from vab_prog_find */
typedef struct VabProgEntry {
    s32 index;
    u8 key;
    u8 num;
    u8 mvol;
    u8 prior;
    u8 mode;
    u8 mpan;
    s16 attr;
} VabProgEntry;

/* from vab_tone_offset */
typedef struct VabToneRef {
    u8 unk_00[0x16];
    s16 pair_index;
    s16 slot_index;
} VabToneRef;

/* from sound_req_active_id */
typedef struct BootSoundSlotState {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 flag_04;
    /* 0x08 */ u8 unk_08[0x04];
    /* 0x0C */ s32 id_0C;
    /* 0x10 */ u8 unk_10[0x0E];
    /* 0x1E */ u16 active_1E;
    /* 0x20 */ u8 unk_20[0x10];
} BootSoundSlotState; /* 0x30 */

typedef struct SoundRequest {
    /* 0x00 */ u8 unk_00[0x08];
    /* 0x08 */ s32 id_08;
} SoundRequest;

/* from stream_sector_put */
typedef struct StreamSectorHdr {
    /* 0x00 */ u16 magic;      /* 0x160 */
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 frame;
    /* 0x06 */ u16 frame_count;
    /* 0x08 */ s32 id;
    /* 0x0C */ s32 frame_size;
    /* 0x10 */ s32 unk_10[4];
} StreamSectorHdr;

/* from stream_sector_put */
typedef struct StreamState {
    /* 0x00 */ s32 state;      /* 0 idle, 1 receiving, 2 done */
    /* 0x04 */ s32 id;
} StreamState;

/* from music_play_by_id */
typedef struct {
    u32 word;
} __attribute__((packed)) Unaligned32;

/* from music_play_by_id */
typedef struct {
    u8 id;
    u8 flags;       /* 0x80: msf is a count that cd_msf_to_sector converts */
    u8 unk_02;
    u8 unk_03;
    s32 open_arg;
    u8 msf[4];
} CdEntry;

/* from spufunc_init */
typedef struct SpuCommonAttrInit {
    s32 mask;
    s16 mvol_l;
    s16 mvol_r;
    s16 mvolmode_l;
    s16 mvolmode_r;
    s32 unk_0C;
    s16 cd_vol_l;
    s16 cd_vol_r;
    s32 cd_reverb;
    s32 cd_mix;
    s16 ext_vol_l;
    s16 ext_vol_r;
    s32 ext_reverb;
    s32 ext_mix;
} SpuCommonAttrInit;

/* from spufunc_init */
typedef struct SpuVoiceAttrInit {
    s32 voice;
    s32 mask;
    s16 volmode_l;
    s16 volmode_r;
    s16 unk_0C;
    s16 unk_0E;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 addr;
    s32 loop_addr;
    s32 a_mode;
    s32 s_mode;
    s32 r_mode;
    s16 ar;
    s16 dr;
    s16 sr;
    s16 rr;
    s16 sl;
    s16 unk_3A;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
} SpuVoiceAttrInit;

/* from stream_setup */
typedef struct StreamFrameParam {
    /* 0x00 */ s32 buffer_base;
    /* 0x04 */ s32 callback;
    /* 0x08 */ u32 buffer_size;
    /* 0x0C */ u32 area_size;
    /* 0x10 */ u32 frame_start;
    /* 0x14 */ u32 frame_end;
} StreamFrameParam;

/* from sound_key_on_slot */
typedef struct SndAllocBlock {
    s32 kind;
    s32 tone_key;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s16 volume;
    s16 unk_1A;
    s16 unk_1C;
    s16 priority;
} SndAllocBlock;

/* from exec_load_mem */
typedef struct ExecImageHeader {
    s32 pc0, gp0, t_addr, t_size, d_addr, d_size, b_addr, b_size;
    s32 s_addr, s_size, sp, fp, gp, ra, s0;
} ExecImageHeader;

/* from callback_table_add */
typedef struct CallbackSlot {
    s32 callback;
    s16 unk_04;
    s16 param;
} CallbackSlot;

/* from sector_stream_read */
typedef struct {
    s32 pos;     /* read offset into the current sector buffer */
    s32 sector;  /* index of the current sector */
    u8 *buf;     /* data of the current sector */
} SectorStream;

/* from stream_slot_alloc */
typedef struct StreamSlot {
    s32 type;
    s32 value;
} StreamSlot;

/* from boot_pairs_load */
typedef struct BootPair {
    s32 unk_00;
    s32 unk_04;
} BootPair;

/* from graph_buf_init */
typedef struct GraphBuf {
    s16 x;
    s16 y;
    s16 unk4;
    s16 unk6;
    s16 x2;
    s16 y2;
    s16 unk0C;
    s16 unk0E;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s8 unk16;
    s8 unk17;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
} GraphBuf;

/* from cdfs_path_chain_match */
typedef struct CdfsPathRecord {
    s32 pad0;
    s32 next;
    u8 name[16];
} CdfsPathRecord;

/* from cdfs_path_resolve */
typedef struct BootBlock84 { s32 w[33]; } BootBlock84;

/* from put_disp_env_checked */
typedef struct DispEnv {
    unsigned char bytes[20];
} DispEnv;

/* from spufunc_set_reverb_depth */
typedef struct {
    s32 mask;
    s32 mode;
    s16 depth_left;
    s16 depth_right;
    s32 unk_0C[3];
} SpuReverbAttr;

/* from pc_file_size */
typedef struct FileInfo {
    s32 unk_00;
    s32 size;
    s32 unk_08[4];
} FileInfo;

/* from thread_schedule, sched_shutdown: sched_thread_slots's thread slots */
typedef struct ThreadSlot {
    s32 handle;
    s32 count;
    s32 limit;
} ThreadSlot;

/* from vab_slot_reset */
typedef struct VabSlotEntry {
    u32 spu_base;
    u32 spu_addr;
    u16 prog_start;
    u16 prog_count;
    u16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
    u16 tone_start;
    u16 tone_count;
    u16 pair_start;
    u16 pair_count;
} VabSlotEntry;

/* from disp_rect_init */
typedef struct DispRect {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 screen_x;
    /* 0x0A */ s16 screen_y;
    /* 0x0C */ s16 screen_width;
    /* 0x0E */ s16 screen_height;
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 flag;
} DispRect;

/* from vab_slot_get */
typedef struct VabSlot {
    u8 unk_00[8];
    u16 prog_start;
    u16 prog_count;
    u16 max_prog_key;
    u8 voice_first;
    u8 voice_count;
    u16 tone_base;
    u8 pad_12[6];
} VabSlot;

/* from cd_set_volume */
typedef struct CdlATV {
    u8 left_to_left;
    u8 left_to_right;
    u8 right_to_left;
    u8 right_to_right;
} CdlATV;

/* from sector_cache_clear */
typedef struct SectorCacheEntry {
    u8 flag;
    u8 pos_tail[3];
    s32 age; /* use counter; halved when it gets large (sector_cache_touch) */
    u8 sector_data[0x800];
} SectorCacheEntry;

/* from thread_set_current */
typedef struct Tcb {
    s32 status; /* 0x4000 while the thread is in use */
    u8 unk_04[0xC0 - 4];
} Tcb;

/* from spu_set_main_volume */
typedef struct SpuCommonAttrBlock {
    u32 mask;
    s16 mvol_left;
    s16 mvol_right;
    u8 unk_08[0x20];
} SpuCommonAttrBlock;

/* from boot_rec_free_bytes, boot_rec_group_count */
typedef struct BootRec {
    u8 pad_00[0xC];
    s32 total_size;
    u8 pad_10[2];
    u16 unk_12;
    u16 group_count;
    u16 pair_count;
} BootRec;

/* from frame_task_slot_clear */
typedef struct FrameTaskSlot {
    void (*callback)(void);
    s16 frame_counter;
    s16 interval;
} FrameTaskSlot;

/* from sound_active_mask */
typedef struct BootSoundSlot {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 flag_04;
    /* 0x08 */ u8 unk_08[0x28];
} BootSoundSlot; /* 0x30 */

/* from exec_run */
typedef struct PsxExec {
    u32 pc0;
    u32 gp0;
    u32 t_addr;
    u32 t_size;
    u32 d_addr;
    u32 d_size;
    u32 b_addr;
    u32 b_size;
    u32 s_addr;
} PsxExec;

/* from vab_prog_count */
/* a VAB program attribute record (PsyQ ProgAtr) */
typedef struct VabProgAtr {
    u8 tones;
    u8 mvol;
    u8 prior;
    u8 mode;
    u8 mpan;
    u8 pad_05;
    s16 attr;
    u8 pad_08[8];
} VabProgAtr;

typedef struct BootSlot {
    u8 unk_00[0x12];
    u16 prog_count;
    u8 pad_14[0xC];
    VabProgAtr progs[1];
} BootSlot;

typedef struct SoundSlotScore {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 flag_04;
    /* 0x08 */ u8 unk_08[0x10];
    /* 0x18 */ u16 score_18;
} SoundSlotScore;

/* One 0xC-byte record of the music table (same as main.c's MusicSlot). */
typedef struct MusicSlot {
    u8 music_no;   /* 0x00: music id, 0xFF ends the table */
    u8 unk_01;     /* 0x01: always 0xC8 */
    u8 attr1;      /* 0x02 */
    u8 unk_03;     /* 0x03: cfg value 6 */
    u8 *name;      /* 0x04: name in the buffer */
    u8 attr2;      /* 0x08 */
    u8 attr3;      /* 0x09 */
    u8 attr4;      /* 0x0A */
    u8 active;     /* 0x0B: 1 when in use */
} MusicSlot;

/* One entry of the [MOVIE] table (64 entries). */
typedef struct MovieSlot {
    s32 movie_id; /* 0x00 */
    u8 *name;     /* 0x04 */
} MovieSlot;

/* 16-byte record of the cd/message queue; msg_queue_alloc, msg_queue_peek and cd_clear_records (main.c) use it. */
typedef struct MsgQueueEntry {
    s32 state;
    s32 unk_04;
    u8 unk_08[8];
} MsgQueueEntry;

#endif
