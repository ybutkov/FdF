/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:16:41 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/01 16:26:13 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "draw_internal.h"
#include "fdf.h"
#include "map.h"
#include "libft.h"
#include "utils.h"

static t_draw_line_delta	init_delta(t_point_2d from, t_point_2d to)
{
	t_draw_line_delta	delta;

	delta.dx = ft_abs(to.x - from.x);
	delta.dy = ft_abs(to.y - from.y);
	delta.sx = ft_sign(to.x - from.x);
	delta.sy = ft_sign(to.y - from.y);
	delta.err = delta.dx - delta.dy;
	return (delta);
}

void	draw_line(t_img *img, t_point_2d from, t_point_2d to)
{
	t_draw_line_delta	delta;

	delta = init_delta(from, to);
	while (1)
	{
		if (between(from.x, 0, WINDOW_WIDTH) && between(from.y, 0,
				WINDOW_HEIGHT))
			ft_mlx_pixel_put(img, from);
		if (from.x == to.x && from.y == to.y)
			break ;
		delta.err2 = delta.err * 2;
		if (delta.err2 > -delta.dy)
		{
			delta.err -= delta.dy;
			from.x += delta.sx;
		}
		if (delta.err2 < delta.dx)
		{
			delta.err += delta.dx;
			from.y += delta.sy;
		}
	}
}
