/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:23:59 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:31 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	const char		*temp_src;
	char			*temp_dest;

	i = 0;
	if (!dest && !src)
		return (NULL);
	temp_src = src;
	temp_dest = dest;
	if (dest > src)
	{
		while (n-- > 0)
			temp_dest[n] = temp_src[n];
	}
	else
	{
		while (i < n)
		{
			temp_dest[i] = temp_src[i];
			i++;
		}
	}
	return (dest);
}
