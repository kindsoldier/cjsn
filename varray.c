/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#include <stdlib.h>
#include "varray.h"

void varray_init(varray_t *array, size_t init_size) {
    array->payload = malloc(init_size * sizeof(void*));
    array->used = 0;
    array->size = init_size;
}

void varray_addelem(varray_t *array, void* item) {
    if (array->used == array->size) {
        array->size *= 2;
        array->payload = realloc(array->payload, array->size * sizeof(void*));
    }
    array->payload[array->used++] = item;
}

void varray_free(varray_t *array) {
    free(array->payload);
    array->payload = NULL;
    array->used = 0;
    array->size = 0;
}
