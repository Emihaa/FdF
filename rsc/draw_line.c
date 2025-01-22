/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:28:33 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/22 20:33:20 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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

void draw_line_hor(mlx_image_t *img, window_t *window)
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
