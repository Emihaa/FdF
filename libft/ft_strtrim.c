/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:11:50 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:37:49 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trim_set(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (*s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		i;
	int		end;
	int		start;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_trim_set(&s1[start], set))
		start++;
	while (end >= start && ft_trim_set(&s1[end], set))
		end--;
	s = malloc(end - start + 2);
	if (!s)
		return (NULL);
	while (start <= end)
	{
		s[i++] = s1[start++];
	}
	s[i] = '\0';
	return (s);
}
