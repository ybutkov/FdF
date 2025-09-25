/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:16:41 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/25 18:58:15 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"
#include "map.h"
#include "utils.h"
#include <math.h>

void	draw_line(t_img *img, t_point_2d from, t_point_2d to)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	// if (from.x >= 0 && from.x < WINDOW_WIDTH && from.y >= 0
	// 	&& from.y < WINDOW_HEIGHT)
	// 	draw_circle(img, from, 4, from.color);
	dx = ft_abs(to.x - from.x);
	dy = ft_abs(to.y - from.y);
	sx = ft_sign(to.x - from.x);
	sy = ft_sign(to.y - from.y);
	err = dx - dy;
	while (1)
	{
		if (from.x >= 0 && from.x < WINDOW_WIDTH && from.y >= 0
			&& from.y < WINDOW_HEIGHT)
			ft_mlx_pixel_put(img, from);
		if (from.x == to.x && from.y == to.y)
			break ;
		err2 = err * 2;
		if (err2 > -dy)
		{
			err -= dy;
			from.x += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			from.y += sy;
		}
	}
	// if (to.x >= 0 && to.x < WINDOW_WIDTH && to.y >= 0 && to.y < WINDOW_HEIGHT)
	// 	draw_circle(img, to, 4, to.color);
}
