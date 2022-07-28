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

void test_qttrim_1() {
    char* src = " \"qwerty\" ";
    char* res = qttrim(src);
    char* pat = "qwerty";
    assert(strcmp(res, pat) == 0);
}

void test_qttrim_2() {
    char* src = " \"qwe rty\" ";
    char* res = qttrim(src);
    char* pat = "qwe rty";
    assert(strcmp(res, pat) == 0);
}


void test_csplitstr_1() {
    char* src = "/abc//def/123";
    char** strarr = NULL;
    int num = csplitstr(src, &strarr, 1024, '/');
    assert(num == 5);
    assert(strarr[0] = "");
    assert(strarr[1] = "abc");
    assert(strarr[2] = "def");
    assert(strarr[3] = "");
    assert(strarr[4] = "123");
}


int main(int argc, char **argv) {
    test_sptrim_1();
    test_qttrim_1();
    test_qttrim_2();
    test_csplitstr_1();
    return 0;
}
