/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 00:31:38 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stddef.h>

typedef struct s_engine	t_engine;

/**
 * @struct s_player
 * @brief Player character state and properties.
 */
typedef struct s_player
{
	double	pos_x;				/**< Player X position in world coordinates. */
	double	pos_y;				/**< Player Y position in world coordinates. */
	double	dir_x;				/**< Player direction vector X component. */
	double	dir_y;				/**< Player direction vector Y component. */
	double	pitch;				/**< Vertical camera pitch angle. */
	double	plane_x;			/**< Camera plane vector X component. */
	double	plane_y;			/**< Camera plane vector Y component. */
	int		mouse_x;			/**< Last mouse X position. */
	int		mouse_y;			/**< Last mouse Y position. */
	double	rot_speed;			/**< Rotation speed multiplier. */
	double	move_speed;			/**< Movement speed multiplier. */
	double	pitch_factor;		/**< Pitch sensitivity factor. */
	int		health;				/**< Current player health points. */
	int		game_over;			/**< Game over flag (1 = dead). */
	double	damage_cooldown;	/**< Time until next damage can be taken. */
	int		is_taking_damage;	/**< Currently taking damage flag. */
}			t_player;

void		handle_player_movement(t_engine *eng);
void		handle_player_rotation_by_mouse(t_engine *eng);
void		handle_player_rotation(t_engine *eng, double rot);

#endif
