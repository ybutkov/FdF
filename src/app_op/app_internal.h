/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:47:55 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/03 16:59:20 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_INTERNAL_H
# define APP_INTERNAL_H

# include "fdf.h"

# ifdef __linux__
#  define IS_MAC 0
# else
#  define IS_MAC 1
# endif

void	draw_map(t_app *app);
void	print_info_panel(t_app *app);
void	ft_mlx_destroy_display(void *mlx);

#endif
