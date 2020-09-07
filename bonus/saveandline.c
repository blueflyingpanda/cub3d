/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveandline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 14:38:38 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 12:16:35 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_line(char *line, int *count, int *max_len)
{
	int len;

	if (*line != ' ' && *line != '1')
	{
		free(line);
		return ;
	}
	len = ft_strlen(line);
	if (len > *max_len)
		*max_len = len;
	(*count)++;
	free(line);
}

void	fill_line(char *map, char *line, int max_len, int line_no)
{
	int len;

	len = ft_strlen(line);
	ft_memcpy(map + (line_no * max_len), line, len);
	while (len < max_len)
	{
		map[len + (line_no * max_len)] = ' ';
		len++;
	}
}

int		fill_array(char *map, char *path, int max_len, int start_map)
{
	int		fd;
	char	*line;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	while (start_map-- > 1)
	{
		get_next_line(fd, &line);
		free(line);
	}
	while (get_next_line(fd, &line))
	{
		if (*line == '\0')
		{
			free(line);
			return (0);
		}
		fill_line(map, line, max_len, start_map++);
		free(line);
	}
	if (*line != '\0')
		fill_line(map, line, max_len, start_map);
	free(line);
	return (0);
}

void	init_bmp_header(int8_t *bmp, t_image *screen)
{
	int16_t data_16bit;
	int32_t	data_32bit;

	ft_bzero(bmp, HEADER_SIZE);
	ft_memcpy(bmp + 0x00, "BM", 2);
	data_32bit = HEADER_SIZE;
	ft_memcpy(bmp + 0x0A, &data_32bit, sizeof(data_32bit));
	data_32bit = INFOHEADER_SIZE;
	ft_memcpy(bmp + 0x0E, &data_32bit, sizeof(data_32bit));
	data_32bit = screen->width;
	ft_memcpy(bmp + 0x12, &data_32bit, sizeof(data_32bit));
	data_32bit = -screen->height;
	ft_memcpy(bmp + 0x16, &data_32bit, sizeof(data_32bit));
	data_16bit = 1;
	ft_memcpy(bmp + 0x1A, &data_16bit, sizeof(data_16bit));
	data_16bit = BPP;
	ft_memcpy(bmp + 0x1C, &data_16bit, sizeof(data_16bit));
}

void	save_bmp(t_image *screen)
{
	int		fd;
	int		size;
	int8_t	*bmp;
	int		tmp;

	tmp = 0;
	size = HEADER_SIZE + (screen->size_line * screen->height);
	bmp = malloc(size);
	init_bmp_header(bmp, screen);
	while (tmp < screen->height)
	{
		ft_memcpy(bmp + HEADER_SIZE + tmp * screen->width * sizeof(int),\
			screen->addr + tmp * screen->size_line, \
				screen->width * sizeof(int));
		tmp++;
	}
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, \
					S_IRUSR | S_IWUSR | S_IROTH);
	if (fd == -1)
		my_exit(EINVAL);
	if (write(fd, bmp, size) == -1)
		my_exit(EINVAL);
	free(bmp);
	close(fd);
}
