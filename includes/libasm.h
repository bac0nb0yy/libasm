#ifndef LIBASM_H
#define LIBASM_H

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_list {
	void* data;
	struct s_list* next;
} t_list;

size_t ft_strlen(const char* str);
char* ft_strcpy(char* dst, const char* src);
int ft_strcmp(const char* str1, const char* str2);
ssize_t ft_write(int fd, const void* buf, size_t count);
ssize_t ft_read(int fd, void* buf, size_t count);
char* ft_strdup(const char* s);

int ft_atoi_base(char* str, char* base);
void ft_list_push_front(t_list** begin_list, void* data);

#endif