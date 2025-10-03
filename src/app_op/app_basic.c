/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:44:10 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/03 12:32:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app_internal.h"
#include "draw.h"
#include "colors.h"
#include "libft.h"

static void	print_info_line(t_app *app, int y, char *label1, char *label2)
{
	mlx_string_put(app->mlx, app->win, 50, y, COLOR_CYAN, label1);
	mlx_string_put(app->mlx, app->win, 200, y, COLOR_WHITE, label2);
}

static void	print_double_value(t_app *app, int x, int y, double value)
{
	char	*str;

	str = ft_double_to_str(value, 2);
	mlx_string_put(app->mlx, app->win, x, y, COLOR_YELLOW, str);
	free(str);
}

void	print_info_panel(t_app *app)
{
	mlx_string_put(app->mlx, app->win, 20, 70, COLOR_NEON_LIME, "ROTATION");
	print_info_line(app, 100, "Rotation X:", "W / S        (Mouse middle)");
	print_double_value(app, 150, 100, app->map->rotation_x);
	print_info_line(app, 130, "Rotation Y:", "A / D        (Mouse right)");
	print_double_value(app, 150, 130, app->map->rotation_y);
	print_info_line(app, 160, "Rotation Z:", "Z / X");
	print_double_value(app, 150, 160, app->map->rotation_z);
	mlx_string_put(app->mlx, app->win, 20, 190, COLOR_NEON_LIME, "ZOOM");
	print_info_line(app, 220, "Zoom:", "+ / -");
	print_double_value(app, 150, 220, app->map->zoom);
	print_info_line(app, 250, "Z Scale:", "Q / E");
	print_double_value(app, 150, 250, app->map->z_scale);
	mlx_string_put(app->mlx, app->win, 20, 280, COLOR_NEON_LIME, "MOVE");
	print_info_line(app, 310, "Offset X:", "left / right (Mouse left)");
	print_double_value(app, 150, 310, app->map->offset_x);
	print_info_line(app, 340, "Offset Y:", "up / down    (Mouse left)");
	print_double_value(app, 150, 340, app->map->offset_y);
	mlx_string_put(app->mlx, app->win, 20, 370, COLOR_NEON_LIME, "VIEWS");
	print_info_line(app, 400, "Reset view", "R");
	print_info_line(app, 430, "Iso view", "I");
	print_info_line(app, 460, "Parallel view", "P");
}

static void	_draw_line(t_app *app, t_point_2d from, int x, int y)
{
	t_point_2d	to;

	to = app->map->transform_point(app->map, x, y);
	draw_line(app->img, (t_point_2d){from.x, from.y, from.color},
		(t_point_2d){to.x, to.y, (from.color + to.color) / 2});
}

void	draw_map(t_app *app)
{
	int			x;
	int			y;
	t_point_2d	from;

	y = 0;
	while (y < app->map->height)
	{
		x = 0;
		while (x < app->map->width)
		{
			from = app->map->transform_point(app->map, x, y);
			if (x + 1 < app->map->width)
				_draw_line(app, from, x + 1, y);
			if (y + 1 < app->map->height)
				_draw_line(app, from, x, y + 1);
			x++;
		}
		y++;
	}
}
