/* fighter_jet_spawner: one of s05's own original source files (scripts/objmap.py); part of src/s05/main.c's unit, included there. */

extern char fighter_jet_slot_table, D_8012005E, D_80120060, D_80120061, D_80120062;
extern char D_80120064, D_80120068, D_8012006C, D_80120070, D_80120072;
extern char D_80120074, D_80120076, D_80120078, D_8012007A;
void slot_clear(s32 index) {
    s32 off = index << 5;

    *(s16 *)(&fighter_jet_slot_table + off) = 0;
    *(s16 *)(&D_8012005E + off) = 0;
    *(s8 *)(&D_80120060 + off) = 0;
    *(s8 *)(&D_80120061 + off) = 0;
    *(s16 *)(&D_80120062 + off) = 0;
    *(s32 *)(&D_80120064 + off) = 0;
    *(s32 *)(&D_80120068 + off) = 0;
    *(s32 *)(&D_8012006C + off) = 0;
    *(s16 *)(&D_80120070 + off) = 0;
    *(s16 *)(&D_80120072 + off) = 0;
    *(s16 *)(&D_80120074 + off) = 0;
    *(s16 *)(&D_80120076 + off) = 0;
    *(s16 *)(&D_80120078 + off) = 0;
    *(s16 *)(&D_8012007A + off) = 0;
}

s32 slot_find_free(Object *obj) {
    s32 i;
    s16 *p = (s16 *)obj;

    for (i = 0; i < 1; i++) {
        if (p[0x125 + 0] == 0) {
            return i;
        }
        p++;
    }
    return -1;
}

/* Countdown on obj's timer; when it runs out, try to spawn a fighter jet into a free slot. */
void fighter_jet_spawner_update(Object *obj, ObjHandler *handler) {
    s32 slot;
    u16 timer;
    s32 *player;
    SlotRec *rec;
    s32 z;
    s32 rnd;
    s16 spawn_rot[3];

    timer = obj->vars.slot_obj.timer;
    obj->vars.slot_obj.timer = timer - 1;
    if ((s16) timer < 0) {
        player = player_position();
        if (player[2] >= -0x1F40) {
            slot = -1;
            if (meter_get_mode() == 0) {
                slot = slot_find_free(obj);
            }
        } else {
            slot = -1;
        }
        if (slot != -1) {
            spawn_rot[0] = 0;
            spawn_rot[1] = 0x800;
            spawn_rot[2] = 0;
            (void) &spawn_rot;
            slot_clear(slot);
            rec = (SlotRec *)(&fighter_jet_slot_table + (slot << 5));
            rec->unk_04 = 4;
            rec->unk_02 = 0;
            rec->unk_05 = 5;
            rec->unk_06 = 0;
            rec->pos_x = ((player[0] + 0x2710) << 12) + (rec->pos_x & 0xFFF);
            rec->pos_y = (rec->pos_y & 0xFFF) + 0xFF254000;
            rnd = rand_a_next();
            z = player[2];
            rec->unk_14 = 0x320;
            rec->unk_16 = 0x708;
            rec->unk_18 = 0x1A;
            rec->unk_1A = 0;
            rec->unk_1C = 0;
            rec->unk_1E = 0;
            rec->pos_x = (rec->pos_x >> 12) << 12;
            rec->pos_z = ((((rnd % 1000) + z) - 0x1F4) << 12) + (rec->pos_z & 0xFFF);
            rec->pos_y = ((rec->pos_y >> 12) << 12) + 0xC00;
            rec->pos_z = (rec->pos_z >> 12) << 12;
            obj->vars.slot_obj.slot = slot;
            if (fighter_jet_spawn_from_parent((Placement *)rec, obj) == 1) {
                ((s16 *)&obj->vars.slot_obj.unused_24A)[slot] = 1;
            }
        }
        obj->vars.slot_obj.timer = 0x4B0;
    }
}

void fighter_jet_spawner_update(Object *obj, ObjHandler *handler);
void slot_obj_init(void) {
    Object *obj;
    u16 *p;
    s32 i;

    obj = obj_new();
    if (obj != NULL) {
        list_insert_after((Node *) get_obj_list_actors(), &obj->node);
        p = (u16 *) obj;
        obj->handlers[0].fn = NULL;
        obj->handlers[0].unk_11 = 0;
        obj->handlers[0].state = 0;
        obj->handlers[1].fn = fighter_jet_spawner_update;
        obj->handlers[1].unk_11 = 0;
        obj->handlers[1].state = 0;
        obj->handlers[2].fn = NULL;
        obj->handlers[2].unk_11 = 0;
        obj->handlers[2].state = 0;
        obj->handlers[3].fn = NULL;
        obj->handlers[3].unk_11 = 0;
        obj->handlers[3].state = 0;
        obj->vars.slot_obj.slot = 0;
        for (i = 0; i < 1; i++) {
            p[0x125 + i] = 0;
        }
        obj->vars.slot_obj.timer = 0x4B0;
    }
}

void slot_table_init(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        slot_clear(var_s0);
        var_s0 += 1;
    } while (var_s0 <= 0);
    slot_obj_init();
}

extern FxRecordParams obj_effect_rec34_start;
extern FxRecordParams obj_effect_rec34_end;
extern RecTemplate obj_effect_template_start;
extern RecTemplate obj_effect_template_mid;
/* Plays two sounds (fx_rec34_spawn, fx_spawn_template) at the object's position, moved down 0xC and then 0x200 and 0x500 for the
 * second and third calls (sound/effect ids are the D_ addresses). */
void obj_play_effects(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);

    pos->x = obj->x >> 12;
    pos->y = (obj->y >> 12) - 0xC;
    pos->z = obj->z >> 12;
    fx_rec34_spawn((s32 *)pos, &obj_effect_rec34_start);
    fx_spawn_template((s32 *)pos, &obj_effect_template_start, NULL);
    pos->y -= 0x200;
    fx_spawn_template((s32 *)pos, &obj_effect_template_mid, NULL);
    pos->y -= 0x500;
    fx_rec34_spawn((s32 *)pos, &obj_effect_rec34_end);
    scratch_top -= 0x10;
}
