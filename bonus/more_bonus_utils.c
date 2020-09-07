/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_bonus_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 17:24:08 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 18:24:22 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inside_main(int argc, char **argv, t_data *img)
{
	g_spview = NULL;
	g_viewer = NULL;
	ft_bzero(&g_keyboard, sizeof(g_keyboard));
	check_args(argc, argv, img);
	load_img(img->mlx, "bonus/sky.xpm", &img->sky);
	init_map(img, argv[1]);
	load_hud(img, "bonus/hud.xpm");
	load_lifebar(img, "bonus/lifebar.xpm");
}

void	inside_draw(int *offset, int *tmp, t_data *img, t_index *id)
{
	*offset = 0;
	*tmp = img->showlifebar;
	calculate_viewer(g_viewer, img, g_spview);
	raycaster(g_viewer, img->i * 4, 0);
	sort_walls(g_viewer, img->i * 4);
	raycaster(g_spview, img->sp, 1);
	sort_walls(g_spview, img->sp);
	ft_bzero(id, sizeof(t_index));
}

int		check_symbol(t_data *img, char *line, t_map *cord, t_flags *flag)
{
	if (line[cord->x] == '1')
	{
		img->obs[img->i] = *cord;
		img->i++;
	}
	else if (line[cord->x] == '2')
	{
		img->items[img->sp] = *cord;
		img->sp++;
	}
	else if (line[cord->x] == '3')
	{
		img->items[img->sp] = *cord;
		img->items[img->sp].sprite_type = 1;
		img->sp++;
	}
	else if (assign_elem(line, img, flag, *cord))
		return (-1);
	return (0);
}
