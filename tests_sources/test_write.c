#include "libasm.h"
#include "tests_utils.h"

#include <criterion/criterion.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_WRITE_TESTCASES 5

static void write_to_file_test(const char* text) {
	int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cr_assert(fd != -1, "Failed to open file for writing.");

	ssize_t bytes_written = ft_write(fd, text, strlen(text));
	cr_expect(bytes_written == (ssize_t)strlen(text),
			  "ft_write wrote %zd bytes but expected %zu", bytes_written,
			  strlen(text));

	close(fd);
}

static void write_to_stdout_test(const char* text) {
	ssize_t bytes_written = ft_write(STDOUT_FILENO, text, strlen(text));
	cr_expect(bytes_written == (ssize_t)strlen(text),
			  "ft_write wrote %zd bytes to stdout but expected %zu",
			  bytes_written, strlen(text));
}

static void write_with_invalid_fd_test(const char* text, int fd) {
	errno = 0;
	ssize_t bytes_written = ft_write(fd, text, strlen(text));

	cr_expect(bytes_written == -1, "ft_write should fail with invalid fd %d",
			  fd);
	cr_expect(errno == EBADF || errno == EINVAL,
			  "errno should be EBADF or EINVAL for fd %d but got %d", fd,
			  errno);
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
			  "errno should be EBADF or EACCES but got %d", errno);
}

Test(mandatory, write_to_file) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		char* generated_string = generate_random_string(LONG_STRING_MAX_LENGTH);
		cr_assert(generated_string != NULL, "Failed to generate random string");

		write_to_file_test(generated_string);
		free(generated_string);
	}
	remove("test_output.txt");
}

Test(mandatory, write_to_stdout) {
	for (uint i = 0; i < NB_WRITE_TESTCASES; ++i) {
		write_to_stdout_test("Writing to stdout.\n");
	}
}

Test(mandatory, write_empty_string) {
	write_to_file_test("");
	remove("test_output.txt");
}

Test(mandatory, write_with_negative_fd) {
	write_with_invalid_fd_test("This should not be written.", -1);
}

Test(mandatory, write_to_read_only_file) {
	write_to_read_only_file_test("Attempt to write to read-only file.");
	remove("read_only_file.txt");
}
