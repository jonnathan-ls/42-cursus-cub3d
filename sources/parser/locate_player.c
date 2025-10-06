/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:00 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 23:59:04 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Checks if character represents player position.
 * @param c Character to check.
 * @return 1 if player character, 0 otherwise.
 */
static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * Records player position in map structure.
 * @param map Pointer to map structure.
 * @param x X coordinate of player.
 * @param y Y coordinate of player.
 * @param found Pointer to found flag.
 * @return 0 on success, -1 if duplicate player.
 */
static int	note_player(t_map *map, int x, int y, int *found)
{
	if (*found)
		return (parser_error("multiple player positions"));
	map->player_x = x;
	map->player_y = y;
	map->player_dir = map->grid[y][x];
	map->grid[y][x] = '0';
	*found = 1;
	return (0);
}

/**
 * Finds and validates player starting position in map.
 * @param map Pointer to map structure.
 * @return 0 on success, -1 on failure.
 */
int	locate_player(t_map *map)
{
	int	y;
	int	x;
	int	found;

	if (!map || !map->grid)
		return (parser_error("empty map"));
	found = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_player(map->grid[y][x]))
			{
				if (note_player(map, x, y, &found) < 0)
					return (-1);
			}
			x = x + 1;
		}
		y = y + 1;
	}
	if (!found)
		return (parser_error("missing player position"));
	return (0);
}
