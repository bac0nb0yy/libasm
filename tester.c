/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelnov <dtelnov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:55:31 by mdesfont          #+#    #+#             */
/*   Updated: 2024/06/14 18:49:47 by dtelnov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main() {
	printf("%s", PINK);
	printf("\n\t/*=======================*/");
	printf("\n\t/*       LIBASM 42       */");
	printf("\n\t/*         test.c        */");
	printf("\n\t/*=======================*/\n");
	printf("%s", RESET);

	printf("%s", CYAN);
	printf("\n--------------- TESTS FT_STRCMP.S ---------------\n");
	printf("%s", RESET);
	ft_strcmp_test();

	printf("%s", CYAN);
	printf("\n--------------- TESTS FT_STRCPY.S ---------------\n");
	printf("%s", RESET);
	ft_strcpy_test();

	printf("%s", CYAN);
	printf("\n--------------- TESTS FT_STRDUP.S ---------------\n");
	printf("%s", RESET);
	ft_strdup_test();

	printf("%s", CYAN);
	printf("\n--------------- TESTS FT_STRLEN.S ---------------\n");
	printf("%s", RESET);
	ft_strlen_test();

	printf("%s", CYAN);
	printf("\n--------------- TESTS FT_WRITE.S ----------------\n");
	printf("%s", RESET);
	ft_write_test();

	printf("%s", CYAN);
	printf("\n--------------- TESTS FT_READ.S -----------------\n");
	printf("%s", RESET);
	ft_read_test();

	return (0);
}

/*
** FONCTIONS TESTS
*/

void ft_read_test(void) {
	int fd;
	int ret;
	char buffer[256];

	fd = open("utils/tst_poem.txt", O_RDONLY);
	ret = read(fd, buffer, 100);
	buffer[ret] = 0;
	printf("\n\tREAD: Number of bytes: %d\n%s|\n", ret, buffer);
	close(fd);

	fd = open("utils/tst_poem.txt", O_RDONLY);
	ret = ft_read(fd, buffer, 100);
	buffer[ret] = 0;
	printf("\tFT_READ: Number of bytes: %d\n%s|\n\n", ret, buffer);
	close(fd);

	fd = open("utils/tst_poem.txt", O_RDONLY);
	ret = read(fd, buffer, 2);
	buffer[ret] = 0;
	printf("\tREAD: Number of bytes: %d\n%s|\n", ret, buffer);
	close(fd);

	fd = open("utils/tst_poem.txt", O_RDONLY);
	ret = ft_read(fd, buffer, 2);
	buffer[ret] = 0;
	printf("\tFT_READ: Number of bytes: %d\n%s|\n\n", ret, buffer);
	close(fd);

	printf("\tTest READ: negative fd:\n");
	fprintf(stderr, "read return: %ld | errno num %i = %s\n",
			read(-42, "Hello World!", 13), errno, strerror(errno));
	printf("\tTest FT_READ: negative fd:\n");
	fprintf(stderr, "ft_read return: %ld | errno num %i = %s\n\n\n",
			ft_read(-42, "Hello World!", 13), errno, strerror(errno));

	printf("\tTest READ: invalid argument:\n");
	fprintf(stderr, "read return: %ld | errno num %i = %s\n",
			read(2, "lol.txt", -7), errno, strerror(errno));
	printf("\tTest FT_READ: invalid argument:\n");
	fprintf(stderr, "ft_read return: %ld | errno num %i = %s\n\n\n",
			ft_read(2, "lol.txt", -7), errno, strerror(errno));

	printf("\tFT_READ from standard stream:\n");
	printf("Enter some characters (max 255):\n");
	ret = ft_read(1, buffer, 256);
	buffer[ret] = 0;
	printf("You wrote (+1 enter): %s\nNumber of bytes: %d\n\n", buffer, ret);

	printf("-----------------\n");
}

void ft_write_test(void) {
	int fd_write;
	int fd_read;
	char* buff;

	fd_write = open("utils/tst_write.txt", O_CREAT | O_RDWR, 0644);
	fd_read = open("utils/tst_write.txt", O_CREAT | O_RDWR, 0644);

	printf("\nTest WRITE: write something in stdout:\n");
	write(1, "\tHello world\n", 13);
	printf("Test FT_WRITE: write something in stdout:\n");
	ft_write(1, "\tHello world\n\n\n", 15);

	write(fd_write, "\tHello world from utils/tst_write.txt\n", 38);
	get_next_line(fd_read, &buff);
	printf("Test: something that was write in utils/tst_write.txt with "
		   "WRITE:\n%s\n",
		   buff);
	free(buff);
	close(fd_read);
	close(fd_write);
	remove("utils/tst_write.txt");
	fd_write = open("utils/tst_write.txt", O_CREAT | O_RDWR, 0644);
	fd_read = open("utils/tst_write.txt", O_CREAT | O_RDWR, 0644);
	ft_write(
		fd_write,
		"\tHello world from utils/tst_write.txt, a little bit different :)\n",
		66);
	get_next_line(fd_read, &buff);
	printf("Test: something that was write in utils/tst_write.txt with "
		   "FT_WRITE:\n%s\n\n\n",
		   buff);
	free(buff);
	close(fd_read);
	close(fd_write);
	printf("Test WRITE: negative fd:\n");
	fprintf(stderr, "write return: %ld | errno num %i = %s\n",
			write(-42, "Hello World!", 13), errno, strerror(errno));
	printf("Test FT_WRITE: negative fd:\n");
	fprintf(stderr, "ft_write return: %ld | errno num %i = %s\n\n\n",
			ft_write(-42, "Hello World!", 13), errno, strerror(errno));

	printf("Test WRITE: str = NULL:\n");
	fprintf(stderr, "write return: %ld | errno num %i = %s\n",
			write(1, NULL, 13), errno, strerror(errno));
	printf("Test FT_WRITE: str = NULL:\n");
	fprintf(stderr, "ft_write return: %ld | errno num %i = %s\n",
			ft_write(1, NULL, 13), errno, strerror(errno));

	remove("utils/tst_write.txt");

	printf("\n-----------------\n");
}

void ft_strcmp_test(void) {
	printf("%s", YELLOW);
	printf(
		"The strcmp() and strncmp() functions return an integer less than, equal\
		to,\
		or greater than zero if s1 (or the first n bytes thereof) is found,\
		respectively, to be less than,\
		to match, or be greater than s2.man 3 strcmp\n ");
	printf(" %s ", RESET);
	printf("\nBASIC: strcmp: %d  | ft_strcmp: %d\n", strcmp("Hello", "Hello"),
		   ft_strcmp("Hello", "Hello"));
	printf("BASIC: strcmp: %d | ft_strcmp : %d\n ",
		   strcmp(" Hello ", " Mello "), ft_strcmp(" Hello ", "Mello"));
	printf("BASIC: strcmp: %d  | ft_strcmp: %d\n", strcmp("Hello", "Cello"),
		   ft_strcmp("Hello", "Cello"));
	printf("BASIC: strcmp: %d  | ft_strcmp: %d\n\n", strcmp("abc", "ab"),
		   ft_strcmp("abc", "ab"));

	printf("EMPTY S1: strcmp:   %d | ft_strcmp: %d\n", strcmp("", "Mello"),
		   ft_strcmp("", "Mello"));
	printf("EMPTY S2: strcmp:    %d | ft_strcmp: %d\n", strcmp("Hello", ""),
		   ft_strcmp("Hello", ""));
	printf("EMPTY S1&S2: strcmp: %d | ft_strcmp: %d\n\n", strcmp("", ""),
		   ft_strcmp("", ""));

	printf("%s", YELLOW);
	printf("(below in the main (in comments), test to see if it's segfault if "
		   "NULL:)\n");
	printf("%s", RESET);

	printf("\n-----------------\n");
}

void ft_strdup_test(void) {
	char* s11 = strdup("Hello world!");
	;
	char* s12 = ft_strdup("Hello world!");
	char* s21 = strdup("");
	char* s22 = ft_strdup("");
	char* s31 = strdup(
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
		"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
		"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
		"aliquip ex ea commodo consequat. Duis aute irure dolor in "
		"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
		"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
		"culpa qui officia deserunt mollit anim id est laborum.");
	char* s32 = ft_strdup(
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
		"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
		"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
		"aliquip ex ea commodo consequat. Duis aute irure dolor in "
		"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
		"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
		"culpa qui officia deserunt mollit anim id est laborum.");

	printf("\nBASIC TEST    strdup: %s|", s11);
	printf("\nBASIC TEST ft_strdup: %s|", s12);

	printf("\n\nEMPTY TEST    strdup: %s|", s21);
	printf("\nEMPTY TEST ft_strdup: %s|", s22);

	printf("\n\nLONG TEST    strdup: %s|\n", s31);
	printf("\nLONG TEST ft_strdup: %s|\n", s32);

	printf("%s", YELLOW);
	printf("\n(below in the main (in comments), test to see if it's segfault "
		   "if NULL:)\n");
	printf("%s", RESET);

	free(s11);
	free(s12);
	free(s21);
	free(s22);
	free(s31);
	free(s32);

	printf("\n-----------------\n");
}

void ft_strcpy_test() {
	char* s = "hello hello";
	char* dst = malloc(sizeof(char) * 12);
	char* my_dst = malloc(sizeof(char) * 12);

	char* src = "Hello";
	char* dst_over = malloc(sizeof(char) * 12);
	char* my_dst_over = malloc(sizeof(char) * 12);

	char* longer_src = "Hellooooooooooo";
	char* dst_smaller = malloc(sizeof(char) * 10);
	char* mydst_smaller = malloc(sizeof(char) * 10);

	char* smaller_src = "Helloooooo";
	char* dst_longer = malloc(sizeof(char) * 15);
	char* mydst_longer = malloc(sizeof(char) * 15);

	char* dst_emptys = malloc(sizeof(char) * 15);
	char* mydst_emptys = malloc(sizeof(char) * 15);

	printf("\nBASIC TEST:    STRCPY: dst = %s|\n", strcpy(dst, s));
	printf("BASIC TEST: FT_STRCPY: dst = %s|\n", ft_strcpy(my_dst, s));

	dst_over = strcpy(dst_over, "hello hello");
	my_dst_over = ft_strcpy(my_dst_over, "hello hello");
	printf("\nOVERWRITE TEST:    STRCPY: dst = %s|\n", strcpy(dst, src));
	printf("OVERWRITE TEST: FT_STRCPY: dst = %s|\n", ft_strcpy(my_dst, src));

	printf("\nLONGER SRC TEST:    STRCPY: dst = %s|\n",
		   strcpy(dst_smaller, longer_src));
	printf("LONGER SRC TEST: FT_STRCPY: dst = %s|\n",
		   ft_strcpy(mydst_smaller, longer_src));

	printf("\nLONGER DST TEST:    STRCPY: dst = %s|\n",
		   strcpy(dst_longer, smaller_src));
	printf("LONGER DST TEST: FT_STRCPY: dst = %s|\n",
		   ft_strcpy(mydst_longer, smaller_src));

	printf("\nEMPTY SRC TEST:    STRCPY: dst = %s|\n", strcpy(dst_emptys, ""));
	printf("EMPTY SRC TEST: FT_STRCPY: dst = %s|\n\n",
		   ft_strcpy(mydst_emptys, ""));

	printf("%s", YELLOW);
	printf("\n(below in the main (in comments), test to see if it's segfault "
		   "if NULL:)\n");
	printf("%s", RESET);

	free(dst);
	free(my_dst);
	free(dst_over);
	free(my_dst_over);
	free(dst_smaller);
	free(mydst_smaller);
	free(dst_longer);
	free(mydst_longer);
	free(dst_emptys);
	free(mydst_emptys);

	printf("\n-----------------\n");
}

void ft_strlen_test() {
	char* basic = "Hello world!";
	char* empty = "";
	char* longstr =
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
		"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
		"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
		"aliquip ex ea commodo consequat. Duis aute irure dolor in "
		"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
		"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
		"culpa qui officia deserunt mollit anim id est laborum.";

	printf("\n   STRLEN: 'Hello world!' %lu\n", strlen(basic));
	printf("FT_STRLEN: 'Hello world!' %lu\n", ft_strlen(basic));
	printf("\n   STRLEN: empty %lu\n", strlen(empty));
	printf("FT_STRLEN: empty %lu\n", ft_strlen(empty));
	printf("\n   STRLEN: very long string %lu\n", strlen(longstr));
	printf("FT_STRLEN: very long string %lu\n", ft_strlen(longstr));
	printf("%s", YELLOW);
	printf("\n(below in the main (in comments), test to see if it's segfault "
		   "if NULL:)\n");
	printf("%s", RESET);
	printf("\n-----------------\n");
}

/*
** UTILS
*/

char* ft_strdup_c(const char* s) {
	char* ret;

	if (!(ret = malloc(sizeof(char) * (strlen(s) + 1))))
		return (NULL);
	strcpy(ret, s);
	return (ret);
}

char* ft_strjoin(char* s1, char const* s2) {
	size_t len_s1;
	char* tmp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = strlen(s1);
	tmp = ft_strdup_c(s1);
	free(s1);
	if (!(s1 = malloc(sizeof(char) * (len_s1 + strlen(s2) + 1))))
		return (NULL);
	strcpy(s1, tmp);
	free(tmp);
	strcpy(s1 + len_s1, s2);
	return (s1);
}

int get_next_line(int fd, char** line) {
	static char buffer[1];
	int ret;

	if (!line)
		return (-1);
	*line = ft_strdup_c("");
	while ((ret = read(fd, buffer, 1)) > 0) {
		if (buffer[0] == '\n')
			return (1);
		if ((*line = ft_strjoin(*line, buffer)) == NULL)
			return (-1);
	}
	if (ret < 0)
		return (-1);
	return (ret);
}
