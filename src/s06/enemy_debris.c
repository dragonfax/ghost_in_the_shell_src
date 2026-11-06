/* Debris of destroyed enemy parts and children (enemy_part_phase0, enemy_child_phase0): 10 pieces each, a
   velocity (x, y, z; -y is up) and a keyframe list (hold the value for 48 frames, then end). Pieces 6-10 reuse
   pieces 1-5's velocities. s06's data from 0x8011EB34 to 0x8011EC34 (C_DATA in gen_splat_configs.py). */

#include "stage.h"

SVECTOR enemy_part_vel_up      = {   0, -24,  0 };
SVECTOR enemy_part_vel_forward = {   0, -24, 12 };
SVECTOR enemy_part_vel_left    = { -32, -24,  0 };
SVECTOR enemy_part_vel_right   = {  32, -24,  0 };
SVECTOR enemy_part_vel_high    = {   0, -36,  0 };

Keyframe enemy_part_keys_10[] = { { 48, 0x10 }, { -1, 0x10 } };
Keyframe enemy_part_keys_11[] = { { 48, 0x11 }, { -1, 0x11 } };
Keyframe enemy_part_keys_12[] = { { 48, 0x12 }, { -1, 0x12 } };
Keyframe enemy_part_keys_13[] = { { 48, 0x13 }, { -1, 0x13 } };
Keyframe enemy_part_keys_14[] = { { 48, 0x14 }, { -1, 0x14 } };
Keyframe enemy_part_keys_20[] = { { 48, 0x20 }, { -1, 0x20 } };
Keyframe enemy_part_keys_21[] = { { 48, 0x21 }, { -1, 0x21 } };
Keyframe enemy_part_keys_22[] = { { 48, 0x22 }, { -1, 0x22 } };
Keyframe enemy_part_keys_23[] = { { 48, 0x23 }, { -1, 0x23 } };
Keyframe enemy_part_keys_24[] = { { 48, 0x24 }, { -1, 0x24 } };

/* obj_hit_mask_avg's values for enemy_part_update: 1.0 for every hit bit */
s16 D_8011EBAC[8] = { 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000 };

SVECTOR enemy_child_vel_up      = {   0, -24,  0 };
SVECTOR enemy_child_vel_forward = {   0, -24, 12 };
SVECTOR enemy_child_vel_left    = { -32, -24,  0 };
SVECTOR enemy_child_vel_right   = {  32, -24,  0 };
SVECTOR enemy_child_vel_high    = {   0, -36,  0 };

Keyframe enemy_child_keys_18[] = { { 48, 0x18 }, { -1, 0x18 } };
Keyframe enemy_child_keys_19[] = { { 48, 0x19 }, { -1, 0x19 } };
Keyframe enemy_child_keys_1a[] = { { 48, 0x1A }, { -1, 0x1A } };
Keyframe enemy_child_keys_1b[] = { { 48, 0x1B }, { -1, 0x1B } };
Keyframe enemy_child_keys_1c[] = { { 48, 0x1C }, { -1, 0x1C } };
Keyframe enemy_child_keys_28[] = { { 48, 0x28 }, { -1, 0x28 } };
Keyframe enemy_child_keys_29[] = { { 48, 0x29 }, { -1, 0x29 } };
Keyframe enemy_child_keys_2a[] = { { 48, 0x2A }, { -1, 0x2A } };
Keyframe enemy_child_keys_2b[] = { { 48, 0x2B }, { -1, 0x2B } };
Keyframe enemy_child_keys_2c[] = { { 48, 0x2C }, { -1, 0x2C } };
