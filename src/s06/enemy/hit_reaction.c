/* hit_reaction: one of s06's own original source files (scripts/objmap.py); part of src/s06/main.c's unit, included there. */

void obj_hit_reaction(Object *obj, s32 arg1) {
    u8 *block;
    s32 pos;
    s32 pitch;
    s32 pad[2]; /* keeps the original 0x28-byte frame */

    block = obj->unk_A4;
    pos = obj->type.unk_0E + (arg1 + ((s32 *)obj->asset)[1]);
    pitch = obj->pitch;
    *(u16 *)&block[0x2E] = obj->yaw;
    *(u16 *)&block[0x30] = obj->roll;
    *(s16 *)&block[0x2C] = -pitch;
    block[1] = 1;
    block[0] = obj->index;
    obj_block_fill(obj, block);
    solid_setup_scratch(obj->solid_id, block, (s16)pos, obj->unk_190);
    fn_800FB460(obj, block);
}
