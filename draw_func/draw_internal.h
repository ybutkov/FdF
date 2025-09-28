/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:42:22 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 20:00:56 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_INTERNAL_H
# define DRAW_INTERNAL_H

typedef struct s_draw_line_delta
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}		t_draw_line_delta;

#endif