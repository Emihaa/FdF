/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:01:00 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:32 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*string1;
	const char		*string2;

	i = 0;
	string1 = dest;
	string2 = src;
	while (i != n)
	{
		string1[i] = string2[i];
		i++;
	}
	return (dest);
}
