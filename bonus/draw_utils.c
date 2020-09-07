/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 21:07:18 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 17:57:17 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inside_drawall(t_data *data, t_draw *s, t_display *play, t_view *viewer)
{
	s->uw = s->u - data->width / 2;
	s->vt = play->v2t - s->dv * (play->u2 - s->u) / s->du;
	s->vb = play->v2b + s->dv * (play->u2 - s->u) / s->du;
	s->i = s->vt;
	s->dw = SIZE * 1.0 * (s->uw * viewer->twx1 + s->uw * DIST - viewer->twy1 *\
	DIST * data->width / 2) / ((viewer->twy2 - viewer->twy1) * DIST *\
	data->width / 2 - s->uw * (viewer->twx2 - viewer->twx1));
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
		screen.addr = mlx_get_data_addr(screen.img, &space, &screen.size_line,\
			&space);
		if (screen.addr == NULL)
			return (screen);
		draw_floorceil(&screen, img, img->ceil, img->floor);
	}
	return (screen);
}

void	wall_or_sprite(t_index *id, t_data *img, t_image *screen)
{
	if (id->s >= img->sp || g_spview[id->s].see < 0)
	{
		draw_wall(screen, img, img->textures[(g_viewer[id->w].texture)\
		% 4], g_viewer[id->w]);
		id->w++;
		return ;
	}
	if (id->w >= img->i * 4 || g_viewer[id->w].see < 0)
	{
		draw_wall(screen, img, g_spview[id->s].texture ? img->item :\
			img->sprite, g_spview[id->s]);
		id->s++;
		return ;
	}
	if (g_viewer[id->w].see < g_spview[id->s].see)
		draw_wall(screen, img, g_spview[id->s].texture ? img->item :\
			img->sprite, g_spview[id->s]);
	else
		draw_wall(screen, img, img->textures[(g_viewer[id->w].texture)\
			% 4], g_viewer[id->w]);
	if (g_viewer[id->w].see < g_spview[id->s].see)
		id->s++;
	else
		id->w++;
}
