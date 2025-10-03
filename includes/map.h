/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 13:10:17 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/03 17:50:21 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

# include "point.h"
# include <stddef.h>

# define COLOR_DEFAULT "0xFFFFFF"

typedef enum e_projection
{
	PROJ_ISO,
	PROJ_PARALLEL
}					t_projection;

typedef struct s_map
{
	t_point			*points;
	int				width;
	int				height;
	double			zoom;
	double			z_scale;
	double			rotation_x;
	double			rotation_y;
	double			rotation_z;
	int				offset_x;
	int				offset_y;
	int				shift_size;
	int				zoom_size;
	int				is_change;
	t_projection	projection;

	void			(*free)(struct s_map *map);
	void			(*reset)(struct s_map *map);
	t_point			*(*get_point)(struct s_map *map, int x, int y);
	void			(*set_point)(struct s_map *map, int x, int y,
			t_point point);
	t_point_2d		(*transform_point)(struct s_map *map, int x, int y);
	void			(*set_rotation)(struct s_map *map, double x, double y,
			double z);
	void			(*rotate)(struct s_map *map, double x, double y, double z);
	void			(*shift)(struct s_map *map, int x, int y);
	void			(*zoom_in)(struct s_map *map, int percent);

}					t_map;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

t_map				*create_map(size_t width, size_t height);

#endif
