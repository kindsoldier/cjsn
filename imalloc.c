
#include <stdlib.h>
#include <string.h>

void* imalloc(size_t bsize) {
    char* buffer = malloc(bsize + 1);
    if (buffer != NULL) {
        memset(buffer, 0, bsize + 1);
    }
    return buffer;
}
