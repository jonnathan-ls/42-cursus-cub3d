/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:09 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 19:06:23 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>

static int	is_wall_at(t_engine *eng, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= eng->map_w || map_y < 0 || map_y >= eng->map_h)
		return (1);
	return (eng->map[map_y][map_x] == '1');
}

static void	move_dir(t_engine *eng, double sx, double sy)
{
	double	new_x;
	double	new_y;

	new_x = eng->player.pos_x + sx * eng->player.move_speed;
	new_y = eng->player.pos_y + sy * eng->player.move_speed;
	if (!is_wall_at(eng, new_x, eng->player.pos_y))
		eng->player.pos_x = new_x;
	if (!is_wall_at(eng, eng->player.pos_x, new_y))
		eng->player.pos_y = new_y;
}

static void	strafe(t_engine *eng, double sign)
{
	double	new_x;
	double	new_y;

	new_x = eng->player.pos_x + sign * eng->player.plane_x
		* eng->player.move_speed;
	new_y = eng->player.pos_y + sign * eng->player.plane_y
		* eng->player.move_speed;
	if (!is_wall_at(eng, new_x, eng->player.pos_y))
		eng->player.pos_x = new_x;
	if (!is_wall_at(eng, eng->player.pos_x, new_y))
		eng->player.pos_y = new_y;
}

void	ft_player_move(t_engine *eng)
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
