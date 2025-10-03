/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:02:39 by ybutkov           #+#    #+#             */
/*   Updated: 2025/10/03 17:03:16 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

#ifdef __linux__

void	ft_mlx_destroy_display(void *mlx)
{
	mlx_destroy_display(app->mlx);
}

#else

void	ft_mlx_destroy_display(void *mlx)
{
	(void)mlx;
	return ;
}
#endif