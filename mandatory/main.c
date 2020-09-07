/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:19:08 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 18:46:04 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_keyboard	g_keyboard;
t_view		*g_viewer;
t_view		*g_spview;

void	calculate_viewer(t_view *viewer, t_data *data, t_view *spview)
{
	int			i;
	t_norme		d;

	i = 0;
	while (i < data->i * 4)
	{
		inside_calculate_viewer(data, viewer, &d, i);
		condition_calculate_viewer(data, viewer, &d, i);
		i++;
	}
	i = 0;
	while (i < data->sp)
	{
		d.dist_x = (data->it[i].a - data->a) * data->cos + (data->it[i].b -\
		data->b) * data->sin;
		if (d.dist_x == 0)
		{
			spview[i].dist2cent = -1;
			spview[i].see = -1;
		}
		else
			inside_calculate_spview(data, spview, &d, i);
		i++;
	}
}

void	draw_wall(t_image *screen, t_data *data, t_image texture, t_view viewer)
{
	t_display	play;
	t_draw		s;

	limit_wall(&viewer);
	calculate_display(&play, &viewer, data);
	assign_delta(&s, &play);
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
	int		space;
	int		index;
	t_image	screen;

	screen = new_frame(img);
	if (screen.img == NULL || screen.addr == NULL)
		return (-1);
	calculate_viewer(g_viewer, img, g_spview);
	raycaster(g_viewer, img->i * 4, 0);
	sort_walls(g_viewer, img->i * 4);
	raycaster(g_spview, img->sp, 1);
	sort_walls(g_spview, img->sp);
	space = 0;
	index = 0;
	while ((space < img->i * 4 && g_viewer[space].see >= 0) || (index < img->sp\
	&& g_spview[index].see >= 0))
		wall_or_sprite(&index, &space, img, &screen);
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
	int		check;

	g_spview = NULL;
	g_viewer = NULL;
	img.mlx = mlx_init();
	if (img.mlx == NULL)
		return (my_exit(ENOMEM));
	ft_bzero(&g_keyboard, sizeof(g_keyboard));
	check_args(argc, argv, &img);
	init_map(&img, argv[1]);
	img.win = mlx_new_window(img.mlx, img.width, img.height, "cub3d");
	if (img.win == NULL)
		return (my_exit(ENOMEM));
	check = draw(&img);
	if (check == -1)
		return (my_exit(ENOMEM));
	if (!img.save)
		init_hooks(&img);
	return (0);
}
