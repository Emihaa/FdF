/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:22:12 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:23 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write( char *buffer, int i, int n, int fd)
{
	while (n > 0)
	{
		buffer[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	buffer[i] = '\0';
	i--;
	while (i >= 0)
	{
		write(fd, &buffer[i], 1);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[12];
	int		i;

	i = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	ft_write(buffer, i, n, fd);
}
