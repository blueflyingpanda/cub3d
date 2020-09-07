/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:18:57 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 12:44:48 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		movement(t_data *img)
{
	int a;
	int b;

	a = 0;
	b = 0;
	try_step(img, &a, &b);
	collision(img, &a, &b);
	img->a += a;
	img->b += b;
	if (g_keyboard.a || g_keyboard.s || g_keyboard.d || g_keyboard.w)
		drink(img);
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
	if (keycode == 4)
	{
		img->showhud = (img->showhud) ? 0 : 1;
		g_keyboard.redraw = 1;
	}
	if (keycode == 27)
	{
		img->showlifebar = (!img->showlifebar) ? 0 : img->showlifebar - 1;
		g_keyboard.redraw = 1;
	}
	if (keycode == 24)
	{
		img->showlifebar = (img->showlifebar == MAX_HP) ? MAX_HP\
			: img->showlifebar + 1;
		g_keyboard.redraw = 1;
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
