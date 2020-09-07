/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 23:55:15 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/28 18:17:05 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_hooks(t_data *img)
{
	mlx_hook(img->win, KEY_PRESS, KEY_PRESS_M, on_key_press, img);
	mlx_hook(img->win, KEY_RELEASE, KEY_RELEASE_M, on_key_release, NULL);
	mlx_hook(img->win, RED_CROSS, RED_CROSS_M, on_red_cross, img);
	mlx_loop_hook(img->mlx, render_frame, img);
	mlx_loop(img->mlx);
}

void	rotation(t_data *img)
{
	if (g_keyboard.left)
		img->angle = (img->angle < ROTATE) ? img->angle - ROTATE + 360 \
		: img->angle - ROTATE;
	if (g_keyboard.right)
		img->angle = (img->angle + ROTATE >= 360) ? img->angle + ROTATE - 360 \
		: img->angle + ROTATE;
	if (g_keyboard.left || g_keyboard.right)
	{
		img->sin = sin((img->angle * M_PI) / 180);
		img->cos = cos((img->angle * M_PI) / 180);
	}
}

void	check_args(int argc, char **argv, t_data *img)
{
	if (argc != 2 && argc != 3)
		my_exit(EINVAL);
	if (argc == 3)
	{
		img->save = !ft_strncmp(argv[2], "--save", ft_strlen(argv[2]));
		if (!img->save)
			my_exit(EINVAL);
	}
	else
		img->save = 0;
}

void	init_map(t_data *img, char *file_name)
{
	int check;

	check = parse_map(img, file_name);
	if (check == -1)
		my_exit(EINVAL);
	if ((g_viewer = (t_view*)malloc(sizeof(t_view) * img->i * 4)) == NULL)
		my_exit(ENOMEM);
	if ((g_spview = (t_view*)malloc(sizeof(t_view) * img->sp)) == NULL)
		my_exit(ENOMEM);
	check = map_to_world(img);
	if (check == -1)
		my_exit(ENOMEM);
}
