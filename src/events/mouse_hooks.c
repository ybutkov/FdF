/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:14:44 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 15:46:37 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mouse.h"
#include <math.h>

int	ft_mouse_press(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_BUTTON)
		app->mouse.left_button = 1;
	else if (button == MOUSE_RIGHT_BUTTON)
		app->mouse.right_button = 1;
	else if (button == MOUSE_MIDDLE_BUTTON)
		app->mouse.middle_button = 1;
	else if (button == MOUSE_SCROLL_UP)
		app->map->zoom++;
	else if (button == MOUSE_SCROLL_DOWN && app->map->zoom > 1)
		app->map->zoom--;
	app->map->is_change = 1;
	return (0);
}

int	ft_mouse_release(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_BUTTON)
		app->mouse.left_button = 0;
	else if (button == MOUSE_RIGHT_BUTTON)
		app->mouse.right_button = 0;
	else if (button == MOUSE_MIDDLE_BUTTON)
		app->mouse.middle_button = 0;
	return (0);
}

int	ft_mouse_move(int x, int y, t_app *app)
{
	t_mouse_state	*mouse;
	int				delta_x;
	int				delta_y;

	mouse = &app->mouse;
	if (mouse->prev_x == -1 && mouse->prev_y == -1)
	{
		mouse->prev_x = x;
		mouse->prev_y = y;
		return (0);
	}
	delta_x = x - mouse->prev_x;
	delta_y = y - mouse->prev_y;
	mouse->prev_x = x;
	mouse->prev_y = y;
	if (mouse->left_button)
		app->map->shift(app->map, delta_x, delta_y);
	else if (mouse->middle_button)
		app->map->rotate(app->map, copysign(0.01, delta_x), 0, 0);
	else if (mouse->right_button)
		app->map->rotate(app->map, 0, copysign(0.01, delta_y), 0);
	else
		return (0);
	app->map->is_change = 1;
	return (0);
}
