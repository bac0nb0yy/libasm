#include "libasm.h"
#include "tests_utils.h"

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#define NB_STRLEN_TESTCASES 100

static void strlen_tests(unsigned int max_length_string) {
	char* generated_string = generate_random_string(max_length_string);

	cr_expect(strlen(generated_string) == ft_strlen(generated_string),
			  "Mismatch: strlen(\"%s\") != ft_strlen(\"%s\")", generated_string,
			  generated_string);

	free(generated_string);
}

Test(mandatory, strlen_small_strings) {
	for (unsigned int i = 0; i < NB_STRLEN_TESTCASES; ++i) {
		strlen_tests(SMALL_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strlen_long_strings) {
	for (unsigned int i = 0; i < NB_STRLEN_TESTCASES; ++i) {
		strlen_tests(LONG_STRING_MAX_LENGTH);
	}
}
