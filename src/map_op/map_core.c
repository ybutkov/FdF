/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:03:00 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/02 18:13:54 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map_internal.h"
#include <math.h>

static void	free_map(t_map *map)
{
	free(map->points);
	free(map);
}

void	set_rotation(struct s_map *map, double x, double y, double z)
{
	map->rotation_x = x;
	map->rotation_y = y;
	map->rotation_z = z;
}

t_map	*create_map(size_t width, size_t height)
{
	t_map	*map;

	if (width <= 0 || height <= 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->points = (t_point *)malloc(sizeof(t_point) * width * height);
	if (!map->points)
		return (free(map), NULL);
	map->projection = PROJ_ISO;
	map->shift_size = SHIFT_SIZE;
	map->zoom_size = ZOOM_SIZE_PERCENT;
	map->free = free_map;
	map->reset = reset_map_transformations;
	map->get_point = get_point;
	map->set_point = set_point;
	map->transform_point = transform_point;
	map->set_rotation = set_rotation;
	map->rotate = rotate_map;
	map->shift = shift;
	map->zoom_in = zoom_in;
	return (map);
}
