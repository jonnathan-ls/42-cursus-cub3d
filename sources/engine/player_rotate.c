/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:13 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 23:39:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>

/**
 * Applies rotation matrix to direction and plane vectors.
 * @param p Pointer to player structure.
 * @param rot Rotation angle in radians.
 */
static void	apply_rotation(t_player *p, double rot)
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

/**
 * Rotates player view by specified angle.
 * @param eng Pointer to engine structure.
 * @param rot Rotation angle in radians.
 */
void	handle_player_rotation(t_engine *eng, double rot)
{
	if (!eng)
		return ;
	apply_rotation(&eng->player, rot);
}

/**
 * Adjusts camera pitch based on mouse movement.
 * @param eng Pointer to engine structure.
 * @param delta_y Vertical mouse movement delta.
 */
static void	player_mouse_pitch(t_engine *eng, double delta_y)
{
	double	pitch_amount;

	if (!eng)
		return ;
	if (delta_y != 0)
	{
		pitch_amount = delta_y * MOUSE_SENSITIVITY;
		eng->player.pitch += pitch_amount * eng->player.pitch_factor;
	}
}

/**
 * Handles camera rotation and pitch from mouse input.
 * @param eng Pointer to engine structure.
 */
void	handle_player_rotation_by_mouse(t_engine *eng)
{
	int		mouse_x;
	int		mouse_y;
	double	delta_x;
	double	rot_amount;
	double	delta_y;

	if (!eng || !eng->mlx)
		return ;
	mlx_get_mouse_pos(eng->mlx, &mouse_x, &mouse_y);
	delta_x = mouse_x - eng->player.mouse_x;
	if (delta_x != 0)
	{
		rot_amount = delta_x * MOUSE_SENSITIVITY;
		apply_rotation(&eng->player, rot_amount);
	}
	delta_y = mouse_y - eng->player.mouse_y;
	player_mouse_pitch(eng, delta_y);
	eng->player.mouse_x = mouse_x;
	eng->player.mouse_y = mouse_y;
}
