/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#include "imalloc.h"
#include "mapper.h"
#include "strtool.h"

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
         case TYPE_FLOAT:
             record->fref = valref;
             break;
         case TYPE_BOOL:
             record->bref = valref;
             break;
    }
    return record;
}

void mrecord_free(mrecord_t* record) {
    if (record != NULL) {
        if (record->key != NULL) free(record->key);
        if (record->cref != NULL) free(record->cref);
        free(record);
    }
}

int mrecord_level(mrecord_t* record) {
    int level = -1;
    if (record != NULL) {

    }
    return level;
}

mapper_t* new_mapper() {
    mapper_t* mapper = imalloc(sizeof(mapper_t)); // todo: check NULL
    mapper->cap = 100;
    mapper->size = 0;
    mapper->records = imalloc(sizeof(mrecord_t*) * mapper->cap);
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

            int     n = 0;
            double  f = 0;
            char*   s = NULL;
            int type = mapper->records[i]->type;
            switch (type) {
                case TYPE_STR:
                    s = imalloc(strlen(val));
                    strcpy(s, val);
                    *(mapper->records[i]->cref) = s;
                    break;
                case TYPE_INT:
                    n = strtol(val, NULL, 10);
                    *(mapper->records[i]->iref) = n;
                    break;
                case TYPE_FLOAT:
                    f = strtod(val, NULL);
                    *(mapper->records[i]->fref) = f;
                    break;
                case TYPE_BOOL:
                    for (int n = 0; n < strlen(val); n++) {
                        tolower(val[n]);
                    }
                    if (strcmp(val, "true") == 0) {
                        *(mapper->records[i]->bref) = true;
                    }
                    break;
            }
        }
    }
}

void print_indent(int len) {
    for (int i = 0; i < len; i++) {
        printf("    ");
    }
}

void record_print(char* key, mrecord_t* record) {
    char* boolstr = "false";
    switch (record->type) {
        case TYPE_STR:
            if (*record->cref != NULL) {
                printf("\"%s\":\"%s\"", key, *record->cref);
            }
            break;
        case TYPE_INT:
            printf("\"%s\":%d", key, *record->iref);
            break;
        case TYPE_FLOAT:
            printf("\"%s\":%lf", key, *record->fref);
            break;
        case TYPE_BOOL:
            if (*record->bref == true) {
                boolstr = "true";
            }
            printf("\"%s\":%s", key, boolstr);
            break;
    }
}

void mapper_print(mapper_t* mapper) {
    int depth = 0;
    int prevdepth = 0;
    printf("\n{\n");
    for (int i = 0; i < mapper->size; i++) {
        mrecord_t* record = mapper->records[i];
        char** keyarr = NULL;

        depth = csplitstr(record->key, &keyarr, 1024, '/') - 1;

        if (depth < prevdepth) {
            for (int n = 0; n < (prevdepth - depth); n++) {
                printf("\n");
                print_indent(depth);
                printf("},\n");
            }
            print_indent(depth);
            record_print(keyarr[depth], record);
            prevdepth = depth;
            continue;
        }
        if (depth > prevdepth && prevdepth == 0) {
            for (int n = 1; n < (depth - prevdepth); n++) {
                printf("\n");
                print_indent(depth);
                printf("\"%s\":{\n", keyarr[prevdepth + n]);
            }
            print_indent(depth);
            record_print(keyarr[depth], record);
            prevdepth = depth;
            continue;
        }

        if (depth > prevdepth && prevdepth > 0) {
            for (int n = 0; n < (depth - prevdepth); n++) {
                printf(",\n");
                print_indent(depth - 1);
                printf("\"%s\":{\n", keyarr[depth - 1]);
            }
            print_indent(depth);
            record_print(keyarr[depth], record);
            prevdepth = depth;
            continue;
        }
        if (depth == prevdepth) {
            printf(",\n");
            print_indent(depth);
            record_print(keyarr[depth], record);
            prevdepth = depth;
            continue;
        }
    }
    depth = 0;
    for (int n = 0; n < (prevdepth - depth); n++) {
        printf("\n");
        print_indent(prevdepth - n - 1);
        printf("}\n");
    }

}
