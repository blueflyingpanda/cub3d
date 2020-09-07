/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:21:37 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/26 16:35:33 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi(char *str)
{
	int result;
	int index;
	int count;

	result = 0;
	index = 0;
	while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n' || \
str[index] == '\v' || str[index] == '\f' || str[index] == '\r')
		index = index + 1;
	count = index;
	if (str[index] == '-' || str[index] == '+')
		index = index + 1;
	while (str[index] >= '0' && str[index] <= '9')
	{
		if (index > 19 && str[count] == '-')
			return (0);
		if (index > 19)
			return (-1);
		result = result * 10 + str[index] - '0';
		index = index + 1;
	}
	if (str[count] == '-')
		return (-result);
	else
		return (result);
}

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t index1;
	size_t index2;

	if (n == 0)
		return (0);
	index1 = 0;
	index2 = 0;
	while (s1[index1] == s2[index2] && index1 < n - 1)
	{
		if (s1[index1] == '\0')
			return (0);
		index1 = index1 + 1;
		index2 = index2 + 1;
	}
	return ((unsigned char)s1[index1] - (unsigned char)s2[index2]);
}

void	*ft_memcpy(void *dst, void *src, int n)
{
	char	*d;
	char	*s;

	if (dst == NULL && src == NULL)
		return (dst);
	d = dst;
	s = src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dst);
}

int		check_digit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		str++;
	}
	return (0);
}

int		check_string(char *st1, char *st2)
{
	int n;

	n = ft_strlen(st1);
	if (n != ft_strlen(st2))
		return (-1);
	while (n > 0)
	{
		if (*st1 != *st2)
			return (-1);
		st1++;
		st2++;
		n--;
	}
	return (0);
}
