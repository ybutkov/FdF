/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:19:13 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/21 18:36:30 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# include "map.h"
# include <mlx.h>
# include <stdint.h>
# include <stdlib.h>

//
# include <stdio.h>

# define FDF_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_app
{
	void	*mlx;
	void	*win;
	size_t	width;
	size_t	height;
	t_map	*map;
	t_img	img;
}			t_app;

#endif