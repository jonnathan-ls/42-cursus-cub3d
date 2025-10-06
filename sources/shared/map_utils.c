/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/**
 * Validates if coordinates are within map boundaries.
 * @param eng Pointer to the engine structure.
 * @param map_x X coordinate in the map grid.
 * @param map_y Y coordinate in the map grid.
 * @return 1 if valid, 0 otherwise.
 */
int	is_valid_map_coords(t_engine *eng, int map_x, int map_y)
{
	if (!eng || !eng->map)
		return (0);
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_x >= eng->map_width)
		return (0);
	if (map_y >= eng->map_height)
		return (0);
	return (1);
}

/**
 * Returns 1 if the tile at (map_x, map_y)
 * is walkable (not a wall or door), 0 otherwise.
 * @param eng Pointer to the engine structure.
 * @param map_x X coordinate in the map grid.
 * @param map_y Y coordinate in the map grid.
 * @return 1 if walkable, 0 otherwise.
 * @note Walkable tiles are those that are not '1' (wall) or 'D' (door).
 */
int	is_walkable_tile(t_engine *eng, int map_x, int map_y)
{
	if (!is_valid_map_coords(eng, map_x, map_y))
		return (0);
	if (eng->map[map_y][map_x] == '1')
		return (0);
	if (eng->map[map_y][map_x] == 'D')
		return (0);
	return (1);
}

/**
 * Retrieves the character at map coordinates.
 * @param eng Pointer to the engine structure.
 * @param map_x X coordinate in the map grid.
 * @param map_y Y coordinate in the map grid.
 * @return Character at position or '1' if invalid.
 */
char	get_map_tile(t_engine *eng, int map_x, int map_y)
{
	if (!is_valid_map_coords(eng, map_x, map_y))
		return ('1');
	return (eng->map[map_y][map_x]);
}
