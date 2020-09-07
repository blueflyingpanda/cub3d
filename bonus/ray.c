/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:35:06 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 12:49:02 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		max_coord(int c1, int c2)
{
	if (c1 >= c2)
		return (c1);
	return (c2);
}

int		min_coord(int c1, int c2)
{
	if (c1 <= c2)
		return (c1);
	return (c2);
}

void	ray_init(t_ray *ray, double *angle)
{
	ray->x = RANGE * cos((*angle * M_PI) / 180);
	ray->y = RANGE * sin((*angle * M_PI) / 180);
	*angle += R_OFFSET;
}

void	formula(t_norm *n, t_view *viewer, t_ray *ray, int is_sprite)
{
	n->m = viewer[n->n].wx1 * (viewer[n->n].wy2 - viewer[n->n].wy1) -\
	viewer[n->n].wy1 * (viewer[n->n].wx2 - viewer[n->n].wx1);
	n->d = ray->x * (viewer[n->n].wy2 - viewer[n->n].wy1) - ray->y * \
	(viewer[n->n].wx2 - viewer[n->n].wx1);
	n->xo = (n->d != 0) ? 1.0 * ray->x * n->m / n->d : 0;
	n->yo = (n->d != 0) ? 1.0 * ray->y * n->m / n->d : 0;
	if (n->d && n->xo > 0 && n->xo >= min_coord(viewer[n->n].wx1,\
	viewer[n->n].wx2) && n->xo <= max_coord(viewer[n->n].wx1,\
	viewer[n->n].wx2) && n->yo >= min_coord(viewer[n->n].wy1,\
	viewer[n->n].wy2) && n->yo <= max_coord(viewer[n->n].wy1,\
	viewer[n->n].wy2))
	{
		n->distance = sqrt((long long)n->xo * n->xo + (long long)n->yo\
		* n->yo);
		if ((n->closest_dist > n->distance || n->closest_dist < 0) &&\
		!is_sprite)
		{
			n->closest_dist = n->distance;
			n->closest_wall = n->n;
		}
		if (is_sprite)
			viewer[n->n].see = viewer[n->n].dist2cent;
	}
}

void	raycaster(t_view *viewer, int icopy, int is_sprite)
{
	t_ray		ray;
	t_norm		n;

	if (icopy == 0)
		return ;
	n.i = 0;
	n.n = 0;
	n.angle = -((RAYS - 1) * R_OFFSET) / 2;
	while (n.i < RAYS)
	{
		n.closest_dist = -1;
		n.closest_wall = -1;
		ray_init(&ray, &n.angle);
		while (n.n < icopy)
		{
			formula(&n, viewer, &ray, is_sprite);
			n.n++;
		}
		if (n.closest_dist >= 0 && !is_sprite && (viewer[n.closest_wall].see >\
		n.closest_dist || viewer[n.closest_wall].see < 0))
			viewer[n.closest_wall].see = viewer[n.closest_wall].dist2cent;
		n.i++;
		n.n = 0;
	}
	return ;
}
