/* pickups: one of the original source files (scripts/objmap.py); every stage. A stage's own copy of a function (other constants or data) is under #if STAGE. */

#include "stage.h"

/* A falling, spinning object: falls with acceleration 0x1800 (speed capped at 0x20000) down to the
 * floor at (s16 at 0x24C) - 0x80, turns, steps the u16 counters at 0x24E/0x250/0x252, and without an
 * owner (placement) lowers unk_254 after 600 steps and is freed after 720. 0x24C/0x24E are two halves
 * of stage.h's unk_24C. */
void pickup_update(Object *obj) {
    s32 y;
    s32 floor;
    s32 yaw;

    if (obj->vy > 0x1FFFF) {
        obj->vy = 0x20000;
    }
    y = obj->y + obj->vy;
    floor = (obj->vars.pickup.floor_y - 0x80) << 12;
    obj->y = y;
    if (y >= floor) {
        obj->y = floor;
    } else {
        obj->vy += 0x1800;
    }
    yaw = obj->yaw;
    obj->yaw = yaw - 0x20;
    obj->vars.pickup.angle_y += 0x20;
    obj->vars.pickup.angle_x += 0x10;
    obj->vars.pickup.angle_z += 8;
    if (obj->placement == 0) {
        if (++obj->vars.pickup.age > 600) {
            obj->vars.pickup.brightness -= 0x10;
        }
        if (obj->vars.pickup.age > 720) {
            obj_free(obj);
        }
    }
}

#if STAGE != 8
s16 d_800B6604[4] = {
    0x0024, 0x003C, 0x0030, 0x0000,
};
#endif

#if STAGE == 8
u16 msg_energy_pack_acquired[4] = {
    0x0024, 0x003C, 0x0030, 0x0000,
};
/* S01's name for the s16 table pickup_draw reads in every stage; s08's symbols name it msg_energy_pack_acquired. */
__asm__(".globl d_800B6604\n.set d_800B6604, msg_energy_pack_acquired");
#endif

/* pickup_phase2's scratchpad block: the player's position (player_position_copy), then the item's position. */
typedef struct PickupScratch {
    VECTOR player;
    VECTOR item;
} PickupScratch;

/* A pickup (energy pack, grenade) in the camera's range: taken when the player is within 0xC0 units. It is
 * freed once taken; out of range it only clears its shown flag. The message and sound depend on the kind
 * (vars.h.unk_24A: 0 or 2 add shield, 1 adds a grenade; other kinds are not taken). */
void pickup_phase2(Object *obj) {
    PickupScratch *scr;
    s32 got = 0;
    s32 dist;
    s32 mode;
    s32 shield;

    if (cam_range_check(obj->x >> 12, obj->y >> 12, obj->z >> 12) == 0) {
        if (obj->placement != NULL) {
            placement_snap_to_obj(obj->placement, obj);
            obj->placement->unk_04[0] = (obj->placement->unk_04[0] & 0xFC) | 2;
        }
        obj_free(obj);
        return;
    }

    scr = (PickupScratch *)scratch_top;
    scratch_top += 0x20;
    player_position_copy(&scr->player);
    scratch_top -= 0x20;
    scr->item.vx = obj->x >> 12;
    scr->item.vy = obj->y >> 12;
    scr->item.vz = obj->z >> 12;
    dist = isqrt(length_sq(scr->item.vx - scr->player.vx, scr->item.vy - scr->player.vy, scr->item.vz - scr->player.vz));

    if (dist < 0xC0) {
        mode = obj->vars.pickup.variant_index;
        switch (mode) {
        case 0:
            shield = get_shield();
            if (shield < 0xC8) {
                shield += 0x14;
                if (shield > 0xC8) {
                    shield = 0xC8;
                }
                set_shield(shield);
                got = 1;
                show_line((s32)"#2Energy pack acquired.\xA1");
                sound_start(SND_ITEM_PICKUP | SND_VOICE_FLAG, 0x7F, 0, 0);
            } else if (obj->vars.pickup.unk_25C == 0) {
                show_line((s32)"Maximum Shield Energy!\xA1");
                sound_start(SND_PICKUP_DENIED | SND_VOICE_FLAG, 0x64, 0, 0);
            }
            break;
        case 1:
            if (grenades_get() < GRENADES_MAX) {
                grenades_add(1);
                show_line((s32)"#2Grenade acquired.\xA1");
                got = 1;
            } else if (obj->vars.pickup.unk_25C == 0) {
                show_line((s32)"Maximum Grenade Count!\xA1");
                sound_start(SND_PICKUP_DENIED | SND_VOICE_FLAG, 0x64, 0, 0);
            }
            break;
        case 2:
            shield = get_shield();
            if (shield < 0xC8) {
                shield += 0x43;
                if (shield > 0xC8) {
                    shield = 0xC8;
                }
                set_shield(shield);
                got = 1;
                show_line((s32)"#2Energy pack acquired.\xA1");
                sound_start(SND_ITEM_PICKUP | SND_VOICE_FLAG, 0x7F, 0, 0);
            } else if (obj->vars.pickup.unk_25C == 0) {
                show_line((s32)"Maximum Shield Energy!\xA1");
                sound_start(SND_PICKUP_DENIED | SND_VOICE_FLAG, 0x64, 0, 0);
            }
            break;
        }
        obj->vars.pickup.unk_25C = 1;
        if (got) {
            sound_start(SND_ITEM_PICKUP_ALT | SND_VOICE_FLAG, 0x7F, 0, 0);
            if (obj->placement != NULL) {
                obj->placement->unk_04[0] = obj->placement->unk_04[0] | 3;
            }
            obj_free(obj);
        }
    } else {
        obj->vars.pickup.unk_25C = 0;
    }
}

void pickup_draw(Object *obj) {
    s32 base;
    s32 pitch;
    Vec3 *pos;
    SVECTOR *rot;
    s32 level;
    s32 colour;
    s32 red;
    s32 sprite;

    if (obj->vars.pickup.age < 0) {
        return;
    }
    if (obj->vars.pickup.age >= 0x259) {
        obj->vars.pickup.unused_258 ^= 1;
    }
    pos = scratch_alloc(0x10);
    pos->x = obj->x >> 12;
    pos->y = obj->y >> 12;
    pos->z = obj->z >> 12;
    rot = scratch_alloc(8);
    pitch = obj->pitch;
    rot->vx = -pitch;
    rot->vy = obj->yaw;
    rot->vz = obj->roll;
    base = get_model_slot_base();
    sprite = base + 0x17;
    level = (s32)(obj->vars.pickup.brightness << 16) >> 21;
    red = level ? level : 1;
    colour = (red << 16) | (level << 8) | level;
    spark_add(pos->x, pos->y, pos->z, obj->vars.pickup.angle_y, obj->vars.pickup.angle_x, obj->vars.pickup.angle_z, sprite, colour);
    spark_add(pos->x, pos->y, pos->z, obj->vars.pickup.angle_y, obj->vars.pickup.angle_x, obj->vars.pickup.angle_z, base + 0x18, colour);
    if (obj->vars.pickup.unused_258 != 0) {
        s32 kind_sprite = base + 0x19;
        s32 top_sprite;

        spark_add_head(&spark_list, pos->x, pos->y, pos->z, rot->vy, rot->vx, rot->vz, kind_sprite + obj->vars.pickup.variant_index, 0);
        if (obj->vars.pickup.floor_y <= 0) {
            top_sprite = base + 0x2D;
            base = top_sprite + obj->vars.pickup.variant_index;
            spark_add_head(&spark_list, pos->x, obj->vars.pickup.floor_y - d_800B6604[obj->vars.pickup.variant_index], pos->z, rot->vy, rot->vx, rot->vz, base, 0);
        }
    }
    scratch_top -= 0x18;
}

/* Spawns an object at (x, y, z) in 12.4 units with a random yaw and a mode-picked value (mode & 3, 0 = random).
 * Returns NULL when no object is free. The arrays are 4 words so the frame matches the original. */
/* Old-style definition: obj_spawn_falling calls it with two arguments. */
void *pickup_spawn(x, y, z, mode)
    s32 x;
    s32 y;
    s32 z;
    s32 mode;
{
    Object *obj;
    s32 start[4];
    s32 end[4];
    s32 hit[4];

    obj = obj_new();
    if (obj == NULL) {
        return NULL;
    }
    list_insert_after((Node *) get_obj_list_c(), (Node *) obj);
    obj->handlers[1].fn = (ObjHandlerFn) pickup_update;
    obj->handlers[2].fn = (ObjHandlerFn) pickup_phase2;
    obj->handlers[3].fn = (ObjHandlerFn) pickup_draw;
    obj->x = x << 12;
    obj->y = y << 12;
    obj->handlers[0].fn = NULL;
    obj->handlers[0].unk_11 = 0;
    obj->handlers[0].state = 0;
    obj->handlers[1].unk_11 = 0;
    obj->handlers[1].state = 0;
    obj->handlers[2].unk_11 = 0;
    obj->handlers[2].state = 0;
    obj->handlers[3].unk_11 = 0;
    obj->handlers[3].state = 0;
    obj->z = z << 12;
    obj->yaw = (s16) rand_a_next();
    obj->pitch = 0;
    obj->roll = 0;

    mode &= 0x3;
    if (mode == 0) {
        obj->vars.pickup.variant_index = rand_a_next() % 3;
    } else {
        obj->vars.pickup.variant_index = mode - 1;
    }
    obj->vars.pickup.angle_y = rand_a_next();
    obj->vars.pickup.angle_x = rand_a_next();
    obj->vars.pickup.angle_z = rand_a_next();

    /* Trace down from the spawn point: the hit's word 1 is the height used at 0x24C. */
    start[0] = x;
    start[1] = y;
    start[2] = z;
    end[0] = x;
    end[1] = 0;
    end[2] = z;
    if (trace_world(2, 8, start, end, hit)) {
        obj->vars.pickup.floor_y = (s16) hit[1];
    } else {
        obj->vars.pickup.floor_y = 0;
    }

    obj->vars.pickup.brightness = 0x800;
    obj->vars.pickup.age = 0;
    obj->vy = 0;
    obj->vars.pickup.unused_258 = 1;
    obj->vars.pickup.unk_25C = 0;
    return obj;
}

/* Sets up the object that pickup_spawn returns, if any: no placement, halfword -12 at 0x248, falling
 * speed -0x18000. The first argument is passed through to pickup_spawn unchanged. */
void obj_spawn_falling(s32 unk_a0, s32 unk_a1) {
    Object *obj;

    if (unk_a1 >= 0) {
        unk_a1 = -0x80;
    }
    obj = pickup_spawn(unk_a0, unk_a1);
    if (obj != NULL) {
        obj->placement = NULL;
        obj->vars.h.unk_248 = -0xC;
        obj->vy = 0xFFFE8000;
    }
}

/* Finds the object that a placement with this position and kind is in, and points it at the placement.
 * Returns 1 when it found one. */
s32 placement_spawn(Placement *placement) {
    Object *obj;

    obj = pickup_spawn(placement->x >> 12, placement->y >> 12, placement->z >> 12, (s16) placement->health);
    if (obj == NULL) {
        return 0;
    }
    obj->placement = placement;
    return 1;
}
