/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

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

mrecord_t* new_mrecord(char* key, int type, void* valref) {
    mrecord_t *record = malloc(sizeof(mrecord_t));
    record->key = key;
    record->type = type;
    switch (type) {
         case TYPE_STR:
             record->cref = valref;
             break;
         case TYPE_INT:
             record->iref = valref;
             break;
    }
    return record;
}

mapper_t* new_mapper() {
    mapper_t* mapper = malloc(sizeof(mapper_t)); // todo: check NULL
    mapper->cap = 100;
    mapper->size = 0;
    mapper->records = malloc(sizeof(mrecord_t*) * mapper->cap);
    return mapper;
}

void mapper_add(mapper_t *mapper, mrecord_t* record) {
    if (mapper->size == mapper->cap) {
        size_t new_cap = mapper->cap * 2;
        if (realloc(mapper->records, sizeof(mrecord_t*) * new_cap) == NULL) {
            return; // todo: return error_t
        }
        mapper->cap = new_cap;
    }
    mapper->records[mapper->size++] = record;
}

mrecord_t* mapper_find(mapper_t* mapper, char* key) {
    for (int i = 0; i < mapper->size; i++) {
        if (strcmp(mapper->records[i]->key, key) == 0) {
            return mapper->records[i];
        }
    }
    return NULL;
}

void mapper_set(mapper_t* mapper, char* key, char* val) {
    for (int i = 0; i < mapper->size; i++) {
        if (strcmp(mapper->records[i]->key, key) == 0) {
            printf("key %d %s %s\n", i, key, val);
            int n = 0;
            switch (mapper->records[i]->type) {
                 case TYPE_STR:
                    *(mapper->records[i]->cref) = val;
                    break;
                 case TYPE_INT:
                    n = strtol(val, NULL, 10);
                    *(mapper->records[i]->iref) = n;
                    break;

            }
        }
    }
}
