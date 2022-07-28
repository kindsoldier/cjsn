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
#include "imalloc.h"

char* origin1 = "{ \"key1\" : \"val1\",  \"key2\": \"val2\", \"key3\": 123 }";
char* origin2 = ",{x,a:{b:{c:e,m:n}},,  ,d:\"e\"}}";
char* origin3 = "{\"browsers\":{\"firefox\":{\"name\":\"Firefox\",\"pref_url\":\"about:config\",\"releases\":{\"1\":{\"release_date\":\"2004-11-09\",\"status\":\"retired\",\"engine\":\"Gecko\",\"engine_version\":\"1.7\"}}}}}";
char* origin4 = "{\"method\":\"saveFile\",\"params\":{\"filePath\":\"/a/b/c/file1.bin\"},\"auth\":{\"ident\":\"YWRtaW4=\",\"hash\":\"YWRt4VQ==\",\"salt\":\"8X1tqNKg2Gji1y67F1UGEQ==\"},\"name\":\"engine\"}";

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

/*
0 /method = saveFile
1 /filePath = /a/b/c/file1.bin
1 /auth/ident = YWRtaW4=
1 /auth/salt = 8X1tqNKg2Gji1y67F1UGEQ==
1 /auth/hash = YWRtaW7xfW2o0qDYaOLXLrsXVQYRYWRtaW7jsMRCmPwcFJr79MiZb7kkJ65B5GSbk0yklZkbeFK4VQ==
*/

typedef struct {
    char* ident;
    char* salt;
    char* hash;
} rpcauth_t;

typedef struct {
    char* method;
    rpcauth_t* auth;
    char* name;
} rpcreq_t;

rpcauth_t* new_rpcauth() {
    rpcauth_t* auth = imalloc(sizeof(rpcauth_t));
    if (auth == NULL) return auth;
    auth->ident = NULL;
    auth->salt = NULL;
    auth->hash = NULL;
    return auth;
}

rpcreq_t* new_rpcreq(rpcauth_t* auth) {
    rpcreq_t* rpcreq = imalloc(sizeof(rpcreq_t));
    if (rpcreq == NULL) { return rpcreq; }
    rpcreq->method = NULL;
    rpcreq->auth = auth;
    return rpcreq;
}

void parser() {

    rpcauth_t* rpcauth = new_rpcauth();
    rpcreq_t* rpcreq = new_rpcreq(rpcauth);

    mapper_t* mapper = new_mapper();
    mapper_add(mapper, new_mrecord("/method", TYPE_STR, &(rpcreq->method)));
    mapper_add(mapper, new_mrecord("/auth/hash", TYPE_STR, &(rpcreq->auth->hash)));
    mapper_add(mapper, new_mrecord("/auth/salt", TYPE_STR, &(rpcreq->auth->salt)));
    mapper_add(mapper, new_mrecord("/auth/ident", TYPE_STR, &(rpcreq->auth->ident)));
    mapper_add(mapper, new_mrecord("/name", TYPE_STR, &(rpcreq->name)));


    stream_t* stream = new_stream(origin4);
    jblock_t* jblock = new_jblock();
    jroot_t* jroot = new_jroot(jblock);
    jroot_read(jroot, stream, mapper);
    stream_free(stream);

    //printf("method: %s\n", rpcreq->method);
    //printf("ident: %s\n", rpcreq->auth->ident);
    //printf("salt: %s\n", rpcreq->auth->salt);
    //printf("hash: %s\n", rpcreq->auth->hash);

    mapper_print(mapper);

}

int main(int argc, char **argv) {
    parser();
    return 0;
}
