

#include <stdlib.h>
#include "jcommon.h"
#include "jroot.h"


jroot_t* new_jroot(jblock_t* jblock) {
    jroot_t* jroot = malloc(sizeof(jroot_t));
    if (jroot == NULL) return jroot;
    jroot->jblock = jblock;
    return jroot;
}

char jroot_read(jroot_t* jroot, stream_t* stream) {
    char c;
    while ((c = stream_getchar(stream)) != END_STREAM) {
        if (c == BLOCK_BEG) {
            jblock_read(jroot->jblock, stream, 0);
        }
    }
    return c;
}

