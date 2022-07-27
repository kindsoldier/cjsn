
#ifndef JROOT_H_QWERTY
#define JROOT_H_QWERTY

#include "jblock.h"
#include "mapper.h"

typedef struct {
    jblock_t* jblock;
} jroot_t;

jroot_t* new_jroot(jblock_t* jblock);
char jroot_read(jroot_t* jroot, stream_t* stream, mapper_t* mapper);

#endif
