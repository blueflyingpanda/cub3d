/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 12:40:30 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 18:27:30 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collision_a(t_data *img, int *a)
{
	int wa1;
	int wb1;
	int wb2;

	if (*a > 0)
	{
		wa1 = img->a - img->a % SIZE + SIZE;
		wb1 = img->b - img->b % SIZE;
		wb2 = wb1 + SIZE;
		if (walla_exists(img, wa1, wb1, wb2))
			*a = min_coord(wa1 - DIST_TO_WALL, img->a + *a) - img->a;
	}
	if (*a < 0)
	{
		wa1 = img->a - img->a % SIZE;
		wb1 = img->b - img->b % SIZE;
		wb2 = wb1 + SIZE;
		if (walla_exists(img, wa1, wb1, wb2))
			*a = max_coord(wa1 + DIST_TO_WALL, img->a + *a) - img->a;
	}
}

void	collision_b(t_data *img, int *b)
{
	int wa1;
	int wa2;
	int wb1;

	if (*b > 0)
	{
		wb1 = img->b - img->b % SIZE + SIZE;
		wa1 = img->a - img->a % SIZE;
		wa2 = wa1 + SIZE;
		if (wallb_exists(img, wb1, wa1, wa2))
			*b = min_coord(wb1 - DIST_TO_WALL, img->b + *b) - img->b;
	}
	if (*b < 0)
	{
		wb1 = img->b - img->b % SIZE;
		wa1 = img->a - img->a % SIZE;
		wa2 = wa1 + SIZE;
		if (wallb_exists(img, wb1, wa1, wa2))
			*b = max_coord(wb1 + DIST_TO_WALL, img->b + *b) - img->b;
	}
}

void	try_step(t_data *img, int *a, int *b)
{
	if (g_keyboard.a)
	{
		*a += STEP * img->sin;
		*b -= STEP * img->cos;
	}
	if (g_keyboard.s)
	{
		*a -= STEP * img->cos;
		*b -= STEP * img->sin;
	}
	if (g_keyboard.d)
	{
		*a -= STEP * img->sin;
		*b += STEP * img->cos;
	}
	if (g_keyboard.w)
	{
		*a += STEP * img->cos;
		*b += STEP * img->sin;
	}
}

void	no_sky(t_data *data, t_image *img, int ceil)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < data->height / 2)
	{
		while (x <= data->width)
			pixel_put(img, x++, y, ceil);
		x = 0;
		y++;
	}
}

void	draw_sky(t_data *data, t_image *img, int ceil)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!data->sky.img)
		no_sky(data, img, ceil);
	else
	{
		while (y < data->height / 2)
		{
			while (x <= data->width)
			{
				pixel_put(img, x, y, get_pixel(&data->sky,\
				(x * (data->sky.width * 90 / 360) / img->width +\
				(data->sky.width * data->angle / 360)) % data->sky.width,\
				y * data->sky.height / (img->height / 2)));
				x++;
			}
			x = 0;
			y++;
		}
	}
}
