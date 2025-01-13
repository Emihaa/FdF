/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:57:42 by ehaanpaa          #+#    #+#             */
/*   Updated: 2024/11/15 14:38:38 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		n = n * -1;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_strswap(char *s)
{
	int		i;
	int		max;
	int		end;
	char	temp;

	i = 0;
	max = ft_strlen(s);
	end = max - 1;
	while (i < max / 2)
	{
		temp = s[i];
		s[i] = s[end];
		s[end] = temp;
		i++;
		end--;
	}
	return (s);
}

static void	ft_addstr(char *s, int n)
{
	int	i;
	int	nb;

	i = 0;
	nb = n;
	if (n < 0)
		nb = nb * -1;
	while (i < ft_countlen(n) + 1 + (n < 0) - 1)
	{
		if (i == 0 && n < 0)
			s[0] = '-';
		else
		{
			s[i] = nb % 10 + '0';
			nb = nb / 10;
		}
		i++;
	}
	s[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	if (n == 0)
	{
		s = malloc(2);
		if (!s)
			return (NULL);
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = malloc(ft_countlen(n) + 1 + (n < 0));
	if (!s)
		return (NULL);
	ft_addstr(s, n);
	ft_strswap(s + (s[0] == '-'));
	return (s);
}
