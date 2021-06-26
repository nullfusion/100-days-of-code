#include <stdio.h>
#include <stdlib.h>

#include "utils/utils.h"

char*
get_err_string(Error code)
{
    char* errors[] = {
        "index out of bounds",
        "failed to allocate memory",
        "null value passed"
    };

    return errors[code];
}

void
die(const char* func_name, Error code)
{
    fprintf(stderr, "error in (function %s): %s\n", func_name, get_err_string(code));
    exit(EXIT_FAILURE);
}