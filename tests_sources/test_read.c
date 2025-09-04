#include "libasm.h"
#include "tests_utils.h"

#include <criterion/criterion.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_READ_TESTCASES 2
#define BUFFER_FIXED_SIZE_READ 1024

static void read_from_file_test(bool fixed_buffer_size) {
	char filename[64];
	snprintf(filename, sizeof(filename), "test_input_%d.txt", getpid());

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cr_assert(fd != -1, "Failed to open file for writing.");

	char* expected_content = generate_random_string(
		fixed_buffer_size ? BUFFER_FIXED_SIZE_READ : LONG_STRING_MAX_LENGTH);

	cr_assert(expected_content != NULL, "Failed to generate random string");

	size_t expected_len = strlen(expected_content);

	ssize_t total_written = 0;
	while ((size_t)total_written < expected_len) {
		ssize_t written = write(fd, expected_content + total_written,
								expected_len - total_written);
		cr_assert(written > 0, "Write failed or returned zero bytes.");
		total_written += written;
	}
	close(fd);

	fd = open(filename, O_RDONLY);
	cr_assert(fd != -1, "Failed to open file for reading.");

	size_t buffer_size = fixed_buffer_size
							 ? BUFFER_FIXED_SIZE_READ
							 : (rand() % (BUFFER_FIXED_SIZE_READ - 1)) + 1;

	char* buffer = calloc(1, LONG_STRING_MAX_LENGTH + 1);
	cr_assert(buffer != NULL, "Failed to allocate buffer");

	ssize_t bytes_read = 0;
	ssize_t bytes = 0;

	while ((bytes = ft_read(fd, buffer + bytes_read, buffer_size)) > 0) {
		bytes_read += bytes;
		cr_assert(bytes_read <= (ssize_t)LONG_STRING_MAX_LENGTH,
				  "Read more bytes than buffer can hold.");
	}
	buffer[bytes_read] = '\0';

	close(fd);

	cr_expect(bytes_read == (ssize_t)expected_len,
			  "ft_read did not read the expected number of bytes.");
	cr_expect(strcmp(buffer, expected_content) == 0,
			  "Read content does not match expected content.");

	free(buffer);
	free(expected_content);

	remove(filename);
}

static void read_from_empty_file_test() {
	const char* filename = "empty_file.txt";

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cr_assert(fd != -1, "Failed to open file for writing.");
	close(fd);

	fd = open(filename, O_RDONLY);
	cr_assert(fd != -1, "Failed to open empty file for reading.");

	char* buffer = calloc(1, BUFFER_FIXED_SIZE_READ);
	cr_assert(buffer != NULL, "Failed to allocate buffer");

	ssize_t bytes_read = ft_read(fd, buffer, BUFFER_FIXED_SIZE_READ);
	close(fd);

	cr_expect(bytes_read == 0,
			  "ft_read should return 0 when reading from an empty file.");

	free(buffer);

	remove(filename);
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
	const char* filename = "write_only_file.txt";

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0222);
	cr_assert(fd != -1, "Failed to open or create write-only file.");

	char buffer[100];
	errno = 0;
	ssize_t bytes_read = ft_read(fd, buffer, sizeof(buffer));
	close(fd);

	cr_expect(bytes_read == -1,
			  "ft_read should fail when reading from a write-only file.");
	cr_expect(errno == EBADF || errno == EACCES,
			  "errno should be set to EBADF or EACCES when reading from a "
			  "write-only file.");

	remove(filename);
}

Test(mandatory, read_from_file_fixed_buffer_length) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_from_file_test(true);
	}
}

Test(mandatory, read_from_file_random_buffer_length) {
	for (uint i = 0; i < NB_READ_TESTCASES; ++i) {
		read_from_file_test(false);
	}
}

Test(mandatory, read_from_empty_file) { read_from_empty_file_test(); }
Test(mandatory, read_with_negative_fd) { read_with_negative_fd_test(); }
Test(mandatory, read_from_write_only_file) { read_from_write_only_file_test(); }
