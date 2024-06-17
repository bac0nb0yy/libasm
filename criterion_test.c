#include <criterion.h>
#include <stdlib.h>
#include "libasm.h"

void generate_random_string(char *str, size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (length) {
        for (size_t i = 0; i < length; i++) {
            int key = rand() % (int)(sizeof(charset) - 1);
            str[i] = charset[key];
        }
        str[length] = '\0';
    }
}

void strlen_tests() {
	int actual_length = ft_strlen("danil");
	int expected_length = strlen("danil");

	cr_expect(actual_length == expected_length);
}

Test(machin, machin0) { strlen_tests(); }
