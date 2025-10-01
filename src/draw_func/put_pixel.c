/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:04:53 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 15:22:59 by ybutkov          ###   ########.fr       */
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
		*(unsigned int *)dst = point.color;
	}
}
