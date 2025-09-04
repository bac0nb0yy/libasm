#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stddef.h>

#define SMALL_STRING_MAX_LENGTH 100
#define LONG_STRING_MAX_LENGTH 100000

void* xmalloc(size_t size);
char* generate_random_string(unsigned int max_length);

#endif