/* s10's own types: the ones only its own code and data use (the shared ones are in stage_types.h). */
#ifndef S10_TYPES_H
#define S10_TYPES_H

#include "stage_types.h"

/* from func_800C929C */
typedef struct ObjSetupBytes {
    u8 unk_248[4];
    u8 unk_24C;
    u8 unk_24D;
    u8 unk_24E;
    u8 unk_24F;
    u8 unk_250;
    u8 unk_251;
    u16 unk_252;
} ObjSetupBytes;

/* from func_800C2880 */
typedef struct CmdReader {
    u8 unk_00[0x20];
    u8 *cursor;             /* 0x20 */
    u8 unk_24[0x208];       /* 0x24 */
    u16 value;              /* 0x22C */
} CmdReader;

/* from func_800C2B30 */
typedef struct ByteStream {
    u8 pad_00[0x20];
    u8 *pos; /* read cursor; advances 2 bytes per call */
} ByteStream;

/* from func_800C2990 */
typedef struct ScriptBranchHeight {
    u8 pad_00[0x1C];
    /* 0x1C */ s32 *targets;
    /* 0x20 */ s16 *pc;
    u8 pad_24[0x1F4 - 0x24];
    /* 0x1F4 */ s32 deadline;
} ScriptBranchHeight;

/* from func_800C244C */
typedef struct CmdStream {
    u8 unk_00[0x1C];
    s32 *table;      /* 0x1C: address table, indexed by the operand after the key */
    u8 *cursor;      /* 0x20: next unread byte of the stream */
    u8 unk_24[0x24C - 0x24];
    s16 selector;    /* 0x24C: the current selector value */
} CmdStream;

/* from func_800C053C */
typedef struct DoorState {
    s8 active;
    s8 unk1;
    u8 unk2;
    s8 unk3;
    s16 scale;
    s16 value;
} DoorState;

/* from func_800C090C */
typedef struct {
    u8 active;
    u8 reverse;
    s16 pad2;
    s16 level;
    s16 step;
} DoorFadeEntry;

/* from func_800C8C50 */
typedef struct ObjPhaseEntry {
    ObjHandlerFn fn;
    ObjHandlerFn later[3]; /* phases 1-3: the code reads them as obj_phase1..3_table[kind].fn */
} ObjPhaseEntry;

/* from elevator_door_draw */
typedef struct ElevatorDoorShape {
    s16 unk_00;
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s16 dx;
    s16 dz;
    s16 range_x;
    s16 range_z;
} ElevatorDoorShape;

/* from func_800C416C */
typedef struct ShotPointRing {
    s32 unk_00;
    s32 head;
    s32 count;
    SVECTOR points[64];
} ShotPointRing;

#endif
