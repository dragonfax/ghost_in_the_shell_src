/* Data shared by s02, s11, s12: scripts/stage_data.py. */

struct PlacedActorAnims {
    s16 script[4];
    s16 *table[1];
} placed_actor_anims = {
    /* script */ {
        STEP(1, 1),
        GOTO(PLACED_ACTOR_SCRIPT),
    },
    /* table */ {
        placed_actor_anims.script,
    },
};
