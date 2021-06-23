#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

// wrap malloc to exit if NULL is returned
void*
xmalloc(size_t size_to_alloc)
{
    void* mem = (void*)malloc(size_to_alloc);

    if (mem == NULL)
        die("unable to allocate memory");

    return mem;
}

// wrap realloc to exit if NULL is returned
void*
xrealloc(void* ptr, size_t size_to_alloc)
{
    void* mem = (void*)realloc(ptr, size_to_alloc);

    if (mem == NULL)
        die("unable to reallocate memory");

    return mem;
}

// utility function to exit with error
void
die(char* err)
{
    fprintf(stderr, "%s\n", err);
    exit(EXIT_FAILURE);
}