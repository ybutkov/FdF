/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:11:26 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/21 19:44:11 by ybutkov          ###   ########.fr       */
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
	// if (key == ON_DESTROY)
	// 	close_window(app);
	// if (key == MAIN_PAD_ESC)
	// 	close_window(app);
	// else if (key == MAIN_PAD_I || key == MAIN_PAD_T
	// 	|| key == MAIN_PAD_R || key == MAIN_PAD_F)
	// 	ft_change_projection(key, app);
	// else if (key == MAIN_PAD_C)
	// 	ft_change_palete(app);
	// else if (key == ARROW_LEFT || key == ARROW_RIGHT
	// 	|| key == ARROW_UP || key == ARROW_DOWN)
	// 	ft_move_map(key, app);
	// else if (key == 69 || key == MP_PLUS || key == 78 || key == MP_MINUS)
	// 	ft_zoom_hook(key, app);
	// else if (key == 83 || key == 18 || key == 84 || key == 19
	// 	|| key == NUM_PAD_3 || key == MAIN_PAD_3
	// 	|| key == NUM_PAD_4 || key == MAIN_PAD_4
	// 	|| key == NUM_PAD_6 || key == MAIN_PAD_6
	// 	|| key == NUM_PAD_7 || key == MAIN_PAD_7
	// 	|| key == NUM_PAD_8 || key == MAIN_PAD_8
	// 	|| key == NUM_PAD_9 || key == MAIN_PAD_9)
	// 	ft_rotate_hook(key, app);
	// else if (key == MAIN_PAD_U || key == MAIN_PAD_D)
	// 	ft_flat_hook(key, app);
	// else if (key == MAIN_PAD_V)
	// 	ft_rotate_video_hook(key, app);
	return (0);
}

