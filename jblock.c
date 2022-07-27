

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "jcommon.h"
#include "jkeyval.h"
#include "jblock.h"
#include "strtool.h"
#include "imalloc.h"
#include "mapper.h"

jblock_t* new_jblock() {
    jblock_t* jblock = malloc(sizeof(jblock));
    if (jblock == NULL) return jblock;
    const size_t init_limit = 16;
    jblock->elems = imalloc(init_limit * sizeof(jitem_t*));
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


char jblock_read(jblock_t* jblock, stream_t* stream, char* jpath, int level, mapper_t* mapper) {
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

        char* jkey_str = strtrim(jkey->string);
        char* jval_str = strtrim(jval->string);

        char* newjpath = imalloc(strlen(jpath) + strlen(jkey_str) + sizeof(char));
        sprintf(newjpath, "%s%c%s", jpath, PATH_DELIM, jkey_str);

        if (l != BLOCK_BEG) {
            //printf("l%d %s = %s\n", level, newjpath, jval_str);
            mapper_set(mapper, newjpath, jval_str);
        }
        free(jkey_str);
        free(jval_str);

        free(jkey);
        free(jval);

        if (l == BLOCK_BEG) {
            jblock_t* next_jblock = new_jblock();

            jblock_read(next_jblock, stream, newjpath, level + 1, mapper);
            free(newjpath);
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
