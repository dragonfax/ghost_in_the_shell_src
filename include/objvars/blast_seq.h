/* ObjVars.blast_seq: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_BLAST_SEQ_H
#define OBJVARS_BLAST_SEQ_H

/* blast sequence with a stage-end option (blast_seq_update, s04/s05/s10) */
typedef struct BlastSeqVars {
    /* 0x248 */ s32 fx_index; /* effect passed to the final blast */
    /* 0x24C */ s32 state;
    /* 0x250 */ s32 timer;
    /* 0x254 */ s32 ends_stage; /* nonzero: set_stage_end(2) when done */
    /* 0x258 */ s32 slot;       /* copy slot, released when done */
} BlastSeqVars;

#endif
