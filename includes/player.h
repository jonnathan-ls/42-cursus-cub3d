/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 19:40:10 by peda-cos         ###   ########.fr       */
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
}			t_player;

void		ft_player_move(struct s_engine *eng);
void		ft_player_rotate(struct s_engine *eng, double rot);
void		ft_player_mouse_rotate(struct s_engine *eng);

#endif
