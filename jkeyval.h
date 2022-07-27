
#ifndef JKEYVAL_H_QWERTY
#define JKEYVAL_H_QWERTY

#include "stream.h"

typedef struct {
    char* string;
    size_t size;
} jkey_t;

typedef struct {
    char* string;
    size_t size;
} jval_t;


jkey_t* new_jkey();
char jkey_read(jkey_t* jkey, stream_t* stream);
void jkey_free(jkey_t* jkey);


jval_t* new_jval();
void jval_free(jval_t* jval);
char jval_read(jval_t* jval, stream_t* stream);

#endif
