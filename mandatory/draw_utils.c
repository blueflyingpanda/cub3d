/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:07:18 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/31 23:08:39 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inside_drawall(t_data *data, t_draw *s, t_display *play, t_view *viewer)
{
	s->uw = s->u - data->width / 2;
	s->dw = SIZE * 1.0 * (s->uw * viewer->twx1 + s->uw * DIST - viewer->twy1 *\
	DIST * data->width / 2) / ((viewer->twy2 - viewer->twy1) * DIST *\
	data->width / 2 - s->uw * (viewer->twx2 - viewer->twx1));
	s->vt = play->v2t - s->dv * (play->u2 - s->u) / s->du;
	s->vb = play->v2b + s->dv * (play->u2 - s->u) / s->du;
	s->i = s->vt;
}

void	draw_column(t_data *data, t_draw *s, t_image texture, t_image *screen)
{
	while (s->i <= s->vb)
	{
		if (s->i < 0)
		{
			s->i++;
			continue;
		}
		if (s->i >= data->height)
			break ;
		draw_texture(s, texture, screen);
	}
}

void	draw_texture(t_draw *s, t_image texture, t_image *screen)
{
	s->x = ((s->dw * WALLPX / 2 / H) % texture.width >= 0) ? (s->dw *\
	WALLPX / 2 / H) % texture.width : 0;
	pixel_put(screen, s->u, s->i, get_pixel(&texture, s->x, (WALLPX * (s->i\
	- s->vt) / (s->vb - s->vt)) % texture.height));
	s->i++;
}

t_image	new_frame(t_data *img)
{
	t_image screen;
	int		space;

	screen.img = mlx_new_image(img->mlx, img->width, img->height);
	if (screen.img != NULL)
	{
		screen.width = img->width;
		screen.height = img->height;
		screen.addr = mlx_get_data_addr(screen.img, &space,\
		&screen.size_line, &space);
		if (screen.addr == NULL)
			return (screen);
		draw_floorceil(&screen, img, img->ceil, img->floor);
	}
	return (screen);
}

void	wall_or_sprite(int *index, int *space, t_data *img, t_image *screen)
{
	if (*index >= img->sp || g_spview[*index].see < 0)
	{
		draw_wall(screen, img, img->textures[(g_viewer[*space].texture)\
		% 4], g_viewer[*space]);
		(*space)++;
		return ;
	}
	if (*space >= img->i * 4 || g_viewer[*space].see < 0)
	{
		draw_wall(screen, img, img->sprite, g_spview[*index]);
		(*index)++;
		return ;
	}
	if (g_viewer[*space].see < g_spview[*index].see)
	{
		draw_wall(screen, img, img->sprite, g_spview[*index]);
		(*index)++;
	}
	else
	{
		draw_wall(screen, img, img->textures[(g_viewer[*space].texture)\
		% 4], g_viewer[*space]);
		(*space)++;
	}
}
