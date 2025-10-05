/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/04 22:33:31 by jlacerda         ###   ########.fr       */
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

	cooldown = 0.3;
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

void	reset_engine_values(t_engine *eng)
{
	eng->map_width = 0;
	eng->map_height = 0;
	eng->window_width = 0;
	eng->window_height = 0;
	eng->ceiling_color = 0;
	eng->floor_color = 0;
	eng->doors.count = 0;
	eng->ignore_doors = 0;
	eng->menu_toggle = 1;
	eng->menu_visible = 0;
	eng->mlx = NULL;
	eng->map = NULL;
	eng->tex.door = NULL;
	eng->tex.menu = NULL;
	eng->tex.west = NULL;
	eng->tex.east = NULL;
	eng->tex.north = NULL;
	eng->tex.south = NULL;
	eng->frame = NULL;
	eng->tex.floor = NULL;
	eng->cursor = NULL;
	eng->doors.list = NULL;
	eng->tex.ceiling = NULL;
}
