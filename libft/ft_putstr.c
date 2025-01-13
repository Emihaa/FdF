/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:09 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/09 20:07:17 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str, int *counter)
{
	int		i;
	char	*s;

	s = "(null)";
	i = 0;
	if (!str)
	{
		while (s[i] != '\0' && *counter != -1)
		{
			ft_putchar(s[i], counter);
			i++;
		}
		return ;
	}
	while (str[i] != '\0' && *counter != -1)
	{
		ft_putchar(str[i], counter);
		i++;
	}
}
