#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stddef.h>

#define SMALL_STRING_MAX_LENGTH 100
#define LONG_STRING_MAX_LENGTH 100000
#define NB_STRCMP_TESTCASES 100
#define NB_WRITE_TESTCASES 100

void* xmalloc(size_t size);
char* generate_random_string(unsigned int max_length);

#endif