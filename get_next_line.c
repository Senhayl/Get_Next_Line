/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:03:50 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/27 15:43:33 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *stock_line(char *buf)
{
	size_t i;
	size_t j;
	char * line;
	
	i = 0;
	j = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = buf[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char * stock_rest(char *stash)
{
	size_t i;
	size_t j;
	char * rest;
	
	i = 0;
	
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i++] != '\n')
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	while (stash[i + j])
		j++;
	if (j == 0)
	{
		free(stash);
		return (NULL);
	}
	rest = malloc(sizeof(char) * j + 1);
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	while (stash[i])
	{
		rest[j] = stash[i];
		i++;
		j++;
	}
	rest[j] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	char *buf;
	static char *stash;
	char *line;
	size_t BUFFER_SIZE;
	size_t byte_read;
	
	BUFFER_SIZE = 3;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == 0)
			break ;
		stash = ft_strjoin(stash, buf);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	if (!stash)
	{
		free(buf);
		return (NULL);
	}
	line = stock_line(stash);
	stash = stock_rest(stash);
	free(buf);
	return(line);
}

int main(void)
{
	char *line;
	int fd;
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
}