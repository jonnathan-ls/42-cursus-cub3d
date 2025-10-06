/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 03:09:07 by peda-cos         ###   ########.fr       */
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
	int	door_idx;

	if (!eng || !eng->doors.list || !eng->doors.grid)
		return (0);
	if (y < 0 || y >= eng->map_height || x < 0 || x >= eng->map_width)
		return (0);
	door_idx = eng->doors.grid[y][x];
	if (door_idx < 0 || door_idx >= eng->doors.count)
		return (0);
	return (eng->doors.list[door_idx].is_open);
}
