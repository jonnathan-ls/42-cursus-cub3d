/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 04:14:59 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "player.h"
#include "constants.h"
#include <MLX42/MLX42.h>

/**
 * Toggles door state between open and closed.
 * @param eng Pointer to engine structure.
 * @param door_index Index of door in doors list.
 */
static void	toggle_door_by_index(t_engine *eng, int door_index)
{
	int	is_door_open;

	if (door_index >= 0 && door_index < eng->doors.count)
	{
		is_door_open = !eng->doors.list[door_index].is_open;
		eng->doors.list[door_index].is_open = is_door_open;
	}
}

/**
 * Handles player door interaction when E key is pressed.
 * @param eng Pointer to engine structure.
 */
void	handle_door_interaction(t_engine *eng)
{
	int	nearest_door_index;

	if (!can_interact_with_door(eng))
		return ;
	nearest_door_index = find_nearest_door_index(eng);
	toggle_door_by_index(eng, nearest_door_index);
}

/**
 * Checks if player can interact with a door.
 * @param eng Pointer to engine structure.
 * @return 1 if can interact, 0 otherwise.
 */
int	can_interact_with_door(t_engine *eng)
{
	if (!eng || !mlx_is_key_down(eng->mlx, MLX_KEY_E))
		return (0);
	return (check_key_press_cooldown());
}

/**
 * Updates single door animation offset.
 * @param door Pointer to door structure.
 * @param speed Animation speed for this frame.
 */
static void	update_door_animation(t_door *door, double speed)
{
	if (door->is_open && door->offset < 1.0)
	{
		door->offset = door->offset + speed;
		if (door->offset > 1.0)
			door->offset = 1.0;
	}
	if (!door->is_open && door->offset > 0.0)
	{
		door->offset = door->offset - speed;
		if (door->offset < 0.0)
			door->offset = 0.0;
	}
}

/**
 * Updates door animation offsets for opening and closing.
 * @param eng Pointer to engine structure.
 */
void	handle_door_updates(t_engine *eng)
{
	int		i;
	double	speed;

	if (!eng || !eng->doors.list)
		return ;
	i = 0;
	speed = DOOR_ANIM_SPEED * eng->mlx->delta_time;
	while (i < eng->doors.count)
	{
		update_door_animation(&eng->doors.list[i], speed);
		i = i + 1;
	}
}
