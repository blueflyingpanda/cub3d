/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:21:55 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 15:05:27 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_display(t_display *play, t_view *viewer, t_data *data)
{
	play->u1 = data->width / 2 + ((viewer->wx1 == -DIST) ? RANGE : \
	(viewer->wy1 * DIST * data->width / 2) / (viewer->wx1 + DIST));
	play->u2 = data->width / 2 + ((viewer->wx2 == -DIST) ? RANGE : \
	(viewer->wy2 * DIST * data->width / 2) / (viewer->wx2 + DIST));
	play->v1t = data->height / 2 - ((viewer->wx1 == -DIST) ? RANGE : \
	(H * DIST * data->width / 2) / (viewer->wx1 + DIST));
	play->v2t = data->height / 2 - ((viewer->wx2 == -DIST) ? RANGE : \
	(H * DIST * data->width / 2) / (viewer->wx2 + DIST));
	play->v1b = data->height / 2 + ((viewer->wx1 == -DIST) ? RANGE : \
	(H * DIST * data->width / 2) / (viewer->wx1 + DIST));
	play->v2b = data->height / 2 + ((viewer->wx2 == -DIST) ? RANGE : \
	(H * DIST * data->width / 2) / (viewer->wx2 + DIST));
	if (play->u1 > play->u2)
	{
		play->tmp = play->u1;
		play->u1 = play->u2;
		play->u2 = play->tmp;
		play->tmp = play->v1t;
		play->v1t = play->v2t;
		play->v2t = play->tmp;
		play->tmp = play->v1b;
		play->v1b = play->v2b;
		play->v2b = play->tmp;
	}
}

void	sort_walls(t_view *viewer, int icopy)
{
	t_view	tmp;
	int		i;

	if (icopy == 0)
		return ;
	i = 0;
	while (icopy > 1)
	{
		while (i < icopy - 1)
		{
			if (viewer[i].see < viewer[i + 1].see)
			{
				tmp = viewer[i];
				viewer[i] = viewer[i + 1];
				viewer[i + 1] = tmp;
			}
			i++;
		}
		i = 0;
		icopy--;
	}
}

void	draw_floorceil(t_image *img, t_data *data, int ceil, int floor)
{
	int x;
	int y;

	x = 0;
	y = data->height / 2;
	draw_sky(data, img, ceil);
	while (y < data->height - 1)
	{
		while (x <= data->width)
			pixel_put(img, x++, y, floor);
		x = 0;
		y++;
	}
}

void	limit_wall(t_view *viewer)
{
	viewer->twx1 = viewer->wx1;
	viewer->twx2 = viewer->wx2;
	viewer->twy1 = viewer->wy1;
	viewer->twy2 = viewer->wy2;
	if (viewer->wx1 < SIGHT && viewer->wx2 < SIGHT)
		return ;
	if (viewer->wx1 < SIGHT)
		viewer->wy1 = viewer->wy2 - viewer->wx2 * (viewer->wy2\
		- viewer->wy1) / (viewer->wx2 - viewer->wx1) + SIGHT;
	if (viewer->wx2 < SIGHT)
		viewer->wy2 = viewer->wy2 - viewer->wx2 * (viewer->wy2\
		- viewer->wy1) / (viewer->wx2 - viewer->wx1) - SIGHT;
	viewer->wx1 = (viewer->wx1 < SIGHT) ? SIGHT : viewer->wx1;
	viewer->wx2 = (viewer->wx2 < SIGHT) ? SIGHT : viewer->wx2;
	if (viewer->wy1 > viewer->wy2)
	{
		viewer->tmp = viewer->wx1;
		viewer->wx1 = viewer->wx2;
		viewer->wx2 = viewer->tmp;
		viewer->tmp = viewer->wy1;
		viewer->wy1 = viewer->wy2;
		viewer->wy2 = viewer->tmp;
	}
}

int		check_extension(char *path)
{
	int		len;
	int		i;
	char	*str;

	str = ".cub";
	len = ft_strlen(path) - 1;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] != path[len])
			return (-1);
		i--;
		len--;
	}
	return (0);
}
