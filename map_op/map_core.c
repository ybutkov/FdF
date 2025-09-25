/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:03:00 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/25 18:43:22 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	free_map(t_map *map)
{
	free(map->points);
	free(map);
}

t_point_2d	iso_project(t_point_3d point)
{
	t_point_2d	result;
	double		angle;

	angle = 0.523599; // 30 градусов в радианах
	result.x = (point.x - point.y) * cos(angle);
	result.y = (point.x + point.y) * sin(angle) - point.z;
	return (result);
}

void	rotate_x(t_point_3d *point, double angle)
{
	double	y;
	double	z;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	// y = point->y * cos_angle - point->z * sin_angle;
	// z = point->y * sin_angle + point->z * cos_angle;
	y = point->y * cos_angle - point->z * sin_angle;
	z = point->y * sin_angle + point->z * cos_angle;
	point->y = y;
	point->z = z;
}

void	rotate_y(t_point_3d *point, double angle)
{
	double	x;
	double	z;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	// x = point->x * cos_angle + point->z * sin_angle;
	// z = -point->x * sin_angle + point->z * cos_angle;
	x = point->x * cos_angle + point->z * sin_angle;
	z = -point->x * sin_angle + point->z * cos_angle;
	point->x = x;
	point->z = z;
}

void	rotate_z(t_point_3d *point, double angle)
{
	double	x;
	double	y;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	x = point->x * cos_angle - point->y * sin_angle;
	y = point->x * sin_angle + point->y * cos_angle;
	point->x = x;
	point->y = y;
}

t_point_2d	transform_point(t_map *map, int x, int y)
{
	t_point_2d	result;
	t_point_3d	point_3d;

	point_3d.x = x * map->zoom;
	point_3d.y = y * map->zoom;
	point_3d.z = map->get_point(map, x, y)->z * map->z_scale * map->zoom;
	rotate_x(&point_3d, map->rotation_x);
	rotate_y(&point_3d, map->rotation_y);
	rotate_z(&point_3d, map->rotation_z);
	result = iso_project(point_3d);
	// result = (t_point_2d){point_3d.x, point_3d.y, 0};
	result.x = result.x + map->offset_x;
	result.y = result.y + map->offset_y;
	result.color = map->get_point(map, x, y)->color;
	return (result);
}

void	set_rotation(struct s_map *map, double x, double y, double z)
{
	map->rotation_x = x;
	map->rotation_y = y;
	map->rotation_z = z;
}

void	reset_map_transformations(t_map *map)
{
	double	z_min;
	double	z_max;
	double	z;

	int x, y;
	z_min = 1e9;
	z_max = -1e9;
	map->set_rotation(map, 0, 0, 0);
	map->zoom = 1.0;
	map->z_scale = 1.0;
	double zoom_x, zoom_y, zoom_plane;
	double width, height;
	// 1. Находим минимальную и максимальную высоту
	for (y = 0; y < map->height; y++)
	{
		for (x = 0; x < map->width; x++)
		{
			z = map->transform_point(map, x, y).y;
			if (z < z_min)
				z_min = z;
			if (z > z_max)
				z_max = z;
		}
	}
	width = map->transform_point(map, map->width - 1, 0).x
		- map->transform_point(map, 0, map->height - 1).x;
	height = map->transform_point(map, map->width - 1, map->height - 1).y
		- map->transform_point(map, 0, 0).y;
	zoom_x = (WINDOW_WIDTH - INFO_PANEL_WIDTH) / width;
	zoom_y = WINDOW_HEIGHT / height;
	zoom_plane = round(fmin(zoom_x, zoom_y) * 0.6 * 100) / 100;
	map->zoom = zoom_plane;
	if (z_max - z_min != 0)
		map->z_scale = round(fmin(zoom_plane, (WINDOW_HEIGHT) / (z_max - z_min))
			/ zoom_plane / 8 * 100) / 100;
	else
		map->z_scale = 1.0;
	map->offset_x = INFO_PANEL_WIDTH/2 + (WINDOW_WIDTH - width * map->zoom) / 2
		+ map->transform_point(map, 0, 0).x - map->transform_point(map, 0,
			map->height - 1).x;
	map->offset_y = (WINDOW_HEIGHT - height * map->zoom) / 2;
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

static double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle > M_PI)
		angle -= 2 * M_PI;
	else if (angle < -M_PI)
		angle += 2 * M_PI;
	return (angle);
}

static void rotate_map(t_map *map, double x, double y, double z)
{
	map->rotation_x = normalize_angle(map->rotation_x + x);
	map->rotation_y = normalize_angle(map->rotation_y + y);
	map->rotation_z = normalize_angle(map->rotation_z + z);
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
	map->zoom = 1.0;
	map->rotation_x = 0.0;
	map->rotation_y = 0.0;
	map->offset_x = 0;
	map->offset_y = 0;
	map->free = free_map;
	map->reset = reset_map_transformations;
	map->get_point = get_point;
	map->set_point = set_point;
	map->transform_point = transform_point;
	map->set_rotation = set_rotation;
	map->rotate = rotate_map;
	return (map);
}
