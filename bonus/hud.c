/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 16:14:19 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 12:05:12 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_img(void *mlx, int width, int height, t_image *image)
{
	int space;

	image->img = mlx_new_image(mlx, width, height);
	if (!image->img)
		return (-1);
	image->addr = mlx_get_data_addr(image->img, &space, &image->size_line, \
	&space);
	if (image->addr == NULL)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
		return (-1);
	}
	image->width = width;
	image->height = height;
	return (0);
}

void	scale_img(t_image *src, t_image *dst)
{
	int		x;
	int		y;
	int		color;
	char	*pixel;

	x = 0;
	y = 0;
	while (y < dst->height)
	{
		while (x < dst->width)
		{
			color = *(unsigned int*)(src->addr + ((y * src->height)\
			/ dst->height) * src->size_line + (x * src->width) / dst->width\
				* sizeof(unsigned int));
			pixel = (char *)dst->addr + (y * dst->size_line + x\
				* sizeof(unsigned int));
			*(unsigned int*)pixel = color;
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_img(t_image *src, t_image *dst, int offset)
{
	int x;
	int y;
	int color;

	x = 0;
	y = 0;
	while (y < src->height)
	{
		while (x < src->width)
		{
			color = get_pixel(src, x, y);
			pixel_put(dst, x + offset, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	load_hud(t_data *img, char *file_name)
{
	t_image hud;

	img->showhud = 0;
	if (load_img(img->mlx, file_name, &hud))
	{
		img->hud = (t_image){NULL, 0, 0, NULL, 0};
		return ;
	}
	if (!create_img(img->mlx, img->width, img->height, &img->hud))
		scale_img(&hud, &img->hud);
	mlx_destroy_image(img->mlx, hud.img);
}

int		get_bonus(t_data *img, char *line, t_flags *flag)
{
	char	**info;
	int		i;

	info = ft_split(line, ' ');
	i = 0;
	while (info[i])
		i++;
	if (i != 2 || check_string(info[0], "B") == -1)
		return (memfree(info, i + 1));
	if (load_img(img->mlx, info[1], &img->item))
		return (memfree(info, i + 1));
	memfree(info, i + 1);
	flag->b = 1;
	return (0);
}
