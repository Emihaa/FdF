/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:50:06 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:29 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	char			*sh;
	char			ch;

	i = 0;
	sh = s;
	ch = c;
	while (i != n)
	{
		sh[i] = ch;
		i++;
	}
	return (s);
}
