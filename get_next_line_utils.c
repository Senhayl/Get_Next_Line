/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:56:13 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/27 15:37:42 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
		if ((char)c == '\0')
			return ((char *)s);
		return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while(str[i])
	{
		i++;
	}
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char *res;
	
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while(s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return(res);
}
