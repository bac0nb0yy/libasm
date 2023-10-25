/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelnov <dtelnov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 17:36:23 by mdesfont          #+#    #+#             */
/*   Updated: 2023/10/25 05:46:24 by dtelnov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define PINK "\033[1;35m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

/*
** FONCTIONS TESTS
*/

void		ft_write_test(void);
void		ft_read_test(void);
void		ft_strcmp_test(void);
void		ft_strdup_test(void);
void		ft_strcpy_test(void);
void		ft_strlen_test(void);

/*
** UTILS
*/

char		*ft_strdup_c(const char *s);
char		*ft_strjoin(char *s1, char const *s2);
int			get_next_line(int fd, char **line);

/*
** FONCTIONS LIBASM
*/

ssize_t		ft_write(int fd, const void *buf, size_t count);
ssize_t		ft_read(int fd, void *buf, size_t count);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strcpy(char *dst, const char *src);

#endif
