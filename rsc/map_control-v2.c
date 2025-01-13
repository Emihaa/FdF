/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control-v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:47:55 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/13 22:15:52 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Exit the program as failure.
static void	error_exit(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

static void hex_convert(char *str, window_t *screen, int i, int j)
{
	char *hex;
	int pos;
	unsigned int dec;
	int len;
	int val;

	dec = 0;
	pos = 0;
	val = 0;
	//check if the lenght is correct and give error if wrong
	hex = ft_strjoin(ft_strchr(str, 'x') + 1, "FF");
	len = ft_strlen(hex) - 1;
	if (len != 7)
		error_exit("wrong color hex");
	while (pos <= len)
	{	
		if (hex[pos] >= '0' && hex[pos] <= '9')
			val = val * hex[pos] - '0';
		else if (hex[pos] >= 'a' && hex[pos] <= 'f')
			val = hex[pos] - 'a' + 10;
		else if (hex[pos] >= 'A' && hex[pos]<= 'F')
			val = hex[pos] - 'A' + 10;
		dec = dec * 16 + val;
		pos++;
	}
	screen->vertex[i][j].color = dec;
	free(hex);
	// ft_printf("color %s\n", hex);
	// ft_printf("color %u\n", dec);
	// ft_printf("color %x\n", dec);
}

static void map_z_info(int fd, char *map_data, window_t *screen)
{
	char *line;
	char **rows;
	int i;
	int j;

	i = 0;
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		rows = ft_split(line, ' ');
		j = 0;
		while (rows[j])
		{
			screen->vertex[i][j].z = ft_atoi(rows[j]);	
			if (ft_strchr(rows[j], 'x') != NULL)
				hex_convert(rows[j], screen, i, j);
			free(rows[j]);
			j++;
		}
		free(rows);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	ft_printf("map:\n%s\n", map_data);
}

static void allocate_points(window_t *screen)
{
	int i = 0;
	
	screen->vertex = malloc(screen->row_h * sizeof(point_t *));
	if (!screen->vertex)
		error_exit("failed to allocate points");
	while (i < (int) screen->row_h)
	{
		screen->vertex[i] = malloc(screen->row_w * sizeof(point_t));
		if (!screen->vertex[i])
		{
			while (i >= 0)
			{
				free(screen->vertex[i]);
				i--;
			}
			free(screen->vertex);
			error_exit("failed to allocate points");
		}
		i++;
	}
}

static void parse_map(char *line, window_t *screen)
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
	if (i != (int)screen->row_check)
		error_exit("Map incorrect");
	free(rows);
}

static void	map_w_h_info(int fd, window_t *screen, char **map_data)
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
    while (rows[screen->row_w])
    {
        free(rows[screen->row_w]);
        screen->row_w++;
    }
	screen->row_check = screen->row_w;
    while (line)
    {
		parse_map(line, screen);
        free(line);
        screen->row_h++;
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

void	open_map(int argc, char *argv[], window_t *screen)
{
	int		fd;
	char	*path;
	char *map_data;

	map_data = NULL;
	path = NULL;
	screen->row_h = 0;
	screen->row_w = 0;
	screen->row_check = 0;
	if (argc < 2 || !argv[1] || argc > 2)
		error_exit("Invalid arguments");
	path = ft_strjoin("./maps/", argv[1]);
	if (!path)
		error_exit("Path is NULL");
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		free(path);
		error_exit("Failed to open the file");
	}
	map_w_h_info(fd, screen, &map_data); //get w & h info and check map parse
	allocate_points(screen); //allocate memory for points
	close(fd);
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		free(path);
		error_exit("Failed to open the file");
	}
	map_z_info(fd, map_data, screen); //get z info from map AND put it to allocated memory
	free(map_data);
	free(path);
	close(fd);
}
