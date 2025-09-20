/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:13 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/19 23:54:55 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>

static void	apply_rot(t_player *p, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

static void	apply_border_rotation(t_engine *eng, int mouse_x)
{
	double	rot_amount;
	double	frame_time;

	frame_time = eng->mlx->delta_time * 60.0;
	if (mouse_x < MOUSE_BORDER_ZONE)
	{
		rot_amount = -MOUSE_BORDER_SPEED * frame_time;
		apply_rot(&eng->player, rot_amount);
	}
	else if (mouse_x > WIN_WIDTH - MOUSE_BORDER_ZONE)
	{
		rot_amount = MOUSE_BORDER_SPEED * frame_time;
		apply_rot(&eng->player, rot_amount);
	}
}

void	ft_player_rotate(t_engine *eng, double rot)
{
	if (!eng)
		return ;
	apply_rot(&eng->player, rot);
}

void	ft_player_mouse_rotate(t_engine *eng)
{
	int		mouse_x;
	int		mouse_y;
	double	delta_x;
	double	rot_amount;

	if (!eng || !eng->mlx)
		return ;
	mlx_get_mouse_pos(eng->mlx, &mouse_x, &mouse_y);
	delta_x = mouse_x - eng->player.mouse_x;
	if (delta_x != 0 && fabs(delta_x) < 200)
	{
		rot_amount = delta_x * MOUSE_SENSITIVITY;
		apply_rot(&eng->player, rot_amount);
	}
	apply_border_rotation(eng, mouse_x);
	eng->player.mouse_x = mouse_x;
	eng->player.mouse_y = mouse_y;
}
