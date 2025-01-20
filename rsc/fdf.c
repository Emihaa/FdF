/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:45:03 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/20 22:44:42 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Exit the program as failure.
void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
 
void image_parameters(mlx_image_t *img, window_t *window)
{
	if (!img || (mlx_image_to_window(window->mlx, img, 0, 0) < 0))
		ft_error();
	display_points(img, window->mlx, window); // give vertex coordinates && display
}

 void free_everything (window_t *window)
 {
	int i = 0;
	
	while (i < (int) window->row_h)
	{
		free(window->points[i]);
		i++;
	}
	free(window->points);
 }

 
int32_t	main(int argc, char *argv[]) //args given on input
{	
	window_t window;
	open_map(argc, argv, &window); //open and read map info
	
	window.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF", true);
	if (!window.mlx)
		ft_error();
	window.img = mlx_new_image(window.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	image_parameters(window.img, &window);
	
	//esc key press and free everything
	mlx_key_hook(window.mlx, &keyhook_events, &window);
	mlx_loop_hook(window.mlx, key_down, &window);
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
	free_everything(&window);
	return (EXIT_SUCCESS);
}

