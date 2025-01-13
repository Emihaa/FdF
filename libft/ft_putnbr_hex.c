/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:30:07 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/09 20:07:27 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hex(unsigned long n, const char *base, int *counter)
{
	char	hex[20];
	int		i;

	i = 0;
	if (n == 0)
	{
		ft_putchar('0', counter);
		return ;
	}
	while (n > 0)
	{
		hex[i] = base[n % 16];
		n = n / 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		ft_putchar(hex[i], counter);
	}
}
