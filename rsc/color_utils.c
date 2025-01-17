/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:04:00 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/16 18:04:11 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"


//the order is ARGB

uint8_t	get_r(uint32_t rgba)
{
	return ((rgba >> 16) & 0xFF);
}

uint8_t	get_g(uint32_t rgba)
{
	return ((rgba >> 8) & 0xFF);
}

uint8_t	get_b(uint32_t rgba)
{
	return (rgba & 0xFF);
}

uint8_t	get_a(uint32_t rgba)
{
	return ((rgba >> 24) & 0xFF);
}

uint8_t	get_r_invert(uint32_t rgba)
{
	return ((rgba >> 24) & 0xFF);
}

uint8_t	get_g_invert(uint32_t rgba)
{
	return ((rgba >> 16) & 0xFF);
}

uint8_t	get_b_invert(uint32_t rgba)
{
	return ((rgba >> 8) & 0xFF);
}

uint8_t	get_a_invert(uint32_t rgba)
{
	return (rgba & 0xFF);
}

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}