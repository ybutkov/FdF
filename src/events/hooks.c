/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:11:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/03 14:56:12 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "hooks.h"
#include "keys.h"

int	close_window(t_app *app)
{
	app->free(app);
	exit(0);
}

int	key_pressed_hook(int key, t_app *app)
{
	t_key_action	*action;

	app->map->is_change = 1;
	action = app->key_actions->get_action(app->key_actions, key);
	if (action)
		action->action(app);
	else
		app->map->is_change = 0;
	return (0);
}
