/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:18:38 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/02 15:50:05 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"
#include "hooks.h"
#include "keys.h"
#include "map.h"
#include "parcer.h"
#include "utils.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	exit_program(t_map *map, char *message)
{
	if (map)
		map->free(map);
	perror(message);
	exit(EXIT_FAILURE);
}

static int	loop_hook(t_app *app)
{
	long int	current_time;

	current_time = get_time_in_milliseconds();
	if ((current_time - app->last_frame_time < MIN_TIME_FRAMES)
		|| !app->map->is_change)
		return (0);
	app->render(app);
	return (0);
}

static t_app	*init_app(t_map *map, char *title)
{
	t_app	*app;

	app = create_app(map);
	if (!app)
		exit_program(map, "Error creating application");
	app->key_actions = init_key_actions();
	if (!app->key_actions)
		exit_program(map, "Error initializing key actions");
	app->mlx = mlx_init();
	app->win = mlx_new_window(app->mlx, app->width, app->height, title);
	app->img->img = mlx_new_image(app->mlx, app->width, app->height);
	app->img->addr = mlx_get_data_addr(app->img->img,
			&(app->img->bits_per_pixel), &(app->img->line_length),
			&(app->img->endian));
	mlx_hook(app->win, 17, 0, close_window, app);
	mlx_hook(app->win, 2, 1L << 0, key_pressed_hook, app);
	mlx_hook(app->win, 4, 1L << 2, ft_mouse_press, app);
	mlx_hook(app->win, 6, 1L << 6, ft_mouse_move, app);
	mlx_hook(app->win, 5, 1L << 3, ft_mouse_release, app);
	mlx_loop_hook(app->mlx, loop_hook, app);
	return (app);
}

int	main(int argc, char const *argv[])
{
	t_map	*map;
	t_app	*app;

	if (argc != 2)
		exit_program(NULL, "Error. There should be one argument - file name");
	map = read_map_from_file(argv[1]);
	if (!map)
		exit_program(NULL, "Error reading map from file");
	app = init_app(map, (char *)argv[1]);
	mlx_loop(app->mlx);
	return (0);
}
