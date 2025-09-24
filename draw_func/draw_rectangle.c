/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:33:43 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/24 17:42:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw.h"
#include "point.h"

void	draw_rectangle(t_img *img, t_point_2d left_top, t_point_2d bottom_right,
		int color)
{
	t_point_2d	current;
	int			x;
	int			y;

	y = left_top.y;
	while (y <= bottom_right.y)
	{
		x = left_top.x;
		while (x < bottom_right.x)
		{
			current = (t_point_2d){x, y, color};
			ft_mlx_pixel_put(img, current);
			x++;
		}
		y++;
	}
}
