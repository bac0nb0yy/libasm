#include <string.h>
#ifndef TEST42
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#else
#include <criterion.h>
#endif

#include "libasm.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define SMALL_STRING_MAX_LENGTH 100
#define LONG_STRING_MAX_LENGTH 100000

#define NB_STRLEN_TESTCASES 100
#define NB_STRCPY_TESTCASES 100
#define NB_STRCMP_TESTCASES 100
#define NB_WRITE_TESTCASES 100

#define FILE_PATH "/tmp/test_file.txt"

static inline char* generate_random_string(uint max_length) {
	uint generated_length = rand() % max_length;
	char* generated_string = malloc(generated_length + 1);

	if (!generated_string) {
		dprintf(STDERR_FILENO, "Allocation failed");
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < generated_length; i++) {
		generated_string[i] = (rand() % 255) + 1;
	}
	generated_string[generated_length] = '\0';

	return generated_string;
}

static void strlen_tests(uint max_length_string) {
	char* generated_string = generate_random_string(max_length_string);

	cr_expect(strlen(generated_string) == ft_strlen(generated_string));

	free(generated_string);
}

Test(mandatory, strlen_small_strings) {
	for (uint i = 0; i < NB_STRLEN_TESTCASES; ++i) {
		strlen_tests(SMALL_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strlen_long_strings) {
	for (uint i = 0; i < NB_STRLEN_TESTCASES; ++i) {
		strlen_tests(LONG_STRING_MAX_LENGTH);
	}
}

static void strcpy_random_tests(uint max_length_string) {
	char* generated_string = generate_random_string(max_length_string);

	char* dest_std = malloc(strlen(generated_string) + 1);
	char* dest_custom = malloc(strlen(generated_string) + 1);

	if (!dest_std || !dest_custom) {
		dprintf(STDERR_FILENO, "Allocation failed");
		exit(EXIT_FAILURE);
	}

	strcpy(dest_std, generated_string);
	ft_strcpy(dest_custom, generated_string);

	cr_expect(strcmp(dest_std, dest_custom) == 0);

	free(generated_string);
	free(dest_std);
	free(dest_custom);
}

static void strcpy_longer_src_tests() {
	char* longer_src = "Hellooooooooooo";
	char* dst_smaller = malloc(10);
	char* mydst_smaller = malloc(10);

	if (!dst_smaller || !mydst_smaller) {
		dprintf(STDERR_FILENO, "Allocation failed");
		exit(EXIT_FAILURE);
	}

	strcpy(dst_smaller, longer_src);
	ft_strcpy(mydst_smaller, longer_src);

	cr_expect(strcmp(dst_smaller, mydst_smaller) == 0);

	free(dst_smaller);
	free(mydst_smaller);
}

static void strcpy_smaller_src_tests() {
	char* smaller_src = "Helloooooo";
	char* dst_longer = malloc(15);
	char* mydst_longer = malloc(15);

	if (!dst_longer || !mydst_longer) {
		dprintf(STDERR_FILENO, "Allocation failed");
		exit(EXIT_FAILURE);
	}

	strcpy(dst_longer, smaller_src);
	ft_strcpy(mydst_longer, smaller_src);

	cr_expect(strcmp(dst_longer, mydst_longer) == 0);

	free(dst_longer);
	free(mydst_longer);
}

static void strcpy_empty_src_tests() {
	char* dst_emptys = malloc(15);
	char* mydst_emptys = malloc(15);

	if (!dst_emptys || !mydst_emptys) {
		dprintf(STDERR_FILENO, "Allocation failed");
		exit(EXIT_FAILURE);
	}

	strcpy(dst_emptys, "");
	ft_strcpy(mydst_emptys, "");

	cr_expect(strcmp(dst_emptys, mydst_emptys) == 0);

	free(dst_emptys);
	free(mydst_emptys);
}

Test(mandatory, strcpy_small_strings) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i) {
		strcpy_random_tests(SMALL_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strcpy_long_strings) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i) {
		strcpy_random_tests(LONG_STRING_MAX_LENGTH);
	}
}

Test(mandatory, strcpy_longer_src) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i) {
		strcpy_longer_src_tests();
	}
}

Test(mandatory, strcpy_smaller_src) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i) {
		strcpy_smaller_src_tests();
	}
}

Test(mandatory, strcpy_empty_src) {
	for (uint i = 0; i < NB_STRCPY_TESTCASES; ++i) {
		strcpy_empty_src_tests();
	}
}

static void strcmp_random_tests(uint max_length_string) {
	char* string1 = generate_random_string(max_length_string);
	char* string2 = generate_random_string(max_length_string);

	int std_result = strcmp(string1, string2);
	int custom_result = ft_strcmp(string1, string2);

	cr_expect((std_result == 0 && custom_result == 0) ||
			  (std_result < 0 && custom_result < 0) ||
			  (std_result > 0 && custom_result > 0));

	free(string1);
	free(string2);
}

static void strcmp_longer_src_tests() {
	char* longer_src1 = "Hellooooooooooo";
	char* longer_src2 = "Hellooooooooooo";

	int std_result = strcmp(longer_src1, longer_src2);
	int custom_result = ft_strcmp(longer_src1, longer_src2);

	cr_expect((std_result == 0 && custom_result == 0) ||
			  (std_result < 0 && custom_result < 0) ||
			  (std_result > 0 && custom_result > 0));
}

static void strcmp_smaller_src_tests() {
	char* smaller_src1 = "Hello";
	char* smaller_src2 = "Helloooooo";

	int std_result = strcmp(smaller_src1, smaller_src2);
	int custom_result = ft_strcmp(smaller_src1, smaller_src2);

	cr_expect((std_result == 0 && custom_result == 0) ||
			  (std_result < 0 && custom_result < 0) ||
			  (std_result > 0 && custom_result > 0));
}

static void strcmp_empty_src_tests() {
	char* empty_src1 = "";
	char* empty_src2 = "";

	int std_result = strcmp(empty_src1, empty_src2);
	int custom_result = ft_strcmp(empty_src1, empty_src2);

	cr_expect((std_result == 0 && custom_result == 0) ||
			  (std_result < 0 && custom_result < 0) ||
			  (std_result > 0 && custom_result > 0));
}

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

Test(mandatory, strcmp_longer_src) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_longer_src_tests();
	}
}

Test(mandatory, strcmp_smaller_src) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_smaller_src_tests();
	}
}

Test(mandatory, strcmp_empty_src) {
	for (uint i = 0; i < NB_STRCMP_TESTCASES; ++i) {
		strcmp_empty_src_tests();
	}
}

// static void capture_stdout(int *pipe_fd, int *saved_stdout) {
//     if (pipe(pipe_fd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }
//     *saved_stdout = dup(STDOUT_FILENO);
//     if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }
//     close(pipe_fd[1]);
// }

// static void restore_stdout(int saved_stdout) {
//     fflush(stdout);
//     if (dup2(saved_stdout, STDOUT_FILENO) == -1) {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }
//     close(saved_stdout);
// }

// static void read_from_pipe(int pipe_fd, char *buffer, size_t size) {
//     ssize_t bytes_read = read(pipe_fd, buffer, size - 1);
//     if (bytes_read == -1) {
//         perror("read");
//         exit(EXIT_FAILURE);
//     }
//     buffer[bytes_read] = '\0';
// }

// Test(ft_write, write_to_stdout) {
//     int pipe_fd[2];
//     int saved_stdout;
//     capture_stdout(pipe_fd, &saved_stdout);

//     char *generated_string = generate_random_string(256);
//     ssize_t std_ret = write(STDOUT_FILENO, generated_string,
//     strlen(generated_string)); fflush(stdout); ssize_t custom_ret =
//     ft_write(STDOUT_FILENO, generated_string, strlen(generated_string));
//     fflush(stdout);

//     char buffer[256] = {0};
//     read_from_pipe(pipe_fd[0], buffer, sizeof(buffer));

//     restore_stdout(saved_stdout);

//     cr_expect(std_ret == custom_ret);
//     cr_expect(strcmp(buffer, generated_string) == 0);

//     free(generated_string);
// }
