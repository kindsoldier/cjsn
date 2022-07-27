# cjsn

Micro project for json de/serialization in C (back to 2007).
In progress.


### Sample

```
typedef struct {
    char* ident;
    char* salt;
    char* hash;
} rpcauth_t;

typedef struct {
    char* method;
    rpcauth_t* auth;
} rpcreq_t;

rpcauth_t* new_rpcauth() {
    rpcauth_t* auth = malloc(sizeof(rpcauth_t));
    if (auth == NULL) return auth;
    auth->ident = NULL;
    auth->salt = NULL;
    auth->hash = NULL;
    return auth;
}

rpcreq_t* new_rpcreq(rpcauth_t* auth) {
    rpcreq_t* rpcreq = malloc(sizeof(rpcreq_t));
    if (rpcreq == NULL) { return rpcreq; }
    rpcreq->method = NULL;
    rpcreq->auth = auth;
    return rpcreq;
}

char* origin = "{\"method\":\"saveFile\",\"params\":{\"filePath\":\"/a/b/c/file1.bin\"},
\"auth\":{\"ident\":\"YWRtaW4=\",\"salt\":\"8X1tqNKg2Gji1y67F1UGEQ==\",
\"hash\":\"YWRtaW7xfW2o0qDYaOLXLrsXVQYRYWRtaW7jsMRCmPwcFJr79MiZb7kkJ65B5GSbk0yklZkbeFK4VQ==\"}}";


void parser() {

    rpcauth_t* rpcauth = new_rpcauth();
    rpcreq_t* rpcreq = new_rpcreq(rpcauth);

    mapper_t* mapper = new_mapper();
    mapper_add(mapper, new_mrecord("/method", TYPE_STR, &(rpcreq->method)));
    mapper_add(mapper, new_mrecord("/auth/ident", TYPE_STR, &(rpcreq->auth->ident)));
    mapper_add(mapper, new_mrecord("/auth/salt", TYPE_STR, &(rpcreq->auth->salt)));
    mapper_add(mapper, new_mrecord("/auth/hash", TYPE_STR, &(rpcreq->auth->hash)));

    stream_t* stream = new_stream(origin);
    jblock_t* jblock = new_jblock();
    jroot_t* jroot = new_jroot(jblock);
    jroot_read(jroot, stream, mapper);
    stream_free(stream);

    printf("method: %s\n", rpcreq->method);
    printf("ident: %s\n", rpcreq->auth->ident);
    printf("hash: %s\n", rpcreq->auth->hash);

}

```
#### Output

```
gmake all (in directory: /home/ziggi/cjs)
cc -c -Wall -o jblock.o jblock.c
cc -Wall -o strtool_test strtool_test.o stream.o jblock.o jkeyval.o jroot.o imalloc.o strtool.o mapper.o
cc -Wall -o parser_test parser_test.o stream.o jblock.o jkeyval.o jroot.o imalloc.o strtool.o mapper.o
./strtool_test
./parser_test
method: saveFile
ident: YWRtaW4=
hash: YWRtaW7xfW2o0qDYaOLXLrsXVQYRYWRtaW7jsMRCmPwcFJr79MiZb7kkJ65B5GSbk0yklZkbeFK4VQ==
Compilation finished successfully.


```



### C object style

Ease & simple.

#### Object
```
typedef struct {
    ...
} foo_t;
```
#### Constructor
```
foo_t* new_foo() {
    ...
}
```
#### Method
```
void foo_method(foo_t* foo, ...) {
    ...
}
```
#### Descructor

```
void foo_free(foo_t* foo) {
    ...
}

```
