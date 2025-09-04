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
#define NB_READ_TESTCASES 2
#define BUFFER_FIXED_SIZE_READ 1024

#define FILE_PATH "/tmp/test_file.txt"

static inline char* generate_random_string(uint max_length) {
	uint generated_length = rand() % max_length;
	char* generated_string = malloc(generated_length + 1);

	if (!generated_string) {
		dprintf(STDERR_FILENO, "Allocation failed");
		return NULL;
	}

	for (size_t i = 0; i < generated_length; i++) {
		generated_string[i] = (rand() % 255) + 1;
	}
	generated_string[generated_length] = '\0';

	return generated_string;
}

static void strlen_tests(uint max_length_string) {
	char* generated_string = generate_random_string(max_length_string);

	if (!generated_string) {
		exit(EXIT_FAILURE);
	}

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

	if (!generated_string) {
		exit(EXIT_FAILURE);
	}

	char* dest_std = malloc(strlen(generated_string) + 1);
	char* dest_custom = malloc(strlen(generated_string) + 1);

	if (!dest_std || !dest_custom) {
		free(dest_std);
		free(dest_custom);
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

static void strcpy_smaller_src_tests() {
	char* smaller_src = "Helloooooo";
	char* dst_longer = malloc(15);
	char* mydst_longer = malloc(15);

	if (!dst_longer || !mydst_longer) {
		free(dst_longer);
		free(mydst_longer);
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
		free(dst_emptys);
		free(mydst_emptys);
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

	if (!string1 || !string2) {
		free(string1);
		free(string2);
		exit(EXIT_FAILURE);
	}

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

static void write_to_file_test(const char* text) {
	int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cr_assert(fd != -1, "Failed to open file for writing.");

	ssize_t bytes_written = ft_write(fd, text, strlen(text));
	cr_expect(bytes_written == (ssize_t)strlen(text),
			  "ft_write did not write the expected number of bytes.");

	close(fd);
}

static void write_to_stdout_test(const char* text) {
	ssize_t bytes_written = ft_write(STDOUT_FILENO, text, strlen(text));
	cr_expect(bytes_written == (ssize_t)strlen(text),
			  "ft_write did not write the expected number of bytes to stdout.");
}

static void write_with_negative_fd_test(const char* text) {
	errno = 0;
	ssize_t bytes_written = ft_write(-1, text, strlen(text));

	cr_expect(bytes_written == -1,
			  "ft_write should fail with negative file descriptor.");
	cr_expect(errno == EBADF,
			  "errno should be set to EBADF for negative file descriptor.");
}

static void write_to_read_only_file_test(const char* text) {
	int fd = open("read_only_file.txt", O_RDONLY | O_CREAT, 0444);
	cr_assert(fd != -1, "Failed to open or create read-only file.");

	errno = 0;
	ssize_t bytes_written = ft_write(fd, text, strlen(text));
	close(fd);

	cr_expect(bytes_written == -1,
			  "ft_write should fail when writing to a read-only file.");
	cr_expect(errno == EBADF || errno == EACCES,
			  "errno should be set to EBADF or EACCES when writing to a "
			  "read-only file.");
}

Test(mandatory, write_to_file) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		char* generated_string = generate_random_string(LONG_STRING_MAX_LENGTH);

		if (!generated_string) {
			exit(EXIT_FAILURE);
		}

		write_to_file_test(generated_string);
	}
}

Test(mandatory, write_to_stdout) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		write_to_stdout_test("Writing to stdout.\n");
	}
}

Test(mandatory, write_empty_string) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		write_to_file_test("");
	}
}

Test(mandatory, write_with_negative_fd) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		write_with_negative_fd_test("This should not be written.");
	}
}

Test(mandatory, write_to_read_only_file) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		write_to_read_only_file_test("Attempt to write to read-only file.");
	}
}

static void read_from_file_test(bool fixed_buffer_size) {
	int fd = open("test_input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cr_assert(fd != -1, "Failed to open file for writing.");

	char* expected_content = generate_random_string(
		fixed_buffer_size ? BUFFER_FIXED_SIZE_READ : LONG_STRING_MAX_LENGTH);

	if (!expected_content) {
		close(fd);
		exit(EXIT_FAILURE);
	}

	write(fd, expected_content, strlen(expected_content));
	close(fd);

	fd = open("test_input.txt", O_RDONLY);
	cr_assert(fd != -1, "Failed to open file for reading.");

	size_t buffer_size = fixed_buffer_size ? BUFFER_FIXED_SIZE_READ
										   : rand() % BUFFER_FIXED_SIZE_READ;
	char* buffer = calloc(sizeof(char), LONG_STRING_MAX_LENGTH + 1);

	if (!buffer) {
		close(fd);
		exit(EXIT_FAILURE);
	}

	ssize_t bytes_read = 0;
	ssize_t bytes = 0;
	for (;;) {
		bytes = ft_read(fd, buffer, buffer_size);
		if (bytes < 1) {
			break;
		}
		bytes_read += bytes;
	}
	close(fd);

	cr_expect(bytes_read == (ssize_t)strlen(expected_content),
			  "ft_read did not read the expected number of bytes.");
	cr_expect(strcmp(buffer, expected_content) == 0,
			  "Read content does not match expected content.");
}

static void read_from_empty_file_test() {
	int fd = open("empty_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);

	fd = open("empty_file.txt", O_RDONLY);
	cr_assert(fd != -1, "Failed to open empty file for reading.");

	char* buffer = calloc(sizeof(char), BUFFER_FIXED_SIZE_READ);

	if (!buffer) {
		close(fd);
		exit(EXIT_FAILURE);
	}

	ssize_t bytes_read = ft_read(fd, buffer, sizeof(buffer));
	close(fd);

	cr_expect(bytes_read == 0,
			  "ft_read should return 0 when reading from an empty file.");
}

static void read_with_negative_fd_test() {
	char buffer[100];
	errno = 0;
	ssize_t bytes_read = ft_read(-1, buffer, sizeof(buffer));
	cr_expect(bytes_read == -1,
			  "ft_read should fail with negative file descriptor.");
	cr_expect(errno == EBADF,
			  "errno should be set to EBADF for negative file descriptor.");
}

static void read_from_write_only_file_test() {
	char buffer[100];
	int fd = open("write_only_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0222);
	cr_assert(fd != -1, "Failed to open or create write-only file.");

	errno = 0;
	ssize_t bytes_read = ft_read(fd, buffer, sizeof(buffer));
	close(fd);

	cr_expect(bytes_read == -1,
			  "ft_read should fail when reading from a write-only file.");
	cr_expect(errno == EBADF || errno == EACCES,
			  "errno should be set to EBADF or EACCES when reading from a "
			  "write-only file.");
}

Test(mandatory, read_from_file_fixed_buffer_length) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_from_file_test(false);
	}
}

Test(mandatory, read_from_file_random_buffer_length) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_from_file_test(true);
	}
}

Test(mandatory, read_from_empy_file) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_from_empty_file_test();
	}
}

Test(mandatory, read_with_negative_fd) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_with_negative_fd_test();
	}
}

Test(mandatory, read_from_write_only_file) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_from_write_only_file_test();
	}
}
