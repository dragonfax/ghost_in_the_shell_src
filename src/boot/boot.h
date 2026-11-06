#ifndef BOOT_H
#define BOOT_H

/* from boot_exec_request */
typedef struct BootExecRequest {
    s32 flags;    /* 0x00: exec_by_name's flags */
    char *name;   /* 0x04: exec file name; NULL means no request */
} BootExecRequest;

/* from exec_set_program */
struct ExecProgram {
    s32 flags; /* exec_by_name's flags */
    char *name;
};

/* PsyQ libspu: SpuVoiceAttr.mask bits */
#define SPU_VOICE_VOLL (1 << 0)
#define SPU_VOICE_VOLR (1 << 1)
#define SPU_VOICE_PITCH (1 << 4)
#define SPU_VOICE_WDSA (1 << 7)
#define SPU_VOICE_LSAX (1 << 16)
#define SPU_VOICE_ADSR_ADSR1 (1 << 17)
#define SPU_VOICE_ADSR_ADSR2 (1 << 18)

/* PsyQ libspu: SpuGetAllKeysStatus values */
#define SPU_OFF 0
#define SPU_ON 1
#define SPU_OFF_ENV_ON 2
#define SPU_ON_ENV_OFF 3

#endif
