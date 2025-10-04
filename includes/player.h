/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 20:29:27 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stddef.h>

typedef struct s_engine	t_engine;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	pitch;
	double	plane_x;
	double	plane_y;
	int		mouse_x;
	int		mouse_y;
	double	rot_speed;
	double	move_speed;
	double	pitch_factor;
}			t_player;

void		handle_player_movement(t_engine *eng);
void		handle_player_rotation_by_mouse(t_engine *eng);
void		handle_player_rotation(t_engine *eng, double rot);

#endif
