/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhelper <lhelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 12:28:02 by lhelper           #+#    #+#             */
/*   Updated: 2020/09/05 18:45:34 by lhelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <sys/errno.h>
# include "../mms/mlx.h"
# include "get_next_line.h"

typedef struct	s_get{
	char	**info;
	char	**color;
	int		i;
}				t_get;

typedef struct	s_draw{
	int i;
	int vt;
	int vb;
	int dv;
	int du;
	int u;
	int uw;
	int dw;
	int x;
}				t_draw;

typedef struct	s_flags{
	int r;
	int no;
	int so;
	int ea;
	int we;
	int f;
	int c;
	int s;
	int p;
	int map;
	int end_map;
	int start_map;
}				t_flags;

typedef struct	s_norme{
	long long	delta_x;
	long long	delta_y;
	long long	dist_x;
	long long	dist_y;
	int			l;
}				t_norme;

typedef struct	s_norm{
	int			i;
	int			n;
	long long	distance;
	int			d;
	int			m;
	int			xo;
	int			yo;
	int			closest_wall;
	int			closest_dist;
	double		angle;
}				t_norm;

typedef struct	s_keyboard{
	int			a;
	int			s;
	int			d;
	int			w;
	int			left;
	int			right;
}				t_keyboard;

extern	t_keyboard g_keyboard;

typedef struct	s_map{
	int x;
	int y;
}				t_map;

typedef struct	s_ray{
	int x;
	int y;
}				t_ray;

typedef struct	s_item{
	int a;
	int b;
}				t_item;

typedef struct	s_display{
	int u1;
	int u2;
	int v1t;
	int v1b;
	int v2t;
	int v2b;
	int tmp;
}				t_display;

typedef struct	s_view{
	int			wx1;
	int			wx2;
	int			wy1;
	int			wy2;
	int			twx1;
	int			twx2;
	int			twy1;
	int			twy2;
	int			tmp;
	int			see;
	int			texture;
	long long	dist2cent;
}				t_view;

extern	t_view *g_viewer;
extern	t_view *g_spview;

typedef struct	s_wall{
	int			walla1;
	int			walla2;
	int			wallb1;
	int			wallb2;
}				t_wall;

typedef struct	s_image{
	void		*img;
	int			width;
	int			height;
	char		*addr;
	int			size_line;
}				t_image;

typedef struct	s_data{
	t_image		sprite;
	t_image		textures[4];
	t_wall		*walls;
	t_item		*it;
	t_map		obs[1000];
	t_map		items[1000];
	int			i;
	int			sp;
	int			save;
	void		*mlx;
	void		*win;
	int			a;
	int			b;
	int			angle;
	int			width;
	int			height;
	int			floor;
	int			ceil;
	double		sin;
	double		cos;
}				t_data;

int				create_trgb(int t, int r, int g, int b);
int				get_trgb(int trgb, char c);
int				add_shade(double distance, int trgb);
int				get_opposite(int trgb);
int				gradient(int trgb, int strength);
int				on_key_press(int keycode, t_data *img);
int				on_key_release(int keycode, void *ptr);
int				on_red_cross(t_data *img);
int				movement(t_data *img);
void			raycaster(t_view *viewer, int icopy, int is_sprite);
int				max_coord(int c1, int c2);
int				min_coord(int c1, int c2);
int				parse_map(t_data *map, char *path);
int				parse_file(int fd, t_data *img, int *y, t_flags *flag);
int				get_what(t_data *map, char *line, int *y, t_flags *flag);
int				get_res(t_data *img, char *line, t_flags *flag);
int				get_north(t_data *img, char *line, t_flags *flag);
int				get_south_or_sprite(t_data *img, char *line, t_flags *flag);
int				get_west(t_data *img, char *line, t_flags *flag);
int				get_east(t_data *img, char *line, t_flags *flag);
int				get_floor(t_data *img, char *line, t_flags *flag);
int				get_ceil(t_data *img, char *line, t_flags *flag);
int				get_map(t_data *img, char *line, int *y, t_flags *flag);
int				get_map_size(char *path, int *count, int *max_len, \
int start_map);
int				cross_check(int i, int len, char *map);
int				check_digit(char *str);
int				check_string(char *st1, char *st2);
int				convert_cord(t_data *img);
int				map_to_world(t_data *img);
int				map_to_array(char *path, int start_map);
int				check_extension(char *path);
int				my_exit(int error);
int				memfree(char **ptr_arr, int x);
int				render_frame(t_data *img);
int				ft_strncmp(char *s1, char *s2, size_t n);
int				fill_array(char *map, char *path, int max_len, int start_map);
int				fill_cord(t_map *cord, int y);
int				before_map(t_data *img, char *line, t_flags *flag);
int				assign_elem(char *line, t_data *img, t_flags *flag,\
t_map cord);
unsigned int	get_pixel(t_image *img, int x, int y);
void			inside_calculate_viewer(t_data *data, t_view *viewer,\
t_norme *d, int i);
void			condition_calculate_viewer(t_data *data, t_view *viewer,\
t_norme *d, int i);
void			inside_calculate_spview(t_data *data, t_view *viewer,\
t_norme *d, int i);
void			assign_delta(t_draw *s, t_display *play);
void			inside_drawall(t_data *data, t_draw *s, t_display *play,\
t_view *viewer);
void			draw_texture(t_draw *s, t_image texture, t_image *screen);
void			formula(t_norm *n, t_view *viewer, t_ray *ray, int is_sprite);
void			process_line(char *line, int *count, int *max_len);
void			fill_line(char *map, char *line, int max_len, int line_no);
void			init_bmp_header(int8_t *bmp, t_image *screen);
void			rotation(t_data *img);
void			set_keyboard_state(int keycode, int value);
void			*ft_memcpy(void *dst, void *src, int n);
void			save_bmp(t_image *screen);
void			ray_init(t_ray *ray, double *angle);
void			limit_wall(t_view *viewer);
void			calculate_viewer(t_view *viewer, t_data *data, t_view *spview);
void			sort_walls(t_view *viewer, int icopy);
void			check_args(int argc, char **argv, t_data *img);
void			init_map(t_data *img, char *file_name);
void			calculate_display(t_display *play, t_view *viewer, \
t_data *data);
void			pixel_put(t_image *img, int x, int y, unsigned int color);
void			draw_floorceil(t_image *img, t_data *data, int ceil, int floor);
void			draw_wall(t_image *screen, t_data *data, t_image texture, \
t_view viewer);
void			draw_column(t_data *data, t_draw *s, t_image texture,\
t_image *screen);
void			wall_or_sprite(int *index, int *space, t_data *img,\
t_image *screen);
void			init_hooks(t_data *img);
int				draw(t_data *img);
int				load_img(void *mlx, char *path, t_image *image);
int				square(long long var);
void			limit_wall(t_view *viewer);
int				ft_atoi(char *str);
int				ft_strncmp(char *s1, char *s2, size_t n);
char			**ft_split(char *s, char c);
t_image			new_frame(t_data *img);

# define H 1000
# define WALLPX 256
# define DIST 2
# define STEP 70
# define ROTATE 2
# define SIGHT 30
# define RAYS 1801
# define FOV 90
# define R_OFFSET 1.0*FOV/(RAYS-1)
# define RANGE 200000
# define SIZE 2000

# define BPP 32
# define FILEHEADER_SIZE 14
# define INFOHEADER_SIZE 40
# define HEADER_SIZE (FILEHEADER_SIZE + INFOHEADER_SIZE)

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define RED_CROSS 17

# define NO_EVENT_M 0L
# define KEY_PRESS_M 1L<<0
# define KEY_RELEASE_M 1L<<1
# define BUTTON_PRESS_M 1L<<2
# define BUTTON_RELEASE_M 1L<<3
# define RED_CROSS_M 1L<<17

#endif
