#ifndef LIBASM_H
# define LIBASM_H

# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *str1, const char *str2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);

int		ft_atoi_base(char *str, char *base);

#endif