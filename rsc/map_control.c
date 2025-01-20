/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:47:55 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/20 22:58:09 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Exit the program as failure.
static void	error_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

static void hex_convert(char *str, window_t *window, int i, int j)
{
	int pos;
	unsigned int dec;
	int len;
	int val;

	dec = 0;
	pos = 0;
	val = 0;
	len = ft_strlen(str) - 1;
	while (pos <= len)
	{	
		if (str[pos] >= '0' && str[pos] <= '9')
			val = str[pos] - '0';
		else if (str[pos] >= 'a' && str[pos] <= 'f')
			val = str[pos] - 'a' + 10;
		else if (str[pos] >= 'A' && str[pos]<= 'F')
			val = str[pos] - 'A' + 10;
		else
			error_exit("Invalid hex char");
		dec = dec * 16 + val;
		pos++;
	}
	window->points[i][j].hex_color = get_rgba(get_r(dec), get_g(dec), get_b(dec), 255);
}

uint32_t base_colors(window_t *window, int i, int j)
{
	uint32_t color = DEFAULT_COLOR;
	int max_top = window->max_z + 1;
	int max_bot = window->min_z - 1;
	
	if (window->points[i][j].z > 0)
	{
		color = get_gradient(DEFAULT_COLOR, DEFAULT_TOP, max_top, window->points[i][j].z - max_top);
	}
	else if (window->points[i][j].z < 0)
	{
		color = get_gradient(DEFAULT_COLOR, DEFAULT_BOTTOM, max_bot, window->points[i][j].z - max_bot);
	}
	return (color);
}


static void map_z_info(int fd, char *map_data, window_t *window)
{
	char *line;
	char **rows;
	char *temp;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = 0;
	temp = NULL;
	line = get_next_line(fd);
	window->max_z = 1;
	window->min_z = -1;
	window->scale.scale_z = 1;
	window->scale.scale_xy = 0;
	window->rotate.rotate_x = 0.5;
	window->rotate.rotate_y = 0.5;
	while (line)
	{
		rows = ft_split(line, ' ');
		j = 0;
		while (rows[j])
		{
			window->points[i][j].z = ft_atoi(rows[j]);
			if (window->points[i][j].z > 1 && window->max_z < window->points[i][j].z)
				window->max_z = window->points[i][j].z;
			else if (window->points[i][j].z < -1 && window->min_z > window->points[i][j].z)
				window->min_z = window->points[i][j].z;
			window->points[i][j].hex_color = DEFAULT_COLOR;
			if (ft_strchr(rows[j], 'x') != NULL)
			{
				if (ft_strchr(rows[j], '\n') != NULL)
				{
					len = ft_strlen(rows[j]);
					temp = ft_substr(rows[j], 0, len-1);
					hex_convert(ft_strchr(temp, 'x')+ 1, window, i, j);
					free(temp);
				}	
				else
					hex_convert(ft_strchr(rows[j], 'x')+ 1, window, i, j);
			}
			else
				window->points[i][j].hex_color = base_colors(window, i, j);
			free(rows[j]);
			j++;
		}
		free(rows);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (map_data)
		ft_printf("print map:\n");
	//ft_printf("map:\n%s\n", map_data);
}

static void allocate_points(window_t *window)
{
	int i = 0;
	
	window->points = malloc(window->row_h * sizeof(point_t *));
	if (!window->points)
		error_exit("failed to allocate points");
	while (i < (int) window->row_h)
	{
		window->points[i] = malloc(window->row_w * sizeof(point_t));
		if (!window->points[i])
		{
			while (i >= 0)
			{
				free(window->points[i]);
				i--;
			}
			free(window->points);
			error_exit("failed to allocate points");
		}
		i++;
	}
}

static void parse_map(char *line, window_t *window)
{
	char **rows;
	int i;
	
	i = 0;
	rows = ft_split(line, ' ');
	if (!rows)
		error_exit("Failed to read the row");
	while (rows[i])
	{
		free(rows[i]);
		i++;
	}
	if (i != (int)window->row_check)
		error_exit("Map incorrect");
	free(rows);
}

static void	map_w_h_info(int fd, window_t *window, char **map_data)
{	
    char *line;
    char **rows;
	char *temp;

	temp = NULL;
    line = get_next_line(fd);
    if (!line)
	{
        error_exit("Failed to read the map1");
	}
	*map_data = ft_strdup(line);
    rows = ft_split(line, ' ');
	if (!rows)
		error_exit("Failed to read the row");
    while (rows[window->row_w])
    {
        free(rows[window->row_w]);
        window->row_w++;
    }
	window->row_check = window->row_w;
    while (line)
    {
		parse_map(line, window);
        free(line);
        window->row_h++;
        line = get_next_line(fd);
		if (!line)
			break;
		temp = *map_data;
		*map_data = ft_strjoin(temp, line);
		if (!*map_data)
		{
			free(temp);
			error_exit("Failed to store map");
		}
		free(temp);
    }
    free(line);
    free(rows);
}

void	open_map(int argc, char *argv[], window_t *window)
{
	int		fd;
	char	*path;
	char *map_data;

	map_data = NULL;
	path = NULL;
	window->row_h = 0;
	window->row_w = 0;
	window->row_check = 0;
	window->move.x = 0;
	window->move.y = 0;
	if (argc < 2 || !argv[1] || argc > 2)
		error_exit("Invalid arguments");
	path = ft_strjoin("./maps/", argv[1]);
	if (!path)
		error_exit("Path is NULL");
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		free(path);
		error_exit("Failed to open the file"); //check as well if file is .fdf format
	}
	map_w_h_info(fd, window, &map_data); //get w & h info and check map parse
	allocate_points(window); //allocate memory for points
	close(fd);
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		free(path);
		error_exit("Failed to open the file");
	}
	map_z_info(fd, map_data, window); //get z info from map AND put it to allocated memory
	free(map_data);
	free(path);
	close(fd);
}
