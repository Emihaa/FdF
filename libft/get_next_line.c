/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:27:36 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 20:27:48 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*loop_read(int fd, char *str, char **storage, char *tmp);
static int	check(char *str);

char	*get_next_line(int fd)
{
	static char	*storage;
	static char	buffer[BUFFER_SIZE];
	char		*tmp;
	char		*str;
	ssize_t		bytes_read;

	str = NULL;
	tmp = NULL;
	if (!storage)
		storage = ft_strdup("");
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer[0] = '\0';
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read >= 0)
		buffer[bytes_read] = '\0';
	if (bytes_read < 0)
		return (NULL);
	tmp = storage;
	storage = ft_strjoin(tmp, buffer);
	if (storage == NULL)
		return (NULL);
	return (loop_read(fd, str, &storage, tmp));
}

static void	loop(char **str, char **storage, char *tmp)
{
	*str = ft_substr((const char *)*storage, 0, (size_t)check(*storage));
	tmp = *storage;
	*storage = ft_substr((const char *)tmp, check(tmp), \
						ft_strlen((const char *)tmp) - check(tmp));
	free(tmp);
}

static char	*loop_read(int fd, char *str, char **storage, char *tmp)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		bytes_read;

	free(tmp);
	buffer[0] = '\0';
	while (check(*storage) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read >= 0)
			buffer[bytes_read] = '\0';
		tmp = *storage;
		*storage = ft_strjoin(tmp, buffer);
		if (!storage)
			return (NULL);
		free(tmp);
		if (bytes_read == 0)
		{
			str = ft_substr((const char *)*storage, 0, \
							ft_strlen((const char *)*storage));
			return (free(*storage), *storage = NULL, str);
		}
	}
	loop(&str, storage, tmp);
	return (str);
}

static int	check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] != '\n')
		return (-1);
	else
		i++;
	return (i);
}
