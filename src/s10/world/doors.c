/* doors: one of s10's own original source files (scripts/objmap.py); part of src/s10/main.c's unit, included there. */

extern s32 spark_base;
extern s8 D_80124D19;

void spark_reset(void) {
    s32 var_a0;
    s8 *var_v1;

    var_a0 = 1;
    var_v1 = &D_80124D19;
    spark_base = point_base;
    do {
        *var_v1 = 0;
        var_a0 -= 1;
        var_v1 -= 1;
    } while (var_a0 >= 0);
}

extern void (*obj_init_table[])(Object *);
extern ObjPhaseEntry obj_phase0_table[4], obj_phase1_table[], obj_phase2_table[], obj_phase3_table[];
s32 obj_spawn_placement(Placement *placement) {
    Object *obj;
    s32 kind, hp, z;
    s32 unused[2];

    obj = obj_new();
    if (obj == NULL) {
        return 0;
    }
    list_insert_after((Node *) get_obj_list_b(), (Node *) obj);
    hp = placement->unk_16;
    kind = *(s16 *)&placement->health;
    obj->damage = hp;
    obj->handlers[0].fn = obj_phase0_table[kind].fn;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].fn = obj_phase1_table[kind].fn;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].fn = obj_phase2_table[kind].fn;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].fn = obj_phase3_table[kind].fn;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->x = placement->x;
    obj->y = placement->y;
    z = placement->z;
    obj->vars.enemy.unk_24C[0] = 1;
    obj->vars.placement.unk_248 = 0x1000;
    obj->vars.placement.unk_24A = 0;
    obj->vars.enemy.unk_24C[1] = 0;
    obj->z = z;
    if (obj_init_table[kind] != NULL) {
        obj_init_table[kind](obj);
    }
    return 1;
}


void fn_800B789C(Object *obj) {
    ObjSum *sum_obj = (ObjSum *) obj;
    s32 sum = sum_obj->total + sum_obj->step;
    s32 clamped;
    s32 result;

    sum_obj->total = sum;
    clamped = (s16) sum;
    if (clamped >= 0x1001) {
        clamped = 0x1000;
    }
    if (clamped >= 0) {
        clamped = (s16) sum;
        if (clamped >= 0x1001) {
            clamped = 0x1000;
        }
        result = clamped;
    } else {
        result = 0;
    }
    sum_obj->total = result;
}


extern u8 door_state_table[];
void door_phase0(Object *obj) {
    if (door_state_table[obj->vars.enemy.unk_24C[0]] == 1) {
        *(s16 *)&obj->vars.placement.unk_24A = -0x80;
        aobj_set_flag(get_rec_id(0) + obj->vars.placement.flag_offset, 0);
    } else {
        obj->vars.placement.unk_24A = 0x80;
        aobj_set_flag(get_rec_id(0) + obj->vars.placement.flag_offset, 1);
    }
}

/* Door: writes its position to the spark list and adds two sparks.
 * The raw bytes at 0x24D..0x251 are not named in Object yet. */
void door_draw(Object *obj) {
    u8 *bytes = (u8 *)obj;
    s32 colour;
    register s32 angle asm("$17"); /* kept in s1 across the calls */
    s32 base;
    s32 hi;
    s32 lo;
    s32 res_a;
    s32 res_b;
    s32 *pos;

    pos = scratch_alloc(0x10);
    pos[0] = obj->x >> 12;
    pos[1] = obj->y >> 12;
    pos[2] = obj->z >> 12;
    base = spark_base;
    colour = 0;
    if (bytes[0x24D] == 1) {
        angle = (s16)rcossin_tbl[((s16)obj->vars.placement.unk_248 / 4) & 0xFFF];
    } else {
        angle = (s16)obj->vars.placement.unk_248;
    }
    hi = base + bytes[0x250];
    lo = base + bytes[0x251];
    res_a = pchr_blend(base + bytes[0x24E], base + bytes[0x24F], angle, 1);
    hi = pchr_blend(hi, lo, angle, 1);
    spark_add(pos[0], pos[1], pos[2], 0, 0, 0, res_a, colour);
    spark_add(pos[0], pos[1], pos[2] - 0x12C, 0, 0, 0, hi, colour);
    scratch_top -= 0x10;
}

void func_800C903C(Object *obj) {
    obj->vars.h.unk_252 = 0xB7;
}

void door_update(Object *obj) {
    s32 dist;
    s32 zt;
    s32 xt;
    s16 angle;

    if (obj->vars.enemy.unk_24C[0] != 0) {
        xt = (cam_pos - obj->x) / 0x1000;
        zt = (cam_pos_z - obj->z) / 0x1000;
        dist = isqrt(length_sq(xt - 0xF0, 0, zt));
        if (dist < 0x280) {
            angle = -0x80;
            obj->vars.placement.unk_24A = angle;
            aobj_set_flag(get_rec_id(0) + obj->vars.placement.flag_offset, 0);
            return;
        }
        obj->vars.placement.unk_24A = 0x80;
        aobj_set_flag(get_rec_id(0) + obj->vars.placement.flag_offset, 1);
        if (zt < 0) {
            obj->vars.enemy.unk_24C[0] = 0;
        }
    }
}

extern s16 spark_level_offsets[3];
/* Adds three sparks, one per spark_level_offsets offset from spark_base, stepping 0xF0 in x. */
void obj_spark_triple(Object *obj) {
    Vec3 *pos = scratch_alloc(0x10);
    s32 colour;
    s32 i;
    s32 base;
    s32 level;
    s32 value;

    colour = 0;
    i = 0;
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    base = spark_base;
    pos->z = obj->z >> 12;
    level = obj->vars.placement.unk_248;
    do {
        value = base + spark_level_offsets[i];
        value = pchr_blend(value, value + 0x10, level, 0);
        spark_add(pos->x, pos->y, pos->z, 0, 0, 0, value, colour);
        pos->x += 0xF0;
        i++;
    } while (i < 3);
    scratch_top -= 0x10;
}

void func_800C929C(Object *obj) {
    ObjSetupBytes *vars = (ObjSetupBytes *)&obj->vars;

    vars->unk_24E = 0x36;
    vars->unk_24F = 0x60;
    vars->unk_250 = 0x37;
    vars->unk_251 = 0x73;
    vars->unk_24C = 0;
    vars->unk_24D = 0;
    vars->unk_252 = 0xB5;
}

void func_800C92D0(Object *obj) {
    u8 *tail;

    obj->vars.enemy.unk_24C[2] = 0x32;
    obj->vars.enemy.unk_24C[3] = 8;
    tail = (u8 *)&obj->vars.enemy.unk_250;
    tail[0] = 0x33;
    tail[1] = 0x38;
    obj->vars.enemy.unk_24C[0] = 1;
    obj->vars.enemy.unk_24C[1] = 0;
    obj->vars.h.unk_252 = 0xB6;
}

extern u8 door_state_table[];
void door_state_set(u32 index, s8 value) {
    if (index < 2) {
        door_state_table[index] = value;
    }
}
