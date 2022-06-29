/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    int type;
    union {
        void* value;
    };
} map_t;


typedef struct {
    int num;
    char* msg;

} msg_t;


void* new_msg() {
    return malloc(sizeof(msg_t));
}
int main(int argc, char **argv) {

    msg_t* msg = new_msg();
    map_t elems[] = {
        { .key = "num", .type = 1, .value = &(msg->num) },
        { .key = "msg", .type = 2, .value = &(msg->msg) }
    };

    //int i = 1;
    //char* t = "qwerty";
    int i;
    for (i = 0; i < 2; i++) {
        printf("%s\n", elems[i].key);
        //*(int*)(elems[0].value) = i;
        //*(char**)(elem[1].value) = t;
    }


    //printf("msg %d %s\n", msg->num, msg->msg);
    return 0;
}
