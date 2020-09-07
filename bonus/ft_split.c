/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:04:32 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/26 13:28:20 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		count_parts(char *s, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			count++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (count);
}

static	int		count_char(char *s, char c)
{
	int count;

	count = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}

int				memfree(char **ptr_arr, int x)
{
	while (x > 0)
	{
		free(ptr_arr[x - 1]);
		x--;
	}
	free(ptr_arr);
	return (-1);
}

static	char	**fill(char **ptr_arr, char *s, char c)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			ptr_arr[x] = malloc(count_char(s, c) + 1);
			if (ptr_arr[x] == NULL)
			{
				memfree(ptr_arr, x);
				return (NULL);
			}
			while (*s != c && *s != '\0')
				ptr_arr[x][y++] = *(s++);
			ptr_arr[x++][y] = '\0';
			y = 0;
		}
	}
	ptr_arr[x] = NULL;
	return (ptr_arr);
}

char			**ft_split(char *s, char c)
{
	char **ptr_arr;

	if (s == NULL)
		return (NULL);
	ptr_arr = malloc((count_parts(s, c) + 1) * sizeof(char *));
	if (ptr_arr == NULL)
		return (NULL);
	ptr_arr = fill(ptr_arr, s, c);
	if (ptr_arr == NULL)
		return (NULL);
	return (ptr_arr);
}
