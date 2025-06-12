/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:50:02 by mlouron           #+#    #+#             */
/*   Updated: 2025/06/04 10:41:29 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*stock_line(char *buf)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
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

char	*stock_rest(char *stash)
{
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	if (stash[i++] != '\n')
		return (free(stash), NULL);
	j = 0;
	while (stash[i + j])
		j++;
	if (j == 0)
		return (free(stash), NULL);
	rest = malloc(sizeof(char) * (j + 1));
	if (!rest)
		return (free(stash), NULL);
	j = 0;
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char		*stash[1024];
	char			*buf;
	char			*line;
	ssize_t			byte_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || fd >= 1024 || (!buf))
		return (free(buf), NULL);
	byte_read = 1;
	while (byte_read > 0 && !ft_strchr(stash[fd], '\n'))
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(stash[fd]), free(buf), stash[fd] = NULL, NULL);
		if (byte_read == 0)
			break ;
		buf[byte_read] = '\0';
		stash[fd] = ft_strjoin(stash[fd], buf);
	}
	free(buf);
	if (!stash[fd] || !*stash[fd])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = stock_line(stash[fd]);
	stash[fd] = stock_rest(stash[fd]);
	return (line);
}

// int	main(void)
// {
// 	int		fd1, fd2, fd3;
// 	char	*line1;
// 	char	*line2;
// 	char	*line3;

// 	fd1 = open("test.txt", O_RDONLY);
// 	fd2 = open("test1.txt", O_RDONLY);
// 	fd3 = open("test2.txt", O_RDONLY);
// 	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
// 		return (1);
// 	line1 = get_next_line(fd1);
// 	line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
// 	while (line1 || line2 || line3)
// 	{
// 		if (line1)
// 		{
// 			printf("fd1: %s", line1);
// 			free(line1);
// 			line1 = get_next_line(fd1);
// 		}
// 		if (line2)
// 		{
// 			printf("fd2: %s", line2);
// 			free(line2);
// 			line2 = get_next_line(fd2);
// 		}
// 		if (line3)
// 		{
// 			printf("fd3: %s", line3);
// 			free(line3);
// 			line3 = get_next_line(fd3);	
// 		}
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }