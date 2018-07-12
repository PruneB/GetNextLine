/*
** EPITECH PROJECT, 2018
** get_next_line.c
** File description:
** get_next_line
*/

#include "my.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*my_strcpy(char *dest, char const *src)
{
	int i = 0;

	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*my_realloc(char *str, int size)
{
	char *save;

	save = malloc(sizeof(char) * (size + 1));
	save[size] = '\0';
	save = my_strcpy(save, str);
	free(str);
	return (save);
}

char	*get_next_line(int fd)
{
	static char *buf;
	char *love;
	static int reads = -2;
	static int i = 0;
	int index = 0;
	int news = READ_SIZE;

	if (reads == -2) {
		buf = malloc(sizeof(char) * (READ_SIZE + 1));
		reads = read(fd, buf, READ_SIZE);
		buf[reads] = '\0';
	}
	love = malloc(sizeof(char) * (READ_SIZE + 1));
	love[reads] = '\0';
	while (reads != 0 && buf[i] != '\n') {
		if (buf[i] == '\0') {
			i = 0;
			reads = read(fd, buf, READ_SIZE);
			buf[reads] = '\0';
			if (reads == -1) {
				free(buf);
				free(love);
				return (NULL);
			}
			news = news + READ_SIZE;
			love = my_realloc(love, news);
			love[news] = '\0';
		} else {
			love[index] = buf[i];
			buf[i] = '\0';
			index++;
			i++;
		}
	}
	i++;
	if (reads == 0) {
		if (love[0] == '\0') {
			free(buf);
			free(love);
			return (NULL);
		}
		love[index] = '\0';
		return (love);
	}
	love[index] = '\0';
	return (love);
}
