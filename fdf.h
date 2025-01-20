/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:51:07 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/20 22:45:04 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define DEFAULT_COLOR 0xFFFFFFFF
# define DEFAULT_TOP 0xFF0000FF
# define DEFAULT_BOTTOM 0x0000FFFF
# define PI 3.14159265358979323846

typedef struct s_point
{
    int x;
    int y;
    int z;
    int32_t hex_color;
    int32_t color;
    
} point_t;

typedef struct s_translate
{
    float x;
    float y;
} translate_t;

typedef struct s_scale
{
    float scale_xy;
    float scale_z;
} scale_t;

typedef struct s_rotate
{
    float rotate_x;
    float rotate_y;
    float rotate_z;
} rotate_t;


//window structure
typedef struct s_window
{
    mlx_t *mlx;
    mlx_image_t *img;
    size_t row_w;
    size_t row_h;
    size_t row_check;
    int max_z;
    int min_z;
    scale_t scale;
    translate_t move;
    rotate_t rotate;
    point_t **points;
}   window_t;

//map_control.c
void open_map(int argc, char *argv[], window_t *window);
uint32_t base_colors(window_t *window, int i, int j);

//color_utils.c
uint8_t get_a(uint32_t rgba);
uint8_t get_b(uint32_t rgba);
uint8_t get_g(uint32_t rgba);
uint8_t get_r(uint32_t rgba);
uint32_t get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint8_t	get_r_invert(uint32_t rgba);
uint8_t	get_g_invert(uint32_t rgba);
uint8_t	get_b_invert(uint32_t rgba);

//draw.c
void display_points(mlx_image_t *img, mlx_t* mlx, window_t *window);
uint32_t get_gradient(uint32_t color_s, uint32_t color_d, int len, int point);
void redraw_image(window_t *window);
void rotate(window_t *window);

//fdf.c
void ft_error(void);

//keyhooks.c
void keyhook_events(mlx_key_data_t keydata, void* param);
void keyhook_z_depth(mlx_key_data_t keydata, void* param);
void keyhook_scale(mlx_key_data_t keydata, void* param);
void key_down(void* param);


#endif