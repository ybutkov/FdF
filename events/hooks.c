/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:11:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/26 14:46:41 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "hooks.h"
#include "keys.h"
#include <math.h>

int	close_window(t_app *app)
{
	(void)app;
	// free(app->img.img);
	// free(app->img.addr);
	// free(app);
	exit(0);
}

int	key_pressed_hook(int key, t_app *app)
{
	(void)app;
	// printf("Key pressed: %d\n", key);
	if (key == KEY_ESC)
	{
		exit_program(app); // твоя функция очистки и выхода
	}
	else if (key == KEY_UP)
		app->map->offset_y -= 10;
	else if (key == KEY_DOWN)
		app->map->offset_y += 10;
	else if (key == KEY_LEFT)
		app->map->offset_x -= 10;
	else if (key == KEY_RIGHT)
		app->map->offset_x += 10;
	else if (key == KEY_PLUS)
		app->map->zoom++;
	else if (key == KEY_MINUS && app->map->zoom > 1)
		app->map->zoom--;
	else if (key == KEY_W)
		app->map->rotate(app->map, 0.05, 0, 0);
	else if (key == KEY_S)
		app->map->rotate(app->map, -0.05, 0, 0);
	else if (key == KEY_A)
		app->map->rotate(app->map, 0, 0.05, 0);
	else if (key == KEY_D)
		app->map->rotate(app->map, 0, -0.05, 0);
	else if (key == KEY_Z)
		app->map->rotate(app->map, 0, 0, 0.05);
	else if (key == KEY_X)
		app->map->rotate(app->map, 0, 0, -0.05);
	else if (key == KEY_Q)
		app->map->z_scale += 0.005;
	else if (key == KEY_E)
		app->map->z_scale -= 0.005;
	else if (key == KEY_R)
		app->map->reset(app->map);
	else if (key == KEY_T)
		app->map->set_rotation(app->map, -M_PI / 2, 0, 0);
	else if (key == KEY_Y)
		app->map->set_rotation(app->map, 0, 0, 0);
	else if (key == KEY_U)
		app->map->set_rotation(app->map, 0, M_PI / 2, 0);
	else if (key == KEY_I)
		app->map->set_rotation(app->map, -M_PI / 6, -M_PI / 6, 0);
	// app->render(app);
	return (0);
}
