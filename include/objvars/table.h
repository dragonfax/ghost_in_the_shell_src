/* ObjVars.table: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_TABLE_H
#define OBJVARS_TABLE_H

/* obj_spawn_table (scripts/objkinds.py) */
typedef struct TableVars {
    /* 0x248 */ s16 unk_248;
    /* 0x24A */ s16 entry_index;
    /* 0x24C */ s16 unk_24C;
    /* 0x24E */ u16 unk_24E;
    /* 0x250 */ u16 blend_amount;
    /* 0x252 */ u16 unk_252;
    /* 0x254 */ s16 unused_254; /* only ever set to a constant in the C: never read */
    /* 0x256 */ u16 unk_256;
} TableVars;

#endif
