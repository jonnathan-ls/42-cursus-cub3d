/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:39:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "player.h"
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
 * Checks if door at position is currently open.
 * @param eng Pointer to engine structure.
 * @param x X coordinate of door.
 * @param y Y coordinate of door.
 * @return 1 if open, 0 otherwise.
 */
int	door_is_open(t_engine *eng, int x, int y)
{
	int	i;

	if (!eng || !eng->doors.list || eng->doors.count == 0)
		return (0);
	i = 0;
	while (i < eng->doors.count)
	{
		if (eng->doors.list[i].x == x && eng->doors.list[i].y == y)
			return (eng->doors.list[i].is_open);
		i = i + 1;
	}
	return (0);
}
