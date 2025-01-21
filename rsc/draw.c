/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:59:24 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/21 16:46:22 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void redraw_image(window_t *window)
{
	mlx_delete_image(window->mlx, window->img);
	window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!window->img)
		ft_error();	
	display_points(window->img, window->mlx, window);
}

uint32_t get_gradient(uint32_t color_s, uint32_t color_d, int len, int point)
{
		float ratio;
		int red;
		int green;
		int blue;

		if (len == 0)
			return (color_s);
		ratio = (float)point / (float)len;		
		red = (int)((1 - ratio) * (get_r_invert(color_s)) + (ratio * (get_r_invert(color_d))));
		green = (int)((1 - ratio) * (get_g_invert(color_s)) + (ratio * (get_g_invert(color_d))));
		blue = (int)((1 - ratio) * (get_b_invert(color_s)) + (ratio * (get_b_invert(color_d))));				
		return (get_rgba((uint8_t)red, (uint8_t)green, (uint8_t)blue, 255));
}

static void draw_line_ver(mlx_image_t *img, window_t *window)
{
	int i = 0;
	int j = 0;
	int index = 0;
	float x = 0;
	float y = 0;
	float destx = 0;
	float desty = 0;
	float len = 0;
	
	while (i + 1 < (int)window->row_h)
	{		
		while (j < (int)window->row_w)
		{
			destx = (window->points[i+1][j].x - window->points[i][j].x);
			desty = (window->points[i+1][j].y - window->points[i][j].y);
			if (destx >= desty)
				len = destx;
			else
				len = desty;
			destx = destx/len;
			desty = desty/len;
			
			x = window->points[i][j].x;
			y = window->points[i][j].y;	
			
			index = 0;
			while (index <= len)
			{
				window->points[i][j].color = get_gradient(window->points[i+1][j].hex_color, window->points[i][j].hex_color, len, len - index);
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_put_pixel(img, x, y, window->points[i][j].color);
				x += destx;
				y += desty;
				index += 1;
			}
			j++;
		}
		j = 0;
		i++;
	}	
}

static void draw_line_hor(mlx_image_t *img, window_t *window)
{
	int i = 0;
	int j = 0;
	int index = 0;
	float x = 0;
	float y = 0;
	float destx = 0;
	float desty = 0;
	float len = 0;
	
	while (i < (int)window->row_h)
	{		
		while (j + 1 < (int)window->row_w)
		{
			destx = (window->points[i][j+1].x - window->points[i][j].x);
			desty = (window->points[i][j+1].y - window->points[i][j].y);
			if (destx >= desty)
				len = destx;
			else
				len = desty;
			destx = destx/len;
			desty = desty/len;

			x = window->points[i][j].x;
			y = window->points[i][j].y;

			index = 0;
			while (index <= len)
			{
				window->points[i][j].color = get_gradient((int)window->points[i][j+1].hex_color, (int)window->points[i][j].hex_color, len, len - index);
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_put_pixel(img, x, y, window->points[i][j].color);
				x += destx;
				y += desty;
				index += 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	draw_line_ver(img, window);
}

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
	int i = 0;
	int j = 0;
	double temp_x = 0;
	double temp_z = 0;
	int q = 120;
	
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

