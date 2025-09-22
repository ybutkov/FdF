/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:11:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/22 14:01:51 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "hooks.h"
#include "keys.h"

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
	printf("Key pressed: %d\n", key);

	if (key == KEY_ESC)
	{
		exit_program(app);  // твоя функция очистки и выхода
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
		app->map->rotation_x += 0.1;
	else if (key == KEY_S)
		app->map->rotation_x -= 0.1;
	else if (key == KEY_A)
		app->map->rotation_y += 0.1;
	else if (key == KEY_D)
		app->map->rotation_y -= 0.1;
	else if (key == KEY_Q)
		app->map->z_scale += 0.1;
	else if (key == KEY_E)
		app->map->z_scale -= 0.1;
	// добавишь свои фичи для бонуса (TAB, R/F и т.п.)
	render_map(app);  // перерисовываем
	return (0);
}
