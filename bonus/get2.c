/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:54:36 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 15:21:08 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_floor(t_data *img, char *line, t_flags *flag)
{
	t_get g;

	if (flag->f == 0)
		flag->f = 1;
	else
		return (-1);
	g.info = ft_split(line, ' ');
	g.i = 0;
	while (g.info[g.i])
		g.i++;
	if (g.i != 2 || check_string(g.info[0], "F") == -1)
		return (memfree(g.info, g.i + 1));
	g.color = ft_split(g.info[1], ',');
	memfree(g.info, g.i + 1);
	g.i = 0;
	while (g.color[g.i])
		g.i++;
	if (g.i != 3 || check_digit(g.color[0]) == -1 || check_digit(g.color[1])\
	== -1 || check_digit(g.color[2]) == -1 || ft_atoi(g.color[0]) > 255 || \
	ft_atoi(g.color[1]) > 255 || ft_atoi(g.color[2]) > 255)
		return (memfree(g.color, g.i + 1));
	img->floor = create_trgb(0, ft_atoi(g.color[0]), ft_atoi(g.color[1]),\
	ft_atoi(g.color[2]));
	memfree(g.color, g.i + 1);
	return (0);
}

int	get_ceil(t_data *img, char *line, t_flags *flag)
{
	t_get g;

	if (flag->c == 0)
		flag->c = 1;
	else
		return (-1);
	g.info = ft_split(line, ' ');
	g.i = 0;
	while (g.info[g.i])
		g.i++;
	if (g.i != 2 || check_string(g.info[0], "C") == -1)
		return (memfree(g.info, g.i + 1));
	g.color = ft_split(g.info[1], ',');
	memfree(g.info, g.i + 1);
	g.i = 0;
	while (g.color[g.i])
		g.i++;
	if (g.i != 3 || check_digit(g.color[0]) == -1 || check_digit(g.color[1])\
	== -1 || check_digit(g.color[2]) == -1 || ft_atoi(g.color[0]) > 255 || \
	ft_atoi(g.color[1]) > 255 || ft_atoi(g.color[2]) > 255)
		return (memfree(g.color, g.i + 1));
	img->ceil = create_trgb(0, ft_atoi(g.color[0]), ft_atoi(g.color[1]),\
	ft_atoi(g.color[2]));
	memfree(g.color, g.i + 1);
	return (0);
}

int	get_map(t_data *img, char *line, int *y, t_flags *flag)
{
	t_map cord;

	cord = (t_map){0, *y, 0};
	flag->map = 1;
	while (line[cord.x])
	{
		if (check_symbol(img, line, &cord, flag))
			return (-1);
		cord.x++;
	}
	(*y)++;
	return (0);
}

int	get_what(t_data *img, char *line, int *y, t_flags *flag)
{
	int check;

	check = 0;
	if (!flag->map)
		flag->start_map++;
	if ((check = before_map(img, line, flag)) != 1)
		return (check);
	if ((*line == '1' || *line == ' ') && \
	flag->r && flag->f && flag->c && flag->no && flag->so && flag->we && \
	flag->ea && flag->s && flag->b && !flag->end_map)
		check = get_map(img, line, y, flag);
	else if (*line == '\0')
	{
		if (flag->map && !flag->end_map)
			flag->end_map = 1;
	}
	else
		check = -1;
	if (check == -1)
		return (-1);
	return (0);
}

int	get_map_size(char *path, int *count, int *max_len, int start_map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (start_map > 1)
	{
		get_next_line(fd, &line);
		free(line);
		start_map--;
	}
	while (get_next_line(fd, &line))
		process_line(line, count, max_len);
	process_line(line, count, max_len);
	close(fd);
	return (0);
}
