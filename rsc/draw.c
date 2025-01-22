/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:59:24 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/22 20:30:34 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static float compute_z_center(window_t *window)
{
	float z_sum = 0.0f;
	int i = 0;
	int j = 0;

	while (i < (int)window->row_h)
	{
		while (j < (int)window->row_w)
		{
			z_sum += window->points[i][j].z;
			j++;
		}
		i++;
	}
	return (z_sum / (window->row_h * window->row_w));
}

void rotate(window_t *window)
{
	int i;
	int j;
	double temp_x;
	double temp_z;
	int q;

	i = 0;
	j = 0;
	temp_x = 0;
	temp_z = 0;
	q = 120;
	while (i < (int)window->row_h)
	{
		while (j < (int)window->row_w)
		{
			temp_x = window->points[i][j].x;
			temp_z = window->points[i][j].z;
			window->points[i][j].x = temp_x * cos(q) + temp_z * sin(q);
			window->points[i][j].z = temp_z * sin(q) - temp_x * cos(q);
			j++;
		}
		i++;
		j = 0;
	}
}

void display_points(mlx_image_t *img, mlx_t* mlx, window_t *window)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	float z = 0;
	int space = 0;
	float z_center = 0;
    
    z = compute_z_center(window);
	if (window->row_w >= window->row_h)	
		space = 1000 / (window->row_w - 1);
	else
		space = 1000 / (window->row_h - 1);
	while (i < (int) window->row_h)
	{
		while (j < (int) window->row_w)
		{
			z = (window->points[i][j].z - z_center) * window->scale.scale_z + z_center;
			window->points[i][j].x = (x - y) * cos(window->rotate.rotate_x);
			window->points[i][j].x *= 0.7 + window->scale.scale_xy;
			window->points[i][j].x += (WINDOW_WIDTH) - (1000) + window->move.x;
			window->points[i][j].y = (x + y) * sin(window->rotate.rotate_y) - z;
			window->points[i][j].y *= 0.7 + window->scale.scale_xy;
			window->points[i][j].y += (WINDOW_HEIGHT) - (1000) + 100 + window->move.y;
			//call here the base color?
			j++;
			x += space;
		}
		y += space;
		i++;
		j = 0;
		x = 0;
	}
	draw_line_hor(img, window);
	mlx_image_to_window(mlx, img, 0, 0);
}

