/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:42:48 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/27 19:47:30 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "draw.h"
#include "fdf.h"
#include "hooks.h"
#include "keys.h"
#include "map.h"
#include "point.h"
#include "utils.h"
#include <time.h>

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
		mlx_destroy_display(app->mlx);
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
		img->addr[i] = 0;
		img->addr[i + 1] = 0;
		img->addr[i + 2] = 0;
		if (bytes_per_pixel == 4)
			img->addr[i + 3] = 0;
		i += bytes_per_pixel;
	}
}

void	draw_info_panel(t_app *app)
{
	draw_rectangle(app->img, (t_point_2d){0, 0, 0x000000},
		(t_point_2d){INFO_PANEL_WIDTH, app->height - 1, 0x000000},
		COLOR_DEEP_INDIGO);
}

static void	print_info_line(t_app *app, int y, char *label1, char *value,
		char *label2)
{
	mlx_string_put(app->mlx, app->win, 100, y, COLOR_CYAN, label1);
	mlx_string_put(app->mlx, app->win, 180, y, COLOR_YELLOW, value);
	mlx_string_put(app->mlx, app->win, 280, y, COLOR_WHITE, label2);
}

void	print_info_panel(t_app *app)
{
	char *str;
	
	mlx_string_put(app->mlx, app->win, 50, 70, COLOR_NEON_LIME, "ROTATION");
	str = ft_doubletostr(app->map->rotation_x, 2);
	print_info_line(app, 100, "Rotation X:", str, "W/S");
	free(str);
	str = ft_doubletostr(app->map->rotation_y, 2);
	print_info_line(app, 130, "Rotation Y:", str, "A/D");
	free(str);
	str = ft_doubletostr(app->map->rotation_z, 2);
	print_info_line(app, 160, "Rotation Z:", str, "Z/X");
	free(str);
	mlx_string_put(app->mlx, app->win, 50, 190, COLOR_NEON_LIME, "ZOOM");
	str = ft_doubletostr(app->map->zoom, 2);
	print_info_line(app, 220, "Zoom:", str, "+/-");
	free(str);
	str =	 ft_doubletostr(app->map->z_scale, 2);
	print_info_line(app, 250, "Z Scale:", str, "Q/E");
	free(str);
	mlx_string_put(app->mlx, app->win, 50, 280, COLOR_NEON_LIME, "MOVE");
	str = ft_doubletostr(app->map->offset_x, 2);
	print_info_line(app, 310, "Offset X:", str, "left/right");
	free(str);
	str = ft_doubletostr(app->map->offset_y, 2);
	print_info_line(app, 340, "Offset Y:", str, "up/down");
	free(str);
	mlx_string_put(app->mlx, app->win, 50, 370, COLOR_NEON_LIME,
		"MOUSE position");
	int x, y;
	mlx_mouse_get_pos(app->mlx, app->win, &x, &y);
	str = ft_lltoa(x);
	print_info_line(app, 400, "X:", str, "");
	free(str);
	str = ft_lltoa(y);
	print_info_line(app, 430, "Y:", str, "");
	free(str);
	mlx_string_put(app->mlx, app->win, 50, 460, COLOR_NEON_LIME, "VIEWS");
	print_info_line(app, 490, "Reset view", "", "R");
	print_info_line(app, 520, "Top view", "", "T");
	print_info_line(app, 550, "Iso view", "", "I");
	print_info_line(app, 580, "Front view", "", "Y");
}

void	render_map(t_app *app)
{
	t_point_2d	from;
	t_point_2d	right;
	t_point_2d	bottom;
	t_map		*map;
	int			x;
	int			y;

	app->clear_image(app->img);
	map = app->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
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
			x++;
		}
		y++;
	}
	draw_info_panel(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img, 0, 0);
	print_info_panel(app);
	app->last_frame_time = get_time_in_milliseconds();
	app->map->is_change = 0;
}



t_app	*create_app(t_map *map)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		return (NULL);
	// app->mlx = mlx_init();
	app->height = WINDOW_HEIGHT;
	app->width = WINDOW_WIDTH;
	// app->win = mlx_new_window(app->mlx, app->width, app->height, title);
	// mlx_hook(app->win, 17, 0, close_window, app);
	// mlx_hook(app->win, 2, 1L << 0, key_pressed_hook, app);
	// mlx_hook(app->win, 4, 1L << 2, ft_mouse_press, app);
	// mlx_hook(app->win, 6, 1L << 6, ft_mouse_move, app);
	// mlx_hook(app->win, 5, 1L << 3, ft_mouse_release, app);
	// mlx_loop_hook(app->mlx, loop_hook, app);
	app->img = (t_img *)malloc(sizeof(t_img));
	if (!app->img)
		return (NULL);
	// app->img->img = mlx_new_image(app->mlx, app->width, app->height);
	// app->img->addr = mlx_get_data_addr(app->img->img,
	// 		&(app->img->bits_per_pixel), &(app->img->line_length),
	// 		&(app->img->endian));
	app->mouse = (t_mouse_state){0, 0, 0, 0, 0, -1, -1};
	app->map = map;
	// map->reset(map);
	app->render = render_map;
	app->free = free_app;
	app->clear_image = clear_image;
	app->last_frame_time = get_time_in_milliseconds() - MIN_TIME_FRAMES - 1;
	return (app);
}
