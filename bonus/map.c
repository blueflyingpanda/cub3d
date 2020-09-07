/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:27:40 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 12:17:14 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_holes(char *map, int len, int line_no)
{
	int	i;
	int	size;

	i = 0;
	size = line_no * len;
	while (i < len)
	{
		if (map[i] != ' ' && map[i] != '1')
			return (-1);
		i++;
	}
	while (i < size - len)
	{
		if (cross_check(i, len, map))
			return (-1);
		i++;
	}
	while (i < size)
	{
		if (map[i] != ' ' && map[i] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int	map_to_array(char *path, int start_map)
{
	int		count;
	int		max_len;
	int		check;
	char	*map;

	count = 0;
	max_len = 0;
	get_map_size(path, &count, &max_len, start_map);
	map = malloc(sizeof(char) * (count * max_len));
	if (map == NULL)
		return (-1);
	check = fill_array(map, path, max_len, start_map);
	if (check)
	{
		free(map);
		return (-1);
	}
	check = check_holes(map, max_len, count);
	free(map);
	if (check)
		return (-1);
	return (0);
}

int	parse_file(int fd, t_data *img, int *y, t_flags *flag)
{
	char	*line;

	img->i = 0;
	img->sp = 0;
	while (get_next_line(fd, &line))
	{
		if (get_what(img, line, y, flag))
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	if (get_what(img, line, y, flag))
	{
		free(line);
		close(fd);
		return (-1);
	}
	free(line);
	return (0);
}

int	parse_map(t_data *img, char *path)
{
	int		fd;
	int		y;
	t_flags	flag;

	ft_bzero(&flag, sizeof(flag));
	if (check_extension(path) == -1)
		return (-1);
	y = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (parse_file(fd, img, &y, &flag))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (flag.p == 0)
		return (-1);
	fd = map_to_array(path, flag.start_map);
	return (fd ? -1 : 0);
}

int	map_to_world(t_data *img)
{
	int icopy;

	icopy = img->i;
	img->walls = malloc(img->i * 4 * sizeof(t_wall));
	img->it = malloc(img->sp * sizeof(t_item));
	if (img->walls == NULL || img->it == NULL)
		return (-1);
	ft_bzero(img->it, img->sp * sizeof(t_item));
	img->i--;
	while (img->i >= 0)
	{
		convert_cord(img);
		img->i--;
	}
	img->i = icopy;
	icopy = img->sp - 1;
	while (icopy >= 0)
	{
		img->it[icopy].a = H * 2 * img->items[icopy].x + H;
		img->it[icopy].b = H * 2 * img->items[icopy].y + H;
		img->it[icopy].sprite_type = img->items[icopy].sprite_type;
		icopy--;
	}
	return (0);
}
