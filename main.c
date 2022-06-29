/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* origin1 = "{ \"key1\" : value1,  \"key2\": \"value2\" }";
char* origin2 = ",{x,a:{b:{c:e,m:n}},,  ,d:\"e\"}}";

char* cmalloc(size_t bsize) {
    char* buffer = malloc(bsize);
    if (buffer != NULL) {
        memset(buffer, 0, bsize);
    }
    return buffer;
}

typedef struct {
    char* origin;
    int pos;
} stream_t;

stream_t* new_stream(char* origin) {
    stream_t* stream = malloc(sizeof(stream_t));
    if (stream == NULL) {
        return stream;
    }
    stream->origin = origin;
    stream->pos = 0;
    return stream;
}

void stream_init(stream_t* stream, char* origin) {
    stream->origin = origin;
    stream->pos = 0;
}

char stream_getchar(stream_t* stream) {
    if (stream->pos == strlen(stream->origin)) {
        return EOF;
    }
    return stream->origin[stream->pos++];
}

void stream_free(stream_t* stream) {
    free(stream);
}


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



#define END_STREAM  EOF
#define BLOCK_BEG   '{'
#define BLOCK_END   '}'
#define BLOCK_CONT  ','
#define KEYV_DELIM  ':'

#define JSON_ERR        1

typedef struct {
    char* string;
    size_t size;
} jkey_t;

jkey_t* new_jkey() {
    size_t init_size = 256;
    jkey_t* jkey = malloc(sizeof(jkey_t));
    if (jkey == NULL) return jkey;
    jkey->size = init_size;
    jkey->string = cmalloc(init_size);
    if (jkey->string == NULL) {
        free(jkey);
        jkey = NULL;
        return jkey;
    }
    return jkey;
}

char jkey_read(jkey_t* jkey, stream_t* stream) {
    size_t pos = 0;
    char c;
    while ((c = stream_getchar(stream)) != END_STREAM) {
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

typedef struct {
    char* string;
    size_t size;
} jval_t;

jval_t* new_jval() {
    size_t init_size = 256;
    jval_t* jval = malloc(sizeof(jval_t));
    if (jval == NULL) return jval;
    jval->size = init_size;
    jval->string = cmalloc(init_size);
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

char jval_read(jval_t* jval, stream_t* stream) {
    size_t pos = 0;
    char c;
    while ((c = stream_getchar(stream)) != END_STREAM) {
        if (c == BLOCK_CONT) break;
        if (c == BLOCK_END) break;
        jval->string[pos++] = c;
        if (c == BLOCK_BEG) break;
    }
    return c;
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


typedef struct {
    jblock_t* jblock;
} jroot_t;

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

void parser() {
    stream_t* stream = new_stream(origin2);
    jblock_t* jblock = new_jblock();
    jroot_t* jroot = new_jroot(jblock);
    jroot_read(jroot, stream);
    stream_free(stream);
}

int main(int argc, char **argv) {
    parser();
    return 0;
}
