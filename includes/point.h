/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:17:14 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/28 20:03:43 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdint.h>

typedef int16_t		t_z_type;
typedef uint32_t	t_color_type;

typedef struct s_point_2d
{
	int				x;
	int				y;
	t_color_type	color;
}					t_point_2d;

typedef struct s_point_3d
{
	double			x;
	double			y;
	double			z;
}					t_point_3d;

typedef struct s_point
{
	t_z_type		z;
	t_color_type	color;
} __attribute__((packed))	t_point;

#endif
