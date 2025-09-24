/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:15 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/24 16:38:04 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "parcer.h"
#include "stack_base.h"
#include "utils.h"
#include "fdf.h"
#include <fcntl.h>
#include <math.h>

int	parse_numbers(char **numbers_str, t_stack *stack)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (numbers_str[i])
	{
		if (numbers_str[i][0] == '\n')
			free(numbers_str[i]);
		else
		{
			stack->push(stack, numbers_str[i]);
			amount++;
		}
		i++;
	}
	free(numbers_str);
	return (amount);
}

int	split_line(char *str, t_stack *stack)
{
	char	**numbers_str;
	int		amount_in_row;

	numbers_str = ft_split(str, ' ');
	free(str);
	if (!numbers_str)
		return (-1);
	amount_in_row = parse_numbers(numbers_str, stack);
	return (amount_in_row);
}

t_point	parse_point(char *data)
{
	t_point	point;
	char	**parts;

	parts = ft_split(data, ',');
	point.z = (t_z_type)ft_atoi(parts[0]);
	free(parts[0]);
	if (parts[1])
	{
		point.color = base_to_long(ft_str_capitalise(parts[1]) + 2,
				"0123456789ABCDEF");
		free(parts[1]);
	}
	else
		point.color = base_to_long(COLOR_DEFAULT + 2, "0123456789ABCDEF");
	free(parts);
	return (point);
}

void	fill_map_from_stack(t_map *map, t_stack *stack)
{
	int		x;
	int		y;
	t_point	point;
	char	*data;

	x = map->width - 1;
	y = map->height - 1;
	while (stack->size > 0)
	{
		if (x < 0)
		{
			x = map->width - 1;
			y--;
		}
		data = (char *)stack->pop(stack);
		point = parse_point(data);
		map->set_point(map, x, y, point);
		free(data);
		x--;
	}
}

t_map	*read_map_from_file(const char *filename)
{
	char	*str;
	int		fd;
	int		amount_in_row;
	t_stack	*stack;
	t_map	*map;
	int		width;
	size_t	height;

	fd = open(filename, O_RDONLY);
	stack = stack_create();
	if (!stack)
		error_and_exit();
	if (fd < 0)
		error_and_exit();
	width = -1;
	height = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		amount_in_row = split_line(str, stack);
		if (amount_in_row < 0)
			error_and_exit();
		if (width == -1)
			width = amount_in_row;
		else if (width != amount_in_row)
			error_and_exit();
		height++;
	}
	map = create_map(width, height);
	if (!map)
		error_and_exit();
	fill_map_from_stack(map, stack);
	stack->free(stack);

	// map->zoom = WINDOW_WIDTH / (float)(map->width);
	// map->zoom = (fmin(WINDOW_WIDTH / (float)(map->width),
	// 			WINDOW_HEIGHT / (float)(map->height))) * 0.7f;
	// map->zoom = 10;
	// map->offset_x = WINDOW_WIDTH / 2 - (map->width * map->zoom) / 2;
	// map->offset_y = WINDOW_HEIGHT / 2 - (map->height * map->zoom) / 2;
	// map->offset_x = 300;
	// map->offset_y = 300;
	// map->rotation_x = M_PI / 6;
	// map->rotation_y = -M_PI / 4;
	// map->rotation_x = 0;
	// map->rotation_y = 0;
	// map->rotation_z = 0;
	// map->z_scale = 0.5f;
	return (map);
}
