/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:28:33 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/24 17:43:50 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_px(point_t *p0, point_t *p1, window_t *window, mlx_image_t *img)
{
	while (window->draw.index <= window->draw.len)
	{
		p0->color = get_gradient((int)p1->hex_color, \
		(int)p0->hex_color, (int)window->draw.len, \
		(int)window->draw.len - window->draw.index);
		if (window->draw.x >= 0 && window->draw.x < WINDOW_WIDTH \
		&& window->draw.y >= 0 && window->draw.y < WINDOW_HEIGHT)
			mlx_put_pixel(img, window->draw.x, window->draw.y, p0->color);
		window->draw.x += window->draw.destx;
		window->draw.y += window->draw.desty;
		window->draw.index += 1;
	}
}

void	dda_line(point_t *p0, point_t *p1, window_t *window, mlx_image_t *img)
{
	window->draw.x = 0;
	window->draw.y = 0;
	window->draw.destx = 0;
	window->draw.desty = 0;
	window->draw.index = 0;
	window->draw.len = 0;
	window->draw.destx = (float)p1->x - p0->x;
	window->draw.desty = (float)p1->y - p0->y;
	if (window->draw.destx >= window->draw.desty)
		window->draw.len = window->draw.destx;
	else
		window->draw.len = window->draw.desty;
	window->draw.destx = window->draw.destx / window->draw.len;
	window->draw.desty = window->draw.desty / window->draw.len;
	window->draw.x = p0->x;
	window->draw.y = p0->y;
	window->draw.index = 0;
	draw_px(p0, p1, window, img);
}

void	draw_line(mlx_image_t *img, window_t *window)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (int)window->row_h)
	{
		while (++j < (int)window->row_w)
			dda_line(&window->points[i][j - 1], \
			&window->points[i][j], window, img);
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
	while (++i < (int)window->row_h)
	{
		while (j < (int)window->row_w)
		{
			dda_line(&window->points[i - 1][j], \
			&window->points[i][j], window, img);
			j++;
		}
		j = 0;
	}	
}
