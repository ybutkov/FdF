/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:15 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/27 19:21:35 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map.h"
#include "parcer.h"
#include "stack_base.h"
#include "utils.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

int	split_line(char *str, t_stack *stack)
{
	char	**numbers_str;
	int		amount_in_row;
	int		i;

	numbers_str = ft_split(str, ' ');
	free(str);
	if (!numbers_str)
		return (-1);
	amount_in_row = 0;
	i = 0;
	while (numbers_str[i])
	{
		if (numbers_str[i][0] == '\n')
			free(numbers_str[i]);
		else
		{
			stack->push(stack, numbers_str[i]);
			amount_in_row++;
		}
		i++;
	}
	free(numbers_str);
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

void	read_map_to_stack(int fd, t_stack *stack, int *width, size_t *height)
{
	char	*str;
	int		amount_in_row;

	*width = -1;
	*height = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		amount_in_row = split_line(str, stack);
		if (amount_in_row < 0)
		{
			*width = -1;
			break ;
		}
		if (*width == -1)
			*width = amount_in_row;
		else if (*width != amount_in_row)
		{
			*width = -1;
			break ;
		}
		(*height)++;
	}
}

t_map	*read_map_from_file(const char *filename)
{
	int		fd;
	t_stack	*stack;
	t_map	*map;
	int		width;
	size_t	height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	stack = stack_create();
	if (!stack)
		return (close(fd), NULL);
	read_map_to_stack(fd, stack, &width, &height);
	close(fd);
	map = create_map(width, height);
	if (!map)
	{
		stack->free(stack);
		return (NULL);
	}
	fill_map_from_stack(map, stack);
	map->reset(map);
	stack->free(stack);
	return (map);
}
