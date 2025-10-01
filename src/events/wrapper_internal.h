/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:05:08 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/29 18:22:42 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_INTERNAL_H
# define WRAPPER_INTERNAL_H

# include "fdf.h"

void	key_up_action(t_app *app);
void	key_down_action(t_app *app);
void	key_left_action(t_app *app);
void	key_right_action(t_app *app);
void	key_plus_action(t_app *app);
void	key_minus_action(t_app *app);
void	key_w_action(t_app *app);
void	key_s_action(t_app *app);
void	key_a_action(t_app *app);
void	key_d_action(t_app *app);
void	key_z_action(t_app *app);
void	key_x_action(t_app *app);
void	key_q_action(t_app *app);
void	key_e_action(t_app *app);
void	key_r_action(t_app *app);
void	key_p_action(t_app *app);
void	key_i_action(t_app *app);
void	key_esc_action(t_app *app);

#endif