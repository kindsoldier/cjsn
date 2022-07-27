/*
 * Copyright 2022 Oleg Borodin  <borodin@unix7.org>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "mapper.h"
#include "stream.h"
#include "jblock.h"
#include "jroot.h"



char* origin1 = "{ \"key1\" : \"val1\",  \"key2\": \"val2\", \"key3\": 123 }";
char* origin2 = ",{x,a:{b:{c:e,m:n}},,  ,d:\"e\"}}";

char* origin3 = "{\"browsers\":{\"firefox\":{\"name\":\"Firefox\",\"pref_url\":\"about:config\",\"releases\":{\"1\":{\"release_date\":\"2004-11-09\",\"status\":\"retired\",\"engine\":\"Gecko\",\"engine_version\":\"1.7\"}}}}}";

/*
 {
  "browsers": {
    "firefox": {
      "name": "Firefox",
      "pref_url": "about:config",
      "releases": {
        "1": {
          "release_date": "2004-11-09",
          "status": "retired",
          "engine": "Gecko",
          "engine_version": "1.7"
        }
      }
    }
  }
}

2 /browsers/firefox/name = Firefox
2 /browsers/firefox/pref_url = about:config
4 /browsers/firefox/releases/1/release_date = 2004-11-09
4 /browsers/firefox/releases/1/status = retired
4 /browsers/firefox/releases/1/engine = Gecko
4 /browsers/firefox/releases/1/engine_version = 1.7

*/

typedef struct {
    char* tag;
    char* val;
} jchar_t;

typedef struct {
    char* tag;
    int val;
} jint_t;

typedef struct {
    char* tag;
    bool val;
} jbool_t;


typedef struct {
    jchar_t* elem1;
    jchar_t* elem2;
    jint_t elem3;
} jtest_t;



typedef struct {
    char* elem1;
    char* elem2;
    int elem3;
} test_t;

void mapp() {
    test_t t;

    mapper_t* mapper = new_mapper();
    mapper_add(mapper, new_mrecord("key1", TYPE_STR, &(t.elem1)));
    mapper_add(mapper, new_mrecord("key2", TYPE_STR, &(t.elem2)));
    mapper_add(mapper, new_mrecord("key3", TYPE_INT, &(t.elem3)));

    mapper_set(mapper, "key1", "val1");
    mapper_set(mapper, "key2", "val2");
    mapper_set(mapper, "key3", "123");
    printf("%s %s %d\n", t.elem1, t.elem2, t.elem3);

}




void parser() {
    stream_t* stream = new_stream(origin3);
    jblock_t* jblock = new_jblock();
    jroot_t* jroot = new_jroot(jblock);
    jroot_read(jroot, stream);
    stream_free(stream);
}

int main(int argc, char **argv) {
    parser();
    return 0;
}
