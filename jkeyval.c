
#include <stdlib.h>
#include "jcommon.h"
#include "jkeyval.h"
#include "imalloc.h"

jkey_t* new_jkey() {
    size_t cap = 1024;
    jkey_t* jkey = imalloc(sizeof(jkey_t));
    if (jkey == NULL) return jkey;
    jkey->size = cap;
    jkey->string = imalloc(cap);
    if (jkey->string == NULL) {
        free(jkey);
        jkey = NULL;
        return jkey;
    }
    return jkey;
}

char jkey_read(jkey_t* jkey, rstream_t* stream) {
    size_t pos = 0;
    char c;
    while ((c = rstream_getchar(stream)) != END_STREAM) {
        if (c == KEYV_DELIM) break;
        if (c == BLOCK_END) break;
        if (c == BLOCK_CONT) break;
        jkey->string[pos++] = c;
    }
    return c;
}

void jkey_free(jkey_t* jkey) {
    if (jkey != NULL) {
        free(jkey->string);
        free(jkey);
    }
}

jval_t* new_jval() {
    size_t cap = 1024;
    jval_t* jval = imalloc(sizeof(jval_t));
    if (jval == NULL) return jval;
    jval->size = cap;
    jval->string = imalloc(cap);
    if (jval->string == NULL) {
        free(jval);
        jval = NULL;
        return jval;
    }
    return jval;
}

void jval_free(jval_t* jval) {
    if (jval != NULL) {
        free(jval->string);
        free(jval);
    }
}

char jval_read(jval_t* jval, rstream_t* stream) {
    size_t pos = 0;
    char c;
    while ((c = rstream_getchar(stream)) != END_STREAM) {
        if (c == BLOCK_CONT) break;
        if (c == BLOCK_END) break;
        jval->string[pos++] = c;
        if (c == BLOCK_BEG) break;
    }
    return c;
}
