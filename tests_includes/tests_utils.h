#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stddef.h>

void* xmalloc(size_t size);
char* generate_random_string(unsigned int max_length);

#endif