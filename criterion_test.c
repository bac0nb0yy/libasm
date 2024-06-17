#ifndef TEST42
# include <criterion/criterion.h>
#else
# include <criterion.h>
#endif

#include <stdlib.h>
#include <stdint.h>
#include "libasm.h"

#define NB_STRLEN_TESTCASES 100
#define MAX_LENGTH 100000

void generate_random_string(char *str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        str[i] = rand() % 256;
    }
    str[length] = '\0';
}

void strlen_tests() {
    uint generated_length = rand() % MAX_LENGTH;
    char string_generated[generated_length];
    generate_random_string(string_generated, generated_length);

    cr_expect(strlen(string_generated) == ft_strlen(string_generated));
}

Test(asserts, strlen) {
    for (uint i = 0; i < NB_STRLEN_TESTCASES; ++i) { strlen_tests(); }
}
