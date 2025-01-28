/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tasks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:15:45 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 19:49:53 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	input_z_data(t_window *window, int *j, int *i, char **rows)
{
	char	*temp;

	temp = NULL;
	window->points[*i][*j].z = ft_atoi(rows[*j]);
	if (window->points[*i][*j].z > 1 && \
		window->max_z < window->points[*i][*j].z)
		window->max_z = window->points[*i][*j].z;
	else if (window->points[*i][*j].z < -1 && \
			window->min_z > window->points[*i][*j].z)
		window->min_z = window->points[*i][*j].z;
	window->points[*i][*j].hex_color = DEFAULT_COLOR;
	if (ft_strchr(rows[*j], ',') != NULL)
	{
		if (ft_strchr(rows[*j], '\n') != NULL)
		{
			temp = ft_substr(rows[*j], 0, ft_strlen(rows[*j]) - 1);
			hex_convert(ft_strchr(temp, ',') + 3, window, *i, *j);
			free(temp);
		}	
		else
			hex_convert(ft_strchr(rows[*j], ',') + 3, window, *i, *j);
	}
	else
		window->points[*i][*j].hex_color = base_colors(window, *i, *j);
	free(rows[*j]);
}

void	map_z_info(int fd, char *map_data, t_window *window)
{
	char	*line;
	char	**rows;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		rows = ft_split(line, ' ');
		j = 0;
		while (rows[j])
		{
			input_z_data(window, &j, &i, rows);
			j++;
		}
		free(rows);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	ft_printf("map:\n%s\n", map_data);
}

void	allocate_points(t_window *window)
{
	int	i;

	i = 0;
	window->points = malloc(window->row_h * sizeof(t_point *));
	if (!window->points)
		ft_error("Malloc fail");
	while (i < (int) window->row_h)
	{
		window->points[i] = malloc(window->row_w * sizeof(t_point));
		if (!window->points[i])
		{
			while (i >= 0)
			{
				free(window->points[i]);
				i--;
			}
			free(window->points);
			ft_error("Malloc fail");
		}
		i++;
	}
}

void	store_map(t_window *window, char **line, int *fd, char **map_data)
{
	char	*temp;

	temp = NULL;
	parse_map(*line, window);
	free(*line);
	window->row_h++;
	*line = get_next_line(*fd);
	if (!*line)
		return ;
	temp = *map_data;
	*map_data = ft_strjoin(temp, *line);
	if (!*map_data)
	{
		free(temp);
		ft_error("Malloc fail");
	}
	free(temp);
}

void	map_w_h_info(int fd, t_window *window, char **map_data)
{
	char	*line;
	char	**rows;

	line = get_next_line(fd);
	null_check(&line);
	*map_data = ft_strdup(line);
	null_check(map_data);
	rows = ft_split(line, ' ');
	null_check(rows);
	while (rows[window->row_w])
	{
		free(rows[window->row_w]);
		window->row_w++;
	}
	window->row_check = window->row_w;
	while (line)
		store_map(window, &line, &fd, map_data);
	free(line);
	free(rows);
}
