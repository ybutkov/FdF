/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:42:48 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/24 18:06:30 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fdf.h"
#include "hooks.h"
#include "map.h"
#include "point.h"

void	free_app(t_app *app)
{
	if (!app)
		return ;
	if (app->img)
	{
		if (app->img->img)
			mlx_destroy_image(app->mlx, app->img->img);
		free(app->img);
	}
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->map)
		app->map->free(app->map);
	if (app->mlx)
	{
		// No explicit mlx_destroy function for mlx_ptr in MinilibX
		// But if there were resources to free, they would be handled here
	}
	free(app);
}

void	clear_image(t_img *img)
{
	int	bytes_per_pixel;
	int	image_size;
	int	i;

	bytes_per_pixel = img->bits_per_pixel / 8;
	image_size = img->line_length * WINDOW_HEIGHT;
	i = 0;
	while (i < image_size)
	{
		img->addr[i] = 0;     // Blue
		img->addr[i + 1] = 0; // Green
		img->addr[i + 2] = 0; // Red
		if (bytes_per_pixel == 4)
			img->addr[i + 3] = 0; // Alpha (если используется)
		i += bytes_per_pixel;
	}
}

void draw_info_panel(t_app *app)
{
	draw_rectangle(app->img, (t_point_2d){0, 0, 0x202020},
		(t_point_2d){500, app->height-1, 0x0000FF}, 0x202020);
}

void print_info_panel(t_app *app)
{
	mlx_string_put(app->mlx, app->win, 100, 100, 0xFFFFFF, "Rotation X: W/S");
	mlx_string_put(app->mlx, app->win, 100, 130, 0xFFFFFF, "Rotation Y: A/D");
	mlx_string_put(app->mlx, app->win, 100, 160, 0xFFFFFF, "Rotation Z: Z/X");
	mlx_string_put(app->mlx, app->win, 100, 190, 0xFFFFFF, "Zoom: +/-");
	mlx_string_put(app->mlx, app->win, 100, 220, 0xFFFFFF, "Z Scale: Q/E");
	mlx_string_put(app->mlx, app->win, 100, 250, 0xFFFFFF, "Move: Arrows");
	mlx_string_put(app->mlx, app->win, 100, 280, 0xFFFFFF, "Reset: R");
	mlx_string_put(app->mlx, app->win, 100, 310, 0xFFFFFF, "Top View: T");
	mlx_string_put(app->mlx, app->win, 100, 340, 0xFFFFFF, "Iso View: I");
	mlx_string_put(app->mlx, app->win, 100, 370, 0xFFFFFF, "Front View: Y");
}

void	render_map(t_app *app)
{
	t_point_2d	from;
	t_point_2d	right;
	t_point_2d	bottom;
	t_map		*map;

	app->clear_image(app->img);
	map = app->map;
	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
		{
			from = map->transform_point(map, x, y);
			if (x + 1 < map->width)
			{
				right = map->transform_point(map, x + 1, y);
				draw_line(app->img, (t_point_2d){from.x, from.y, from.color},
					(t_point_2d){right.x, right.y, (from.color + right.color)
					/ 2});
			}
			if (y + 1 < map->height)
			{
				bottom = map->transform_point(map, x, y + 1);
				draw_line(app->img, (t_point_2d){from.x, from.y, from.color},
					(t_point_2d){bottom.x, bottom.y, (from.color + bottom.color)
					/ 2});
			}
		}
	draw_info_panel(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img, 0, 0);
	print_info_panel(app);
}

t_app	*create_app(t_map *map, char *title)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		exit_program(NULL);
	app->mlx = mlx_init();
	app->height = WINDOW_HEIGHT;
	app->width = WINDOW_WIDTH;
	app->win = mlx_new_window(app->mlx, app->width, app->height, title);
	// mlx_hook(app->win, KEY_ESC, 0, close_window, app);
	mlx_hook(app->win, 2, 1L << 0, key_pressed_hook, app);
	app->img = (t_img *)malloc(sizeof(t_img));
	if (!app->img)
		exit_program(app);
	app->img->img = mlx_new_image(app->mlx, app->width, app->height);
	app->img->addr = mlx_get_data_addr(app->img->img,
			&(app->img->bits_per_pixel), &(app->img->line_length),
			&(app->img->endian));
	app->map = map;
	map->reset(map);
	app->render = render_map;
	app->free = free_app;
	app->clear_image = clear_image;
	return (app);
}
