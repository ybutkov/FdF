/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:03:00 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/21 16:32:28 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_map(t_map *map)
{
	free(map->points);
	free(map);
}

static void	reset_map_transformations(t_map *map)
{
	map->zoom = 1.0f;
	map->rotation_x = 0.0f;
	map->rotation_y = 0.0f;
	map->offset_x = 0;
	map->offset_y = 0;
}

static t_point	*get_point(t_map *map, int x, int y)
{
	if (!map || x >= map->width || y >= map->height)
		return (NULL);
	return (&map->points[y * map->width + x]);
}

static void	set_point(t_map *map, int x, int y, t_point point)
{
	t_point	*target;

	if (!map || x >= map->width || y >= map->height)
		return ;
	target = &map->points[y * map->width + x];
	*target = point;
}

t_map	*create_map(size_t width, size_t height)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->points = (t_point *)malloc(sizeof(t_point) * width * height);
	if (!map->points)
	{
		free(map);
		return (NULL);
	}
	map->zoom = 1.0f;
	map->rotation_x = 0.0f;
	map->rotation_y = 0.0f;
	map->offset_x = 0;
	map->offset_y = 0;
	map->free = free_map;
	map->reset = reset_map_transformations;
	map->get_point = get_point;
	map->set_point = set_point;
	return (map);
}
