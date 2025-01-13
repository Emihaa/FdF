/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:00:57 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:37:52 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char		cc;
	const char	*p;

	i = 0;
	cc = (char) c;
	p = s;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			p = &s[i];
		i++;
	}
	if (p == s && cc == '\0')
		return ((char *) &s[i]);
	if (*p == cc)
		return ((char *) p);
	return (NULL);
}
