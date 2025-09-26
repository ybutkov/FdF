/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:19:13 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/26 14:21:57 by ybutkov          ###   ########.fr       */
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
# define INFO_PANEL_WIDTH 400
# define MIN_TIME_FRAMES 16 // примерно 60 FPS

typedef struct s_app
{
	void		*mlx;
	void		*win;
	size_t		width;
	size_t		height;
	t_map		*map;
	t_img		*img;
	long int	last_frame_time;

	void		(*free)(struct s_app *app);
	void		(*render)(struct s_app *app);
	void		(*clear_image)(t_img *img);
}				t_app;

void			exit_program(t_app *app);
void			render_map(t_app *app);
t_app			*create_app(t_map *map, char *title);

#endif