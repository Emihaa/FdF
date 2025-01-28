/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:26:42 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/14 12:19:27 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstrs(char const *s, char c)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static int	ft_countlen(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static void	ft_freeall(int i, char **strarray)
{
	while (i >= 0)
	{
		free(strarray[i]);
		i++;
	}
	free(strarray);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strcount;
	char	**strarray;

	i = 0;
	strcount = ft_countstrs(s, c);
	strarray = (char **) malloc((strcount + 1) * sizeof(char *));
	if (!strarray)
		return (NULL);
	while (i < strcount)
	{
		while (*s == c)
			s++;
		strarray[i] = ft_substr(s, 0, (size_t)(ft_countlen(s, c)));
		if (!strarray[i])
		{
			ft_freeall(i, strarray);
			return (NULL);
		}
		s = s + (ft_countlen(s, c));
		i++;
	}
	strarray[i++] = NULL;
	return (strarray);
}
