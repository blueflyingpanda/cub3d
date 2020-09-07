/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 19:19:04 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 14:37:43 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_lifebar(t_data *img, char *file_name)
{
	img->showlifebar = 0;
	if (load_img(img->mlx, file_name, &img->lifebar))
	{
		img->lifebar = (t_image){NULL, 0, 0, NULL, 0};
		return ;
	}
}

void	drink(t_data *img)
{
	int i;

	i = 0;
	while (i < img->sp)
	{
		if (!img->it[i].invisible && sqrt(square(img->it[i].a - img->a)\
			+ square(img->it[i].b - img->b)) < DIST_TO_DRINK)
		{
			img->it[i].invisible = 1;
			system("afplay ./bonus/sound.mp3");
			if (img->it[i].sprite_type)
				img->showlifebar = (!img->showlifebar) ? 0 :\
					img->showlifebar - 1;
			else
				img->showlifebar = (img->showlifebar == MAX_HP)\
					? MAX_HP : img->showlifebar + 1;
		}
		i++;
	}
}

int		walla_exists(t_data *img, int wa, int wb1, int wb2)
{
	int i;
	int x;

	x = 0;
	i = img->i * 4;
	while (x < i)
	{
		if (img->walls[x].walla1 == wa && img->walls[x].walla2 == wa &&\
			min_coord(img->walls[x].wallb1, img->walls[x].wallb2) == wb1 &&\
			max_coord(img->walls[x].wallb1, img->walls[x].wallb2) == wb2)
			return (1);
		x++;
	}
	return (0);
}

int		wallb_exists(t_data *img, int wb, int wa1, int wa2)
{
	int i;
	int x;

	x = 0;
	i = img->i * 4;
	while (x < i)
	{
		if (img->walls[x].wallb1 == wb && img->walls[x].wallb2 == wb &&\
			min_coord(img->walls[x].walla1, img->walls[x].walla2) == wa1 &&\
			max_coord(img->walls[x].walla1, img->walls[x].walla2) == wa2)
			return (1);
		x++;
	}
	return (0);
}

void	collision(t_data *img, int *a, int *b)
{
	collision_a(img, a);
	collision_b(img, b);
}
