/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybutkov <ybutkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:41:59 by ybutkov           #+#    #+#             */
/*   Updated: 2025/09/22 14:12:58 by ybutkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_program(t_app *app)
{
	printf("Exiting program and freeing resources...\n");
	if (app->img->img)
		mlx_destroy_image(app->mlx, app->img->img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		// Depending on the MLX version, you might need to free mlx itself.
		// Uncomment if your MLX version requires this.
		// mlx_destroy_display(app.mlx); 
		free(app->mlx);
	}
	if (app->map)
		app->map->free(app->map);
	exit(0);
}
