/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:42:40 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/09 19:04:40 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	substr = NULL;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s) || len == 0)
	{
		return (NULL);
	}
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (i < len && s[(size_t)start + i] != '\0')
	{
		substr[i] = s[(size_t)start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
