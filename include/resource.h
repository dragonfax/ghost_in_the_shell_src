#ifndef RESOURCE_H
#define RESOURCE_H

/* A stage's resource tables: what it loads and from where. Types only (no declarations), so the data files can
 * include this without stage.h's declarations of the same objects. */

#include "common.h"

/* An enemy's or the engine's models (stage_model_block_load); a field is a pointer or an offset from the block
 * (block_ref). */
typedef struct ModelBlockRef {
    s32 handle;
    s16 a;
    s16 b;
} ModelBlockRef;
/* from stage_model_block_load */
typedef struct ModelBlockRange {
    s16 first;
    s16 last;
    s16 a;
    s16 b;
} ModelBlockRange;
/* from stage_model_block_load */
typedef struct ModelBlock {
    s32 palettes;     /* 0x00 */
    s32 models;       /* 0x04 */
    s32 textures;     /* 0x08 */
    s32 links;        /* 0x0C */
    s32 values;       /* 0x10 */
    s32 angles;       /* 0x14 */
    s32 scales;       /* 0x18 */
    s32 palette_ids;  /* 0x1C */
    s32 id_flags;     /* 0x20 */
} ModelBlock;

/* One loader step (scan_items_run): a pair of hooks, three result words, and up to three things to load. For an
 * enemy: its two handlers (hook_table) and its slot (keyholder_asset ...: {-1, -1, -1} until loaded). */
typedef struct ScanEntry {
    s32 hooks[2];       /* 0x00: hook_set's pair for the step's index (functions, or 0) */
    s32 *out;           /* 0x08: three result words (model, ptr table count, files), set to -1 first */
    s32 model_block;    /* 0x0C: a ModelBlock for stage_model_block_load, 0 when unused */
    s32 ptr_table_ids;  /* 0x10: ptr_table_load_ids argument (a zero-ended list of names), 0 when unused */
    s32 stage_files;    /* 0x14: stage_files_load argument (a zero-ended list of names), 0 when unused */
} ScanEntry;

/* A list of loader steps, ended by an entry of -1; the name is the step's directory (its debug name). */
typedef struct ScanItem {
    ScanEntry *entry;
    u8 *name;
} ScanItem;

/* The engine's own resources (get_rec_root): its directory, archive and loader steps. */
typedef struct ResourceRoot {
    u8 *dir;            /* ..\main\data\ */
    u8 *archive;        /* com_dat.fac */
    ScanItem *items;    /* run by load_stage_data */
} ResourceRoot;

/* One part of a mission (area_entry_table, get_area_entry): its directory and files. Read in pieces by the code
 * as NamedEntry (name, config), SetupEntry (name, grid, pos) and AreaData (items). */
typedef struct AreaEntry {
    u8 *name;           /* 0x00: directory, the debug name; bg_load_request's name */
    u8 *config;         /* 0x04: .bcf, named_entry_run's record (stage_data_set) */
    u8 *grid;           /* 0x08: .ea3, setup_stage's record (grid_load) */
    u8 *joy;            /* 0x0C: .bin */
    u8 *archive;        /* 0x10: <stage>_dat.fac, loaded by load_stage_data */
    u8 *part_archive;   /* 0x14: <stage>_ene.fac, loaded by load_stage_part */
    s16 pos[3];         /* 0x18: setup_stage's position */
    s16 unk_1E;
    s32 sound_arg;      /* 0x20: sound_stage_init's argument */
    ScanItem *items;    /* 0x24: scan_record_run's loader steps */
} AreaEntry;

#endif
