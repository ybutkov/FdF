/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:04:53 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/03 16:26:50 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map.h"

void	ft_mlx_pixel_put(t_img *img, t_point_2d point)
{
	char	*dst;

	if (point.x >= 0 && point.x < WINDOW_WIDTH && point.y >= 0
		&& point.y < WINDOW_HEIGHT)
	{
		dst = img->addr + (point.y * img->line_length + point.x
				* (img->bits_per_pixel / 8));
		dst[0] = (point.color) & 0xFF;
		dst[1] = (point.color >> 8) & 0xFF;
		dst[2] = (point.color >> 16) & 0xFF;
		dst[3] = 0;
	}
}
