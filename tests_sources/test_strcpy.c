#include "../includes/libasm.h"
#include "../tests_includes/tests_utils.h"
#include <criterion/criterion.h>
#include <string.h>

#define NB_STRCPY_TESTCASES 100
#define SMALL_STRING_MAX_LENGTH 100
#define LONG_STRING_MAX_LENGTH 100000

static void run_strcpy_test(const char* src) {
	size_t len = strlen(src) + 1;

	char* dest_std = xmalloc(len);
	char* dest_custom = xmalloc(len);

	strcpy(dest_std, src);
	ft_strcpy(dest_custom, src);

	cr_expect_str_eq(dest_custom, dest_std,
					 "ft_strcpy output differs from strcpy");

	free(dest_std);
	free(dest_custom);
}

static void strcpy_random_tests(uint max_length_string) {
	char* generated = generate_random_string(max_length_string);
	run_strcpy_test(generated);
	free(generated);
}

static void strcpy_smaller_src_tests(void) { run_strcpy_test("Helloooooo"); }

static void strcpy_empty_src_tests(void) { run_strcpy_test(""); }

Test(mandatory, strcpy_small_strings) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i)
		strcpy_random_tests(SMALL_STRING_MAX_LENGTH);
}

Test(mandatory, strcpy_long_strings) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i)
		strcpy_random_tests(LONG_STRING_MAX_LENGTH);
}

Test(mandatory, strcpy_smaller_src) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i)
		strcpy_smaller_src_tests();
}

Test(mandatory, strcpy_empty_src) { strcpy_empty_src_tests(); }