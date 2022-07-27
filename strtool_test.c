/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strtool.h"
#include "assert.h"

void test_sptrim_1() {
    char* src = "   \"qwerty\"   ";
    char* res = sptrim(src);
    char* pat = "\"qwerty\"";
    assert(strcmp(res, pat) == 0);
}

void test_strtrim_1() {
    char* src = " \"qwerty\" ";
    char* res = strtrim(src);
    char* pat = "qwerty";
    assert(strcmp(res, pat) == 0);
}

void test_strtrim_2() {
    char* src = " \"qwe rty\" ";
    char* res = strtrim(src);
    char* pat = "qwe rty";
    assert(strcmp(res, pat) == 0);
}

int main(int argc, char **argv) {
    test_sptrim_1();
    test_strtrim_1();
    test_strtrim_2();
    return 0;
}
