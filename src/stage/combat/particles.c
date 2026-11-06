/* particles: one of the original source files (scripts/objmap.py); every stage. */

#include "stage.h"

void particle_pool_init(void) {
    s32 i = 1;

    do {
        particles[i].prev = i - 1;
        particles[i].next = i + 1;
        i++;
    } while (i < 0xA0);
    particle_free_head = 1;
    d_801363F3 = 0;
    particles[0].prev = 0;
    particles[0].next = 0;
    particle_free_count = 0xA0;
}

void particle_base_init(void) {
    particle_base_ptr = get_model_slot_base() + 0x78;
}

void particle_pool_reset(void) {
    particle_pool_init();
}

static inline void particle_release(s32 idx)
{
    u8 prev;
    u8 next;

    if (idx != 0) {
        prev = particles[idx].prev;
        next = particles[idx].next;
        particles[prev].next = next;
        particles[next].prev = prev;
        if (particle_list_tail == idx) {
            particle_list_tail = prev;
        }
        particles[idx].next = particle_free_head;
        particle_free_head = idx;
        particle_free_count++;
    }
}
/* Ages each live particle: past age 0x2E it is released, otherwise it falls (gravity on vy), moves and gets a
 * random spin. */
void particle_list_update(void) {
    Particle *p;
    u8 next;
    u8 index;

    next = particle_list_head;
    while (next != 0) {
        index = next;
        p = &particles[index];
        next = p->next;
        if (p->age++ >= 0x2E) {
            particle_release(index);
        } else {
            p->vy += 0x1000;
            p->x += p->vx;
            p->y += p->vy;
            p->z += p->vz;
            p->rot_y = rand_a_next();
            p->rot_x = rand_a_next();
            p->rot_z = rand_a_next();
        }
    }
}

/* Walks the particle list from D_80134D73 and spawns a spark for each live particle. The first pass reads
 * `p->unk_21` before `p` is set: it uses the caller's pointer, as the original does. */
void particle_sparks_draw(void) {
    Particle *p;
    u8 idx;
    s32 base;
    s32 colour;
    s32 value;
    s32 scale;
    u8 kind;
    s32 hi;

    idx = particle_list_head;
    base = particle_base_ptr;
    if (idx != 0) {
        hi = 0x20;
        do {
            colour = 0;
            do {
                kind = p->kind_variant;
            } while (0);
            if ((kind >> 4) == 1) {
                colour = (hi << 16) | 0x2080;
            }
            p = &particles[idx];
            idx = p->next;
            scale = p->scale_offset + 0x1000;
            value = pool_spawn_scaled(base + (p->kind_variant & 7), scale, scale, scale);
            spark_add(p->x >> 12, p->y >> 12, p->z >> 12, p->rot_y, p->rot_x, p->rot_z, value, colour);
        } while (idx != 0);
    }
}

/* Spawns up to 20 particles around (x, y, z); `kind` goes into the upper bits of unk_21. */
void particle_spawn_burst(s32 x, s32 y, s32 z, s32 kind) {
    s32 i = 0;
    s32 n;
    s32 index;
    Particle *p;

    do {
        n = particle_free_head;
        if (n == 0) {
            index = 0;
        } else {
            particle_free_head = particles[n].next;
            particles[n].prev = particle_list_tail;
            particles[n].next = 0;
            particles[particle_list_tail].next = n;
            index = n;
            particle_list_tail = index;
            particle_free_count -= 1;
        }
        if (index == 0) {
            return;
        }
        p = &particles[index];
        p->x = (x + rand_a_next() % 64 - 0x20) << 12;
        p->z = (z + rand_a_next() % 64 - 0x20) << 12;
        p->y = (y + rand_a_next() % 32) << 12;
        p->vx = (rand_a_next() % 32) << 12;
        p->vz = (rand_a_next() % 32) << 12;
        p->vy = 0xFFFE8000;
        p->scale_offset = rand_a_next() * 2;
        if (rand_a_next() & 1) {
            p->vx = -p->vx;
        }
        if (rand_a_next() & 1) {
            p->vz = -p->vz;
        }
        p->kind_variant = rand_a_next() % 8 + (kind << 4);
        p->age = 0;
        i++;
    } while (i < 20);
}

/* particle_spawn_burst with the velocity masks as arguments: vx and vz are random bits under mask_x and mask_z. */
void particle_spawn_burst_masked(s32 x, s32 y, s32 z, s32 kind, s32 mask_x, s32 mask_z) {
    s32 i = 0;
    s32 n;
    s32 index;
    Particle *p;

    do {
        n = particle_free_head;
        if (n == 0) {
            index = 0;
        } else {
            particle_free_head = particles[n].next;
            particles[n].prev = particle_list_tail;
            particles[n].next = 0;
            particles[particle_list_tail].next = n;
            index = n;
            particle_list_tail = index;
            particle_free_count -= 1;
        }
        if (index == 0) {
            return;
        }
        p = &particles[index];
        p->x = (x + rand_a_next() % 64 - 0x20) << 12;
        p->z = (z + rand_a_next() % 64 - 0x20) << 12;
        p->y = (y + rand_a_next() % 32) << 12;
        p->vx = (rand_a_next() & mask_x) << 12;
        p->vz = (rand_a_next() & mask_z) << 12;
        p->vy = 0xFFFE8000;
        p->scale_offset = rand_a_next() * 2;
        if (rand_a_next() & 1) {
            p->vx = -p->vx;
        }
        if (rand_a_next() & 1) {
            p->vz = -p->vz;
        }
        p->kind_variant = rand_a_next() % 8 + (kind << 4);
        p->age = 0;
        i++;
    } while (i < 20);
}

void query_tables_clear(void) {
    wall_tables_ptr = 0;
    placement_angle_table = 0;
}

void fn_8011285C(void) {

}
