# cjsn

Micro project for json de/serialization in C (back to 2007).
In progress.


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
