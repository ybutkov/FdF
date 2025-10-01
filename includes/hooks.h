/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:12:51 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/01 18:47:06 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "fdf.h"

# define AMOUNT_OF_KEY_ACTIONS 18

typedef struct s_app	t_app;

typedef void			(*t_key_action_fn)(t_app *app);

typedef struct s_key_action
{
	int					key;
	t_key_action_fn		action;
}						t_key_action;

typedef struct s_key_actions
{
	t_key_action		*actions;
	int					count;
	void				(*free)(struct s_key_actions *key_actions);
	t_key_action		*(*get_action)(struct s_key_actions *key_actions,
			int key);
}						t_key_actions;

int						close_window(t_app *app);
int						key_pressed_hook(int key, t_app *app);
t_key_actions			*init_key_actions(void);
int						ft_mouse_move(int x, int y, t_app *app);
int						ft_mouse_press(int button, int x, int y, t_app *app);
int						ft_mouse_release(int button, int x, int y, t_app *app);

#endif
