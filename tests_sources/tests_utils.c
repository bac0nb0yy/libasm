#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* xmalloc(size_t size) {
	void* ptr = malloc(size);
	if (!ptr) {
		dprintf(STDERR_FILENO, "Fatal: malloc(%zu) failed\n", size);
		exit(EXIT_FAILURE);
	}
	return ptr;
}

char* generate_random_string(unsigned int max_length) {
	unsigned int generated_length = rand() % max_length;
	char* generated_string = xmalloc(generated_length + 1);

	for (unsigned int i = 0; i < generated_length; i++) {
		generated_string[i] = (rand() % (126 - 32 + 1)) + 32;
	}
	generated_string[generated_length] = '\0';

	return generated_string;
}