
#ifndef JROOT_H_QWERTY
#define JROOT_H_QWERTY

#include "jblock.h"

typedef struct {
    jblock_t* jblock;
} jroot_t;

jroot_t* new_jroot(jblock_t* jblock);
char jroot_read(jroot_t* jroot, stream_t* stream);

#endif
