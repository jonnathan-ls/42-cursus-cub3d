/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:09 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:34:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>
#include "constants.h"

static int	is_wall_at(t_engine *eng, double x, double y)
{
	int	map_x;
	int	map_y;

	if (!eng || !eng->map)
		return (1);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= eng->map_w || map_y < 0 || map_y >= eng->map_h)
		return (1);
	if (!eng->map[map_y] || !eng->map[map_y][map_x])
		return (1);
	if (eng->map[map_y][map_x] == '1')
		return (1);
	if (eng->map[map_y][map_x] == 'D')
	{
		if (door_is_open(eng, map_x, map_y))
			return (0);
		return (1);
	}
	return (0);
}

static int	has_collision(t_engine *eng, double x, double y)
{
	double	buffer;

	buffer = 0.15;
	if (is_wall_at(eng, x - buffer, y) || is_wall_at(eng, x + buffer, y))
		return (1);
	if (is_wall_at(eng, x, y - buffer) || is_wall_at(eng, x, y + buffer))
		return (1);
	if (is_wall_at(eng, x - buffer, y - buffer))
		return (1);
	if (is_wall_at(eng, x + buffer, y + buffer))
		return (1);
	return (0);
}

static void	move_dir(t_engine *eng, double sx, double sy)
{
	double	new_x;
	double	new_y;
	double	move_dist;

	move_dist = eng->player.move_speed;
	new_x = eng->player.pos_x + sx * move_dist;
	new_y = eng->player.pos_y + sy * move_dist;
	if (!has_collision(eng, new_x, new_y))
	{
		eng->player.pos_x = new_x;
		eng->player.pos_y = new_y;
	}
	else
	{
		new_x = eng->player.pos_x + sx * move_dist * WALL_SLIDE_FACTOR;
		new_y = eng->player.pos_y + sy * move_dist * WALL_SLIDE_FACTOR;
		if (!has_collision(eng, new_x, eng->player.pos_y))
			eng->player.pos_x = new_x;
		if (!has_collision(eng, eng->player.pos_x, new_y))
			eng->player.pos_y = new_y;
	}
}

static void	strafe(t_engine *eng, double sign)
{
	double	new_x;
	double	new_y;
	double	move_dist;

	move_dist = eng->player.move_speed;
	new_x = eng->player.pos_x + sign * eng->player.plane_x * move_dist;
	new_y = eng->player.pos_y + sign * eng->player.plane_y * move_dist;
	if (!has_collision(eng, new_x, new_y))
	{
		eng->player.pos_x = new_x;
		eng->player.pos_y = new_y;
	}
	else
	{
		new_x = eng->player.pos_x + sign
			* eng->player.plane_x * move_dist * WALL_SLIDE_FACTOR;
		new_y = eng->player.pos_y + sign
			* eng->player.plane_y * move_dist * WALL_SLIDE_FACTOR;
		if (!has_collision(eng, new_x, eng->player.pos_y))
			eng->player.pos_x = new_x;
		if (!has_collision(eng, eng->player.pos_x, new_y))
			eng->player.pos_y = new_y;
	}
}

void	player_move(t_engine *eng)
{
	double	delta_time;

	if (!eng || !eng->mlx)
		return ;
	delta_time = eng->mlx->delta_time * 60.0;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_W))
		move_dir(eng, eng->player.dir_x * delta_time, eng->player.dir_y
			* delta_time);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_S))
		move_dir(eng, -eng->player.dir_x * delta_time, -eng->player.dir_y
			* delta_time);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_A))
		strafe(eng, -1.0 * delta_time);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_D))
		strafe(eng, 1.0 * delta_time);
}
