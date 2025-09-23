/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:18:38 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/23 19:34:23 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"
#include "hooks.h"
#include "keys.h"
#include "map.h"
#include "parcer.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

void	print_map(t_map *map)
{
	t_point	*point;

	if (!map || !map->points)
	{
		printf("Map is empty or NULL.\n");
		return ;
	}
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			point = map->get_point(map, x, y);
			if (point)
				printf("%3d(%#x)", point->z, point->color);
			else
				printf("(NULL) ");
		}
		printf("\n");
	}
}

t_point_2d iso_project(t_point_3d point)
{
	t_point_2d	result;
	float		angle;

	angle = 0.523599; // 30 градусов в радианах
	result.x = (point.x - point.y) * cos(angle);
	result.y = (point.x + point.y) * sin(angle) - point.z;
	return (result);
}

void rotate_x(t_point_3d *point, float angle)
{
	float	y;
	float	z;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	// y = point->y * cos_angle - point->z * sin_angle;
	// z = point->y * sin_angle + point->z * cos_angle;
	y = point->y * cos_angle - point->z * sin_angle;
	z = point->y * sin_angle + point->z * cos_angle;

	point->y = y;
	point->z = z;
}

void rotate_y(t_point_3d *point, float angle)
{
	float	x;
	float	z;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	// x = point->x * cos_angle + point->z * sin_angle;
	// z = -point->x * sin_angle + point->z * cos_angle;
	x = point->x * cos_angle + point->z * sin_angle;
	z = -point->x * sin_angle + point->z * cos_angle;

	point->x = x;
	point->z = z;
}

void rotate_z(t_point_3d *point, float angle)
{
	float	x;
	float	y;
	float	cos_angle;
	float	sin_angle;

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
	t_point_3d point_3d;

	point_3d.x = x * map->zoom;
	point_3d.y = y * map->zoom;
	point_3d.z = map->get_point(map, x, y)->z * map->z_scale;

	rotate_x(&point_3d, map->rotation_x);
	rotate_y(&point_3d, map->rotation_y);
	rotate_z(&point_3d, map->rotation_z);

	result = iso_project(point_3d);
	result.x = result.x + map->offset_x;
	result.y = result.y + map->offset_y;
	result.color = map->get_point(map, x, y)->color;
	return (result);
}

void clear_image(t_img *img)
{
	int	bytes_per_pixel;
	int	image_size;
	int	i;

	bytes_per_pixel = img->bits_per_pixel / 8;
	image_size = img->line_length * WINDOW_HEIGHT;
	i = 0;
	while (i < image_size)
	{
		img->addr[i] = 0;         // Blue
		img->addr[i + 1] = 0;     // Green
		img->addr[i + 2] = 0;     // Red
		if (bytes_per_pixel == 4)
			img->addr[i + 3] = 0; // Alpha (если используется)
		i += bytes_per_pixel;
	}
}	

void	render_map(t_app *app)
{
	t_point_2d	from;
	t_point_2d	right;
	t_point_2d	bottom;
	t_map		*map;

	clear_image(app->img);
	map = app->map;
	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
		{
			// from = project_iso(map, x, y);
			from = transform_point(map, x, y);
			if (x + 1 < map->width)
			{
				// right = project_iso(map, x + 1, y);
				right = transform_point(map, x + 1, y);
				draw_line(app->img, (t_point_2d){from.x, from.y, from.color},
					(t_point_2d){right.x, right.y, (from.color + right.color) / 2});
			}
			if (y + 1 < map->height)
			{
				// bottom = project_iso(map, x, y + 1);
				bottom = transform_point(map, x, y + 1);
				draw_line(app->img, (t_point_2d){from.x, from.y, from.color},
					(t_point_2d){bottom.x, bottom.y, (from.color + bottom.color) / 2});
			}
		}
	mlx_put_image_to_window(app->mlx, app->win, app->img->img, 0, 0);
}

void	set_default_zoom_offset(t_map *map)
{
	map->zoom = fmin(1.0 * WINDOW_WIDTH / map->width,
				1.0 * WINDOW_HEIGHT / map->height);
	// if (map->zoom < 1)
	map->zoom = map->zoom * 0.7f;
	map->offset_x = (int)((WINDOW_WIDTH - map->width * map->zoom)/2);
	map->offset_y = (int)((WINDOW_HEIGHT - map->height * map->zoom)/2);
}

void	init_camera(t_map *map)
{
	int		x, y;
	double	z_min = 1e9;
	double	z_max = -1e9;
	double	zoom_x, zoom_y, zoom_plane;
	double	width, height;
	// 1. Находим минимальную и максимальную высоту
	for (y = 0; y < map->height; y++)
	{
		for (x = 0; x < map->width; x++)
		{
			double z = transform_point(map, x, y).y;
			if (z < z_min) z_min = z;
			if (z > z_max) z_max = z;
		}
	}
	printf("z_min=%f, z_max=%f\n", z_min, z_max);
	map->zoom = 1.0;
	map->z_scale = 1.0;
	width = transform_point(map, map->width-1, 0).x - transform_point(map, 0, map->height-1).x;
	height = transform_point(map, map->width-1, map->height-1).y - transform_point(map, 0, 0).y;
	zoom_x = WINDOW_WIDTH / width;
	zoom_y = WINDOW_HEIGHT / height;
	zoom_plane = fmin(zoom_x, zoom_y) * 0.6;
	map->zoom = zoom_plane;
	if (z_max - z_min != 0)
		map->z_scale = fmin(zoom_plane / 4, (WINDOW_HEIGHT) / (z_max - z_min) / 4);
	else
		map->z_scale = 1.0;
	// map->z_scale = map->zoom / 4;
	// 4. Смещение для центрирования
	map->offset_x = (WINDOW_WIDTH  - width * map->zoom) / 2 +
		transform_point(map, 0, 0).x - transform_point(map, 0, map->height-1).x;
	map->offset_y = (WINDOW_HEIGHT - height * map->zoom) / 2;
}

void	init_mlx_window(t_map *map)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		exit_program(NULL);
	app->mlx = mlx_init();
	app->height = WINDOW_HEIGHT;
	app->width = WINDOW_WIDTH;
	app->win = mlx_new_window(app->mlx, app->width, app->height,
			"Hello world!");
	// mlx_hook(app->win, KEY_ESC, 0, close_window, app);
	mlx_hook(app->win, 2, 1L << 0, key_pressed_hook, app);
	app->img = (t_img *)malloc(sizeof(t_img));
	if (!app->img)
		exit_program(app);
	app->img->img = mlx_new_image(app->mlx, app->width, app->height);
	app->img->addr = mlx_get_data_addr(app->img->img, &(app->img->bits_per_pixel),
			&(app->img->line_length), &(app->img->endian));
	app->map = map;
	// set_default_zoom_offset(map);
	init_camera(map);
	printf("zoom: %f, offset_x=%d, offset_y=%d, z-scale=%f\n",
		map->zoom, map->offset_x, map->offset_y, map->z_scale);
	// map->zoom = 45;
	render_map(app);
	mlx_loop(app->mlx);
}

int	main(int argc, char const *argv[])
{
	t_map	*map;

	if (argc != 2)
		return (1);
	map = read_map_from_file(argv[1]);
	// print_map(map);
	init_mlx_window(map);
	(map->free(map), map = NULL);
	return (0);
}
