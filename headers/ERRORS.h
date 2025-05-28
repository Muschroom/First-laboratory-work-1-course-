#pragma once

typedef enum {
    NONE = 0,
    OUT_OF_RANGE,
    MEMORY_ALLOC,
    NULL_POINTER,
    INVALID_INPUT,
    UNKNOWN
 } Error;
 
typedef struct {
    Error type;   
    char *message;
} ErrorInfo;

void set_error();
void clear_error();
void print_last_error();

static ErrorInfo last_error = {NONE};



 
#define CHECK_NULL(ptr) \
do { \
    if ((ptr) == NULL) { \
        set_error(NULL_POINTER); \
        return NULL; \
    } \
} while(0)

#define CHECK_NULL_VOID(ptr) \
do { \
    if ((ptr) == NULL) { \
        set_error(NULL_POINTER); \
        return; \
    } \
} while(0)

#define CHECK_MEM(ptr) \
do { \
    if ((ptr) == NULL) { \
        set_error(MEMORY_ALLOC); \
        return NULL; \
    } \
} while(0)

#define CHECK_INDEX(arr, ind) \
do { \
    if ((ind) < 0 || (ind) >= (arr)->data.size) { \
        set_error(OUT_OF_RANGE); \
        return NULL; \
    } \
} while(0)