/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:26:07 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:13 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s) +1;
	p = malloc(len);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	return (p);
}
