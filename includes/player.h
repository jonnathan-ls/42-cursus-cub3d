/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 18:36:30 by jlacerda         ###   ########.fr       */
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

void		player_move(struct s_engine *eng);
void		player_rotate(struct s_engine *eng, double rot);
void		player_mouse_rotate(struct s_engine *eng);

#endif
