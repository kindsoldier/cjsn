
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stream.h"

stream_t* new_stream(char* origin) {
    stream_t* stream = malloc(sizeof(stream_t));
    if (stream == NULL) {
        return stream;
    }
    stream->origin = origin;
    stream->pos = 0;
    return stream;
}

void stream_init(stream_t* stream, char* origin) {
    stream->origin = origin;
    stream->pos = 0;
}

char stream_getchar(stream_t* stream) {
    if (stream->pos == strlen(stream->origin)) {
        return EOF;
    }
    return stream->origin[stream->pos++];
}

void stream_free(stream_t* stream) {
    free(stream);
}
