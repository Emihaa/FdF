/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:36:06 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/27 19:48:15 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkformat(char c)
{
	int		i;
	char	*s;

	s = "cspdiuxX%";
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	pointer(va_list args, int *counter)
{
	void	*p;

	p = va_arg(args, void *);
	if (p == NULL)
	{
		ft_putstr("(nil)", counter);
		return ;
	}
	ft_putstr("0x", counter);
	ft_putnbr_hex((unsigned long)p, "0123456789abcdef", counter);
}

static void	whichformat(char c, va_list args, int *counter)
{
	if (c == 'c')
		ft_putchar((char)va_arg(args, int), counter);
	if (c == 's')
		ft_putstr(va_arg(args, char *), counter);
	if (c == 'p')
		pointer(args, counter);
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), counter);
	if (c == 'u')
		ft_putnbr_un(va_arg(args, unsigned int), counter);
	if (c == 'x')
		ft_putnbr_hex(va_arg(args, unsigned int), "0123456789abcdef", counter);
	if (c == 'X')
		ft_putnbr_hex(va_arg(args, unsigned int), "0123456789ABCDEF", counter);
	if (c == '%')
		ft_putchar('%', counter);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			counter;

	va_start(args, str);
	counter = 0;
	while (*str && counter != -1)
	{
		if (*str == '%')
		{
			str++;
			if (checkformat(*str))
				whichformat(*str, args, &counter);
			else
				break ;
		}
		else
			ft_putchar(*str, &counter);
		str++;
	}
	va_end(args);
	return (counter);
}
