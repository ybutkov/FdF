/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:19:13 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/27 18:18:39 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "map.h"
# include "mouse.h"
# include <mlx.h>
# include <stdint.h>
# include <stdlib.h>


# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define INFO_PANEL_WIDTH 400
# define MIN_TIME_FRAMES 16
# define SHIFT_SIZE 10
# define ZOOM_SIZE_PERCENT 5

typedef struct s_app
{
	void			*mlx;
	void			*win;
	size_t			width;
	size_t			height;
	t_map			*map;
	t_img			*img;
	long int		last_frame_time;
	t_mouse_state	mouse;

	void			(*free)(struct s_app *app);
	void			(*render)(struct s_app *app);
	void			(*clear_image)(t_img *img);
}					t_app;

void				render_map(t_app *app);
t_app				*create_app(t_map *map);

#endif