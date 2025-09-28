/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:03:00 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 15:18:18 by ybutkov          ###   ########.fr       */
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

static void	set_rotation(struct s_map *map, double x, double y, double z)
{
	map->rotation_x = x;
	map->rotation_y = y;
	map->rotation_z = z;
}

static void	find_z_extrenum(t_map *map, double *z_min, double *z_max)
{
	int		x;
	int		y;
	double	z;

	*z_min = 1e9;
	*z_max = -1e9;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->get_point(map, x, y)->z;
			if (z < *z_min)
				*z_min = z;
			if (z > *z_max)
				*z_max = z;
			x++;
		}
		y++;
	}
}

static void	reset_map_transformations(t_map *map)
{
	double	z_min;
	double	z_max;
	double	width;
	double	height;

	map->set_rotation(map, 0, 0, 0);
	map->zoom = 1.0;
	map->z_scale = 1.0;
	width = map->transform_point(map, map->width - 1, 0).x
		- map->transform_point(map, 0, map->height - 1).x;
	height = map->transform_point(map, map->width - 1, map->height - 1).y
		- map->transform_point(map, 0, 0).y;
	map->zoom = round(fmin((WINDOW_WIDTH - INFO_PANEL_WIDTH) / width,
				WINDOW_HEIGHT / height) * 0.6 * 100) / 100;
	find_z_extrenum(map, &z_min, &z_max);
	if (z_max - z_min != 0)
		map->z_scale = round(fmin(map->zoom, (WINDOW_HEIGHT) / (z_max - z_min))
				/ map->zoom / 8 * 100) / 100;
	else
		map->z_scale = 1.0;
	map->offset_x = INFO_PANEL_WIDTH / 2 + (WINDOW_WIDTH - width * map->zoom)
		/ 2 + map->transform_point(map, 0, 0).x - map->transform_point(map, 0,
			map->height - 1).x;
	map->offset_y = (WINDOW_HEIGHT - height * map->zoom) / 2;
	map->is_change = 1;
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
