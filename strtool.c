
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


bool ischar(const char ch, const char* chset) {
    for (int i = 0; i < strlen(chset); i++) {
        if (ch == chset[i]) {
            return true;
        }
    }
    return false;
}

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


char* qttrim(char* str) {
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

int csplitstr(const char *str, char*** words, const int wmax, const char sep) {
    int wnum = 0;
    *words = malloc(sizeof(char*) * wmax);
    for (int i = 0; i < wmax; i++) { (*words)[i] = NULL; }

    int wpos = 0;
    for (int i = 0; i <= strlen(str); i++) {
        if (str[i] == sep || i == strlen(str)) {
            (*words)[wnum] = malloc(wpos + 1);
            memset((*words)[wnum], '\0', wpos + 1);
            int wbegin = i - wpos;
            strncpy((*words)[wnum], &str[wbegin], wpos);
            wnum++;
            wpos = 0;
            if (wnum > wmax) break;
            continue;
        }
        wpos++;
    }
    return wnum;
}
