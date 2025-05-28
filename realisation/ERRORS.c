#include "headers/ERRORS.h"
#include <string.h>
#include <stdio.h>
const char* error_message() {
    switch (last_error.type) {
        case NONE: return "No error";
        case OUT_OF_RANGE: return "Index out of range";
        case MEMORY_ALLOC: return "Bad memory allocation";
        case NULL_POINTER: return "Null pointer";
        case INVALID_INPUT: return "Invalid input";
        default: return "Unknown error";
    }
 }
 
 void set_error(Error type) {
    last_error.type = type;
    last_error.message = error_message();
 }
 
 void clear_error() {
    last_error.type = NONE;
 }

 void print_last_error() {
    if (last_error.type != NONE) {
        fprintf(stderr, "Error: %s\n", last_error.message);
    }
}