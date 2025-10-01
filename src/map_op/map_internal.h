/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:56:13 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/29 18:39:54 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_INTERNAL_H
# define MAP_INTERNAL_H

# include "map.h"
# include "point.h"

t_point		*get_point(t_map *map, int x, int y);
void		set_point(t_map *map, int x, int y, t_point point);
void		shift(t_map *map, int x, int y);
void		zoom_in(t_map *map, int percent);
t_point_2d	transform_point(t_map *map, int x, int y);
double		normalize_angle(double angle);
void		rotate_map(t_map *map, double x, double y, double z);

#endif