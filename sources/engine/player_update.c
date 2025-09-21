/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:09 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/20 22:10:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>
#include "constants.h"

static void	move_dir(t_engine *eng, double sx, double sy)
{
	double	new_x;
	double	new_y;
	double	move_dist;

	move_dist = eng->player.move_speed;
	new_x = eng->player.pos_x + sx * move_dist;
	new_y = eng->player.pos_y + sy * move_dist;
	if (!ft_check_collision_with_buffer(eng, new_x, new_y))
	{
		eng->player.pos_x = new_x;
		eng->player.pos_y = new_y;
	}
	else
	{
		new_x = eng->player.pos_x + sx * move_dist * WALL_SLIDE_FACTOR;
		new_y = eng->player.pos_y + sy * move_dist * WALL_SLIDE_FACTOR;
		if (!ft_check_collision_with_buffer(eng, new_x, eng->player.pos_y))
			eng->player.pos_x = new_x;
		if (!ft_check_collision_with_buffer(eng, eng->player.pos_x, new_y))
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
	if (!ft_check_collision_with_buffer(eng, new_x, new_y))
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
		if (!ft_check_collision_with_buffer(eng, new_x, eng->player.pos_y))
			eng->player.pos_x = new_x;
		if (!ft_check_collision_with_buffer(eng, eng->player.pos_x, new_y))
			eng->player.pos_y = new_y;
	}
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
