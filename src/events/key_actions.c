/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:37:44 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/02 17:00:27 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "keys.h"
#include "wrapper_internal.h"

static void	init_functions(t_key_actions *key_actions)
{
	key_actions->actions[0] = (t_key_action){KEY_ESC, key_esc_action};
	key_actions->actions[1] = (t_key_action){KEY_UP, key_up_action};
	key_actions->actions[2] = (t_key_action){KEY_DOWN, key_down_action};
	key_actions->actions[3] = (t_key_action){KEY_LEFT, key_left_action};
	key_actions->actions[4] = (t_key_action){KEY_RIGHT, key_right_action};
	key_actions->actions[5] = (t_key_action){KEY_PLUS, key_plus_action};
	key_actions->actions[6] = (t_key_action){KEY_MINUS, key_minus_action};
	key_actions->actions[7] = (t_key_action){KEY_W, key_w_action};
	key_actions->actions[8] = (t_key_action){KEY_S, key_s_action};
	key_actions->actions[9] = (t_key_action){KEY_A, key_a_action};
	key_actions->actions[10] = (t_key_action){KEY_D, key_d_action};
	key_actions->actions[11] = (t_key_action){KEY_Z, key_z_action};
	key_actions->actions[12] = (t_key_action){KEY_X, key_x_action};
	key_actions->actions[13] = (t_key_action){KEY_Q, key_q_action};
	key_actions->actions[14] = (t_key_action){KEY_E, key_e_action};
	key_actions->actions[15] = (t_key_action){KEY_R, key_r_action};
	key_actions->actions[16] = (t_key_action){KEY_P, key_p_action};
	key_actions->actions[17] = (t_key_action){KEY_I, key_i_action};
}

static t_key_action	*get_action(t_key_actions *key_actions, int key)
{
	int	i;

	i = 0;
	while (i < key_actions->count)
	{
		if (key_actions->actions[i].key == key)
			return (&key_actions->actions[i]);
		i++;
	}
	return (NULL);
}

static void	free_key_actions(t_key_actions *key_actions)
{
	if (key_actions->actions)
		free(key_actions->actions);
	free(key_actions);
}

t_key_actions	*init_key_actions(void)
{
	t_key_actions	*key_actions;

	key_actions = malloc(sizeof(t_key_actions));
	if (key_actions == NULL)
		return (NULL);
	key_actions->count = AMOUNT_OF_KEY_ACTIONS;
	key_actions->actions = malloc(sizeof(t_key_action) * key_actions->count);
	if (key_actions->actions == NULL)
		return (free(key_actions), NULL);
	init_functions(key_actions);
	key_actions->free = free_key_actions;
	key_actions->get_action = get_action;
	return (key_actions);
}
