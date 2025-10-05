/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 00:30:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include <MLX42/MLX42.h>

int	check_key_press_cooldown(void)
{
	double	last_press_time;
	double	current_time;
	double	cooldown;

	cooldown = 0.3;
	last_press_time = 0.0;
	current_time = mlx_get_time();
	if (current_time - last_press_time < cooldown)
		return (0);
	last_press_time = current_time;
	return (1);
}

void	set_player_direction(t_engine *eng, char dir)
{
	eng->player.dir_x = 0;
	eng->player.dir_y = 0;
	eng->player.plane_x = 0;
	eng->player.plane_y = 0;
	if (dir == 'E')
		eng->player.dir_x = 1;
	if (dir == 'W')
		eng->player.dir_x = -1;
	if (dir == 'S')
		eng->player.dir_y = 1;
	if (dir == 'N')
		eng->player.dir_y = -1;
	if (dir == 'N')
		eng->player.plane_x = PLANE_FACTOR;
	if (dir == 'S')
		eng->player.plane_x = -PLANE_FACTOR;
	if (dir == 'E')
		eng->player.plane_y = PLANE_FACTOR;
	if (dir == 'W')
		eng->player.plane_y = -PLANE_FACTOR;
}

void	draw_circle(uint32_t *pixels, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			dx = x;
			dy = y;
			if (dx * dx + dy * dy <= radius * radius && dx * dx + dy
				* dy >= (radius - 1) * (radius - 1))
				pixels[(cy + y) * 32 + (cx + x)] = 0xFFFFFFFF;
			x = x + 1;
		}
		y = y + 1;
	}
}

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
