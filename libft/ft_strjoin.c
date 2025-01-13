/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:48:27 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/09 18:37:37 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		len;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		len = (int)ft_strlen(s1);
	else if (!s1)
		len = (int)ft_strlen(s2);
	else
		len = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	while (i < len)
	{
		while (s1 && *s1 != '\0')
			s[i++] = *s1++;
		while (*s2 != '\0')
			s[i++] = *s2++;
	}
	s[i] = '\0';
	return (s);
}
