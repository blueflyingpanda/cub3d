/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:54:11 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/29 15:13:57 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_res(t_data *img, char *line, t_flags *flag)
{
	char		**info;
	int			i;
	int			screen_width;
	int			screen_height;

	if (flag->r == 0)
		flag->r = 1;
	else
		return (-1);
	info = ft_split(line, ' ');
	i = 0;
	while (info[i])
		i++;
	if (i != 3 || check_string(info[0], "R") == -1 || check_digit(info[1])\
	== -1 || check_digit(info[2]) == -1)
		return (memfree(info, i + 1));
	mlx_get_screen_size(img->mlx, &screen_width, &screen_height);
	img->width = (ft_atoi(info[1]) > screen_width) ? screen_width :\
	ft_atoi(info[1]);
	img->height = (ft_atoi(info[2]) > screen_height) ? screen_height :\
	ft_atoi(info[2]);
	memfree(info, i + 1);
	return (0);
}

int	get_north(t_data *img, char *line, t_flags *flag)
{
	char	**info;
	int		i;

	if (flag->no == 0)
		flag->no = 1;
	else
		return (-1);
	info = ft_split(line, ' ');
	i = 0;
	while (info[i])
		i++;
	if (i != 2 || check_string(info[0], "NO") == -1)
		return (memfree(info, i + 1));
	if (load_img(img->mlx, info[1], &img->textures[3]))
		return (memfree(info, i + 1));
	memfree(info, i + 1);
	return (0);
}

int	get_south_or_sprite(t_data *img, char *line, t_flags *flag)
{
	char	**info;
	int		i;
	int		check;

	if (flag->s == 1 && flag->so == 1)
		return (-1);
	info = ft_split(line, ' ');
	i = 0;
	while (info[i])
		i++;
	if (flag->so == 0 && i == 2 && (check_string(info[0], "SO") != -1))
	{
		flag->so = 1;
		check = load_img(img->mlx, info[1], &img->textures[2]);
	}
	else if (flag->s == 0 && i == 2 && (check_string(info[0], "S") != -1))
	{
		flag->s = 1;
		check = load_img(img->mlx, info[1], &img->sprite);
	}
	else
		return (memfree(info, i + 1));
	memfree(info, i + 1);
	return (check);
}

int	get_west(t_data *img, char *line, t_flags *flag)
{
	char	**info;
	int		i;

	if (flag->we == 0)
		flag->we = 1;
	else
		return (-1);
	info = ft_split(line, ' ');
	i = 0;
	while (info[i])
		i++;
	if (i != 2 || check_string(info[0], "WE") == -1)
		return (memfree(info, i + 1));
	if (load_img(img->mlx, info[1], &img->textures[0]))
		return (memfree(info, i + 1));
	memfree(info, i + 1);
	return (0);
}

int	get_east(t_data *img, char *line, t_flags *flag)
{
	char	**info;
	int		i;

	if (flag->ea == 0)
		flag->ea = 1;
	else
		return (-1);
	info = ft_split(line, ' ');
	i = 0;
	while (info[i])
		i++;
	if (i != 2 || check_string(info[0], "EA") == -1)
		return (memfree(info, i + 1));
	if (load_img(img->mlx, info[1], &img->textures[1]))
		return (memfree(info, i + 1));
	memfree(info, i + 1);
	return (0);
}
