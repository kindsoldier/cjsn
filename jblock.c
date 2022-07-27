

#include <stdlib.h>
#include <stdbool.h>
#include "jcommon.h"
#include "jkeyval.h"
#include "jblock.h"

jblock_t* new_jblock() {
    jblock_t* jblock = malloc(sizeof(jblock));
    if (jblock == NULL) return jblock;
    const size_t init_limit = 16;
    jblock->elems = malloc(init_limit * sizeof(jitem_t*));
    jblock->size = 0;
    jblock->limit = init_limit;
    return jblock;
}


void jblock_addelem(jblock_t *jblock, jitem_t* elem) {
    if (jblock->size == jblock->limit) {
        jblock->limit *= 2;
        jblock->elems = realloc(jblock->elems, jblock->limit * sizeof(jitem_t*));
    }
    jblock->elems[jblock->size++] = elem;
}

void jblock_free(jblock_t *jblock) {
    free(jblock->elems);
    free(jblock);
}


char jblock_read(jblock_t* jblock, stream_t* stream, int level) {
    char l;
    while (true) {
        jkey_t* jkey = new_jkey();
        if (jkey == NULL) return EOF;

        l = jkey_read(jkey, stream);
        if (l == END_STREAM) {
            jkey_free(jkey);
            break;
        }
        if (l == BLOCK_END) {
            jkey_free(jkey);
            break;
        }
        if (l == BLOCK_CONT) {
            jkey_free(jkey);
            continue;
        }

        jval_t* jval = new_jval();
        if (jval == NULL) return EOF;

        l = jval_read(jval, stream);
        if (l == EOF) {
            jkey_free(jkey);
            jval_free(jval);
            break;
        }

        printf("%d %s:%s\n", level, jkey->string, jval->string);
        free(jkey);
        free(jval);

        if (l == BLOCK_BEG) {
            jblock_t* next_jblock = new_jblock();
            jblock_read(next_jblock, stream, level + 1);
            free(next_jblock);
        }
        if (l == BLOCK_END) {
            jkey_free(jkey);
            jval_free(jval);
            break;
        }
    }
    return l;
}
