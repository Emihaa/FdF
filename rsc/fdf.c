/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:45:03 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/24 17:46:59 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	redraw_image(window_t *window)
{
	mlx_delete_image(window->mlx, window->img);
	window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!window->img)
		ft_error();
	calculate_points(window->img, window->mlx, window);
}

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	free_everything(window_t *window)
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

static void	window_parameters(window_t *window)
{
	window->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF", true);
	if (!window->mlx)
		ft_error();
	window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!window->img || \
		(mlx_image_to_window(window->mlx, window->img, 0, 0) < 0))
		ft_error();
	calculate_points(window->img, window->mlx, window);
}

int32_t	main(int argc, char *argv[])
{	
	window_t	window;

	initiliaze_map(argc, argv, &window);
	window_parameters(&window);
	mlx_key_hook(window.mlx, &keyhook_events, &window);
	mlx_loop_hook(window.mlx, key_down, &window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
	free_everything(&window);
	return (EXIT_SUCCESS);
}
