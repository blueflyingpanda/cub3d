/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 10:42:39 by lhelper           #+#    #+#             */
/*   Updated: 2020/08/26 13:25:06 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_trgb(int trgb, char c)
{
	if (c == 't')
		return (trgb & (0xFF << 24));
	if (c == 'r')
		return (trgb & (0xFF << 16));
	if (c == 'g')
		return (trgb & (0xFF << 8));
	if (c == 'b')
		return (trgb & 0xFF);
	return (-1);
}

int		add_shade(double distance, int trgb)
{
	int t;
	int r;
	int g;
	int b;

	t = get_trgb(trgb, 't');
	r = (int)lround(get_trgb(trgb, 'r') * (1 - distance));
	g = (int)lround(get_trgb(trgb, 'g') * (1 - distance));
	b = (int)lround(get_trgb(trgb, 'b') * (1 - distance));
	r = r >> 16;
	g = g >> 8;
	return (create_trgb(t, r, g, b));
}

int		get_opposite(int trgb)
{
	int t;
	int r;
	int g;
	int b;

	t = get_trgb(trgb, 't');
	r = get_trgb(trgb, 'r');
	g = get_trgb(trgb, 'g');
	b = get_trgb(trgb, 'b');
	r = 255 - (r >> 16);
	g = 255 - (g >> 8);
	b = 255 - b;
	return (create_trgb(t, r, g, b));
}

int		gradient(int trgb, int strength)
{
	int t;
	int r;
	int g;
	int b;

	t = get_trgb(trgb, 't');
	r = get_trgb(trgb, 'r');
	g = get_trgb(trgb, 'g');
	b = get_trgb(trgb, 'b');
	r = r >> 16;
	g = g >> 8;
	r -= strength;
	g -= strength;
	b -= strength;
	return (create_trgb(t, r, g, b));
}
