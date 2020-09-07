/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:19:08 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 17:51:18 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_keyboard	g_keyboard;
t_view		*g_viewer;
t_view		*g_spview;
pid_t		g_mpid;

void	calculate_viewer(t_view *viewer, t_data *data, t_view *spview)
{
	t_norme		d;

	d.i = 0;
	while (d.i < data->i * 4)
	{
		inside_calculate_viewer(data, viewer, &d, d.i);
		condition_calculate_viewer(data, viewer, &d, d.i);
		d.i++;
	}
	d.i = 0;
	while (d.i < data->sp)
	{
		spview[d.i].invisible = data->it[d.i].invisible;
		d.dist_x = (data->it[d.i].a - data->a) * data->cos + (data->it[d.i].b -\
		data->b) * data->sin;
		if (d.dist_x == 0)
		{
			spview[d.i].dist2cent = -1;
			spview[d.i].see = -1;
		}
		else
			inside_calculate_spview(data, spview, &d, data->it);
		d.i++;
	}
}

void	draw_wall(t_image *screen, t_data *data, t_image texture, t_view viewer)
{
	t_display	play;
	t_draw		s;

	if (viewer.invisible)
		return ;
	limit_wall(&viewer);
	calculate_display(&play, &viewer, data);
	s.du = play.u2 - play.u1;
	s.dv = play.v2t - play.v1t;
	s.u = play.u1;
	while (s.u < play.u2)
	{
		if (s.u < 0)
		{
			s.u++;
			continue;
		}
		if (s.u >= data->width)
			break ;
		inside_drawall(data, &s, &play, &viewer);
		draw_column(data, &s, texture, screen);
		s.u++;
	}
}

int		draw(t_data *img)
{
	t_index id;
	t_image	screen;
	int		tmp;
	int		offset;

	screen = new_frame(img);
	if (screen.img == NULL || screen.addr == NULL)
		return (-1);
	inside_draw(&offset, &tmp, img, &id);
	while ((id.w < img->i * 4 && g_viewer[id.w].see >= 0) || (id.s < img->sp\
	&& g_spview[id.s].see >= 0))
		wall_or_sprite(&id, img, &screen);
	if (img->hud.img && img->showhud)
		draw_img(&img->hud, &screen, offset);
	while (img->lifebar.img && tmp--)
	{
		draw_img(&img->lifebar, &screen, offset);
		offset += img->lifebar.width;
	}
	if (img->save)
		save_bmp(&screen);
	else
		mlx_put_image_to_window(img->mlx, img->win, screen.img, 0, 0);
	mlx_destroy_image(img->mlx, screen.img);
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	img;

	img.mlx = mlx_init();
	if (img.mlx == NULL)
		return (my_exit(ENOMEM));
	inside_main(argc, argv, &img);
	img.win = mlx_new_window(img.mlx, img.width, img.height, "cub3d");
	if (img.win == NULL)
		return (my_exit(ENOMEM));
	mlx_mouse_move(img.win, img.width / 2, -(img.height / 2));
	if (draw(&img))
		return (my_exit(ENOMEM));
	if (!img.save)
	{
		g_mpid = fork();
		if (!g_mpid)
		{
			while (1)
				system("afplay ./bonus/track.mp3");
			return (0);
		}
		init_hooks(&img);
	}
	return (0);
}
