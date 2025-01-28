/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:45:03 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 19:51:25 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	redraw_image(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	window->img = mlx_new_image(window->mlx, WINDOW_W, WINDOW_H);
	if (!window->img)
		ft_error("MLX_new_image failed");
	calculate_points(window->img, window->mlx, window);
}

void	ft_error(char *s)
{	
	ft_printf("Error: %s\n", s);
	exit(EXIT_FAILURE);
}

static void	free_everything(t_window *window)
{
	int	i;

	i = 0;
	while (i < (int) window->row_h)
	{
		free(window->points[i]);
		i++;
	}
	free(window->points);
}

static void	window_parameters(t_window *window)
{
	window->mlx = mlx_init(WINDOW_W, WINDOW_H, "FDF", true);
	if (!window->mlx)
		ft_error("MLX_init failed");
	window->img = mlx_new_image(window->mlx, WINDOW_W, WINDOW_H);
	if (!window->img || \
		(mlx_image_to_window(window->mlx, window->img, 0, 0) < 0))
		ft_error("MLX_new_image failed");
	calculate_points(window->img, window->mlx, window);
}

int32_t	main(int argc, char *argv[])
{	
	t_window	window;

	initiliaze_map(argc, argv, &window);
	window_parameters(&window);
	mlx_key_hook(window.mlx, &keyhook_events, &window);
	mlx_loop_hook(window.mlx, key_down, &window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
	free_everything(&window);
	return (EXIT_SUCCESS);
}
