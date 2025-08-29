/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:09 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/28 21:40:32 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>

static void	move_dir(t_engine *eng, double sx, double sy)
{
	eng->player.pos_x += sx * eng->player.move_speed;
	eng->player.pos_y += sy * eng->player.move_speed;
}

static void	strafe(t_engine *eng, double sign)
{
	eng->player.pos_x += sign * eng->player.plane_x * eng->player.move_speed;
	eng->player.pos_y += sign * eng->player.plane_y * eng->player.move_speed;
}

void	ft_player_move(t_engine *eng)
{
	if (!eng || !eng->mlx)
		return ;
	if (mlx_is_key_down(eng->mlx, MLX_KEY_W))
		move_dir(eng, eng->player.dir_x, eng->player.dir_y);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_S))
		move_dir(eng, -eng->player.dir_x, -eng->player.dir_y);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_A))
		strafe(eng, -1.0);
	if (mlx_is_key_down(eng->mlx, MLX_KEY_D))
		strafe(eng, 1.0);
}
