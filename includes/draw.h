/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:06:56 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/23 12:17:27 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "map.h"

void	ft_mlx_pixel_put(t_img *img, t_point_2d point);
void	draw_line(t_img *img, t_point_2d from, t_point_2d to);
void	draw_circle(t_img *img, t_point_2d point, int radius, int color);

#endif