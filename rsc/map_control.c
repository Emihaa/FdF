/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:47:55 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/22 19:27:01 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	close_map(char **path, int *fd)
{
	close(*fd);
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
	{
		free(*path);
		ft_error();
	}
}

void	parse_map(char *line, window_t *window)
{
	char	**rows;
	int		i;

	i = 0;
	rows = ft_split(line, ' ');
	if (!rows)
		ft_error();
	while (rows[i])
	{
		free(rows[i]);
		i++;
	}
	if (i != (int)window->row_check)
		ft_error();
	free(rows);
}

void	null_check(char **source)
{
	if (!*source)
		ft_error();
}

static void	open_map(int argc, char *argv[], char **path, int *fd)
{
	if (argc < 2 || !argv[1] || argc > 2)
		ft_error();
	*path = ft_strjoin("./maps/", argv[1]);
	if (!*path)
		ft_error();
	*fd = open(*path, O_RDONLY);
	if (*fd == -1)
	{
		free(*path);
		ft_error();
	}
}

void	initiliaze_map(int argc, char *argv[], window_t *window)
{
	int		fd;
	char	*path;
	char	*map_data;

	fd = 0;
	map_data = NULL;
	path = NULL;
	initiliaze(window);
	open_map(argc, argv, &path, &fd);
	map_w_h_info(fd, window, &map_data);
	allocate_points(window);
	close_map(&path, &fd);
	map_z_info(fd, map_data, window);
	free(map_data);
	free(path);
	close(fd);
}
