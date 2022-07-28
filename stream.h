

#ifndef STREAM_H_QWERTY
#define STREAM_H_QWERTY

typedef struct {
    char* origin;
    int pos;
} rstream_t;

rstream_t* new_rstream(char* origin);
void rstream_init(rstream_t* rstream, char* origin);
char rstream_getchar(rstream_t* rstream);
void rstream_free(rstream_t* rstream);

#endif
