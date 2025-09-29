/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 22:20:57 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stddef.h>

struct	s_engine;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		mouse_x;
	int		mouse_y;
	double	pitch;
	double	pitch_factor;
}			t_player;

void		handle_player_movement(struct s_engine *eng);
void		handle_player_rotation_by_mouse(struct s_engine *eng);
void		handle_player_rotation(struct s_engine *eng, double rot);

#endif
