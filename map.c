/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_STR 1
#define TYPE_INT 2

typedef struct {
    char*   key;
    int     type;
    union {
        char**  cref;
        int*    iref;
    };
} record_t;

typedef struct {
    record_t **records;
    size_t size;
    size_t cap;
} maper_t;

record_t* new_record(char* key, int type, void* val) {
    record_t *record = malloc(sizeof(record_t));
    record->key = key;
    record->type = type;
    switch (type) {
         case TYPE_STR:
             record->cref = val;
             break;
         case TYPE_INT:
             record->iref = val;
             break;
    }
    return record;
}

maper_t* new_maper() {
    maper_t* maper = malloc(sizeof(maper_t));
    maper->cap = 100;
    maper->size = 0;
    maper->records = malloc(sizeof(record_t*) * maper->cap);
    return maper;
}

void maper_add(maper_t *maper, record_t* record) {
    maper->records[maper->size++] = record;
}

record_t* maper_find(maper_t* maper, char* key) {
    for (int i = 0; i < maper->size; i++) {
        if (strcmp(maper->records[i]->key, key) == 0) {
            return maper->records[i];
        }
    }
    return NULL;
}

void maper_set(maper_t* maper, char* key, char* val) {
    for (int i = 0; i < maper->size; i++) {
        if (strcmp(maper->records[i]->key, key) == 0) {
            printf("key %d %s %s\n", i, key, val);
            int n = 0;
            switch (maper->records[i]->type) {
                 case TYPE_STR:
                    *(maper->records[i]->cref) = val;
                    break;
                 case TYPE_INT:
                    n = strtol(val, NULL, 10);
                    *(maper->records[i]->iref) = n;
                    break;

            }
        }
    }
}

typedef struct {
    char* elem1;
    char* elem2;
    int elem3;
} test_t;

int main(int argc, char **argv) {

    test_t t;

    maper_t* maper = new_maper();
    maper_add(maper, new_record("key1", TYPE_STR, &(t.elem1)));
    maper_add(maper, new_record("key2", TYPE_STR, &(t.elem2)));
    maper_add(maper, new_record("key3", TYPE_INT, &(t.elem3)));

    maper_set(maper, "key1", "val1");
    maper_set(maper, "key2", "val2");
    maper_set(maper, "key3", "123");
    printf("%s %s %d\n", t.elem1, t.elem2, t.elem3);

    return 0;
}
