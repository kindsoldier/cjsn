

#ifndef STREAM_H_QWERTY
#define STREAM_H_QWERTY

typedef struct {
    char* origin;
    int pos;
} stream_t;

stream_t* new_stream(char* origin);
void stream_init(stream_t* stream, char* origin);
char stream_getchar(stream_t* stream);
void stream_free(stream_t* stream);

#endif
