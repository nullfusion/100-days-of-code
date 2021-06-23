#ifndef XDOC_UTILS_H
#define XDOC_UTILS_H

#include <stdio.h>
#include <stdlib.h>

void* xmalloc(size_t size_to_alloc);
void* xrealloc(void* ptr, size_t site_to_alloc);
void die(char* err);

#endif