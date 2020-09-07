/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:18:57 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/29 14:53:54 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		movement(t_data *img)
{
	if (g_keyboard.a)
	{
		img->a += STEP * img->sin;
		img->b -= STEP * img->cos;
	}
	if (g_keyboard.s)
	{
		img->a -= STEP * img->cos;
		img->b -= STEP * img->sin;
	}
	if (g_keyboard.d)
	{
		img->a -= STEP * img->sin;
		img->b += STEP * img->cos;
	}
	if (g_keyboard.w)
	{
		img->a += STEP * img->cos;
		img->b += STEP * img->sin;
	}
	rotation(img);
	return (0);
}

void	set_keyboard_state(int keycode, int value)
{
	if (keycode == 0)
		g_keyboard.a = value;
	else if (keycode == 1)
		g_keyboard.s = value;
	else if (keycode == 2)
		g_keyboard.d = value;
	else if (keycode == 13)
		g_keyboard.w = value;
	else if (keycode == 123)
		g_keyboard.left = value;
	else if (keycode == 124)
		g_keyboard.right = value;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

int		on_key_press(int keycode, t_data *img)
{
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->win);
		my_exit(0);
	}
	set_keyboard_state(keycode, 1);
	return (0);
}

int		on_key_release(int keycode, void *ptr)
{
	set_keyboard_state(keycode, 0);
	return (0);
}

int		on_red_cross(t_data *img)
{
	mlx_destroy_window(img->mlx, img->win);
	my_exit(0);
	return (0);
}
