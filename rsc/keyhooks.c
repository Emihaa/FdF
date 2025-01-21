/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:55:53 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/21 17:02:31 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void keyhook_rotate(void* param)
{
	window_t *window = (window_t *)param;
	
	if (mlx_is_key_down(window->mlx, MLX_KEY_1))
	{
		window->rotate.rotate_x += 0.05;
		redraw_image(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_2))
	{
		window->rotate.rotate_y += 0.05;
		redraw_image(window);
	}
}

void keyhook_translate_img(void* param)
{
	int dx = 0;
	int dy = 0;
    window_t *window = (window_t *)param;	
	
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
		dy -= 10;
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
		dy += 10;
    if (mlx_is_key_down(window->mlx, MLX_KEY_A))
		dx -= 10;
    if (mlx_is_key_down(window->mlx,MLX_KEY_D))
		dx += 10;
	window->move.x += dx;
	window->move.y += dy;
	if (dx != 0 || dy != 0)
		redraw_image(window);
	
}

void keyhook_scale(void* param)
{
	window_t *window = (window_t *)param;

	if (mlx_is_key_down(window->mlx, MLX_KEY_Q))
	{
		window->scale.scale_xy += 0.05;
		window->move.x -= 20;
		redraw_image(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_Z))
	{
		window->scale.scale_xy -= 0.05;
		window->move.x += 20;
		redraw_image(window);
	}
}

void key_down(void* param)
{
	window_t *window = (window_t *)param;
	
	if (mlx_is_key_down(window->mlx, MLX_KEY_C))
	{
		window->scale.scale_z -= 0.2;
		redraw_image(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_E))
	{
		window->scale.scale_z += 0.2;
		redraw_image(window);
	}
	keyhook_scale(window);
	keyhook_translate_img(window);
	keyhook_rotate(window);
}

void keyhook_events(mlx_key_data_t keydata, void* param)
{
	window_t *window = (window_t *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		{
			mlx_close_window(window->mlx);
            return;
		}
	}
}