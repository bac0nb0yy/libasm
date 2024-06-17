#include <criterion.h>
#include <rand.h>

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
	int actual = ft_strlen()
	cr_assert_arr_eq(actual, expected, sizeof(expected), 
                     "Expected [%d] bytes but got [%d] bytes for string [%s]", expected_s, actual_s);
}

Test(machin, machin0) { cr_expect(ft_machin(0) == 3); }
