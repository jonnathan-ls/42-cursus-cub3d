/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:16:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include <MLX42/MLX42.h>

int	check_key_press_cooldown(void)
{
	static double	last_press;
	double			current;
	double			cooldown;

	cooldown = 0.3;
	current = mlx_get_time();
	if (current - last_press < cooldown)
		return (0);
	last_press = current;
	return (1);
}

static void	set_direction_vector(t_engine *eng, char dir)
{
	eng->player.dir_x = 0;
	eng->player.dir_y = 0;
	if (dir == 'E')
		eng->player.dir_x = 1;
	if (dir == 'W')
		eng->player.dir_x = -1;
	if (dir == 'S')
		eng->player.dir_y = 1;
	if (dir == 'N')
		eng->player.dir_y = -1;
}

static void	set_plane_vector(t_engine *eng, char dir)
{
	eng->player.plane_x = 0;
	eng->player.plane_y = 0;
	if (dir == 'N')
		eng->player.plane_x = PLANE_FACTOR;
	if (dir == 'S')
		eng->player.plane_x = -PLANE_FACTOR;
	if (dir == 'E')
		eng->player.plane_y = PLANE_FACTOR;
	if (dir == 'W')
		eng->player.plane_y = -PLANE_FACTOR;
}

void	set_player_direction(t_engine *eng, char dir)
{
	set_direction_vector(eng, dir);
	set_plane_vector(eng, dir);
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
