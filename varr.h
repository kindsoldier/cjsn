/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#ifndef DYNARR_H_QWERTY
#define DYNARR_H_QWERTY

typedef struct {
    void **payload;
    size_t used;
    size_t size;
} varray_t;

#endif
