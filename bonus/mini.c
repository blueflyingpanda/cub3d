/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:32:46 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/04 17:33:34 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				load_img(void *mlx, char *path, t_image *image)
{
	int space;

	image->img = mlx_xpm_file_to_image(mlx, path, \
	&image->width, &image->height);
	if (image->img == NULL)
		return (-1);
	image->addr = mlx_get_data_addr(image->img, &space, &image->size_line, \
	&space);
	if (image->addr == NULL)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
		return (-1);
	}
	return (0);
}

void			pixel_put(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (color >> 24 == 0xff)
		return ;
	if (x > img->width || x < 0)
		return ;
	if (y > img->height || y < 0)
		return ;
	dst = (char *)img->addr + (y * img->size_line + x * sizeof(unsigned int));
	*(unsigned int*)dst = color;
}

unsigned int	get_pixel(t_image *img, int x, int y)
{
	return (*(unsigned int*)(img->addr + (y * img->size_line + x \
	* sizeof(unsigned int))));
}

int				my_exit(int error)
{
	if (error > 0)
	{
		errno = error;
		perror("Error\n");
	}
	if (g_viewer)
		free(g_viewer);
	if (g_spview)
		free(g_spview);
	kill(g_mpid, SIGTERM);
	system("killall afplay");
	exit(0);
	return (0);
}

int				render_frame(t_data *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(img->win, &x, &y);
	if (y < img->height && y > 0)
		mouse_rotation(x, img);
	if (!g_keyboard.a && !g_keyboard.s && !g_keyboard.d && !g_keyboard.w \
	&& !g_keyboard.left && !g_keyboard.right && !g_keyboard.redraw)
		return (0);
	g_keyboard.redraw = 0;
	movement(img);
	draw(img);
	nanosleep((const struct timespec[]){{0, 25000000}}, NULL);
	return (0);
}
