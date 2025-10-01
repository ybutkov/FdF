/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_wrapper_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:54:49 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/29 18:23:12 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "hooks.h"

void	key_up_action(t_app *app)
{
	app->map->shift(app->map, 0, -app->map->shift_size);
}

void	key_down_action(t_app *app)
{
	app->map->shift(app->map, 0, app->map->shift_size);
}

void	key_left_action(t_app *app)
{
	app->map->shift(app->map, -app->map->shift_size, 0);
}

void	key_right_action(t_app *app)
{
	app->map->shift(app->map, app->map->shift_size, 0);
}

void	key_plus_action(t_app *app)
{
	app->map->zoom_in(app->map, app->map->zoom_size);
}
