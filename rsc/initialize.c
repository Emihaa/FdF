/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:43:59 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/01/22 20:31:30 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	initiliaze(window_t *window)
{
	window->row_h = 0;
	window->row_w = 0;
	window->row_check = 0;
	window->move.x = 0;
	window->move.y = 0;
	window->max_z = 1;
	window->min_z = -1;
	window->scale.scale_z = 1;
	window->scale.scale_xy = 0;
	window->rotate.rotate_x = 0.5;
	window->rotate.rotate_y = 0.5;
    
}
