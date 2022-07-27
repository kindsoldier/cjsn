/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */


#ifndef ASSERT_H_QWERTY
#define ASSERT_H_QWERTY

#include <stdio.h>
#include <stdlib.h>

#define assert(expr) if (!(expr)) \
    { x__assert(__FILE__, __LINE__, (char*)__PRETTY_FUNCTION__); }

void x__assert(char* path, int line, char* func) {
    printf("%s:%d: assert error in %s\n", path, line, func);
    abort();
}

#endif
