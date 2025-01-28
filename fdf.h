/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:51:07 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 20:06:21 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define WINDOW_W 1920
# define WINDOW_H 1080
# define DEFAULT_COLOR 0xFFFFFFFF
# define DEFAULT_TOP 0xFF0000FF
# define DEFAULT_BOTTOM 0x0000FFFF

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int32_t	hex_color;
	int32_t	color;
}	t_point;

typedef struct s_translate
{
	float	x;
	float	y;
}	t_translate;

typedef struct s_scale
{
	float	scale_xy;
	float	scale_z;
}	t_scale;

typedef struct s_rotate
{
	float	rot_x;
	float	rot_y;
}	t_rotate;

typedef struct s_draw_line
{
	int		index;
	float	len;
	float	x;
	float	y;
	float	destx;
	float	desty;
}	t_draw;

//window structure
typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	size_t		row_w;
	size_t		row_h;
	size_t		row_check;
	int			max_z;
	int			min_z;
	t_scale		scale;
	t_translate	move;
	t_rotate	rot;
	t_point		**points;
	t_draw		draw;
}	t_window;

//color_utils_invert.c
uint8_t		get_r_invert(uint32_t rgba);
uint8_t		get_g_invert(uint32_t rgba);
uint8_t		get_b_invert(uint32_t rgba);
uint8_t		get_a_invert(uint32_t rgba);

//color_utils.c
uint8_t		get_r(uint32_t rgba);
uint8_t		get_g(uint32_t rgba);
uint8_t		get_b(uint32_t rgba);
uint8_t		get_a(uint32_t rgba);
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//colors.c
uint32_t	get_gradient(uint32_t color_s, uint32_t color_d, \
						int len, int point);
void		hex_convert(char *str, t_window *window, int i, int j);
uint32_t	base_colors(t_window *window, int i, int j);

//draw_line.c
void		draw_px(t_point *p0, t_point *p1, \
					t_window *window, mlx_image_t *img);
void		dda_line(t_point *p0, t_point *p1, \
					t_window *window, mlx_image_t *img);
void		draw_line(mlx_image_t *img, t_window *window);

//draw.c
void		rotate(t_window *window);
void		grid_points(t_window *window, int i, int j, float z);
void		calculate_points(mlx_image_t *img, mlx_t *mlx, t_window *window);

//fdf.c
void		redraw_image(t_window *window);
void		ft_error(char *s);

//initialize.c
void		initiliaze(t_window *window);

//keyhooks.c
void		keyhook_rotate(void *param);
void		keyhook_translate_img(void *param);
void		keyhook_scale(void *param);
void		key_down(void *param);
void		keyhook_events(mlx_key_data_t keydata, void *param);

//map_control.c
void		parse_map(char *line, t_window *window);
void		null_check(char **source);
void		initiliaze_map(int argc, char *argv[], t_window *window);

//map_tasks.c
void		input_z_data(t_window *window, int *j, int *i, char **rows);
void		map_z_info(int fd, char *map_data, t_window *window);
void		allocate_points(t_window *window);
void		store_map(t_window *window, char **line, int *fd, char **map_data);
void		map_w_h_info(int fd, t_window *window, char **map_data);

#endif
