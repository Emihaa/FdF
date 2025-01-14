/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:45:03 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/14 14:31:39 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

//esc button for closing
void keyhook_esc(mlx_key_data_t keydata, void* param)
{
	mlx_t* mlx = (mlx_t*)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

static void draw_line_ver(mlx_image_t *img, window_t *screen)
{
	int i = 0;
	int j = 0;
	int index = 0;
	float x = 0;
	float y = 0;
	float destx = 0;
	float desty = 0;
	float step = 0;
	
	while (i + 1 < (int)screen->row_h)
	{		
		while (j < (int)screen->row_w)
		{
			destx = (screen->vertex[i+1][j].x - screen->vertex[i][j].x);
			desty = (screen->vertex[i+1][j].y - screen->vertex[i][j].y);
			if (destx >= desty)
				step = destx;
			else
				step = desty;
			destx = destx/step;
			desty = desty/step;

			x = screen->vertex[i][j].x;
			y = screen->vertex[i][j].y;
			
			index = 0;
			while (index <= step)
			{
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_put_pixel(img, x, y, DEFAULT_COLOR);
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

static void draw_line_hor(mlx_image_t *img, window_t *screen)
{
	int i = 0;
	int j = 0;
	int index = 0;
	float x = 0;
	float y = 0;
	float destx = 0;
	float desty = 0;
	float step = 0;
	
	while (i < (int)screen->row_h)
	{		
		while (j + 1 < (int)screen->row_w)
		{
			destx = (screen->vertex[i][j+1].x - screen->vertex[i][j].x);
			desty = (screen->vertex[i][j+1].y - screen->vertex[i][j].y);
			if (destx >= desty)
				step = destx;
			else
				step = desty;
			destx = destx/step;
			desty = desty/step;

			x = screen->vertex[i][j].x;
			y = screen->vertex[i][j].y;

			index = 0;
			while (index <= step)
			{
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_put_pixel(img, x, y, DEFAULT_COLOR);
				x += destx;
				y += desty;
				index += 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	draw_line_ver(img, screen);
}

static void display_points(mlx_image_t *img, mlx_t* mlx, window_t *screen)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int angle = 120;
	int space = 0;

	if (screen->row_w >= screen->row_h)	
		space = 400 / (screen->row_w - 1);
	else
		space = 400 / (screen->row_h - 1); 
	ft_printf("rows & columns: %d %d\n", screen->row_w, screen->row_h);
	mlx_put_pixel(img, 40, 40, 0xFFFFFFFF);
	mlx_put_pixel(img, 40, WINDOW_HEIGHT-40, 0xFFFFFFFF);	
	while (i < (int) screen->row_h)
	{
		while (j < (int) screen->row_w)
		{
			screen->vertex[i][j].x = (int)(x * cos(angle)) + (y * cos(angle + 2)) + (screen->vertex[i][j].z * cos(angle - 2));
			screen->vertex[i][j].x *= 2;
			screen->vertex[i][j].x += (WINDOW_WIDTH) - (1000);
			screen->vertex[i][j].y = (int)(x * sin(angle)) + (y * sin(angle + 2)) + (screen->vertex[i][j].z * sin(angle - 2));
			screen->vertex[i][j].y *= 2;
			screen->vertex[i][j].y += (WINDOW_HEIGHT) - (1000) + 70;
			j++;
			x += space;
		}
		y += space;
		i++;
		j = 0;
		x = 0;
	}
	draw_line_hor(img, screen);
	mlx_image_to_window(mlx, img, 0, 0);
}
 
int32_t	main(int argc, char *argv[]) //args given on input
{	
	window_t screen;
	int i = 0;
	
	open_map(argc, argv, &screen); //open and read map info
	
	screen.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF", true);
	if (!screen.mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(screen.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img || (mlx_image_to_window(screen.mlx, img, 0, 0) < 0))
		ft_error();
	display_points(img, screen.mlx, &screen); // give vertex coordinates && display
	
	//esc key press and free everything
	while (i < (int) screen.row_h)
	{
		free(screen.vertex[i]);
		i++;
	}
	free(screen.vertex);
	mlx_key_hook(screen.mlx, &keyhook_esc, screen.mlx);	
	mlx_loop(screen.mlx);
	mlx_terminate(screen.mlx);
	return (EXIT_SUCCESS);
}


