/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:04:51 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/22 20:19:28 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t get_gradient(uint32_t color_s, uint32_t color_d, int len, int point)
{
		float ratio;
		int red;
		int green;
		int blue;

		if (len == 0)
			return (color_s);
		ratio = (float)point / (float)len;		
		red = (int)((1 - ratio) * (get_r_invert(color_s)) + (ratio * (get_r_invert(color_d))));
		green = (int)((1 - ratio) * (get_g_invert(color_s)) + (ratio * (get_g_invert(color_d))));
		blue = (int)((1 - ratio) * (get_b_invert(color_s)) + (ratio * (get_b_invert(color_d))));				
		return (get_rgba((uint8_t)red, (uint8_t)green, (uint8_t)blue, 255));
}

void	hex_convert(char *str, window_t *window, int i, int j)
{
	int				pos;
	unsigned int	dec;
	int				len;
	int				val;

	dec = 0;
	pos = 0;
	val = 0;
	len = ft_strlen(str) - 1;
	while (pos <= len)
	{	
		if (str[pos] >= '0' && str[pos] <= '9')
			val = str[pos] - '0';
		else if (str[pos] >= 'a' && str[pos] <= 'f')
			val = str[pos] - 'a' + 10;
		else if (str[pos] >= 'A' && str[pos] <= 'F')
			val = str[pos] - 'A' + 10;
		else
			ft_error();
		dec = dec * 16 + val;
		pos++;
	}
	window->points[i][j].hex_color = \
		get_rgba(get_r(dec), get_g(dec), get_b(dec), 255);
}

uint32_t	base_colors(window_t *window, int i, int j)
{
	uint32_t	color;
	int			max_top;
	int			max_bot;

	color = DEFAULT_COLOR;
	max_top = window->max_z + 1;
	max_bot = window->min_z - 1;
	if (window->points[i][j].z > 0)
		color = get_gradient(DEFAULT_COLOR, DEFAULT_TOP, max_top, \
							window->points[i][j].z - max_top);
	else if (window->points[i][j].z < 0)
		color = get_gradient(DEFAULT_COLOR, DEFAULT_BOTTOM, max_bot, \
							window->points[i][j].z - max_bot);
	return (color);
}
