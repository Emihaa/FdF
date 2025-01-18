/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:55:53 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/18 22:31:39 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void keyhook_rotate(mlx_key_data_t keydata, void* param)
{
	window_t *window = (window_t *)param;
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		ft_printf("1");
		rotate(window, M_PI / 18);
	}
	if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	{
		ft_printf("2");
		rotate(window, -M_PI / 18);
	}
}

void keyhook_scale(mlx_key_data_t keydata, void* param)
{
	window_t *window = (window_t *)param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		window->scale.scale_z += 5;
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		window->scale.scale_z -= 5;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		window->scale.scale_xy += 0.1;
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_PRESS)
		window->scale.scale_xy -= 0.1;
	redraw_image(window);
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
	mlx_t* mlx = (mlx_t *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		{
			ft_printf("esc\n");
			mlx_close_window(mlx);
            return;
		}
		keyhook_scale(keydata, mlx);
        keyhook_translate_img(keydata, mlx);
		keyhook_rotate(keydata, mlx);
	}	
}