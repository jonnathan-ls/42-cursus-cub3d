/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:19:58 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include <MLX42/MLX42.h>

void	apply_window_scale(t_engine *eng)
{
	int32_t	monitor_width;
	int32_t	monitor_height;

	if (!eng->fullscreen)
	{
		eng->window_width = WIN_WIDTH;
		eng->window_height = WIN_HEIGHT;
		return ;
	}
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	if (monitor_width <= 0 || monitor_height <= 0)
		return ;
	eng->window_width = monitor_width;
	eng->window_height = monitor_height;
	mlx_set_window_size(eng->mlx, eng->window_width, eng->window_height);
	if (eng->frame)
		mlx_resize_image(eng->frame, eng->window_width, eng->window_height);
}
