// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   map_control.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/23 22:47:55 by ehaanpaa          #+#    #+#             */
// /*   Updated: 2025/01/09 16:10:05 by ehaanpaa         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../fdf.h"

// // Exit the program as failure.
// static void	error_exit(char *s)
// {
// 	perror(s);
// 	exit(EXIT_FAILURE);
// }

// static void	count_row_w(char **map_data, Window *screen, int *flag, int *i)
// {
// 	if ((*map_data)[*i] != ' ' && *flag == 0)
// 	{
// 		if (screen->row_h == 0)
// 			screen->row_w += 1;
// 		else
// 			screen->row_check += 1;
// 		*flag = 1;
// 	}
// 	if ((*map_data)[*i] == ' ')
// 		*flag = 0;
// }

// static void	count_row_h(char **map_data, Window *screen)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	flag = 0;
// 	while ((*map_data)[i] != '\0')
// 	{
// 		if ((*map_data)[i] != '\n')
// 		{
// 			count_row_w(map_data, screen, &flag, &i);
// 		}
// 		if ((*map_data)[i] == '\n')
// 		{
// 			screen->row_h += 1;
// 			if (screen->row_h > 1 && screen->row_check != screen->row_w)
// 				error_exit("Incorrect map dimensions");
// 			flag = 0;
// 			screen->row_check = 0;
// 		}
// 		i++;
// 	}
// 	printf("height %zu width %zu\n", screen->row_h, screen->row_w);
// }

// static void	store_map(int fd, char **map_data, Window *screen)
// {
// 	static char	buffer[11];
// 	int			bytes_read;
// 	char		*temp;

// 	bytes_read = 1;
// 	temp = NULL;
// 	while (bytes_read > 0)
// 	{
// 		bytes_read = read(fd, buffer, 10);
// 		buffer[bytes_read] = '\0';
// 		temp = *map_data;
// 		*map_data = ft_strjoin(temp, buffer);
// 		free(temp);
// 		if (!(*map_data))
// 			error_exit("Memory allocation failed");
// 	}
// 	if (bytes_read == -1)
// 		error_exit("Failed to read the file");
// 	count_row_h(map_data, screen);
// }

// void	open_map(char **map_data, int argc, char *argv[], Window *screen)
// {
// 	int		fd;
// 	char	*path;

// 	path = NULL;
// 	screen->row_h = 0;
// 	screen->row_w = 0;
// 	screen->row_check = 0;
// 	if (argc < 2 || !argv[1] || argc > 2)
// 		error_exit("Invalid arguments");
// 	path = ft_strjoin("./maps/", argv[1]);
// 	if (!path)
// 		error_exit("Path is NULL");
// 	fd = open(path, O_RDONLY);
// 	if (!fd)
// 	{
// 		free(path);
// 		error_exit("Failed to open the file");
// 	}
// 	store_map(fd, map_data, screen);
// 	free(path);
// 	close(fd);
// }
