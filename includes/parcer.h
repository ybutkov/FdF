/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:04:29 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/20 16:10:11 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# ifndef FD_MAX_SIZE
#  define FD_MAX_SIZE 1024
# endif

# include "map.h"
# include "stack_base.h"

t_map	*read_map_from_file(const char *filename);
char	*get_next_line(int fd);

#endif