/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 23:58:07 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/28 01:35:01 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cross_check(int i, int len, char *map)
{
	if (map[i] != ' ' && map[i] != '1')
	{
		if ((i % len) == 0 || (i % len) == len - 1)
			return (-1);
		else
		{
			if (map[i + 1] == ' ' || map[i - 1] == ' ' ||\
			map[i + len] == ' ' || map[i - len] == ' ')
				return (-1);
		}
	}
	return (0);
}

int	fill_cord(t_map *cord, int y)
{
	cord->x = 0;
	cord->y = y;
	return (0);
}

int	assign_elem(char *line, t_data *img, t_flags *flag, t_map cord)
{
	if (line[cord.x] == 'N' || line[cord.x] == 'E' || \
	line[cord.x] == 'S' || line[cord.x] == 'W')
	{
		if (flag->p == 0)
			flag->p = 1;
		else
			return (-1);
		img->a = cord.x * 2 * H + H;
		img->b = cord.y * 2 * H + H;
		if (line[cord.x] == 'N')
			img->angle = 270;
		else if (line[cord.x] == 'E')
			img->angle = 0;
		else if (line[cord.x] == 'S')
			img->angle = 90;
		else if (line[cord.x] == 'W')
			img->angle = 180;
		img->sin = sin((img->angle * M_PI) / 180);
		img->cos = cos((img->angle * M_PI) / 180);
	}
	else if (line[cord.x] != '0' && line[cord.x] != ' ')
		return (-1);
	return (0);
}

int	before_map(t_data *img, char *line, t_flags *flag)
{
	if (*line == 'R' && !flag->map)
		return (get_res(img, line, flag));
	if (*line == 'N' && !flag->map)
		return (get_north(img, line, flag));
	if (*line == 'S' && !flag->map)
		return (get_south_or_sprite(img, line, flag));
	if (*line == 'W' && !flag->map)
		return (get_west(img, line, flag));
	if (*line == 'E' && !flag->map)
		return (get_east(img, line, flag));
	if (*line == 'F' && !flag->map)
		return (get_floor(img, line, flag));
	if (*line == 'C' && !flag->map)
		return (get_ceil(img, line, flag));
	return (1);
}

int	convert_cord(t_data *img)
{
	img->walls[img->i * 4 + 0].walla1 = H * 2 * (img->obs[img->i].x + 1);
	img->walls[img->i * 4 + 0].wallb1 = H * 2 * (img->obs[img->i].y);
	img->walls[img->i * 4 + 0].walla2 = H * 2 * (img->obs[img->i].x + 1);
	img->walls[img->i * 4 + 0].wallb2 = H * 2 * (img->obs[img->i].y + 1);
	img->walls[img->i * 4 + 1].walla1 = H * 2 * (img->obs[img->i].x);
	img->walls[img->i * 4 + 1].wallb1 = H * 2 * (img->obs[img->i].y);
	img->walls[img->i * 4 + 1].walla2 = H * 2 * (img->obs[img->i].x);
	img->walls[img->i * 4 + 1].wallb2 = H * 2 * (img->obs[img->i].y + 1);
	img->walls[img->i * 4 + 2].walla1 = H * 2 * (img->obs[img->i].x);
	img->walls[img->i * 4 + 2].wallb1 = H * 2 * (img->obs[img->i].y);
	img->walls[img->i * 4 + 2].walla2 = H * 2 * (img->obs[img->i].x + 1);
	img->walls[img->i * 4 + 2].wallb2 = H * 2 * (img->obs[img->i].y);
	img->walls[img->i * 4 + 3].walla1 = H * 2 * (img->obs[img->i].x);
	img->walls[img->i * 4 + 3].wallb1 = H * 2 * (img->obs[img->i].y + 1);
	img->walls[img->i * 4 + 3].walla2 = H * 2 * (img->obs[img->i].x + 1);
	img->walls[img->i * 4 + 3].wallb2 = H * 2 * (img->obs[img->i].y + 1);
	return (0);
}
