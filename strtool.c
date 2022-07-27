
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>


char* sptrim(char* str) {
    int i = 0;
    for (i = 0; i < strlen(str); i++) {
        if (isspace(str[i])) continue;
        break;
    }
    int begin = i;

    int m = 0;
    for (m = strlen(str); m > 0 ; m--) {
        if (isspace(str[m - 1])) continue;
        break;
    }
    int end = m;

    int memsize = sizeof(char) * (end - begin) + 1;
    char* dest = malloc(sizeof(char) * memsize);
    memset(dest, '\0', memsize);

    strncpy(dest, &str[begin], end - begin);
    return dest;
}


char* strtrim(char* str) {
    int i = 0;
    for (i = 0; i < strlen(str); i++) {
        if (isspace(str[i])) continue;
        if (str[i] == '"') continue;
        break;
    }
    int begin = i;

    int m = 0;
    for (m = strlen(str); m > 0 ; m--) {
        if (isspace(str[m - 1])) continue;
        if (str[m - 1] == '"') continue;
        break;
    }
    int end = m;

    int memsize = sizeof(char) * (end - begin) + 1;
    char* dest = malloc(sizeof(char) * memsize);
    memset(dest, '\0', memsize);

    strncpy(dest, &str[begin], end - begin);
    return dest;
}
