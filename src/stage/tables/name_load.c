/* name_load: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

#if STAGE == 1
/* Stores `value` in name_table_base. */
void set_name_table_ptr(s32 value) {
    name_table_base = value;
}
#endif

#if STAGE != 1
extern s32 name_table_base;

void set_name_table_ptr(s32 arg0) {
    name_table_base = arg0;
}
#endif

#if STAGE != 1
extern s32 name_table_base;
#endif

/* Returns name_table_base. */
s32 name_base_get(void) {
    return name_table_base;
}

/* Reads a name-table record: its first word holds the size (16-bit halves
   byte-swapped, 24 bits); copies the data after it to dest. Falls back to
   file_read_retry without a name table; -1 if the name is not found. */
s32 name_record_read(char *name, void *dest) {
    NameRec *rec;
    s32 *data;
    s32 word;
    s32 size;
    register s32 mask asm("a2"); /* the original masks with the argument register */

    if (name_table_base == 0) {
        return file_read_retry(name, dest);
    }
    name_table_set((NameEntry *) name_table_base);
    file_name_build((u8 *) name);
    rec = (NameRec *) name_table_lookup(name);
    if (rec == NULL) {
        return -1;
    }
    mask = 0xFFFFFF;
    data = (s32 *) (name_table_base + rec->offset);
    word = *data;
    size = (((word & 0xFF) << 8) | ((word & 0xFF00) >> 8)) << 16;
    size |= (((word >> 16) & 0xFF) << 8) | (((word >> 16) & 0xFF00) >> 8);
    size &= mask;
    lz_decompress(data + 1, dest, mask);
    return size;
}

/* Looks up a name's colour word and returns it as 0xRRGGBB with each
   16-bit half's bytes swapped (BGR order); -1 if the name is not found. */
s32 name_color_get(char *name) {
    NameRec *rec;
    s32 color;
    s32 low_part;
    s32 high_part;

    if (name_table_base == 0) {
        return file_seek_retry(name);
    }
    name_table_set((NameEntry *) name_table_base);
    file_name_build((u8 *) name);
    rec = (NameRec *) name_table_lookup(name);
    if (rec == NULL) {
        return -1;
    }
    color = *(s32 *) (name_table_base + rec->offset);
    low_part = (((color & 0xFF) << 8) | ((color & 0xFF00) >> 8)) << 16;
    high_part = color >> 16;
    return (low_part | (((high_part & 0xFF) << 8) | ((high_part & 0xFF00) >> 8))) & 0xFFFFFF;
}

s32 name_load(s8 *name) {
    NameEntry *entry;
    s32 *rec;
    s32 word;
    s32 header;
    s32 size;

    if (name_table_base == 0) {
        return (s32)file_load_to_heap(name);
    }
    name_table_set((NameEntry *)name_table_base);
    file_name_build((u8 *)name);
    entry = name_table_lookup(name);
    if (entry == NULL) {
        return 0;
    }
    /* the record's offset from the table base */
    rec = (s32 *)(name_table_base + ((NameRec *)entry)->offset);
    /* the stored word has each 16-bit half byte-swapped; the 24-bit result is the key */
    word = rec[0];
    header = ((((word & 0xFF) << 8) | ((word & 0xFF00) >> 8)) << 16);
    header |= (((word >> 16) & 0xFF) << 8) | (((word >> 16) & 0xFF00) >> 8);
    size = heap_bump_alloc(header & 0xFFFFFF);
    lz_decompress((u8 *)rec + 4, size);
    return size;
}

s32 handle_load(u8 *p, s32 extra) {
    s32 raw;
    s32 val;

    switch (p[0]) {
    case 0:
        raw = cmd_swap(*(s32 *)p);
        val = raw & 0xFFFFFF;
        lz_decompress(p + 4, extra, raw);
        return val;
    case 1:
        raw = cmd_swap(*(s32 *)p);
        val = raw & 0xFFFFFF;
        mem_copy_blocks(p + 4, (void *)extra, val);
        return val;
    default:
        return name_record_read((char *) p, (void *) extra);
    }
}

void *record_data_get(u8 *rec) {
    s32 w;
    s32 size;

    switch (rec[0]) {
    case 0:
        w = *(s32 *) rec;
        size = ((((w & 0xFF) << 8) | ((w & 0xFF00) >> 8)) << 16 |
                ((((w >> 16) & 0xFF) << 8) | (((w >> 16) & 0xFF00) >> 8))) & 0xFFFFFF;
        size = heap_bump_alloc(size);
        lz_decompress(rec + 4, size);
        return (void *) size;
    case 1:
        return rec + 4;
    default:
        return (void *) name_load((s8 *) rec);
    }
}

/* Record type 0..1: byte-swap each 16-bit half of the first word and keep 24 bits.
 * Other types fall back to name_color_get. */
s32 record_key_get(u8 *rec) {
    s32 type = rec[0];

    if (type < 2) {
        if (type >= 0) {
            s32 word = *(s32 *)rec;
            s32 lo = (((word & 0xFF) << 8) | ((word & 0xFF00) >> 8)) << 16;
            s32 hi_word = word >> 16;
            s32 hi = ((hi_word & 0xFF) << 8) | ((hi_word & 0xFF00) >> 8);
            return (lo | hi) & 0xFFFFFF;
        }
    }
    return name_color_get((char *)rec);
}

/* Number of entries before the terminating zero key. */
s32 pair_list_count(IntPair *p) {
    s32 n = 0;

    while (p->a != 0) {
        p++;
        n++;
    }
    return n;
}

static inline s32 block_ref(ModelBlock *blk, s32 off) {
    if (off > 0) {
        return (s32)blk + ((off << 8) >> 8);
    }
    return off;
}
s32 stage_model_block_load(ModelBlock *blk, s32 *out) {
    u16 *clut;
    u8 *image;
    s32 ok;
    s32 n_pal;
    s32 n_tex;
    s32 n_models;
    void **models;
    s32 slot;
    s32 i;
    s32 off;
    ModelBlockRef *list;
    ModelBlockRange *r;
    s32 base;

    clut = arena_alloc(0x200);
    image = arena_alloc(0x10008);
    ok = 0;
    *out = -1;
    n_pal = pair_list_count((IntPair *)block_ref(blk, blk->palettes));
    n_tex = pair_list_count((IntPair *)block_ref(blk, blk->textures));
    n_models = pair_list_count((IntPair *)block_ref(blk, blk->models));
    models = arena_alloc(n_models * 4);
    slot = model_slot_new(n_tex, n_pal);
    if (slot < 0) {
        goto done;
    }
    palette_mark_ranges((s16 *)block_ref(blk, blk->palette_ids));
    id_flags_mark_ranges((s16 *)block_ref(blk, blk->id_flags));

    list = (ModelBlockRef *)block_ref(blk, blk->models);
    for (i = 0; list[i].handle != 0; i++) {
        void *data = record_data_get((u8 *)block_ref(blk, list[i].handle));
        models[i] = data;
        if (data == NULL) {
            goto done;
        }
        model_slots_mark_used(data, list[i].a);
    }

    list = (ModelBlockRef *)block_ref(blk, blk->textures);
    for (i = 0; list[i].handle != 0; i++) {
        if (handle_load((u8 *)block_ref(blk, list[i].handle), (s32)image) < 0) {
            goto done;
        }
        model_slot_mark_palette(image, list[i].a);
    }

    list = (ModelBlockRef *)block_ref(blk, blk->palettes);
    for (i = 0; list[i].handle != 0; i++) {
        if (handle_load((u8 *)block_ref(blk, list[i].handle), (s32)clut) < 0) {
            goto done;
        }
        clut_set_stp(0x100, clut);
        model_remap_palettes(slot, i, clut);
    }

    list = (ModelBlockRef *)block_ref(blk, blk->textures);
    for (i = 0; list[i].handle != 0; i++) {
        if (n_tex >= 2) {
            if (handle_load((u8 *)block_ref(blk, list[i].handle), (s32)image) < 0) {
                goto done;
            }
        }
        tex_block_upload(slot, i, list[i].a, image, list[i].b);
    }

    list = (ModelBlockRef *)block_ref(blk, blk->models);
    for (i = 0; list[i].handle != 0; i++) {
        pchr_bank_load_scratch(slot, list[i].a, list[i].b, models[i]);
    }

    model_slot_free_buffers();
    pchr_trim_tail();

    base = model_slot_pchr(slot);
    off = blk->scales;
    if (off <= 0) {
        r = (ModelBlockRange *)off;
    } else {
        r = (ModelBlockRange *)((s32)blk + ((off << 8) >> 8));
    }
    if (r != NULL) {
        for (; r->first >= 0; r++) {
            pchr_scale_range(r->first + base, r->last - r->first + 1, r->a);
        }
    }
    base = model_slot_pchr(slot);
    off = blk->links;
    if (off <= 0) {
        r = (ModelBlockRange *)off;
    } else {
        r = (ModelBlockRange *)((s32)blk + ((off << 8) >> 8));
    }
    if (r != NULL) {
        for (; r->first >= 0; r++) {
            pchr_set_link_offsets(r->first + base, r->last - r->first + 1, r->a, r->b);
        }
    }
    base = model_slot_pchr(slot);
    off = blk->values;
    if (off <= 0) {
        r = (ModelBlockRange *)off;
    } else {
        r = (ModelBlockRange *)((s32)blk + ((off << 8) >> 8));
    }
    if (r != NULL) {
        for (; r->first >= 0; r++) {
            pchr_set_value_range(r->first + base, r->last - r->first + 1, r->a);
        }
    }
    base = model_slot_pchr(slot);
    off = blk->angles;
    if (off <= 0) {
        r = (ModelBlockRange *)off;
    } else {
        r = (ModelBlockRange *)((s32)blk + ((off << 8) >> 8));
    }
    if (r != NULL) {
        for (; r->first >= 0; r++) {
            pchr_set_angle_range(r->first + base, r->last - r->first + 1, r->a);
        }
    }
    ok = 1;
    *out = slot;
done:
    arena_pop(n_models * 4);
    arena_pop(0x10208);
    return ok;
}

s32 stage_files_load(u8 **handles, s32 *out) {
    s32 found = 0;
    void *buf0;
    s32 len;
    void *buf1;
    s32 slot;
    void *src;

    if (out != NULL) {
        *out = -1;
    }
    buf0 = arena_alloc(0x200);
    if (handle_load(handles[0], (s32)buf0) >= 0) {
        len = handle_load(handles[1], (s32)arena_top());
        if (len >= 0) {
            buf1 = arena_alloc(len);
            src = record_data_get(handles[2]);
            if (src != NULL) {
                slot = scratch_slot_load(src, buf0, buf1, len);
                found = 1;
                if (out != NULL) {
                    *out = slot;
                }
            }
            arena_pop(len);
        }
    }
    arena_pop(0x200);
    return found;
}

static inline s32 stage_ref(s32 base, s32 ref) {
    if (ref > 0) {
        return base + ((ref << 8) >> 8);
    }
    return ref;
}
static inline s32 stage_entry(s32 base, s32 ref) {
    if (ref <= 0) {
        return ref;
    }
    return base + ((ref << 8) >> 8);
}
/* Stage setup loader: reads the setup block (each word a 24-bit offset from the block, or an address when
 * 0 or negative) and loads textures, models and placements, lights, anim objects, the record lists, the
 * light records, CLUT and data files, then the get_stage_file_list file list. Returns 0 on any load failure. */
s32 stage_setup_load(void) {
    s32 *setup;
    u16 *clut;
    u8 *pixels;
    s32 *list;
    s32 *handles;
    s32 *out;
    s32 count;
    s32 file;
    s32 top;
    SetupLight *light;
    SetupColourRange *range;
    s32 aobjs;
    s32 i;
    s32 j;
    SetupLightRecord *rec;
    s32 v;
    s32 sub;
    s32 *chars;
    s32 item;
    s32 idx;
    s32 *refs;
    s32 base;
    s32 *entry;
    s32 slot;
    s32 value; /* the 0x30 word, then stage_data_count() */
    s32 *walk;
    s32 clut_size;
    s32 size;
    u8 *data2;

    setup = (s32 *)get_stage_setup_block();
    ((void (*)(s32))set_anim_clock_rate)(setup[0x4C / 4]);
    if (setup[0]) {
        count = (s32)arena_alloc(0x200);
        out = arena_alloc(0x10008);
        if (handle_load((u8 *)stage_ref((s32)setup, setup[0]), count) < 0) {
            return 0;
        }
        if (handle_load((u8 *)stage_ref((s32)setup, setup[1]), (s32)out) < 0) {
            return 0;
        }
        tex_load_4bpp((u16 *)count, (u8 *)out);
        arena_pop(0x10208);
    }
    if (setup[2]) {
        count = (s32)arena_alloc(0x200);
        out = arena_alloc(0x10008);
        if (handle_load((u8 *)stage_ref((s32)setup, setup[2]), count) < 0) {
            return 0;
        }
        if (handle_load((u8 *)stage_ref((s32)setup, setup[3]), (s32)out) < 0) {
            return 0;
        }
        img_upload_4bpp((u16 *)count, (u8 *)out);
        arena_pop(0x10208);
    }
    if (stage_model_block_load(get_stage_model_block(), &slot) == 0) {
        return 0;
    }
    point_set_base(model_slot_pchr(slot));
    part_base_set(model_slot_pchr(slot));

    list = (s32 *)stage_ref((s32)setup, setup[0x1C / 4]);
    if (list == NULL) {
        return 0;
    }
    handles = arena_alloc(0x60);
    count = 0;
    while (*list != 0) {
        file = stage_entry((s32)setup, *list);
        if (handle_load((u8 *)file, (s32)arena_top()) < 0) {
            return 0;
        }
        top = heap_get_top();
        heap_bump_alloc(records_be_to_le(arena_top(), (s32 *)top));
        handles[count] = (s32)sort_records_by_band((void *)top, (s16 *)stage_ref((s32)setup, setup[0x74 / 4]));
        count++;
        list++;
    }
    list = (s32 *)stage_ref((s32)setup, setup[0x20 / 4]);
    if (list == NULL) {
        return 0;
    }
    while ((v = list[3]) >= 0) {
        aobjs = v >> 16;
        idx = v & 0xFFFF;
        sub = idx >> 8;
        idx = v & 0xFF;
        if (idx >= count) {
            return 0;
        }
        scene_model_add(aobjs, sub, list[0], list[1], list[2], handles[idx]);
        list += 4;
    }
    arena_pop(0x60);

    light = (SetupLight *)stage_ref((s32)setup, setup[0x24 / 4]);
    if (light != NULL) {
        while (light->flags >= 0) {
            if (light->flags & 0x100) {
                set_vec3(light->x, light->y, light->z);
            } else {
                model_set_scale(light->flags, light->x, light->y, light->z);
            }
            light++;
        }
    }

    aobjs = aobj_count();
    chars = (s32 *)stage_entry((s32)setup, setup[0x28 / 4]);
    if (chars != NULL) {
        while (*chars != 0) {
            top = (s32)record_data_get((u8 *)stage_ref((s32)setup, *chars));
            if (top == 0) {
                return 0;
            }
            aobj_link_char((u8 *)top);
            chars++;
        }
    }

    list = (s32 *)stage_ref((s32)setup, setup[0x2C / 4]);
    if (list != NULL) {
        handles = arena_alloc(0x60);
        count = 0;
        while (*list != 0) {
            file = stage_entry((s32)setup, *list);
            if (handle_load((u8 *)file, (s32)arena_top()) < 0) {
                return 0;
            }
            list++;
            top = heap_get_top();
            heap_bump_alloc(records_be_to_le(arena_top(), (s32 *)top));
            handles[count] = (s32)atr_map_build((AtrSrc *)top, aobjs);
            count++;
        }
        value = setup[0x30 / 4];
        list = (s32 *)value;
        if (value > 0) {
            list = (s32 *)((s32)setup + ((value << 8) >> 8));
        }
        if (list == NULL) {
            return 0;
        }
        while ((idx = list[3]) >= 0) {
            if (idx >= count) {
                return 0;
            }
            ((s32 (*)(s32, s32, s32, s32, s32 **))rec_add)(aobjs, list[0], list[1], list[2], (s32 **)handles[idx]);
            list += 4;
        }
        arena_pop(0x60);
    }

    value = stage_data_count();
    if (value >= 2) {
        refs = (s32 *)stage_ref((s32)setup, setup[0x88 / 4]);
        if (refs != NULL) {
            clamp_table_set((s32)refs);
        }
    }
    value = stage_data_count();
    if (value > 0) {
        refs = (s32 *)stage_ref((s32)setup, setup[0x7C / 4]);
        if (refs != NULL) {
            colour_table_set((s32)refs);
        }
        range = (SetupColourRange *)stage_ref((s32)setup, setup[0x78 / 4]);
        if (range != NULL) {
            while (range->first >= 0) {
                aobj_fill_value(range->first + aobjs, range->last - range->first + 1, range->value);
                range++;
            }
        }
        refs = (s32 *)stage_ref((s32)setup, setup[0x80 / 4]);
        if (refs != NULL) {
            slope_table_set((s32)refs);
        }
    }

    refs = (s32 *)stage_ref((s32)setup, setup[0x50 / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            interp_alloc_record(stage_ref((s32)setup, item));
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x54 / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            interp1c_add(stage_ref((s32)setup, item), slot);
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x58 / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            interp2c_add((void *)stage_ref((s32)setup, item), slot);
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x60 / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            interp38_add_script((s16 *)stage_ref((s32)setup, item));
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x5C / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            interp38b_add((u8 *)stage_ref((s32)setup, item));
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x68 / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            part_slots_append(stage_ref((s32)setup, item));
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x64 / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            stage_queue_push(stage_ref((s32)setup, item));
        }
    }
    refs = (s32 *)stage_ref((s32)setup, setup[0x6C / 4]);
    if (refs != NULL) {
        while (*refs != 0) {
            item = *refs++;
            str_queue_push(stage_ref((s32)setup, item));
        }
    }

    for (i = 0; i < stage_record_count(); i++) {
        rec = (SetupLightRecord *)get_stage_record(i);
        rec_set_point(i, rec->point[0], rec->point[1], 0x1000);
        for (j = 0; j < 3; j++) {
            rec_set_colour(i, j, rec->colour[j][0], rec->colour[j][1], rec->colour[j][2]);
        }
        rec_set_vec(i, rec->vec[0], rec->vec[1], rec->vec[2]);
        rec_set_tex_flag(i, rec->tex_flag);
        rec_set_on(i, rec->on);
        rec_set_flag(i, rec->flag);
        for (j = 0; j < 3; j++) {
            light_set_dir_from_angles(i, j, rec->dir_angles[j][0], rec->dir_angles[j][1]);
        }
        for (j = 0; j < 7; j++) {
            rec_set_part(i, j, rec->part[j][0], rec->part[j][1], rec->part[j][2]);
        }
    }

    if (setup[0x10 / 4]) {
        count = (s32)arena_alloc(0x200);
        if (handle_load((u8 *)stage_ref((s32)setup, setup[0x10 / 4]), count) < 0) {
            return 0;
        }
        clut_set_stp(0x100, (u16 *)count);
        aobjs = record_key_get((u8 *)stage_ref((s32)setup, setup[0x18 / 4]));
        if (aobjs < 0) {
            return 0;
        }
        refs = arena_alloc(aobjs);
        if (handle_load((u8 *)stage_ref((s32)setup, setup[0x18 / 4]), (s32)refs) < 0) {
            return 0;
        }
        j = record_key_get((u8 *)stage_ref((s32)setup, setup[0x14 / 4]));
        if (j < 0) {
            return 0;
        }
        out = arena_alloc(j);
        if (handle_load((u8 *)stage_ref((s32)setup, setup[0x14 / 4]), (s32)out) < 0) {
            return 0;
        }
        texture_page_decode((s16 *)refs, (s16 *)count, (u8 *)out, j);
        arena_pop(j);
        arena_pop(aobjs);
        arena_pop(0x200);
    }

    part_offset_set(pspr_top);
    walk = get_stage_file_list();
    if (walk != NULL) {
        refs = walk;
        while ((entry = (s32 *)stage_entry((s32)refs, *walk++)) != NULL) {
            u8 *files[3];

            files[0] = (u8 *)stage_ref((s32)refs, entry[0]);
            files[1] = (u8 *)stage_ref((s32)refs, entry[1]);
            files[2] = (u8 *)stage_ref((s32)refs, entry[2]);
            if (stage_files_load(files, NULL) == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void stage_setup_pair_load(s32 index) {
    StageSetupBlock *data = get_stage_setup_block();

    if (stage_data_count() >= 2) {
        stage_pair_set_vectors(&data->pairs[index].a, &data->pairs[index].b);
    }
}
