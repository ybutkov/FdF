/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:14:44 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/26 13:43:05 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>
int ft_mouse_press(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
		printf("Mouse press: x=%d, y=%d\n", x, y);
	if (button == 4)
		app->map->zoom++;
	else if (button == 5 && app->map->zoom > 1)
		app->map->zoom--;
	return (0);
}

int ft_mouse_move(int x, int y, t_app *app)
{
	// printf("Mouse move: x=%d, y=%d\n", x, y);
	static int last_x = -1;
	static int last_y = -1;
	int delta_x;
	int delta_y;

	if (last_x == -1 && last_y == -1)
	{
		last_x = x;
		last_y = y;
		return (0);
	}
	delta_x = x - last_x;
	delta_y = y - last_y;
	last_x = x;
	last_y = y;

	(void)delta_x;
	(void)delta_y;
	(void)app;
	// app->map->offset_x += delta_x;
	// app->map->offset_y += delta_y;

	return (0);
}
