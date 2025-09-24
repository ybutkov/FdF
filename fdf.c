/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:18:38 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/24 16:29:51 by ybutkov          ###   ########.fr       */
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

void print_point(t_point_2d point)
{
	printf("Point2D: x=%d, y=%d, color=%#x\n", point.x, point.y, point.color);
}

void	init_mlx_window(t_map *map, char *title)
{
	t_app	*app;

	app = create_app(map, title);
	if (!app)
		exit_program(NULL);
	app->render(app);
	mlx_loop(app->mlx);
}

int	main(int argc, char const *argv[])
{
	t_map	*map;

	if (argc != 2)
		return (1);
	map = read_map_from_file(argv[1]);
	// print_map(map);
	init_mlx_window(map, (char *)argv[1]);
	(map->free(map), map = NULL);
	return (0);
}
