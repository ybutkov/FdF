/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:14:29 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/23 12:21:42 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "draw.h"

void draw_circle(t_img *img, t_point_2d point, int radius, int color)
{
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		// Draw the eight octants
		ft_mlx_pixel_put(img, (t_point_2d){point.x + x, point.y + y, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x + y, point.y + x, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x - y, point.y + x, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x - x, point.y + y, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x - x, point.y - y, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x - y, point.y - x, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x + y, point.y - x, color});
		ft_mlx_pixel_put(img, (t_point_2d){point.x + x, point.y - y, color});

		y += 1;
		if (err <= 0)
		{
			err += 2 * y + 1;
		}
		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}
