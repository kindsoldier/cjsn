/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "imalloc.h"
#include "mapper.h"

mrecord_t* new_mrecord(char* key, int type, void* valref) {
    mrecord_t *record = imalloc(sizeof(mrecord_t));
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
    mapper_t* mapper = imalloc(sizeof(mapper_t)); // todo: check NULL
    mapper->cap = 100;
    mapper->size = 0;
    mapper->records = imalloc(sizeof(mrecord_t*) * mapper->cap);
    return mapper;
}

void mapper_add(mapper_t *mapper, mrecord_t* record) {
    //if (mapper->size == mapper->cap) {
    //    size_t new_cap = mapper->cap * 2;
    //    if (realloc(mapper->records, sizeof(mrecord_t*) * new_cap) == NULL) {
    //        return; // todo: return error_t
    //    }
    //    mapper->cap = new_cap;
    //}
    mapper->records[mapper->size] = record;
    mapper->size++;
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
        if (mapper->records[i] == NULL) continue;
        if (strcmp(mapper->records[i]->key, key) == 0) {

            int n = 0;
            char* newval = NULL;
            int type = mapper->records[i]->type;
            switch (type) {
                 case TYPE_STR:
                    newval = imalloc(strlen(val));
                    strcpy(newval, val);
                    *(mapper->records[i]->cref) = newval;
                    break;
                 case TYPE_INT:
                    n = strtol(val, NULL, 10);
                    *(mapper->records[i]->iref) = n;
                    break;

            }
        }
    }
}
