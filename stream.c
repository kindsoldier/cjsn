
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stream.h"

rstream_t* new_rstream(char* origin) {
    rstream_t* rstream = malloc(sizeof(rstream_t));
    if (rstream == NULL) {
        return rstream;
    }
    rstream->origin = origin;
    rstream->pos = 0;
    return rstream;
}

void rstream_init(rstream_t* rstream, char* origin) {
    rstream->origin = origin;
    rstream->pos = 0;
}

char rstream_getchar(rstream_t* rstream) {
    if (rstream->pos == strlen(rstream->origin)) {
        return EOF;
    }
    return rstream->origin[rstream->pos++];
}

void rstream_free(rstream_t* rstream) {
    free(rstream);
}
