/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:55:53 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 19:51:01 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	keyhook_rotate(void *param)
{
	float		x;
	float		y;
	t_window	*window;

	window = (t_window *)param;
	x = 0;
	y = 0;
	if (mlx_is_key_down(window->mlx, MLX_KEY_1))
		x += 0.05;
	if (mlx_is_key_down(window->mlx, MLX_KEY_2))
		y += 0.05;
	window->rot.rot_x += x;
	window->rot.rot_y += y;
	if (y != 0 || x != 0)
		redraw_image(window);
}

void	keyhook_translate_img(void *param)
{
	int			dx;
	int			dy;
	t_window	*window;

	window = (t_window *)param;
	dx = 0;
	dy = 0;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
		dy -= 10;
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
		dy += 10;
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
		dx -= 10;
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
		dx += 10;
	window->move.x += dx;
	window->move.y += dy;
	if (dx != 0 || dy != 0)
		redraw_image(window);
}

void	keyhook_scale(void *param)
{
	float		xy;
	int			x;
	t_window	*window;

	window = (t_window *)param;
	xy = 0;
	x = 0;
	if (mlx_is_key_down(window->mlx, MLX_KEY_Q))
	{
		xy += 0.05;
		x -= 20;
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_Z))
	{
		xy -= 0.05;
		x += 20;
	}
	window->scale.scale_xy += xy;
	window->move.x -= x;
	if (xy != 0 || x != 0)
		redraw_image(window);
}

void	key_down(void *param)
{
	float		z;
	t_window	*window;

	window = (t_window *)param;
	z = 0;
	if (mlx_is_key_down(window->mlx, MLX_KEY_C))
		z -= 0.2;
	if (mlx_is_key_down(window->mlx, MLX_KEY_E))
		z += 0.2;
	window->scale.scale_z += z;
	if (z != 0)
		redraw_image(window);
	keyhook_scale(window);
	keyhook_translate_img(window);
	keyhook_rotate(window);
}

void	keyhook_events(mlx_key_data_t keydata, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		{
			mlx_close_window(window->mlx);
			return ;
		}
	}
}
