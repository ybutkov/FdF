/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:18:38 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/21 19:50:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"
#include "map.h"
#include "parcer.h"
#include "hooks.h"
#include "keys.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

t_point_2d project_iso(t_map *map, int x, int y)
{
	t_point		*point;
	t_point_2d	result;
	float		angle;

	angle = 0.523599;
	point = map->get_point(map, x, y);
	if (!point)
		return ((t_point_2d){0, 0, 0});
	result.x = (x - y) * cos(angle) * map->zoom + map->offset_x;
	result.y = (x + y) * sin(angle) * map->zoom - point->z * map->z_scale
		* map->zoom + map->offset_y;
	result.color = point->color;
	return (result);
}

void	draw_map(t_app app, t_map *map)
{
	t_point_2d	from;
	t_point_2d	right;
	t_point_2d	bottom;

	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
		{
			// from = (t_point_2d){x * map->zoom + map->offset_x, y * map->zoom
			// 	+ map->offset_y, map->get_point(map, x, y)->color};
			from = project_iso(map, x, y);
			if (x + 1 < map->width)
			{
				// right = (t_point_2d){(x + 1) * map->zoom + map->offset_x, y
				// 	* map->zoom + map->offset_y, map->get_point(map, x + 1,
				// 		y)->color};
				right = project_iso(map, x + 1, y);
				draw_line(&app.img, (t_point_2d){from.x, from.y, from.color},
					(t_point_2d){right.x, right.y, right.color});

			}
			if (y + 1 < map->height)
			{
				// bottom = (t_point_2d){x * map->zoom + map->offset_x, (y + 1)
				// 	* map->zoom + map->offset_y, map->get_point(map, x, y
				// 		+ 1)->color};
				bottom = project_iso(map, x, y + 1);
				draw_line(&app.img, (t_point_2d){from.x, from.y, from.color},
					(t_point_2d){bottom.x, bottom.y, bottom.color});
			}
		}
}

void	init_mlx_window(t_map *map)
{
	t_app	app;

	app.mlx = mlx_init();
	app.height = WINDOW_HEIGHT;
	app.width = WINDOW_WIDTH;
	app.win = mlx_new_window(app.mlx, app.width, app.height, "Hello world!");
	mlx_hook(app.win, KEY_ESC, 0, close_window, &app);
	mlx_hook(app.win, 2, 1L << 0, key_pressed_hook, &app);
	app.img.img = mlx_new_image(app.mlx, app.width, app.height);
	app.img.addr = mlx_get_data_addr(app.img.img, &app.img.bits_per_pixel,
			&app.img.line_length, &app.img.endian);
	draw_map(app, map);
	mlx_put_image_to_window(app.mlx, app.win, app.img.img, 0, 0);
	mlx_loop(app.mlx);
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
