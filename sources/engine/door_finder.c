/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 04:14:59 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include "shared.h"
#include "constants.h"

/**
 * Finds nearest door within interaction radius.
 * @param eng Pointer to engine structure.
 * @return Door index or -1 if none found.
 */
int	find_nearest_door_index(t_engine *eng)
{
	int		i;
	double	door_x;
	double	door_y;

	if (!eng || !eng->doors.list)
		return (-1);
	i = 0;
	while (i < eng->doors.count)
	{
		door_x = (double)eng->doors.list[i].x + DOOR_CENTER_OFFSET;
		door_y = (double)eng->doors.list[i].y + DOOR_CENTER_OFFSET;
		if (is_in_radius(eng->player.pos_x, eng->player.pos_y,
				door_x, door_y))
			return (i);
		i = i + 1;
	}
	return (-1);
}

/**
 * Gets texture offset for animated door at position.
 * @param eng Pointer to engine structure.
 * @param map_x X coordinate of door.
 * @param map_y Y coordinate of door.
 * @return Texture offset in pixels.
 */
int	get_door_texture_offset(t_engine *eng, int map_x, int map_y)
{
	int	door_idx;
	int	cell_w;

	if (!eng || !eng->doors.list || !eng->doors.grid)
		return (0);
	if (map_y < 0 || map_y >= eng->map_height)
		return (0);
	if (map_x < 0 || map_x >= eng->map_width)
		return (0);
	door_idx = eng->doors.grid[map_y][map_x];
	if (door_idx < 0 || door_idx >= eng->doors.count)
		return (0);
	cell_w = eng->window_width / eng->map_width;
	return ((int)(eng->doors.list[door_idx].offset * (double)cell_w));
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
