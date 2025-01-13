/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:35:13 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:52 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	int		total;
	char	*p;

	i = 0;
	total = nmemb * size;
	if (nmemb != 0 && total / nmemb != size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (ft_strdup(""));
	p = (char *) malloc(nmemb * size);
	if (!p)
		return (NULL);
	while (i < (nmemb * size))
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
