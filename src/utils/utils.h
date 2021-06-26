#ifndef XDOC_UTILS_H
#define XDOC_UTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef enum Error Error;

enum Error {
    ERR_OUT_OF_BOUNDS,
    ERR_ALLOC_FAILED,
    ERR_NULL_VALUE
};

void die(const char* func_name, Error err);
char* get_err_string(Error code);

#endif