/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:55:11 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/29 18:40:00 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_internal.h"
#include <math.h>

static t_point_2d	iso_project(t_point_3d point)
{
	t_point_2d	result;
	double		angle;

	angle = 0.5235987756;
	result.x = (int)((point.x - point.y) * cos(angle));
	result.y = (int)((point.x + point.y) * sin(angle) - point.z);
	return (result);
}

static t_point_2d	parallel_project(t_point_3d point)
{
	t_point_2d	result;

	result.x = (int)round(point.x);
	result.y = (int)(point.y - point.z);
	return (result);
}

static void	rotate_coord(double *a, double *b, double angle)
{
	double	cos_angle;
	double	sin_angle;
	double	tmp_a;
	double	tmp_b;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	tmp_a = *a * cos_angle - *b * sin_angle;
	tmp_b = *a * sin_angle + *b * cos_angle;
	*a = tmp_a;
	*b = tmp_b;
}

t_point_2d	transform_point(t_map *map, int x, int y)
{
	t_point_2d	result;
	t_point_3d	point_3d;

	point_3d.x = x * map->zoom;
	point_3d.y = y * map->zoom;
	point_3d.z = map->get_point(map, x, y)->z * map->z_scale * map->zoom;
	rotate_coord(&point_3d.y, &point_3d.z, map->rotation_x);
	rotate_coord(&point_3d.x, &point_3d.z, map->rotation_y);
	rotate_coord(&point_3d.x, &point_3d.y, map->rotation_z);
	if (map->projection == PROJ_ISO)
		result = iso_project(point_3d);
	else if (map->projection == PROJ_PARALLEL)
		result = parallel_project(point_3d);
	else
		result = (t_point_2d){0, 0, 0};
	result.x = result.x + map->offset_x;
	result.y = result.y + map->offset_y;
	result.color = map->get_point(map, x, y)->color;
	return (result);
}

void	rotate_map(t_map *map, double x, double y, double z)
{
	map->rotation_x = normalize_angle(map->rotation_x + x);
	map->rotation_y = normalize_angle(map->rotation_y + y);
	map->rotation_z = normalize_angle(map->rotation_z + z);
}
