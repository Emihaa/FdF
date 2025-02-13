/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:59:24 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 19:51:40 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static float	compute_z_center(t_window *window, int *space)
{
	float	z_sum;
	int		i;
	int		j;

	z_sum = 0.0f;
	i = 0;
	j = 0;
	while (i < (int)window->row_h)
	{
		while (j < (int)window->row_w)
		{
			z_sum += window->points[i][j].z;
			j++;
		}
		i++;
	}
	if (window->row_w >= window->row_h)
		*space = 1000 / (window->row_w - 1);
	else
		*space = 1000 / (window->row_h - 1);
	return (z_sum / (window->row_h * window->row_w));
}

void	rotate(t_window *window)
{
	int		i;
	int		j;
	double	temp_x;
	double	temp_z;
	int		q;

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

void	grid_points(t_window *window, int i, int j, float z)
{
	int	space;
	int	x;
	int	y;

	x = 0;
	y = 0;
	z = compute_z_center(window, &space);
	while (i++ < (int) window->row_h)
	{
		while (j++ < (int) window->row_w)
		{
			z = (window->points[i - 1][j - 1].z) * window->scale.scale_z;
			window->points[i - 1][j - 1].x = (x - y) * cos(window->rot.rot_x);
			window->points[i - 1][j - 1].x *= 0.7 + window->scale.scale_xy;
			window->points[i - 1][j - 1].x += WINDOW_W - 1000 + window->move.x;
			window->points[i - 1][j - 1].y = (x + y) * \
			sin(window->rot.rot_y) - z;
			window->points[i - 1][j - 1].y *= 0.7 + window->scale.scale_xy;
			window->points[i - 1][j - 1].y += WINDOW_H - 800 + window->move.y;
			x += space;
		}
		y += space;
		j = 0;
		x = 0;
	}
}

void	calculate_points(mlx_image_t *img, mlx_t *mlx, t_window *window)
{
	int		i;
	int		j;
	float	z;

	i = 0;
	j = 0;
	z = 0;
	grid_points(window, i, j, z);
	draw_line(img, window);
	mlx_image_to_window(mlx, img, 0, 0);
}
