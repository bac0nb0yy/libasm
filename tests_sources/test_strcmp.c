#include "libasm.h"
#include "tests_utils.h"

#include <criterion/criterion.h>
#include <string.h>

static void run_strcmp_test(const char* s1, const char* s2) {
	int std_res = strcmp(s1, s2);
	int ft_res = ft_strcmp(s1, s2);

	cr_expect((std_res == 0 && ft_res == 0) || (std_res < 0 && ft_res < 0) ||
				  (std_res > 0 && ft_res > 0),
			  "Mismatch: strcmp(\"%s\", \"%s\") = %d, ft_strcmp = %d", s1, s2,
			  std_res, ft_res);
}

static void strcmp_random_tests(uint max_length_string) {
	char* s1 = generate_random_string(max_length_string);
	char* s2 = generate_random_string(max_length_string);

	run_strcmp_test(s1, s2);

	free(s1);
	free(s2);
}

static void strcmp_equal_strings_test(void) {
	const char* s = "Hellooooooooooo";
	run_strcmp_test(s, s);
}

static void strcmp_prefix_suffix_test(void) {
	const char* s1 = "Hello";
	const char* s2 = "Helloooooo";
	run_strcmp_test(s1, s2);
}

static void strcmp_empty_strings_test(void) { run_strcmp_test("", ""); }

Test(mandatory, strcmp_small_strings) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_random_tests(SMALL_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strcmp_long_strings) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_random_tests(LONG_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strcmp_equal_strings) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_equal_strings_test();
	}
}

Test(mandatory, strcmp_prefix_vs_suffix) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_prefix_suffix_test();
	}
}

Test(mandatory, strcmp_empty_strings) { strcmp_empty_strings_test(); }