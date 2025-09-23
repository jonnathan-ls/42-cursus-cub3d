/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/23 19:39:15 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include <MLX42/MLX42.h>

int	check_key_press_cooldown(void)
{
	static double	last_press_time = 0.0;
	double			current_time;
	double			cooldown;

	cooldown = 0.2;
	current_time = mlx_get_time();
	if (current_time - last_press_time < cooldown)
		return (0);
	last_press_time = current_time;
	return (1);
}

void	set_player_dir(t_engine *eng, char dir)
{
	eng->player.dir_x = (dir == 'E') - (dir == 'W');
	eng->player.dir_y = (dir == 'S') - (dir == 'N');
	eng->player.plane_x = ((dir == 'N') - (dir == 'S')) * PLANE_FACTOR;
	eng->player.plane_y = ((dir == 'E') - (dir == 'W')) * PLANE_FACTOR;
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
			x++;
		}
		y++;
	}
}

void	zero_engine(t_engine *eng)
{
	eng->mlx = NULL;
	eng->img.frame = NULL;
	eng->img.cursor = NULL;
	eng->tex.north = NULL;
	eng->tex.south = NULL;
	eng->tex.west = NULL;
	eng->tex.east = NULL;
	eng->tex.door_closed = NULL;
}
