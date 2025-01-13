/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:25:44 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/09 20:07:24 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_values(long *nb, int *counter)
{
	if (*nb == 0)
		ft_putchar('0', counter);
	return (*nb);
}

static void	print_nbrs(char *str, int count, long *nb, int *counter)
{
	int	i;

	i = 0;
	while (count != 0)
	{
		str[i] = *nb % 10 + '0';
		*nb = *nb / 10;
		i++;
		count--;
	}
	while (i > 0)
	{
		i--;
		ft_putchar(str[i], counter);
	}
}

void	ft_putnbr_un(unsigned int nb, int *counter)
{
	long		d;
	long		value;
	int			count;
	char		str[25];

	count = 0;
	d = (long) nb;
	value = (long) nb;
	check_values (&value, counter);
	while (d != 0)
	{
		d = d / 10;
		count++;
	}
	print_nbrs (str, count, &value, counter);
}
