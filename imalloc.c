
#include <stdlib.h>
#include <string.h>

char* imalloc(size_t bsize) {
    char* buffer = malloc(bsize);
    if (buffer != NULL) {
        memset(buffer, 0, bsize);
    }
    return buffer;
}
