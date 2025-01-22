/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_invert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:03 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/22 16:56:20 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
