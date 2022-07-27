/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stream.h"
#include "jblock.h"
#include "jroot.h"



char* origin1 = "{ \"key1\" : \"val1\",  \"key2\": \"val2\", \"key3\": 123 }";
char* origin2 = ",{x,a:{b:{c:e,m:n}},,  ,d:\"e\"}}";


void parser() {
    stream_t* stream = new_stream(origin1);
    jblock_t* jblock = new_jblock();
    jroot_t* jroot = new_jroot(jblock);
    jroot_read(jroot, stream);
    stream_free(stream);
}

int main(int argc, char **argv) {
    parser();
    return 0;
}
