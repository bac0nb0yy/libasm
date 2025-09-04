#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "libasm.h"
#include "tests_utils.h"

#define NB_STRDUP_TESTCASES 100

static void strdup_random_tests(uint max_length_string) {
	char* generated_string = generate_random_string(max_length_string);
	cr_assert(generated_string != NULL, "Failed to generate random string");

	char* std_dup = strdup(generated_string);
	char* ft_dup = ft_strdup(generated_string);

	cr_expect(std_dup != NULL && ft_dup != NULL,
			  "strdup or ft_strdup returned NULL");
	cr_expect(strcmp(std_dup, ft_dup) == 0,
			  "ft_strdup does not match strdup output");

	free(generated_string);
	free(std_dup);
	free(ft_dup);
}

static void strdup_empty_string_test(void) {
	char* std_dup = strdup("");
	char* ft_dup = ft_strdup("");

	cr_expect(std_dup != NULL && ft_dup != NULL,
			  "strdup or ft_strdup returned NULL on empty string");
	cr_expect(strcmp(std_dup, ft_dup) == 0,
			  "ft_strdup does not match strdup output on empty string");

	free(std_dup);
	free(ft_dup);
}

Test(mandatory, strdup_random_strings) {
	for (uint i = 0; i < NB_STRDUP_TESTCASES; ++i) {
		strdup_random_tests(LONG_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strdup_empty_string) { strdup_empty_string_test(); }
