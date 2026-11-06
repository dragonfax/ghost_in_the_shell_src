/* world_query: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void aobj_trim_count(void) {
    s32 count = aobj_entry_count;
    AobjEntry *rec = &aobj_table[count - 1];
    s32 i;

    for (i = count - 1; i >= 0 && rec->unk_04[2] == 0; i--, rec--) {
    }
    aobj_entry_count = i + 1;
}

/* Marks the quads whose edges all run along x or y. */
void model_mark_squares(Model *model) {
    s32 j;
    FaceList *list = model->list;
    Face *face = list->faces;
    FaceTail *tail;
    s32 count = list->count;
    Vert *verts;
    Vert *prev;
    Vert *cur;

    poly_count += count;
    verts = (Vert *)(model->vertices - 4);
    if (count > 0) {
        do {
            tail = (FaceTail *)&face->flags;
            if (tail->last != 0) {
                prev = &verts[tail->last];
                for (j = 0; j < 4; j++) {
                    cur = &verts[*((u8 *)face + 8 + j)];
                    if (prev->y != cur->y && prev->x != cur->x) {
                        break;
                    }
                    prev = cur;
                }
                if (j == 4) {
                    tail->flags |= 0x100;
                    square_count += 1;
                }
            }
            count--;
            face++;
        } while (count > 0);
    }
}

void aobj_build_face_boxes(AobjEntry *rec) {
    BoxedMesh *mesh;
    QuadFaceList *list;
    Vertex *verts;
    QuadFace *face;
    FaceBox *out;
    s32 count;
    s32 min_x, max_x, min_y, max_y, min_z, max_z;

    mesh = (BoxedMesh *)rec;
    list = mesh->faces;
    count = list->count;
    verts = (Vertex *)((u8 *)mesh->verts - 4);
    out = (FaceBox *)heap_bump_alloc(count * 12);
    mesh->boxes = out;
    if (count > 0) {
        face = list->faces;
        do {
            max_x = verts[face->vtx[0]].x;
            min_x = max_x;
            max_y = verts[face->vtx[0]].y;
            min_y = max_y;
            max_z = verts[face->vtx[0]].z;
            min_z = max_z;

            if (verts[face->vtx[1]].x < max_x) {
                min_x = verts[face->vtx[1]].x;
            } else if (max_x < verts[face->vtx[1]].x) {
                max_x = verts[face->vtx[1]].x;
            }
            if (verts[face->vtx[1]].y < min_y) {
                min_y = verts[face->vtx[1]].y;
            } else if (max_y < verts[face->vtx[1]].y) {
                max_y = verts[face->vtx[1]].y;
            }
            if (verts[face->vtx[1]].z < min_z) {
                min_z = verts[face->vtx[1]].z;
            } else if (max_z < verts[face->vtx[1]].z) {
                max_z = verts[face->vtx[1]].z;
            }

            if (verts[face->vtx[2]].x < min_x) {
                min_x = verts[face->vtx[2]].x;
            } else if (max_x < verts[face->vtx[2]].x) {
                max_x = verts[face->vtx[2]].x;
            }
            if (verts[face->vtx[2]].y < min_y) {
                min_y = verts[face->vtx[2]].y;
            } else if (max_y < verts[face->vtx[2]].y) {
                max_y = verts[face->vtx[2]].y;
            }
            if (verts[face->vtx[2]].z < min_z) {
                min_z = verts[face->vtx[2]].z;
            } else if (max_z < verts[face->vtx[2]].z) {
                max_z = verts[face->vtx[2]].z;
            }

            if (face->vtx[3] != 0) {
                if (verts[face->vtx[3]].x < min_x) {
                    min_x = verts[face->vtx[3]].x;
                } else if (max_x < verts[face->vtx[3]].x) {
                    max_x = verts[face->vtx[3]].x;
                }
                if (verts[face->vtx[3]].y < min_y) {
                    min_y = verts[face->vtx[3]].y;
                } else if (max_y < verts[face->vtx[3]].y) {
                    max_y = verts[face->vtx[3]].y;
                }
                if (verts[face->vtx[3]].z < min_z) {
                    min_z = verts[face->vtx[3]].z;
                } else if (max_z < verts[face->vtx[3]].z) {
                    max_z = verts[face->vtx[3]].z;
                }
            }

            count--;
            face++;
            out->min_x = min_x;
            out->max_x = max_x;
            out->min_y = min_y;
            out->max_y = max_y;
            out->min_z = min_z;
            out->max_z = max_z;
            out++;
        } while (count > 0);
    }
}

/* Shell sort of keys[0..count) by key, ascending (gaps 1, 4, 13, ...). */
void aobj_sort_keys(s32 count, SortKey *keys)
{
    s32 gap;
    s32 h;
    s32 next;
    s32 i;
    s32 j;
    s32 index, key;
    SortKey *p;

    for (gap = 1; gap <= count / 9; gap = gap * 3 + 1)
        ;
    for (h = gap; h > 0; h = next) {
        next = div3_pos(h);
        for (i = h; i < count; i++) {
            p = &keys[i];
            index = p->index;
            key = p->key;
            for (j = i - h; j >= 0 && key < keys[j].key; j -= h)
                keys[j + h] = keys[j];
            keys[j + h].index = index;
            keys[j + h].key = key;
        }
    }
}

/* Sorts the entries of a job (count and 12-byte entries at *(obj+8), parallel 12-byte entries at *(obj+0x10)):
 * builds (index, key) pairs on the scratchpad, pairs both entry arrays into 0x18-byte temporaries, sorts the
 * keys (aobj_sort_keys) and writes the entries back in the new order. */
void aobj_sort_entries(u8 *obj) {
    SortKey *keys;
    s32 *head = *(s32 **)(obj + 8);
    Bytes12 *second = *(Bytes12 **)(obj + 0x10);
    s32 count = head[0];
    Bytes12 *first = (Bytes12 *)(head + 1);
    Bytes12 (*temp)[2];
    s32 idx;
    s32 i;

    keys = scratch_alloc(0x200);
    temp = arena_top();
    for (i = 0; i < count; i++) {
        keys[i].index = i;
        keys[i].key = *(u16 *)((u8 *)&second[i] + 4);
        temp[i][0] = first[i];
        temp[i][1] = second[i];
    }
    aobj_sort_keys(count, keys);
    for (i = 0; i < count; i++) {
        idx = keys[i].index;
        first[i] = temp[idx][0];
        second[i] = temp[idx][1];
    }
    scratch_top -= 0x200;
}

s32 aobj_link_char(u8 *data) {
    AobjEntry *rec;
    s32 count;
    s32 n;
    s32 i;
    u8 *p;
    s32 unused[2];

    p = data + 4;
    FAKE_OPAQUE(p);
    count = *(s32 *)(p - 4);
    if (aobj_entry_count + count >= 0x201) {
        printf("AObj Link Char Over!\r");
        return 0;
    }
    rec = &aobj_table[aobj_entry_count];
    i = 0;
    if (count > 0) {
        do {
            p += 4;
            n = *(s32 *)(p - 4);
            if (n != 0) {
                rec->unk_04[0] = (s32)(p - 4);
                p += n * 8;
                if (max_apex_count < n) {
                    max_apex_count = n;
                }
                rec->unk_04[1] = (s32)p;
                p += 4;
                n = *(s32 *)(p - 4);
                p += n * 12;
                if (max_poly_count < n) {
                    max_poly_count = n;
                }
                rec->unk_04[2] = (s32)p;
                p += 12;
                aobj_build_face_boxes(rec);
                aobj_sort_entries((u8 *)rec);
                model_mark_squares((Model *)rec);
            }
            i++;
            rec++;
        } while (i < count);
    }
    aobj_entry_count += count;
    return aobj_entry_count - count;
}

s32 rec_add(s16 id, s32 a, s32 b, s32 c, s32 **counter) {
    s32 n;
    s32 pos;
    s32 *inner;
    s32 inc;
    s32 *words;

    if (counter != 0) {
        n = rec_count;
        if (n < 0x18) {
            pos = rec_pos_total;
            words = &rec_table[n].unk_00[1];
            rec_table[n].unk_00[0] = (s32)counter;
            words[0] = a;
            words[1] = b;
            words[2] = c;
            rec_table[n].id = id;
            rec_table[n].pos = pos;
            inner = *counter;
            rec_count = n + 1;
            inc = *inner;
            rec_table[n].value = 1;
            rec_pos_total = pos + inc;
            return n;
        }
    }
}

void aobj_set_flag(s32 index, s32 flag) {
    if (index >= 0 && aobj_entry_count - 1 >= index) {
        aobj_table[index].flag = flag;
    }
}

s16 aobj_get_flag(s32 index) {
    if (index >= 0 && aobj_entry_count - 1 >= index) {
        return aobj_table[index].flag;
    }
    return 0;
}

/* Sets entry `index`'s value if index is within the rec_count entries. */
void rec_set_value(s32 index, s32 value) {
    if (index >= 0 && index <= rec_count - 1) {
        rec_table[index].value = value;
    }
}

s32 rec_get_value(s32 index) {
    if (index >= 0 && rec_count - 1 >= index) {
        return rec_table[index].value;
    }
    return 0;
}

/* Links one node per bucket first..last of src into the buckets' lists
   (the first bucket's head list, the others' tail lists), counting them.
   Returns the next free node. */
void *bucket_link_nodes(ListNode8 *nodes, s32 key, BucketSrc *src, Bucket14 *bucket)
{
    register ListNode8 *out asm("$8") = nodes;
    s32 i = src->first;
    s32 side_off = (src->key == key) * 8;
    s32 last = src->last;

    bucket += i;
    out->value = src->value;
    out->next = ((ListNode8 **)((u8 *)bucket + side_off))[2];
    i++;
    ((ListNode8 **)((u8 *)bucket + side_off))[2] = out;
    goto next;
    do {
        out->value = src->value;
        out->next = *(ListNode8 **)((u8 *)bucket->slot + side_off);
        i++;
        *(ListNode8 **)((u8 *)bucket->slot + side_off) = out;
next:
        bucket->count++;
        out++;
        bucket++;
    } while (i <= last);
    return out;
}

/* Shell sort of order[0..count) by slot key: the s16 at +4 of the aobj_table[base + slot.rec_index] record's pointer, plus slot.key_off. */
void aobj_sort_slots(s32 count, s16 *order, s32 base, SortSlot *slots) {
    AobjEntry *rec_base;
    s32 start_gap;
    s32 gap;
    s32 i;
    s32 k;
    s32 cur;
    s32 other;
    s32 cur_key;
    s32 next;

    rec_base = &aobj_table[base];
    for (start_gap = 1; start_gap <= count / 9; start_gap = start_gap * 3 + 1)
        ;
    for (gap = start_gap; gap > 0; gap = next) {
        next = div3_pos(gap);
        for (i = gap; i < count; i++) {
            cur = order[i];
            cur_key = ((s16 *)rec_base[slots[cur].rec_index].unk_04[2])[2] + slots[cur].key_off;
            for (k = i - gap; k >= 0; k -= gap) {
                other = order[k];
                if (cur_key >= ((s16 *)rec_base[slots[other].rec_index].unk_04[2])[2] + slots[other].key_off) {
                    break;
                }
                order[k + gap] = other;
            }
            order[k + gap] = cur;
        }
    }
}

s16 *atr_map_make_index(s32 key, s16 *out, s32 count, BucketSrc *src, s32 base, SortSlot *slots)
{
    s32 hi;
    s32 start;
    Bucket14 *cells;
    Bucket14 *cell;
    ListNode8 *nodes;
    s32 i;
    s32 k;
    s32 byte_off;
    s32 rec;
    s32 lo;
    s32 n;
    s16 *list;
    u32 offset;
    s16 *slot;
    s16 *data;
    ListNode8 *node;

    start = 0;
    cells = arena_top();
    nodes = (ListNode8 *)(cells + 128);
    cell = cells;
    for (byte_off = 0; byte_off < 128 * (s32)sizeof(Bucket14); byte_off += sizeof(Bucket14)) {
        cell->count = 0;
        for (k = 3; k >= 0; k--) {
            ((ListNode8 **)cell->slot)[k] = 0;
        }
        cell++;
    }
    hi = start;
    lo = 0x80;
    for (i = hi, rec = 0; i < count; i++, rec++) {
        if (key < src[rec].key) {
            break;
        }
        if (src[rec].key_max >= key) {
            if (src[rec].first < lo) {
                lo = src[rec].first;
            }
            if (hi < src[rec].last) {
                hi = src[rec].last;
            }
            nodes = bucket_link_nodes(nodes, key, &src[rec], cells);
        }
    }
    cells += lo;
    out[0] = lo;
    out[1] = hi;
    data = out + ((hi - lo) + 3);
    for (slot = out + 2; lo <= hi; lo++, cells++, slot++) {
        *slot = 0;
        if (cells->count != 0) {
            offset = ((u32)data - (u32)slot) >> 1;
            if ((s32)offset > 0xFFFF) {
                printf("AtrMapMakeIndex: OverFlow -> %d\r", offset);
                offset = 0;
            }
            *slot = offset;
            n = 0;
            for (i = 0; i < 4; i++) {
                count = n;
                list = &data[4 + n];
                node = ((ListNode8 **)cells->slot)[i];
                while (node != NULL) {
                    do {
                        data[4 + n++] = node->value;
                    } while (0);
                    node = node->next;
                }
                count = n - count;
                data[i] = n;
                if (max_unit_count < count) {
                    max_unit_count = count;
                }
                aobj_sort_slots(count, list, base, slots);
            }
            data += n + 4;
        }
    }
    return data;
}

static inline AobjBounds *aobj_bounds(AobjEntry *obj)
{
    return (AobjBounds *)obj->unk_04[2];
}
static inline s32 atr_cell(s32 v)
{
    return (v + 0x8000) >> 9;
}
static inline void atr_cell_copy(AtrCellWords *src, AtrCellWords *dst)
{
    s32 w0 = src->words[0];
    s32 w1 = src->words[1];

    dst->words[0] = w0;
    dst->words[1] = w1;
}
static inline s32 atr_cell_before(BucketSrc *key, BucketSrc *cell)
{
    s32 a = key->key;
    s32 b = cell->key;

    if (b < a) return 1;
    if (a < b) return 0;
    a = key->key_max;
    b = cell->key_max;
    return !(a < b);
}
/* Builds the attribute map of `src` on the heap: the bounding box of every
   placed aobj, its z cells sorted (shell sort), then one index row per z cell. */
void *atr_map_build(AtrSrc *src, s32 base)
{
    SortSlot *entry;
    SortSlot *pos;
    AtrMap *map;
    AtrCellWords *cells;
    AtrCellWords *tmp;
    AobjEntry *obj;
    s16 *row;
    s16 *data;
    s32 total;
    s32 run;
    s32 count;
    s32 i;
    s32 j;
    s32 k;
    s32 hole;
    s32 v;
    s32 m;
    s32 step;
    s32 gap;
    s32 next;
    s32 z;
    s32 z_hi;
    s32 offset;

    if (src == NULL) {
        return 0;
    }
    total = src->count;
    pos = src->entries;
    map = (AtrMap *)heap_get_top();
    map->min_z = 0x7FFF;
    map->min_y = 0x7FFF;
    map->min_x = 0x7FFF;
    map->src = src;
    map->max_z = -0x8000;
    map->max_y = -0x8000;
    map->max_x = -0x8000;
    cells = arena_top();
    entry = src->entries;
    i = 0;
    count = 0;
    for (; i < total; i++, entry++, pos++) {
        if (entry->rec_index == 0) {
            continue;
        }
        obj = &aobj_table[entry->rec_index + base];
        if (aobj_bounds(obj) == NULL) {
            continue;
        }
        v = pos->x + aobj_bounds(obj)->min_x;
        cells[count].cell.first = atr_cell(v);
        m = map->min_x;
        if (v < m) {
            m = v;
        }
        map->min_x = m;
        v = pos->x + aobj_bounds(obj)->max_x;
        cells[count].cell.last = atr_cell(v);
        m = map->max_x;
        if (m < v) {
            m = v;
        }
        map->max_x = m;
        v = entry->z + aobj_bounds(obj)->min_z;
        cells[count].cell.key = atr_cell(v);
        m = map->min_z;
        if (v < m) {
            m = v;
        }
        map->min_z = m;
        v = entry->z + aobj_bounds(obj)->max_z;
        cells[count].cell.key_max = atr_cell(v);
        m = map->max_z;
        if (m < v) {
            m = v;
        }
        map->max_z = m;
        v = entry->key_off + aobj_bounds(obj)->min_y;
        m = map->min_y;
        if (v < m) {
            m = v;
        }
        map->min_y = m;
        v = entry->key_off + aobj_bounds(obj)->max_y;
        m = map->max_y;
        if (m < v) {
            m = v;
        }
        map->max_y = m;
        cells[count].cell.value = i;
        count++;
    }
    printf("ACharTotal:%d\r", count);
    if (count == 0) {
        return 0;
    }
    arena_alloc(count * 8);
    tmp = scratch_alloc(8);
    for (step = 1; step <= count / 9; step = step * 3 + 1) {
    }
    for (gap = step; gap > 0; gap = next) {
        next = div3_pos(gap);
        for (hole = gap; hole < count; hole++) {
            atr_cell_copy(&cells[hole], tmp);
            for (k = hole - gap; k >= 0; k -= gap) {
                if (atr_cell_before(&tmp->cell, &cells[k].cell)) {
                    break;
                }
                atr_cell_copy(&cells[k], &cells[k + gap]);
            }
            atr_cell_copy(tmp, &cells[k + gap]);
        }
    }
    scratch_top -= 8;
    z = atr_cell(map->min_z);
    z_hi = atr_cell(map->max_z);
    map->z_lo = z;
    map->z_hi = z_hi;
    printf("RangeZ:%d..%d\r", z, z_hi);
    /* after the call: sched1 hoists it above (row already crosses calls) */
    row = map->rows;
    data = &map->rows[z_hi - z + 1];
    i = 0;
    if (z <= z_hi) {
        for (; z <= z_hi; z++, row++) {
            while (cells[i].cell.key_max < z) {
                i++;
            }
            *row = 0;
            j = i;
            for (run = 0; j < count; j++) {
                if (z < cells[j].cell.key) {
                    break;
                }
                run++;
            }
            total = run;
            if (total != 0) {
                offset = (u32)((u8 *)data - (u8 *)row) >> 1;
                if (offset > 0xFFFF) {
                    printf("AtrMapMakeVram: OverFlow -> %d\r", offset);
                    offset = 0;
                }
                *row = offset;
                data = atr_map_make_index(z, data, total, &cells[i].cell, base, map->src->entries);
            }
        }
    }
    arena_pop(count * 8);
    printf("AVramSize:%d\r", (s32)data - heap_get_top());
    heap_set_top((s32)data);
    return map;
}

/* Appends to list the index of every face of obj whose surface bits (colour_table_ptr's row for the object) meet
 * q->kind and whose box, placed at (x, y, z), overlaps q's box; returns how many. The boxes (s16 min/max pairs
 * read as words: x, y, z) are sorted by y min, so the scan stops at the first box whose y min lies past q's
 * y max. */
static inline s32 aobj_collect_faces(CellQuery *q, AobjEntry *obj, s16 *list, s32 x, s32 y, s32 z)
{
    s32 hits = 0;
    s32 index = 0;
    s32 *boxes;
    s32 *faces;
    u8 *face;
    s32 count;
    s32 *attrs;
    s32 bound, max, qmax;
    s32 bits;

    boxes = (s32 *)obj->unk_04[3];
    faces = (s32 *)obj->unk_04[1];
    face = (u8 *)(faces + 1);
    count = *faces;
    attrs = (s32 *)colour_table_ptr + obj->value;
    for (; index < count; index++, boxes += 3, face += 12) {
        bound = boxes[1];
        max = bound >> 16;
        bound = (bound << 16) >> 16;
        qmax = q->y[1];
        if (qmax - y < bound)
            break;
        bits = attrs[face[6]];
        if (!(bits & q->kind))
            continue;
        if (max < q->y[0] - y)
            continue;
        bound = boxes[0];
        max = bound >> 16;
        if (max < q->x[0] - x)
            continue;
        bound = (bound << 16) >> 16;
        qmax = q->x[1];
        if (qmax - x < bound)
            continue;
        bound = boxes[2];
        max = bound >> 16;
        if (max < q->z[0] - z)
            continue;
        bound = (bound << 16) >> 16;
        qmax = q->z[1];
        if (qmax - z < bound)
            continue;
        hits++;
        *list++ = index;
    }
    return hits;
}
/* Scans the vertex lists of one map cell for objects whose bounds overlap q's box and appends, for each object
 * with matching faces, (vertex index, face count, face indices...) to out; returns the new end of out. The
 * cell holds four lists (cell[k] is the end of list k, counted from cell + 4); list k is scanned when
 * (k | edges) == 3, edges having bit 1 set in the query's first row and bit 0 in its first column. */
s16 *cell_list_query(s32 edges, CellQuery *q, s16 *cell, s16 *out)
{
    s16 *entry;
    s16 *end;
    s16 *list_end;
    s32 k;
    s32 id_base;

    entry = cell + 4;
    k = 0;
    list_end = cell;
    id_base = q->id;
    do {
        end = cell + 4 + *list_end;
        if ((k | edges) == 3) {
            while (entry != end) {
                s32 vertex;
                s32 offset;
                s32 *words;
                s32 x, y, z;
                AobjEntry *obj;
                s32 *bounds;
                s32 bound, max, qmax; /* bound: a min/max word, then its min half, then the hit count */

                vertex = *entry++;
                offset = vertex * 8 + 4;
                words = (s32 *)(q->word + offset);
                x = words[0];
                z = words[1];
                y = x >> 16;
                x = (x << 16) >> 16;
                if (z >> 16 <= 0)
                    continue;
                obj = &aobj_table[(z >> 16) + id_base];
                if (obj->flag == 0)
                    continue;
                z = (z << 16) >> 16;
                bounds = (s32 *)obj->unk_04[2];
                bound = bounds[1];
                max = bound >> 16;
                bound = (bound << 16) >> 16;
                qmax = q->y[1];
                if (qmax - y < bound)
                    break;
                if (max < q->y[0] - y)
                    continue;
                bound = bounds[0];
                max = bound >> 16;
                if (max < q->x[0] - x)
                    continue;
                bound = (bound << 16) >> 16;
                qmax = q->x[1];
                if (qmax - x < bound)
                    continue;
                bound = bounds[2];
                max = bound >> 16;
                if (max < q->z[0] - z)
                    continue;
                bound = (bound << 16) >> 16;
                qmax = q->z[1];
                if (qmax - z < bound)
                    continue;
                *out = vertex;
                bound = aobj_collect_faces(q, obj, out + 2, x, y, z);
                if (bound > 0) {
                    q->count++;
                    out[1] = bound;
                    out += bound + 2;
                }
            }
        }
        entry = end;
        k++;
        list_end++;
    } while (k < 4);
    return out;
}

s16 *cell_row_query(s32 edges, CellQuery *q, s16 *row, s16 *acc)
{
    s32 first = (q->x[0] + 0x8000) >> 9;
    s32 last = (q->x[1] + 0x8000) >> 9;
    u16 *p;
    u16 *end;
    s32 link;

    if (row[1] < first)
        return acc;
    if (last < row[0])
        return acc;
    if (first < row[0])
        first = row[0];
    if (row[1] < last)
        last = row[1];
    last -= first;
    first -= row[0];
    p = (u16 *)&row[first + 2];
    end = p + last + 1;
    link = *p;
    if (link)
        acc = cell_list_query(edges + 1, q, (s16 *)(p + link), acc);
    while (++p != end) {
        link = *p;
        if (link)
            acc = cell_list_query(edges, q, (s16 *)(p + link), acc);
    }
    return acc;
}

static inline s16 *cell_query_rows(CellQuery *q, s16 *row, s16 *acc)
{
    s32 first = (q->z[0] + 0x8000) >> 9;
    s32 last = (q->z[1] + 0x8000) >> 9;
    u16 *p;
    u16 *end;
    s32 link;

    if (row[1] < first)
        return acc;
    if (last < row[0])
        return acc;
    if (first < row[0])
        first = row[0];
    if (row[1] < last)
        last = row[1];
    last -= first;
    first -= row[0];
    p = (u16 *)&row[first + 2];
    end = p + last + 1;
    link = *p;
    if (link)
        acc = cell_row_query(2, q, (s16 *)(p + link), acc);
    while (++p != end) {
        link = *p;
        if (link)
            acc = cell_row_query(0, q, (s16 *)(p + link), acc);
    }
    return acc;
}
/* Clips the box vmin..vmax against every enabled rec_table cell grid and
   queries its rows; for each record with hits appends (index, hit count) and
   the hits to out, terminated by -1. */
s32 rec_table_query_box(s32 kind, s32 *vmin, s32 *vmax, s16 *out)
{
    CellQuery *q;
    s16 *hdr;
    s32 i;
    s32 total;
    s32 uninit; /* never set in the original: total adds stack garbage */
    s32 off_x, off_y, off_z;
    s16 *start;
    s16 *saved;

    out[0] = -1;
    if (rec_count <= 0)
        return 0;
    q = scratch_alloc(sizeof(CellQuery));
    q->kind = kind & 0xF;
    total = 0;
    for (i = 0; i < rec_count; i++) {
        if (rec_table[i].value == 0)
            continue;
        hdr = (s16 *)rec_table[i].unk_00[0];
        if (hdr == 0)
            continue;
        off_x = rec_table[i].unk_00[1];
        off_y = rec_table[i].unk_00[2];
        off_z = rec_table[i].unk_00[3];
        if (hdr[5] < vmin[1] - off_y)
            continue;
        if (vmax[1] - off_y < hdr[4])
            continue;
        if (hdr[3] < vmin[0] - off_x)
            continue;
        if (vmax[0] - off_x < hdr[2])
            continue;
        if (hdr[7] < vmin[2] - off_z)
            continue;
        if (vmax[2] - off_z < hdr[6])
            continue;
        q->id = rec_table[i].id;
        q->word = *(s32 *)hdr;
        q->x[0] = vmin[0] - off_x;
        q->x[1] = vmax[0] - off_x;
        q->y[0] = vmin[1] - off_y;
        q->y[1] = vmax[1] - off_y;
        q->z[0] = vmin[2] - off_z;
        q->z[1] = vmax[2] - off_z;
        q->count = 0;
        saved = out;
        out += 2;
        start = out;
        out = cell_query_rows(q, hdr + 8, out);
        if (start == out) {
            out = saved;
            continue;
        }
        saved[0] = i;
        total += uninit;
        saved[1] = q->count;
    }
    out[0] = -1;
    scratch_top -= sizeof(CellQuery);
    return total;
}

s32 surface_of(s32 code) {
    s32 region;
    s32 kind;
    s32 i;
    s32 index;
    AobjEntry *obj;
    SurfaceSpan *span;
    SurfaceKind *entry;
    register s32 surface asm("$2");

    region = code >> 8;
    kind = code & 0xFF;
    if (region == 0) {
        return 0;
    }
    if (region < 0x100) {
        return 0x1F;
    }
    if (region == 0x100) {
        index = 0;
    } else {
        region -= 0x101;
        for (i = 0; i < rec_count; i++) {
            if (region < rec_table[i].pos) {
                break;
            }
        }
        i--;
        region -= rec_table[i].pos;
        span = *(SurfaceSpan **)rec_table[i].unk_00[0] + region;
        index = rec_table[i].id + span[1].unk_02;
    }
    obj = &aobj_table[index];
    entry = (SurfaceKind *)obj->unk_04[1] + kind;
    surface = entry->surface;
    return *(s32 *)((surface << 2) + ((obj->value << 2) + colour_table_ptr));
}

s32 ground_slope_lookup(s32 key, s32 *out) {
    s32 slot = key >> 8;
    s32 frame_no = key & 0xFF;
    s32 aobj;
    s32 i;
    ModelGroup *group;
    ModelPosEntry *entry;
    AobjEntry *ae;
    s32 offset;
    u8 *frame;
    s32 index;
    s32 base;
    s32 *values;

    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    if (slot == 0) {
        return 0;
    }
    if (slot < 0x100) {
        return 0x1F;
    }
    if (slot == 0x100) {
        aobj = 0;
    } else {
        slot -= 0x101;
        for (i = 0; i < rec_count; i++) {
            if (slot < rec_table[i].pos) {
                break;
            }
        }
        group = &rec_table[i - 1];
        slot -= group->pos;
        entry = &(*(ModelPosTable **)group->unk_00[0])->entries[slot];
        aobj = group->id + entry->aobj;
        out[0] = group->unk_00[1] + entry->x;
        out[1] = group->unk_00[2] + entry->y;
        out[2] = group->unk_00[3] + entry->z;
    }
    out[3] = aobj;
    ae = &aobj_table[aobj];
    offset = frame_no * 12;
    frame = (u8 *)ae->unk_04[1] + offset;
    index = frame[10];
    base = ae->value;
    values = (s32 *)colour_table_ptr;
    /* keeps the byte in v0 and orders the loads as the original */
    __asm__("" : "=r"(index) : "0"(index), "r"(base), "r"(values));
    return (values + base)[index];
}

/* Finds the record whose id range holds (packed >> 8) - 0x101 and returns the
   address of word 1 of that id's 8-byte entry in the record's table. */
s32 rec_table_word_addr(s32 packed) {
    s32 id;
    s32 i;
    s32 ret = 0;

    id = (packed >> 8) - 0x101;
    if (id >= 0) {
        i = 0;
        while (i < rec_count && rec_table[i].pos <= id) {
            i++;
        }
        id -= rec_table[i - 1].pos;
        ret = (s32)&((s32 *)*(s32 *)rec_table[i - 1].unk_00[0])[id * 2 + 1];
    }
    return ret;
}

s32 rec_lookup_code(s32 code) {
    s32 result = -1;
    s32 n = code >> 8;
    s32 i;
    s32 rec;

    if (n == 0x100) {
        return 0;
    }
    n -= 0x101;
    if (n >= 0) {
        for (i = 0; i < rec_count; i++) {
            if (n < rec_table[i].pos) {
                break;
            }
        }
        rec = i - 1;
        n -= rec_table[rec].pos;
        result = *(s16 *)(*(u8 **)rec_table[rec].unk_00[0] + n * 8 + 0xA);
        result += rec_table[rec].id;
    }
    return result;
}

/* Returns max.x of clamp box index, or 0 when index is out of range (see clamp_set_max_x). */
s32 clamp_get_max_x(s32 index) {
    u8 *table;

    if (index < 0) {
        return 0;
    }
    table = (u8 *)clamp_table_ptr;
    if (index > *(s32 *)table - 1) {
        return 0;
    }
    return ((ClampEntry *)(table + (index << 5)))->max.x;
}

/* Index of the first enabled clamp box that contains the point (x, y, z), or -1. The table at
 * clamp_table_ptr starts with its box count; the boxes follow at +4 (ClampEntry, 0x20 bytes each). */
s32 clamp_find_box(s32 x, s32 y, s32 z) {
    u8 *table = (u8 *)clamp_table_ptr;
    s32 count = *(s32 *)table;
    ClampEntry *box = (ClampEntry *)(table + 4);
    s32 i;

    for (i = 0; i < count; i++, box++) {
        if (box->enabled == 0 || x < box->min.x || box->max.x < x || y < box->min.y || box->max.y < y ||
            z < box->min.z || box->max.z < z) {
            continue;
        }
        return i;
    }
    return -1;
}

/* Clamp a point into the box; returns the bits of the sides it was moved to (0x10000 | side). */
s32 clamp_point_to_box(s32 index, Vec3 *p) {
    ClampBox *box;
    s32 flags = 0;
    s32 x, y, z;
    s32 lo, hi;
    s32 offset;

    if (index < 0) {
        return 0;
    }
    offset = (index << 5) + 4;
    box = (ClampBox *)(clamp_table_ptr + offset);
    if (box->enabled == 0) {
        return 0;
    }
    x = p->x;
    y = p->y;
    z = p->z;
    lo = box->min.x;
    hi = box->max.x;
    if (x < lo) {
        x = lo;
        flags = 0x10020;
    } else if (hi < x) {
        x = hi;
        flags = 0x10010;
    }
    lo = box->min.y;
    hi = box->max.y;
    if (y < lo) {
        y = lo;
        flags |= 0x10002;
    } else if (hi < y) {
        y = hi;
        flags |= 0x10001;
    }
    lo = box->min.z;
    hi = box->max.z;
    if (z < lo) {
        z = lo;
        flags |= 0x10008;
    } else if (hi < z) {
        z = hi;
        flags |= 0x10004;
    }
    p->x = x;
    p->y = y;
    p->z = z;
    return flags;
}

/* Clips the closed polygon in[0..n-1] to lo <= x <= hi and writes it to out with x and z
 * swapped, so a second call clips z (trace_world_sweep, zone_add_model_faces). in needs room for one
 * more vertex: the first one is copied after the last. Returns the output vertex count. */
u32 clip_poly_slab(s32 lo_arg, s32 hi, s32 n, ClipVertex *in, ClipVertex *out) {
    register s32 lo asm("$4") = lo_arg;
    ClipVertex *end;
    ClipVertex *dst;
    s32 next_x;   /* in[1].x */
    s32 cur, aux; /* work values shared by every crossing */

    dst = out;
    end = in + n;
    CLIP_VERTEX_COPY(end, in);
    if (in->x >= lo) {
        goto test_above;
    }
below: /* in[0] below lo: skip to the edge that comes back */
    do {
        next_x = in[1].x;
        if (next_x >= lo) {
            goto enter_lo;
        }
        in++;
    } while (in != end);
    goto done;

enter_lo:
    CLIP_X_ENTER(dst, in, next_x, cur, aux, lo);
    dst++;
    goto check_hi;

test_above:
    if (hi >= in->x) {
        goto inside;
    }
above: /* in[0] above hi */
    do {
        next_x = in[1].x;
        if (hi >= next_x) {
            goto enter_hi;
        }
        in++;
    } while (in != end);
    goto done;

enter_hi: {
    ClipVertex *next = in + 1;

    CLIP_X_ENTER(dst, in, next_x, cur, aux, hi);
    dst++;
    next_x = in[1].x;
    if (next_x >= lo) {
        goto advance;
    }
    CLIP_X_EXIT(dst, in, next_x, cur, aux, lo); /* the edge crosses the whole slab */
    dst++;
    in = next;
    if (in != end) {
        goto below;
    }
    goto done;
}

inside: /* in[0] inside: keep it */
    dst->x = in->z;
    dst->y = in->y;
    dst->z = in->x;
    dst++;
    next_x = in[1].x;
    if (next_x >= lo) {
        goto test_hi;
    }
    {
        ClipVertex *next = in + 1;

        CLIP_X_EXIT(dst, in, next_x, cur, aux, lo);
        dst++;
        in = next;
    }
    if (in != end) {
        goto below;
    }
    goto done;

check_hi:
    next_x = in[1].x;
test_hi:
    if (hi >= next_x) {
        goto advance;
    }
    {
        ClipVertex *next = in + 1;

        CLIP_X_EXIT(dst, in, next_x, cur, aux, hi);
        dst++;
        in = next;
    }
    if (in != end) {
        goto above;
    }
    goto done;

advance:
    in++;
    if (in != end) {
        goto inside;
    }
done:
    return ((u32)dst - (u32)out) / sizeof(ClipVertex);
}

void xform_points_local(s32 *origin, s32 count, s16 *in, s16 *out) {
    s32 tx, ty, tz;
    s16 *end = in + count * 4;
    s32 x, y, z, m;

    gte_get_ctrl(TRX, tx);
    gte_get_ctrl(TRY, ty);
    gte_get_ctrl(TRZ, tz);
    x = *(s32 *)in;
    tx -= origin[0];
    ty -= origin[1];
    tz -= origin[2];
    z = in[2] - tz;
    y = (x >> 16) - ty;
    x -= tx;
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    in += 4;
    gte_nop();
    gte_rtir_b();
    while (in != end) {
        x = *(s32 *)in;
        z = in[2] - tz;
        in += 4;
        y = (x >> 16) - ty;
        x -= tx;
        gte_store(MAC1, out, 0);
        gte_get(MAC2, m);
        gte_store(MAC3, out, 4);
        gte_set(IR1, x);
        gte_set(IR2, y);
        gte_set(IR3, z);
        out[1] = m;
        gte_nop();
        gte_rtir_b();
        out += 4;
    }
    gte_store(MAC1, out, 0);
    gte_get(MAC2, m);
    gte_store(MAC3, out, 4);
    out[1] = m;
}

s32 clip_verts_test_box(s32 count, ClipVertex *verts, ClipBox *box) {
    ClipVertex *v;
    ClipVertex *end;
    s32 result;
    s32 flags;
    s16 minX, maxX, minY, maxY, minZ, maxZ;

    minX = box->minX;
    maxX = box->maxX;
    minY = box->minY;
    maxY = box->maxY;
    minZ = box->minZ;
    maxZ = box->maxZ;

    result = 0x3F;
    v = verts;
    end = verts + count;
    do {
        s32 x = v->x;
        s32 y = v->y;
        s32 z = v->z;

        flags = (x < minX) * 8;
        if (maxX < x) {
            flags |= 4;
        }
        if (y < minY) {
            flags |= 2;
        }
        flags |= (maxY < y);
        if (z < minZ) {
            flags |= 0x20;
        }
        if (maxZ < z) {
            flags |= 0x10;
        }
        v->flags = flags;
        result &= flags;
        v++;
    } while (v != end);
    return result;
}

s32 world_query_segment(s32 a0, s32 margin, s32 *p, s32 *q, s32 arg5) {
    Aabb *box = (Aabb *)scratch_top;
    s32 *hi;
    s32 x0 = p[0], y0 = p[1], z0 = p[2];
    s32 x1 = q[0], y1 = q[1], z1 = q[2];
    s32 t;
    scratch_top += 0x20;
    hi = box->hi;
    if (x1 < x0) { t = x0; x0 = x1; x1 = t; }
    if (y1 < y0) { t = y0; y0 = y1; y1 = t; }
    if (z1 < z0) { t = z0; z0 = z1; z1 = t; }
    box->lo[0] = x0 - margin;
    box->lo[1] = y0 - margin;
    box->lo[2] = z0 - margin;
    box->hi[0] = x1 + margin;
    box->hi[1] = y1 + margin;
    box->hi[2] = z1 + margin;
    rec_table_query_box(a0, box->lo, hi, (s16 *)arg5);
    scratch_top -= 0x20;
}

void rot_look_at(s32 *from, s32 *to) {
    s32 yaw;
    s32 pitch;
    volatile s32 *m;
    s32 a, b, c;
    s32 x = from[0];
    s32 y = from[1];
    s32 z = from[2];
    s32 tx = to[0];
    s32 ty = to[1];
    s32 tz = to[2];

    gte_set_ctrl(TRX, x);
    gte_set_ctrl(TRY, y);
    gte_set_ctrl(TRZ, z);
    vector_to_angles(tx - x, ty - y, tz - z, &yaw, &pitch);
    m = (s32 *)scratch_top;
    scratch_top += 0x20;
    rot_matrix_b((void *)m, -yaw, pitch - 0x400, 0);
    a = m[0];
    b = m[1];
    c = m[2];
    gte_set_ctrl(R11R12, a);
    gte_set_ctrl(R13R21, b);
    gte_set_ctrl(R22R23, c);
    a = m[3];
    b = m[4];
    gte_set_ctrl(R31R32, a);
    gte_set_ctrl(R33, b);
    scratch_top -= 0x20;
}

/* out = RotMatrix^T * (0, max(a - b, 0), 0) + translation */
void rot_inverse_offset(s32 *out, s32 a, s32 b) {
    s32 *m = (s32 *)scratch_alloc(0x40);
    register s32 r3 asm("$3");
    register s32 r4 asm("$4");
    register s32 r2 asm("$2");
    s32 tx, ty, tz, x, y, z, d;

    gte_get_ctrl(R11R12, r3);
    gte_get_ctrl(R13R21, r4);
    gte_get_ctrl(R22R23, r2);
    m[0] = r3;
    m[1] = r4;
    m[2] = r2;
    gte_get_ctrl(R31R32, r3);
    gte_get_ctrl(R33, r4);
    ((volatile s32 *)m)[3] = r3;
    ((volatile s32 *)m)[4] = r4;
    transpose_matrix(m, m);
    r3 = m[0];
    r4 = m[1];
    r2 = m[2];
    gte_set_ctrl(R11R12, r3);
    gte_set_ctrl(R13R21, r4);
    gte_set_ctrl(R22R23, r2);
    r3 = m[3];
    r4 = m[4];
    gte_set_ctrl(R31R32, r3);
    gte_set_ctrl(R33, r4);
    scratch_top -= 0x40;
    d = a - b;
    if (d < 0) {
        d = 0;
    }
    a = d;
    gte_set(IR1, 0);
    gte_set(IR2, a);
    gte_set(IR3, 0);
    gte_rtir();
    gte_get(MAC1, x);
    gte_get(MAC2, y);
    gte_get(MAC3, z);
    gte_get_ctrl(TRX, tx);
    gte_get_ctrl(TRY, ty);
    gte_get_ctrl(TRZ, tz);
    out[0] = x + tx;
    out[1] = y + ty;
    out[2] = z + tz;
}

/* Writes a six-entry box of s16 around the distance between two points: +-radius on each axis, and
   the distance plus radius on the third entry (sphere_sweep_bounds is the sphere's bounds). */
void sphere_sweep_bounds(VECTOR *from, VECTOR *to, s16 *box, s32 radius) {
    s32 dist;

    dist = isqrt(length_sq(to->vx - from->vx, to->vy - from->vy, to->vz - from->vz));
    box[0] = -radius;
    box[1] = radius;
    box[2] = 0;
    box[3] = dist + radius;
    box[4] = -radius;
    box[5] = radius;
}

/* Sweeps a sphere from q->from to q->to against the world's model faces
 * (and the stage floor); writes the stop point to q->hit, its w the hit id. */
s32 trace_world_sweep(TraceRequest *q) {
    s32 found;
    s32 result;
    s32 part_count;
    s32 rec_x, rec_y, rec_z;
    s32 part_index;
    s32 aobj_base, part_base;
    SweepPart *parts;
    s32 radius;
    SweepVec *from;
    SweepVec *to;
    SweepVec *out;
    s32 *faces;
    ClipVertex *vtx3;
    ClipBox *box;
    s32 kind;
    s32 *origin;
    s16 *list;
    s32 rec;
    s32 hit;
    s32 ret;

    box = scratch_alloc(0xC);
    kind = q->mode;
    radius = q->flags;
    from = q->from;
    origin = scratch_alloc(0x20);
    to = q->to;
    out = q->hit;

    if (world_query_segment(kind, radius, &from->x, &to->x, (s32)work_area_ptr->packet)) {
        rot_look_at(&from->x, &to->x);
        sphere_sweep_bounds((VECTOR *)from, (VECTOR *)to, (s16 *)box, radius);
        list = work_area_ptr->packet;
        found = 0;
        while ((rec = *list++) >= 0) {
            s32 *rec_pos;
            part_count = *list++;
            parts = (SweepPart *)(*(s32 *)rec_table[rec].unk_00[0] + 4);
            rec_pos = &rec_table[rec].unk_00[1];
            rec_x = rec_pos[0];
            rec_y = rec_pos[1];
            rec_z = rec_pos[2];
            aobj_base = rec_table[rec].id;
            part_base = rec_table[rec].pos;

            while (part_count > 0) {
                s16 *p;
                SweepPart *part;
                AobjEntry *ao;
                s32 n;
                s32 best;
                ClipVertex *work;
                ClipVertex *verts;
                s32 xy, z_aobj;
                s32 dy, aobj;

                part_index = *list++;
                part = &parts[part_index];
                xy = part->xy;
                z_aobj = part->z_aobj;
                dy = xy >> 16;
                xy = (s16)xy;
                aobj = z_aobj >> 16;
                z_aobj = (s16)z_aobj;
                origin[0] = rec_x + xy;
                origin[1] = rec_y + dy;
                origin[2] = rec_z + z_aobj;
                p = list;
                work = scratch_alloc(0x220);
                ao = &aobj_table[aobj + aobj_base];
                n = *(s32 *)ao->unk_04[0];
                best = box->maxY;
                if (n <= 48) {
                    verts = work + 20;
                } else {
                    verts = (ClipVertex *)work_area_ptr->packet + 0x200;
                }
                xform_points_local(origin, n, (s16 *)(ao->unk_04[0] + 4), (s16 *)verts);
                if (!clip_verts_test_box(n, verts, box)) {
                    n = *p++;
                    faces = (s32 *)(ao->unk_04[1] + 4);
                    while (n > 0) {
                        s32 face_index = *p++;
                        SweepFace *face;
                        s32 gte_val;
                        s32 idx3;
                        s32 mask;
                        s32 nverts;
                        s32 clipped;
                        ClipVertex *vtx0, *vtx1, *vtx2;
                        s16 mask3;
                        ClipVertex *base;

                        gte_get(VZ1, gte_val);
                        face = (SweepFace *)((u8 *)faces + face_index * 12);
                        if (gte_val != 0) {
                            /* skip faces turned away from the sweep */
                            gte_ldv0(face);
                            gte_rtv0();
                            gte_get_wait(MAC2, gte_val);
                            if (gte_val >= 0) {
                                goto next;
                            }
                        }
                        nverts = 3;
                        base = verts - 1;
                        vtx0 = base + face->idx[0];
                        vtx1 = base + face->idx[1];
                        vtx2 = base + face->idx[2];
                        mask3 = vtx0->flags & vtx1->flags & vtx2->flags;
                        mask = mask3;
                        idx3 = face->idx[3];
                        if (idx3 != 0) {
                            vtx3 = base + idx3;
                            nverts = 4;
                            mask &= vtx3->flags;
                        }
                        if (mask == 0) {
                            {
                                SweepWords *src = (SweepWords *)vtx0;
                                SweepWords *dst = (SweepWords *)&work[0];
                                s32 lo = src->lo;
                                s32 hi = src->hi;
                                dst->lo = lo;
                                dst->hi = hi;
                            }
                            {
                                SweepWords *src = (SweepWords *)vtx1;
                                SweepWords *dst = (SweepWords *)&work[1];
                                s32 lo = src->lo;
                                s32 hi = src->hi;
                                dst->lo = lo;
                                dst->hi = hi;
                            }
                            {
                                SweepWords *src = (SweepWords *)vtx2;
                                SweepWords *dst = (SweepWords *)&work[2];
                                s32 lo = src->lo;
                                s32 hi = src->hi;
                                dst->lo = lo;
                                dst->hi = hi;
                            }
                            if (idx3 != 0) {
                                {
                                    SweepWords *src = (SweepWords *)vtx3;
                                    SweepWords *dst = (SweepWords *)&work[3];
                                    s32 lo = src->lo;
                                    s32 hi = src->hi;
                                    dst->lo = lo;
                                    dst->hi = hi;
                                }
                            }
                            clipped = nverts;
                        } else {
                            clipped = 0;
                        }
                        if (clipped != 0) {
                            clipped = clip_poly_slab(box->minX, box->maxX, clipped, work, work + 10);
                            if (clipped != 0) {
                                clipped = clip_poly_slab(box->minZ, box->maxZ, clipped, work + 10, work);
                                if (clipped != 0) {
                                    ClipVertex *c = work;
                                    s32 min_y = box->minY;
                                    ClipVertex *end = work + clipped;
                                    s32 lowest = 0x7FFF;
                                    do {
                                        s32 y = c->y;
                                        if (y >= min_y && y < lowest) {
                                            lowest = y;
                                        }
                                        c++;
                                    } while (c != end);
                                    if (lowest < best) {
                                        best = lowest;
                                        origin[3] = face_index;
                                    }
                                }
                            }
                        }
                    next:
                        n--;
                    }
                }
                scratch_top -= 0x220;
                {
                    s32 skip = *list++;
                    list += skip;
                }
                if (best < box->maxY) {
                    found = 1;
                    box->maxY = best;
                    result = ((part_base + 0x101 + part_index) << 8) | (u8)origin[3];
                }
                part_count--;
            }
        }
        if (found) {
            rot_inverse_offset(&out->x, box->maxY, radius);
            ret = 1;
            goto done;
        }
    }
    result = 0;
    {
        s32 floor = stage_offset_x - radius;
        if (floor < from->y) {
            *out = *from;
            hit = 1;
        } else if (floor < to->y) {
            s32 t = ((floor - from->y) << 14) / (to->y - from->y);
            out->x = (to->x - from->x) * t / 0x4000 + from->x;
            out->z = (to->z - from->z) * t / 0x4000 + from->z;
            out->y = floor;
            hit = 1;
        } else {
            *out = *to;
            hit = 0;
        }
        ret = hit;
        if (ret) {
            result = 0x10000;
        }
    }
done:
    scratch_top -= 0x2C;
    out->w = result;
    return ret;
}

s32 trace_world(s32 mode, s32 flags, void *from, void *to, void *hit) {
    TraceRequest *req = scratch_alloc(sizeof(TraceRequest));
    s32 result;

    req->mode = mode;
    req->flags = flags;
    req->from = from;
    req->to = to;
    req->hit = hit;
    gte_load(VZ1, &d_8012006C, 0);
    SCRATCH_STACK_ENTER(SCRATCH_STACK_TOP);
    result = trace_world_sweep(req);
    SCRATCH_STACK_LEAVE();
    scratch_top -= sizeof(TraceRequest);
    return result;
}

/* Push the player's z movement (move[2]) out of the mesh boxes listed in `list`. */
void player_wall_clip_z(PlayerObj *p, s16 *list, s32 *box) {
    s32 dz;
    s32 rec;
    s32 vert_count;
    s32 row_base;
    s32 ox, oy, oz;
    s32 *rec_pos;
    s32 *verts;
    s32 *vert;
    s32 vx, vy, vz;
    s32 n;
    s16 *end;
    s32 *faces;
    s32 *face;
    s32 hi, lo, lo_limit, hi_limit, push_neg, push_pos;
    s32 vert_index;
    s32 row;
    u32 flags;
    s32 vy_local;
    AobjEntry *aobjs;

    rec = *list++;
    dz = p->move[2] >> 12;
    while (rec >= 0) {
        aobjs = aobj_table;
        vert_count = *list++;
        verts = (s32 *)(*(s32 *)rec_table[rec].unk_00[0] + 4);
        rec_pos = &rec_table[rec].unk_00[1];
        ox = rec_pos[0];
        oy = rec_pos[1];
        oz = rec_pos[2];
        row_base = rec_table[rec].id;
        for (; vert_count > 0; vert_count--) {
            vert_index = *list++;
            n = *list++;
            vert = &verts[vert_index * 2];
            vx = vert[0];
            vz = vert[1];
            vy_local = vx >> 16;
            vx = (s16)vx + ox;
            row = vz >> 16;
            vz = (s16)vz + oz;
            faces = (s32 *)aobjs[row + row_base].unk_04[3];
            end = list + n;
            vy = vy_local + oy;
            while (list != end) {
                n = *list++;
                face = &faces[n * 3];
                hi_limit = box[5] - vy;
                lo = face[1];
                hi = lo >> 16;
                lo = (s16)lo;
                if (lo >= hi_limit) {
                    /* the rest start higher still */
                    list = end;
                    break;
                }
                lo_limit = box[1] - vy;
                if (hi < lo_limit)
                    continue;
                lo_limit = box[0] - vx;
                lo = face[0];
                hi = lo >> 16;
                if (hi < lo_limit)
                    continue;
                hi_limit = box[4] - vx;
                lo = (s16)lo;
                if (hi_limit < lo)
                    continue;
                lo_limit = box[2] - vz + dz;
                lo = face[2];
                hi = lo >> 16;
                if (hi < lo_limit)
                    continue;
                hi_limit = box[6] - vz + dz;
                lo = (s16)lo;
                if (hi_limit < lo)
                    continue;
                if (dz < 0) {
                    push_neg = lo_limit - 1;
                    push_neg = hi - push_neg;
                    dz += push_neg;
                    flags = p->flags | 0x8;
                } else {
                    push_pos = hi_limit + 1;
                    push_pos = lo - push_pos;
                    dz += push_pos;
                    flags = p->flags | 0x4;
                }
                p->flags = flags;
                if (dz == 0)
                    goto done;
            }
        }
        rec = *list++;
    }
done:
    p->move[2] = dz << 12;
}

/* p->flags bits player_wall_clip_x sets when a wall stops the x move. */
/* Clips the player's x move against walls. list holds, per record, the record index, a vertex count and
   for each vertex its index, a face count and the face indices (-1 ends it). A vertex packs x/y and z/row
   as two halfwords each; a face is three lo/hi halfword spans (x, y, z), sorted by y lo. box is the move's
   bounds (lo at 0..2, hi at 4..6). For each face the box overlaps in y and z, the x move is cut back to
   the face's edge; it stops when nothing is left of it. */
void player_wall_clip_x(PlayerObj *p, s16 *list, s32 *box) {
    s32 dx;
    s32 rec;
    s32 vert_count;
    s32 row_base;
    s32 ox, oy, oz;
    s32 *rec_pos;
    s32 *verts;
    s32 *vert;
    s32 vx, vy, vz;
    s32 n;
    s16 *end;
    s32 *faces;
    s32 *face;
    s32 hi, lo, lo_limit, hi_limit, push_neg, push_pos;
    s32 vert_index;
    s32 row;
    u32 flags;
    s32 vy_local;
    AobjEntry *aobjs;

    rec = *list++;
    dx = p->move[0] >> 12;
    while (rec >= 0) {
        aobjs = aobj_table;
        vert_count = *list++;
        verts = (s32 *)(*(s32 *)rec_table[rec].unk_00[0] + 4);
        rec_pos = &rec_table[rec].unk_00[1];
        ox = rec_pos[0];
        oy = rec_pos[1];
        oz = rec_pos[2];
        row_base = rec_table[rec].id;
        for (; vert_count > 0; vert_count--) {
            vert_index = *list++;
            n = *list++;
            vert = &verts[vert_index * 2];
            vx = vert[0];
            vz = vert[1];
            vy_local = vx >> 16;
            vx = (s16)vx + ox;
            row = vz >> 16;
            vz = (s16)vz + oz;
            faces = (s32 *)aobjs[row + row_base].unk_04[3];
            end = list + n;
            vy = vy_local + oy;
            while (list != end) {
                n = *list++;
                face = &faces[n * 3];
                hi_limit = box[5] - vy;
                lo = face[1];
                hi = lo >> 16;
                lo = (s16)lo;
                if (lo >= hi_limit) {
                    /* the rest start higher still */
                    list = end;
                    break;
                }
                lo_limit = box[1] - vy;
                if (hi < lo_limit)
                    continue;
                lo_limit = box[2] - vz;
                lo = face[2];
                hi = lo >> 16;
                if (hi < lo_limit)
                    continue;
                hi_limit = box[6] - vz;
                lo = (s16)lo;
                if (hi_limit < lo)
                    continue;
                lo_limit = box[0] - vx + dx;
                lo = face[0];
                hi = lo >> 16;
                if (hi < lo_limit)
                    continue;
                hi_limit = box[4] - vx + dx;
                lo = (s16)lo;
                if (hi_limit < lo)
                    continue;
                if (dx < 0) {
                    push_neg = lo_limit - 1;
                    push_neg = hi - push_neg;
                    dx += push_neg;
                    flags = p->flags | 0x20;
                } else {
                    push_pos = hi_limit + 1;
                    push_pos = lo - push_pos;
                    dx += push_pos;
                    flags = p->flags | 0x10;
                }
                p->flags = flags;
                if (dx == 0)
                    goto done;
            }
        }
        rec = *list++;
    }
done:
    p->move[0] = dx << 12;
}

/* Tests the player's box against the face boxes listed in a stream:
 * per group (rec_table index, negative ends) a vertex count, then per
 * vertex its index, a face count and the face indices. Each face box is
 * three words of (min low half, max high half) for x, y, z, relative to the
 * vertex. Pushes this step's Y move out of the faces and records the floor
 * (y_max, ground) and ceiling (y_min) heights. */
void player_ground_clip(PlayerObj *player, s16 *stream, PlayerBox *box) {
    register s32 vy asm("$5");
    s32 y;
    s32 group;
    s32 nverts;
    s32 *verts;
    s32 *ofs;
    s32 ox, oy, oz;
    s32 id, page;
    s32 vi, nfaces, obj, ground;
    s16 *end;
    s32 *vert;
    s32 vx, vz, vt;
    s32 *faces;
    s32 face;
    s32 *span;
    s32 bot, lo, hi, top;
    AobjEntry *aobjs;

    group = *stream++;
    y = player->move[1] >> 12;
    if (group >= 0) {
        do {
            aobjs = aobj_table;
            nverts = *stream++;
            verts = (s32 *)(*(s32 *)rec_table[group].unk_00[0] + 4);
            ofs = &rec_table[group].unk_00[1];
            ox = ofs[0];
            oy = ofs[1];
            oz = ofs[2];
            id = rec_table[group].id;
            page = rec_table[group].pos;
            for (; nverts > 0; nverts--) {
                vi = *stream++;
                nfaces = *stream++;
                end = stream + nfaces;
                vert = &verts[vi * 2];
                /* x | y << 16, z | table << 16 */
                vx = vert[0];
                vz = vert[1];
                vy = vx >> 16;
                vx = (s16)vx + ox;
                vt = vz >> 16;
                vz = (s16)vz + oz;
                faces = (s32 *)aobjs[vt + id].unk_04[3];
                vy += oy;
                if (stream != end) {
                    obj = vi + 0x101;
                    ground = (page + obj) << 8;
                    do {
                        face = *stream++;
                        span = &faces[face * 3];
                        bot = span[0];
                        lo = box->lo[0] - vx;
                        top = bot >> 16;
                        if (top < lo) continue;
                        hi = box->hi[0] - vx;
                        bot = (s16)bot;
                        if (hi < bot) continue;
                        bot = span[2];
                        lo = box->lo[2] - vz;
                        top = bot >> 16;
                        if (top < lo) continue;
                        hi = box->hi[2] - vz;
                        bot = (s16)bot;
                        if (hi < bot) continue;
                        bot = span[1];
                        lo = box->lo[1] - vy + y;
                        top = bot >> 16;
                        hi = box->hi[1] - vy + y;
                        bot = (s16)bot;
                        if (bot < hi && top >= lo) {
                            if (y < 0) {
                                s32 edge = lo - 1;
                                y += top - edge;
                                player->flags |= 2;
                            } else {
                                y += bot - hi;
                            }
                        }
                        hi = box->hi[1] - vy + y;
                        if (bot >= hi) {
                            if (hi == bot) {
                                player->flags |= 1;
                            }
                            hi = bot + vy;
                            if (hi <= player->y_max) {
                                player->y_max = hi;
                                player->ground = ground | (face & 0xFF);
                            }
                        } else {
                            hi = top + vy;
                            if (hi >= player->y_min) {
                                player->y_min = hi;
                            }
                        }
                    } while (stream != end);
                }
            }
            group = *stream++;
        } while (group >= 0);
    }
    player->move[1] = y << 12;
}

/* Per-frame player move: splits the 20.12 position into whole units plus a kept fraction, caps the vertical move at
 * the floor (stage_offset_x), clips the move against walls in z, then x, and against the ground through the
 * player_*_clip routines using a scratch box around the player, then applies the move and publishes the position. */
void player_move_step(PlayerObj *p, void *packet) {
    s32 x, y, z;
    s32 dx, dy, dz;
    s32 fx, fy, fz;
    s32 hx, hy, hz;
    s32 bx, by, bz;
    s32 ex, ez;
    s32 floor_y;
    s32 d;
    PlayerBox *box;

    p->y_min = -0x80000;
    p->flags = 0;
    p->x_min = 0;
    p->unk_70 = 0;
    p->unk_74 = 0;
    p->x_max = 0;
    p->unk_60 = 0;
    p->ground = 0x10000;
    /* per axis: whole units moved (dx) and the fraction kept in sub */
    x = p->sub[0];
    dx = x + p->move[0];
    x >>= 12;
    fx = dx & 0xFFF;
    dx = (dx >> 12) - x;
    p->sub[0] = (x << 12) + fx;
    y = p->sub[1];
    dy = y + p->move[1];
    y >>= 12;
    fy = dy & 0xFFF;
    dy = (dy >> 12) - y;
    p->sub[1] = (y << 12) + fy;
    z = p->sub[2];
    dz = z + p->move[2];
    z >>= 12;
    fz = dz & 0xFFF;
    dz = (dz >> 12) - z;
    z = (z << 12) + fz;
    floor_y = stage_offset_x;
    p->move[0] = dx << 12;
    p->move[1] = dy << 12;
    p->sub[2] = z;
    p->move[2] = dz << 12;
    y = p->sub[1];
    p->y_max = floor_y;
    by = (y + p->move[1]) >> 12;
    if (by >= floor_y) {
        p->move[1] = (floor_y - (y >> 12)) << 12;
        p->flags |= 1;
    }
    box = scratch_alloc(0x20);
    bx = p->sub[0] >> 12;
    by = p->sub[1] >> 12;
    bz = p->sub[2] >> 12;
    hx = ((s16 *)&p->x18)[0];
    hy = ((s16 *)&p->x18)[1];
    hz = ((s16 *)&p->unk_1C)[0];
    box->lo[0] = bx - hx;
    box->lo[1] = by - hy;
    box->lo[2] = bz - hz;
    box->hi[0] = bx + hx;
    box->hi[1] = by;
    box->hi[2] = bz + hz;
    if (p->move[2] != 0) {
        player_wall_clip_z(p, packet, (s32 *)box);
        d = p->move[2] >> 12;
        p->sub[2] += d << 12;
        box->lo[2] += d;
        box->hi[2] += d;
    }
    if (p->move[0] != 0) {
        player_wall_clip_x(p, packet, (s32 *)box);
        d = p->move[0] >> 12;
        p->sub[0] += d << 12;
        box->lo[0] += d;
        box->hi[0] += d;
    }
    player_ground_clip(p, packet, box);
    p->sub[1] += p->move[1];
    scratch_top -= 0x20;
    ex = p->sub[0] >> 12;
    ez = p->sub[2] >> 12;
    p->x_max = ex;
    p->x_min = ex;
    p->unk_60 = ez;
    p->unk_70 = ez;
    *(VECTOR *)p->pos = *(VECTOR *)p->sub;
}

s32 *xform_fixed_point(s32 *in, s32 *out) {
    s32 x = in[0];
    s32 y = in[1];
    s32 z = in[2];
    s32 lx, ly, lz;

    gte_set(IR1, x & 0xFFF);
    gte_set(IR2, y & 0xFFF);
    gte_set(IR3, z & 0xFFF);
    x >>= 12;
    y >>= 12;
    gte_rtir_b();
    z >>= 12;
    gte_get(MAC1, lx);
    gte_set(IR1, x);
    gte_set(IR2, y);
    gte_set(IR3, z);
    gte_get(MAC2, ly);
    gte_get(MAC3, lz);
    gte_rtir_sf0_b();
    gte_get(MAC1, x);
    gte_get(MAC2, y);
    gte_get(MAC3, z);
    out[0] = x + lx;
    out[1] = y + ly;
    out[2] = z + lz;
    return out;
}

/* TRUE if the five-field record is the identity scale (0x1000, 0, 0x1000, 0, 0x1000) */
s32 is_unit_scale(s32 *p) {
    s32 v = p[0];
    if (v != 0x1000 || p[1] != 0 || p[2] != v || p[3] != 0) {
        return 0;
    }
    return *(s16 *)&p[4] == 0x1000;
}

/* Builds the two corner points (lo, hi) of the player's bounding box around
 * the sub position in scratch memory and passes them to rec_table_query_box with the
 * pose. Pose bit 0x40 uses one radius for all axes (isqrt of the move length
 * plus 0x90 plus half[3]); otherwise each axis uses its own half size plus
 * 0x90, widened toward the move direction by 2 units. */
void player_bounds_query(PlayerObj *p, void *packet) {
    s32 *lo;
    s32 *hi;
    s16 *half;
    s32 sx, sy, sz;
    s32 r;

    lo = scratch_alloc(0x10);
    hi = scratch_alloc(0x10);
    half = (s16 *)&p->x18;

    sx = p->sub[0] >> 12;
    sy = p->sub[1] >> 12;
    sz = p->sub[2] >> 12;

    if (p->pose & 0x40) {
        r = isqrt(length_sq((p->move[0] + 0xFFF) >> 12,
                            (p->move[1] + 0xFFF) >> 12,
                            (p->move[2] + 0xFFF) >> 12)) + 0x90;
        r += half[3];
        lo[0] = sx - r;
        lo[1] = sy - r;
        lo[2] = sz - r;
        hi[0] = sx + r;
        hi[1] = sy + r;
        hi[2] = sz + r;
    } else {
        lo[0] = sx - half[0] - 0x90;
        lo[1] = sy - half[1] - 0x90;
        lo[2] = sz - half[2] - 0x90;
        hi[0] = sx + half[0] + 0x90;
        hi[1] = sy + 0x90;
        hi[2] = sz + half[2] + 0x90;

        if (p->move[0] > 0) {
            hi[0] += 2 + (p->move[0] >> 12);
        } else {
            lo[0] += -2 + (p->move[0] >> 12);
        }
        if (p->move[1] > 0) {
            hi[1] += 2 + (p->move[1] >> 12);
        } else {
            lo[1] += -2 + (p->move[1] >> 12);
        }
        if (p->move[2] > 0) {
            hi[2] += 2 + (p->move[2] >> 12);
        } else {
            lo[2] += -2 + (p->move[2] >> 12);
        }
    }
    rec_table_query_box(p->pose, lo, hi, packet);
    scratch_top -= 0x20;
}

/* Axis-aligned bounds of `count` vertices (8-byte records: x, y, z, pad).
 * Writes min/max of x, y, z to bounds[0..5]: minX, maxX, minY, maxY, minZ, maxZ. */
void verts_bounds(s32 count, s16 *verts, s16 *bounds) {
    s16 *p;
    s16 *q;
    s16 *end;
    s32 min_x, max_x, min_y, max_y, min_z, max_z;
    s32 v;

    p = verts;
    min_x = p[0];
    max_x = p[0];
    min_y = p[1];
    max_y = p[1];
    min_z = p[2];
    max_z = p[2];
    end = verts + count * 4;
    p += 4;

    if (p != end) {
        q = p + 2;
        do {
            v = p[0];
            if (v < min_x) {
                min_x = v;
            } else if (max_x < v) {
                max_x = v;
            }
            v = q[-1];
            if (v < min_y) {
                min_y = v;
            } else if (max_y < v) {
                max_y = v;
            }
            v = q[0];
            if (v < min_z) {
                min_z = v;
            } else if (max_z < v) {
                max_z = v;
            }
            p += 4;
            q += 4;
        } while (p != end);
    }

    bounds[0] = min_x;
    bounds[1] = max_x;
    bounds[2] = min_y;
    bounds[3] = max_y;
    bounds[4] = min_z;
    bounds[5] = max_z;
}

s32 zone_add_model_faces(s32 *origin, ClipBox *box, AobjEntry *model, s32 key, s16 *stream) {
    s32 added = 0;
    u8 *faces;
    s32 *colours;
    ClipVertex *d; /* fourth vertex */
    ClipVertex *xf; /* transformed vertices */
    ClipVertex *base; /* xf - 1: vertex indices are 1-based */
    s32 m; /* vertices in the clipped polygon */
    MeshFace *face;
    ClipVertex *buf = scratch_alloc(0x220);
    s32 idx;
    ZoneRec *rec;
    s32 count;
    ZonePoint *points;
    ClipVertex *a, *b, *c;
    s32 n, flags, vi;

    count = *(s32 *)model->unk_04[0];
    if (count < 0x30) {
        xf = buf + 20;
    } else {
        xf = ((ZoneTable *)work_area_ptr->packet)->verts;
    }
    xform_points_local(origin, count, (s16 *)(model->unk_04[0] + 4), (s16 *)xf);
    if (clip_verts_test_box(count, xf, box) == 0) {
        ZoneTable *zones = work_area_ptr->packet;
        count = *stream++;
        points = (ZonePoint *)&zones->points[zones->point_count];
        rec = &zones->recs[zones->count];
        faces = (u8 *)(model->unk_04[1] + 4);
        colours = (s32 *)colour_table_ptr + model->value;
        for (; count > 0; count--) {
            idx = *stream++;
            face = (MeshFace *)(faces + idx * 12);
            base = xf - 1;
            n = 3;
            a = &base[face->v[0]];
            b = &base[face->v[1]];
            c = &base[face->v[2]];
            flags = (s16)(a->flags & b->flags & c->flags);
            vi = face->v[3];
            if (vi != 0) {
                /* The nesting raises base's use count (loop depth) so it gets $s4. */
                do { do { d = &base[vi]; } while (0); } while (0);
                flags &= d->flags;
                n = 4;
            }
            if (flags != 0) {
                m = 0;
            } else {
                CLIP_VERTEX_COPY(&buf[0], a);
                CLIP_VERTEX_COPY(&buf[1], b);
                CLIP_VERTEX_COPY(&buf[2], c);
                if (vi != 0) {
                    CLIP_VERTEX_COPY(&buf[3], d);
                }
                m = n;
            }
            if (m != 0) {
                m = clip_poly_slab(box->minX, box->maxX, m, buf, buf + 10);
                if (m != 0) {
                    m = clip_poly_slab(box->minZ, box->maxZ, m, buf + 10, (ClipVertex *)points);
                    if (m != 0) {
                        verts_bounds(m, (s16 *)points, &rec->x_min);
                        gte_load(VXY0, face, 0);
                        gte_load(VZ0, face, 4);
                        rec->key = (key << 8) | (idx & 0xFF);
                        gte_rtv0_b();
                        rec->first = ((ZoneTable *)work_area_ptr->packet)->point_count;
                        rec->count = m;
                        rec->colour = colours[face->colour];
                        points += m;
                        added++;
                        ((ZoneTable *)work_area_ptr->packet)->point_count += m;
                        gte_store(MAC2, rec, 0x18); /* rec->depth */
                        rec++;
                    }
                }
            }
        }
        ((ZoneTable *)work_area_ptr->packet)->count += added;
    }
    scratch_top -= 0x220;
    return added;
}

/* Shell-sorts the packet area spans by (y_top, y_bottom), then finds the spans
 * around height y: out[1]/out[3] the first span below, out[5]/out[7] the one
 * above. Returns the flags of every span reaching y. */
s32 packet_spans_at_height(s32 y, s32 *out) {
    register PacketSpanArea *packet asm("$3");
    PacketSpanArea *area;
    PacketSpan *rec;
    PacketSpan *recs;
    s16 *order;
    s16 *sorted;
    SpanBracket lo;
    SpanBracket hi;
    s32 n_spans;
    s32 count;
    s32 flags;
    s32 have_lo;
    s32 have_hi;
    s32 i;
    s32 j;
    s32 k;
    s32 step;
    s32 gap;
    s32 cur;
    s32 other;
    s32 cur_top;
    s32 cur_bottom;
    s32 top;
    s32 bottom;

    out[0] = 0;
    out[1] = 0x7FFF;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;
    out[5] = -0x7FFF;
    out[6] = 0;
    out[7] = 0;
    /* read through a const pointer: the load is scheduled above the saves */
    packet = (PacketSpanArea *)(*(WorkArea *const *)&work_area_ptr)->packet;
    n_spans = packet->count;
    if (n_spans == 0) {
        return 0;
    }
    y -= 0x30;
    i = 0;
    order = packet->order;
    count = n_spans;
    for (; i < count; i++) {
        order[i] = i;
    }
    if (count > 1) {
        recs = ((PacketSpanArea *)work_area_ptr->packet)->recs;
        for (step = 1; step <= count / 9; step = step * 3 + 1) {
        }
        for (gap = step; gap > 0;) {
            /* gap / 3 for gap > 0: the product is started here, read below */
            mips_mult(gap, 0x55555556);
            for (i = gap; i < count; i++) {
                cur = order[i];
                j = i - gap;
                cur_top = recs[cur].y_top;
                cur_bottom = recs[cur].y_bottom;
                for (; j >= 0; j -= gap) {
                    other = order[j];
                    if (recs[other].y_top < cur_top) {
                        break;
                    }
                    if (recs[other].y_top == cur_top && recs[other].y_bottom >= cur_bottom) {
                        break;
                    }
                    order[j + gap] = other;
                }
                order[j + gap] = cur;
            }
            mips_mfhi(gap);
        }
    }
    have_lo = 0;
    area = ((PacketSpanArea *)work_area_ptr->packet);
    have_hi = 0;
    flags = 0;
    sorted = area->order;
    rec = &area->recs[sorted[0]];
    if (y + 0x30 >= rec->y_top) {
        flags = rec->flags;
    }
    if (rec->y_bottom < y) {
        lo.y_top = rec->y_top;
        lo.y_bottom = rec->y_bottom;
        lo.pos_bottom = lo.pos_top = rec->pos;
        lo.depth = rec->depth;
        have_lo = 1;
    } else {
        hi.y_top = rec->y_top;
        hi.pos_top = rec->pos;
        hi.depth = rec->depth;
        have_hi = 1;
    }
    for (k = 1; k < n_spans; k++) {
        rec = &((PacketSpanArea *)work_area_ptr->packet)->recs[sorted[k]];
        if (rec->y_top <= y + 0x30) {
            flags |= rec->flags;
        }
        if (have_hi) {
            if (hi.y_top < rec->y_top) {
                if (y < rec->y_top) {
                    break;
                }
            } else if (rec->depth < hi.depth) {
                hi.pos_top = rec->pos;
                hi.depth = rec->depth;
            }
        } else if (rec->y_bottom < y) {
            if (lo.y_bottom < rec->y_top) {
                lo.y_top = rec->y_top;
                lo.y_bottom = rec->y_bottom;
                lo.pos_bottom = lo.pos_top = rec->pos;
                lo.depth = rec->depth;
            } else {
                if (lo.y_top == rec->y_top && rec->depth < lo.depth) {
                    lo.pos_top = rec->pos;
                    lo.depth = rec->depth;
                }
                if (lo.y_bottom < rec->y_bottom) {
                    lo.pos_bottom = rec->pos;
                    lo.y_bottom = rec->y_bottom;
                }
            }
        } else {
            have_hi = 1;
            if (lo.y_bottom < rec->y_top) {
                hi.y_top = rec->y_top;
                hi.pos_top = rec->pos;
                hi.depth = rec->depth;
            } else {
                have_lo = 0;
                if (lo.y_top == rec->y_top && rec->depth < lo.depth) {
                    lo.pos_top = rec->pos;
                    lo.depth = rec->depth;
                }
                hi.y_top = lo.y_top;
                hi.pos_top = lo.pos_top;
                hi.depth = lo.depth;
            }
        }
    }
    if (have_hi) {
        out[1] = hi.y_top;
        out[3] = hi.pos_top;
    }
    if (have_lo) {
        top = lo.y_bottom + 2;
        bottom = out[1];
        if (top < bottom) {
            bottom = top;
        }
        out[5] = bottom;
        out[7] = lo.pos_bottom;
    }
    return flags;
}

void zone_query_box(s16 *list, void *box) {
    /* list: { rec index, vertex count, { vertex, n, n words }... }... -1 */
    s16 *cmds;
    s32 *out;
    ZoneTable *zones;
    s32 idx, count;
    s32 origin_x, origin_y, origin_z;
    s32 obj_base, idx_base;
    u8 *verts;
    s32 *origin;
    s32 *words;
    s32 v, w1, w0;
    s32 y, obj;
    s32 id;
    AobjEntry *obj_tbl;

    cmds = list;
    zones = work_area_ptr->packet;
    out = scratch_alloc(0x10);
    zones->point_count = 0;
    zones->count = 0;

    while ((idx = *cmds++) >= 0) {
        count = *cmds++;
        verts = (u8 *)*(s32 *)rec_table[idx].unk_00[0] + 4; /* skip the count word */
        origin = &rec_table[idx].unk_00[1];
        origin_x = origin[0];
        origin_y = origin[1];
        origin_z = origin[2];
        obj_base = rec_table[idx].id;
        idx_base = rec_table[idx].pos;
        while (count > 0) {
            v = *cmds++;
            words = (s32 *)(verts + v * 8);
            w0 = words[0];
            w1 = words[1];
            y = w0 >> 16;
            w0 = (w0 << 16) >> 16;
            obj = w1 >> 16;
            w1 = (w1 << 16) >> 16;
            obj_tbl = &aobj_table[obj + obj_base];
            out[0] = origin_x + w0;
            out[1] = origin_y + y;
            out[2] = origin_z + w1;
            id = idx_base + 0x101;
            zone_add_model_faces(out, box, obj_tbl, v + id, cmds);
            v = *cmds++; /* skip the vertex's word list */
            cmds += v;
            count--;
        }
    }

    gte_get_ctrl(TRX, w0);
    gte_get_ctrl(TRZ, w1);
    out[1] = stage_offset_x;
    out[0] = w0;
    out[2] = w1;
    zone_add_model_faces(out, box, aobj_table, 0x100, clip_index_stream);
    scratch_top -= 0x10;
}

/* Puts the player's collision box (the position being moved, in whole units, plus or minus the half-sizes at
 * 0x18..0x1C; taller by 0x60 at both ends and by twice the depth in pose bit 6) on the scratchpad and passes it
 * to zone_query_box. */
void player_column_query(PlayerObj *player, void *packet) {
    s16 *box = scratch_alloc(0xC);
    u16 *size = (u16 *)&player->x18;
    s32 x = player->sub[0] >> 12;
    s32 y = player->sub[1] >> 12;
    s32 z = player->sub[2] >> 12;
    s32 ox;

    box[0] = x - size[0];
    box[2] = y - size[1];
    box[4] = z - size[2];
    ox = size[0];
    box[3] = y;
    box[1] = ox + x;
    box[5] = size[2] + z;
    if (player->pose & 0x40) {
        box[3] += (s16)size[2] * 2;
    }
    box[3] += 0x60;
    box[2] -= 0x60;
    zone_query_box(packet, box);
    scratch_top -= 0xC;
}

void player_record_surface(PlayerObj *p) {
    s32 surface = p->unk_56;
    s32 x = p->sub[0] >> 12;
    s32 y;
    s32 z;

    player_last_flags = p->flags;
    player_clamp_box = surface;
    y = p->sub[1] >> 12;
    z = p->sub[2] >> 12;
    if (clamp_get_max_x(surface) == 0) {
        player_clamp_box = -1;
    }
    player_pos_x = x;
    player_pos_y = y;
    player_pos_z = z;
}

/* Clamps the player's position to the stage and to the current clamp box,
   then stores the position relative to player_pos and the box index. */
void player_clamp_pos(PlayerObj *p) {
    s32 x = p->sub[0] >> 12;
    s32 y = p->sub[1] >> 12;
    s32 z = p->sub[2] >> 12;
    s32 box;
    Vec3 *v;
    u32 flags;

    p->flags &= 0xFFFEFFFF;
    if (stage_offset_x < y) {
        y = stage_offset_x;
        p->sub[1] = stage_offset_x << 12;
    }
    box = -1;
    if ((p->pose & 0x10) && (p->pose & 3)) {
        box = clamp_find_box(x, y, z);
    }
    if (player_clamp_box >= 0) {
        do { /* loop note: register priority of z */
            x = p->sub[0] >> 12;
            y = p->sub[1] >> 12;
            z = p->sub[2] >> 12;
        } while (0);
        if (box < 0) {
            v = scratch_alloc(0x10);
            v->x = x;
            v->y = y;
            v->z = z;
            flags = clamp_point_to_box(player_clamp_box, v);
            scratch_top -= 0x10;
            x = v->x;
            y = v->y;
            z = v->z;
            box = player_clamp_box;
            p->sub[0] = x << 12;
            p->sub[1] = y << 12;
            p->sub[2] = z << 12;
            p->pos[0] = x << 12;
            p->pos[1] = y << 12;
            p->pos[2] = z << 12;
            p->flags |= flags;
        }
    }
    p->delta[0] = (p->sub[0] >> 12) - (u16)player_pos_x;
    do { } while (0); /* scheduling barrier */
    p->delta[1] = (p->sub[1] >> 12) - (u16)player_pos_y;
    p->unk_56 = box;
    p->delta[2] = (p->sub[2] >> 12) - (u16)player_pos_z;
}

s32 player_step_vertical(PlayerObj *p, s32 dy) {
    s32 blocked = 0;
    s32 top = p->y_max;
    s32 bottom = p->y_min;
    s32 y = p->sub[1];
    s32 room = top - bottom;
    s32 flags;

    top <<= 12;
    bottom = (bottom + ((s16 *)&p->x18)[1]) << 12;
    flags = p->flags & ~2;
    p->flags = flags;
    if ((y >> 12) < (bottom >> 12)) {
        p->flags = flags | 2;
        if (((s16 *)&p->x18)[1] < room && ((bottom - y) >> 12) < 0x30) {
            y = bottom;
        } else {
            blocked = 1;
        }
    }
    if ((y >> 12) > (top >> 12)) {
        p->flags |= 1;
        if (((s16 *)&p->x18)[1] < room && ((y - top) >> 12) < 0x30) {
            y = top;
        } else {
            blocked = 1;
        }
    }
    if (blocked) {
        return 1;
    }
    if (y + dy < bottom) {
        dy = bottom - y;
        p->flags |= 2;
    } else {
        p->flags &= ~2;
    }
    if (p->flags & 1) {
        if (y + dy >= top - 0x30000) {
            dy = top - y;
        } else {
            p->flags &= ~1;
        }
    } else if (y + dy >= top) {
        dy = top - y;
        p->flags |= 1;
    }
    p->sub[1] = y + dy;
    return 0;
}

void player_move_vertical(PlayerObj *p) {
    ScratchBox6 *box;
    u16 *half = (u16 *)&p->x18;
    s32 x, y, z, my;
    u16 lo;

    player_vertical_blocked = 0;
    if (p->move[1] != 0 || (p->pose & 0x40)) {
        box = scratch_alloc(0xC);
        x = p->sub[0] >> 12;
        y = p->sub[1] >> 12;
        z = p->sub[2] >> 12;
        box->x0 = x - half[0];
        box->y0 = y - half[1];
        box->z0 = z - half[2];
        box->x1 = half[0] + x;
        box->y1 = y;
        box->z1 = half[2] + z;
        my = p->move[1];
        if (my < 0) {
            lo = box->y0 - 0x60;
            box->y0 = lo + (my >> 12);
            box->y1 = box->y1 + 0x60;
        } else {
            lo = box->y1 + 0x60;
            box->y0 = box->y0 - 0x60;
            box->y1 = lo + (p->move[1] >> 12);
        }
        zone_query_box(work_area_ptr->packet, box);
        scratch_top -= 0xC;
        packet_spans_at_height(p->sub[1] >> 12, &p->x_max);
        player_vertical_blocked = player_step_vertical(p, p->move[1]);
        p->move[1] = 0;
    }
}

/* Probes the ground under a box: fills a 12-byte extent (x0 x1 y0 y1 z0 z1) around its centre and a 0x20-byte
 * probe result, then clamps the box's y to the probed height. Returns flag bits (0x40/0x80 from the probe,
 * 1 when the box is above the probe). */
s32 box_ground_probe(GroundBox *box) {
    s32 *probe = scratch_alloc(0x20);
    s32 *hi = probe + 4;
    s16 *ext = (s16 *)scratch_top;
    s32 flags;
    s32 cy = box->y >> 12;
    s32 cz = box->z >> 12;
    s32 cx = box->x >> 12;
    s32 half_x;
    s32 y;
    s32 delta;
    s32 probed;
    s32 top;

    ext[0] = cx - (u16)box->half_x;
    ext[2] = cy - (u16)box->half_y;
    ext[4] = cz - (u16)box->half_z;
    half_x = (u16)box->half_x;
    /* Empty asms that take scratch_top and clobber memory: they keep the $gp bump between the stores, as the
     * original orders them. */
    __asm__("" : "=r"(scratch_top) : "0"(scratch_top) : "memory");
    scratch_top += 0xC;
    __asm__("" : "=r"(scratch_top) : "0"(scratch_top) : "memory");
    ext[3] = cy;
    ext[1] = half_x + cx;
    ext[5] = (u16)box->half_z + cz;
    ext[3] = (u16)box->half_y + ((u16)ext[3] + 0x60);
    zone_query_box(work_area_ptr->packet, ext);
    scratch_top -= 0xC;

    probed = packet_spans_at_height(box->y >> 12, probe);
    flags = 0;
    if (probed & 0x10) {
        flags = 0xC0;
    }
    flags |= 2;

    y = box->y >> 12;
    top = probe[5] + box->half_y;
    if (top < probe[1] && y >= top) {
        delta = y - top;
        flags &= 0xC0;
        if (delta > 0x30) {
            delta = 0x30;
        }
        if (box->flags & 1) {
            if (probe[1] + delta < y) {
                flags |= 1;
                goto done;
            }
            if (y < probe[1] - 0x30) {
                box->flags &= ~1;
            } else {
                y = probe[1];
            }
        } else if (probe[1] < y) {
            flags |= 1;
            goto done;
        }
        box->corner_a = *(MatrixHalf *)probe;
        box->corner_b = *(MatrixHalf *)hi;
    }
done:
    scratch_top -= 0x20;
    box->y = (y << 12) + (box->y & 0xFFF);
    return flags;
}

void zone_y_range(ZoneQueryY *q, s32 *out_min, s32 *out_max)
{
    s32 r = q->radius;
    s32 y = q->y >> 12;
    s32 z_center = q->z >> 12;
    s32 z;
    s32 max_y = y - r;
    s32 min_y = y + r;
    ZoneRecY *rec;
    s32 n;
    s32 found;

    *out_min = max_y;
    *out_max = min_y;
    n = ((ZoneTableY *)work_area_ptr->packet)->count;
    if (n == 0) {
        return;
    }
    found = 0;
    rec = ((ZoneTableY *)work_area_ptr->packet)->recs;
    for (; n > 0; n--, rec++) {
        z = z_center + r;
        if (z < rec->z_min) {
            continue;
        }
        if (z >= rec->z_max) {
            found++;
            if (rec->y_min < min_y) {
                min_y = rec->y_min;
            }
            if (max_y < rec->y_max) {
                max_y = rec->y_max;
            }
        } else {
            s32 edge_min = min_y;
            s32 edge_max = max_y;
            s32 k = rec->count;
            ZonePointY *cur = &((ZoneTableY *)work_area_ptr->packet)->points[rec->first];
            ZonePointY *prev = cur + k - 1;
            s32 v;
            s32 dz;

            for (; k > 0; k--, prev = cur, cur++) {
                if (z < prev->z) {
                    if (z < cur->z) {
                        continue;
                    }
                    dz = cur->z - prev->z;
                    v = (cur->y - prev->y) * (((z - prev->z) << 14) / dz) / 16384 + prev->y;
                } else {
                    v = prev->y;
                }
                if (v < edge_min) {
                    edge_min = v;
                }
                if (edge_max < v) {
                    edge_max = v;
                }
                if (z < cur->z) {
                    register s32 num asm("$2") = (z - cur->z) << 14;
                    v = (prev->y - cur->y) * (num / (prev->z - cur->z)) / 16384 + cur->y;
                    if (v < edge_min) {
                        edge_min = v;
                    }
                    if (edge_max < v) {
                        edge_max = v;
                    }
                }
            }
            found++;
            if (edge_min < min_y) {
                min_y = edge_min;
            }
            if (max_y < edge_max) {
                max_y = edge_max;
            }
        }
    }
    if (found != 0) {
        *out_min = min_y;
        *out_max = max_y;
    }
}

void zone_x_range(EdgeQuery *q, s32 *out_min, s32 *out_max)
{
    s32 r = q->radius;
    s32 x = q->x >> 12;
    s32 z_center = q->z >> 12;
    s32 z;
    s32 max_x = x - r;
    s32 min_x = x + r;
    ZoneTable *tab;
    ZoneRec *rec;
    s32 n;
    s32 found;

    *out_min = max_x;
    *out_max = min_x;
    tab = work_area_ptr->packet;
    n = tab->count;
    if (n == 0) {
        return;
    }
    rec = tab->recs;
    found = 0;
    for (; n > 0; n--, rec++) {
        z = z_center + r;
        if (z < rec->z_min) {
            continue;
        }
        if (z >= rec->z_max) {
            found++;
            if (rec->x_min < min_x) {
                min_x = rec->x_min;
            }
            if (max_x < rec->x_max) {
                max_x = rec->x_max;
            }
        } else {
            s32 edge_min = min_x;
            s32 edge_max = max_x;
            s32 k = rec->count;
            ZonePoint *cur = &((ZoneTable *)work_area_ptr->packet)->points[rec->first];
            ZonePoint *prev = cur + k - 1;
            s32 v;
            s32 dz;

            for (; k > 0; k--, prev = cur, cur++) {
                if (z < prev->z) {
                    if (z < cur->z) {
                        continue;
                    }
                    dz = cur->z - prev->z;
                    v = (cur->x - prev->x) * (((z - prev->z) << 14) / dz) / 16384 + prev->x;
                } else {
                    v = prev->x;
                }
                if (v < edge_min) {
                    edge_min = v;
                }
                if (edge_max < v) {
                    edge_max = v;
                }
                if (z < cur->z) {
                    register s32 num asm("$2") = (z - cur->z) << 14;
                    v = (prev->x - cur->x) * (num / (prev->z - cur->z)) / 16384 + cur->x;
                    if (v < edge_min) {
                        edge_min = v;
                    }
                    if (edge_max < v) {
                        edge_max = v;
                    }
                }
            }
            found++;
            if (edge_min < min_x) {
                min_x = edge_min;
            }
            if (max_x < edge_max) {
                max_x = edge_max;
            }
        }
    }
    if (found != 0) {
        *out_min = min_x;
        *out_max = max_x;
    }
}

/* Moves the player along z by move[2] in steps of 32 units (64 while player_vertical_blocked is set, 2 when the flags
 * already say blocked that way), probing at each step (box_ground_probe) and halving the step on a hit; a step
 * that stays blocked sets 8 (-z) or 4 (+z), and 0x40 from the probe. On a slope (pose bit 0x10) a step that
 * changed y calls atan2 twice, results unused. Wall climbing (pose bit 0x40): queries the column, then past
 * the zone's z range (zone_y_range) moves around the edge, swaps the y and z half-sizes and turns the frame
 * (the GTE rotation matrix) a quarter turn about x. `frac` is unused. */
void player_move_z(PlayerObj *p, s32 frac) {
    s32 left = p->move[2] >> 12;
    u32 before;
    u32 entry_flags = p->flags;
    s32 chunk = 0x20;
    s32 step;
    s32 dir;
    s32 hit;
    s32 stuck;
    s32 start_flags;
    s32 surface;
    s32 flags;
    s32 old_y;
    s32 rise;
    s32 *spans;

    if (left < 0) {
        dir = -1;
        left = -left;
        if (player_vertical_blocked != 0) {
            chunk = 0x40;
        } else if ((entry_flags & 0x10008) == 8) {
            chunk = 2;
        }
    } else if (left > 0) {
        dir = 1;
        if (player_vertical_blocked != 0) {
            chunk = 0x40;
        } else if ((entry_flags & 0x10004) == 4) {
            chunk = 2;
        }
    } else {
        dir = 0;
    }
    stuck = (left != 0) ? 0x3F : 0;
    hit = 0;
    start_flags = p->flags &= ~0x34C;
    surface = surface_of(p->ground);

    while (left > 0) {
        if (chunk <= 0) {
            break;
        }
        if (left < chunk) {
            chunk = left;
        }
        step = chunk;
        if (dir < 0) {
            step = -step;
        }
        before = p->flags;
        old_y = p->sub[1];
        p->sub[2] += step << 12;
        hit = box_ground_probe((GroundBox *)p);
        if ((hit & 0x3F) != 0) {
            left = ABS(step) - 1;
            chunk >>= 1;
            p->sub[2] -= step << 12;
        } else {
            stuck = 0;
            left -= ABS(step);
            if ((p->pose & 0x10) && p->sub[1] != old_y && (before & p->flags & ON_GROUND)) {
                /* Hard registers: as plain locals, local-alloc ties dy to rise (both s0) and the
                 * a0 copy sinks below the subtraction. */
                register s32 run asm("$4") = step;
                register s32 dy asm("$2") = p->sub[1] - old_y;

                rise = dy >> 12;
                atan2(run, rise);
                atan2(step, rise);
                p->sub[1] = p->sub[1];
                p->sub[2] = p->sub[2];
            }
        }
    }

    if (stuck != 0) {
        if (hit & 0x40) {
            p->flags |= 0x40;
        }
        if (dir < 0) {
            p->flags |= 8;
        } else if (dir > 0) {
            p->flags |= 4;
        }
    }

    p->move[2] = 0;
    if (!(p->pose & 0x40) || (surface & 0x10)) {
        return;
    }
    if (dir == 0 || !(start_flags & ON_GROUND)) {
        if ((player_last_flags & 1) || !(p->flags & ON_GROUND)) {
            return;
        }
    }

    {
        s16 *box = scratch_alloc(0xC); /* x0 x1 y0 y1 z0 z1 */
        s32 x = p->sub[0] >> 12;
        s32 y = p->sub[1] >> 12;
        s32 z = p->sub[2] >> 12;

        box[0] = x - PLAYER_HALF(p)[0];
        box[2] = y - PLAYER_HALF(p)[1];
        box[4] = z - PLAYER_HALF(p)[2];
        box[1] = PLAYER_HALF(p)[0] + x;
        box[3] = y;
        box[5] = PLAYER_HALF(p)[2] + z;
        box[3] += 0x30 + (s16)PLAYER_HALF(p)[2] * 2;
        zone_query_box(work_area_ptr->packet, box);
        scratch_top -= 0xC;
    }
    spans = &p->x_max;
    packet_spans_at_height(p->sub[1] >> 12, spans);
    player_step_vertical(p, 0);

    flags = p->flags;
    if (!(flags & ON_GROUND)) {
        if (dir < 0) {
            p->flags = flags | 0x200;
        } else if (dir > 0) {
            p->flags = flags | 0x100;
        }
        return;
    }
    if (stuck != 0 || (flags & 0xF000)) {
        return;
    }
    {
        s32 range[2]; /* the zone's z range */
        s32 edge;
        s32 bound;
        s32 z;
        s32 half_y, half_z, half_y2;
        RotMatrix *saved; /* saved[0]: the frame; saved[1]: the turn */
        register RotMatrix *frame asm("$5");

        zone_y_range((ZoneQueryY *)p, &range[0], &range[1]);
        z = p->sub[2] >> 12;
        edge = range[1];
        if (edge + 0x20 < z) {
            p->sub[2] += (edge + 1 - z + (half_y2 = (half_y = (s16)PLAYER_HALF(p)[1]) / 2)) << 12;
            half_z = (s16)PLAYER_HALF(p)[2];
            p->sub[1] += half_z << 12;
            PLAYER_HALF(p)[2] = half_y2;
            PLAYER_HALF(p)[1] = half_z * 2;
            player_column_query(p, work_area_ptr->packet);
            packet_spans_at_height(p->sub[1] >> 12, spans);
            PLAYER_HALF(p)[2] = half_z;
            PLAYER_HALF(p)[1] = half_y;
            if ((p->sub[1] >> 12) < p->y_max && p->y_min < (p->sub[1] >> 12) - half_z * 2) {
                s32 climb, room;
                s32 turn;

                saved = (RotMatrix *)scratch_top;
                bound = range[1];
                climb = z - bound + 1;
                scratch_top += 0x40;
                frame = saved;
                room = p->y_max - (p->sub[1] >> 12) - 1;
                if (room < climb) {
                    climb = room;
                }
                p->sub[1] += climb << 12;
                p->sub[2] -= half_y2 << 12;
                p->sub[1] -= half_z << 12;
                /* Hides frame == saved from cse, which would store the first word through saved. */
                __asm__("" : "=r"(frame) : "0"(frame));
                rot_matrix_save(frame);
                turn = rcossin_tbl[0x400];
                saved[1].m[0][0] = 0x1000;
                saved[1].m[0][1] = 0;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[1][1] = (u32)turn >> 16;
                saved[1].m[1][2] = -turn;
                saved[1].m[2][1] = turn;
                saved[1].m[2][2] = (u32)turn >> 16;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                scratch_top -= 0x40;
                p->flags &= ~0x2000;
            } else {
                p->sub[2] -= (range[1] + 1 - z + half_y / 2) << 12;
                p->sub[1] -= half_z << 12;
            }
        } else if (edge = range[0], z < edge - 0x20) {
            half_y = (s16)PLAYER_HALF(p)[1];
            half_z = (s16)PLAYER_HALF(p)[2];
            p->sub[2] += (edge - 1 - z - half_y / 2) << 12;
            p->sub[1] += half_z << 12;
            PLAYER_HALF(p)[2] = half_y / 2;
            PLAYER_HALF(p)[1] = half_z * 2;
            player_column_query(p, work_area_ptr->packet);
            packet_spans_at_height(p->sub[1] >> 12, spans);
            PLAYER_HALF(p)[2] = half_z;
            PLAYER_HALF(p)[1] = half_y;
            if ((p->sub[1] >> 12) < p->y_max && p->y_min < (p->sub[1] >> 12) - half_z * 2) {
                s32 climb, room;
                s32 turn;

                saved = (RotMatrix *)scratch_top;
                bound = range[0];
                climb = bound - z + 1;
                scratch_top += 0x40;
                frame = saved;
                room = p->y_max - (p->sub[1] >> 12) - 1;
                if (room < climb) {
                    climb = room;
                }
                p->sub[1] += climb << 12;
                p->sub[2] -= ((-half_y) / 2) << 12;
                p->sub[1] -= half_z << 12;
                __asm__("" : "=r"(frame) : "0"(frame));
                rot_matrix_save(frame);
                turn = rcossin_tbl[0xC00];
                saved[1].m[0][0] = 0x1000;
                saved[1].m[0][1] = 0;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[1][1] = (u32)turn >> 16;
                saved[1].m[1][2] = -turn;
                saved[1].m[2][1] = turn;
                saved[1].m[2][2] = (u32)turn >> 16;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                scratch_top -= 0x40;
                p->flags &= ~0x1000;
            } else {
                p->sub[2] -= (range[0] - 1 - z - half_y / 2) << 12;
                p->sub[1] -= half_z << 12;
            }
        }
    }
}

void player_move_x(PlayerObj *p, s32 frac) {
    s32 left = p->move[0] >> 12;
    u32 before;
    u32 entry_flags = p->flags;
    s32 chunk = 0x20;
    s32 step;
    s32 dir;
    s32 hit;
    s32 stuck;
    s32 start_flags;
    s32 surface;
    s32 flags;
    s32 old_y;
    s32 rise;
    s32 *spans;

    if (left < 0) {
        dir = -1;
        left = -left;
        if (player_vertical_blocked != 0) {
            chunk = 0x40;
        } else if ((entry_flags & 0x10020) == 0x20) {
            chunk = 2;
        }
    } else if (left > 0) {
        dir = 1;
        if (player_vertical_blocked != 0) {
            chunk = 0x40;
        } else if ((entry_flags & 0x10010) == 0x10) {
            chunk = 2;
        }
    } else {
        dir = 0;
    }
    stuck = (left != 0) ? 0x3F : 0;
    hit = 0;
    start_flags = p->flags &= ~0xCB0;
    surface = surface_of(p->ground);

    while (left > 0) {
        if (chunk <= 0) {
            break;
        }
        if (left < chunk) {
            chunk = left;
        }
        step = chunk;
        if (dir < 0) {
            step = -step;
        }
        before = p->flags;
        old_y = p->sub[1];
        p->sub[0] += step << 12;
        hit = box_ground_probe((GroundBox *)p);
        if ((hit & 0x3F) != 0) {
            left = ABS(step) - 1;
            chunk >>= 1;
            p->sub[0] -= step << 12;
        } else {
            stuck = 0;
            left -= ABS(step);
            if ((p->pose & 0x10) && p->sub[1] != old_y && (before & p->flags & ON_GROUND)) {
                /* Hard registers: as plain locals, local-alloc ties dy to rise (both s0) and the
                 * a0 copy sinks below the subtraction. */
                register s32 run asm("$4") = step;
                register s32 dy asm("$2") = p->sub[1] - old_y;

                rise = dy >> 12;
                atan2(run, rise);
                atan2(step, rise);
                p->sub[1] = p->sub[1];
                p->sub[0] = p->sub[0];
            }
        }
    }

    if (stuck != 0) {
        if (hit & 0x80) {
            p->flags |= 0x80;
        }
        if (dir < 0) {
            p->flags |= 0x20;
        } else if (dir > 0) {
            p->flags |= 0x10;
        }
    }

    p->move[0] = 0;
    if (!(p->pose & 0x40) || (surface & 0x10)) {
        return;
    }
    if (dir == 0 || !(start_flags & ON_GROUND)) {
        if ((player_last_flags & 1) || !(p->flags & ON_GROUND)) {
            return;
        }
    }

    {
        s16 *box = scratch_alloc(0xC); /* x0 x1 y0 y1 z0 z1 */
        s32 x = p->sub[0] >> 12;
        s32 y = p->sub[1] >> 12;
        s32 z = p->sub[2] >> 12;

        box[0] = x - PLAYER_HALF(p)[0];
        box[2] = y - PLAYER_HALF(p)[1];
        box[4] = z - PLAYER_HALF(p)[2];
        box[1] = PLAYER_HALF(p)[0] + x;
        box[3] = y;
        box[5] = PLAYER_HALF(p)[2] + z;
        box[3] += 0x30 + (s16)PLAYER_HALF(p)[0] * 2;
        zone_query_box(work_area_ptr->packet, box);
        scratch_top -= 0xC;
    }
    spans = &p->x_max;
    packet_spans_at_height(p->sub[1] >> 12, spans);
    player_step_vertical(p, 0);

    flags = p->flags;
    if (!(flags & ON_GROUND)) {
        if (dir < 0) {
            p->flags = flags | 0x800;
        } else if (dir > 0) {
            p->flags = flags | 0x400;
        }
        return;
    }
    if (stuck != 0 || (flags & 0xF000)) {
        return;
    }
    {
        s32 range[2]; /* the zone's x range */
        s32 edge;
        s32 bound;
        s32 x;
        s32 half_y, half_x, half_y2;
        u16 *half = PLAYER_HALF(p);
        WorkArea *wa;
        RotMatrix *saved; /* saved[0]: the frame; saved[1]: the turn */
        register RotMatrix *frame asm("$5");

        zone_x_range((EdgeQuery *)p, &range[0], &range[1]);
        x = p->sub[0] >> 12;
        edge = range[1];
        if (edge + 0x20 < x) {
            p->sub[0] += (edge + 1 - x + (half_y2 = (half_y = (s16)half[1]) / 2)) << 12;
            half_x = (s16)half[0];
            p->sub[1] += half_x << 12;
            do { } while (0);
            wa = work_area_ptr;
            half[0] = half_y2;
            half[1] = half_x * 2;
            player_column_query(p, wa->packet);
            packet_spans_at_height(p->sub[1] >> 12, spans);
            half[0] = half_x;
            half[1] = half_y;
            if ((p->sub[1] >> 12) < p->y_max && p->y_min < (p->sub[1] >> 12) - half_x * 2) {
                s32 climb, room;
                s32 turn;

                saved = (RotMatrix *)scratch_top;
                bound = range[1];
                climb = x - bound + 1;
                scratch_top += 0x40;
                frame = saved;
                room = p->y_max - (p->sub[1] >> 12) - 1;
                if (room < climb) {
                    climb = room;
                }
                p->sub[1] += climb << 12;
                p->sub[0] -= half_y2 << 12;
                p->sub[1] -= half_x << 12;
                /* Hides frame == saved from cse, which would store the first word through saved. */
                __asm__("" : "=r"(frame) : "0"(frame));
                rot_matrix_save(frame);
                turn = rcossin_tbl[0xC00];
                saved[1].m[0][2] = 0;
                saved[1].m[1][2] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = 0;
                saved[1].m[2][2] = 0x1000;
                saved[1].m[0][0] = (u32)turn >> 16;
                saved[1].m[0][1] = -turn;
                saved[1].m[1][0] = turn;
                saved[1].m[1][1] = (u32)turn >> 16;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                scratch_top -= 0x40;
            } else {
                p->sub[0] -= (range[1] + 1 - x + half_y / 2) << 12;
                p->sub[1] -= half_x << 12;
            }
        } else if (edge = range[0], x < edge - 0x20) {
            half_y = (s16)half[1];
            half_x = (s16)half[0];
            p->sub[0] += (edge - 1 - x - half_y / 2) << 12;
            p->sub[1] += half_x << 12;
            do { } while (0);
            wa = work_area_ptr;
            half[0] = half_y / 2;
            half[1] = half_x * 2;
            player_column_query(p, wa->packet);
            packet_spans_at_height(p->sub[1] >> 12, spans);
            half[0] = half_x;
            half[1] = half_y;
            if ((p->sub[1] >> 12) < p->y_max && p->y_min < (p->sub[1] >> 12) - half_x * 2) {
                s32 climb, room;
                s32 turn;

                saved = (RotMatrix *)scratch_top;
                bound = range[0];
                climb = bound - x + 1;
                scratch_top += 0x40;
                frame = saved;
                room = p->y_max - (p->sub[1] >> 12) - 1;
                if (room < climb) {
                    climb = room;
                }
                p->sub[1] += climb << 12;
                p->sub[0] -= ((-half_y) / 2) << 12;
                p->sub[1] -= half_x << 12;
                __asm__("" : "=r"(frame) : "0"(frame));
                rot_matrix_save(frame);
                turn = rcossin_tbl[0x400];
                saved[1].m[0][2] = 0;
                saved[1].m[1][2] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = 0;
                saved[1].m[2][2] = 0x1000;
                saved[1].m[0][0] = (u32)turn >> 16;
                saved[1].m[0][1] = -turn;
                saved[1].m[1][0] = turn;
                saved[1].m[1][1] = (u32)turn >> 16;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                scratch_top -= 0x40;
            } else {
                p->sub[0] -= (range[0] - 1 - x - half_y / 2) << 12;
                p->sub[1] -= half_x << 12;
            }
        }
    }
}

void player_slope_push(PlayerObj *p) {
    s32 x, y, z, ang, trx, trz;
    s32 *v;
    SlopeRec *rec;
    s16 *tri; /* triangle normal x, y, z */
    u32 surf;
    u32 ground;

    if ((p->pose & 0x10) && (p->flags & 1)) {
        v = scratch_alloc(0x10);
        ground = p->ground;
        surf = ground_slope_lookup(ground, v);
        rec = (SlopeRec *)((u8 *)slope_table_ptr + ((surf & 0xF000) >> 8));
        tri = (s16 *)(((GroundTileEntry *)&ground_tile_table)[v[3]].tris + ((ground & 0xFF) * 12 + 4));
        x = rec->x;
        y = rec->y;
        z = rec->z;
        switch (rec->kind) {
        case 1:
            if (tri[1] == 0 || ABS(tri[1]) == 0x4000) {
                z = 0;
                x = 0;
                y = 0;
                break;
            }
            ang = atan2(tri[2], tri[0]);
            if (tri[1] > 0) {
                ang += 0x800;
            }
            goto rot;
        case 2:
            gte_get_ctrl(TRX, trx);
            gte_get_ctrl(TRZ, trz);
            ang = atan2(trz - v[2], trx - v[0]);
rot:
            ang &= 0xFFF;
            do {
                z = z * (cos_table[ang].value / 4) / 1024;
                x = x * (*(s16 *)&rcossin_tbl[ang] / 4) / 1024;
            } while (0);
            y = 0;
            break;
        }
        if (surf & 0x20) {
            if (tri[1] > 0) {
                y += tri[1] * 4;
                x -= tri[0] * 4;
                z -= tri[2] * 4;
            } else if (tri[1] < 0) {
                y -= tri[1] * 4;
                x += tri[0] * 4;
                z += tri[2] * 4;
            } else {
                y += 0x10000;
            }
        }
        v[0] = x;
        v[1] = y;
        v[2] = z;
        xform_fixed_point(v, v);
        p->move[0] += v[0];
        p->move[2] += v[2];
        scratch_top -= 0x10;
    }
}

s32 player_zone_probe(PlayerObj *p, s32 dir, s32 *out) {
    ZoneTableY *zones;
    ZonePointY *points;
    s32 i, count, found, px, pz;
    s32 maxy, miny, minz;
    s32 end_y, end_z;

    out[0] = p->sub[0] >> 12;
    out[1] = p->sub[1] >> 12;
    out[2] = p->sub[2] >> 12;
    if (surface_of(p->ground) & 0x10) {
        return 0;
    }
    zones = work_area_ptr->packet;
    count = zones->point_count;
    found = 0;
    if (count == 0) {
        return 0;
    }
    pz = p->sub[1] >> 12;
    points = zones->points;
    if (dir != 0) {
        minz = pz;
        found = 1;
        miny = (p->sub[2] >> 12) + dir * (s16)p->unk_1C;
        maxy = miny;
    }
    for (i = 0; i < count; i++) {
        s32 ez = points[i].z;
        if (ez >= pz) {
            if (found == 0 || ez < minz) {
                miny = points[i].y;
                minz = ez;
                found++;
                maxy = miny;
            } else if (ez == minz) {
                s32 ey = points[i].y;
                if (ey < miny) {
                    miny = ey;
                } else if (maxy < ey) {
                    maxy = ey;
                }
            }
        }
    }
    if (found == 0) {
        return 0;
    }
    if (pz < minz - 0x30) {
        return 0;
    }
    px = p->sub[2] >> 12;
    if (px + 0x30 < miny) {
        gte_set(SXY0, (minz << 16) | (miny & 0xFFFF));
        end_y = miny;
        end_z = minz + 0x30;
        gte_set(SXY2, (end_z << 16) | (miny & 0xFFFF));
        for (i = 0; i < count; i++) {
            px = points[i].y;
            pz = points[i].z;
            if (px < miny && pz >= minz) {
                s32 w = pz << 16;
                s32 r;

                w |= px & 0xFFFF;
                gte_set(SXY1, w);
                gte_nclip();
                gte_get(MAC0, r);
                gte_nop();
                if (r < 0) {
                    gte_set(SXY2, w);
                    end_y = px;
                    end_z = pz;
                }
            }
        }
        end_y = miny - (end_y - miny);
        end_z = minz - (end_z - minz);
    } else {
        if (maxy >= px - 0x30) {
            goto fail;
        }
        miny = maxy;
        gte_set(SXY0, (minz << 16) | (miny & 0xFFFF));
        end_y = miny;
        end_z = minz + 0x30;
        gte_set(SXY2, (end_z << 16) | (miny & 0xFFFF));
        for (i = 0; i < count; i++) {
            px = points[i].y;
            pz = points[i].z;
            if (miny < px && pz >= minz) {
                s32 w = pz << 16;
                s32 r;

                w |= px & 0xFFFF;
                gte_set(SXY1, w);
                gte_nclip();
                gte_get(MAC0, r);
                gte_nop();
                if (r > 0) {
                    gte_set(SXY2, w);
                    end_y = px;
                    end_z = pz;
                }
            }
        }
    }
    out[2] = miny;
    out[1] = minz;
    return (atan2(end_y - miny, end_z - minz) << 20) >> 20;
fail:
    return 0;
}

s32 player_edge_angle(PlayerObj *p, s32 dir, s32 *out) {
    ZoneTable *zones;
    ZonePoint *points;
    s32 i, count, found, px, py;
    s32 maxx, minx, miny;
    s32 end_x, end_y;

    out[0] = p->sub[0] >> 12;
    out[1] = p->sub[1] >> 12;
    out[2] = p->sub[2] >> 12;
    if (surface_of(p->ground) & 0x10) {
        return 0;
    }
    zones = work_area_ptr->packet;
    count = zones->point_count;
    found = 0;
    if (count == 0) {
        return 0;
    }
    py = p->sub[1] >> 12;
    points = zones->points;
    if (dir != 0) {
        miny = py;
        found = 1;
        minx = (p->sub[0] >> 12) + dir * (s16)p->x18;
        maxx = minx;
    }
    for (i = 0; i < count; i++) {
        s32 ey = points[i].z;
        if (ey >= py) {
            if (found == 0 || ey < miny) {
                minx = points[i].x;
                miny = ey;
                found++;
                maxx = minx;
            } else if (ey == miny) {
                s32 ex = points[i].x;
                if (ex < minx) {
                    minx = ex;
                } else if (maxx < ex) {
                    maxx = ex;
                }
            }
        }
    }
    if (found == 0) {
        return 0;
    }
    if (py < miny - 0x30) {
        return 0;
    }
    px = p->sub[0] >> 12;
    if (px + 0x30 < minx) {
        gte_set(SXY0, (miny << 16) | (minx & 0xFFFF));
        end_x = minx;
        end_y = miny + 0x30;
        gte_set(SXY2, (end_y << 16) | (minx & 0xFFFF));
        for (i = 0; i < count; i++) {
            px = points[i].x;
            py = points[i].z;
            if (px < minx && py >= miny) {
                s32 w = py << 16;
                s32 r;

                w |= px & 0xFFFF;
                gte_set(SXY1, w);
                gte_nclip();
                gte_get(MAC0, r);
                gte_nop();
                if (r < 0) {
                    gte_set(SXY2, w);
                    end_x = px;
                    end_y = py;
                    if (end_y == miny) {
                        break;
                    }
                }
            }
        }
        end_x = minx - (end_x - minx);
        end_y = miny - (end_y - miny);
    } else {
        if (maxx >= px - 0x30) {
            goto fail;
        }
        minx = maxx;
        gte_set(SXY0, (miny << 16) | (minx & 0xFFFF));
        end_x = minx;
        end_y = miny + 0x30;
        gte_set(SXY2, (end_y << 16) | (minx & 0xFFFF));
        for (i = 0; i < count; i++) {
            px = points[i].x;
            py = points[i].z;
            if (minx < px && py >= miny) {
                s32 w = py << 16;
                s32 r;

                w |= px & 0xFFFF;
                gte_set(SXY1, w);
                gte_nclip();
                gte_get(MAC0, r);
                gte_nop();
                if (r > 0) {
                    gte_set(SXY2, w);
                    end_x = px;
                    end_y = py;
                    if (end_y == miny) {
                        break;
                    }
                }
            }
        }
    }
    out[0] = minx;
    out[1] = miny;
    return (-atan2(end_x - minx, end_y - miny) << 20) >> 20;
fail:
    return 0;
}

static inline void gte_read_rot(RotMatrix *m) {
    register s32 *dst asm("$2");
    register s32 r4 asm("$4");
    register s32 r5 asm("$5");
    register s32 r3 asm("$3");

    __asm__("" : "=r"(dst) : "0"(m));
    gte_get_ctrl(R11R12, r4);
    gte_get_ctrl(R13R21, r5);
    gte_get_ctrl(R22R23, r3);
    dst[0] = r4;
    dst[1] = r5;
    dst[2] = r3;
    gte_get_ctrl(R31R32, r4);
    gte_get_ctrl(R33, r5);
    dst[3] = r4;
    dst[4] = r5;
}
static inline void gte_write_rot(RotMatrix *m) {
    s32 *src;
    register s32 r4 asm("$4");
    register s32 r5 asm("$5");
    register s32 r3 asm("$3");

    __asm__("" : "=r"(src) : "0"(m));
    r4 = src[0];
    r5 = src[1];
    r3 = src[2];
    gte_set_ctrl(R11R12, r4);
    gte_set_ctrl(R13R21, r5);
    gte_set_ctrl(R22R23, r3);
    r4 = src[3];
    r5 = src[4];
    gte_set_ctrl(R31R32, r4);
    gte_set_ctrl(R33, r5);
}
static inline s32 angle_wrap(s32 angle) {
    return (angle << 20) >> 20;
}
void player_tilt_to_ground(PlayerObj *p) {
    s32 ang[3];
    s32 *v;
    RotMatrix *m;
    RotMatrix *cur;
    RotMatrix *mat;
    RotMatrix *src;
    u32 flags;
    s32 dir;
    s32 a, b, c, step;
    register s32 r3 asm("$3");
    register s32 r4 asm("$4");
    register s32 r2 asm("$2");

    *(PlayerPosWords *)p->pos = *(PlayerPosWords *)p->sub;
    if (!(p->pose & 0x20)) {
        return;
    }
    m = (RotMatrix *)scratch_alloc(0x80);
    v = (s32 *)scratch_alloc(0x20);
    ang[2] = 0;
    ang[1] = 0;
    flags = p->flags;
    if (flags & 1) {
        dir = 0;
        if (flags & 0x1000) {
            dir = 1;
        } else if (flags & 0x2000) {
            dir = -1;
        }
        ang[1] = player_zone_probe(p, dir, v);
        if (ang[1] == 0) {
            u32 flags2 = p->flags;

            dir = 0;
            if (flags2 & 0x4000) {
                dir = 1;
            } else if (flags2 & 0x8000) {
                dir = -1;
            }
            ang[2] = player_edge_angle(p, dir, v);
        }
    }
    gte_read_rot(&m[3]);
    gte_get_ctrl(R11R12, r3);
    gte_get_ctrl(R13R21, r4);
    gte_get_ctrl(R22R23, r2);
    ((RotMatrixWords *)m)->words[0] = r3;
    ((RotMatrixWords *)m)->words[1] = r4;
    ((RotMatrixWords *)m)->words[2] = r2;
    gte_get_ctrl(R31R32, r3);
    gte_get_ctrl(R33, r4);
    ((RotMatrixWords *)m)->words[3] = r3;
    ((RotMatrixWords *)m)->words[4] = r4;
    mat = &m[1];
    if (ang[1] != 0 || ang[2] != 0) {
        rot_matrix_b(mat, 0, ang[1], ang[2]);
        mul_matrix(mat, m, m);
        __asm__("" : "=r"(mat) : "0"(mat)); /* the loads go through mat, not m + 0x20 */
        r3 = ((RotMatrixWords *)mat)->words[0];
        r4 = ((RotMatrixWords *)mat)->words[1];
        r2 = ((RotMatrixWords *)mat)->words[2];
        gte_set_ctrl(R11R12, r3);
        gte_set_ctrl(R13R21, r4);
        gte_set_ctrl(R22R23, r2);
        r3 = ((RotMatrixWords *)mat)->words[3];
        r4 = ((RotMatrixWords *)mat)->words[4];
        gte_set_ctrl(R31R32, r3);
        gte_set_ctrl(R33, r4);
        v[0] -= p->pos[0] >> 12;
        v[1] -= p->pos[1] >> 12;
        v[2] -= p->pos[2] >> 12;
        p->pos[0] += v[0] << 12;
        p->pos[1] += v[1] << 12;
        p->pos[2] += v[2] << 12;
        xform_fixed_point(v, v);
        p->pos[0] -= v[0] << 12;
        p->pos[1] += v[1] << 12;
        p->pos[2] -= v[2] << 12;
        __asm__ volatile(""); /* keeps the reset below after the pos updates */
        mat = &m[1];
    }
    rot_matrix_b(mat, p->rot[1], p->rot[0], p->rot[2]);
    src = mat;
    mat = &m[2];
    transpose_matrix(src, mat);
    mul_matrix(m, mat, mat);
    if (p->flags & 1) {
        rot_matrix_to_angles(mat, &ang[0], &ang[1], &ang[2]);
    } else {
        const RotMatrix *rel = &m[2];

        ang[1] = -atan2(m[2].m[1][1], -m[2].m[2][1]);
        ang[2] = atan2(rel->m[1][1], -rel->m[0][1]);
        ang[0] = 0;
    }
    a = ABS(angle_wrap(ang[0]));
    b = ABS(angle_wrap(ang[1]));
    c = ABS(angle_wrap(ang[2]));
    if (a < 4 && b < 4 && c < 4) {
        cur = m;
    } else {
        step = b / 10;
        ang[1] = angle_approach(0, ang[1], step < 16 ? 16 : step);
        step = c / 10;
        ang[2] = angle_approach(0, ang[2], step < 16 ? 16 : step);
        step = a / 10;
        ang[0] = angle_approach(0, ang[0], step < 16 ? 16 : step);
        rot_matrix_b(&m[2], ang[0], ang[1], ang[2]);
        mul_matrix(&m[2], &m[1], &m[1]);
        cur = &m[1];
    }
    rot_matrix_to_angles(cur, &ang[0], &ang[1], &ang[2]);
    p->rot[0] = *(u16 *)&ang[1];
    p->rot[1] = *(u16 *)&ang[0];
    p->rot[2] = *(u16 *)&ang[2];
    gte_write_rot(&m[3]);
    scratch_top -= 0xA0;
}

void player_gte_load_pose(PlayerObj *p) {
    volatile s32 *m = scratch_alloc(0x40);
    s32 *sub;
    s32 x, y, z;

    rot_matrix_b((void *)m, p->angle[1], p->angle[0], p->angle[2]);
    {
        s32 r0, r1, r2;
        r0 = m[0];
        r1 = m[1];
        r2 = m[2];
        gte_set_ctrl(R11R12, r0);
        gte_set_ctrl(R13R21, r1);
        gte_set_ctrl(R22R23, r2);
        r0 = m[3];
        r1 = m[4];
        gte_set_ctrl(R31R32, r0);
        gte_set_ctrl(R33, r1);
    }
    scratch_top -= 0x40;
    sub = p->sub;
    x = ((volatile s32 *)sub)[0] >> 12;
    y = ((volatile s32 *)sub)[1] >> 12;
    z = ((volatile s32 *)sub)[2] >> 12;
    gte_set_ctrl(TRX, x);
    gte_set_ctrl(TRY, y);
    gte_set_ctrl(TRZ, z);
    p->sub[0] -= x << 12;
    p->sub[1] -= y << 12;
    p->sub[2] -= z << 12;
    xform_fixed_point(sub, sub);
}

static inline void gte_rot_save(s32 *m) {
    register s32 a asm("$4");
    register s32 b asm("$5");
    register s32 c asm("$3");
    do {
    } while (0);
    gte_get_ctrl(R11R12, a);
    gte_get_ctrl(R13R21, b);
    gte_get_ctrl(R22R23, c);
    m[0] = a;
    m[1] = b;
    m[2] = c;
    gte_get_ctrl(R31R32, a);
    gte_get_ctrl(R33, b);
    m[3] = a;
    m[4] = b;
    do {
    } while (0);
}
static inline void gte_rot_restore(s32 *m) {
    s32 a, b, c;

    gte_load_R012(m, a, b, c);
    gte_load_R34(m, a, b);
}
/* Re-bases the player on the current GTE frame: reads the rotation back as angles,
 * then applies its inverse plus the translation to the player's points. */
void player_gte_store_pose(PlayerObj *p) {
    register s32 *m asm("$16");
    s32 ax, ay, az;
    s32 tx, ty, tz;
    s32 sx, sy, sz;

    m = (s32 *)scratch_top;
    scratch_top += 0x40;
    gte_rot_save(m);
    rot_matrix_to_angles((RotMatrix *)m, &ax, &ay, &az);
    p->angle[0] = *(u16 *)&ay;
    p->angle[1] = *(u16 *)&ax;
    p->angle[2] = *(u16 *)&az;
    if (!(p->pose & 0x20)) {
        p->rot[0] = *(u16 *)&ay;
        p->rot[1] = *(u16 *)&ax;
        p->rot[2] = *(u16 *)&az;
    }
    transpose_matrix(m, m + 8);
    gte_rot_restore(m + 8);
    gte_get_ctrl(TRX, tx);
    gte_get_ctrl(TRY, ty);
    gte_get_ctrl(TRZ, tz);
    xform_fixed_point(p->sub, p->sub);
    sx = tx << 12;
    sy = ty << 12;
    sz = tz << 12;
    p->sub[0] += sx;
    p->sub[1] += sy;
    p->sub[2] += sz;
    xform_fixed_point(&p->x_max, &p->x_max);
    p->x_max += tx;
    p->y_max += ty;
    p->unk_60 += tz;
    xform_fixed_point(&p->x_min, &p->x_min);
    p->x_min += tx;
    p->y_min += ty;
    p->unk_70 += tz;
    xform_fixed_point(p->pos, p->pos);
    scratch_top -= 0x40;
    p->pos[0] += sx;
    p->pos[1] += sy;
    p->pos[2] += sz;
}

/*
 * Turns the player's rotation delta into the GTE rotation: saves the current
 * GTE rotation in scratch, loads the delta (a packed cos/sin pair, one of two
 * table entries picked by flags), advances the player's y and z, transforms
 * the three points, then composes delta * current into the GTE.
 * Pass 1 flips the 0x3000 flags (the other half of the frame).
 */
void player_apply_rotation(PlayerObj *p, s32 pass) {
    u32 flags = p->flags;
    s32 *cur_mtx;
    s16 *delta16;
    volatile s32 *delta;
    volatile s32 *combined;
    register s32 mx0 asm("$3");
    register s32 mx1 asm("$4");
    register s32 mx2 asm("$2");
    register s32 mx3 asm("$3");
    register s32 mx4 asm("$4");
    s32 shift_a, shift_b;
    u32 sincos, cos_hi;
    s32 neg_sin;
    s32 new_z;
    s32 half_b;
    s32 step_y;
    s32 cur_y;

    if (flags & 0x3000) {
        if (pass != 0) {
            flags ^= 0x3000;
        }
        /* save the current GTE rotation (5 words of ctrl) */
        cur_mtx = scratch_alloc(0x40);
        gte_get_ctrl(R11R12, mx0);
        gte_get_ctrl(R13R21, mx1);
        gte_get_ctrl(R22R23, mx2);
        cur_mtx[0] = mx0;
        cur_mtx[1] = mx1;
        cur_mtx[2] = mx2;
        gte_get_ctrl(R31R32, mx3);
        gte_get_ctrl(R33, mx4);
        cur_mtx[3] = mx3;
        cur_mtx[4] = mx4;
        do { } while (0);
        __asm__("" : "=r"(flags) : "0"(flags));
        shift_a = *(s16 *)((u8 *)&p->x18 + 2);
        shift_b = *(s16 *)&p->unk_1C;
        if (flags & 0x1000) {
            sincos = sincos_deg270[0];
            cos_hi = sincos >> 16;
            neg_sin = -sincos;
            new_z = p->sub[2] + ((shift_b + 1) << 12);
            goto set;
        }
        if (flags & 0x2000) {
            sincos = sincos_deg90[0];
            cos_hi = sincos >> 16;
            neg_sin = -sincos;
            new_z = p->sub[2] - ((shift_b + 1) << 12);
set:
            p->sub[2] = new_z;
            /* delta matrix at cur_mtx + 0x20: diag(1, c, c), sin in the off-diagonals */
            delta16 = (s16 *)(cur_mtx + 8);
            delta16[0] = 0x1000;
            delta16[1] = 0;
            delta16[2] = 0;
            delta16[3] = 0;
            delta16[4] = cos_hi;
            delta16[5] = neg_sin;
            delta16[6] = 0;
            delta16[7] = sincos;
            delta16[8] = cos_hi;
        }
        half_b = shift_a / 2;
        *(s16 *)&p->unk_1C = half_b;
        step_y = (half_b + 1) << 12;
        *(s16 *)((u8 *)&p->x18 + 2) = shift_b * 2;
        do { } while (0);
        cur_y = p->sub[1];
        delta = cur_mtx + 8;
        p->sub[1] = cur_y - step_y;
        __asm__("" : "=r"(delta) : "0"(delta));
        mx0 = delta[0];
        mx1 = delta[1];
        mx2 = delta[2];
        gte_set_ctrl(R11R12, mx0);
        gte_set_ctrl(R13R21, mx1);
        gte_set_ctrl(R22R23, mx2);
        mx3 = delta[3];
        mx4 = delta[4];
        gte_set_ctrl(R31R32, mx3);
        gte_set_ctrl(R33, mx4);
        xform_fixed_point(p->sub, p->sub);
        xform_fixed_point(&p->x_max, &p->x_max);
        xform_fixed_point(&p->x_min, &p->x_min);
        mul_matrix(delta, cur_mtx, cur_mtx);
        combined = cur_mtx;
        mx0 = combined[0];
        mx1 = combined[1];
        mx2 = combined[2];
        gte_set_ctrl(R11R12, mx0);
        gte_set_ctrl(R13R21, mx1);
        gte_set_ctrl(R22R23, mx2);
        mx3 = combined[3];
        mx4 = combined[4];
        gte_set_ctrl(R31R32, mx3);
        gte_set_ctrl(R33, mx4);
        scratch_top -= 0x40;
    }
}

/*
 * Applies a quarter-turn rotation about the player's y axis: builds the delta
 * matrix from the sin/cos table entry picked by flags 0x4000 / 0x8000 (pass 1
 * flips them), advances x, halves the 0x1A half-extent into 0x18 and doubles
 * 0x18 into 0x1A, lowers y, transforms the three points, then composes
 * delta * current into the GTE.
 */
void player_quarter_turn(PlayerObj *p, s32 pass) {
    u32 flags = p->flags;
    s32 *cur_mtx;
    s16 *delta16;
    s32 *delta;
    register s32 mx0 asm("$3");
    register s32 mx1 asm("$4");
    register s32 mx2 asm("$2");
    register s32 neg_sin asm("$5");
    register s32 cos_hi asm("$6");
    u32 sincos;
    s32 size_b;
    s32 size_a;
    s32 half_b;
    s32 new_x;

    if (flags & 0xC000) {
        if (pass != 0) {
            flags ^= 0xC000;
        }
        /* save the current GTE rotation (5 words of ctrl) */
        cur_mtx = scratch_alloc(0x40);
        gte_get_ctrl(R11R12, mx0);
        gte_get_ctrl(R13R21, mx1);
        gte_get_ctrl(R22R23, mx2);
        cur_mtx[0] = mx0;
        cur_mtx[1] = mx1;
        cur_mtx[2] = mx2;
        gte_get_ctrl(R31R32, mx0);
        gte_get_ctrl(R33, mx1);
        cur_mtx[3] = mx0;
        cur_mtx[4] = mx1;
        do { } while (0);
        __asm__("" : "=r"(flags) : "0"(flags));
        size_b = ((s16 *)&p->x18)[1];
        size_a = *(s16 *)&p->x18;
        if (flags & 0x4000) {
            sincos = sincos_deg90[0];
            cos_hi = sincos >> 16;
            neg_sin = -sincos;
            new_x = p->sub[0] + ((size_a + 1) << 12);
            goto set;
        }
        if (flags & 0x8000) {
            sincos = sincos_deg270[0];
            cos_hi = sincos >> 16;
            neg_sin = -sincos;
            new_x = p->sub[0] - ((size_a + 1) << 12);
set:
            p->sub[0] = new_x;
            /* delta matrix at cur_mtx + 0x20: rotation about y */
            delta16 = (s16 *)(cur_mtx + 8);
            delta16[0] = cos_hi;
            delta16[1] = neg_sin;
            delta16[2] = 0;
            delta16[3] = sincos;
            delta16[4] = cos_hi;
            delta16[5] = 0;
            delta16[6] = 0;
            delta16[7] = 0;
            delta16[8] = 0x1000;
        }
        half_b = size_b / 2;
        *(s16 *)&p->x18 = half_b;
        ((s16 *)&p->x18)[1] = size_a * 2;
        p->sub[1] -= (half_b + 1) << 12;
        delta = cur_mtx + 8;
        gte_set_R012(mx0, mx1, mx2, delta[0], delta[1], delta[2]);
        gte_set_R34(mx0, mx1, delta[3], delta[4]);
        xform_fixed_point(p->sub, p->sub);
        xform_fixed_point(&p->x_max, &p->x_max);
        xform_fixed_point(&p->x_min, &p->x_min);
        mul_matrix(delta, cur_mtx, cur_mtx);
        gte_set_R012(mx0, mx1, mx2, cur_mtx[0], cur_mtx[1], cur_mtx[2]);
        gte_set_R34(mx0, mx1, cur_mtx[3], cur_mtx[4]);
        scratch_top -= 0x40;
    }
}

void obj_set_contact_flags(ObjContactState *obj) {
    s32 gte_flag;
    s32 flags;

    gte_get_ctrl(R22R23, gte_flag);
    flags = obj->flags;
    gte_flag &= 0xFFFF;
    if (!(flags & 0x40) && ((obj->mode & 0x80) || gte_flag != 0x1000)) {
        if (flags & 4) {
            obj->flags = flags | 0x1000;
            return;
        }
        if (flags & 8) {
            obj->flags = flags | 0x2000;
            return;
        }
        flags = ((volatile ObjContactState *)obj)->flags;
    }
    if (!(flags & 0x80) && ((obj->mode & 0x80) || gte_flag != 0x1000)) {
        if (flags & 0x10) {
            obj->flags = flags | 0x4000;
        } else if (flags & 0x20) {
            obj->flags = flags | 0x8000;
        }
    }
}

static inline s16 *player_half(PlayerObj *p) {
    return (s16 *)&p->x18;
}
/* Wall climbing (pose bit 0x40): when the player crosses an edge of the surface it stands on
 * (flags 0x1000/0x2000: z edges, 0x4000/0x8000: x edges; 0x100..0x800 the edge it steps over), it
 * moves around the edge and turns its frame (the GTE rotation matrix, saved at the top) a quarter
 * turn about x or z. Otherwise, on the ground, it levels the frame to the surface (atan2 of the
 * matrix) or sets the contact flags. `value` is one local for the headroom, the sin/cos word, the
 * angle and a GTE word: reusing it gives the original's registers. */
void player_wall_climb_frame(PlayerObj *p) {
    RotMatrix *saved; /* saved[0]: the frame; saved[1]: the turn applied to it */
    s32 *offset;
    s32 surface;
    u32 flags;
    s32 value;
    s32 size;
    s32 turn_sc, turn_cos, turn_nsin;
    s32 tilt_cos;
    s32 tilt_nsin;
    s32 turned;
    s32 m0, m1, m2;
    s32 *frame_words;

    if (!(p->pose & 0x40)) {
        return;
    }
    surface = surface_of(p->ground);
    player_column_query(p, work_area_ptr->packet);
    packet_spans_at_height(p->sub[1] >> 12, &p->x_max);
    saved = scratch_alloc(0x40);
    frame_words = (s32 *)saved;
    offset = scratch_alloc(0x10);
    gte_get_ctrl(R11R12, m0);
    gte_get_ctrl(R13R21, m1);
    gte_get_ctrl(R22R23, m2);
    frame_words[0] = m0;
    frame_words[1] = m1;
    frame_words[2] = m2;
    gte_get_ctrl(R31R32, m0);
    gte_get_ctrl(R33, m1);
    frame_words[3] = m0;
    frame_words[4] = m1;

    flags = p->flags;
    if (flags & 0x1000) {
        if (flags & 8) {
            p->flags = (flags & ~0x1000) | ON_GROUND;
        } else if (flags & ON_GROUND) {
            s32 extra = 0;
            if (flags & 4) {
                extra = player_half(p)[1];
            }
            value = p->y_max - (p->sub[1] >> 12) + extra;
            if (player_half(p)[2] * 2 < value) {
                if (surface & 0x10) {
                    u32 cleared = flags & ~0x1000;

                    p->flags = cleared & ~ON_GROUND;
                    goto settle;
                }
                value = rcossin_tbl[0xC00];
                p->sub[2] += (player_half(p)[2] + 1) << 12;
                p->sub[1] += (player_half(p)[2] - extra) << 12;
                tilt_cos = (u32)value >> 16;
                tilt_nsin = -value;
                saved[1].m[0][0] = 0x1000;
                saved[1].m[0][1] = 0;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = 0;
                saved[1].m[1][1] = tilt_cos;
                saved[1].m[1][2] = tilt_nsin;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = value;
                saved[1].m[2][2] = tilt_cos;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                p->flags &= ~0x1000;
            } else if (flags & 0x20) {
                p->flags = (flags & ~0x1000) | 0x8000;
            } else if (flags & 0x10) {
                p->flags = (flags & ~0x1000) | 0x4000;
            }
        } else {
            p->flags = flags & ~0x1000;
            if (flags & 0x100) {
                p->sub[2] += 0x1000;
                p->flags |= ON_GROUND;
            } else if (flags & 0x400) {
                p->sub[2] += 0x1000;
                goto step_400;
            } else if (flags & 0x800) {
                p->sub[2] += 0x1000;
                goto step_800;
            } else {
                goto settle;
            }
        }
    } else if (flags & 0x2000) {
        if (flags & 4) {
            p->flags = (flags & ~0x2000) | ON_GROUND;
        } else if (flags & ON_GROUND) {
            s32 extra = 0;
            if (flags & 8) {
                extra = player_half(p)[1];
            }
            value = p->y_max - (p->sub[1] >> 12) + extra;
            if (player_half(p)[2] * 2 < value) {
                if (surface & 0x10) {
                    u32 cleared = flags & ~0x2000;

                    p->flags = cleared & ~ON_GROUND;
                    goto settle;
                }
                value = rcossin_tbl[0x400];
                p->sub[2] -= (player_half(p)[2] + 1) << 12;
                p->sub[1] += (player_half(p)[2] - extra) << 12;
                tilt_cos = (u32)value >> 16;
                tilt_nsin = -value;
                saved[1].m[0][0] = 0x1000;
                saved[1].m[0][1] = 0;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = 0;
                saved[1].m[1][1] = tilt_cos;
                saved[1].m[1][2] = tilt_nsin;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = value;
                saved[1].m[2][2] = tilt_cos;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                p->flags &= ~0x2000;
            } else if (flags & 0x20) {
                p->flags = (flags & ~0x2000) | 0x8000;
            } else if (flags & 0x10) {
                p->flags = (flags & ~0x2000) | 0x4000;
            }
        } else {
            p->flags = flags & ~0x2000;
            if (flags & 0x200) {
                p->sub[2] -= 0x1000;
                p->flags |= ON_GROUND;
            } else if (flags & 0x400) {
                p->sub[2] -= 0x1000;
                goto step_400;
            } else if (flags & 0x800) {
                p->sub[2] -= 0x1000;
                goto step_800;
            } else {
                goto settle;
            }
        }
    } else if (flags & 0x4000) {
        if (flags & 0x20) {
            p->flags = (flags & ~0x4000) | ON_GROUND;
        } else if (flags & ON_GROUND) {
            s32 extra = 0;
            if (flags & 0x10) {
                extra = player_half(p)[1];
            }
            value = p->y_max - (p->sub[1] >> 12) + extra;
            if (player_half(p)[0] * 2 < value) {
                if (surface & 0x10) {
                    u32 cleared = flags & ~0x4000;

                    p->flags = cleared & ~ON_GROUND;
                    goto settle;
                }
                value = rcossin_tbl[0x400];
                p->sub[0] += (player_half(p)[0] + 1) << 12;
                p->sub[1] += (player_half(p)[0] - extra) << 12;
                tilt_cos = (u32)value >> 16;
                tilt_nsin = -value;
                saved[1].m[0][0] = tilt_cos;
                saved[1].m[0][1] = tilt_nsin;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = value;
                saved[1].m[1][1] = tilt_cos;
                saved[1].m[1][2] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = 0;
                saved[1].m[2][2] = 0x1000;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                p->flags &= ~0x4000;
            } else if (flags & 4) {
                p->flags = (flags & ~0x4000) | 0x1000;
            } else if (flags & 8) {
                p->flags = (flags & ~0x4000) | 0x2000;
            }
        } else {
            p->flags = flags & ~0x4000;
            if (flags & 0x400) {
                p->sub[0] += 0x1000;
                p->flags |= ON_GROUND;
            } else if (flags & 0x100) {
                p->sub[0] += 0x1000;
                goto step_100;
            } else if (flags & 0x200) {
                p->sub[0] += 0x1000;
                goto step_200;
            } else {
                goto settle;
            }
        }
    } else if (flags & 0x8000) {
        if (flags & 0x10) {
            p->flags = (flags & ~0x8000) | ON_GROUND;
        } else if (flags & ON_GROUND) {
            s32 extra = 0;
            if (flags & 0x20) {
                extra = player_half(p)[1];
            }
            value = p->y_max - (p->sub[1] >> 12) + extra;
            if (player_half(p)[0] * 2 < value) {
                if (surface & 0x10) {
                    u32 cleared = flags & ~0x8000;

                    p->flags = cleared & ~ON_GROUND;
                    goto settle;
                }
                value = rcossin_tbl[0xC00];
                p->sub[0] -= (player_half(p)[0] + 1) << 12;
                p->sub[1] += (player_half(p)[0] - extra) << 12;
                tilt_cos = (u32)value >> 16;
                tilt_nsin = -value;
                saved[1].m[0][0] = tilt_cos;
                saved[1].m[0][1] = tilt_nsin;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = value;
                saved[1].m[1][1] = tilt_cos;
                saved[1].m[1][2] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = 0;
                saved[1].m[2][2] = 0x1000;
                rot_matrix_load(&saved[1]);
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                p->flags &= ~0x8000;
            } else if (flags & 4) {
                p->flags = (flags & ~0x8000) | 0x1000;
            } else if (flags & 8) {
                p->flags = (flags & ~0x8000) | 0x2000;
            }
        } else {
            p->flags = flags & ~0x8000;
            if (flags & 0x800) {
                p->sub[0] -= 0x1000;
                p->flags |= ON_GROUND;
            } else if (flags & 0x100) {
                p->sub[0] -= 0x1000;
                goto step_100;
            } else if (flags & 0x200) {
                p->sub[0] -= 0x1000;
                goto step_200;
            } else {
                goto settle;
            }
        }
    } else if (flags & 0x100) {
        p->sub[1] += 0x1000;
    step_100:
        value = p->y_max - (p->sub[1] >> 12);
        p->flags |= 0x2001;
        if (player_half(p)[2] * 2 < value) {
            turn_sc = rcossin_tbl[0x400];
            turn_cos = (u32)turn_sc >> 16;
            turn_nsin = -turn_sc;
            p->sub[2] -= (player_half(p)[2] + 1) << 12;
            p->sub[1] += player_half(p)[2] << 12;
            saved[1].m[0][0] = 0x1000;
            saved[1].m[0][1] = 0;
            saved[1].m[0][2] = 0;
            saved[1].m[1][0] = 0;
            saved[1].m[1][1] = turn_cos;
            saved[1].m[1][2] = turn_nsin;
            saved[1].m[2][0] = 0;
            saved[1].m[2][1] = turn_sc;
            saved[1].m[2][2] = turn_cos;
            rot_matrix_load(&saved[1]);
            xform_fixed_point(p->sub, p->sub);
            mul_matrix(&saved[1], saved, saved);
            rot_matrix_load(saved);
            p->flags &= ~0x2000;
        }
    } else if (flags & 0x200) {
        p->sub[1] += 0x1000;
    step_200:
        value = p->y_max - (p->sub[1] >> 12);
        p->flags |= 0x1001;
        if (player_half(p)[2] * 2 < value) {
            turn_sc = rcossin_tbl[0xC00];
            turn_cos = (u32)turn_sc >> 16;
            turn_nsin = -turn_sc;
            p->sub[2] += (player_half(p)[2] + 1) << 12;
            p->sub[1] += player_half(p)[2] << 12;
            saved[1].m[0][0] = 0x1000;
            saved[1].m[0][1] = 0;
            saved[1].m[0][2] = 0;
            saved[1].m[1][0] = 0;
            saved[1].m[1][1] = turn_cos;
            saved[1].m[1][2] = turn_nsin;
            saved[1].m[2][0] = 0;
            saved[1].m[2][1] = turn_sc;
            saved[1].m[2][2] = turn_cos;
            rot_matrix_load(&saved[1]);
            xform_fixed_point(p->sub, p->sub);
            mul_matrix(&saved[1], saved, saved);
            rot_matrix_load(saved);
            p->flags &= ~0x1000;
        }
    } else if (flags & 0x400) {
        p->sub[1] += 0x1000;
    step_400:
        value = p->y_max - (p->sub[1] >> 12);
        p->flags |= 0x8001;
        if (player_half(p)[0] * 2 < value) {
            turn_sc = rcossin_tbl[0xC00];
            turn_cos = (u32)turn_sc >> 16;
            turn_nsin = -turn_sc;
            p->sub[0] -= (player_half(p)[0] + 1) << 12;
            p->sub[1] += player_half(p)[0] << 12;
            saved[1].m[0][0] = turn_cos;
            saved[1].m[0][1] = turn_nsin;
            saved[1].m[0][2] = 0;
            saved[1].m[1][0] = turn_sc;
            saved[1].m[1][1] = turn_cos;
            saved[1].m[1][2] = 0;
            saved[1].m[2][0] = 0;
            saved[1].m[2][1] = 0;
            saved[1].m[2][2] = 0x1000;
            rot_matrix_load(&saved[1]);
            xform_fixed_point(p->sub, p->sub);
            mul_matrix(&saved[1], saved, saved);
            rot_matrix_load(saved);
            p->flags &= ~0x8000;
        }
    } else if (flags & 0x800) {
        p->sub[1] += 0x1000;
    step_800:
        value = p->y_max - (p->sub[1] >> 12);
        p->flags |= 0x4001;
        if (player_half(p)[0] * 2 < value) {
            turn_sc = rcossin_tbl[0x400];
            turn_cos = (u32)turn_sc >> 16;
            turn_nsin = -turn_sc;
            p->sub[0] += (player_half(p)[0] + 1) << 12;
            p->sub[1] += player_half(p)[0] << 12;
            saved[1].m[0][0] = turn_cos;
            saved[1].m[0][1] = turn_nsin;
            saved[1].m[0][2] = 0;
            saved[1].m[1][0] = turn_sc;
            saved[1].m[1][1] = turn_cos;
            saved[1].m[1][2] = 0;
            saved[1].m[2][0] = 0;
            saved[1].m[2][1] = 0;
            saved[1].m[2][2] = 0x1000;
            rot_matrix_load(&saved[1]);
            xform_fixed_point(p->sub, p->sub);
            mul_matrix(&saved[1], saved, saved);
            rot_matrix_load(saved);
            p->flags &= ~0x4000;
        }
    } else if (!(flags & ON_GROUND)) {
    settle:
        turned = 0;
        value = p->y_max - (p->sub[1] >> 12) + player_half(p)[1];
        if (player_half(p)[2] * 2 < value) {
            value = -atan2(saved->m[1][1], -saved->m[0][1]);
            if (value != 0) {
                s32 sc = rcossin_tbl[value & 0xFFF];
                saved[1].m[0][0] = (u32)sc >> 16;
                saved[1].m[0][1] = -sc;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = sc;
                saved[1].m[1][1] = (u32)sc >> 16;
                saved[1].m[1][2] = 0;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = 0;
                saved[1].m[2][2] = 0x1000;
                rot_matrix_load(&saved[1]);
                if (value != 0x800) {
                    offset[0] = 0;
                    offset[1] = player_half(p)[1] - player_half(p)[0];
                    offset[2] = 0;
                    xform_fixed_point(offset, offset);
                    p->sub[1] += (offset[1] - (player_half(p)[1] - player_half(p)[0])) << 12;
                    p->sub[0] -= offset[0] << 12;
                } else {
                    p->sub[1] -= player_half(p)[1] << 12;
                }
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                turned = 1;
            }
            value = atan2(saved->m[1][1], -saved->m[2][1]);
            if (value != 0) {
                s32 sc = rcossin_tbl[value & 0xFFF];
                saved[1].m[0][0] = 0x1000;
                saved[1].m[0][1] = 0;
                saved[1].m[0][2] = 0;
                saved[1].m[1][0] = 0;
                saved[1].m[1][1] = (u32)sc >> 16;
                saved[1].m[1][2] = -sc;
                saved[1].m[2][0] = 0;
                saved[1].m[2][1] = sc;
                saved[1].m[2][2] = (u32)sc >> 16;
                rot_matrix_load(&saved[1]);
                if (value != 0x800) {
                    offset[0] = 0;
                    offset[1] = player_half(p)[1] - player_half(p)[2];
                    offset[2] = 0;
                    xform_fixed_point(offset, offset);
                    p->sub[1] += (offset[1] - (player_half(p)[1] - player_half(p)[2])) << 12;
                    p->sub[2] -= offset[2] << 12;
                } else {
                    p->sub[1] -= player_half(p)[1] << 12;
                }
                xform_fixed_point(p->sub, p->sub);
                mul_matrix(&saved[1], saved, saved);
                rot_matrix_load(saved);
                turned = 1;
            }
        }
        if (!turned) {
            obj_set_contact_flags((ObjContactState *)p);
        }
    } else {
        s32 y;

        gte_get_ctrl(R22R23, value);
        value &= 0xFFFF;
        if ((surface & 0x10) && value != 0x1000) {
            y = p->sub[1];
            value = (y >> 12) - p->y_min;
            size = player_half(p)[2] * 2;
            if (size < value) {
                p->sub[1] = y - ((size - player_half(p)[1] + 1) << 12);
                p->flags &= ~1;
                goto settle;
            }
        }
        obj_set_contact_flags((ObjContactState *)p);
    }
    scratch_top -= 0x50;
}

/* The player's move for this step: when standing still (no move, or only pushing into a contact),
 * keeps the position; otherwise moves it through the collision passes. */
void player_step_move(PlayerObj *p) {
    s32 old;
    s32 new;
    s32 frac;
    s32 mv;

    if (!(p->pose & 0x40) && p->move[0] == 0 && p->move[2] == 0
        && (p->move[1] == 0 || ((p->flags & ON_GROUND) && p->move[1] > 0)
            || ((p->flags & BLOCKED_ABOVE) && p->move[1] < 0))) {
        p->delta[0] = 0;
        p->delta[1] = 0;
        p->delta[2] = 0;
        *(VECTOR *)p->pos = *(VECTOR *)p->sub;
        return;
    }
    if (p->pose & 0x200) {
        player_bounds_query(p, work_area_ptr->packet);
        player_record_surface(p);
        player_move_step(p, work_area_ptr->packet);
    } else {
        player_bounds_query(p, work_area_ptr->packet);
        if ((p->pose & 0x40) || (*(s32 *)&p->angle[0] & 0x0FFF0FFF) || (p->angle[2] & 0xFFF)) {
            p->move[0] = p->move[0] >> 12 << 12;
            p->move[1] = p->move[1] >> 12 << 12;
            p->move[2] = p->move[2] >> 12 << 12;
            p->sub[0] = p->sub[0] >> 12 << 12;
            p->sub[1] = p->sub[1] >> 12 << 12;
            p->sub[2] = p->sub[2] >> 12 << 12;
        }
        player_record_surface(p);
        player_gte_load_pose(p);
        player_apply_rotation(p, 0);
        player_quarter_turn(p, 0);
        player_slope_push(p);
        player_move_vertical(p);

        /* z, then x: the sub-position keeps its whole units plus the new fraction; the move becomes
         * the whole units crossed, which the collision passes then apply. */
        old = p->sub[2];
        mv = p->move[2];
        new = old + mv;
        old >>= 12;
        frac = new & 0xFFF;
        new >>= 12;
        new -= old;
        p->sub[2] = (old << 12) + frac;
        p->move[2] = new << 12;
        player_move_z(p, frac);

        old = p->sub[0];
        mv = p->move[0];
        new = old + mv;
        old >>= 12;
        frac = new & 0xFFF;
        new >>= 12;
        new -= old;
        p->sub[0] = (old << 12) + frac;
        p->move[0] = new << 12;
        player_move_x(p, frac);

        player_quarter_turn(p, 1);
        player_apply_rotation(p, 1);
        player_wall_climb_frame(p);
        player_tilt_to_ground(p);
        player_gte_store_pose(p);
    }
    player_clamp_pos(p);
}

/* Calls player_step_move(p) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * The original is hand-written asm: the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void player_step_move_scratch(PlayerObj *p) {
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    player_step_move(p);
    SCRATCH_STACK_LEAVE_BELOW();
}

void player_refresh_state(PlayerObj *p) {
    s32 cell;
    u32 pose;
    s32 y;
    s32 top;

    pose = p->pose;
    p->move[0] = 0;
    p->move[1] = 0;
    p->move[2] = 0;
    if ((pose & 0x10) && (pose & 3)) {
        cell = clamp_find_box(p->sub[0] >> 12, p->sub[1] >> 12, p->sub[2] >> 12);
    } else {
        cell = -1;
    }
    p->delta[0] = 0;
    p->delta[1] = 0;
    p->delta[2] = 0;
    p->unk_56 = cell;
    player_bounds_query(p, work_area_ptr->packet);
    player_gte_load_pose(p);
    player_column_query(p, work_area_ptr->packet);
    packet_spans_at_height(p->sub[1] >> 12, &p->x_max);
    top = p->y_max << 12;
    p->flags = 0;
    y = p->sub[1];
    if (y < (p->y_min + ((s16 *)&p->x18)[1]) << 12) {
        p->flags = 2;
    } else if (y >= top) {
        p->flags = 1;
    }
    *(VECTOR *)p->pos = *(VECTOR *)p->sub;
    player_gte_store_pose(p);
}

/* Calls player_refresh_state(p) on the scratchpad stack: the old $sp is saved at its top word, $sp just below it.
 * The original is hand-written asm: the asm keeps the old $sp in $at and sets up the frame
 * by hand (FINDINGS "$sp in C"). */
void player_refresh_state_scratch(PlayerObj *p, ...) { /* one caller passes a second word the asm ignores */
    SCRATCH_STACK_ENTER_BELOW(SCRATCH_STACK_TOP);
    player_refresh_state(p);
    SCRATCH_STACK_LEAVE_BELOW();
}
