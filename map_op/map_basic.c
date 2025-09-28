/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:53:52 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 15:18:41 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"

t_point	*get_point(t_map *map, int x, int y)
{
	if (!map || x >= map->width || y >= map->height)
		return (NULL);
	return (&map->points[y * map->width + x]);
}

void	set_point(t_map *map, int x, int y, t_point point)
{
	t_point	*target;

	if (!map || x >= map->width || y >= map->height)
		return ;
	target = &map->points[y * map->width + x];
	*target = point;
}

void	shift(t_map *map, int x, int y)
{
	map->offset_x += x;
	map->offset_y += y;
}

void	zoom_in(t_map *map, int percent)
{
	if (percent == 0)
		return ;
	map->zoom *= (1.0 + percent / 100.0);
	if (map->zoom < 1.0)
		map->zoom = 1.0;
}
