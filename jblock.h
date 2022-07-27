

#ifndef JBLOCK_H_QWERTY
#define JBLOCK_H_QWERTY

#include "stream.h"

typedef struct jblock jblock_t;
typedef struct jitem jitem_t;

struct jblock {
    jitem_t** elems;
    size_t size;
    size_t limit;
};

struct jitem {
    char* key;
    char *val;
};

jblock_t* new_jblock();
void jblock_addelem(jblock_t *jblock, jitem_t* elem);
void jblock_free(jblock_t *jblock);

char jblock_read(jblock_t* jblock, stream_t* stream, int level);


#endif
