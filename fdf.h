/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:51:07 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/13 18:12:32 by ehaanpaa         ###   ########.fr       */
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

typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
    
} point_t;

//window structure
typedef struct s_window
{
    mlx_t *mlx;
    size_t row_w;
    size_t row_h;
    size_t row_check;
    point_t **vertex;
}   window_t;

//map_control.c
void open_map(int argc, char *argv[], window_t *screen);

//fdf.c


#endif