/* ObjVars.script: an object kind's vars (Object +0x248..+0x288); the offsets are Object's, as in the asm.
   Made from ObjVars' inline view by scripts/objvars_split.py. */
#ifndef OBJVARS_SCRIPT_H
#define OBJVARS_SCRIPT_H

/* a word read from the object's script (script_read_s32) */
typedef struct ScriptVars {
    /* 0x248 */ u8 pad_248[0x30];
    /* 0x278 */ s32 value;
} ScriptVars;

#endif
