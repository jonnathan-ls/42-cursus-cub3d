/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:04 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/20 08:05:15 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Checks if character is valid for map.
 * @param c Character to validate.
 * @return 1 if valid, 0 otherwise.
 * @note Valid: 0,1,space,N,S,E,W,D.
 */
static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == 'D')
		return (1);
	return (0);
}

/**
 * Validates all characters in map grid.
 * @param map Pointer to map structure.
 * @return 0 if all valid, -1 otherwise.
 */
int	validate_map_chars(t_map *map)
{
	int	y;
	int	x;

	if (!map || !map->grid)
		return (parser_error("empty map"));
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!is_valid_char(map->grid[y][x]))
				return (parser_error("invalid map character"));
			x = x + 1;
		}
		y = y + 1;
	}
	return (0);
}
