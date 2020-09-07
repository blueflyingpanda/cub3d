/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:38:36 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 12:19:55 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		square(long long var)
{
	return (var * var);
}

void	inside_calculate_viewer(t_data *data, t_view *viewer, t_norme *d, int i)
{
	viewer[i].wx1 = (data->walls[i].walla1 - data->a) * data->cos +\
	(data->walls[i].wallb1 - data->b) * data->sin;
	viewer[i].wx2 = (data->walls[i].walla2 - data->a) * data->cos +\
	(data->walls[i].wallb2 - data->b) * data->sin;
	viewer[i].wy1 = (data->walls[i].wallb1 - data->b) * data->cos -\
	(data->walls[i].walla1 - data->a) * data->sin;
	viewer[i].wy2 = (data->walls[i].wallb2 - data->b) * data->cos -\
	(data->walls[i].walla2 - data->a) * data->sin;
	viewer[i].see = -1;
	viewer[i].texture = i;
	d->dist_x = ((data->walls[i].walla2 + data->walls[i].walla1) / 2 -\
	data->a) * data->cos + ((data->walls[i].wallb2 + data->walls[i].wallb1)\
	/ 2 - data->b)
	* data->sin;
}

void	condition_calculate_viewer(t_data *data, t_view *viewer, t_norme *d,\
int i)
{
	if (d->dist_x == 0)
	{
		d->dist_y = -1;
		viewer[i].dist2cent = -1;
	}
	else
	{
		d->dist_y = ((data->walls[i].wallb2 + data->walls[i].wallb1) / 2 -\
		data->b) * data->cos - ((data->walls[i].walla2 +\
		data->walls[i].walla1) / 2 - data->a) * data->sin;
		viewer[i].dist2cent = sqrt(square(d->dist_x) + square(d->dist_y));
	}
	d->l = (2 * H * data->sprite.width) / WALLPX;
}

void	inside_calculate_spview(t_data *data, t_view *spview,\
	t_norme *d, t_item *ar)
{
	d->dist_y = (ar[d->i].b - data->b) * data->cos - (ar[d->i].a -\
		data->a) * data->sin;
	d->delta_y = (sqrt((d->dist_x * d->dist_x * d->l * d->l) / (4 * (d->dist_x\
		* d->dist_x + d->dist_y * d->dist_y))));
	d->delta_x = (d->dist_y * d->delta_y) / d->dist_x;
	spview[d->i].wx1 = d->dist_x + d->delta_x;
	spview[d->i].wx2 = d->dist_x - d->delta_x;
	spview[d->i].wy1 = d->dist_y - d->delta_y;
	spview[d->i].wy2 = d->dist_y + d->delta_y;
	spview[d->i].see = -1;
	spview[d->i].dist2cent = sqrt(d->dist_x * d->dist_x + d->dist_y\
		* d->dist_y);
	spview[d->i].texture = ar[d->i].sprite_type;
}
