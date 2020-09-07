/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:38:36 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/27 22:44:31 by lhelper          ###   ########.fr       */
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
		viewer[i].wx1 = -1;
		viewer[i].wx2 = -1;
		viewer[i].wy1 = -1;
		viewer[i].wy2 = -1;
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

void	inside_calculate_spview(t_data *data, t_view *spview, t_norme *d, int i)
{
	d->dist_y = (data->it[i].b - data->b) * data->cos - (data->it[i].a -\
		data->a) * data->sin;
	d->delta_y = (sqrt((d->dist_x * d->dist_x * d->l * d->l) / (4 * (d->dist_x\
		* d->dist_x + d->dist_y * d->dist_y))));
	d->delta_x = (d->dist_y * d->delta_y) / d->dist_x;
	spview[i].wx1 = d->dist_x + d->delta_x;
	spview[i].wx2 = d->dist_x - d->delta_x;
	spview[i].wy1 = d->dist_y - d->delta_y;
	spview[i].wy2 = d->dist_y + d->delta_y;
	spview[i].see = -1;
	spview[i].dist2cent = sqrt(d->dist_x * d->dist_x + d->dist_y * d->dist_y);
}

void	assign_delta(t_draw *s, t_display *play)
{
	s->du = play->u2 - play->u1;
	s->dv = play->v2t - play->v1t;
	s->u = play->u1;
}
