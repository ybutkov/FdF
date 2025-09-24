/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:21:43 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/24 16:51:34 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __linux__
typedef enum e_keys
{
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_R = 114,
	KEY_F = 102,
	KEY_Z = 122,
	KEY_X = 120,
	KEY_T = 116,
	KEY_Y = 121,
	KEY_U = 117,
	KEY_I = 105,
	KEY_PLUS = 61,  // '='
	KEY_MINUS = 45, // '-'
	KEY_SPACE = 32,
	KEY_TAB = 65289,
	KEY_SHIFT = 65505,
	KEY_CTRL = 65507
}	t_keys;
# elif __APPLE__
typedef enum e_keys
{
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Q = 12,
	KEY_E = 14,
	KEY_R = 15,
	KEY_F = 3,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_T = 17,
	KEY_Y = 16,
	KEY_U = 32,
	KEY_I = 34,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_SPACE = 49,
	KEY_TAB = 48,
	KEY_SHIFT = 257,
	KEY_CTRL = 256
}	t_keys;
# endif
#endif
