#ifndef STAGE_TYPES_H
#define STAGE_TYPES_H

/* The stage engine's types and constants (stage.h declares its functions and globals). Types only, so the
 * data files can include this without stage.h's declarations of the objects they define. */

#include "common.h"
#include "gte.h"
#include "resource.h"

struct Object; /* defined below; ObjHandler and ObjHandlerFn refer to it */

/* One of an object's four handler records: the function obj_list_run calls for a phase, then (for
 * coroutine-style handlers) a resume address and counters. obj_handler_clear resets one. */
typedef struct ObjHandler {
    /* 0x00 */ void (*fn)(struct Object *obj, struct ObjHandler *handler);
    /* 0x04 */ u32 resume;
    /* 0x08 */ s16 entry_index;
    /* 0x0A */ s16 next_entry;
    /* 0x0C */ s16 queued_entry;
    /* 0x0E */ s16 pending_state;
    /* 0x10 */ u8 request_flags;
    /* 0x11 */ s8 unk_11;
    /* 0x12 */ s16 state;  /* set to 1 when the object dies */
    /* 0x14 */ s16 result; /* a behaviour step's outcome (e.g. 1 shot fired, -2 done) */
    /* 0x16 */ s16 state_delay;
    /* 0x18 */ s16 turn_timer;
    /* 0x1A */ s16 timer;
} ObjHandler; /* 0x1C */
typedef void (*ObjHandlerFn)(struct Object *obj, ObjHandler *handler);

/* A 16-byte record of an object, reset by obj_link_clear. */
typedef struct ObjLink {
    /* 0x00 */ void *data; /* the type link's: a per-type data table */
    /* 0x04 */ s16 *pc; /* a script's program counter; the type link's: its table entry */
    /* 0x08 */ s16 blend_duration;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} ObjLink;

/* A script link's program counter (ObjLink.pc, a cursor over s16 words) and a jump to
   entry i of its data table. */
#define OBJLINK_JUMP(l, i) ((l)->pc = ((s16 **)(l)->data)[i])
/* ObjLink.unk_0C while a script waits (obj_link_script_run). */
#define OBJLINK_SCRIPT_WAIT (-0x20)

/* A placement record an object is set up from (obj_init_from_place). */
typedef struct Placement {
    /* 0x00 */ u8 unk_00[2];
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04[2];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 x, y, z; /* whole units in the high bits, an angle (x, yaw, z) in the low 12 bits */
    /* 0x14 */ u16 health;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ s16 range;
    /* 0x1E */ s16 unk_1E; /* s13 func_800B8E9C divides 0x1000 by it */
} Placement;

/* The flow that pushes the player (flow_update). */
typedef struct Flow {
    /* 0x00 */ s16 state; /* negative: off */
    /* 0x02 */ s16 wall_direction;
    /* 0x04 */ s16 angle;
    /* 0x06 */ s16 speed;
} Flow;

/* The last 0x40 bytes of an object, whose meaning depends on its kind. */
/* from func_800C62C8 */
typedef struct Quad {
    s32 w[4];
} Quad;

/* from countdown_tick */
typedef struct Countdown {
    Quad value;
    u16 count;
    s16 latched;
} Countdown;

/* s05 M5 camouflaged target boss: a model part's offset and rotation */
typedef struct M5BossPart {
    /* 0x00 */ s16 x, y, z;
    /* 0x06 */ s16 rot_x, rot_y, rot_z;
} M5BossPart;

typedef struct M5BossModel {
    /* 0x00 */ u8 pad_00[0x1C];
    /* 0x1C */ M5BossPart part;
} M5BossModel;

#include "objvars.h"

typedef union ObjVars {
    s32 words[16]; /* obj_reset clears them as a block */
    EnemyVars enemy;
    FlyerVars flyer;
    SpawnKindVars spawn;
    SndVars snd;
    struct {       /* the halfword view of other kinds */
        /* 0x248 */ s16 unk_248;
        /* 0x24A */ u16 unk_24A;
        /* 0x24C */ s16 unk_24C;
        /* 0x24E */ u16 unk_24E;
        /* 0x250 */ u16 unk_250;
        /* 0x252 */ u16 unk_252;
        /* 0x254 */ s16 unk_254;
        /* 0x256 */ u16 unk_256;
        /* 0x258 */ u16 unk_258;
        /* 0x25A */ s16 unk_25A;
        /* 0x25C */ s32 unk_25C; /* pickup_phase2: 1 in range, 0 out of range; its message shows only at 0 */
        /* 0x260 */ s16 unk_260;
        /* 0x262 */ s16 unk_262;
        /* 0x264 */ u8 pad_264[0x270 - 0x264];
        /* 0x270 */ s16 unk_270; /* s02 func_800C0D44: meter maximum */
        /* 0x272 */ u16 sound;   /* s10 func_800BCA08: stopped on death */
        /* 0x274 */ u8 pad_274[4];
        /* 0x278 */ s32 unk_278; /* s06 tank_sink_step: top speed while sinking */
        /* 0x27C */ u8 pad_27C[0x282 - 0x27C];
        /* 0x282 */ s16 unk_282; /* s06 tank_sink_step: -2 starts sinking, -1 frees, else counts down */
        /* 0x284 */ s16 unk_284; /* s06 tank_draw: 2 lifts the drawn model by |height * sin(pitch)| */
    } h;
    TmechVars tmech;
    TurretVars turret;
    HomingKindVars homing;
    EshotVars eshot;
    ArcVars arc;
    TurnKindVars turn;
    Snd2Vars snd2;
    DriftVars drift;
    CopterVars copter;
    ScriptVars script;
    PairVars pair;
    DmechVars dmech;
    ChaserVars chaser;
    SpinVars spin;
    PartVars part;
    FlareVars flare;
    SparkPartVars spark_part;
    FlyVars fly;
    HoverVars hover;
    MineVars mine;
    TraceVars trace;
    RideVars ride;
    BobVars bob;
    PushedVars pushed;
    HeliVars heli;
    JitterVars jitter;
    FadeVars fade;
    FollowVars follow;
    ShotVars shot;
    GunsVars guns;
    RocketVars rocket;
    LaserVars laser;
    SpinLaserVars spin_laser;
    TraceShotVars trace_shot;
    ExplodeVars explode;
    BarrierVars barrier;
    CamoVars camo;
    BeamVars beam;
    MissileVars missile;
    LimbVars limb;
    SlotsVars slots;
    BurstVars burst;
    TracerVars tracer;
    FlierKindVars flier;
    RibbonVars ribbon;
    BurstEnemyVars burst_enemy;
    BlastSeqVars blast_seq;
    AnimObjVars anim_obj;
    AreaEffectVars area_effect;
    ArrivalWarningVars arrival_warning;
    AxeSoldierVars axe_soldier;
    BazookaRocketVars bazooka_rocket;
    BeamSegmentVars beam_segment;
    BombMechM7BossVars bomb_mech_m7_boss;
    BossAreaAttackExplosionVars boss_area_attack_explosion;
    BossLaserVars boss_laser;
    BurstObjVars burst_obj;
    BurstShotVars burst_shot;
    CamouflagedTargetM5BossVars camouflaged_target_m5_boss;
    CeilingBomberVars ceiling_bomber;
    CtrlVars ctrl;
    DamageRecordVars damage_record;
    DreadnoughtM11BossVars dreadnought_m11_boss;
    DualMechVars dual_mech;
    ElevatorDoorsVars elevator_doors;
    EndZoneVars end_zone;
    EnemyChildPartVars enemy_child_part;
    EnemyCreateObjVars enemy_create_obj;
    EnemyFireRocketObjVars enemy_fire_rocket_obj;
    EnemyPartChildVars enemy_part_child;
    EnemyPlaceVars enemy_place;
    EnemyShotVars enemy_shot;
    EnemySpawnBeeperObjVars enemy_spawn_beeper_obj;
    EnemySpawnChildObjVars enemy_spawn_child_obj;
    EnemySpawnCopyObjVars enemy_spawn_copy_obj;
    EnemySpawnFromVars enemy_spawn_from;
    EnemySpawnShooterObjVars enemy_spawn_shooter_obj;
    EnergyMoteVars energy_mote;
    EscapingBoatM4BossVars escaping_boat_m4_boss;
    FighterJetVars fighter_jet;
    FighterJetSpawnFromParentObjVars fighter_jet_spawn_from_parent_obj;
    Fn800BBB78ObjVars fn_800BBB78_obj;
    Fn800BBF9CObjVars fn_800BBF9C_obj;
    FnS07800BAE10ObjVars fn_s07_800BAE10_obj;
    GiantRobotVars giant_robot;
    GridControllerVars grid_controller;
    GunTurret2Vars gun_turret_2;
    GunTurretVars gun_turret;
    HeavyMobileSuitVars heavy_mobile_suit;
    Helicopter2Vars helicopter2;
    HelicopterVars helicopter;
    HomingEnergyPulseVars homing_energy_pulse;
    HomingRocketVars homing_rocket;
    ImpactVars impact;
    JetskiVars jetski;
    JetskiWakeVars jetski_wake;
    KeyCodeExitDoorsVars key_code_exit_doors;
    KeyholderFuchikomaVars keyholder_fuchikoma;
    LaserBarrierBoatKindVars laser_barrier_boat;
    LaserDroneVars laser_drone;
    LaserSliceVars laser_slice;
    MinicopterVars minicopter;
    MotorcycleVars motorcycle;
    MuzzleShotVars muzzle_shot;
    ObjDebrisVars obj_debris;
    ObjExpandingBlastVars obj_expanding_blast;
    ObjGrowFadeVars obj_grow_fade;
    ObjKindVars obj;
    AfterVars after;
    AtVars at;
    AtPointVars at_point;
    AtPosVars at_pos;
    ChildVars child;
    CopyVars copy;
    FixedVars fixed;
    FromVars from;
    PairFromPlacementVars pair_from_placement;
    PlacedVars placed;
    PlacementVars placement;
    ProjectileVars projectile;
    RampVars ramp;
    RampInOutVars ramp_in_out;
    RangedVars ranged;
    ReplacementVars replacement;
    SoundLoopVars sound_loop;
    TableVars table;
    TimedVars timed;
    TypedVars typed;
    PickupVars pickup;
    PlacedActorVars placed_actor;
    ProjectileFireVars projectile_fire;
    ProximitySensorVars proximity_sensor;
    PylonSpawnChildObjVars pylon_spawn_child_obj;
    PyramidMineVars pyramid_mine;
    QuickFuchikomaM8BossVars quick_fuchikoma_m8_boss;
    QuickFuchikomaRocketVars quick_fuchikoma_rocket;
    ReactorControlRodsM9BossVars reactor_control_rods_m9_boss;
    RecedingWallDoorVars receding_wall_door;
    RedLaserBallVars red_laser_ball;
    RoadBarrierWithTrafficConeVars road_barrier_with_traffic_cone;
    RocketBoatRocketVars rocket_boat_rocket;
    RocketBoatShellVars rocket_boat_shell;
    RocketBoatShotVars rocket_boat_shot;
    RocketBoatSparkVars rocket_boat_spark;
    RocketBoatVars rocket_boat;
    RocketBoatSpawnSideObjVars rocket_boat_spawn_side_obj;
    RocketBoatWakeVars rocket_boat_wake;
    RocketDroneVars rocket_drone;
    RollingDoorVars rolling_door;
    S06HelicopterVars s06_helicopter;
    SeaMineVars sea_mine;
    SemiTruckMechVars semi_truck_mech;
    ShotSpawnTraceObjVars shot_spawn_trace_obj;
    SlotObjVars slot_obj;
    SoundEffectVars sound_effect;
    SoundObjVars sound_obj;
    SparkEmitObjVars spark_emit_obj;
    SparkEmitterVars spark_emitter;
    SparkFxVars spark_fx;
    SparkObjVars spark_obj;
    SparkOrShotVars spark_or_shot;
    SparkVars spark;
    SparkTrailKindVars spark_trail;
    TimedBurstVars timed_burst;
    SpeedboatWakeVars speedboat_wake;
    StageControllerVars stage_controller;
    StageVars stage;
    StateMachineVars state_machine;
    StationaryRocketLauncher2Vars stationary_rocket_launcher_2;
    StationaryRocketLauncherVars stationary_rocket_launcher;
    SupermechM12BossVars supermech_m12_boss;
    SupermechVars supermech;
    TankVars tank;
    TimeBombVars time_bomb;
    TimedEffectVars timed_effect;
    TimerTailVars timer_tail;
    TripleBarrelRobotVars triple_barrel_robot;
    TunnelMechLaserVars tunnel_mech_laser;
    TunnelMechLaserStrikeVars tunnel_mech_laser_strike;
    TunnelMechM2BossVars tunnel_mech_m2_boss;
    TunnelMechShotLaunchObjVars tunnel_mech_shot_launch_obj;
    TunnelMechShotVars tunnel_mech_shot;
    WalkerMechVars walker_mech;
    CamPathObjVars cam_path_obj;
    EnemyChildVars enemy_child;
    EnemySpawnRecordObjVars enemy_spawn_record_obj;
    WithMatrixVars with_matrix;
    SmgSoldierVars smg_soldier;
} ObjVars;
#define SOUND_PENDING 0x100

/* A pool object (96 of them at 0x80155b44 in S01): enemies, figures, projectiles, pickups. Objects are
 * list nodes; each step obj_list_run calls the handler whose slot index is in phase_slot[phase]
 * (phase 1 = behaviour, 3 = draw). obj_reset gives the field widths. Names are provisional where unk_. */
typedef struct Object {
    /* 0x000 */ Node node;
    /* 0x008 */ u8 phase_slot[4];
    /* 0x00C */ ObjLink type;
    /* 0x01C */ ObjLink script;
    /* 0x02C */ s16 rot_angles[3];
    /* 0x032 */ u8 pad_32[2];
    /* 0x034 */ s16 unk_34[3];
    /* 0x03A */ u8 pad_3A[2];
    /* 0x03C */ s32 unk_3C;
    /* 0x040 */ s32 ground_flags;
    /* 0x044 */ s16 extents[3];
    /* 0x04A */ s16 bound_radius; /* length of the unk_44 extents (obj_set_part_bounds) */
    /* 0x04C */ s32 unk_4C[3]; /* a copy of the position */
    /* 0x058 */ u8 pad_58[4];
    /* 0x05C */ s32 home_pos[3];
    /* 0x068 */ u8 pad_68[4];
    /* 0x06C */ s32 unk_6C[3];
    /* 0x078 */ u8 pad_78[4];
    /* 0x07C */ s16 unk_7C[3];
    /* 0x082 */ u8 pad_82[2];
    /* 0x084 */ s32 unk_84[3];
    /* 0x090 */ s32 ground_id;     /* a ground id, read through surface_of */
    /* 0x094 */ s32 unk_94[3];
    /* 0x0A0 */ u8 pad_A0[4];
    /* 0x0A4 */ u8 unk_A4[0x54]; /* reset by obj_clear_block54 (with the next two fields) */
    /* 0x0F8 */ s16 script_flag;
    /* 0x0FA */ u8 pad_FA[2];
    /* 0x0FC */ Placement *placement; /* what it was set up from (obj_init_from_place) */
    /* 0x100 */ ObjHandler handlers[4]; /* phase_slot indexes these, as word offsets into the object */
    /* 0x170 */ s32 callback;
    /* 0x174 */ void (*destructor)(struct Object *obj);
    /* 0x178 */ u8 index;
    /* 0x179 */ s8 rocket_marker;
    /* 0x17A */ s8 unk_17A;
    /* 0x17B */ u8 unk_17B;
    /* 0x17C */ s16 serial;
    /* 0x17E */ s16 kind;
    /* 0x180 */ s32 unk_180;
    /* 0x184 */ s16 damage;
    /* 0x186 */ s16 health;
    /* 0x188 */ s32 score;     /* passed to add_score when it dies */
    /* 0x18C */ s16 flags;       /* from obj_init_from_place; bit 2: unk_17A, bit 5: hit reaction */
    /* 0x18E */ s16 next_state;
    /* 0x190 */ s16 unk_190;
    /* 0x192 */ u8 free;
    /* 0x193 */ u8 solid_id;
    /* 0x194 */ struct ScriptCallEntry *call_table; /* script ops >= 0 call entry `op` */
    /* 0x198 */ struct StateEntry *state_table;     /* the handler states (obj_script_step) */
    /* 0x19C */ struct SoundVolume *sounds;         /* script op 4 plays entry `n` */
    /* 0x1A0 */ void *asset;
    /* 0x1A4 */ s32 unk_1A4;
    /* 0x1A8 */ s32 unk_1A8;
    /* 0x1AC */ s16 hit;          /* set to 1 by a hit */
    /* 0x1AE */ s16 unk_1AE;
    /* 0x1B0 */ s16 unk_1B0;
    /* 0x1B2 */ s16 unk_1B2;
    /* 0x1B4 */ u8 blocked_z;
    /* 0x1B5 */ u8 blocked_x;
    /* 0x1B6 */ s8 blocked_y;
    /* 0x1B7 */ u8 unk_1B7;
    /* 0x1B8 */ s32 unk_1B8;
    /* 0x1BC */ s32 unk_1BC;
    /* 0x1C0 */ s16 unk_1C0;
    /* 0x1C2 */ s8 hit_type;      /* of the last hit */
    /* 0x1C3 */ u8 hit_cooldown;  /* steps left; reloaded from hit_cooldown_max */
    /* 0x1C4 */ s16 hit_from;     /* obj_hits[].from of the last hit */
    /* 0x1C6 */ s16 unk_1C6;
    /* 0x1C8 */ u8 hit_cooldown_max;
    /* 0x1C9 */ u8 unk_1C9;
    /* 0x1CA */ s8 hit_mode;
    /* 0x1CB */ u8 unk_1CB;
    /* 0x1CC */ s32 unk_1CC;
    /* 0x1D0 */ s32 unk_1D0;
    /* 0x1D4 */ u8 pad_1D4[8];
    /* 0x1DC */ s32 unk_1DC;
    /* 0x1E0 */ s32 unk_1E0;
    /* 0x1E4 */ s16 width;
    /* 0x1E6 */ u16 height; /* the aim point is this much above the position (gun_shot_turn_to_player) */
    /* 0x1E8 */ s16 unk_1E8[4];
    /* 0x1F0 */ s32 x;
    /* 0x1F4 */ s32 y;
    /* 0x1F8 */ s32 z;
    /* 0x1FC */ s32 scale[3];     /* 0x1400 after a reset */
    /* 0x208 */ s32 vx;
    /* 0x20C */ s32 vy;           /* falling speed */
    /* 0x210 */ s32 vz;
    /* 0x214 */ s32 accel_x;
    /* 0x218 */ s32 accel_y;
    /* 0x21C */ s32 accel_z;
    /* 0x220 */ s16 yaw;
    /* 0x222 */ s16 pitch;
    /* 0x224 */ s16 roll;
    /* 0x226 */ s16 unk_226[5];
    /* 0x230 */ s32 speed;
    /* 0x234 */ s32 speed_accel;
    /* 0x238 */ s16 move_delta[3];
    /* 0x23E */ s16 turn;         /* the last yaw change */
    /* 0x240 */ u16 target_yaw;
    /* 0x242 */ s16 unk_242;
    /* 0x244 */ s16 wobble_count;
    /* 0x246 */ s16 wobble_offset;
    /* 0x248 */ ObjVars vars;
} Object; /* 0x288 */

#define OBJ_POOL_SIZE 96

/* ---- vsync.c: vertical blank task, display switch, frame rate, pad log ---- */

typedef struct VblankState {
    /* 0x00 */ u16 put_env;  /* show `env` at the next vblank */
    /* 0x02 */ u16 count;    /* vblanks while the pad log runs; wraps at 600 */
    /* 0x04 */ u16 pad_flags; /* bit 0: log pads; bit 15: log being reset */
    /* 0x06 */ u16 disp_on;  /* display mask as last set (0xFFFF: unknown) */
    /* 0x08 */ u16 draws;    /* frames drawn in this second */
    /* 0x0A */ s16 ticks;    /* vblanks in this second */
    /* 0x0C */ s16 fps;      /* frames drawn in the last second */
    /* 0x0E */ u16 unk_E;
    /* 0x10 */ void *env;    /* DISPENV to show */
    /* 0x14 */ void (*callback)(void); /* called once at the next vblank */
} VblankState;

#define PAD_LOG_SIZE 128

/* Pad readings taken at every vblank, consumed by the game loop. */
typedef struct PadLog {
    /* 0x00 */ s32 read;
    /* 0x04 */ s32 write;
    /* 0x08 */ s32 toggle;
    /* 0x0C */ u16 buttons[PAD_LOG_SIZE];
} PadLog;

/* ---- rand.c: two lagged-Fibonacci generators (taps 24 and 55) of 12-bit values ---- */

#define RAND_SIZE 64

typedef struct Rand {
    /* 0x00 */ s32 index;
    /* 0x04 */ u16 values[RAND_SIZE];
} Rand;

/* ---- math.c: angles (0x1000 = full turn), vectors, CLUT helpers ---- */

typedef struct VECTOR {
    s32 vx, vy, vz, pad;
} VECTOR;

typedef struct SVECTOR {
    s16 vx, vy, vz, pad;
} SVECTOR;

typedef struct RibbonRing {  /* last 64 points of a ribbon edge (s10) */
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 head;          /* newest point, & 0x3F */
    /* 0x08 */ s32 count;
    /* 0x0C */ SVECTOR points[64];
} RibbonRing;

typedef struct Vec3 {
    s32 x, y, z;
} Vec3;

/* ---- Input ---- */

typedef struct PadInput {
    s16 held;
    s16 pressed; /* held now and not the step before */
    s16 unk_04;  /* cleared by pad_input_reset */
    s16 unk_06;
} PadInput;

/* Buttons in the game's pad words (the PS1's digital pad bits, byte-swapped). */
#define PAD_L2 0x0001
#define PAD_R2 0x0002
#define PAD_L1 0x0004
#define PAD_R1 0x0008
#define PAD_TRIANGLE 0x0010
#define PAD_CIRCLE 0x0020
#define PAD_CROSS 0x0040
#define PAD_SQUARE 0x0080
#define PAD_SELECT 0x0100
#define PAD_START 0x0800
#define PAD_UP 0x1000
#define PAD_RIGHT 0x2000
#define PAD_DOWN 0x4000
#define PAD_LEFT 0x8000

/* The pad buttons for each action (get_key_config: one of 4 configurations of 12 actions, picked on the
 * options screen). Configuration 0: fire Square, jump Cross, Circle, Triangle, forward Up, back Down,
 * Right, Left, strafe R1/L1, R2, L2. */
typedef struct KeyConfig {
    u32 action[12]; /* button masks */
} KeyConfig;
#define KEY_FIRE 0
#define KEY_JUMP 1
#define KEY_FORWARD 4
#define KEY_BACK 5
#define KEY_STRAFE_RIGHT 8
#define KEY_STRAFE_LEFT 9

/* ---- Player and collision ---- */

/* A coroutine context: code address to resume at per level (0: the start), and a counter per level. */
typedef struct Coroutine {
    u32 level; /* 0-7 */
    u32 resume[8];
    s32 count[8];
} Coroutine;

/* A collider (the player's at PlayerObj.coll; solid objects start with one). The collision code
 * (collide_solids_y, push_out_of_solids_xz, collide_objects) moves its position out of the world and
 * reports contacts. */
typedef struct Collider {
    /* 0x00 */ s16 x0;
    /* 0x02 */ s16 state;           /* 1: the box is set (collider_box); collider_begin applies size_delta */
    /* 0x04 */ s16 size[3];         /* half-sizes of the turned box (0: not set yet) */
    /* 0x0A */ s16 offset[3];       /* the box centre from the position, turned */
    /* 0x10 */ s16 offset_delta[3]; /* change of offset at the last collider_box */
    /* 0x16 */ s16 size_delta[3];   /* change of size at the last collider_box */
    /* 0x1C */ s32 sub[4];          /* a copy of the object's sub-position */
    /* 0x2C */ s16 angle[3];        /* orientation (for the player: its rot, negated) */
    /* 0x32 */ s16 x32;
    /* 0x34 */ s16 dim[3];          /* half-width, height, half-depth */
    /* 0x3A */ u8 unk_3A[2];
    /* 0x3C */ s16 pos[3];          /* this step's move in world units (in; cut by the collision) */
    /* 0x42 */ u8 unk_42[0xA];
    /* 0x4C */ u8 contact;          /* CONTACT_* */
    /* 0x4D */ u8 contact_type_mask;
    /* 0x4E */ u16 contact_id;      /* what it touched: low byte an object index, high byte a type */
    /* 0x50 */ u8 unk_50[4];
    /* 0x54 */ s32 solid;           /* solid_alloc index, -1 when freed */
} Collider; /* 0x58 */
#define CONTACT_WALL_A 0x01
#define CONTACT_WALL_B 0x04
#define CONTACT_FLOOR 0x08
#define CONTACT_CEILING 0x10
#define CONTACT_20 0x20

/* 1 when point a0..a2 lies within r0..r2 of b0..b2 on all three axes (tested in that order). */
#define BOX_OVERLAP(a0, b0, r0, a1, b1, r1, a2, b2, r2) \
    (in_range(a0, b0, r0) && in_range(a1, b1, r1) && in_range(a2, b2, r2))

/* The player's object (not in the object pool). Angles and positions are 20.12 fixed point. */
typedef struct PlayerObj {
    /* 0x000 */ s16 rot[3];
    /* 0x006 */ u16 unk_06;
    /* 0x008 */ s16 angle[3];     /* the orientation (rotation matrix from [1], [0], [2]) */
    /* 0x00E */ u16 unk_0E;
    /* 0x010 */ u32 pose;         /* 0x31, 0x71, 0xf1 or 0x211, set by player_control each step */
    /* 0x014 */ u32 flags;        /* ON_GROUND, BLOCKED_ABOVE, OUT_OF_AREA, ... */
    /* 0x018 */ u32 x18;
    /* 0x01C */ u32 unk_1C;
    /* 0x020 */ s32 pos[3];       /* the position after collision, copied to x, y, z */
    /* 0x02C */ u32 unk_2C;
    /* 0x030 */ s32 sub[4];       /* the position being moved */
    /* 0x040 */ s32 move[3];      /* this step's move (the velocity, then turned into the object's frame) */
    /* 0x04C */ u8 unk_4C[4];
    /* 0x050 */ s16 delta[3];     /* the whole units moved this step (mover_apply); 0 when still */
    /* 0x056 */ s16 unk_56;
    /* 0x058 */ s32 x_max;
    /* 0x05C */ s32 y_max;
    /* 0x060 */ s32 unk_60;
    /* 0x064 */ u32 ground;       /* what it stands on: (object index + 1) << 8 | type (surface_of) */
    /* 0x068 */ s32 x_min;
    /* 0x06C */ s32 y_min;
    /* 0x070 */ s32 unk_70;
    /* 0x074 */ s32 unk_74;
    /* 0x078 */ Collider coll;
    /* 0x0D0 */ s32 x, y, z;
    /* 0x0DC */ s32 yaw, pitch, roll;
    /* 0x0E8 */ s32 vx, vy, vz;   /* vy negative is up */
    /* 0x0F4 */ s32 spin_yaw, spin_pitch, spin_roll;
    /* 0x100 */ s32 strafe_speed; /* sideways (strafe keys) */
    /* 0x104 */ s32 walk_speed;   /* forward/back keys */
    /* 0x108 */ s32 gravity;
    /* 0x10C */ u8 unk_10C[4];
    /* 0x110 */ u32 x110;         /* set on landing, cleared on take-off */
    /* 0x114 */ u32 x114;
    /* 0x118 */ s32 slowdown;     /* from 0x10 up it slows the player (player_slowdown) */
    /* 0x11C */ Coroutine co;
} PlayerObj;
/* The half-sizes x, y, z at 0x18..0x1C, read as u16 (lhu). */
#define PLAYER_HALF(p) ((u16 *)&(p)->x18)
#define ON_GROUND 0x1
#define BLOCKED_ABOVE 0x2
#define OUT_OF_AREA 0x10000
/* The record svc_get_shared_state returns (the boot exe's persistent state?): stage_begin stores the next mission
 * at 0xD0, dev_mode reads the word at 0xC0. */
typedef struct StageRecord {
    /* 0x00 */ u8 unk_00[0xC0];
    /* 0xC0 */ s32 unk_C0;
    /* 0xC4 */ u8 unk_C4[0xC];
    /* 0xD0 */ s32 next_mission;
} StageRecord;

/* A grenade's aim, copied unaligned into a GrenadeMover at 0x24 (launch_grenade: lwl/lwr + swl/swr). */
typedef struct AimPacket {
    s16 pitch;
    s16 yaw;
    s32 unk_04;
} __attribute__((packed)) AimPacket;

/* The record an object's placement pointer (0xFC) leads to in some kinds, with a target position at 0x28
 * (obj_aim_jitter_placement, func_800BB234 aim at it, func_800BC0E8 measures the distance). */
typedef struct PlacedTarget {
    u8 unk_00[0x28];
    s32 x, y, z;
} PlacedTarget;

/* A spark-pool record (spark_alloc) used as a missile (launch_missile). */
typedef struct Missile {
    s16 active;    /* 0x00: set by spark_alloc */
    s16 flags;     /* 0x02 */
    s32 origin[3]; /* 0x04: the launch position */
    u8 unk_10[4];
    s32 pos[3];    /* 0x14 */
    u8 unk_20[0x14];
    AimPacket aim; /* 0x34: copied from the caller */
    s32 speed;     /* 0x3C */
    s32 age;       /* 0x40 */
} Missile;

/* An Interp record's script view (script_runner_step): a script is a count, then (field, value) pairs that
 * set the record's halfwords. */
typedef struct ScriptRunner {
    u16 pos;
    u16 speed;
    s16 unk_04;
    s16 running; /* interp_reset sets it to 1 */
    s16 repeat;
    s16 cursor;
    s16 *script;
} ScriptRunner;
typedef struct ScriptEntry {
    s16 field;
    s16 value;
} ScriptEntry;

/* The template fx_spawn_template copies into a free FxEffect. */
typedef struct RecTemplate {
    u8 used;    /* copied to the record's used flag */
    u8 color_r;
    u8 color_g;
    u8 color_b;
    s16 progress;
    s16 progress_step;
    s32 size;
    s32 size_speed;
    s32 size_accel;
    s32 unk_14;
} RecTemplate;

/* A fade item's levels as words (fade_list_update reads them unsigned). */
typedef struct FadeWords {
    u8 unk_00[0x14];
    u16 level;
    u16 step;
    u16 pos;
    u16 pos_step;
} FadeWords;

/* Parts of the 0x84-byte view records rec_set_part sets: a 3x3 matrix and three words at 0x34, then
 * s16 triples at 0x54. */
typedef struct LightColourMatrix {
    s16 m[3][3];
    s16 pad_12;
    s32 w[3];
} LightColourMatrix;
typedef struct LightVector {
    s16 x, y, z;
    s16 pad;
} LightVector;

/* An entry with a debug name and a key (named_entry_run; get_area_entry returns one). */
typedef struct NamedEntry {
    u8 *name;
    u8 *key; /* a record for record_data_get */
} NamedEntry;

/* The current area's data block (get_area_entry); s12 func_800CCC44 reads a word through a row of the
 * 8-byte table at 0x24. */
typedef struct AreaRes {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ s32 *value;
} AreaRes;
typedef struct AreaRow {
    /* 0x00 */ AreaRes *res;
    /* 0x04 */ s32 unk_04;
} AreaRow;
typedef struct AreaData {
    /* 0x00 */ u8 pad_00[0x24];
    /* 0x24 */ AreaRow *rows;
} AreaData;

/* 32 colours split into shifted 5-bit fields (palette_expand, from palette_colours). */
typedef struct ColorShift {
    u16 r;
    u16 g;
    u16 b;
    u16 unk_06;
} ColorShift;
typedef struct TextRgb {
    s16 r;
    s16 g;
    s16 b;
} TextRgb;

/* A list record (placement_list_pop drops its first 0x20-byte block: the words from 0x24 on move down over 0x04,
 * the 4-byte header stays). */
typedef struct ListRecord {
    /* 0x00 */ s16 first;
    /* 0x02 */ s16 second;
    /* 0x04 */ s32 body[15];
} ListRecord;
typedef struct ListBlock {
    s32 w[8];
} ListBlock;

/* 0x14-byte UI records (D_80121F80; frame_env_build, ui_rec_setup fill them, ui_rec_advance moves one). */
typedef struct UiRecord {
    u8 unk_00[0x0A];
    u16 rect_y;
    u8 rect_size[6];
    u8 flag; /* 0x12 */
    u8 unk_13;
} UiRecord;

#define SCORE_MAX 9999999 /* player_score (set_score) */
#define COUNT_MAX 9999    /* mission_limit (set_mission_limit), kill_count */
#define GRENADES_MAX 3    /* grenade_count (grenades_add, set_grenades) */

/* ---- Engine tables (addresses are S01's) ---- */

#define ABS(x) ((x) >= 0 ? (x) : -(x)) /* evaluates x twice, as the original does with calls */
/* angle wrapped to -0x7FF..0x800 */
#define WRAP12(v) ({ s32 _v = (v) & 0xFFF; if (_v > 0x800) _v -= 0x1000; _v; })
/* a - b, both wrapped, the result wrapped again (fuchikoma_chase_update) */
#define YAW_DIFF(a, b) ({ s32 _x = WRAP12(a); s32 _w = (_x - WRAP12(b)) & 0xFFF; if (_w > 0x800) _w -= 0x1000; _w; })
#define CLAMP_HI(x, hi) ((x) > (hi) ? (hi) : (x)) /* MIN with the test the other way round */
/* CLAMP_HI through a variable set twice: keeps the `li v1,hi; move v0,v1` the ternary loses (enemy_walk_step) */
#define CLAMP_HI_VAR(x, hi) ({ s32 _c = (x); if (_c > (hi)) { _c = (hi); } _c; })
#define NOT_NEGATIVE(a) ((a) < 0 ? 0 : (a))
#define LERP(from, to, t) (((to) - (from)) * (t) / 0x1000 + (from)) /* t: 0x1000 = all `to` */

typedef struct CVECTOR {
    u8 r, g, b, cd;
} CVECTOR;

/* Functions that set a part of a table record take a pointer to that part (`&cameras[i].rot`), so the
 * part's offset is folded into the table address. */

/* Records of the table at rec_table_pos (stride 0x18), read by cam_world_to_screen: a world position and a size. */
typedef struct WorldPoint {
    s32 x;
    s32 y;
    s32 z;
    u16 size;
} WorldPoint;

/* cam_world_to_screen's result: the screen position (SXY2), the clamped depth (at least 0x80) and the size on screen. */
typedef struct ProjectedPoint {
    s16 sx;
    s16 sy;
    s16 depth;
    s16 size;
} ProjectedPoint;

/* Cameras (0x8013657c): cam_set_pos sets the position, cam_set_rot the angles. */
typedef struct Camera {
    /* 0x00 */ VECTOR pos;
    /* 0x10 */ SVECTOR rot; /* pitch, yaw, roll */
    /* 0x18 */ s16 scale[2];
    /* 0x1C */ s16 rec_index;
    /* 0x1E */ s16 user_count;
} Camera; /* 0x20 */

/* Views (0x8013667c), the screen layers: view_set_on turns one on, set_view_offset and view_set_clip_size
 * place it. The scaled rotation of a view is at +0x38/+0x60 (FINDINGS "Camera"). */
typedef struct View {
    /* 0x00 */ s16 on;
    /* 0x02 */ s16 parent;
    /* 0x04 */ s16 depth;
    /* 0x06 */ s16 camera; /* index into cameras; < 0: none */
    /* 0x08 */ s16 x, y;   /* screen centre */
    /* 0x0C */ s16 w, h;
    /* 0x10 */ s16 unk_10, unk_12, unk_14, unk_16;
    /* 0x18 */ s16 clip_w, clip_h; /* view_set_clip_size: even size, at most twice w/h */
    /* 0x1C */ CVECTOR colour; /* view_set_colour */
    /* 0x20 */ CVECTOR colour_b; /* view_set_colour_b */
    /* 0x24 */ CVECTOR colour_c; /* view_set_colour_c */
    /* 0x28 */ s32 ready;
    /* 0x2C */ u8 unk_2C[0x1E];
    /* 0x4A */ s16 unk_4A; /* shadow_pass_draw: scaled by 0x1600/0x1000 into LO */
    /* 0x4C */ u8 pad_4C[8];
    /* 0x54 */ s16 vram_x, vram_y, vram_w, vram_h; /* night_vision_draw_overlay: the view's rect in VRAM */
    /* 0x5C */ u8 screen_offset[4];
    /* 0x60 */ s16 rot[3][3]; /* camera rotation matrix (GTE R) */
    /* 0x72 */ u8 pad_72[0x2E];
    /* 0xA0 */ s32 ot;
    /* 0xA4 */ u8 pad_A4[4];
} View; /* 0xA8 */

/* A stage sound handle (FINDINGS "Stage sound module"), 0x44 bytes each at 0x801337bc; handle 0 is none. */
typedef struct SoundHandle {
    /* 0x00 */ s32 id;
    /* 0x04 */ u8 voices[8]; /* the two voices */
    /* 0x0C */ s16 delay;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 volume;
    /* 0x12 */ s16 pan;
    /* 0x14 */ s16 pitch;
    /* 0x16 */ u8 unk_16[0x22];
    /* 0x38 */ void (*update)();
    /* 0x3C */ void *owner;      /* what it follows: a position (&obj->x) or the update's record */
    /* 0x40 */ u8 flags;         /* bits 0-3 set by sound_set_flag_bit0, sound_set_flag_bit1, sound_set_flag_bit2, sound_set_flag_bit3 */
    /* 0x41 */ u8 changed[2];
    /* 0x43 */ u8 next;          /* the next handle of a chain that starts at handle 0 (sound_stop_all) */
} SoundHandle;

/* A solid (32 of them at `solids`): a collision shape made of boxes. */
typedef struct Solid {
    /* 0x000 */ s16 state;       /* 1: active */
    /* 0x002 */ s16 node_root;     /* -1 when allocated */
    /* 0x004 */ s16 radius;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s32 *owner;      /* its words 7-9 are the position (<< 12) the part offsets add to; 0: unused */
    /* 0x00C */ SVECTOR box[32]; /* solid_set_box */
    /* 0x10C */ SVECTOR box_b[32]; /* solid_set_box_b */
    /* 0x20C */ s16 unk_20C;     /* cleared when a box changes */
    /* 0x20E */ u16 unk_20E;
    /* 0x210 */ u32 part_mask;   /* bit n: record n of unk_218 is in use (solid_copy copies those) */
    /* 0x214 */ s32 part_enable_mask;
    /* 0x218 */ u8 parts[0x300];
} Solid; /* 0x518 */

/* What hit each pool object this step (128 at 0x801396d0, by object index). */
typedef struct ObjHit {
    /* 0x00 */ s16 from;
    /* 0x02 */ s16 damage;
    /* 0x04 */ u8 type;   /* damage factors per type in d_801185DC */
    /* 0x05 */ u8 flags;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} ObjHit;

/* A pchr entry (pchr_table, pchr_count used). */
typedef struct Pchr {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 link_count; /* > 0: `link` names the entry this one continues in */
    /* 0x04 */ u16 link;       /* low 11 bits: an index */
    /* 0x06 */ s16 unk_06;    /* blend entries: the second source index (pchr_blend) */
    /* 0x08 */ s32 *data;     /* [0]: count, then halfword indexes (pchr_set_entry_flags) */
    /* 0x0C */ s32 *unk_0C; /* a sequence pointer (pchr_poses_build) */
    /* 0x10 */ s16 bounds_radius;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 far_bias;
    /* 0x18 */ s16 angle;
    /* 0x1A */ s16 unk_1A;
} Pchr; /* 0x1C */
/* A Pchr's first four words seen as list pointers: pchr_lists_build's blend pass writes its result
 * lists over the halfword fields at 0x00..0x07. */
typedef struct PchrLists {
    /* 0x00 */ s32 *colours; /* colour_intpl_list / vtx_rotate_list */
    /* 0x04 */ s32 *list_04; /* colour_list_intpl */
    /* 0x08 */ s32 *quads;   /* quad_list_build */
    /* 0x0C */ s32 *poses;   /* pose_list_intpl / gte_transform_to_end */
} PchrLists;
#define PCHR_LISTS(entry) ((PchrLists *)(entry))

/* A slot of the 8-byte model table model_slots (count model_slot_count, at most 32): model_slot_new makes one. */
typedef struct ModelSlot {
    s16 pchr; /* pchr_count when made */
    s16 y;
    s16 x;
    s16 unk_06;
} ModelSlot;

/* Six values reset by interp_reset to 0, 0, 0, 1, 0, 0 (state 2 of the records below restarts them). */
typedef struct Interp {
    /* 0x00 */ s16 v[6];
    /* 0x0C */ u8 unk_0C[4];
} Interp; /* 0x10 */
typedef struct InterpRec18 {
    s32 state;
    Interp part;
    s32 script_data; /* script data base (interp_alloc_record) */
} InterpRec18;
typedef struct InterpRec1C {
    s32 state;
    Interp part;
    u8 unk_14[8];
} InterpRec1C;
/* Header (0x1A bytes) of an InterpRec2C script: a scrolling, waving textured strip. */
typedef struct ScrollStripHeader {
    /* 0x00 */ s16 index;
    /* 0x02 */ s16 x_off;
    /* 0x04 */ s16 y_off;
    /* 0x06 */ s16 width;
    /* 0x08 */ s16 height;
    /* 0x0A */ s16 tex_x;
    /* 0x0C */ s16 tex_y;
    /* 0x0E */ s16 tex_w;
    /* 0x10 */ s16 tex_h;
    /* 0x12 */ s16 wave_x_period;
    /* 0x14 */ s16 wave_x_amp;
    /* 0x16 */ s16 wave_y_amp;
    /* 0x18 */ s16 wave_y_scale;
} ScrollStripHeader;
typedef struct InterpRec2C {
    s32 state;
    Interp part[2];
    /* 0x24 */ ScrollStripHeader *key;
    /* 0x28 */ s32 track;
} InterpRec2C;
typedef struct InterpRec38 {
    s32 state;
    Interp part[3];
    u8 script[4];
} InterpRec38;

/* 8 records of 0x234 bytes at track_table: each turns an angle and advances a counter (track_step_all). */
typedef struct Track {
    /* 0x000 */ s16 enabled;
    /* 0x002 */ s16 last_row;
    /* 0x004 */ s16 write_col;
    /* 0x006 */ s16 write_row;
    /* 0x008 */ s16 unk_08;
    /* 0x00A */ u16 mode; /* 0-3 */
    /* 0x00C */ u8 colour[4][4]; /* four slots (track_set_slot sets 3 bytes of one; track_reset_all clears them) */
    /* 0x01C */ s16 origin_x;
    /* 0x01E */ s16 origin_y;
    /* 0x020 */ u8 unk_20[6];
    /* 0x026 */ u16 rows;
    /* 0x028 */ s16 pos_x;
    /* 0x02A */ s16 pos_y;
    /* 0x02C */ u8 angle_step[2];
    /* 0x02E */ s16 angle;
    /* 0x030 */ s16 phase_step;
    /* 0x032 */ s16 phase;
    /* 0x034 */ s32 slots[0x80];
} Track; /* 0x234 */

/* An entry of the grid of pending things (grid_entries points to them): due entries move from the pending
 * list (grid_pending_head) into the bucket of their 2048-unit x/z cell (grid_pending_step). */
#define LIST_END (-0x8000) /* any negative index ends a list */
typedef struct GridEntry {
    /* 0x00 */ s16 next;   /* index of the next entry */
    /* 0x02 */ s16 delay;  /* steps to wait; negative: remove */
    /* 0x04 */ u8 flags;   /* bits 0-1 state (3: removed), bit 4: check first */
    /* 0x05 */ u8 kind;    /* < 0x80: handler in grid_kind_handlers (grid_entry_handle) */
    /* 0x06 */ s16 unk_06; /* nonzero: goes to the overflow bucket */
    /* 0x08 */ s32 x, y, z;
    /* 0x14 */ u8 unk_14[0x2C];
} GridEntry; /* 0x40 */
typedef struct GridKind {
    s32 (*handler)(GridEntry *entry);
    s32 unk_04;
} GridKind;

/* A queued request (req_queue, count req_queue_count): three arguments and a kind (0-4). */
typedef struct Request {
    s32 a, b, c;
    u32 kind;
} Request;

/* 32 records of 0x34 bytes at fx_rec34_pool (fx_rec34_init sets one up, fx_rec34_reset resets one). */
typedef struct FxRecord {
    /* 0x00 */ s32 pos[3];
    /* 0x0C */ u8 unk_0C[4];
    /* 0x10 */ s16 phase;
    /* 0x12 */ s16 phase_speed;
    /* 0x14 */ s16 clamped_phase; /* unk_10, at least 0x800 */
    /* 0x16 */ s16 active;
    /* 0x18 */ s32 radius_motion[4];
    /* 0x28 */ s32 depth_sorted;
    /* 0x2C */ s32 step_fn;
    /* 0x30 */ u8 color_r;
    /* 0x31 */ u8 color_g;
    /* 0x32 */ u8 color_b;
    /* 0x33 */ u8 unk_33;
} FxRecord;
/* The parameter block fx_rec34_init copies into a FxRecord. */
typedef struct FxRecordParams {
    /* 0x00 */ u8 b0, b1, b2, b3;
    /* 0x04 */ s16 h4;
    /* 0x06 */ s16 h6;
    /* 0x08 */ s32 w[4];
} FxRecordParams;

/* 0x84-byte records at light_sets (current index light_env_index): three s16, 24-bit colours at 8/0xC/0x10,
 * and a screen point (rec_set_point). */
typedef struct ScreenPoint {
    /* 0x00 */ s32 out_a; /* point_calc_projection's results */
    /* 0x04 */ s32 out_b;
    /* 0x08 */ s16 x, y;
    /* 0x0C */ s16 scale;
    /* 0x0E */ s16 z;
    /* 0x10 */ s16 tex_flag;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 flag;
    /* 0x16 */ u8 unk_16[2];
} ScreenPoint;
typedef struct LightSet {
    /* 0x00 */ s16 v[3];
    /* 0x06 */ u8 unk_06[0xE];
    /* 0x14 */ s16 light_dir[3][3]; /* light direction matrix: one unit vector (0x400) per row, light_set_dir_from_angles */
    /* 0x26 */ u8 unk_26[0x46];
    /* 0x6C */ ScreenPoint point;
} LightSet;

/* 0x14-byte records at point_slots (rec_set_pos, point_set_extra). */
typedef struct PointSlot {
    /* 0x00 */ s16 x, y, z;
    /* 0x06 */ u16 flags; /* bit 15: values set */
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 unk_0E[2];
    /* 0x10 */ s32 colour; /* 5-bit-shifted components: blue << 16 | green << 8 | red (rec_set_rgb) */
} PointSlot;

/* 16 records of 0x14 bytes at text_slots; text_slots_clear clears the s16 at +0. */
typedef struct TextSlotEntry {
    s16 unk_00;
    u8 unk_02[0x12];
} TextSlotEntry;

/* What stage_screen_size returns: the screen size. */
typedef struct ScreenSize {
    s16 w;
    s16 h;
} ScreenSize;

typedef struct VecPair {
    SVECTOR a;
    SVECTOR b;
} VecPair;
/* What get_stage_setup_block returns (layout unknown apart from these pairs). */
typedef struct StageSetupBlock {
    /* 0x00 */ u8 unk_00[0x34];
    /* 0x34 */ s32 x; /* start position */
    /* 0x38 */ s32 y;
    /* 0x3C */ s32 z;
    /* 0x40 */ u8 pad_40[4];
    /* 0x44 */ u16 pitch; /* start angles, low 12 bits */
    /* 0x46 */ u16 yaw;
    /* 0x48 */ u16 roll;
    /* 0x4A */ u8 pad_4A[0x42];
    /* 0x8C */ VecPair pairs[1];
} StageSetupBlock;

/* A script's running state (script_advance, script_start). */
typedef struct ScriptState {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 *pc;
    /* 0x08 */ u16 a;
    /* 0x0A */ u16 b;
    /* 0x0C */ u16 c;
    /* 0x0E */ u16 d;
} ScriptState;

/* A script context (script_jump starts one; script_run_neg_ops runs an opcode). */
typedef struct Script {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ ScriptState state;
} Script;

/* A record probe_clip_to_column tests (probe_test_both_sides tests it twice, mirrored). */
typedef struct Probe {
    /* 0x00 */ s32 x0;
    /* 0x04 */ s32 x1;
    /* 0x08 */ s32 y0;
    /* 0x0C */ s32 y1;
    /* 0x10 */ s32 half_extent;
} Probe;

/* The player's mover (`mover`, mover_move, mover_apply, mover_set). */
typedef struct Mover {
    s32 distance; /* 20.12, between mover_min_dist and mover_max_dist whole units */
    s32 yaw;      /* 20.12 angle, wraps at 24 bits */
    s32 pitch;    /* 20.12 angle, at most +-0x400 whole units */
} Mover;

/* A record cam_track_part_clear clears. */
typedef struct CamTrackPart {
    /* 0x00 */ s32 unk_00[3];
    /* 0x0C */ s32 start_time;
    /* 0x10 */ u8 mode;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ s16 duration; /* mode 3: value_queue_get index */
    /* 0x14 */ union {
        s16 keys[3][2]; /* mode 2: from, to */
        struct {
            s16 delay;
            s16 offset;
            s16 rate;
            s16 weight[3];
        } curve; /* mode 3 */
    } anim;
} CamTrackPart;

/* 0x18-byte records at rec_table (count rec_count): rec_set_value sets `value`. */
typedef struct ModelGroup {
    s32 unk_00[4];
    s32 value;
    s16 id;
    s16 pos; /* rec_pos_total when rec_add added it */
} ModelGroup;

/* The name table name_table_root (and its copy name_table_cwd) points to: 0x18-byte entries after the header
 * pointer stage_data_ptr (get_stage_table_entry). name_table_find searches it by key and text; name_table_record returns the
 * entry name_key_endian_swap picks for the found one. */
typedef struct NameEntry {
    /* 0x00 */ u8 key;  /* name_key of the name */
    /* 0x01 */ u8 used; /* 0 ends the table */
    /* 0x02 */ char text[0x16];
} NameEntry;

/* 16 records at part_slot_recs (count part_slot_count): part_slots_append appends a value. */
typedef struct PartSlot {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 state;
    /* 0x04 */ s16 wait_timer;
    /* 0x06 */ s16 script_index;
    /* 0x08 */ s32 value;
} PartSlot;

/* 0x14-byte records at aobj_table: aobj_fill_value sets `value` of a run of them. */
typedef struct AobjEntry {
    s16 value;
    s16 flag; /* reset to 1 */
    s32 unk_04[4];
} AobjEntry;

/* An entry recip_table_fill completes with the inverse of its divisor. */
typedef struct Recip {
    s16 unk_0;
    s16 unk_2;
    s16 divisor;
    s16 inverse; /* 0x80000 / divisor */
} Recip;

/* An angle and a value at keyframe_cells (keyframe_lookup: keyframe-angle lookup). */
typedef struct KeyframeCell {
    s16 angle;
    u8 value;
    u8 pad;
} KeyframeCell;

/* 6 slots at lock_slots, flags in the byte table lock_flag_counts after them (lock_set_mode). */
typedef struct Slot14 {
    s16 id;
    s16 flag_index;
    u8 unk_04[0x10];
} Slot14;

/* Node pairs at node_pair_table (node_tree_eval). */
typedef struct NodePair {
    s16 left;
    s16 right;
    s16 left_weight;
    s16 right_weight;
} NodePair;

/* The UI item pool (0x7C bytes each at ui_item_pool): ui_item_alloc(update) allocates one (its index & 0xFF). */
typedef struct Item7C {
    /* 0x00 */ u8 unk_00[0x44];
    /* 0x44 */ void (*update)(void);
    /* 0x48 */ s32 colour;
    /* 0x4C */ s16 x0;
    /* 0x4E */ s16 y0;
    /* 0x50 */ s16 x;
    /* 0x52 */ s16 y;
    /* 0x54 */ s16 gfx_index;
    /* 0x56 */ s16 width;
    /* 0x58 */ union {
        u8 *text;
        s32 value;
    } arg;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 slide_speed;
    /* 0x64 */ s32 left_x;
    /* 0x68 */ s32 right_x;
    /* 0x6C */ u8 unk_6C[0xC];
    /* 0x78 */ s16 kind;
    /* 0x7A */ u8 prev; /* byte links; item 0 is the head (first free at +0x60, last used at +0x64) */
    /* 0x7B */ u8 next;
} Item7C;

/* Sparks: 8 of 0x44 bytes at spark_pool (sparks_step spawns, sparks_reset). */
typedef struct Spark {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 target; /* target object slot, 0 for none */
    /* 0x04 */ s32 prev[3]; /* position before the last step (fixed point, as x/y/z) */
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ s32 x, y, z;
    /* 0x20 */ u8 unk_20[4];
    /* 0x24 */ s32 vx, vy, vz;
    /* 0x30 */ u8 unk_30[4];
    /* 0x34 */ s16 pitch;
    /* 0x36 */ s16 yaw;
    /* 0x38 */ u8 unk_38[4];
    /* 0x3C */ s32 speed;
    /* 0x40 */ s32 age;
} Spark; /* 0x44 */

/* A model's geometry as model_mark_squares walks it (marks axis-aligned quads). */
typedef struct Face {
    /* 0x00 */ u8 unk_00[6];
    /* 0x06 */ u16 flags; /* 0x100: axis-aligned rectangle */
    /* 0x08 */ u8 idx[4];
} Face; /* 0xC */
typedef struct FaceTail {
    u16 flags;
    u8 unk_02[3];
    u8 last;
    u8 unk_06[6];
} FaceTail;
typedef struct FaceList {
    s32 count;
    Face faces[1];
} FaceList;
typedef struct Vert {
    s16 x;
    s16 unk_02;
    s16 y;
    s16 unk_06;
} Vert;
typedef struct Model {
    /* 0x00 */ u8 unk_00[4];
    /* 0x04 */ u8 *vertices; /* vertex k at vertices - 4 + 8k */
    /* 0x08 */ FaceList *list;
} Model;

/* A cursor over s16 entries (entry_cursor_seek). */
typedef struct EntryCursor {
    /* 0x00 */ s32 value;
    /* 0x04 */ s16 *entry;
} EntryCursor;

typedef struct Bytes8 {
    u8 b[8];
} Bytes8;

/* Two halfwords per entry, 8 at half_pairs. */
typedef struct HalfPair {
    s16 a, b;
} HalfPair;

/* An id table (id_table): a count and 16 ids, -1 when free (id_table_init). */
typedef struct IdTable {
    s32 count;
    s16 id[16];
} IdTable;

/* Particles: 0x24-byte records at particle_free_head in a doubly linked free list by byte index; record 0 is the
 * list head (its first words are the first free record and the free count). particle_spawn_burst spawns. */
typedef struct Particle {
    /* 0x00 */ s32 x, y, z;
    /* 0x0C */ s32 vx, vy, vz;
    /* 0x18 */ s16 rot_y, rot_x, rot_z;
    /* 0x1E */ s16 scale_offset;
    /* 0x20 */ u8 age;
    /* 0x21 */ u8 kind_variant;
    /* 0x22 */ u8 prev;
    /* 0x23 */ u8 next;
} Particle;

/* The 8 short-lived records (records_step ages them, frees them at 40). */
typedef struct Record {
    /* 0x00 */ s16 age; /* negative: free */
    /* 0x02 */ s16 pchr_slot;
    /* 0x04 */ s32 x, y, z;
    /* 0x10 */ u8 pad_10[4];
    /* 0x14 */ s16 rot[3];
    /* 0x1A */ u8 pad_1A[0x12];
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 pad_34[0x480];
} Record; /* 0x4B4 */

/* 16 timers (timers_update). */
typedef struct Timer {
    u8 unk_00[4];
    u16 phase; /* 0x1000: expired */
    u8 unk_06[0xE];
} Timer; /* 0x14 */

/* Effect records (0x18 bytes) after the 0x28-byte header of the list at spark_list, linked by byte index
 * into one chain per colour (the top byte of the colour word); the header holds each chain's tail link. */
typedef struct SparkRec {
    /* 0x00 */ s32 x, y, z;
    /* 0x0C */ s16 yaw, pitch, roll, unk_12;
    /* 0x14 */ u8 colour[3]; /* the colour word overlaps these and `next` */
    /* 0x17 */ u8 next;
} SparkRec;
typedef struct SparkList {
    /* 0x00 */ u8 head[8];
    /* 0x08 */ u8 *tail[8];
    /* 0x28 */ SparkRec items[0xFF];
} SparkList;
/* The count read as a struct member: GCC 2.7 lets a load of a plain scalar global move above earlier stores
 * through pointers (a struct/array store can't alias a scalar), but not a struct member's. The spark adders
 * whose count load stays below the scratch-vector stores read it this way (func_800C3858 in S04). */
typedef struct SparkCount { s16 n; } SparkCount;
#define SPARK_COUNT (((SparkCount *)&spark_count)->n)
/* cam_pos/88/8C (the camera position, per its readers) as one Vec3, for the same reason. */
#define VEC_80139584 (*(Vec3 *)&cam_pos)

/* Keyframes (func_800C2114): steps until the next one (-1 ends the list) and a value. */
typedef struct Keyframe {
    s16 time;
    u16 value;
} Keyframe;

/* Parameters func_800BB148 sets to their defaults (S01: D_801204FC). */
typedef struct ShotParams {
    /* 0x00 */ s32 speed;
    /* 0x04 */ s32 max_speed;
    /* 0x08 */ s32 speed_delta;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 hit_effect_index;
    /* 0x10 */ s16 launch_age;
    /* 0x12 */ s16 homing_duration;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 smoke_limit;
    /* 0x1A */ s16 smoke_period;
    /* 0x1C */ s16 smoke_arg;
    /* 0x1E */ s16 turn_start_age;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 turn_step;
} ShotParams;

/* 0x20-byte records at scene_models (count scene_model_count; scene_model_add adds one). */
typedef struct SceneModel {
    /* 0x00 */ s32 handle;
    /* 0x04 */ s32 offset_x;
    /* 0x08 */ s32 offset_y;
    /* 0x0C */ s32 offset_z;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s16 scale[3]; /* model_set_scale */
    /* 0x1A */ u8 unk_1A[2];
    /* 0x1C */ u8 layer;
    /* 0x1D */ u8 flag;      /* scene_model_set_flag */
    /* 0x1E */ s16 unk_1E;
} SceneModel;

/* One mover record at grenade_pool (grenades_update moves it, grenade_pool_init clears it). */
typedef struct GrenadeMover {
    /* 0x00 */ s16 active;
    /* 0x02 */ u16 age;
    /* 0x04 */ s32 pos[3];
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ s32 vel[3];
    /* 0x20 */ u8 unk_20[4];
    /* 0x24 */ s16 pitch;
    /* 0x26 */ s16 yaw;
    /* 0x28 */ u8 unk_28[4];
    /* 0x2C */ s32 speed;
} GrenadeMover;

/* Clamp boxes (0x20-byte records; clamp_table_ptr + 4 points to them, clamp_point_to_box). */
typedef struct ClampBox {
    Vec3 min;
    s32 enabled;
    Vec3 max;
} ClampBox;
/* A clamp table entry (0x20 bytes) as clamp_set_max_x/clamp_get_max_x address them: the count is the word at
 * clamp_table_ptr, entry i at clamp_table_ptr + i * 0x20. */
typedef struct ClampEntry {
    Vec3 min;
    s32 enabled;
    Vec3 max;
    s32 unk_1C;
} ClampEntry;

/* The sound allocator's 65 records (0x44 bytes at sound_alloc_pool; sound_alloc_init sets them up) and its tag
 * arrays. */
typedef struct AllocRec {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[2];
    /* 0x1A */ u8 tail;
    /* 0x1B */ u8 next;
    /* 0x1C */ u8 unk_1C[0x28];
} AllocRec;

/* Fade records (12 bytes, fade_records) on a byte-linked list: fades_head, fades_free. */
typedef struct FadeRec {
    u8 next;
    u8 unk_01[11];
} FadeRec;

/* Points converted to whole units by point_list_to_units. */
typedef struct PointIn {
    /* 0x00 */ s32 x, y, z;
    /* 0x0C */ u8 unk_0C[0xC];
    /* 0x18 */ u16 yaw, pitch, roll;
    /* 0x1E */ u8 unk_1E[6];
} PointIn;
typedef struct PointListIn {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ s32 count;
    /* 0x34 */ PointIn points[1];
} PointListIn;
typedef struct PointOut {
    s16 x, y, z;
    s16 yaw, pitch, roll;
} PointOut;
typedef struct PointListOut {
    s32 count;
    PointOut points[1];
} PointListOut;

/* A ring of 160 aged entries at trail_ring (count trail_ring_count, head trail_ring_tail; trail_ring_age). */
#define RING_SIZE 160
typedef struct RingEntry {
    u16 age;
    u8 pos[6];
} RingEntry;

/* Byte swap of a halfword (big-endian data files). */
#define SWAP16S(v) ((((v) & 0xFF) << 8) | (((v) & 0xFF00) >> 8))
typedef struct Half8 {
    s16 w[8];
} Half8;
typedef struct Half4 {
    s16 w[4];
} Half4;

typedef struct Rect {
    s16 x, y, w, h;
} Rect;

/* Tables only reached through accessors so far. */
/* 0x88-byte records (cam_tracks, cam_track_recs, part_recs): four 0x20-byte parts, then halfwords. */
/* Keyframe: a 3-component value at time t; interpolated by time. */
typedef struct TrackKey {
    s32 v[3];
    s32 t;
} TrackKey;

typedef struct TrackRec {
    /* 0x00 */ u8 part[4][0x20];
    /* 0x80 */ s16 unk_80;
    /* 0x82 */ s16 unk_82;
    /* 0x84 */ s16 on;
    /* 0x86 */ s16 index;
} TrackRec;
/* The last 8 bytes of a TrackRec, through a pointer (countdown_rec_step counts them down). */
typedef struct TrackRecState {
    s16 active; /* unk_80 */
    s16 unk_82;
    s16 on;
    s16 index;
} TrackRecState;
typedef struct ViewRec {
    /* 0x00 */ u8 unk_00[0xA0];
    /* 0xA0 */ s16 enabled; /* also set in view_set_on's table */
    /* 0xA2 */ u8 unk_A2[2];
} ViewRec;
/* 16 records at fx_rec30_pool; fx_rec30_clear clears one, fx_rec30_alloc finds a free one. */
typedef struct FxEffect {
    /* 0x00 */ u8 pos[0x10];
    /* 0x10 */ s16 progress;
    /* 0x12 */ s16 progress_step;
    /* 0x14 */ void (*callback)(); /* fx_spawn_template's argument */
    /* 0x18 */ s32 size;
    /* 0x1C */ s32 size_speed;
    /* 0x20 */ s32 size_accel;
    /* 0x24 */ u8 size_speed_min[4];
    /* 0x28 */ s16 intensity;
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ u8 color_r;
    /* 0x2D */ u8 color_g;
    /* 0x2E */ u8 color_b;
    /* 0x2F */ u8 used; /* nonzero while in use */
} FxEffect;

typedef struct IntPair {
    s32 a, b;
} IntPair;

/* A fade item (fade_items), started by fade_list_add. */
typedef struct FadeItem {
    /* 0x00 */ s32 x, y, z; /* 20.12 */
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 pad_0E;
    /* 0x10 */ s16 range_start;
    /* 0x12 */ s16 range_end;
    /* 0x14 */ s16 level;
    /* 0x16 */ s16 level_step;
    /* 0x18 */ s16 brightness;
    /* 0x1A */ s16 brightness_step;
} FadeItem; /* 0x1C */

/* The engine work area (work_area_ptr): the packet cursor at +0x74 (0x40-byte DR_ENV packets).
 * +0x18/+0x1A: the capture width and height copied to capture_width/capture_height (screenshot_update). */
typedef struct WorkArea {
    u8 unk_00[0x14];
    s16 draw_x; /* 0x14: drawing area origin in VRAM */
    s16 draw_y;
    u16 width;
    u16 height;
    s16 scroll_x; /* 0x1C: scroll position, passed as an (x, y) pair */
    s16 scroll_y; /* 0x1E */
    u8 unk_20[0xD];
    u8 fade_r; /* 0x2D: the screen fade colour (cam_frame_draw's full-screen tile) */
    u8 fade_g;
    u8 fade_b;
    u8 unk_30[0x40];
    u32 *ot; /* 0x70 */
    void *packet; /* 0x74 */
    void *packet_start; /* 0x78: packet area start (frame_begin) */
    void *packet_end; /* 0x7C: end of this frame's half of the arena */
    s32 list_cursor; /* 0x80: copied to d_8011FFE4 by gte_light_setup */
} WorkArea;

/* from player_warp_request */
typedef struct UnalignedVec {
    u8 b[8];
} UnalignedVec;
/* ScanEntry, ScanItem: resource.h */
/* from solid_part_pos */
typedef struct SolidPart {
    s16 active;    /* 0x00: nonzero when the part is in use */
    u8 unk_02[4];
    s16 off[3];    /* 0x06: offset of the part, added to the frame position */
    u8 unk_0C[0xC];
} SolidPart;
/* from solid_part_pos */
typedef struct SolidFrame {
    u8 unk_00[0x1C];
    s32 pos[3];
} SolidFrame;
/* from ranking_place */
typedef struct LimitRec {
    u32 limit;
    u32 unk_04;
    u32 unk_08;
} LimitRec;
/* from run_restore */
typedef struct RunRecord {
    u8 unk_00[0x20];
    s32 mission_next;  /* 0x20: area / 3 + 1 */
    u8 unk_24;
    u8 flag_25;
    u8 unk_26;
    u8 flag_27;
    u8 flag_28;
    u8 unk_29[0x8F];
    s32 max_mission_reached;        /* a high-water mark (unsigned compare) */
    s32 score;
    u8 unk_C0[4];
    s32 kill_count;
    u8 unk_C8[4];
    s32 unk_CC;        /* 1: reset when the record is handled */
} RunRecord;
/* from spark_spawn */
typedef struct SpawnHead {
    s16 unk_00;
    u16 unk_02;
    s16 unk_04;
} SpawnHead;
/* from spark_spawn */
typedef struct SpawnStats {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} SpawnStats;
/* from record_update */
typedef struct RecordEntry {
    s32 pos[3];     /* 0x00: pos += vel each step */
    s32 vel[3];     /* 0x0C: vel += accel, clamped to 0x1C000 */
    u16 ang[3];     /* 0x18 */
    u16 ang_vel[3]; /* 0x1E */
} RecordEntry;
/* from record_update */
typedef struct RecordBody {
    s16 age;
    u8 unk_02[0x1A];
    s32 accel[3];    /* 0x1C */
    u8 unk_28[8];
    s32 count;       /* 0x30 */
    RecordEntry entries[0]; /* 0x34 */
} RecordBody;

/* obj->state_table: the handler's states, 8 bytes each; obj_script_step runs `code` (a resume address);
 * obj_start_state_script starts or jumps to script `index` of the object's type data. */
typedef struct StateEntry {
    u32 code;
    s16 index; /* -1 = none; else index into the type's script table */
    s16 flag;  /* nonzero: script_start, else script_jump */
} StateEntry;

/* A grid block's header (at the block plus its first halfword): the entry count, then the entries. */
typedef struct GridHeader {
    s32 count;
    GridEntry entries[1];
} GridHeader;

/* from gun_shot_setup */
typedef struct GunSetup {
    /* 0x00 */ s32 speed;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 speed_delta;
    /* 0x0C */ u16 damage;
    /* 0x0E */ u16 hit_effect_index;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ u16 unk_22;
} GunSetup;
/* from gun_shot_setup */
typedef struct GunVars {
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ s32 x;
    /* 0x250 */ s32 y;
    /* 0x254 */ s32 z;
    /* 0x258 */ s32 pad_258;
    /* 0x25C */ s16 target[3];
    /* 0x262 */ s16 pad_262;
    /* 0x264 */ s16 unk_264;
    /* 0x266 */ u16 unk_266;
    /* 0x268 */ s16 unk_268;
    /* 0x26A */ u16 unk_26A;
    /* 0x26C */ u16 unk_26C;
    /* 0x26E */ u16 unk_26E;
    /* 0x270 */ u16 unk_270;
    /* 0x272 */ u16 unk_272;
    /* 0x274 */ u16 unk_274;
    /* 0x276 */ u16 unk_276;
    /* 0x278 */ u16 unk_278;
    /* 0x27A */ s16 unk_27A;
    /* 0x27C */ s8 hit_effect_index;
    /* 0x27D */ s8 unk_27D;
    /* 0x27E */ s8 has_target;
    /* 0x27F */ s8 trace_countdown;
} GunVars;
#define GUN_VARS(obj) ((GunVars *)&(obj)->vars) /* gun_shot_setup: a local pointer costs a register */
/* from fx_spawn_style */
typedef struct FxParams {
    /* 0x00 */ u8 used;
    /* 0x01 */ u8 col[3];
    /* 0x04 */ u16 progress;
    /* 0x06 */ u16 progress_step;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 size_speed;
    /* 0x10 */ s32 size_accel;
    /* 0x14 */ s32 unk_14;
} FxParams;

/* from record_run_result */
typedef struct RunEntry {
    s32 w[3];
} RunEntry;
/* from record_run_result */
typedef struct RunHistory {
    s32 unk_00;
    s32 ending;
    s32 unk_08;
    s32 count;
    u8 unk_10[0x10];
    s32 unk_20;
    u8 unk_24[8];
    RunEntry a[5];
    RunEntry b[5];
    u8 unk_A4[0x14];
    s32 max_mission_reached;
    s32 score;
    u8 unk_C0[4];
    s32 kill_count;
} RunHistory;
/* from prim_clip_band */
typedef struct ClipIn {
    s16 c; /* coordinate clipped against +-0x20 */
    s16 o; /* other coordinate */
} ClipIn;
/* from stage_end_fade_update */
typedef struct CoItem {
    s32 level;
    void *resume[8];
    s32 count[8];
} CoItem;
/* from span_table_build */
typedef struct SpanEdge {
    s16 y0;
    s16 y1;
    u16 value;
    s16 unk_06;
} SpanEdge;
/* from span_table_build */
typedef struct SpanTable {
    s32 arg0;
    s32 *src;
    s16 line[256];
    s16 data[1];
} SpanTable;
/* from spawn_effect */
typedef struct EffectRec {
    u8 next;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 x;
    s16 y;
    s16 z;
    s16 unk_0A;
} EffectRec;
/* from func_800B802C */
typedef struct FlagRecord04 {
    u8 unk_00[4];
    u8 flags;
} FlagRecord04;
/* from func_800BEEE4 */
typedef struct ObjTail {
    u8 pad_000[0x284];
    s16 unk_284;
} ObjTail;
/* from func_800C1C24 */
typedef struct ObjState {
    u8 pad_000[0x252];
    s16 state;
} ObjState;
/* from func_800C6364 */
/* from func_800C8800 */
typedef struct Debris {
    /* 0x00 */ u8 unk_00[0x04];
    /* 0x04 */ s32 active;
    /* 0x08 */ u8 unk_08[0x28 - 0x08];
} Debris;
/* from func_800B789C */
typedef struct ObjSum {
    u8 pad_000[0x248];
    u16 total;
    u16 step;
} ObjSum;
/* from func_800C8218 */
typedef struct CopySlot {
    s32 used;
    Object *obj;
} CopySlot;

/* from aobj_sort_entries */
typedef struct Bytes12 {
    u8 b[12];
} Bytes12;
/* from aobj_sort_entries */
typedef struct SortKey {
    s16 index;
    s16 key;
} SortKey;
/* from draw_view_hline */
typedef struct ViewDrawFields {
    u8 unk_00[0x40];
    s16 scale_x, scale_y;
    u8 unk_44[0x14];
    s16 clip_w, clip_h;
    s16 origin_x, origin_y;
    u8 unk_60[0x44];
    u32 *ot;
} ViewDrawFields;
/* from func_800BA534 */
typedef struct VarsTail274 {
    /* 0x274 */ s32 timer; /* a timer that counts toward zero from either side */
    /* 0x278 */ s16 unk_278; /* 1: counting down from above zero */
    /* 0x27A */ u8 unk_27A[8];
    /* 0x282 */ s16 countdown; /* counts down to zero, then stops */
    /* 0x284 */ u8 unk_284;
    /* 0x285 */ u8 unk_285; /* 1: func_800BA1F0 runs each step */
} VarsTail274;

/* scratch_top ($gp, the scratchpad allocator) is declared in common.h. */

/* Runs the calls between them on a stack at the top of the scratchpad: the old sp is saved at `top`, which becomes
 * the new sp. The matching constraint keeps `top` in a pseudo, as the original's register choice needs. */
#define SCRATCH_STACK_ENTER(top) ({                                                                   \
        u32 top_;                                                                                     \
        __asm__ volatile("sw $sp, 0(%0)\n\taddu $sp, %0, $zero" : "=r"(top_) : "0"(top));          \
    })
#define SCRATCH_STACK_LEAVE() __asm__ volatile("lw $sp, 0($sp)")
#define SCRATCH_STACK_TOP 0x1F8003FC

/* from func_800C2678 */
typedef struct PosRot12 {
    s16 x, y, z;
    u16 ay, ax, az;
} PosRot12;
/* from func_800B94A4 */
typedef struct MatrixHalf {
    s32 w[4];
} MatrixHalf;

/* from rot_matrix_to_angles */
typedef struct RotMatrix {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} RotMatrix;
/* from view_order_build */
typedef struct ViewSortEntry {
    s16 view;
    s16 depth;
} ViewSortEntry;
/* from sound_set_pos_from_rec */
typedef struct SoundPosSource {
    u8 pad_00[8];
    Vec3 pos;
} SoundPosSource;
/* from effect_sound_update */
typedef struct EffectSoundSource {
    u8 pad_00[4];
    SVECTOR pos;
} EffectSoundSource;
/* from sound_play_at_units */
typedef struct SoundPos {
    Vec3 pos;
    s32 sound_id;
} SoundPos;
/* from func_800BE850 */
typedef struct TraceScratch {
    /* 0x00 */ Vec3 from;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ Vec3 to;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ Vec3 hit;
    /* 0x2C */ s32 unk_2C;
} TraceScratch;

/* from sound_emitter_update */
/* A pair of points, each padded to 16 bytes (S01 SoundPair). */
typedef struct Segment32 {
    Vec3 a;
    s32 pad_0C;
    Vec3 b;
    s32 pad_1C;
} Segment32;
/* One entry of the spark offset table at spark_offset_table (0x28 bytes per idx, 0x14 per sub). */
typedef struct SparkOffset {
    /* 0x00 */ s16 ax, ay; /* added to spark_blend_base and passed to pchr_blend */
    /* 0x04 */ u16 unk_04, unk_06; /* base of a solid's point pair (func_800BF424, plus solid_point_base) */
    /* 0x08 */ s16 dx, dz; /* added to the object's x and z */
    /* 0x0C */ u8 unk_0C[8];
} SparkOffset;

/* from func_800C06EC */
typedef struct Rec8013C970 {
    s32 *first;
    u8 unk_04[0x18];
} Rec8013C970;
/* from func_800C5D00 */
/* A 16-byte trace hit point (S10 func_800C5D00, func_800C7758; S09 func_800C87AC). */
typedef struct TraceHit {
    s32 w[4];
} TraceHit;

/* from grenade_step */
typedef struct GrenadeStep {
    Vec3 from;
    s32 unk_0C;
    Vec3 to;
    s32 unk_1C;
} GrenadeStep;

/* from func_800C6A8C */
typedef struct SegTarget {
    s16 unk_00;
    s16 kind;          /* 0x108 is the kind that keeps unk_3A */
} SegTarget;

/* from func_800BFB84 */
typedef struct ReadCursor {
    u8 unk_00[0x20];
    u8 *cursor;
    u8 unk_24[0x23C];
    u16 value;
} ReadCursor;

/* from ring_cursor_advance */
typedef struct RingCursor {
    u8 unk_00[2];
    short wrap_at;
    short hit;
    short pos;
    u8 unk_08[0x1E];
    short period;
    u8 unk_28[4];
    u16 hold;
    u16 held;
} RingCursor;

/* from solid_add */
typedef struct {
    s16 v[4];
} SolidCoords;
/* solid_add ignores its last two arguments; callers that pass only the two point pairs cast it to this */
typedef s32 (*SolidAddFn)(s16 *p0, s16 *p1);
/* from obj_snapshot_save */
typedef struct ObjSnapshot {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s32 unk_10;         /* flags func_800C7198 sets (bits 0x10-0x1F0) */
    /* 0x14 */ s32 flags;          /* bit 0: object was moving */
    /* 0x18 */ u8 unk_18[0x8];
    /* 0x20 */ s32 unk_20[3];      /* copied to Object x/y/z (obj_snapshot_restore) */
    /* 0x2C */ u8 pad_2C[0x4];
    /* 0x30 */ s32 pos[3];
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 vel[3];
    /* 0x4C */ u8 pad_4C[0x4];
    /* 0x50 */ s16 unk_50[3];      /* copied to Object unk_238 */
    /* 0x56 */ u8 pad_56[0x6];
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ u8 pad_60[0xC];
    /* 0x6C */ s32 unk_6C;
} ObjSnapshot;

/* from vtx_rotate_list */
typedef struct GteVtx {
    s32 xy;
    s16 z;
    s16 pad;
} GteVtx;
/* from vtx_rotate_list */
typedef struct GteOut {
    s32 mac1;
    s32 mac3;
} GteOut;

/* from value_queue_pop */
typedef struct RingLookup {
    u8 unk_00[0x1C];
    s32 *table;
    s32 value;
} RingLookup;
/* from fade_red_update */
typedef struct FadeRedState {
    u8 pad_00[0x18];
    s32 timer;
    s32 limit;
    u8 pad_20[0xC];
    s8 colour[3];
    s8 flag;
} FadeRedState;
/* from fade_red_update */
typedef struct Next800C5620 {
    u8 pad_00[0x24C];
    s32 state;
} Next800C5620;
/* from scaled_rec_list_scale */
typedef struct ScaledRec { s16 v[3]; s16 pad[3]; } ScaledRec;

/* from track_set_dims */
typedef struct TrackDims {
    s16 width;
    s16 height;
    s16 depth;
    s16 scale;
    u8 unk_08[0x234 - 8];
} TrackDims;
/* from clip_verts_test_box */
typedef struct ClipVertex {
    s16 x, y, z, flags;
} ClipVertex;
/* Copies a ClipVertex as two words (both loads before the stores). */
#define CLIP_VERTEX_COPY(dst, src) { s32 w0_ = ((s32 *)(src))[0]; s32 w1_ = ((s32 *)(src))[1]; ((s32 *)(dst))[0] = w0_; ((s32 *)(dst))[1] = w1_; }
/* clip_poly_slab's slab crossings. CLIP_X_ENTER writes to dst the point where the edge from in[0]
 * (outside) to in[1] (x: next_x) crosses x = plane: t = (plane - x0) / (x1 - x0) in 14-bit fixed
 * point (div, read back later with mflo), then gpl0 gives y0 + t * (y1 - y0) and z0 + t * (z1 - z0).
 * x and z are written swapped. cur and aux are the caller's work variables, shared by every
 * crossing (one register each in the original). */
#define CLIP_X_ENTER(dst, in, next_x, cur, aux, plane) \
    {                                                  \
        s32 dy_, dz_, t_;                              \
        cur = (in)->x;                                 \
        aux = ((plane) - cur) << 14;                   \
        mips_div(aux, (next_x) - cur);                 \
        (dst)->z = (plane);                            \
        cur = (in)->y;                                 \
        dy_ = (in)[1].y;                               \
        aux = (in)->z;                                 \
        dz_ = (in)[1].z;                               \
        dy_ -= cur;                                    \
        dz_ -= aux;                                    \
        gte_set(IR1, dy_);                             \
        gte_set(IR2, dz_);                             \
        gte_set(MAC1, cur << 14);                      \
        gte_set(MAC2, aux << 14);                      \
        mips_mflo(t_);                                 \
        gte_set(IR0, t_);                              \
        gte_gpl0();                                    \
        gte_get(MAC1, dy_);                            \
        gte_get(MAC2, dz_);                            \
        (dst)->y = dy_ >> 14;                          \
        (dst)->x = dz_ >> 14;                          \
    }
/* The same for the edge from in[1] (outside, x: next_x) back to in[0]. */
#define CLIP_X_EXIT(dst, in, next_x, cur, aux, plane)  \
    {                                                  \
        s32 y1_, dz_;                                  \
        aux = ((plane) - (next_x)) << 14;              \
        cur = (in)->x;                                 \
        cur -= (next_x);                               \
        mips_div(aux, cur);                            \
        (dst)->z = (plane);                            \
        cur = (in)->y;                                 \
        aux = (in)[1].z;                               \
        y1_ = (in)[1].y;                               \
        dz_ = (in)->z;                                 \
        cur -= y1_;                                    \
        dz_ -= aux;                                    \
        gte_set(IR1, cur);                             \
        gte_set(IR2, dz_);                             \
        gte_set(MAC1, y1_ << 14);                      \
        gte_set(MAC2, aux << 14);                      \
        mips_mflo(cur);                                \
        gte_set(IR0, cur);                             \
        gte_gpl0();                                    \
        gte_get(MAC1, cur);                            \
        gte_get(MAC2, dz_);                            \
        (dst)->y = cur >> 14;                          \
        (dst)->x = dz_ >> 14;                          \
    }
/* from clip_verts_test_box */
typedef struct ClipBox {
    s16 minX, maxX, minY, maxY, minZ, maxZ;
} ClipBox;

/* trace_world's request, taken from the scratch allocator and passed to trace_world_sweep. */
typedef struct TraceRequest {
    /* 0x00 */ s16 mode;
    /* 0x02 */ s16 flags;
    /* 0x04 */ void *from;
    /* 0x08 */ void *to;
    /* 0x0C */ void *hit;
} TraceRequest;

/* from func_800C92FC */
typedef struct MarkerEntry {
    s32 owner;      /* 0x00 */
    s32 pos_x;     /* 0x04 */
    s32 pos_y;     /* 0x08 */
    s32 pos_z;     /* 0x0C */
    u8 pad_10[4];
    u16 unk_14;     /* 0x14 */
    u16 unk_16;     /* 0x16 */
    u8 pad_18[8];
    s16 unk_20;     /* 0x20 */
    s16 unk_22;     /* 0x22 */
} MarkerEntry;
/* from func_800C4EC8 */
typedef struct TrailEntry {
    s16 x;
    s16 y;
    s16 z;
    s16 pad_06;
} TrailEntry;
/* A record with two looping sounds at 0x48 and 0x4C (sway_state in S01; sound_pair_start_loops starts, func_800C3E60 stops). */
typedef struct SoundPair {
    /* 0x00 */ s32 owner;
    /* 0x04 */ Segment32 seg; /* the sounds play at its point nearest the listener */
    /* 0x24 */ s32 unk_24[3];
    /* 0x30 */ s32 volume;
    /* 0x34 */ s32 call_flag; /* when 1, sound_pair_run_copy passes a copy to move_box_sweep */
    /* 0x38 */ u8 unk_38[0x10];
    /* 0x48 */ s32 sound[2];
} SoundPair;

/* from obj_set_contact_flags */
typedef struct ObjContactState {
    s32 pad[4];
    s32 mode;
    s32 flags;
} ObjContactState;
/* from effect_spawn_at */
typedef struct FadeRecFull {
    u8 next;
    u8 level_step;
    u8 level_scale;
    u8 level;
    s16 pos[3];
    s16 base_level;
} FadeRecFull;
/* from cam_path_update */
typedef struct CamPathSample {
    Vec3 pos;
    s32 pad0;
    Vec3 out;
    s32 pad1;
} CamPathSample;
/* from sea_mine_update */
typedef struct { s16 frame; u16 delay; } AnimFrame;

/* from name_color_get */
typedef struct NameRec {
    u8 unk_00[0x14];
    s32 offset; /* 0x14: offset of the colour word from name_table_base */
} NameRec;
/* from func_800CA2D8 */
typedef struct {
    u32 word0;
    u32 word1;
} __attribute__((packed)) Unaligned8;
/* from func_800C6978 */
typedef struct Vec4Words {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Vec4Words;
/* from func_800C3030 */
typedef struct PosHist {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} PosHist;

/* from angle_state_value */
typedef struct AngleState {
    s16 angle;
    s16 unk_02;
    s16 flags;
} AngleState;
/* from angle_state_value */
typedef struct AngleEntry801188EE {
    s16 value;
    s16 unk_02;
} AngleEntry801188EE;
/* from anim_seq_step */
typedef struct AnimSequence {
    u16 **table;
    u16 *cur;
    u16 value;
    u16 count;
    u16 prev;
    u16 next;
} AnimSequence;
/* from fx_palette_init */
typedef struct { s16 x, y, w, h; } ScreenRect;
/* from box_query */
typedef struct WallTables {
    u8 *boxes;
    u8 *offsets;
} WallTables;
/* from wall_segment_query: scratch for wall_query_bisect, box in, two clamped points out */
typedef struct WallQuery {
    s32 box[4];
    s16 a_z, a_x;        /* 0x10 */
    s16 b_z, b_x;        /* 0x14 */
} WallQuery;

/* from shift_table_add_delta */
typedef struct ShiftEntry {
    u16 x;
    u16 y;
    u16 z;
    u8 unk_06[6];
} ShiftEntry;
/* from shift_table_add_delta */
typedef struct ShiftTable {
    s32 count;
    ShiftEntry entries[1];
} ShiftTable;
/* from placed_rect_query */
typedef struct PlacedRect {
    s32 pad_00[2];
    s16 x0, y0, x1, y1;
} PlacedRect;
/* from placed_rect_query */
typedef struct RectOffset {
    s32 pos_x, pos_y;
} RectOffset;
/* from placed_rect_query */
typedef struct PlacedRects {
    PlacedRect *rects;
    RectOffset *placements;
} PlacedRects;

/* from beam_impact */
typedef struct BeamTimer {
    s16 length;
    s16 phase;
    u16 unk_04;
    s32 x;
    s32 y;
    s32 z;
} BeamTimer;
/* from func_800BE500 */
typedef struct {
    s32 v[4];
} Vec4;

/* The state loop_state_start starts in S01 (loop_state_update updates it; loop_state_stop resets it). */
typedef struct LoopState {
    /* 0x00 */ Object *owner; /* sound_track_pos follows it */
    /* 0x04 */ Vec3 pos;
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ s16 level;
    /* 0x16 */ s16 step;
    /* 0x18 */ s16 active;
    /* 0x1A */ s16 noisy;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 scale;  /* reset to 0x1000 (loop_state_stop) */
    /* 0x20 */ s32 sound;  /* loop handle loop_state_sound_start starts */
} LoopState;
/* from world_query_segment */
typedef struct { s32 lo[3]; s32 pad0; s32 hi[3]; s32 pad1; } Aabb;
/* Lock-on slot table: 16 records of 0x18 bytes from d_8012EE14
   (s16 level, s16 actor id, s16 flag at +6, screen bounds at +8);
   o is the record's byte offset. */
#define SLOT_LEVEL(o) (*(s16 *)((u8 *)d_8012EE14 + (o)))
#define SLOT_ID(o) (*(s16 *)((u8 *)lock_slot_target + (o)))
#define SLOT_FLAG(o) (*(s16 *)(rec_table_flag + (o)))
#define SLOT_BOUNDS(o) ((s32 *)(rec_table_pos + (o)))

/* from obj_ceiling_near */
typedef struct TraceVec4 {
    s32 x, y, z, w;
} TraceVec4;
/* from solid_alloc */
typedef struct SolidPart12 {
    s16 v[12];
} SolidPart12;
/* from func_800C1704 */
typedef struct MatrixRow {
    s32 w[4];
} MatrixRow;
/* from func_800CA584 */
typedef struct Quad4S12 {
    s32 v[4];
} Quad4S12;

/* from placement_angle */
typedef struct PlacementTables { u8 *shapes; u8 *links; } PlacementTables;
/* from placement_angle */
typedef struct PlacementAngle { s32 pad0; s16 angle; s16 pad2; } PlacementAngle;
/* from func_800C7CEC */
typedef struct KeyTrackSlot {
    Object *owner;                 /* 0x00 */
    Keyframe *cursor;              /* 0x04: Keyframe ** for keyframe_step */
    s32 pos_x;                     /* 0x08 */
    s32 pos_y;                     /* 0x0C */
    s32 pos_z;                     /* 0x10 */
    u8 pad_14[0x18 - 0x14];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s32 tick;                      /* 0x20 */
    s32 size;
    s32 key_index;                 /* 0x28: index into cam_shake_nudges, -1 when done */
    s16 life;
    s16 unk_2E;
    u16 from;                      /* 0x30 */
    u16 to;                        /* 0x32 */
    s16 t;                         /* 0x34 */
    s16 active;                    /* 0x36: keyframe step result */
} KeyTrackSlot;
/* from func_800C0D44 */
typedef struct GridBox {
    s32 x0, x1, z0, z1, y0, y1;
} GridBox;

/* from text_slots_step */
typedef struct TextSlot {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 id;
    /* 0x04 */ u16 delay;
    /* 0x06 */ u16 delay_space;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ s16 length;
    /* 0x0C */ s16 index;
    /* 0x0E */ u16 timer;
    /* 0x10 */ u8 *cursor;
} TextSlot;

/* from enemy_spawn_step */
typedef struct ScriptPcSlot { s16 *pc; } ScriptPcSlot;
/* from player_move_vertical */
typedef struct ScratchBox6 {
    u16 x0, x1, y0, y1, z0, z1;
} ScratchBox6;
/* from solid_part_box */
typedef struct SolidPartBox {
    s16 size[3];   /* 0x00: written to the box; size[0] is zero for an unused part */
    s16 off[3];    /* 0x06: offset added to the owner's position */
    u8 unk_0C[0xC];
} SolidPartBox;
/* from enemy_spawn_countdown */
typedef struct ScriptCursor { s16 *pc; } ScriptCursor;

/* from blast_hit_actors */
typedef struct ProximityQuery {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ s32 unk_0C[3];
    /* 0x18 */ s32 range;
} ProximityQuery;
/* from setup_stage */
typedef struct SetupEntry {
    /* 0x00 */ u8 *name;
    /* 0x04 */ u8 unk_04[4];
    /* 0x08 */ u8 *key;
    /* 0x0C */ u8 unk_0C[0xC];
    /* 0x18 */ s16 pos[3];
} SetupEntry;

/* from prim_fade_quad */
typedef struct PolyFT4 {
    /* 0x00 */ u8 link[3];
    /* 0x03 */ u8 len;
    /* 0x04 */ u8 r0;
    /* 0x05 */ u8 g0;
    /* 0x06 */ u8 b0;
    /* 0x07 */ u8 code;
    /* 0x08 */ s16 x0;
    /* 0x0A */ s16 y0;
    /* 0x0C */ u8 u0;
    /* 0x0D */ u8 v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ s16 x1;
    /* 0x12 */ s16 y1;
    /* 0x14 */ u8 u1;
    /* 0x15 */ u8 v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ s16 x2;
    /* 0x1A */ s16 y2;
    /* 0x1C */ u8 u2;
    /* 0x1D */ u8 v2;
    /* 0x1E */ u16 pad1;
    /* 0x20 */ s16 x3;
    /* 0x22 */ s16 y3;
    /* 0x24 */ u8 u3;
    /* 0x25 */ u8 v3;
    /* 0x26 */ u16 pad2;
} PolyFT4;
/* from prim_fade_quad */
typedef struct DrTwin {
    /* 0x00 */ u8 link[3];
    /* 0x03 */ u8 len;
    /* 0x04 */ u32 code[2];
} DrTwin;

/* from func_800B94BC */
typedef s32 (*GetAngleFn)(void);
/* from func_800C885C */
typedef struct SparkOwner {
    /* 0x000 */ u8 pad0[0x1A0];
    /* 0x1A0 */ s32 *asset;
    /* 0x1A4 */ u8 pad1[0x4C];
    /* 0x1F0 */ s32 x, y, z;
} SparkOwner;

/* from obj_fall_update */
typedef struct FallState {
    u8 pad_000[0x278];
    s16 fall_dir;     /* 1 or -1: the random direction picked at launch */
    s16 unk_27A;
    s16 unk_27C;
    s16 unk_27E;
    s16 launch_timer; /* set to 8 at launch */
    s16 unk_282;      /* set to -2 when the object comes to rest */
} FallState;

/* from rocket_trail_draw */
typedef struct TrailOffset {
    s16 y0, y1, y2, unk_06, z, z2, unk_0C[3];
} TrailOffset;
/* from rocket_trail_draw */
typedef struct TrailVars {
    u8 pad_248[0x1C];
    u16 amount;
    u8 pad_266[8];
    u16 limit_a;
    u16 limit_b;
    u8 pad_272[8];
    u16 scale;
    s8 kind;
} TrailVars;

/* from debug_info_draw */
typedef struct WorkAreaPool {
    u8 unk_00[0x74];
    s32 packet;
    s32 unk_78[2];
    s32 limit;
} WorkAreaPool;

/* from sound_handles_update */
typedef struct SoundHandleFull {
    /* 0x00 */ union { u32 word; u16 half[2]; } id;
    /* 0x04 */ s32 voice[2];
    /* 0x0C */ s16 delay;
    /* 0x0E */ u8 pad_0E[2];
    /* 0x10 */ s16 volume;
    /* 0x12 */ s16 pan;
    /* 0x14 */ s16 pitch;
    /* 0x16 */ u8 pad_16[2];
    /* 0x18 */ VECTOR last_pos;
    /* 0x28 */ VECTOR pos;
    /* 0x38 */ s32 (*update)(void *owner, s32 index);
    /* 0x3C */ void *owner;
    /* 0x40 */ u8 flags;
    /* 0x41 */ u8 dirty;
    /* 0x42 */ u8 pad_42;
    /* 0x43 */ u8 next;
} SoundHandleFull;

/* from func_800C1180 */
typedef struct ModelPartList {
    s32 *first;
    u8 pad[0x18];
} ModelPartList;

/* from cam_path_sample */
typedef struct PathPoint {
    s32 x, y, z, w;
} PathPoint;

/* from gun_shot_update */
typedef struct GunShotVars {
    s32 max_speed;
    s32 x, y, z;
    s32 pad_258;
    s16 target[3];
    s16 pad_262;
    u16 age;
    u16 launch_age;
    u16 homing_end_age;
    u16 unk_26A;
    u16 unk_26C;
    u16 turn_start_age;
    u16 unk_270;
    u16 smoke_period;
    u16 smoke_arg;
    u16 smoke_limit;
    u16 turn_step;
    u16 turn_angle;
    s8 kind;
    u8 phase;
    u8 has_target;
    u8 trace_count;
} GunShotVars;
/* from gun_shot_update */
typedef struct ShotScratch {
    Vec3 from;
    s32 pad_0C;
    Vec3 to;
    s32 pad_1C;
    Vec3 offs;
    s32 pad_2C;
} ShotScratch;

/* from gte_transform_to_end */
typedef struct {
    s32 xy;
    s16 z;
    s16 pad;
    s32 pad2;
} GteVertexIn;
/* from gte_transform_to_end */
typedef struct {
    s32 xy;
    s32 pad[2];
} GteVertexOut;
/* from prim_depth_cue_strip */
typedef struct { s32 rgb; s16 pad; s16 ir0; } DepthCueRec;
/* from uvec2_rotate_array */
typedef struct { u16 x, y; } UVec2;

/* from point_to_view_angles */
typedef struct { s32 v; } PlayerCoord;
/* The GTE light table: 16 records of 0x84 bytes, indexed by light_env_index (gte_light_setup). */
typedef struct LightEnv {
    /* 0x00 */ s32 color[5];     /* light colour matrix, as GTE control registers 16-20 */
    /* 0x14 */ s32 back[3];      /* back colour R, G, B */
    /* 0x20 */ SVECTOR unk_20[3]; /* [2]: point_light_setup_draw's RGB colour (each component >> 5) */
    /* 0x38 */ s32 depth_cue[2]; /* DQA, DQB */
    /* 0x40 */ u8 unk_40[0x44];
} LightEnv;

/* from prim_depth_cue_quad */
typedef struct ClipPoint {
    s16 u, v, z, w;
} ClipPoint;
/* from prim_depth_cue_quad */
typedef struct ClipPointWords {
    s32 uv, zw;
} ClipPointWords;
/* from prim_depth_cue_quad */
typedef struct ViewRecord {
    s16 value;
    s16 offset_y;
    u8 pad_04[0xA4];
} ViewRecord;

/* from obj_velocity_to_ctrl */
typedef struct Vector3 {
    s32 x, y, z;
} Vector3;
/* from obj_velocity_to_ctrl */
typedef struct TargetCtrl {
    /* 0x00 */ s16 rot[3];
    /* 0x06 */ u8 pad_06[0xE];
    /* 0x14 */ u32 flags;
    /* 0x18 */ u8 pad_18[0x28];
    /* 0x40 */ Vector3 pos;
} TargetCtrl;
/* A shot: 32 of them in a stage's shot table. Kind 0 flies ahead (shot_update) and is traced each step
 * (shot_trace); kinds 1-2 play keyframes (keyframe_step), 2 being the burst a hit turns it into. */
typedef struct Shot {
    /* 0x00 */ s32 owner; /* the Object that fired it (shot_pool_take) */
    /* 0x04 */ s32 pos[3];
    /* 0x10 */ u8 unk_10[4];
    /* 0x14 */ s16 pitch;
    /* 0x16 */ s16 yaw;
    /* 0x18 */ s16 roll;
    /* 0x1A */ u8 unk_1A[2];
    /* 0x1C */ s32 tick; /* keyframe time, reset by tick_reset */
    /* 0x20 */ s16 active;
    /* 0x22 */ s16 kind;
    /* 0x24 */ Keyframe *keys;
    /* 0x28 */ u16 key_from;
    /* 0x2A */ u16 key_to;
    /* 0x2C */ s16 key_t;
    /* 0x2E */ u8 unk_2E[2];
} Shot;
/* from shot_trace */
typedef struct ShotSlot {
    Object *owner;  /* 0x00: its asset table gives the model slot */
    s32 pos[3];     /* 0x04 */
    u8 pad_10[4];
    s16 yaw;        /* 0x14 */
    s16 pitch;      /* 0x16 */
    s16 roll;     /* 0x18 */
    u8 pad_1A[2];
    u8 tick[6];     /* 0x1C, reset by tick_reset */
    s16 state;      /* 0x22 */
    Keyframe *unk_24; /* 0x24 */
    s16 blend_from_offset;     /* 0x28 */
    s16 blend_to_offset;     /* 0x2A */
    s16 blend_factor;     /* 0x2C */
} ShotSlot;

/* from view_draw */
typedef struct ViewDraw {
    /* 0x00 */ s16 on;
    /* 0x02 */ u8 pad_02[4];
    /* 0x06 */ s16 camera;
    /* 0x08 */ u8 pad_08[0x14];
    /* 0x1C */ u8 colour[3];
    /* 0x1F */ u8 mode;
    /* 0x20 */ u8 border_rgb[3]; /* line colour; with `border` (the style) one GPU colour word */
    /* 0x23 */ u8 border;
    /* 0x24 */ u8 fill_rgb[3]; /* tile colour; with `fill` one GPU colour word */
    /* 0x27 */ u8 fill;
    /* 0x28 */ u8 pad_28[4];
    /* 0x2C */ s16 box_x, box_y, box_w, box_h;
    /* 0x34 */ u8 pad_34[0x18];
    /* 0x4C */ u16 edge[4];
    /* 0x54 */ s16 x, y, w, h;
    /* 0x5C */ u8 pad_5C[0x44];
    /* 0xA0 */ u8 *ctx;
    /* 0xA4 */ u8 *prim;
} ViewDraw;
/* from view_draw */
typedef struct RenderWork {
    /* 0x00 */ u8 pad_00[0x14];
    /* 0x14 */ s16 off_x, off_y;
    /* 0x18 */ u8 pad_18[0x5C];
    /* 0x74 */ u8 *packet;
} RenderWork;
/* from grid_entries_init_state */
typedef struct {
    u8 state;
    u8 pad_1[0x1F];
    u8 state2;
    u8 pad_21[0x1F];
} GridEntryState;
/* from obj_clear_block54 */
typedef struct ClearBlock54 {
    s16 unk_0;
    s16 flags;
} ClearBlock54;

/* from shot_params_init */
typedef struct ShotParamBlock {
    s32 unk_00;
    u8 pad_04[4];
    s32 unk_08;
    u8 pad_0C[2];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
} ShotParamBlock;

/* from func_800BE608 */
typedef struct IdRecord {
    s16 field_00;
    s16 field_02;
    s16 field_04;
    u16 prev_id;
    s16 field_08;
    s16 field_0A;
    s16 field_0C;
    s16 field_0E;
    s32 field_10;
} IdRecord;

/* from axis_vectors_rotate */
typedef struct {
    s16 vx, vy, vz, pad;
} Vec8;
/* from axis_vectors_rotate */
typedef struct {
    s32 xy;
    s32 z;
} Vec8Words;

/* from pool_spawn_scaled */
typedef struct PoolRec {
    s16 flags;      /* 0x00: a1 clamped, | 0x8000 */
    s16 unk_02;     /* 0x02: a2 clamped */
    s16 index;      /* 0x04 */
    s16 unk_06;     /* 0x06: a3 clamped */
    s32 unk_08;
    s32 unk_0C;
    s16 scale;      /* 0x10 */
    u16 unk_12;
    u16 unk_14;
    s16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} PoolRec;

/* from solid_copy */
typedef struct SolidPartWords {
    s32 w[6];
} SolidPartWords;

/* from script_value_queue_push */
typedef struct ValueScript {
    /* 0x00 */ u8 pad_00[0x20];
    /* 0x20 */ u16 *pc;
} ValueScript;

/* from stream_reader_init */
typedef struct StreamReader {
    s32 base;
    s16 *cursor;
    u16 first[2];
    u16 second[2];
} StreamReader;

/* from solid_parts_move */
typedef struct SolidPartMotion {
    s16 pos[3];
    s16 unk_06[3];
    s16 unk_0C[3];
    s16 vel[3];
} SolidPartMotion;

/* from pchr_set_value_range */
typedef struct PchrBank {
    s16 count;
    s16 pad;
    Pchr table[1];
} PchrBank;

/* from mem_copy_blocks */
typedef struct CopyBlock16 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} CopyBlock16;

/* from bucket_link_nodes */
typedef struct ListNode8 {
    struct ListNode8 *next;
    s32 value;
} ListNode8;
/* from bucket_link_nodes */
typedef struct BucketSrc {
    u8 key;
    u8 key_max;
    u8 first;
    u8 last;
    s16 value;
    s16 pad_6;
} BucketSrc;
/* from bucket_link_nodes */
typedef struct Bucket14 {
    s32 count;
    ListNode8 *slot[2][2]; /* [side][0] = tail list, [side][1] = head list */
} Bucket14;
/* from aobj_sort_slots */
typedef struct SortSlot {
    s16 x;
    s16 key_off; /* added to the record's key */
    s16 z;
    s16 rec_index; /* index into the aobj_table run at `base` */
} SortSlot;

/* from atr_map_build: the placed-object list an attribute map is built from */
typedef struct AtrSrc {
    s32 count;
    SortSlot entries[1];
} AtrSrc;

/* from atr_map_build: attribute map header; rows[] holds one offset per z cell
   (z_lo..z_hi), followed by the index data atr_map_make_index writes */
typedef struct AtrMap {
    AtrSrc *src;
    s16 min_x;
    s16 max_x;
    s16 min_y;
    s16 max_y;
    s16 min_z;
    s16 max_z;
    s16 z_lo;
    s16 z_hi;
    s16 rows[1];
} AtrMap;

/* from atr_map_build: an aobj's bounding box, pointed to by AobjEntry.unk_04[2] */
typedef struct AobjBounds {
    s16 min_x;
    s16 max_x;
    s16 min_y;
    s16 max_y;
    s16 min_z;
    s16 max_z;
} AobjBounds;

/* from pchr_copy_slot */
typedef struct PchrSlotEntry {
    s32 words[7];
} PchrSlotEntry;

/* from interp2c_restart_all */
typedef struct InterpPair {
    Interp part[2];
    u8 unk_20[0xC];
} InterpPair;

/* from ui_follow_update */
typedef struct UiFollower {
    /* 0x00 */ s32 level;
    /* 0x04 */ void *resume[8];
    /* 0x24 */ s32 count[8];
    /* 0x44 */ u8 pad_44[0xC];
    /* 0x50 */ s16 x;
    /* 0x52 */ s16 y;
    /* 0x54 */ s16 unk_54;
    /* 0x56 */ u8 pad_56[2];
    /* 0x58 */ struct UiFollower *parent;
    /* 0x5C */ u8 pad_5C[0x10];
    /* 0x6C */ s32 parent_done; /* nonzero: the parent is done, free this item */
    /* 0x70 */ u8 pad_70[0xC];
} UiFollower;

/* from interp38_restart_all */
typedef struct InterpTriple {
    Interp part[3];
    u8 unk_30[8];
} InterpTriple;

/* per model slot row: model_texel_to_vram (base, offset-to-step) and xs3_remap_palette_rows (remap) */
typedef struct TexelRemapRow {
    s16 base;
    s16 palette_count; /* number of remapped palettes (model_remap_palettes) */
    s8 remap[16];
} TexelRemapRow;

/* from func_800C0BEC */
typedef struct BoundsBox {
    s32 min_x;
    s32 max_x;
    s32 min_y;
    s32 max_y;
    s32 min_z;
    s32 max_z;
} BoundsBox;

/* from pending_grid_reset */
typedef struct GridEntryHalf {
    s32 words[8];
} GridEntryHalf;

/* from pchr_poses_build */
typedef struct PchrPose {
    s16 pos[3];
    s16 rot[3];
} PchrPose;
/* from pchr_poses_build */
typedef struct PchrPoseList {
    s32 count;
    PchrPose pose[1];
} PchrPoseList;

/* from prim_tex_rect_add */
typedef struct PrimTexRect {
    u8 link[3];
    u8 len;
    u8 r, g, b;
    u8 code;
    s16 x, y;
    u16 uv;
    u16 clut;
} PrimTexRect;
/* from prim_tex_rect_add */
typedef struct PrimDrMode {
    u8 link[3];
    u8 len;
    u32 cmd;
} PrimDrMode;
/* from prim_tex_rect_add */
typedef struct TexInfo {
    u8 pad_0[4];
    u16 uv;
    u16 clut;
} TexInfo;
/* from prim_tex_rect_add */
typedef struct Rgb {
    u8 r, g, b;
} Rgb;

/* from spark_list_collect_near */
typedef struct SparkOut {
    s16 x, y, z, unk_06;
    s32 unk_08, unk_0C, unk_10, colour;
} SparkOut;
/* from spark_list_collect_near */
typedef struct SparkArea {
    SparkList list;
    SparkOut *out;
    s16 *cur;
    s16 pad_1818;
    s16 out_count;
} SparkArea;

/* from prim_flat_black_build */
typedef struct PrimWord {
    u8 lo[3];
    s8 hi;
} PrimWord;
/* from prim_flat_black_build */
typedef struct PolyFlat {
    u8 link[3];
    u8 len;
    u8 r, g, b;
    u8 code;
    s16 xy[4][2];
} PolyFlat;

/* GPU TILE primitive (code 0x60, +2 semi-transparent) */
typedef struct PrimTile {
    u8 link[3];
    u8 len;
    union {
        s32 word;
        struct {
            u8 r, g, b, code;
        } c;
    } colour;
    s16 x, y, w, h;
} PrimTile;

/* A VRAM rectangle, as LoadImage takes it (cam_frame_draw). */
typedef struct VramRect {
    s16 x, y, w, h;
} VramRect;

/* from interp1c_draw_rec */
typedef struct GaugePrim {
    u8 link[3];
    u8 len;
    u8 unk_04[3];
    u8 code;
    u32 unk_08;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s16 w;
    s16 h;
} GaugePrim;

/* from alloc_id_release */
typedef struct AllocLink {
    u8 prev;
    u8 next;
    u8 unk_02[0x42];
} AllocLink;

/* from interp38_run_span */
typedef struct SpanRec {
    s16 code;
    s16 count;
    s16 x0, x1;
    s16 y0, y1;
    s16 z0, z1;
} SpanRec;

/* from interp38_add_script */
typedef struct ScriptRec {
    s32 state;
    u8 pad_04[0xC];
    s16 *block0;
    u8 pad_14[0xC];
    s16 *block1;
    u8 pad_24[0xC];
    s16 *block2;
    s16 *script;
} ScriptRec;

/* from tile_positions_set */
typedef struct {
    u8 bytes[4];
} TilePos;

/* from hud_draw_digit */
typedef struct IdTableRecords {
    s32 count;
    s16 id[16];
    IdRecord rec[256];
} IdTableRecords;

/* from obj_recs_init */
typedef struct ObjRec {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    s16 unk_18[6];
} ObjRec;
/* from obj_recs_init */
typedef struct ObjRecTable {
    u8 unk_00[0x30];
    s32 count;
    ObjRec recs[1];
} ObjRecTable;
/* from obj_recs_init */
typedef struct Src80107478 {
    s16 *data;
    u32 unk_04;
    s32 *count_ptr;
} Src80107478;

/* from ramp_start_script */
typedef struct RampState {
    s16 active;
    s16 length;
    s16 pos;
    s16 from;
    s16 to;
} RampState;

/* from span_edges_build */
typedef struct SpanQuad {
    s16 y0;
    s16 pad_2;
    s16 y1;
    s16 pad_6;
    s16 y2;
    s16 pad_A;
    s16 y3;
    s16 pad_E;
} SpanQuad;

/* from ui_rec_setup */
typedef struct UiRec84 {
    UiRecord draw;
    u8 disp[0x19];
    u8 unk_2D;
    u8 unk_2E;
    u8 unk_2F;
    u8 pad_30[0x54];
} UiRec84;

/* from screenshot_bmp_write */
typedef struct {
    s16 type;            /* 0x00 'BM' */
    s16 fileSizeLo;      /* 0x02 */
    s16 fileSizeHi;      /* 0x04 */
    s16 reserved1;       /* 0x06 */
    s16 reserved2;       /* 0x08 */
    s16 dataOffsetLo;    /* 0x0A */
    s16 dataOffsetHi;    /* 0x0C */
    s16 infoSizeLo;      /* 0x0E */
    s16 infoSizeHi;      /* 0x10 */
    s16 widthLo;         /* 0x12 */
    s16 widthHi;         /* 0x14 */
    s16 heightLo;        /* 0x16 */
    s16 heightHi;        /* 0x18 */
    s16 planes;          /* 0x1A */
    s16 bitCount;        /* 0x1C */
    s16 compressionLo;   /* 0x1E */
    s16 compressionHi;   /* 0x20 */
    s16 imageSizeLo;     /* 0x22 */
    s16 imageSizeHi;     /* 0x24 */
    s16 xPelsPerMeterLo; /* 0x26 */
    s16 xPelsPerMeterHi; /* 0x28 */
    s16 yPelsPerMeterLo; /* 0x2A */
    s16 yPelsPerMeterHi; /* 0x2C */
    s16 clrUsedLo;       /* 0x2E */
    s16 clrUsedHi;       /* 0x30 */
    s16 clrImportantLo;  /* 0x32 */
    s16 clrImportantHi;  /* 0x34 */
} BmpHeader;

/* from grid_entry_near_camera */
typedef struct CameraReach {
    s32 unk_00;
    s32 below;  /* reach below a camera */
    s32 above;  /* reach above a camera */
    s32 radius; /* horizontal reach */
} CameraReach;

/* from sound_attached_update */
typedef struct SoundSegment {
    Vec3 start;
    s32 pad_0C;
    Vec3 end;
    s32 pad_1C;
} SoundSegment;

/* from func_800C3F08 */
typedef struct RotMatrixWords {
    s32 words[8];
} RotMatrixWords;

/* from span_source_build */
typedef struct StripSeg {
    /* 0x0 */ s16 dy;
    /* 0x2 */ s16 unk_2;
    /* 0x4 */ s16 dx;
    /* 0x6 */ s16 range;
} StripSeg;
/* from span_source_build */
typedef struct StripSet {
    /* 0x0 */ s32 count;
    /* 0x4 */ StripSeg segs[1];
} StripSet;
/* from span_source_build */
typedef struct StripRange {
    s16 first;
    s16 count;
} StripRange;
/* from span_source_build */
typedef struct StripTable {
    s32 count;
    StripRange ranges[1];
} StripTable;
/* from span_source_build */
typedef struct StripPoint {
    s32 x, y;
} StripPoint;
/* from span_source_build */
typedef struct StripOut {
    s32 count;
    StripPoint pts[1];
} StripOut;
/* from span_source_build */
typedef struct StripOrigin {
    s32 x, y, z;
} StripOrigin;

/* from pchr_scale_range */
typedef struct PchrScaleRec {
    /* 0x00 */ s32 *tracks;
    /* 0x04 */ u8 pad_04[8];
    /* 0x0C */ s32 *list;
    /* 0x10 */ s16 scale;
    /* 0x12 */ u8 pad_12[8];
    /* 0x1A */ s16 locked;
} PchrScaleRec;
/* from pchr_scale_range */
typedef struct PchrScaleTable {
    s16 count;
    s16 pad_02;
    PchrScaleRec recs[1];
} PchrScaleTable;

/* from enemy_draw */
typedef struct FlashScratch {
    /* 0x00 */ Vec3 pos;
    /* 0x0C */ s32 pad_0C;
    /* 0x10 */ SVECTOR box;
} FlashScratch;

/* from pchr_copy_range */
typedef struct PchrWords {
    s32 head; /* unk_00, link_count */
    s32 link; /* link, unk_06 */
} PchrWords;

/* from object_spawn_at */
typedef struct SpawnPos {
    s32 v[4];
} SpawnPos;
/* from object_spawn_at */
typedef struct PchrSpawn {
    s16 age;
    s16 pchr;
    SpawnPos pos;
    UnalignedVec rot;
    u8 unk_1C[0x10];
    s32 unk_2C;
} PchrSpawn;

/* from pchr_burst_init: a pchr's particle burst, built over a PchrSpawn object */
typedef struct PchrBurstSource {
    s16 pos[3];
    u16 a, b, c;
} PchrBurstSource;

typedef struct PchrBurstPart {
    s32 pos[3];
    s32 vel[3];
    s16 a, b, c;
    s16 r, g, z;
} PchrBurstPart;

typedef struct PchrBurstFx {
    s16 pad_0[10];
    s16 rx, ry, rz, pad_1A;
    s32 dir[3];
    s32 pad_28[2];
    s32 count;
    PchrBurstPart parts[1];
} PchrBurstFx;

/* from stage_setup_load */
typedef struct SetupLight {
    s16 x;
    s16 y;
    s16 z;
    s16 flags;
} SetupLight;
/* from stage_setup_load */
typedef struct SetupColourRange {
    s16 first;
    s16 last;
    s16 value;
    s16 pad_06;
} SetupColourRange;
/* from stage_setup_load */
typedef struct SetupLightRecord {
    /* 0x00 */ s32 tex_flag;
    /* 0x04 */ s32 on;
    /* 0x08 */ s32 flag;
    /* 0x0C */ s16 vec[3];
    /* 0x12 */ s16 pad_12;
    /* 0x14 */ s16 point[2];
    /* 0x18 */ u8 colour[3][4];
    /* 0x24 */ s16 dir_angles[3][2];
    /* 0x30 */ s16 part[7][4];
} SetupLightRecord;

/* from push_out_of_solids_xz */
typedef struct MovingBox {
    s16 size[3];   /* 0x00: written to the box; size[0] is zero for an unused part */
    s16 offset[3];  /* 0x06: offset added to the owner's position */
    s16 offset_delta[3];  /* 0x0C: change of offset this step */
    s16 size_delta[3]; /* 0x12: change of size this step */
} MovingBox;
/* from draw_view_entries */
typedef struct DrawEntry {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 scale;
    /* 0x06 */ s16 next;   /* next entry, < 0: end */
    /* 0x08 */ s16 w;      /* clip: width; sprite: rotation x */
    /* 0x0A */ s16 h;      /* clip: height; sprite: rotation y */
    /* 0x0C */ s16 rot_z;
    /* 0x0E */ s16 flags;  /* 0x8000: clip rect; & 0xFFF: shape index in shape_slot_table */
    /* 0x10 */ u32 colour;
} DrawEntry;
/* from draw_view_entries */
typedef struct DrawMatrix {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} DrawMatrix;
/* from draw_view_entries */
typedef struct DrawXform {
    /* 0x00 */ s16 scale_x, scale_y;
    /* 0x04 */ s32 ox, oy;
    /* 0x0C */ s32 clip_w, clip_h;
    /* 0x14 */ DrawMatrix base;
    /* 0x34 */ DrawMatrix rot;
} DrawXform;
/* from draw_view_entries */
typedef struct ClipRect {
    s16 x, y, w, h;
} ClipRect;
/* from draw_view_entries */
typedef struct DrawView {
    /* 0x00 */ s16 scale_x, scale_y;
    /* 0x04 */ u8 pad_04[4];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 pad_0A[0xA];
    /* 0x14 */ ClipRect clip;
    /* 0x1C */ s16 centre_x, centre_y;
    /* 0x20 */ s32 rot[5]; /* GTE rotation matrix */
    /* 0x34 */ u8 pad_34[0x74];
} DrawView;
/* from draw_view_entries */
typedef struct DrawIdTable {
    IdTable head;
    DrawEntry entry[1];
} DrawIdTable;

/* from aobj_build_face_boxes */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk_06;
} Vertex;
/* from aobj_build_face_boxes */
typedef struct {
    u8 unk_00[3];
    u8 vtx[4];
    u8 unk_07[5];
} QuadFace;
/* from aobj_build_face_boxes */
typedef struct {
    s32 count;
    u8 unk_04[5];
    QuadFace faces[1];
} QuadFaceList;
/* from aobj_build_face_boxes */
typedef struct {
    s16 min_x;
    s16 max_x;
    s16 min_y;
    s16 max_y;
    s16 min_z;
    s16 max_z;
} FaceBox;
/* from aobj_build_face_boxes */
typedef struct {
    s32 unk_00;
    Vertex *verts;
    QuadFaceList *faces;
    s32 unk_0C;
    FaceBox *boxes;
} BoxedMesh;

/* from solid_setup */
typedef struct SolidShape {
    /* 0x00 */ u8 unk_00[0x1C];
    /* 0x1C */ s32 pos[3];
    /* 0x28 */ u8 unk_28[4];
    /* 0x2C */ s16 size[3];
} SolidShape;

/* from quad_list_build */
typedef struct Rec800CF0D0 {
    s32 w[7];
} Rec800CF0D0;

/* from lock_target_distance */
typedef struct SelRecord {
    s32 pos[3];
    s16 unk_0C;
    s16 radius;
} SelRecord;

/* from rec_table_query_box */
typedef struct CellQuery {
    s16 x[2];
    s16 y[2];
    s16 z[2];
    s32 word;
    s16 id;
    u8 count;
    u8 kind;
} CellQuery;

/* from packet_spans_at_height */
typedef struct PacketSpan {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 y_top;
    /* 0x06 */ s16 y_bottom;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 pos;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 flags;
    /* 0x18 */ s32 depth;
} PacketSpan;
/* from packet_spans_at_height */
typedef struct PacketSpanArea {
    /* 0x0000 */ u8 pad0[0x1400];
    /* 0x1400 */ s32 count;
    /* 0x1404 */ PacketSpan recs[0x100];
    /* 0x1404 + 0x1C * 0x100 = 0x3004 */
    u8 pad1[0x8C08 - 0x3004];
    /* 0x8C08 */ s16 order[1];
} PacketSpanArea;
/* from packet_spans_at_height */
typedef struct SpanBracket {
    s16 y_top;
    s16 y_bottom;
    s32 pos_top;
    s32 pos_bottom;
    s32 depth;
} SpanBracket;

/* from fx_glow_draw */
typedef struct FxGlowScratch {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 pad_06;
    /* 0x08 */ s16 extent_x; /* signed x and z size of the quarter fx_glow_grid_draw draws */
    /* 0x0A */ s16 extent_z;
    /* 0x0C */ s32 level;
    /* 0x10 */ s32 colour;
    /* 0x14 */ WorkArea *work;
    /* 0x18 */ u32 *ot;
} FxGlowScratch;
/* from fx_glow_draw */
typedef struct FxOtBuffer {
    /* 0x00 */ u32 unk_00[8];
    /* 0x20 */ u32 front; /* unsorted entry, in front of the depth-sorted ones */
    /* 0x24 */ u32 ot[0x200];
} FxOtBuffer;

/* from red_laser_ball_update */
typedef struct SinCosHalves {
    u16 sin;
    s16 cos;
} SinCosHalves;

/* from prim_draw_mirrored_sprite */
typedef struct DrTexWindow {
    u8 link[3];
    u8 len;
    u32 code[2];
} DrTexWindow;

/* from countdown_trace */
typedef struct TraceSegment {
    Vec3 start; /* 0x00 */
    s32 pad_0C; /* 0x0C */
    Vec3 end;   /* 0x10 */
    s32 pad_1C; /* 0x1C */
} TraceSegment;

/* from sprite_draw_rect */
typedef struct PrimBuf {
    /* 0x00 */ u8 unk_00[0x74];
    /* 0x74 */ u8 *top;
} PrimBuf;
/* from sprite_draw_rect */
typedef struct WinPolyFT4 {
    /* 0x00 */ u8 link[3];
    /* 0x03 */ u8 len;
    /* 0x04 */ u32 tex_window;
    /* 0x08 */ union {
        u32 word;
        struct { u8 r, g, b, code; } c;
    } rgbc;
    /* 0x0C */ s16 x0, y0;
    /* 0x10 */ u8 u0, v0;
    /* 0x12 */ u16 clut;
    /* 0x14 */ s16 x1, y1;
    /* 0x18 */ u8 u1, v1;
    /* 0x1A */ u16 tpage;
    /* 0x1C */ s16 x2, y2;
    /* 0x20 */ u8 u2, v2;
    /* 0x22 */ u16 pad_22;
    /* 0x24 */ s16 x3, y3;
    /* 0x28 */ u8 u3, v3;
    /* 0x2A */ u16 pad_2A;
} WinPolyFT4;
/* from sprite_draw_rect */
typedef struct SpriteRec {
    /* 0x00 */ s16 half_w;
    /* 0x02 */ s16 half_h;
    /* 0x04 */ u8 *ot;
    /* 0x08 */ s32 xy;
    /* 0x0C */ PrimBuf *buf;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u32 color;
} SpriteRec;

/* from prim_fade_quad_shade */
typedef struct PrimGp0Cmd {
    u8 link[3];
    u8 len;
    u32 code;
    u32 pad;
} PrimGp0Cmd;
/* from prim_fade_quad_shade */
typedef struct FadeQuad {
    u8 link[3];
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    u8 r1, g1, b1, p1;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    u8 r2, g2, b2, p2;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad2;
    u8 r3, g3, b3, p3;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad3;
} FadeQuad;
/* from prim_fade_quad_shade */
typedef struct FadeRect {
    u16 x, y, w, h;
} FadeRect;

/* from prim_fade_curtain */
typedef struct PolyGT4 {
    u8 link[3];
    u8 len;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    u8 r1, g1, b1, pad1;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    u8 r2, g2, b2, pad2;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad3;
    u8 r3, g3, b3, pad4;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad5;
} PolyGT4;

/* from light_backdrop_draw */
typedef struct LightSetColours {
    s16 v[3];
    u8 unk_06[2];
    s32 colour_c; /* 0x08 */
    s32 colour_a; /* 0x0C */
    s32 colour_b; /* 0x10 */
    u8 unk_14[0x58];
    s32 out_a; /* 0x6C, same as point.out_a */
    s32 out_b; /* 0x70 */
    u8 unk_74[8];
    s16 use_a; /* 0x7C, same as point.unk_10 */
    s16 use_b; /* 0x7E, same as point.unk_12 */
    u8 unk_80[4];
} LightSetColours;

/* from tex_block_upload */
typedef struct TexBlockHeader {
    u8 unk_00[4];
    u16 width;  /* big-endian */
    u16 height; /* big-endian */
    u8 pixels[1];
} TexBlockHeader;

/* from zone_x_range */
typedef struct EdgeQuery {
    u8 pad_00[0x18];
    s16 radius; /* 0x18 */
    u8 pad_1A[0x16];
    s32 x; /* 0x30 */
    s32 z; /* 0x34 */
} EdgeQuery;
/* from zone_x_range */
typedef struct ZonePoint {
    s16 x;
    s16 z;
    u8 pad_4[4];
} ZonePoint;
/* from zone_x_range */
typedef struct ZoneRec {
    s16 x_min; /* 0x0 */
    s16 x_max; /* 0x2 */
    s16 z_min; /* 0x4 */
    s16 z_max; /* 0x6 */
    u8 pad_8[4];
    s32 key;   /* 0xC: (model key << 8) | face index */
    s16 first; /* 0x10 */
    s16 count; /* 0x12 */
    s32 colour; /* 0x14 */
    s32 depth; /* 0x18: GTE MAC2 of the face normal */
} ZoneRec;
/* from zone_x_range */
typedef struct ZoneTable {
    u8 pad_0000[0x1000];
    ClipVertex verts[128]; /* 0x1000: transformed model vertices (when more than fit the scratchpad) */
    s32 count;          /* 0x1400 */
    ZoneRec recs[512];  /* 0x1404 */
    s32 point_count;    /* 0x4C04 */
    ZonePoint points[1]; /* 0x4C08 */
} ZoneTable;

/* from wall_segment_bisect */
typedef struct Point4 {
    s32 x, y, z, w;
} Point4;
/* from wall_segment_bisect */
typedef struct WallSegment {
    Point4 a, b;
} WallSegment;

/* from func_800C35A0 */
typedef struct ModelSlotHead {
    s32 words[3];
} ModelSlotHead;

/* from cam_view_update */
typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unk_0C;
    s16 pitch;
    s16 yaw;
    s16 roll;
    s16 pad_16;
    s32 dist; /* smoothed camera distance (value_approach state), -1 = not set */
} CamViewSource;
/* from cam_view_update */
typedef struct {
    s32 unk_00[6];
    s32 pos_x;
    s32 pos_y;
    s32 pos_z;
    s32 unk_24[3];
    s32 yaw;
    s32 pitch;
    s32 roll;
} CamViewState;

/* from box_ground_probe */
typedef struct GroundBox {
    /* 0x00 */ u8 unk_00[0x14];
    /* 0x14 */ u32 flags;
    /* 0x18 */ s16 half_x;
    /* 0x1A */ s16 half_y;
    /* 0x1C */ s16 half_z;
    /* 0x1E */ u8 unk_1E[0x12];
    /* 0x30 */ s32 x;
    /* 0x34 */ s32 y;
    /* 0x38 */ s32 z;
    /* 0x3C */ u8 unk_3C[0x1C];
    /* 0x58 */ MatrixHalf corner_a;
    /* 0x68 */ MatrixHalf corner_b;
} GroundBox;

/* from fade_mask_draw */
typedef struct PrimMaskCmd {
    u8 link[3];
    u8 len;
    u32 cmd;
    u32 data;
} PrimMaskCmd;
/* from fade_mask_draw */
typedef struct PrimDrawAreas {
    u8 link[3];
    u8 len;
    u32 e3;
    u32 e4;
    u32 e5;
} PrimDrawAreas;

/* from player_tilt_to_ground */
typedef struct PlayerPosWords {
    s32 w[4];
} PlayerPosWords;

/* from sort_records_by_band */
typedef struct SortRecord {
    s16 x;
    s16 pad2;
    s16 z;
    u16 flags;
} SortRecord;
/* from sort_records_by_band */
typedef struct SortInput {
    s32 count;
    SortRecord recs[1];
} SortInput;
/* from sort_records_by_band */
typedef struct SortGroup {
    s16 start;
    s16 len;
} SortGroup;
/* from sort_records_by_band */
typedef struct SortResult {
    SortInput *input;
    s16 first_key;
    s16 num_groups;
    SortGroup groups[1];
} SortResult;

/* from stage_model_block_load */
/* ModelBlockRef, ModelBlockRange, ModelBlock: resource.h */

/* from collide_solid_cells */
typedef struct SolidOwner {
    union {
        s16 id;
        struct {
            u8 unk_0;
            u8 flags; /* tested against collide_mode and Collider.unk_4D */
        } b;
    } head;
} SolidOwner;
/* from collide_solid_cells */
typedef struct SolidPartHit {
    s16 size[3];
    s16 off[3];
    u8 unk_0C[6];
    s16 size_delta[3];
} SolidPartHit;

/* from colour_intpl_list */
typedef struct {
    s16 b;
    s16 g;
    s32 r;
} IntplColour;

/* from wall_quad_at */
typedef struct WallQuadTable {
    s32 *quads;    /* 0x0: count, then 4 packed corners per quad */
    s32 *centers;  /* 0x4: count, then (z << 12 | quad, x << 12) pairs */
    u16 cells[1];  /* 0x8 */
} WallQuadTable;

/* from zone_y_range */
typedef struct ZoneQueryY {
    u8 pad_00[0x1C];
    s16 radius; /* 0x1C */
    u8 pad_1E[0x16];
    s32 z; /* 0x34 */
    s32 y; /* 0x38 */
} ZoneQueryY;
/* from zone_y_range */
typedef struct ZoneRecY {
    s16 x_min; /* 0x0 */
    s16 x_max; /* 0x2 */
    s16 z_min; /* 0x4 */
    s16 z_max; /* 0x6 */
    s16 y_min; /* 0x8 */
    s16 y_max; /* 0xA */
    u8 pad_C[4];
    s16 first; /* 0x10 */
    s16 count; /* 0x12 */
    u8 pad_14[8];
} ZoneRecY;
/* from zone_y_range */
typedef struct ZonePointY {
    s16 x;
    s16 z;
    s16 y;
    u8 pad_6[2];
} ZonePointY;
/* from zone_y_range */
typedef struct ZoneTableY {
    u8 pad_0000[0x1400];
    s32 count;          /* 0x1400 */
    ZoneRecY recs[512];  /* 0x1404 */
    s32 point_count;    /* 0x4C04 */
    ZonePointY points[1]; /* 0x4C08 */
} ZoneTableY;

/* from time_bomb_draw */
typedef struct ScratchRot {
    SVECTOR spark_rot;
    SVECTOR rot;
} ScratchRot;

/* from cam_fade_draw */
typedef struct PrimBgRect {
    u8 link[3];
    u8 len;
    u8 r, g, b;
    u8 code;
    s16 x, y;
    u16 w, h;
} PrimBgRect;
/* from cam_fade_draw */
typedef struct PrimFadeStrip {
    u8 link[3];
    u8 len;
    u8 r, g, b;
    u8 code;
    s16 x, y;
    u8 u, v;
    u8 pad_0E[2];
    s16 w, h;
} PrimFadeStrip;

/* from trace_shot_phase1 */
typedef struct TraceShotSeg {
    Quad from;
    Quad to;
} TraceShotSeg;

/* from sound_handle_slots_update */
typedef struct SoundHandleSlot {
    /* 0x00 */ u16 id_a;
    /* 0x02 */ u16 id_b;
    /* 0x04 */ s32 voice_a;
    /* 0x08 */ s32 voice_b;
    /* 0x0C */ s16 delay;
    /* 0x0E */ s16 timer;
    /* 0x10 */ u16 volume;
    /* 0x12 */ u16 pan;
    /* 0x14 */ u16 pitch;
    /* 0x16 */ u8 pad_16[2];
    /* 0x18 */ SoundPos saved_pos;
    /* 0x28 */ SoundPos default_pos;
    /* 0x38 */ void *(*update)(void *owner, s32 index);
    /* 0x3C */ void *owner;
    /* 0x40 */ u8 flags;
    /* 0x41 */ u8 pad_41[2];
    /* 0x43 */ u8 next;
} SoundHandleSlot;

/* from player_slope_push */
typedef struct GroundTileEntry {
    u8 *tris;
    s32 pad[4];
} GroundTileEntry;
/* from player_slope_push */
typedef struct SlopeRec {
    s32 x, y, z, kind;
} SlopeRec;

/* from model_bounds_radius */
typedef struct ModelVert {
    u16 x, y, z;
    s16 pad_06[3];
} ModelVert;

/* from point_light_glow_draw */
typedef struct PointLight {
    s32 x, y, z;
    s16 env;
    s16 intensity; /* negative: always drawn, at -intensity */
} PointLight;

/* from player_frame_update */
typedef struct SubPos {
    s32 v[4];
} SubPos;

/* from pose_rotate_range */
typedef struct PosePoint {
    u16 pos[3];
    s16 ang[3];
} PosePoint;

/* from part_rec_visible */
typedef struct TrackPart {
    /* 0x00 */ s32 pos[3];
    /* 0x0C */ u8 unk_0C[5];
    /* 0x11 */ u8 kind;
    /* 0x12 */ u8 unk_12[0xE];
} TrackPart;

/* from text_put_char */
typedef struct GlyphSprite {
    u8 tag[3];
    u8 len;
    u8 r, g, b;
    u8 code;
    s16 x, y;
    u16 uv;
    u16 clut;
} GlyphSprite;

/* views[i] from +0x54 (view_tails, 0xA8 apart): light_env_draw addresses the view through this base. */
typedef struct ViewTail {
    /* 0x00 */ s16 vram_x, vram_y, vram_w, vram_h;
    /* 0x08 */ s16 ofs_x, ofs_y;
    /* 0x0C */ s16 rot[3][3];
    /* 0x1E */ u8 pad_1E[0x6E];
    /* 0x8C */ s16 next_scale_x, next_scale_y; /* the next view's sprite scale (its record starts 0x1C before its ViewTail) */
    /* 0x90 */ u8 pad_90[0x18];
} ViewTail;
/* d_8011FFE4 (gte_light_setup copies work_area_ptr->unk_80 there) and the end of light_env_draw's draw records,
 * read as one struct (`draw_list`, an asm alias): a struct member's load stays below the scratch stores as in the
 * original (MEM_IN_STRUCT_P), a scalar's is hoisted above them. */
typedef struct DrawList {
    s32 unk_00;
    s32 *end;
} DrawList;
/* from light_env_draw */
typedef struct DrawRec {
    s16 head;  /* bit 15: single entry; low bits: byte offset back to the index words */
    s16 prim;  /* bit 15: wrap in a DR packet; low bits: word offset into the primitive buffer */
    s32 color;
    s32 arg;
} DrawRec;
/* from light_env_draw */
typedef struct DrawScratch {
    s32 env[4];
    s32 rot[4];
    s16 rot33;
    s16 pad;
    s32 trans[3];
} DrawScratch;
/* GPU POLY_F3 (flat triangle, code 0x20) with packed (x, y) vertex words (prim_triangle_fan_add) */
typedef struct PolyF3 {
    u8 link[3];
    u8 len;
    u32 rgb_code;
    u32 xy[3];
} PolyF3;

/* from light_records_build */
typedef struct LightRec18 {
    /* 0x00 */ s16 x, y, z;
    /* 0x06 */ s16 index; /* low 11 bits: pchr entry; 0xB000: flags */
    /* 0x08 */ u8 pad_08[6];
    /* 0x0E */ s16 next;
    /* 0x10 */ s16 depth;
    /* 0x12 */ s16 level;
    /* 0x14 */ u8 pad_14[4];
} LightRec18;

/* from pchr_bank_load */
typedef struct PchrPrim {
    /* 0x00 */ u16 clut;
    /* 0x02 */ u16 tpage;
    /* 0x04 */ union {
        s32 word;
        struct {
            u8 u_base, v_base, w, h;
        } b;
    } tex;
    /* 0x08 */ u8 rgb[4];
    /* 0x0C */ union {
        u8 uv[8];
        u16 clut4[4];
    } c;
    /* 0x14 */ u8 pad_14[8];
} PchrPrim;

/* from view_border_draw */
typedef struct PrimLineF3 {
    u8 link[3];
    u8 len;
    union {
        s32 word;
        struct {
            u8 r, g, b, code;
        } c;
    } colour;
    s16 x0, y0, x1, y1, x2, y2;
    u32 term;
} PrimLineF3;

/* from shadow_pass_draw */
typedef struct LightEnvColour {
    u8 pad_00[8];
    s16 x, y, z;
    u8 pad_0E[0x76];
} LightEnvColour;

/* from flier_callback */
typedef struct DebrisVars {
    /* 0x248 */ u8 flying;      /* nonzero: flies off, else just counts down */
    /* 0x249 */ u8 pad_249[3];
    /* 0x24C */ s16 pitch_turn;
    /* 0x24E */ s16 pitch;
    /* 0x250 */ s16 timer;      /* -2: start, -1: finish, else countdown */
    /* 0x252 */ s16 ground;     /* bit 0 set when the trace found the floor at the aim point */
    /* 0x254 */ u8 pad_254[8];
    /* 0x25C */ s32 floor_a;
    /* 0x260 */ s32 floor_b;
    /* 0x264 */ s32 floor_diff;
    /* 0x268 */ s32 yaw_turn;
    /* 0x26C */ u8 pad_26C[0x10];
    /* 0x27C */ u8 sound;
} DebrisVars;

/* from req_queue_lamps_draw */
typedef struct LampColour {
    s16 r, g, b, pad;
} LampColour;

/* from pose_list_intpl */
typedef struct {
    s16 x, y, z;
    s16 rx, ry, rz;
} PoseKey;

/* from ground_slope_lookup */
typedef struct ModelPosEntry {
    s16 x;
    s16 y;
    s16 z;
    s16 aobj;
} ModelPosEntry;
/* from ground_slope_lookup */
typedef struct ModelPosTable {
    s32 count;
    ModelPosEntry entries[1];
} ModelPosTable;

/* from prim_vram_load_packet */
typedef struct DrawLoadPacket {
    u8 tag_addr[3];
    u8 len;
    u32 code;
    s32 xy;
    s32 wh;
    u32 data[13];
} DrawLoadPacket;
/* from prim_vram_load_packet */
typedef struct RectWords {
    s32 xy;
    s32 wh;
} RectWords;

/* from obj_link_script_run */
typedef struct ScriptCallEntry {
    ObjHandlerFn fn;
    s32 unk_04;
} ScriptCallEntry;

/* from sea_mine_draw */
typedef struct GlowSparkVars {
    u8 pad_000[0x248];
    s16 size_phase; /* sine phase of the spark size */
    u8 pad_24A[4];
    s16 second_spark_model_offset; /* model offset of the second spark */
    u8 pad_250[4];
    s16 second_spark_y; /* y of the second spark */
    s16 blink_enabled; /* nonzero: unk_258 toggles every step (blink) */
    s16 red_color; /* nonzero: red colour */
    s16 unk_25A; /* 0: model + 4, else model + 1 */
    s16 second_spark_enabled; /* nonzero: second spark */
} GlowSparkVars;

/* from player_ground_clip */
typedef struct PlayerBox {
    s32 lo[3];
    s32 unk_0C;
    s32 hi[3];
} PlayerBox;

/* from colour_list_intpl */
typedef union PackedColour {
    s32 word;
    struct {
        s8 r;
        s8 b;
        s8 g;
        s8 code;
    } c;
} PackedColour;
/* from colour_list_intpl */
typedef struct ColourIntplScratch {
    PackedColour far;
    PackedColour base;
} ColourIntplScratch;

/* from lens_flare_draw */
typedef struct LensFlare {
    s16 offset;    /* how far along the line through the screen centre, /120 */
    s16 size;
    s16 pal;
    s16 intensity;
    s16 r, g, b;
    s16 pad_0E;
} LensFlare;
/* from lens_flare_draw */
typedef struct FlareView {
    s16 x, y, w, h;
    u8 pad_08[0xA0];
} FlareView;

/* from trace_solids_masked */
typedef struct SweepScratch {
    /* 0x00 */ s32 m_local[8];   /* world -> sweep frame */
    /* 0x20 */ s32 m_world[8];   /* sweep frame -> world */
    /* 0x40 */ SVECTOR rel;
    /* 0x48 */ SVECTOR dir;
    /* 0x50 */ SVECTOR ext;
    /* 0x58 */ Vec8 axes[4];
    /* 0x78 */ SVECTOR wrel;
    /* 0x80 */ SVECTOR seg;
    /* 0x88 */ MovingBox box;
} SweepScratch;

/* from scene_models_project */
typedef struct CamRotation {
    /* 0x00 */ s32 rot[5];
    /* 0x14 */ u8 pad_14[0x94];
} CamRotation;
/* from scene_models_project */
typedef struct ModelRowsHdr {
    /* 0x00 */ u8 *verts;
    /* 0x04 */ s16 first_row;
    /* 0x06 */ s16 num_rows;
    /* 0x08 */ struct {
        s16 start;
        s16 count;
    } rows[1];
} ModelRowsHdr;
/* from scene_models_project */
typedef struct ModelVert8 {
    /* 0x0 */ s16 x, y, z;
    /* 0x6 */ s16 idx;
} ModelVert8;
/* from scene_models_project */
typedef struct ModelVertWords {
    /* 0x0 */ s32 xy;
    /* 0x4 */ s32 z_idx;
} ModelVertWords;
/* from scene_models_project */
typedef struct OutRec18 {
    /* 0x00 */ s16 x, y, z;
    /* 0x06 */ u16 flags;
    /* 0x08 */ s16 unk_08[3];
    /* 0x0E */ u8 pad_0E[6];
    /* 0x14 */ s32 colour;
} OutRec18;

/* from trace_world_sweep */
typedef struct SweepVec {
    s32 x, y, z, w;
} SweepVec;
/* from trace_world_sweep */
typedef struct SweepPart {
    s32 xy;
    s32 z_aobj;
} SweepPart;
/* from trace_world_sweep */
typedef struct SweepWords {
    s32 lo, hi;
} SweepWords;
/* from trace_world_sweep */
typedef struct SweepFace {
    s16 nx, ny, nz, pad;
    u8 idx[4];
} SweepFace;

/* from view_frame_setup */
typedef struct ViewSetup {
    /* 0x00 */ s16 on;
    /* 0x02 */ s16 parent; /* View.unk_02: index of the view this one sits in; < 0: the screen */
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 camera;
    /* 0x08 */ s16 x, y;
    /* 0x0C */ s16 w, h;
    /* 0x10 */ s16 origin_offset_x, origin_offset_y, unk_14, unk_16;
    /* 0x18 */ s16 clip_w, clip_h;
    /* 0x1C */ CVECTOR colour, colour_b, colour_c;
    /* 0x28 */ s32 ready; /* View.unk_28: set up this frame */
    /* 0x2C */ RECT box;  /* the parent's visible rect (the screen for a top view) */
    /* 0x34 */ s16 box_scale_x, box_scale_y; /* the parent's scale, 0x1000 = 1 */
    /* 0x38 */ s16 cam_scale[4]; /* camera projection scale times scale_x/y, times scale_vec */
    /* 0x40 */ s16 scale_x, scale_y, scale_z; /* clip size / size, times the parent's */
    /* 0x46 */ s16 pad_46;
    /* 0x48 */ s16 depth_scale; /* 0x1000000 >> shift, at most 0x7FFF */
    /* 0x4A */ s16 depth_unit;  /* View.unk_4A: 1 << shift */
    /* 0x4C */ s16 area_x, area_y, area_w, area_h; /* the view's rect before clipping to box */
    /* 0x54 */ RECT vram; /* View.vram_x..vram_h: area clipped to box */
    /* 0x5C */ s16 origin_x, origin_y; /* the projection centre, relative to vram */
    /* 0x60 */ s16 rot[3][3]; /* camera rotation (yaw, pitch, roll) */
    /* 0x72 */ s16 pad_72[7];
    /* 0x80 */ s16 rot_b[3][3]; /* camera rotation without yaw */
    /* 0x92 */ s16 pad_92[7];
    /* 0xA0 */ u32 *ot;   /* View.unk_A0: 0x20A-entry ordering table; NULL without a camera */
    /* 0xA4 */ u32 *prim; /* 3-entry ordering table */
} ViewSetup;

/* from atr_map_build */
typedef union AtrCellWords {
    BucketSrc cell;
    s32 words[2];
} AtrCellWords;

/* from surface_of */
typedef struct SurfaceSpan {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
} SurfaceSpan;
/* from surface_of */
typedef struct SurfaceKind {
    u8 pad_00[10];
    u8 surface;
    u8 pad_0B;
} SurfaceKind;

/* from sound_play_note */
typedef struct SoundVoiceRequest {
    s32 flags;      /* 0x00 sound_key_cmd */
    s32 voice;      /* 0x04 sound_key_voice */
    s32 pad_08;
    s32 volume;     /* 0x0C sound_key_volume */
    s32 pad_10;
    s32 scale;      /* 0x14 sound_key_rate */
    s16 pan;        /* 0x18 sound_key_pan */
    s16 key;        /* 0x1A sound_key_note */
    s16 fine_pitch; /* 0x1C sound_key_pitch */
    s16 mode;       /* 0x1E sound_key_mode */
} SoundVoiceRequest;

/* from light_backdrop_strip_draw */
typedef struct PolyGT4Rgb {
    u8 link[3];
    u8 len;
    union {
        u32 rgb;
        u8 c[4];
    } rgb0;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    u32 rgb1;
    s16 x1, y1;
    u8 u1, v1;
    u16 tpage;
    u32 rgb2;
    s16 x2, y2;
    u8 u2, v2;
    u16 pad2;
    u32 rgb3;
    s16 x3, y3;
    u8 u3, v3;
    u16 pad3;
} PolyGT4Rgb;

/* from light_matrix_set */
typedef struct ViewVramRect {
    s16 x, y, w, h;
} ViewVramRect;
/* from light_matrix_set */
typedef struct ViewOffset {
    s16 x, y;
} ViewOffset;
/* from light_matrix_set */
typedef struct ViewLightParams {
    s16 w, h;
    u8 pad_04[0x18];
    ViewVramRect lim;
    ViewOffset off;
    /* 0x28 */ s16 rot[3][3]; /* View.rot */
    /* 0x3A */ u8 pad_3A[0xE];
    /* 0x48 */ s16 rot_b[3][3];
    /* 0x5A */ u8 pad_5A[0x4E];
} ViewLightParams;

/* from zone_add_model_faces */
typedef struct MeshFace {
    s16 normal[3];
    u8 colour;
    u8 pad_7;
    u8 v[4];
} MeshFace;

/* from scratch_slot_load */
typedef struct TexCellEntry {
    s16 tpage;
    u8 nib;
    u8 flags;
} TexCellEntry;
/* from scratch_slot_load */
typedef struct ColourRec {
    s32 unk_0;
    union {
        s32 packed;
        struct {
            s16 index;
            u8 mode;
        } src;
    } u;
} ColourRec;

/* from model_groups_draw */
typedef struct ModelTables {
    s32 *verts;
    s32 *norms;
    s32 *groups;
} ModelTables;

/* from cam_place_behind_player: cam_distance stored as a struct member keeps the store before its cam_state loads */
typedef struct {
    s32 v;
} CamDistance;

/* from fx_glow_grid_draw */
typedef struct GlowVert {
    /* 0x00 */ s32 sxy;     /* screen x, y from the GTE */
    /* 0x04 */ u8 u;
    /* 0x05 */ u8 v;
    /* 0x06 */ u16 clipped; /* GTE FLAG had an error bit set */
} GlowVert;

/* from light_draw_list_build */
typedef struct LightDrawPos {
    s32 xy;
    union {
        s32 word;
        struct {
            s16 z;
            s16 depth;
        } h;
    } zf;
} LightDrawPos;
/* from light_draw_list_build */
typedef union LightDrawTrans {
    s32 w[2];
    SVECTOR v;
} LightDrawTrans;
/* from light_draw_list_build */
typedef struct LightDrawNode {
    /* 0x00 */ LightDrawPos pos;
    /* 0x08 */ LightDrawTrans trans;
    /* 0x10 */ s16 rot[10];
    /* 0x24 */ s16 light[10];
} LightDrawNode;
/* from light_draw_list_build */
typedef struct LightDrawRoot {
    /* 0x00 */ SVECTOR scale;
    /* 0x08 */ LightDrawNode node;
} LightDrawRoot;
/* from light_draw_list_build */
typedef struct LightRecWords {
    /* 0x00 */ s32 xy;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 index; /* low 11 bits: pchr entry; 0x1000, 0x2000: matrix flags */
    /* 0x08 */ s32 rot_xy;
    /* 0x0C */ s16 rot_z;
    /* 0x0E */ s16 next;
    /* 0x10 */ s32 depth_level;
    /* 0x14 */ s32 unk_14;
} LightRecWords;
/* from light_draw_list_build */
typedef struct LightDrawOut {
    s16 size;   /* bytes of the block; bit 15: a single mesh part, no key list */
    s16 level;  /* the record's level */
    s32 unk_04; /* LightRec18 0x14, low 24 bits */
    Pchr *pchr;
} LightDrawOut;
/* from light_draw_list_build */
typedef struct LightDepthKey {
    s32 key;
    s32 dist;
} LightDepthKey;
/* from light_draw_list_build */
typedef struct PchrBone {
    s16 x, y, z;
    s16 rx, ry, rz;
} PchrBone;
/* from light_draw_list_build */
typedef struct PchrVert {
    s32 xy;
    s16 z;
    s16 pad;
} PchrVert;
/* from light_draw_list_build */
typedef union PchrPartCursor {
    s32 *word;
    s16 *index;
} PchrPartCursor;

/* from mask_layers_draw */
typedef struct MaskLayer {
    u32 head;
    u32 end;
    struct MaskLayer *next;
    s32 fade;
} MaskLayer;
/* from mask_layers_draw */
typedef struct PrimVramCopy {
    u8 link[3];
    u8 len;
    u8 pad_04[3];
    u8 flush;
    u32 cmd;
    s16 src_x, src_y;
    s16 dst_x, dst_y;
    s16 w, h;
} PrimVramCopy;

/* obj->sounds: sound id and volume pairs; read by the script runner (script_run_neg_ops). */
typedef struct SoundVolume {
    s32 sound;
    s32 volume;
} SoundVolume;

/* A script step list entry: the step kind (-1 ends the list) and its value; lists in supermech_script_entry (S12). */
typedef struct ScriptStep {
    s16 kind;
    s16 value;
} ScriptStep;

/* A sound owner for sound_start_attached: a count and that many line segments; sound_attached_update plays the
 * sound at the closest point (S02 cam_zone_spawn, S03 stage_sound_owner_a/b). Data definitions list the segments
 * after the count (cc1 lays a zero-length array's initializer out after the struct). */
typedef struct SoundSegmentList {
    s32 count;
    SoundSegment segs[0];
} SoundSegmentList;

/* A beam segment's step (beam_segment_data, read by beam_segment_update/draw): at health below
   health_below it switches to the next step's speed; model is added to the beam's sound slot. */
typedef struct BeamStep {
    /* 0x00 */ s16 health_below;
    /* 0x02 */ s16 model;
    /* 0x04 */ s16 speed;
    /* 0x06 */ s16 unk_06;
} BeamStep;

/* Point-light list: a count, then that many lights; passed to set_data_base (s01 data_base_area, s04 stage_data_base). */
typedef struct LightData {
    s32 count;
    PointLight lights[1];
} LightData;

/* s11 obj_pair_model_table: 0x14-byte records, index kind * 2 + i (obj_spawn_pair_from_placement, placed_rect_trigger) */
typedef struct PlacedRectDef {
    s16 model_part;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 x_max;
    s16 z_max;
    s16 x_min; /* negated by the reader */
    s16 z_min; /* negated by the reader */
    s16 unk_10;
    s16 unk_12;
} PlacedRectDef;

#endif
