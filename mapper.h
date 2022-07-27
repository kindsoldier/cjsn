
#ifndef MAPPER_H_QWERTY
#define MAPPER_H_QWERTY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_STR    11
#define TYPE_INT    12
#define TYPE_FLOAT  13
#define TYPE_BOOL   14


typedef struct {
    char*   key;
    int     type;
    union {
        char**  cref;
        int*    iref;
    };
} mrecord_t;

typedef struct {
    mrecord_t **records;
    size_t size;
    size_t cap;
} mapper_t;

mrecord_t* new_mrecord(char* key, int type, void* val);
mapper_t* new_mapper();
void mapper_add(mapper_t *mapper, mrecord_t* record);
mrecord_t* mapper_find(mapper_t* mapper, char* key);
void mapper_set(mapper_t* mapper, char* key, char* val);

#endif