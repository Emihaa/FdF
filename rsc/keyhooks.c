/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:55:53 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/20 22:58:29 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
}

void keyhook_rotate(mlx_key_data_t keydata, void* param)
{
	window_t *window = (window_t *)param;
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		window->rotate.rotate_x += 0.2;
		redraw_image(window);
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		window->rotate.rotate_y += 0.2;
		redraw_image(window);
	}
}

void keyhook_scale(mlx_key_data_t keydata, void* param)
{
	window_t *window = (window_t *)param;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		window->scale.scale_xy += 0.1;
		redraw_image(window);
	}
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
	{
		window->scale.scale_xy -= 0.1;
		redraw_image(window);
	}
}

void keyhook_translate_img(mlx_key_data_t keydata, void* param)
{
    window_t *window = (window_t *)param;
	if (keydata.key == MLX_KEY_W)
		window->move.y -= 50;
	if (keydata.key == MLX_KEY_S)
		window->move.y += 50;
    if (keydata.key == MLX_KEY_A)
		window->move.x -= 50;
    if (keydata.key == MLX_KEY_D)
		window->move.x += 50;
	redraw_image(window);
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
		keyhook_scale(keydata, window);
        keyhook_translate_img(keydata, window);
		keyhook_rotate(keydata, window);
	}
}